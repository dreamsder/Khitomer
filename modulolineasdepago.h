#ifndef MODULOLINEASDEPAGO_H
#define MODULOLINEASDEPAGO_H

/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2022>  <Cristian Montano>

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

#include <QAbstractListModel>

class LineasDePago
{
public:
    Q_INVOKABLE LineasDePago(
            const QString &codigoDocumento,
            const QString &codigoTipoDocumento,
            const QString &serieDocumento,
            const QString &numeroLinea,
            const QString &codigoMedioPago,
            const QString &monedaMedioPago,
            const QString &importePago,
            const QString &cuotas,
            const QString &codigoBanco,
            const QString &codigoTarjetaCredito,
            const QString &numeroCheque,
            const QString &tarjetaCobrada,
            const QString &montoCobrado,
            const QString &codigoTipoCheque,
            const QString &fechaCheque,
            const QString &numeroCuentaBancaria,
            const QString &codigoBancoCuentaBancaria
            );

    QString codigoDocumento() const;
    QString codigoTipoDocumento() const;
    QString serieDocumento() const;
    QString numeroLinea() const;
    QString codigoMedioPago() const;
    QString monedaMedioPago() const;
    QString importePago() const;
    QString cuotas() const;
    QString codigoBanco() const;
    QString codigoTarjetaCredito() const;
    QString numeroCheque() const;
    QString tarjetaCobrada() const;
    QString montoCobrado() const;
    QString codigoTipoCheque() const;
    QString fechaCheque() const;
    QString numeroCuentaBancaria() const;
    QString codigoBancoCuentaBancaria() const;

private:
    QString m_codigoDocumento;
    QString m_codigoTipoDocumento;
    QString m_serieDocumento;
    QString m_numeroLinea;
    QString m_codigoMedioPago;
    QString m_monedaMedioPago;
    QString m_importePago;
    QString m_cuotas;
    QString m_codigoBanco;
    QString m_codigoTarjetaCredito;
    QString m_numeroCheque;
    QString m_tarjetaCobrada;
    QString m_montoCobrado;
    QString m_codigoTipoCheque;
    QString m_fechaCheque;
    QString m_numeroCuentaBancaria;
    QString m_codigoBancoCuentaBancaria;
};

class ModuloLineasDePago : public QAbstractListModel
{
    Q_OBJECT
public:
    enum LineasDePagoRoles {
        codigoDocumentoRole = Qt::UserRole + 1,
        codigoTipoDocumentoRole,
        serieDocumentoRole,
        numeroLineaRole,
        codigoMedioPagoRole,
        monedaMedioPagoRole,
        importePagoRole,
        cuotasRole,
        codigoBancoRole,
        codigoTarjetaCreditoRole,
        numeroChequeRole,
        tarjetaCobradaRole,
        montoCobradoRole,
        codigoTipoChequeRole,
        fechaChequeRole,
        numeroCuentaBancariaRole,
        codigoBancoCuentaBancariaRole

    };

    ModuloLineasDePago(QObject *parent = 0);

    Q_INVOKABLE void agregarLineaDePago(const LineasDePago &LineasDePago);

    Q_INVOKABLE void limpiarListaLineasDePago();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarLineasDePagoChequesDiferidos(QString , QString);

    Q_INVOKABLE void buscarLineasDePagoTarjetasDeCreditoPendientesDePago(QString , QString);

    Q_INVOKABLE bool actualizarLineaDePagoChequeDiferido(QString ,QString ,QString ,QString, QString ) const;

    Q_INVOKABLE bool actualizarLineaDePagoTarjetaCredito(QString ,QString ,QString ,QString, QString ) const;

    Q_INVOKABLE bool verificaMedioPagoEstaUtilizado(QString ,QString ,QString , QString) const;




    Q_INVOKABLE QString retornacodigoDocumento(int);
    Q_INVOKABLE QString retornacodigoTipoDocumento(int);
    Q_INVOKABLE QString retornaSerieDocumento(int);
    Q_INVOKABLE QString retornanumeroLinea(int);
    Q_INVOKABLE QString retornacodigoMedioPago(int);
    Q_INVOKABLE QString retornamonedaMedioPago(int);
    Q_INVOKABLE QString retornaimportePago(int);
    Q_INVOKABLE QString retornacuotas(int);
    Q_INVOKABLE QString retornacodigoBanco(int);
    Q_INVOKABLE QString retornacodigoTarjetaCredito(int);
    Q_INVOKABLE QString retornanumeroCheque(int);
    Q_INVOKABLE QString retornatarjetaCobrada(int);
    Q_INVOKABLE QString retornamontoCobrado(int);
    Q_INVOKABLE QString retornacodigoTipoCheque(int);
    Q_INVOKABLE QString retornafechaCheque(int);
    Q_INVOKABLE QString retornanumeroCuentaBancaria(int);
    Q_INVOKABLE QString retornacodigoBancoCuentaBancaria(int);


    Q_INVOKABLE QString retornaRazonDeCliente(QString , QString , QString serieDocumento) const;
    Q_INVOKABLE QString retornaFechaDocumento(QString , QString , QString _serieDocumento) const;



private:
    QList<LineasDePago> m_LineasDePago;
};

#endif // MODULOLINEASDEPAGO_H
