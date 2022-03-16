/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2019>  <Cristian Montano>

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
#include "moduloreportesperfilesusuarios.h"


ModuloReportesPerfilesUsuarios::ModuloReportesPerfilesUsuarios(QObject *parent)
    : QAbstractListModel(parent)
{


    QHash<int, QByteArray> roles;
    roles[codigoReporteRole]="codigoReporte";
    roles[codigoPerfilRole]="codigoPerfil";
    setRoleNames(roles);
}
ReportesPerfilesUsuarios::ReportesPerfilesUsuarios(
        const QString &codigoReporte,
        const QString &codigoPerfil
        ):
    m_codigoReporte(codigoReporte),
    m_codigoPerfil(codigoPerfil)
{}

QString ReportesPerfilesUsuarios::codigoReporte()const{
    return m_codigoReporte;}
QString ReportesPerfilesUsuarios::codigoPerfil()const{
    return m_codigoPerfil;}

void ModuloReportesPerfilesUsuarios::agregar(const ReportesPerfilesUsuarios &variable)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ReportesPerfilesUsuarios << variable;
    endInsertRows();
}

void ModuloReportesPerfilesUsuarios::limpiar(){
    m_ReportesPerfilesUsuarios.clear();
}

int ModuloReportesPerfilesUsuarios::rowCount(const QModelIndex & parent) const {
    return m_ReportesPerfilesUsuarios.count();
}

QVariant ModuloReportesPerfilesUsuarios::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_ReportesPerfilesUsuarios.count()){
        return QVariant();

    }

    const ReportesPerfilesUsuarios &variable = m_ReportesPerfilesUsuarios[index.row()];
    if (role == codigoReporteRole){
        return variable.codigoReporte();
    }
    else if (role == codigoPerfilRole)
    {
        return variable.codigoPerfil();
    }
    return QVariant();
}


bool ModuloReportesPerfilesUsuarios::retornaReporteActivoPorPerfil(QString _codigoReporte,QString _codigoPerfil){


    bool _valor=false;
    for (int var = 0; var < m_ReportesPerfilesUsuarios.size(); ++var) {
        if(m_ReportesPerfilesUsuarios[var].codigoReporte()==_codigoReporte && m_ReportesPerfilesUsuarios[var].codigoPerfil()==_codigoPerfil){

            _valor= true;

        }
    }
    return _valor;
    /*
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

        if(query.exec("SELECT codigoReporte FROM ReportesPerfilesUsuarios where codigoReporte='"+_codigoReporte+"' and codigoPerfil='"+_codigoPerfil+"' ")) {
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
    }else{return false;}*/

}


void ModuloReportesPerfilesUsuarios::buscarReportesPerfilesUsuarios(){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("SELECT * FROM ReportesPerfilesUsuarios;");
        QSqlRecord rec = q.record();


        ModuloReportesPerfilesUsuarios::reset();

        if(q.record().count()>0){

            while (q.next()){
                ModuloReportesPerfilesUsuarios::agregar(ReportesPerfilesUsuarios(
                                                                                    q.value(rec.indexOf("codigoReporte")).toString(),
                                                                                    q.value(rec.indexOf("codigoPerfil")).toString()
                                                                                    ));
            }
        }
    }
}
