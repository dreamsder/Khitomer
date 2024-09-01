/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2024>  <Cristian Montano>

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

#ifndef MODULOREPORTES_H
#define MODULOREPORTES_H

#include <QAbstractListModel>
#include <QSqlQuery>


class Reportes
{
public:
    Q_INVOKABLE Reportes(const qlonglong &codigoReporte, const int &codigoMenuReporte,const QString &descripcionReporte,const QString &consultaSql,const QString &consultaSqlGraficas,
                         const QString &consultaSqlCabezal,

                         const QString &utilizaCodigoCliente,
                         const QString &utilizaCodigoProveedor,
                         const QString &utilizaCodigoArticulo,
                         const QString &utilizaCantidadItemRanking,
                         const QString &utilizaFecha,
                         const QString &utilizaFechaDesde,
                         const QString &utilizaFechaHasta,
                         const QString &utilizaVendedor,
                         const QString &utilizaTipoDocumento,
                         const QString &utilizaSubRubros,
                         const QString &utilizaCodigoLiquidacionCaja,
                         const QString &utilizaRubros,
                         const QString &utilizaDesdeCodigoArticulo,
                         const QString &utilizaHastaCodigoArticulo,
                         const QString &utilizaListaPrecio,
                         const QString &utilizaGraficas,
                         const QString &utilizaCuentaBancaria,
                         const QString &utilizaMonedas,
                         const QString &utilizaPais,
                         const QString &utilizaDepartamento,
                         const QString &utilizaLocalidad,
                         const QString &utilizaCoincidenciaCodigoCliente,
                         const QString &utilizaOrdenEnReporte,
                         const QString &utilizaTipoClasificacionCliente,
                         const QString &utilizaListaPrecio2,
                         const QString &utilizaProcedenciaEnReporte,
                         const QString &utilizaAbrirDocumentos



                         );

    qlonglong codigoReporte() const;
    int codigoMenuReporte() const;
    QString descripcionReporte() const;
    QString consultaSql() const;
    QString consultaSqlGraficas() const;
    QString consultaSqlCabezal() const;


    QString utilizaCodigoCliente() const;
    QString utilizaCodigoProveedor() const;
    QString utilizaCodigoArticulo() const;
    QString utilizaCantidadItemRanking() const;
    QString utilizaFecha() const;
    QString utilizaFechaDesde() const;
    QString utilizaFechaHasta() const;
    QString utilizaVendedor() const;
    QString utilizaTipoDocumento() const;
    QString utilizaSubRubros() const;
    QString utilizaCodigoLiquidacionCaja() const;
    QString utilizaRubros() const;
    QString utilizaDesdeCodigoArticulo() const;
    QString utilizaHastaCodigoArticulo() const;
    QString utilizaListaPrecio() const;
    QString utilizaGraficas() const;
    QString utilizaCuentaBancaria() const;
    QString utilizaMonedas() const;
    QString utilizaPais() const;
    QString utilizaDepartamento() const;
    QString utilizaLocalidad() const;
    QString utilizaCoincidenciaCodigoCliente() const;
    QString utilizaOrdenEnReporte() const;
    QString utilizaTipoClasificacionCliente() const;
    QString utilizaListaPrecio2() const;
    QString utilizaProcedenciaEnReporte() const;
    QString utilizaAbrirDocumentos() const;

private:
    qlonglong m_codigoReporte;
    int m_codigoMenuReporte;
    QString m_descripcionReporte;
    QString m_consultaSql;
    QString m_consultaSqlGraficas;
    QString m_consultaSqlCabezal;

    QString m_utilizaCodigoCliente;
    QString m_utilizaCodigoProveedor;
    QString m_utilizaCodigoArticulo;
    QString m_utilizaCantidadItemRanking;
    QString m_utilizaFecha;
    QString m_utilizaFechaDesde;
    QString m_utilizaFechaHasta;
    QString m_utilizaVendedor;
    QString m_utilizaTipoDocumento;
    QString m_utilizaSubRubros;
    QString m_utilizaCodigoLiquidacionCaja;
    QString m_utilizaRubros;
    QString m_utilizaDesdeCodigoArticulo;
    QString m_utilizaHastaCodigoArticulo;
    QString m_utilizaListaPrecio;
    QString m_utilizaGraficas;
    QString m_utilizaCuentaBancaria;
    QString m_utilizaMonedas;
    QString m_utilizaPais;
    QString m_utilizaDepartamento;
    QString m_utilizaLocalidad;
    QString m_utilizaCoincidenciaCodigoCliente;
    QString m_utilizaOrdenEnReporte;
    QString m_utilizaTipoClasificacionCliente;
    QString m_utilizaListaPrecio2;
    QString m_utilizaProcedenciaEnReporte;
    QString m_utilizaAbrirDocumentos;
};

class ModuloReportes : public QAbstractListModel
{
    Q_OBJECT
public:
    enum IvasRoles {
        CodigoReporteRole = Qt::UserRole + 1,
        CodigoMenuReporteRole,
        DescripcionReporteRole,
        ConsultaSqlRole,
        ConsultaSqlGraficasRole,
        ConsultaSqlCabezalRole,

        utilizaCodigoClienteRole,
        utilizaCodigoProveedorRole,
        utilizaCodigoArticuloRole,
        utilizaCantidadItemRankingRole,
        utilizaFechaRole,
        utilizaFechaDesdeRole,
        utilizaFechaHastaRole,
        utilizaVendedorRole,
        utilizaTipoDocumentoRole,
        utilizaSubRubrosRole,
        utilizaCodigoLiquidacionCajaRole,
        utilizaRubrosRole,
        utilizaDesdeCodigoArticuloRole,
        utilizaHastaCodigoArticuloRole,
        utilizaListaPrecioRole,
        utilizaGraficasRole,
        utilizaCuentaBancariaRole,
        utilizaMonedasRole,
        utilizaPaisRole,
        utilizaDepartamentoRole,
        utilizaLocalidadRole,
        utilizaCoincidenciaCodigoClienteRole,
        utilizaOrdenEnReporteRole,
        utilizaTipoClasificacionClienteRole,
        utilizaListaPrecio2Role,
        utilizaProcedenciaEnReporteRole,
        utilizaAbrirDocumentosRole

    };

    ModuloReportes(QObject *parent = 0);

    Q_INVOKABLE void agregarReportes(const Reportes &Reportes);

    Q_INVOKABLE void limpiarListaReportes();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;


    Q_INVOKABLE void buscarReportes(QString , QString , QString );

    Q_INVOKABLE void buscarReportesSegunMenu(QString campo, QString datoABuscar,QString _codigoPerfil);

    Q_INVOKABLE qlonglong retornarCodigoReporte(int indice) const;

    Q_INVOKABLE QString retornarDescripcionReporte(int indice) const;

    Q_INVOKABLE bool retornaPermisosDelReporte(QString ,QString ) const;

    Q_INVOKABLE QString generarReporte(QString, QString , QString, bool,QString) const;

    Q_INVOKABLE QString generarReporteXLS(QString ,QString ) const;

    Q_INVOKABLE QString retornaDirectorioReporteXLS(QString )const;

    Q_INVOKABLE void insertarReportesMasUsados(QString _codigoReporte,QString _idUsuario);

    Q_INVOKABLE void buscarReportesDeBusquedas(QString campo, QString datoABuscar, QString _codigoPerfil, QString _usuario);


    Q_INVOKABLE QString retornaDescripcionDelReporte(QString) const;

    Q_INVOKABLE QString retornaConfiguracionAlineacionDeColumnaDelReporte(QString ,QString ) const;

    Q_INVOKABLE QString retornaConfiguracionTotalizadorDeColumnaDelReporte(QString ,QString ) const;

    Q_INVOKABLE QString retornaConfiguracionTipoDeDatoDeColumnaDelReporte(QString ,QString ) const;

    Q_INVOKABLE bool retornaSiReportaEstaHabilitadoEnPerfil(QString ,QString ) const;


    Q_INVOKABLE void eliminarReportesPerfil(QString ,QString ) const;

    Q_INVOKABLE void insertarReportesPerfil(QString ,QString ) const ;


    Q_INVOKABLE bool imprimirReporteEnImpresora(QString )const;




    Q_INVOKABLE QString retornaDirectorioReporteWeb() const;
    Q_INVOKABLE QString retornaDirectorioEstiloCssPDF() const;
    Q_INVOKABLE QString retornaDirectorioEstiloCssHTML() const;
    Q_INVOKABLE QString retornaDirectorioJquery_min_js() const;
    Q_INVOKABLE QString retornaDirectorioJs_highcharts_js() const;
    Q_INVOKABLE QString retornaDirectorioJs_modules_exporting_js() const;

    Q_INVOKABLE QString retornaDirectorioReporteCSV()const;





    QString totalizoSumando(QSqlQuery ,int ) const;
    QVariant totalizoSumandoXLS(QSqlQuery ,int ) const;


    QString totalizoContando(QSqlQuery ,int ) const;

    Q_INVOKABLE bool imprimirReporteEnPDF(QString) const;

    Q_INVOKABLE QString generarCSV(QString sqlConsulta, QString, QString, QString fecha) const;

    Q_INVOKABLE QString retornaSqlReporte(QString) const;
    Q_INVOKABLE QString retornaSqlReporteGraficas(QString) const;
    Q_INVOKABLE QString retornaSqlReporteCabezal(QString) const;


    Q_INVOKABLE void abrirNavegadorArchivos()const;








private:
    QList<Reportes> m_Reportes;
};

#endif // MODULOREPORTES_H
