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
#ifndef MODULOTARJETASCREDITO_H
#define MODULOTARJETASCREDITO_H

#include <QAbstractListModel>


class TarjetasCredito
{
public:
   Q_INVOKABLE TarjetasCredito(const int &codigoTarjetaCredito, const QString &descripcionTarjetaCredito);

    int codigoTarjetaCredito() const;
    QString descripcionTarjetaCredito() const;


private:
    int m_codigoTarjetaCredito;
    QString m_descripcionTarjetaCredito;

};

class ModuloTarjetasCredito : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TarjetasCreditoRoles {
        codigoTarjetaCreditoRole = Qt::UserRole + 1,
        descripcionTarjetaCreditoRole
    };

    ModuloTarjetasCredito(QObject *parent = 0);

    Q_INVOKABLE void agregarTarjetaCredito(const TarjetasCredito &TarjetasCredito);

    Q_INVOKABLE void limpiarListaTarjetasCredito();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarTarjetasCredito(QString , QString);

    Q_INVOKABLE QString retornaDescripcionTarjetaCredito(QString) const;

private:
    QList<TarjetasCredito> m_TarjetasCredito;
};

#endif // MODULOTARJETASCREDITO_H
