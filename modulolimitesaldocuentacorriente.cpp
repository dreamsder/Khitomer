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

#include "modulolimitesaldocuentacorriente.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>



ModuloLimiteSaldoCuentaCorriente::ModuloLimiteSaldoCuentaCorriente(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[codigoClienteRole] = "codigoCliente";
    roles[tipoClienteRole] = "tipoCliente";
    roles[codigoMonedaRole] = "codigoMoneda";
    roles[limiteSaldoRole] = "limiteSaldo";

    setRoleNames(roles);
}


LimiteSaldoCuentaCorriente::LimiteSaldoCuentaCorriente(const QString &codigoCliente, const QString &tipoCliente,const QString &codigoMoneda,const double &limiteSaldo)
    : m_codigoCliente(codigoCliente), m_tipoCliente(tipoCliente), m_codigoMoneda(codigoMoneda), m_limiteSaldo(limiteSaldo)
{
}

QString LimiteSaldoCuentaCorriente::codigoCliente() const
{
    return m_codigoCliente;
}
QString LimiteSaldoCuentaCorriente::tipoCliente() const
{
    return m_tipoCliente;
}
QString LimiteSaldoCuentaCorriente::codigoMoneda() const
{
    return m_codigoMoneda;
}
double LimiteSaldoCuentaCorriente::limiteSaldo() const
{
    return m_limiteSaldo;
}


void ModuloLimiteSaldoCuentaCorriente::agregar(const LimiteSaldoCuentaCorriente &limiteSaldoCuentaCorriente)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_LimiteSaldoCuentaCorriente << limiteSaldoCuentaCorriente;
    endInsertRows();
}

void ModuloLimiteSaldoCuentaCorriente::limpiar(){
    m_LimiteSaldoCuentaCorriente.clear();
}

void ModuloLimiteSaldoCuentaCorriente::buscar(QString _codigoCliente, QString _tipoCliente){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from LimiteSaldoCuentaCorriente where codigoCliente='"+_codigoCliente+"' and  tipoCliente='"+_tipoCliente+"' ");
        QSqlRecord rec = q.record();

        ModuloLimiteSaldoCuentaCorriente::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloLimiteSaldoCuentaCorriente::agregar(LimiteSaldoCuentaCorriente(q.value(rec.indexOf("codigoCliente")).toString(), q.value(rec.indexOf("tipoCliente")).toString(), q.value(rec.indexOf("codigoMoneda")).toString(), q.value(rec.indexOf("limiteSaldo")).toDouble()));
            }
        }
    }
}

int ModuloLimiteSaldoCuentaCorriente::rowCount(const QModelIndex & parent) const {
    return m_LimiteSaldoCuentaCorriente.count();
}

QVariant ModuloLimiteSaldoCuentaCorriente::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_LimiteSaldoCuentaCorriente.count()){
        return QVariant();

    }

    const LimiteSaldoCuentaCorriente &limiteSaldoCuentaCorriente = m_LimiteSaldoCuentaCorriente[index.row()];

    if (role == codigoClienteRole){
        return limiteSaldoCuentaCorriente.codigoCliente();
    }
    else if (role == tipoClienteRole){
        return limiteSaldoCuentaCorriente.tipoCliente();
    }
    else if (role == codigoMonedaRole){
        return limiteSaldoCuentaCorriente.codigoMoneda();
    }
    else if (role == limiteSaldoRole){
        return limiteSaldoCuentaCorriente.limiteSaldo();
    }

    return QVariant();
}

QVariantMap ModuloLimiteSaldoCuentaCorriente::get(int row) const {
    QVariantMap result;
    QModelIndex idx = index(row, 0);  // Obtiene el QModelIndex de la fila
    if (!idx.isValid())
        return result;
    QHash<int, QByteArray> roles = roleNames();  // Obtiene los nombres de roles
    for (QHash<int, QByteArray>::const_iterator it = roles.constBegin(); it != roles.constEnd(); ++it) {
        // Inserta en el mapa el nombre de rol como clave y el dato de ese rol
        result.insert(QString::fromLatin1(it.value()), idx.data(it.key()));
    }
    return result;
}

