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

#include "modulolistaproveedor.h"
#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>
#include <Utilidades/database.h>




ModuloListaProveedor::ModuloListaProveedor(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoClienteProveedorRole] = "codigoClienteProveedor";
    roles[TipoClienteProveedorRole] = "tipoClienteProveedor";
    roles[NombreClienteProveedorRole] = "nombreClienteProveedor";
    roles[RazonSocialProveedorRole] = "razonSocialProveedor";

    setRoleNames(roles);

}


ListaProveedor::ListaProveedor(const QString &codigoClienteProveedor, const int &tipoClienteProveedor, const QString &nombreClienteProveedor,const QString &razonSocialProveedor)

    : m_codigoClienteProveedor(codigoClienteProveedor), m_tipoClienteProveedor(tipoClienteProveedor),m_nombreClienteProveedor(nombreClienteProveedor), m_razonSocialProveedor(razonSocialProveedor)
{
}

QString ListaProveedor::codigoClienteProveedor() const
{
    return m_codigoClienteProveedor;
}
int ListaProveedor::tipoClienteProveedor() const
{
    return m_tipoClienteProveedor;
}
QString ListaProveedor::nombreClienteProveedor() const
{
    return m_nombreClienteProveedor;
}
QString ListaProveedor::razonSocialProveedor() const
{
    return m_razonSocialProveedor;
}


void ModuloListaProveedor::addCliente(const ListaProveedor &clienteProveedor)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ListaProveedor << clienteProveedor;
    endInsertRows();
}

void ModuloListaProveedor::clearClientes(){
    m_ListaProveedor.clear();
}

void ModuloListaProveedor::buscarCliente(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from Clientes where "+campo+"'"+datoABuscar+"' order by nombreCliente");
        QSqlRecord rec = q.record();

        ModuloListaProveedor::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloListaProveedor::addCliente(ListaProveedor(q.value(rec.indexOf("codigoCliente")).toString(), q.value(rec.indexOf("tipoCliente")).toInt(), q.value(rec.indexOf("nombreCliente")).toString(),     q.value(rec.indexOf("razonSocial")).toString()));
            }
        }
    }
}

int ModuloListaProveedor::rowCount(const QModelIndex & parent) const {
    return m_ListaProveedor.count();
}

QVariant ModuloListaProveedor::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_ListaProveedor.count()){
        return QVariant();

    }

    const ListaProveedor &clienteProveedor = m_ListaProveedor[index.row()];

    if (role == CodigoClienteProveedorRole){
        return clienteProveedor.codigoClienteProveedor();

    }
    else if (role == TipoClienteProveedorRole){
        return clienteProveedor.tipoClienteProveedor();

    }
    else if (role == NombreClienteProveedorRole){
        return clienteProveedor.nombreClienteProveedor();

    }
    else if (role == RazonSocialProveedorRole){
        return clienteProveedor.razonSocialProveedor();

    }

    return QVariant();
}

QString ModuloListaProveedor::primerRegistroDeProveedorNombreEnBase(QString _codigoProveedor) const {
    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select nombreCliente from Clientes where codigoCliente='"+_codigoProveedor+"' and tipoCliente=2 order by codigoCliente asc limit 1");
        QSqlRecord rec = q.record();

        if(q.record().count()>0){

            if(q.first()){
                return q.value(rec.indexOf("nombreCliente")).toString();
            }else{return "";}

        }else{
            return "";
        }
    }else{return "";}
}

QString ModuloListaProveedor::primerRegistroDeProveedorCodigoEnBase() const {

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select codigoCliente from Clientes where tipoCliente=2 order by codigoCliente asc limit 1");
        QSqlRecord rec = q.record();

        if(q.record().count()>0){

            if(q.first()){
                return q.value(rec.indexOf("codigoCliente")).toString();
            }else{return "";}
        }else{
            return "";
        }
    }else{return "";}
}
