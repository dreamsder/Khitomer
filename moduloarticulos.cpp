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

#include "moduloarticulos.h"
#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <Utilidades/database.h>
#include "funciones.h"

#include <Utilidades/moduloconfiguracion.h>
#include <modulolistatipodocumentos.h>

ModuloConfiguracion func_configuracionArticulos;
ModuloListaTipoDocumentos func_tipoDocumentosArticulos;

Funciones func;

ModuloArticulos::ModuloArticulos(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoArticuloRole] = "codigoArticulo";
    roles[DescripcionArticuloRole] = "descripcionArticulo";
    roles[DescripcionExtendidaRole] = "descripcionExtendida";
    roles[CodigoProveedorRole] = "codigoProveedor";
    roles[CodigoIvaRole] = "codigoIva";
    roles[CodigoMonedaRole] = "codigoMoneda";
    roles[ActivoRole] = "activo";
    roles[UsuarioAltaRole] = "usuarioAlta";
    roles[CantidadMinimaStockRole] = "cantidadMinimaStock";
    roles[CodigoSubRubroRole] = "codigoSubRubro";
    roles[codigoTipoGarantiaRole] = "codigoTipoGarantia";

    setRoleNames(roles);

}
Articulo::Articulo(const QString &codigoArticulo, const QString &descripcionArticulo, const QString &descripcionExtendida, const QString &codigoProveedor,const int &codigoIva,const int &codigoMoneda, const QString &activo, const QString &usuarioAlta,
                   const QString &cantidadMinimaStock, const QString &codigoSubRubro, const int &codigoTipoGarantia)
    : m_codigoArticulo(codigoArticulo), m_descripcionArticulo(descripcionArticulo), m_descripcionExtendida(descripcionExtendida), m_codigoProveedor(codigoProveedor),m_codigoIva(codigoIva),m_codigoMoneda(codigoMoneda), m_activo(activo), m_usuarioAlta(usuarioAlta), m_cantidadMinimaStock(cantidadMinimaStock)
    , m_codigoSubRubro(codigoSubRubro),m_codigoTipoGarantia(codigoTipoGarantia)
{
}

QString Articulo::codigoArticulo() const
{
    return m_codigoArticulo;
}
QString Articulo::descripcionArticulo() const
{
    return m_descripcionArticulo;
}
QString Articulo::descripcionExtendida() const
{
    return m_descripcionExtendida;
}

QString Articulo::codigoProveedor() const
{
    return m_codigoProveedor;
}
int Articulo::codigoIva() const
{
    return m_codigoIva;
}
int Articulo::codigoMoneda() const
{
    return m_codigoMoneda;
}

QString Articulo::activo() const
{
    return m_activo;
}
QString Articulo::usuarioAlta() const
{
    return m_usuarioAlta;
}
QString Articulo::cantidadMinimaStock() const
{
    return m_cantidadMinimaStock;
}
QString Articulo::codigoSubRubro() const
{
    return m_codigoSubRubro;
}

int Articulo::codigoTipoGarantia() const{
    return m_codigoTipoGarantia;
}

void ModuloArticulos::addArticulo(const Articulo &articulo)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Articulos << articulo;
    endInsertRows();
}

void ModuloArticulos::clearArticulos(){
    m_Articulos.clear();
}

void ModuloArticulos::buscarArticulo(QString campo, QString datoABuscar, int orden){


    bool conexion=true;

    Database::chequeaStatusAccesoMysql();

    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q;

        if(orden==0){
            q = Database::consultaSql("select * from Articulos join Clientes on Articulos.codigoProveedor=Clientes.codigoCliente and Articulos.tipoCliente=Clientes.tipoCliente where  Clientes.tipoCliente=2  and "+campo+"'"+datoABuscar+"' order by cast(codigoArticulo as unsigned) ");
        }else{
            q = Database::consultaSql("select * from Articulos join Clientes on Articulos.codigoProveedor=Clientes.codigoCliente and Articulos.tipoCliente=Clientes.tipoCliente where  Clientes.tipoCliente=2  and "+campo+"'"+datoABuscar+"' order by Articulos.descripcionArticulo ");
        }


        QSqlRecord rec = q.record();

        ModuloArticulos::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloArticulos::addArticulo(Articulo(q.value(rec.indexOf("codigoArticulo")).toString(),
                                                      q.value(rec.indexOf("descripcionArticulo")).toString(),
                                                      q.value(rec.indexOf("descripcionExtendida")).toString(),
                                                      q.value(rec.indexOf("codigoProveedor")).toString(),
                                                      q.value(rec.indexOf("codigoIva")).toInt(),
                                                      q.value(rec.indexOf("codigoMoneda")).toInt(),
                                                      q.value(rec.indexOf("activo")).toString(),
                                                      q.value(rec.indexOf("usuarioAlta")).toString(),
                                                      q.value(rec.indexOf("cantidadMinimaStock")).toString(),
                                                      q.value(rec.indexOf("codigoSubRubro")).toString(),
                                                      q.value(rec.indexOf("codigoTipoGarantia")).toInt()

                                                      ));
            }
        }
    }
}

int ModuloArticulos::rowCount(const QModelIndex & parent) const {
    return m_Articulos.count();
}

QVariant ModuloArticulos::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Articulos.count()){
        return QVariant();

    }

    const Articulo &articulo = m_Articulos[index.row()];

    if (role == CodigoArticuloRole){
        return articulo.codigoArticulo();

    }
    else if (role == DescripcionArticuloRole){
        return articulo.descripcionArticulo();

    }
    else if (role == DescripcionExtendidaRole){
        return articulo.descripcionExtendida();

    }
    else if (role == CodigoProveedorRole){
        return articulo.codigoProveedor();

    }
    else if (role == CodigoIvaRole){
        return articulo.codigoIva();

    }
    else if (role == CodigoMonedaRole){
        return articulo.codigoMoneda();

    }
    else if (role == ActivoRole){
        return articulo.activo();

    }
    else if (role == UsuarioAltaRole){
        return articulo.usuarioAlta();
    }
    else if (role == CantidadMinimaStockRole){
        return articulo.cantidadMinimaStock();
    }
    else if (role == CodigoSubRubroRole){
        return articulo.codigoSubRubro();
    }
    else if (role == codigoTipoGarantiaRole){
        return articulo.codigoTipoGarantia();
    }

    return QVariant();
}

ulong ModuloArticulos::ultimoRegistroDeArticuloEnBase()const {

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

        if(query.exec("select codigoArticulo from Articulos order by cast(codigoArticulo as unsigned)  desc limit 1")) {

            if(query.first()){
                if(query.value(0).toString()!=""){
                    return query.value(0).toULongLong()+1;
                }else{
                    return 1;
                }
            }else{return 1;}


        }else{
            return 1;
        }
    }
}

int ModuloArticulos::insertarArticulo(QString _codigoArticulo,QString _descripcionArticulo,QString _descripcionExtendida, QString _codigoProveedor,QString _codigoIva,QString _codigoMoneda,QString _activo, QString _usuarioAlta, QString _cantidadMinimaStock, QString _codigoSubRubro, QString _codigoTipoGarantia) const {


    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el articulo
    // 1  articulo dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar el articulo
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El articulo no tiene los datos sufucientes para darse de alta.


    if(_codigoArticulo.trimmed()=="" || _descripcionArticulo.trimmed()=="" || _codigoProveedor.trimmed()==""){
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

        if(query.exec("select codigoArticulo from Articulos where codigoArticulo='"+_codigoArticulo+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("update Articulos set descripcionArticulo='"+_descripcionArticulo+"',descripcionExtendida='"+_descripcionExtendida+"', codigoProveedor='"+_codigoProveedor+"',codigoIva='"+_codigoIva+"',codigoMoneda='"+_codigoMoneda+"',activo='"+_activo+"',usuarioUltimaModificacion='"+_usuarioAlta+"',cantidadMinimaStock='"+_cantidadMinimaStock+"',codigoSubRubro='"+_codigoSubRubro+"',sincronizadoWeb='0', codigoTipoGarantia='"+_codigoTipoGarantia+"'     where codigoArticulo='"+_codigoArticulo+"'")){

                        return 2;
                    }else{
                        return -2;
                    }
                }else{
                    return -2;
                }
            }else{
                if(query.exec("insert INTO Articulos (codigoArticulo,descripcionArticulo,descripcionExtendida,codigoProveedor,codigoIva,codigoMoneda,activo,usuarioAlta,fechaAlta,cantidadMinimaStock,codigoSubRubro,sincronizadoWeb,codigoTipoGarantia) values('"+_codigoArticulo+"','"+_descripcionArticulo+"','"+_descripcionExtendida+"','"+_codigoProveedor+"','"+_codigoIva+"','"+_codigoMoneda+"','"+_activo+"','"+_usuarioAlta+"','"+func.fechaHoraDeHoy()+"','"+_cantidadMinimaStock+"','"+_codigoSubRubro+"','0','"+_codigoTipoGarantia+"')")){
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

bool ModuloArticulos::eliminarArticulo(QString _codigoArticulo) const {

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


        if(query.exec("select codigoArticulo from Articulos where codigoArticulo='"+_codigoArticulo+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("delete from Articulos where codigoArticulo='"+_codigoArticulo+"'")){

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


QString ModuloArticulos::existeArticulo(QString _codigoArticulo) const {    
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

        if(query.exec("select codigoArticulo from Articulos where codigoArticulo='"+_codigoArticulo+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    return query.value(0).toString();
                }else{return "";}
            }
            else{
                if(query.exec("select codigoArticuloInterno from ArticulosBarras where codigoArticuloBarras='"+_codigoArticulo+"'")) {
                    if(query.first()){
                        if(query.value(0).toString()!=""){

                            return query.value(0).toString();

                        }else{
                            return "";
                        }
                    }else{return "";}
                }else{return "";}
            }
        }else{return "";}
    }else{
        return "";
    }
}



QString ModuloArticulos::retornaDescripcionArticulo(QString _codigoArticulo) const {

   /* QString _valor="";

    for (int var = 0; var < m_Articulos.size(); ++var) {
        if(m_Articulos[var].codigoArticulo()==_codigoArticulo ){

            _valor=m_Articulos[var].descripcionArticulo() ;

        }
    }*/


  // if(m_Articulos.size()==0 && _valor==""){
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

            if(query.exec("select descripcionArticulo from Articulos where codigoArticulo='"+_codigoArticulo+"'")) {

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
        }else{
            return "";
        }
    /*}else{
        return _valor;
    }*/
}

QString ModuloArticulos::retornaDescripcionArticuloExtendida(QString _codigoArticulo) const {

    if(func_configuracionArticulos.retornaValorConfiguracion("MUESTRA_DESCRIPCION_ARTICULO_EXTENDIDA_FACTURACION")=="0"){
        return "";
    }

   /* QString _valor="";
    for (int var = 0; var < m_Articulos.size(); ++var) {
        if(m_Articulos[var].codigoArticulo()==_codigoArticulo ){

            _valor=m_Articulos[var].descripcionExtendida() ;

        }
    }


    if(m_Articulos.size()==0 && _valor==""){*/

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

            if(query.exec("select descripcionExtendida from Articulos where codigoArticulo='"+_codigoArticulo+"'")) {

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
        }else{
            return "";
        }

    /*}else{
        return _valor;
    }*/



}


bool ModuloArticulos::retornaArticuloActivo(QString _codigoArticulo) const {

  /*  bool _valor=false;
    for (int var = 0; var < m_Articulos.size(); ++var) {
        if(m_Articulos[var].codigoArticulo()==_codigoArticulo ){
            if(m_Articulos[var].activo()=="1"){
                _valor=true;
            }
        }
    }


    if(m_Articulos.size()==0 && _valor==false){*/
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

            if(query.exec("select activo from Articulos where codigoArticulo='"+_codigoArticulo+"'")) {

                if(query.first()){
                    if(query.value(0).toString()!=""){

                        if(query.value(0).toString()=="1"){
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
   /* }else{
        return _valor;
    }*/


}

qlonglong ModuloArticulos::retornaStockTotalArticulo(QString _codigoArticulo) const {
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
        //if(query.exec("SELECT DOCL.codigoArticulo, sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) 'cantidad' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in ('E','G','P') and DOC.fechaHoraGuardadoDocumentoSQL>=  (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in ('E','G') order by codigoDocumento desc limit 1) and DOCL.codigoArticulo='"+_codigoArticulo+"'  group by DOCL.codigoArticulo")) {
        if(query.exec("SELECT DOCL.codigoArticulo, sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) 'cantidad' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and (DOC.codigoEstadoDocumento in ('E','G') or  (DOC.codigoEstadoDocumento='P' and DOC.codigoTipoDocumento!=5)  ) and DOC.fechaHoraGuardadoDocumentoSQL>=  (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS where DOCS.codigoTipoDocumento=8 and DOCS.codigoEstadoDocumento in ('E','G') order by DOCS.codigoDocumento desc limit 1) and DOCL.codigoArticulo='"+_codigoArticulo+"'  group by DOCL.codigoArticulo")) {

            if(query.first()){
                if(query.value(1).toString()!=""){

                    return query.value(1).toLongLong();

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
qlonglong ModuloArticulos::retornaStockTotalArticuloReal(QString _codigoArticulo) const {
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

        if(query.exec("SELECT DOCL.codigoArticulo, sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) 'cantidad' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in ('E','G') and DOC.fechaHoraGuardadoDocumentoSQL>=  (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in ('E','G') order by codigoDocumento desc limit 1) and DOCL.codigoArticulo='"+_codigoArticulo+"'  group by DOCL.codigoArticulo")) {
            if(query.first()){
                if(query.value(1).toString()!=""){

                    return query.value(1).toLongLong();

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

bool ModuloArticulos::existeArticuloEnDocumentos(QString _codigoArticulo) const {
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

        if(query.exec("select count(codigoArticulo) from DocumentosLineas where codigoArticulo='"+_codigoArticulo+"'")) {

            if(query.first()){
                if(query.value(0).toString()!="0"){

                    return true;

                }else{
                    return false;
                }
            }else{return false;}

        }else{
            return true;
        }
    }else{
        return true;
    }
}
QString ModuloArticulos::retornaCantidadArticulosSinStock() const {
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

        if(query.exec("select sum(FS.cantidadArticulosSinStock) from FaltaStock FS join Articulos AR on AR.codigoArticulo=FS.codigoArticulo where AR.activo=1; ")) {

            if(query.first()){

                if(query.value(0).toString()!="0"){

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
bool ModuloArticulos::reemplazaCantidadArticulosSinStock(QString _codigoArticulos,QString _cantidad) const {

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

        if(query.exec("REPLACE INTO FaltaStock (codigoArticulo,cantidadArticulosSinStock) VALUES('"+_codigoArticulos+"',"+_cantidad+");")) {

            return true;

        }else{
            return false;
        }
    }else{

        return false;
    }
}
qlonglong ModuloArticulos::retornaCantidadMinimaAvisoArticulo(QString _codigoArticulo) const {

 /*   qlonglong _valor=0;
    for (int var = 0; var < m_Articulos.size(); ++var) {
        if(m_Articulos[var].codigoArticulo()==_codigoArticulo ){

            _valor= m_Articulos[var].cantidadMinimaStock().toLongLong();

        }
    }


    if(m_Articulos.size()==0 && _valor==0){*/
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

            if(query.exec("select cantidadMinimaStock from Articulos where codigoArticulo='"+_codigoArticulo+"'")) {

                if(query.first()){
                    if(query.value(0).toString()!=""){

                        return query.value(0).toLongLong();

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
   /* }else{
        return _valor;
    }*/
}


///
/// \brief ModuloArticulos::retornaSiPuedeVenderSinStock
/// \param _cantidad
/// \param _codigoTipoDocumento
/// \param _codigoArticulo
/// \return true o false
///
bool ModuloArticulos::retornaSiPuedeVenderSinStock(qlonglong _cantidad, QString _codigoTipoDocumento, QString _codigoArticulo,qlonglong _cantidadYaVendida) const {

    if(func_tipoDocumentosArticulos.retornaPermisosDelDocumento(_codigoTipoDocumento,"noPermiteFacturarConStockPrevistoCero")){

        qlonglong cantidadItemsVendidos= _cantidad;
        qlonglong cantidadStockPrevisto= retornaStockTotalArticulo(_codigoArticulo)-cantidadItemsVendidos-_cantidadYaVendida;



        if(cantidadStockPrevisto<0){
            func.mensajeAdvertenciaOk("Atención:\n\nNo hay Stock(Previsto) suficiente para agregar el artículo a la venta.");
            return false;
        }else{
            return true;
        }

    }else{
        return true;
    }
}
QString ModuloArticulos::retornaCodigoTipoGarantia(QString _codigoArticulo) const {

   /* QString _valor="0";
    for (int var = 0; var < m_Articulos.size(); ++var) {
        if(m_Articulos[var].codigoArticulo()==_codigoArticulo ){

            _valor= QString::number(m_Articulos[var].codigoTipoGarantia());

        }
    }


     if(m_Articulos.size()==0 && _valor=="0"){*/
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

             if(query.exec("select codigoTipoGarantia from Articulos where codigoArticulo='"+_codigoArticulo+"'")) {

                 if(query.first()){
                     if(query.value(0).toString()!=""){

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
  /*  }else{
         return _valor;
     }*/
}



void ModuloArticulos::actualizarGarantia(QString _codigoArticulo, QString _codigoTipoGarantia) const {

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
        query.exec("update Articulos set codigoTipoGarantia='"+_codigoTipoGarantia+"'  where codigoArticulo='"+_codigoArticulo+"'");
    }
}
