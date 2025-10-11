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

#include "modulodocumentoslineasajustes.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>



ModuloDocumentosLineasAjustes::ModuloDocumentosLineasAjustes(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[IdAjusteRole]              = "idAjuste";
    roles[CodigoDocumentoRole]       = "codigoDocumento";
    roles[CodigoTipoDocumentoRole]   = "codigoTipoDocumento";
    roles[SerieDocumentoRole]        = "serieDocumento";
    roles[NumeroLineaRole]           = "numeroLinea";
    roles[CodigoArticuloRole]        = "codigoArticulo";
    roles[DescripcionArticuloRole]   = "descripcionArticulo";
    roles[IdDescuentoRole]           = "idDescuento";
    roles[DescripcionRole]           = "descripcion";
    roles[TipoRole]                  = "tipo";               // "DESCUENTO" | "RECARGO"
    roles[TipoValorRole]             = "tipoValor";          // "PORCENTAJE" | "MONTO"
    roles[PorcentajeRole]            = "porcentaje";         // QVariant (nullable)
    roles[MontoRole]                 = "monto";              // QVariant (nullable)
    roles[MonedaRole]                = "moneda";             // QVariant (nullable)
    roles[CotizacionUsadaRole]       = "cotizacionUsada";    // QVariant (nullable)
    roles[MontoAplicadoRole]         = "montoAplicado";      // double
    roles[PrecioUnitBaseRole]        = "precioUnitBase";     // QVariant (nullable)
    roles[PrecioUnitResultanteRole]  = "precioUnitResultante"; // QVariant (nullable)
    roles[UsuarioRole]               = "usuario";
    roles[UuidRole]                  = "uuid";


    setRoleNames(roles);
}


AjusteLineaDTO::AjusteLineaDTO(
        const quint64 &idAjuste,
        const quint64 &codigoDocumento,
        const quint32 &codigoTipoDocumento,
        const QString &serieDocumento,
        const quint32 &numeroLinea,
        const QString &codigoArticulo,
        const QString &descripcionArticulo,
        const quint32 &idDescuento,
        const QString &descripcion,
        const QString &tipo,       // "DESCUENTO" | "RECARGO"
        const QString &tipoValor,  // "PORCENTAJE" | "MONTO"
        const QVariant &porcentaje, // DECIMAL(45,6) nullable
        const QVariant &monto,      // DECIMAL(45,4) nullable
        const QVariant &moneda,     // INT unsigned nullable
        const QVariant &cotizacionUsada, // DECIMAL(45,8) nullable
        const double &montoAplicado,
        const QVariant &precioUnitBase,       // DECIMAL(45,4) nullable
        const QVariant &precioUnitResultante, // DECIMAL(45,4) nullable
        const QString &usuario,
        const QString &uuid
        )

    : m_idAjuste(idAjuste),
      m_codigoDocumento(codigoDocumento),
      m_codigoTipoDocumento(codigoTipoDocumento),
      m_serieDocumento(serieDocumento),
      m_numeroLinea(numeroLinea),
      m_codigoArticulo(codigoArticulo),
      m_descripcionArticulo(descripcionArticulo),
      m_idDescuento(idDescuento),
      m_descripcion(descripcion),
      m_tipo(tipo),
      m_tipoValor(tipoValor),
      m_porcentaje(porcentaje),
      m_monto(monto),
      m_moneda(moneda),
      m_cotizacionUsada(cotizacionUsada),
      m_montoAplicado(montoAplicado),
      m_precioUnitBase(precioUnitBase),
      m_precioUnitResultante(precioUnitResultante),
      m_usuario(usuario),
      m_uuid(uuid)
{
}


qulonglong AjusteLineaDTO::idAjuste() const               { return m_idAjuste; }
qulonglong AjusteLineaDTO::codigoDocumento() const        { return m_codigoDocumento; }
quint32    AjusteLineaDTO::codigoTipoDocumento() const    { return m_codigoTipoDocumento; }
QString AjusteLineaDTO::serieDocumento() const     { return m_serieDocumento; }
quint32    AjusteLineaDTO::numeroLinea() const            { return m_numeroLinea; }

QString AjusteLineaDTO::codigoArticulo() const     { return m_codigoArticulo; }
QString AjusteLineaDTO::descripcionArticulo() const{ return m_descripcionArticulo; }

quint32    AjusteLineaDTO::idDescuento() const            { return m_idDescuento; }
QString AjusteLineaDTO::descripcion() const        { return m_descripcion; }

QString AjusteLineaDTO::tipo() const               { return m_tipo; }
QString AjusteLineaDTO::tipoValor() const          { return m_tipoValor; }

QVariant   AjusteLineaDTO::porcentaje() const             { return m_porcentaje; }
QVariant   AjusteLineaDTO::monto() const                  { return m_monto; }
QVariant   AjusteLineaDTO::moneda() const                 { return m_moneda; }
QVariant   AjusteLineaDTO::cotizacionUsada() const        { return m_cotizacionUsada; }

double     AjusteLineaDTO::montoAplicado() const          { return m_montoAplicado; }

QVariant   AjusteLineaDTO::precioUnitBase() const         { return m_precioUnitBase; }
QVariant   AjusteLineaDTO::precioUnitResultante() const   { return m_precioUnitResultante; }

QString AjusteLineaDTO::usuario() const            { return m_usuario; }
QString AjusteLineaDTO::uuid() const               { return m_uuid; }



void ModuloDocumentosLineasAjustes::agregar(const AjusteLineaDTO &ajusteLineaDTO)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_AjusteLineaDTO << ajusteLineaDTO;
    endInsertRows();
}

void ModuloDocumentosLineasAjustes::limpiarLista(){
    m_AjusteLineaDTO.clear();
}


bool ModuloDocumentosLineasAjustes::guardarLineaDocumentoAjustes(QString _consultaInsertLineas) const {

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


bool ModuloDocumentosLineasAjustes::eliminarLineaDocumentoAjustes(QString _codigoDocumento, QString _codigoTipoDocumento, QString _serieDocumento) const {

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

        if(query.exec("delete from DocumentosLineasAjustes where codigoDocumento="+_codigoDocumento+" and codigoTipoDocumento="+_codigoTipoDocumento+" and serieDocumento='"+_serieDocumento+"'")){

            return true;

        }else{
            return false;
        }

    }else{return false;}
}



void ModuloDocumentosLineasAjustes::buscar(QString codigoDocumento, QString codigoTipoDocumento, QString serieDocumento){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        //QSqlQuery q = Database::consultaSql("select * from Ivas where "+campo+"'"+datoABuscar+"'");
        QSqlQuery q = Database::consultaSql("select * From DocumentosLineasAjustes where codigoDocumento="+codigoDocumento+" and codigoTipoDocumento="+codigoTipoDocumento+" and serieDocumento='"+serieDocumento+"' order by numeroLinea;");

        QSqlRecord rec = q.record();

        ModuloDocumentosLineasAjustes::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloDocumentosLineasAjustes::agregar(
                            AjusteLineaDTO(
                                q.value(rec.indexOf("idAjuste")).toULongLong(),
                                q.value(rec.indexOf("codigoDocumento")).toULongLong(),
                                q.value(rec.indexOf("codigoTipoDocumento")).toUInt(),
                                q.value(rec.indexOf("serieDocumento")).toString(),
                                q.value(rec.indexOf("numeroLinea")).toUInt(),
                                q.value(rec.indexOf("codigoArticulo")).toString(),
                                q.value(rec.indexOf("descripcionArticulo")).toString(),
                                q.value(rec.indexOf("idDescuento")).toUInt(),
                                q.value(rec.indexOf("descripcion")).toString(),
                                q.value(rec.indexOf("tipo")).toString(),
                                q.value(rec.indexOf("tipoValor")).toString(),
                                q.value(rec.indexOf("porcentaje")),          // QVariant (nullable)
                                q.value(rec.indexOf("monto")),               // QVariant (nullable)
                                q.value(rec.indexOf("moneda")),              // QVariant (nullable)
                                q.value(rec.indexOf("cotizacionUsada")),     // QVariant (nullable)
                                q.value(rec.indexOf("montoAplicado")).toDouble(),
                                q.value(rec.indexOf("precioUnitBase")),      // QVariant (nullable)
                                q.value(rec.indexOf("precioUnitResultante")),// QVariant (nullable)
                                q.value(rec.indexOf("usuario")).toString(),
                                q.value(rec.indexOf("uuid")).toString()
                                )
                            );
            }
        }
    }
}

int ModuloDocumentosLineasAjustes::rowCount(const QModelIndex & parent) const {
    return m_AjusteLineaDTO.count();
}

QVariant ModuloDocumentosLineasAjustes::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_AjusteLineaDTO.count()){
        return QVariant();

    }

    const AjusteLineaDTO &ajusteLineaDTO = m_AjusteLineaDTO[index.row()];



    if (role == IdAjusteRole){
        return QVariant::fromValue<qulonglong>(ajusteLineaDTO.idAjuste());
    }
    else if (role == CodigoDocumentoRole){
        return QVariant::fromValue<qulonglong>(ajusteLineaDTO.codigoDocumento());
    }
    else if (role == CodigoTipoDocumentoRole){
        return QVariant::fromValue<quint32>(ajusteLineaDTO.codigoTipoDocumento());
    }
    else if (role == SerieDocumentoRole){
        return ajusteLineaDTO.serieDocumento();
    }
    else if (role == NumeroLineaRole){
        return QVariant::fromValue<quint32>(ajusteLineaDTO.numeroLinea());
    }
    else if (role == CodigoArticuloRole){
        return ajusteLineaDTO.codigoArticulo();
    }
    else if (role == DescripcionArticuloRole){
        return ajusteLineaDTO.descripcionArticulo();
    }
    else if (role == IdDescuentoRole){
        return QVariant::fromValue<quint32>(ajusteLineaDTO.idDescuento());
    }
    else if (role == DescripcionRole){
        return ajusteLineaDTO.descripcion();
    }
    else if (role == TipoRole){
        return ajusteLineaDTO.tipo();              // "DESCUENTO" | "RECARGO"
    }
    else if (role == TipoValorRole){
        return ajusteLineaDTO.tipoValor();        // "PORCENTAJE" | "MONTO"
    }
    else if (role == PorcentajeRole){
        return ajusteLineaDTO.porcentaje();       // QVariant (nullable)
    }
    else if (role == MontoRole){
        return ajusteLineaDTO.monto();            // QVariant (nullable)
    }
    else if (role == MonedaRole){
        return ajusteLineaDTO.moneda();           // QVariant (nullable)
    }
    else if (role == CotizacionUsadaRole){
        return ajusteLineaDTO.cotizacionUsada();  // QVariant (nullable)
    }
    else if (role == MontoAplicadoRole){
        return ajusteLineaDTO.montoAplicado();    // double
    }
    else if (role == PrecioUnitBaseRole){
        return ajusteLineaDTO.precioUnitBase();   // QVariant (nullable)
    }
    else if (role == PrecioUnitResultanteRole){
        return ajusteLineaDTO.precioUnitResultante(); // QVariant (nullable)
    }
    else if (role == UsuarioRole){
        return ajusteLineaDTO.usuario();
    }
    else if (role == UuidRole){
        return ajusteLineaDTO.uuid();
    }




    return QVariant();
}


quint64 ModuloDocumentosLineasAjustes::retornaIdAjuste(int index){
    return m_AjusteLineaDTO[index].idAjuste();
}

quint64 ModuloDocumentosLineasAjustes::retornaCodigoDocumento(int index){
    return m_AjusteLineaDTO[index].codigoDocumento();
}

quint32 ModuloDocumentosLineasAjustes::retornaCodigoTipoDocumento(int index){
    return m_AjusteLineaDTO[index].codigoTipoDocumento();
}

QString ModuloDocumentosLineasAjustes::retornaSerieDocumento(int index){
    return m_AjusteLineaDTO[index].serieDocumento();
}

quint32 ModuloDocumentosLineasAjustes::retornaNumeroLinea(int index){
    return m_AjusteLineaDTO[index].numeroLinea();
}

QString ModuloDocumentosLineasAjustes::retornaCodigoArticulo(int index){
    return m_AjusteLineaDTO[index].codigoArticulo();
}

QString ModuloDocumentosLineasAjustes::retornaDescripcionArticulo(int index){
    return m_AjusteLineaDTO[index].descripcionArticulo();
}

quint32 ModuloDocumentosLineasAjustes::retornaIdDescuento(int index){
    return m_AjusteLineaDTO[index].idDescuento();
}

QString ModuloDocumentosLineasAjustes::retornaDescripcion(int index){
    return m_AjusteLineaDTO[index].descripcion();
}

QString ModuloDocumentosLineasAjustes::retornaTipo(int index){
    return m_AjusteLineaDTO[index].tipo();
}

QString ModuloDocumentosLineasAjustes::retornaTipoValor(int index){
    return m_AjusteLineaDTO[index].tipoValor();
}

QVariant ModuloDocumentosLineasAjustes::retornaPorcentaje(int index){
    return m_AjusteLineaDTO[index].porcentaje();
}

QVariant ModuloDocumentosLineasAjustes::retornaMonto(int index){
    return m_AjusteLineaDTO[index].monto();
}

QVariant ModuloDocumentosLineasAjustes::retornaMoneda(int index){
    return m_AjusteLineaDTO[index].moneda();
}

QVariant ModuloDocumentosLineasAjustes::retornaCotizacionUsada(int index){
    return m_AjusteLineaDTO[index].cotizacionUsada();
}

double ModuloDocumentosLineasAjustes::retornaMontoAplicado(int index){
    return m_AjusteLineaDTO[index].montoAplicado();
}

QVariant ModuloDocumentosLineasAjustes::retornaPrecioUnitBase(int index){
    return m_AjusteLineaDTO[index].precioUnitBase();
}

QVariant ModuloDocumentosLineasAjustes::retornaPrecioUnitResultante(int index){
    return m_AjusteLineaDTO[index].precioUnitResultante();
}

QString ModuloDocumentosLineasAjustes::retornaUsuario(int index){
    return m_AjusteLineaDTO[index].usuario();
}

QString ModuloDocumentosLineasAjustes::retornaUuid(int index){
    return m_AjusteLineaDTO[index].uuid();
}




