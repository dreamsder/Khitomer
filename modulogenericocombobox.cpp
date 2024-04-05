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
#include "modulogenericocombobox.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>

ModuloGenericoCombobox::ModuloGenericoCombobox(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[codigoItemRole] = "codigoItem";
    roles[descripcionItemRole] = "descripcionItem";
    roles[checkBoxActivoRole] = "checkBoxActivo";

    roles[codigoTipoItemRole] = "codigoTipoItem";
    roles[valorItemRole] = "valorItem";
    roles[descripcionItemSegundafilaRole] = "descripcionItemSegundafila";

    roles[serieDocRole] = "serieDoc";



    setRoleNames(roles);
}


ModuloGenerico::ModuloGenerico(const QString &codigoItem, const QString &descripcionItem, const bool &checkBoxActivo
    , const QString &codigoTipoItem, const QString &valorItem, const QString &descripcionItemSegundafila
    , const QString &serieDoc)
    : m_codigoItem(codigoItem), m_descripcionItem(descripcionItem), m_checkBoxActivo(checkBoxActivo)
    , m_codigoTipoItem(codigoTipoItem), m_valorItem(valorItem), m_descripcionItemSegundafila(descripcionItemSegundafila)
    , m_serieDoc(serieDoc)
{
}

QString ModuloGenerico::codigoItem() const
{
    return m_codigoItem;
}
QString ModuloGenerico::descripcionItem() const
{
    return m_descripcionItem;
}
bool ModuloGenerico::checkBoxActivo() const
{
    return m_checkBoxActivo;
}
QString ModuloGenerico::codigoTipoItem() const
{
    return m_codigoTipoItem;
}
QString ModuloGenerico::valorItem() const
{
    return m_valorItem;
}
QString ModuloGenerico::descripcionItemSegundafila() const
{
    return m_descripcionItemSegundafila;
}
QString ModuloGenerico::serieDoc() const
{
    return m_serieDoc;
}


void ModuloGenericoCombobox::agregarModuloGenerico(const ModuloGenerico &moduloGenerico)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ModuloGenerico << moduloGenerico;
    endInsertRows();
}

void ModuloGenericoCombobox::limpiarListaModuloGenerico(){
    m_ModuloGenerico.clear();
}

void ModuloGenericoCombobox::buscarModuloGenerico(){

    ModuloGenericoCombobox::limpiarListaModuloGenerico();
    ModuloGenericoCombobox::agregarModuloGenerico(ModuloGenerico("1","",false,"","","",""));

}
void ModuloGenericoCombobox::buscarTodosLosTipoDocumentos(){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery q = Database::consultaSql("select codigoTipoDocumento,descripcionTipoDocumento from TipoDocumento ;");
        QSqlRecord rec = q.record();

        ModuloGenericoCombobox::reset();
        if(q.record().count()>0){
            while (q.next()){

                ModuloGenericoCombobox::agregarModuloGenerico(ModuloGenerico( q.value(rec.indexOf("codigoTipoDocumento")).toString(),
                                                                                 q.value(rec.indexOf("descripcionTipoDocumento")).toString(),
                                                                                false,"","","",""
                                                                                 ));
            }
        }
    }
}

void ModuloGenericoCombobox::buscarTodosLosReportes(){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery q = Database::consultaSql("select codigoReporte,descripcionReporte from Reportes order by descripcionReporte;");
        QSqlRecord rec = q.record();

        ModuloGenericoCombobox::reset();
        if(q.record().count()>0){
            while (q.next()){

                ModuloGenericoCombobox::agregarModuloGenerico(ModuloGenerico( q.value(rec.indexOf("codigoReporte")).toString(),
                                                                                 q.value(rec.indexOf("descripcionReporte")).toString(),
                                                                              false,"","","",""
                                                                                 ));
            }
        }
    }
}


void ModuloGenericoCombobox::buscarTodosLosTiposPromocion(){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery q = Database::consultaSql("select idTipoPromocion,nombreTipoPromocion from TipoPromocion order by nombreTipoPromocion;");
        QSqlRecord rec = q.record();

        ModuloGenericoCombobox::reset();
        if(q.record().count()>0){
            while (q.next()){

                ModuloGenericoCombobox::agregarModuloGenerico(ModuloGenerico( q.value(rec.indexOf("idTipoPromocion")).toString(),
                                                                                 q.value(rec.indexOf("nombreTipoPromocion")).toString(),
                                                                              false,"","","",""
                                                                                 ));
            }
        }
    }
}


int ModuloGenericoCombobox::rowCount(const QModelIndex & parent) const {
    return m_ModuloGenerico.count();
}

QVariant ModuloGenericoCombobox::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_ModuloGenerico.count()){
        return QVariant();

    }

    const ModuloGenerico &moduloGenerico = m_ModuloGenerico[index.row()];

    if (role == codigoItemRole){
        return moduloGenerico.codigoItem();
    }
    else if (role == descripcionItemRole){
        return moduloGenerico.descripcionItem();
    }
    else if (role == checkBoxActivoRole){
        return moduloGenerico.checkBoxActivo();
    }
    else if (role == codigoTipoItemRole){
        return moduloGenerico.codigoTipoItem();
    }
    else if (role == valorItemRole){
        return moduloGenerico.valorItem();
    }
    else if (role == descripcionItemSegundafilaRole){
        return moduloGenerico.descripcionItemSegundafila();
    }

    else if (role == serieDocRole){
        return moduloGenerico.serieDoc();
    }
    return QVariant();
}

QString ModuloGenericoCombobox::retornarCodigoItem(int indice) const{
                return m_ModuloGenerico[indice].codigoItem();
}
QString ModuloGenericoCombobox::retornarDescripcionItem(int indice) const{
                return m_ModuloGenerico[indice].descripcionItem();
}
bool ModuloGenericoCombobox::retornarCheckBoxActivo(int indice) const{
                return m_ModuloGenerico[indice].checkBoxActivo();
}
QString ModuloGenericoCombobox::retornarCodigoTipoItem(int indice) const{
                return m_ModuloGenerico[indice].codigoTipoItem();
}
QString ModuloGenericoCombobox::retornarValorItem(int indice) const{
                return m_ModuloGenerico[indice].valorItem();
}
QString ModuloGenericoCombobox::retornarDescripcionItemSegundafila(int indice) const{
                return m_ModuloGenerico[indice].descripcionItemSegundafila();
}
QString ModuloGenericoCombobox::retornarSerieDoc(int indice) const{
                return m_ModuloGenerico[indice].serieDoc();
}
