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
#include "modulomodelosdeimpresion.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>


ModuloModelosDeImpresion::ModuloModelosDeImpresion(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[codigoModeloImpresionRole] = "codigoItem";
    roles[descripcionModeloImpresionRole] = "descripcionItem";


    setRoleNames(roles);
}


ModeloImpresion::ModeloImpresion(const int &codigoModeloImpresion, const QString &descripcionModeloImpresion)
    : m_codigoModeloImpresion(codigoModeloImpresion), m_descripcionModeloImpresion(descripcionModeloImpresion)
{
}

int ModeloImpresion::codigoModeloImpresion() const
{
    return m_codigoModeloImpresion;
}
QString ModeloImpresion::descripcionModeloImpresion() const
{
    return m_descripcionModeloImpresion;
}


void ModuloModelosDeImpresion::agregarModeloImpresion(const ModeloImpresion &modeloImpresion)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ModeloImpresion << modeloImpresion;
    endInsertRows();
}

void ModuloModelosDeImpresion::limpiarListaModeloImpresion(){
    m_ModeloImpresion.clear();
}

void ModuloModelosDeImpresion::buscarModeloImpresion(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from ModeloImpresion where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloModelosDeImpresion::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloModelosDeImpresion::agregarModeloImpresion(ModeloImpresion(q.value(rec.indexOf("codigoModeloImpresion")).toInt(), q.value(rec.indexOf("descripcionModeloImpresion")).toString()));
            }
        }
    }
}

int ModuloModelosDeImpresion::rowCount(const QModelIndex & parent) const {
    return m_ModeloImpresion.count();
}

QVariant ModuloModelosDeImpresion::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_ModeloImpresion.count()){
        return QVariant();

    }

    const ModeloImpresion &modeloImpresion = m_ModeloImpresion[index.row()];

    if (role == codigoModeloImpresionRole){
        return modeloImpresion.codigoModeloImpresion();

    }
    else if (role == descripcionModeloImpresionRole){
        return modeloImpresion.descripcionModeloImpresion();

    }

    return QVariant();
}




QString ModuloModelosDeImpresion::retornaDescripcionModeloImpresion(QString _codigoModeloImpresion) const{
    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect());

        if(query.exec("select descripcionModeloImpresion from ModeloImpresion where codigoModeloImpresion='"+_codigoModeloImpresion+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toString();

                }else{
                    return "";
                }
            }else{return "";}


        }else{
            return "";
        }
    }else{return "";}
}

