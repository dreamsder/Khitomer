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

#ifndef MODULOLISTAIMPRESORAS_H
#define MODULOLISTAIMPRESORAS_H

#include <QAbstractListModel>

class Impresoras
{
public:
   Q_INVOKABLE Impresoras(const QString &nombreImpresora);

    QString nombreImpresora() const;


private:
    QString m_nombreImpresora;
};

class ModuloListaImpresoras : public QAbstractListModel
{
    Q_OBJECT
public:
    enum IvasRoles {
        NombreImpresoraRole = Qt::UserRole + 1

    };

    ModuloListaImpresoras(QObject *parent = 0);

    Q_INVOKABLE void agregarImpresoras(const Impresoras &Impresoras);

    Q_INVOKABLE void limpiarListaImpresoras();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarImpresoras();



private:
    QList<Impresoras> m_Impresoras;
};

#endif // MODULOLISTAIMPRESORAS_H
