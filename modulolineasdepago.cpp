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
#include "modulolineasdepago.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>



ModuloLineasDePago::ModuloLineasDePago(QObject *parent)
    : QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[codigoDocumentoRole] = "codigoDocumento";
    roles[codigoTipoDocumentoRole] = "codigoTipoDocumento";
    roles[serieDocumentoRole] = "serieDocumento";
    roles[numeroLineaRole] = "numeroLinea";
    roles[codigoMedioPagoRole] = "codigoMedioPago";
    roles[monedaMedioPagoRole] = "monedaMedioPago";
    roles[importePagoRole] = "importePago";
    roles[cuotasRole] = "cuotas";
    roles[codigoBancoRole] = "codigoBanco";
    roles[codigoTarjetaCreditoRole] = "codigoTarjetaCredito";
    roles[numeroChequeRole] = "numeroCheque";
    roles[tarjetaCobradaRole] = "tarjetaCobrada";
    roles[montoCobradoRole] = "montoCobrado";
    roles[codigoTipoChequeRole] = "codigoTipoCheque";
    roles[fechaChequeRole] = "fechaCheque";
    roles[numeroCuentaBancariaRole] = "numeroCuentaBancaria";
    roles[codigoBancoCuentaBancariaRole] = "codigoBancoCuentaBancaria";



    setRoleNames(roles);
}


LineasDePago::LineasDePago(
        const QString &codigoDocumento,
        const QString &codigoTipoDocumento,
        const QString &serieDocumento,
        const QString &numeroLinea,
        const QString &codigoMedioPago,
        const QString &monedaMedioPago,
        const QString &importePago,
        const QString &cuotas,
        const QString &codigoBanco,
        const QString &codigoTarjetaCredito,
        const QString &numeroCheque,
        const QString &tarjetaCobrada,
        const QString &montoCobrado,
        const QString &codigoTipoCheque,
        const QString &fechaCheque,
        const QString &numeroCuentaBancaria,
        const QString &codigoBancoCuentaBancaria


        )
    : m_codigoDocumento(codigoDocumento),
      m_codigoTipoDocumento(codigoTipoDocumento),
      m_serieDocumento(serieDocumento),
      m_numeroLinea(numeroLinea),
      m_codigoMedioPago(codigoMedioPago),
      m_monedaMedioPago(monedaMedioPago),
      m_importePago(importePago),
      m_cuotas(cuotas),
      m_codigoBanco(codigoBanco),
      m_codigoTarjetaCredito(codigoTarjetaCredito),
      m_numeroCheque(numeroCheque),
      m_tarjetaCobrada(tarjetaCobrada),
      m_montoCobrado(montoCobrado),
      m_codigoTipoCheque(codigoTipoCheque),
      m_fechaCheque(fechaCheque),
      m_numeroCuentaBancaria(numeroCuentaBancaria),
      m_codigoBancoCuentaBancaria(codigoBancoCuentaBancaria)

{

}

QString LineasDePago::codigoDocumento() const{ return m_codigoDocumento;}
QString LineasDePago::codigoTipoDocumento() const{ return m_codigoTipoDocumento;}
QString LineasDePago::serieDocumento() const{ return m_serieDocumento;}
QString LineasDePago::numeroLinea() const{ return m_numeroLinea;}
QString LineasDePago::codigoMedioPago() const{ return m_codigoMedioPago;}
QString LineasDePago::monedaMedioPago() const{ return m_monedaMedioPago;}
QString LineasDePago::importePago() const{ return m_importePago;}
QString LineasDePago::cuotas() const{ return m_cuotas;}
QString LineasDePago::codigoBanco() const{ return m_codigoBanco;}
QString LineasDePago::codigoTarjetaCredito() const{ return m_codigoTarjetaCredito;}
QString LineasDePago::numeroCheque() const{ return m_numeroCheque;}
QString LineasDePago::tarjetaCobrada() const{ return m_tarjetaCobrada;}
QString LineasDePago::montoCobrado() const{ return m_montoCobrado;}
QString LineasDePago::codigoTipoCheque() const{ return m_codigoTipoCheque;}
QString LineasDePago::fechaCheque() const{ return m_fechaCheque;}
QString LineasDePago::numeroCuentaBancaria() const{ return m_numeroCuentaBancaria;}
QString LineasDePago::codigoBancoCuentaBancaria() const{ return m_codigoBancoCuentaBancaria;}

void ModuloLineasDePago::agregarLineaDePago(const LineasDePago &lineaDePago)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_LineasDePago << lineaDePago;
    endInsertRows();
}

void ModuloLineasDePago::limpiarListaLineasDePago(){
    m_LineasDePago.clear();
}

void ModuloLineasDePago::buscarLineasDePagoChequesDiferidos(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery q = Database::consultaSql("select DOCLP.* from DocumentosLineasPago DOCLP join Documentos DOC on DOC.codigoDocumento=DOCLP.codigoDocumento and DOC.codigoTipoDocumento=DOCLP.codigoTipoDocumento and DOC.serieDocumento=DOCLP.serieDocumento join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento   join MediosDePago MDP on MDP.codigoMedioPago=DOCLP.codigoMedioPago  where   MDP.codigoTipoMedioDePago=3 and DOCLP.montoCobrado<importePago and DOCLP.documentoChequeDiferido=0 and DOCLP.tipoDocumentoChequeDiferido=0 and  TD.afectaCuentaBancaria!=1 and  DOC.codigoEstadoDocumento not in ('C','A','P')  and "+campo+"'"+datoABuscar+"' order by DOC.fechaEmisionDocumento");
        QSqlRecord rec = q.record();

        ModuloLineasDePago::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloLineasDePago::agregarLineaDePago(LineasDePago(
                                                           q.value(rec.indexOf("codigoDocumento")).toString(),
                                                           q.value(rec.indexOf("codigoTipoDocumento")).toString(),
                                                           q.value(rec.indexOf("serieDocumento")).toString(),
                                                           q.value(rec.indexOf("numeroLinea")).toString(),
                                                           q.value(rec.indexOf("codigoMedioPago")).toString(),
                                                           q.value(rec.indexOf("monedaMedioPago")).toString(),
                                                           q.value(rec.indexOf("importePago")).toString(),
                                                           q.value(rec.indexOf("cuotas")).toString(),
                                                           q.value(rec.indexOf("codigoBanco")).toString(),
                                                           q.value(rec.indexOf("codigoTarjetaCredito")).toString(),
                                                           q.value(rec.indexOf("numeroCheque")).toString(),
                                                           q.value(rec.indexOf("tarjetaCobrada")).toString(),
                                                           q.value(rec.indexOf("montoCobrado")).toString(),
                                                           q.value(rec.indexOf("codigoTipoCheque")).toString(),
                                                           q.value(rec.indexOf("fechaCheque")).toString(),
                                                           q.value(rec.indexOf("numeroCuentaBancaria")).toString(),
                                                           q.value(rec.indexOf("codigoBancoCuentaBancaria")).toString()
                                                           ));
            }
        }
    }
}

int ModuloLineasDePago::rowCount(const QModelIndex & parent) const {
    return m_LineasDePago.count();
}

QVariant ModuloLineasDePago::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_LineasDePago.count()){
        return QVariant();

    }

    const LineasDePago &lineasDePago = m_LineasDePago[index.row()];

    if (role == codigoDocumentoRole){
        return lineasDePago.codigoDocumento();

    }
    else if (role == codigoTipoDocumentoRole){return lineasDePago.codigoTipoDocumento();}
    else if (role == serieDocumentoRole){return lineasDePago.serieDocumento();}


    else if (role == numeroLineaRole){return lineasDePago.numeroLinea();}
    else if (role == codigoMedioPagoRole){return lineasDePago.codigoMedioPago();}
    else if (role == monedaMedioPagoRole){return lineasDePago.monedaMedioPago();}
    else if (role == importePagoRole){return lineasDePago.importePago();}
    else if (role == cuotasRole){return lineasDePago.cuotas();}
    else if (role == codigoBancoRole){return lineasDePago.codigoBanco();}
    else if (role == codigoTarjetaCreditoRole){return lineasDePago.codigoTarjetaCredito();}
    else if (role == numeroChequeRole){return lineasDePago.numeroCheque();}
    else if (role == tarjetaCobradaRole){return lineasDePago.tarjetaCobrada();}
    else if (role == montoCobradoRole){return lineasDePago.montoCobrado();}
    else if (role == codigoTipoChequeRole){return lineasDePago.codigoTipoCheque();}
    else if (role == fechaChequeRole){return lineasDePago.fechaCheque();}
    else if (role == numeroCuentaBancariaRole){return lineasDePago.numeroCuentaBancaria();}
    else if (role == codigoBancoCuentaBancariaRole){return lineasDePago.codigoBancoCuentaBancaria();}

    return QVariant();
}

bool ModuloLineasDePago::actualizarLineaDePagoChequeDiferido(QString _codigoDocumento,QString _codigoTipoDocumento,QString _numeroLineaDocumento,QString _montoPagado, QString _serieDocumento) const {
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

        if(query.exec("update DocumentosLineasPago set montoCobrado='"+_montoPagado+"' where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'  and numeroLinea='"+_numeroLineaDocumento+"'")){

            return true;

        }else{
            return false;
        }

    }
}
bool ModuloLineasDePago::actualizarLineaDePagoTarjetaCredito(QString _codigoDocumento,QString _codigoTipoDocumento,QString _numeroLineaDocumento,QString _montoPagado, QString _serieDocumento) const {
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

        if(query.exec("update DocumentosLineasPago set montoCobrado='"+_montoPagado+"',tarjetaCobrada=1 where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'  and numeroLinea='"+_numeroLineaDocumento+"'")){

            return true;

        }else{
            return false;
        }

    }
}

void ModuloLineasDePago::buscarLineasDePagoTarjetasDeCreditoPendientesDePago(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select DOCLP.* from DocumentosLineasPago DOCLP  join Documentos DOC on DOC.codigoDocumento=DOCLP.codigoDocumento and DOC.codigoTipoDocumento=DOCLP.codigoTipoDocumento and DOC.serieDocumento=DOCLP.serieDocumento join MediosDePago MDP on MDP.codigoMedioPago=DOCLP.codigoMedioPago  where  MDP.codigoTipoMedioDePago=2 and DOCLP.tarjetaCobrada=0  and DOCLP.montoCobrado<importePago  and DOC.codigoEstadoDocumento not in ('C','A','P')  and "+campo+"'"+datoABuscar+"' order by DOC.fechaEmisionDocumento");
        QSqlRecord rec = q.record();

        ModuloLineasDePago::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloLineasDePago::agregarLineaDePago(LineasDePago(
                                                           q.value(rec.indexOf("codigoDocumento")).toString(),
                                                           q.value(rec.indexOf("codigoTipoDocumento")).toString(),
                                                           q.value(rec.indexOf("serieDocumento")).toString(),
                                                           q.value(rec.indexOf("numeroLinea")).toString(),
                                                           q.value(rec.indexOf("codigoMedioPago")).toString(),
                                                           q.value(rec.indexOf("monedaMedioPago")).toString(),
                                                           q.value(rec.indexOf("importePago")).toString(),
                                                           q.value(rec.indexOf("cuotas")).toString(),
                                                           q.value(rec.indexOf("codigoBanco")).toString(),
                                                           q.value(rec.indexOf("codigoTarjetaCredito")).toString(),
                                                           q.value(rec.indexOf("numeroCheque")).toString(),
                                                           q.value(rec.indexOf("tarjetaCobrada")).toString(),
                                                           q.value(rec.indexOf("montoCobrado")).toString(),
                                                           q.value(rec.indexOf("codigoTipoCheque")).toString(),
                                                           q.value(rec.indexOf("fechaCheque")).toString(),
                                                           q.value(rec.indexOf("numeroCuentaBancaria")).toString(),
                                                           q.value(rec.indexOf("codigoBancoCuentaBancaria")).toString()


                                                           ));
            }
        }
    }
}

QString ModuloLineasDePago::retornacodigoDocumento(int index){return m_LineasDePago[index].codigoDocumento();}
QString ModuloLineasDePago::retornacodigoTipoDocumento(int index){return m_LineasDePago[index].codigoTipoDocumento();}
QString ModuloLineasDePago::retornaSerieDocumento(int index){return m_LineasDePago[index].serieDocumento();}


QString ModuloLineasDePago::retornanumeroLinea(int index){return m_LineasDePago[index].numeroLinea();}
QString ModuloLineasDePago::retornacodigoMedioPago(int index){return m_LineasDePago[index].codigoMedioPago();}
QString ModuloLineasDePago::retornamonedaMedioPago(int index){return m_LineasDePago[index].monedaMedioPago();}
QString ModuloLineasDePago::retornaimportePago(int index){return m_LineasDePago[index].importePago();}
QString ModuloLineasDePago::retornacuotas(int index){return m_LineasDePago[index].cuotas();}
QString ModuloLineasDePago::retornacodigoBanco(int index){return m_LineasDePago[index].codigoBanco();}
QString ModuloLineasDePago::retornacodigoTarjetaCredito(int index){return m_LineasDePago[index].codigoTarjetaCredito();}
QString ModuloLineasDePago::retornanumeroCheque(int index){return m_LineasDePago[index].numeroCheque();}
QString ModuloLineasDePago::retornatarjetaCobrada(int index){return m_LineasDePago[index].tarjetaCobrada();}
QString ModuloLineasDePago::retornamontoCobrado(int index){return m_LineasDePago[index].montoCobrado();}
QString ModuloLineasDePago::retornacodigoTipoCheque(int index){return m_LineasDePago[index].codigoTipoCheque();}
QString ModuloLineasDePago::retornafechaCheque(int index){return m_LineasDePago[index].fechaCheque();}
QString ModuloLineasDePago::retornanumeroCuentaBancaria(int index){return m_LineasDePago[index].numeroCuentaBancaria();}
QString ModuloLineasDePago::retornacodigoBancoCuentaBancaria(int index){return m_LineasDePago[index].codigoBancoCuentaBancaria();}




QString ModuloLineasDePago::retornaRazonDeCliente(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{
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


        if(query.exec("select concat(TIPOCLI.descripcionTipoCliente,': ',CLI.razonSocial) from Documentos DOC join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente join TipoCliente TIPOCLI on TIPOCLI.codigoTipoCliente=CLI.tipoCliente where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'  ")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toString();

                }else{
                    return "";
                }
            }else{return "Error BD";}
        }else{
            return "Error SQL";
        }
    }else{
        return "Error BD";
    }
}

QString ModuloLineasDePago::retornaFechaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{
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

        if(query.exec("select DOC.fechaEmisionDocumento from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"'  and DOC.serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toString();

                }else{
                    return "";
                }
            }else{return "Error BD";}
        }else{
            return "Error SQL";
        }
    }else{
        return "Error BD";
    }
}

bool ModuloLineasDePago::verificaMedioPagoEstaUtilizado(QString _codigoDocumento,QString _codigoTipoDocumento,QString _numeroLineaDocumento, QString _serieDocumento) const{
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

        if(query.exec("select montoCobrado from DocumentosLineasPago where codigoDocumento='"+_codigoDocumento+"'  and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'  and numeroLinea='"+_numeroLineaDocumento+"'")) {
            if(query.first()){

                if(query.value(0).toString()=="0"){
                    return false;
                }else{
                    return true;
                }
            }else{
                return true;
            }
        }else{
            return true;
        }
    }else{
        return true;
    }
}
