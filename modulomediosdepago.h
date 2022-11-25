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


#ifndef MODULOMEDIOSDEPAGO_H
#define MODULOMEDIOSDEPAGO_H

#include <QAbstractListModel>

class MediosDePago
{
public:
   Q_INVOKABLE MediosDePago(const int &codigoMedioPago, const QString &descripcionMedioPago, const int &monedaMedioPago,const int &codigoTipoMedioDePago);

    int codigoMedioPago() const;
    QString descripcionMedioPago() const;
    int monedaMedioPago() const;
    int codigoTipoMedioDePago() const;

private:
    int m_codigoMedioPago;
    QString m_descripcionMedioPago;
    int m_monedaMedioPago;
    int m_codigoTipoMedioDePago;

};

class ModuloMediosDePago : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MediosDePagoRoles {
        CodigoMedioPagoRole = Qt::UserRole + 1,
        DescripcionMedioPagoRole,
        MonedaMedioPagoRole,
        CodigoTipoMedioDePagoRole
    };

    ModuloMediosDePago(QObject *parent = 0);

    Q_INVOKABLE void agregarMediosDePago(const MediosDePago &MediosDePago);

    Q_INVOKABLE void limpiarListaMediosDePago();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarMediosDePago(QString , QString);

    Q_INVOKABLE bool utilizaCuotas(QString ) const;

    Q_INVOKABLE bool utilizaBanco(QString ) const;

    Q_INVOKABLE bool utilizaNumeroCheque(QString ) const;

    Q_INVOKABLE bool utilizaCuentaBancaria(QString ) const;



    Q_INVOKABLE QString retornaDescripcionMedioDePago(QString ) const;

    Q_INVOKABLE QString retornaMonedaMedioDePago(QString ) const;

    Q_INVOKABLE bool guardarLineaMedioDePago(QString , QString , QString , QString , QString , QString , QString, QString , QString , QString, QString , QString, QString, QString , QString , QString , QString , QString _serieDocumento) const;

    Q_INVOKABLE bool eliminarLineaMedioDePagoDocumento( QString , QString, QString)const;

    Q_INVOKABLE int retornaCantidadLineasMedioDePago(QString , QString, QString _serieDocumento) const;

    Q_INVOKABLE QString retornoCuotas(QString , QString , QString , QString _serieDocumento);

    Q_INVOKABLE double retornoImportePago(QString , QString , QString , QString _serieDocumento);

    Q_INVOKABLE QString retornoMonedaMedioPago(QString , QString , QString , QString _serieDocumento);

    Q_INVOKABLE QString retornoCodigoMedioPago(QString , QString , QString , QString _serieDocumento);

    Q_INVOKABLE QString retornoCodigoTarjetaCredito(QString , QString , QString , QString _serieDocumento);
    Q_INVOKABLE QString retornoCodigoBanco(QString , QString , QString , QString _serieDocumento);
    Q_INVOKABLE QString retornoNumeroCheque(QString , QString , QString , QString _serieDocumento);
    Q_INVOKABLE QString retornoFechaCheque(QString ,QString , QString , QString _serieDocumento);
    Q_INVOKABLE QString retornoTipoCheque(QString ,QString , QString , QString _serieDocumento);

    Q_INVOKABLE QString retornoCuentaBancaria(QString , QString , QString , QString _serieDocumento);
    Q_INVOKABLE QString retornoBancoCuentaBancaria(QString ,QString , QString , QString _serieDocumento);

    Q_INVOKABLE QString retornoCodigoDocumentoCheque(QString ,QString , QString , QString _serieDocumento);
    Q_INVOKABLE bool retornoEsDiferidoCheque(QString ,QString , QString , QString _serieDocumento);
    Q_INVOKABLE QString retornoCodigoTipoDocumentoCheque(QString ,QString , QString , QString _serieDocumento);
    Q_INVOKABLE QString retornoNumeroLineaDocumentoCheque(QString ,QString , QString , QString _serieDocumento);

    Q_INVOKABLE QString retornoSerieDocumentoCheque(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento);






private:
    QList<MediosDePago> m_MediosDePago;
};

#endif // MODULOMEDIOSDEPAGO_H
