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

#include "modulolistaimpresoras.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include <QPrinterInfo>
#include <QList>

static QList<QPrinterInfo> list = QPrinterInfo::availablePrinters();

ModuloListaImpresoras::ModuloListaImpresoras(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[NombreImpresoraRole] = "nombreImpresora";

    setRoleNames(roles);
}


Impresoras::Impresoras(const QString &nombreImpresora)
    : m_nombreImpresora(nombreImpresora)
{
}

QString Impresoras::nombreImpresora() const
{
    return m_nombreImpresora;
}


void ModuloListaImpresoras::agregarImpresoras(const Impresoras &impresoras)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Impresoras << impresoras;
    endInsertRows();
}

void ModuloListaImpresoras::limpiarListaImpresoras(){
    m_Impresoras.clear();
}

void ModuloListaImpresoras::buscarImpresoras(){


    list = QPrinterInfo::availablePrinters();
    list = QPrinterInfo::availablePrinters();
    list = QPrinterInfo::availablePrinters();

    int totallist=list.count();

    if(totallist!=0)
        for(int i=0; i < totallist;i++){
            ModuloListaImpresoras::agregarImpresoras(Impresoras(list.value(i).printerName()));
        }
}

int ModuloListaImpresoras::rowCount(const QModelIndex & parent) const {
    return m_Impresoras.count();
}

QVariant ModuloListaImpresoras::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Impresoras.count()){
        return QVariant();

    }

    const Impresoras &impresoras = m_Impresoras[index.row()];

    if (role == NombreImpresoraRole){
        return impresoras.nombreImpresora();

    }

    return QVariant();
}
