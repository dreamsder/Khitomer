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
#include "moduloreportesmenu.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>

ModuloReportesMenu::ModuloReportesMenu(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoMenuReporteRole] = "codigoMenuReporte";
    roles[DescripcionMenuReporteRole] = "descripcionMenuReporte";

    setRoleNames(roles);
}


ReportesMenu::ReportesMenu(const int &codigoMenuReporte, const QString &descripcionMenuReporte)
    : m_codigoMenuReporte(codigoMenuReporte), m_descripcionMenuReporte(descripcionMenuReporte)
{
}

int ReportesMenu::codigoMenuReporte() const
{
    return m_codigoMenuReporte;
}
QString ReportesMenu::descripcionMenuReporte() const
{
    return m_descripcionMenuReporte;
}


void ModuloReportesMenu::agregarReporteMenu(const ReportesMenu &reportesMenu)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ReportesMenu << reportesMenu;
    endInsertRows();
}

void ModuloReportesMenu::limpiarListaReportesMenu(){
    m_ReportesMenu.clear();
}

void ModuloReportesMenu::buscarReportesMenu(QString campo, QString datoABuscar, QString _codigoPerfil){




    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){


        QSqlQuery q;
        QSqlRecord rec;


        QString _listaMenuesPorPerfil=listaCodigoMenusPorPerfil(_codigoPerfil);


        if(_listaMenuesPorPerfil==""){
            q = Database::consultaSql("select * from ReportesMenu where "+campo+"'"+datoABuscar+"'");
            rec = q.record();
            ModuloReportesMenu::reset();
            if(q.record().count()>0){

                while (q.next()){
                    ModuloReportesMenu::agregarReporteMenu(ReportesMenu(q.value(rec.indexOf("codigoMenuReporte")).toInt(), q.value(rec.indexOf("descripcionMenuReporte")).toString()));
                }
            }
        }else{
            q = Database::consultaSql("select * from ReportesMenu where codigoMenuReporte in ("+_listaMenuesPorPerfil+");");
            rec = q.record();
            ModuloReportesMenu::reset();
            if(q.record().count()>0){

                while (q.next()){
                    ModuloReportesMenu::agregarReporteMenu(ReportesMenu(q.value(rec.indexOf("codigoMenuReporte")).toInt(), q.value(rec.indexOf("descripcionMenuReporte")).toString()));
                }
            }
        }
    }
}


QString ModuloReportesMenu::listaCodigoMenusPorPerfil(QString _codigoPerfil){


    if(_codigoPerfil=="" || _codigoPerfil=="-1" || _codigoPerfil=="1"){
        return "";
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

        QSqlQuery q;
        QSqlRecord rec;


        q = Database::consultaSql("select RE.codigoMenuReporte from Reportes RE  join ReportesPerfilesUsuarios RPU on RPU.codigoReporte=RE.codigoReporte where RPU.codigoPerfil='"+_codigoPerfil+"' group by RE.codigoMenuReporte;");
        rec = q.record();

        if(q.record().count()>0){

            QString valorARetornar="";
            int i=0;

            while (q.next()){
                if(i!=0){
                    valorARetornar+=",";
                }
                valorARetornar+=q.value(rec.indexOf("codigoMenuReporte")).toString();
                i++;
            }

            return valorARetornar;
        }else{
            return "";
        }
    }
}

int ModuloReportesMenu::rowCount(const QModelIndex & parent) const {
    return m_ReportesMenu.count();
}

QVariant ModuloReportesMenu::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_ReportesMenu.count()){
        return QVariant();

    }

    const ReportesMenu &reportesMenu = m_ReportesMenu[index.row()];

    if (role == CodigoMenuReporteRole){
        return reportesMenu.codigoMenuReporte();

    }
    else if (role == DescripcionMenuReporteRole){
        return reportesMenu.descripcionMenuReporte();

    }

    return QVariant();
}



