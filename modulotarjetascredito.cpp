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
#include "modulotarjetascredito.h"

#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>

ModuloTarjetasCredito::ModuloTarjetasCredito(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[codigoTarjetaCreditoRole] = "codigoTarjetaCredito";
    roles[descripcionTarjetaCreditoRole] = "descripcionTarjetaCredito";


    setRoleNames(roles);
}


TarjetasCredito::TarjetasCredito(const int &codigoTarjetaCredito, const QString &descripcionTarjetaCredito)
    : m_codigoTarjetaCredito(codigoTarjetaCredito), m_descripcionTarjetaCredito(descripcionTarjetaCredito)
{
}

int TarjetasCredito::codigoTarjetaCredito() const
{
    return m_codigoTarjetaCredito;
}
QString TarjetasCredito::descripcionTarjetaCredito() const
{
    return m_descripcionTarjetaCredito;
}


void ModuloTarjetasCredito::agregarTarjetaCredito(const TarjetasCredito &tarjetaCreditos)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_TarjetasCredito << tarjetaCreditos;
    endInsertRows();
}

void ModuloTarjetasCredito::limpiarListaTarjetasCredito(){
    m_TarjetasCredito.clear();
}

void ModuloTarjetasCredito::buscarTarjetasCredito(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from TarjetasCredito where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloTarjetasCredito::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloTarjetasCredito::agregarTarjetaCredito(TarjetasCredito(q.value(rec.indexOf("codigoTarjetaCredito")).toInt(), q.value(rec.indexOf("descripcionTarjetaCredito")).toString()));
            }
        }
    }
}

int ModuloTarjetasCredito::rowCount(const QModelIndex & parent) const {
    return m_TarjetasCredito.count();
}

QVariant ModuloTarjetasCredito::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_TarjetasCredito.count()){
        return QVariant();

    }

    const TarjetasCredito &tarjetaCredito = m_TarjetasCredito[index.row()];

    if (role == codigoTarjetaCreditoRole){
        return tarjetaCredito.codigoTarjetaCredito();

    }
    else if (role == descripcionTarjetaCreditoRole){
        return tarjetaCredito.descripcionTarjetaCredito();

    }

    return QVariant();
}
QString ModuloTarjetasCredito::retornaDescripcionTarjetaCredito(QString _codigoTarjetaCredito) const{

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


        if(query.exec("select descripcionTarjetaCredito from TarjetasCredito where codigoTarjetaCredito='"+_codigoTarjetaCredito+"'")) {
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


