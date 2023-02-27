/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2023>  <Cristian Montano>

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


#ifndef MODULODOCUMENTOS_H
#define MODULODOCUMENTOS_H

#include <QAbstractListModel>

class Documentos
{
public:
    Q_INVOKABLE Documentos(const qulonglong &codigoDocumento,
                           const int &codigoTipoDocumento,
                           const QString &serieDocumento,
                           const QString &codigoEstadoDocumento

                           ,const QString &codigoCliente
                           ,const int &tipoCliente

                           ,const int &codigoMonedaDocumento

                           ,const QString &fechaEmisionDocumento

                           ,const QString &precioTotalVenta

                           ,const QString &precioSubTotalVenta

                           ,const QString &precioIvaVenta

                           ,const QString &codigoLiquidacion

                           ,const QString &codigoVendedorLiquidacion

                           ,const QString &codigoVendedorComisiona

                           ,const QString &nombreCliente

                           ,const QString &razonSocial

                           ,const QString &descripcionTipoDocumento

                           ,const QString &descripcionEstadoDocumento

                           ,const QString &totalIva1
                           ,const QString &totalIva2
                           ,const QString &totalIva3
                           ,const QString &observaciones

                           ,const QString &numeroCuentaBancaria
                           ,const QString &codigoBanco
                           ,const QString &esDocumentoWeb

                           ,const QString &montoDescuentoTotal

                           ,const QString &saldoClienteCuentaCorriente
                           ,const QString &formaDePago
                           ,const QString &porcentajeDescuentoAlTotal
                           ,const QString &esDocumentoCFE
                           ,const QString &cae_numeroCae
                           ,const QString &cae_serie
                            ,const QString &comentarios

                           );

    qulonglong codigoDocumento() const;
    int codigoTipoDocumento() const;
    QString serieDocumento() const;
    QString codigoEstadoDocumento() const;

    QString codigoCliente() const;
    int tipoCliente() const;
    int codigoMonedaDocumento() const;

    QString fechaEmisionDocumento() const;
    QString precioTotalVenta() const;
    QString precioSubTotalVenta() const;
    QString precioIvaVenta() const;
    QString codigoLiquidacion() const;
    QString codigoVendedorLiquidacion() const;
    QString codigoVendedorComisiona() const;

    QString nombreCliente() const;
    QString razonSocial() const;
    QString descripcionTipoDocumento() const;
    QString descripcionEstadoDocumento() const;

    QString totalIva1() const;
    QString totalIva2() const;
    QString totalIva3() const;
    QString observaciones() const;
    QString numeroCuentaBancaria() const;
    QString codigoBanco() const;
    QString esDocumentoWeb() const;
    QString montoDescuentoTotal() const;

    QString saldoClienteCuentaCorriente() const;
    QString formaDePago() const;
    QString porcentajeDescuentoAlTotal() const;

    QString esDocumentoCFE() const;

    QString cae_numeroCae() const;
    QString cae_serie() const;
    QString comentarios() const;





private:
    qulonglong m_codigoDocumento;
    int m_codigoTipoDocumento;
    QString m_serieDocumento;
    QString m_codigoEstadoDocumento;

    QString m_codigoCliente;
    int m_tipoCliente;
    int m_codigoMonedaDocumento;

    QString m_fechaEmisionDocumento;
    QString m_precioTotalVenta;
    QString m_precioSubTotalVenta;
    QString m_precioIvaVenta;
    QString m_codigoLiquidacion;
    QString m_codigoVendedorLiquidacion;
    QString m_codigoVendedorComisiona;
    QString m_nombreCliente;
    QString m_razonSocial;
    QString m_descripcionTipoDocumento;
    QString m_descripcionEstadoDocumento;
    QString m_totalIva1;
    QString m_totalIva2;
    QString m_totalIva3;
    QString m_observaciones;
    QString m_numeroCuentaBancaria;
    QString m_codigoBanco;
    QString m_esDocumentoWeb;
    QString m_montoDescuentoTotal;

    QString m_saldoClienteCuentaCorriente;
    QString m_formaDePago;
    QString m_porcentajeDescuentoAlTotal;
    QString m_esDocumentoCFE;

    QString m_cae_numeroCae;
    QString m_cae_serie;
    QString m_comentarios;


};

class ModuloDocumentos : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DocumentosRoles {
        CodigoDocumentoRole = Qt::UserRole + 1,
        CodigoTipoDocumentoRole,
        SerieDocumentoRole,
        CodigoEstadoDocumentoRole,
        CodigoClienteRole,
        TipoClienteRole,
        CodigoMonedaDocumentoRole,
        FechaEmisionDocumentoRole,
        PrecioTotalVentaRole,
        PrecioSubTotalVentaRole,
        PrecioIvaVentaRole,
        CodigoLiquidacionRole,
        CodigoVendedorLiquidacionRole,
        CodigoVendedorComisionaRole,

        NombreClienteRole,
        RazonSocialRole,
        DescripcionTipoDocumentoRole,
        DescripcionEstadoDocumentoRole,

        TotalIva1Role,
        TotalIva2Role,
        TotalIva3Role,
        ObservacionRole,
        numeroCuentaBancariaRole,
        codigoBancoRole,
        esDocumentoWebRole,
        montoDescuentoTotalRole,

        saldoClienteCuentaCorrienteRole,
        formaDePagoRole,
        porcentajeDescuentoAlTotalRole,

        esDocumentoCFERole,
        cae_numeroCaeRole,
        cae_serieRole,
        comentariosRole

    };

    ModuloDocumentos(QObject *parent = 0);

    Q_INVOKABLE void agregarDocumento(const Documentos &Documentos);

    Q_INVOKABLE void limpiarListaDocumentos();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarDocumentos(QString , QString);

    Q_INVOKABLE int guardarDocumentos(QString , QString, QString, QString,QString, QString , QString, QString, QString, QString, QString , QString, QString , QString, QString, QString , QString , QString , QString, QString , QString , QString , int , QString, QString, QString, QString, QString) const;

    Q_INVOKABLE bool guardarLineaDocumento(QString) const;

    Q_INVOKABLE void marcoArticulosincronizarWeb(QString _codigoArticulo) const;

    Q_INVOKABLE bool eliminarDocumento(QString , QString, QString _serieDocumento)const;

    Q_INVOKABLE bool eliminarLineaDocumento(QString , QString, QString)const;

    Q_INVOKABLE bool actualizoEstadoDocumento(QString , QString, QString,QString,QString )const;

    Q_INVOKABLE bool actualizoEstadoDocumentoCFE(QString _codigoDocumento, QString _codigoTipoDocumento, QString _estadoDocumento, QString) const;


    Q_INVOKABLE void buscarDocumentosEnLiquidaciones(QString , QString,QString,QString);

    Q_INVOKABLE int retornaCantidadLineasDocumento(QString , QString, QString) const;

    Q_INVOKABLE QString retornoCodigoArticuloDeLineaDocumento(QString , QString, QString, QString _serieDocumento) ;

    Q_INVOKABLE QString retornoCodigoArticuloBarrasDeLineaDocumento(QString , QString, QString, QString _serieDocumento) ;

    Q_INVOKABLE QString retornoCantidadDocumentosPorCliente(QString , QString,QString) ;

    Q_INVOKABLE double retornoPrecioArticuloDeLineaDocumento(QString , QString, QString, QString _serieDocumento);

    Q_INVOKABLE double retornoCostoArticuloMonedaReferenciaDeLineaDocumento(QString , QString, QString,QString _serieDocumento);

    Q_INVOKABLE QString retornoCodigoTipoGarantiaLineaArticuloDeLineaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento);

    Q_INVOKABLE int retornoCantidadArticuloDeLineaDocumento(QString , QString , QString , QString _serieDocumento);

    Q_INVOKABLE double retornoDescuentoLineaArticuloDeLineaDocumento(QString ,QString , QString, QString _serieDocumento );


    Q_INVOKABLE qlonglong retornoCodigoUltimoDocumentoDisponible(QString);

    Q_INVOKABLE bool emitirDocumentoEnImpresora(QString , QString, QString, QString _serieDocumento);

    Q_INVOKABLE bool emitirDocumentoEnImpresoraTicket(QString _codigoDocumento, QString _codigoTipoDocumento, QString _impresora, int cantidadDecimalesMonto, QString _serieDocumento);

    Q_INVOKABLE bool emitirDocumentoEnModoRecibo(QString _codigoDocumento, QString _codigoTipoDocumento, QString _impresora, int cantidadDecimalesMonto, QString _serieDocumento);



    Q_INVOKABLE bool emitirEnvioEnImpresoraTicket(QString _codigoTipoImpresion, QString _impresora, QString _codigoCliente, QString _tipoCliente, QString _observacion);

    Q_INVOKABLE void buscarDocumentosEnMantenimiento(QString , QString, QString,QString);
    Q_INVOKABLE void buscarDocumentosAPagarCuentaCorriente(QString , QString, QString);
    Q_INVOKABLE void buscarDocumentosDePagoCuentaCorriente(QString , QString, QString);


    Q_INVOKABLE int actualizarCuentaCorriente(QString , QString, QString , QString , QString , QString , QString , QString, QString , QString, QString
                                                    , QString, QString _serieDocumentoAPagar, QString _serieDocumentoDePago) const;

    Q_INVOKABLE bool restauroMontoDeudaCuentaCorrienteDocumento(QString , QString ,QString,QString ) const;
    Q_INVOKABLE bool anuloMontosDebitadosCuentaCorriente(QString , QString , QString) const ;


    Q_INVOKABLE bool actualizarDatoExtraLineaDocumento(QString , QString , QString , QString,QString ) const;


    Q_INVOKABLE bool documentoValidoParaCalculoPonderado(QString)const;

    Q_INVOKABLE double retonaCostoPonderadoSegunStock(QString ,qlonglong , double ) const;



    Q_INVOKABLE QString retornaDescripcionEstadoDocumento(QString ) const;

    bool retornaClienteTieneRUT(QString ,QString ) const;

    Q_INVOKABLE bool actualizoSaldoClientePagoContadoDocumento(QString ,QString , QString,QString ) const;



    Q_INVOKABLE QString retornacodigoEstadoDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornatipoClienteDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornacodigoClienteDocumento(QString , QString, QString _serieDocumento)const ;



    Q_INVOKABLE QString retornaserieDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornacodigoVendedorComisionaDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornacodigoLiquidacionDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornacodigoVendedorLiquidacionDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornafechaEmisionDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornacodigoMonedaDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornaprecioIvaVentaDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornaprecioSubTotalVentaDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornaprecioTotalVentaDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornatotalIva1Documento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornatotalIva2Documento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornatotalIva3Documento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornaobservacionesDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornacomentariosDocumento(QString , QString, QString _serieDocumento) const;

    Q_INVOKABLE QString retornaonumeroCuentaBancariaDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornaocodigoBancoDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornaEsDocumentoWebDocumento(QString , QString, QString _serieDocumento) const;
    Q_INVOKABLE QString retornaEsDocumentoCFEDocumento(QString , QString, QString _serieDocumento) const;


    Q_INVOKABLE QString retornaMontoDescuentoTotalDocumento(QString ,QString, QString ) const;
    Q_INVOKABLE QString retornaFormaDePagoDocumento(QString ,QString, QString ) const;
    Q_INVOKABLE QString retornaPorcentajeDescuentoAlTotalDocumento(QString ,QString , QString) const;

    Q_INVOKABLE QString retornaNumeroCFEOriginal(QString , QString , QString _serieDocumento) const;


    Q_INVOKABLE bool existeDocumento(QString _codigoDocumento, QString _codigoTipoDocumento, QString _serieDocumento) const;


    Q_INVOKABLE bool actualizarNumeroCFEDocumento(QString ,QString , QString,QString ) const;




   Q_INVOKABLE bool retornoSiClienteTieneDocumentos(QString )const;

   Q_INVOKABLE bool emitirDocumentoCFEImix(QString _codigoDocumento, QString _codigoTipoDocumento, QString _descripcionEstadoActualDocumento,QString _serieDocumento);

   Q_INVOKABLE bool emitirDocumentoCFEDynamia(QString , QString , QString, QString, QString, QString , QString _serieDocumento);

   Q_INVOKABLE bool emitirDocumentoCFE_Imix_Nube(QString _codigoDocumento,QString _codigoTipoDocumento,QString _numeroDocumentoCFEADevolver,QString _fechaDocumentoCFEADevolver,QString tipoDocumentoCFEADevolver, QString _descripcionEstadoActualDocumento, QString _serieDocumento);


   Q_INVOKABLE bool actualizarInformacionCFEDocumentoDynamia(QString _codigoDocumento, QString _codigoTipoDocumento, QString  _nro,
                                                                 QString _serie,
                                                                 QString _vencimiento,
                                                                 QString _cod_seguridad,
                                                                 QString _cae_id,
                                                                 QString _desde,
                                                                 QString _hasta,
                                                                 QString _qr,
                                                                 QString _idDocGaia
                                                                 , QString _caeTipoDocumentoCFEDescripcion, QString _serieDocumento);




    Q_INVOKABLE qulonglong retornaCodigoDocumentoPorIndice(int indice) const;

    Q_INVOKABLE  int retornaCodigoTipoDocumentoPorIndice(int indice) const;

    Q_INVOKABLE  QString retornaSerieDocumentoPorIndice(int indice) const;

    Q_INVOKABLE  QString retornaTotalDocumentoPorIndice(int indice) const;

    Q_INVOKABLE  QString retornaSaldoCuentaCorrientePorIndice(int indice) const;

    Q_INVOKABLE  int retornaCodigoMonedaPorIndice(int indice) const;

    Q_INVOKABLE  QString retornaFechaDocumentoPorIndice(int indice) const;

    Q_INVOKABLE  QString retornaObservacionesDocumentoPorIndice(int indice) const;

    Q_INVOKABLE  QString retornacomentariosDocumentoPorIndice(int indice) const;


    Q_INVOKABLE bool actualizoComentarios(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento,QString _comentarios   ) const;



private:
    QList<Documentos> m_Documentos;
};

#endif // MODULODOCUMENTOS_H
