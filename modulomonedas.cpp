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

#include "modulomonedas.h"
#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>
#include <Utilidades/database.h>


int ModuloMonedas::m_codigoMoneda;
QString ModuloMonedas::m_descripcionMoneda;
QString ModuloMonedas::m_simboloMoneda;
double ModuloMonedas::m_cotizacionMoneda;
double ModuloMonedas::m_cotizacionMonedaOficial;
QString ModuloMonedas::m_esMonedaReferenciaSistema;
QString ModuloMonedas::m_codigoISO3166;
QString ModuloMonedas::m_codigoISO4217;


ModuloMonedas::ModuloMonedas(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoMonedaRole] = "codigoMoneda";
    roles[DescripcionMonedaRole] = "descripcionMoneda";
    roles[SimboloMonedaRole] = "simboloMoneda";
    roles[CotizacionMonedaRole] = "cotizacionMoneda";

    roles[cotizacionMonedaOficialRole] = "cotizacionMonedaOficial";
    roles[esMonedaReferenciaSistemaRole] = "esMonedaReferenciaSistema";
    roles[codigoISO3166Role] = "codigoISO3166";
    roles[codigoISO4217Role] = "codigoISO4217";

    setRoleNames(roles);

}


Monedas::Monedas(const int &codigoMoneda, const QString &descripcionMoneda, const QString &simboloMoneda,const double &cotizacionMoneda
                 ,const double &cotizacionMonedaOficial
                 , const QString &esMonedaReferenciaSistema
                 , const QString &codigoISO3166
                 , const QString &codigoISO4217)
    : m_codigoMoneda(codigoMoneda)
    , m_descripcionMoneda(descripcionMoneda)
    , m_simboloMoneda(simboloMoneda)
    , m_cotizacionMoneda(cotizacionMoneda)
    , m_cotizacionMonedaOficial(cotizacionMonedaOficial)
    , m_esMonedaReferenciaSistema(esMonedaReferenciaSistema)
    , m_codigoISO3166(codigoISO3166)
    , m_codigoISO4217(codigoISO4217)
{
}

int Monedas::codigoMoneda() const
{
    return m_codigoMoneda;
}

QString Monedas::descripcionMoneda() const
{
    return m_descripcionMoneda;
}
QString Monedas::simboloMoneda() const
{
    return m_simboloMoneda;
}
double Monedas::cotizacionMoneda() const
{
    return m_cotizacionMoneda;
}
double Monedas::cotizacionMonedaOficial() const
{
    return m_cotizacionMonedaOficial;
}


QString Monedas::esMonedaReferenciaSistema() const
{
    return m_esMonedaReferenciaSistema;
}
QString Monedas::codigoISO3166() const
{
    return m_codigoISO3166;
}
QString Monedas::codigoISO4217() const
{
    return m_codigoISO4217;
}



void ModuloMonedas::agregarMonedas(const Monedas &monedas)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Monedas << monedas;
    endInsertRows();
}




void ModuloMonedas::limpiarListaMonedas(){
    m_Monedas.clear();
}

void ModuloMonedas::buscarMonedas(QString campo, QString datoABuscar){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from Monedas where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloMonedas::reset();


        if(q.record().count()>0){

            while (q.next()){



                Monedas mon = Monedas(q.value(rec.indexOf("codigoMoneda")).toInt()
                                      ,q.value(rec.indexOf("descripcionMoneda")).toString()
                                      ,q.value(rec.indexOf("simboloMoneda")).toString()
                                      ,q.value(rec.indexOf("cotizacionMoneda")).toDouble()
                                      ,q.value(rec.indexOf("cotizacionMonedaOficial")).toDouble()
                                      ,q.value(rec.indexOf("esMonedaReferenciaSistema")).toString()
                                      ,q.value(rec.indexOf("codigoISO3166")).toString()
                                      ,q.value(rec.indexOf("codigoISO4217")).toString());
                //m_Monedas.append(mon);
                ModuloMonedas::agregarMonedas(mon);


                /*       ModuloMonedas::agregarMonedas(Monedas(q.value(rec.indexOf("codigoMoneda")).toInt(),

                                                      q.value(rec.indexOf("descripcionMoneda")).toString(),

                                                      q.value(rec.indexOf("simboloMoneda")).toString(),

                                                      q.value(rec.indexOf("cotizacionMoneda")).toDouble(),

                                                      q.value(rec.indexOf("cotizacionMonedaOficial")).toDouble(),

                                                      q.value(rec.indexOf("esMonedaReferenciaSistema")).toString(),

                                                      q.value(rec.indexOf("codigoISO3166")).toString(),

                                                      q.value(rec.indexOf("codigoISO4217")).toString()

                                                      ));    */
            }
        }
    }
}

int ModuloMonedas::rowCount(const QModelIndex & parent) const {
    return m_Monedas.count();
}

QVariant ModuloMonedas::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Monedas.count()){
        return QVariant();

    }
    const Monedas &monedas = m_Monedas[index.row()];

    if (role == CodigoMonedaRole){
        return monedas.codigoMoneda();
    }
    else if (role == DescripcionMonedaRole){
        return monedas.descripcionMoneda();
    }
    else if (role == SimboloMonedaRole){
        return monedas.simboloMoneda();
    }
    else if (role == CotizacionMonedaRole){
        return monedas.cotizacionMoneda();
    }
    else if (role == cotizacionMonedaOficialRole){
        return monedas.cotizacionMonedaOficial();
    }

    else if (role == esMonedaReferenciaSistemaRole){
        return monedas.esMonedaReferenciaSistema();
    }
    else if (role == codigoISO3166Role){
        return monedas.codigoISO3166();
    }
    else if (role == codigoISO4217Role){
        return monedas.codigoISO4217();
    }
    return QVariant();
}

int ModuloMonedas::insertarMonedas(QString _codigoMoneda,QString _descripcionMoneda, QString _codigoISO3166,QString _codigoISO4217,QString _simboloMoneda, QString _cotizacionMoneda, QString _cotizacionMonedaOficial, QString _esMonedaReferenciaSistema) const {

    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar la moneda
    // 1  articulo dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar la moneda
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 La moneda no tiene los datos sufucientes para darse de alta.


    if(_codigoMoneda.trimmed()=="" || _descripcionMoneda.trimmed()=="" || _simboloMoneda.trimmed()=="" || _cotizacionMoneda.trimmed()=="" || _cotizacionMonedaOficial.trimmed()==""){
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

        if(query.exec("select codigoMoneda from Monedas where codigoMoneda='"+_codigoMoneda+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("update Monedas set descripcionMoneda='"+_descripcionMoneda+"', codigoISO3166='"+_codigoISO3166+"', codigoISO4217='"+_codigoISO4217+"', simboloMoneda='"+_simboloMoneda+"',cotizacionMoneda='"+_cotizacionMoneda+"',cotizacionMonedaOficial='"+_cotizacionMonedaOficial+"',esMonedaReferenciaSistema='"+_esMonedaReferenciaSistema+"' where codigoMoneda='"+_codigoMoneda+"'")){
                        return 2;

                    }else{
                        qDebug()<< query.lastError();
                        return -2;
                    }
                }else{
                    qDebug()<< query.lastError();
                    return -2;
                }
            }else{

                if(query.exec("insert INTO Monedas (codigoMoneda,descripcionMoneda,codigoISO3166,codigoISO4217,simboloMoneda,cotizacionMoneda,cotizacionMonedaOficial,esMonedaReferenciaSistema) values('"+_codigoMoneda+"','"+_descripcionMoneda+"','"+_codigoISO3166+"','"+_codigoISO4217+"','"+_simboloMoneda+"','"+_cotizacionMoneda+"','"+_cotizacionMonedaOficial+"','"+_esMonedaReferenciaSistema+"')")){
                    return 1;
                }else{
                    qDebug()<< query.lastError();
                    return -3;
                }
            }
        }else{
            qDebug()<< query.lastError();
            return -4;
        }
    }else{return -1;}
}

bool ModuloMonedas::eliminarMonedas(QString _codigoMoneda) const {
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

        if(query.exec("select codigoMoneda from Monedas where codigoMoneda='"+_codigoMoneda+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("delete from Monedas where codigoMoneda='"+_codigoMoneda+"'")){

                        return true;

                    }else{
                        return false;
                    }
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{return false;}
}

QString ModuloMonedas::retornaDescripcionMoneda(QString _codigoMoneda) const{

    QString _valor="";
    for (int var = 0; var < m_Monedas.size(); ++var) {
        if(QString::number(m_Monedas[var].codigoMoneda())==_codigoMoneda){
            _valor = m_Monedas[var].descripcionMoneda();
        }
    }


    if(m_Monedas.size()==0 && _valor==""){
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

            if(query.exec("select descripcionMoneda from Monedas where codigoMoneda='"+_codigoMoneda+"'")) {

                if(query.first()){
                    if(query.value(0).toString()!=""){
                        return query.value(0).toString();
                    }else{
                        return "";
                    }
                }else{
                    return "";
                }
            }else{
                return "";
            }
        }else{return "";}
    }else{
        return _valor;
    }

    /*
    */
}

QString ModuloMonedas::retornaSimboloMoneda(QString _codigoMoneda) const{

    QString _valor="";
    for (int var = 0; var < m_Monedas.size(); ++var) {
        if(QString::number(m_Monedas[var].codigoMoneda())==_codigoMoneda){
            _valor = m_Monedas[var].simboloMoneda();
        }
    }


    if(m_Monedas.size()==0 && _valor==""){
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

            if(query.exec("select simboloMoneda from Monedas where codigoMoneda='"+_codigoMoneda+"'")) {

                if(query.first()){
                    if(query.value(0).toString()!=""){

                        return query.value(0).toString();

                    }else{
                        return "";
                    }
                }else{
                    return "";
                }
            }else{
                return "";
            }
        }else{return "";}
    }else{
        return _valor;
    }

    /*
    */
}
QString ModuloMonedas::retornaCodigoMoneda(QString _codigoArticulo) const{
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

        if(query.exec("select codigoMoneda from Articulos where codigoArticulo='"+_codigoArticulo+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toString();

                }else{
                    return "";
                }
            }else{
                return "";
            }
        }else{
            return "";
        }
    }else{return "";}
}

double ModuloMonedas::retornaCotizacionMoneda(QString _codigoMoneda) const{

    double _valor=1;
    for (int var = 0; var < m_Monedas.size(); ++var) {
        if(QString::number(m_Monedas[var].codigoMoneda())==_codigoMoneda){
            _valor = m_Monedas[var].cotizacionMoneda();
        }
    }

    if(m_Monedas.size()==0 && _valor==1){
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

            if(query.exec("select cotizacionMoneda from Monedas where codigoMoneda='"+_codigoMoneda+"'")) {
                if(query.first()){
                    if(query.value(0).toString()!=""){

                        return query.value(0).toDouble();

                    }else{
                        return 1;
                    }
                }else{
                    return 1;
                }
            }else{
                return 1;
            }
        }else{return 1;}
    }else{
        return _valor;
    }


}

int ModuloMonedas::actualizarCotizacion(QString _codigoMoneda, QString _cotizacionMoneda) const {

    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el articulo
    // 1  articulo dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar el articulo
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El articulo no tiene los datos sufucientes para darse de alta.


    if(_codigoMoneda.trimmed()=="" || _cotizacionMoneda.trimmed()=="." || _cotizacionMoneda.trimmed()==""){
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

        if(query.exec("select codigoMoneda from Monedas where codigoMoneda='"+_codigoMoneda+"'")) {

            if(query.next()){
                if(query.value(0).toString()!=""){

                    if(query.exec("update Monedas set cotizacionMoneda='"+_cotizacionMoneda+"' where codigoMoneda='"+_codigoMoneda+"'")){

                        return 2;
                    }else{

                        return -2;
                    }
                }else{
                    return -2;
                }
            }else{
                return -2;
            }
        }else{
            return -4;
        }
    }else{return -1;}
}
QString ModuloMonedas::retornaMonedaReferenciaSistema() const{

    QString _valor="";
    for (int var = 0; var < m_Monedas.size(); ++var) {
        if(m_Monedas[var].esMonedaReferenciaSistema()=="1"){
            _valor= QString::number(m_Monedas[var].codigoMoneda());
        }
    }

    if(m_Monedas.size()==0 && _valor==""){
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

            if(query.exec("select codigoMoneda from Monedas where esMonedaReferenciaSistema=1 limit 1")) {
                if(query.first()){
                    if(query.value(0).toString()!=""){

                        return query.value(0).toString();

                    }else{
                        return "";
                    }
                }else{
                    return "";
                }
            }else{
                return "";
            }
        }else{return "";}
    }else{
        return _valor;
    }


}


int ModuloMonedas::ultimoRegistroDeMoneda()const {
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

        if(query.exec("select codigoMoneda from Monedas order by codigoMoneda desc limit 1")) {

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




