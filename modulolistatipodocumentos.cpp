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

#include "modulolistatipodocumentos.h"
#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include <QDebug>


ModuloListaTipoDocumentos::ModuloListaTipoDocumentos(QObject *parent)
    : QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[codigoTipoDocumentoRole] = "codigoTipoDocumento";
    roles[descripcionTipoDocumentoRole] = "descripcionTipoDocumento";
    roles[utilizaArticulosRole] = "utilizaArticulos";
    roles[utilizaCodigoBarrasADemandaRole] = "utilizaCodigoBarrasADemanda";
    roles[utilizaTotalesRole] = "utilizaTotales";
    roles[utilizaListaPrecioRole] = "utilizaListaPrecio";
    roles[utilizaMediosDePagoRole] = "utilizaMediosDePago";
    roles[utilizaFechaPrecioRole] = "utilizaFechaPrecio";
    roles[utilizaFechaDocumentoRole] = "utilizaFechaDocumento";
    roles[utilizaNumeroDocumentoRole] = "utilizaNumeroDocumento";
    roles[utilizaSerieDocumentoRole] = "utilizaSerieDocumento";
    roles[serieDocumentoRole] = "serieDocumento";
    roles[utilizaVendedorRole] = "utilizaVendedor";
    roles[utilizaClienteRole] = "utilizaCliente";
    roles[utilizaTipoClienteRole] = "utilizaTipoCliente";
    roles[utilizaSoloProveedoresRole] = "utilizaSoloProveedores";
    roles[afectaCuentaCorrienteRole] = "afectaCuentaCorriente";
    roles[afectaCuentaCorrienteMercaderiaRole] = "afectaCuentaCorrienteMercaderia";
    roles[afectaStockRole] = "afectaStock";
    roles[afectaTotalesRole] = "afectaTotales";
    roles[utilizaCantidadesRole] = "utilizaCantidades";
    roles[utilizaPrecioManualRole] = "utilizaPrecioManual";
    roles[utilizaDescuentoArticuloRole] = "utilizaDescuentoArticulo";
    roles[utilizaDescuentoTotalRole] = "utilizaDescuentoTotal";
    roles[emiteEnImpresoraRole] = "emiteEnImpresora";
    roles[codigoModeloImpresionRole] = "codigoModeloImpresion";
    roles[cantidadCopiasRole] = "cantidadCopias";
    roles[utilizaObservacionesRole] = "utilizaObservaciones";
    roles[afectaCuentaBancariaRole] = "afectaCuentaBancaria";
    roles[utilizaCuentaBancariaRole] = "utilizaCuentaBancaria";
    roles[utilizaPagoChequeDiferidoRole] = "utilizaPagoChequeDiferido";
    roles[utilizaSoloMediosDePagoChequeRole] = "utilizaSoloMediosDePagoCheque";
    roles[esDocumentoDeVentaRole] = "esDocumentoDeVenta";
    roles[descripcionTipoDocumentoImpresoraRole] = "descripcionTipoDocumentoImpresora";
    roles[utilizaArticulosInactivosRole] = "utilizaArticulosInactivos";

    roles[utilizaRedondeoEnTotalRole] = "utilizaRedondeoEnTotal";
    roles[utilizaPrecioManualEnMonedaReferenciaRole] = "utilizaPrecioManualEnMonedaReferencia";
    roles[descripcionCodigoBarrasADemandaRole] = "descripcionCodigoBarrasADemanda";
    roles[utilizaListaPrecioManualRole] = "utilizaListaPrecioManual";

    roles[utilizaFormasDePagoRole] = "utilizaFormasDePago";

    roles[noAfectaIvaRole] = "noAfectaIva";
    roles[utilizaSeteoDePreciosEnListasDePrecioPorArticuloRole] = "utilizaSeteoDePreciosEnListasDePrecioPorArticulo";

    roles[noPermiteFacturarConStockPrevistoCeroRole] = "noPermiteFacturarConStockPrevistoCero";

    roles[imprimeEnFormatoTicketRole] = "imprimeEnFormatoTicket";
    roles[imprimeObservacionesEnTicketRole] = "imprimeObservacionesEnTicket";


    roles[utilizaComentariosRole] = "utilizaComentarios";

    roles[cantidadMaximaLineasEnDocumentoRole] = "cantidadMaximaLineasEnDocumento";





    setRoleNames(roles);


}


TipoDocumentos::TipoDocumentos(
        const int &codigoTipoDocumento,
        const QString &descripcionTipoDocumento,
        const QString &utilizaArticulos,
        const QString &utilizaCodigoBarrasADemanda,
        const QString &utilizaTotales,
        const QString &utilizaListaPrecio,
        const QString &utilizaMediosDePago,
        const QString &utilizaFechaPrecio,
        const QString &utilizaFechaDocumento,
        const QString &utilizaNumeroDocumento,
        const QString &utilizaSerieDocumento,
        const QString &serieDocumento,
        const QString &utilizaVendedor,
        const QString &utilizaCliente,
        const QString &utilizaTipoCliente,
        const QString &utilizaSoloProveedores,
        const QString &afectaCuentaCorriente,
        const QString &afectaCuentaCorrienteMercaderia,
        const QString &afectaStock,
        const QString &afectaTotales,
        const QString &utilizaCantidades,
        const QString &utilizaPrecioManual,
        const QString &utilizaDescuentoArticulo,
        const QString &utilizaDescuentoTotal,
        const QString &emiteEnImpresora,
        const QString &codigoModeloImpresion,
        const QString &cantidadCopias,
        const QString &utilizaObservaciones,
        const QString &afectaCuentaBancaria,
        const QString &utilizaCuentaBancaria,
        const QString &utilizaPagoChequeDiferido,
        const QString &utilizaSoloMediosDePagoCheque,
        const QString &esDocumentoDeVenta,
        const QString &descripcionTipoDocumentoImpresora,
        const QString &utilizaArticulosInactivos,

        const QString &utilizaRedondeoEnTotal,
        const QString &utilizaPrecioManualEnMonedaReferencia,
        const QString &descripcionCodigoBarrasADemanda,
        const QString &utilizaListaPrecioManual,
        const QString &utilizaFormasDePago,
        const QString &noAfectaIva,
        const QString &utilizaSeteoDePreciosEnListasDePrecioPorArticulo,
        const QString &noPermiteFacturarConStockPrevistoCero,
        const QString &imprimeEnFormatoTicket,
        const QString &imprimeObservacionesEnTicket,
        const QString &utilizaComentarios,
        const QString &cantidadMaximaLineasEnDocumento



        )
    : m_codigoTipoDocumento(codigoTipoDocumento),
      m_descripcionTipoDocumento(descripcionTipoDocumento),
      m_utilizaArticulos(utilizaArticulos),
      m_utilizaCodigoBarrasADemanda(utilizaCodigoBarrasADemanda),
      m_utilizaTotales(utilizaTotales),
      m_utilizaListaPrecio(utilizaListaPrecio),
      m_utilizaMediosDePago(utilizaMediosDePago),
      m_utilizaFechaPrecio(utilizaFechaPrecio),
      m_utilizaFechaDocumento(utilizaFechaDocumento),
      m_utilizaNumeroDocumento(utilizaNumeroDocumento),
      m_utilizaSerieDocumento(utilizaSerieDocumento),
      m_serieDocumento(serieDocumento),
      m_utilizaVendedor(utilizaVendedor),
      m_utilizaCliente(utilizaCliente),
      m_utilizaTipoCliente(utilizaTipoCliente),
      m_utilizaSoloProveedores(utilizaSoloProveedores),
      m_afectaCuentaCorriente(afectaCuentaCorriente),
      m_afectaCuentaCorrienteMercaderia(afectaCuentaCorrienteMercaderia),
      m_afectaStock(afectaStock),
      m_afectaTotales(afectaTotales),
      m_utilizaCantidades(utilizaCantidades),
      m_utilizaPrecioManual(utilizaPrecioManual),
      m_utilizaDescuentoArticulo(utilizaDescuentoArticulo),
      m_utilizaDescuentoTotal(utilizaDescuentoTotal),
      m_emiteEnImpresora(emiteEnImpresora),
      m_codigoModeloImpresion(codigoModeloImpresion),
      m_cantidadCopias(cantidadCopias),
      m_utilizaObservaciones(utilizaObservaciones),
      m_afectaCuentaBancaria(afectaCuentaBancaria),
      m_utilizaCuentaBancaria(utilizaCuentaBancaria),
      m_utilizaPagoChequeDiferido(utilizaPagoChequeDiferido),
      m_utilizaSoloMediosDePagoCheque(utilizaSoloMediosDePagoCheque),
      m_esDocumentoDeVenta(esDocumentoDeVenta),
      m_descripcionTipoDocumentoImpresora(descripcionTipoDocumentoImpresora),
      m_utilizaArticulosInactivos(utilizaArticulosInactivos),

      m_utilizaRedondeoEnTotal(utilizaRedondeoEnTotal),
      m_utilizaPrecioManualEnMonedaReferencia(utilizaPrecioManualEnMonedaReferencia),
      m_descripcionCodigoBarrasADemanda(descripcionCodigoBarrasADemanda),
      m_utilizaListaPrecioManual(utilizaListaPrecioManual),
      m_utilizaFormasDePago(utilizaFormasDePago),
      m_noAfectaIva(noAfectaIva),
      m_utilizaSeteoDePreciosEnListasDePrecioPorArticulo(utilizaSeteoDePreciosEnListasDePrecioPorArticulo),
      m_noPermiteFacturarConStockPrevistoCero(noPermiteFacturarConStockPrevistoCero),
      m_imprimeEnFormatoTicket(imprimeEnFormatoTicket),
      m_imprimeObservacionesEnTicket(imprimeObservacionesEnTicket),
      m_utilizaComentarios(utilizaComentarios),
      m_cantidadMaximaLineasEnDocumento(cantidadMaximaLineasEnDocumento)




{
}

int TipoDocumentos::codigoTipoDocumento() const{ return m_codigoTipoDocumento;}
QString TipoDocumentos::descripcionTipoDocumento() const{ return m_descripcionTipoDocumento;}
QString TipoDocumentos::utilizaArticulos() const{ return m_utilizaArticulos;}
QString TipoDocumentos::utilizaCodigoBarrasADemanda() const{ return m_utilizaCodigoBarrasADemanda;}
QString TipoDocumentos::utilizaTotales() const{ return m_utilizaTotales;}
QString TipoDocumentos::utilizaListaPrecio() const{ return m_utilizaListaPrecio;}
QString TipoDocumentos::utilizaMediosDePago() const{ return m_utilizaMediosDePago;}
QString TipoDocumentos::utilizaFechaPrecio() const{ return m_utilizaFechaPrecio;}
QString TipoDocumentos::utilizaFechaDocumento() const{ return m_utilizaFechaDocumento;}
QString TipoDocumentos::utilizaNumeroDocumento() const{ return m_utilizaNumeroDocumento;}
QString TipoDocumentos::utilizaSerieDocumento() const{ return m_utilizaSerieDocumento;}
QString TipoDocumentos::serieDocumento() const{ return m_serieDocumento;}
QString TipoDocumentos::utilizaVendedor() const{ return m_utilizaVendedor;}
QString TipoDocumentos::utilizaCliente() const{ return m_utilizaCliente;}
QString TipoDocumentos::utilizaTipoCliente() const{ return m_utilizaTipoCliente;}
QString TipoDocumentos::utilizaSoloProveedores() const{ return m_utilizaSoloProveedores;}
QString TipoDocumentos::afectaCuentaCorriente() const{ return m_afectaCuentaCorriente;}
QString TipoDocumentos::afectaCuentaCorrienteMercaderia() const{ return m_afectaCuentaCorrienteMercaderia;}
QString TipoDocumentos::afectaStock() const{ return m_afectaStock;}
QString TipoDocumentos::afectaTotales() const{ return m_afectaTotales;}
QString TipoDocumentos::utilizaCantidades() const{ return m_utilizaCantidades;}
QString TipoDocumentos::utilizaPrecioManual() const{ return m_utilizaPrecioManual;}
QString TipoDocumentos::utilizaDescuentoArticulo() const{ return m_utilizaDescuentoArticulo;}
QString TipoDocumentos::utilizaDescuentoTotal() const{ return m_utilizaDescuentoTotal;}
QString TipoDocumentos::emiteEnImpresora() const{ return m_emiteEnImpresora;}
QString TipoDocumentos::codigoModeloImpresion() const{ return m_codigoModeloImpresion;}
QString TipoDocumentos::cantidadCopias() const{ return m_cantidadCopias;}
QString TipoDocumentos::utilizaObservaciones() const{ return m_utilizaObservaciones;}
QString TipoDocumentos::afectaCuentaBancaria() const{ return m_afectaCuentaBancaria;}
QString TipoDocumentos::utilizaCuentaBancaria() const{ return m_utilizaCuentaBancaria;}
QString TipoDocumentos::utilizaPagoChequeDiferido() const{ return m_utilizaPagoChequeDiferido;}
QString TipoDocumentos::utilizaSoloMediosDePagoCheque() const{ return m_utilizaSoloMediosDePagoCheque;}
QString TipoDocumentos::esDocumentoDeVenta() const{ return m_esDocumentoDeVenta;}
QString TipoDocumentos::descripcionTipoDocumentoImpresora() const{ return m_descripcionTipoDocumentoImpresora;}
QString TipoDocumentos::utilizaArticulosInactivos() const{ return m_utilizaArticulosInactivos;}

QString TipoDocumentos::utilizaRedondeoEnTotal() const{ return m_utilizaRedondeoEnTotal;}
QString TipoDocumentos::utilizaPrecioManualEnMonedaReferencia() const{ return m_utilizaPrecioManualEnMonedaReferencia;}
QString TipoDocumentos::descripcionCodigoBarrasADemanda() const{ return m_descripcionCodigoBarrasADemanda;}
QString TipoDocumentos::utilizaListaPrecioManual() const{ return m_utilizaListaPrecioManual;}
QString TipoDocumentos::utilizaFormasDePago() const{ return m_utilizaFormasDePago;}
QString TipoDocumentos::noAfectaIva() const{ return m_noAfectaIva;}
QString TipoDocumentos::utilizaSeteoDePreciosEnListasDePrecioPorArticulo() const{ return m_utilizaSeteoDePreciosEnListasDePrecioPorArticulo;}
QString TipoDocumentos::noPermiteFacturarConStockPrevistoCero() const{ return m_noPermiteFacturarConStockPrevistoCero;}

QString TipoDocumentos::imprimeEnFormatoTicket() const{ return m_imprimeEnFormatoTicket;}
QString TipoDocumentos::imprimeObservacionesEnTicket() const{ return m_imprimeObservacionesEnTicket;}
QString TipoDocumentos::utilizaComentarios() const{ return m_utilizaComentarios;}
QString TipoDocumentos::cantidadMaximaLineasEnDocumento() const{ return m_cantidadMaximaLineasEnDocumento;}



void ModuloListaTipoDocumentos::agregarTipoDocumentos(const TipoDocumentos &monedas)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_TipoDocumentos << monedas;
    endInsertRows();
}

void ModuloListaTipoDocumentos::limpiarListaTipoDocumentos(){
    m_TipoDocumentos.clear();
}


bool ModuloListaTipoDocumentos::retornaTipoDocumentoActivoPorPerfil(QString _codigoTipoDocumento,QString _codigoPerfil){

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

}




void ModuloListaTipoDocumentos::buscarTipoDocumentosDefault(){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select TD.* from TipoDocumento TD join TipoDocumentoPerfilesUsuarios TDP on TDP.codigoTipoDocumento=TD.codigoTipoDocumento where TDP.codigoPerfil=1 and TD.utilizaCliente='1' order by TD.ordenDelMenu,TD.codigoTipoDocumento ");
        QSqlRecord rec = q.record();

        ModuloListaTipoDocumentos::reset();
        if(q.record().count()>0){

            ModuloListaTipoDocumentos::agregarTipoDocumentos(TipoDocumentos(-1,"Sin documento seleccionado","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"));

            while (q.next()){

                ModuloListaTipoDocumentos::agregarTipoDocumentos(TipoDocumentos(
                                                                     q.value(rec.indexOf("codigoTipoDocumento")).toInt(),
                                                                     q.value(rec.indexOf("descripcionTipoDocumento")).toString(),
                                                                     q.value(rec.indexOf("utilizaArticulos")).toString(),
                                                                     q.value(rec.indexOf("utilizaCodigoBarrasADemanda")).toString(),
                                                                     q.value(rec.indexOf("utilizaTotales")).toString(),
                                                                     q.value(rec.indexOf("utilizaListaPrecio")).toString(),
                                                                     q.value(rec.indexOf("utilizaMediosDePago")).toString(),
                                                                     q.value(rec.indexOf("utilizaFechaPrecio")).toString(),
                                                                     q.value(rec.indexOf("utilizaFechaDocumento")).toString(),
                                                                     q.value(rec.indexOf("utilizaNumeroDocumento")).toString(),
                                                                     q.value(rec.indexOf("utilizaSerieDocumento")).toString(),
                                                                     q.value(rec.indexOf("serieDocumento")).toString(),
                                                                     q.value(rec.indexOf("utilizaVendedor")).toString(),
                                                                     q.value(rec.indexOf("utilizaCliente")).toString(),
                                                                     q.value(rec.indexOf("utilizaTipoCliente")).toString(),
                                                                     q.value(rec.indexOf("utilizaSoloProveedores")).toString(),
                                                                     q.value(rec.indexOf("afectaCuentaCorriente")).toString(),
                                                                     q.value(rec.indexOf("afectaCuentaCorrienteMercaderia")).toString(),
                                                                     q.value(rec.indexOf("afectaStock")).toString(),
                                                                     q.value(rec.indexOf("afectaTotales")).toString(),
                                                                     q.value(rec.indexOf("utilizaCantidades")).toString(),
                                                                     q.value(rec.indexOf("utilizaPrecioManual")).toString(),
                                                                     q.value(rec.indexOf("utilizaDescuentoArticulo")).toString(),
                                                                     q.value(rec.indexOf("utilizaDescuentoTotal")).toString(),
                                                                     q.value(rec.indexOf("emiteEnImpresora")).toString(),
                                                                     q.value(rec.indexOf("codigoModeloImpresion")).toString(),
                                                                     q.value(rec.indexOf("cantidadCopias")).toString(),
                                                                     q.value(rec.indexOf("utilizaObservaciones")).toString(),
                                                                     q.value(rec.indexOf("afectaCuentaBancaria")).toString(),
                                                                     q.value(rec.indexOf("utilizaCuentaBancaria")).toString(),
                                                                     q.value(rec.indexOf("utilizaPagoChequeDiferido")).toString(),
                                                                     q.value(rec.indexOf("utilizaSoloMediosDePagoCheque")).toString(),
                                                                     q.value(rec.indexOf("esDocumentoDeVenta")).toString(),
                                                                     q.value(rec.indexOf("descripcionTipoDocumentoImpresora")).toString(),
                                                                     q.value(rec.indexOf("utilizaArticulosInactivos")).toString(),
                                                                     q.value(rec.indexOf("utilizaRedondeoEnTotal")).toString(),
                                                                     q.value(rec.indexOf("utilizaPrecioManualEnMonedaReferencia")).toString(),
                                                                     q.value(rec.indexOf("descripcionCodigoBarrasADemanda")).toString(),
                                                                     q.value(rec.indexOf("utilizaListaPrecioManual")).toString(),
                                                                     q.value(rec.indexOf("utilizaFormasDePago")).toString(),
                                                                     q.value(rec.indexOf("noAfectaIva")).toString(),
                                                                     q.value(rec.indexOf("utilizaSeteoDePreciosEnListasDePrecioPorArticulo")).toString(),
                                                                     q.value(rec.indexOf("noPermiteFacturarConStockPrevistoCero")).toString(),
                                                                     q.value(rec.indexOf("imprimeEnFormatoTicket")).toString(),
                                                                     q.value(rec.indexOf("imprimeObservacionesEnTicket")).toString(),
                                                                     q.value(rec.indexOf("utilizaComentarios")).toString(),
                                                                     q.value(rec.indexOf("cantidadMaximaLineasEnDocumento")).toString()


                                                                     ));
            }
        }
    }
}



void ModuloListaTipoDocumentos::buscarTipoDocumentos(QString campo, QString datoABuscar, QString _codigoPerfil){




    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select TD.* from TipoDocumento TD join TipoDocumentoPerfilesUsuarios TDP on TDP.codigoTipoDocumento=TD.codigoTipoDocumento where "+campo+"'"+datoABuscar+"' and TDP.codigoPerfil='"+_codigoPerfil+"' order by TD.ordenDelMenu,TD.codigoTipoDocumento ");
        QSqlRecord rec = q.record();

        ModuloListaTipoDocumentos::reset();
        if(q.record().count()>0){

            while (q.next()){

                ModuloListaTipoDocumentos::agregarTipoDocumentos(TipoDocumentos(
                                                                     q.value(rec.indexOf("codigoTipoDocumento")).toInt(),
                                                                     q.value(rec.indexOf("descripcionTipoDocumento")).toString(),
                                                                     q.value(rec.indexOf("utilizaArticulos")).toString(),
                                                                     q.value(rec.indexOf("utilizaCodigoBarrasADemanda")).toString(),
                                                                     q.value(rec.indexOf("utilizaTotales")).toString(),
                                                                     q.value(rec.indexOf("utilizaListaPrecio")).toString(),
                                                                     q.value(rec.indexOf("utilizaMediosDePago")).toString(),
                                                                     q.value(rec.indexOf("utilizaFechaPrecio")).toString(),
                                                                     q.value(rec.indexOf("utilizaFechaDocumento")).toString(),
                                                                     q.value(rec.indexOf("utilizaNumeroDocumento")).toString(),
                                                                     q.value(rec.indexOf("utilizaSerieDocumento")).toString(),
                                                                     q.value(rec.indexOf("serieDocumento")).toString(),
                                                                     q.value(rec.indexOf("utilizaVendedor")).toString(),
                                                                     q.value(rec.indexOf("utilizaCliente")).toString(),
                                                                     q.value(rec.indexOf("utilizaTipoCliente")).toString(),
                                                                     q.value(rec.indexOf("utilizaSoloProveedores")).toString(),
                                                                     q.value(rec.indexOf("afectaCuentaCorriente")).toString(),
                                                                     q.value(rec.indexOf("afectaCuentaCorrienteMercaderia")).toString(),
                                                                     q.value(rec.indexOf("afectaStock")).toString(),
                                                                     q.value(rec.indexOf("afectaTotales")).toString(),
                                                                     q.value(rec.indexOf("utilizaCantidades")).toString(),
                                                                     q.value(rec.indexOf("utilizaPrecioManual")).toString(),
                                                                     q.value(rec.indexOf("utilizaDescuentoArticulo")).toString(),
                                                                     q.value(rec.indexOf("utilizaDescuentoTotal")).toString(),
                                                                     q.value(rec.indexOf("emiteEnImpresora")).toString(),
                                                                     q.value(rec.indexOf("codigoModeloImpresion")).toString(),
                                                                     q.value(rec.indexOf("cantidadCopias")).toString(),
                                                                     q.value(rec.indexOf("utilizaObservaciones")).toString(),
                                                                     q.value(rec.indexOf("afectaCuentaBancaria")).toString(),
                                                                     q.value(rec.indexOf("utilizaCuentaBancaria")).toString(),
                                                                     q.value(rec.indexOf("utilizaPagoChequeDiferido")).toString(),
                                                                     q.value(rec.indexOf("utilizaSoloMediosDePagoCheque")).toString(),
                                                                     q.value(rec.indexOf("esDocumentoDeVenta")).toString(),
                                                                     q.value(rec.indexOf("descripcionTipoDocumentoImpresora")).toString(),
                                                                     q.value(rec.indexOf("utilizaArticulosInactivos")).toString(),

                                                                     q.value(rec.indexOf("utilizaRedondeoEnTotal")).toString(),
                                                                     q.value(rec.indexOf("utilizaPrecioManualEnMonedaReferencia")).toString(),
                                                                     q.value(rec.indexOf("descripcionCodigoBarrasADemanda")).toString(),
                                                                     q.value(rec.indexOf("utilizaListaPrecioManual")).toString(),
                                                                     q.value(rec.indexOf("utilizaFormasDePago")).toString(),
                                                                     q.value(rec.indexOf("noAfectaIva")).toString(),
                                                                     q.value(rec.indexOf("utilizaSeteoDePreciosEnListasDePrecioPorArticulo")).toString(),
                                                                     q.value(rec.indexOf("noPermiteFacturarConStockPrevistoCero")).toString(),
                                                                     q.value(rec.indexOf("imprimeEnFormatoTicket")).toString(),
                                                                     q.value(rec.indexOf("imprimeObservacionesEnTicket")).toString(),
                                                                     q.value(rec.indexOf("utilizaComentarios")).toString(),
                                                                     q.value(rec.indexOf("cantidadMaximaLineasEnDocumento")).toString()








                                                                     ));
            }
        }
    }
}




void ModuloListaTipoDocumentos::buscarTodosLosTipoDocumentos(QString campo, QString datoABuscar){
    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from TipoDocumento   where "+campo+"'"+datoABuscar+"' order by ordenDelMenu,codigoTipoDocumento ");
        QSqlRecord rec = q.record();

        ModuloListaTipoDocumentos::reset();
        if(q.record().count()>0){

            while (q.next()){

                ModuloListaTipoDocumentos::agregarTipoDocumentos(TipoDocumentos( q.value(rec.indexOf("codigoTipoDocumento")).toInt(),
                                                                                 q.value(rec.indexOf("descripcionTipoDocumento")).toString(),
                                                                                 q.value(rec.indexOf("utilizaArticulos")).toString(),
                                                                                 q.value(rec.indexOf("utilizaCodigoBarrasADemanda")).toString(),
                                                                                 q.value(rec.indexOf("utilizaTotales")).toString(),
                                                                                 q.value(rec.indexOf("utilizaListaPrecio")).toString(),
                                                                                 q.value(rec.indexOf("utilizaMediosDePago")).toString(),
                                                                                 q.value(rec.indexOf("utilizaFechaPrecio")).toString(),
                                                                                 q.value(rec.indexOf("utilizaFechaDocumento")).toString(),
                                                                                 q.value(rec.indexOf("utilizaNumeroDocumento")).toString(),
                                                                                 q.value(rec.indexOf("utilizaSerieDocumento")).toString(),
                                                                                 q.value(rec.indexOf("serieDocumento")).toString(),
                                                                                 q.value(rec.indexOf("utilizaVendedor")).toString(),
                                                                                 q.value(rec.indexOf("utilizaCliente")).toString(),
                                                                                 q.value(rec.indexOf("utilizaTipoCliente")).toString(),
                                                                                 q.value(rec.indexOf("utilizaSoloProveedores")).toString(),
                                                                                 q.value(rec.indexOf("afectaCuentaCorriente")).toString(),
                                                                                 q.value(rec.indexOf("afectaCuentaCorrienteMercaderia")).toString(),
                                                                                 q.value(rec.indexOf("afectaStock")).toString(),
                                                                                 q.value(rec.indexOf("afectaTotales")).toString(),
                                                                                 q.value(rec.indexOf("utilizaCantidades")).toString(),
                                                                                 q.value(rec.indexOf("utilizaPrecioManual")).toString(),
                                                                                 q.value(rec.indexOf("utilizaDescuentoArticulo")).toString(),
                                                                                 q.value(rec.indexOf("utilizaDescuentoTotal")).toString(),
                                                                                 q.value(rec.indexOf("emiteEnImpresora")).toString(),
                                                                                 q.value(rec.indexOf("codigoModeloImpresion")).toString(),
                                                                                 q.value(rec.indexOf("cantidadCopias")).toString(),
                                                                                 q.value(rec.indexOf("utilizaObservaciones")).toString(),
                                                                                 q.value(rec.indexOf("afectaCuentaBancaria")).toString(),
                                                                                 q.value(rec.indexOf("utilizaCuentaBancaria")).toString(),
                                                                                 q.value(rec.indexOf("utilizaPagoChequeDiferido")).toString(),
                                                                                 q.value(rec.indexOf("utilizaSoloMediosDePagoCheque")).toString(),
                                                                                 q.value(rec.indexOf("esDocumentoDeVenta")).toString(),
                                                                                 q.value(rec.indexOf("descripcionTipoDocumentoImpresora")).toString(),
                                                                                 q.value(rec.indexOf("utilizaArticulosInactivos")).toString(),

                                                                                 q.value(rec.indexOf("utilizaRedondeoEnTotal")).toString(),
                                                                                 q.value(rec.indexOf("utilizaPrecioManualEnMonedaReferencia")).toString(),
                                                                                 q.value(rec.indexOf("descripcionCodigoBarrasADemanda")).toString(),
                                                                                 q.value(rec.indexOf("utilizaListaPrecioManual")).toString(),
                                                                                 q.value(rec.indexOf("utilizaFormasDePago")).toString(),
                                                                                 q.value(rec.indexOf("noAfectaIva")).toString(),
                                                                                 q.value(rec.indexOf("utilizaSeteoDePreciosEnListasDePrecioPorArticulo")).toString(),
                                                                                 q.value(rec.indexOf("noPermiteFacturarConStockPrevistoCero")).toString(),
                                                                                 q.value(rec.indexOf("imprimeEnFormatoTicket")).toString(),
                                                                                 q.value(rec.indexOf("imprimeObservacionesEnTicket")).toString(),
                                                                                 q.value(rec.indexOf("utilizaComentarios")).toString(),
                                                                                 q.value(rec.indexOf("cantidadMaximaLineasEnDocumento")).toString()



                                                                                 ));
            }
        }
    }
}





QString ModuloListaTipoDocumentos::retornaDescripcionTipoDocumento(QString _codigoTipoDocumento) const {

    QString _descripcionTipoDocumento="";
    for (int var = 0; var < m_TipoDocumentos.size(); ++var) {
        if(QString::number(m_TipoDocumentos[var].codigoTipoDocumento())==_codigoTipoDocumento){
            _descripcionTipoDocumento = m_TipoDocumentos[var].descripcionTipoDocumento();
        }
    }
    return _descripcionTipoDocumento;


    /*  bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect());

        if(query.exec("select descripcionTipoDocumento from TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"' ")) {

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
    }else{return "";}*/
}

QString ModuloListaTipoDocumentos::retornaSerieTipoDocumento(QString _codigoTipoDocumento) const {

    QString _valorARetornar="A";
    for (int var = 0; var < m_TipoDocumentos.size(); ++var) {
        if(QString::number(m_TipoDocumentos[var].codigoTipoDocumento())==_codigoTipoDocumento){
            _valorARetornar = m_TipoDocumentos[var].serieDocumento();
        }
    }
    return _valorARetornar;

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

        if(query.exec("select serieDocumento from TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toString();

                }else{
                    return "A";
                }
            }else{return "A";}
        }else{
            return "A";
        }
    }else{return "A";}*/
}
QString ModuloListaTipoDocumentos::retornaDescripcionCodigoADemanda(QString _codigoTipoDocumento) const {

    QString _valorARetornar="A";
    for (int var = 0; var < m_TipoDocumentos.size(); ++var) {
        if(QString::number(m_TipoDocumentos[var].codigoTipoDocumento())==_codigoTipoDocumento){
            _valorARetornar = m_TipoDocumentos[var].descripcionCodigoBarrasADemanda();
        }
    }
    return _valorARetornar;

    /* bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect());

        if(query.exec("select descripcionCodigoBarrasADemanda from TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"'")) {

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
    }else{return "";}*/
}


bool ModuloListaTipoDocumentos::retornaPermisosDelDocumento(QString _codigoTipoDocumento,QString _permisoDocumento) const {

    bool _valorARetornar=false;
    for (int var = 0; var < m_TipoDocumentos.size(); ++var) {
        if(QString::number(m_TipoDocumentos[var].codigoTipoDocumento())==_codigoTipoDocumento){

            // _valorARetornar= convertirStringABool(m_TipoDocumentos[var].afectaCuentaBancaria());


            if (_permisoDocumento == "utilizaArticulos"){
                _valorARetornar = convertirStringABool(m_TipoDocumentos[var].utilizaArticulos());
            }
            else if (_permisoDocumento == "utilizaCodigoBarrasADemanda"){
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaCodigoBarrasADemanda());
            }
            else if (_permisoDocumento == "utilizaTotales")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaTotales());}
            else if (_permisoDocumento == "utilizaListaPrecio")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaListaPrecio());}
            else if (_permisoDocumento == "utilizaMediosDePago")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaMediosDePago());}
            else if (_permisoDocumento == "utilizaFechaPrecio")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaFechaPrecio());}
            else if (_permisoDocumento == "utilizaFechaDocumento")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaFechaDocumento());}
            else if (_permisoDocumento == "utilizaNumeroDocumento")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaNumeroDocumento());}
            else if (_permisoDocumento == "utilizaSerieDocumento")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaSerieDocumento());}
            else if (_permisoDocumento == "utilizaVendedor")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaVendedor());}
            else if (_permisoDocumento == "utilizaCliente")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaCliente());}
            else if (_permisoDocumento == "utilizaTipoCliente")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaTipoCliente());}
            else if (_permisoDocumento == "utilizaSoloProveedores")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaSoloProveedores());}
            else if (_permisoDocumento == "afectaCuentaCorriente")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].afectaCuentaCorriente());}
            else if (_permisoDocumento == "afectaCuentaCorrienteMercaderia")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].afectaCuentaCorrienteMercaderia());
            }


            else if (_permisoDocumento == "afectaStock")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].afectaStock());}
            else if (_permisoDocumento == "afectaTotales")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].afectaTotales());}
            else if (_permisoDocumento == "utilizaCantidades")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaCantidades());}
            else if (_permisoDocumento == "utilizaPrecioManual")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaPrecioManual());}
            else if (_permisoDocumento == "utilizaDescuentoArticulo")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaDescuentoArticulo());}
            else if (_permisoDocumento == "utilizaDescuentoTotal")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaDescuentoTotal());}
            else if (_permisoDocumento == "emiteEnImpresora")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].emiteEnImpresora());}
            else if (_permisoDocumento == "codigoModeloImpresion")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].codigoModeloImpresion());}
            else if (_permisoDocumento == "cantidadCopias")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].cantidadCopias());}
            else if (_permisoDocumento == "utilizaObservaciones")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaObservaciones());}
            else if (_permisoDocumento == "afectaCuentaBancaria")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].afectaCuentaBancaria());}
            else if (_permisoDocumento == "utilizaCuentaBancaria")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaCuentaBancaria());}
            else if (_permisoDocumento == "utilizaPagoChequeDiferido")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaPagoChequeDiferido());}


            else if (_permisoDocumento == "utilizaSoloMediosDePagoCheque")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaSoloMediosDePagoCheque());}
            else if (_permisoDocumento == "esDocumentoDeVenta")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].esDocumentoDeVenta());}
            else if (_permisoDocumento == "descripcionTipoDocumentoImpresora")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].descripcionTipoDocumentoImpresora());}
            else if (_permisoDocumento == "utilizaArticulosInactivos")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaArticulosInactivos());}
            else if (_permisoDocumento == "utilizaRedondeoEnTotal")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaRedondeoEnTotal());}
            else if (_permisoDocumento == "utilizaPrecioManualEnMonedaReferencia")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaPrecioManualEnMonedaReferencia());}
            else if (_permisoDocumento == "descripcionCodigoBarrasADemanda")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].descripcionCodigoBarrasADemanda());}



            else if (_permisoDocumento == "utilizaListaPrecioManual")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaListaPrecioManual());}
            else if (_permisoDocumento == "utilizaFormasDePago")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaFormasDePago());}
            else if (_permisoDocumento == "noAfectaIva")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].noAfectaIva());}
            else if (_permisoDocumento == "utilizaSeteoDePreciosEnListasDePrecioPorArticulo")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaSeteoDePreciosEnListasDePrecioPorArticulo());}
            else if (_permisoDocumento == "noPermiteFacturarConStockPrevistoCero")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].noPermiteFacturarConStockPrevistoCero());}
            else if (_permisoDocumento == "imprimeEnFormatoTicket")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].imprimeEnFormatoTicket());}
            else if (_permisoDocumento == "imprimeObservacionesEnTicket")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].imprimeObservacionesEnTicket());}
            else if (_permisoDocumento == "utilizaComentarios")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaComentarios());}


        }
    }
    return _valorARetornar;

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

        if(query.exec("select  "+_permisoDocumento+"  from TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"'")) {


            if(query.first()){
                if(query.value(0).toString()!=""){


                    if(query.value(0).toString()=="1"){
                        return true;
                    }else{
                        return  false;
                    }
                }else{
                    return false;
                }
            }else{return false;}


        }else{
            return false;
        }
    }else{return false;}*/
}


bool ModuloListaTipoDocumentos::convertirStringABool(QString valor) const{
    if(valor=="1"){
        return true;
    }else{
        return false;
    }
}

bool ModuloListaTipoDocumentos::retornaPermiteModificacionMedioPagoPorDeudaContado(QString _codigoTipoDocumento,QString _codigoDocumento, QString _serieDocumento) const {

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

        if(query.exec("select documentoAceptaIngresoDeMediosDePagoLuegoDeEmitido  from TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    if(query.value(0).toString()=="1"){
                        query.clear();
                        if(query.exec("SELECT ROUND(DOC.precioTotalVenta-(DOC.precioTotalVenta/(SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion='MULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADO' limit 1)),2)'maximoPorcentajeAdmitidoDeDeuda', DOC.precioTotalVenta-DOC.saldoClientePagoContado'saldoPorPagarCliente' FROM Documentos DOC join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento where TD.documentoAceptaIngresoDeMediosDePagoLuegoDeEmitido='1' and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.codigoDocumento='"+_codigoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"' and DOC.codigoEstadoDocumento in ('E','G') limit 1;")){
                            if(query.first()){
                                if(query.value(0).toString()!=""){

                                    qDebug()<<query.value(0).toDouble();
                                    qDebug()<<query.value(1).toDouble();

                                    if(query.value(0).toDouble()<=query.value(1).toDouble()){
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
                    }else{
                        return  false;
                    }
                }else{
                    return false;
                }
            }else{return false;}
        }else{
            return false;
        }
    }else{return false;}
}


bool ModuloListaTipoDocumentos::retornaDocumentoSegunMonedaRedondea(QString _codigoTipoDocumento,QString _codigoMoneda) const {

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

        if(query.exec("select codigoTipoDocumento  from TipoDocumentoMonedasRedondeo where codigoTipoDocumento='"+_codigoTipoDocumento+"' and codigoMoneda='"+_codigoMoneda+"' limit 1; ")) {
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
}



int ModuloListaTipoDocumentos::rowCount(const QModelIndex & parent) const {
    return m_TipoDocumentos.count();
}

QVariant ModuloListaTipoDocumentos::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_TipoDocumentos.count()){
        return QVariant();

    }
    const TipoDocumentos &tipoDocumentos = m_TipoDocumentos[index.row()];

    if (role == codigoTipoDocumentoRole){ return tipoDocumentos.codigoTipoDocumento();}
    else if (role == descripcionTipoDocumentoRole){  return tipoDocumentos.descripcionTipoDocumento();}
    else if (role == utilizaArticulosRole){  return tipoDocumentos.utilizaArticulos();}
    else if (role == utilizaCodigoBarrasADemandaRole){  return tipoDocumentos.utilizaCodigoBarrasADemanda();}
    else if (role == utilizaTotalesRole){  return tipoDocumentos.utilizaTotales();}
    else if (role == utilizaListaPrecioRole){  return tipoDocumentos.utilizaListaPrecio();}
    else if (role == utilizaMediosDePagoRole){  return tipoDocumentos.utilizaMediosDePago();}
    else if (role == utilizaFechaPrecioRole){  return tipoDocumentos.utilizaFechaPrecio();}
    else if (role == utilizaFechaDocumentoRole){  return tipoDocumentos.utilizaFechaDocumento();}
    else if (role == utilizaNumeroDocumentoRole){  return tipoDocumentos.utilizaNumeroDocumento();}
    else if (role == utilizaSerieDocumentoRole){  return tipoDocumentos.utilizaSerieDocumento();}
    else if (role == serieDocumentoRole){  return tipoDocumentos.serieDocumento();}
    else if (role == utilizaVendedorRole){  return tipoDocumentos.utilizaVendedor();}
    else if (role == utilizaClienteRole){  return tipoDocumentos.utilizaCliente();}
    else if (role == utilizaTipoClienteRole){  return tipoDocumentos.utilizaTipoCliente();}
    else if (role == utilizaSoloProveedoresRole){  return tipoDocumentos.utilizaSoloProveedores();}
    else if (role == afectaCuentaCorrienteRole){  return tipoDocumentos.afectaCuentaCorriente();}
    else if (role == afectaCuentaCorrienteMercaderiaRole){  return tipoDocumentos.afectaCuentaCorrienteMercaderia();}
    else if (role == afectaStockRole){  return tipoDocumentos.afectaStock();}
    else if (role == afectaTotalesRole){  return tipoDocumentos.afectaTotales();}
    else if (role == utilizaCantidadesRole){  return tipoDocumentos.utilizaCantidades();}
    else if (role == utilizaPrecioManualRole){  return tipoDocumentos.utilizaPrecioManual();}
    else if (role == utilizaDescuentoArticuloRole){  return tipoDocumentos.utilizaDescuentoArticulo();}
    else if (role == utilizaDescuentoTotalRole){  return tipoDocumentos.utilizaDescuentoTotal();}
    else if (role == emiteEnImpresoraRole){  return tipoDocumentos.emiteEnImpresora();}
    else if (role == codigoModeloImpresionRole){  return tipoDocumentos.codigoModeloImpresion();}
    else if (role == cantidadCopiasRole){  return tipoDocumentos.cantidadCopias();}
    else if (role == utilizaObservacionesRole){  return tipoDocumentos.utilizaObservaciones();}
    else if (role == afectaCuentaBancariaRole){  return tipoDocumentos.afectaCuentaBancaria();}
    else if (role == utilizaCuentaBancariaRole){  return tipoDocumentos.utilizaCuentaBancaria();}
    else if (role == utilizaPagoChequeDiferidoRole){  return tipoDocumentos.utilizaPagoChequeDiferido();}
    else if (role == utilizaSoloMediosDePagoChequeRole){  return tipoDocumentos.utilizaSoloMediosDePagoCheque();}
    else if (role == esDocumentoDeVentaRole){  return tipoDocumentos.esDocumentoDeVenta();}
    else if (role == descripcionTipoDocumentoImpresoraRole){  return tipoDocumentos.descripcionTipoDocumentoImpresora();}
    else if (role == utilizaArticulosInactivosRole){  return tipoDocumentos.utilizaArticulosInactivos();}

    else if (role == utilizaRedondeoEnTotalRole){  return tipoDocumentos.utilizaRedondeoEnTotal();}
    else if (role == utilizaPrecioManualEnMonedaReferenciaRole){  return tipoDocumentos.utilizaPrecioManualEnMonedaReferencia();}
    else if (role == descripcionCodigoBarrasADemandaRole){  return tipoDocumentos.descripcionCodigoBarrasADemanda();}
    else if (role == utilizaListaPrecioManualRole){  return tipoDocumentos.utilizaListaPrecioManual();}
    else if (role == utilizaFormasDePagoRole){  return tipoDocumentos.utilizaFormasDePago();}
    else if (role == noAfectaIvaRole){  return tipoDocumentos.noAfectaIva();}
    else if (role == utilizaSeteoDePreciosEnListasDePrecioPorArticuloRole){  return tipoDocumentos.utilizaSeteoDePreciosEnListasDePrecioPorArticulo();}
    else if (role == noPermiteFacturarConStockPrevistoCeroRole){  return tipoDocumentos.noPermiteFacturarConStockPrevistoCero();}

    else if (role == imprimeEnFormatoTicketRole){  return tipoDocumentos.imprimeEnFormatoTicket();}

    else if (role == imprimeObservacionesEnTicketRole){  return tipoDocumentos.imprimeObservacionesEnTicket();}
    else if (role == utilizaComentariosRole){  return tipoDocumentos.utilizaComentarios();}
    else if (role == cantidadMaximaLineasEnDocumentoRole){  return tipoDocumentos.cantidadMaximaLineasEnDocumento();}


    return QVariant();
}

int ModuloListaTipoDocumentos::ultimoRegistroDeTipoDeDocumento()const {
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

        if(query.exec("select codigoTipoDocumento from TipoDocumento order by codigoTipoDocumento desc limit 1")) {

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





bool ModuloListaTipoDocumentos::eliminarTipoDocumento(QString _codigoTipoDocumento) const {

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
        if(query.exec("select codigoTipoDocumento from TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"' ")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    if(query.exec("delete from TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"' ")){
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



int ModuloListaTipoDocumentos::cantidadMaximaLineasTipoDocumento(QString _codigoTipoDocumento)const {

    int _valorARetornar=0;
    for (int var = 0; var < m_TipoDocumentos.size(); ++var) {
        if(QString::number(m_TipoDocumentos[var].codigoTipoDocumento())==_codigoTipoDocumento){
            _valorARetornar = m_TipoDocumentos[var].cantidadMaximaLineasEnDocumento().toInt();
        }
    }
    return _valorARetornar;

    /*
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

        if(query.exec("select cantidadMaximaLineasEnDocumento  from TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"' ")){

            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toInt();

                }else{
                    return 0;
                }
            }else {
                return 0;
            }
        }else{
            return 0;
        }
    }*/
}


int ModuloListaTipoDocumentos::insertarTipoDocumento(
        QString _codigoTipoDocumento,
        QString _descripcionTipoDocumento,
        QString _utilizaArticulos,
        QString _utilizaCodigoBarrasADemanda,
        QString _utilizaTotales,
        QString _utilizaMediosDePago,
        QString _utilizaFechaPrecio,
        QString _utilizaFechaDocumento,
        QString _utilizaNumeroDocumento,
        QString _utilizaSerieDocumento,
        QString _serieDocumento,
        QString _utilizaVendedor,
        QString _utilizaCliente,
        QString _utilizaTipoCliente,
        QString _utilizaSoloProveedores,
        QString _afectaCuentaCorriente,
        QString _afectaCuentaCorrienteMercaderia,
        QString _afectaStock,
        QString _afectaTotales,
        QString _utilizaCantidades,
        QString _utilizaPrecioManual,
        QString _utilizaDescuentoTotal,
        QString _emiteEnImpresora,
        QString _codigoModeloImpresion,
        QString _cantidadCopias,
        QString _utilizaObservaciones,
        QString _utilizaComentarios,
        QString _afectaCuentaBancaria,
        QString _utilizaCuentaBancaria,
        QString _utilizaPagoChequeDiferido,
        QString _utilizaSoloMediosDePagoCheque,
        QString _esDocumentoDeVenta,
        QString _descripcionTipoDocumentoImpresora,
        QString _utilizaArticulosInactivos,

        QString _utilizaRedondeoEnTotal,
        QString _utilizaPrecioManualEnMonedaReferencia,
        QString _descripcionCodigoBarrasADemanda,
        QString _utilizaListaPrecioManual,
        QString _utilizaFormasDePago,
        QString _noAfectaIva,
        QString _utilizaSeteoDePreciosEnListasDePrecioPorArticulo,

        QString _noPermiteFacturarConStockPrevistoCero,
        QString _imprimeEnFormatoTicket,
        QString _imprimeObservacionesEnTicket


        ){


    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el tipo documento
    // 1  tipo documento dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar el tipo documento
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El tipo documento no tiene los datos sufucientes para darse de alta.

    if(_codigoTipoDocumento.trimmed()=="" || _descripcionTipoDocumento.trimmed()=="" ){
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

        if(query.exec("select codigoTipoDocumento from TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"'")) {

            if(query.first()){

                if(query.value(0).toString()!=""){

                    if(query.exec("update TipoDocumento set  descripcionTipoDocumento='"+_descripcionTipoDocumento+"',utilizaArticulos='"+_utilizaArticulos+"',utilizaCodigoBarrasADemanda='"+_utilizaCodigoBarrasADemanda+"',utilizaTotales='"+_utilizaTotales+"',utilizaMediosDePago='"+_utilizaMediosDePago+"',utilizaFechaPrecio='"+_utilizaFechaPrecio+"',utilizaFechaDocumento='"+_utilizaFechaDocumento+"',utilizaNumeroDocumento='"+_utilizaNumeroDocumento+"',utilizaSerieDocumento='"+_utilizaSerieDocumento+"',serieDocumento='"+_serieDocumento+"',utilizaVendedor='"+_utilizaVendedor+"',utilizaCliente='"+_utilizaCliente+"',utilizaTipoCliente='"+_utilizaTipoCliente+"',utilizaSoloProveedores='"+_utilizaSoloProveedores+"',afectaCuentaCorriente='"+_afectaCuentaCorriente+"',afectaCuentaCorrienteMercaderia='"+_afectaCuentaCorrienteMercaderia+"',afectaStock='"+_afectaStock+"',afectaTotales='"+_afectaTotales+"',utilizaCantidades='"+_utilizaCantidades+"',utilizaPrecioManual='"+_utilizaPrecioManual+"',utilizaDescuentoTotal='"+_utilizaDescuentoTotal+"',emiteEnImpresora='"+_emiteEnImpresora+"',codigoModeloImpresion='"+_codigoModeloImpresion+"',cantidadCopias='"+_cantidadCopias+"',utilizaObservaciones='"+_utilizaObservaciones+"',utilizaComentarios='"+_utilizaComentarios+"',afectaCuentaBancaria='"+_afectaCuentaBancaria+"',utilizaCuentaBancaria='"+_utilizaCuentaBancaria+"',utilizaPagoChequeDiferido='"+_utilizaPagoChequeDiferido+"',utilizaSoloMediosDePagoCheque='"+_utilizaSoloMediosDePagoCheque+"',esDocumentoDeVenta='"+_esDocumentoDeVenta+"',descripcionTipoDocumentoImpresora='"+_descripcionTipoDocumentoImpresora+"',utilizaArticulosInactivos='"+_utilizaArticulosInactivos+"' ,utilizaRedondeoEnTotal='"+_utilizaRedondeoEnTotal+"'  ,utilizaPrecioManualEnMonedaReferencia='"+_utilizaPrecioManualEnMonedaReferencia+"'   ,descripcionCodigoBarrasADemanda='"+_descripcionCodigoBarrasADemanda+"'  ,utilizaListaPrecioManual='"+_utilizaListaPrecioManual+"',utilizaFormasDePago='"+_utilizaFormasDePago+"',noAfectaIva='"+_noAfectaIva+"',utilizaSeteoDePreciosEnListasDePrecioPorArticulo='"+_utilizaSeteoDePreciosEnListasDePrecioPorArticulo+"' ,noPermiteFacturarConStockPrevistoCero='"+_noPermiteFacturarConStockPrevistoCero+"' ,imprimeEnFormatoTicket='"+_imprimeEnFormatoTicket+"',imprimeObservacionesEnTicket='"+_imprimeObservacionesEnTicket+"'               where codigoTipoDocumento='"+_codigoTipoDocumento+"'    ")){

                        return 2;

                    }else{
                        return -2;
                    }
                }else{
                    return -4;
                }
            }else{
                if(query.exec("insert INTO TipoDocumento (codigoTipoDocumento,descripcionTipoDocumento,utilizaArticulos,utilizaCodigoBarrasADemanda,utilizaTotales,utilizaMediosDePago,utilizaFechaPrecio,utilizaFechaDocumento,utilizaNumeroDocumento,utilizaSerieDocumento,serieDocumento,utilizaVendedor,utilizaCliente,utilizaTipoCliente,utilizaSoloProveedores,afectaCuentaCorriente,afectaCuentaCorrienteMercaderia,afectaStock,afectaTotales,utilizaCantidades,utilizaPrecioManual,utilizaDescuentoTotal,emiteEnImpresora,codigoModeloImpresion,cantidadCopias,utilizaObservaciones,utilizaComentarios,afectaCuentaBancaria,utilizaCuentaBancaria,utilizaPagoChequeDiferido,utilizaSoloMediosDePagoCheque,esDocumentoDeVenta,descripcionTipoDocumentoImpresora,utilizaArticulosInactivos,utilizaRedondeoEnTotal,utilizaPrecioManualEnMonedaReferencia,descripcionCodigoBarrasADemanda,utilizaListaPrecioManual,utilizaFormasDePago,noAfectaIva,utilizaSeteoDePreciosEnListasDePrecioPorArticulo,noPermiteFacturarConStockPrevistoCero,imprimeEnFormatoTicket,imprimeObservacionesEnTicket) values('"+_codigoTipoDocumento+"','"+_descripcionTipoDocumento+"','"+_utilizaArticulos+"','"+_utilizaCodigoBarrasADemanda+"','"+_utilizaTotales+"','"+_utilizaMediosDePago+"','"+_utilizaFechaPrecio+"','"+_utilizaFechaDocumento+"','"+_utilizaNumeroDocumento+"','"+_utilizaSerieDocumento+"','"+_serieDocumento+"','"+_utilizaVendedor+"','"+_utilizaCliente+"','"+_utilizaTipoCliente+"','"+_utilizaSoloProveedores+"','"+_afectaCuentaCorriente+"','"+_afectaCuentaCorrienteMercaderia+"','"+_afectaStock+"','"+_afectaTotales+"','"+_utilizaCantidades+"','"+_utilizaPrecioManual+"','"+_utilizaDescuentoTotal+"','"+_emiteEnImpresora+"','"+_codigoModeloImpresion+"','"+_cantidadCopias+"','"+_utilizaObservaciones+"','"+_utilizaComentarios+"','"+_afectaCuentaBancaria+"','"+_utilizaCuentaBancaria+"','"+_utilizaPagoChequeDiferido+"','"+_utilizaSoloMediosDePagoCheque+"','"+_esDocumentoDeVenta+"','"+_descripcionTipoDocumentoImpresora+"','"+_utilizaArticulosInactivos+"'   ,'"+_utilizaRedondeoEnTotal+"' ,'"+_utilizaPrecioManualEnMonedaReferencia+"','"+_descripcionCodigoBarrasADemanda+"','"+_utilizaListaPrecioManual+"','"+_utilizaFormasDePago+"','"+_noAfectaIva+"','"+_utilizaSeteoDePreciosEnListasDePrecioPorArticulo+"','"+_noPermiteFacturarConStockPrevistoCero+"','"+_imprimeEnFormatoTicket+"','"+_imprimeObservacionesEnTicket+"')")){

                    insertarTipoDocumentoPerfil(_codigoTipoDocumento,"1");

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

void ModuloListaTipoDocumentos::eliminarTipoDocumentoPerfil(QString _codigoTipoDocumento,QString _codigoPerfil) const {

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

        query.exec("delete from TipoDocumentoPerfilesUsuarios where codigoTipoDocumento='"+_codigoTipoDocumento+"' and codigoPerfil='"+_codigoPerfil+"' ");
    }
}
void ModuloListaTipoDocumentos::insertarTipoDocumentoPerfil(QString _codigoTipoDocumento,QString _codigoPerfil) const {



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

        query.exec("REPLACE INTO TipoDocumentoPerfilesUsuarios(codigoTipoDocumento,codigoPerfil) VALUES('"+_codigoTipoDocumento+"','"+_codigoPerfil+"')  ");
    }
}




///Carga los documento para devolver un documento especifico
bool ModuloListaTipoDocumentos::permiteDevolucionTipoDocumento(QString _codigoTipoDocumento){


    QString _utilizaArticulos = retornaValorCampoTipoDocumento(_codigoTipoDocumento,"utilizaArticulos");
    if(_utilizaArticulos==""){
        return false;
    }

    QString _utilizaTotales=retornaValorCampoTipoDocumento(_codigoTipoDocumento,"utilizaTotales");
    if(_utilizaTotales==""){
        return false;
    }

    QString _utilizaCliente=retornaValorCampoTipoDocumento(_codigoTipoDocumento,"utilizaCliente");
    if(_utilizaCliente==""){
        return false;
    }

    QString _afectaCuentaCorriente=retornaValorCampoTipoDocumento(_codigoTipoDocumento,"afectaCuentaCorriente");
    if(_afectaCuentaCorriente==""){
        return false;
    }else if(_afectaCuentaCorriente=="1"){
        _afectaCuentaCorriente="-1";
    }else if(_afectaCuentaCorriente=="-1"){
        _afectaCuentaCorriente="1";
    }

    QString _afectaCuentaCorrienteMercaderia=retornaValorCampoTipoDocumento(_codigoTipoDocumento,"afectaCuentaCorrienteMercaderia");
    if(_afectaCuentaCorrienteMercaderia==""){
        return false;
    }else if(_afectaCuentaCorrienteMercaderia=="1"){
        _afectaCuentaCorrienteMercaderia="-1";
    }else if(_afectaCuentaCorrienteMercaderia=="-1"){
        _afectaCuentaCorrienteMercaderia="1";
    }

    QString _afectaStock=retornaValorCampoTipoDocumento(_codigoTipoDocumento,"afectaStock");
    if(_afectaStock==""){
        return false;
    }else if(_afectaStock=="1"){
        _afectaStock="-1";
    }else if(_afectaStock=="-1"){
        _afectaStock="1";
    }

    QString _afectaTotales=retornaValorCampoTipoDocumento(_codigoTipoDocumento,"afectaTotales");
    if(_afectaTotales==""){
        return false;
    }else if(_afectaTotales=="1"){
        _afectaTotales="-1";
    }else if(_afectaTotales=="-1"){
        _afectaTotales="1";
    }

    QString _esDocumentoDeVenta=retornaValorCampoTipoDocumento(_codigoTipoDocumento,"esDocumentoDeVenta");
    if(_esDocumentoDeVenta==""){
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

        QSqlQuery q = Database::consultaSql("select * from TipoDocumento  where utilizaArticulos='"+_utilizaArticulos+"' and  utilizaTotales='"+_utilizaTotales+"' and utilizaCliente='"+_utilizaCliente+"' and afectaCuentaCorriente='"+_afectaCuentaCorriente+"' and afectaCuentaCorrienteMercaderia='"+_afectaCuentaCorrienteMercaderia+"' and  afectaStock='"+_afectaStock+"' and  afectaTotales='"+_afectaTotales+"' and esDocumentoDeVenta='"+_esDocumentoDeVenta+"' order by ordenDelMenu,codigoTipoDocumento ");
        QSqlRecord rec = q.record();

        ModuloListaTipoDocumentos::reset();

        if(q.record().count()>0){

            while (q.next()){

                ModuloListaTipoDocumentos::agregarTipoDocumentos(TipoDocumentos( q.value(rec.indexOf("codigoTipoDocumento")).toInt(),
                                                                                 q.value(rec.indexOf("descripcionTipoDocumento")).toString(),
                                                                                 q.value(rec.indexOf("utilizaArticulos")).toString(),
                                                                                 q.value(rec.indexOf("utilizaCodigoBarrasADemanda")).toString(),
                                                                                 q.value(rec.indexOf("utilizaTotales")).toString(),
                                                                                 q.value(rec.indexOf("utilizaListaPrecio")).toString(),
                                                                                 q.value(rec.indexOf("utilizaMediosDePago")).toString(),
                                                                                 q.value(rec.indexOf("utilizaFechaPrecio")).toString(),
                                                                                 q.value(rec.indexOf("utilizaFechaDocumento")).toString(),
                                                                                 q.value(rec.indexOf("utilizaNumeroDocumento")).toString(),
                                                                                 q.value(rec.indexOf("utilizaSerieDocumento")).toString(),
                                                                                 q.value(rec.indexOf("serieDocumento")).toString(),
                                                                                 q.value(rec.indexOf("utilizaVendedor")).toString(),
                                                                                 q.value(rec.indexOf("utilizaCliente")).toString(),
                                                                                 q.value(rec.indexOf("utilizaTipoCliente")).toString(),
                                                                                 q.value(rec.indexOf("utilizaSoloProveedores")).toString(),
                                                                                 q.value(rec.indexOf("afectaCuentaCorriente")).toString(),
                                                                                 q.value(rec.indexOf("afectaCuentaCorrienteMercaderia")).toString(),
                                                                                 q.value(rec.indexOf("afectaStock")).toString(),
                                                                                 q.value(rec.indexOf("afectaTotales")).toString(),
                                                                                 q.value(rec.indexOf("utilizaCantidades")).toString(),
                                                                                 q.value(rec.indexOf("utilizaPrecioManual")).toString(),
                                                                                 q.value(rec.indexOf("utilizaDescuentoArticulo")).toString(),
                                                                                 q.value(rec.indexOf("utilizaDescuentoTotal")).toString(),
                                                                                 q.value(rec.indexOf("emiteEnImpresora")).toString(),
                                                                                 q.value(rec.indexOf("codigoModeloImpresion")).toString(),
                                                                                 q.value(rec.indexOf("cantidadCopias")).toString(),
                                                                                 q.value(rec.indexOf("utilizaObservaciones")).toString(),
                                                                                 q.value(rec.indexOf("afectaCuentaBancaria")).toString(),
                                                                                 q.value(rec.indexOf("utilizaCuentaBancaria")).toString(),
                                                                                 q.value(rec.indexOf("utilizaPagoChequeDiferido")).toString(),
                                                                                 q.value(rec.indexOf("utilizaSoloMediosDePagoCheque")).toString(),
                                                                                 q.value(rec.indexOf("esDocumentoDeVenta")).toString(),
                                                                                 q.value(rec.indexOf("descripcionTipoDocumentoImpresora")).toString(),
                                                                                 q.value(rec.indexOf("utilizaArticulosInactivos")).toString(),

                                                                                 q.value(rec.indexOf("utilizaRedondeoEnTotal")).toString(),
                                                                                 q.value(rec.indexOf("utilizaPrecioManualEnMonedaReferencia")).toString(),
                                                                                 q.value(rec.indexOf("descripcionCodigoBarrasADemanda")).toString(),
                                                                                 q.value(rec.indexOf("utilizaListaPrecioManual")).toString(),
                                                                                 q.value(rec.indexOf("utilizaFormasDePago")).toString(),
                                                                                 q.value(rec.indexOf("noAfectaIva")).toString(),
                                                                                 q.value(rec.indexOf("utilizaSeteoDePreciosEnListasDePrecioPorArticulo")).toString(),
                                                                                 q.value(rec.indexOf("noPermiteFacturarConStockPrevistoCero")).toString(),
                                                                                 q.value(rec.indexOf("imprimeEnFormatoTicket")).toString(),
                                                                                 q.value(rec.indexOf("imprimeObservacionesEnTicket")).toString(),
                                                                                 q.value(rec.indexOf("utilizaComentarios")).toString(),
                                                                                 q.value(rec.indexOf("cantidadMaximaLineasEnDocumento")).toString()






                                                                                 ));

            }

            if(ModuloListaTipoDocumentos::rowCount()==0){
                return false;
            }else{
                return true;
            }

        }else{
            return false;
        }
    }else{
        return false;
    }
}



QString ModuloListaTipoDocumentos::retornaValorCampoTipoDocumento(QString _codigoTipoDocumento ,QString _permisoDocumento) const{


    QString _valorARetornar="";
    for (int var = 0; var < m_TipoDocumentos.size(); ++var) {
        if(QString::number(m_TipoDocumentos[var].codigoTipoDocumento())==_codigoTipoDocumento){


            if (_permisoDocumento == "utilizaArticulos"){
                _valorARetornar = convertirStringABool(m_TipoDocumentos[var].utilizaArticulos());
            }
            else if (_permisoDocumento == "utilizaCodigoBarrasADemanda"){
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaCodigoBarrasADemanda());
            }
            else if (_permisoDocumento == "utilizaTotales")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaTotales());}
            else if (_permisoDocumento == "utilizaListaPrecio")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaListaPrecio());}
            else if (_permisoDocumento == "utilizaMediosDePago")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaMediosDePago());}
            else if (_permisoDocumento == "utilizaFechaPrecio")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaFechaPrecio());}
            else if (_permisoDocumento == "utilizaFechaDocumento")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaFechaDocumento());}
            else if (_permisoDocumento == "utilizaNumeroDocumento")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaNumeroDocumento());}
            else if (_permisoDocumento == "utilizaSerieDocumento")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaSerieDocumento());}
            else if (_permisoDocumento == "utilizaVendedor")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaVendedor());}
            else if (_permisoDocumento == "utilizaCliente")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaCliente());}
            else if (_permisoDocumento == "utilizaTipoCliente")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaTipoCliente());}
            else if (_permisoDocumento == "utilizaSoloProveedores")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaSoloProveedores());}
            else if (_permisoDocumento == "afectaCuentaCorriente")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].afectaCuentaCorriente());}
            else if (_permisoDocumento == "afectaCuentaCorrienteMercaderia")           {
                _valorARetornar= convertirStringABool(m_TipoDocumentos[var].afectaCuentaCorrienteMercaderia());
            }


            else if (_permisoDocumento == "afectaStock")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].afectaStock());}
            else if (_permisoDocumento == "afectaTotales")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].afectaTotales());}
            else if (_permisoDocumento == "utilizaCantidades")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaCantidades());}
            else if (_permisoDocumento == "utilizaPrecioManual")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaPrecioManual());}
            else if (_permisoDocumento == "utilizaDescuentoArticulo")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaDescuentoArticulo());}
            else if (_permisoDocumento == "utilizaDescuentoTotal")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaDescuentoTotal());}
            else if (_permisoDocumento == "emiteEnImpresora")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].emiteEnImpresora());}
            else if (_permisoDocumento == "codigoModeloImpresion")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].codigoModeloImpresion());}
            else if (_permisoDocumento == "cantidadCopias")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].cantidadCopias());}
            else if (_permisoDocumento == "utilizaObservaciones")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaObservaciones());}
            else if (_permisoDocumento == "afectaCuentaBancaria")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].afectaCuentaBancaria());}
            else if (_permisoDocumento == "utilizaCuentaBancaria")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaCuentaBancaria());}
            else if (_permisoDocumento == "utilizaPagoChequeDiferido")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaPagoChequeDiferido());}


            else if (_permisoDocumento == "utilizaSoloMediosDePagoCheque")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaSoloMediosDePagoCheque());}
            else if (_permisoDocumento == "esDocumentoDeVenta")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].esDocumentoDeVenta());}
            else if (_permisoDocumento == "descripcionTipoDocumentoImpresora")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].descripcionTipoDocumentoImpresora());}
            else if (_permisoDocumento == "utilizaArticulosInactivos")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaArticulosInactivos());}
            else if (_permisoDocumento == "utilizaRedondeoEnTotal")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaRedondeoEnTotal());}
            else if (_permisoDocumento == "utilizaPrecioManualEnMonedaReferencia")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaPrecioManualEnMonedaReferencia());}
            else if (_permisoDocumento == "descripcionCodigoBarrasADemanda")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].descripcionCodigoBarrasADemanda());}



            else if (_permisoDocumento == "utilizaListaPrecioManual")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaListaPrecioManual());}
            else if (_permisoDocumento == "utilizaFormasDePago")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaFormasDePago());}
            else if (_permisoDocumento == "noAfectaIva")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].noAfectaIva());}
            else if (_permisoDocumento == "utilizaSeteoDePreciosEnListasDePrecioPorArticulo")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaSeteoDePreciosEnListasDePrecioPorArticulo());}
            else if (_permisoDocumento == "noPermiteFacturarConStockPrevistoCero")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].noPermiteFacturarConStockPrevistoCero());}
            else if (_permisoDocumento == "imprimeEnFormatoTicket")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].imprimeEnFormatoTicket());}
            else if (_permisoDocumento == "imprimeObservacionesEnTicket")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].imprimeObservacionesEnTicket());}
            else if (_permisoDocumento == "utilizaComentarios")           {_valorARetornar= convertirStringABool(m_TipoDocumentos[var].utilizaComentarios());}


        }
    }
    return _valorARetornar;


    /*
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

        if(query.exec("select "+_campoTipoDocumento+" from TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"' ")){

            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toString();

                }else{
                    return "";
                }
            }else {
                return "";
            }
        }else{
            return "";
        }
    }*/
}










