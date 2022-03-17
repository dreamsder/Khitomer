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
#include <QtSql>

#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include <QDebug>
#include <funciones.h>
#include "moduloreportesconfiguracion.h"

ModuloReportesConfiguracion::ModuloReportesConfiguracion(QObject *parent)
    : QAbstractListModel(parent)
{


    QHash<int, QByteArray> roles;
    roles[codigoReporteRole]="codigoReporte";
    roles[columnaReporteRole]="columnaReporte";
    roles[alineacionColumnaRole]="alineacionColumna";
    roles[totalizacionColumnaRole]="totalizacionColumna";
    roles[textoPieOpcionalRole]="textoPieOpcional";
    roles[tipoDatoColumnaRole]="tipoDatoColumna";
    setRoleNames(roles);
}
ReportesConfiguracion::ReportesConfiguracion(
        const QString &codigoReporte,
        const QString &columnaReporte,
        const QString &alineacionColumna,
        const QString &totalizacionColumna,
        const QString &textoPieOpcional,
        const QString &tipoDatoColumna
        ):
    m_codigoReporte(codigoReporte),
    m_columnaReporte(columnaReporte),
    m_alineacionColumna(alineacionColumna),
    m_totalizacionColumna(totalizacionColumna),
    m_textoPieOpcional(textoPieOpcional),
    m_tipoDatoColumna(tipoDatoColumna)
{}

QString ReportesConfiguracion::codigoReporte()const{
    return m_codigoReporte;}
QString ReportesConfiguracion::columnaReporte()const{
    return m_columnaReporte;}
QString ReportesConfiguracion::alineacionColumna()const{
    return m_alineacionColumna;}
QString ReportesConfiguracion::totalizacionColumna()const{
    return m_totalizacionColumna;}
QString ReportesConfiguracion::textoPieOpcional()const{
    return m_textoPieOpcional;}
QString ReportesConfiguracion::tipoDatoColumna()const{
    return m_tipoDatoColumna;}

void ModuloReportesConfiguracion::agregar(const ReportesConfiguracion &variable)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ReportesConfiguracion << variable;
    endInsertRows();
}

void ModuloReportesConfiguracion::limpiar(){
    m_ReportesConfiguracion.clear();
}

int ModuloReportesConfiguracion::rowCount(const QModelIndex & parent) const {
    return m_ReportesConfiguracion.count();
}

QVariant ModuloReportesConfiguracion::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_ReportesConfiguracion.count()){
        return QVariant();

    }

    const ReportesConfiguracion &variable = m_ReportesConfiguracion[index.row()];
    if (role == codigoReporteRole){
        return variable.codigoReporte();
    }
    else if (role == columnaReporteRole)
    {
        return variable.columnaReporte();
    }
    else if (role == alineacionColumnaRole)
    {
        return variable.alineacionColumna();
    }
    else if (role == totalizacionColumnaRole)
    {
        return variable.totalizacionColumna();
    }
    else if (role == textoPieOpcionalRole)
    {
        return variable.textoPieOpcional();
    }
    else if (role == tipoDatoColumnaRole)
    {
        return variable.tipoDatoColumna();
    }
    return QVariant();
}






void ModuloReportesConfiguracion::buscarReportesConfiguracion(){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("SELECT * FROM ReportesConfiguracion;");
        QSqlRecord rec = q.record();


        ModuloReportesConfiguracion::reset();

        if(q.record().count()>0){

            while (q.next()){
                ModuloReportesConfiguracion::agregar(ReportesConfiguracion(
                                                                              q.value(rec.indexOf("codigoReporte")).toString(),
                                                                              q.value(rec.indexOf("columnaReporte")).toString(),
                                                                              q.value(rec.indexOf("alineacionColumna")).toString(),
                                                                              q.value(rec.indexOf("totalizacionColumna")).toString(),
                                                                              q.value(rec.indexOf("textoPieOpcional")).toString(),
                                                                              q.value(rec.indexOf("tipoDatoColumna")).toString()
                                                                              ));
            }
        }
    }
}
