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

#include "modulolistasprecios.h"
#include <QtSql>
#include <QSqlQuery>
#include <QMessageBox>
#include <Utilidades/database.h>
#include <QPrinter>
#include <QPainter>
#include <QFont>
#include <funciones.h>
#include <Utilidades/moduloconfiguracion.h>

ModuloConfiguracion func_configuracionListaPrecio;



Funciones funcionMensaje;

QRectF cuadroTexto(double x, double y, double ancho, double alto, bool justifica);

double centimetroTexto;



ModuloListasPrecios::ModuloListasPrecios(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoListaPrecioRole] = "codigoListaPrecio";
    roles[DescripcionListaPrecioRole] = "descripcionListaPrecio";
    roles[VigenciaDesdeFechaRole] = "vigenciaDesdeFecha";
    roles[VigenciaHastaFechaRole] = "vigenciaHastaFecha";
    roles[UsuarioAltaRole] = "usuarioAlta";
    roles[activoRole] = "activo";
    roles[participaEnBusquedaInteligenteRole] = "participaEnBusquedaInteligente";


    setRoleNames(roles);


}


ListasPrecio::ListasPrecio(const QString &codigoListaPrecio, const QString &descripcionListaPrecio, const QString &vigenciaDesdeFecha, const QString &vigenciaHastaFecha, const QString &usuarioAlta, const QString &activo, const QString &participaEnBusquedaInteligente)
    : m_codigoListaPrecio(codigoListaPrecio), m_descripcionListaPrecio(descripcionListaPrecio), m_vigenciaDesdeFecha(vigenciaDesdeFecha), m_vigenciaHastaFecha(vigenciaHastaFecha), m_usuarioAlta(usuarioAlta), m_activo(activo), m_participaEnBusquedaInteligente(participaEnBusquedaInteligente)

{
}

QString ListasPrecio::codigoListaPrecio() const
{
    return m_codigoListaPrecio;
}
QString ListasPrecio::descripcionListaPrecio() const
{
    return m_descripcionListaPrecio;
}
QString ListasPrecio::vigenciaDesdeFecha() const
{
    return m_vigenciaDesdeFecha;
}
QString ListasPrecio::vigenciaHastaFecha() const
{
    return m_vigenciaHastaFecha;
}

QString ListasPrecio::usuarioAlta() const
{
    return m_usuarioAlta;
}
QString ListasPrecio::activo() const
{
    return m_activo;
}
QString ListasPrecio::participaEnBusquedaInteligente() const
{
    return m_participaEnBusquedaInteligente;
}

void ModuloListasPrecios::addListasPrecio(const ListasPrecio &listaPrecio)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ListasPrecio << listaPrecio;
    endInsertRows();
}

void ModuloListasPrecios::clearListasPrecio(){
    m_ListasPrecio.clear();
}

void ModuloListasPrecios::buscarListasPrecio(QString campo, QString datoABuscar){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from ListaPrecio where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloListasPrecios::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloListasPrecios::addListasPrecio(ListasPrecio(q.value(rec.indexOf("codigoListaPrecio")).toString(),

                                                                  q.value(rec.indexOf("descripcionListaPrecio")).toString(),

                                                                  q.value(rec.indexOf("vigenciaDesdeFecha")).toString(),

                                                                  q.value(rec.indexOf("vigenciaHastaFecha")).toString(),

                                                                  q.value(rec.indexOf("usuarioAlta")).toString(),

                                                                  q.value(rec.indexOf("activo")).toString(),

                                                                  q.value(rec.indexOf("participaEnBusquedaInteligente")).toString()

                                                                  ));
            }
        }
    }
}

int ModuloListasPrecios::rowCount(const QModelIndex & parent) const {
    return m_ListasPrecio.count();
}

QVariant ModuloListasPrecios::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_ListasPrecio.count()){
        return QVariant();

    }

    const ListasPrecio &listaPrecio = m_ListasPrecio[index.row()];

    if (role == CodigoListaPrecioRole){
        return listaPrecio.codigoListaPrecio();

    }
    else if (role == DescripcionListaPrecioRole){
        return listaPrecio.descripcionListaPrecio();

    }
    else if (role == VigenciaDesdeFechaRole){
        return listaPrecio.vigenciaDesdeFecha();

    }
    else if (role == VigenciaHastaFechaRole){
        return listaPrecio.vigenciaHastaFecha();

    }
    else if (role == UsuarioAltaRole){
        return listaPrecio.usuarioAlta();
    }
    else if (role == activoRole){
        return listaPrecio.activo();
    }
    else if (role == participaEnBusquedaInteligenteRole){
        return listaPrecio.participaEnBusquedaInteligente();
    }

    return QVariant();
}

int ModuloListasPrecios::insertarListasPrecio(QString _codigoListaPrecio, QString _descripcionListaPrecio, QString _vigenciaDesdeFecha, QString _vigenciaHastaFecha, QString _usuarioAlta, QString _activo, QString _participaEnBusquedaInteligente) const {

    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el articulo
    // 1  articulo dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar el articulo
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El articulo no tiene los datos sufucientes para darse de alta.

    if(_codigoListaPrecio.trimmed()=="" || _descripcionListaPrecio.trimmed()=="" || _vigenciaDesdeFecha.trimmed()=="" || _vigenciaHastaFecha.trimmed()==""){
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


        if(query.exec("select codigoListaPrecio from ListaPrecio where codigoListaPrecio='"+_codigoListaPrecio+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("update ListaPrecio set descripcionListaPrecio='"+_descripcionListaPrecio+"', vigenciaDesdeFecha='"+_vigenciaDesdeFecha+"',vigenciaHastaFecha='"+_vigenciaHastaFecha+"',activo='"+_activo+"',participaEnBusquedaInteligente='"+_participaEnBusquedaInteligente+"' where codigoListaPrecio='"+_codigoListaPrecio+"'")){

                        return 2;

                    }else{

                        return -2;
                    }

                }else{return -2;}
            }else{

                if(query.exec("insert INTO ListaPrecio (codigoListaPrecio,descripcionListaPrecio,vigenciaDesdeFecha,vigenciaHastaFecha,usuarioAlta,activo,participaEnBusquedaInteligente) values('"+_codigoListaPrecio+"','"+_descripcionListaPrecio+"','"+_vigenciaDesdeFecha+"','"+_vigenciaHastaFecha+"','"+_usuarioAlta+"','"+_activo+"','"+_participaEnBusquedaInteligente+"')")){
                    return 1;
                }else{
                    return -3;
                }
            }
        }


    }else{return -1;}
}


bool ModuloListasPrecios::eliminarListasPrecio(QString _codigoListaPrecio) const {

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

        if(query.exec("select codigoListaPrecio from ListaPrecio where codigoListaPrecio='"+_codigoListaPrecio+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("delete from ListaPrecioArticulos where codigoListaPrecio='"+_codigoListaPrecio+"'")){

                        if(query.exec("delete from ListaPrecio where codigoListaPrecio='"+_codigoListaPrecio+"'")){

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
            return false;
        }
    }else{return false;}
}


int ModuloListasPrecios::ultimoRegistroDeListasPrecioEnBase() const{

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

        if(query.exec("select codigoListaPrecio from ListaPrecio order by codigoListaPrecio desc limit 1")) {
            if(query.first()){
                if(query.value(0).toString()==""){
                    return 1;
                }else{
                    return query.value(0).toInt()+1;
                }
            }else{
                return -1;
            }
        }else{
            return -1;
        }
    }else{return -1;}
}

QString ModuloListasPrecios::retornaDescripcionListaPrecio(QString _codigoListaPrecio) const{

   /* QString _valor="";
    for (int var = 0; var < m_ListasPrecio.size(); ++var) {
        if(m_ListasPrecio[var].codigoListaPrecio()==_codigoListaPrecio ){

            _valor= m_ListasPrecio[var].descripcionListaPrecio();

        }
    }

    if(m_ListasPrecio.size()==0 && _valor==""){*/
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


            if(query.exec("select descripcionListaPrecio from ListaPrecio where codigoListaPrecio='"+_codigoListaPrecio+"'")) {
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
  /*  }else{
        return _valor;
    }*/

    /*
    */
}
QString ModuloListasPrecios::retornaListaPrecioDeCliente(QString _fechaDePrecios,QString _codigoCliente,QString _tipoCliente) const{
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


        if(query.exec("select LP.codigoListaPrecio from ListaPrecio LP join ListaPrecioClientes LPC on LPC.codigoListaPrecio=LP.codigoListaPrecio and '"+_fechaDePrecios+"' between LP.vigenciaDesdeFecha and LP.vigenciaHastaFecha where LP.activo=1 and LPC.codigoCliente='"+_codigoCliente+"' and LPC.tipoCliente='"+_tipoCliente+"' order by LP.codigoListaPrecio desc limit 1")) {
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
bool ModuloListasPrecios::eliminaListaPrecioDeCliente(QString _codigoCliente,QString _tipoCliente) const{
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

        if(query.exec("delete from ListaPrecioClientes where codigoCliente='"+_codigoCliente+"' and tipoCliente='"+_tipoCliente+"'")){
            return true;

        }else{
            return false;
        }

    }else{return false;}
}
bool ModuloListasPrecios::insertarListaPrecioCliente(QString _codigoListaPrecio,QString _codigoCliente,QString _tipoCliente) const {

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

        if(query.exec("insert INTO ListaPrecioClientes (codigoListaPrecio,codigoCliente,tipoCliente) values('"+_codigoListaPrecio+"','"+_codigoCliente+"','"+_tipoCliente+"')")){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

void ModuloListasPrecios::buscarListasPrecioCliente(QString _codigoCliente,QString _tipoCliente){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("SELECT LPC.codigoListaPrecio,LP.descripcionListaPrecio,LPC.codigoCliente,LPC.tipoCliente  FROM ListaPrecioClientes LPC join ListaPrecio LP on LP.codigoListaPrecio=LPC.codigoListaPrecio  where LPC.codigoCliente='"+_codigoCliente+"' and LPC.tipoCliente='"+_tipoCliente+"'");
        QSqlRecord rec = q.record();

        ModuloListasPrecios::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloListasPrecios::addListasPrecio(ListasPrecio(q.value(rec.indexOf("codigoListaPrecio")).toString(),

                                                                  q.value(rec.indexOf("descripcionListaPrecio")).toString(),

                                                                  q.value(rec.indexOf("codigoCliente")).toString(),

                                                                  q.value(rec.indexOf("tipoCliente")).toString(),

                                                                  q.value(rec.indexOf("tipoCliente")).toString(),

                                                                  q.value(rec.indexOf("tipoCliente")).toString(),

                                                                  q.value(rec.indexOf("tipoCliente")).toString()

                                                                  ));
            }
        }
    }
}
QString ModuloListasPrecios::retornarListaPrecio(int indice, QString  _codigoCliente, QString  _tipoCliente) const{

    int contador=0;

    int totalm_ListasPrecio=m_ListasPrecio.count();

    for(int i=0;i<totalm_ListasPrecio;i++){

        if(m_ListasPrecio[i].vigenciaDesdeFecha()==_codigoCliente && m_ListasPrecio[i].vigenciaHastaFecha()==_tipoCliente){
            if(contador==indice){
                return m_ListasPrecio[i].codigoListaPrecio();
            }
            contador++;
        }
    }
    return "";
}


QString ModuloListasPrecios::retornaCodigoListaPrecioPorIndice(int indice) const{
    return m_ListasPrecio[indice].codigoListaPrecio();
}
QString ModuloListasPrecios::retornaDescripcionListaPrecioPorIndice(int indice) const{
    return m_ListasPrecio[indice].descripcionListaPrecio();
}

bool ModuloListasPrecios::retornaSiClienteTieneListaPrecio(QString _codigoListaPrecio,QString _codigoCliente,QString _tipoCliente) const{
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


        if(query.exec("select codigoListaPrecio from ListaPrecioClientes where codigoListaPrecio='"+_codigoListaPrecio+"' and codigoCliente='"+_codigoCliente+"' and tipoCliente='"+_tipoCliente+"' limit 1;")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

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
}


bool ModuloListasPrecios::emitirListaPrecioDuplex(QString _codigoListaPrecio, QString _impresora, QString _stringFiltroArticulos, int _tamanioFuente) const{

    /*qDebug()<< "_codigoListaPrecio";
    qDebug()<< _codigoListaPrecio;
    qDebug()<< "_impresora";
    qDebug()<< _impresora;
    qDebug()<< "_stringFiltroArticulos";
    qDebug()<< _stringFiltroArticulos;
    qDebug()<< "_tamanioFuente";
    qDebug()<< _tamanioFuente;*/

    int cantidadDecimalesMontoListaPrecio=func_configuracionListaPrecio.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO").toInt(0);


    bool conexion=true;

    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }


    if(conexion){
        QSqlQuery query(Database::connect());
        if(query.exec("SELECT LPA.codigoArticulo,AR.descripcionArticulo,MON.simboloMoneda,LPA.precioArticulo FROM ListaPrecioArticulos LPA join Articulos AR on AR.codigoArticulo=LPA.codigoArticulo join Monedas MON on MON.codigoMoneda=AR.codigoMoneda where LPA.codigoListaPrecio='"+_codigoListaPrecio+"'   "+_stringFiltroArticulos+"   and (SELECT  sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) 'cantidad'  FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in ('E','G') and DOCL.codigoArticulo=AR.codigoArticulo  and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in ('E','G') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo)>0    order by CAST(LPA.codigoArticulo AS SIGNED) asc ;")) {

            //    qDebug()<< query.lastQuery();

            if(query.first()){
                if(query.value(0).toString()==""){
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }

        int fuenteSizePoints=_tamanioFuente;


        //##################################################
        // Preparo los seteos de la impresora ##############
        QPrinter printer;
        QPrinter printer2;
        printer.setPrinterName(_impresora);
        printer2.setPrinterName(_impresora);

        QPainter painterPrimeraTirada ;
        QPainter painterSegundaTirada ;

        printer.setOutputFormat(QPrinter::NativeFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setPageSize(QPrinter::A4);

        printer2.setOutputFormat(QPrinter::NativeFormat);
        printer2.setPaperSize(QPrinter::A4);
        printer2.setPageSize(QPrinter::A4);


        printer.setOrientation(QPrinter::Portrait);
        printer.setCreator("Khitomer");
        printer.setColorMode(QPrinter::GrayScale);
        printer.setFullPage(true);

        printer2.setOrientation(QPrinter::Portrait);
        printer2.setCreator("Khitomer");
        printer2.setColorMode(QPrinter::GrayScale);
        printer2.setFullPage(true);

        QFont fuente("Arial");

        fuente.setPointSize(fuenteSizePoints);



        centimetroTexto = (printer.QPaintDevice::width()/(printer.QPaintDevice::widthMM()/10)/1.03f);

        // FIN de preparo los seteos de la impresora ######
        //#################################################


        if (!painterPrimeraTirada.begin(&printer)) {
            return false;
        }

        painterPrimeraTirada.setFont(fuente);


        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////

        double i=2;
        double j=2;
        bool paginaSegundaCara=false;
        query.previous();
        int contadorRegistros=0;
        int terminaPrimerLibro=0;
        int cantidadPaginas=1;

        while(query.next()){

            if(i!=30 && j==2){

                if(i==2){
                    if(paginaSegundaCara){
                        // painterSegundaTirada.drawText(cuadroTexto(2,1,2.5,1,true),0,"ARTICULO");
                        // painterSegundaTirada.drawText(cuadroTexto(10.5,1,2,1,true),2,"PRECIO");
                    }else{
                        painterPrimeraTirada.drawText(cuadroTexto(2,1,2.5,1,true),0,"ARTICULO");
                        painterPrimeraTirada.drawText(cuadroTexto(10.5,1,2,1,true),2,"PRECIO");
                    }
                }

                if(paginaSegundaCara){
                    //   painterSegundaTirada.drawText(cuadroTexto(1,i,2.5,1,true),0,query.value(0).toString());
                    //   painterSegundaTirada.drawText(cuadroTexto(2.3,i,5,1,true),0,query.value(1).toString());
                    //   painterSegundaTirada.drawText(cuadroTexto(8.5,i,1,1,true),2,query.value(2).toString());
                    //  painterSegundaTirada.drawText(cuadroTexto(10.5,i,2,1,true),2,QString::number(query.value(3).toDouble(), 'f', 2));
                }else{
                    painterPrimeraTirada.drawText(cuadroTexto(1,i,2.5,1,true),0,query.value(0).toString());
                    painterPrimeraTirada.drawText(cuadroTexto(2.3,i,5,1,true),0,query.value(1).toString());
                    painterPrimeraTirada.drawText(cuadroTexto(8.5,i,1,1,true),2,query.value(2).toString());
                    painterPrimeraTirada.drawText(cuadroTexto(10.5,i,2,1,true),2,QString::number(query.value(3).toDouble(), 'f', cantidadDecimalesMontoListaPrecio));
                }

                i+=0.5;
                contadorRegistros++;
            }else if(j!=30 && i==30){

                if(j==2){
                    if(paginaSegundaCara){
                        //    painterSegundaTirada.drawText(cuadroTexto(15.4,1,2.5,1,true),0,"ARTICULO");
                        //    painterSegundaTirada.drawText(cuadroTexto(13.6,1,2.5,1,true),0,"||");
                        //    painterSegundaTirada.drawText(cuadroTexto(13.6,1.5,2.5,1,true),0,"||");
                        //    painterSegundaTirada.drawText(cuadroTexto(21.5,1,2,1,true),2,"PRECIO");
                    }else{
                        painterPrimeraTirada.drawText(cuadroTexto(15.4,1,2.5,1,true),0,"ARTICULO");
                        painterPrimeraTirada.drawText(cuadroTexto(13.6,1,2.5,1,true),0,"||");
                        painterPrimeraTirada.drawText(cuadroTexto(13.6,1.5,2.5,1,true),0,"||");
                        painterPrimeraTirada.drawText(cuadroTexto(21.5,1,2,1,true),2,"PRECIO");
                    }
                }

                if(paginaSegundaCara){
                    //  painterSegundaTirada.drawText(cuadroTexto(13.6,j,2.5,1,true),0,"||");
                    //  painterSegundaTirada.drawText(cuadroTexto(14.4,j,2.5,1,true),0,query.value(0).toString());
                    //  painterSegundaTirada.drawText(cuadroTexto(18.4,j,5,1,true),0,query.value(1).toString());
                    //  painterSegundaTirada.drawText(cuadroTexto(19.5,j,1,1,true),2,query.value(2).toString());
                    //  painterSegundaTirada.drawText(cuadroTexto(21.5,j,2,1,true),2,QString::number(query.value(3).toDouble(), 'f', 2));
                }else{
                    painterPrimeraTirada.drawText(cuadroTexto(13.6,j,2.5,1,true),0,"||");
                    painterPrimeraTirada.drawText(cuadroTexto(14.4,j,2.5,1,true),0,query.value(0).toString());
                    painterPrimeraTirada.drawText(cuadroTexto(18.4,j,5,1,true),0,query.value(1).toString());
                    painterPrimeraTirada.drawText(cuadroTexto(19.5,j,1,1,true),2,query.value(2).toString());
                    painterPrimeraTirada.drawText(cuadroTexto(21.5,j,2,1,true),2,QString::number(query.value(3).toDouble(), 'f', cantidadDecimalesMontoListaPrecio));
                }
                j+=0.5;
                contadorRegistros++;
            }

            if(i==30 && j==30){

                if(paginaSegundaCara){

                    // painterSegundaTirada.drawText(cuadroTexto(21,30.5,3,1,true),2,"Pagina #"+QString::number(cantidadPaginas));
                    cantidadPaginas++;
                    if((contadorRegistros+112)< query.size()){
                        //   printer2.newPage();
                    }

                    paginaSegundaCara=false;

                }else{
                    if(contadorRegistros<(query.size()/2)){
                        painterPrimeraTirada.drawText(cuadroTexto(21,30.5,3,1,true),2,"Pagina #"+QString::number(cantidadPaginas));
                        if((contadorRegistros+112)< query.size()){
                            printer.newPage();
                        }
                        cantidadPaginas++;

                    }else{
                        if(terminaPrimerLibro==0){
                            painterPrimeraTirada.drawText(cuadroTexto(21,30.5,3,1,true),2,"Pagina #"+QString::number(cantidadPaginas));
                            if((contadorRegistros+112)< query.size()){
                                printer.newPage();
                            }
                            cantidadPaginas++;
                            terminaPrimerLibro=1;
                        }else{
                            painterPrimeraTirada.drawText(cuadroTexto(21,30.5,3,1,true),2,"Pagina #"+QString::number(cantidadPaginas));
                            if((contadorRegistros+112)< query.size()){
                                printer.newPage();
                            }

                            cantidadPaginas++;

                        }
                    }
                    paginaSegundaCara=true;
                }

                i=2;
                j=2;
            }
        }

        if(paginaSegundaCara){
            //   painterSegundaTirada.drawText(cuadroTexto(21,30.5,3,1,true),2,"Pagina #"+QString::number(cantidadPaginas));
        }else{
            painterPrimeraTirada.drawText(cuadroTexto(21,30.5,3,1,true),2,"Pagina #"+QString::number(cantidadPaginas));
        }

        painterPrimeraTirada.end();

        if(query.size()>112){

            QMessageBox men;
            men.setText(qtTrId("Se termino de enviar a la impresora la primera etapa de impresión\nAhora, de vuelta las hojas y preparece para la segunda etapa.\n\nPrecione 'Continuar' cuando este listo el papel."));

            men.setModal(true);
            men.setWindowTitle("Impresión del reverso");
            men.setWindowIcon(QIcon("qrc:/qml/ProyectoQML/Imagenes/icono.png"));
            men.setMinimumHeight(100);
            men.setStandardButtons(QMessageBox::Ok);
            men.setDefaultButton(QMessageBox::Ok);
            men.setButtonText(1024,"Continuar");

            if(men.exec()!=1024){
                return false;
            }else{

                if(query.size()>112){
                    if (!painterSegundaTirada.begin(&printer2)) {
                        return false;
                    }
                    painterSegundaTirada.setFont(fuente);
                }

                i=2;
                j=2;
                paginaSegundaCara=false;
                query.previous();
                contadorRegistros=0;
                terminaPrimerLibro=0;
                cantidadPaginas=1;

                query.first();
                query.previous();

                while(query.next()){

                    if(i!=30 && j==2){

                        if(i==2){
                            if(paginaSegundaCara){
                                painterSegundaTirada.drawText(cuadroTexto(2,1,2.5,1,true),0,"ARTICULO");
                                painterSegundaTirada.drawText(cuadroTexto(10.5,1,2,1,true),2,"PRECIO");
                            }else{
                                //      painterPrimeraTirada.drawText(cuadroTexto(2,1,2.5,1,true),0,"ARTICULO");
                                //      painterPrimeraTirada.drawText(cuadroTexto(10.5,1,2,1,true),2,"PRECIO");
                            }
                        }

                        if(paginaSegundaCara){
                            painterSegundaTirada.drawText(cuadroTexto(1,i,2.5,1,true),0,query.value(0).toString());
                            painterSegundaTirada.drawText(cuadroTexto(2.3,i,5,1,true),0,query.value(1).toString());
                            painterSegundaTirada.drawText(cuadroTexto(8.5,i,1,1,true),2,query.value(2).toString());
                            painterSegundaTirada.drawText(cuadroTexto(10.5,i,2,1,true),2,QString::number(query.value(3).toDouble(), 'f', cantidadDecimalesMontoListaPrecio));
                        }else{
                            //    painterPrimeraTirada.drawText(cuadroTexto(1,i,2.5,1,true),0,query.value(0).toString());
                            //    painterPrimeraTirada.drawText(cuadroTexto(2.3,i,5,1,true),0,query.value(1).toString());
                            //    painterPrimeraTirada.drawText(cuadroTexto(8.5,i,1,1,true),2,query.value(2).toString());
                            //    painterPrimeraTirada.drawText(cuadroTexto(10.5,i,2,1,true),2,QString::number(query.value(3).toDouble(), 'f', 2));
                        }

                        i+=0.5;
                        contadorRegistros++;
                    }else if(j!=30 && i==30){

                        if(j==2){
                            if(paginaSegundaCara){
                                painterSegundaTirada.drawText(cuadroTexto(15.4,1,2.5,1,true),0,"ARTICULO");
                                painterSegundaTirada.drawText(cuadroTexto(13.6,1,2.5,1,true),0,"||");
                                painterSegundaTirada.drawText(cuadroTexto(13.6,1.5,2.5,1,true),0,"||");
                                painterSegundaTirada.drawText(cuadroTexto(21.5,1,2,1,true),2,"PRECIO");
                            }else{
                                //      painterPrimeraTirada.drawText(cuadroTexto(15.4,1,2.5,1,true),0,"ARTICULO");
                                //      painterPrimeraTirada.drawText(cuadroTexto(13.6,1,2.5,1,true),0,"||");
                                //      painterPrimeraTirada.drawText(cuadroTexto(13.6,1.5,2.5,1,true),0,"||");
                                //      painterPrimeraTirada.drawText(cuadroTexto(21.5,1,2,1,true),2,"PRECIO");
                            }
                        }

                        if(paginaSegundaCara){
                            painterSegundaTirada.drawText(cuadroTexto(13.6,j,2.5,1,true),0,"||");
                            painterSegundaTirada.drawText(cuadroTexto(14.4,j,2.5,1,true),0,query.value(0).toString());
                            painterSegundaTirada.drawText(cuadroTexto(18.4,j,5,1,true),0,query.value(1).toString());
                            painterSegundaTirada.drawText(cuadroTexto(19.5,j,1,1,true),2,query.value(2).toString());
                            painterSegundaTirada.drawText(cuadroTexto(21.5,j,2,1,true),2,QString::number(query.value(3).toDouble(), 'f', cantidadDecimalesMontoListaPrecio));
                        }else{
                            //    painterPrimeraTirada.drawText(cuadroTexto(13.6,j,2.5,1,true),0,"||");
                            //    painterPrimeraTirada.drawText(cuadroTexto(14.4,j,2.5,1,true),0,query.value(0).toString());
                            //    painterPrimeraTirada.drawText(cuadroTexto(18.4,j,5,1,true),0,query.value(1).toString());
                            //    painterPrimeraTirada.drawText(cuadroTexto(19.5,j,1,1,true),2,query.value(2).toString());
                            //    painterPrimeraTirada.drawText(cuadroTexto(21.5,j,2,1,true),2,QString::number(query.value(3).toDouble(), 'f', 2));
                        }
                        j+=0.5;
                        contadorRegistros++;
                    }

                    if(i==30 && j==30){

                        if(paginaSegundaCara){

                            painterSegundaTirada.drawText(cuadroTexto(21,30.5,3,1,true),2,"Pagina #"+QString::number(cantidadPaginas));
                            cantidadPaginas++;
                            if((contadorRegistros+112)< query.size()){
                                printer2.newPage();
                            }

                            paginaSegundaCara=false;

                        }else{
                            if(contadorRegistros<(query.size()/2)){
                                //    painterPrimeraTirada.drawText(cuadroTexto(21,30.5,3,1,true),2,"Pagina #"+QString::number(cantidadPaginas));
                                if((contadorRegistros+112)< query.size()){
                                    //       printer.newPage();
                                }
                                cantidadPaginas++;

                            }else{
                                if(terminaPrimerLibro==0){
                                    //     painterPrimeraTirada.drawText(cuadroTexto(21,30.5,3,1,true),2,"Pagina #"+QString::number(cantidadPaginas));
                                    if((contadorRegistros+112)< query.size()){
                                        //       printer.newPage();
                                    }
                                    cantidadPaginas++;
                                    terminaPrimerLibro=1;
                                }else{
                                    //   painterPrimeraTirada.drawText(cuadroTexto(21,30.5,3,1,true),2,"Pagina #"+QString::number(cantidadPaginas));
                                    if((contadorRegistros+112)< query.size()){
                                        //     printer.newPage();
                                    }

                                    cantidadPaginas++;

                                }
                            }
                            paginaSegundaCara=true;
                        }

                        i=2;
                        j=2;
                    }
                }

                if(paginaSegundaCara){
                    painterSegundaTirada.drawText(cuadroTexto(21,30.5,3,1,true),2,"Pagina #"+QString::number(cantidadPaginas));
                }

                painterSegundaTirada.end();
            }
        }

    }else{
        return false;
    }

}
//################################################################################
//######## Calcula en centimetros la posicion de los campos a imprimirse #########
//################################################################################
QRectF cuadroTexto(double x, double y, double ancho, double alto,bool justifica=false){

    QRectF punto(x*centimetroTexto,y*centimetroTexto,ancho*centimetroTexto,alto*centimetroTexto);
    if(justifica){

        if(x>ancho)
            punto=QRect((x*centimetroTexto)-(ancho*centimetroTexto),y*centimetroTexto,ancho*centimetroTexto,alto*centimetroTexto);

    }
    return punto;
}
