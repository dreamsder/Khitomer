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

#include "moduloclientes.h"
#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include <funciones.h>
#include <Utilidades/moduloconfiguracion.h>


Funciones func_Fecha;

ModuloConfiguracion func_configuracionClientes;


ModuloClientes::ModuloClientes(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoClienteRole] = "codigoCliente";
    roles[TipoClienteRole] = "tipoCliente";
    roles[RutRole] = "rut";
    roles[NombreClienteRole] = "nombreCliente";
    roles[RazonSocialRole] = "razonSocial";
    roles[DireccionRole] = "direccion";
    roles[EsquinaRole] = "esquina";
    roles[NumeroPuertaRole] = "numeroPuerta";
    roles[TelefonoRole] = "telefono";
    roles[Telefono2Role] = "telefono2";
    roles[DocumentoRole] = "documento";
    roles[CodigoPostalRole] = "codigoPostal";
    roles[EmailRole] = "email";
    roles[SitioWebRole] = "sitioWeb";
    roles[UsuarioAltaRole] = "usuarioAlta";
    roles[ObservacionesRole] = "observaciones";
    roles[TipoClasificacionRole] = "tipoClasificacion";
    roles[CodigoTipoClienteRole] = "codigoTipoCliente";
    roles[DescripcionTipoClienteRole] = "descripcionTipoCliente";
    roles[CodigoTipoClasificacionRole] = "codigoTipoClasificacion";
    roles[DescripcionTipoClasificacionRole] = "descripcionTipoClasificacion";
    roles[ContactoRole] = "contacto";
    roles[HorarioRole] = "horario";

    roles[CodigoPaisRole] = "codigoPais";
    roles[CodigoDepartamentoRole] = "codigoDepartamento";
    roles[CodigoLocalidadRole] = "codigoLocalidad";

    roles[codigoTipoDocumentoClienteRole] = "codigoTipoDocumentoCliente";


    roles[codigoTipoProcedenciaClienteRole] = "codigoTipoProcedenciaCliente";

    roles[fechaNacimientoRole] = "fechaNacimiento";
    roles[permiteFacturaCreditoRole] = "permiteFacturaCredito";

    roles[codigoMonedaDefaultRole] = "codigoMonedaDefault";
    roles[codigoFormasDePagoDefaultRole] = "codigoFormasDePagoDefault";

    roles[codigoTipoDocumentoDefaultRole] = "codigoTipoDocumentoDefault";
    roles[porcentajeDescuentoRole] = "porcentajeDescuento";






    setRoleNames(roles);

}


Cliente::Cliente(const QString &codigoCliente, const int &tipoCliente, const QString &rut, const QString &nombreCliente,const QString &razonSocial,const QString &direccion,const QString &esquina,const QString &numeroPuerta,const QString &telefono,const QString &telefono2,const QString &documento,const QString &codigoPostal, const QString &email,const QString &sitioWeb,const QString &usuarioAlta,const QString &observaciones,const int &tipoClasificacion,const int &codigoTipoCliente,const QString &descripcionTipoCliente,const int &codigoTipoClasificacion,const QString &descripcionTipoClasificacion,const QString &contacto,const QString &horario,const int &codigoPais,const int &codigoDepartamento,const int &codigoLocalidad,const int &codigoTipoDocumentoCliente,const int &codigoTipoProcedenciaCliente, const QString &fechaNacimiento, const QString &permiteFacturaCredito
,const int &codigoMonedaDefault,const int &codigoFormasDePagoDefault, const int &codigoTipoDocumentoDefault, const QString &porcentajeDescuento)

    : m_codigoCliente(codigoCliente), m_tipoCliente(tipoCliente), m_rut(rut), m_nombreCliente(nombreCliente), m_razonSocial(razonSocial), m_direccion(direccion),  m_esquina(esquina), m_numeroPuerta(numeroPuerta), m_telefono(telefono), m_telefono2(telefono2), m_documento(documento), m_codigoPostal(codigoPostal), m_email(email),

      m_sitioWeb(sitioWeb), m_usuarioAlta(usuarioAlta), m_observaciones(observaciones),m_tipoClasificacion(tipoClasificacion), m_codigoTipoCliente(codigoTipoCliente),m_descripcionTipoCliente(descripcionTipoCliente), m_codigoTipoClasificacion(codigoTipoClasificacion),m_descripcionTipoClasificacion(descripcionTipoClasificacion),m_contacto(contacto),m_horario(horario),
      m_codigoPais(codigoPais), m_codigoDepartamento(codigoDepartamento),m_codigoLocalidad(codigoLocalidad),
      m_codigoTipoDocumentoCliente(codigoTipoDocumentoCliente),
      m_codigoTipoProcedenciaCliente(codigoTipoProcedenciaCliente),
      m_fechaNacimiento(fechaNacimiento),
      m_permiteFacturaCredito(permiteFacturaCredito),
      m_codigoMonedaDefault(codigoMonedaDefault),
      m_codigoFormasDePagoDefault(codigoFormasDePagoDefault),
      m_codigoTipoDocumentoDefault(codigoTipoDocumentoDefault),
      m_porcentajeDescuento(porcentajeDescuento)


{
}



QString Cliente::codigoCliente() const
{
    return m_codigoCliente;
}
int Cliente::tipoCliente() const
{
    return m_tipoCliente;
}
QString Cliente::rut() const
{
    return m_rut;
}
QString Cliente::nombreCliente() const
{
    return m_nombreCliente;
}
QString Cliente::razonSocial() const
{
    return m_razonSocial;
}
QString Cliente::direccion() const
{
    return m_direccion;
}
QString Cliente::esquina() const
{
    return m_esquina;
}
QString Cliente::numeroPuerta() const
{
    return m_numeroPuerta;
}
QString Cliente::telefono() const
{
    return m_telefono;
}
QString Cliente::telefono2() const
{
    return m_telefono2;
}
QString Cliente::documento() const
{
    return m_documento;
}
QString Cliente::codigoPostal() const
{
    return m_codigoPostal;
}
QString Cliente::email() const
{
    return m_email;
}
QString Cliente::sitioWeb() const
{
    return m_sitioWeb;
}
QString Cliente::usuarioAlta() const
{
    return m_usuarioAlta;
}
QString Cliente::observaciones() const
{
    return m_observaciones;
}
int Cliente::tipoClasificacion() const
{
    return m_tipoClasificacion;
}
int Cliente::codigoTipoCliente() const
{
    return m_codigoTipoCliente;
}
QString Cliente::descripcionTipoCliente() const
{
    return m_descripcionTipoCliente;
}
int Cliente::codigoTipoClasificacion() const
{
    return m_codigoTipoClasificacion;
}
QString Cliente::descripcionTipoClasificacion() const
{
    return m_descripcionTipoClasificacion;
}
QString Cliente::contacto() const
{
    return m_contacto;
}
QString Cliente::horario() const
{
    return m_horario;
}
int Cliente::codigoPais() const
{
    return m_codigoPais;
}
int Cliente::codigoDepartamento() const
{
    return m_codigoDepartamento;
}
int Cliente::codigoLocalidad() const
{
    return m_codigoLocalidad;
}
int Cliente::codigoTipoDocumentoCliente() const
{
    return m_codigoTipoDocumentoCliente;
}
int Cliente::codigoTipoProcedenciaCliente() const
{
    return m_codigoTipoProcedenciaCliente;
}
QString Cliente::fechaNacimiento() const
{
    return m_fechaNacimiento;
}
QString Cliente::permiteFacturaCredito() const
{
    return m_permiteFacturaCredito;
}
int Cliente::codigoMonedaDefault() const
{
    return m_codigoMonedaDefault;
}
int Cliente::codigoFormasDePagoDefault() const
{
    return m_codigoFormasDePagoDefault;
}
int Cliente::codigoTipoDocumentoDefault() const
{
    return m_codigoTipoDocumentoDefault;
}
QString Cliente::porcentajeDescuento() const
{
    return m_porcentajeDescuento;
}




void ModuloClientes::addCliente(const Cliente &cliente)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Clientes << cliente;
    endInsertRows();


}

void ModuloClientes::clearClientes(){
    m_Clientes.clear();
}

void ModuloClientes::buscarCliente(QString campo, QString datoABuscar){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){
        QSqlQuery q = Database::consultaSql("select * from Clientes  join TipoCliente on Clientes.tipoCliente=TipoCliente.codigoTipoCliente join TipoClasificacion on Clientes.tipoClasificacion=TipoClasificacion.codigoTipoClasificacion where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloClientes::reset();
        if(q.record().count()>0){          

            while (q.next()){
                ModuloClientes::addCliente(Cliente(q.value(rec.indexOf("codigoCliente")).toString(), q.value(rec.indexOf("tipoCliente")).toInt(), q.value(rec.indexOf("rut")).toString(),  q.value(rec.indexOf("nombreCliente")).toString(),     q.value(rec.indexOf("razonSocial")).toString(),  q.value(rec.indexOf("direccion")).toString(),  q.value(rec.indexOf("esquina")).toString(),  q.value(rec.indexOf("numeroPuerta")).toString(), q.value(rec.indexOf("telefono")).toString(),  q.value(rec.indexOf("telefono2")).toString(),  q.value(rec.indexOf("documento")).toString(), q.value(rec.indexOf("codigoPostal")).toString(), q.value(rec.indexOf("email")).toString(), q.value(rec.indexOf("sitioWeb")).toString(), q.value(rec.indexOf("usuarioAlta")).toString() ,q.value(rec.indexOf("observaciones")).toString() ,q.value(rec.indexOf("tipoClasificacion")).toInt()
                                                   ,q.value(rec.indexOf("codigoTipoCliente")).toInt(),q.value(rec.indexOf("descripcionTipoCliente")).toString()
                                                   ,q.value(rec.indexOf("codigoTipoClasificacion")).toInt(),q.value(rec.indexOf("descripcionTipoClasificacion")).toString()
                                                   ,q.value(rec.indexOf("contacto")).toString(),q.value(rec.indexOf("horario")).toString()
                                                   ,q.value(rec.indexOf("codigoPais")).toInt(),q.value(rec.indexOf("codigoDepartamento")).toInt()
                                                   ,q.value(rec.indexOf("codigoLocalidad")).toInt()
                                                   ,q.value(rec.indexOf("codigoTipoDocumentoCliente")).toInt()
                                                   ,q.value(rec.indexOf("codigoTipoProcedenciaCliente")).toInt()
                                                   ,q.value(rec.indexOf("fechaNacimiento")).toString()
                                                   ,q.value(rec.indexOf("permiteFacturaCredito")).toString()
                                                   ,q.value(rec.indexOf("codigoMonedaDefault")).toInt()
                                                   ,q.value(rec.indexOf("codigoFormasDePagoDefault")).toInt()
                                                   ,q.value(rec.indexOf("codigoTipoDocumentoDefault")).toInt()
                                                   ,q.value(rec.indexOf("porcentajeDescuento")).toString()



                                                   ));
            }
        }
    }
}

int ModuloClientes::rowCount(const QModelIndex & parent) const {
    return m_Clientes.count();
}

QVariant ModuloClientes::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Clientes.count()){
        return QVariant();

    }

    const Cliente &cliente = m_Clientes[index.row()];

    if (role == CodigoClienteRole){
        return cliente.codigoCliente();
    }
    else if (role == TipoClienteRole){
        return cliente.tipoCliente();

    }
    else if (role == RutRole){
        return cliente.rut();

    }
    else if (role == NombreClienteRole){
        return cliente.nombreCliente();

    }
    else if (role == RazonSocialRole){
        return cliente.razonSocial();

    }
    else if (role == DireccionRole){
        return cliente.direccion();

    }
    else if (role == EsquinaRole){
        return cliente.esquina();

    }
    else if (role == NumeroPuertaRole){
        return cliente.numeroPuerta();

    }
    else if (role == TelefonoRole){
        return cliente.telefono();

    }
    else if (role == Telefono2Role){
        return cliente.telefono2();

    }
    else if (role == DocumentoRole){
        return cliente.documento();

    }
    else if (role == CodigoPostalRole){
        return cliente.codigoPostal();

    }
    else if (role == EmailRole){
        return cliente.email();

    }
    else if (role == SitioWebRole){
        return cliente.sitioWeb();

    }
    else if (role == UsuarioAltaRole){
        return cliente.usuarioAlta();

    }
    else if (role == ObservacionesRole){
        return cliente.observaciones();

    }else if (role == TipoClasificacionRole){
        return cliente.tipoClasificacion();

    }else if (role == CodigoTipoClienteRole){
        return cliente.codigoTipoCliente();

    }else if (role == DescripcionTipoClienteRole){
        return cliente.descripcionTipoCliente();

    }else if (role == CodigoTipoClasificacionRole){
        return cliente.codigoTipoClasificacion();

    }else if (role == DescripcionTipoClasificacionRole){
        return cliente.descripcionTipoClasificacion();

    }else if (role == ContactoRole){
        return cliente.contacto();

    }else if (role == HorarioRole){
        return cliente.horario();
    }
    else if (role == CodigoPaisRole){ return cliente.codigoPais(); }
    else if (role == CodigoDepartamentoRole){ return cliente.codigoDepartamento(); }
    else if (role == CodigoLocalidadRole){ return cliente.codigoLocalidad(); }

    else if (role == codigoTipoDocumentoClienteRole){ return cliente.codigoTipoDocumentoCliente(); }

    else if (role == codigoTipoProcedenciaClienteRole){ return cliente.codigoTipoProcedenciaCliente(); }

    else if (role == fechaNacimientoRole){ return cliente.fechaNacimiento(); }

    else if (role == permiteFacturaCreditoRole){ return cliente.permiteFacturaCredito(); }

    else if (role == codigoMonedaDefaultRole){ return cliente.codigoMonedaDefault(); }
    else if (role == codigoFormasDePagoDefaultRole){ return cliente.codigoFormasDePagoDefault(); }

    else if (role == codigoTipoDocumentoDefaultRole){ return cliente.codigoTipoDocumentoDefault(); }

    else if (role == porcentajeDescuentoRole){ return cliente.porcentajeDescuento(); }

    return QVariant();
}

qlonglong ModuloClientes::ultimoRegistroDeClienteEnBase(QString _tipoCliente)const {

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

        if(query.exec("select CONVERT(codigoCliente,UNSIGNED INTEGER) from Clientes where tipoCliente='"+_tipoCliente+"' order by cast(codigoCliente as unsigned) desc limit 1")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toULongLong()+1;

                }else{
                    return 1;
                }
            }else {return 1;}
        }else{
            return 1;
        }
    }
}

qlonglong ModuloClientes::primerRegistroDeClienteEnBase() const {

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery q = Database::consultaSql("select codigoCliente from Clientes order by cast(codigoCliente as unsigned) asc limit 1");
        QSqlRecord rec = q.record();

        if(q.record().count()>0){
            return q.value(rec.indexOf("codigoCliente")).toLongLong();
        }else{
            return -1;
        }
    }
}

QString ModuloClientes::insertarCliente(QString _codigoCliente,QString _tipoCliente, QString _nombreCliente, QString _razonSocial, QString _rut, QString _tipoClasificacion,QString _direccion,QString _esquina, QString _numeroPuerta, QString _telefono, QString _telefono2, QString _codigoPostal, QString _email, QString _sitioWeb, QString _contacto,QString _observaciones,QString _usuarioAlta, QString _horario, QString _codigoPais, QString _codigoDepartamento, QString _codigoLocalidad, QString _codigoTipoDocumentoCliente, QString  _codigoTipoProcedenciaCliente, QString _fechaNacimiento,QString _permiteFacturaCredito,QString _codigoMonedaDefault, QString _codigoFormasDePagoDefault, QString _codigoTipoDocumentoDefault,QString _porcentajeDescuento) const {



    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el cliente
    // 1  cliente dado de alta ok
    // -7 Actualizacion correcta
    // -3  no se pudo insertar el cliente
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El cliente no tiene los datos sufucientes para darse de alta.


    if(_nombreCliente.trimmed()=="" || _tipoClasificacion.trimmed()==""){
        return "-5";
    }

    if(_tipoCliente.trimmed()=="2"){

        if(_direccion.trimmed()=="" || _telefono.trimmed()=="" || _rut.trimmed()=="" || _razonSocial.trimmed()==""){
            return "-5";
        }
    }


    if(_codigoCliente.trimmed()==""){

        if(func_configuracionClientes.retornaValorConfiguracion("MODO_CLIENTE")=="0"){
            return "-5";
        }else{


          _codigoCliente=QString::number(ultimoRegistroDeClienteEnBase(_tipoCliente));


        }

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


        if(query.exec("select codigoCliente from Clientes where codigoCliente='"+_codigoCliente+"' and tipoCliente='"+_tipoCliente+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("update Clientes set nombreCliente='"+_nombreCliente+"', razonSocial='"+_razonSocial+"',rut='"+_rut+"',tipoClasificacion='"+_tipoClasificacion+"', direccion='"+_direccion+"',esquina='"+_esquina+"', numeroPuerta='"+_numeroPuerta+"',telefono='"+_telefono+"',telefono2='"+_telefono2+"',codigoPostal='"+_codigoPostal+"',email='"+_email+"',sitioWeb='"+_sitioWeb+"',contacto='"+_contacto+"',observaciones='"+_observaciones+"',usuarioAlta='"+_usuarioAlta+"',horario='"+_horario+"',codigoPais='"+_codigoPais+"',codigoDepartamento='"+_codigoDepartamento+"',codigoLocalidad='"+_codigoLocalidad+"',sincronizadoWeb='0',codigoTipoDocumentoCliente='"+_codigoTipoDocumentoCliente+"',codigoTipoProcedenciaCliente='"+_codigoTipoProcedenciaCliente+"',fechaNacimiento='"+_fechaNacimiento+"',permiteFacturaCredito='"+_permiteFacturaCredito+"',codigoMonedaDefault='"+_codigoMonedaDefault+"',codigoFormasDePagoDefault='"+_codigoFormasDePagoDefault+"',codigoTipoDocumentoDefault='"+_codigoTipoDocumentoDefault+"',porcentajeDescuento='"+_porcentajeDescuento+"'     where codigoCliente='"+_codigoCliente+"' and tipoCliente='"+_tipoCliente+"'")){

                        return "-7";
                    }else{
                        return "-2";
                    }

                }
            }else{
                if(query.exec("insert INTO Clientes (codigoCliente,tipoCliente,nombreCliente,razonSocial,rut,tipoClasificacion,direccion,esquina,numeroPuerta,telefono,telefono2,codigoPostal,email,sitioWeb,contacto,observaciones,usuarioAlta,horario,fechaAlta,codigoPais,codigoDepartamento,codigoLocalidad,sincronizadoWeb,codigoTipoDocumentoCliente,codigoTipoProcedenciaCliente,fechaNacimiento,permiteFacturaCredito,codigoMonedaDefault,codigoFormasDePagoDefault,codigoTipoDocumentoDefault,porcentajeDescuento ) values('"+_codigoCliente+"',"+_tipoCliente+",'"+_nombreCliente+"','"+_razonSocial+"','"+_rut+"','"+_tipoClasificacion+"','"+ _direccion +"','"+ _esquina +"','" + _numeroPuerta+"','"+_telefono+"','"+_telefono2+"','"+_codigoPostal+"','"+_email+"','"+_sitioWeb+"','"+_contacto+"','"+_observaciones+"','" +_usuarioAlta+"','"+_horario+"','"+func_Fecha.fechaHoraDeHoy()+"','"+_codigoPais+"','"+_codigoDepartamento+"','"+_codigoLocalidad+"','0','"+_codigoTipoDocumentoCliente+"','"+_codigoTipoProcedenciaCliente+"','"+_fechaNacimiento+"','"+_permiteFacturaCredito+"','"+_codigoMonedaDefault+"','"+_codigoFormasDePagoDefault+"','"+_codigoTipoDocumentoDefault+"','"+_porcentajeDescuento+"' )")){
                    return _codigoCliente;
                }else{
                    return "-3";
                }
            }
        }else{
            return "-4";
        }
    }else{
        return "-1";
    }
}

bool ModuloClientes::eliminarCliente(QString _codigoCliente,QString _tipoCliente) const {

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


        if(query.exec("select codigoCliente from Clientes where codigoCliente='"+_codigoCliente+"' and tipoCliente='"+_tipoCliente+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("delete from Clientes where codigoCliente='"+_codigoCliente+"' and tipoCliente='"+_tipoCliente+"'")){
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
    }else{
        return false;
    }
}

QString ModuloClientes::retornaDescripcionDeCliente(QString _codigoCliente,QString _tipoCliente) const {
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

        if(query.exec("select concat(C.razonSocial,'-',(case when C.rut is null then '' else C.rut end), '-', left(trim(C.observaciones),100)) from Clientes C  where C.codigoCliente='"+_codigoCliente+"' and C.tipoCliente='"+_tipoCliente+"'")) {

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

bool ModuloClientes::retornaSiEsClienteWeb(QString _codigoCliente,QString _tipoCliente) const {
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

        if(query.exec("select C.esClienteWeb from Clientes C  where C.codigoCliente='"+_codigoCliente+"' and C.tipoCliente='"+_tipoCliente+"'")) {

            if(query.first()){
                if(query.value(0).toString()=="1"){
                    return true;
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
bool ModuloClientes::retornaSiPermiteFacturaCredito(QString _codigoCliente,QString _tipoCliente) const {
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

        if(query.exec("select C.permiteFacturaCredito from Clientes C  where C.codigoCliente='"+_codigoCliente+"' and C.tipoCliente='"+_tipoCliente+"'")) {

            if(query.first()){
                if(query.value(0).toString()=="1"){
                    return true;
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

QString ModuloClientes::retornaDatoGenericoCliente(QString _codigoCliente,QString _tipoCliente, QString _campo) const {
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

        if(query.exec("select  "+_campo+"  from Clientes C  where C.codigoCliente='"+_codigoCliente+"' and C.tipoCliente='"+_tipoCliente+"'")) {

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
}
