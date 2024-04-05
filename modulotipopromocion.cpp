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

#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include <QDebug>
#include <funciones.h>
#include "modulotipopromocion.h"


#include <Utilidades/moduloconfiguracion.h>

ModuloConfiguracion func_configuracionModuloTipoPromocion;

ModuloTipoPromocion::ModuloTipoPromocion(QObject *parent)
    : QAbstractListModel(parent)
{


    	QHash<int, QByteArray> roles;
    roles[idTipoPromocionRole]="idTipoPromocion";
    roles[nombreTipoPromocionRole]="nombreTipoPromocion";
	setRoleNames(roles);
}
TipoPromocion::TipoPromocion(
    const QString &idTipoPromocion,
    const QString &nombreTipoPromocion
):
    m_idTipoPromocion(idTipoPromocion),
    m_nombreTipoPromocion(nombreTipoPromocion)
{}

QString TipoPromocion::idTipoPromocion()const{
    return m_idTipoPromocion;}
QString TipoPromocion::nombreTipoPromocion()const{
    return m_nombreTipoPromocion;}

void ModuloTipoPromocion::agregarTipoPromocion(const TipoPromocion &variable)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_TipoPromocion << variable;
    endInsertRows();
}

void ModuloTipoPromocion::limpiarTipoPromocion(){
    m_TipoPromocion.clear();
}

int ModuloTipoPromocion::rowCount(const QModelIndex & parent) const {
    return m_TipoPromocion.count();
}

QVariant ModuloTipoPromocion::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_TipoPromocion.count()){
        return QVariant();

    }

    const TipoPromocion &variable = m_TipoPromocion[index.row()];
	if (role == idTipoPromocionRole){
            return variable.idTipoPromocion();
	}
	    else if (role == nombreTipoPromocionRole)
	{
    	return variable.nombreTipoPromocion();
	}
    return QVariant();
	}

QString ModuloTipoPromocion::retornaValor(int index, QString role) const{

    const TipoPromocion &variable = m_TipoPromocion[index];
    if (role == "idTipoPromocion"){
            return variable.idTipoPromocion();
      }
        else if (role == "nombreTipoPromocion")
     {
            return variable.nombreTipoPromocion();
      }
}


QString ModuloTipoPromocion::retornaUltimoTipoPromocion() const{
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

        if(query.exec("select idTipoPromocion from TipoPromocion order by idTipoPromocion desc limit 1")) {
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




bool ModuloTipoPromocion::eliminarTipoPromocion(QString _idTipoPromocion) const {
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
        if(query.exec("select idTipoPromocion from TipoPromocion where idTipoPromocion='"+_idTipoPromocion+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    if(query.exec("delete from TipoPromocion where idTipoPromocion='"+_idTipoPromocion+"'")){
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

void ModuloTipoPromocion::buscarTipoPromocion(QString campo){
	bool conexion=true;
	Database::chequeaStatusAccesoMysql();
    	if(!Database::connect().isOpen()){
        	if(!Database::connect().open()){
            	qDebug() << "No conecto";
            	conexion=false;
        	}
    	}



    	if(conexion){

        QSqlQuery q = Database::consultaSql("SELECT * FROM TipoPromocion "+campo+";");
        QSqlRecord rec = q.record();


        ModuloTipoPromocion::reset();

        if(q.record().count()>0){

            while (q.next()){
                ModuloTipoPromocion::agregarTipoPromocion(TipoPromocion( 
						    q.value(rec.indexOf("idTipoPromocion")).toString(),
						    q.value(rec.indexOf("nombreTipoPromocion")).toString()
                                                                 ));
            }
        }
    }
}
