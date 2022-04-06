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

#include "modulolistaprecioarticulos.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include "Utilidades/moduloconfiguracion.h"

ModuloConfiguracion func_configuracionListaArticulos;

ModuloListaPrecioArticulos::ModuloListaPrecioArticulos(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoListaPrecioRole] = "codigoListaPrecio";
    roles[CodigoArticuloRole] = "codigoArticulo";
    roles[DescripcionArticuloRole] = "descripcionArticulo";
    roles[PrecioArticuloRole] = "precioArticulo";

    setRoleNames(roles);
}


ArticulosListaPrecio::ArticulosListaPrecio(const QString &codigoListaPrecio, const QString &codigoArticulo, const QString &descripcionArticulo,const QString &precioArticulo)
    : m_codigoListaPrecio(codigoListaPrecio), m_codigoArticulo(codigoArticulo), m_descripcionArticulo(descripcionArticulo),m_precioArticulo(precioArticulo)
{
}

QString ArticulosListaPrecio::codigoListaPrecio() const
{
    return m_codigoListaPrecio;
}
QString ArticulosListaPrecio::codigoArticulo() const
{
    return m_codigoArticulo;
}
QString ArticulosListaPrecio::descripcionArticulo() const
{
    return m_descripcionArticulo;
}
QString ArticulosListaPrecio::precioArticulo() const
{
    return m_precioArticulo;
}


void ModuloListaPrecioArticulos::addArticulosListaPrecio(const ArticulosListaPrecio &articulosListaPrecio)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ArticulosListaPrecio << articulosListaPrecio;
    endInsertRows();
}

void ModuloListaPrecioArticulos::clearArticulosListaPrecio(){
    m_ArticulosListaPrecio.clear();
}

void ModuloListaPrecioArticulos::buscarArticulosListaPrecio(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){
        QString orderArticulo=" order by A.descripcionArticulo asc ";

        if(func_configuracionListaArticulos.retornaValorConfiguracion("MODO_ARTICULO")=="1"){
            orderArticulo=" order by CAST(A.codigoArticulo as SIGNED) asc ";
        }


        QSqlQuery q = Database::consultaSql("select LA.codigoListaPrecio, LA.codigoArticulo, A.descripcionArticulo, LA.precioArticulo from ListaPrecioArticulos LA join Articulos A on A.codigoArticulo=LA.codigoArticulo join SubRubros SRU on SRU.codigoSubRubro=A.codigoSubRubro join Rubros RU on RU.codigoRubro=SRU.codigoRubro where "+campo+"'"+datoABuscar+"'   "+orderArticulo+"  ");
        QSqlRecord rec = q.record();

        ModuloListaPrecioArticulos::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloListaPrecioArticulos::addArticulosListaPrecio(ArticulosListaPrecio(q.value(rec.indexOf("codigoListaPrecio")).toString(),

                                                                                         q.value(rec.indexOf("codigoArticulo")).toString(),

                                                                                         q.value(rec.indexOf("descripcionArticulo")).toString(),

                                                                                         q.value(rec.indexOf("precioArticulo")).toString()));
            }
        }
    }
}


void ModuloListaPrecioArticulos::buscarArticulosListaPrecioParaModificar(QString _codigoArticulo){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){


        QSqlQuery q = Database::consultaSql("SELECT LP.codigoListaPrecio'codigoListaPrecio','"+_codigoArticulo+"' as 'codigoArticulo',(select AR.descripcionArticulo from Articulos AR  where AR.codigoArticulo='"+_codigoArticulo+"')'descripcionArticulo',case when (select LPA.precioArticulo from ListaPrecioArticulos LPA where LPA.codigoListaPrecio=LP.codigoListaPrecio and LPA.codigoArticulo='"+_codigoArticulo+"') is null then '0.00' else (select LPA.precioArticulo from ListaPrecioArticulos LPA where LPA.codigoListaPrecio=LP.codigoListaPrecio and LPA.codigoArticulo='"+_codigoArticulo+"') end 'precioArticulo'  FROM  ListaPrecio LP order by LP.codigoListaPrecio asc");
        QSqlRecord rec = q.record();

        ModuloListaPrecioArticulos::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloListaPrecioArticulos::addArticulosListaPrecio(ArticulosListaPrecio(q.value(rec.indexOf("codigoListaPrecio")).toString(),

                                                                                         q.value(rec.indexOf("codigoArticulo")).toString(),

                                                                                         q.value(rec.indexOf("descripcionArticulo")).toString(),

                                                                                         q.value(rec.indexOf("precioArticulo")).toString()));
            }
        }
    }
}

int ModuloListaPrecioArticulos::rowCount(const QModelIndex & parent) const {
    return m_ArticulosListaPrecio.count();
}

QVariant ModuloListaPrecioArticulos::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_ArticulosListaPrecio.count()){
        return QVariant();

    }

    const ArticulosListaPrecio &articulosListaPrecio = m_ArticulosListaPrecio[index.row()];

    if (role == CodigoListaPrecioRole){
        return articulosListaPrecio.codigoListaPrecio();

    }
    else if (role == CodigoArticuloRole){
        return articulosListaPrecio.codigoArticulo();

    }
    else if (role == DescripcionArticuloRole){
        return articulosListaPrecio.descripcionArticulo();

    }
    else if (role == PrecioArticuloRole){
        return articulosListaPrecio.precioArticulo();
    }

    return QVariant();
}

int ModuloListaPrecioArticulos::insertarArticulosListaPrecio(QString _codigoListaPrecio, QString _codigoArticulo, QString _precioArticulo) const {

    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el articulo
    // 1  articulo dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar el articulo
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El articulo no tiene los datos sufucientes para darse de alta.

    if(_codigoListaPrecio.trimmed()=="" || _codigoArticulo.trimmed()==""){
        qDebug() << "datos invalidos";
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

        if(query.exec("replace into ListaPrecioArticulos (codigoListaPrecio,codigoArticulo,precioArticulo,sincronizadoWeb) values('"+_codigoListaPrecio+"','"+_codigoArticulo+"','"+_precioArticulo+"','0')")){


            return 1;
        }else{
            return -3;
        }
    }else{return -1;}
}


QString ModuloListaPrecioArticulos::retornarArticulosEnLista(int indice, QString  _codigoListaPrecio) const{

    int contador=0;
    int totalm_ArticulosListaPrecio=m_ArticulosListaPrecio.count();


    for(int i=0;i<totalm_ArticulosListaPrecio;i++){
        if(m_ArticulosListaPrecio[i].codigoListaPrecio()==_codigoListaPrecio){
            if(contador==indice){
                return m_ArticulosListaPrecio[i].codigoArticulo();
            }
            contador++;
        }
    }
    return "";
}

QString ModuloListaPrecioArticulos::retornarDescripcionArticulosEnLista(int indice, QString  _codigoListaPrecio) const{

    int contador=0;
    int totalm_ArticulosListaPrecio=m_ArticulosListaPrecio.count();


    for(int i=0;i<totalm_ArticulosListaPrecio;i++){
        if(m_ArticulosListaPrecio[i].codigoListaPrecio()==_codigoListaPrecio){
            if(contador==indice){
                return m_ArticulosListaPrecio[i].descripcionArticulo();
            }
            contador++;
        }
    }
    return "";
}




QString ModuloListaPrecioArticulos::retornarPrecioEnLista(int indice, QString  _codigoListaPrecio) const{

    int contador=0;

    int totalm_ArticulosListaPrecio=m_ArticulosListaPrecio.count();

    for(int i=0;i<totalm_ArticulosListaPrecio;i++){
        if(m_ArticulosListaPrecio[i].codigoListaPrecio()==_codigoListaPrecio){
            if(contador==indice){
                return m_ArticulosListaPrecio[i].precioArticulo();
            }
            contador++;
        }
    }
    return "";
}


double ModuloListaPrecioArticulos::retornarPrecioDeArticuloEnBaseDeDatos(QString _codigoArticulo,QString _codigoListaPrecio) const {

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

        if(query.exec("select precioArticulo from ListaPrecioArticulos where codigoListaPrecio='"+_codigoListaPrecio+"' and codigoArticulo ='"+_codigoArticulo+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toDouble();

                }else{
                    return 0.00;
                }
            }else{return 0.00;}
        }else{
            return 0.00;
        }
    }else{return 0.00;}
}



double ModuloListaPrecioArticulos::retornarCostoMonedaReferenciaDelSistema(QString _codigoArticulo) const {

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

        if(query.exec("SELECT DOCLL.costoArticuloMonedaReferencia FROM Documentos DOC join DocumentosLineas DOCLL on DOCLL.codigoDocumento=DOC.codigoDocumento and DOCLL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCLL.serieDocumento=DOC.serieDocumento where DOC.codigoEstadoDocumento in ('E','G') and DOCLL.codigoArticulo='"+_codigoArticulo+"' and DOCLL.costoArticuloMonedaReferencia!=0 order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toDouble();

                }else{
                    return 0.00;
                }
            }else{return 0.00;}
        }else{
            return 0.00;
        }
    }else{return 0.00;}
}

double ModuloListaPrecioArticulos::retornarCostoEnMonedaExtrangera(QString _codigoArticulo) const {

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

        if(query.exec("SELECT DOCLL.precioArticuloUnitario FROM Documentos DOC join DocumentosLineas DOCLL on  DOCLL.codigoDocumento=DOC.codigoDocumento and DOCLL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCLL.serieDocumento=DOC.serieDocumento join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento where TD.utilizaSoloProveedores=1 and DOC.codigoEstadoDocumento in ('E','G') and DOCLL.codigoArticulo='"+_codigoArticulo+"' and DOCLL.costoArticuloMonedaReferencia!=0 order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toDouble();

                }else{
                    return 0.00;
                }
            }else{return 0.00;}
        }else{
            return 0.00;
        }
    }else{return 0.00;}
}

QString ModuloListaPrecioArticulos::retornarSimboloMonedaDocumentoArticuloCosto(QString _codigoArticulo) const {

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

        if(query.exec("SELECT MON.simboloMoneda FROM Documentos DOC join DocumentosLineas DOCLL on  DOCLL.codigoDocumento=DOC.codigoDocumento and DOCLL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCLL.serieDocumento=DOC.serieDocumento join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where TD.utilizaSoloProveedores=1 and DOC.codigoEstadoDocumento in ('E','G') and DOCLL.codigoArticulo='"+_codigoArticulo+"' and DOCLL.costoArticuloMonedaReferencia!=0  order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1")) {
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
}



bool ModuloListaPrecioArticulos::eliminarArticulosListaPrecio(QString _codigoListaPrecio) const {
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



        if(query.exec("select codigoArticulo from ListaPrecioArticulos where codigoListaPrecio='"+_codigoListaPrecio+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("delete from ListaPrecioArticulos where codigoListaPrecio='"+_codigoListaPrecio+"' ")){

                        return true;

                    }else{
                        return false;
                    }
                }else{
                    return true;
                }
            }else{return true;}


        }else{
            return false;
        }
    }else{return false;}
}
bool ModuloListaPrecioArticulos::eliminarArticuloPorListaPrecio(QString _codigoListaPrecio, QString _codigoArticulo) const {
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



        if(query.exec("select codigoArticulo from ListaPrecioArticulos where codigoListaPrecio='"+_codigoListaPrecio+"' and codigoArticulo='"+_codigoArticulo+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("delete from ListaPrecioArticulos where codigoListaPrecio='"+_codigoListaPrecio+"' and  codigoArticulo='"+_codigoArticulo+"'")){

                        return true;

                    }else{
                        return false;
                    }
                }else{
                    return true;
                }
            }else{return true;}


        }else{
            return false;
        }
    }else{return false;}
}

bool ModuloListaPrecioArticulos::eliminarArticuloDeListaPrecio(QString _codigoArticulo) const {
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


        if(query.exec("delete from ListaPrecioArticulos where codigoArticulo='"+_codigoArticulo+"' ")){

            return true;

        }else{
            return false;
        }

    }else{return false;}
}

bool ModuloListaPrecioArticulos::actualizarArticuloDeListaPrecio(QString _codigoArticulo,QString _codigoListaDePrecio,QString _precioArticulo) const {

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

        if(query.exec("replace into ListaPrecioArticulos (codigoListaPrecio,codigoArticulo,precioArticulo,sincronizadoWeb) values('"+_codigoListaDePrecio+"','"+_codigoArticulo+"','"+_precioArticulo+"','0')"))
        {

            return true;
        }else{
            return false;
        }

    }else{return false;}
}
qlonglong ModuloListaPrecioArticulos::retornaCantidadArticulosEnListaPrecio(QString _codigoListaPrecio) const {
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

        if(query.exec("select count(*) from ListaPrecioArticulos where codigoListaPrecio='"+_codigoListaPrecio+"'")) {
            if(query.first()){
                if(query.value(0).toString()!="0"){

                    return query.value(0).toLongLong();

                }else{
                    return 0;
                }
            }else{return 0;}
        }else{
            return 0;
        }
    }else{return 0;}
}
QString ModuloListaPrecioArticulos::retornaCodigoListaPrecio(int index){return m_ArticulosListaPrecio[index].codigoListaPrecio();}
QString ModuloListaPrecioArticulos::retornaCodigoArticulo(int index){return m_ArticulosListaPrecio[index].codigoArticulo();}
QString ModuloListaPrecioArticulos::retornaPrecioArticulo(int index){return m_ArticulosListaPrecio[index].precioArticulo();}
QString ModuloListaPrecioArticulos::retornaDescripcionArticulo(int index){return m_ArticulosListaPrecio[index].descripcionArticulo();}
