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
QString ModuloTipoGarantia::retornaDescripcionTipoGarantia(QString _codigoTipoGarantia) const{

  /*  QString _valor="";
    for (int var = 0; var < m_TipoGarantia.size(); ++var) {
        if(QString::number(m_TipoGarantia[var].codigoTipoGarantia())==_codigoTipoGarantia ){

            _valor= m_TipoGarantia[var].descripcionTipoGarantia();

        }
    }

    if(m_TipoGarantia.size()==0 && _valor==""){*/
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


            if(query.exec("select descripcionTipoGarantia from TipoGarantia where codigoTipoGarantia='"+_codigoTipoGarantia+"'")) {
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

    /*
    */
}
QString ModuloTipoGarantia::retornaUltimoCodigo() const{
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


        if(query.exec("select codigoTipoGarantia from TipoGarantia order by codigoTipoGarantia desc limit 1")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    return QString::number(query.value(0).toInt()+1);
                }else{
                    return "1";
                }
            }else{return "1";}
        }else{
            return "1";
        }
    }else{
        return "1";
    }
}
bool ModuloTipoGarantia::eliminar(QString _codigo) const {

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
        if(query.exec("select codigoTipoGarantia from TipoGarantia where codigoTipoGarantia='"+_codigo+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    if(query.exec("delete from TipoGarantia where codigoTipoGarantia='"+_codigo+"'")){
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    return false;
                }
            }else{return false;}
        }else{
            return false;
        }
    }else{
        return false;
    }
}



int ModuloTipoGarantia::insertarTipoGarantia(QString _codigo,QString _nombre){

    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar
    // 1  item dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El item no tiene los datos sufucientes para darse de alta.

    if(_codigo.trimmed()=="" || _nombre.trimmed()=="" ){
        return -5;
    }

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


        if(query.exec("select codigoTipoGarantia from TipoGarantia where codigoTipoGarantia='"+_codigo+"'")) {

            if(query.first()){

                if(query.value(0).toString()!=""){

                    if(query.exec("update TipoGarantia set descripcionTipoGarantia='"+_nombre+"'  where codigoTipoGarantia='"+_codigo+"'")){
                        return 2;
                    }else{
                        return -2;
                    }
                }else{
                    return -4;
                }
            }else{
                if(query.exec("insert INTO TipoGarantia (codigoTipoGarantia,descripcionTipoGarantia) values('"+_codigo+"','"+_nombre+"')")){
                    return 1;
                }else{
                    return -3;
                }
            }
        }else{
            return -4;
        }
    }else{
        return -1;
    }
}



