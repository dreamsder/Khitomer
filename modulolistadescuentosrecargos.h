#ifndef MODULOLISTADESCUENTOSRECARGOS_H
#define MODULOLISTADESCUENTOSRECARGOS_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QVariant>
#include <QDateTime>

class DescuentoRecargo
{
public:
    Q_INVOKABLE DescuentoRecargo(const int &id,
                                 const int &activo,           // 1/0
                                 const QString &tipo,         // "DESCUENTO" | "RECARGO"
                                 const QString &tipoValor,    // "PORCENTAJE" | "MONTO"
                                 const QString &descripcion,
                                 const double &porcentaje,
                                 const double &monto,
                                 const int &moneda,
                                 const QString &simbolo,
                                 const int &aplicaSobrePrecioUnitario
                                 )
        : m_id(id), m_activo(activo), m_tipo(tipo), m_tipoValor(tipoValor),
          m_descripcion(descripcion), m_porcentaje(porcentaje),
          m_monto(monto), m_moneda(moneda), m_simbolo(simbolo), m_aplicaSobrePrecioUnitario(aplicaSobrePrecioUnitario)
    {}

    inline int id() const { return m_id; }
    inline int activo() const { return m_activo; }
    inline QString tipo() const { return m_tipo; }
    inline QString tipoValor() const { return m_tipoValor; }
    inline QString descripcion() const { return m_descripcion; }
    inline double porcentaje() const { return m_porcentaje; }
    inline double monto() const { return m_monto; }
    inline int moneda() const { return m_moneda; }
    inline QString simbolo() const { return m_simbolo; }
    inline int aplicaSobrePrecioUnitario() const {return m_aplicaSobrePrecioUnitario;}

private:
    int m_id;
    int m_activo;
    QString m_tipo;
    QString m_tipoValor;
    QString m_descripcion;
    double m_porcentaje;
    double m_monto;
    int m_moneda;
    QString m_simbolo;
    int m_aplicaSobrePrecioUnitario;
};

class ModuloListaDescuentosRecargos : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ModuloListaDescuentosRecargos(QObject *parent = 0);

    enum Roles {
        CodigoRole = Qt::UserRole + 1,
        ActivoRole,
        TipoRole,
        TipoValorRole,
        NombreRole,
        DescripcionRole,
        PorcentajeRole,
        MontoRole,
        MonedaRole,
        SimboloRole,
        AplicaSobrePrecioUnitarioRole
    };

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QHash<int, QByteArray> roleNames() const { return m_roles; }

    Q_INVOKABLE void limpiar();

    // Búsquedas
    Q_INVOKABLE void buscarDescuentosRecargos(const QString &textoFiltro,
                                              const QString &tipoFiltro,
                                              bool soloActivos /*=false*/);

    // Busca SÓLO vigentes en una marca temporal local: "yyyy-MM-dd HH:mm:ss"
    Q_INVOKABLE void buscarActivosEnFechaHora(const QString &textoFiltro,
                                              const QString &tipoFiltro,
                                              const QString &timestampLocal /*""=ahora*/);

    // --------- CRUD PRINCIPAL ----------
    Q_INVOKABLE int insertar(int activo,
                             const QString &tipo,
                             const QString &tipoValor,
                             const QString &descripcion,
                             const QVariant &porcentaje,   // null para MONTO
                             const QVariant &monto,        // null para PORCENTAJE
                             const QVariant &moneda, const int &aplicaSobrePrecioUnitario);      // null/0 si no aplica

    Q_INVOKABLE bool modificar(int id,
                               int activo,
                               const QString &tipo,
                               const QString &tipoValor,
                               const QString &descripcion,
                               const QVariant &porcentaje,
                               const QVariant &monto,
                               const QVariant &moneda, const int &aplicaSobrePrecioUnitario);

    Q_INVOKABLE bool eliminar(int id);

    // --------- RANGOS DE FECHA ----------
    Q_INVOKABLE int  agregarRangoFecha(int descuentoId, const QString &desdeYYYYMMDD, const QString &hastaYYYYMMDD);
    Q_INVOKABLE bool eliminarRangoFecha(int rangoId);
    Q_INVOKABLE bool eliminarRangoFechas(int descuentoId);

    Q_INVOKABLE bool eliminarRangoHoras(int descuentoId);
    Q_INVOKABLE bool eliminarRangoHora(int rangoId);


    Q_INVOKABLE QVariantList listarRangosFecha(int descuentoId) const;

    // --------- DÍAS DE SEMANA (1=Dom..7=Sáb) ----------
    Q_INVOKABLE int  agregarDiaSemana(int descuentoId, int diaSemana);
    Q_INVOKABLE bool eliminarDiaSemana(int descuentoId, int diaSemana);
    Q_INVOKABLE QVariantList listarDiasSemana(int descuentoId) const;

    // --------- HORARIOS (SIN día) ----------
    Q_INVOKABLE int  agregarHorario(int descuentoId, const QString &horaDesde,
                                    const QString &horaHasta);               // NUEVO
    Q_INVOKABLE int  agregarHorario(int descuentoId, int diaSemana,
                                    const QString &horaDesde,
                                    const QString &horaHasta);               // compat: delega en el nuevo
    Q_INVOKABLE bool eliminarHorario(int rangoHoraId);
    Q_INVOKABLE QVariantList listarHorarios(int descuentoId) const;

    Q_INVOKABLE QVariantMap obtenerFila(int id) const;

    Q_INVOKABLE int retornaIdPorIndice(int indice) const;

    Q_INVOKABLE QString retornaDescripcionPorIndice(int indice) const;

private:
    void recargarDesdeQuery(class QSqlQuery &q);
    void cargarQueryBasica(QString &sql, bool incluirMonedaSimbolo) const;
    void bindFiltroBasico(class QSqlQuery &q,
                          const QString &textoFiltro,
                          const QString &tipoFiltro) const;

    void prepararQueryVigentes(QString &sql) const;
    void bindMarcaTemporal(class QSqlQuery &q,
                           const QDate &d, const QTime &t, int dow) const;



private:
    QList<DescuentoRecargo> m_items;
    QHash<int, QByteArray> m_roles;
    int roleId(const char* name) const;
};

#endif // MODULOLISTADESCUENTOSRECARGOS_H
