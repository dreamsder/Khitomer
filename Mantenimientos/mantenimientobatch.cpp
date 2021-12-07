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
#include "mantenimientobatch.h"
#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include <QFileDialog>
#include <QDebug>


MantenimientoBatch::MantenimientoBatch(QObject *parent)
    : QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[codigoTipoCargaMantenimientoBatchRole] = "codigoTipoCargaMantenimientoBatch";
    roles[codigoTipoCampoCargaMantenimientoBatchRole] = "codigoTipoCampoCargaMantenimientoBatch";
    roles[utilizaCargaRole] = "utilizaCarga";

    setRoleNames(roles);
}
CargaMantenimientoBatch::CargaMantenimientoBatch(const QString &codigoTipoCargaMantenimientoBatch,const QString &codigoTipoCampoCargaMantenimientoBatch,const QString &utilizaCarga)
    :m_codigoTipoCargaMantenimientoBatch(codigoTipoCargaMantenimientoBatch)
    ,m_codigoTipoCampoCargaMantenimientoBatch(codigoTipoCampoCargaMantenimientoBatch)
    ,m_utilizaCarga(utilizaCarga)
{
}
QString CargaMantenimientoBatch::codigoTipoCargaMantenimientoBatch() const
{
    return m_codigoTipoCargaMantenimientoBatch;
}
QString CargaMantenimientoBatch::codigoTipoCampoCargaMantenimientoBatch() const
{
    return m_codigoTipoCampoCargaMantenimientoBatch;
}
QString CargaMantenimientoBatch::utilizaCarga() const
{
    return m_utilizaCarga;
}


int MantenimientoBatch::rowCount(const QModelIndex & parent) const {
    return m_CargaMantenimientoBatch.count();
}

QVariant MantenimientoBatch::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_CargaMantenimientoBatch.count()){
        return QVariant();
    }
    const CargaMantenimientoBatch &cargaMantenimientoBatch = m_CargaMantenimientoBatch[index.row()];

    if (role == codigoTipoCargaMantenimientoBatchRole){
        return cargaMantenimientoBatch.codigoTipoCargaMantenimientoBatch();
    }else if(role == codigoTipoCampoCargaMantenimientoBatchRole){
        return cargaMantenimientoBatch.codigoTipoCampoCargaMantenimientoBatch();
    }else if(role == utilizaCargaRole){
        return cargaMantenimientoBatch.utilizaCarga();
    }
    return QVariant();
}
bool MantenimientoBatch::cargarMantenimientoArticulos(){


  //  const QString _titulo="Cargar archivo";
  //  const QString _filtro="Archivos (*.*)";
  //  const QString _otro="";


    //qDebug()<< _nombreArchivo;

    return true;

}
