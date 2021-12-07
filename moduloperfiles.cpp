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

#include "moduloperfiles.h"
#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>
#include <Utilidades/database.h>

ModuloPerfiles::ModuloPerfiles(QObject *parent)
    : QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[CodigoPerfilRole] = "codigoPerfil";
    roles[DescripcionPerfilRole] = "descripcionPerfil";

    roles[permiteUsarLiquidacionesRole] = "permiteUsarLiquidaciones";
    roles[permiteUsarFacturacionRole] = "permiteUsarFacturacion";
    roles[permiteUsarArticulosRole] = "permiteUsarArticulos";
    roles[permiteUsarListaPreciosRole] = "permiteUsarListaPrecios";
    roles[permiteUsarClientesRole] = "permiteUsarClientes";
    roles[permiteUsarMenuAvanzadoRole] = "permiteUsarMenuAvanzado";
    roles[permiteUsarDocumentosRole] = "permiteUsarDocumentos";
    roles[permiteUsarReportesRole] = "permiteUsarReportes";
    roles[permiteUsarCuentaCorrienteRole] = "permiteUsarCuentaCorriente";
    roles[permiteCrearLiquidacionesRole] = "permiteCrearLiquidaciones";
    roles[permiteBorrarLiquidacionesRole] = "permiteBorrarLiquidaciones";
    roles[permiteCerrarLiquidacionesRole] = "permiteCerrarLiquidaciones";
    roles[permiteAutorizarCierreLiquidacionesRole] = "permiteAutorizarCierreLiquidaciones";
    roles[permiteCrearFacturasRole] = "permiteCrearFacturas";
    roles[permiteBorrarFacturasRole] = "permiteBorrarFacturas";
    roles[permiteAnularFacturasRole] = "permiteAnularFacturas";
    roles[permiteCrearClientesRole] = "permiteCrearClientes";
    roles[permiteBorrarClientesRole] = "permiteBorrarClientes";
    roles[permiteCrearArticulosRole] = "permiteCrearArticulos";
    roles[permiteBorrarArticulosRole] = "permiteBorrarArticulos";
    roles[permiteCrearListaDePreciosRole] = "permiteCrearListaDePrecios";
    roles[permiteBorrarListaDePreciosRole] = "permiteBorrarListaDePrecios";
    roles[permiteAutorizarDescuentosArticuloRole] = "permiteAutorizarDescuentosArticulo";
    roles[permiteAutorizarDescuentosTotalRole] = "permiteAutorizarDescuentosTotal";
    roles[permiteAutorizarAnulacionesRole] = "permiteAutorizarAnulaciones";
    roles[permiteExportarAPDFRole] = "permiteExportarAPDF";
    roles[permiteReimprimirFacturasRole] = "permiteReimprimirFacturas";

    roles[permiteCambioRapidoDePreciosRole] = "permiteCambioRapidoDePrecios";


    roles[permiteUsarMenuAvanzadoConfiguracionesRole]="permiteUsarMenuAvanzadoConfiguraciones";
    roles[permiteUsarMenuAvanzadoIvasRole]="permiteUsarMenuAvanzadoIvas";
    roles[permiteUsarMenuAvanzadoTiposDeDocumentosRole]="permiteUsarMenuAvanzadoTiposDeDocumentos";
    roles[permiteUsarMenuAvanzadoLocalidadesRole]="permiteUsarMenuAvanzadoLocalidades";
    roles[permiteUsarMenuAvanzadoBancosRole]="permiteUsarMenuAvanzadoBancos";
    roles[permiteUsarMenuAvanzadoPagoDeFinacierasRole]="permiteUsarMenuAvanzadoPagoDeFinacieras";
    roles[permiteUsarMenuAvanzadoCuentasBancariasRole]="permiteUsarMenuAvanzadoCuentasBancarias";
    roles[permiteUsarMenuAvanzadoRubrosRole]="permiteUsarMenuAvanzadoRubros";
    roles[permiteUsarMenuAvanzadoMonedasRole]="permiteUsarMenuAvanzadoMonedas";
    roles[permiteUsarMenuAvanzadoPermisosRole]="permiteUsarMenuAvanzadoPermisos";
    roles[permiteUsarMenuAvanzadoUsuariosRole]="permiteUsarMenuAvanzadoUsuarios";




    setRoleNames(roles);

}


Perfiles::Perfiles(const int &codigoPerfil, const QString &descripcionPerfil
                   ,const QString &permiteUsarLiquidaciones
                   ,const QString &permiteUsarFacturacion
                   ,const QString &permiteUsarArticulos
                   ,const QString &permiteUsarListaPrecios
                   ,const QString &permiteUsarClientes
                   ,const QString &permiteUsarMenuAvanzado

                   ,const QString &permiteUsarDocumentos
                   ,const QString &permiteUsarReportes
                   ,const QString &permiteUsarCuentaCorriente
                   ,const QString &permiteCrearLiquidaciones
                   ,const QString &permiteBorrarLiquidaciones
                   ,const QString &permiteCerrarLiquidaciones
                   ,const QString &permiteAutorizarCierreLiquidaciones
                   ,const QString &permiteCrearFacturas
                   ,const QString &permiteBorrarFacturas
                   ,const QString &permiteAnularFacturas
                   ,const QString &permiteCrearClientes
                   ,const QString &permiteBorrarClientes
                   ,const QString &permiteCrearArticulos
                   ,const QString &permiteBorrarArticulos
                   ,const QString &permiteCrearListaDePrecios
                   ,const QString &permiteBorrarListaDePrecios
                   ,const QString &permiteAutorizarDescuentosArticulo
                   ,const QString &permiteAutorizarDescuentosTotal
                   ,const QString &permiteAutorizarAnulaciones
                   ,const QString &permiteExportarAPDF
                   ,const QString &permiteReimprimirFacturas
                   ,const QString &permiteCambioRapidoDePrecios,


                   const QString &permiteUsarMenuAvanzadoConfiguraciones,
                   const QString &permiteUsarMenuAvanzadoIvas,
                   const QString &permiteUsarMenuAvanzadoTiposDeDocumentos,
                   const QString &permiteUsarMenuAvanzadoLocalidades,
                   const QString &permiteUsarMenuAvanzadoBancos,
                   const QString &permiteUsarMenuAvanzadoPagoDeFinacieras,
                   const QString &permiteUsarMenuAvanzadoCuentasBancarias,
                   const QString &permiteUsarMenuAvanzadoRubros,
                   const QString &permiteUsarMenuAvanzadoMonedas,
                   const QString &permiteUsarMenuAvanzadoPermisos,
                   const QString &permiteUsarMenuAvanzadoUsuarios


                   )



    : m_codigoPerfil(codigoPerfil), m_descripcionPerfil(descripcionPerfil), m_permiteUsarLiquidaciones(permiteUsarLiquidaciones)
    , m_permiteUsarFacturacion(permiteUsarFacturacion)
    , m_permiteUsarArticulos(permiteUsarArticulos)
    , m_permiteUsarListaPrecios(permiteUsarListaPrecios)
    , m_permiteUsarClientes(permiteUsarClientes)
    , m_permiteUsarMenuAvanzado(permiteUsarMenuAvanzado)

    , m_permiteUsarDocumentos(permiteUsarDocumentos)
    , m_permiteUsarReportes(permiteUsarReportes)
    , m_permiteUsarCuentaCorriente(permiteUsarCuentaCorriente)
    , m_permiteCrearLiquidaciones(permiteCrearLiquidaciones)
    , m_permiteBorrarLiquidaciones(permiteBorrarLiquidaciones)
    , m_permiteCerrarLiquidaciones(permiteCerrarLiquidaciones)
    , m_permiteAutorizarCierreLiquidaciones(permiteAutorizarCierreLiquidaciones)
    , m_permiteCrearFacturas(permiteCrearFacturas)
    , m_permiteBorrarFacturas(permiteBorrarFacturas)
    , m_permiteAnularFacturas(permiteAnularFacturas)
    , m_permiteCrearClientes(permiteCrearClientes)
    , m_permiteBorrarClientes(permiteBorrarClientes)
    , m_permiteCrearArticulos(permiteCrearArticulos)
    , m_permiteBorrarArticulos(permiteBorrarArticulos)
    , m_permiteCrearListaDePrecios(permiteCrearListaDePrecios)
    , m_permiteBorrarListaDePrecios(permiteBorrarListaDePrecios)
    , m_permiteAutorizarDescuentosArticulo(permiteAutorizarDescuentosArticulo)
    , m_permiteAutorizarDescuentosTotal(permiteAutorizarDescuentosTotal)
    , m_permiteAutorizarAnulaciones(permiteAutorizarAnulaciones)
    , m_permiteExportarAPDF(permiteExportarAPDF)
    , m_permiteReimprimirFacturas(permiteReimprimirFacturas)
    , m_permiteCambioRapidoDePrecios(permiteCambioRapidoDePrecios),

      m_permiteUsarMenuAvanzadoConfiguraciones(permiteUsarMenuAvanzadoConfiguraciones),
      m_permiteUsarMenuAvanzadoIvas(permiteUsarMenuAvanzadoIvas),
      m_permiteUsarMenuAvanzadoTiposDeDocumentos(permiteUsarMenuAvanzadoTiposDeDocumentos),
      m_permiteUsarMenuAvanzadoLocalidades(permiteUsarMenuAvanzadoLocalidades),
      m_permiteUsarMenuAvanzadoBancos(permiteUsarMenuAvanzadoBancos),
      m_permiteUsarMenuAvanzadoPagoDeFinacieras(permiteUsarMenuAvanzadoPagoDeFinacieras),
      m_permiteUsarMenuAvanzadoCuentasBancarias(permiteUsarMenuAvanzadoCuentasBancarias),
      m_permiteUsarMenuAvanzadoRubros(permiteUsarMenuAvanzadoRubros),
      m_permiteUsarMenuAvanzadoMonedas(permiteUsarMenuAvanzadoMonedas),
      m_permiteUsarMenuAvanzadoPermisos(permiteUsarMenuAvanzadoPermisos),
      m_permiteUsarMenuAvanzadoUsuarios(permiteUsarMenuAvanzadoUsuarios)


{
}

int Perfiles::codigoPerfil() const
{
    return m_codigoPerfil;
}
QString Perfiles::descripcionPerfil() const
{
    return m_descripcionPerfil;
}
QString Perfiles::permiteUsarLiquidaciones() const
{
    return m_permiteUsarLiquidaciones;
}
QString Perfiles::permiteUsarFacturacion() const
{
    return m_permiteUsarFacturacion;
}
QString Perfiles::permiteUsarArticulos() const
{
    return m_permiteUsarArticulos;
}
QString Perfiles::permiteUsarListaPrecios() const
{
    return m_permiteUsarListaPrecios;
}
QString Perfiles::permiteUsarClientes() const
{
    return m_permiteUsarClientes;
}
QString Perfiles::permiteUsarMenuAvanzado() const { return m_permiteUsarMenuAvanzado; }

QString Perfiles::permiteUsarDocumentos() const { return m_permiteUsarDocumentos; }
QString Perfiles::permiteUsarReportes() const { return m_permiteUsarReportes; }
QString Perfiles::permiteUsarCuentaCorriente() const { return m_permiteUsarCuentaCorriente; }
QString Perfiles::permiteCrearLiquidaciones() const { return m_permiteCrearLiquidaciones; }
QString Perfiles::permiteBorrarLiquidaciones() const { return m_permiteBorrarLiquidaciones; }
QString Perfiles::permiteCerrarLiquidaciones() const { return m_permiteCerrarLiquidaciones; }
QString Perfiles::permiteAutorizarCierreLiquidaciones() const { return m_permiteAutorizarCierreLiquidaciones; }
QString Perfiles::permiteCrearFacturas() const { return m_permiteCrearFacturas; }
QString Perfiles::permiteBorrarFacturas() const { return m_permiteBorrarFacturas; }
QString Perfiles::permiteAnularFacturas() const { return m_permiteAnularFacturas; }
QString Perfiles::permiteCrearClientes() const { return m_permiteCrearClientes; }
QString Perfiles::permiteBorrarClientes() const { return m_permiteBorrarClientes; }
QString Perfiles::permiteCrearArticulos() const { return m_permiteCrearArticulos; }
QString Perfiles::permiteBorrarArticulos() const { return m_permiteBorrarArticulos; }
QString Perfiles::permiteCrearListaDePrecios() const { return m_permiteCrearListaDePrecios; }
QString Perfiles::permiteBorrarListaDePrecios() const { return m_permiteBorrarListaDePrecios; }
QString Perfiles::permiteAutorizarDescuentosArticulo() const { return m_permiteAutorizarDescuentosArticulo; }
QString Perfiles::permiteAutorizarDescuentosTotal() const { return m_permiteAutorizarDescuentosTotal; }
QString Perfiles::permiteAutorizarAnulaciones() const { return m_permiteAutorizarAnulaciones; }
QString Perfiles::permiteExportarAPDF() const { return m_permiteExportarAPDF; }
QString Perfiles::permiteReimprimirFacturas() const { return m_permiteReimprimirFacturas; }
QString Perfiles::permiteCambioRapidoDePrecios() const { return m_permiteCambioRapidoDePrecios; }


QString Perfiles::permiteUsarMenuAvanzadoConfiguraciones()const{
    return m_permiteUsarMenuAvanzadoConfiguraciones;}
QString Perfiles::permiteUsarMenuAvanzadoIvas()const{
    return m_permiteUsarMenuAvanzadoIvas;}
QString Perfiles::permiteUsarMenuAvanzadoTiposDeDocumentos()const{
    return m_permiteUsarMenuAvanzadoTiposDeDocumentos;}
QString Perfiles::permiteUsarMenuAvanzadoLocalidades()const{
    return m_permiteUsarMenuAvanzadoLocalidades;}
QString Perfiles::permiteUsarMenuAvanzadoBancos()const{
    return m_permiteUsarMenuAvanzadoBancos;}
QString Perfiles::permiteUsarMenuAvanzadoPagoDeFinacieras()const{
    return m_permiteUsarMenuAvanzadoPagoDeFinacieras;}
QString Perfiles::permiteUsarMenuAvanzadoCuentasBancarias()const{
    return m_permiteUsarMenuAvanzadoCuentasBancarias;}
QString Perfiles::permiteUsarMenuAvanzadoRubros()const{
    return m_permiteUsarMenuAvanzadoRubros;}
QString Perfiles::permiteUsarMenuAvanzadoMonedas()const{
    return m_permiteUsarMenuAvanzadoMonedas;}
QString Perfiles::permiteUsarMenuAvanzadoPermisos()const{
    return m_permiteUsarMenuAvanzadoPermisos;}
QString Perfiles::permiteUsarMenuAvanzadoUsuarios()const{
    return m_permiteUsarMenuAvanzadoUsuarios;}



void ModuloPerfiles::agregarPerfil(const Perfiles &perfiles)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Perfiles << perfiles;
    endInsertRows();
}

void ModuloPerfiles::limpiarListaPerfiles(){
    m_Perfiles.clear();
}

void ModuloPerfiles::buscarPerfiles(QString campo, QString datoABuscar){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from PerfilesUsuarios where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloPerfiles::reset();
        if(q.record().count()>0){

            while (q.next()){

                ModuloPerfiles::agregarPerfil(Perfiles(q.value(rec.indexOf("codigoPerfil")).toInt(),
                                                       q.value(rec.indexOf("descripcionPerfil")).toString(),
                                                       q.value(rec.indexOf("permiteUsarLiquidaciones")).toString(),
                                                       q.value(rec.indexOf("permiteUsarFacturacion")).toString(),
                                                       q.value(rec.indexOf("permiteUsarArticulos")).toString(),
                                                       q.value(rec.indexOf("permiteUsarListaPrecios")).toString(),
                                                       q.value(rec.indexOf("permiteUsarClientes")).toString(),
                                                       q.value(rec.indexOf("permiteUsarMenuAvanzado")).toString(),

                                                       q.value(rec.indexOf("permiteUsarDocumentos")).toString(),
                                                       q.value(rec.indexOf("permiteUsarReportes")).toString(),
                                                       q.value(rec.indexOf("permiteUsarCuentaCorriente")).toString(),
                                                       q.value(rec.indexOf("permiteCrearLiquidaciones")).toString(),
                                                       q.value(rec.indexOf("permiteBorrarLiquidaciones")).toString(),
                                                       q.value(rec.indexOf("permiteCerrarLiquidaciones")).toString(),
                                                       q.value(rec.indexOf("permiteAutorizarCierreLiquidaciones")).toString(),
                                                       q.value(rec.indexOf("permiteCrearFacturas")).toString(),
                                                       q.value(rec.indexOf("permiteBorrarFacturas")).toString(),
                                                       q.value(rec.indexOf("permiteAnularFacturas")).toString(),
                                                       q.value(rec.indexOf("permiteCrearClientes")).toString(),
                                                       q.value(rec.indexOf("permiteBorrarClientes")).toString(),
                                                       q.value(rec.indexOf("permiteCrearArticulos")).toString(),
                                                       q.value(rec.indexOf("permiteBorrarArticulos")).toString(),
                                                       q.value(rec.indexOf("permiteCrearListaDePrecios")).toString(),
                                                       q.value(rec.indexOf("permiteBorrarListaDePrecios")).toString(),
                                                       q.value(rec.indexOf("permiteAutorizarDescuentosArticulo")).toString(),
                                                       q.value(rec.indexOf("permiteAutorizarDescuentosTotal")).toString(),
                                                       q.value(rec.indexOf("permiteAutorizarAnulaciones")).toString(),
                                                       q.value(rec.indexOf("permiteExportarAPDF")).toString(),
                                                       q.value(rec.indexOf("permiteReimprimirFacturas")).toString(),
                                                       q.value(rec.indexOf("permiteCambioRapidoDePrecios")).toString(),

                                                       q.value(rec.indexOf("permiteUsarMenuAvanzadoConfiguraciones")).toString(),
                                                       q.value(rec.indexOf("permiteUsarMenuAvanzadoIvas")).toString(),
                                                       q.value(rec.indexOf("permiteUsarMenuAvanzadoTiposDeDocumentos")).toString(),
                                                       q.value(rec.indexOf("permiteUsarMenuAvanzadoLocalidades")).toString(),
                                                       q.value(rec.indexOf("permiteUsarMenuAvanzadoBancos")).toString(),
                                                       q.value(rec.indexOf("permiteUsarMenuAvanzadoPagoDeFinacieras")).toString(),
                                                       q.value(rec.indexOf("permiteUsarMenuAvanzadoCuentasBancarias")).toString(),
                                                       q.value(rec.indexOf("permiteUsarMenuAvanzadoRubros")).toString(),
                                                       q.value(rec.indexOf("permiteUsarMenuAvanzadoMonedas")).toString(),
                                                       q.value(rec.indexOf("permiteUsarMenuAvanzadoPermisos")).toString(),
                                                       q.value(rec.indexOf("permiteUsarMenuAvanzadoUsuarios")).toString()



                                                       ));
            }
        }
    }
}

int ModuloPerfiles::rowCount(const QModelIndex & parent) const {
    return m_Perfiles.count();
}

QVariant ModuloPerfiles::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Perfiles.count()){
        return QVariant();

    }

    const Perfiles &perfiles = m_Perfiles[index.row()];

    if (role == CodigoPerfilRole){
        return perfiles.codigoPerfil();

    }
    else if (role == DescripcionPerfilRole){ return perfiles.descripcionPerfil();    }

    else if (role == permiteUsarLiquidacionesRole){ return perfiles.permiteUsarLiquidaciones();    }
    else if (role == permiteUsarFacturacionRole){ return perfiles.permiteUsarFacturacion();    }
    else if (role == permiteUsarArticulosRole){ return perfiles.permiteUsarArticulos();    }
    else if (role == permiteUsarListaPreciosRole){ return perfiles.permiteUsarListaPrecios();    }
    else if (role == permiteUsarClientesRole){ return perfiles.permiteUsarClientes();    }
    else if (role == permiteUsarMenuAvanzadoRole){ return perfiles.permiteUsarMenuAvanzado();    }

    else if (role == permiteUsarDocumentosRole){ return perfiles.permiteUsarDocumentos();}
    else if (role == permiteUsarReportesRole){ return perfiles.permiteUsarReportes();}
    else if (role == permiteUsarCuentaCorrienteRole){ return perfiles.permiteUsarCuentaCorriente();}
    else if (role == permiteCrearLiquidacionesRole){ return perfiles.permiteCrearLiquidaciones();}
    else if (role == permiteBorrarLiquidacionesRole){ return perfiles.permiteBorrarLiquidaciones();}
    else if (role == permiteCerrarLiquidacionesRole){ return perfiles.permiteCerrarLiquidaciones();}
    else if (role == permiteAutorizarCierreLiquidacionesRole){ return perfiles.permiteAutorizarCierreLiquidaciones();}
    else if (role == permiteCrearFacturasRole){ return perfiles.permiteCrearFacturas();}
    else if (role == permiteBorrarFacturasRole){ return perfiles.permiteBorrarFacturas();}
    else if (role == permiteAnularFacturasRole){ return perfiles.permiteAnularFacturas();}
    else if (role == permiteCrearClientesRole){ return perfiles.permiteCrearClientes();}
    else if (role == permiteBorrarClientesRole){ return perfiles.permiteBorrarClientes();}
    else if (role == permiteCrearArticulosRole){ return perfiles.permiteCrearArticulos();}
    else if (role == permiteBorrarArticulosRole){ return perfiles.permiteBorrarArticulos();}
    else if (role == permiteCrearListaDePreciosRole){ return perfiles.permiteCrearListaDePrecios();}
    else if (role == permiteBorrarListaDePreciosRole){ return perfiles.permiteBorrarListaDePrecios();}
    else if (role == permiteAutorizarDescuentosArticuloRole){ return perfiles.permiteAutorizarDescuentosArticulo();}
    else if (role == permiteAutorizarDescuentosTotalRole){ return perfiles.permiteAutorizarDescuentosTotal();}
    else if (role == permiteAutorizarAnulacionesRole){ return perfiles.permiteAutorizarAnulaciones();}
    else if (role == permiteExportarAPDFRole){ return perfiles.permiteExportarAPDF();}
    else if (role == permiteReimprimirFacturasRole){ return perfiles.permiteReimprimirFacturas();}
    else if (role == permiteCambioRapidoDePreciosRole){ return perfiles.permiteCambioRapidoDePrecios();}



    else if (role == permiteUsarMenuAvanzadoConfiguracionesRole)
    {
        return perfiles.permiteUsarMenuAvanzadoConfiguraciones();
    }
    else if (role == permiteUsarMenuAvanzadoIvasRole)
    {
        return perfiles.permiteUsarMenuAvanzadoIvas();
    }
    else if (role == permiteUsarMenuAvanzadoTiposDeDocumentosRole)
    {
        return perfiles.permiteUsarMenuAvanzadoTiposDeDocumentos();
    }
    else if (role == permiteUsarMenuAvanzadoLocalidadesRole)
    {
        return perfiles.permiteUsarMenuAvanzadoLocalidades();
    }
    else if (role == permiteUsarMenuAvanzadoBancosRole)
    {
        return perfiles.permiteUsarMenuAvanzadoBancos();
    }
    else if (role == permiteUsarMenuAvanzadoPagoDeFinacierasRole)
    {
        return perfiles.permiteUsarMenuAvanzadoPagoDeFinacieras();
    }
    else if (role == permiteUsarMenuAvanzadoCuentasBancariasRole)
    {
        return perfiles.permiteUsarMenuAvanzadoCuentasBancarias();
    }
    else if (role == permiteUsarMenuAvanzadoRubrosRole)
    {
        return perfiles.permiteUsarMenuAvanzadoRubros();
    }
    else if (role == permiteUsarMenuAvanzadoMonedasRole)
    {
        return perfiles.permiteUsarMenuAvanzadoMonedas();
    }
    else if (role == permiteUsarMenuAvanzadoPermisosRole)
    {
        return perfiles.permiteUsarMenuAvanzadoPermisos();
    }
    else if (role == permiteUsarMenuAvanzadoUsuariosRole)
    {
        return perfiles.permiteUsarMenuAvanzadoUsuarios();
    }



    return QVariant();
}
QString ModuloPerfiles::retornaDescripcionPerfil(QString _codigoPerfil) const{
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

        if(query.exec("select descripcionPerfil from PerfilesUsuarios where codigoPerfil='"+_codigoPerfil+"'")) {

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

bool ModuloPerfiles::retornaValorDePermiso(QString _idUsuario,QString _permiso) const{
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

        QString valorPerfil=retornaCodigoPerfil(_idUsuario);

        if(valorPerfil=="0")
            return false;

        if(query.exec("select "+_permiso+" from PerfilesUsuarios where codigoPerfil ='"+valorPerfil+"'" )) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.value(0).toString()=="0"){
                        return false;
                    }else if(query.value(0).toString()=="1"){

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
    }else{return false;}
}

QString ModuloPerfiles::retornaCodigoPerfil(QString _idUsuario) const{
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

        if(query.exec("select codigoPerfil from Usuarios where idUsuario='"+_idUsuario+"'")) {

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
    }else{return "0";}

}
int ModuloPerfiles::ultimoRegistroDePerfil()const {
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

        if(query.exec("select codigoPerfil from PerfilesUsuarios order by codigoPerfil desc limit 1")) {

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

bool ModuloPerfiles::eliminarPerfil(QString _codigoPerfil) const {
    bool conexion=true;

    if(_codigoPerfil=="1")
        return false;

    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery query(Database::connect());

        if(query.exec("select codigoPerfil from PerfilesUsuarios where codigoPerfil='"+_codigoPerfil+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("delete from PerfilesUsuarios where codigoPerfil='"+_codigoPerfil+"'")){

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
int ModuloPerfiles::insertarPerfil(QString _codigoPerfil,QString _descripcionPerfil
                                   , QString _permiteUsarLiquidaciones
                                   , QString _permiteUsarFacturacion
                                   , QString _permiteUsarArticulos
                                   , QString _permiteUsarListaPrecios
                                   , QString _permiteUsarClientes
                                   , QString _permiteUsarMenuAvanzado

                                   , QString _permiteUsarDocumentos
                                   , QString _permiteUsarReportes
                                   , QString _permiteUsarCuentaCorriente
                                   , QString _permiteCrearLiquidaciones
                                   , QString _permiteBorrarLiquidaciones
                                   , QString _permiteCerrarLiquidaciones
                                   , QString _permiteAutorizarCierreLiquidaciones
                                   , QString _permiteCrearFacturas
                                   , QString _permiteBorrarFacturas
                                   , QString _permiteAnularFacturas
                                   , QString _permiteCrearClientes
                                   , QString _permiteBorrarClientes
                                   , QString _permiteCrearArticulos
                                   , QString _permiteBorrarArticulos
                                   , QString _permiteCrearListaDePrecios
                                   , QString _permiteBorrarListaDePrecios
                                   , QString _permiteAutorizarDescuentosArticulo
                                   , QString _permiteAutorizarDescuentosTotal
                                   , QString _permiteAutorizarAnulaciones
                                   , QString _permiteExportarAPDF
                                   , QString _permiteReimprimirFacturas
                                   , QString _permiteCambioRapidoDePrecios


                                   , QString AccedeAlMenuUsuarios
                                   , QString AccedeAlMenuPermisos
                                   , QString AccedeAlMenuMonedas
                                   , QString AccedeAlMenuRubros
                                   , QString AccedeAlMenuCuentasBancarias
                                   , QString AccedeAlMenuPagoDeFinacieras
                                   , QString AccedeAlMenuBancos
                                   , QString AccedeAlMenuLocalidades
                                   , QString AccedeAlMenuTiposDeDocumentos
                                   , QString AccedeAlMenuIvas
                                   , QString AccedeAlMenuConfiguraciones


                                   ){

    if(_codigoPerfil=="1")
        return -6;

    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el perfil
    // 1  perfil dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar el perfil
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El perfil no tiene los datos sufucientes para darse de alta.
    // -6 El perfil del administrador no se puede modificar, solo visualizar.

    if(_codigoPerfil.trimmed()=="" || _descripcionPerfil.trimmed()=="" ){
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

        if(query.exec("select codigoPerfil from PerfilesUsuarios where codigoPerfil='"+_codigoPerfil+"'")) {

            if(query.first()){

                if(query.value(0).toString()!=""){

                    if(query.exec("update PerfilesUsuarios set  descripcionPerfil='"+_descripcionPerfil+"',  permiteUsarLiquidaciones ='"+_permiteUsarLiquidaciones+"',  permiteUsarFacturacion ='"+_permiteUsarFacturacion+"',  permiteUsarArticulos ='"+_permiteUsarArticulos+"',  permiteUsarListaPrecios ='"+_permiteUsarListaPrecios+"',  permiteUsarClientes ='"+_permiteUsarClientes+"',  permiteUsarDocumentos ='"+_permiteUsarDocumentos+"',  permiteUsarReportes ='"+_permiteUsarReportes+"',  permiteUsarCuentaCorriente ='"+_permiteUsarCuentaCorriente+"',  permiteUsarMenuAvanzado ='"+_permiteUsarMenuAvanzado+"',  permiteExportarAPDF ='"+_permiteExportarAPDF+"',  permiteCrearLiquidaciones ='"+_permiteCrearLiquidaciones+"',  permiteBorrarLiquidaciones ='"+_permiteBorrarLiquidaciones+"',  permiteCerrarLiquidaciones ='"+_permiteCerrarLiquidaciones+"',  permiteAutorizarCierreLiquidaciones ='"+_permiteAutorizarCierreLiquidaciones+"',  permiteCrearFacturas ='"+_permiteCrearFacturas+"',  permiteBorrarFacturas ='"+_permiteBorrarFacturas+"',  permiteAnularFacturas ='"+_permiteAnularFacturas+"',  permiteCrearClientes ='"+_permiteCrearClientes+"',  permiteBorrarClientes ='"+_permiteBorrarClientes+"',  permiteCrearArticulos ='"+_permiteCrearArticulos+"',  permiteBorrarArticulos ='"+_permiteBorrarArticulos+"',  permiteCrearListaDePrecios ='"+_permiteCrearListaDePrecios+"',  permiteBorrarListaDePrecios ='"+_permiteBorrarListaDePrecios+"',  permiteAutorizarDescuentosArticulo ='"+_permiteAutorizarDescuentosArticulo+"',  permiteAutorizarDescuentosTotal ='"+_permiteAutorizarDescuentosTotal+"',  permiteAutorizarAnulaciones ='"+_permiteAutorizarAnulaciones+"',  permiteReimprimirFacturas ='"+_permiteReimprimirFacturas+"',  permiteCambioRapidoDePrecios ='"+_permiteCambioRapidoDePrecios+"' , permiteUsarMenuAvanzadoUsuarios ='"+AccedeAlMenuUsuarios+"'  , permiteUsarMenuAvanzadoPermisos ='"+AccedeAlMenuPermisos+"'  , permiteUsarMenuAvanzadoMonedas ='"+AccedeAlMenuMonedas+"', permiteUsarMenuAvanzadoRubros ='"+AccedeAlMenuRubros+"'  , permiteUsarMenuAvanzadoCuentasBancarias ='"+AccedeAlMenuCuentasBancarias+"'  , permiteUsarMenuAvanzadoPagoDeFinacieras ='"+AccedeAlMenuPagoDeFinacieras+"' , permiteUsarMenuAvanzadoBancos ='"+AccedeAlMenuBancos+"' , permiteUsarMenuAvanzadoLocalidades ='"+AccedeAlMenuLocalidades+"' , permiteUsarMenuAvanzadoTiposDeDocumentos ='"+AccedeAlMenuTiposDeDocumentos+"'  , permiteUsarMenuAvanzadoIvas ='"+AccedeAlMenuIvas+"' , permiteUsarMenuAvanzadoConfiguraciones ='"+AccedeAlMenuConfiguraciones+"'     where codigoPerfil='"+_codigoPerfil+"'")){

                        return 2;

                    }else{
                        return -2;
                    }
                }else{
                    return -4;
                }
            }else{
                if(query.exec("insert INTO PerfilesUsuarios (codigoPerfil,descripcionPerfil,permiteUsarLiquidaciones	,permiteUsarFacturacion,permiteUsarArticulos,permiteUsarListaPrecios,permiteUsarClientes,permiteUsarDocumentos,permiteUsarReportes,permiteUsarCuentaCorriente,permiteUsarMenuAvanzado	,permiteExportarAPDF,  permiteCrearLiquidaciones,permiteBorrarLiquidaciones,  permiteCerrarLiquidaciones,permiteAutorizarCierreLiquidaciones,permiteCrearFacturas,permiteBorrarFacturas,permiteAnularFacturas,permiteCrearClientes,permiteBorrarClientes,permiteCrearArticulos,permiteBorrarArticulos,permiteCrearListaDePrecios,permiteBorrarListaDePrecios,permiteAutorizarDescuentosArticulo,permiteAutorizarDescuentosTotal,permiteAutorizarAnulaciones,permiteReimprimirFacturas,permiteCambioRapidoDePrecios,permiteUsarMenuAvanzadoConfiguraciones, permiteUsarMenuAvanzadoIvas,permiteUsarMenuAvanzadoTiposDeDocumentos,permiteUsarMenuAvanzadoLocalidades,permiteUsarMenuAvanzadoBancos,permiteUsarMenuAvanzadoPagoDeFinacieras,permiteUsarMenuAvanzadoCuentasBancarias,permiteUsarMenuAvanzadoRubros,permiteUsarMenuAvanzadoMonedas,permiteUsarMenuAvanzadoPermisos,permiteUsarMenuAvanzadoUsuarios) values('"+_codigoPerfil+"','"+_descripcionPerfil+"','"+_permiteUsarLiquidaciones+"','"+_permiteUsarFacturacion+"','"+_permiteUsarArticulos+"','"+_permiteUsarListaPrecios+"','"+_permiteUsarClientes+"','"+_permiteUsarDocumentos+"','"+_permiteUsarReportes+"','"+_permiteUsarCuentaCorriente+"','"+_permiteUsarMenuAvanzado+"','"+_permiteExportarAPDF+"','"+_permiteCrearLiquidaciones+"','"+_permiteBorrarLiquidaciones+"','"+_permiteCerrarLiquidaciones+"','"+_permiteAutorizarCierreLiquidaciones+"','"+_permiteCrearFacturas+"','"+_permiteBorrarFacturas+"','"+_permiteAnularFacturas+"','"+_permiteCrearClientes+"','"+_permiteBorrarClientes+"','"+_permiteCrearArticulos+"','"+_permiteBorrarArticulos+"','"+_permiteCrearListaDePrecios+"','"+_permiteBorrarListaDePrecios+"','"+_permiteAutorizarDescuentosArticulo+"','"+_permiteAutorizarDescuentosTotal+"','"+_permiteAutorizarAnulaciones+"','"+_permiteReimprimirFacturas+"','"+_permiteCambioRapidoDePrecios+"' ,'"+AccedeAlMenuConfiguraciones+"','"+AccedeAlMenuIvas+"','"+AccedeAlMenuTiposDeDocumentos+"','"+AccedeAlMenuLocalidades+"','"+AccedeAlMenuBancos+"','"+AccedeAlMenuPagoDeFinacieras+"','"+AccedeAlMenuCuentasBancarias+"','"+AccedeAlMenuRubros+"','"+AccedeAlMenuMonedas+"','"+AccedeAlMenuPermisos+"','"+AccedeAlMenuUsuarios+"'  )")){
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
