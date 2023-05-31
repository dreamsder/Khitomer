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

#ifndef MODULOCONFIGURACION_H
#define MODULOCONFIGURACION_H

#include <QAbstractListModel>


class Configuracion
{
public:
    Q_INVOKABLE Configuracion(const QString &codigoConfiguracion, const QString &valorConfiguracion,const QString &descripcionConfiguracion);

    QString codigoConfiguracion() const;
    QString valorConfiguracion() const;
    QString descripcionConfiguracion() const;


private:
    QString m_codigoConfiguracion;
    QString m_valorConfiguracion;
    QString m_descripcionConfiguracion;

};

class ModuloConfiguracion : public QAbstractListModel
{
    Q_OBJECT
public:
    enum IvasRoles {
        CodigoConfiguracionRole = Qt::UserRole + 1,
        ValorConfiguracionRole,
        DescripcionConfiguracionRole
    };

    ModuloConfiguracion(QObject *parent = 0);

    Q_INVOKABLE void agregarConfiguracion(const Configuracion &Configuracion);

    Q_INVOKABLE void limpiarListaConfiguracion();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarConfiguracion(QString , QString);

    Q_INVOKABLE void cargarConfiguracion();

    Q_INVOKABLE QString retornaValorConfiguracion(QString ) const;
    Q_INVOKABLE bool retornaValorConfiguracionBooleano(QString _codigoConfiguracion) const;


    Q_INVOKABLE QString retornaCantidadDecimalesString() const;

    Q_INVOKABLE bool retornaModoAvisoDocumentosNuevoVisible() const;



    static QString getCANTIDAD_DIGITOS_DECIMALES_MONTO(){
        return m_CANTIDAD_DIGITOS_DECIMALES_MONTO;
    }
    static QString getCANTIDAD_DIGITOS_DECIMALES_MONTO_IMPRESION(){
        return m_CANTIDAD_DIGITOS_DECIMALES_MONTO_IMPRESION;
    }
    static QString getIMPRIME_DESCRIPCION_ARTICULO_ORIGINAL(){
        return m_IMPRIME_DESCRIPCION_ARTICULO_ORIGINAL;
    }
    static QString getIVA_DEFAULT_SISTEMA(){
        return m_IVA_DEFAULT_SISTEMA;
    }
    static QString getMODO_AFECTACION_CAJA(){
        return m_MODO_AFECTACION_CAJA;
    }
    static QString getMODO_ARTICULO(){
        return m_MODO_ARTICULO;
    }
    static QString getMODO_AUTORIZACION(){
        return m_MODO_AUTORIZACION;
    }
    static QString getMODO_CALCULOTOTAL(){
        return m_MODO_CALCULOTOTAL;
    }
    static QString getMODO_CLIENTE(){
        return m_MODO_CLIENTE;
    }
    static QString getMODO_IMPRESION_A4(){
        return m_MODO_IMPRESION_A4;
    }
    static QString getMONEDA_DEFAULT(){
        return m_MONEDA_DEFAULT;
    }
    static QString getMULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADOS(){
        return m_MULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADOS;
    }
    static QString getMULTI_BD(){
        return m_MULTI_BD;
    }
    static QString getMULTI_EMPRESA(){
        return m_MULTI_EMPRESA;
    }
    static QString getSEPARADOR_MANTENIMIENTO_BATCH(){
        return m_SEPARADOR_MANTENIMIENTO_BATCH;
    }
    static QString getTIPO_CIERRE_LIQUIDACION(){
        return m_TIPO_CIERRE_LIQUIDACION;
    }
    static QString getVERSION_BD(){
        return m_VERSION_BD;
    }
    static QString getCantidadDecimalesString(){
        return m_CantidadDecimalesString;
    }
    static QString getMODO_AVISO_NUEVO_DOCUMENTO(){
        return m_MODO_AVISO_NUEVO_DOCUMENTO;
    }
    static QString getMUESTRA_DESCRIPCION_ARTICULO_EXTENDIDA_FACTURACION(){
        return m_MUESTRA_DESCRIPCION_ARTICULO_EXTENDIDA_FACTURACION;
    }
    static QString getMODO_CFE(){
        return m_MODO_CFE;
    }

    static QString getCODIGO_BARRAS_A_DEMANDA_EXTENDIDO(){
        return m_CODIGO_BARRAS_A_DEMANDA_EXTENDIDO;
    }

    static QString getDISTANCIAENTREBOTONESMENU(){
        return m_DISTANCIAENTREBOTONESMENU;
    }

    static QString getUTILIZA_CONTROL_CLIENTE_CREDITO(){
        return m_UTILIZA_CONTROL_CLIENTE_CREDITO;
    }

    static QString getIMPRESION_ENVIOS(){
        return m_IMPRESION_ENVIOS;
    }

    static QString getNOMBRE_EMPRESA(){
        return m_NOMBRE_EMPRESA;
    }




private:
    QList<Configuracion> m_Configuracion;

    static QString m_CANTIDAD_DIGITOS_DECIMALES_MONTO;
    static QString m_CANTIDAD_DIGITOS_DECIMALES_MONTO_IMPRESION;
    static QString m_IMPRIME_DESCRIPCION_ARTICULO_ORIGINAL;
    static QString m_IVA_DEFAULT_SISTEMA;
    static QString m_MODO_AFECTACION_CAJA;
    static QString m_MODO_ARTICULO;
    static QString m_MODO_AUTORIZACION;
    static QString m_MODO_CALCULOTOTAL;
    static QString m_MODO_CLIENTE;
    static QString m_MODO_IMPRESION_A4;
    static QString m_MONEDA_DEFAULT;
    static QString m_MULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADOS;
    static QString m_MULTI_BD;
    static QString m_MULTI_EMPRESA;
    static QString m_SEPARADOR_MANTENIMIENTO_BATCH;
    static QString m_TIPO_CIERRE_LIQUIDACION;
    static QString m_VERSION_BD;
    static QString m_CantidadDecimalesString;
    static QString m_MODO_AVISO_NUEVO_DOCUMENTO;
    static QString m_MUESTRA_DESCRIPCION_ARTICULO_EXTENDIDA_FACTURACION;
    static QString m_MODO_CFE;
    static QString m_CODIGO_BARRAS_A_DEMANDA_EXTENDIDO;
    static QString m_DISTANCIAENTREBOTONESMENU;
    static QString m_UTILIZA_CONTROL_CLIENTE_CREDITO;

    static QString m_IMPRESION_ENVIOS;
    static QString m_NOMBRE_EMPRESA;




    static void setCANTIDAD_DIGITOS_DECIMALES_MONTO(QString value){
        m_CANTIDAD_DIGITOS_DECIMALES_MONTO=value;
    }
    static void setCANTIDAD_DIGITOS_DECIMALES_MONTO_IMPRESION(QString value){
        m_CANTIDAD_DIGITOS_DECIMALES_MONTO_IMPRESION=value;
    }
    static void setIMPRIME_DESCRIPCION_ARTICULO_ORIGINAL(QString value){
        m_IMPRIME_DESCRIPCION_ARTICULO_ORIGINAL=value;
    }
    static void setIVA_DEFAULT_SISTEMA(QString value){
        m_IVA_DEFAULT_SISTEMA=value;
    }
    static void setMODO_AFECTACION_CAJA(QString value){
        m_MODO_AFECTACION_CAJA=value;
    }
    static void setMODO_ARTICULO(QString value){
        m_MODO_ARTICULO=value;
    }
    static void setMODO_AUTORIZACION(QString value){
        m_MODO_AUTORIZACION=value;
    }
    static void setMODO_CALCULOTOTAL(QString value){
        m_MODO_CALCULOTOTAL=value;
    }
    static void setMODO_CLIENTE(QString value){
        m_MODO_CLIENTE=value;
    }
    static void setMODO_IMPRESION_A4(QString value){
        m_MODO_IMPRESION_A4=value;
    }
    static void setMONEDA_DEFAULT(QString value){
        m_MONEDA_DEFAULT=value;
    }
    static void setMULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADOS(QString value){
        m_MULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADOS=value;
    }
    static void setMULTI_BD(QString value){
        m_MULTI_BD=value;
    }
    static void setMULTI_EMPRESA(QString value){
        m_MULTI_EMPRESA=value;
    }
    static void setSEPARADOR_MANTENIMIENTO_BATCH(QString value){
        m_SEPARADOR_MANTENIMIENTO_BATCH=value;
    }
    static void setTIPO_CIERRE_LIQUIDACION(QString value){
        m_TIPO_CIERRE_LIQUIDACION=value;
    }
    static void setVERSION_BD(QString value){
        m_VERSION_BD=value;
    }
    static void setCantidadDecimalesString(QString value){
        m_CantidadDecimalesString=value;
    }
    static void setMODO_AVISO_NUEVO_DOCUMENTO(QString value){
        m_MODO_AVISO_NUEVO_DOCUMENTO=value;
    }
    static void setMUESTRA_DESCRIPCION_ARTICULO_EXTENDIDA_FACTURACION(QString value){
        m_MUESTRA_DESCRIPCION_ARTICULO_EXTENDIDA_FACTURACION=value;
    }
    static void setMODO_CFE(QString value){
        m_MODO_CFE=value;
    }
    static void setCODIGO_BARRAS_A_DEMANDA_EXTENDIDO(QString value){
        m_CODIGO_BARRAS_A_DEMANDA_EXTENDIDO=value;
    }
    static void setDISTANCIAENTREBOTONESMENU(QString value){
        m_DISTANCIAENTREBOTONESMENU=value;
    }
    static void setUTILIZA_CONTROL_CLIENTE_CREDITO(QString value){
        m_UTILIZA_CONTROL_CLIENTE_CREDITO=value;
    }
    static void setIMPRESION_ENVIOS(QString value){
        m_IMPRESION_ENVIOS=value;
    }
    static void setNOMBRE_EMPRESA(QString value){
        m_NOMBRE_EMPRESA=value;
    }



};

#endif // MODULOCONFIGURACION_H
