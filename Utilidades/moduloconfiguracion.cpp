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

#include "moduloconfiguracion.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>



QString ModuloConfiguracion::m_CANTIDAD_DIGITOS_DECIMALES_MONTO;
QString ModuloConfiguracion::m_CANTIDAD_DIGITOS_DECIMALES_MONTO_IMPRESION;
QString ModuloConfiguracion::m_IMPRIME_DESCRIPCION_ARTICULO_ORIGINAL;
QString ModuloConfiguracion::m_IVA_DEFAULT_SISTEMA;
QString ModuloConfiguracion::m_MODO_AFECTACION_CAJA;
QString ModuloConfiguracion::m_MODO_ARTICULO;

QString ModuloConfiguracion::m_MODO_AUTORIZACION;
QString ModuloConfiguracion::m_MODO_CALCULOTOTAL;
QString ModuloConfiguracion::m_MODO_CLIENTE;
QString ModuloConfiguracion::m_MODO_IMPRESION_A4;
QString ModuloConfiguracion::m_MONEDA_DEFAULT;

QString ModuloConfiguracion::m_MULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADOS;
QString ModuloConfiguracion::m_MULTI_BD;
QString ModuloConfiguracion::m_MULTI_EMPRESA;
QString ModuloConfiguracion::m_SEPARADOR_MANTENIMIENTO_BATCH;
QString ModuloConfiguracion::m_TIPO_CIERRE_LIQUIDACION;
QString ModuloConfiguracion::m_VERSION_BD;
QString ModuloConfiguracion::m_MODO_AVISO_NUEVO_DOCUMENTO;
QString ModuloConfiguracion::m_MUESTRA_DESCRIPCION_ARTICULO_EXTENDIDA_FACTURACION;
QString ModuloConfiguracion::m_MODO_CFE;
QString ModuloConfiguracion::m_CODIGO_BARRAS_A_DEMANDA_EXTENDIDO;

QString ModuloConfiguracion::m_DISTANCIAENTREBOTONESMENU;

QString ModuloConfiguracion::m_UTILIZA_CONTROL_CLIENTE_CREDITO;

QString ModuloConfiguracion::m_IMPRESION_ENVIOS;
QString ModuloConfiguracion::m_NOMBRE_EMPRESA;








QString ModuloConfiguracion::m_CantidadDecimalesString;



ModuloConfiguracion::ModuloConfiguracion(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoConfiguracionRole] = "codigoConfiguracion";
    roles[ValorConfiguracionRole] = "valorConfiguracion";
    roles[DescripcionConfiguracionRole] = "descripcionConfiguracion";


    setRoleNames(roles);
}


Configuracion::Configuracion(const QString &codigoConfiguracion, const QString &valorConfiguracion ,const QString &descripcionConfiguracion)
    : m_codigoConfiguracion(codigoConfiguracion), m_valorConfiguracion(valorConfiguracion), m_descripcionConfiguracion(descripcionConfiguracion)
{
}

QString Configuracion::codigoConfiguracion() const
{
    return m_codigoConfiguracion;
}
QString Configuracion::valorConfiguracion() const
{
    return m_valorConfiguracion;
}
QString Configuracion::descripcionConfiguracion() const
{
    return m_descripcionConfiguracion;
}


void ModuloConfiguracion::agregarConfiguracion(const Configuracion &configuracion)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Configuracion << configuracion;
    endInsertRows();
}

void ModuloConfiguracion::limpiarListaConfiguracion(){
    m_Configuracion.clear();
}

void ModuloConfiguracion::buscarConfiguracion(QString campo, QString datoABuscar){

    bool conexion=true;

    Database::chequeaStatusAccesoMysql();

    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from Configuracion where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloConfiguracion::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloConfiguracion::agregarConfiguracion(Configuracion(q.value(rec.indexOf("codigoConfiguracion")).toString()

                                                                        , q.value(rec.indexOf("valorConfiguracion")).toString()

                                                                        , q.value(rec.indexOf("descripcionConfiguracion")).toString()

                                                                        ));
            }
        }
    }
}

void ModuloConfiguracion::cargarConfiguracion(){

    bool conexion=true;

    Database::chequeaStatusAccesoMysql();

    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from Configuracion;");
        QSqlRecord rec = q.record();

        ModuloConfiguracion::reset();
        if(q.record().count()>0){

            while (q.next()){

                if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="CANTIDAD_DIGITOS_DECIMALES_MONTO"){
                    ModuloConfiguracion::setCANTIDAD_DIGITOS_DECIMALES_MONTO(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="CANTIDAD_DIGITOS_DECIMALES_MONTO_IMPRESION"){
                    ModuloConfiguracion::setCANTIDAD_DIGITOS_DECIMALES_MONTO_IMPRESION(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="IMPRIME_DESCRIPCION_ARTICULO_ORIGINAL"){
                    ModuloConfiguracion::setIMPRIME_DESCRIPCION_ARTICULO_ORIGINAL(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="IVA_DEFAULT_SISTEMA"){
                    ModuloConfiguracion::setIVA_DEFAULT_SISTEMA(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="MODO_AFECTACION_CAJA"){
                    ModuloConfiguracion::setMODO_AFECTACION_CAJA(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="MODO_ARTICULO"){
                    ModuloConfiguracion::setMODO_ARTICULO(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="MODO_AUTORIZACION"){
                    ModuloConfiguracion::setMODO_AUTORIZACION(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="MODO_CALCULOTOTAL"){
                    ModuloConfiguracion::setMODO_CALCULOTOTAL(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="MODO_CLIENTE"){
                    ModuloConfiguracion::setMODO_CLIENTE(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="MODO_IMPRESION_A4"){
                    ModuloConfiguracion::setMODO_IMPRESION_A4(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="MONEDA_DEFAULT"){
                    ModuloConfiguracion::setMONEDA_DEFAULT(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="MULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADOS"){
                    ModuloConfiguracion::setMULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADOS(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="MULTI_BD"){
                    ModuloConfiguracion::setMULTI_BD(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="MULTI_EMPRESA"){
                    ModuloConfiguracion::setMULTI_EMPRESA(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="SEPARADOR_MANTENIMIENTO_BATCH"){
                    ModuloConfiguracion::setSEPARADOR_MANTENIMIENTO_BATCH(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="TIPO_CIERRE_LIQUIDACION"){
                    ModuloConfiguracion::setTIPO_CIERRE_LIQUIDACION(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="VERSION_BD"){
                    ModuloConfiguracion::setVERSION_BD(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="MODO_AVISO_NUEVO_DOCUMENTO"){
                    ModuloConfiguracion::setMODO_AVISO_NUEVO_DOCUMENTO(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="MUESTRA_DESCRIPCION_ARTICULO_EXTENDIDA_FACTURACION"){
                    ModuloConfiguracion::setMUESTRA_DESCRIPCION_ARTICULO_EXTENDIDA_FACTURACION(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="MODO_CFE"){
                    ModuloConfiguracion::setMODO_CFE(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="CODIGO_BARRAS_A_DEMANDA_EXTENDIDO"){
                    ModuloConfiguracion::setCODIGO_BARRAS_A_DEMANDA_EXTENDIDO(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="DISTANCIAENTREBOTONESMENU"){
                    ModuloConfiguracion::setDISTANCIAENTREBOTONESMENU(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="UTILIZA_CONTROL_CLIENTE_CREDITO"){
                    ModuloConfiguracion::setUTILIZA_CONTROL_CLIENTE_CREDITO(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="IMPRESION_ENVIOS"){
                    ModuloConfiguracion::setIMPRESION_ENVIOS(q.value(rec.indexOf("valorConfiguracion")).toString());
                }
                else if(q.value(rec.indexOf("codigoConfiguracion")).toString()=="NOMBRE_EMPRESA"){
                    ModuloConfiguracion::setNOMBRE_EMPRESA(q.value(rec.indexOf("valorConfiguracion")).toString());
                }

            }
            if(ModuloConfiguracion::getCANTIDAD_DIGITOS_DECIMALES_MONTO()=="0"){
                ModuloConfiguracion::setCantidadDecimalesString("");
            }else if(ModuloConfiguracion::getCANTIDAD_DIGITOS_DECIMALES_MONTO()=="1"){
                ModuloConfiguracion::setCantidadDecimalesString(".0");
            }else if(ModuloConfiguracion::getCANTIDAD_DIGITOS_DECIMALES_MONTO()=="2"){
                ModuloConfiguracion::setCantidadDecimalesString(".00");
            }else if(ModuloConfiguracion::getCANTIDAD_DIGITOS_DECIMALES_MONTO()=="3"){
                ModuloConfiguracion::setCantidadDecimalesString(".000");
            }else if(ModuloConfiguracion::getCANTIDAD_DIGITOS_DECIMALES_MONTO()=="4"){
                ModuloConfiguracion::setCantidadDecimalesString(".0000");
            }else if(ModuloConfiguracion::getCANTIDAD_DIGITOS_DECIMALES_MONTO()=="5"){
                ModuloConfiguracion::setCantidadDecimalesString(".00000");
            }else if(ModuloConfiguracion::getCANTIDAD_DIGITOS_DECIMALES_MONTO()=="6"){
                ModuloConfiguracion::setCantidadDecimalesString(".000000");
            }else{
                ModuloConfiguracion::setCantidadDecimalesString(".00");
            }

        }
    }
}


int ModuloConfiguracion::rowCount(const QModelIndex & parent) const {
    return m_Configuracion.count();
}

QVariant ModuloConfiguracion::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Configuracion.count()){
        return QVariant();

    }

    const Configuracion &configuracion = m_Configuracion[index.row()];

    if (role == CodigoConfiguracionRole){
        return configuracion.codigoConfiguracion();

    }
    else if (role == ValorConfiguracionRole){
        return configuracion.valorConfiguracion();

    }
    else if (role == DescripcionConfiguracionRole){
        return configuracion.descripcionConfiguracion();

    }
    return QVariant();
}


QString ModuloConfiguracion::retornaValorConfiguracion(QString _codigoConfiguracion) const{


    if(_codigoConfiguracion=="CANTIDAD_DIGITOS_DECIMALES_MONTO"){

        return ModuloConfiguracion::getCANTIDAD_DIGITOS_DECIMALES_MONTO();

    }
    else if(_codigoConfiguracion=="CANTIDAD_DIGITOS_DECIMALES_MONTO_IMPRESION"){
        return ModuloConfiguracion::getCANTIDAD_DIGITOS_DECIMALES_MONTO_IMPRESION();
    }
    else if(_codigoConfiguracion=="IMPRIME_DESCRIPCION_ARTICULO_ORIGINAL"){
        return ModuloConfiguracion::getIMPRIME_DESCRIPCION_ARTICULO_ORIGINAL();
    }
    else if(_codigoConfiguracion=="IVA_DEFAULT_SISTEMA"){
        return ModuloConfiguracion::getIVA_DEFAULT_SISTEMA();
    }
    else if(_codigoConfiguracion=="MODO_AFECTACION_CAJA"){
        return ModuloConfiguracion::getMODO_AFECTACION_CAJA();
    }
    else if(_codigoConfiguracion=="MODO_ARTICULO"){
        return ModuloConfiguracion::getMODO_ARTICULO();
    }
    else if(_codigoConfiguracion=="MODO_AUTORIZACION"){
        return ModuloConfiguracion::getMODO_AUTORIZACION();
    }
    else if(_codigoConfiguracion=="MODO_CALCULOTOTAL"){
        return ModuloConfiguracion::getMODO_CALCULOTOTAL();
    }
    else if(_codigoConfiguracion=="MODO_CLIENTE"){
        return ModuloConfiguracion::getMODO_CLIENTE();
    }
    else if(_codigoConfiguracion=="MODO_IMPRESION_A4"){
        return ModuloConfiguracion::getMODO_IMPRESION_A4();
    }
    else if(_codigoConfiguracion=="MONEDA_DEFAULT"){
        return ModuloConfiguracion::getMONEDA_DEFAULT();
    }
    else if(_codigoConfiguracion=="MULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADOS"){
        return ModuloConfiguracion::getMULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADOS();
    }
    else if(_codigoConfiguracion=="MULTI_BD"){
        return ModuloConfiguracion::getMULTI_BD();
    }
    else if(_codigoConfiguracion=="MULTI_EMPRESA"){
        return ModuloConfiguracion::getMULTI_EMPRESA();
    }
    else if(_codigoConfiguracion=="SEPARADOR_MANTENIMIENTO_BATCH"){
        return ModuloConfiguracion::getSEPARADOR_MANTENIMIENTO_BATCH();
    }
    else if(_codigoConfiguracion=="TIPO_CIERRE_LIQUIDACION"){
        return ModuloConfiguracion::getTIPO_CIERRE_LIQUIDACION();
    }
    else if(_codigoConfiguracion=="VERSION_BD"){
        return ModuloConfiguracion::getVERSION_BD();
    }
    else if(_codigoConfiguracion=="MODO_AVISO_NUEVO_DOCUMENTO"){
        return ModuloConfiguracion::getMODO_AVISO_NUEVO_DOCUMENTO();
    }
    else if(_codigoConfiguracion=="MUESTRA_DESCRIPCION_ARTICULO_EXTENDIDA_FACTURACION"){
        return ModuloConfiguracion::getMUESTRA_DESCRIPCION_ARTICULO_EXTENDIDA_FACTURACION();
    }
    else if(_codigoConfiguracion=="MODO_CFE"){
        return ModuloConfiguracion::getMODO_CFE();
    }
    else if(_codigoConfiguracion=="CODIGO_BARRAS_A_DEMANDA_EXTENDIDO"){
        return ModuloConfiguracion::getCODIGO_BARRAS_A_DEMANDA_EXTENDIDO();
    }
    else if(_codigoConfiguracion=="DISTANCIAENTREBOTONESMENU"){
        return ModuloConfiguracion::getDISTANCIAENTREBOTONESMENU();
    }
    else if(_codigoConfiguracion=="UTILIZA_CONTROL_CLIENTE_CREDITO"){
        return ModuloConfiguracion::getUTILIZA_CONTROL_CLIENTE_CREDITO();
    }
    else if(_codigoConfiguracion=="IMPRESION_ENVIOS"){
        return ModuloConfiguracion::getIMPRESION_ENVIOS();
    }
    else if(_codigoConfiguracion=="NOMBRE_EMPRESA"){
        return ModuloConfiguracion::getNOMBRE_EMPRESA();
    }

}
QString ModuloConfiguracion::retornaCantidadDecimalesString() const{

    return ModuloConfiguracion::getCantidadDecimalesString();
}
bool ModuloConfiguracion::retornaModoAvisoDocumentosNuevoVisible() const{

    if(ModuloConfiguracion::getMODO_AVISO_NUEVO_DOCUMENTO()=="0"){
        return false;
    }
    else{
        return true;
    }
}



bool ModuloConfiguracion::retornaValorConfiguracionBooleano(QString _codigoConfiguracion) const {
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

        if(query.exec("select valorConfiguracion from Configuracion where codigoConfiguracion='"+_codigoConfiguracion+"';")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    qDebug()<< query.value(0).toString();
                    return (query.value(0).toString() == "1") ? true : false;

                }else{return false;}
            }
            else{
                return false;
            }
        }else{return false;}
    }else{
        return false;
    }
}
QString ModuloConfiguracion::retornaValorConfiguracionValorString(QString _codigoConfiguracion) const {
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

        if(query.exec("select valorConfiguracion from Configuracion where codigoConfiguracion='"+_codigoConfiguracion+"';")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    return query.value(0).toString();
                }else{return "0";}
            }
            else{
                return "0";
            }
        }else{return "0";}
    }else{
        return "0";
    }
}
