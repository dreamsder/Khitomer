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

#ifndef MODULOTIPOPROCEDENCIACLIENTE_H
#define MODULOTIPOPROCEDENCIACLIENTE_H

#include <QAbstractListModel>


class TipoProcedenciaCliente
{
public:
   Q_INVOKABLE TipoProcedenciaCliente(const int &codigoTipoProcedenciaCliente,const QString &descripcionTipoProcedenciaCliente);


    int codigoTipoProcedenciaCliente() const;
    QString descripcionTipoProcedenciaCliente() const;

private:
    int m_codigoTipoProcedenciaCliente;
    QString m_descripcionTipoProcedenciaCliente;

};

class ModuloTipoProcedenciaCliente : public QAbstractListModel
{
    Q_OBJECT


public:
    enum TipoProcedenciaClienteRoles {
        codigoTipoProcedenciaClienteRole = Qt::UserRole + 1,
        descripcionTipoProcedenciaClienteRole


    };

    ModuloTipoProcedenciaCliente(QObject *parent = 0);

    Q_INVOKABLE void add(const TipoProcedenciaCliente &TipoProcedenciaCliente);

    Q_INVOKABLE void limpiar();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscar(QString , QString);
    Q_INVOKABLE void buscar();

    Q_INVOKABLE QString retornaDescripcionTipoProcedenciaCliente(QString) const;




private:
    QList<TipoProcedenciaCliente> m_lista;

};


#endif // MODULOTIPOPROCEDENCIACLIENTE_H

