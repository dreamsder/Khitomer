/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2021>  <Cristian Montano>

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

#ifndef MODULOFORMASDEPAGO_H
#define MODULOFORMASDEPAGO_H

#include <QAbstractListModel>




class FormaDePago
{
public:
   Q_INVOKABLE FormaDePago(const int &codigoFormaDePago, const QString &descripcionFormaDePago);

    int codigoFormaDePago() const;
    QString descripcionFormaDePago() const;


private:
    int m_codigoFormaDePago;
    QString m_descripcionFormaDePago;

};

class ModuloFormasDePago : public QAbstractListModel
{
    Q_OBJECT
public:
    enum FormaDePagoRoles {
        CodigoFormaDePagoRole = Qt::UserRole + 1,
        DescripcionFormaDePagoRole

    };

    ModuloFormasDePago(QObject *parent = 0);

    Q_INVOKABLE void agregarFormaDePago(const FormaDePago &FormaDePago);

    Q_INVOKABLE void limpiarListaFormaDePago();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarFormaDePago(QString , QString);

    Q_INVOKABLE QString retornaDescripcionFormaDePago(QString) const;






private:
    QList<FormaDePago> m_FormaDePago;
};

#endif // MODULOFORMASDEPAGO_H
