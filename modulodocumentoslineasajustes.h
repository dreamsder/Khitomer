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

#ifndef MODULODDOCUMENTOSLINEASAJUSTES_H
#define MODULODDOCUMENTOSLINEASAJUSTES_H

#include <QAbstractListModel>

class AjusteLineaDTO
{
public:
   Q_INVOKABLE AjusteLineaDTO(


            const quint64 &idAjuste,
            const quint64 &codigoDocumento,
            const quint32 &codigoTipoDocumento,
            const QString &serieDocumento,
            const quint32 &numeroLinea,
            const QString &codigoArticulo,
            const QString &descripcionArticulo,
            const quint32 &idDescuento,
            const QString &descripcion,
            const QString &tipo,       // "DESCUENTO" | "RECARGO"
            const QString &tipoValor,  // "PORCENTAJE" | "MONTO"
            const QVariant &porcentaje, // DECIMAL(45,6) nullable
            const QVariant &monto,      // DECIMAL(45,4) nullable
            const QVariant &moneda,     // INT unsigned nullable
            const QVariant &cotizacionUsada, // DECIMAL(45,8) nullable
            const double &montoAplicado,
            const QVariant &precioUnitBase,       // DECIMAL(45,4) nullable
            const QVariant &precioUnitResultante, // DECIMAL(45,4) nullable
            const QString &usuario,
            const QString &uuid

            );
    quint64 idAjuste() const;
    quint64 codigoDocumento() const;
    quint32 codigoTipoDocumento() const;
    QString serieDocumento() const;
    quint32 numeroLinea() const;
    QString codigoArticulo() const;
    QString descripcionArticulo() const;
    quint32 idDescuento() const;
    QString descripcion() const;
    QString tipo() const;
    QString tipoValor() const;
    QVariant porcentaje() const;
    QVariant monto() const;
    QVariant moneda() const;
    QVariant cotizacionUsada() const;
    double montoAplicado() const;
    QVariant precioUnitBase() const;
    QVariant precioUnitResultante() const;
    QString usuario() const;
    QString uuid() const;


private:
        quint64 m_idAjuste;
        quint64 m_codigoDocumento;
        quint32 m_codigoTipoDocumento;
        QString m_serieDocumento;
        quint32 m_numeroLinea;
        QString m_codigoArticulo;
        QString m_descripcionArticulo;
        quint32 m_idDescuento;
        QString m_descripcion;
        QString m_tipo;       // "DESCUENTO" | "RECARGO"
        QString m_tipoValor;  // "PORCENTAJE" | "MONTO"
        QVariant m_porcentaje; // DECIMAL(45,6) nullable
        QVariant m_monto;      // DECIMAL(45,4) nullable
        QVariant m_moneda;     // INT unsigned nullable
        QVariant m_cotizacionUsada; // DECIMAL(45,8) nullable
        double m_montoAplicado;
        QVariant m_precioUnitBase;       // DECIMAL(45,4) nullable
        QVariant m_precioUnitResultante; // DECIMAL(45,4) nullable
        QString m_usuario;
        QString m_uuid;
};

class ModuloDocumentosLineasAjustes : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AjusteLineaDTORoles {
        IdAjusteRole = Qt::UserRole + 1,
        CodigoDocumentoRole,
        CodigoTipoDocumentoRole,
        SerieDocumentoRole,
        NumeroLineaRole,
        CodigoArticuloRole,
        DescripcionArticuloRole,
        IdDescuentoRole,
        DescripcionRole,
        TipoRole,
        TipoValorRole,
        PorcentajeRole,
        MontoRole,
        MonedaRole,
        CotizacionUsadaRole,
        MontoAplicadoRole,
        PrecioUnitBaseRole,
        PrecioUnitResultanteRole,
        UsuarioRole,
        UuidRole
    };

    ModuloDocumentosLineasAjustes(QObject *parent = 0);

    Q_INVOKABLE void agregar(const AjusteLineaDTO &AjusteLineaDTO);

    Q_INVOKABLE void limpiarLista();


    Q_INVOKABLE bool guardarLineaDocumentoAjustes(QString _consultaInsertLineas) const;

    Q_INVOKABLE bool eliminarLineaDocumentoAjustes(QString _codigoDocumento, QString _codigoTipoDocumento, QString _serieDocumento) const;

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscar(QString codigoDocumento, QString codigoTipoDocumento, QString serieDocumento);



    Q_INVOKABLE quint64 retornaIdAjuste(int index);

    Q_INVOKABLE quint64 retornaCodigoDocumento(int index);

    Q_INVOKABLE quint32 retornaCodigoTipoDocumento(int index);

    Q_INVOKABLE QString retornaSerieDocumento(int index);

    Q_INVOKABLE quint32 retornaNumeroLinea(int index);

    Q_INVOKABLE QString retornaCodigoArticulo(int index);

    Q_INVOKABLE QString retornaDescripcionArticulo(int index);

    Q_INVOKABLE quint32 retornaIdDescuento(int index);

    Q_INVOKABLE QString retornaDescripcion(int index);

    Q_INVOKABLE QString retornaTipo(int index);

    Q_INVOKABLE QString retornaTipoValor(int index);

    Q_INVOKABLE QVariant retornaPorcentaje(int index);

    Q_INVOKABLE QVariant retornaMonto(int index);

    Q_INVOKABLE QVariant retornaMoneda(int index);

    Q_INVOKABLE QVariant retornaCotizacionUsada(int index);

    Q_INVOKABLE double retornaMontoAplicado(int index);

    Q_INVOKABLE QVariant retornaPrecioUnitBase(int index);

    Q_INVOKABLE QVariant retornaPrecioUnitResultante(int index);

    Q_INVOKABLE QString retornaUsuario(int index);

    Q_INVOKABLE QString retornaUuid(int index);







private:
    QList<AjusteLineaDTO> m_AjusteLineaDTO;
};

#endif // MODULODDOCUMENTOSLINEASAJUSTES_H
