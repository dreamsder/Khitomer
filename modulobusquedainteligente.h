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

#ifndef MODULOBUSQUEDAINTELIGENTE_H
#define MODULOBUSQUEDAINTELIGENTE_H

#include <QAbstractListModel>

class BusquedaInteligente
{
public:
   Q_INVOKABLE BusquedaInteligente(const QString &codigoItem, const QString &tipoItem);

    QString codigoItem() const;
    QString tipoItem() const;

private:
    QString m_codigoItem;
    QString m_tipoItem;
};

class ModuloBusquedaInteligente : public QAbstractListModel
{
    Q_OBJECT
public:
    enum BusquedaInteligenteRoles {
        codigoItemRole = Qt::UserRole + 1,
        tipoItemRole
    };

    ModuloBusquedaInteligente(QObject *parent = 0);

    Q_INVOKABLE void agregarBusquedaInteligente(const BusquedaInteligente &BusquedaInteligente);

    Q_INVOKABLE void limpiarBusquedaInteligente();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarArticulosInteligente(QString, bool);

    Q_INVOKABLE void buscarClientesInteligente(QString);

    Q_INVOKABLE void buscarProveedorInteligente(QString);

private:
    QList<BusquedaInteligente> m_BusquedaInteligente;
};


#endif // MODULOBUSQUEDAINTELIGENTE_H
