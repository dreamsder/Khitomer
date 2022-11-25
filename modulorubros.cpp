/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2023>  <Cristian Montano>

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
#include "modulorubros.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>


ModuloRubros::ModuloRubros(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoRubroRole] = "codigoRubro";
    roles[DescripcionRubroRole] = "descripcionRubro";

    setRoleNames(roles);
}


Rubros::Rubros(const int &codigoRubro, const QString &descripcionRubro)
    : m_codigoRubro(codigoRubro), m_descripcionRubro(descripcionRubro)
{
}

int Rubros::codigoRubro() const
{
    return m_codigoRubro;
}
QString Rubros::descripcionRubro() const
{
    return m_descripcionRubro;
}


void ModuloRubros::agregarRubro(const Rubros &rubros)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Rubros << rubros;
    endInsertRows();
}

void ModuloRubros::limpiarListaRubros(){
    m_Rubros.clear();
}

void ModuloRubros::buscarRubros(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from Rubros where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloRubros::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloRubros::agregarRubro(Rubros(q.value(rec.indexOf("codigoRubro")).toInt(), q.value(rec.indexOf("descripcionRubro")).toString()));
            }
        }
    }
}

int ModuloRubros::retornaCantidadSubRubros(QString _codigoRubro){

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

        if(query.exec("SELECT count(*) FROM SubRubros where codigoRubro='"+_codigoRubro+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toInt();

                }else{
                    return 0;
                }
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

QString ModuloRubros::retornaNombreRubro(QString _codigoRubro){

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

        if(query.exec("SELECT descripcionRubro FROM Rubros where codigoRubro='"+_codigoRubro+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toString();

                }else{
                    return "ERROR BD";
                }
            }return "ERROR: No existe el registro";
        }else{
            return "ERROR BD";
        }
    }else{
        return "ERROR BD";
    }
}
int ModuloRubros::rowCount(const QModelIndex & parent) const {
    return m_Rubros.count();
}

QVariant ModuloRubros::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Rubros.count()){
        return QVariant();

    }

    const Rubros &rubros = m_Rubros[index.row()];

    if (role == CodigoRubroRole){
        return rubros.codigoRubro();

    }
    else if (role == DescripcionRubroRole){
        return rubros.descripcionRubro();

    }

    return QVariant();
}
int ModuloRubros::insertarRubro(QString _codigoRubro,QString _nombreRubro){

    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el rubro
    // 1  rubro dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar el rubro
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El rubro no tiene los datos sufucientes para darse de alta.

    if(_codigoRubro.trimmed()=="" || _nombreRubro.trimmed()=="" ){
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


        if(query.exec("select codigoRubro from Rubros where codigoRubro='"+_codigoRubro+"'")) {

            if(query.first()){

                if(query.value(0).toString()!=""){

                    if(query.exec("update Rubros set sincronizadoWeb='0', descripcionRubro='"+_nombreRubro+"'  where codigoRubro='"+_codigoRubro+"'")){
                        return 2;
                    }else{
                        return -2;
                    }
                }else{
                    return -4;
                }
            }else{
                if(query.exec("insert INTO Rubros (codigoRubro,descripcionRubro,sincronizadoWeb) values('"+_codigoRubro+"','"+_nombreRubro+"','0')")){
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

bool ModuloRubros::eliminarRubro(QString _codigoRubro) const {
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

        if(query.exec("select codigoRubro from Rubros where codigoRubro='"+_codigoRubro+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("delete from Rubros where codigoRubro='"+_codigoRubro+"'")){

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
int ModuloRubros::ultimoRegistroDeRubro()const {
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

        if(query.exec("select codigoRubro from Rubros order by codigoRubro desc limit 1")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toInt()+1;

                }else{
                    return 1;
                }
            }else {return 1;}
        }else{
            return 1;
        }
    }
}
