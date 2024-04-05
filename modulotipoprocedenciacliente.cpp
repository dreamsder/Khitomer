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

#include "modulotipoprocedenciacliente.h"
#include <QtSql>
#include <Utilidades/database.h>



ModuloTipoProcedenciaCliente::ModuloTipoProcedenciaCliente(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[codigoTipoProcedenciaClienteRole] = "codigoTipoProcedenciaCliente";
    roles[descripcionTipoProcedenciaClienteRole] = "descripcionTipoProcedenciaCliente";

    setRoleNames(roles);

}


TipoProcedenciaCliente::TipoProcedenciaCliente(const int &codigoTipoProcedenciaCliente,const QString &descripcionTipoProcedenciaCliente)

    : m_codigoTipoProcedenciaCliente(codigoTipoProcedenciaCliente),m_descripcionTipoProcedenciaCliente(descripcionTipoProcedenciaCliente)
{
}


int TipoProcedenciaCliente::codigoTipoProcedenciaCliente() const
{
    return m_codigoTipoProcedenciaCliente;
}
QString TipoProcedenciaCliente::descripcionTipoProcedenciaCliente() const
{
    return m_descripcionTipoProcedenciaCliente;
}

void ModuloTipoProcedenciaCliente::add(const TipoProcedenciaCliente &aux)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_lista << aux;
    endInsertRows();
}

void ModuloTipoProcedenciaCliente::limpiar(){
    m_lista.clear();
}

void ModuloTipoProcedenciaCliente::buscar(QString campo, QString datoABuscar){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery q = Database::consultaSql("select * from TipoProcedenciaCliente where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloTipoProcedenciaCliente::reset();
        if(q.record().count()>0){

            while (q.next()){

                ModuloTipoProcedenciaCliente::add(TipoProcedenciaCliente(q.value(rec.indexOf("codigoTipoProcedenciaCliente")).toInt(),q.value(rec.indexOf("descripcionTipoProcedenciaCliente")).toString()));

            }
        }

    }
}

void ModuloTipoProcedenciaCliente::buscar(){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery q = Database::consultaSql("select * from TipoProcedenciaCliente;");
        QSqlRecord rec = q.record();

        ModuloTipoProcedenciaCliente::reset();
        if(q.record().count()>0){

            while (q.next()){

                ModuloTipoProcedenciaCliente::add(TipoProcedenciaCliente(q.value(rec.indexOf("codigoTipoProcedenciaCliente")).toInt(),q.value(rec.indexOf("descripcionTipoProcedenciaCliente")).toString()));

            }
        }
    }
}


QString ModuloTipoProcedenciaCliente::retornaDescripcionTipoProcedenciaCliente(QString codigoTipoProcedenciaCliente) const {

   /* QString _valor="";
    for (int var = 0; var < m_lista.size(); ++var) {
        if(QString::number(m_lista[var].codigoTipoProcedenciaCliente())==codigoTipoProcedenciaCliente){

            _valor= m_lista[var].descripcionTipoProcedenciaCliente();

        }
    }

    if(m_lista.size()==0 && _valor==""){*/
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

            if(query.exec("select descripcionTipoProcedenciaCliente from TipoProcedenciaCliente   where codigoTipoProcedenciaCliente='"+codigoTipoProcedenciaCliente+"'")) {

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
   /* }else{
        return _valor;
    }*/
}


int ModuloTipoProcedenciaCliente::rowCount(const QModelIndex & parent) const {
    return m_lista.count();
}

QVariant ModuloTipoProcedenciaCliente::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_lista.count()){
        return QVariant();

    }
    const TipoProcedenciaCliente &aux = m_lista[index.row()];

    if (role == codigoTipoProcedenciaClienteRole){
        return aux.codigoTipoProcedenciaCliente();

    }else if (role == descripcionTipoProcedenciaClienteRole){
        return aux.descripcionTipoProcedenciaCliente();

    }
    return QVariant();
}
