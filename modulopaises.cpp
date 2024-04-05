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

#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include "modulopaises.h"





ModuloPaises::ModuloPaises(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoPaisRole] = "codigoPais";
    roles[DescripcionPaisRole] = "descripcionPais";

    setRoleNames(roles);
}


Pais::Pais(const int &codigoPais, const QString &descripcionPais)
    : m_codigoPais(codigoPais), m_descripcionPais(descripcionPais)
{
}

int Pais::codigoPais() const
{
    return m_codigoPais;
}
QString Pais::descripcionPais() const
{
    return m_descripcionPais;
}



void ModuloPaises::agregarPais(const Pais &paises)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Paises << paises;
    endInsertRows();
}

void ModuloPaises::limpiarListaPaises(){
    m_Paises.clear();
}

void ModuloPaises::buscarPaises(QString campo, QString datoABuscar,QString _orderBy){


    bool conexion=true;

    QString orderBy="";

    if(_orderBy.trimmed()!="")
        orderBy=" order by "+_orderBy+" asc ";

    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from Pais where "+campo+" "+datoABuscar+" "+orderBy);
        QSqlRecord rec = q.record();

        ModuloPaises::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloPaises::agregarPais(Pais(q.value(rec.indexOf("codigoPais")).toInt(), q.value(rec.indexOf("descripcionPais")).toString()));
            }
        }
    }
}

int ModuloPaises::rowCount(const QModelIndex & parent) const {
    return m_Paises.count();
}
QVariant ModuloPaises::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Paises.count()){
        return QVariant();

    }
    const Pais &paises = m_Paises[index.row()];

    if (role == CodigoPaisRole){
        return paises.codigoPais();
    }
    else if (role == DescripcionPaisRole){
        return paises.descripcionPais();
    }
    return QVariant();
}
QString ModuloPaises::retornaUltimoCodigoPais() const{
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


        if(query.exec("select codigoPais from Pais order by codigoPais desc limit 1")) {
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
bool ModuloPaises::eliminarPais(QString _codigoPais) const {
    Database::chequeaStatusAccesoMysql();
    bool conexion=true;
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect());
        if(query.exec("select codigoPais from Pais where codigoPais='"+_codigoPais+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    if(query.exec("delete from Pais where codigoPais='"+_codigoPais+"'")){
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
int ModuloPaises::insertarPais(QString _codigoPais,QString _nombrePais){

    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el pais
    // 1  pais dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar el pais
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El pais no tiene los datos sufucientes para darse de alta.

    if(_codigoPais.trimmed()=="" || _nombrePais.trimmed()=="" ){
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


        if(query.exec("select codigoPais from Pais where codigoPais='"+_codigoPais+"'")) {

            if(query.first()){

                if(query.value(0).toString()!=""){

                    if(query.exec("update Pais set descripcionPais='"+_nombrePais+"'  where codigoPais='"+_codigoPais+"'")){
                        return 2;
                    }else{
                        return -2;
                    }
                }else{
                    return -4;
                }
            }else{
                if(query.exec("insert INTO Pais (codigoPais,descripcionPais) values('"+_codigoPais+"','"+_nombrePais+"')")){
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
QString ModuloPaises::retornaDescripcionPais(QString _codigoPais) const{


    /*QString _valor="";
    for (int var = 0; var < m_Paises.size(); ++var) {
        if(QString::number(m_Paises[var].codigoPais())==_codigoPais){
            _valor = m_Paises[var].descripcionPais();
        }
    }


    if(m_Paises.size()==0 && _valor==""){*/
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


            if(query.exec("select descripcionPais from Pais where codigoPais='"+_codigoPais+"'")) {
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
  /*  }else{
        return _valor;
    }*/
}
