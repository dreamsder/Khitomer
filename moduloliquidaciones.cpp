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

#include "moduloliquidaciones.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include <modulomonedas.h>
#include <Utilidades/moduloconfiguracion.h>


ModuloMonedas func_moneda;
ModuloConfiguracion conf_;

ModuloLiquidaciones::ModuloLiquidaciones(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoLiquidacionRole] = "codigoLiquidacion";
    roles[CodigoVendedorRole] = "codigoVendedor";
    roles[NombreCompletoVendedorRole] = "nombreCompletoVendedor";
    roles[FechaLiquidacionRole] = "fechaLiquidacion";
    roles[FechaCierreLiquidacionRole] = "fechaCierreLiquidacion";
    roles[EstadoLiquidacionRole] = "estadoLiquidacion";
    roles[UsuarioAltaRole] = "usuarioAlta";
    setRoleNames(roles);


}


Liquidacion::Liquidacion(const QString &codigoLiquidacion, const QString &codigoVendedor, const QString &nombreCompletoVendedor, const QString &fechaLiquidacion, const QString &fechaCierreLiquidacion, const QString &estadoLiquidacion, const QString &usuarioAlta)
    : m_codigoLiquidacion(codigoLiquidacion), m_codigoVendedor(codigoVendedor), m_nombreCompletoVendedor(nombreCompletoVendedor), m_fechaLiquidacion(fechaLiquidacion), m_fechaCierreLiquidacion(fechaCierreLiquidacion), m_estadoLiquidacion(estadoLiquidacion), m_usuarioAlta(usuarioAlta)

{
}

QString Liquidacion::codigoLiquidacion() const
{
    return m_codigoLiquidacion;
}
QString Liquidacion::codigoVendedor() const
{
    return m_codigoVendedor;
}
QString Liquidacion::nombreCompletoVendedor() const
{
    return m_nombreCompletoVendedor;
}
QString Liquidacion::fechaLiquidacion() const
{
    return m_fechaLiquidacion;
}
QString Liquidacion::fechaCierreLiquidacion() const
{
    return m_fechaCierreLiquidacion;
}
QString Liquidacion::estadoLiquidacion() const
{
    return m_estadoLiquidacion;
}

QString Liquidacion::usuarioAlta() const
{
    return m_usuarioAlta;
}


void ModuloLiquidaciones::addLiquidacion(const Liquidacion &liquidacion)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Liquidaciones << liquidacion;
    endInsertRows();
}

void ModuloLiquidaciones::clearLiquidaciones(){
    m_Liquidaciones.clear();
}

void ModuloLiquidaciones::buscarLiquidacion(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from Liquidaciones L join Usuarios U on U.idUsuario=L.codigoVendedor where L.estadoLiquidacion='A' and "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloLiquidaciones::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloLiquidaciones::addLiquidacion(Liquidacion(q.value(rec.indexOf("codigoLiquidacion")).toString(),

                                                                q.value(rec.indexOf("codigoVendedor")).toString(),

                                                                q.value(rec.indexOf("nombreUsuario")).toString()+" "+q.value(rec.indexOf("apellidoUsuario")).toString(),

                                                                q.value(rec.indexOf("fechaLiquidacion")).toString(),

                                                                q.value(rec.indexOf("fechaCierreLiquidacion")).toString(),
                                                                q.value(rec.indexOf("estadoLiquidacion")).toString(),

                                                                q.value(rec.indexOf("usuarioAlta")).toString()));
            }
        }
    }
}

int ModuloLiquidaciones::rowCount(const QModelIndex & parent) const {
    return m_Liquidaciones.count();
}

QVariant ModuloLiquidaciones::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Liquidaciones.count()){
        return QVariant();

    }

    const Liquidacion &liquidacion = m_Liquidaciones[index.row()];

    if (role == CodigoLiquidacionRole){
        return liquidacion.codigoLiquidacion();

    }
    else if (role == CodigoVendedorRole){
        return liquidacion.codigoVendedor();

    }
    else if (role == NombreCompletoVendedorRole){
        return liquidacion.nombreCompletoVendedor();

    }
    else if (role == FechaLiquidacionRole){
        return liquidacion.fechaLiquidacion();

    }
    else if (role == FechaCierreLiquidacionRole){
        return liquidacion.fechaCierreLiquidacion();

    }
    else if (role == EstadoLiquidacionRole){
        return liquidacion.estadoLiquidacion();

    }
    else if (role == UsuarioAltaRole){
        return liquidacion.usuarioAlta();
    }

    return QVariant();
}

int ModuloLiquidaciones::insertarLiquidacion(QString _codigoVendedor, QString _fechaLiquidacion, QString _usuarioAlta) const {


    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el articulo
    // 1  articulo dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar el articulo
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El articulo no tiene los datos sufucientes para darse de alta.

    if(_codigoVendedor.trimmed()=="" || _fechaLiquidacion.trimmed()==""){
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

        QString _codigoLiquidacion= QString::number(ultimoRegistroDeLiquidacionEnBase(_codigoVendedor));

        if(query.exec("insert INTO Liquidaciones (codigoLiquidacion,codigoVendedor,fechaLiquidacion,estadoLiquidacion,usuarioAlta) values('"+_codigoLiquidacion+"','"+_codigoVendedor+"','"+_fechaLiquidacion+"','A','"+_usuarioAlta+"')")){
            return 1;
        }else{
            return -3;
        }
    }else{return -1;}
}


bool ModuloLiquidaciones::eliminarLiquidacion(QString _codigoLiquidacion,QString _codigoVendedor) const {
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

        if(query.exec("select codigoLiquidacion from Liquidaciones where codigoLiquidacion='"+_codigoLiquidacion+"' and codigoVendedor='"+_codigoVendedor+"'  and estadoLiquidacion='A'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    //Compruebo que la liquidacion no tenga documentos
                    if(query.exec("select D.codigoLiquidacion from Documentos D join Liquidaciones L on L.codigoLiquidacion=D.codigoLiquidacion and L.codigoVendedor=D.codigoVendedorLiquidacion where D.codigoLiquidacion='"+_codigoLiquidacion+"' and D.codigoVendedorLiquidacion='"+_codigoVendedor+"'  and L.estadoLiquidacion='A'")) {
                        query.next();
                        if(query.value(0).toString()==""){

                            if(query.exec("delete from Liquidaciones where codigoLiquidacion='"+_codigoLiquidacion+"' and codigoVendedor='"+_codigoVendedor+"'  and estadoLiquidacion='A'")){

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
        }else{
            return false;
        }
    }else{return false;}
}


int ModuloLiquidaciones::ultimoRegistroDeLiquidacionEnBase(QString _codigoVendedor) const{
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


        if(query.exec("select codigoLiquidacion from Liquidaciones where codigoVendedor='"+_codigoVendedor+"' order by codigoLiquidacion desc limit 1")) {

            if(query.first()){
                if(query.value(0).toString()==""){
                    return 1;
                }else{
                    return query.value(0).toInt()+1;
                }
            }else{
                return 1;
            }

        }else{
            return -1;
        }
    }else{
        return -1;
    }
}
QString ModuloLiquidaciones::retornaDescripcionLiquidacionDeVendedorPorDefault(QString _codigoVendedor) const{
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

        if(query.exec("select concat(L.codigoLiquidacion,' - ',U.nombreUsuario,' ',U.apellidoUsuario,' - ',L.fechaLiquidacion) from Liquidaciones L join Usuarios U on U.idUsuario=L.codigoVendedor where L.codigoVendedor='"+_codigoVendedor+"' and L.estadoLiquidacion='A'  order by L.codigoLiquidacion desc limit 1")) {
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
}
QString ModuloLiquidaciones::retornaDescripcionLiquidacionDeVendedor(QString _codigoLiquidacion,QString _codigoVendedor) const{
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

        ///and L.estadoLiquidacion='A'
        if(query.exec("select concat(L.codigoLiquidacion,' - ',U.nombreUsuario,' ',U.apellidoUsuario,' - ',L.fechaLiquidacion) from Liquidaciones L join Usuarios U on U.idUsuario=L.codigoVendedor where L.codigoVendedor='"+_codigoVendedor+"' and L.codigoLiquidacion='"+_codigoLiquidacion+"'   limit 1")) {
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
    }else{
        return "";
    }
}
QString ModuloLiquidaciones::retornaNumeroLiquidacionDeVendedor(QString _codigoVendedor) const{
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

        if(query.exec("select L.codigoLiquidacion from Liquidaciones L join Usuarios U on U.idUsuario=L.codigoVendedor where L.codigoVendedor='"+_codigoVendedor+"' and L.estadoLiquidacion='A'  order by L.codigoLiquidacion desc limit 1")) {
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
    }else{
        return "";
    }
}
QString ModuloLiquidaciones::retornaNumeroPrimeraLiquidacionActiva() const{
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

        if(query.exec("select L.codigoLiquidacion from Liquidaciones L join Usuarios U on U.idUsuario=L.codigoVendedor where L.estadoLiquidacion='A'  order by L.fechaDiaLiquidacion asc limit 1")) {
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
    }else{
        return "";
    }
}
QString ModuloLiquidaciones::retornaCodigoVendedorPrimeraLiquidacionActiva() const{
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

        if(query.exec("select L.codigoVendedor from Liquidaciones L join Usuarios U on U.idUsuario=L.codigoVendedor where L.estadoLiquidacion='A'  order by L.fechaDiaLiquidacion asc limit 1")) {
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
    }else{
        return "";
    }
}



QString ModuloLiquidaciones::retornaValorTotalDocumentosEnLiquidaciones(QString _codigoLiquidacion,QString _codigoVendedor,QString _codigoMoneda) const{
    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){

        QString consultaMonedaReferencia="";
        QString consultaOtrasMonedas="";

        QString modoAfectacionCaja=conf_.retornaValorConfiguracion("MODO_AFECTACION_CAJA");

        if(modoAfectacionCaja=="0"){
            consultaMonedaReferencia="";
            consultaOtrasMonedas="";
        }else if(modoAfectacionCaja=="1"){
            consultaMonedaReferencia="SELECT ROUND(sum(case when  D.codigoMonedaDocumento='"+_codigoMoneda+"' then D.precioTotalVenta*T.afectaTotales else 0 end),2)  FROM Documentos D join Monedas M on M.codigoMoneda=D.codigoMonedaDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento where D.codigoLiquidacion='"+_codigoLiquidacion+"' and D.codigoVendedorLiquidacion='"+_codigoVendedor+"' and T.afectaTotales!=0  and D.codigoEstadoDocumento not in ('C','A')";
            consultaOtrasMonedas="select ROUND(sum(case when  D.codigoMonedaDocumento='"+_codigoMoneda+"' then D.precioTotalVenta*T.afectaTotales else (D.precioTotalVenta/(select MON.cotizacionMoneda from Monedas MON  where codigoMoneda='"+_codigoMoneda+"'))*T.afectaTotales end),2)  FROM Documentos D join Monedas M on M.codigoMoneda=D.codigoMonedaDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento where D.codigoLiquidacion='"+_codigoLiquidacion+"' and D.codigoVendedorLiquidacion='"+_codigoVendedor+"'and D.codigoMonedaDocumento='"+_codigoMoneda+"' and T.afectaTotales!=0 and D.codigoEstadoDocumento not in ('C','A','P')";
        }else if(modoAfectacionCaja=="2"){
            consultaMonedaReferencia="select ROUND(sum(DLP.importePago*T.afectaTotales),2) FROM Documentos D  join DocumentosLineasPago DLP on DLP.codigoDocumento=D.codigoDocumento and  DLP.codigoTipoDocumento=D.codigoTipoDocumento and DLP.serieDocumento=D.serieDocumento join MediosDePago MP on MP.codigoMedioPago=DLP.codigoMedioPago join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento where D.codigoLiquidacion='"+_codigoLiquidacion+"' and D.codigoVendedorLiquidacion='"+_codigoVendedor+"' and T.afectaTotales!=0  and D.codigoEstadoDocumento not in ('C','A','P') and MP.codigoTipoMedioDePago=1 and MP.monedaMedioPago='"+_codigoMoneda+"'";
            consultaOtrasMonedas="select ROUND(sum(DLP.importePago*T.afectaTotales),2) FROM Documentos D  join DocumentosLineasPago DLP on DLP.codigoDocumento=D.codigoDocumento and  DLP.codigoTipoDocumento=D.codigoTipoDocumento and DLP.serieDocumento=D.serieDocumento join MediosDePago MP on MP.codigoMedioPago=DLP.codigoMedioPago join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento where D.codigoLiquidacion='"+_codigoLiquidacion+"' and D.codigoVendedorLiquidacion='"+_codigoVendedor+"' and T.afectaTotales!=0  and D.codigoEstadoDocumento not in ('C','A','P') and MP.codigoTipoMedioDePago=1 and MP.monedaMedioPago='"+_codigoMoneda+"'";
        }else{
            consultaMonedaReferencia="";
            consultaOtrasMonedas="";
            qDebug()<< "ATENCIÓN: Configuracion::MODO_AFECTACION_CAJA contiene un valor incompatible para la funcionalidad de caja";
        }

        QSqlQuery query(Database::connect());

        if(func_moneda.retornaMonedaReferenciaSistema()==_codigoMoneda){
            //if(query.exec("SELECT ROUND(sum(case when  D.codigoMonedaDocumento='"+_codigoMoneda+"' then D.precioTotalVenta*T.afectaTotales else 0 end),2)  FROM Documentos D join Monedas M on M.codigoMoneda=D.codigoMonedaDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento where D.codigoLiquidacion='"+_codigoLiquidacion+"' and D.codigoVendedorLiquidacion='"+_codigoVendedor+"' and T.afectaTotales!=0  and D.codigoEstadoDocumento not in ('C','A') ;")) {
            if(query.exec(consultaMonedaReferencia)) {

                if(query.first()){
                    if(query.value(0).toString()!=""){
                        return query.value(0).toString();
                    }else{
                        return "0";
                    }
                }else{
                    return "0";
                }
            }else{
                return "0";
            }
        }else{

            //if(query.exec("select ROUND(sum(case when  D.codigoMonedaDocumento='"+_codigoMoneda+"' then D.precioTotalVenta*T.afectaTotales else (D.precioTotalVenta/(select MON.cotizacionMoneda from Monedas MON  where codigoMoneda='"+_codigoMoneda+"'))*T.afectaTotales end),2)  FROM Documentos D join Monedas M on M.codigoMoneda=D.codigoMonedaDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento where D.codigoLiquidacion='"+_codigoLiquidacion+"' and D.codigoVendedorLiquidacion='"+_codigoVendedor+"'and D.codigoMonedaDocumento='"+_codigoMoneda+"' and T.afectaTotales!=0 and D.codigoEstadoDocumento not in ('C','A','P');")) {
            if(query.exec(consultaOtrasMonedas)) {

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
        }
    }else{
        return "0";
    }
}
QString ModuloLiquidaciones::retornaCantidadDocumentosEnLiquidacionSegunEstado(QString _codigoLiquidacion,QString _codigoVendedor,QString _estadoDocumento) const{
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

        if(_estadoDocumento=="P"){
            if(query.exec("select count(*) from Documentos where codigoLiquidacion='"+_codigoLiquidacion+"' and codigoVendedorLiquidacion='"+_codigoVendedor+"' and codigoEstadoDocumento='P'")) {
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
            if(query.exec("select count(*) from Documentos where codigoLiquidacion='"+_codigoLiquidacion+"' and codigoVendedorLiquidacion='"+_codigoVendedor+"' and codigoEstadoDocumento not in ('C','A','P')")) {
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
        }
    }else{
        return "";
    }
}
bool ModuloLiquidaciones::cerrarLiquidacion(QString _codigoLiquidacion,QString _codigoVendedor) const {
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

        if(query.exec("select codigoLiquidacion from Liquidaciones where codigoLiquidacion='"+_codigoLiquidacion+"' and codigoVendedor='"+_codigoVendedor+"'  and estadoLiquidacion='A'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("update Liquidaciones set estadoLiquidacion='C' where codigoLiquidacion='"+_codigoLiquidacion+"' and codigoVendedor='"+_codigoVendedor+"'  and estadoLiquidacion='A'")){

                        return true;

                    }else{
                        return false;
                    }
                }else{
                    return false;
                }
            }else {return false;}
        }else{
            return false;
        }
    }else{return false;}
}


bool ModuloLiquidaciones::liquidacionActiva(QString _codigoLiquidacion,QString _codigoVendedor) const{
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

        if(query.exec("select estadoLiquidacion from Liquidaciones  where codigoLiquidacion='"+_codigoLiquidacion+"' and codigoVendedor='"+_codigoVendedor+"' ")) {
            if(query.first()){
                if(query.value(0).toString()=="A"){
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
