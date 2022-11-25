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
#include <QtSql>

#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include <QDebug>
#include <funciones.h>
#include "modulopromociones.h"


#include <Utilidades/moduloconfiguracion.h>

ModuloConfiguracion func_configuracionModuloPromociones;

ModuloPromociones::ModuloPromociones(QObject *parent)
    : QAbstractListModel(parent)
{


    	QHash<int, QByteArray> roles;
    roles[idPromocionesRole]="idPromociones";
    roles[idTipoPromocionRole]="idTipoPromocion";
    roles[habilitadaRole]="habilitada";
    roles[fechaRole]="fecha";
    roles[fechaDesdeRole]="fechaDesde";
    roles[fechaHastaRole]="fechaHasta";
    roles[diasSemanaRole]="diasSemana";
    roles[nombrePromocionRole]="nombrePromocion";
    roles[HTMLPromocionRole]="HTMLPromocion";
    roles[urlImagenRole]="urlImagen";
    roles[urlImagen2Role]="urlImagen2";
    roles[ejecutaSiempreRole]="ejecutaSiempre";
    roles[codigoTipoClienteRole]="codigoTipoCliente";
	setRoleNames(roles);
}
Promociones::Promociones(
    const QString &idPromociones,
    const QString &idTipoPromocion,
    const QString &habilitada,
    const QString &fecha,
    const QString &fechaDesde,
    const QString &fechaHasta,
    const QString &diasSemana,
    const QString &nombrePromocion,
    const QString &HTMLPromocion,
    const QString &urlImagen,
    const QString &urlImagen2,
    const QString &ejecutaSiempre,
    const QString &codigoTipoCliente
):
    m_idPromociones(idPromociones),
    m_idTipoPromocion(idTipoPromocion),
    m_habilitada(habilitada),
    m_fecha(fecha),
    m_fechaDesde(fechaDesde),
    m_fechaHasta(fechaHasta),
    m_diasSemana(diasSemana),
    m_nombrePromocion(nombrePromocion),
    m_HTMLPromocion(HTMLPromocion),
    m_urlImagen(urlImagen),
    m_urlImagen2(urlImagen2),
    m_ejecutaSiempre(ejecutaSiempre),
    m_codigoTipoCliente(codigoTipoCliente)
{}

QString Promociones::idPromociones()const{
    return m_idPromociones;}
QString Promociones::idTipoPromocion()const{
    return m_idTipoPromocion;}
QString Promociones::habilitada()const{
    return m_habilitada;}
QString Promociones::fecha()const{
    return m_fecha;}
QString Promociones::fechaDesde()const{
    return m_fechaDesde;}
QString Promociones::fechaHasta()const{
    return m_fechaHasta;}
QString Promociones::diasSemana()const{
    return m_diasSemana;}
QString Promociones::nombrePromocion()const{
    return m_nombrePromocion;}
QString Promociones::HTMLPromocion()const{
    return m_HTMLPromocion;}
QString Promociones::urlImagen()const{
    return m_urlImagen;}
QString Promociones::urlImagen2()const{
    return m_urlImagen2;}
QString Promociones::ejecutaSiempre()const{
    return m_ejecutaSiempre;}
QString Promociones::codigoTipoCliente()const{
    return m_codigoTipoCliente;}

void ModuloPromociones::agregarPromociones(const Promociones &variable)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Promociones << variable;
    endInsertRows();
}

void ModuloPromociones::limpiarPromociones(){
    m_Promociones.clear();
}

int ModuloPromociones::rowCount(const QModelIndex & parent) const {
    return m_Promociones.count();
}

QVariant ModuloPromociones::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Promociones.count()){
        return QVariant();

    }

    const Promociones &variable = m_Promociones[index.row()];
	if (role == idPromocionesRole){
            return variable.idPromociones();
	}
	    else if (role == idTipoPromocionRole)
	{
    	return variable.idTipoPromocion();
	}
	    else if (role == habilitadaRole)
	{
    	return variable.habilitada();
	}
	    else if (role == fechaRole)
	{
    	return variable.fecha();
	}
	    else if (role == fechaDesdeRole)
	{
    	return variable.fechaDesde();
	}
	    else if (role == fechaHastaRole)
	{
    	return variable.fechaHasta();
	}
	    else if (role == diasSemanaRole)
	{
    	return variable.diasSemana();
	}
	    else if (role == nombrePromocionRole)
	{
    	return variable.nombrePromocion();
	}
	    else if (role == HTMLPromocionRole)
	{
    	return variable.HTMLPromocion();
	}
	    else if (role == urlImagenRole)
	{
    	return variable.urlImagen();
	}
	    else if (role == urlImagen2Role)
	{
    	return variable.urlImagen2();
	}
	    else if (role == ejecutaSiempreRole)
	{
    	return variable.ejecutaSiempre();
	}
	    else if (role == codigoTipoClienteRole)
	{
    	return variable.codigoTipoCliente();
	}
    return QVariant();
	}

QString ModuloPromociones::retornaValor(int index, QString role) const{

    const Promociones &variable = m_Promociones[index];
    if (role == "idPromociones"){
            return variable.idPromociones();
      }
        else if (role == "idTipoPromocion")
     {
            return variable.idTipoPromocion();
      }
        else if (role == "habilitada")
     {
            return variable.habilitada();
      }
        else if (role == "fecha")
     {
            return variable.fecha();
      }
        else if (role == "fechaDesde")
     {
            return variable.fechaDesde();
      }
        else if (role == "fechaHasta")
     {
            return variable.fechaHasta();
      }
        else if (role == "diasSemana")
     {
            return variable.diasSemana();
      }
        else if (role == "nombrePromocion")
     {
            return variable.nombrePromocion();
      }
        else if (role == "HTMLPromocion")
     {
            return variable.HTMLPromocion();
      }
        else if (role == "urlImagen")
     {
            return variable.urlImagen();
      }
        else if (role == "urlImagen2")
     {
            return variable.urlImagen2();
      }
        else if (role == "ejecutaSiempre")
     {
            return variable.ejecutaSiempre();
      }
        else if (role == "codigoTipoCliente")
     {
            return variable.codigoTipoCliente();
      }
}


QString ModuloPromociones::retornaUltimoPromociones() const{
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

        if(query.exec("select idPromociones from Promociones order by idPromociones desc limit 1")) {
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




bool ModuloPromociones::eliminarPromociones(QString _idPromociones) const {
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
        if(query.exec("select idPromociones from Promociones where idPromociones='"+_idPromociones+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    if(query.exec("delete from Promociones where idPromociones='"+_idPromociones+"'")){
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

void ModuloPromociones::buscarPromociones(QString campo){
	bool conexion=true;
	Database::chequeaStatusAccesoMysql();
    	if(!Database::connect().isOpen()){
        	if(!Database::connect().open()){
            	qDebug() << "No conecto";
            	conexion=false;
        	}
    	}



    	if(conexion){

        QSqlQuery q = Database::consultaSql("SELECT * FROM Promociones "+campo+";");
        QSqlRecord rec = q.record();


        ModuloPromociones::reset();

        if(q.record().count()>0){

            while (q.next()){
                ModuloPromociones::agregarPromociones(Promociones( 
						    q.value(rec.indexOf("idPromociones")).toString(),
						    q.value(rec.indexOf("idTipoPromocion")).toString(),
						    q.value(rec.indexOf("habilitada")).toString(),
						    q.value(rec.indexOf("fecha")).toString(),
						    q.value(rec.indexOf("fechaDesde")).toString(),
						    q.value(rec.indexOf("fechaHasta")).toString(),
						    q.value(rec.indexOf("diasSemana")).toString(),
						    q.value(rec.indexOf("nombrePromocion")).toString(),
						    q.value(rec.indexOf("HTMLPromocion")).toString(),
						    q.value(rec.indexOf("urlImagen")).toString(),
						    q.value(rec.indexOf("urlImagen2")).toString(),
						    q.value(rec.indexOf("ejecutaSiempre")).toString(),
						    q.value(rec.indexOf("codigoTipoCliente")).toString()
                                                                 ));
            }
        }
    }
}
