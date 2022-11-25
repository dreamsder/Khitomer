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

#include "modulomediosdepago.h"

#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>
#include <Utilidades/database.h>


ModuloMediosDePago::ModuloMediosDePago(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoMedioPagoRole] = "codigoMedioPago";
    roles[DescripcionMedioPagoRole] = "descripcionMedioPago";
    roles[MonedaMedioPagoRole] = "monedaMedioPago";
    roles[CodigoTipoMedioDePagoRole] = "cotizacionMoneda";

    setRoleNames(roles);



}


MediosDePago::MediosDePago(const int &codigoMedioPago, const QString &descripcionMedioPago, const int &monedaMedioPago,const int &codigoTipoMedioDePago)
    : m_codigoMedioPago(codigoMedioPago), m_descripcionMedioPago(descripcionMedioPago), m_monedaMedioPago(monedaMedioPago), m_codigoTipoMedioDePago(codigoTipoMedioDePago)
{
}

int MediosDePago::codigoMedioPago() const
{
    return m_codigoMedioPago;
}

QString MediosDePago::descripcionMedioPago() const
{
    return m_descripcionMedioPago;
}
int MediosDePago::monedaMedioPago() const
{
    return m_monedaMedioPago;
}
int MediosDePago::codigoTipoMedioDePago() const
{
    return m_codigoTipoMedioDePago;
}


void ModuloMediosDePago::agregarMediosDePago(const MediosDePago &mediosDePago)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_MediosDePago << mediosDePago;
    endInsertRows();
}




void ModuloMediosDePago::limpiarListaMediosDePago(){
    m_MediosDePago.clear();
}

void ModuloMediosDePago::buscarMediosDePago(QString campo, QString datoABuscar){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();

    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from MediosDePago where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloMediosDePago::reset();
        if(q.record().count()>0){

            while (q.next()){

                ModuloMediosDePago::agregarMediosDePago(MediosDePago(q.value(rec.indexOf("codigoMedioPago")).toInt(),

                                                                     q.value(rec.indexOf("descripcionMedioPago")).toString(),

                                                                     q.value(rec.indexOf("monedaMedioPago")).toInt(),

                                                                     q.value(rec.indexOf("codigoTipoMedioDePago")).toInt()

                                                                     ));
            }
        }
    }
}

bool ModuloMediosDePago::utilizaCuotas(QString _codigoMedioPago) const{
   /* bool _valor=false;
    for (int var = 0; var < m_MediosDePago.size(); ++var) {
        if(QString::number(m_MediosDePago[var].codigoMedioPago())==_codigoMedioPago){

            if(QString::number(m_MediosDePago[var].codigoTipoMedioDePago())=="2"){
                return true;
            }
        }
    }


    if(m_MediosDePago.size()==0 && _valor==false){*/
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

            if(query.exec("select codigoTipoMedioDePago from MediosDePago where codigoMedioPago='"+_codigoMedioPago+"'")) {
                if(query.first()){
                    if(query.value(0).toString()=="2"){
                        return true;

                    }else{
                        return false;
                    }
                }else{return false;}
            }else{
                return false;
            }
        }else{return false;}
  /*  }else{
        return _valor;
    }*/
}
bool ModuloMediosDePago::utilizaBanco(QString _codigoMedioPago) const{
   /* bool _valor=false;
    for (int var = 0; var < m_MediosDePago.size(); ++var) {
        if(QString::number(m_MediosDePago[var].codigoMedioPago())==_codigoMedioPago){

            if(QString::number(m_MediosDePago[var].codigoTipoMedioDePago())=="2" || QString::number(m_MediosDePago[var].codigoTipoMedioDePago())=="3"){
                return true;
            }
        }
    }


    if(m_MediosDePago.size()==0 && _valor==false){*/
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

            if(query.exec("select codigoTipoMedioDePago from MediosDePago where codigoMedioPago='"+_codigoMedioPago+"'")) {
                if(query.first()){
                    if(query.value(0).toString()=="2" || query.value(0).toString()=="3"){

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
        }else{return false;}
    /*}else{
        return _valor;
    }*/

    /*
    */
}
bool ModuloMediosDePago::utilizaCuentaBancaria(QString _codigoMedioPago) const{

   /* bool _valor=false;
    for (int var = 0; var < m_MediosDePago.size(); ++var) {
        if(QString::number(m_MediosDePago[var].codigoMedioPago())==_codigoMedioPago){

            if(QString::number(m_MediosDePago[var].codigoTipoMedioDePago())=="4" ){
                return true;
            }
        }
    }


    if(m_MediosDePago.size()==0 && _valor==false){*/
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

            if(query.exec("select codigoTipoMedioDePago from MediosDePago where codigoMedioPago='"+_codigoMedioPago+"'")) {
                if(query.first()){
                    if(query.value(0).toString()=="4"){

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
        }else{return false;}
    /*}else{
        return _valor;
    }*/

    /*
    */
}
bool ModuloMediosDePago::utilizaNumeroCheque(QString _codigoMedioPago) const{

   /* bool _valor=false;
    for (int var = 0; var < m_MediosDePago.size(); ++var) {
        if(QString::number(m_MediosDePago[var].codigoMedioPago())==_codigoMedioPago){

            if(QString::number(m_MediosDePago[var].codigoTipoMedioDePago())=="3" ){
                return true;
            }
        }
    }


    if(m_MediosDePago.size()==0 && _valor==false){*/
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

            if(query.exec("select codigoTipoMedioDePago from MediosDePago where codigoMedioPago='"+_codigoMedioPago+"'")) {
                if(query.first()){
                    if(query.value(0).toString()=="3"){

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

QString ModuloMediosDePago::retornaDescripcionMedioDePago(QString _codigoMedioPago) const{
   /* QString _valor="";
    for (int var = 0; var < m_MediosDePago.size(); ++var) {
        if(QString::number(m_MediosDePago[var].codigoMedioPago())==_codigoMedioPago){
            _valor=m_MediosDePago[var].descripcionMedioPago();
        }
    }


    if(m_MediosDePago.size()==0 && _valor==""){*/
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

            if(query.exec("select descripcionMedioPago  from MediosDePago where codigoMedioPago='"+_codigoMedioPago+"'")) {
                if(query.first()){
                    if(query.value(0).toString()!=""){

                        return query.value(0).toString();

                    }else{
                        return "";
                    }
                }else{return "";}
            }else{
                return "";
            }
        }else{return "";}
   /* }else{
        return _valor;
    }*/

    /*
    */
}

QString ModuloMediosDePago::retornaMonedaMedioDePago(QString _codigoMedioPago) const{

//    qDebug()<<"Codigo medio de pago en c++: "+_codigoMedioPago ;

    /*QString _valor="";
    for (int var = 0; var < m_MediosDePago.size(); ++var) {
        if(QString::number(m_MediosDePago[var].codigoMedioPago())==_codigoMedioPago){

            _valor= m_MediosDePago[var].monedaMedioPago();

        }
    }*/


   // if(m_MediosDePago.size()==0 && _valor==""){
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

            if(query.exec("select monedaMedioPago from MediosDePago where codigoMedioPago='"+_codigoMedioPago+"'")) {
                if(query.first()){
                    if(query.value(0).toString()!=""){

                        return query.value(0).toString();

                    }else{
                        return "";
                    }
                }else{return "";}
            }else{
                return "";
            }
        }else{return "";}
    /*}else{
        return _valor;
    }*/


    /*
    */
}




int ModuloMediosDePago::rowCount(const QModelIndex & parent) const {
    return m_MediosDePago.count();
}

QVariant ModuloMediosDePago::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_MediosDePago.count()){
        return QVariant();

    }
    const MediosDePago &mediosDePago = m_MediosDePago[index.row()];

    if (role == CodigoMedioPagoRole){
        return mediosDePago.codigoMedioPago();
    }
    else if (role == DescripcionMedioPagoRole){
        return mediosDePago.descripcionMedioPago();
    }
    else if (role == MonedaMedioPagoRole){
        return mediosDePago.monedaMedioPago();
    }
    else if (role == CodigoTipoMedioDePagoRole){
        return mediosDePago.codigoTipoMedioDePago();
    }
    return QVariant();
}


bool ModuloMediosDePago::guardarLineaMedioDePago(QString _codigoDocumento,QString _codigoTipoDocumento,QString _numeroLinea,
                                                 QString _codigoMedioPago,QString _monedaMedioPago,QString _importePago,QString _cuotas,

                                                 QString _codigoBanco,QString _codigoTarjetaCredito,QString _numeroCheque
                                                 ,QString _codigoTipoCheque,QString _fechaCheque

                                                 ,QString _codigoDocumentoCheque,QString _codigoTipoDocumentoCheque
                                                 ,QString _numeroLineaDocumentoCheque
                                                 ,QString _numeroCuentaBancaria
                                                 ,QString _codigoBancoCuentaBancaria
                                                 ,QString _serieDocumento
                                                 ) const {




    if(_codigoDocumento.trimmed()=="" || _codigoTipoDocumento.trimmed()==""){
        return false;
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

        if(query.exec("insert INTO DocumentosLineasPago (codigoDocumento, codigoTipoDocumento, numeroLinea, codigoMedioPago, monedaMedioPago, importePago, cuotas,codigoBanco,codigoTarjetaCredito,numeroCheque, codigoTipoCheque, fechaCheque,documentoChequeDiferido, tipoDocumentoChequeDiferido,lineaDocumentoChequeDiferido, numeroCuentaBancaria,codigoBancoCuentaBancaria,serieDocumento)values('"+_codigoDocumento+"','"+_codigoTipoDocumento+"','"+_numeroLinea+"','"+_codigoMedioPago+"','"+_monedaMedioPago+"','"+_importePago+"','"+_cuotas+"','"+_codigoBanco+"','"+_codigoTarjetaCredito+"','"+_numeroCheque+"','"+_codigoTipoCheque+"','"+_fechaCheque+"','"+_codigoDocumentoCheque+"','"+_codigoTipoDocumentoCheque+"','"+_numeroLineaDocumentoCheque+"','"+_numeroCuentaBancaria+"','"+_codigoBancoCuentaBancaria+"','"+_serieDocumento+"' )")){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool ModuloMediosDePago::eliminarLineaMedioDePagoDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{

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

        if(query.exec("delete from DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")){

            return true;

        }else{
            return false;
        }
    }else{
        return false;
    }
}
int ModuloMediosDePago::retornaCantidadLineasMedioDePago(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{
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

        if(query.exec("SELECT count(*) FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){
                    return query.value(0).toInt();
                }else{
                    return 0;
                }
            }else{return 0;}
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

QString ModuloMediosDePago::retornoCodigoMedioPago(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT codigoMedioPago FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"' and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}


        }else{
            return "";
        }
    }else{
        return "";
    }
}
QString ModuloMediosDePago::retornoMonedaMedioPago(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT monedaMedioPago FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"' and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}
        }else{
            return "";
        }
    }else{
        return "";
    }
}
double ModuloMediosDePago::retornoImportePago(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT importePago FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"'  and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toDouble();
                }else{
                    return 0.00;
                }
            }else{return 0.00;}


        }else{
            return 0.00;
        }
    }else{
        return 0.00;
    }
}
QString ModuloMediosDePago::retornoCuotas(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT cuotas FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"'  and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}


        }else{
            return "";
        }
    }else{
        return "";
    }
}
QString ModuloMediosDePago::retornoCodigoTarjetaCredito(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT codigoTarjetaCredito FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"'  and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}


        }else{
            return "";
        }
    }else{
        return "";
    }
}
QString ModuloMediosDePago::retornoCodigoBanco(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT codigoBanco FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"'  and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}


        }else{
            return "";
        }
    }else{
        return "";
    }
}
QString ModuloMediosDePago::retornoNumeroCheque(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT numeroCheque FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"' and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}
        }else{
            return "";
        }
    }else{
        return "";
    }
}
QString ModuloMediosDePago::retornoTipoCheque(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT codigoTipoCheque FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"' and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}
        }else{
            return "";
        }
    }else{
        return "";
    }
}
QString ModuloMediosDePago::retornoFechaCheque(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT fechaCheque FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"' and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}
        }else{
            return "";
        }
    }else{
        return "";
    }
}
QString ModuloMediosDePago::retornoCodigoDocumentoCheque(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT documentoChequeDiferido FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"'  and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}
        }else{
            return "";
        }
    }else{
        return "";
    }
}
QString ModuloMediosDePago::retornoCodigoTipoDocumentoCheque(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT tipoDocumentoChequeDiferido FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"'  and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}
        }else{
            return "";
        }
    }else{
        return "";
    }
}

QString ModuloMediosDePago::retornoSerieDocumentoCheque(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT serieDocumento FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"'  and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}
        }else{
            return "";
        }
    }else{
        return "";
    }
}


QString ModuloMediosDePago::retornoCuentaBancaria(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT numeroCuentaBancaria FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"' and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}
        }else{
            return "";
        }
    }else{
        return "";
    }
}
QString ModuloMediosDePago::retornoBancoCuentaBancaria(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT codigoBancoCuentaBancaria FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"'  and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}
        }else{
            return "";
        }
    }else{
        return "";
    }
}
QString ModuloMediosDePago::retornoNumeroLineaDocumentoCheque(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT lineaDocumentoChequeDiferido FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"'  and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}
        }else{
            return "";
        }
    }else{
        return "";
    }
}
bool ModuloMediosDePago::retornoEsDiferidoCheque(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT codigoTipoCheque FROM DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"'  and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    if(query.value(0).toString()=="2"){
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
