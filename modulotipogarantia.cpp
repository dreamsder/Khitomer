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

#include "modulotipogarantia.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>

ModuloTipoGarantia::ModuloTipoGarantia(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[codigoTipoGarantiaRole] = "codigoItem";
    roles[descripcionTipoGarantiaRole] = "descripcionItem";


    setRoleNames(roles);
}


TipoGarantia::TipoGarantia(const int &codigoTipoGarantia, const QString &descripcionTipoGarantia)
    : m_codigoTipoGarantia(codigoTipoGarantia), m_descripcionTipoGarantia(descripcionTipoGarantia)
{
}

int TipoGarantia::codigoTipoGarantia() const
{
    return m_codigoTipoGarantia;
}
QString TipoGarantia::descripcionTipoGarantia() const
{
    return m_descripcionTipoGarantia;
}

void ModuloTipoGarantia::agregarTipoGarantia(const TipoGarantia &tipoGarantia)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_TipoGarantia << tipoGarantia;
    endInsertRows();
}

void ModuloTipoGarantia::limpiarListaTipoGarantia(){
    m_TipoGarantia.clear();
}

void ModuloTipoGarantia::buscarTipoGarantia(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from TipoGarantia where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloTipoGarantia::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloTipoGarantia::agregarTipoGarantia(TipoGarantia(q.value(rec.indexOf("codigoTipoGarantia")).toInt(), q.value(rec.indexOf("descripcionTipoGarantia")).toString()));
            }
        }
    }
}

int ModuloTipoGarantia::rowCount(const QModelIndex & parent) const {
    return m_TipoGarantia.count();
}

QVariant ModuloTipoGarantia::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_TipoGarantia.count()){
        return QVariant();

    }

    const TipoGarantia &tipoGarantia = m_TipoGarantia[index.row()];

    if (role == codigoTipoGarantiaRole){
        return tipoGarantia.codigoTipoGarantia();

    }
    else if (role == descripcionTipoGarantiaRole){
        return tipoGarantia.descripcionTipoGarantia();

    }

    return QVariant();
}
QString ModuloTipoGarantia::retornaDescripcionTipoGarantia(QString _codigoIva) const{

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


        if(query.exec("select descripcionTipoGarantia from TipoGarantia where codigoTipoGarantia='"+_codigoIva+"'")) {
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
    }else{
        return "";
    }
}








