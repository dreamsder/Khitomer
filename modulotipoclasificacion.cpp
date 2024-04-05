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

#include "modulotipoclasificacion.h"
#include <QtSql>
#include <Utilidades/database.h>

ModuloTipoClasificacion::ModuloTipoClasificacion(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoTipoClasificacionRole] = "codigoTipoClasificacion";
    roles[DescripcionTipoClasificacionRole] = "descripcionTipoClasificacion";

    setRoleNames(roles);
}


TipoDeClasificacion::TipoDeClasificacion(const int &codigoTipoClasificacion,const QString &descripcionTipoClasificacion)

    : m_codigoTipoClasificacion(codigoTipoClasificacion),m_descripcionTipoClasificacion(descripcionTipoClasificacion)
{
}


int TipoDeClasificacion::codigoTipoClasificacion() const
{
    return m_codigoTipoClasificacion;
}
QString TipoDeClasificacion::descripcionTipoClasificacion() const
{
    return m_descripcionTipoClasificacion;
}

void ModuloTipoClasificacion::addTipoClasificacion(const TipoDeClasificacion &tipoDeClasificacion)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_TipoDeClasificacion << tipoDeClasificacion;
    endInsertRows();

}

void ModuloTipoClasificacion::clearTipoClasificacion(){

    m_TipoDeClasificacion.clear();

}

void ModuloTipoClasificacion::buscarTipoClasificacion(QString campo, QString datoABuscar){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery q = Database::consultaSql("select * from TipoClasificacion where "+campo+"'"+datoABuscar+"'");

        QSqlRecord rec = q.record();

        ModuloTipoClasificacion::reset();
        if(q.record().count()>0){

            while (q.next()){

                ModuloTipoClasificacion::addTipoClasificacion(TipoDeClasificacion(q.value(rec.indexOf("codigoTipoClasificacion")).toInt(),q.value(rec.indexOf("descripcionTipoClasificacion")).toString()));

            }

        }
    }
}


int ModuloTipoClasificacion::rowCount(const QModelIndex & parent) const {
    return m_TipoDeClasificacion.count();
}




QVariant ModuloTipoClasificacion::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_TipoDeClasificacion.count()){
        return QVariant();

    }

    const TipoDeClasificacion &tipoclasificacion = m_TipoDeClasificacion[index.row()];

    if (role == CodigoTipoClasificacionRole){
        return tipoclasificacion.codigoTipoClasificacion();

    }else if (role == DescripcionTipoClasificacionRole){
        return tipoclasificacion.descripcionTipoClasificacion();

    }


    return QVariant();

}


QString ModuloTipoClasificacion::primerRegistroDeTipoClasificacionEnBase() const {
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery q = Database::consultaSql("select descripcionTipoClasificacion from TipoClasificacion order by codigoTipoClasificacion asc limit 1");
        QSqlRecord rec = q.record();

        if(q.record().count()>0){
            while (q.next()){
                return q.value(rec.indexOf("descripcionTipoClasificacion")).toString();
            }
        }else{
            return "";
        }





    }


}
