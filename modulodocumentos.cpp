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

#include "modulodocumentos.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include <funciones.h>
#include <QPrinter>
#include <QPainter>
#include <QDebug>
#include <QFont>
#include <moduloarticulos.h>
#include "modulomediosdepago.h"
#include <Utilidades/moduloconfiguracion.h>
#include <modulolistatipodocumentos.h>
#include <CFE/modulo_cfe_parametrosgenerales.h>
#include <proxy/modulo_configuracionproxy.h>
#include <curl/curl.h>
#include <QImage>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <QByteArray>
#include <iostream>
#include <QThread>
#include <algorithm>
#include <json/json.h>


#if linux
#include "QrCode/qrcode.hpp"
using qrcodegen::QrCode;
#endif

#ifdef Q_OS_WIN
    #include <windows.h>
#else
    #include <unistd.h>
#endif


ModuloConfiguracion func_configuracion;

Modulo_CFE_ParametrosGenerales func_CFE_ParametrosGenerales;

Modulo_ConfiguracionProxy func_configuracionProxy;

ModuloListaTipoDocumentos func_tipoDocumentos;

Funciones funcion;

ModuloArticulos func_articulos;

ModuloMediosDePago func_medioDePago;

ModuloDocumentos miDocumento;

QRectF cuadro(double x, double y, double ancho, double alto, bool justifica);

QRectF cuadroA4(double x, double y, double ancho, double alto, bool justifica);

double centimetro;

QString crearJsonIMIX(QString, QString, QString _serieDocumento);


QString crearJsonImix_Nube(QString, QString, QString , QString , QString , QString _serieDocumento);

QString crearJsonDynamia(QString, QString, QString , QString , QString , QString _serieDocumento);

QRectF cuadroTicketRight(double x, double y, double ancho, double alto, QString dato);




bool procesarImix(QString, QString, QString _serieDocumento);

bool procesarImix_Nube(QString, QString, QString, QString, QString, QString _serieDocumento );

bool procesarDynamia(QString, QString, QString, QString, QString, QString _serieDocumento );

bool enviarYConsultarRespuesta(const QByteArray &jsonAEnviar);
bool httpGet(const QString &url, QString &respuesta);
bool httpPostJson(const QString &url, const QByteArray &jsonData, QString &respuesta);


QString numeroDocumentoV="";
QString codigoTipoDocumentoV="";
QString serieDocumentoV="";


QString tipoDeCFEAEnviarDynamiaV="";

QString caeTipoDocumentoCFEDescripcionV="";


#define CURL_ICONV_CODESET_FOR_UTF8 "UTF-8"

QString resultadoFinal="";

QPainter painter;

QFont fuente("Arial");


// Función auxiliar para pausar en segundos:
static inline void esperarSegundos(unsigned int segundos)
{
#ifdef Q_OS_WIN
    Sleep(segundos * 1000); // Sleep en Windows mide milisegundos
#else
    sleep(segundos);        // sleep en Linux/Unix mide segundos
#endif
}


bool ModuloDocumentos::actualizarNumeroCFEDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _numeroCae, QString _serieDocumento) const{

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

        if(query.exec("update Documentos  set fechaUltimaModificacionDocumento='"+funcion.fechaHoraDeHoy()+"',cae_numeroCae='"+_numeroCae+"' where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")){

            return true;

        }else{
            return false;
        }
    }else{
        return false;
    }
}




static int writer(char *data, size_t size, size_t nmemb, std::string *buffer_in)
{

    if (buffer_in != NULL)
    {
        QString resultado = ((QString)data).trimmed();

        if(resultado.contains("<title>Request Error</title>",Qt::CaseInsensitive)){

            funcion.loguear("Respuesta Imix:\n"+resultado);
            funcion.mensajeAdvertenciaOk("Hubo un error al procesar el CFE: \n\n"+resultado);

            //qDebug()<< resultado;
            return -1;

        }

        QXmlStreamReader xs(resultado);

        while (!xs.atEnd()) {
            if (xs.readNextStartElement()){
                if(xs.name().toString().toLower()!="int"){
                    funcion.mensajeAdvertenciaOk("ERROR: "+xs.readElementText());
                    funcion.loguear("Respuesta Imix:\n"+resultado);

                    return -1;
                }else{
                    QString numeroCae= xs.readElementText();

                    if(miDocumento.actualizarNumeroCFEDocumento(numeroDocumentoV,codigoTipoDocumentoV,numeroCae, serieDocumentoV)){
                        funcion.loguear("Respuesta Imix:\nNúmero CFE OK: "+numeroCae);

                        return size * nmemb;
                    }else{
                        funcion.mensajeAdvertenciaOk("ERROR: \nEl CFE se emitio, pero no se pudo actualizar el documento en Khitomer.");
                        return -1;
                    }

                }
            }
        }

        if(resultado.contains("status",Qt::CaseSensitive)){
            resultadoFinal=resultado;
        }
        return size * nmemb;
    }

}


static int writerDynamia(char *data, size_t size, size_t nmemb, std::string *buffer_in)
{

    if (buffer_in != NULL)
    {
        QString resultado = ((QString)data).trimmed();

        //        qDebug()<< resultado;

        if(resultado.contains("status",Qt::CaseSensitive)){
            funcion.loguear("Respuesta Dynamia:\n"+resultado);
            resultadoFinal=resultado;
            return size * nmemb;
        }else{
            funcion.loguear("Respuesta Dynamia:\n"+resultado);
            funcion.mensajeAdvertenciaOk("ERROR GRAVE: \n\n"+resultado+"\n\n Anote la información del documento y ponganse en contacto\ncon su proveedor del sistema");
            return 0;
        }
    }else{
        return 0;
    }

}




static int writerImix_Nube(char *data, size_t size, size_t nmemb, std::string *buffer_in)
{

    if (buffer_in != NULL)
    {
        QString resultado = ((QString)data).trimmed();

        if(resultado.contains("CaeDesde",Qt::CaseSensitive)){
            funcion.loguear("Respuesta Imix_nube OK:\n"+resultado);
            resultadoFinal=resultado;
            return size * nmemb;
        }else{
            funcion.loguear("Respuesta Imix_nube ERROR:\n"+resultado);
            funcion.mensajeAdvertenciaOk("ERROR GRAVE: \n\n"+resultado+"\n\n Anote la información del documento y ponganse en contacto\ncon su proveedor del sistema");
            return 0;
        }
    }else{
        return 0;
    }

}


static int writerProxy(char *data, size_t size, size_t nmemb, std::string *buffer_in)
{

    if (buffer_in != NULL)
    {
            QString resultado = ((QString)data).trimmed();
            funcion.loguear("Respuesta Proxy OK:\n"+resultado);
            resultadoFinal=resultado;
            return size * nmemb;
    }else{
        return 0;
    }

}



ModuloDocumentos::ModuloDocumentos(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoDocumentoRole] = "codigoDocumento";
    roles[CodigoTipoDocumentoRole] = "codigoTipoDocumento";
    roles[SerieDocumentoRole] = "serieDocumento";
    roles[CodigoEstadoDocumentoRole] = "codigoEstadoDocumento";

    roles[CodigoClienteRole] = "codigoCliente";
    roles[TipoClienteRole] = "tipoCliente";
    roles[CodigoMonedaDocumentoRole] = "codigoMonedaDocumento";
    roles[FechaEmisionDocumentoRole] = "fechaEmisionDocumento";

    roles[PrecioTotalVentaRole] = "precioTotalVenta";
    roles[PrecioSubTotalVentaRole] = "precioSubTotalVenta";
    roles[PrecioIvaVentaRole] = "precioIvaVenta";
    roles[CodigoLiquidacionRole] = "codigoLiquidacion";

    roles[CodigoVendedorLiquidacionRole] = "codigoVendedorLiquidacion";
    roles[CodigoVendedorComisionaRole] = "codigoVendedorComisiona";

    roles[NombreClienteRole] = "nombreCliente";
    roles[RazonSocialRole] = "razonSocial";
    roles[DescripcionTipoDocumentoRole] = "descripcionTipoDocumento";
    roles[DescripcionEstadoDocumentoRole] = "descripcionEstadoDocumento";

    roles[TotalIva1Role] = "totalIva1";
    roles[TotalIva2Role] = "totalIva2";
    roles[TotalIva3Role] = "totalIva3";
    roles[ObservacionRole] = "observaciones";

    roles[numeroCuentaBancariaRole] = "numeroCuentaBancaria";
    roles[codigoBancoRole] = "codigoBanco";
    roles[esDocumentoWebRole] = "esDocumentoWeb";
    roles[montoDescuentoTotalRole] = "montoDescuentoTotal";

    roles[saldoClienteCuentaCorrienteRole] = "saldoClienteCuentaCorriente";
    roles[formaDePagoRole] = "formaDePago";

    roles[porcentajeDescuentoAlTotalRole] = "porcentajeDescuentoAlTotal";
    roles[esDocumentoCFERole] = "esDocumentoCFE";

    roles[cae_numeroCaeRole] = "cae_numeroCae";
    roles[cae_serieRole] = "cae_serie";

    roles[comentariosRole] = "comentarios";







    setRoleNames(roles);



}

Documentos::Documentos(const qulonglong &codigoDocumento, const int &codigoTipoDocumento, const QString &serieDocumento, const QString &codigoEstadoDocumento
                       ,const QString &codigoCliente ,const int &tipoCliente ,const int &codigoMonedaDocumento ,const QString &fechaEmisionDocumento
                       ,const QString &precioTotalVenta ,const QString &precioSubTotalVenta ,const QString &precioIvaVenta ,const QString &codigoLiquidacion
                       ,const QString &codigoVendedorLiquidacion,const QString &codigoVendedorComisiona

                       ,const QString &nombreCliente,const QString &razonSocial,const QString &descripcionTipoDocumento,const QString &descripcionEstadoDocumento
                       ,const QString &totalIva1,const QString &totalIva2,const QString &totalIva3,const QString &observaciones
                       ,const QString &numeroCuentaBancaria,const QString &codigoBanco,const QString &esDocumentoWeb,const QString &montoDescuentoTotal
                       ,const QString &saldoClienteCuentaCorriente,const QString &formaDePago,const QString &porcentajeDescuentoAlTotal
                       ,const QString &esDocumentoCFE

                       ,const QString &cae_numeroCae
                       ,const QString &cae_serie
                       ,const QString &comentarios

                       )

    : m_codigoDocumento(codigoDocumento), m_codigoTipoDocumento(codigoTipoDocumento) , m_serieDocumento(serieDocumento), m_codigoEstadoDocumento(codigoEstadoDocumento) , m_codigoCliente(codigoCliente), m_tipoCliente(tipoCliente)
    , m_codigoMonedaDocumento(codigoMonedaDocumento), m_fechaEmisionDocumento(fechaEmisionDocumento), m_precioTotalVenta(precioTotalVenta), m_precioSubTotalVenta(precioSubTotalVenta)
    , m_precioIvaVenta(precioIvaVenta), m_codigoLiquidacion(codigoLiquidacion), m_codigoVendedorLiquidacion(codigoVendedorLiquidacion), m_codigoVendedorComisiona(codigoVendedorComisiona)

    , m_nombreCliente(nombreCliente), m_razonSocial(razonSocial), m_descripcionTipoDocumento(descripcionTipoDocumento)
    , m_descripcionEstadoDocumento(descripcionEstadoDocumento), m_totalIva1(totalIva1), m_totalIva2(totalIva2), m_totalIva3(totalIva3), m_observaciones(observaciones)
    , m_numeroCuentaBancaria(numeroCuentaBancaria), m_codigoBanco(codigoBanco), m_esDocumentoWeb(esDocumentoWeb), m_montoDescuentoTotal(montoDescuentoTotal)
    , m_saldoClienteCuentaCorriente(saldoClienteCuentaCorriente), m_formaDePago(formaDePago),m_porcentajeDescuentoAlTotal(porcentajeDescuentoAlTotal)
    , m_esDocumentoCFE(esDocumentoCFE), m_cae_numeroCae(cae_numeroCae), m_cae_serie(cae_serie), m_comentarios(comentarios)

{
}
qulonglong Documentos::codigoDocumento() const
{
    return m_codigoDocumento;
}
int Documentos::codigoTipoDocumento() const
{
    return m_codigoTipoDocumento;
}
QString Documentos::serieDocumento() const
{
    return m_serieDocumento;
}
QString Documentos::codigoEstadoDocumento() const
{
    return m_codigoEstadoDocumento;
}
QString Documentos::codigoCliente() const
{
    return m_codigoCliente;
}
int Documentos::tipoCliente() const
{
    return m_tipoCliente;
}
int Documentos::codigoMonedaDocumento() const
{
    return m_codigoMonedaDocumento;
}
QString Documentos::fechaEmisionDocumento() const
{
    return m_fechaEmisionDocumento;
}


QString Documentos::precioTotalVenta() const
{
    return m_precioTotalVenta;
}
QString Documentos::precioSubTotalVenta() const
{
    return m_precioSubTotalVenta;
}

QString Documentos::precioIvaVenta() const
{
    return m_precioIvaVenta;
}

QString Documentos::codigoLiquidacion() const
{
    return m_codigoLiquidacion;
}
QString Documentos::codigoVendedorLiquidacion() const
{
    return m_codigoVendedorLiquidacion;
}
QString Documentos::codigoVendedorComisiona() const
{
    return m_codigoVendedorComisiona;
}


QString Documentos::nombreCliente() const
{
    return m_nombreCliente;
}
QString Documentos::razonSocial() const
{
    return m_razonSocial;
}
QString Documentos::descripcionTipoDocumento() const
{
    return m_descripcionTipoDocumento;
}
QString Documentos::descripcionEstadoDocumento() const
{
    return m_descripcionEstadoDocumento;
}



QString Documentos::totalIva1() const
{
    return m_totalIva1;
}
QString Documentos::totalIva2() const
{
    return m_totalIva2;
}
QString Documentos::totalIva3() const
{
    return m_totalIva3;
}
QString Documentos::observaciones() const
{
    return m_observaciones;
}


QString Documentos::numeroCuentaBancaria() const
{
    return m_numeroCuentaBancaria;
}
QString Documentos::codigoBanco() const
{
    return m_codigoBanco;
}
QString Documentos::esDocumentoWeb() const
{
    return m_esDocumentoWeb;
}
QString Documentos::montoDescuentoTotal() const
{
    return m_montoDescuentoTotal;
}

QString Documentos::saldoClienteCuentaCorriente() const
{
    return m_saldoClienteCuentaCorriente;
}
QString Documentos::formaDePago() const
{
    return m_formaDePago;
}
QString Documentos::porcentajeDescuentoAlTotal() const
{
    return m_porcentajeDescuentoAlTotal;
}
QString Documentos::esDocumentoCFE() const
{
    return m_esDocumentoCFE;
}

QString Documentos::cae_numeroCae() const
{
    return m_cae_numeroCae;
}
QString Documentos::cae_serie() const
{
    return m_cae_serie;
}
QString Documentos::comentarios() const
{
    return m_comentarios;
}




qulonglong ModuloDocumentos::retornaCodigoDocumentoPorIndice(int indice) const{
    return m_Documentos[indice].codigoDocumento();
}
int ModuloDocumentos::retornaCodigoTipoDocumentoPorIndice(int indice) const{
    return m_Documentos[indice].codigoTipoDocumento();
}
QString ModuloDocumentos::retornaSerieDocumentoPorIndice(int indice) const{
    return m_Documentos[indice].serieDocumento();
}
QString ModuloDocumentos::retornaTotalDocumentoPorIndice(int indice) const{
    return m_Documentos[indice].precioTotalVenta();
}
QString ModuloDocumentos::retornaSaldoCuentaCorrientePorIndice(int indice) const{
    return m_Documentos[indice].saldoClienteCuentaCorriente();
}
int ModuloDocumentos::retornaCodigoMonedaPorIndice(int indice) const{
    return m_Documentos[indice].codigoMonedaDocumento();
}
QString ModuloDocumentos::retornaFechaDocumentoPorIndice(int indice) const{
    return m_Documentos[indice].fechaEmisionDocumento();
}
QString ModuloDocumentos::retornaObservacionesDocumentoPorIndice(int indice) const{
    return m_Documentos[indice].observaciones();
}
QString ModuloDocumentos::retornacomentariosDocumentoPorIndice(int indice) const{
    return m_Documentos[indice].comentarios();
}




void ModuloDocumentos::agregarDocumento(const Documentos &documentos)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Documentos << documentos;
    endInsertRows();
}

void ModuloDocumentos::limpiarListaDocumentos(){
    m_Documentos.clear();
}

void ModuloDocumentos::buscarDocumentos(QString campo, QString datoABuscar){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from Documentos D left join Clientes C on D.codigoCliente=C.codigoCliente and D.tipoCliente=C.tipoCliente join TipoDocumento TD on TD.codigoTipoDocumento=D.codigoTipoDocumento join TipoEstadoDocumento TED on TED.codigoEstadoDocumento=D.codigoEstadoDocumento where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloDocumentos::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloDocumentos::agregarDocumento(Documentos(
                                                       q.value(rec.indexOf("codigoDocumento")).toULongLong(),
                                                       q.value(rec.indexOf("codigoTipoDocumento")).toInt(),
                                                       q.value(rec.indexOf("serieDocumento")).toString(),
                                                       q.value(rec.indexOf("codigoEstadoDocumento")).toString(),


                                                       q.value(rec.indexOf("codigoCliente")).toString(),
                                                       q.value(rec.indexOf("tipoCliente")).toInt(),
                                                       q.value(rec.indexOf("codigoMonedaDocumento")).toInt(),
                                                       q.value(rec.indexOf("fechaEmisionDocumento")).toString(),

                                                       q.value(rec.indexOf("precioTotalVenta")).toString(),
                                                       q.value(rec.indexOf("precioSubTotalVenta")).toString(),
                                                       q.value(rec.indexOf("precioIvaVenta")).toString(),
                                                       q.value(rec.indexOf("codigoLiquidacion")).toString(),
                                                       q.value(rec.indexOf("codigoVendedorLiquidacion")).toString(),
                                                       q.value(rec.indexOf("codigoVendedorComisiona")).toString(),

                                                       q.value(rec.indexOf("nombreCliente")).toString(),
                                                       q.value(rec.indexOf("razonSocial")).toString(),
                                                       q.value(rec.indexOf("descripcionTipoDocumento")).toString(),
                                                       q.value(rec.indexOf("descripcionEstadoDocumento")).toString(),

                                                       q.value(rec.indexOf("totalIva1")).toString(),
                                                       q.value(rec.indexOf("totalIva2")).toString(),
                                                       q.value(rec.indexOf("totalIva3")).toString(),
                                                       q.value(rec.indexOf("observaciones")).toString(),

                                                       q.value(rec.indexOf("numeroCuentaBancaria")).toString(),
                                                       q.value(rec.indexOf("codigoBanco")).toString(),
                                                       q.value(rec.indexOf("esDocumentoWeb")).toString(),
                                                       q.value(rec.indexOf("montoDescuentoTotal")).toString(),

                                                       q.value(rec.indexOf("saldoClienteCuentaCorriente")).toString(),
                                                       q.value(rec.indexOf("formaDePago")).toString(),
                                                       q.value(rec.indexOf("porcentajeDescuentoAlTotal")).toString(),
                                                       q.value(rec.indexOf("esDocumentoCFE")).toString(),
                                                       q.value(rec.indexOf("cae_numeroCae")).toString(),
                                                       q.value(rec.indexOf("cae_serie")).toString(),
                                                       q.value(rec.indexOf("comentarios")).toString()

                                                       )

                                                   );
            }
        }
    }
}
void ModuloDocumentos::buscarDocumentosEnLiquidaciones(QString _codigoLiquidacion, QString _codigoVendedorLiquidacion, QString _codigoPerfil, QString _estadoDocumento,QString _aniosHaciaAtras){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    QString mesHaciaAtras="";

    QString anioHaciaAtras=" AND fechaHoraGuardadoDocumentoSQL > DATE_SUB(CURDATE(), INTERVAL "+_aniosHaciaAtras+" YEAR) ";


    // Si el año hacia atras es 0, pongo el mes en 1 hacia atras
    if(_aniosHaciaAtras=="0"){

        mesHaciaAtras=" AND fechaHoraGuardadoDocumentoSQL > DATE_SUB(CURDATE(), INTERVAL 1 MONTH)  ";
        anioHaciaAtras="";

    }


    if(conexion){

        QSqlQuery q;
        // Si es -1 el estado del documeto, cargo todos
        if(_estadoDocumento=="-1"){
            //  q = Database::consultaSql("select * from Documentos D join TipoDocumentoPerfilesUsuarios TDP on TDP.codigoTipoDocumento=D.codigoTipoDocumento    left join Clientes C on D.codigoCliente=C.codigoCliente and D.tipoCliente=C.tipoCliente join TipoDocumento TD on TD.codigoTipoDocumento=D.codigoTipoDocumento join TipoEstadoDocumento TED on TED.codigoEstadoDocumento=D.codigoEstadoDocumento where D.codigoLiquidacion='"+_codigoLiquidacion+"' and D.codigoVendedorLiquidacion='"+_codigoVendedorLiquidacion+"' and TDP.codigoPerfil='"+_codigoPerfil+"'  order by D.fechaHoraGuardadoDocumentoSQL desc");
            q = Database::consultaSql("select * from VDocumentosLiquidaciones  where codigoLiquidacion='"+_codigoLiquidacion+"' and codigoVendedorLiquidacion='"+_codigoVendedorLiquidacion+"' and codigoPerfil='"+_codigoPerfil+"' "+anioHaciaAtras+"  "+mesHaciaAtras+"   order by fechaHoraGuardadoDocumentoSQL desc");
        }else{
            // Cargo el estado del documento que me pasaron
            //  q = Database::consultaSql("select * from Documentos D join TipoDocumentoPerfilesUsuarios TDP on TDP.codigoTipoDocumento=D.codigoTipoDocumento    left join Clientes C on D.codigoCliente=C.codigoCliente and D.tipoCliente=C.tipoCliente join TipoDocumento TD on TD.codigoTipoDocumento=D.codigoTipoDocumento join TipoEstadoDocumento TED on TED.codigoEstadoDocumento=D.codigoEstadoDocumento where D.codigoEstadoDocumento='"+_estadoDocumento+"'   and   D.codigoLiquidacion='"+_codigoLiquidacion+"' and D.codigoVendedorLiquidacion='"+_codigoVendedorLiquidacion+"' and TDP.codigoPerfil='"+_codigoPerfil+"'  order by D.fechaHoraGuardadoDocumentoSQL desc");
            q = Database::consultaSql("select * from VDocumentosLiquidaciones where codigoEstadoDocumento='"+_estadoDocumento+"'   and   codigoLiquidacion='"+_codigoLiquidacion+"' and codigoVendedorLiquidacion='"+_codigoVendedorLiquidacion+"' and codigoPerfil='"+_codigoPerfil+"'  "+anioHaciaAtras+"  "+mesHaciaAtras+"  order by fechaHoraGuardadoDocumentoSQL desc");
        }




        //qDebug()<< q.lastQuery();

        QSqlRecord rec = q.record();

        ModuloDocumentos::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloDocumentos::agregarDocumento(Documentos(
                                                       q.value(rec.indexOf("codigoDocumento")).toULongLong(),
                                                       q.value(rec.indexOf("codigoTipoDocumento")).toInt(),
                                                       q.value(rec.indexOf("serieDocumento")).toString(),
                                                       q.value(rec.indexOf("codigoEstadoDocumento")).toString(),

                                                       q.value(rec.indexOf("codigoCliente")).toString(),
                                                       q.value(rec.indexOf("tipoCliente")).toInt(),
                                                       q.value(rec.indexOf("codigoMonedaDocumento")).toInt(),
                                                       q.value(rec.indexOf("fechaEmisionDocumento")).toString(),

                                                       q.value(rec.indexOf("precioTotalVenta")).toString(),
                                                       q.value(rec.indexOf("precioSubTotalVenta")).toString(),
                                                       q.value(rec.indexOf("precioIvaVenta")).toString(),
                                                       q.value(rec.indexOf("codigoLiquidacion")).toString(),
                                                       q.value(rec.indexOf("codigoVendedorLiquidacion")).toString(),
                                                       q.value(rec.indexOf("codigoVendedorComisiona")).toString(),

                                                       q.value(rec.indexOf("nombreCliente")).toString(),
                                                       q.value(rec.indexOf("razonSocial")).toString(),
                                                       q.value(rec.indexOf("descripcionTipoDocumento")).toString(),
                                                       q.value(rec.indexOf("descripcionEstadoDocumento")).toString(),

                                                       q.value(rec.indexOf("totalIva1")).toString(),
                                                       q.value(rec.indexOf("totalIva2")).toString(),
                                                       q.value(rec.indexOf("totalIva3")).toString(),
                                                       q.value(rec.indexOf("observaciones")).toString(),
                                                       q.value(rec.indexOf("numeroCuentaBancaria")).toString(),
                                                       q.value(rec.indexOf("codigoBanco")).toString(),
                                                       q.value(rec.indexOf("esDocumentoWeb")).toString(),
                                                       q.value(rec.indexOf("montoDescuentoTotal")).toString(),

                                                       q.value(rec.indexOf("saldoClienteCuentaCorriente")).toString(),
                                                       q.value(rec.indexOf("formaDePago")).toString(),
                                                       q.value(rec.indexOf("porcentajeDescuentoAlTotal")).toString(),
                                                       q.value(rec.indexOf("esDocumentoCFE")).toString(),
                                                       q.value(rec.indexOf("cae_numeroCae")).toString(),
                                                       q.value(rec.indexOf("cae_serie")).toString(),
                                                       q.value(rec.indexOf("comentarios")).toString()


                                                       )

                                                   );
            }
        }
    }
}


void ModuloDocumentos::buscarDocumentosEnMantenimiento(QString campo, QString datoABuscar, QString _codigoPerfil,QString _aniosHaciaAtras){


    // qDebug()<< campo;

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }




    if(conexion){

        QString mesHaciaAtras="";
        QString anioHaciaAtras=" AND fechaHoraGuardadoDocumentoSQL > DATE_SUB(CURDATE(), INTERVAL "+_aniosHaciaAtras+" YEAR) ";

        // Si el año hacia atras es 0, pongo el mes en 1 hacia atras
        if(_aniosHaciaAtras=="0"){
            mesHaciaAtras=" AND fechaHoraGuardadoDocumentoSQL > DATE_SUB(CURDATE(), INTERVAL 1 MONTH)  ";
            anioHaciaAtras="";

        }else if(_aniosHaciaAtras=="-1"){
            mesHaciaAtras="";
            anioHaciaAtras="";
        }


        QSqlQuery q = Database::consultaSql("select D.*, TD.descripcionTipoDocumento, TED.descripcionEstadoDocumento, C.nombreCliente,C.razonSocial from Documentos D join TipoDocumentoPerfilesUsuarios TDP on TDP.codigoTipoDocumento=D.codigoTipoDocumento left join Clientes C on D.codigoCliente=C.codigoCliente and D.tipoCliente=C.tipoCliente join TipoDocumento TD on TD.codigoTipoDocumento=D.codigoTipoDocumento join TipoEstadoDocumento TED on TED.codigoEstadoDocumento=D.codigoEstadoDocumento left join DocumentosLineas DL on DL.codigoDocumento=D.codigoDocumento and DL.codigoTipoDocumento=D.codigoTipoDocumento where "+campo+"'"+datoABuscar+"' and TDP.codigoPerfil='"+_codigoPerfil+"'   "+anioHaciaAtras+" "+mesHaciaAtras+"   group by D.codigoDocumento,D.codigoTipoDocumento   order by D.fechaUltimaModificacionDocumento desc");
        QSqlRecord rec = q.record();



        ModuloDocumentos::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloDocumentos::agregarDocumento(Documentos(
                                                       q.value(rec.indexOf("codigoDocumento")).toULongLong(),
                                                       q.value(rec.indexOf("codigoTipoDocumento")).toInt(),
                                                       q.value(rec.indexOf("serieDocumento")).toString(),
                                                       q.value(rec.indexOf("codigoEstadoDocumento")).toString(),


                                                       q.value(rec.indexOf("codigoCliente")).toString(),
                                                       q.value(rec.indexOf("tipoCliente")).toInt(),
                                                       q.value(rec.indexOf("codigoMonedaDocumento")).toInt(),
                                                       q.value(rec.indexOf("fechaEmisionDocumento")).toString(),

                                                       q.value(rec.indexOf("precioTotalVenta")).toString(),
                                                       q.value(rec.indexOf("precioSubTotalVenta")).toString(),
                                                       q.value(rec.indexOf("precioIvaVenta")).toString(),
                                                       q.value(rec.indexOf("codigoLiquidacion")).toString(),
                                                       q.value(rec.indexOf("codigoVendedorLiquidacion")).toString(),
                                                       q.value(rec.indexOf("codigoVendedorComisiona")).toString(),

                                                       q.value(rec.indexOf("nombreCliente")).toString(),
                                                       q.value(rec.indexOf("razonSocial")).toString(),
                                                       q.value(rec.indexOf("descripcionTipoDocumento")).toString(),
                                                       q.value(rec.indexOf("descripcionEstadoDocumento")).toString(),

                                                       q.value(rec.indexOf("totalIva1")).toString(),
                                                       q.value(rec.indexOf("totalIva2")).toString(),
                                                       q.value(rec.indexOf("totalIva3")).toString(),
                                                       q.value(rec.indexOf("observaciones")).toString(),
                                                       q.value(rec.indexOf("numeroCuentaBancaria")).toString(),
                                                       q.value(rec.indexOf("codigoBanco")).toString(),
                                                       q.value(rec.indexOf("esDocumentoWeb")).toString(),
                                                       q.value(rec.indexOf("montoDescuentoTotal")).toString(),

                                                       q.value(rec.indexOf("saldoClienteCuentaCorriente")).toString(),
                                                       q.value(rec.indexOf("formaDePago")).toString(),
                                                       q.value(rec.indexOf("porcentajeDescuentoAlTotal")).toString(),
                                                       q.value(rec.indexOf("esDocumentoCFE")).toString(),
                                                       q.value(rec.indexOf("cae_numeroCae")).toString(),
                                                       q.value(rec.indexOf("cae_serie")).toString(),
                                                       q.value(rec.indexOf("comentarios")).toString()



                                                       )

                                                   );
            }
        }
    }
}


void ModuloDocumentos::buscarDocumentosAPagarCuentaCorriente(QString _codigoMoneda, QString _codigoCliente, QString _codigoTipoCliente){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * FROM Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento where DOC.tipoCliente='"+_codigoTipoCliente+"' and DOC.codigoEstadoDocumento in ('E','G') and TDOC.afectaCuentaCorriente=1 and DOC.codigoCliente='"+_codigoCliente+"' and DOC.codigoMonedaDocumento='"+_codigoMoneda+"'  and DOC.saldoClienteCuentaCorriente!=0;");
        QSqlRecord rec = q.record();

        ModuloDocumentos::reset();
        if(q.record().count()>0){

            while (q.next()){




                ModuloDocumentos::agregarDocumento(Documentos(
                                                       q.value(rec.indexOf("codigoDocumento")).toULongLong(),
                                                       q.value(rec.indexOf("codigoTipoDocumento")).toInt(),
                                                       q.value(rec.indexOf("serieDocumento")).toString(),
                                                       q.value(rec.indexOf("codigoEstadoDocumento")).toString(),


                                                       q.value(rec.indexOf("codigoCliente")).toString(),
                                                       q.value(rec.indexOf("tipoCliente")).toInt(),
                                                       q.value(rec.indexOf("codigoMonedaDocumento")).toInt(),
                                                       q.value(rec.indexOf("fechaEmisionDocumento")).toString(),

                                                       q.value(rec.indexOf("precioTotalVenta")).toString(),
                                                       q.value(rec.indexOf("precioSubTotalVenta")).toString(),
                                                       q.value(rec.indexOf("precioIvaVenta")).toString(),
                                                       q.value(rec.indexOf("codigoLiquidacion")).toString(),
                                                       q.value(rec.indexOf("codigoVendedorLiquidacion")).toString(),
                                                       q.value(rec.indexOf("codigoVendedorComisiona")).toString(),

                                                       q.value(rec.indexOf("nombreCliente")).toString(),
                                                       q.value(rec.indexOf("razonSocial")).toString(),
                                                       q.value(rec.indexOf("descripcionTipoDocumento")).toString(),
                                                       q.value(rec.indexOf("descripcionEstadoDocumento")).toString(),

                                                       q.value(rec.indexOf("totalIva1")).toString(),
                                                       q.value(rec.indexOf("totalIva2")).toString(),
                                                       q.value(rec.indexOf("totalIva3")).toString(),
                                                       q.value(rec.indexOf("observaciones")).toString(),
                                                       q.value(rec.indexOf("numeroCuentaBancaria")).toString(),
                                                       q.value(rec.indexOf("codigoBanco")).toString(),
                                                       q.value(rec.indexOf("esDocumentoWeb")).toString(),
                                                       q.value(rec.indexOf("montoDescuentoTotal")).toString(),

                                                       q.value(rec.indexOf("saldoClienteCuentaCorriente")).toString(),
                                                       q.value(rec.indexOf("formaDePago")).toString(),
                                                       q.value(rec.indexOf("porcentajeDescuentoAlTotal")).toString(),
                                                       q.value(rec.indexOf("esDocumentoCFE")).toString(),
                                                       q.value(rec.indexOf("cae_numeroCae")).toString(),
                                                       q.value(rec.indexOf("cae_serie")).toString(),
                                                       q.value(rec.indexOf("comentarios")).toString()

                                                       )

                                                   );
            }
        }
    }
}



void ModuloDocumentos::buscarDocumentosDePagoCuentaCorriente(QString _codigoMoneda, QString _codigoCliente, QString _codigoTipoCliente){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * FROM Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento where DOC.tipoCliente='"+_codigoTipoCliente+"' and DOC.codigoEstadoDocumento in ('E','G') and TDOC.afectaCuentaCorriente=-1 and DOC.codigoCliente='"+_codigoCliente+"' and DOC.codigoMonedaDocumento='"+_codigoMoneda+"'  and DOC.saldoClienteCuentaCorriente!=0;");
        QSqlRecord rec = q.record();

        ModuloDocumentos::reset();
        if(q.record().count()>0){

            while (q.next()){




                ModuloDocumentos::agregarDocumento(Documentos(
                                                       q.value(rec.indexOf("codigoDocumento")).toULongLong(),
                                                       q.value(rec.indexOf("codigoTipoDocumento")).toInt(),
                                                       q.value(rec.indexOf("serieDocumento")).toString(),
                                                       q.value(rec.indexOf("codigoEstadoDocumento")).toString(),


                                                       q.value(rec.indexOf("codigoCliente")).toString(),
                                                       q.value(rec.indexOf("tipoCliente")).toInt(),
                                                       q.value(rec.indexOf("codigoMonedaDocumento")).toInt(),
                                                       q.value(rec.indexOf("fechaEmisionDocumento")).toString(),

                                                       q.value(rec.indexOf("precioTotalVenta")).toString(),
                                                       q.value(rec.indexOf("precioSubTotalVenta")).toString(),
                                                       q.value(rec.indexOf("precioIvaVenta")).toString(),
                                                       q.value(rec.indexOf("codigoLiquidacion")).toString(),
                                                       q.value(rec.indexOf("codigoVendedorLiquidacion")).toString(),
                                                       q.value(rec.indexOf("codigoVendedorComisiona")).toString(),

                                                       q.value(rec.indexOf("nombreCliente")).toString(),
                                                       q.value(rec.indexOf("razonSocial")).toString(),
                                                       q.value(rec.indexOf("descripcionTipoDocumento")).toString(),
                                                       q.value(rec.indexOf("descripcionEstadoDocumento")).toString(),

                                                       q.value(rec.indexOf("totalIva1")).toString(),
                                                       q.value(rec.indexOf("totalIva2")).toString(),
                                                       q.value(rec.indexOf("totalIva3")).toString(),
                                                       q.value(rec.indexOf("observaciones")).toString(),
                                                       q.value(rec.indexOf("numeroCuentaBancaria")).toString(),
                                                       q.value(rec.indexOf("codigoBanco")).toString(),
                                                       q.value(rec.indexOf("esDocumentoWeb")).toString(),
                                                       q.value(rec.indexOf("montoDescuentoTotal")).toString(),

                                                       q.value(rec.indexOf("saldoClienteCuentaCorriente")).toString(),
                                                       q.value(rec.indexOf("formaDePago")).toString(),
                                                       q.value(rec.indexOf("porcentajeDescuentoAlTotal")).toString(),
                                                       q.value(rec.indexOf("esDocumentoCFE")).toString(),
                                                       q.value(rec.indexOf("cae_numeroCae")).toString(),
                                                       q.value(rec.indexOf("cae_serie")).toString(),
                                                       q.value(rec.indexOf("comentarios")).toString()

                                                       )

                                                   );
            }
        }
    }
}



int ModuloDocumentos::rowCount(const QModelIndex & parent) const {
    return m_Documentos.count();
}

QVariant ModuloDocumentos::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Documentos.count()){
        return QVariant();

    }

    const Documentos &documentos = m_Documentos[index.row()];

    if (role == CodigoDocumentoRole){
        return documentos.codigoDocumento();
    }
    else if (role == CodigoTipoDocumentoRole){
        return documentos.codigoTipoDocumento();
    }
    else if (role == SerieDocumentoRole){
        return documentos.serieDocumento();
    }
    else if (role == CodigoEstadoDocumentoRole){
        return documentos.codigoEstadoDocumento();
    }

    else if (role == CodigoClienteRole){
        return documentos.codigoCliente();
    }
    else if (role == TipoClienteRole){
        return documentos.tipoCliente();
    }
    else if (role == CodigoMonedaDocumentoRole){
        return documentos.codigoMonedaDocumento();
    }
    else if (role == FechaEmisionDocumentoRole){
        return documentos.fechaEmisionDocumento();
    }
    else if (role == PrecioTotalVentaRole){
        return documentos.precioTotalVenta();
    }
    else if (role == PrecioSubTotalVentaRole){
        return documentos.precioSubTotalVenta();
    }

    else if (role == PrecioIvaVentaRole){
        return documentos.precioIvaVenta();
    }
    else if (role == CodigoLiquidacionRole){
        return documentos.codigoLiquidacion();
    }
    else if (role == CodigoVendedorLiquidacionRole){
        return documentos.codigoVendedorLiquidacion();
    }
    else if (role == CodigoVendedorComisionaRole){
        return documentos.codigoVendedorComisiona();
    }

    else if (role == NombreClienteRole){
        return documentos.nombreCliente();
    }
    else if (role == RazonSocialRole){
        return documentos.razonSocial();
    }
    else if (role == DescripcionTipoDocumentoRole){
        return documentos.descripcionTipoDocumento();
    }
    else if (role == DescripcionEstadoDocumentoRole){
        return documentos.descripcionEstadoDocumento();
    }

    else if (role == TotalIva1Role){
        return documentos.totalIva1();
    }
    else if (role == TotalIva2Role){
        return documentos.totalIva2();
    }
    else if (role == TotalIva3Role){
        return documentos.totalIva3();
    }
    else if (role == ObservacionRole){
        return documentos.observaciones();
    }
    else if (role == numeroCuentaBancariaRole){
        return documentos.numeroCuentaBancaria();
    }
    else if (role == codigoBancoRole){
        return documentos.codigoBanco();
    }
    else if (role == esDocumentoWebRole){
        return documentos.esDocumentoWeb();
    }
    else if (role == montoDescuentoTotalRole){
        return documentos.montoDescuentoTotal();
    }
    else if (role == saldoClienteCuentaCorrienteRole){
        return documentos.saldoClienteCuentaCorriente();
    }
    else if (role == formaDePagoRole){
        return documentos.formaDePago();
    }
    else if (role == porcentajeDescuentoAlTotalRole){
        return documentos.porcentajeDescuentoAlTotal();
    }
    else if (role == esDocumentoCFERole){
        return documentos.esDocumentoCFE();
    }
    else if (role == cae_numeroCaeRole){
        return documentos.cae_numeroCae();
    }
    else if (role == cae_serieRole){
        return documentos.cae_serie();
    }
    else if (role == comentariosRole){
        return documentos.comentarios();
    }

    return QVariant();
}


bool ModuloDocumentos::eliminarDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{

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

        // Elimina las lineas de articulo del documento
        if(eliminarLineaDocumento(_codigoDocumento,_codigoTipoDocumento,_serieDocumento)){

            // Elimina las lineas de medio de pago del documento
            if(func_medioDePago.eliminarLineaMedioDePagoDocumento(_codigoDocumento,_codigoTipoDocumento,_serieDocumento)){

                // Elimina el documento.
                if(query.exec("delete from Documentos where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")){

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
}

bool ModuloDocumentos::eliminarLineaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{

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

        if(query.exec("delete from DocumentosLineas where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")){

            return true;

        }else{
            return false;
        }
    }else{
        return false;
    }
}


bool ModuloDocumentos::actualizarDatoExtraLineaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _numeroLinea, QString _datoAModificar, QString _serieDocumento) const{

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

        if(query.exec("update DocumentosLineas set codigoArticuloBarras='"+_datoAModificar+"' where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_numeroLinea+"' and serieDocumento='"+_serieDocumento+"'   ")){

            return true;

        }else{
            return false;
        }
    }else{
        return false;
    }
}



int ModuloDocumentos::guardarDocumentos(QString _codigoDocumento,QString _codigoTipoDocumento,QString _serieDocumento, QString _codigoCliente,QString _tipoCliente ,

                                        QString _codigoMonedaDocumento , QString _fechaEmisionDocumento,

                                        QString _precioTotalVenta, QString _precioSubTotalVenta,QString _precioIvaVenta ,

                                        QString _codigoLiquidacion, QString _codigoVendedorComisiona,QString _usuarioAlta, QString _estadoFinalDocumento

                                        , QString _codigoVendedorLiquidacion,
                                        QString _totalIva1,
                                        QString _totalIva2,
                                        QString _totalIva3,
                                        QString _cotizacionMoneda,QString _observaciones,QString _comentarios,
                                        QString _numeroCuentaBancaria,int _codigoBancoCuentaBancaria,
                                        QString _montoDescuentoTotal, QString _precioSubTotalSinDescuento,
                                        QString _formaDePago,
                                        QString _porcentajeDescuentoAlTotal,
                                        QString _saldoClientePagoContado
                                        ) const {

    // -1  No se pudo conectar a la base de datos
    // -2  Documento con estado invalido
    //  1  documento dado de alta ok
    //  2  Documento actualizado correctamente
    // -3  no se pudo guardar el documento
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El documento no tiene los datos sufucientes para darse de alta.
    // -6 El documento existe cancelado.
    // -7 El documento existe como emitido/impreso/finalizado
    // -8 El documento existe como guardado/finalizado
    // -9 El documento existe en proceso de guardado, ATENCION.
    // -10 No se realizaron cambios en el documento existente como pendiente.


    if(_codigoDocumento.trimmed()=="" || _codigoTipoDocumento.trimmed()=="" || _serieDocumento.trimmed()==""){
        return -5;
    }



    QString esUnDocumentoDeCFE="0";

    if(func_configuracion.retornaValorConfiguracion("MODO_CFE")=="1" && func_tipoDocumentos.retornaPermisosDelDocumento(_codigoTipoDocumento,"emiteCFEImprime")){
        esUnDocumentoDeCFE="1";
    }

    if(_codigoLiquidacion==""){
        _codigoLiquidacion="0";
    }

    QString _tieneDescuentoAlTotal="0";

    if(!_montoDescuentoTotal.toDouble()==0.00){
        _tieneDescuentoAlTotal="1";
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

        if(_estadoFinalDocumento=="EMITIR"){

            if(query.exec("select codigoDocumento,codigoEstadoDocumento from Documentos where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")) {

                if(query.first()){
                    if(query.value(0).toString()!=""){

                        if(query.value(1).toString()=="C"){
                            return -6;
                        }else if(query.value(1).toString()=="E"){
                            return -7;
                        }else if(query.value(1).toString()=="G"){
                            return -8;
                        }else if(query.value(1).toString()=="A"){
                            return -9;
                        }else if(query.value(1).toString()=="P"){
                            if(funcion.mensajeAdvertencia("El documento ya existe guardado en estado pendiente.\nDesea guardarlo como finalizado?\n\nPresione [ Sí ] para confirmar.")){

                                if(query.exec("update Documentos set codigoEstadoDocumento='A',  codigoMonedaDocumento='"+_codigoMonedaDocumento+"',fechaUltimaModificacionDocumento='"+funcion.fechaHoraDeHoy()+"',fechaHoraGuardadoDocumentoSQL='"+funcion.fechaHoraDeHoy()+"  ', fechaEmisionDocumento='"+_fechaEmisionDocumento+"',usuarioUltimaModificacion='"+_usuarioAlta+"',precioTotalVenta='"+_precioTotalVenta+"',precioSubTotalVenta='"+_precioSubTotalVenta+"',precioSubTotalVentaSinDescuento='"+_precioSubTotalSinDescuento+"'     ,precioIvaVenta='"+_precioIvaVenta+"',codigoLiquidacion='"+_codigoLiquidacion+"',codigoVendedorComisiona='"+_codigoVendedorComisiona+"', codigoVendedorLiquidacion='"+_codigoVendedorLiquidacion+"', totalIva1='"+_totalIva1+"', totalIva2='"+_totalIva2+"', totalIva3='"+_totalIva3+"',cotizacionMoneda='"+_cotizacionMoneda+"',observaciones='"+_observaciones+"',comentarios='"+_comentarios+"',numeroCuentaBancaria='"+_numeroCuentaBancaria+"',codigoBanco='"+QString::number(_codigoBancoCuentaBancaria)+"', montoDescuentoTotal='"+_montoDescuentoTotal+"',tieneDescuentoAlTotal='"+_tieneDescuentoAlTotal+"',saldoClienteCuentaCorriente='"+_precioTotalVenta+"',formaDePago='"+_formaDePago+"',porcentajeDescuentoAlTotal='"+_porcentajeDescuentoAlTotal+"',saldoClientePagoContado='"+_saldoClientePagoContado+"',esDocumentoCFE='"+esUnDocumentoDeCFE+"'          where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"' ")){
                                    return 1;
                                }else{
                                    funcion.mensajeAdvertencia(query.lastError().text());
                                    funcion.mensajeAdvertencia(query.lastQuery());
                                    return -3;
                                }
                            }else{
                                return -10;
                            }
                        }else{
                            return -2;
                        }
                    }else{return -4;}
                }else{
                    if(query.exec("insert INTO Documentos (codigoDocumento, codigoTipoDocumento, serieDocumento, codigoEstadoDocumento, codigoCliente, tipoCliente, codigoMonedaDocumento, fechaEmisionDocumento, precioTotalVenta,precioSubTotalVenta, precioIvaVenta, codigoLiquidacion, codigoVendedorComisiona, usuarioAlta,codigoVendedorLiquidacion,totalIva1,totalIva2,totalIva3,cotizacionMoneda,observaciones,comentarios,numeroCuentaBancaria,codigoBanco,montoDescuentoTotal,tieneDescuentoAlTotal,precioSubTotalVentaSinDescuento,saldoClienteCuentaCorriente,formaDePago,porcentajeDescuentoAlTotal,saldoClientePagoContado,esDocumentoCFE,documentoEnviadoPorMail,fechaUltimaModificacionDocumento) values('"+_codigoDocumento+"','"+_codigoTipoDocumento+"','"+_serieDocumento+"','A','"+_codigoCliente+"','"+_tipoCliente+"','"+_codigoMonedaDocumento+"','"+_fechaEmisionDocumento+"','"+_precioTotalVenta+"','"+_precioSubTotalVenta+"','"+_precioIvaVenta+"','"+_codigoLiquidacion+"','"+_codigoVendedorComisiona+"','"+_usuarioAlta+"','"+_codigoVendedorLiquidacion+"','"+_totalIva1+"','"+_totalIva2+"','"+_totalIva3+"','"+_cotizacionMoneda+"','"+_observaciones+"','"+_comentarios+"','"+_numeroCuentaBancaria+"','"+QString::number(_codigoBancoCuentaBancaria)+"','"+_montoDescuentoTotal+"','"+_tieneDescuentoAlTotal+"','"+_precioSubTotalSinDescuento+"','"+_precioTotalVenta+"','"+_formaDePago+"','"+_porcentajeDescuentoAlTotal+"','"+_saldoClientePagoContado+"','"+esUnDocumentoDeCFE+"',0,'"+funcion.fechaHoraDeHoy()+"' )")){
                        return 1;
                    }else{
                        funcion.mensajeAdvertencia(query.lastError().text());
                        funcion.mensajeAdvertencia(query.lastQuery());
                        return -3;
                    }
                }
            }else{
                return -4;
            }
        }else if(_estadoFinalDocumento=="PENDIENTE"){
            if(query.exec("select codigoDocumento,codigoEstadoDocumento from Documentos where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")) {

                if(query.first()){
                    if(query.value(0).toString()!=""){

                        if(query.value(1).toString()=="C"){
                            return -6;
                        }else if(query.value(1).toString()=="E"){
                            return -7;
                        }else if(query.value(1).toString()=="G"){
                            return -8;
                        }else if(query.value(1).toString()=="A"){
                            return -9;
                        }else if(query.value(1).toString()=="P"){
                            if(funcion.mensajeAdvertencia("El documento ya existe guardado en estado pendiente.\nDesea actualizarlo?\n\nPresione [ Sí ] para confirmar.")){

                                if(query.exec("update Documentos set codigoMonedaDocumento='"+_codigoMonedaDocumento+"',fechaUltimaModificacionDocumento='"+funcion.fechaHoraDeHoy()+"', fechaEmisionDocumento='"+_fechaEmisionDocumento+"',usuarioUltimaModificacion='"+_usuarioAlta+"',precioTotalVenta='"+_precioTotalVenta+"',precioSubTotalVenta='"+_precioSubTotalVenta+"',precioSubTotalVentaSinDescuento='"+_precioSubTotalSinDescuento+"'  ,precioIvaVenta='"+_precioIvaVenta+"',codigoLiquidacion='"+_codigoLiquidacion+"',codigoVendedorComisiona='"+_codigoVendedorComisiona+"',codigoVendedorLiquidacion='"+_codigoVendedorLiquidacion+"', totalIva1='"+_totalIva1+"', totalIva2='"+_totalIva2+"', totalIva3='"+_totalIva3+"',cotizacionMoneda='"+_cotizacionMoneda+"',observaciones='"+_observaciones+"',comentarios='"+_comentarios+"',numeroCuentaBancaria='"+_numeroCuentaBancaria+"',codigoBanco='"+QString::number(_codigoBancoCuentaBancaria)+"', montoDescuentoTotal="+_montoDescuentoTotal+",tieneDescuentoAlTotal='"+_tieneDescuentoAlTotal+"',saldoClienteCuentaCorriente='"+_precioTotalVenta+"',formaDePago='"+_formaDePago+"',porcentajeDescuentoAlTotal='"+_porcentajeDescuentoAlTotal+"',saldoClientePagoContado='"+_saldoClientePagoContado+"'    where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")){
                                    return 1;
                                }else{
                                    funcion.mensajeAdvertencia(query.lastError().text());
                                    funcion.mensajeAdvertencia(query.lastQuery());
                                    return -3;
                                }
                            }else{
                                return -10;
                            }
                        }else{
                            return -2;
                        }
                    }else{return -4;}
                }else{

                    if(query.exec("insert INTO Documentos (codigoDocumento, codigoTipoDocumento, serieDocumento, codigoEstadoDocumento, codigoCliente, tipoCliente, codigoMonedaDocumento, fechaEmisionDocumento, precioTotalVenta,precioSubTotalVenta, precioIvaVenta, codigoLiquidacion, codigoVendedorComisiona, usuarioAlta,codigoVendedorLiquidacion,totalIva1,totalIva2,totalIva3,cotizacionMoneda,observaciones,comentarios,numeroCuentaBancaria,codigoBanco,montoDescuentoTotal,tieneDescuentoAlTotal,precioSubTotalVentaSinDescuento,saldoClienteCuentaCorriente,formaDePago,porcentajeDescuentoAlTotal,saldoClientePagoContado,esDocumentoCFE,documentoEnviadoPorMail,fechaUltimaModificacionDocumento) values('"+_codigoDocumento+"','"+_codigoTipoDocumento+"','"+_serieDocumento+"','P','"+_codigoCliente+"','"+_tipoCliente+"','"+_codigoMonedaDocumento+"','"+_fechaEmisionDocumento+"','"+_precioTotalVenta+"','"+_precioSubTotalVenta+"','"+_precioIvaVenta+"','"+_codigoLiquidacion+"','"+_codigoVendedorComisiona+"','"+_usuarioAlta+"','"+_codigoVendedorLiquidacion+"','"+_totalIva1+"','"+_totalIva2+"','"+_totalIva3+"','"+_cotizacionMoneda+"','"+_observaciones+"','"+_comentarios+"','"+_numeroCuentaBancaria+"','"+QString::number(_codigoBancoCuentaBancaria)+"','"+_montoDescuentoTotal+"','"+_tieneDescuentoAlTotal+"','"+_precioSubTotalSinDescuento+"','"+_precioTotalVenta+"','"+_formaDePago+"','"+_porcentajeDescuentoAlTotal+"','"+_saldoClientePagoContado+"','"+esUnDocumentoDeCFE+"',0,'"+funcion.fechaHoraDeHoy()+"'    )")){
                        return 1;
                    }else{
                        funcion.mensajeAdvertencia(query.lastError().text());
                        funcion.mensajeAdvertencia(query.lastQuery());
                        return -3;
                    }
                }
            }else{
                return -4;
            }
        }
    }else{
        return -1;
    }
}

bool ModuloDocumentos::guardarLineaDocumento(QString _consultaInsertLineas) const {

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

        if(query.exec(_consultaInsertLineas)){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

void ModuloDocumentos::marcoArticulosincronizarWeb(QString _codigoArticulo) const {

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
        if(query.exec("update Articulos set sincronizadoWebStock='0' where codigoArticulo='"+_codigoArticulo+"';")){

        }
    }
}




bool ModuloDocumentos::anuloMontosDebitadosCuentaCorriente(QString _codigoDocumentoDePago, QString _codigoTipoDocumentoDePago, QString _serieDocumentoQueCancela) const {

    bool actualizacionCorrecta=true;

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

        if(query.exec("SELECT  codigoDocumento,codigoTipoDocumento,montoDescontadoCuentaCorriente,serieDocumento   FROM DocumentosCanceladosCuentaCorriente where codigoDocumentoQueCancela='"+_codigoDocumentoDePago+"' and codigoTipoDocumentoQueCancela='"+_codigoTipoDocumentoDePago+"' and serieDocumentoQueCancela='"+_serieDocumentoQueCancela+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    query.previous();
                    while (query.next()){

                        if(restauroMontoDeudaCuentaCorrienteDocumento(query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString())==false){
                            actualizacionCorrecta==false;
                            break;
                        }

                    }
                    return actualizacionCorrecta;
                }else{
                    return true;
                }
            }else {return true;}
        }else{
            return false;
        }
    }else{
        qDebug()<<"No se puede conectar a mysql server";
        return false;
    }

}

bool ModuloDocumentos::restauroMontoDeudaCuentaCorrienteDocumento(QString _codigoDocumentoAPagar, QString _codigoTipoDocumentoAPagar,QString _montoADebitar, QString _serieDocumento) const {

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

        ///Actualizo el documento de venta(factura credito, ajuste cuenta corriente +)
        if(query.exec("update Documentos set fechaUltimaModificacionDocumento='"+funcion.fechaHoraDeHoy()+"',saldoClienteCuentaCorriente=saldoClienteCuentaCorriente+"+_montoADebitar+" where codigoDocumento="+_codigoDocumentoAPagar+" and codigoTipoDocumento="+_codigoTipoDocumentoAPagar+" and serieDocumento='"+_serieDocumento+"'  ")){
            return true;
        }else{
            qDebug()<< query.lastError();
            return false;
        }
    }else{
        qDebug()<<"No se puede conectar a mysql server";
        return false;
    }
}

int ModuloDocumentos::actualizarCuentaCorriente(QString _codigoDocumentoAPagar, QString _codigoTipoDocumentoAPagar, QString _codigoClienteAPagar, QString _codigoTipoClienteAPagar, QString _codigoMonedaAPagar
                                                ,QString _codigoDocumentoDePago, QString _codigoTipoDocumentoDePago, QString _codigoClienteDePago, QString _codigoTipoClienteDePago, QString _codigoMonedaDePago,
                                                QString _montoADebitar,QString _montoDelSaldo,
                                                QString _serieDocumentoAPagar, QString _serieDocumentoDePago
                                                ) const {
    /// -5 Atencion, error al actualizar el documento de pago, y no se pudo restaurar el documento original, esto provoca incongruencias en el sistema
    /// -4 Datos no concuerdan para realizar la actualización
    /// -3 - Error en monto a debitar
    /// -2 - Error al actualizar el documento de pago
    /// -1 - Error al actualizar el documento a pagar
    /// 0 - Error en conexion a mysql server
    /// 1 - Actualizado con exito



    if(_montoADebitar=="0.00" || _montoADebitar=="0" || _montoADebitar=="0.0" || _montoADebitar=="0."|| _montoADebitar==".00" || _montoADebitar==".0"){
        return -3;
    }else{
        if(_codigoClienteAPagar!=_codigoClienteDePago || _codigoTipoClienteAPagar!=_codigoTipoClienteDePago || _codigoMonedaAPagar!=_codigoMonedaDePago){
            return -4;
        }
    }

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            //qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery query(Database::connect());

        ///Actualizo el documento de venta(factura credito, ajuste cuenta corriente +)
        if(query.exec("update Documentos set fechaUltimaModificacionDocumento='"+funcion.fechaHoraDeHoy()+"',saldoClienteCuentaCorriente=saldoClienteCuentaCorriente-"+_montoADebitar+" where codigoDocumento="+_codigoDocumentoAPagar+" and codigoTipoDocumento="+_codigoTipoDocumentoAPagar+"  and serieDocumento='"+_serieDocumentoAPagar+"'   and codigoCliente='"+_codigoClienteAPagar+"' and tipoCliente="+_codigoTipoClienteAPagar+" and codigoMonedaDocumento="+_codigoMonedaAPagar+"")){
            //qDebug() << query.lastQuery();
            //qDebug() << "1";
            query.clear();
            ///Actualizo el documento de pago(recibo, nota de credito, ajuste cuenta corriente -)
            if(query.exec("update Documentos set fechaUltimaModificacionDocumento='"+funcion.fechaHoraDeHoy()+"',saldoClienteCuentaCorriente=saldoClienteCuentaCorriente-"+_montoADebitar+" where codigoDocumento="+_codigoDocumentoDePago+" and codigoTipoDocumento="+_codigoTipoDocumentoDePago+" and serieDocumento='"+_serieDocumentoDePago+"'   and codigoCliente='"+_codigoClienteDePago+"' and tipoCliente="+_codigoTipoClienteDePago+" and codigoMonedaDocumento="+_codigoMonedaDePago+"")){
                //qDebug() << query.lastQuery();
                //qDebug() << "2";
                query.clear();
                ///Inserto las referencias de pago en la base de datos
                if(query.exec("insert into DocumentosCanceladosCuentaCorriente(codigoDocumento,codigoTipoDocumento,serieDocumento ,codigoDocumentoQueCancela,codigoTipoDocumentoQueCancela,serieDocumentoQueCancela,montoDescontadoCuentaCorriente)values('"+_codigoDocumentoAPagar+"','"+_codigoTipoDocumentoAPagar+"','"+_serieDocumentoAPagar+"','"+_codigoDocumentoDePago+"','"+_codigoTipoDocumentoDePago+"','"+_serieDocumentoDePago+"',"+_montoADebitar+");")){
                    funcion.loguear("Inserto DocumentosCanceladosCuentaCorriente: "+query.lastQuery());
                    //   qDebug() << query.lastQuery();
                    //  qDebug() << "3";
                    return 1;
                }else{
                    //  qDebug()<< "Insert";
                    //  qDebug()<< query.lastError();
                    funcion.mensajeAdvertencia(query.lastError().text());
                    funcion.mensajeAdvertencia(query.lastQuery());
                    return -5;
                }
            }else{

                funcion.mensajeAdvertencia(query.lastQuery());
                //qDebug()<< query.lastError();
                query.clear();
                if(query.exec("update Documentos set fechaUltimaModificacionDocumento='"+funcion.fechaHoraDeHoy()+"',saldoClienteCuentaCorriente="+_montoDelSaldo+" where codigoDocumento="+_codigoDocumentoAPagar+" and codigoTipoDocumento="+_codigoTipoDocumentoAPagar+" and serieDocumento='"+_serieDocumentoAPagar+"' and codigoCliente='"+_codigoClienteAPagar+"' and tipoCliente="+_codigoTipoClienteAPagar+" and codigoMonedaDocumento="+_codigoMonedaAPagar+";")){
                    //  qDebug()<< "update 1";
                    // qDebug()<< query.lastError();
                    return -2;
                }else{
                    // qDebug()<< "update 2";
                    // qDebug()<< query.lastError();
                    funcion.mensajeAdvertencia(query.lastError().text());
                    funcion.mensajeAdvertencia(query.lastQuery());
                    return -5;
                }
            }
        }else{
            //  qDebug()<< "update 3";
            //  qDebug()<< query.lastError();
            funcion.mensajeAdvertencia(query.lastError().text());
            funcion.mensajeAdvertencia(query.lastQuery());
            return -1;
        }
    }else{
        //qDebug()<<"No se puede conectar a mysql server";
        return 0;
    }
}

bool ModuloDocumentos::actualizoEstadoDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _estadoDocumento ,QString _usuarioAlta, QString _serieDocumento , QString _codigoCliente,QString _tipoCliente, QString _codigoMoneda  ) const {


    if(_codigoDocumento.trimmed()=="" || _codigoTipoDocumento.trimmed()=="" ){
        return false;
    }
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

        if(query.exec("update Documentos set fechaUltimaModificacionDocumento='"+funcion.fechaHoraDeHoy()+"',codigoEstadoDocumento='"+_estadoDocumento+"' ,usuarioUltimaModificacion='"+_usuarioAlta+"' where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")){

            // Aca me preparo para actualizar el saldo del documento
            if(_estadoDocumento=="G" || _estadoDocumento=="E"){
                QString  afectaCuentaCorriente = func_tipoDocumentos.retornaValorCampoTipoDocumento(_codigoTipoDocumento,"afectaCuentaCorriente");
                if(afectaCuentaCorriente!="0" && afectaCuentaCorriente!=""){
                    // Obtengo el saldo del cliente
                    if(query.exec("select  sum(case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(DOC.precioTotalVenta*-1,2) end) AS Saldo            from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where  DOC.tipoCliente='"+_tipoCliente+"' and DOC.codigoEstadoDocumento in ('E','G')  and TDOC.afectaCuentaCorriente!=0  and DOC.codigoCliente='"+_codigoCliente+"'  and DOC.codigoMonedaDocumento='"+_codigoMoneda+"' ;")) {
                        if(query.first()){
                            if(query.value(0).toString()!=""){
                                if(query.exec("update Documentos set fechaUltimaModificacionDocumento='"+funcion.fechaHoraDeHoy()+"', nuevoSaldo='"+query.value(0).toString()+"'  where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")){
                                    return true;
                                }
                            }
                        }
                    }
                }
            }else if(_estadoDocumento=="C"){
                // Si cancelo una factura, tengo que modificar el saldo en el ultimo documento del cliente que afecta la cuenta corriente
                QString  afectaCuentaCorriente = func_tipoDocumentos.retornaValorCampoTipoDocumento(_codigoTipoDocumento,"afectaCuentaCorriente");
                if(afectaCuentaCorriente!="0" && afectaCuentaCorriente!=""){
                    // Obtengo el saldo del cliente
                    if(query.exec("select  sum(case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(DOC.precioTotalVenta*-1,2) end) AS Saldo            from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where  DOC.tipoCliente='"+_tipoCliente+"' and DOC.codigoEstadoDocumento in ('E','G')  and TDOC.afectaCuentaCorriente!=0  and DOC.codigoCliente='"+_codigoCliente+"'  and DOC.codigoMonedaDocumento='"+_codigoMoneda+"' ;")) {
                        if(query.first()){
                            if(query.value(0).toString()!=""){
                                if(query.exec("update Documentos DOC join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento  set DOC.fechaUltimaModificacionDocumento='"+funcion.fechaHoraDeHoy()+"', DOC.nuevoSaldo='"+query.value(0).toString()+"' where DOC.codigoCliente='"+_codigoCliente+"' and DOC.tipoCliente='"+_tipoCliente+"' and DOC.codigoMonedaDocumento='"+_codigoMoneda+"' and DOC.codigoEstadoDocumento in ('E','G')   and   TD.afectaCuentaCorriente!=0  order by DOC.fechaHoraGuardadoDocumentoSQL DESC limit 1;")){
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}


bool ModuloDocumentos::actualizoEstadoDocumentoCFE(QString _codigoDocumento,QString _codigoTipoDocumento, QString _estadoDocumento, QString _serieDocumento) const {


    if(_codigoDocumento.trimmed()=="" || _codigoTipoDocumento.trimmed()=="" ){
        return false;
    }
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

        if(query.exec("update Documentos set fechaUltimaModificacionDocumento='"+funcion.fechaHoraDeHoy()+"',codigoEstadoDocumento='"+_estadoDocumento+"'  where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}


bool ModuloDocumentos::actualizoSaldoClientePagoContadoDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _saldoClientePagoContado, QString _serieDocumento) const {


    if(_codigoDocumento.trimmed()=="" || _codigoTipoDocumento.trimmed()=="" ){
        return false;
    }
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
        if(query.exec("update Documentos set fechaUltimaModificacionDocumento='"+funcion.fechaHoraDeHoy()+"',saldoClientePagoContado='"+_saldoClientePagoContado+"'  where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}



bool ModuloDocumentos::actualizoComentarios(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento,QString _comentarios   ) const {


    if(_codigoDocumento.trimmed()=="" || _codigoTipoDocumento.trimmed()=="" ){
        return false;
    }
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

        if(query.exec("update Documentos set fechaUltimaModificacionDocumento='"+funcion.fechaHoraDeHoy()+"',comentarios='"+_comentarios+"'  where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

int ModuloDocumentos::retornaCantidadLineasDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{
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

        if(query.exec("SELECT count(*) FROM DocumentosLineas where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){
                    return query.value(0).toInt();
                }else{
                    return 0;
                }
            }else {return 0;}
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

QString ModuloDocumentos::retornoCodigoArticuloDeLineaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT codigoArticulo FROM DocumentosLineas where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"' and serieDocumento='"+_serieDocumento+"'")) {
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

QString ModuloDocumentos::retornoCantidadDocumentosPorCliente(QString _codigoCliente,QString _codigoTipoCliente, QString _estadoDocumentos) {
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

        if(_estadoDocumentos=="ANULADOS"){
            if(query.exec("select count(*) from Documentos where codigoCliente ='"+_codigoCliente+"'   and tipoCliente='"+_codigoTipoCliente+"' and codigoEstadoDocumento in ('C')")) {
                if(query.first()){
                    if(query.value(0).toString()!=0){
                        return query.value(0).toString();
                    }else{
                        return "0";
                    }
                }else{return "0";}
            }else{
                return "0";
            }
        }else{
            if(query.exec("select count(*) from Documentos where codigoCliente ='"+_codigoCliente+"'   and tipoCliente='"+_codigoTipoCliente+"' and codigoEstadoDocumento in ('E','G')")) {
                if(query.first()){
                    if(query.value(0).toString()!=0){
                        return query.value(0).toString();
                    }else{
                        return "0";
                    }
                }else{return "0";}
            }else{
                return "0";
            }
        }
    }else{
        return "0";
    }
}

QString ModuloDocumentos::retornoCodigoArticuloBarrasDeLineaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT codigoArticuloBarras FROM DocumentosLineas where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"' and serieDocumento='"+_serieDocumento+"'")) {
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

double ModuloDocumentos::retornoPrecioArticuloDeLineaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT precioArticuloUnitario FROM DocumentosLineas where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"' and serieDocumento='"+_serieDocumento+"'")) {
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

double ModuloDocumentos::retornoCostoArticuloMonedaReferenciaDeLineaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea,QString _serieDocumento) {
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

        if(query.exec("SELECT costoArticuloMonedaReferencia FROM DocumentosLineas where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"' and serieDocumento='"+_serieDocumento+"'")) {
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


double ModuloDocumentos::retornoDescuentoLineaArticuloDeLineaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT montoDescuento FROM DocumentosLineas where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"' and serieDocumento='"+_serieDocumento+"'")) {
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

QString ModuloDocumentos::retornoCodigoTipoGarantiaLineaArticuloDeLineaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT codigoTipoGarantia FROM DocumentosLineas where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"' and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){
                    return query.value(0).toString();
                }else{
                    return "0";
                }
            }else{return "0";}
        }else{
            return "0";
        }
    }else{
        return "0";
    }
}


int ModuloDocumentos::retornoCantidadArticuloDeLineaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _linea, QString _serieDocumento) {
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

        if(query.exec("SELECT cantidad FROM DocumentosLineas where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and numeroLinea='"+_linea+"' and serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){
                    return query.value(0).toInt();
                }else{
                    return 1;
                }
            }else{return 1;}
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}

qlonglong ModuloDocumentos::retornoCodigoUltimoDocumentoDisponible(QString _codigoTipoDocumento) {
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
        if(query.exec("SELECT DOC.codigoDocumento FROM Documentos DOC join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento where DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento=TD.serieDocumento order by DOC.codigoDocumento desc limit 1")) {

            if(query.first()){
                if(query.value(0).toString()!=0){
                    return query.value(0).toLongLong()+1;
                }else{
                    return 1;
                }
            }else{return 1;}
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}

QString ModuloDocumentos::retornacodigoEstadoDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{
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
        if(query.exec("select DOC.codigoEstadoDocumento from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {
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

QString ModuloDocumentos::retornaDescripcionEstadoDocumento(QString _codigoEstado) const{
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
        if(query.exec("SELECT codigoEstadoDocumento,descripcionEstadoDocumento FROM TipoEstadoDocumento where codigoEstadoDocumento='"+_codigoEstado+"';")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    return query.value(1).toString();
                }else{
                    return "Nuevo";
                }
            }else{return "Nuevo";}
        }else{
            return "Nuevo";
        }
    }else{
        return "Nuevo";
    }
}

bool ModuloDocumentos::retornaClienteTieneRUT(QString _codigoCliente,QString _codigoTipoCliente) const{
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
        if(query.exec("select rut,codigoTipoDocumentoCliente from Clientes where codigoCliente='"+_codigoCliente+"' and tipoCliente='"+_codigoTipoCliente+"' limit 1")) {
            if(query.first()){
                if(query.value(1).toString()=="2"){
                    if(query.value(0).toString()=="" || query.value(0).toString().toLower().trimmed() =="null" || query.value(0).toString().isNull() || query.value(0).toString().isEmpty()){
                        return false;
                    }else{
                        return true;
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

bool ModuloDocumentos::documentoValidoParaCalculoPonderado(QString _codigoTipoDocumento)const{
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
        if(query.exec("SELECT * FROM TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"' and utilizaArticulos=1 and afectaStock=1 and utilizaSoloProveedores=1")) {
            if(query.first()){
                if(query.value(0).toString()=="" || query.value(0).toString().toLower().trimmed() =="null" || query.value(0).toString().isNull() || query.value(0).toString().isEmpty()){
                    return false;
                }else{
                    return true;
                }
            }else{return false;}
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool ModuloDocumentos::retornoSiClienteTieneDocumentos(QString _codigoCliente)const{
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
        if(query.exec("SELECT codigoDocumento FROM Documentos where codigoCliente ='"+_codigoCliente+"' ")) {
            if(query.first()){
                if(query.value(0).toString()=="" || query.value(0).toString().toLower().trimmed() =="null" || query.value(0).toString().isNull() || query.value(0).toString().isEmpty()){
                    return false;
                }else{
                    return true;
                }
            }else{return false;}
        }else{
            return true;
        }
    }else{
        return true;
    }
}

double ModuloDocumentos::retonaCostoPonderadoSegunStock(QString _codigoArticulo, qlonglong _cantidad, double _costoArticuloUnitario) const {

    double totalCostoDelArticulo=_costoArticuloUnitario*_cantidad;

    qlonglong stockTotalArticulo=func_articulos.retornaStockTotalArticulo(_codigoArticulo);

    if(stockTotalArticulo == 0){
        return _costoArticuloUnitario;
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

        if(query.exec("SELECT DL.costoArticuloPonderado FROM DocumentosLineas DL join Documentos DOC on DOC.codigoDocumento=DL.codigoDocumento and DOC.codigoTipoDocumento=DL.codigoTipoDocumento join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento where DOC.codigoEstadoDocumento in ('G','E') and TD.utilizaArticulos=1 and TD.afectaStock=1 and TD.utilizaSoloProveedores=1 and DL.codigoArticulo='"+_codigoArticulo+"' order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1 ")) {
            if(query.first()){
                if(query.value(0).toString()!=0){

                    double totalCostoPonderado=query.value(0).toDouble()*stockTotalArticulo;

                    double totalCostoDeTodoElStock=totalCostoPonderado+totalCostoDelArticulo;

                    return totalCostoDeTodoElStock/(_cantidad+stockTotalArticulo);

                }else{
                    return _costoArticuloUnitario;
                }
            }else{
                return _costoArticuloUnitario;
            }
        }else{
            return _costoArticuloUnitario;
        }
    }else{
        return _costoArticuloUnitario;
    }
}



bool ModuloDocumentos::actualizarInformacionCFEDocumentoDynamia(QString _codigoDocumento, QString _codigoTipoDocumento, QString  _nro,
                                                                QString _serie, QString _vencimiento,
                                                                QString _cod_seguridad, QString _cae_id,
                                                                QString _desde, QString _hasta,
                                                                QString _qr, QString _idDocGaia,
                                                                QString _caeTipoDocumentoCFEDescripcion,
                                                                QString _serieDocumento
                                                                ){

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
        if(query.exec("update Documentos set fechaUltimaModificacionDocumento='"+funcion.fechaHoraDeHoy()+"',cae_numeroCae='"+_nro+"',cae_serie='"+_serie+"',cae_fechaVencimiento='"+_vencimiento+"',cae_codigoSeguridad='"+_cod_seguridad+"',cae_Cae='"+_cae_id+"',cae_rangoDesde='"+_desde+"',cae_rangoHasta='"+_hasta+"',cae_QrCode='"+_qr+"',cae_idDocGaia='"+_idDocGaia+"',caeTipoDocumentoCFEDescripcion='"+_caeTipoDocumentoCFEDescripcion+"'   where codigoDocumento='"+_codigoDocumento+"' and codigoTipoDocumento='"+_codigoTipoDocumento+"' and serieDocumento='"+_serieDocumento+"'")){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }



}




QString ModuloDocumentos::retornatipoClienteDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.tipoCliente from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornacodigoClienteDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.codigoCliente from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}


QString ModuloDocumentos::retornaserieDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.serieDocumento from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornacodigoVendedorComisionaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.codigoVendedorComisiona from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornacodigoLiquidacionDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.codigoLiquidacion from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornacodigoVendedorLiquidacionDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.codigoVendedorLiquidacion from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornafechaEmisionDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.fechaEmisionDocumento from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornacodigoMonedaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.codigoMonedaDocumento from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornaprecioIvaVentaDocumento    (QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.precioIvaVenta from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornaprecioSubTotalVentaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.precioSubTotalVenta from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornaprecioTotalVentaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.precioTotalVenta from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornatotalIva1Documento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.totalIva1 from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornatotalIva2Documento  (QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.totalIva2 from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornatotalIva3Documento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.totalIva3 from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornaobservacionesDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.observaciones from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornacomentariosDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.comentarios from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornaonumeroCuentaBancariaDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.numeroCuentaBancaria from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornaocodigoBancoDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.codigoBanco from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornaEsDocumentoWebDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.esDocumentoWeb from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornaMontoDescuentoTotalDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.montoDescuentoTotal from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornaFormaDePagoDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.formaDePago from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornaPorcentajeDescuentoAlTotalDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.porcentajeDescuentoAlTotal from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}

QString ModuloDocumentos::retornaEsDocumentoCFEDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{    bool conexion=true;    if(!Database::connect().isOpen()){        if(!Database::connect().open()){            qDebug() << "No conecto";            conexion=false;        }    }    if(conexion){        QSqlQuery query(Database::connect());
        if(query.exec("select DOC.esDocumentoCFE from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {            if(query.first()){                if(query.value(0).toString()!=""){                    return query.value(0).toString();                }else{                    return  "";                }            }else{return "Error BD";}        }else{            return "Error SQL";        }    }else{        return "Error BD";    }}


QString ModuloDocumentos::retornaNumeroCFEOriginal(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{


    bool conexion=true;


    if(!Database::connect().isOpen()){

        if(!Database::connect().open()){

            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery query(Database::connect());

        if(query.exec("select DOC.cae_numeroCae from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")){
            if(query.first()){
                if(query.value(0).toString()!=""){
                    return query.value(0).toString();
                }else{
                    return  "";
                }
            }
            else{
                return "Error BD";
            }
        }else{
            return "Error SQL";
        }
    }else{
        return "Error BD";
    }
}



bool ModuloDocumentos::existeDocumento(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento) const{


    bool conexion=true;


    if(!Database::connect().isOpen()){

        if(!Database::connect().open()){

            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){
        QSqlQuery query(Database::connect());

        if(query.exec("select DOC.codigoDocumento from Documentos DOC  where DOC.codigoDocumento='"+_codigoDocumento+"'  and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")){
            if(query.first()){
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
}



bool ModuloDocumentos::emitirEnvioEnImpresoraTicket(QString _codigoTipoImpresion,QString _impresora, QString _codigoCliente, QString _tipoCliente, QString _observacion){

    //##################################################
    // Preparo los seteos de la impresora ##############
    QPrinter printer;
    printer.setPrinterName(_impresora);

    printer.setFullPage(true);
    centimetro = printer.QPaintDevice::width()/(printer.QPaintDevice::widthMM()/10);
    fuente.setPointSize(8);


    QString consultaSql = "select C.codigoCliente,C.nombreCliente,C.direccion, C.esquina,C.numeroPuerta,C.telefono, C.telefono2,C.horario,D.descripcionDepartamento,L.descripcionLocalidad, C.rut from Clientes C  join Departamentos D on D.codigoDepartamento=C.codigoDepartamento and D.codigoPais=C.codigoPais  join Localidades L on L.codigoDepartamento=C.codigoDepartamento and L.codigoPais=C.codigoPais and L.codigoLocalidad=C.codigoLocalidad  where C.codigoCliente="+_codigoCliente+" and C.tipoCliente="+_tipoCliente+";";


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

        if(query.exec(consultaSql)) {
            if(query.first()){

                QString codigoCliente=query.value(0).toString();
                QString nombreCliente=query.value(1).toString();
                QString direccion=query.value(2).toString();
                QString esquina=query.value(3).toString();
                QString numeroPuerta=query.value(4).toString();
                QString telefono=query.value(5).toString();
                QString telefono2=query.value(6).toString();
                QString horario=query.value(7).toString();
                QString departamento=query.value(8).toString();
                QString localidad=query.value(9).toString();
                QString rut=query.value(10).toString();

                if (!painter.begin(&printer)) {
                    return false;
                }
                painter.setFont(fuente);


                double desplazamientoLogo=0.0;

                fuente.setBold(true);
                fuente.setPointSize(10);
                fuente.setUnderline(true);
                painter.setFont(fuente);
                painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"¡ABRIR EL PAQUETE EN AGENCIA");
                desplazamientoLogo+=0.5;
                painter.drawText(cuadroTicketRight(6.0,1.0+desplazamientoLogo,8.0,0.5,"O FRENTE AL CADETE!"),"O FRENTE AL CADETE!");

                fuente.setPointSize(8);
                fuente.setUnderline(false);
                fuente.setBold(false);
                painter.setFont(fuente);

                desplazamientoLogo+=0.5;
                fuente.setPointSize(8);
                painter.setFont(fuente);
                painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"ANTE POSIBLES RECLAMOS POR ROTURA");
                desplazamientoLogo+=1.0;

                fuente.setBold(true);
                fuente.setPointSize(9);
                fuente.setUnderline(true);
                painter.setFont(fuente);

                painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"  ESTE LADO HACIA ARRIBA SIEMPRE  ");

                fuente.setBold(false);
                fuente.setUnderline(false);
                painter.setFont(fuente);

                desplazamientoLogo+=0.7;

                // Se imprime una linea separadora
                fuente.setBold(true);
                painter.setFont(fuente);
                painter.drawText( cuadro(0.0,1.0+desplazamientoLogo,8.0,0.5,false), "____________________________________________");
                fuente.setBold(false);
                painter.setFont(fuente);

                desplazamientoLogo+=0.7;

                // Codigo cliente
                painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"Cliente: "+codigoCliente);
                // Nombre cliente
                desplazamientoLogo+=0.5;
                painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),nombreCliente);
                //painter.drawText(cuadroTicketRight(7.0,1.0+desplazamientoLogo,8.0,0.5,nombreCliente),nombreCliente);

                desplazamientoLogo+=0.5;

                // Cadeteria
                if(_codigoTipoImpresion=="2"){

                    painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"Dirección: "+direccion);
                    desplazamientoLogo+=0.5;
                    painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"Telefono: "+telefono);
                    desplazamientoLogo+=0.5;
                    painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"Telefono 2: "+telefono2);
                    desplazamientoLogo+=0.5;
                    painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"Hora entrega: "+horario);
                }else if(_codigoTipoImpresion=="3"){

                    painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"Rut: "+rut);
                    desplazamientoLogo+=0.5;
                    painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"Dirección: "+direccion);
                    desplazamientoLogo+=0.5;
                    painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"Telefono: "+telefono);
                    desplazamientoLogo+=0.5;
                    painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"Telefono 2: "+telefono2);
                    desplazamientoLogo+=0.5;
                    painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"Ciudad: "+localidad);
                    desplazamientoLogo+=0.5;
                    painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"Departamento: "+departamento);
                    desplazamientoLogo+=0.5;
                    painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"Hora entrega: "+horario);
                    desplazamientoLogo+=0.5;
                    painter.drawText(cuadro(0.5,2.0+desplazamientoLogo,8.0,0.5,false),"Agencia: "+_observacion);

                }






                desplazamientoLogo+=2;
                // Se imprime una linea separadora
                fuente.setBold(true);
                painter.setFont(fuente);
                painter.drawText( cuadro(0.0,1.0+desplazamientoLogo,8.0,0.5,false), "____________________________________________");
                fuente.setBold(false);
                painter.setFont(fuente);


                QString fragilImagen="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";
                //Imprimo imagen fragil
                QImage imagenLogoFragil;
                imagenLogoFragil.loadFromData(QByteArray::fromBase64(fragilImagen.toAscii()));
                painter.drawImage(cuadro(0.5,2.0+desplazamientoLogo,6.5,2.8,false), imagenLogoFragil);

                desplazamientoLogo+=4;


                QString logoEmpresa="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";


                //Imprimo detalle de ivas
                QImage imagenLogoEmpresa;
                imagenLogoEmpresa.loadFromData(QByteArray::fromBase64(logoEmpresa.toAscii()));
                painter.drawImage(cuadro(0.5,2.0+desplazamientoLogo,6.5,2.8,false), imagenLogoEmpresa);
                desplazamientoLogo+=4.5;

                painter.drawText(cuadroTicketRight(8.0,1.0+desplazamientoLogo,7.0,0.5,"29021052 / 29082199"),"29021052 / 29082199");
                desplazamientoLogo+=0.5;
                painter.drawText(cuadroTicketRight(7.0,1.0+desplazamientoLogo,8.0,0.5,"PAYSANDÚ 1325"),"PAYSANDÚ 1325");
                desplazamientoLogo+=0.5;
                painter.drawText(cuadroTicketRight(7.0,1.0+desplazamientoLogo,8.0,0.5,"MONTEVIDEO - UY"),"MONTEVIDEO - UY");



                if(_codigoTipoImpresion=="2"){
                    desplazamientoLogo+=1;
                    // Se imprime una linea separadora
                    fuente.setBold(true);
                    painter.setFont(fuente);
                    painter.drawText( cuadro(0.0,1.0+desplazamientoLogo,8.0,0.5,false), "____________________________________________");
                    fuente.setBold(true);
                    painter.setFont(fuente);
                    desplazamientoLogo+=0.8;
                    painter.drawText(cuadro(0.5,1.0+desplazamientoLogo,8.0,0.5,false),"Constancia de recepción: ");
                    desplazamientoLogo+=1;
                    // Se imprime una linea separadora
                    fuente.setBold(true);
                    painter.setFont(fuente);
                    painter.drawText( cuadro(0.0,1.0+desplazamientoLogo,8.0,0.5,false), "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _");
                    fuente.setBold(false);
                    painter.setFont(fuente);
                }




                return painter.end();


            }else{

                return false;
            }
        }else{

            return false;
        }
    }else{

        return false;
    }
}



/// ##########################################################################################################################
/// #        Imprime el documento en formato ticket          #################################################################
/// ##########################################################################################################################
bool ModuloDocumentos::emitirDocumentoEnImpresoraTicket(QString _codigoDocumento,QString _codigoTipoDocumento,QString _impresora, int cantidadDecimalesMonto, QString _serieDocumento){

    //##################################################
    // Preparo los seteos de la impresora ##############
    QPrinter printer;
    printer.setPrinterName(_impresora);

    printer.setFullPage(true);

    printer.setPageMargins(0,0,0,0,QPrinter::Millimeter);


    centimetro = printer.QPaintDevice::width()/(printer.QPaintDevice::widthMM()/10);
    fuente.setPointSize(8);


    QString logoConsumoFinal = "iVBORw0KGgoAAAANSUhEUgAAC54AAAGpCAYAAABfrAieAAAABHNCSVQICAgIfAhkiAAAAAlwSFlzAACl8AAApfABIWuNQgAAABl0RVh0U29mdHdhcmUAd3d3Lmlua3NjYXBlLm9yZ5vuPBoAABjiSURBVHic7NoxrqZjAIbhx++IRKbRmOgUCnRiB5Yw1ZQ6K1CSWIXCAugswESsQlQqjVBRTqOYkGOGm5F8/z9nznWV3/fmfd4F3BsAAAAAAAAAAAAAAIQX4t+b29440zsAAAAAAAAAAAAAALi877f9+PjHfwrP39v29bZXj3wRAAAAAAAAAAAAAADPlJ+2vb/tu+sf/y48F50DAAAAAAAAAAAAANxeT8Tnj4fnonMAAAAAAAAAAAAAAP4Sn18Pz0XnAAAAAAAAAAAAAAD84c/4/HTt40cTnQMAAAAAAAAAAAAA8MjdbR9s26nPAQAAAAAAAAAAAABw2wnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAANLVU5z9YduHRz0EAAAAAAAAAAAAAICz+2rbnX879DTh+W/bHvzv5wAAAAAAAAAAAAAA8Kx5+F8OnY5+BQAAAAAAAAAAAAAAN5vwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgXZ1p5/VtH2978Ux7AAAAAAAAAAAAAADPu5+3fbrt4dFD5wjP7257sO2dM2wBAAAAAAAAAAAAANwmb2+7v4Pj89ORl+9RdP7NROcAAAAAAAAAAAAAAEe4t+3LbS8dOXJkeC46BwAAAAAAAAAAAAA43uHx+VHh+cvbvp3oHAAAAAAAAAAAAADgHO5t+/yoy48Kz1/Z9tZBdwMAAAAAAAAAAAAA8KR3j7r4qPAcAAAAAAAAAAAAAIDnhPAcAAAAAAAAAAAAAIB0dcHtX7b9esF9AAAAAAAAAAAAAICb5LVtdy4xfMnw/JNtn11wHwAAAAAAAAAAAADgJvli2/1LDJ8uMQoAAAAAAAAAAAAAwM0hPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAAAAAAAAAAACAJzwEAAAAAAAAAAAAASMJzAAAAAAAAAAAAAACS8BwAAAAAAAAAAAAAgCQ8BwAAAAAAAAAAAAAgCc8BAAAAAAAAAAAAAEjCcwAAAAAAAAAAAAAAkvAcAAAAAAAAAAAAAIAkPAcAAAAAAAAAAAAAIAnPAQAAAAAAAAAAAABIwnMAAAAAAAAAAAAAAJLwHAAAAAAAAAAAAACAJDwHAAAA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";
    QString logoDetalleIva="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";


    QString consultaSql = " SELECT ";
    consultaSql +=" DATE_FORMAT(STR_TO_DATE(DOC.fechaEmisionDocumento, '%Y-%m-%d'),'%d/%m/%Y')'fecha',  ";
    consultaSql +=" MO.codigoISO4217'iso_moneda', ";
    consultaSql +=" (SELECT case when valorConfiguracion='1' then '1' else '0' end FROM Configuracion where codigoConfiguracion='MODO_CALCULOTOTAL')'montos_brutos', ";
    consultaSql +=" '0' as 'vencimiento', ";
    consultaSql +=" DOC.codigoCliente'id_receptor', ";
    consultaSql +=" left(trim(CLI.razonSocial),30) 'razon_social', ";
    consultaSql +=" PA.codigoIsoPais'iso_pais', ";
    consultaSql +=" left(trim(CLI.nombreCliente),30) 'nombre', ";
    consultaSql +=" left(trim(DEP.descripcionDepartamento),30) 'ciudad', ";
    consultaSql +=" left(trim(CLI.direccion),30) 'direccion', ";
    consultaSql +=" left(trim(CLI.email),30)'e_mail', ";
    consultaSql +=" left(trim(CLI.telefono),30)'telefono', ";
    consultaSql +=" CLI.codigoTipoDocumentoCliente'tipoDocumento',  ";
    consultaSql +=" CLI.rut'numeroDocumento', ";
    consultaSql +=" case when DL.precioArticuloUnitario=0 then '5' else IVA.indicadorFacturacionCFE end 'indicador_facturacion', ";
    consultaSql +=" UPPER(left(trim(AR.descripcionArticulo),35))'descripcion', "; // indice 15
    consultaSql +=" DL.cantidad'cantidad',";                                      // indice 16
    consultaSql +=" 'N/A' as 'unidad', ";                                         // indice 17
    consultaSql +=" CAST(DOC.porcentajeDescuentoAlTotal AS DECIMAL(10,3)) 'descuento', ";   // indice 18
    consultaSql +=" '1' as 'tipo_descuento', ";                                             // indice 19
    consultaSql +=" case when IVA.indicadorFacturacionCFE=4 then CAST(IVA.porcentajeIva as DECIMAL(20,2)) else 'null' end 'ivaArticulo', "; // indice 20
    consultaSql +=" CAST(DL.precioArticuloUnitario AS DECIMAL(20,3))'precio_unitario', ";                                                   // indice 21
    consultaSql +=" CAST((DL.cantidad*DL.precioArticuloUnitario) -  (((DL.cantidad*DL.precioArticuloUnitario)*((DOC.porcentajeDescuentoAlTotal/100)+1))-(DL.cantidad*DL.precioArticuloUnitario))  AS DECIMAL(20,3))'totalLinea', "; // indice 22
    consultaSql +=" CAST(DOC.precioSubTotalVenta AS DECIMAL(20,3))'subtotal', ";    // indice 23
    consultaSql +=" CAST(DOC.totalIva3 AS DECIMAL(20,3))'exento', ";                // indice 24
    consultaSql +=" CAST(DOC.totalIva2 AS DECIMAL(20,3))'minima', ";                // indice 25
    consultaSql +=" CAST(DOC.totalIva1 AS DECIMAL(20,3))'basica', ";                // indice 26
    consultaSql +=" case when IVA.indicadorFacturacionCFE=4 then CAST(DL.precioIvaArticulo AS DECIMAL(20,3)) else 'null' end 'otro', ";     // indice 27
    consultaSql +=" CAST(DOC.precioTotalVenta AS DECIMAL(20,3))'total', ";          // indice 28
    consultaSql +=" TD.descripcionTipoDocumentoCFE'TipoDocumentoCFE', ";            // indice 29
    consultaSql +=" case when DOC.codigoMonedaDocumento=1 then    ";
    consultaSql +="          case when DOC.precioTotalVenta > (SELECT 10000*valorParametro FROM CFE_ParametrosGenerales where nombreParametro='montoUI') then 'mayor' else 'menor' end ";
    consultaSql +=" else  ";
    consultaSql +="          case when (DOC.precioTotalVenta*MO.cotizacionMoneda) > (SELECT 10000*valorParametro FROM CFE_ParametrosGenerales where nombreParametro='montoUI') then 'mayor' else 'menor' end ";
    consultaSql +=" end 'UI', ";                            // indice 30
    consultaSql +=" case when IVA.indicadorFacturacionCFE=4 then CAST(IVA.porcentajeIva as DECIMAL(20,2)) else 'null' end 'ivaOtroPorcentaje', ";      // indice 31
    consultaSql +=" CAST(DOC.precioTotalVenta AS DECIMAL(20,3))-(CAST(DOC.precioSubTotalVenta AS DECIMAL(20,3))+CAST(DOC.precioIvaVenta AS DECIMAL(20,3))) 'Redondeo',";    // indice 32
    consultaSql +=" case when AR.codigoIva=IVA.codigoIva and IVA.indicadorFacturacionCFE=1 then CAST((DL.cantidad*DL.precioArticuloUnitario) -  (((DL.cantidad*DL.precioArticuloUnitario)*((DOC.porcentajeDescuentoAlTotal/100)+1))-(DL.cantidad*DL.precioArticuloUnitario))  AS DECIMAL(20,3)) else 0 end 'Exento2',"; // indice 33
    consultaSql +=" DOC.esDocumentoCFE,";                   // indice 34

    //Datos del CFE
    consultaSql +=" DOC.cae_numeroCae,";                    // indice 35
    consultaSql +=" DOC.cae_serie,";                        // indice 36
    consultaSql +=" DOC.cae_fechaVencimiento,";             // indice 37
    consultaSql +=" DOC.cae_codigoSeguridad,";              // indice 38
    consultaSql +=" DOC.cae_Cae,";                          // indice 39
    consultaSql +=" DOC.cae_rangoDesde,";                   // indice 40
    consultaSql +=" DOC.cae_rangoHasta,";                   // indice 41
    consultaSql +=" DOC.cae_urlCode,";                      // indice 42
    consultaSql +=" DOC.cae_QrCode,";                       // indice 43

    consultaSql +=" DOC.caeTipoDocumentoCFEDescripcion,";    // indice 44
    consultaSql +=" DOC.serieDocumento,";                    // indice 45
    consultaSql +=" CFETDC.descripcionTipoDocumentoCliente,";// indice 46
    consultaSql +=" (CAST(DOC.precioSubTotalVenta AS DECIMAL(20,3))+CAST(DOC.precioIvaVenta AS DECIMAL(20,3))) 'totalSinRedondeo',"; // indice 47
    consultaSql +=" DOC.usuarioUltimaModificacion,";         // indice 48

    consultaSql +=" DATE_FORMAT(fechaHoraGuardadoDocumentoSQL,'%H:%i:%s'),"; // indice 49
    consultaSql +=" DOC.usuarioAlta,";                       // indice 50
    consultaSql +=" DL.codigoArticulo,";                     // indice 51
    consultaSql +=" TD.descripcionTipoDocumentoImpresora,";  // indice 52
    consultaSql +=" left(trim(DOC.observaciones),30),";      // indice 53
    consultaSql +=" TD.descripcionTipoDocumento,";           // indice 54
    consultaSql +=" CLI.codigoCliente,";                      // indice 55
    consultaSql +=" MO.simboloMoneda";                        // indice 56



    consultaSql +=" FROM DocumentosLineas DL  ";
    consultaSql +=" join Documentos DOC on DOC.codigoDocumento=DL.codigoDocumento and DOC.codigoTipoDocumento=DL.codigoTipoDocumento and DOC.serieDocumento=DL.serieDocumento ";
    consultaSql +=" join Articulos AR on AR.codigoArticulo=DL.codigoArticulo ";
    consultaSql +=" join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento ";
    consultaSql +=" join Monedas MO on MO.codigoMoneda = DOC.codigoMonedaDocumento ";
    consultaSql +=" join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente ";
    consultaSql +=" join CFE_TipoDocumentoCliente CFETDC on CFETDC.codigoTipoDocumentoCliente=CLI.codigoTipoDocumentoCliente ";
    consultaSql +=" join Pais PA on PA.codigoPais=CLI.codigoPais ";
    consultaSql +=" join Departamentos DEP on DEP.codigoDepartamento=CLI.codigoDepartamento and DEP.codigoPais=CLI.codigoPais ";
    consultaSql +=" join Ivas IVA on IVA.codigoIva=AR.codigoIva ";
    consultaSql +=" where DOC.codigoDocumento="+_codigoDocumento+" and DOC.codigoTipoDocumento="+_codigoTipoDocumento+" and DOC.serieDocumento='"+_serieDocumento+"' ;";




    QString consultaDesgloseIVA ="SELECT ";
    consultaDesgloseIVA +="sum(case when sub.tipoDeIva=1 then sub.totalLinea else 0 end)-sub.basica'NetoBasico',";
    consultaDesgloseIVA +="sum(case when sub.tipoDeIva=2 then sub.totalLinea else 0 end)-sub.minima'NetoMinimo',";
    consultaDesgloseIVA +="sum(case when sub.tipoDeIva=3 then sub.totalLinea else 0 end)-sub.exento'Exento',";
    consultaDesgloseIVA +="sum(case when sub.tipoDeIva=4 then sub.totalLinea else 0 end)-sub.otro'Otro',";
    consultaDesgloseIVA +="sub.basica, sub.minima, sub.exento, sub.otro ";
    consultaDesgloseIVA +="from (SELECT CAST((DL.cantidad*DL.precioArticuloUnitario) -  (((DL.cantidad*DL.precioArticuloUnitario)*((DOC.porcentajeDescuentoAlTotal/100)+1))-(DL.cantidad*DL.precioArticuloUnitario))  AS DECIMAL(20,3))'totalLinea', ";
    consultaDesgloseIVA +="CAST(DOC.totalIva3 AS DECIMAL(20,3))'exento',  CAST(DOC.totalIva2 AS DECIMAL(20,3))'minima',  CAST(DOC.totalIva1 AS DECIMAL(20,3))'basica',  case when IVA.indicadorFacturacionCFE=4 then CAST(DL.precioIvaArticulo AS DECIMAL(20,3)) else 'null' end 'otro',  ";
    consultaDesgloseIVA +="CAST(DOC.precioTotalVenta AS DECIMAL(20,3))'total',  TD.descripcionTipoDocumentoCFE'TipoDocumentoCFE',  case when DOC.codigoMonedaDocumento=1 then              case when DOC.precioTotalVenta > (SELECT 10000*valorParametro FROM CFE_ParametrosGenerales where nombreParametro='montoUI') then 'mayor' else 'menor' end  else            case when (DOC.precioTotalVenta*MO.cotizacionMoneda) > (SELECT 10000*valorParametro FROM CFE_ParametrosGenerales where nombreParametro='montoUI') then 'mayor' else 'menor' end  end 'UI',  case when IVA.indicadorFacturacionCFE=4 then CAST(IVA.porcentajeIva as DECIMAL(20,2)) else 'null' end 'ivaOtroPorcentaje',  CAST(DOC.precioTotalVenta AS DECIMAL(20,3))-(CAST(DOC.precioSubTotalVenta AS DECIMAL(20,3))+CAST(DOC.precioIvaVenta AS DECIMAL(20,3))) 'Redondeo',";
    consultaDesgloseIVA +="case when AR.codigoIva=IVA.codigoIva and IVA.indicadorFacturacionCFE=1 then CAST((DL.cantidad*DL.precioArticuloUnitario) -  (((DL.cantidad*DL.precioArticuloUnitario)*((DOC.porcentajeDescuentoAlTotal/100)+1))-(DL.cantidad*DL.precioArticuloUnitario))  AS DECIMAL(20,3)) else 0 end 'Exento2',  DOC.esDocumentoCFE, DOC.cae_numeroCae, DOC.cae_serie, DOC.cae_fechaVencimiento, DOC.cae_codigoSeguridad, DOC.cae_Cae, DOC.cae_rangoDesde, DOC.cae_rangoHasta, DOC.cae_urlCode, DOC.cae_QrCode, DOC.caeTipoDocumentoCFEDescripcion, DOC.serieDocumento, CFETDC.descripcionTipoDocumentoCliente, (CAST(DOC.precioSubTotalVenta AS DECIMAL(20,3))+CAST(DOC.precioIvaVenta AS DECIMAL(20,3))) 'totalSinRedondeo' ,";
    consultaDesgloseIVA +="AR.codigoIva'tipoDeIva'   FROM DocumentosLineas DL join Documentos DOC on DOC.codigoDocumento=DL.codigoDocumento and DOC.codigoTipoDocumento=DL.codigoTipoDocumento and DOC.serieDocumento=DL.serieDocumento  join Articulos AR on AR.codigoArticulo=DL.codigoArticulo  join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MO on MO.codigoMoneda = DOC.codigoMonedaDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente join CFE_TipoDocumentoCliente CFETDC on CFETDC.codigoTipoDocumentoCliente=CLI.codigoTipoDocumentoCliente   join Pais PA on PA.codigoPais=CLI.codigoPais  join Departamentos DEP on DEP.codigoDepartamento=CLI.codigoDepartamento and DEP.codigoPais=CLI.codigoPais  join Ivas IVA on IVA.codigoIva=AR.codigoIva  where DOC.codigoDocumento="+_codigoDocumento+" and DOC.codigoTipoDocumento="+_codigoTipoDocumento+" and DOC.serieDocumento='"+_serieDocumento+"') sub;";


    //Cantidad de copias por defecto del documento
    int MaximoCopias=0;




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
        QSqlQuery queryDesgloseIva(Database::connect());
        QSqlQuery queryCantidadCopias(Database::connect());

        if(queryCantidadCopias.exec("SELECT cantidadCopias FROM TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"'")) {
            if(queryCantidadCopias.first()){
                if(queryCantidadCopias.value(0).toString()!=0){
                    MaximoCopias = queryCantidadCopias.value(0).toInt();
                }
            }else{return false;}
        }else{
            return false;
        }

        bool seImprimioTodoOk=false;

        for (int var = 0; var < MaximoCopias; ++var) {
            query.first();
            query.previous();
            queryDesgloseIva.first();
            queryDesgloseIva.previous();
            seImprimioTodoOk=false;

            if(query.exec(consultaSql)) {
                if(query.first()){

                    if(queryDesgloseIva.exec(consultaDesgloseIVA)){
                        if(!queryDesgloseIva.first()){
                            return false;
                        }
                    }else{
                        return false;
                    }


                    if (!painter.begin(&printer)) {
                        return false;
                    }
                    painter.setFont(fuente);
                    QString logoImpresora=func_CFE_ParametrosGenerales.retornaValor("logoImpresoraTicket").trimmed();

                    //  qDebug()<< logoImpresora;

                    // Alto en centimetros que ocupa el logo
                    double desplazamientoLogo=2.0;

                    if(logoImpresora!=""){
                        // Si esta cargado el logo lo imprimo
                        QByteArray imagenQrString = logoImpresora.toAscii();
                        QImage imagenQr;
                        imagenQr.loadFromData(QByteArray::fromBase64(imagenQrString));
                        painter.drawImage(cuadro(0.7,0.3,6.0,desplazamientoLogo,false), imagenQr);
                        //painter.drawText(cuadro(0.5,2.5,7.0,0.5,false),"__________________________________________");

                    }else{
                        // Si no existe un logo para imprimir seteo el desplazamiento en cero, para que el texto se imprima al principio del ticket
                        desplazamientoLogo=0.0;
                    }

                    //Cabezal
                    QString codigoCliente=query.value(55).toString();
                    QString fecha=query.value(0).toString();
                    QString iso_moneda=query.value(1).toString().replace("\n","");
                    QString montos_brutos=query.value(2).toString();
                    QString razon_social=query.value(5).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","")+"("+codigoCliente+")";
                    QString nombreCliente=query.value(5).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                    QString ciudad=query.value(8).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                    QString direccion=query.value(9).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                    QString tipoDocumento=query.value(12).toString().replace("\n","");
                    QString numeroDocumento=query.value(13).toString().replace("\n","");
                    QString simbolo_moneda=query.value(56).toString().replace("\n","");

                    QString isoPais=query.value(6).toString().replace("\n","");

                    QString descripcionTipoDocumentoCliente= query.value(46).toString();


                    //totales
                    QString subtotal=QString::number(query.value(23).toFloat()+query.value(32).toFloat(),'f',3);
                    float exento=query.value(24).toFloat();
                    float minima=query.value(25).toFloat();
                    float basica=query.value(26).toFloat();
                    float otro=query.value(27).toFloat();
                    float total=query.value(28).toFloat();
                    QString tipoDocumentoCFE=query.value(29).toString();
                    QString ui=query.value(30).toString();
                    float redondeo=query.value(32).toFloat();
                    float totalSinRedondeo= query.value(47).toFloat();

                    //Desglose de iva
                    float netoBasico= queryDesgloseIva.value(0).toFloat();
                    float netoMinimo= queryDesgloseIva.value(1).toFloat();
                    float netoExento= queryDesgloseIva.value(2).toFloat();
                    float netoOtro=   queryDesgloseIva.value(3).toFloat();

                    // Si es un documento sin iva, muestro todo el campo de iva en 0.
                    if(func_tipoDocumentos.retornaValorCampoTipoDocumento(_codigoTipoDocumento,"noAfectaIva")=="1"){
                        netoBasico= 0.00;
                        netoMinimo= 0.00;
                        netoExento= 0.00;
                        netoOtro=   0.00;
                    }

                    //Datos CFE
                    QString caeTipoDocumentoCFEDescripcionV=query.value(44).toString();
                    QString esDocumentoCFE=query.value(34).toString();
                    QString cae_numeroCae =query.value(35).toString();
                    QString cae_serie =query.value(36).toString();
                    QString cae_fechaVencimiento =query.value(37).toString();
                    QString cae_codigoSeguridad =query.value(38).toString();
                    QString cae_Cae =query.value(39).toString();
                    QString cae_rangoDesde =query.value(40).toString();
                    QString cae_rangoHasta =query.value(41).toString();
                    QString cae_urlCode =query.value(42).toString();
                    QString cae_QrCode =query.value(43).toString();

                    // Usario que emitio el documento
                    QString emisorDelDocumento = query.value(48).toString().toUpper().trimmed();


                    if(emisorDelDocumento.trimmed()=="")
                        emisorDelDocumento=query.value(50).toString().toUpper().trimmed();

                    QString horaEmisionDocumento = query.value(49).toString();

                    QString serieInterna = query.value(45).toString();


                    QString descripcionTipoDocumentoImpresora=query.value(52).toString().trimmed();


                    QString observacionesDelDocumento=query.value(53).toString().trimmed();


                    // Información si es e-ticket o cualquiera de ellos
                    if(esDocumentoCFE=="0"){
                        caeTipoDocumentoCFEDescripcionV=query.value(54).toString().trimmed();
                    }
                    painter.drawText(cuadro(0.0,1.0+desplazamientoLogo,8.0,0.5,false),caeTipoDocumentoCFEDescripcionV);
                    //Fecha
                    painter.drawText(cuadroTicketRight(8.0,1.0+desplazamientoLogo,8.0,0.5,fecha),fecha);


                    // Serie y numero de e-ticket
                    QString serieYNumero=cae_serie+" -"+cae_numeroCae;
                    if(esDocumentoCFE=="0"){
                        serieYNumero=query.value(45).toString()+" - "+_codigoDocumento;
                    }
                    painter.drawText(cuadro(0.0,1.3+desplazamientoLogo,8.0,0.5,false),serieYNumero);



                    //Información sobre cliente, consumo final o rut
                    //Verifico si es cliente con RUT
                    QString textoConsumoFinalRut="CONSUMO FINAL";
                    double leftTextoConsumoFinalRut=2.4;
                    if(tipoDocumento=="2"){
                        textoConsumoFinalRut="RUT COMPRADOR: "+ numeroDocumento;
                        leftTextoConsumoFinalRut=1.2;
                        direccion=direccion+" - "+ciudad;
                    }else{
                        razon_social="NRO. DOCUMENTO: "+numeroDocumento;
                        direccion="CODIGO PAIS: "+isoPais;
                    }
                    QImage imagenLogoConsumoFinal;
                    imagenLogoConsumoFinal.loadFromData(QByteArray::fromBase64(logoConsumoFinal.toAscii()));
                    painter.drawImage(cuadro(0.2,1.8+desplazamientoLogo,7.0,1.0,false), imagenLogoConsumoFinal);
                    fuente.setBold(true);
                    painter.setFont(fuente);
                    //Texto del cuadro consumo final
                    painter.drawText( cuadro(leftTextoConsumoFinalRut,2.1+desplazamientoLogo,8.0,0.5,false), textoConsumoFinalRut);
                    fuente.setBold(false);
                    painter.setFont(fuente);


                    //Datos del cliente
                    if(tipoDocumento!="2"){
                        if(numeroDocumento.trimmed()==""){
                            desplazamientoLogo=desplazamientoLogo-0.9;
                        }else{
                            painter.drawText( cuadro(0.4,3.0+desplazamientoLogo,8.0,0.5,false), razon_social);
                            painter.drawText( cuadro(0.4,3.3+desplazamientoLogo,8.0,0.5,false), direccion);
                            painter.drawText( cuadro(0.4,3.6+desplazamientoLogo,8.0,0.5,false), "TIPO DOC: "+ tipoDocumento + " - " + descripcionTipoDocumentoCliente);
                        }
                    }else{
                        painter.drawText( cuadro(0.4,3.0+desplazamientoLogo,8.0,0.5,false), razon_social);
                        painter.drawText( cuadro(0.4,3.3+desplazamientoLogo,8.0,0.5,false), direccion);
                        painter.drawText( cuadro(0.4,3.6+desplazamientoLogo,8.0,0.5,false), "TIPO DOC: "+ tipoDocumento + " - " + descripcionTipoDocumentoCliente);
                    }




                    // Se imprime una linea separadora
                    fuente.setBold(true);
                    painter.setFont(fuente);
                    painter.drawText( cuadro(0.0,3.8+desplazamientoLogo,8.0,0.5,false), "____________________________________________");
                    fuente.setBold(false);
                    painter.setFont(fuente);


                    // Se imprime la moneda de la transacción
                    painter.drawText( cuadro(0.0,4.2+desplazamientoLogo,8.0,0.5,false), "MONEDA: "+ iso_moneda);


                    // Carga de articulos en el ticket
                    query.previous();
                    double desplazamientoArticulos=4.7;
                    QString codigoArticuloLinea="";
                    while (query.next()){

                        painter.drawText( cuadro(0.0,desplazamientoArticulos+desplazamientoLogo,8.0,0.5,false),query.value(15).toString().replace("\n",""));
                        painter.drawText(cuadroTicketRight(8.0,desplazamientoArticulos+desplazamientoLogo,8.0,0.5,QString::number(query.value(22).toFloat(),'f',2)),QString::number(query.value(22).toFloat(),'f',2));

                        desplazamientoArticulos+=0.3;
                        codigoArticuloLinea = "[ "+query.value(51).toString().toUpper().trimmed()+" ]  ";


                        if(QString::number(query.value(18).toFloat(),'f',2)==QString::number(0.000000,'f',2)){
                            painter.drawText( cuadro(0.3,desplazamientoArticulos+desplazamientoLogo,8.0,0.5,false),codigoArticuloLinea+query.value(16).toString().replace("\n","") +"  UN  x  "+ QString::number(query.value(21).toFloat(),'f',2));
                        }else{
                            painter.drawText( cuadro(0.3,desplazamientoArticulos+desplazamientoLogo,8.0,0.5,false),codigoArticuloLinea+query.value(16).toString().replace("\n","") +"  UN  x  "+ QString::number(query.value(21).toFloat(),'f',2) +"  -  "+ QString::number(query.value(18).toFloat(),'f',2) + " % Dto.");
                        }
                        desplazamientoArticulos+=0.3;
                    }

                    double desplazamientoRestoTicket=desplazamientoArticulos;

                    // Se imprime una linea separadora
                    fuente.setBold(true);
                    painter.setFont(fuente);
                    painter.drawText( cuadro(0.0,desplazamientoRestoTicket+desplazamientoLogo,8.0,0.5,false), "____________________________________________");


                    desplazamientoLogo=desplazamientoRestoTicket+desplazamientoLogo;


                    // Imprimo el total del ticket
                    fuente.setPointSize(12);
                    painter.setFont(fuente);
                    painter.drawText(cuadro(0.0,0.4+desplazamientoLogo,8.0,0.5,false), "T O T A L "+simbolo_moneda+":");

                    painter.drawText(cuadroTicketRight(8.0,0.4+desplazamientoLogo,8.0,0.5,QString::number(total,'f',2)),QString::number(total,'f',2));


                    fuente.setPointSize(8);
                    fuente.setBold(false);
                    painter.setFont(fuente);


                    //Imprimo pago total real
                    painter.drawText(cuadro(0.0,0.9+desplazamientoLogo,8.0,0.5,false), "Pago total");
                    painter.drawText(cuadroTicketRight(8.0,0.9+desplazamientoLogo,8.0,0.5,QString::number(totalSinRedondeo,'f',2)),QString::number(totalSinRedondeo,'f',2));

                    //Imprimo el redondeo
                    painter.drawText(cuadro(0.0,1.2+desplazamientoLogo,8.0,0.5,false), "Redondeo");
                    painter.drawText(cuadroTicketRight(8.0,1.2+desplazamientoLogo,8.0,0.5,QString::number(redondeo,'f',2)),QString::number(redondeo,'f',2));

                    // Se imprime una linea separadora de adenda
                    fuente.setBold(true);
                    painter.setFont(fuente);
                    painter.drawText( cuadro(0.0,1.6+desplazamientoLogo,8.0,0.5,false), "__________________ ADENDA __________________");
                    fuente.setBold(false);
                    painter.setFont(fuente);


                    //Imprimo detalle de ivas
                    QImage imagenLogoDetalleIva;
                    imagenLogoDetalleIva.loadFromData(QByteArray::fromBase64(logoDetalleIva.toAscii()));
                    painter.drawImage(cuadro(0.2,2.0+desplazamientoLogo,7.0,1.0,false), imagenLogoDetalleIva);



                    int largoCampo=QString::number(netoBasico,'f',2).length();

                    // Iva 22%
                    if(largoCampo==6){
                        painter.drawText(cuadro(0.0,3.0+desplazamientoLogo,8.0,0.5,false), "22 %                       " + QString::number(netoBasico,'f',2)+"           "+QString::number(basica,'f',2));
                    }else if(largoCampo==7){
                        painter.drawText(cuadro(0.0,3.0+desplazamientoLogo,8.0,0.5,false), "22 %                    " + QString::number(netoBasico,'f',2)+"           "+QString::number(basica,'f',2));
                    }else if(largoCampo==8){
                        painter.drawText(cuadro(0.0,3.0+desplazamientoLogo,8.0,0.5,false), "22 %                 " + QString::number(netoBasico,'f',2)+"            "+QString::number(basica,'f',2));
                    }else if(largoCampo==9){
                        painter.drawText(cuadro(0.0,3.0+desplazamientoLogo,8.0,0.5,false), "22 %            " + QString::number(netoBasico,'f',2)+"          "+QString::number(basica,'f',2));
                    }else if(largoCampo==10){
                        painter.drawText(cuadro(0.0,3.0+desplazamientoLogo,8.0,0.5,false), "22 %              " + QString::number(netoBasico,'f',2)+"    "+QString::number(basica,'f',2));
                    }
                    else if(largoCampo==5){
                        painter.drawText(cuadro(0.0,3.0+desplazamientoLogo,8.0,0.5,false), "22 %                        " + QString::number(netoBasico,'f',2)+"            "+QString::number(basica,'f',2));
                    }
                    else if(largoCampo==4){
                        painter.drawText(cuadro(0.0,3.0+desplazamientoLogo,8.0,0.5,false), "22 %                          " + QString::number(netoBasico,'f',2)+"              "+QString::number(basica,'f',2));
                    }else{
                        painter.drawText(cuadro(0.0,3.0+desplazamientoLogo,8.0,0.5,false), "22 %          " + QString::number(netoBasico,'f',2)+"       "+QString::number(basica,'f',2));
                    }
                    painter.drawText(cuadroTicketRight(8.0,3.0+desplazamientoLogo,8.0,0.5,QString::number(netoBasico+basica,'f',2)),QString::number(netoBasico+basica,'f',2));



                    largoCampo=QString::number(netoMinimo,'f',2).length();


                    // Iva 10%
                    if(largoCampo==6){
                        painter.drawText(cuadro(0.0,3.3+desplazamientoLogo,8.0,0.5,false), "10 %                       " + QString::number(netoMinimo,'f',2)+"          "+QString::number(minima,'f',2));
                    }else if(largoCampo==7){
                        painter.drawText(cuadro(0.0,3.3+desplazamientoLogo,8.0,0.5,false), "10 %                    " + QString::number(netoMinimo,'f',2)+"           "+QString::number(minima,'f',2));
                    }else if(largoCampo==8){
                        painter.drawText(cuadro(0.0,3.3+desplazamientoLogo,8.0,0.5,false), "10 %                 " + QString::number(netoMinimo,'f',2)+"            "+QString::number(minima,'f',2));
                    }else if(largoCampo==9){
                        painter.drawText(cuadro(0.0,3.3+desplazamientoLogo,8.0,0.5,false), "10 %            " + QString::number(netoMinimo,'f',2)+"          "+QString::number(minima,'f',2));
                    }else if(largoCampo==10){
                        painter.drawText(cuadro(0.0,3.3+desplazamientoLogo,8.0,0.5,false), "10 %              " + QString::number(netoMinimo,'f',2)+"    "+QString::number(minima,'f',2));
                    }
                    else if(largoCampo==5){
                        painter.drawText(cuadro(0.0,3.3+desplazamientoLogo,8.0,0.5,false), "10 %                        " + QString::number(netoMinimo,'f',2)+"              "+QString::number(minima,'f',2));
                    }
                    else if(largoCampo==4){
                        painter.drawText(cuadro(0.0,3.3+desplazamientoLogo,8.0,0.5,false), "10 %                          " + QString::number(netoMinimo,'f',2)+"              "+QString::number(minima,'f',2));
                    }else{
                        painter.drawText(cuadro(0.0,3.3+desplazamientoLogo,8.0,0.5,false), "10 %          " + QString::number(netoMinimo,'f',2)+"       "+QString::number(minima,'f',2));
                    }
                    painter.drawText(cuadroTicketRight(8.0,3.3+desplazamientoLogo,8.0,0.5,QString::number(netoMinimo+minima,'f',2)),QString::number(netoMinimo+minima,'f',2));


                    largoCampo=QString::number(exento,'f',2).length();

                    // Iva 0%
                    if(largoCampo==6){
                        painter.drawText(cuadro(0.0,3.6+desplazamientoLogo,8.0,0.5,false), "  0 %                               " + QString::number(exento,'f',2)+"            "+QString::number(0,'f',2));
                    }else if(largoCampo==7){
                        painter.drawText(cuadro(0.0,3.6+desplazamientoLogo,8.0,0.5,false), "  0 %                            " + QString::number(exento,'f',2)+"             "+QString::number(0,'f',2));
                    }else if(largoCampo==8){
                        painter.drawText(cuadro(0.0,3.6+desplazamientoLogo,8.0,0.5,false), "  0 %                         " + QString::number(exento,'f',2)+"              "+QString::number(0,'f',2));
                    }else if(largoCampo==9){
                        painter.drawText(cuadro(0.0,3.6+desplazamientoLogo,8.0,0.5,false), "  0 %                     " + QString::number(exento,'f',2)+"            "+QString::number(0,'f',2));
                    }else if(largoCampo==10){
                        painter.drawText(cuadro(0.0,3.6+desplazamientoLogo,8.0,0.5,false), "  0 %                       " + QString::number(exento,'f',2)+"      "+QString::number(0,'f',2));
                    }else if(largoCampo==5){
                        painter.drawText(cuadro(0.0,3.6+desplazamientoLogo,8.0,0.5,false), "  0 %                        " + QString::number(exento,'f',2)+"              "+QString::number(0,'f',2));
                    }else if(largoCampo==4){
                        painter.drawText(cuadro(0.0,3.6+desplazamientoLogo,8.0,0.5,false), "  0 %                          " + QString::number(exento,'f',2)+"              "+QString::number(0,'f',2));
                    }else{
                        painter.drawText(cuadro(0.0,3.6+desplazamientoLogo,8.0,0.5,false), "  0 %                   " + QString::number(exento,'f',2)+"         "+QString::number(0,'f',2));
                    }
                    painter.drawText(cuadroTicketRight(8.0,3.6+desplazamientoLogo,8.0,0.5,QString::number(exento,'f',2)),QString::number(exento,'f',2));



                    largoCampo=QString::number(netoOtro,'f',2).length();

                    // Otro iva
                    if(largoCampo==6){
                        painter.drawText(cuadro(0.0,3.9+desplazamientoLogo,8.0,0.5,false), "Otro                          " + QString::number(netoOtro,'f',2)+"          "+QString::number(otro,'f',2));
                    }else if(largoCampo==7){
                        painter.drawText(cuadro(0.0,3.9+desplazamientoLogo,8.0,0.5,false), "Otro                      " + QString::number(netoOtro,'f',2)+"           "+QString::number(otro,'f',2));
                    }else if(largoCampo==8){
                        painter.drawText(cuadro(0.0,3.9+desplazamientoLogo,8.0,0.5,false), "Otro                   " + QString::number(netoOtro,'f',2)+"            "+QString::number(otro,'f',2));
                    }else if(largoCampo==9){
                        painter.drawText(cuadro(0.0,3.9+desplazamientoLogo,8.0,0.5,false), "Otro              " + QString::number(netoOtro,'f',2)+"          "+QString::number(otro,'f',2));
                    }else if(largoCampo==10){
                        painter.drawText(cuadro(0.0,3.9+desplazamientoLogo,8.0,0.5,false), "Otro                " + QString::number(netoOtro,'f',2)+"    "+QString::number(otro,'f',2));
                    }else if(largoCampo==5){
                        painter.drawText(cuadro(0.0,3.9+desplazamientoLogo,8.0,0.5,false), "Otro                       " + QString::number(netoOtro,'f',2)+"            "+QString::number(otro,'f',2));
                    }else if(largoCampo==4){
                        painter.drawText(cuadro(0.0,3.9+desplazamientoLogo,8.0,0.5,false), "Otro                           " + QString::number(netoOtro,'f',2)+"              "+QString::number(otro,'f',2));
                    }else{
                        painter.drawText(cuadro(0.0,3.9+desplazamientoLogo,8.0,0.5,false), "Otro            " + QString::number(netoOtro,'f',2)+"       "+QString::number(otro,'f',2));
                    }
                    painter.drawText(cuadroTicketRight(8.0,3.9+desplazamientoLogo,8.0,0.5,QString::number(netoOtro+otro,'f',2)),QString::number(netoOtro+otro,'f',2));



                    // Se imprime una linea separadora
                    fuente.setBold(true);
                    painter.setFont(fuente);
                    painter.drawText( cuadro(0.0,4.1+desplazamientoLogo,8.0,0.5,false), "____________________________________________");
                    fuente.setBold(false);
                    painter.setFont(fuente);

                    // información del que emitio el documento, nro transacción, fecha y hora
                    painter.drawText(cuadro(0.0,4.5+desplazamientoLogo,8.0,0.5,false),"N° Trans.");
                    painter.drawText(cuadro(3.0,4.5+desplazamientoLogo,8.0,0.5,false),"Fecha/Hora");
                    painter.drawText(cuadroTicketRight(8.0,4.5+desplazamientoLogo,8.0,0.5,"Vend."),"Vend.");
                    painter.drawText(cuadro(0.0,4.8+desplazamientoLogo,8.0,0.5,false),serieInterna+" - "+_codigoDocumento);

                    painter.drawText(cuadro(2.4,4.8+desplazamientoLogo,8.0,0.5,false),fecha+" - "+horaEmisionDocumento);
                    painter.drawText(cuadroTicketRight(7.7,4.8+desplazamientoLogo,8.0,0.5,emisorDelDocumento),emisorDelDocumento);



                    // Imprimo el modo de pago, contado,credito, etc.
                    if(descripcionTipoDocumentoImpresora.trimmed()!=""){
                        desplazamientoLogo=desplazamientoLogo+0.3;
                        painter.drawText(cuadro(0.0,4.8+desplazamientoLogo,8.0,0.5,false),descripcionTipoDocumentoImpresora);
                    }


                    // Imprimo las observaciones del documento, si el mismo esta configurado para ello
                    if(func_tipoDocumentos.retornaValorCampoTipoDocumento(_codigoTipoDocumento,"imprimeObservacionesEnTicket")=="1"){

                        if(observacionesDelDocumento!=""){
                            desplazamientoLogo=desplazamientoLogo+0.3;
                            painter.drawText(cuadro(0.0,4.8+desplazamientoLogo,8.0,0.5,false),observacionesDelDocumento);
                        }
                    }


                    if(tipoDocumento!="2"){
                        // Información de cliente
                        desplazamientoLogo=desplazamientoLogo+0.3;
                        painter.drawText(cuadro(0.0,4.8+desplazamientoLogo,8.0,0.5,false),nombreCliente+"("+codigoCliente+")");
                    }


                    // Se imprime linea fin de adenda
                    fuente.setBold(true);
                    painter.setFont(fuente);
                    painter.drawText( cuadro(0.0,5.2+desplazamientoLogo,8.0,0.5,false), "_________________ FIN ADENDA ________________");
                    fuente.setBold(false);
                    painter.setFont(fuente);



                    // Si el documento es un CFE, imprimo información de factura electronica que este disponible en la base
                    if(esDocumentoCFE!="0"){


                        // Imprimo codigo QR
                        QImage imagenLogoQr;
                        imagenLogoQr.loadFromData(QByteArray::fromBase64(cae_QrCode.toAscii()));
                        painter.drawImage(cuadro(2.3,5.7+desplazamientoLogo,2.8,2.8,false), imagenLogoQr);



                        // Imprrimo codigo de seguridad
                        painter.drawText(cuadro(1.8,8.5+desplazamientoLogo,8.0,0.5,false),"Cod. de Seguridad: "+cae_codigoSeguridad.trimmed());

                        // Imprimo Resolución DGI
                        painter.drawText(cuadro(2.2,8.8+desplazamientoLogo,8.0,0.5,false),func_CFE_ParametrosGenerales.retornaValor("resolucionDGINro"));

                        // Imprimo texto verificar comprobante
                        painter.drawText(cuadro(1.3,9.1+desplazamientoLogo,8.0,0.5,false),"Puede verificar el comprobante en:");

                        // Imprimo url
                        painter.drawText(cuadro(2.5,9.4+desplazamientoLogo,8.0,0.5,false),func_CFE_ParametrosGenerales.retornaValor("urlDGI"));

                        // Imprimo iva al dia
                        painter.drawText(cuadro(3.0,9.7+desplazamientoLogo,8.0,0.5,false),"IVA al día.");


                        // Imprimo palabra DGI
                        fuente.setBold(true);
                        fuente.setPointSize(12);
                        painter.setFont(fuente);
                        painter.drawText(cuadro(3.2,10.2+desplazamientoLogo,8.0,0.5,false),"DGI");
                        fuente.setBold(false);
                        fuente.setPointSize(8);
                        painter.setFont(fuente);


                        // Imprimo texto CAE   Inicio   Fin
                        painter.drawText(cuadro(0.5,10.7+desplazamientoLogo,8.0,0.5,false),"CAE                          Inicio                               Fin");


                        painter.drawText(cuadro(0.0,11.0+desplazamientoLogo,8.0,0.5,false),cae_Cae);
                        painter.drawText(cuadro(3.2,11.0+desplazamientoLogo,8.0,0.5,false),cae_rangoDesde);
                        painter.drawText(cuadroTicketRight(8.0,11.0+desplazamientoLogo,8.0,0.5,cae_rangoHasta),cae_rangoHasta);


                        imagenLogoConsumoFinal.loadFromData(QByteArray::fromBase64(logoConsumoFinal.toAscii()));
                        painter.drawImage(cuadro(0.2,11.4+desplazamientoLogo,7.0,1.0,false), imagenLogoConsumoFinal);

                        painter.drawText(cuadro(1.4,11.7+desplazamientoLogo,8.0,0.5,false),"Fecha de vencimiento:  "+cae_fechaVencimiento);

                    }


                    painter.end();
                    seImprimioTodoOk=true;

                }else{
                    return false;
                }
            }else{
                return false;
            }

        }

        return seImprimioTodoOk;



    }else{
        return false;
    }
    return false;

}






/// ##########################################################################################################################
/// #        Imprime el documento en formato recibo          #################################################################
/// ##########################################################################################################################
bool ModuloDocumentos::emitirDocumentoEnModoRecibo(QString _codigoDocumento,QString _codigoTipoDocumento,QString _impresora, int cantidadDecimalesMonto, QString _serieDocumento){

    //##################################################
    // Preparo los seteos de la impresora ##############
    QPrinter printer;
    printer.setPrinterName(_impresora);

    printer.setFullPage(true);
    centimetro = printer.QPaintDevice::width()/(printer.QPaintDevice::widthMM()/10);
    fuente.setPointSize(8);



    QString consultaSql="select DATE_FORMAT(STR_TO_DATE(DOC.fechaEmisionDocumento, '%Y-%m-%d'),'%d/%m/%Y')'fecha', MO.codigoISO4217'iso_moneda',CAST(DOC.precioTotalVenta AS DECIMAL(20,3))'total',left(trim(CLI.razonSocial),30) 'razon_social',(select valorParametro from CFE_ParametrosGenerales where nombreParametro='rutEmpresa' limit 1)'rut',MO.descripcionMoneda,MO.simboloMoneda,CLI.codigoCliente    from Documentos DOC join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  join Monedas MO on MO.codigoMoneda = DOC.codigoMonedaDocumento  where DOC.codigoDocumento="+_codigoDocumento+" and DOC.codigoTipoDocumento="+_codigoTipoDocumento+" and DOC.serieDocumento='"+_serieDocumento+"' ;";

    QString consultaSqlMediosDePago="select MP.descripcionMedioPago,MO.simboloMoneda,DOC.importePago  from DocumentosLineasPago DOC join MediosDePago MP on MP.codigoMedioPago=DOC.codigoMedioPago join Monedas MO on MO.codigoMoneda=DOC.monedaMedioPago where DOC.codigoDocumento="+_codigoDocumento+" and DOC.codigoTipoDocumento="+_codigoTipoDocumento+" and DOC.serieDocumento='"+_serieDocumento+"' ;";



    QString consultaFacturasCanceladas = "select concat(DCCC.serieDocumento,' - ',DCCC.codigoDocumento),DCCC.montoDescontadoCuentaCorriente from DocumentosCanceladosCuentaCorriente DCCC where DCCC.codigoDocumentoQueCancela="+_codigoDocumento+" and DCCC.codigoTipoDocumentoQueCancela="+_codigoTipoDocumento+" and DCCC.serieDocumentoQueCancela='"+_serieDocumento+"';";

    //Cantidad de copias por defecto del documento
    int MaximoCopias=0;


    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        qDebug()<<"Tengo conexión";
        QSqlQuery query(Database::connect());
        QSqlQuery queryCantidadCopias(Database::connect());
        QSqlQuery queryMedeiosDePago(Database::connect());
        QSqlQuery queryFacturasCanceladas(Database::connect());

        if(queryCantidadCopias.exec("SELECT cantidadCopias FROM TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"'")) {
            if(queryCantidadCopias.first()){
                if(queryCantidadCopias.value(0).toString()!=0){
                    MaximoCopias = queryCantidadCopias.value(0).toInt();
                }
            }else{
                return false;}
        }else{
            return false;
        }

        bool existeMediosDePago=false;
        if(queryMedeiosDePago.exec(consultaSqlMediosDePago)){
            if(queryMedeiosDePago.first()){
                queryMedeiosDePago.previous();
                existeMediosDePago=true;
            }
        }else{
            return false;
        }

        int cantidadFacturas=0;
        bool existeFacturasCanceladas=false;
        if(queryFacturasCanceladas.exec(consultaFacturasCanceladas)){
            if(queryFacturasCanceladas.first()){
                queryFacturasCanceladas.previous();
                existeFacturasCanceladas=true;
                cantidadFacturas=queryFacturasCanceladas.size();
            }
        }else{
            return false;
        }





        bool seImprimioTodoOk=false;

        for (int var = 0; var < MaximoCopias; ++var) {


            if(query.first())
                query.previous();

            if(queryMedeiosDePago.first())
                queryMedeiosDePago.previous();

            if(queryFacturasCanceladas.first())
                queryFacturasCanceladas.previous();


            seImprimioTodoOk=false;

            if(query.exec(consultaSql)) {
                if(query.first()){

                    if (!painter.begin(&printer)) {
                        return false;
                    }
                    painter.setFont(fuente);
                    QString logoImpresora=func_CFE_ParametrosGenerales.retornaValor("logoImpresoraTicket").trimmed();

                    // qDebug()<< "logo imrpesora: " << logoImpresora;

                    // Alto en centimetros que ocupa el logo
                    double desplazamientoLogo=2.0;

                    if(logoImpresora!=""){
                        // Si esta cargado el logo lo imprimo
                        QByteArray imagenQrString = logoImpresora.toAscii();
                        QImage imagenQr;
                        imagenQr.loadFromData(QByteArray::fromBase64(imagenQrString));
                        painter.drawImage(cuadro(0.7,0.3,6.0,desplazamientoLogo,false), imagenQr);

                    }else{
                        // Si no existe un logo para imprimir seteo el desplazamiento en cero, para que el texto se imprima al principio del ticket
                        desplazamientoLogo=0.0;
                    }

                    //Cabezal
                    QString fecha=query.value(0).toString();
                    QString iso_moneda=query.value(1).toString().replace("\n","");
                    float total=query.value(2).toFloat();

                    QString razon_social=query.value(3).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                    QString rutEmpresa=query.value(4).toString();
                    QString descripcionMoneda=query.value(5).toString();
                    QString simboloMoneda=query.value(6).toString();
                    QString codigo_cliente=query.value(7).toString();



                    QString   serieYNumero=_serieDocumento+" - "+_codigoDocumento;



                    fuente.setBold(false);
                    painter.setFont(fuente);

                    painter.setBrush(Qt::NoBrush);
                    QPen pen;

                    pen.setColor(Qt::darkCyan);
                    pen.setWidth(1);

                    painter.setPen(pen);
                    painter.drawRect(QRect(290,20,120,50));// cuadro fecha
                    painter.drawRect(QRect(290,20,120,20));






                    painter.drawRect(QRect(430,20,50,50));// cuadro moneda
                    painter.drawRect(QRect(480,20,90,50));

                    painter.drawRect(QRect(30,120,735,100));// cuadro datos

                    painter.drawRect(QRect(30,235,535,130));// cuadro medios de pago


                    if(existeFacturasCanceladas){
                        int cantidadRenglonesABajar=0;
                        if(cantidadFacturas>7){
                            if(cantidadFacturas>=50){
                                cantidadRenglonesABajar=52;
                            }else{
                                cantidadRenglonesABajar=cantidadFacturas;
                            }


                            painter.drawRect(QRect(575,235,190,130+((cantidadRenglonesABajar-7)*15)));// cuadro facturas canceladas
                        }else{
                            painter.drawRect(QRect(575,235,190,130));// cuadro facturas canceladas
                        }
                    }else{
                        painter.drawRect(QRect(575,235,190,130));// cuadro facturas canceladas
                    }


                    // Impresion de texto

                    pen.setColor(Qt::darkGray);

                    painter.setPen(pen);
                    fuente.setPointSize(11);
                    fuente.setBold(true);
                    painter.setFont(fuente);

                    painter.drawText(cuadro(8.7,0.6,8.0,1.0,false),"FECHA");
                    // Fecha
                    painter.drawText(cuadro(8.4,1.2,8.0,1.0,false),fecha);

                    // iso moneda
                    painter.drawText(cuadro(11.9,0.6,8.0,1.0,false),iso_moneda);
                    painter.drawText(cuadro(11.9,1.2,8.0,1.0,false),simboloMoneda);

                    // Total
                    painter.drawText(cuadro(13.1,1.0,8.0,1.0,false),QString::number(total,'f',2));

                    // Rut
                    painter.drawText(cuadro(16.6,0.5,8.0,1.0,false),"RUT "+rutEmpresa);
                    painter.drawText(cuadro(17.0,0.9,8.0,1.0,false),"RECIBO OFICIAL");

                    // numero documento y serie
                    painter.drawText(cuadroTicketRight(20.5,1.4,5.0,1.0,serieYNumero),serieYNumero);

                    // Texto detalle
                    painter.drawText(cuadro(1.5,3.5,20.0,1.0,false),"Recibimos de "+razon_social.trimmed()+"("+codigo_cliente.trimmed()+") la suma de "+descripcionMoneda+" "+simboloMoneda+" "+QString::number(total,'f',2));
                    painter.drawText(cuadro(1.5,4.0,20.0,1.0,false),"correspondiente al concepto adjunto.");


                    painter.drawText(cuadro(1.5,6.5,5.0,1.0,false),"MEDIOS DE PAGO:");

                    painter.drawText(cuadro(16.0,6.5,5.0,1.0,false),"Nº FACT./IMPORTE "+simboloMoneda);


                    float incremento=0;
                    float factorIncremento=0.4;
                    if(existeMediosDePago){

                        fuente.setPointSize(10);
                        fuente.setBold(false);
                        painter.setFont(fuente);

                        while (queryMedeiosDePago.next()) {
                            painter.drawText(cuadro(2.0,7.0+incremento,5.0,1.0,false),queryMedeiosDePago.value(0).toString());
                            painter.drawText(cuadroTicketRight(14.0,7.0+incremento,5.0,1.0,QString::number(queryMedeiosDePago.value(2).toFloat(),'f',2)),QString::number(queryMedeiosDePago.value(2).toFloat(),'f',2));
                            painter.drawText(cuadro(14.0,7.0+incremento,2.0,1.0,false),queryMedeiosDePago.value(1).toString());

                            incremento=incremento+factorIncremento;
                        }

                    }


                    incremento=0;
                    int numeradorIncremento=0;
                    if(existeFacturasCanceladas){
                        while (queryFacturasCanceladas.next()) {
                            if(cantidadFacturas>=50){

                                if(numeradorIncremento<51){
                                    painter.drawText(cuadro(16.0,7.0+incremento,3.0,1.0,false),queryFacturasCanceladas.value(0).toString());
                                    painter.drawText(cuadroTicketRight(21.0,7.0+incremento,3.0,1.0,QString::number(queryFacturasCanceladas.value(1).toFloat(),'f',2)),QString::number(queryFacturasCanceladas.value(1).toFloat(),'f',2));

                                }


                            }else{
                                painter.drawText(cuadro(16.0,7.0+incremento,3.0,1.0,false),queryFacturasCanceladas.value(0).toString());
                                painter.drawText(cuadroTicketRight(21.0,7.0+incremento,3.0,1.0,QString::number(queryFacturasCanceladas.value(1).toFloat(),'f',2)),QString::number(queryFacturasCanceladas.value(1).toFloat(),'f',2));
                            }
                            numeradorIncremento++;
                            incremento=incremento+factorIncremento;

                        }
                        if(cantidadFacturas>=50){
                            painter.drawText(cuadro(16.0,27.5,3.0,1.0,false),"+"+QString::number(cantidadFacturas-51)+" facturas");
                        }

                    }
                    // firma
                    painter.drawLine(QLine(275,405,465,405));
                    painter.drawText(cuadro(8.5,11.0,3.0,1.0,false),"por "+func_configuracion.retornaValorConfiguracion("NOMBRE_EMPRESA"));

                    painter.end();
                    seImprimioTodoOk=true;

                }else{
                    qDebug()<<"Error en consulta sql 1, no first ";
                    return false;
                }
            }else{
                qDebug()<<"Error en consulta sql 1 ";

                return false;
            }

        }

        return seImprimioTodoOk;



    }else{
        return false;
    }
    return false;

}






/// ##########################################################################################################################
/// #        Realiza los calculos para posicionar los campos del modelo de impresion e imprime el documento ##################
/// ##########################################################################################################################
bool ModuloDocumentos::emitirDocumentoEnImpresora(QString _codigoDocumento,QString _codigoTipoDocumento,QString _impresora,QString _serieDocumento,bool impresionActiva){

    // Si la impresión no se necesita se retorna true.
    if(!impresionActiva)
        return true;


    // consulto si estoy en modo CFE y si es modo IMIX me voy de la funciona, ya que IMIX imprime él, no Khitomer.
    if(func_configuracion.retornaValorConfiguracion("MODO_CFE")=="1" && func_CFE_ParametrosGenerales.retornaValor("modoFuncionCFE")=="0"){

        return true;

    }else{

        // Continuo con la impresión, ya que si estoy en modo CFE, el modo cfe es de dynamia y khitomer es el que imprime,
        // asi como si no estuviera en modo CFE


        // Retorna la cantidad de decimales que tiene confiruado el sistema para manejar los montos
        int cantidadDecimalesMonto=func_configuracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO_IMPRESION").toInt(0);



        // Chequeo si el documento se imprime en modo ticket
        if(func_tipoDocumentos.retornaPermisosDelDocumento(_codigoTipoDocumento,"imprimeEnFormatoTicket")){
            funcion.loguear("Impresora seleccionada para formato ticket: "+_impresora);


            qDebug() << "Emite en ticket";
            return emitirDocumentoEnImpresoraTicket(_codigoDocumento,_codigoTipoDocumento,_impresora,cantidadDecimalesMonto,_serieDocumento);

        }
        // Chequeo si el documento se imprime en modo recibo en formato A4
        if(func_tipoDocumentos.retornaPermisosDelDocumento(_codigoTipoDocumento,"imprimeEnFormatoRecibo")){
            funcion.loguear("Impresora seleccionada para formato recibo: "+_impresora);
            qDebug() << "Emite en modo recibo";
            return emitirDocumentoEnModoRecibo(_codigoDocumento,_codigoTipoDocumento,_impresora,cantidadDecimalesMonto,_serieDocumento);

        }


        bool conexion=true;
        Database::chequeaStatusAccesoMysql();

        if(!Database::connect().isOpen()){
            if(!Database::connect().open()){
                qDebug() << "No conecto";
                conexion=false;
            }
        }

        QString _codigoModeloImpresion="";
        double altoPagina;
        double anchoPagina;
        double comienzoCuerpo;
        double comienzoPie;
        double cantidadItemsPorHoja=0;
        int fuenteSizePoints=9;

        double cantidadLineas=0;

        if(conexion){
            QSqlQuery query(Database::connect());
            if(query.exec("SELECT codigoModeloImpresion FROM TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"'")) {
                if(query.first()){
                    if(query.value(0).toString()!=0){
                        _codigoModeloImpresion = query.value(0).toString();
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


        if(_codigoModeloImpresion=="")
            return false;

        QSqlQuery query(Database::connect());
        if(query.exec("SELECT altoPagina,anchoPagina,comienzoCuerpo,comienzoPie,fuenteSizePoints FROM ModeloImpresion where codigoModeloImpresion='"+_codigoModeloImpresion+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){
                    altoPagina = query.value(0).toDouble()*10;
                }else{
                    return false;
                }

                if(query.value(1).toString()!=0){
                    anchoPagina = query.value(1).toDouble()*10;
                }else{
                    return false;
                }

                if(query.value(2).toString()!=0){
                    comienzoCuerpo = query.value(2).toDouble();
                }else{
                    return false;
                }

                if(query.value(3).toString()!=0){
                    comienzoPie = query.value(3).toDouble();
                }else{
                    return false;
                }

                if(query.value(4).toString()!=0){
                    fuenteSizePoints = query.value(4).toInt();
                }else{
                    return false;
                }
            }else{return false;}
        }else{
            return false;
        }
        int MaximoCopias=1;


        double seteos=comienzoCuerpo;


        query.clear();


        if(query.exec("SELECT cantidadCopias FROM TipoDocumento where codigoTipoDocumento='"+_codigoTipoDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){
                    MaximoCopias = query.value(0).toInt();
                }
            }else{return false;}
        }else{
            return false;
        }

        query.clear();

        /// Obtengo la cantidad de lineas del cuerpo a imprimir
        if(query.exec("SELECT count(distinct DOC.codigoArticulo) FROM DocumentosLineas DOC where DOC.codigoDocumento='"+_codigoDocumento+"' and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=0){
                    cantidadLineas = query.value(0).toInt();
                }else{
                    cantidadLineas = 0;
                }
            }else{cantidadLineas = 0;}
        }


        ///Obtengo la cantidad de lineas que puedo usar en la hoja
        cantidadItemsPorHoja= ((comienzoPie-comienzoCuerpo)*26)/13;

        int MaximoHojasAImprimir=0;


        ///Calculo la cantidad de hojas necesarias para imprimir la factura
        if(cantidadLineas<=cantidadItemsPorHoja){

            MaximoHojasAImprimir=1;

        }else{

            if((cantidadLineas/cantidadItemsPorHoja)<=2){
                MaximoHojasAImprimir=2;
            }else if((cantidadLineas/cantidadItemsPorHoja)<=3){
                MaximoHojasAImprimir=3;
            }else if((cantidadLineas/cantidadItemsPorHoja)<=4){
                MaximoHojasAImprimir=4;
            }else if((cantidadLineas/cantidadItemsPorHoja)<=5){
                MaximoHojasAImprimir=5;
            }else if((cantidadLineas/cantidadItemsPorHoja)<=6){
                MaximoHojasAImprimir=6;
            }else if((cantidadLineas/cantidadItemsPorHoja)<=7){
                MaximoHojasAImprimir=7;
            }else if((cantidadLineas/cantidadItemsPorHoja)<=8){
                MaximoHojasAImprimir=8;
            }else if((cantidadLineas/cantidadItemsPorHoja)<=9){
                MaximoHojasAImprimir=9;
            }else if((cantidadLineas/cantidadItemsPorHoja)<=10){
                MaximoHojasAImprimir=10;
            }else if((cantidadLineas/cantidadItemsPorHoja)<=11){
                MaximoHojasAImprimir=11;
            }else if((cantidadLineas/cantidadItemsPorHoja)<=12){
                MaximoHojasAImprimir=12;
            }

        }

        //##################################################
        // Preparo los seteos de la impresora ##############
        QPrinter printer;
        printer.setPrinterName(_impresora);
        QPainter painter;
        printer.setOutputFormat(QPrinter::NativeFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setPageSize(QPrinter::A4);
        QSizeF size;
        size.setHeight(altoPagina);
        size.setWidth(anchoPagina);
        //printer.setPaperSize(size,QPrinter::Millimeter);
        printer.setOrientation(QPrinter::Portrait);
        printer.setCreator("Khitomer");
        printer.setColorMode(QPrinter::GrayScale);
        printer.setFullPage(true);
        QFont fuente("Arial");

        fuente.setPointSize(fuenteSizePoints);



        centimetro = printer.QPaintDevice::width()/(printer.QPaintDevice::widthMM()/10);

        // FIN de preparo los seteos de la impresora ######
        //#################################################


        QSqlQuery queryCabezal(Database::connect());
        QSqlQuery queryCuerpo(Database::connect());
        QSqlQuery queryPie(Database::connect());


        int cantidadVecesIncremento=cantidadItemsPorHoja;


        //Cantidad de veces que se repite la impresion del mismo documento
        for(int i=0;i<MaximoCopias;i++){

            int contadorLineas=0;
            int iterador=0;
            comienzoCuerpo=seteos;
            cantidadItemsPorHoja=cantidadVecesIncremento;



            if (! painter.begin(&printer)) {
                return false;
            }
            painter.setFont(fuente);


            // Cantidad de hojas que se imprimen del mismo documento
            for(int j=0;j<MaximoHojasAImprimir;j++){



                if(j<MaximoHojasAImprimir && j!=0){

                    printer.newPage();

                    iterador+=cantidadVecesIncremento;
                    cantidadItemsPorHoja+=cantidadVecesIncremento;
                    comienzoCuerpo=seteos;

                }


                ///Armamos el cabezal de la impresion

                if(query.exec("select MIL.posicionX,MIL.posicionY,MIL.largoDeCampo,MIL.alineacion,case when MIL.alineacion=2 then true else false end,IC.campoEnTabla,IC.codigoEtiqueta, MIL.textoImprimibleIzquierda, MIL.textoImprimibleDerecha, MIL.fuenteSizePoints   from ModeloImpresionLineas MIL join ImpresionCampos IC on IC.codigoCampoImpresion=MIL.codigoCampoImpresion where MIL.codigoModeloImpresion='"+_codigoModeloImpresion+"' and IC.tipoCampo=1")) {

                    while(query.next()){

                        fuente.setPointSize(query.value(9).toInt());
                        painter.setFont(fuente);

                        queryCabezal.clear();
                        if(queryCabezal.exec("SELECT case when "+query.value(5).toString()+"='' then ' ' else "+query.value(5).toString()+"  end, Doc.codigoCliente,Doc.tipoCliente FROM Documentos Doc left join Clientes C on C.codigoCliente=Doc.codigoCliente and C.tipoCliente=Doc.tipoCliente left join Localidades LOC on LOC.codigoLocalidad=C.codigoLocalidad and LOC.codigoDepartamento=C.codigoDepartamento and LOC.codigoPais=C.codigoPais join TipoDocumento TD on TD.codigoTipoDocumento=Doc.codigoTipoDocumento  where Doc.codigoDocumento='"+_codigoDocumento+"' and Doc.codigoTipoDocumento='"+_codigoTipoDocumento+"' and Doc.serieDocumento='"+_serieDocumento+"'")) {
                            queryCabezal.next();
                            if(queryCabezal.value(0).toString()!=0){

                                if(func_configuracion.retornaValorConfiguracion("MODO_IMPRESION_A4")=="1"){
                                    if(query.value(5).toString()=="Doc.fechaEmisionDocumento"){
                                        painter.drawText(cuadroA4(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(7).toString()+" "+QDateTime::fromString(queryCabezal.value(0).toString(),Qt::ISODate).toString("dd-MM-yyyy")+" "+query.value(8).toString());

                                    }else{
                                        if(query.value(6).toString()=="txtMarcaXDeClienteFinalCampo"){

                                            //chequeo si el cliente tiene RUT, si no tiene, imprimo la X de cliente final
                                            if(!retornaClienteTieneRUT(queryCabezal.value(1).toString().trimmed(),queryCabezal.value(2).toString().trimmed())){
                                                painter.drawText(cuadroA4(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(7).toString()+" "+"X"+" "+query.value(8).toString());
                                            }

                                        }else if(query.value(6).toString()=="txtTextoGenericoCabezal1" || query.value(6).toString()=="txtTextoGenericoCabezal2" || query.value(6).toString()=="txtTextoGenericoCabezal3" || query.value(6).toString()=="txtTextoGenericoCabezal4"){
                                            painter.drawText(cuadroA4(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(7).toString()+" "+query.value(8).toString());
                                        }else{
                                            painter.drawText(cuadroA4(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(7).toString()+" "+queryCabezal.value(0).toString()+" "+query.value(8).toString());
                                        }
                                    }
                                }



                                if(query.value(5).toString()=="Doc.fechaEmisionDocumento"){
                                    painter.drawText(cuadro(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(7).toString()+" "+QDateTime::fromString(queryCabezal.value(0).toString(),Qt::ISODate).toString("dd-MM-yyyy")+" "+query.value(8).toString());
                                }else{
                                    if(query.value(6).toString()=="txtMarcaXDeClienteFinalCampo"){

                                        //chequeo si el cliente tiene RUT, si no tiene, imprimo la X de cliente final
                                        if(!retornaClienteTieneRUT(queryCabezal.value(1).toString().trimmed(),queryCabezal.value(2).toString().trimmed())){

                                            painter.drawText(cuadro(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(7).toString()+" "+"X"+" "+query.value(8).toString());

                                        }
                                    }else if(query.value(6).toString()=="txtTextoGenericoCabezal1" || query.value(6).toString()=="txtTextoGenericoCabezal2" || query.value(6).toString()=="txtTextoGenericoCabezal3" || query.value(6).toString()=="txtTextoGenericoCabezal4"){
                                        painter.drawText(cuadroA4(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(7).toString()+" "+query.value(8).toString());
                                    }else{
                                        painter.drawText(cuadro(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(7).toString()+" "+queryCabezal.value(0).toString()+" "+query.value(8).toString());
                                    }
                                }
                            }
                        }
                    }
                }else{ return false; }


                ///Armamos el cuerpo de la impresion
                query.clear();
                if(query.exec("select MIL.posicionX,MIL.posicionY,MIL.largoDeCampo,MIL.alineacion,case when MIL.alineacion=2 then true else false end,IC.campoEnTabla, MIL.textoImprimibleIzquierda, MIL.textoImprimibleDerecha, IC.codigoEtiqueta, MIL.fuenteSizePoints from ModeloImpresionLineas MIL join ImpresionCampos IC on IC.codigoCampoImpresion=MIL.codigoCampoImpresion where MIL.codigoModeloImpresion='"+_codigoModeloImpresion+"' and IC.tipoCampo=2")) {

                    QString campoDeOrdenItemsFacturaOrderOGroupBy=" order by DOC.numeroLinea asc  ";
                    QString campoSumaONoSumaCantidadLineasSegunCampoOrden=" DOC.cantidad ";
                    QString campoSumaONoSumaTotalVentaItemsSegunCampoOrden=" precioTotalVenta ";

                    QString campoSumaONoSumaDescuentoLineaVentaItemsSegunCampoOrden = " montoDescuento ";


                    QString resultadoConsulta=func_tipoDocumentos.retornaValorCampoTipoDocumento(_codigoTipoDocumento,"tipoOrdenLineasFacturasAlEmitirse");


                    if(resultadoConsulta=="0"){
                        campoDeOrdenItemsFacturaOrderOGroupBy=" group by DOC.codigoArticulo  ";
                        campoSumaONoSumaCantidadLineasSegunCampoOrden=" sum(DOC.cantidad) ";
                        campoSumaONoSumaTotalVentaItemsSegunCampoOrden=" sum(precioTotalVenta) ";
                        campoSumaONoSumaDescuentoLineaVentaItemsSegunCampoOrden = " sum(montoDescuento) ";
                    }else if(resultadoConsulta=="1"){
                        campoDeOrdenItemsFacturaOrderOGroupBy=" order by DOC.numeroLinea asc  ";
                        campoSumaONoSumaCantidadLineasSegunCampoOrden=" DOC.cantidad ";
                        campoSumaONoSumaTotalVentaItemsSegunCampoOrden=" precioTotalVenta ";
                        campoSumaONoSumaDescuentoLineaVentaItemsSegunCampoOrden = " montoDescuento ";
                    }

                    while(query.next()){


                        fuente.setPointSize(query.value(9).toInt());
                        painter.setFont(fuente);

                        comienzoCuerpo=seteos;
                        queryCuerpo.clear();
                        if(query.value(5).toString()=="CANTIDAD"){

                            if(queryCuerpo.exec("SELECT DOC.codigoArticulo,   "+campoSumaONoSumaCantidadLineasSegunCampoOrden+"   FROM DocumentosLineas DOC where DOC.codigoDocumento='"+_codigoDocumento+"' and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'  "+campoDeOrdenItemsFacturaOrderOGroupBy+"  ")) {

                                contadorLineas=0;
                                while(queryCuerpo.next()){


                                    if(queryCuerpo.value(0).toString()!=0){

                                        if(contadorLineas<cantidadItemsPorHoja && contadorLineas >=iterador ){

                                            if(func_configuracion.retornaValorConfiguracion("MODO_IMPRESION_A4")=="1"){

                                                if(query.value(8).toString()=="txtTextoGenericoCuerpo1" || query.value(8).toString()=="txtTextoGenericoCuerpo2" || query.value(8).toString()=="txtTextoGenericoCuerpo3" || query.value(8).toString()=="txtTextoGenericoCuerpo4"){
                                                    painter.drawText(cuadroA4(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+query.value(7).toString());
                                                }else{
                                                    painter.drawText(cuadroA4(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+queryCuerpo.value(1).toString()+" "+query.value(7).toString());
                                                }

                                            }
                                            if(query.value(8).toString()=="txtTextoGenericoCuerpo1" || query.value(8).toString()=="txtTextoGenericoCuerpo2" || query.value(8).toString()=="txtTextoGenericoCuerpo3" || query.value(8).toString()=="txtTextoGenericoCuerpo4"){
                                                painter.drawText(cuadro(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+query.value(7).toString());
                                            }else{
                                                painter.drawText(cuadro(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+queryCuerpo.value(1).toString()+" "+query.value(7).toString());
                                            }

                                            comienzoCuerpo+=0.5;
                                        }
                                        contadorLineas++;
                                    }

                                }
                            }

                        }else if(query.value(5).toString()=="precioTotalVenta"){
                            if(queryCuerpo.exec("SELECT DOC.codigoArticulo, "+campoSumaONoSumaTotalVentaItemsSegunCampoOrden+"  FROM DocumentosLineas DOC where DOC.codigoDocumento='"+_codigoDocumento+"' and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'   "+campoDeOrdenItemsFacturaOrderOGroupBy+" ")) {

                                contadorLineas=0;

                                while(queryCuerpo.next()){
                                    if(queryCuerpo.value(0).toString()!=0){

                                        if(contadorLineas<cantidadItemsPorHoja && contadorLineas >=iterador){

                                            if(func_configuracion.retornaValorConfiguracion("MODO_IMPRESION_A4")=="1"){
                                                if(query.value(8).toString()=="txtTextoGenericoCuerpo1" || query.value(8).toString()=="txtTextoGenericoCuerpo2" || query.value(8).toString()=="txtTextoGenericoCuerpo3" || query.value(8).toString()=="txtTextoGenericoCuerpo4"){
                                                    painter.drawText(cuadroA4(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+query.value(7).toString());
                                                }else{
                                                    painter.drawText(cuadroA4(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+QString::number(queryCuerpo.value(1).toDouble(),'f',cantidadDecimalesMonto)+" "+query.value(7).toString());
                                                }

                                            }
                                            if(query.value(8).toString()=="txtTextoGenericoCuerpo1" || query.value(8).toString()=="txtTextoGenericoCuerpo2" || query.value(8).toString()=="txtTextoGenericoCuerpo3" || query.value(8).toString()=="txtTextoGenericoCuerpo4"){
                                                painter.drawText(cuadro(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+query.value(7).toString());
                                            }else{
                                                painter.drawText(cuadro(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+QString::number(queryCuerpo.value(1).toDouble(),'f',cantidadDecimalesMonto)+" "+query.value(7).toString());
                                            }
                                            comienzoCuerpo+=0.5;

                                        }
                                        contadorLineas++;
                                    }
                                }
                            }
                        }
                        else if(query.value(5).toString()=="montoDescuento"){
                            if(queryCuerpo.exec("SELECT DOC.codigoArticulo, "+campoSumaONoSumaDescuentoLineaVentaItemsSegunCampoOrden+"  FROM DocumentosLineas DOC where DOC.codigoDocumento='"+_codigoDocumento+"' and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'   "+campoDeOrdenItemsFacturaOrderOGroupBy+" ")) {

                                contadorLineas=0;

                                while(queryCuerpo.next()){
                                    if(queryCuerpo.value(0).toString()!=0){

                                        if(contadorLineas<cantidadItemsPorHoja && contadorLineas >=iterador){

                                            if(func_configuracion.retornaValorConfiguracion("MODO_IMPRESION_A4")=="1"){
                                                if(query.value(8).toString()=="txtTextoGenericoCuerpo1" || query.value(8).toString()=="txtTextoGenericoCuerpo2" || query.value(8).toString()=="txtTextoGenericoCuerpo3" || query.value(8).toString()=="txtTextoGenericoCuerpo4"){
                                                    painter.drawText(cuadroA4(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+query.value(7).toString());
                                                }else{
                                                    painter.drawText(cuadroA4(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+QString::number(queryCuerpo.value(1).toDouble(),'f',cantidadDecimalesMonto)+" "+query.value(7).toString());
                                                }

                                            }
                                            if(query.value(8).toString()=="txtTextoGenericoCuerpo1" || query.value(8).toString()=="txtTextoGenericoCuerpo2" || query.value(8).toString()=="txtTextoGenericoCuerpo3" || query.value(8).toString()=="txtTextoGenericoCuerpo4"){
                                                painter.drawText(cuadro(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+query.value(7).toString());
                                            }else{
                                                painter.drawText(cuadro(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+QString::number(queryCuerpo.value(1).toDouble(),'f',cantidadDecimalesMonto)+" "+query.value(7).toString());
                                            }
                                            comienzoCuerpo+=0.5;

                                        }
                                        contadorLineas++;
                                    }
                                }
                            }
                        }

                        else if(query.value(5).toString()=="precioArticuloUnitario"){
                            if(queryCuerpo.exec("SELECT DOC.codigoArticulo, precioArticuloUnitario  FROM DocumentosLineas DOC where DOC.codigoDocumento='"+_codigoDocumento+"' and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"' and DOC.serieDocumento='"+_serieDocumento+"'  "+campoDeOrdenItemsFacturaOrderOGroupBy+" ")) {

                                contadorLineas=0;

                                while(queryCuerpo.next()){
                                    if(queryCuerpo.value(0).toString()!=0){

                                        if(contadorLineas<cantidadItemsPorHoja && contadorLineas >=iterador){
                                            if(func_configuracion.retornaValorConfiguracion("MODO_IMPRESION_A4")=="1"){
                                                if(query.value(8).toString()=="txtTextoGenericoCuerpo1" || query.value(8).toString()=="txtTextoGenericoCuerpo2" || query.value(8).toString()=="txtTextoGenericoCuerpo3" || query.value(8).toString()=="txtTextoGenericoCuerpo4"){
                                                    painter.drawText(cuadroA4(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+query.value(7).toString());
                                                }else{
                                                    painter.drawText(cuadroA4(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+QString::number(queryCuerpo.value(1).toDouble(),'f',cantidadDecimalesMonto)+" "+query.value(7).toString());
                                                }

                                            }
                                            if(query.value(8).toString()=="txtTextoGenericoCuerpo1" || query.value(8).toString()=="txtTextoGenericoCuerpo2" || query.value(8).toString()=="txtTextoGenericoCuerpo3" || query.value(8).toString()=="txtTextoGenericoCuerpo4"){
                                                painter.drawText(cuadro(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+query.value(7).toString());
                                            }else{
                                                painter.drawText(cuadro(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+QString::number(queryCuerpo.value(1).toDouble(),'f',cantidadDecimalesMonto)+" "+query.value(7).toString());
                                            }

                                            comienzoCuerpo+=0.5;

                                        }
                                        contadorLineas++;
                                    }
                                }
                            }
                        }else if(query.value(5).toString()=="descripcionArticulo"){
                            if(queryCuerpo.exec("SELECT DOC.codigoArticulo  FROM DocumentosLineas DOC where DOC.codigoDocumento='"+_codigoDocumento+"' and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"'  and DOC.serieDocumento='"+_serieDocumento+"'  "+campoDeOrdenItemsFacturaOrderOGroupBy+"  ")) {

                                contadorLineas=0;

                                while(queryCuerpo.next()){
                                    if(queryCuerpo.value(0).toString()!=0){

                                        if(contadorLineas<cantidadItemsPorHoja && contadorLineas >=iterador){

                                            if(func_configuracion.retornaValorConfiguracion("MODO_IMPRESION_A4")=="1"){
                                                if(query.value(8).toString()=="txtTextoGenericoCuerpo1" || query.value(8).toString()=="txtTextoGenericoCuerpo2" || query.value(8).toString()=="txtTextoGenericoCuerpo3" || query.value(8).toString()=="txtTextoGenericoCuerpo4"){
                                                    painter.drawText(cuadroA4(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(), query.value(6).toString()+" "+query.value(7).toString());
                                                }else{
                                                    painter.drawText(cuadroA4(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(), query.value(6).toString()+" "+func_articulos.retornaDescripcionArticulo(queryCuerpo.value(0).toString())+" "+query.value(7).toString());
                                                }

                                            }
                                            if(query.value(8).toString()=="txtTextoGenericoCuerpo1" || query.value(8).toString()=="txtTextoGenericoCuerpo2" || query.value(8).toString()=="txtTextoGenericoCuerpo3" || query.value(8).toString()=="txtTextoGenericoCuerpo4"){
                                                painter.drawText(cuadro(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(), query.value(6).toString()+" "+query.value(7).toString());
                                            }else{
                                                painter.drawText(cuadro(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(), query.value(6).toString()+" "+func_articulos.retornaDescripcionArticulo(queryCuerpo.value(0).toString())+" "+query.value(7).toString());
                                            }

                                            comienzoCuerpo+=0.5;

                                        }
                                        contadorLineas++;
                                    }
                                }
                            }
                        }else{
                            if(queryCuerpo.exec("SELECT DOC.codigoArticulo, case when "+query.value(5).toString()+"='' then ' ' else "+query.value(5).toString()+"  end  FROM DocumentosLineas DOC where DOC.codigoDocumento='"+_codigoDocumento+"' and DOC.codigoTipoDocumento='"+_codigoTipoDocumento+"'  and DOC.serieDocumento='"+_serieDocumento+"'  "+campoDeOrdenItemsFacturaOrderOGroupBy+" ")) {

                                contadorLineas=0;

                                while(queryCuerpo.next()){
                                    if(queryCuerpo.value(0).toString()!=0){

                                        if(contadorLineas<cantidadItemsPorHoja && contadorLineas >=iterador){
                                            if(func_configuracion.retornaValorConfiguracion("MODO_IMPRESION_A4")=="1"){
                                                if(query.value(8).toString()=="txtTextoGenericoCuerpo1" || query.value(8).toString()=="txtTextoGenericoCuerpo2" || query.value(8).toString()=="txtTextoGenericoCuerpo3" || query.value(8).toString()=="txtTextoGenericoCuerpo4"){
                                                    painter.drawText(cuadroA4(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+query.value(7).toString());
                                                }else{
                                                    painter.drawText(cuadroA4(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+queryCuerpo.value(1).toString()+" "+query.value(7).toString());
                                                }

                                            }
                                            if(query.value(8).toString()=="txtTextoGenericoCuerpo1" || query.value(8).toString()=="txtTextoGenericoCuerpo2" || query.value(8).toString()=="txtTextoGenericoCuerpo3" || query.value(8).toString()=="txtTextoGenericoCuerpo4"){
                                                painter.drawText(cuadro(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+query.value(7).toString());
                                            }else{
                                                painter.drawText(cuadro(query.value(0).toDouble(),comienzoCuerpo,query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+queryCuerpo.value(1).toString()+" "+query.value(7).toString());
                                            }

                                            comienzoCuerpo+=0.5;

                                        }
                                        contadorLineas++;
                                    }
                                }
                            }
                        }


                    }
                }else{ return false; }



                ///Armamos el pie de la impresion
                query.clear();


                QImage imagenQr;
                QByteArray imagenQrString;

                QString _montoAGrabar="0"+func_configuracion.retornaCantidadDecimalesString()+"";
                if(query.exec("select MIL.posicionX,MIL.posicionY,MIL.largoDeCampo,MIL.alineacion,case when MIL.alineacion=2 then true else false end,IC.campoEnTabla, MIL.textoImprimibleIzquierda, MIL.textoImprimibleDerecha, IC.codigoEtiqueta, MIL.fuenteSizePoints from ModeloImpresionLineas MIL join ImpresionCampos IC on IC.codigoCampoImpresion=MIL.codigoCampoImpresion where MIL.codigoModeloImpresion='"+_codigoModeloImpresion+"' and IC.tipoCampo=3")) {

                    while(query.next()){

                        fuente.setPointSize(query.value(9).toInt());
                        painter.setFont(fuente);


                        _montoAGrabar="0"+func_configuracion.retornaCantidadDecimalesString()+"";
                        queryPie.clear();
                        if(queryPie.exec("SELECT case when "+query.value(5).toString()+"='' then ' ' else "+query.value(5).toString()+"  end FROM Documentos Doc left join Clientes C on C.codigoCliente=Doc.codigoCliente and C.tipoCliente=Doc.tipoCliente join Monedas on Monedas.codigoMoneda=Doc.codigoMonedaDocumento where Doc.codigoDocumento='"+_codigoDocumento+"' and Doc.codigoTipoDocumento='"+_codigoTipoDocumento+"' and Doc.serieDocumento='"+_serieDocumento+"'"))
                        {
                            queryPie.next();
                            if(queryPie.value(0).toString()!=0){

                                if(func_configuracion.retornaValorConfiguracion("MODO_IMPRESION_A4")=="1"){
                                    if(query.value(8).toString()=="txtTextoGenericoPie1" || query.value(8).toString()=="txtTextoGenericoPie2" || query.value(8).toString()=="txtTextoGenericoPie3" || query.value(8).toString()=="txtTextoGenericoPie4"){

                                        painter.drawText(cuadroA4(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+query.value(7).toString());
                                    }else if(query.value(8).toString()=="txtSubTotalSinDescuentoCampo" || query.value(8).toString()=="txtTotalDescuentoAlTotal" || query.value(8).toString()=="txtIvaExentoCampo"
                                             || query.value(8).toString()=="txtIvaMinimoCampo"|| query.value(8).toString()=="txtIvaBasicoCampo"|| query.value(8).toString()=="txtIvaTotalCampo"
                                             || query.value(8).toString()=="txtTotalCampo"|| query.value(8).toString()=="txtSubTotalCampo"){
                                        if(!queryPie.value(0).toString().trimmed().isEmpty()){
                                            _montoAGrabar = QString::number(queryPie.value(0).toDouble(),'f',cantidadDecimalesMonto);
                                        }
                                        painter.drawText(cuadroA4(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+_montoAGrabar+" "+query.value(7).toString());
                                    }else if(query.value(8).toString()=="txtCae_QrCode"){

                                        imagenQrString = queryPie.value(0).toString().toLatin1();
                                        imagenQr.loadFromData(QByteArray::fromBase64(imagenQrString));
                                        painter.drawImage(cuadroA4(query.value(0).toDouble(),query.value(1).toDouble(),query.value(9).toDouble(),query.value(9).toDouble(),query.value(4).toBool()), imagenQr);

                                    }else if(query.value(8).toString()=="txtCae_urlCode"){

                                        painter.drawText(cuadroA4(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+func_CFE_ParametrosGenerales.retornaValor("urlDGI")+" "+query.value(7).toString());
                                    }
                                    else{
                                        if(!queryPie.value(0).toString().trimmed().isEmpty()){
                                            _montoAGrabar=queryPie.value(0).toString();
                                        }
                                        painter.drawText(cuadroA4(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+_montoAGrabar+" "+query.value(7).toString());
                                    }
                                }
                                if(query.value(8).toString()=="txtTextoGenericoPie1" || query.value(8).toString()=="txtTextoGenericoPie2" || query.value(8).toString()=="txtTextoGenericoPie3" || query.value(8).toString()=="txtTextoGenericoPie4"){

                                    painter.drawText(cuadro(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+query.value(7).toString());

                                }else if(query.value(8).toString()=="txtSubTotalSinDescuentoCampo" || query.value(8).toString()=="txtTotalDescuentoAlTotal" || query.value(8).toString()=="txtIvaExentoCampo"
                                         || query.value(8).toString()=="txtIvaMinimoCampo"|| query.value(8).toString()=="txtIvaBasicoCampo"|| query.value(8).toString()=="txtIvaTotalCampo"
                                         || query.value(8).toString()=="txtTotalCampo"|| query.value(8).toString()=="txtSubTotalCampo"

                                         ){
                                    if(!queryPie.value(0).toString().trimmed().isEmpty()){
                                        _montoAGrabar = QString::number(queryPie.value(0).toDouble(),'f',cantidadDecimalesMonto);
                                    }
                                    painter.drawText(cuadro(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+_montoAGrabar+" "+query.value(7).toString());
                                }else if(query.value(8).toString()=="txtCae_QrCode"){

                                    imagenQrString = queryPie.value(0).toString().toLatin1();
                                    imagenQr.loadFromData(QByteArray::fromBase64(imagenQrString));
                                    painter.drawImage(cuadro(query.value(0).toDouble(),query.value(1).toDouble(),query.value(9).toDouble(),query.value(9).toDouble(),query.value(4).toBool()), imagenQr);

                                }else if(query.value(8).toString()=="txtCae_urlCode"){

                                    painter.drawText(cuadro(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+func_CFE_ParametrosGenerales.retornaValor("urlDGI")+" "+query.value(7).toString());
                                }
                                else{
                                    if(!queryPie.value(0).toString().trimmed().isEmpty()){
                                        _montoAGrabar=queryPie.value(0).toString();
                                    }
                                    painter.drawText(cuadro(query.value(0).toDouble(),query.value(1).toDouble(),query.value(2).toDouble(),1,query.value(4).toBool()),query.value(3).toInt(),query.value(6).toString()+" "+_montoAGrabar+" "+query.value(7).toString());
                                }

                            }
                        }
                    }
                }else{return false;}

            }
            painter.end();
        }

        return true;

    }
}





//################################################################################
//######## Calcula en centimetros la posicion de los campos a imprimirse #########
//################################################################################
QRectF cuadro(double x, double y, double ancho, double alto,bool justifica=false){

    QRectF punto(x*centimetro,y*centimetro,ancho*centimetro,alto*centimetro);
    if(justifica){

        if(x>ancho)
            punto=QRect((x*centimetro)-(ancho*centimetro),y*centimetro,ancho*centimetro,alto*centimetro);

    }
    return punto;
}
QRectF cuadroA4(double x, double y, double ancho, double alto,bool justifica=false){

    QRectF punto(x*centimetro,(y+15)*centimetro,ancho*centimetro,alto*centimetro);
    if(justifica){

        if(x>ancho)
            punto=QRect((x*centimetro)-(ancho*centimetro),(y+15)*centimetro,ancho*centimetro,alto*centimetro);

    }
    return punto;
}

QRectF cuadroTicketRight(double x, double y, double ancho, double alto, QString dato){


    double desplazamientoIzquierdaFuente=0.00;
    if(fuente.pointSize()==12){

        desplazamientoIzquierdaFuente=(double)dato.length()*(0.07+(((double)dato.length()/800)-0.001));
    }

    double frame = (double)dato.count(QLatin1Char('1'))*0.006;

    frame += (double)dato.count(QLatin1Char('-'))*0.006;

    if(dato.count(QLatin1Char('1'))==0 && dato.count(QLatin1Char('-'))==0)
        frame=0.0;

    dato=dato.replace(".","").replace(",","").replace(":","").replace(";","").replace("|","");

    if(QString(dato).length()>9){
        ancho =    (((double)QString(dato).length())*0.279) -(((double)QString(dato).length()/10)/2) -frame + desplazamientoIzquierdaFuente;

    }else if(QString(dato).length()==3){
        ancho =    (((double)QString(dato).length())*0.42)-frame + desplazamientoIzquierdaFuente;
    }
    else if(QString(dato).length()==4){
        ancho =    (((double)QString(dato).length())*0.355)-frame + desplazamientoIzquierdaFuente;
    }
    else if(QString(dato).length()==5){
        ancho =    (((double)QString(dato).length())*0.321)-frame + desplazamientoIzquierdaFuente;
    }
    else if(QString(dato).length()==6){
        ancho =    (((double)QString(dato).length())*0.30)-frame + desplazamientoIzquierdaFuente;
    }
    else if(QString(dato).length()==7){
        ancho =    (((double)QString(dato).length())*0.28)-frame+ desplazamientoIzquierdaFuente;
    }
    else if(QString(dato).length()==8){
        ancho =    (((double)QString(dato).length())*0.2679)-frame+ desplazamientoIzquierdaFuente;
    }
    else if(QString(dato).length()==9){
        ancho =    (((double)QString(dato).length())*0.26)-frame+ desplazamientoIzquierdaFuente;
    }
    else{
        ancho =    (((double)QString(dato).length())*0.28)-frame + desplazamientoIzquierdaFuente;
    }

    QRectF punto(x*centimetro,y*centimetro,ancho*centimetro,alto*centimetro);

    if(x>ancho)
        punto=QRect((x*centimetro)-(ancho*centimetro),y*centimetro,ancho*centimetro,alto*centimetro);


    return punto;
}



bool procesarImix(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento){

    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);

    QString str1 = crearJsonIMIX(_codigoDocumento, _codigoTipoDocumento,_serieDocumento);



    funcion.loguear("Modo CFE Imix: \n\nEnvio a Imix:\n"+str1+"\n\n");

    if(str1=="-1"){

        funcion.loguear("ERROR: \nNo existe documento para enviar como CFE");
        funcion.mensajeAdvertenciaOk("ERROR: \nNo existe documento para enviar como CFE");
        return false;
    }else if(str1=="-2"){
        funcion.loguear("ERROR: \nNo se puede ejecutar la consulta a la base de datos");
        funcion.mensajeAdvertenciaOk("ERROR: \nNo se puede ejecutar la consulta a la base de datos");
        return false;
    }else if(str1=="-3"){
        funcion.loguear("ERROR: \nNo hay conexión con la base de datos");
        funcion.mensajeAdvertenciaOk("ERROR: \nNo hay conexión con la base de datos");
        return false;
    }


    numeroDocumentoV=_codigoDocumento;
    codigoTipoDocumentoV=_codigoTipoDocumento;
    serieDocumentoV=_serieDocumento;

    //  qDebug()<<str1;

    QByteArray baddddd = str1.toUtf8();
    const char *mensajeAEnviarPost = baddddd.data();


    // qDebug()<< mensajeAEnviarPost;

    struct curl_slist *headers=NULL; // init to NULL is important
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charsets: utf-8");

    curl = curl_easy_init();
    if(curl) {

        resultadoFinal="";
        QByteArray testing;
        QByteArray produccion;


        if(func_configuracion.retornaValorConfiguracionValorString("USA_PRINCIPAL_LOGUEO_IP")=="1" && func_configuracion.retornaValorConfiguracionValorString("USA_IP_IMIX_LOCAL")=="1"){
            QString ipPcPrincipal=func_configuracion.retornaValorConfiguracionValorString("IP_PRINCIPAL_PC");

            testing =    func_CFE_ParametrosGenerales.retornaValor("urlImixTesting").replace("localhost", ipPcPrincipal).toLatin1();
            produccion = func_CFE_ParametrosGenerales.retornaValor("urlImixProduccion").replace("localhost", ipPcPrincipal).toLatin1();

        }else{

            testing =    func_CFE_ParametrosGenerales.retornaValor("urlImixTesting").toLatin1();
            produccion = func_CFE_ParametrosGenerales.retornaValor("urlImixProduccion").toLatin1();

        }



        const char *c_conexion;
        if(func_CFE_ParametrosGenerales.retornaValor("modoTrabajoCFE")=="0"){
            c_conexion=testing.data();
        }else{
            c_conexion=produccion.data();
        }

        curl_easy_setopt(curl, CURLOPT_URL, c_conexion);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 120L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST,1);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(mensajeAEnviarPost));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, mensajeAEnviarPost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);


        res = curl_easy_perform(curl);

        if(res != CURLE_OK){

            QString resultadoError=curl_easy_strerror(res);

            if(resultadoError.trimmed()=="Couldn't resolve host name" || resultadoError.trimmed()=="Couldn't connect to server"){
                //  funcion.loguear("ERROR: No hay conexión con Imix: \n\n"+(QString)c_conexion);
                funcion.mensajeAdvertenciaOk("ERROR: No hay conexión con Imix: \n\n"+(QString)c_conexion);
            }else{
                //  funcion.loguear("ERROR: "+resultadoError+"\n\nConexión: \n\n"+(QString)c_conexion);
                funcion.mensajeAdvertenciaOk("ERROR: "+resultadoError+"\n\nConexión: \n\n"+(QString)c_conexion);
            }

            return false;
        }
        else {

            resultadoFinal =  resultadoFinal.remove(resultadoFinal.length()-1,1);
            //   qDebug() <<resultadoFinal;
            //   qDebug() <<"Salio todo divino";
            return true;

        }
        curl_easy_cleanup(curl);
    }
    else{
        return false;
    }
    curl_global_cleanup();



}


QString crearJsonIMIX(QString _codigoDocumento,QString _codigoTipoDocumento, QString _serieDocumento){

    bool concatenaCodigoArticuloyDescripcion=false;
    if(func_CFE_ParametrosGenerales.retornaValor("articuloUsaConcatenacionImix")=="1"){
        concatenaCodigoArticuloyDescripcion=true;
    }


    QString consultaSql = " SELECT ";
    consultaSql +=" TD.descripcionTipoDocumentoCFE'Comprobante', ";
    consultaSql +=" DOC.serieDocumento'Serie', ";
    consultaSql +=" DOC.codigoDocumento'Numero', ";
    consultaSql +=" UNIX_TIMESTAMP(STR_TO_DATE(DOC.fechaEmisionDocumento, '%Y-%m-%d '))'Fecha', ";
    consultaSql +=" case when DOC.tipoCliente=1 then  DOC.codigoCliente else 'null' end 'Cliente', ";
    consultaSql +=" case when DOC.tipoCliente=2 then  DOC.codigoCliente else 'null' end 'Proveedor', ";
    consultaSql +=" left(trim(CLI.razonSocial),32) 'RazonSocial', ";
    consultaSql +=" left(trim(CLI.direccion),32) 'Direccion',     ";

    consultaSql +=" case when CLI.rut is null then 'null' else case when CLI.codigoTipoDocumentoCliente=2 then 'null' else case when CLI.codigoTipoDocumentoCliente in (3,4,5,6) and (CLI.rut is not null and trim(CLI.rut)!='') then  CLI.rut else 'null'end end end 'Documento',";
    consultaSql +=" case when CLI.codigoTipoDocumentoCliente in (4,5,6) then PA.codigoIsoPais else 'null' end 'PaisDocumento',";
    consultaSql +=" case when CLI.codigoTipoDocumentoCliente in (4,5,6) then CLI.codigoTipoDocumentoCliente else 'null' end 'TipoDocumento',";
    consultaSql +=" case when CLI.rut is null then 'null' else case when CLI.codigoTipoDocumentoCliente = 2 then CLI.rut else 'null' end end 'Rut',";


    //consultaSql +=" case when CLI.rut is null then 'null' else CLI.rut end 'Documento', ";
    //consultaSql +=" case when CLI.rut is null then 'null' else case when CLI.codigoTipoDocumentoCliente in (2,3) then 'null' else PA.codigoIsoPais end end 'PaisDocumento', ";
    //consultaSql +=" case when CLI.rut is null then 'null' else case when CLI.codigoTipoDocumentoCliente in (2,3) then 'null' else CFETDC.descripcionTipoDocumentoCliente end end 'TipoDocumento', ";
    //consultaSql +=" case when CLI.rut is null then 'null' else case when CLI.codigoTipoDocumentoCliente = 2 then CLI.rut else 'null' end end 'Rut', ";

    consultaSql +=" MO.codigoISO4217'Moneda', ";
    consultaSql +=" left(DOC.porcentajeDescuentoAlTotal/100,6)'PorcentajeDescuento',     ";
    consultaSql +=" DOC.precioTotalVenta'Total',    ";

    consultaSql +=" DL.codigoArticulo'Articulo', ";
    consultaSql +=" left(trim(AR.descripcionArticulo),32)'Descripcion', ";
    consultaSql +=" DL.cantidad'Cantidad', ";
    consultaSql +=" DL.precioArticuloUnitario'Precio', ";
    consultaSql +=" concat('N° ',DOC.codigoDocumento, ' - ',left(trim(DOC.observaciones),48))'Observaciones',  ";
    consultaSql +=" TD.TipoTrasladoRemito'TipoTrasladoRemito',  ";
    consultaSql +=" AR.codigoIva'codigoIva',  ";
    consultaSql +=" IV.codigoIvaCFE'codigoIvaCFE', ";
    consultaSql +=" DOC.formaDePago'formaDePago', ";
    consultaSql +=" concat(DE.descripcionDepartamento,'-',LO.descripcionLocalidad)'Ciudad' ";

    consultaSql +=" FROM DocumentosLineas DL      ";
    consultaSql +=" join Documentos DOC on DOC.codigoDocumento=DL.codigoDocumento and DOC.codigoTipoDocumento=DL.codigoTipoDocumento and DOC.serieDocumento=DL.serieDocumento ";
    consultaSql +=" join Articulos AR on AR.codigoArticulo=DL.codigoArticulo ";
    consultaSql +=" join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento ";
    consultaSql +=" join Monedas MO on MO.codigoMoneda = DOC.codigoMonedaDocumento ";
    consultaSql +=" join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente ";
    consultaSql +=" join Localidades LO on LO.codigoPais=CLI.codigoPais and LO.codigoDepartamento=CLI.codigoDepartamento and LO.codigoLocalidad=CLI.codigoLocalidad join Departamentos DE on DE.codigoPais=CLI.codigoPais and DE.codigoDepartamento=CLI.codigoDepartamento ";
    consultaSql +=" join CFE_TipoDocumentoCliente CFETDC on CFETDC.codigoTipoDocumentoCliente=CLI.codigoTipoDocumentoCliente ";
    consultaSql +=" join Pais PA on PA.codigoPais=CLI.codigoPais ";
    consultaSql +=" join Ivas IV on IV.codigoIva=AR.codigoIva ";
    consultaSql +=" where DOC.codigoDocumento="+_codigoDocumento+" and DOC.codigoTipoDocumento="+_codigoTipoDocumento+" and DOC.serieDocumento='"+_serieDocumento+"' and DOC.esDocumentoCFE='1' ";


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
        if(query.exec(consultaSql)) {
            if(query.first()){
                //  QString j=  "{\"Cliente\":\"1\",\"Comprobante\":\"Venta Contado\",\"Direccion\":\"Direccion del cliente\",\"Emitir\":true,\"Fecha\":\"/Date(1504666800)/\",\"Lineas\":[{\"Articulo\":\"2\",\"Cantidad\":1,\"Descripcion\":\"pepe\",\"Precio\":150},{\"Articulo\":\"1\",\"Cantidad\":1,\"Descripcion\":\"pepe\",\"Precio\":150}],\"Moneda\":\"UYU\",\"Numero\":\"207\",\"Observaciones\":\"\",\"PaisDocumento\":\"UY\",\"PorcentajeDescuento\":0.0,\"Proveedor\":\"10\",\"RazonSocial\":\"Demostracion\",\"Rut\":\"222245432128\",\"Serie\":\"B\",\"TipoDeTraslado\":1,\"TipoDocumento\":0,\"Total\":300}";

                //Variables cabezal:
                QString Comprobante=query.value(0).toString().replace("\n","");
                //    QString Serie=query.value(1).toString();
                //    QString Numero=query.value(2).toString();
                QString Fecha=query.value(3).toString().replace("\n","");
                QString Cliente=query.value(4).toString().replace("\n","");
                QString Proveedor=query.value(5).toString().replace("\n","");
                QString RazonSocial=query.value(6).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");



                QString Direccion=query.value(7).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                QString Documento=query.value(8).toString().replace("\n","");
                QString PaisDocumento=query.value(9).toString().replace("\n","");
                QString TipoDocumento=query.value(10).toString().replace("\n","");
                QString Rut=query.value(11).toString().replace("\n","");
                QString Moneda=query.value(12).toString().replace("\n","");
                QString PorcentajeDescuento=query.value(13).toString();
                QString Total=query.value(14).toString();
                QString Observacion=query.value(19).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                QString TipoTrasladoRemito=query.value(20).toString();

                QString FormaDePago=query.value(23).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                QString Ciudad=query.value(24).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");

                QString ClienteOProveedor="Cliente";
                QString DatoDocumento=",\"Documento\":\""+Documento+"\"";
                QString DatoPaisDocumento=",\"PaisDocumento\":\""+PaisDocumento+"\"";
                QString DatoTipoDocumento=",\"TipoDocumento\":"+TipoDocumento+"";
                QString DatoRut= ",\"Rut\":\""+Rut+"\"";

                QString DatoFecha= ",\"Fecha\":\"/Date("+Fecha+")/\"";

                QString DatoTipoDeTraslado=",\"TipoDeTraslado\":"+TipoTrasladoRemito+"";







                DatoFecha="";

                if(Cliente=="null"){
                    Cliente=Proveedor;
                    ClienteOProveedor="Proveedor";
                }

                if(func_CFE_ParametrosGenerales.retornaValor("envioClienteGenerico")=="1"){
                    Cliente="1";
                }


                if(func_CFE_ParametrosGenerales.retornoValorPatrametro("envioCiudadEnDireccion")=="1"){
                    Direccion=Direccion+"-"+Ciudad;
                }



                if(Documento=="null")
                    DatoDocumento="";

                if(PaisDocumento=="null")
                    DatoPaisDocumento="";

                if(TipoDocumento=="null")
                    DatoTipoDocumento="";


                if(TipoTrasladoRemito=="0")
                    DatoTipoDeTraslado="";

                if(Rut=="null")
                    DatoRut="";

                QString cabezal = "{\""+ClienteOProveedor+"\":\""+Cliente+"\",\"Comprobante\":\""+Comprobante+"\",\"Adicional\":\""+FormaDePago+"\",\"Direccion\":\""+Direccion+"\",\"Emitir\":true "+DatoFecha+" ";

                QString pie = ""+DatoDocumento+",\"Moneda\":\""+Moneda+"\",\"Observaciones\":\""+Observacion+"\""+DatoPaisDocumento+",\"PorcentajeDescuento\":"+PorcentajeDescuento+",\"RazonSocial\":\""+RazonSocial+"\""+DatoRut+DatoTipoDeTraslado+DatoTipoDocumento+",\"Total\":"+Total+"}";

                //,\"Serie\":\""+Serie+"\"

                //\"Numero\":\""+Numero+"\"

                QString Lineas= " ,\"Lineas\":[ ";

                query.previous();
                int i=0;
                QString codigoArticuloCargado="";

                while (query.next()){

                    if(i!=0){
                        Lineas += " , ";
                    }
                    codigoArticuloCargado=query.value(15).toString();

                    if(func_CFE_ParametrosGenerales.retornaValor("envioArticuloClienteGenerico")=="1"){

                        // Utilizo el mapeo de iva del campo codigoIvaCFE para enviar a Imix utilizado como articulo
                        QString codigoIvaCFE=query.value(22).toString();

                        codigoArticuloCargado=codigoIvaCFE;

                    }

                    QString textoConcatenado="";
                    if(concatenaCodigoArticuloyDescripcion){

                        // Relleno el codigo del articulo con ceros a la izquierda para que el texto quede parejo.
                        QString valor=query.value(15).toString();;
                        for (int var = valor.length(); var < 6; ++var) {
                            valor="0"+valor;
                        }
                        textoConcatenado=valor+" - ";
                    }


                    Lineas += "{\"Articulo\":\""+codigoArticuloCargado+"\",\"Cantidad\":"+query.value(17).toString()+",\"Descripcion\":\""+textoConcatenado+query.value(16).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","")+"\",\"Precio\":"+query.value(18).toString()+"}";
                    i=1;

                }
                Lineas += "] ";

                QString ok=cabezal + Lineas + pie;

                return ok;//QString::fromUtf8(ok.toUtf8());

            }else{
                return "-1"; //No existe documento para enviar como CFE
            }
        }else{
            return "-2";//No se puede ejecutar la consulta a la base de datos
        }
    }else{
        return "-3"; //No hay conexión con la base de datos
    }
}



bool procesarImix_Nube(QString _codigoDocumento,QString _codigoTipoDocumento,QString _numeroDocumentoCFEADevolver,QString _fechaDocumentoCFEADevolver, QString tipoDocumentoCFEADevolver, QString _serieDocumento){

    qDebug()<< "procesarImix_Nube";

    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);

    QString str1 = crearJsonImix_Nube(_codigoDocumento, _codigoTipoDocumento,_numeroDocumentoCFEADevolver,_fechaDocumentoCFEADevolver, tipoDocumentoCFEADevolver, _serieDocumento);


    if(str1=="-1"){
        funcion.mensajeAdvertenciaOk("ERROR: \nNo existe documento para enviar como CFE");
        return false;
    }else if(str1=="-2"){
        funcion.mensajeAdvertenciaOk("ERROR: \nNo se puede ejecutar la consulta a la base de datos");
        return false;
    }else if(str1=="-3"){
        funcion.mensajeAdvertenciaOk("ERROR: \nNo hay conexión con la base de datos");
        return false;
    }else if(str1=="-4"){
        funcion.mensajeAdvertenciaOk("ERROR: \nEl documento PASSAPORTE es obligatorio");
        return false;
    }else if(str1=="-5"){
        funcion.mensajeAdvertenciaOk("ERROR: \nDocumento DNI es obligatorio para el pais del cliente");
        return false;
    }else if(str1=="-6"){
        funcion.mensajeAdvertenciaOk("ERROR: \nMonto mayor a 10000UI, se requiere documento");
        return false;
    }else if(str1=="-7"){
        funcion.mensajeAdvertenciaOk("ERROR: \nError en tipo de documento CFE en khitomer.TipoDocumento");
        return false;
    }else if(str1=="-8"){
        funcion.mensajeAdvertenciaOk("ERROR: \nNo se puede anular un documento que no fue emitido como CFE.");
        return false;
    }


    numeroDocumentoV=_codigoDocumento;
    codigoTipoDocumentoV=_codigoTipoDocumento;
    serieDocumentoV=_serieDocumento;

    // Consulto si voy a pasar por el proxy
    if(func_configuracion.retornaValorConfiguracionValorString("UTILIZA_PROXY_PARA_CFE")=="1"){
        funcion.loguear("Modo CFE Imix: \n\nEnvio a Imix en la Nube a travez del proxy:\n"+str1+"\n\n");


        QString nuevoSegmento = ",\"Documento\":{\"codigo\":"+_codigoDocumento+",\"tipo\":"+_codigoTipoDocumento+",\"serie\":\""+_serieDocumento+"\",\"caeTipoDocumentoCFEDescripcionV\":\""+caeTipoDocumentoCFEDescripcionV+"\"}";


        #ifdef Q_OS_WIN
            // En Windows usas la sintaxis tradicional (sin raw string literal)
            str1 = QString("{\"Informacion\":%1}").arg(str1);
        #else
            // En Linux o cualquier otro SO
            str1 = QString(R"({"Informacion":%1})").arg(str1);
        #endif

        int posicionCierre = str1.lastIndexOf('}');
        if (posicionCierre != -1) {
            str1.insert(posicionCierre, nuevoSegmento);
        }

        qDebug() << str1;
        bool resultado = enviarYConsultarRespuesta(str1.toUtf8());

        return resultado;
    }else{

        funcion.loguear("Modo CFE Imix: \n\nEnvio a Imix en la Nube:\n"+str1+"\n\n");



        qDebug()<<str1;

        QByteArray baddddd = str1.toUtf8();
        const char *mensajeAEnviarPost = baddddd.data();

        struct curl_slist *headers=NULL; // init to NULL is important
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charsets: utf-8");

        curl = curl_easy_init();

        if(curl) {

            resultadoFinal="";

            QByteArray testing =    func_CFE_ParametrosGenerales.retornaValor("urlImixTesting").toLatin1();
            QByteArray produccion = func_CFE_ParametrosGenerales.retornaValor("urlImixProduccion").toLatin1();


            const char *c_produccion;

            if(func_CFE_ParametrosGenerales.retornaValor("modoTrabajoCFE")=="0"){
                c_produccion=testing.data();
            }else{
                c_produccion=produccion.data();
            }

            curl_easy_setopt(curl, CURLOPT_URL, c_produccion);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 120L);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_HTTPPOST,1);
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(mensajeAEnviarPost));
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, mensajeAEnviarPost);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writerImix_Nube);



            res = curl_easy_perform(curl);

            if(res != CURLE_OK){

                QString resultadoError=curl_easy_strerror(res);

                funcion.loguear("RESULTADO: "+resultadoError.trimmed());


                if(resultadoError.trimmed()=="Couldn't resolve host name" || resultadoError.trimmed()=="Couldn't connect to server"){
                    funcion.mensajeAdvertenciaOk("ERROR: No hay conexión con Imix_Nube: \n\n"+(QString)produccion.data());
                }else{
                    funcion.mensajeAdvertenciaOk("ERROR: "+resultadoError+"\n\nConexión: \n\n"+(QString)produccion.data());
                }

                return false;
            }
            else {


                bool ok;
                // json is a QString containing the JSON data
                QtJson::JsonObject result = QtJson::parse(resultadoFinal, ok).toMap();

                if(!ok) {
                    funcion.loguear("Respuesta Imix_nube:\n"+resultadoFinal);
                    funcion.mensajeAdvertenciaOk("Error en parseo de información desde Imix_nube:\n\nMensaje devuelto: "+resultadoFinal);
                    return false;
                }

                /*
                {
                  "CaeDesde": 1,
                  "CaeHasta": 1000,
                  "CaeNumero": "123",
                  "DigestValue": "EqRa5c7yHYspqqq9cLaXNkaLzbI=",
                  "Id": 1048198,
                  "Numero": 50,
                  "Serie": "A",
                  "TextoVencimiento": "2020-12-26",
                  "TipoCfe": 111,
                  "Total": 100.00,
                  "Vencimiento": "\/Date(1608951600000-0300)\/"
                }

                */


                QString TipoCfe=result["TipoCfe"].toString();
                QString Numero=result["Numero"].toString();
                QString Serie=result["Serie"].toString();
                QString Total=result["Total"].toString();
                QString DigestValue=result["DigestValue"].toString();
                QString Vencimiento=result["TextoVencimiento"].toString();

                QString CaeDesde=result["CaeDesde"].toString();
                QString CaeHasta=result["CaeHasta"].toString();
                QString CaeNumero=result["CaeNumero"].toString();

                QString Id=result["Id"].toString();


                QString codigoSeguridad = DigestValue.mid(0,6);


                /*qDebug()<< result["CaeDesde"].toString();
                qDebug()<< result["CaeHasta"].toString();
                qDebug()<< result["CaeNumero"].toString();
                qDebug()<< result["DigestValue"].toString();
                qDebug()<< result["Id"].toString();
                qDebug()<< result["TipoCfe"].toString();
                qDebug()<< result["Total"].toString();
                qDebug()<< result["TextoVencimiento"].toString();*/

                QString rut = func_CFE_ParametrosGenerales.retornoValorPatrametro("rutEmpresa");

                QString fechaEmision=   funcion.fechaDeHoyCFE();


                QString QR ="";
                //"https://www.efactura.dgi.gub.uy/consultaQR/cfe?<Rut>,<TipoCfe>,<Serie>,<Numero>,<Total>,<FechaEmision>,<DigestValue>"

#if linux
                QR = QrCode::obtengoQr("https://www.efactura.dgi.gub.uy/consultaQR/cfe?"+rut.trimmed()+","+TipoCfe.trimmed()+","+Serie.trimmed()+","+Numero.trimmed()+","+Total.trimmed()+","+fechaEmision.trimmed()+","+DigestValue.trimmed()+" ");
#else
                QR ="";
#endif


                /// PRUEBA
                //return false;


                if(result["CaeDesde"].toString().trimmed()!="" && result["CaeDesde"].toString().trimmed()!="0"){

                    ModuloDocumentos modeloDocumento;

                    if(modeloDocumento.actualizarInformacionCFEDocumentoDynamia(_codigoDocumento, _codigoTipoDocumento,
                                                                                Numero.trimmed(),
                                                                                Serie.trimmed(),
                                                                                Vencimiento.trimmed(),
                                                                                codigoSeguridad.trimmed(),
                                                                                CaeNumero.trimmed(),
                                                                                CaeDesde.trimmed(),
                                                                                CaeHasta.trimmed(),
                                                                                QR.trimmed(),
                                                                                Id.trimmed(),
                                                                                caeTipoDocumentoCFEDescripcionV,
                                                                                _serieDocumento
                                                                                )){
                        return true;
                    }else{
                        return false;
                    }
                }else{

                    funcion.mensajeAdvertenciaOk("ERROR: \n Respuesta con error desde Imix_nube.");
                    return false;
                }
            }
            curl_easy_cleanup(curl);
        }
        else{
            return false;
        }
        curl_global_cleanup();

    }



}


QString crearJsonImix_Nube(QString _codigoDocumento, QString _codigoTipoDocumento, QString _numeroDocumentoCFEADevolver, QString _fechaDocumentoCFEADevolver, QString tipoDocumentoCFEADevolver, QString _serieDocumento){


    qDebug()<< "crearJsonImix_Nube";


    bool concatenaCodigoArticuloyDescripcion=false;
    if(func_CFE_ParametrosGenerales.retornaValor("articuloUsaConcatenacionImix")=="1"){
        concatenaCodigoArticuloyDescripcion=true;
    }


    QString consultaSql = " SELECT ";
    consultaSql +=" TD.descripcionTipoDocumentoCFE'Comprobante', ";
    consultaSql +=" DOC.serieDocumento'Serie', ";
    consultaSql +=" DOC.codigoDocumento'Numero', ";
    consultaSql +=" UNIX_TIMESTAMP(STR_TO_DATE(DOC.fechaEmisionDocumento, '%Y-%m-%d '))'Fecha', ";
    consultaSql +=" case when DOC.tipoCliente=1 then  DOC.codigoCliente else 'null' end 'Cliente', ";
    consultaSql +=" case when DOC.tipoCliente=2 then  DOC.codigoCliente else 'null' end 'Proveedor', ";
    consultaSql +=" left(trim(CLI.razonSocial),32) 'RazonSocial', ";
    consultaSql +=" left(trim(CLI.direccion),32) 'Direccion',     ";

    consultaSql +=" case when CLI.rut is null then 'null' else case when CLI.codigoTipoDocumentoCliente=2 then 'null' else case when CLI.codigoTipoDocumentoCliente in (3,4,5,6) and (CLI.rut is not null and trim(CLI.rut)!='') then  CLI.rut else 'null'end end end 'Documento',";
    consultaSql +=" case when CLI.codigoTipoDocumentoCliente in (4,5,6) then PA.codigoIsoPais else 'null' end 'PaisDocumento',";
    consultaSql +=" case when CLI.codigoTipoDocumentoCliente in (4,5,6) then CLI.codigoTipoDocumentoCliente else 'null' end 'TipoDocumento',";
    consultaSql +=" case when CLI.rut is null then 'null' else case when CLI.codigoTipoDocumentoCliente = 2 then CLI.rut else 'null' end end 'Rut',";

    consultaSql +=" MO.codigoISO4217'Moneda', ";
    consultaSql +=" left(DOC.porcentajeDescuentoAlTotal/100,6)'PorcentajeDescuento',     ";
    consultaSql +=" DOC.precioTotalVenta'Total',    ";

    consultaSql +=" DL.codigoArticulo'Articulo', ";
    consultaSql +=" left(trim(AR.descripcionArticulo),32)'Descripcion', ";
    consultaSql +=" DL.cantidad'Cantidad', ";
    consultaSql +=" DL.precioArticuloUnitario'Precio', ";
    consultaSql +=" concat('N° ',DOC.codigoDocumento, ' - ',left(trim(DOC.observaciones),48))'Observaciones',  ";
    consultaSql +=" TD.TipoTrasladoRemito'TipoTrasladoRemito',  ";
    consultaSql +=" AR.codigoIva'codigoIva',  ";
    consultaSql +=" IV.codigoIvaCFE'codigoIvaCFE', ";
    consultaSql +=" DOC.formaDePago'formaDePago', ";
    consultaSql +=" concat(DE.descripcionDepartamento,'-',LO.descripcionLocalidad)'Ciudad' , ";
    consultaSql +=" CLI.codigoTipoDocumentoCliente ";



    consultaSql +=" FROM DocumentosLineas DL      ";
    consultaSql +=" join Documentos DOC on DOC.codigoDocumento=DL.codigoDocumento and DOC.codigoTipoDocumento=DL.codigoTipoDocumento and DOC.serieDocumento=DL.serieDocumento ";
    consultaSql +=" join Articulos AR on AR.codigoArticulo=DL.codigoArticulo ";
    consultaSql +=" join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento ";
    consultaSql +=" join Monedas MO on MO.codigoMoneda = DOC.codigoMonedaDocumento ";
    consultaSql +=" join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente ";
    consultaSql +=" join Localidades LO on LO.codigoPais=CLI.codigoPais and LO.codigoDepartamento=CLI.codigoDepartamento and LO.codigoLocalidad=CLI.codigoLocalidad join Departamentos DE on DE.codigoPais=CLI.codigoPais and DE.codigoDepartamento=CLI.codigoDepartamento ";
    consultaSql +=" join CFE_TipoDocumentoCliente CFETDC on CFETDC.codigoTipoDocumentoCliente=CLI.codigoTipoDocumentoCliente ";
    consultaSql +=" join Pais PA on PA.codigoPais=CLI.codigoPais ";
    consultaSql +=" join Ivas IV on IV.codigoIva=AR.codigoIva ";
    consultaSql +=" where DOC.codigoDocumento="+_codigoDocumento+" and DOC.codigoTipoDocumento="+_codigoTipoDocumento+" and DOC.serieDocumento='"+_serieDocumento+"' and DOC.esDocumentoCFE='1' ";


    QString clave =func_CFE_ParametrosGenerales.retornoValorPatrametro("password");
    QString claveEmpresa =func_CFE_ParametrosGenerales.retornoValorPatrametro("claveEmpresaImix");
    QString empresa =func_CFE_ParametrosGenerales.retornoValorPatrametro("empresaImix");
    QString usuario = func_CFE_ParametrosGenerales.retornoValorPatrametro("username");

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
        if(query.exec(consultaSql)) {
            if(query.first()){


                qDebug()<< "Tipo documento: "+ query.value(10).toString();



                //Variables cabezal:
                QString Comprobante=query.value(0).toString().replace("\n","");
                QString Fecha=query.value(3).toString().replace("\n","");
                QString Cliente=query.value(4).toString().replace("\n","");
                QString Proveedor=query.value(5).toString().replace("\n","");
                QString RazonSocial=query.value(6).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");



                QString Direccion=query.value(7).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                QString Documento=query.value(8).toString().replace("\n","");
                QString PaisDocumento=query.value(9).toString().replace("\n","");
                QString TipoDocumento=query.value(10).toString().replace("\n","");
                QString Rut=query.value(11).toString().replace("\n","");
                QString Moneda=query.value(12).toString().replace("\n","");
                QString PorcentajeDescuento=query.value(13).toString();
                QString Total=query.value(14).toString();
                QString Observacion=query.value(19).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                QString TipoTrasladoRemito=query.value(20).toString();

                QString FormaDePago=query.value(23).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                QString Ciudad=query.value(24).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                QString codigoTipoDocumentoCliente=query.value(25).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");

                if(Rut=="null"){

                }else{
                    if(codigoTipoDocumentoCliente=="2"){
                        TipoDocumento="2";
                    }

                }


                if(codigoTipoDocumentoCliente=="3"){

                    qDebug()<< Documento;
                    qDebug()<< Documento.trimmed().length();


                    if(Documento!="null"){

                        QString nuevaCedula = funcion.verificarCedula(Documento);

                        if(nuevaCedula=="-1ERROR"){
                            return "-1";
                        }else{
                            Documento=nuevaCedula;
                        }
                    }

                }else if(codigoTipoDocumentoCliente=="2"){
                    if(Rut=="null" || Rut.trimmed()==""){
                        funcion.mensajeAdvertenciaOk("ATENCION:...El Rut del cliente no puede estar vacio");
                        return "-1";
                    }
                }


                QString ClienteOProveedor="Cliente";
                QString DatoDocumento=",\"Documento\":\""+Documento+"\"";
                QString DatoPaisDocumento=",\"PaisDocumento\":\""+PaisDocumento+"\"";
                QString DatoTipoDocumento=",\"TipoDocumento\":"+TipoDocumento+"";
                QString DatoRut= ",\"Rut\":\""+Rut+"\"";

                QString DatoFecha= ",\"Fecha\":\"/Date("+Fecha+")/\"";

                QString DatoTipoDeTraslado=",\"TipoDeTraslado\":"+TipoTrasladoRemito+"";


                if(Comprobante=="Venta contado" || Comprobante=="Venta contado exenta"  || Comprobante== "VENTA CONTADO EXENTA" ){

                    caeTipoDocumentoCFEDescripcionV="e-Ticket";

                }else if(Comprobante=="Venta credito" || Comprobante=="Venta crédito" || Comprobante=="Venta credito exenta" || Comprobante=="Venta crédito exenta" || Comprobante=="VENTA CRÉDITO EXENTA"){

                    caeTipoDocumentoCFEDescripcionV="e-Ticket";

                }else if(Comprobante=="Devolucion venta" || Comprobante=="Devolución venta" || Comprobante=="Devolucion venta exenta" || Comprobante=="Dev venta exenta" || Comprobante=="Devolución venta exenta" || Comprobante== "DV EXENTA"){

                    caeTipoDocumentoCFEDescripcionV="Nota de Crédito de e-Ticket";

                }else if(Comprobante=="Nota credito venta" || Comprobante=="Nota crédito venta" || Comprobante=="Nota credito venta exenta" || Comprobante=="NC crédito venta exenta" || Comprobante=="NC credito venta exenta"  || Comprobante== "NC VTA EXENTA"){

                    caeTipoDocumentoCFEDescripcionV="Nota de Crédito de e-Ticket";

                }else{
                    return "-1"; //Error en tipo documento CFE en khitomer.TipoDocumento
                }




                if(TipoDocumento=="2"){

                    if(Comprobante=="Venta contado" || Comprobante=="Venta contado exenta"  || Comprobante== "VENTA CONTADO EXENTA"){

                        caeTipoDocumentoCFEDescripcionV="e-Factura";

                    }else if(Comprobante=="Venta credito" || Comprobante=="Venta crédito" || Comprobante=="Venta credito exenta" || Comprobante=="Venta crédito exenta" || Comprobante=="VENTA CRÉDITO EXENTA"){

                        caeTipoDocumentoCFEDescripcionV="e-Factura";

                    }else if(Comprobante=="Devolucion venta" || Comprobante=="Devolución venta" || Comprobante=="Devolucion venta exenta" || Comprobante=="Dev venta exenta" || Comprobante=="Devolución venta exenta" || Comprobante== "DV EXENTA"){

                        caeTipoDocumentoCFEDescripcionV="Nota de Crédito de e-Factura";

                    }else if(Comprobante=="Nota credito venta" || Comprobante=="Nota crédito venta" || Comprobante=="Nota credito venta exenta" || Comprobante=="NC crédito venta exenta" || Comprobante=="NC credito venta exenta" || Comprobante== "NC VTA EXENTA"){

                        caeTipoDocumentoCFEDescripcionV="Nota de Crédito de e-Factura";

                    }else{
                        return "-1"; //Error en tipo documento CFE en khitomer.TipoDocumento
                    }

                }














                DatoFecha="";

                if(Cliente=="null"){
                    Cliente=Proveedor;
                    ClienteOProveedor="Proveedor";
                }

                if(func_CFE_ParametrosGenerales.retornaValor("envioClienteGenerico")=="1"){
                    Cliente="1";
                }


                if(func_CFE_ParametrosGenerales.retornoValorPatrametro("envioCiudadEnDireccion")=="1"){
                    Direccion=Direccion+"-"+Ciudad;
                }



                if(Documento=="null")
                    DatoDocumento="";

                if(PaisDocumento=="null")
                    DatoPaisDocumento="";

                if(TipoDocumento=="null")
                    DatoTipoDocumento="";


                if(TipoTrasladoRemito=="0")
                    DatoTipoDeTraslado="";

                if(Rut=="null")
                    DatoRut="";



                /*
            {
                "Credenciales":{
                    "Clave":"String content",
                    "ClaveEmpresa":"String content",
                    "Empresa":"String content",
                    "Usuario":"String content"
                },
                "Operacion":{
                    "Adicional":"String content",
                    "Cliente":"String content",
                    "Comprobante":"String content",
                    "Direccion":"String content",
                    "Documento":"String content",
                    "Emitir":true,
                    "Fecha":"\/Date(928160400000-0300)\/",
                    "Lineas":[{
                        "Articulo":"String content",
                        "Cantidad":12678967.543233,
                        "Descripcion":"String content",
                        "PorcentajeDescuento":12678967.543233,
                        "Precio":12678967.543233
                    }],
                    "Mail":"String content",
                    "Moneda":"String content",
                    "Numero":"String content",
                    "Observaciones":"String content",
                    "PaisDocumento":"String content",
                    "PorcentajeDescuento":12678967.543233,
                    "Proveedor":"String content",
                    "RazonSocial":"String content",
                    "Rut":"String content",
                    "Serie":"String content",
                    "TextoFecha":"String content",
                    "TipoDeCambio":12678967.543233,
                    "TipoDeTraslado":2147483647,
                    "TipoDocumento":0,
                    "Total":12678967.543233
                }
            }
                 *
                 *
                 **/

                QString credenciales="{\"Credenciales\":{\"Clave\":\""+clave+"\",\"ClaveEmpresa\":\""+claveEmpresa+"\",\"Empresa\":\""+empresa+"\",\"Usuario\":\""+usuario+"\"}, ";

                QString cabezal = "\"Operacion\":{\""+ClienteOProveedor+"\":\""+Cliente+"\",\"Comprobante\":\""+Comprobante+"\",\"Adicional\":\""+FormaDePago+"\",\"Direccion\":\""+Direccion+"\",\"Emitir\":true "+DatoFecha+" ";

                QString pie = ""+DatoDocumento+",\"Moneda\":\""+Moneda+"\",\"Numero\":\""+_codigoDocumento+"\",\"Serie\":\""+_serieDocumento+"\",\"Observaciones\":\""+Observacion+"\""+DatoPaisDocumento+",\"PorcentajeDescuento\":"+PorcentajeDescuento+",\"RazonSocial\":\""+RazonSocial+"\""+DatoRut+DatoTipoDeTraslado+DatoTipoDocumento+",\"Total\":"+Total+"}}";


                QString Lineas= " ,\"Lineas\":[ ";

                query.previous();
                int i=0;
                QString codigoArticuloCargado="";

                while (query.next()){

                    if(i!=0){
                        Lineas += " , ";
                    }
                    codigoArticuloCargado=query.value(15).toString();

                    if(func_CFE_ParametrosGenerales.retornaValor("envioArticuloClienteGenerico")=="1"){

                        // Utilizo el mapeo de iva del campo codigoIvaCFE para enviar a Imix utilizado como articulo
                        QString codigoIvaCFE=query.value(22).toString();

                        codigoArticuloCargado=codigoIvaCFE;

                    }

                    QString textoConcatenado="";
                    if(concatenaCodigoArticuloyDescripcion){

                        // Relleno el codigo del articulo con ceros a la izquierda para que el texto quede parejo.
                        QString valor=query.value(15).toString();;
                        for (int var = valor.length(); var < 6; ++var) {
                            valor="0"+valor;
                        }
                        textoConcatenado=valor+" - ";
                    }


                    Lineas += "{\"Articulo\":\""+codigoArticuloCargado+"\",\"Cantidad\":"+query.value(17).toString()+",\"Descripcion\":\""+textoConcatenado+query.value(16).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","")+"\",\"Precio\":"+query.value(18).toString()+"}";
                    i=1;

                }
                Lineas += "] ";

                QString ok=credenciales + cabezal + Lineas + pie;

                return ok;//QString::fromUtf8(ok.toUtf8());

            }else{
                return "-1"; //No existe documento para enviar como CFE
            }
        }else{
            return "-2";//No se puede ejecutar la consulta a la base de datos
        }
    }else{
        return "-3"; //No hay conexión con la base de datos
    }
}



bool procesarDynamia(QString _codigoDocumento,QString _codigoTipoDocumento,QString _numeroDocumentoCFEADevolver,QString _fechaDocumentoCFEADevolver, QString tipoDocumentoCFEADevolver, QString _serieDocumento){


    qDebug()<< "procesarDynamia";

    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);

    QString str1 = crearJsonDynamia(_codigoDocumento, _codigoTipoDocumento,_numeroDocumentoCFEADevolver,_fechaDocumentoCFEADevolver, tipoDocumentoCFEADevolver, _serieDocumento);


    funcion.loguear("Modo CFE Dynamia: \n\nEnvio a Dynamia:\n"+str1+"\n\n");

    if(str1=="-1"){
        funcion.mensajeAdvertenciaOk("ERROR: \nNo existe documento para enviar como CFE");
        return false;
    }else if(str1=="-2"){
        funcion.mensajeAdvertenciaOk("ERROR: \nNo se puede ejecutar la consulta a la base de datos");
        return false;
    }else if(str1=="-3"){
        funcion.mensajeAdvertenciaOk("ERROR: \nNo hay conexión con la base de datos");
        return false;
    }else if(str1=="-4"){
        funcion.mensajeAdvertenciaOk("ERROR: \nEl documento PASSAPORTE es obligatorio");
        return false;
    }else if(str1=="-5"){
        funcion.mensajeAdvertenciaOk("ERROR: \nDocumento DNI es obligatorio para el pais del cliente");
        return false;
    }else if(str1=="-6"){
        funcion.mensajeAdvertenciaOk("ERROR: \nMonto mayor a 10000UI, se requiere documento");
        return false;
    }else if(str1=="-7"){
        funcion.mensajeAdvertenciaOk("ERROR: \nError en tipo de documento CFE en khitomer.TipoDocumento");
        return false;
    }else if(str1=="-8"){
        funcion.mensajeAdvertenciaOk("ERROR: \nNo se puede anular un documento que no fue emitido como CFE.");
        return false;
    }


    numeroDocumentoV=_codigoDocumento;
    codigoTipoDocumentoV=_codigoTipoDocumento;
    serieDocumentoV=_serieDocumento;

    qDebug()<<str1;

    QByteArray baddddd = str1.toUtf8();
    const char *mensajeAEnviarPost = baddddd.data();

    struct curl_slist *headers=NULL; // init to NULL is important
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charsets: utf-8");

    curl = curl_easy_init();

    if(curl) {

        resultadoFinal="";

        QByteArray produccion = func_CFE_ParametrosGenerales.retornaValor("urlWS").toLatin1()+tipoDeCFEAEnviarDynamiaV.toLatin1();

        const char *c_produccion = produccion.data();

        curl_easy_setopt(curl, CURLOPT_URL, c_produccion);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 120L);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST,1);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(mensajeAEnviarPost));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, mensajeAEnviarPost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writerDynamia);


        res = curl_easy_perform(curl);

        if(res != CURLE_OK){

            QString resultadoError=curl_easy_strerror(res);

            if(resultadoError.trimmed()=="Couldn't resolve host name" || resultadoError.trimmed()=="Couldn't connect to server"){
                funcion.mensajeAdvertenciaOk("ERROR: No hay conexión con Dynamia: \n\n"+(QString)produccion.data());
            }else{
                funcion.mensajeAdvertenciaOk("ERROR: "+resultadoError+"\n\nConexión: \n\n"+(QString)produccion.data());
            }

            return false;
        }
        else {

            // resultadoFinal =  resultadoFinal.remove(resultadoFinal.length()-1,1);

            //        qDebug()<<resultadoFinal;

            bool ok;
            // json is a QString containing the JSON data
            QtJson::JsonObject result = QtJson::parse(resultadoFinal, ok).toMap();

            if(!ok) {
                funcion.loguear("Respuesta Dynamia:\n"+resultadoFinal);
                funcion.mensajeAdvertenciaOk("Error en parseo de información desde Dynamia:\n\nMensaje devuelto: "+resultadoFinal);
                return false;
            }

            if(result["status"].toString().toLower()=="true"){

                QtJson::JsonObject nested = result["result"].toMap();
                QtJson::JsonObject nested2 = nested["cae"].toMap();


                /*qDebug() << "QR:" << nested["qr"].toString();
                qDebug() << "idDocGaia:" << nested["idDocGaia"].toString();*/



                /*qDebug() << "CAE_ID:" << nested2["cae_id"].toString();
                qDebug() << "NRO:" << nested2["nro"].toString();
                qDebug() << "SERIE:" << nested2["serie"].toString();
                qDebug() << "DESDE:" << nested2["desde"].toString();
                qDebug() << "HASTA:" << nested2["hasta"].toString();
                qDebug() << "VENCIMIENTO:" << nested2["vencimiento"].toString();
                qDebug() << "CODIGO_SEGURIDAD:" << nested2["cod_seguridad"].toString();*/


                ModuloDocumentos modeloDocumento;

                if(modeloDocumento.actualizarInformacionCFEDocumentoDynamia(_codigoDocumento, _codigoTipoDocumento,
                                                                            nested2["nro"].toString(),
                                                                            nested2["serie"].toString(),
                                                                            nested2["vencimiento"].toString(),
                                                                            nested2["cod_seguridad"].toString(),
                                                                            nested2["cae_id"].toString(),
                                                                            nested2["desde"].toString(),
                                                                            nested2["hasta"].toString(),
                                                                            nested["qr"].toString(),
                                                                            nested["idDocGaia"].toString(),
                                                                            caeTipoDocumentoCFEDescripcionV,
                                                                            _serieDocumento
                                                                            )){



                    return true;
                }else{
                    return false;
                }



            }else{

                QtJson::JsonObject nested = result["result"].toMap();

                funcion.mensajeAdvertenciaOk("ERROR: \n"+nested["err_msg"].toString());

                return false;
            }
        }
        curl_easy_cleanup(curl);
    }
    else{
        return false;
    }
    curl_global_cleanup();



}


QString crearJsonDynamia(QString _codigoDocumento, QString _codigoTipoDocumento, QString _numeroDocumentoCFEADevolver, QString _fechaDocumentoCFEADevolver, QString tipoDocumentoCFEADevolver, QString _serieDocumento){


    qDebug()<< "crearJsonDynamia";

    QString consultaSql = " SELECT ";

    consultaSql +=" STR_TO_DATE(DOC.fechaEmisionDocumento, '%Y-%m-%d ')'fecha',  ";
    consultaSql +=" MO.codigoISO4217'iso_moneda', ";
    consultaSql +=" (SELECT case when valorConfiguracion='1' then '1' else '0' end FROM Configuracion where codigoConfiguracion='MODO_CALCULOTOTAL')'montos_brutos', ";
    consultaSql +=" '0' as 'vencimiento', ";
    consultaSql +=" DOC.codigoCliente'id_receptor', ";
    consultaSql +=" left(trim(CLI.razonSocial),45) 'razon_social', ";
    consultaSql +=" PA.codigoIsoPais'iso_pais', ";
    consultaSql +=" left(trim(CLI.nombreCliente),45) 'nombre', ";
    consultaSql +=" left(trim(DEP.descripcionDepartamento),29) 'ciudad', ";
    consultaSql +=" left(trim(CLI.direccion),45) 'direccion', ";
    consultaSql +=" left(trim(CLI.email),39)'e_mail', ";
    consultaSql +=" left(trim(CLI.telefono),19)'telefono', ";
    consultaSql +=" CLI.codigoTipoDocumentoCliente'tipoDocumento',  ";
    consultaSql +=" CLI.rut'numeroDocumento', ";

    consultaSql +=" case when DL.precioArticuloUnitario=0 then '5' else IVA.indicadorFacturacionCFE end 'indicador_facturacion', ";
    consultaSql +=" left(trim(AR.descripcionArticulo),32)'descripcion', ";
    consultaSql +=" DL.cantidad'cantidad', ";
    consultaSql +=" 'N/A' as 'unidad', ";
    consultaSql +=" CAST(DOC.porcentajeDescuentoAlTotal AS DECIMAL(10,3)) 'descuento', ";
    consultaSql +=" '1' as 'tipo_descuento', ";
    consultaSql +=" case when IVA.indicadorFacturacionCFE=4 then CAST(IVA.porcentajeIva as DECIMAL(20,2)) else 'null' end 'ivaArticulo', ";
    consultaSql +=" CAST(DL.precioArticuloUnitario AS DECIMAL(20,3))'precio_unitario', ";
    consultaSql +=" CAST((DL.cantidad*DL.precioArticuloUnitario) -  (((DL.cantidad*DL.precioArticuloUnitario)*((DOC.porcentajeDescuentoAlTotal/100)+1))-(DL.cantidad*DL.precioArticuloUnitario))  AS DECIMAL(20,3))'totalLinea', ";
    consultaSql +=" CAST(DOC.precioSubTotalVenta AS DECIMAL(20,3))'subtotal', ";


    consultaSql +=" CAST(DOC.totalIva3 AS DECIMAL(20,3))'exento', ";
    consultaSql +=" CAST(DOC.totalIva2 AS DECIMAL(20,3))'minima', ";
    consultaSql +=" CAST(DOC.totalIva1 AS DECIMAL(20,3))'basica', ";
    consultaSql +=" case when IVA.indicadorFacturacionCFE=4 then CAST(DL.precioIvaArticulo AS DECIMAL(20,3)) else 'null' end 'otro', ";
    consultaSql +=" CAST(DOC.precioTotalVenta AS DECIMAL(20,3))'total', ";
    consultaSql +=" TD.descripcionTipoDocumentoCFE'TipoDocumentoCFE', ";

    consultaSql +=" case when DOC.codigoMonedaDocumento=1 then    ";
    consultaSql +="          case when DOC.precioTotalVenta > (SELECT 10000*valorParametro FROM CFE_ParametrosGenerales where nombreParametro='montoUI') then 'mayor' else 'menor' end ";
    consultaSql +=" else  ";
    consultaSql +="          case when (DOC.precioTotalVenta*MO.cotizacionMoneda) > (SELECT 10000*valorParametro FROM CFE_ParametrosGenerales where nombreParametro='montoUI') then 'mayor' else 'menor' end ";
    consultaSql +=" end 'UI', ";

    consultaSql +=" case when IVA.indicadorFacturacionCFE=4 then CAST(IVA.porcentajeIva as DECIMAL(20,2)) else 'null' end 'ivaOtroPorcentaje', ";


    consultaSql +=" CAST(DOC.precioTotalVenta AS DECIMAL(20,3))-(CAST(DOC.precioSubTotalVenta AS DECIMAL(20,3))+CAST(DOC.precioIvaVenta AS DECIMAL(20,3))) 'Redondeo',";

    consultaSql +=" case when AR.codigoIva=IVA.codigoIva and IVA.indicadorFacturacionCFE=1 then CAST((DL.cantidad*DL.precioArticuloUnitario) -  (((DL.cantidad*DL.precioArticuloUnitario)*((DOC.porcentajeDescuentoAlTotal/100)+1))-(DL.cantidad*DL.precioArticuloUnitario))  AS DECIMAL(20,3)) else 0 end 'Exento2'";


    consultaSql +=" FROM DocumentosLineas DL  ";

    consultaSql +=" join Documentos DOC on DOC.codigoDocumento=DL.codigoDocumento and DOC.codigoTipoDocumento=DL.codigoTipoDocumento and DOC.serieDocumento=DL.serieDocumento ";
    consultaSql +=" join Articulos AR on AR.codigoArticulo=DL.codigoArticulo ";
    consultaSql +=" join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento ";
    consultaSql +=" join Monedas MO on MO.codigoMoneda = DOC.codigoMonedaDocumento ";
    consultaSql +=" join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente ";
    consultaSql +=" join CFE_TipoDocumentoCliente CFETDC on CFETDC.codigoTipoDocumentoCliente=CLI.codigoTipoDocumentoCliente ";
    consultaSql +=" join Pais PA on PA.codigoPais=CLI.codigoPais ";
    consultaSql +=" join Departamentos DEP on DEP.codigoDepartamento=CLI.codigoDepartamento and DEP.codigoPais=CLI.codigoPais ";
    consultaSql +=" join Ivas IVA on IVA.codigoIva=AR.codigoIva ";
    consultaSql +=" where DOC.codigoDocumento="+_codigoDocumento+" and DOC.codigoTipoDocumento="+_codigoTipoDocumento+"  and DOC.serieDocumento='"+_serieDocumento+"' and DOC.esDocumentoCFE='1' ";


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
        if(query.exec(consultaSql)) {
            if(query.first()){


                //Cabezal
                QString fecha=query.value(0).toString();
                QString iso_moneda=query.value(1).toString().replace("\n","");
                QString montos_brutos=query.value(2).toString();
                QString vencimientos=query.value(3).toString();
                QString id_receptor=query.value(4).toString();
                QString razon_social=query.value(5).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                QString iso_pais=query.value(6).toString().replace("\n","");
                QString nombre=query.value(7).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                QString ciudad=query.value(8).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                QString direccion=query.value(9).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");
                QString email=query.value(10).toString().replace("\"","\\\"").replace("\n","");
                QString telefono=query.value(11).toString().replace("\"","\\\"").replace("\n","");
                QString tipoDocumento=query.value(12).toString().replace("\n","");
                QString numeroDocumento=query.value(13).toString().replace("\n","");




                //totales
                QString subtotal=QString::number(query.value(23).toFloat()+query.value(32).toFloat(),'f',3);
                QString exento=query.value(24).toString();
                QString minima=query.value(25).toString();
                QString basica=query.value(26).toString();
                QString otro=query.value(27).toString();
                QString total=query.value(28).toString();
                QString tipoDocumentoCFE=query.value(29).toString();
                QString ui=query.value(30).toString();

                QString redondeo=query.value(32).toString();

                float _redondeoMonto=query.value(32).toFloat();

                QString _OtroIva = ",\""+query.value(31).toString()+"\":"+otro+"";

                QString _Rut=",\"rut\":\""+numeroDocumento.replace("\"","\\\"")+"\"";
                QString _Documento_identidad= ",\"documento_identidad\":{\"tipo\":"+tipoDocumento+",\"numero\":\""+numeroDocumento+"\"}";

                QString _Vencimiento="\"vencimiento\":"+vencimientos+",";

                //Verifico tipo de documento
                if(tipoDocumentoCFE!="Venta credito" && tipoDocumentoCFE!="Nota credito venta"){
                    _Vencimiento="";
                }



                if(tipoDocumentoCFE=="Venta contado"){

                    caeTipoDocumentoCFEDescripcionV="e-Ticket";
                    tipoDeCFEAEnviarDynamiaV=func_CFE_ParametrosGenerales.retornaValor("urlE-ticketContado");

                }else if(tipoDocumentoCFE=="Venta credito"){

                    caeTipoDocumentoCFEDescripcionV="e-Ticket";
                    tipoDeCFEAEnviarDynamiaV=func_CFE_ParametrosGenerales.retornaValor("urlE-ticketCredito");

                }else if(tipoDocumentoCFE=="Devolucion venta"){

                    caeTipoDocumentoCFEDescripcionV="Nota de Crédito de e-Ticket";
                    tipoDeCFEAEnviarDynamiaV=func_CFE_ParametrosGenerales.retornaValor("urlE-ticketNotaCredito");

                }else if(tipoDocumentoCFE=="Nota credito venta"){

                    caeTipoDocumentoCFEDescripcionV="Nota de Crédito de e-Ticket";
                    tipoDeCFEAEnviarDynamiaV=func_CFE_ParametrosGenerales.retornaValor("urlE-ticketNotaCredito");

                }else{
                    return "-7"; //Error en tipo documento CFE en khitomer.TipoDocumento
                }


                //Verifico si es cliente con RUT
                if(tipoDocumento=="2"){
                    //Si es rut no puede ser otro documento
                    _Documento_identidad="";

                    if(tipoDocumentoCFE=="Venta contado"){

                        caeTipoDocumentoCFEDescripcionV="e-Factura";
                        tipoDeCFEAEnviarDynamiaV=func_CFE_ParametrosGenerales.retornaValor("urlE-facturaContado");

                    }else if(tipoDocumentoCFE=="Venta credito"){

                        caeTipoDocumentoCFEDescripcionV="e-Factura";
                        tipoDeCFEAEnviarDynamiaV=func_CFE_ParametrosGenerales.retornaValor("urlE-facturaCredito");

                    }else if(tipoDocumentoCFE=="Devolucion venta"){

                        caeTipoDocumentoCFEDescripcionV="Nota de Crédito de e-Factura";
                        tipoDeCFEAEnviarDynamiaV=func_CFE_ParametrosGenerales.retornaValor("urlE-facturaNotaCredito");

                    }else if(tipoDocumentoCFE=="Nota credito venta"){

                        caeTipoDocumentoCFEDescripcionV="Nota de Crédito de e-Factura";
                        tipoDeCFEAEnviarDynamiaV=func_CFE_ParametrosGenerales.retornaValor("urlE-facturaNotaCredito");

                    }else{
                        return "-7"; //Error en tipo documento CFE en khitomer.TipoDocumento
                    }



                }else if(tipoDocumento=="5"){    ///PASSAPORTE
                    _Rut="";
                    //Si es passaporte tiene que ir el documento
                    if(numeroDocumento=="null"){
                        funcion.mensajeAdvertenciaOk("Error: El documento PASSAPORTE es obligatorio");
                        return "-4";//Documento passaporte es obligatorio
                    }
                }else if(tipoDocumento=="6"){   ///DNI
                    _Rut="";
                    //Si es DNI chequeo si lo muestro segun el pais
                    if(iso_pais!="AR" && iso_pais!="BR" && iso_pais!="CL" && iso_pais!="PY"){
                        if(ui=="menor"){
                            _Documento_identidad="";
                        }else{
                            if(numeroDocumento=="null"){
                                return "-6"; //Monto mayor a 10000UI, se requiere documento
                            }
                        }
                    }else{
                        if(numeroDocumento=="null"){
                            return "-5";//Documento DNI es obligatorio para el pais del cliente
                        }
                    }
                }else{
                    ///otro documento
                    _Rut="";
                    if(ui=="menor"){
                        _Documento_identidad="";
                    }else{
                        if(numeroDocumento=="null"){
                            return "-6"; //Monto mayor a 10000UI, se requiere documento
                        }
                    }
                }


                if(otro=="null"){
                    _OtroIva="";
                }


                //Seteo las lineas genericas
                QString Cabezal = "{\"data\":{\"documento\":{\"fecha\":\""+fecha+"\",\"iso_moneda\":\""+iso_moneda+"\",";
                QString MontoBrutos = "\"montos_brutos\":"+montos_brutos+", "+_Vencimiento+" ";

                QString Receptor= "\"receptor\":{\"iso_pais\":\""+iso_pais+"\",\"ciudad\":\""+ciudad+"\",\"direccion\":\""+direccion+"\",\"e_mail\":\""+email+"\",\"id_receptor\":\""+id_receptor+"\",\"razon_social\":\""+razon_social+"\",\"nombre\":\""+nombre+"\""+_Rut+""+_Documento_identidad+" ,\"telefono\":\""+telefono+"\"},";


                QString Referencias = "\"referencias\":[{\"nro_doc\":"+_numeroDocumentoCFEADevolver.trimmed()+",\"doc_sin_codificar\":false,\"fecha\":\""+_fechaDocumentoCFEADevolver.trimmed()+"\"}],";


                if(tipoDocumentoCFE!="Devolucion venta" && tipoDocumentoCFE!="Nota credito venta"){

                    Referencias="";

                }else{
                    if(_numeroDocumentoCFEADevolver.trimmed()=="" || _numeroDocumentoCFEADevolver.trimmed().toLower()=="null" || _numeroDocumentoCFEADevolver.trimmed()==NULL){
                        return "-8"; //No se puede devolver un documento que no fue emitido como cfe
                    }
                }




                QString User_info = "\"user_info\":\""+func_CFE_ParametrosGenerales.retornaValor("claveCifrada")+"\"},";

                QString Token= "\"token\":\""+func_CFE_ParametrosGenerales.retornaValor("token")+"\"} ";



                QString Lineas= "\"lineas\":[ ";

                query.previous();
                int i=0;

                QString descripcionArticulo="";

                QString IVA="";

                float _exentoTotal=0;

                while (query.next()){

                    if(i!=0){
                        Lineas += " , ";
                    }

                    if(query.value(14).toString()=="4"){
                        IVA=",\"iva\":"+query.value(20).toString()+"";
                    }else{
                        IVA="";
                    }

                    descripcionArticulo=query.value(15).toString().toUpper().replace("Á","A").replace("É","E").replace("Í","I").replace("Ó","O").replace("Ú","U").replace("\"","\\\"").replace("\n","");

                    Lineas += "{\"cantidad\":"+query.value(16).toString()+",\"descripcion\":\""+descripcionArticulo+"\",\"indicador_facturacion\":"+query.value(14).toString()+""+IVA+",\"precio_unitario\":"+query.value(21).toString()+",\"total\":"+query.value(22).toString()+",\"unidad\":\"NA\",\"descuento\":"+query.value(18).toString()+",\"tipo_descuento\":"+query.value(19).toString()+"}";
                    i=1;

                    //Calculo el exento segun el monto de los articulos
                    _exentoTotal+=query.value(33).toFloat();

                }

                exento = QString::number(_exentoTotal,'f',3);


                //chequeo si es devolucion o no, para verificar segun el documento original los montos de redondeo
                if(Referencias!=""){
                    //Chequeo si hay redondeos y agrego la linea correspondiente
                    if(func_tipoDocumentos.retornaPermisosDelDocumento(tipoDocumentoCFEADevolver,"utilizaRedondeoEnTotal") && _redondeoMonto!=0){

                        //qDebug()<<_redondeoMonto;

                        if(_redondeoMonto<0){
                            Lineas += ", {\"cantidad\":1,\"descripcion\":\"Redondeo\",\"indicador_facturacion\":7,\"precio_unitario\":"+redondeo+",\"total\":"+redondeo+",\"unidad\":\"NA\",\"descuento\":0}";
                        }else{
                            Lineas += ", {\"cantidad\":1,\"descripcion\":\"Redondeo\",\"indicador_facturacion\":6,\"precio_unitario\":"+redondeo+",\"total\":"+redondeo+",\"unidad\":\"NA\",\"descuento\":0}";
                            //  qDebug()<<"Mayor a 0";
                        }

                    }
                }else{
                    //Chequeo si hay redondeos y agrego la linea correspondiente
                    if(func_tipoDocumentos.retornaPermisosDelDocumento(_codigoTipoDocumento,"utilizaRedondeoEnTotal") && _redondeoMonto!=0){

                        //qDebug()<<_redondeoMonto;

                        if(_redondeoMonto<0){
                            Lineas += ", {\"cantidad\":1,\"descripcion\":\"Redondeo\",\"indicador_facturacion\":7,\"precio_unitario\":"+redondeo+",\"total\":"+redondeo+",\"unidad\":\"NA\",\"descuento\":0}";
                        }else{
                            Lineas += ", {\"cantidad\":1,\"descripcion\":\"Redondeo\",\"indicador_facturacion\":6,\"precio_unitario\":"+redondeo+",\"total\":"+redondeo+",\"unidad\":\"NA\",\"descuento\":0}";
                            //  qDebug()<<"Mayor a 0";
                        }

                    }
                }



                Lineas += "], ";



                QString Totales= "\"totales\":{\"ivas\":";

                Totales+= "{\"basica\":"+basica+",\"exento\":"+exento+",\"minima\":"+minima+""+_OtroIva+"},";

                Totales+= "\"subtotal\":"+subtotal+",\"total\":"+total+"}},";

                return Cabezal + Lineas + MontoBrutos + Receptor + Referencias + Totales + User_info + Token; ;

            }else{
                return "-1"; //No existe documento para enviar como CFE
            }
        }else{

            qDebug()<< query.lastError();
            return "-2";//No se puede ejecutar la consulta a la base de datos
        }
    }else{
        return "-3"; //No hay conexión con la base de datos
    }
}


bool ModuloDocumentos::emitirDocumentoCFEImix(QString _codigoDocumento,QString _codigoTipoDocumento, QString _descripcionEstadoActualDocumento, QString _serieDocumento){

    //Consulto si el modo es 0 = imix, 1 = dynamia
    if(func_CFE_ParametrosGenerales.retornaValor("modoFuncionCFE")=="0"){

        bool resultadoprocesarImix= procesarImix(_codigoDocumento, _codigoTipoDocumento, _serieDocumento);

        //  qDebug()<< resultadoprocesarImix;

        //Si se procesa correctamente el cfe retorno true
        if(resultadoprocesarImix){
            return true;
        }else{

            qDebug() << "Estado del documento: ";
            qDebug() << _descripcionEstadoActualDocumento;

            if(_descripcionEstadoActualDocumento=="Pendiente"){

                actualizoEstadoDocumentoCFE(_codigoDocumento, _codigoTipoDocumento,"P", _serieDocumento);



                return false;
            }else{
                //   Si falla, intento eliminar el documento en la base
                bool resultado2 = eliminarDocumento(_codigoDocumento, _codigoTipoDocumento, _serieDocumento);

                if(resultado2){
                    return false;
                }else{
                    funcion.mensajeAdvertenciaOk("Hubo un error al intentar eliminar la informacion del documento");
                    return false;
                }
            }
        }

    }else{
        return false;
    }


}


bool ModuloDocumentos::emitirDocumentoCFE_Imix_Nube(QString _codigoDocumento,QString _codigoTipoDocumento,QString _numeroDocumentoCFEADevolver,QString _fechaDocumentoCFEADevolver,QString tipoDocumentoCFEADevolver, QString _descripcionEstadoActualDocumento, QString _serieDocumento){


    qDebug()<< "emitirDocumentoCFE_Imix_Nube";

    //Consulto si el modo es 0 = imix, 1 = dynamia, 2 = Imix en la nube
    if(func_CFE_ParametrosGenerales.retornaValor("modoFuncionCFE")=="2"){

        bool resultadoProcesador= procesarImix_Nube(_codigoDocumento, _codigoTipoDocumento,_numeroDocumentoCFEADevolver,_fechaDocumentoCFEADevolver,tipoDocumentoCFEADevolver, _serieDocumento);


        qDebug()<< resultadoProcesador;

        //Si se procesa correctamente el cfe retorno true
        if(resultadoProcesador){
            return true;
        }else{

            if(_descripcionEstadoActualDocumento=="Pendiente"){

                actualizoEstadoDocumentoCFE(_codigoDocumento, _codigoTipoDocumento,"P", _serieDocumento);

                return false;
            }else{

                //   Si falla, intento eliminar el documento en la base
                bool resultado2 = eliminarDocumento(_codigoDocumento, _codigoTipoDocumento, _serieDocumento);

                if(resultado2){
                    return false;
                }else{
                    funcion.mensajeAdvertenciaOk("Hubo un error al intentar eliminar la informacion del documento");
                    return false;
                }
            }
        }


    }else{
        return false;
    }


}

bool ModuloDocumentos::emitirDocumentoCFEDynamia(QString _codigoDocumento,QString _codigoTipoDocumento,QString _numeroDocumentoCFEADevolver,QString _fechaDocumentoCFEADevolver,QString tipoDocumentoCFEADevolver, QString _descripcionEstadoActualDocumento, QString _serieDocumento){


    qDebug()<< "emitirDocumentoCFEDynamia";

    //Consulto si el modo es 0 = imix, 1 = dynamia
    if(func_CFE_ParametrosGenerales.retornaValor("modoFuncionCFE")=="1"){

        bool resultadoprocesarDynamia= procesarDynamia(_codigoDocumento, _codigoTipoDocumento,_numeroDocumentoCFEADevolver,_fechaDocumentoCFEADevolver,tipoDocumentoCFEADevolver, _serieDocumento);


        qDebug()<< resultadoprocesarDynamia;

        //Si se procesa correctamente el cfe retorno true
        if(resultadoprocesarDynamia){
            return true;
        }else{

            if(_descripcionEstadoActualDocumento=="Pendiente"){

                actualizoEstadoDocumentoCFE(_codigoDocumento, _codigoTipoDocumento,"P", _serieDocumento);

                return false;
            }else{

                //   Si falla, intento eliminar el documento en la base
                bool resultado2 = eliminarDocumento(_codigoDocumento, _codigoTipoDocumento, _serieDocumento);

                if(resultado2){
                    return false;
                }else{
                    funcion.mensajeAdvertenciaOk("Hubo un error al intentar eliminar la informacion del documento");
                    return false;
                }
            }
        }


    }else{
        return false;
    }


}






// Función principal que implementa la lógica solicitada
bool enviarYConsultarRespuesta(const QByteArray &jsonAEnviar)
{

    QString ipServidor = func_configuracionProxy.retornoValorPatrametro("ipServidor");
    QString puerto = func_configuracionProxy.retornoValorPatrametro("puerto");
    QString endpointMensaje = func_configuracionProxy.retornoValorPatrametro("endpointMensaje");
    QString endpointRespuesta = func_configuracionProxy.retornoValorPatrametro("endpointRespuesta");
    QString timeoutCola = func_configuracionProxy.retornoValorPatrametro("timeoutCola");



    // 1) Enviar POST al endpoint factura
    QString urlPost = ipServidor+":"+puerto+endpointMensaje;

    qDebug()<< urlPost;

    QString respuestaPost;
    if(!httpPostJson(urlPost, jsonAEnviar, respuestaPost)) {
        funcion.loguear("Error realizando POST contra el Proxy: " + respuestaPost);
        funcion.mensajeAdvertenciaOk("Error en POST contra el Proxy:\n" + respuestaPost);
        return false;
    }

    // Parsear la respuesta del POST
    bool ok;
    QtJson::JsonObject result = QtJson::parse(respuestaPost, ok).toMap();
    if(!ok) {
        funcion.loguear("Error parseando respuesta POST del proxy: " + respuestaPost);
        funcion.mensajeAdvertenciaOk("Error parseando respuesta POST del proxy:\n" + respuestaPost);
        return false;
    }

    if(!result.contains("id")) {
        funcion.loguear("La respuesta no contiene 'id'. Respuesta: " + respuestaPost);
        funcion.mensajeAdvertenciaOk("La respuesta del servidor no contiene 'id'.");
        return false;
    }

    QString id = result["id"].toString();
    if(id.isEmpty()) {
        funcion.loguear("El 'id' devuelto está vacío. Respuesta: " + respuestaPost);
        funcion.mensajeAdvertenciaOk("El 'id' devuelto está vacío.");
        return false;
    }

    // 2) Iniciar el polling (60s en total, cada 2s)
    QString urlGetBase = ipServidor+":"+puerto+endpointRespuesta;
    int totalTime = timeoutCola.toInt(); // segundos totales
    int interval = 2;   // segundos entre consultas
    int attempts = totalTime / interval;

    bool success = false;
    bool errorEnRespuesta=false;
    for (int i = 0; i < attempts; ++i) {
        // Construir URL con el id
        QString urlGet = urlGetBase + "?id=" + id;
        QString respuestaGet;
        if(!httpGet(urlGet, respuestaGet)) {
            // Error en GET, se reintenta luego de 2s
            esperarSegundos(interval);
            continue;
        }

        // Parsear respuesta GET
        QtJson::JsonObject getResult = QtJson::parse(respuestaGet, ok).toMap();
        if(!ok) {
            funcion.loguear("Error parseando respuesta GET: " + respuestaGet);
            esperarSegundos(interval);
            continue;
        }

        // Chequear si la respuesta es "OK"
        // Se asume que getResult["status"] == "OK" significa éxito
        if (getResult.contains("status") && getResult["status"].toString().toUpper()=="OK") {
            success = true;
            break;
        }else if(getResult.contains("status") && getResult["status"].toString().toUpper()=="ERROR"){
            if(getResult.contains("error") && getResult["error"].toString().toUpper().trimmed() !=""){
                funcion.loguear("Respuesta de error: "+getResult["error"].toString().toUpper().trimmed());
                funcion.mensajeAdvertenciaOk("Respuesta de error: "+getResult["error"].toString().toUpper().trimmed());
                success = false;
                errorEnRespuesta = true;
                break;
            }
        }

        // Esperar 2s antes de reintentar
        esperarSegundos(interval);

    }

    if(!success && !errorEnRespuesta) {
        funcion.loguear("No se obtuvo respuesta del Proxy en "+timeoutCola+"s.");
        funcion.mensajeAdvertenciaOk("No se obtuvo respuesta del Proxy en el tiempo esperado ("+timeoutCola+"s).");
    }

    return success;
}





// Función auxiliar para realizar POST con JSON
bool httpPostJson(const QString &url, const QByteArray &jsonData, QString &respuesta)
{


    respuesta.clear();
    resultadoFinal.clear();

    CURL *curl = curl_easy_init();
    if(!curl) return false;

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charsets: utf-8");

    curl_easy_setopt(curl, CURLOPT_URL, url.toLatin1().data());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.constData());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)jsonData.size());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writerProxy);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&resultadoFinal);

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        respuesta = curl_easy_strerror(res);
        return false;
    }

    respuesta = resultadoFinal;
    return true;
}

// Función auxiliar para realizar GET
bool httpGet(const QString &url, QString &respuesta)
{
    respuesta.clear();
    resultadoFinal.clear();

    CURL *curl = curl_easy_init();
    if(!curl) return false;

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charsets: utf-8");

    curl_easy_setopt(curl, CURLOPT_URL, url.toLatin1().data());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writerProxy);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&resultadoFinal);

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        respuesta = curl_easy_strerror(res);
        return false;
    }

    respuesta = resultadoFinal;
    return true;
}
