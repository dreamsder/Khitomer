/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2025>  <Cristian Montano>

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
#include "modulobusquedainteligente.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>


ModuloBusquedaInteligente::ModuloBusquedaInteligente(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[codigoItemRole] = "codigoItem";
    roles[tipoItemRole] = "tipoItem";

    setRoleNames(roles);
}


BusquedaInteligente::BusquedaInteligente(const QString &codigoItem, const QString &tipoItem)
    : m_codigoItem(codigoItem), m_tipoItem(tipoItem)
{
}

QString BusquedaInteligente::codigoItem() const
{
    return m_codigoItem;
}
QString BusquedaInteligente::tipoItem() const
{
    return m_tipoItem;
}



void ModuloBusquedaInteligente::agregarBusquedaInteligente(const BusquedaInteligente &busquedaInteligente)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_BusquedaInteligente << busquedaInteligente;
    endInsertRows();
}

void ModuloBusquedaInteligente::limpiarBusquedaInteligente(){
    m_BusquedaInteligente.clear();
}

void ModuloBusquedaInteligente::buscarArticulosInteligente(QString datoABuscar,bool _incluyeInactivos){



    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery q;

        if(_incluyeInactivos){
            q = Database::consultaSql("select Articulos.codigoArticulo'codigoItem', 'ARTICULO' as 'tipoItem' from Articulos join Clientes on Articulos.codigoProveedor=Clientes.codigoCliente and Articulos.tipoCliente=Clientes.tipoCliente where  Clientes.tipoCliente=2  and (Articulos.codigoIva=(SELECT codigoIva FROM Ivas where descripcionIva rlike '"+datoABuscar+"' limit 1)  or Articulos.codigoMoneda=(SELECT codigoMoneda FROM Monedas where descripcionMoneda rlike '"+datoABuscar+"' limit 1) or Articulos.descripcionExtendida rlike '"+datoABuscar+"' or Articulos.descripcionArticulo rlike '"+datoABuscar+"') order by cast(Articulos.codigoArticulo as unsigned) ");
        }else{
            q = Database::consultaSql("select Articulos.codigoArticulo'codigoItem', 'ARTICULO' as 'tipoItem' from Articulos join Clientes on Articulos.codigoProveedor=Clientes.codigoCliente and Articulos.tipoCliente=Clientes.tipoCliente where activo='1' and Clientes.tipoCliente=2  and (Articulos.codigoIva=(SELECT codigoIva FROM Ivas where descripcionIva rlike '"+datoABuscar+"' limit 1)  or codigoMoneda=(SELECT codigoMoneda FROM Monedas where descripcionMoneda rlike '"+datoABuscar+"' limit 1) or descripcionExtendida rlike '"+datoABuscar+"' or descripcionArticulo rlike '"+datoABuscar+"') order by cast(codigoArticulo as unsigned) ");
        }


        QSqlRecord rec = q.record();

        ModuloBusquedaInteligente::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloBusquedaInteligente::agregarBusquedaInteligente(BusquedaInteligente(q.value(rec.indexOf("codigoItem")).toString(), q.value(rec.indexOf("tipoItem")).toString()));
            }
        }
    }
}

void ModuloBusquedaInteligente::buscarClientesInteligente(QString datoABuscar){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery q = Database::consultaSql("select Clientes.codigoCliente'codigoItem', 'CLIENTE' as 'tipoItem'  from Clientes join TipoCliente on Clientes.tipoCliente=TipoCliente.codigoTipoCliente join TipoClasificacion on Clientes.tipoClasificacion=TipoClasificacion.codigoTipoClasificacion where Clientes.tipoCliente=1 and (razonSocial rlike '"+datoABuscar+"' or direccion rlike '"+datoABuscar+"' or rut rlike '"+datoABuscar+"' or nombreCliente rlike '"+datoABuscar+"')");
        QSqlRecord rec = q.record();

        ModuloBusquedaInteligente::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloBusquedaInteligente::agregarBusquedaInteligente(BusquedaInteligente(q.value(rec.indexOf("codigoItem")).toString(), q.value(rec.indexOf("tipoItem")).toString()));
            }
        }
    }
}

void ModuloBusquedaInteligente::buscarProveedorInteligente(QString datoABuscar){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery q = Database::consultaSql("select Clientes.codigoCliente'codigoItem', 'PROVEEDOR' as 'tipoItem'  from Clientes join TipoCliente on Clientes.tipoCliente=TipoCliente.codigoTipoCliente join TipoClasificacion on Clientes.tipoClasificacion=TipoClasificacion.codigoTipoClasificacion where Clientes.tipoCliente=2 and (razonSocial rlike '"+datoABuscar+"' or direccion rlike '"+datoABuscar+"' or rut rlike '"+datoABuscar+"' or nombreCliente rlike '"+datoABuscar+"')");
        QSqlRecord rec = q.record();

        ModuloBusquedaInteligente::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloBusquedaInteligente::agregarBusquedaInteligente(BusquedaInteligente(q.value(rec.indexOf("codigoItem")).toString(), q.value(rec.indexOf("tipoItem")).toString()));
            }
        }
    }
}

int ModuloBusquedaInteligente::rowCount(const QModelIndex & parent) const {
    return m_BusquedaInteligente.count();
}

QVariant ModuloBusquedaInteligente::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_BusquedaInteligente.count()){
        return QVariant();

    }

    const BusquedaInteligente &busquedaInteligente = m_BusquedaInteligente[index.row()];

    if (role == codigoItemRole){
        return busquedaInteligente.codigoItem();

    }
    else if (role == tipoItemRole){
        return busquedaInteligente.tipoItem();

    }
    return QVariant();
}


