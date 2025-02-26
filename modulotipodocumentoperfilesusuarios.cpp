
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
#include <QtSql>

#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include <QDebug>
#include <funciones.h>
#include "modulotipodocumentoperfilesusuarios.h"


ModuloTipoDocumentoPerfilesUsuarios::ModuloTipoDocumentoPerfilesUsuarios(QObject *parent)
    : QAbstractListModel(parent)
{


    QHash<int, QByteArray> roles;
    roles[codigoTipoDocumentoRole]="codigoTipoDocumento";
    roles[codigoPerfilRole]="codigoPerfil";
    setRoleNames(roles);
}
TipoDocumentoPerfilesUsuarios::TipoDocumentoPerfilesUsuarios(
        const QString &codigoTipoDocumento,
        const QString &codigoPerfil
        ):
    m_codigoTipoDocumento(codigoTipoDocumento),
    m_codigoPerfil(codigoPerfil)
{}

QString TipoDocumentoPerfilesUsuarios::codigoTipoDocumento()const{
    return m_codigoTipoDocumento;}
QString TipoDocumentoPerfilesUsuarios::codigoPerfil()const{
    return m_codigoPerfil;}

void ModuloTipoDocumentoPerfilesUsuarios::agregar(const TipoDocumentoPerfilesUsuarios &variable)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_TipoDocumentoPerfilesUsuarios << variable;
    endInsertRows();
}

void ModuloTipoDocumentoPerfilesUsuarios::limpiar(){
    m_TipoDocumentoPerfilesUsuarios.clear();
}

int ModuloTipoDocumentoPerfilesUsuarios::rowCount(const QModelIndex & parent) const {
    return m_TipoDocumentoPerfilesUsuarios.count();
}

QVariant ModuloTipoDocumentoPerfilesUsuarios::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_TipoDocumentoPerfilesUsuarios.count()){
        return QVariant();

    }

    const TipoDocumentoPerfilesUsuarios &variable = m_TipoDocumentoPerfilesUsuarios[index.row()];
    if (role == codigoTipoDocumentoRole){
        return variable.codigoTipoDocumento();
    }
    else if (role == codigoPerfilRole)
    {
        return variable.codigoPerfil();
    }
    return QVariant();
}




bool ModuloTipoDocumentoPerfilesUsuarios::retornaTipoDocumentoActivoPorPerfil(QString _codigoTipoDocumento,QString _codigoPerfil){


  /*  bool _valor=false;
    for (int var = 0; var < m_TipoDocumentoPerfilesUsuarios.size(); ++var) {
        if(m_TipoDocumentoPerfilesUsuarios[var].codigoTipoDocumento()==_codigoTipoDocumento && m_TipoDocumentoPerfilesUsuarios[var].codigoPerfil()==_codigoPerfil){

            _valor= true;

        }
    }


    if(m_TipoDocumentoPerfilesUsuarios.size()==0 && _valor==false){*/
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

            if(query.exec("select  codigoTipoDocumento  from TipoDocumentoPerfilesUsuarios where codigoTipoDocumento='"+_codigoTipoDocumento+"' and codigoPerfil='"+_codigoPerfil+"' order by  codigoTipoDocumento ")) {
                if(query.first()){
                    if(query.value(0).toString()!=""){

                        return true;

                    }else{
                        return false;
                    }
                }else{return false;}
            }else{
                return false;
            }
        }else{return false;}
    /*}else{
        return _valor;
    }*/



    /*
    */

}




void ModuloTipoDocumentoPerfilesUsuarios::buscarTipoDocumentoPerfilesUsuarios(){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }



    if(conexion){

        QSqlQuery q = Database::consultaSql("SELECT * FROM TipoDocumentoPerfilesUsuarios;");
        QSqlRecord rec = q.record();


        ModuloTipoDocumentoPerfilesUsuarios::reset();

        if(q.record().count()>0){

            while (q.next()){
                ModuloTipoDocumentoPerfilesUsuarios::agregar(TipoDocumentoPerfilesUsuarios(
                                                                 q.value(rec.indexOf("codigoTipoDocumento")).toString(),
                                                                 q.value(rec.indexOf("codigoPerfil")).toString()
                                                                 ));
            }
        }
    }
}
