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
#include "modulocuentasbancarias.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>



ModuloCuentasBancarias::ModuloCuentasBancarias(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[numeroCuentaBancariaRole] = "numeroCuentaBancaria";
    roles[codigoBancoRole] = "codigoBanco";
    roles[descripcionCuentaBancariaRole] = "descripcionCuentaBancaria";
    roles[observacionesRole] = "observaciones";

    setRoleNames(roles);
}

CuentasBancarias::CuentasBancarias(const QString &numeroCuentaBancaria, const int &codigoBanco,const QString &descripcionCuentaBancaria,const QString &observaciones)
    : m_numeroCuentaBancaria(numeroCuentaBancaria), m_codigoBanco(codigoBanco), m_descripcionCuentaBancaria(descripcionCuentaBancaria), m_observaciones(observaciones)
{
}

QString CuentasBancarias::numeroCuentaBancaria() const
{
    return m_numeroCuentaBancaria;
}
int CuentasBancarias::codigoBanco() const
{
    return m_codigoBanco;
}
QString CuentasBancarias::descripcionCuentaBancaria() const
{
    return m_descripcionCuentaBancaria;
}
QString CuentasBancarias::observaciones() const
{
    return m_observaciones;
}
void ModuloCuentasBancarias::agregarCuentaBancaria(const CuentasBancarias &cuentasBancarias)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_CuentasBancarias << cuentasBancarias;
    endInsertRows();
}

void ModuloCuentasBancarias::limpiarListaCuentasBancarias(){
    m_CuentasBancarias.clear();
}

void ModuloCuentasBancarias::buscarCuentasBancarias(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from CuentaBancaria where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloCuentasBancarias::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloCuentasBancarias::agregarCuentaBancaria(CuentasBancarias(
                                                                  q.value(rec.indexOf("numeroCuentaBancaria")).toString(),
                                                                  q.value(rec.indexOf("codigoBanco")).toInt(),
                                                                  q.value(rec.indexOf("descripcionCuentaBancaria")).toString(),
                                                                  q.value(rec.indexOf("observaciones")).toString()
                                                                  ));
            }
        }
    }
}

int ModuloCuentasBancarias::rowCount(const QModelIndex & parent) const {
    return m_CuentasBancarias.count();
}

QVariant ModuloCuentasBancarias::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_CuentasBancarias.count()){
        return QVariant();
    }

    const CuentasBancarias &cuentasBancarias = m_CuentasBancarias[index.row()];

    if (role == numeroCuentaBancariaRole){
        return cuentasBancarias.numeroCuentaBancaria();
    }else if (role == codigoBancoRole){
        return cuentasBancarias.codigoBanco();
    }else if (role == descripcionCuentaBancariaRole){
        return cuentasBancarias.descripcionCuentaBancaria();
    }else if (role == observacionesRole){
        return cuentasBancarias.observaciones();
    }

    return QVariant();
}
bool ModuloCuentasBancarias::eliminarCuentaBancaria(QString _numeroCuenta,QString _codigoBanco) const {
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

        if(query.exec("select numeroCuentaBancaria from Documentos where numeroCuentaBancaria='"+_numeroCuenta+"' and codigoBanco='"+_codigoBanco+"'")) {
            if(query.first()){
                return false;
            }else{
                if(query.exec("delete from CuentaBancaria where numeroCuentaBancaria='"+_numeroCuenta+"' and codigoBanco='"+_codigoBanco+"'")){
                    return true;
                }else{
                    return false;
                }
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}
int ModuloCuentasBancarias::insertarCuentaBancaria(QString _numeroCuentaBancaria,QString _codigoBanco,QString _descripcionCuentaBancaria,QString _observaciones){

    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar la Cuenta Bancaria
    // 1  rubro dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar la Cuenta Bancaria
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 La Cuenta Bancaria no tiene los datos sufucientes para darse de alta.
    if(_numeroCuentaBancaria.trimmed()=="" || _codigoBanco.trimmed()=="" ){
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
        if(query.exec("select numeroCuentaBancaria from CuentaBancaria where numeroCuentaBancaria='"+_numeroCuentaBancaria+"' and codigoBanco='"+_codigoBanco+"'")) {

            if(query.first()){

                if(query.value(0).toString()!=""){

                    if(query.exec("update CuentaBancaria set descripcionCuentaBancaria='"+_descripcionCuentaBancaria+"',observaciones='"+_observaciones+"'  where numeroCuentaBancaria='"+_numeroCuentaBancaria+"' and codigoBanco='"+_codigoBanco+"'")){
                        return 2;
                    }else{
                        return -2;
                    }
                }else{
                    return -4;
                }
            }else{
                if(query.exec("insert INTO CuentaBancaria (numeroCuentaBancaria,codigoBanco,descripcionCuentaBancaria,observaciones) values('"+_numeroCuentaBancaria+"','"+_codigoBanco+"','"+_descripcionCuentaBancaria+"','"+_observaciones+"')")){
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
QString ModuloCuentasBancarias::retornaPrimeraCuentaBancariaDisponible()const {

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

        if(query.exec("select numeroCuentaBancaria from CuentaBancaria order by numeroCuentaBancaria desc limit 1")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toString();

                }else{
                    return "";
                }
            }else {return "";}
        }else{
            return "";
        }
    }else{
        return "";
    }
}
QString ModuloCuentasBancarias::retornaBancoCuentaBancaria(QString _numeroCuentaBancaria)const {

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

        if(query.exec("select codigoBanco from CuentaBancaria where numeroCuentaBancaria='"+_numeroCuentaBancaria+"' order by numeroCuentaBancaria desc limit 1")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toString();

                }else{
                    return "";
                }
            }else {return "";}
        }else{
            return "";
        }
    }else{
        return "";
    }
}

QString ModuloCuentasBancarias::retornaTotalXMonedaCuentaBancaria(QString _numeroCuentaBancaria, QString _codigoBancoCuentaBancaria,QString _codigoMoneda)const {

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

        if(query.exec("select "
                      "ROUND(sum(case when T.utilizaCuentaBancaria=1 "
                      "then "
                      "case when (DLP.importePago*T.afectaCuentaBancaria) is null then 0.00 else  (DLP.importePago*T.afectaCuentaBancaria) end "
                      "else "
                      "case when (DLP.importePago*T.afectaTotales) is null then 0.00 else (DLP.importePago*T.afectaTotales) end "
                      "end),2)'Valor Total:'  "
                      "from DocumentosLineasPago DLP   "
                      "join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento and D.serieDocumento=DLP.serieDocumento   "
                      "join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  "
                      "join Monedas MON on MON.codigoMoneda=DLP.monedaMedioPago "
                      "join CuentaBancaria CB on CB.numeroCuentaBancaria=DLP.numeroCuentaBancaria and CB.codigoBanco=DLP.codigoBancoCuentaBancaria "
                      "where  D.codigoEstadoDocumento not in ('C','A','P')  "
                      "and CB.numeroCuentaBancaria='"+_numeroCuentaBancaria+"'  "
                      "and CB.codigoBanco='"+_codigoBancoCuentaBancaria+"'  and MON.codigoMoneda='"+_codigoMoneda+"'   "
                      "group by CB.numeroCuentaBancaria , CB.codigoBanco, MON.codigoMoneda ")){

            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toString();

                }else{
                    return "0";
                }
            }else {return "0";}
        }else{
            return "0";
        }
    }else{
        return "0";
    }
}

