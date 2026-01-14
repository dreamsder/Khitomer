/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2025>  <Cristian Montano>

Este archivo es parte de Khitomer.

Khitomer es software libre: usted puede redistribuirlo y/o modificarlo
bajo los términos de la Licencia Pública General GNU publicada
por la Fundación para el Software Libre, ya sea la versión 3
de la Licencia, o (a su elección) cualquier versión posterior.

Este programa se distribuye con la esperanza de que sea útil, pero
SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita
MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO.
Consulte los detalles de la Licencia Pública General GNU para obtener
una información más detallada.

Debería haber recibido una copia de la Licencia Pública General GNU
junto a este programa.
En caso contrario, consulte <http://www.gnu.org/licenses/>.
*********************************************************************/
#include "modulobusquedainteligente.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>


ModuloBusquedaInteligente::ModuloBusquedaInteligente(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[codigoItemRole] = "codigoItem";
    roles[tipoItemRole] = "tipoItem";

    setRoleNames(roles);
}


BusquedaInteligente::BusquedaInteligente(const QString &codigoItem, const QString &tipoItem)
    : m_codigoItem(codigoItem), m_tipoItem(tipoItem)
{
}

QString BusquedaInteligente::codigoItem() const
{
    return m_codigoItem;
}
QString BusquedaInteligente::tipoItem() const
{
    return m_tipoItem;
}



void ModuloBusquedaInteligente::agregarBusquedaInteligente(const BusquedaInteligente &busquedaInteligente)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_BusquedaInteligente << busquedaInteligente;
    endInsertRows();
}

void ModuloBusquedaInteligente::limpiarBusquedaInteligente(){
    m_BusquedaInteligente.clear();
}
static QString foldAccents(const QString& s)
{
    QString n = s.normalized(QString::NormalizationForm_D);
    QString out;
    out.reserve(n.size());
    for (int i = 0; i < n.size(); ++i) {
        const QChar c = n.at(i);
        if (c.category() != QChar::Mark_NonSpacing &&
            c.category() != QChar::Mark_SpacingCombining &&
            c.category() != QChar::Mark_Enclosing) {
            out.append(c);
        }
    }
    return out;
}

void ModuloBusquedaInteligente::buscarArticulosInteligente(QString datoABuscar, bool _incluyeInactivos)
{
    Database::chequeaStatusAccesoMysql();
    if (!Database::connect().isOpen() && !Database::connect().open()) {
        qDebug() << "No conecto";
        return;
    }

    // 1) Normaliza: espacios + minúsculas + quitar acentos del INPUT
    QString texto = foldAccents(datoABuscar).toLower().simplified();
    if (texto.isEmpty()) return;

    // 2) Tokeniza
    QStringList tokens = texto.split(' ', QString::SkipEmptyParts);
    if (tokens.isEmpty()) return;

    // Helper: arma (expr RLIKE ? AND expr RLIKE ? AND ...)
    auto buildAndForExpr = [&](const QString& expr) {
        QStringList parts;
        for (int i = 0; i < tokens.size(); ++i)
            parts << QString("%1 RLIKE ?").arg(expr);
        return "(" + parts.join(" AND ") + ")";
    };

    // Expresiones principales (texto)
    QString artDescExt = buildAndForExpr("LOWER(Articulos.descripcionExtendida)");
    QString artDescArt = buildAndForExpr("LOWER(Articulos.descripcionArticulo)");

    // Subqueries “inteligentes” para IVA y Moneda (por descripción)
    // (SELECT codigoIva FROM Ivas WHERE <tokens> LIMIT 1)
    QString ivaSub =
        "Articulos.codigoIva = ("
        "SELECT codigoIva FROM Ivas WHERE "
        + buildAndForExpr("LOWER(Ivas.descripcionIva)") +
        " LIMIT 1)";

    QString monedaSub =
        "Articulos.codigoMoneda = ("
        "SELECT codigoMoneda FROM Monedas WHERE "
        + buildAndForExpr("LOWER(Monedas.descripcionMoneda)") +
        " LIMIT 1)";

    // WHERE base
    QString where =
        "Clientes.tipoCliente=2 AND ("
        + ivaSub + " OR "
        + monedaSub + " OR "
        + artDescExt + " OR "
        + artDescArt +
        ")";

    if (!_incluyeInactivos) {
        where = "Articulos.activo='1' AND " + where;
    }

    QSqlQuery q(Database::connect());
    q.prepare(
        "SELECT Articulos.codigoArticulo AS codigoItem, 'ARTICULO' AS tipoItem "
        "FROM Articulos "
        "JOIN Clientes ON Articulos.codigoProveedor=Clientes.codigoCliente "
        "           AND Articulos.tipoCliente=Clientes.tipoCliente "
        "WHERE " + where + " "
        "ORDER BY CAST(Articulos.codigoArticulo AS UNSIGNED)"
    );

    // 3) Bind de patrones:
    // Orden IMPORTANTE: coincide con cómo construimos el WHERE:
    // - Ivas.descripcionIva: tokens
    // - Monedas.descripcionMoneda: tokens
    // - Articulos.descripcionExtendida: tokens
    // - Articulos.descripcionArticulo: tokens
    auto bindTokens = [&]() {
        for (int i = 0; i < tokens.size(); ++i) {
            QString t = QRegExp::escape(tokens[i]);
            q.addBindValue("([[:<:]]" + t + "[^[:space:]]*)");
        }
    };

    bindTokens(); // IVA
    bindTokens(); // Moneda
    bindTokens(); // desc extendida
    bindTokens(); // desc articulo

    if (!q.exec()) {
        qDebug() << "Error SQL:" << q.lastError().text();
        return;
    }

    ModuloBusquedaInteligente::reset();
    QSqlRecord rec = q.record();

    while (q.next()) {
        ModuloBusquedaInteligente::agregarBusquedaInteligente(
            BusquedaInteligente(
                q.value(rec.indexOf("codigoItem")).toString(),
                q.value(rec.indexOf("tipoItem")).toString()
            )
        );
    }
}


/*
void ModuloBusquedaInteligente::buscarArticulosInteligente(QString datoABuscar,bool _incluyeInactivos){



    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery q;

        if(_incluyeInactivos){
            q = Database::consultaSql("select Articulos.codigoArticulo'codigoItem', 'ARTICULO' as 'tipoItem' from Articulos join Clientes on Articulos.codigoProveedor=Clientes.codigoCliente and Articulos.tipoCliente=Clientes.tipoCliente where  Clientes.tipoCliente=2  and (Articulos.codigoIva=(SELECT codigoIva FROM Ivas where descripcionIva rlike '"+datoABuscar+"' limit 1)  or Articulos.codigoMoneda=(SELECT codigoMoneda FROM Monedas where descripcionMoneda rlike '"+datoABuscar+"' limit 1) or Articulos.descripcionExtendida rlike '"+datoABuscar+"' or Articulos.descripcionArticulo rlike '"+datoABuscar+"') order by cast(Articulos.codigoArticulo as unsigned) ");
        }else{
            q = Database::consultaSql("select Articulos.codigoArticulo'codigoItem', 'ARTICULO' as 'tipoItem' from Articulos join Clientes on Articulos.codigoProveedor=Clientes.codigoCliente and Articulos.tipoCliente=Clientes.tipoCliente where activo='1' and Clientes.tipoCliente=2  and (Articulos.codigoIva=(SELECT codigoIva FROM Ivas where descripcionIva rlike '"+datoABuscar+"' limit 1)  or codigoMoneda=(SELECT codigoMoneda FROM Monedas where descripcionMoneda rlike '"+datoABuscar+"' limit 1) or descripcionExtendida rlike '"+datoABuscar+"' or descripcionArticulo rlike '"+datoABuscar+"') order by cast(codigoArticulo as unsigned) ");
        }


        QSqlRecord rec = q.record();

        ModuloBusquedaInteligente::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloBusquedaInteligente::agregarBusquedaInteligente(BusquedaInteligente(q.value(rec.indexOf("codigoItem")).toString(), q.value(rec.indexOf("tipoItem")).toString()));
            }
        }
    }
}*/

static QString foldAccentsArticulos(const QString& s)
{
    QString n = s.normalized(QString::NormalizationForm_D);
    QString out;
    out.reserve(n.size());
    for (int i = 0; i < n.size(); ++i) {
        const QChar c = n.at(i);
        if (c.category() != QChar::Mark_NonSpacing &&
            c.category() != QChar::Mark_SpacingCombining &&
            c.category() != QChar::Mark_Enclosing) {
            out.append(c);
        }
    }
    return out;
}


void ModuloBusquedaInteligente::buscarClientesInteligente(QString datoABuscar)
{
    Database::chequeaStatusAccesoMysql();
    if (!Database::connect().isOpen() && !Database::connect().open()) {
        qDebug() << "No conecto";
        return;
    }

    // 1) Normaliza: espacios + minúsculas + quitar acentos del INPUT
    QString texto = foldAccentsArticulos(datoABuscar).toLower().simplified();
    if (texto.isEmpty()) return;

    // 2) Tokeniza
    QStringList tokens = texto.split(' ', QString::SkipEmptyParts);
    if (tokens.isEmpty()) return;

    auto buildAndForColumn = [&](const QString& col) {
        QStringList parts;
        for (int i = 0; i < tokens.size(); ++i)
            parts << QString("%1 RLIKE ?").arg(col);
        return "(" + parts.join(" AND ") + ")";
    };

    // IMPORTANTE: si querés case-insensitive, podés forzar LOWER(col)
    // (aunque esto puede empeorar performance). Mejor es collation apropiada.
    QString where =
        "Clientes.tipoCliente=1 AND ("
        + buildAndForColumn("LOWER(razonSocial)") + " OR "
        + buildAndForColumn("LOWER(direccion)")   + " OR "
        + buildAndForColumn("LOWER(rut)")         + " OR "
        + buildAndForColumn("LOWER(nombreCliente)")
        + ")";

    QSqlQuery q(Database::connect());
    q.prepare(
        "SELECT Clientes.codigoCliente AS codigoItem, 'CLIENTE' AS tipoItem "
        "FROM Clientes "
        "JOIN TipoCliente ON Clientes.tipoCliente=TipoCliente.codigoTipoCliente "
        "JOIN TipoClasificacion ON Clientes.tipoClasificacion=TipoClasificacion.codigoTipoClasificacion "
        "WHERE " + where
    );

    // 3) Bind: patrón por token (prefijo de palabra)
    //    ([[:<:]]token[^[:space:]]*)  => token al inicio de una palabra, y permite continuar
    for (int col = 0; col < 4; ++col) {
        for (int i = 0; i < tokens.size(); ++i) {
            QString t = QRegExp::escape(tokens[i]);
            q.addBindValue("([[:<:]]" + t + "[^[:space:]]*)");
        }
    }

    if (!q.exec()) {
        qDebug() << "Error SQL:" << q.lastError().text();
        return;
    }

    ModuloBusquedaInteligente::reset();
    QSqlRecord rec = q.record();

    while (q.next()) {
        ModuloBusquedaInteligente::agregarBusquedaInteligente(
            BusquedaInteligente(
                q.value(rec.indexOf("codigoItem")).toString(),
                q.value(rec.indexOf("tipoItem")).toString()
            )
        );
    }
}


/*
void ModuloBusquedaInteligente::buscarClientesInteligente(QString datoABuscar){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery q = Database::consultaSql("select Clientes.codigoCliente'codigoItem', 'CLIENTE' as 'tipoItem'  from Clientes join TipoCliente on Clientes.tipoCliente=TipoCliente.codigoTipoCliente join TipoClasificacion on Clientes.tipoClasificacion=TipoClasificacion.codigoTipoClasificacion where Clientes.tipoCliente=1 and (razonSocial rlike '"+datoABuscar+"' or direccion rlike '"+datoABuscar+"' or rut rlike '"+datoABuscar+"' or nombreCliente rlike '"+datoABuscar+"')");
        QSqlRecord rec = q.record();

        ModuloBusquedaInteligente::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloBusquedaInteligente::agregarBusquedaInteligente(BusquedaInteligente(q.value(rec.indexOf("codigoItem")).toString(), q.value(rec.indexOf("tipoItem")).toString()));
            }
        }
    }
}*/


void ModuloBusquedaInteligente::buscarProveedorInteligente(QString datoABuscar)
{
    Database::chequeaStatusAccesoMysql();
    if (!Database::connect().isOpen() && !Database::connect().open()) {
        qDebug() << "No conecto";
        return;
    }

    // 1) Normaliza: espacios + minúsculas + quitar acentos del INPUT
    QString texto = foldAccents(datoABuscar).toLower().simplified();
    if (texto.isEmpty()) return;

    // 2) Tokeniza
    QStringList tokens = texto.split(' ', QString::SkipEmptyParts);
    if (tokens.isEmpty()) return;

    // Helper: arma (col RLIKE ? AND col RLIKE ? AND ...)
    auto buildAndForColumn = [&](const QString& col) {
        QStringList parts;
        for (int i = 0; i < tokens.size(); ++i)
            parts << QString("%1 RLIKE ?").arg(col);
        return "(" + parts.join(" AND ") + ")";
    };

    // 3) Cada columna debe contener TODOS los tokens (y luego OR entre columnas)
    QString where =
        "Clientes.tipoCliente=2 AND ("
        + buildAndForColumn("LOWER(razonSocial)") + " OR "
        + buildAndForColumn("LOWER(direccion)")   + " OR "
        + buildAndForColumn("LOWER(rut)")         + " OR "
        + buildAndForColumn("LOWER(nombreCliente)")
        + ")";

    QSqlQuery q(Database::connect());
    q.prepare(
        "SELECT Clientes.codigoCliente AS codigoItem, 'PROVEEDOR' AS tipoItem "
        "FROM Clientes "
        "JOIN TipoCliente ON Clientes.tipoCliente=TipoCliente.codigoTipoCliente "
        "JOIN TipoClasificacion ON Clientes.tipoClasificacion=TipoClasificacion.codigoTipoClasificacion "
        "WHERE " + where
    );

    // 4) Bind: patrón por token (prefijo de palabra)
    //    ([[:<:]]token[^[:space:]]*) => token al inicio de una palabra, permite continuar
    for (int col = 0; col < 4; ++col) {
        for (int i = 0; i < tokens.size(); ++i) {
            QString t = QRegExp::escape(tokens[i]);
            q.addBindValue("([[:<:]]" + t + "[^[:space:]]*)");
        }
    }

    if (!q.exec()) {
        qDebug() << "Error SQL:" << q.lastError().text();
        return;
    }

    ModuloBusquedaInteligente::reset();
    QSqlRecord rec = q.record();

    while (q.next()) {
        ModuloBusquedaInteligente::agregarBusquedaInteligente(
            BusquedaInteligente(
                q.value(rec.indexOf("codigoItem")).toString(),
                q.value(rec.indexOf("tipoItem")).toString()
            )
        );
    }
}

/*void ModuloBusquedaInteligente::buscarProveedorInteligente(QString datoABuscar){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery q = Database::consultaSql("select Clientes.codigoCliente'codigoItem', 'PROVEEDOR' as 'tipoItem'  from Clientes join TipoCliente on Clientes.tipoCliente=TipoCliente.codigoTipoCliente join TipoClasificacion on Clientes.tipoClasificacion=TipoClasificacion.codigoTipoClasificacion where Clientes.tipoCliente=2 and (razonSocial rlike '"+datoABuscar+"' or direccion rlike '"+datoABuscar+"' or rut rlike '"+datoABuscar+"' or nombreCliente rlike '"+datoABuscar+"')");
        QSqlRecord rec = q.record();

        ModuloBusquedaInteligente::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloBusquedaInteligente::agregarBusquedaInteligente(BusquedaInteligente(q.value(rec.indexOf("codigoItem")).toString(), q.value(rec.indexOf("tipoItem")).toString()));
            }
        }
    }
}*/

int ModuloBusquedaInteligente::rowCount(const QModelIndex & parent) const {
    return m_BusquedaInteligente.count();
}

QVariant ModuloBusquedaInteligente::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_BusquedaInteligente.count()){
        return QVariant();

    }

    const BusquedaInteligente &busquedaInteligente = m_BusquedaInteligente[index.row()];

    if (role == codigoItemRole){
        return busquedaInteligente.codigoItem();

    }
    else if (role == tipoItemRole){
        return busquedaInteligente.tipoItem();

    }
    return QVariant();
}


