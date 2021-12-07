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

#include "modulodepartamentos.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>


ModuloDepartamentos::ModuloDepartamentos(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoDepartamentoRole] = "codigoDepartamento";
    roles[DescripcionDepartamentoRole] = "descripcionDepartamento";
    roles[CodigoPaisRole] = "codigoPais";

    setRoleNames(roles);
}


Departamento::Departamento(const int &codigoDepartamento, const QString &descripcionDepartamento,const int &codigoPais)
    : m_codigoDepartamento(codigoDepartamento), m_descripcionDepartamento(descripcionDepartamento),m_codigoPais(codigoPais)
{
}

int Departamento::codigoDepartamento() const
{
    return m_codigoDepartamento;
}
QString Departamento::descripcionDepartamento() const
{
    return m_descripcionDepartamento;
}
int Departamento::codigoPais() const
{
    return m_codigoPais;
}


void ModuloDepartamentos::agregarDepartamento(const Departamento &departamentos)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Departamentos << departamentos;
    endInsertRows();
}

void ModuloDepartamentos::limpiarListaDepartamentos(){
    m_Departamentos.clear();
}

void ModuloDepartamentos::buscarDepartamentos(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from Departamentos where "+campo+"'"+datoABuscar+"' order by descripcionDepartamento");
        QSqlRecord rec = q.record();

        ModuloDepartamentos::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloDepartamentos::agregarDepartamento(Departamento(q.value(rec.indexOf("codigoDepartamento")).toInt(), q.value(rec.indexOf("descripcionDepartamento")).toString(),q.value(rec.indexOf("codigoPais")).toInt()));
            }
        }
    }
}

int ModuloDepartamentos::rowCount(const QModelIndex & parent) const {
    return m_Departamentos.count();
}

QVariant ModuloDepartamentos::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Departamentos.count()){
        return QVariant();

    }

    const Departamento &departamentos = m_Departamentos[index.row()];

    if (role == CodigoDepartamentoRole){
        return departamentos.codigoDepartamento();

    }
    else if (role == DescripcionDepartamentoRole){
        return departamentos.descripcionDepartamento();

    }else if (role == CodigoPaisRole){
        return departamentos.codigoPais();

    }

    return QVariant();
}
QString ModuloDepartamentos::retornaUltimoCodigoDepartamento(QString _codigoPais) const{
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

        if(query.exec("select codigoDepartamento from Departamentos where codigoPais='"+_codigoPais+"'  order by codigoDepartamento desc limit 1")) {
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
int ModuloDepartamentos::insertarDepartamento(QString _codigoDepartamento,QString _nombreDepartamento,QString _codigoPais){

    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el departamento
    // 1  departamento dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar el departamento
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El departamento no tiene los datos sufucientes para darse de alta.

    if(_codigoDepartamento.trimmed()=="" || _codigoPais.trimmed()=="" || _nombreDepartamento.trimmed()=="" ){
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


        if(query.exec("select codigoDepartamento from Departamentos where codigoDepartamento='"+_codigoDepartamento+"' and codigoPais='"+_codigoPais+"'")) {

            if(query.first()){

                if(query.value(0).toString()!=""){

                    if(query.exec("update Departamentos set descripcionDepartamento='"+_nombreDepartamento+"'  where codigoDepartamento='"+_codigoDepartamento+"' and codigoPais='"+_codigoPais+"'")){
                        return 2;
                    }else{
                        return -2;
                    }
                }else{
                    return -4;
                }
            }else{
                if(query.exec("insert INTO Departamentos (codigoDepartamento,codigoPais,descripcionDepartamento) values('"+_codigoDepartamento+"','"+_codigoPais+"','"+_nombreDepartamento+"')")){
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
bool ModuloDepartamentos::eliminarDepartamento(QString _codigoDepartamento,QString _codigoPais) const {

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
        if(query.exec("select codigoDepartamento from Departamentos where codigoDepartamento='"+_codigoDepartamento+"' and codigoPais='"+_codigoPais+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    if(query.exec("delete from Departamentos where codigoDepartamento='"+_codigoDepartamento+"' and codigoPais='"+_codigoPais+"'")){
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
QString ModuloDepartamentos::retornaDescripcionDepartamento(QString _codigoDepartamento,QString _codigoPais) const{

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


        if(query.exec("select descripcionDepartamento from Departamentos where codigoDepartamento='"+_codigoDepartamento+"' and codigoPais='"+_codigoPais+"'")) {
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
