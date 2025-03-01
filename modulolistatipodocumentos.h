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

#ifndef MODULOLISTATIPODOCUMENTOS_H
#define MODULOLISTATIPODOCUMENTOS_H

#include <QAbstractListModel>


class TipoDocumentos
{
public:
    Q_INVOKABLE TipoDocumentos(const int &codigoTipoDocumento,
                               const QString &descripcionTipoDocumento,
                               const QString &utilizaArticulos,
                               const QString &utilizaCodigoBarrasADemanda,
                               const QString &utilizaTotales,
                               const QString &utilizaListaPrecio,
                               const QString &utilizaMediosDePago,
                               const QString &utilizaFechaPrecio,
                               const QString &utilizaFechaDocumento,
                               const QString &utilizaNumeroDocumento,
                               const QString &utilizaSerieDocumento,
                               const QString &serieDocumento,
                               const QString &utilizaVendedor,
                               const QString &utilizaCliente,
                               const QString &utilizaTipoCliente,
                               const QString &utilizaSoloProveedores,
                               const QString &afectaCuentaCorriente,
                               const QString &afectaCuentaCorrienteMercaderia,
                               const QString &afectaStock,
                               const QString &afectaTotales,
                               const QString &utilizaCantidades,
                               const QString &utilizaPrecioManual,
                               const QString &utilizaDescuentoArticulo,
                               const QString &utilizaDescuentoTotal,
                               const QString &emiteEnImpresora,
                               const QString &codigoModeloImpresion,
                               const QString &cantidadCopias,
                               const QString &utilizaObservaciones,
                               const QString &afectaCuentaBancaria,
                               const QString &utilizaCuentaBancaria,
                               const QString &utilizaPagoChequeDiferido,
                               const QString &utilizaSoloMediosDePagoCheque,
                               const QString &esDocumentoDeVenta,
                               const QString &descripcionTipoDocumentoImpresora,
                               const QString &utilizaArticulosInactivos,

                               const QString &utilizaRedondeoEnTotal,
                               const QString &utilizaPrecioManualEnMonedaReferencia,
                               const QString &descripcionCodigoBarrasADemanda,
                               const QString &utilizaListaPrecioManual,
                               const QString &utilizaFormasDePago,
                               const QString &noAfectaIva,
                               const QString &utilizaSeteoDePreciosEnListasDePrecioPorArticulo,

                               const QString &noPermiteFacturarConStockPrevistoCero,
                               const QString &imprimeEnFormatoTicket,
                               const QString &imprimeObservacionesEnTicket,
                               const QString &utilizaComentarios,
                               const QString &cantidadMaximaLineasEnDocumento

                               );


    int codigoTipoDocumento() const;
    QString descripcionTipoDocumento() const;
    QString utilizaArticulos() const;
    QString utilizaCodigoBarrasADemanda() const;
    QString utilizaTotales() const;
    QString utilizaListaPrecio() const;
    QString utilizaMediosDePago() const;
    QString utilizaFechaPrecio() const;
    QString utilizaFechaDocumento() const;
    QString utilizaNumeroDocumento() const;
    QString utilizaSerieDocumento() const;
    QString serieDocumento() const;
    QString utilizaVendedor() const;
    QString utilizaCliente() const;
    QString utilizaTipoCliente() const;
    QString utilizaSoloProveedores() const;
    QString afectaCuentaCorriente() const;
    QString afectaCuentaCorrienteMercaderia() const;
    QString afectaStock() const;
    QString afectaTotales() const;
    QString utilizaCantidades() const;
    QString utilizaPrecioManual() const;
    QString utilizaDescuentoArticulo() const;
    QString utilizaDescuentoTotal() const;
    QString emiteEnImpresora() const;
    QString codigoModeloImpresion() const;
    QString cantidadCopias() const;
    QString utilizaObservaciones() const;
    QString afectaCuentaBancaria() const;
    QString utilizaCuentaBancaria() const;
    QString utilizaPagoChequeDiferido() const;
    QString utilizaSoloMediosDePagoCheque() const;
    QString esDocumentoDeVenta() const;
    QString descripcionTipoDocumentoImpresora() const;
    QString utilizaArticulosInactivos() const;

    QString utilizaRedondeoEnTotal() const;
    QString utilizaPrecioManualEnMonedaReferencia() const;
    QString descripcionCodigoBarrasADemanda() const;
    QString utilizaListaPrecioManual() const;
    QString utilizaFormasDePago() const;
    QString noAfectaIva() const;
    QString utilizaSeteoDePreciosEnListasDePrecioPorArticulo() const;

    QString noPermiteFacturarConStockPrevistoCero()const;

    QString imprimeEnFormatoTicket()const;

    QString imprimeObservacionesEnTicket()const;

    QString utilizaComentarios() const;
    QString cantidadMaximaLineasEnDocumento()const;






private:        
    int m_codigoTipoDocumento;
    QString m_descripcionTipoDocumento;
    QString m_utilizaArticulos;
    QString m_utilizaCodigoBarrasADemanda;
    QString m_utilizaTotales;
    QString m_utilizaListaPrecio;
    QString m_utilizaMediosDePago;
    QString m_utilizaFechaPrecio;
    QString m_utilizaFechaDocumento;
    QString m_utilizaNumeroDocumento;
    QString m_utilizaSerieDocumento;
    QString m_serieDocumento;
    QString m_utilizaVendedor;
    QString m_utilizaCliente;
    QString m_utilizaTipoCliente;
    QString m_utilizaSoloProveedores;
    QString m_afectaCuentaCorriente;
    QString m_afectaCuentaCorrienteMercaderia;
    QString m_afectaStock;
    QString m_afectaTotales;
    QString m_utilizaCantidades;
    QString m_utilizaPrecioManual;
    QString m_utilizaDescuentoArticulo;
    QString m_utilizaDescuentoTotal;
    QString m_emiteEnImpresora;
    QString m_codigoModeloImpresion;
    QString m_cantidadCopias;
    QString m_utilizaObservaciones;
    QString m_afectaCuentaBancaria;
    QString m_utilizaCuentaBancaria;
    QString m_utilizaPagoChequeDiferido;
    QString m_utilizaSoloMediosDePagoCheque;
    QString m_esDocumentoDeVenta;
    QString m_descripcionTipoDocumentoImpresora;
    QString m_utilizaArticulosInactivos;

    QString m_utilizaRedondeoEnTotal;
    QString m_utilizaPrecioManualEnMonedaReferencia;
    QString m_descripcionCodigoBarrasADemanda;
    QString m_utilizaListaPrecioManual;
    QString m_utilizaFormasDePago;
    QString m_noAfectaIva;
    QString m_utilizaSeteoDePreciosEnListasDePrecioPorArticulo;

    QString m_noPermiteFacturarConStockPrevistoCero;


    QString m_imprimeEnFormatoTicket;

    QString m_imprimeObservacionesEnTicket;
    QString m_utilizaComentarios;
    QString m_cantidadMaximaLineasEnDocumento;

};

class ModuloListaTipoDocumentos : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TipoDocumentosRoles {
        codigoTipoDocumentoRole = Qt::UserRole + 1,
        descripcionTipoDocumentoRole,
        utilizaArticulosRole,
        utilizaCodigoBarrasADemandaRole,
        utilizaTotalesRole,
        utilizaListaPrecioRole,
        utilizaMediosDePagoRole,
        utilizaFechaPrecioRole,
        utilizaFechaDocumentoRole,
        utilizaNumeroDocumentoRole,
        utilizaSerieDocumentoRole,
        serieDocumentoRole,
        utilizaVendedorRole,
        utilizaClienteRole,
        utilizaTipoClienteRole,
        utilizaSoloProveedoresRole,
        afectaCuentaCorrienteRole,
        afectaCuentaCorrienteMercaderiaRole,
        afectaStockRole,
        afectaTotalesRole,
        utilizaCantidadesRole,
        utilizaPrecioManualRole,
        utilizaDescuentoArticuloRole,
        utilizaDescuentoTotalRole,
        emiteEnImpresoraRole,
        codigoModeloImpresionRole,
        cantidadCopiasRole,
        utilizaObservacionesRole,
        afectaCuentaBancariaRole,
        utilizaCuentaBancariaRole,
        utilizaPagoChequeDiferidoRole,
        utilizaSoloMediosDePagoChequeRole,
        esDocumentoDeVentaRole,
        descripcionTipoDocumentoImpresoraRole,
        utilizaArticulosInactivosRole,

        utilizaRedondeoEnTotalRole,
        utilizaPrecioManualEnMonedaReferenciaRole,
        descripcionCodigoBarrasADemandaRole,
        utilizaListaPrecioManualRole,
        utilizaFormasDePagoRole,
        noAfectaIvaRole,
        utilizaSeteoDePreciosEnListasDePrecioPorArticuloRole,
        noPermiteFacturarConStockPrevistoCeroRole,
        imprimeEnFormatoTicketRole,
        imprimeObservacionesEnTicketRole,
        utilizaComentariosRole,
        cantidadMaximaLineasEnDocumentoRole



    };

    ModuloListaTipoDocumentos(QObject *parent = 0);

    Q_INVOKABLE void agregarTipoDocumentos(const TipoDocumentos &TipoDocumentos);

    Q_INVOKABLE void limpiarListaTipoDocumentos();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarTipoDocumentos(QString , QString,QString);

    Q_INVOKABLE void buscarTipoDocumentosDefault();

    Q_INVOKABLE void buscarTodosLosTipoDocumentos(QString , QString);

    Q_INVOKABLE QString retornaDescripcionTipoDocumento(QString)const;

    Q_INVOKABLE QString retornaDescripcionCodigoADemanda(QString) const;

    Q_INVOKABLE bool retornaPermisosDelDocumento(QString,QString)const;

    Q_INVOKABLE QString retornaSerieTipoDocumento(QString) const;

    Q_INVOKABLE int ultimoRegistroDeTipoDeDocumento()const;

    Q_INVOKABLE int cantidadMaximaLineasTipoDocumento(QString)const;


    Q_INVOKABLE bool eliminarTipoDocumento(QString) const;

   // Q_INVOKABLE bool retornaTipoDocumentoActivoPorPerfil(QString,QString);

    Q_INVOKABLE void insertarTipoDocumentoPerfil(QString ,QString ) const;

    Q_INVOKABLE void eliminarTipoDocumentoPerfil(QString ,QString ) const;

    Q_INVOKABLE bool convertirStringABool(QString valor) const;


    Q_INVOKABLE int insertarTipoDocumento(QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString ,
            QString,
            QString,
            QString,
            QString, QString,QString, QString );




    Q_INVOKABLE QString retornaValorCampoTipoDocumento(QString  ,QString ) const;
    Q_INVOKABLE bool permiteDevolucionTipoDocumento(QString );

    Q_INVOKABLE bool retornaDocumentoSegunMonedaRedondea(QString ,QString ) const;

    Q_INVOKABLE bool retornaPermiteModificacionMedioPagoPorDeudaContado(QString ,QString,QString ) const;

    Q_INVOKABLE bool esUnTipoDeDocumentoCreditoVenta(QString _codigoTipoDocumento) const;




private:
    QList<TipoDocumentos> m_TipoDocumentos;
};

#endif // MODULOLISTATIPODOCUMENTOS_H
