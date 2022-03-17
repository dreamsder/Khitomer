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

#include "modulolocalidades.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>


ModuloLocalidades::ModuloLocalidades(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoLocalidadRole] = "codigoLocalidad";
    roles[DescripcionLocalidadRole] = "descripcionLocalidad";
    roles[CodigoDepartamentoRole] = "codigoDepartamento";
    roles[CodigoPaisRole] = "codigoPais";

    setRoleNames(roles);
}


Localidad::Localidad(const int &codigoLocalidad, const QString &descripcionLocalidad,const int &codigoDepartamento,const int &codigoPais)
    : m_codigoLocalidad(codigoLocalidad), m_descripcionLocalidad(descripcionLocalidad),m_codigoDepartamento(codigoDepartamento),m_codigoPais(codigoPais)
{
}

int Localidad::codigoLocalidad() const
{
    return m_codigoLocalidad;
}
QString Localidad::descripcionLocalidad() const
{
    return m_descripcionLocalidad;
}
int Localidad::codigoDepartamento() const
{
    return m_codigoDepartamento;
}
int Localidad::codigoPais() const
{
    return m_codigoPais;
}




void ModuloLocalidades::agregarLocalidad(const Localidad &localidades)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Localidades << localidades;
    endInsertRows();
}

void ModuloLocalidades::limpiarListaLocalidades(){
    m_Localidades.clear();
}

void ModuloLocalidades::buscarLocalidades(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from Localidades where "+campo+"'"+datoABuscar+"' order by descripcionLocalidad");
        QSqlRecord rec = q.record();

        ModuloLocalidades::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloLocalidades::agregarLocalidad(Localidad(q.value(rec.indexOf("codigoLocalidad")).toInt(), q.value(rec.indexOf("descripcionLocalidad")).toString(),q.value(rec.indexOf("codigoDepartamento")).toInt(),q.value(rec.indexOf("codigoPais")).toInt()));
            }
        }
    }
}

int ModuloLocalidades::rowCount(const QModelIndex & parent) const {
    return m_Localidades.count();
}

QVariant ModuloLocalidades::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Localidades.count()){
        return QVariant();

    }

    const Localidad &localidades = m_Localidades[index.row()];

    if (role == CodigoLocalidadRole){
        return localidades.codigoLocalidad();
    }
    else if (role == DescripcionLocalidadRole){
        return localidades.descripcionLocalidad();
    }else if (role == CodigoDepartamentoRole){
        return localidades.codigoDepartamento();
    }else if (role == CodigoPaisRole){
        return localidades.codigoPais();
    }

    return QVariant();
}
QString ModuloLocalidades::retornaDescripcionLocalidad(QString _codigoPais,QString _codigoDepartamento,QString _codigoLocalidad) const{

    QString _valor="";
    for (int var = 0; var < m_Localidades.size(); ++var) {
        if(QString::number(m_Localidades[var].codigoLocalidad())==_codigoLocalidad && QString::number(m_Localidades[var].codigoPais())==_codigoPais
                && QString::number(m_Localidades[var].codigoDepartamento())==_codigoDepartamento){
            _valor = m_Localidades[var].descripcionLocalidad();
        }
    }

    if(m_Localidades.size()==0 && _valor==""){
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


            if(query.exec("select descripcionLocalidad from Localidades where codigoPais='"+_codigoPais+"' and codigoDepartamento='"+_codigoDepartamento+"' and codigoLocalidad='"+_codigoLocalidad+"'")) {
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
    }else{
        return _valor;
    }


}
QString ModuloLocalidades::retornaUltimoCodigoLocalidad(QString _codigoPais,QString _codigoDepartamento) const{
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

        if(query.exec("select codigoLocalidad from Localidades where codigoPais='"+_codigoPais+"' and codigoDepartamento='"+_codigoDepartamento+"'  order by codigoLocalidad desc limit 1")) {
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
int ModuloLocalidades::insertarLocalidad(QString _codigoLocalidad,QString _nombreLocalidad,QString _codigoDepartamento,QString _codigoPais){

    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar la localidad
    // 1  localidad dada de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar la localidad
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 La localidad no tiene los datos sufucientes para darse de alta.

    if(_codigoLocalidad.trimmed()=="" || _codigoDepartamento.trimmed()=="" || _codigoPais.trimmed()=="" || _nombreLocalidad.trimmed()=="" ){
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

        if(query.exec("select codigoLocalidad from Localidades where codigoLocalidad='"+_codigoLocalidad+"' and codigoDepartamento='"+_codigoDepartamento+"' and codigoPais='"+_codigoPais+"'")) {

            if(query.first()){

                if(query.value(0).toString()!=""){

                    if(query.exec("update Localidades set descripcionLocalidad='"+_nombreLocalidad+"'  where codigoLocalidad='"+_codigoLocalidad+"' and codigoDepartamento='"+_codigoDepartamento+"' and codigoPais='"+_codigoPais+"'")){
                        return 2;
                    }else{
                        return -2;
                    }
                }else{
                    return -4;
                }
            }else{
                if(query.exec("insert INTO Localidades (codigoLocalidad,codigoDepartamento,codigoPais,descripcionLocalidad) values('"+_codigoLocalidad+"','"+_codigoDepartamento+"','"+_codigoPais+"','"+_nombreLocalidad+"')")){
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
bool ModuloLocalidades::eliminarLocalidad(QString _codigoLocalidad,QString _codigoDepartamento,QString _codigoPais) const {

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
        if(query.exec("select codigoLocalidad from Localidades where codigoLocalidad='"+_codigoLocalidad+"' and codigoDepartamento='"+_codigoDepartamento+"' and codigoPais='"+_codigoPais+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    if(query.exec("delete from Localidades where codigoLocalidad='"+_codigoLocalidad+"' and codigoDepartamento='"+_codigoDepartamento+"' and codigoPais='"+_codigoPais+"'")){
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
