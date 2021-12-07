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
#include "modulosubrubros.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>


ModuloSubRubros::ModuloSubRubros(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoSubRubroRole] = "codigoSubRubro";
    roles[CodigoRubroRole] = "codigoRubro";
    roles[DescripcionSubRubroRole] = "descripcionSubRubro";

    setRoleNames(roles);
}


SubRubros::SubRubros(const int &codigoSubRubro,const int &codigoRubro, const QString &descripcionSubRubro)
    : m_codigoSubRubro(codigoSubRubro),m_codigoRubro(codigoRubro), m_descripcionSubRubro(descripcionSubRubro)
{
}
int SubRubros::codigoSubRubro() const
{
    return m_codigoSubRubro;
}
int SubRubros::codigoRubro() const
{
    return m_codigoRubro;
}
QString SubRubros::descripcionSubRubro() const
{
    return m_descripcionSubRubro;
}


void ModuloSubRubros::agregarSubRubros(const SubRubros &subRubros)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_SubRubros << subRubros;
    endInsertRows();
}

void ModuloSubRubros::limpiarListaSubRubros(){
    m_SubRubros.clear();
}

void ModuloSubRubros::buscarSubRubros(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from SubRubros where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloSubRubros::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloSubRubros::agregarSubRubros(SubRubros(q.value(rec.indexOf("codigoSubRubro")).toInt(),
                                                            q.value(rec.indexOf("codigoRubro")).toInt(),
                                                            q.value(rec.indexOf("descripcionSubRubro")).toString()));
            }
        }
    }
}

int ModuloSubRubros::rowCount(const QModelIndex & parent) const {
    return m_SubRubros.count();
}

QVariant ModuloSubRubros::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_SubRubros.count()){
        return QVariant();

    }

    const SubRubros &subRubros = m_SubRubros[index.row()];

    if (role == CodigoSubRubroRole){
        return subRubros.codigoSubRubro();

    }
    else if (role == CodigoRubroRole){
        return subRubros.codigoRubro();

    }
    else if (role == DescripcionSubRubroRole){
        return subRubros.descripcionSubRubro();

    }

    return QVariant();
}
QString ModuloSubRubros::retornaDescripcionSubRubro(QString _codigoSubRubro){

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

        if(query.exec("SELECT descripcionSubRubro FROM SubRubros where codigoSubRubro='"+_codigoSubRubro+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                   return query.value(0).toString();

                }else{
                    return "Error BD";
                }
            }else{
                return "Error: No existe el registro";
            }
        }else{
            return "Error BD";
        }
    }else{
        return "Error BD";
    }

}
int ModuloSubRubros::ultimoRegistroDeSubRubro()const {
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

        if(query.exec("select codigoSubRubro from SubRubros order by codigoSubRubro desc limit 1")) {

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
bool ModuloSubRubros::eliminarSubRubro(QString _codigoSubRubro) const {
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

        if(query.exec("select codigoSubRubro from SubRubros where codigoSubRubro='"+_codigoSubRubro+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("delete from SubRubros where codigoSubRubro='"+_codigoSubRubro+"'")){

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
int ModuloSubRubros::insertarSubRubro(QString _codigoSubRubro,QString _codigoRubro,QString _nombreSubRubro){

    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el subrubro
    // 1  rubro dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar el subrubro
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El subrubro no tiene los datos sufucientes para darse de alta.

    if(_codigoSubRubro.trimmed()=="" | _codigoRubro.trimmed()=="" || _nombreSubRubro.trimmed()=="" ){
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
        if(query.exec("select codigoSubRubro from SubRubros where codigoSubRubro='"+_codigoSubRubro+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("update SubRubros set sincronizadoWeb='0', descripcionSubRubro='"+_nombreSubRubro+"',codigoRubro='"+_codigoRubro+"'   where codigoSubRubro='"+_codigoSubRubro+"'")){
                        return 2;
                    }else{
                        return -2;
                    }
                }else{
                    return -4;
                }
            }else{
                if(query.exec("insert INTO SubRubros (codigoSubRubro,codigoRubro,descripcionSubRubro,sincronizadoWeb) values('"+_codigoSubRubro+"','"+_codigoRubro+"','"+_nombreSubRubro+"','0')")){
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
