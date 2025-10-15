#include "modulolistadescuentosrecargos.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

#include <Utilidades/database.h>

// =====================
//  Modelo (QAbstractListModel)
// =====================

ModuloListaDescuentosRecargos::ModuloListaDescuentosRecargos(QObject *parent)
    : QAbstractListModel(parent)
{
    m_roles[CodigoRole]      = "codigo";
    m_roles[ActivoRole]      = "activo";
    m_roles[TipoRole]        = "tipo";
    m_roles[TipoValorRole]   = "tipoValor";
    m_roles[NombreRole]      = "nombre";
    m_roles[DescripcionRole] = "descripcion";
    m_roles[PorcentajeRole]  = "porcentaje";
    m_roles[MontoRole]       = "monto";
    m_roles[MonedaRole]      = "moneda";
    m_roles[SimboloRole]     = "simbolo";
    m_roles[AplicaSobrePrecioUnitarioRole]     = "aplicaSobrePrecioUnitario";

    setRoleNames(m_roles);

}

int ModuloListaDescuentosRecargos::rowCount(const QModelIndex &parent) const
{
   // Q_UNUSED(parent)
    return m_items.count();
}




QVariant ModuloListaDescuentosRecargos::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    const int row = index.row();
    if (row < 0 || row >= m_items.count()) return QVariant();

    const DescuentoRecargo &it = m_items.at(row);
    switch (role) {
    case CodigoRole:      return it.id();
    case ActivoRole:      return it.activo();
    case TipoRole:        return it.tipo();
    case TipoValorRole:   return it.tipoValor();
    case NombreRole:      return it.descripcion();
    case DescripcionRole: return it.descripcion();
    case PorcentajeRole:  return it.porcentaje();
    case MontoRole:       return it.monto();
    case MonedaRole:      return it.moneda();
    case SimboloRole:     return it.simbolo();
    case AplicaSobrePrecioUnitarioRole:      return it.aplicaSobrePrecioUnitario();
    default:              return QVariant();
    }
}


void ModuloListaDescuentosRecargos::limpiar()
{
    beginResetModel();
    m_items.clear();
    endResetModel();
}


int ModuloListaDescuentosRecargos::retornaIdPorIndice(int indice) const{
    return m_items[indice].id();
}
QString ModuloListaDescuentosRecargos::retornaDescripcionPorIndice(int indice) const{
    return m_items[indice].descripcion();
}

// ----------------- Internos -----------------

static inline QString _likeWrapLower(const QString &s)
{
    return s.isEmpty() ? QString() : QString("%%1%").arg(s.toLower());
}

void ModuloListaDescuentosRecargos::recargarDesdeQuery(QSqlQuery &q)
{
    beginResetModel();
    m_items.clear();

    //qDebug()<<q.size();

    while (q.next()) {
        const int id           = q.value(0).toInt();
        const int activo       = q.value(1).toInt();
        const QString tipo     = q.value(2).toString();
        const QString tipoVal  = q.value(3).toString();
        const QString desc     = q.value(4).toString();
        const double porc      = q.value(5).isNull() ? 0.0 : q.value(5).toDouble();
        const double monto     = q.value(6).isNull() ? 0.0 : q.value(6).toDouble();
        const int moneda       = q.value(7).isNull() ? 0 : q.value(7).toInt();
        const QString simbolo  = q.value(8).toString();
        const int aplicaSobrePrecioUnitario       = q.value(9).toInt();


        m_items.append(DescuentoRecargo(id, activo, tipo, tipoVal, desc, porc, monto, moneda, simbolo,aplicaSobrePrecioUnitario));
    }
    //qDebug()<< q.lastQuery();
    endResetModel();
}

void ModuloListaDescuentosRecargos::cargarQueryBasica(QString &sql, bool incluirMonedaSimbolo) const
{
    sql =
        "SELECT d.id, d.activo, d.tipo, d.tipoValor, d.descripcion, "
        "       d.porcentaje, d.monto, d.moneda, "
        + QString(incluirMonedaSimbolo ? "IFNULL(m.simboloMoneda,'') AS simbolo " : "'' AS simbolo ") + " ,d.aplicaSobrePrecioUnitario " +
        "FROM Descuentos d "
        "LEFT JOIN Monedas m ON m.codigoMoneda = d.moneda "
        "WHERE 1=1 ";
}

void ModuloListaDescuentosRecargos::bindFiltroBasico(QSqlQuery &q,
                                                     const QString &textoFiltro,
                                                     const QString &tipoFiltro) const
{

    if (!tipoFiltro.trimmed().isEmpty()) {
        q.bindValue(":tipoFiltro", tipoFiltro);
        q.bindValue(":tipoFiltro2", tipoFiltro);
    }
    if (!textoFiltro.trimmed().isEmpty()) {
        q.bindValue(":f", _likeWrapLower(textoFiltro.trimmed()));



    }

}

// ----------------- Búsquedas -----------------

static QString expandQueryForLog(const QSqlQuery &q) {
    QString s = q.lastQuery();
    // Reemplazo simple para log (cubre texto; numéricos quedarán entre comillas, está bien para depurar)
    QMapIterator<QString, QVariant> it(q.boundValues());
    while (it.hasNext()) {
        it.next();
        QString key = it.key();
        QString val = it.value().toString();
        // Escapar barra y comillas simples para que el log se parezca a SQL real
        val.replace("\\", "\\\\");
        val.replace("'", "''");
        s.replace(key, "'" + val + "'");
    }
    return s;
}

void ModuloListaDescuentosRecargos::buscarDescuentosRecargos(const QString &textoFiltro,
                                                             const QString &tipoFiltro,
                                                             bool soloActivos)
{
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) { limpiar(); return; }

    QString sql;
    cargarQueryBasica(sql, true); // debe dejar "WHERE 1=1"

    if (soloActivos)
        sql += " AND d.activo = 1 ";

    if (!tipoFiltro.trimmed().isEmpty())
        sql += " AND (d.tipo = :tipoFiltro OR UPPER(d.tipo) = UPPER(:tipoFiltro2)) ";

    if (!textoFiltro.trimmed().isEmpty())
        sql += " AND (d.descripcion LIKE :f1 ESCAPE '\\\\' "
               "  OR d.tipo        LIKE :f2 ESCAPE '\\\\' "
               "  OR d.tipoValor   LIKE :f3 ESCAPE '\\\\') ";

    sql += " ORDER BY d.descripcion ASC";

    QSqlQuery q(db);
    q.prepare(sql);

    if (!tipoFiltro.trimmed().isEmpty()) {
        QString t = tipoFiltro.trimmed();
        q.bindValue(":tipoFiltro",  t);
        q.bindValue(":tipoFiltro2", t);
    }

    if (!textoFiltro.trimmed().isEmpty()) {
        QString f = textoFiltro.trimmed();
        // Escapar lo que afecta a LIKE
        f.replace("\\", "\\\\");  // \  -> \\
        f.replace("%",  "\\%");   // %  -> \%
        f.replace("_",  "\\_");   // _  -> \_
        const QString like = "%" + f + "%";
        q.bindValue(":f1", like);
        q.bindValue(":f2", like);
        q.bindValue(":f3", like);
    }

    // Logs útiles
    //qDebug() << "[SQL prepared]" << q.lastQuery();
    //qDebug() << "[SQL expanded ]" << expandQueryForLog(q);
    //foreach (const QString &k, q.boundValues().keys())
        //qDebug() << "  " << k << "=" << q.boundValues().value(k).toString();

    if (!q.exec()) {
        qWarning() << "ERROR SQL:" << q.lastError().text();
        limpiar();
        return;
    }

    recargarDesdeQuery(q);
}

void ModuloListaDescuentosRecargos::prepararQueryVigentes(QString &sql) const
{
    // d.activo + rangos de FECHA + DÍAS + HORAS (HORAS sin día)
    sql +=
      " AND d.activo = 1 "
      " AND ("
      "   NOT EXISTS (SELECT 1 FROM DescuentosRangoFecha rf WHERE rf.descuento_id = d.id)"
      "   OR EXISTS (SELECT 1 FROM DescuentosRangoFecha rf "
      "              WHERE rf.descuento_id = d.id "
      "                AND STR_TO_DATE(:D1, '%Y-%m-%d') BETWEEN rf.fecha_desde AND rf.fecha_hasta)"
      " )"
      " AND ("
      "   NOT EXISTS (SELECT 1 FROM DescuentosDiaSemana ds WHERE ds.descuento_id = d.id)"
      "   OR EXISTS (SELECT 1 FROM DescuentosDiaSemana ds "
      "              WHERE ds.descuento_id = d.id AND ds.dia_semana = :DOW1)"
      " )"
      " AND ("
      "   NOT EXISTS (SELECT 1 FROM DescuentosRangoHora rh WHERE rh.descuento_id = d.id)"
      "   OR EXISTS ("
      "       SELECT 1 FROM DescuentosRangoHora rh "
      "        WHERE rh.descuento_id = d.id "
      "          AND ("
      "               (rh.hora_hasta > rh.hora_desde "
      "                AND STR_TO_DATE(:T1, '%H:%i:%s') BETWEEN rh.hora_desde AND rh.hora_hasta)"
      "               OR"
      "               (rh.hora_hasta <= rh.hora_desde "
      "                AND (STR_TO_DATE(:T2, '%H:%i:%s') >= rh.hora_desde "
      "                     OR  STR_TO_DATE(:T3, '%H:%i:%s') <= rh.hora_hasta))"
      "          )"
      "   )"
      " )";
}

void ModuloListaDescuentosRecargos::bindMarcaTemporal(QSqlQuery &q,
                                                      const QDate &d, const QTime &t, int dow) const
{
    q.bindValue(":D1",  d.toString("yyyy-MM-dd"));
    q.bindValue(":DOW1", dow);

    const QString ts = t.toString("HH:mm:ss");
    q.bindValue(":T1", ts);
    q.bindValue(":T2", ts);
    q.bindValue(":T3", ts);
}

void ModuloListaDescuentosRecargos::buscarActivosEnFechaHora(const QString &textoFiltro,
                                                             const QString &tipoFiltro,
                                                             const QString &timestampLocal)
{
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) { limpiar(); return; }

    QDateTime dt;
    if (timestampLocal.trimmed().isEmpty())
        dt = QDateTime::currentDateTime();
    else
        dt = QDateTime::fromString(timestampLocal, "yyyy-MM-dd HH:mm:ss");
    if (!dt.isValid()) dt = QDateTime::currentDateTime();

    const QDate d  = dt.date();
    const QTime t  = dt.time();

    // Qt: 1=Lun..7=Dom → sistema: 1=Dom..7=Sáb
    const int qtDow = d.dayOfWeek(); // 1..7 (Mon..Sun)
    const int myDow = (qtDow==7) ? 1 : (qtDow+1);

    QString sql; cargarQueryBasica(sql, true);

    if (!tipoFiltro.trimmed().isEmpty())
        sql += " AND (d.tipo = :tipoFiltro OR UPPER(d.tipo) = UPPER(:tipoFiltro2)) ";
    if (!textoFiltro.trimmed().isEmpty())
        sql += " AND (LOWER(d.descripcion) LIKE :f OR LOWER(d.tipo) LIKE :f OR LOWER(d.tipoValor) LIKE :f) ";

    prepararQueryVigentes(sql);
    sql += " ORDER BY d.descripcion ASC";

    QSqlQuery q(db);
    q.prepare(sql);
    bindFiltroBasico(q, textoFiltro, tipoFiltro);
    bindMarcaTemporal(q, d, t, myDow);

    if (!q.exec()) {
        //qDebug() << "buscarActivosEnFechaHora() error:" << q.lastError().text();
        limpiar();
        return;
    }
    recargarDesdeQuery(q);
}

// ----------------- CRUD principal -----------------

int ModuloListaDescuentosRecargos::insertar(int activo,
                                            const QString &tipo,
                                            const QString &tipoValor,
                                            const QString &descripcion,
                                            const QVariant &porcentaje,
                                            const QVariant &monto,
                                            const QVariant &moneda,
                                            const int &aplicaSobrePrecioUnitario
                                            )
{




    qDebug()<< "aplicaSobrePrecioUnitario: " <<aplicaSobrePrecioUnitario ;


    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return 0;

    QSqlQuery q(db);
    q.prepare("INSERT INTO Descuentos (activo, tipo, tipoValor, descripcion, porcentaje, monto, moneda, aplicaSobrePrecioUnitario) "
              "VALUES (:a, :t, :tv, :d, :p, :m, :mon, :_aplicaSobrePrecioUnitario)");
    q.bindValue(":a",  activo);
    q.bindValue(":t",  tipo);
    q.bindValue(":tv", tipoValor);
    q.bindValue(":d",  descripcion);
    q.bindValue(":p",  (porcentaje.isValid()? porcentaje : QVariant(QVariant::Double)));
    q.bindValue(":m",  (monto.isValid()? monto : QVariant(QVariant::Double)));
    q.bindValue(":mon",(moneda.isValid() && moneda.toInt()>0 ? moneda : QVariant(QVariant::Int)));
    q.bindValue(":_aplicaSobrePrecioUnitario",  aplicaSobrePrecioUnitario);

    if (!q.exec()) return 0;
    return q.lastInsertId().toInt();
}

bool ModuloListaDescuentosRecargos::modificar(int id,
                                              int activo,
                                              const QString &tipo,
                                              const QString &tipoValor,
                                              const QString &descripcion,
                                              const QVariant &porcentaje,
                                              const QVariant &monto,
                                              const QVariant &moneda,
                                              const int &aplicaSobrePrecioUnitario
                                              )
{
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return false;

    qDebug() << "aplicaSobrePrecioUnitario: " << aplicaSobrePrecioUnitario;

    QSqlQuery q(db);
    q.prepare("UPDATE Descuentos SET aplicaSobrePrecioUnitario=:_aplicaSobrePrecioUnitario, activo=:a, tipo=:t, tipoValor=:tv, descripcion=:d, "
              "porcentaje=:p, monto=:m, moneda=:mon WHERE id=:id");
    q.bindValue(":_aplicaSobrePrecioUnitario",  aplicaSobrePrecioUnitario);
    q.bindValue(":a",  activo);
    q.bindValue(":t",  tipo);
    q.bindValue(":tv", tipoValor);
    q.bindValue(":d",  descripcion);
    q.bindValue(":p",  (porcentaje.isValid()? porcentaje : QVariant(QVariant::Double)));
    q.bindValue(":m",  (monto.isValid()? monto : QVariant(QVariant::Double)));
    q.bindValue(":mon",(moneda.isValid() && moneda.toInt()>0 ? moneda : QVariant(QVariant::Int)));
    q.bindValue(":id", id);

    if (!q.exec()) return false;
    return true;
}

bool ModuloListaDescuentosRecargos::eliminar(int id)
{
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return false;

    QSqlQuery q(db);
    q.prepare("DELETE FROM Descuentos WHERE id=:id");
    q.bindValue(":id", id);
    if (!q.exec()) return false;
    return true;
}

// ----------------- Rangos de FECHA -----------------

int ModuloListaDescuentosRecargos::agregarRangoFecha(int descuentoId,
                                                     const QString &desdeYYYYMMDD,
                                                     const QString &hastaYYYYMMDD)
{
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return -1;

    QSqlQuery q(db);
    q.prepare("INSERT INTO DescuentosRangoFecha (descuento_id, fecha_desde, fecha_hasta) "
              "VALUES (:id, :fd, :fh)");
    q.bindValue(":id", descuentoId);
    q.bindValue(":fd", desdeYYYYMMDD);
    q.bindValue(":fh", hastaYYYYMMDD);

    if (!q.exec()) return -2;
    return q.lastInsertId().toInt();
}

bool ModuloListaDescuentosRecargos::eliminarRangoFecha(int rangoId)
{
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return false;

    QSqlQuery q(db);
    q.prepare("DELETE FROM DescuentosRangoFecha WHERE id=:id");
    q.bindValue(":id", rangoId);
    if (!q.exec()) return false;
    return true;
}

bool ModuloListaDescuentosRecargos::eliminarRangoFechas(int descuentoId)
{
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return false;

    QSqlQuery q(db);
    q.prepare("DELETE FROM DescuentosRangoFecha WHERE descuento_id=:descuento_id");
    q.bindValue(":descuento_id", descuentoId);
    if (!q.exec()) return false;
    return true;
}


bool ModuloListaDescuentosRecargos::eliminarRangoHora(int rangoId)
{
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return false;

    QSqlQuery q(db);
    q.prepare("DELETE FROM DescuentosRangoHora WHERE id=:id");
    q.bindValue(":id", rangoId);
    if (!q.exec()) return false;
    return true;
}

bool ModuloListaDescuentosRecargos::eliminarRangoHoras(int descuentoId)
{
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return false;

    QSqlQuery q(db);
    q.prepare("DELETE FROM DescuentosRangoHora  WHERE descuento_id=:descuento_id");
    q.bindValue(":descuento_id", descuentoId);
    if (!q.exec()) return false;
    return true;
}

QVariantList ModuloListaDescuentosRecargos::listarRangosFecha(int descuentoId) const
{
    QVariantList out;
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return out;

    QSqlQuery q(db);
    q.prepare("SELECT id, fecha_desde, fecha_hasta "
              "FROM DescuentosRangoFecha WHERE descuento_id = :id "
              "ORDER BY fecha_desde ASC, fecha_hasta ASC");
    q.bindValue(":id", descuentoId);
    if (!q.exec()) return out;

    while (q.next()) {
        QVariantMap m;
        m["id"]          = q.value(0).toInt();
        m["fecha_desde"] = q.value(1).toString();
        m["fecha_hasta"] = q.value(2).toString();
        out.append(m);
    }
    return out;
}

// ----------------- DÍAS de semana -----------------

int ModuloListaDescuentosRecargos::agregarDiaSemana(int descuentoId, int diaSemana)
{
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return -1;

    QSqlQuery q(db);
    q.prepare("INSERT INTO DescuentosDiaSemana (descuento_id, dia_semana) "
              "VALUES (:id, :dia)");
    q.bindValue(":id", descuentoId);
    q.bindValue(":dia", diaSemana);

    if (!q.exec()) return -2;
    return q.lastInsertId().toInt();
}

bool ModuloListaDescuentosRecargos::eliminarDiaSemana(int descuentoId, int diaSemana)
{
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return false;

    QSqlQuery q(db);
    q.prepare("DELETE FROM DescuentosDiaSemana WHERE descuento_id=:id AND dia_semana=:dia");
    q.bindValue(":id",  descuentoId);
    q.bindValue(":dia", diaSemana);

    if (!q.exec()) return false;
    return true;
}

QVariantList ModuloListaDescuentosRecargos::listarDiasSemana(int descuentoId) const
{
    QVariantList out;
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return out;

    QSqlQuery q(db);
    q.prepare("SELECT dia_semana FROM DescuentosDiaSemana WHERE descuento_id = :id ORDER BY dia_semana ASC");
    q.bindValue(":id", descuentoId);
    if (!q.exec()) return out;

    while (q.next()) {
        QVariantMap m;
        m["dia_semana"] = q.value(0).toInt();
        out.append(m);
    }
    return out;
}

// ----------------- HORARIOS (SIN día) -----------------

int ModuloListaDescuentosRecargos::agregarHorario(int descuentoId, int /*diaSemana*/,
                                                  const QString &horaDesde, const QString &horaHasta)
{
    // Compatibilidad: ignoramos diaSemana y delegamos en la nueva firma
    return agregarHorario(descuentoId, horaDesde, horaHasta);
}

int ModuloListaDescuentosRecargos::agregarHorario(int descuentoId,
                                                  const QString &horaDesde, const QString &horaHasta)
{
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return -1;

    QSqlQuery q(db);
    q.prepare("INSERT INTO DescuentosRangoHora (descuento_id, hora_desde, hora_hasta) "
              "VALUES (:id, :desde, :hasta)");
    q.bindValue(":id", descuentoId);
    q.bindValue(":desde", horaDesde);
    q.bindValue(":hasta", horaHasta);

    if (!q.exec()) return -2;
    return q.lastInsertId().toInt();
}

bool ModuloListaDescuentosRecargos::eliminarHorario(int rangoHoraId)
{
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return false;

    QSqlQuery q(db);
    q.prepare("DELETE FROM DescuentosRangoHora WHERE id=:id");
    q.bindValue(":id", rangoHoraId);

    if (!q.exec()) return false;
    return true;
}

QVariantList ModuloListaDescuentosRecargos::listarHorarios(int descuentoId) const
{
    QVariantList out;
    QSqlDatabase db = Database::connect(); if (!db.isOpen()) db.open();
    if (!db.isValid() || !db.isOpen()) return out;

    QSqlQuery q(db);
    q.prepare("SELECT id, hora_desde, hora_hasta "
              "FROM DescuentosRangoHora WHERE descuento_id = :id "
              "ORDER BY hora_desde ASC, hora_hasta ASC");
    q.bindValue(":id", descuentoId);
    if (!q.exec()) return out;

    while (q.next()) {
        QVariantMap m;
        m["id"]         = q.value(0).toInt();
        m["hora_desde"] = q.value(1).toString();
        m["hora_hasta"] = q.value(2).toString();
        out.append(m);
    }
    return out;
}

int ModuloListaDescuentosRecargos::roleId(const char* name) const {
    const QHash<int, QByteArray> names = roleNames();
    for (QHash<int, QByteArray>::const_iterator it = names.constBegin(); it != names.constEnd(); ++it) {
        if (it.value() == name) return it.key();
    }
    return -1;
}

QVariantMap ModuloListaDescuentosRecargos::obtenerFila(int id) const {
    QVariantMap out;
    const QHash<int, QByteArray> names = roleNames();
    const int idRole     = roleId("id");
    const int codigoRole = roleId("codigo");

    for (int r = 0; r < rowCount(); ++r) {
        QModelIndex idx = index(r, 0);
        int got = -1;
        if (idRole != -1)     got = data(idx, idRole).toInt();
        else if (codigoRole!=-1) got = data(idx, codigoRole).toInt();

        if (got == id) {
            for (QHash<int, QByteArray>::const_iterator it = names.constBegin(); it != names.constEnd(); ++it) {
                out.insert(QString::fromLatin1(it.value()), data(idx, it.key()));
            }
            break;
        }
    }
    return out; // vacío si no se encontró
}
