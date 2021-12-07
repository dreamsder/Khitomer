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

#ifndef MODULOTIPOCHEQUES_H
#define MODULOTIPOCHEQUES_H

#include <QAbstractListModel>


class Cheques
{
public:
   Q_INVOKABLE Cheques(const int &codigoTipoCheque, const QString &descripcionTipoCheque);

    int codigoTipoCheque() const;
    QString descripcionTipoCheque() const;


private:
    int m_codigoTipoCheque;
    QString m_descripcionTipoCheque;

};

class ModuloTipoCheques : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TipoChequesRoles {
        codigoTipoChequeRole = Qt::UserRole + 1,
        descripcionTipoChequeRole
    };

    ModuloTipoCheques(QObject *parent = 0);

    Q_INVOKABLE void agregarCheque(const Cheques &Cheques);

    Q_INVOKABLE void limpiarListaCheques();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarCheques(QString , QString);

    Q_INVOKABLE QString retornaDescripcionCheque(QString) const;

private:
    QList<Cheques> m_Cheques;
};


#endif // MODULOTIPOCHEQUES_H
