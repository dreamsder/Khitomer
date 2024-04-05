#ifndef MODULOTOTALCHEQUESDIFERIDOS_H
#define MODULOTOTALCHEQUESDIFERIDOS_H

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

#include <QAbstractListModel>


class TotalCheques
{
public:
   Q_INVOKABLE TotalCheques(const int &codigoMoneda, const QString &importeTotalChequesDiferidos);

    int codigoMoneda() const;
    QString importeTotalChequesDiferidos() const;


private:
    int m_codigoMoneda;
    QString m_importeTotalChequesDiferidos;

};

class ModuloTotalChequesDiferidos : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TotalChequesRoles {
        codigoMonedaRole = Qt::UserRole + 1,
        importeTotalChequesDiferidosRole
    };

    ModuloTotalChequesDiferidos(QObject *parent = 0);

    Q_INVOKABLE void agregarTotalCheques(const TotalCheques &TotalCheques);

    Q_INVOKABLE void limpiarListaTotalCheques();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarTotalCheques(QString , QString);

    Q_INVOKABLE void buscarTotalOtrosCheques(QString,QString);


private:
    QList<TotalCheques> m_TotalCheques;
};

#endif // MODULOTOTALCHEQUESDIFERIDOS_H
