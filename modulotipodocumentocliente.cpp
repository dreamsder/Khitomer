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
#include "modulotipodocumentocliente.h"
#include <QtSql>
#include <Utilidades/database.h>


ModuloTipoDocumentoCliente::ModuloTipoDocumentoCliente(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[codigoTipoDocumentoClienteRole] = "codigoTipoDocumentoCliente";
    roles[descripcionTipoDocumentoClienteRole] = "descripcionTipoDocumentoCliente";

    setRoleNames(roles);

}


TipoDocumentoCliente::TipoDocumentoCliente(const int &codigoTipoDocumentoCliente,const QString &descripcionTipoDocumentoCliente)

    : m_codigoTipoDocumentoCliente(codigoTipoDocumentoCliente),m_descripcionTipoDocumentoCliente(descripcionTipoDocumentoCliente)
{
}


int TipoDocumentoCliente::codigoTipoDocumentoCliente() const
{
    return m_codigoTipoDocumentoCliente;
}
QString TipoDocumentoCliente::descripcionTipoDocumentoCliente() const
{
    return m_descripcionTipoDocumentoCliente;
}

void ModuloTipoDocumentoCliente::add(const TipoDocumentoCliente &aux)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_lista << aux;
    endInsertRows();
}

void ModuloTipoDocumentoCliente::limpiar(){
    m_lista.clear();
}

void ModuloTipoDocumentoCliente::buscar(QString campo, QString datoABuscar){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery q = Database::consultaSql("select * from CFE_TipoDocumentoCliente where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloTipoDocumentoCliente::reset();
        if(q.record().count()>0){

            while (q.next()){

                ModuloTipoDocumentoCliente::add(TipoDocumentoCliente(q.value(rec.indexOf("codigoTipoDocumentoCliente")).toInt(),q.value(rec.indexOf("descripcionTipoDocumentoCliente")).toString()));

            }
        }

    }
}

void ModuloTipoDocumentoCliente::buscar(){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery q = Database::consultaSql("select * from CFE_TipoDocumentoCliente;");
        QSqlRecord rec = q.record();

        ModuloTipoDocumentoCliente::reset();
        if(q.record().count()>0){

            while (q.next()){

                ModuloTipoDocumentoCliente::add(TipoDocumentoCliente(q.value(rec.indexOf("codigoTipoDocumentoCliente")).toInt(),q.value(rec.indexOf("descripcionTipoDocumentoCliente")).toString()));

            }
        }
    }
}


QString ModuloTipoDocumentoCliente::retornaDescripcionTipoDocumentoCliente(QString codigoTipoDocumentoCliente) const {
    QString _valor="";
    for (int var = 0; var < m_lista.size(); ++var) {
        if(QString::number(m_lista[var].codigoTipoDocumentoCliente())==codigoTipoDocumentoCliente ){

            _valor= m_lista[var].descripcionTipoDocumentoCliente();

        }
    }
    return _valor;


    /*
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

        if(query.exec("select descripcionTipoDocumentoCliente from CFE_TipoDocumentoCliente   where codigoTipoDocumentoCliente='"+codigoTipoDocumentoCliente+"'")) {

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
    }*/
}


int ModuloTipoDocumentoCliente::rowCount(const QModelIndex & parent) const {
    return m_lista.count();
}

QVariant ModuloTipoDocumentoCliente::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_lista.count()){
        return QVariant();

    }
    const TipoDocumentoCliente &aux = m_lista[index.row()];

    if (role == codigoTipoDocumentoClienteRole){
        return aux.codigoTipoDocumentoCliente();

    }else if (role == descripcionTipoDocumentoClienteRole){
        return aux.descripcionTipoDocumentoCliente();

    }
    return QVariant();
}
