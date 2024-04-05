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

#include "modulotipoclientes.h"
#include <QtSql>
#include <Utilidades/database.h>

ModuloTipoClientes::ModuloTipoClientes(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoTipoClienteRole] = "codigoTipoCliente";
    roles[DescripcionTipoClienteRole] = "descripcionTipoCliente";

    setRoleNames(roles);

}


TipoDeCliente::TipoDeCliente(const int &codigoTipoCliente,const QString &descripcionTipoCliente)

    : m_codigoTipoCliente(codigoTipoCliente),m_descripcionTipoCliente(descripcionTipoCliente)
{
}


int TipoDeCliente::codigoTipoCliente() const
{
    return m_codigoTipoCliente;
}
QString TipoDeCliente::descripcionTipoCliente() const
{
    return m_descripcionTipoCliente;
}






void ModuloTipoClientes::addTipoCliente(const TipoDeCliente &tipoDeCliente)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_TipoDeClientes << tipoDeCliente;
    endInsertRows();

}

void ModuloTipoClientes::clearTipoClientes(){

    m_TipoDeClientes.clear();

}

void ModuloTipoClientes::buscarTipoCliente(QString campo, QString datoABuscar){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery q = Database::consultaSql("select * from TipoCliente where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloTipoClientes::reset();
        if(q.record().count()>0){

            while (q.next()){

                ModuloTipoClientes::addTipoCliente(TipoDeCliente(q.value(rec.indexOf("codigoTipoCliente")).toInt(),q.value(rec.indexOf("descripcionTipoCliente")).toString()));

            }
        }


    }




}


int ModuloTipoClientes::rowCount(const QModelIndex & parent) const {
    return m_TipoDeClientes.count();
}




QVariant ModuloTipoClientes::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_TipoDeClientes.count()){
        return QVariant();

    }

    const TipoDeCliente &tipocliente = m_TipoDeClientes[index.row()];

    if (role == CodigoTipoClienteRole){
        return tipocliente.codigoTipoCliente();

    }else if (role == DescripcionTipoClienteRole){
        return tipocliente.descripcionTipoCliente();

    }


    return QVariant();

}

QString ModuloTipoClientes::primerRegistroDeTipoClienteEnBase(QString _tipoCliente) const {

   /* QString _valor="";
    for (int var = 0; var < m_TipoDeClientes.size(); ++var) {
        if(QString::number(m_TipoDeClientes[var].codigoTipoCliente())==_tipoCliente ){

            _valor= m_TipoDeClientes[var].descripcionTipoCliente();

        }
    }


    if(m_TipoDeClientes.size()==0 && _valor==""){*/
        bool conexion=true;
        Database::chequeaStatusAccesoMysql();
        if(!Database::connect().isOpen()){
            if(!Database::connect().open()){
                qDebug() << "No conecto";
                conexion=false;
            }
        }
        if(conexion){
            QSqlQuery q = Database::consultaSql("select descripcionTipoCliente from TipoCliente where codigoTipoCliente='"+_tipoCliente+"'");
            QSqlRecord rec = q.record();

            if(q.record().count()>0){
                while (q.next()){
                    return q.value(rec.indexOf("descripcionTipoCliente")).toString();
                }
            }else{
                return "";
            }

        }
  /*  }else{
        return _valor;
    }*/


    /*
   */
}
