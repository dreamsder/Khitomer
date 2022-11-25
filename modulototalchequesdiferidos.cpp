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

#include "modulototalchequesdiferidos.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>


ModuloTotalChequesDiferidos::ModuloTotalChequesDiferidos(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[codigoMonedaRole] = "codigoMoneda";
    roles[importeTotalChequesDiferidosRole] = "importeTotalChequesDiferidos";
    setRoleNames(roles);
}


TotalCheques::TotalCheques(const int &codigoMoneda, const QString &importeTotalChequesDiferidos)
    : m_codigoMoneda(codigoMoneda), m_importeTotalChequesDiferidos(importeTotalChequesDiferidos)
{
}

int TotalCheques::codigoMoneda() const
{
    return m_codigoMoneda;
}
QString TotalCheques::importeTotalChequesDiferidos() const
{
    return m_importeTotalChequesDiferidos;
}

void ModuloTotalChequesDiferidos::agregarTotalCheques(const TotalCheques &totalCheques)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_TotalCheques << totalCheques;
    endInsertRows();
}

void ModuloTotalChequesDiferidos::limpiarListaTotalCheques(){
    m_TotalCheques.clear();
}

void ModuloTotalChequesDiferidos::buscarTotalCheques(QString _codigoLiquidacion, QString _codigoVendedor){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery q = Database::consultaSql("SELECT   MP.monedaMedioPago'codigoMoneda',  case when   (select  sum(DLP.importePago*T.afectaTotales)   FROM  Documentos D  join DocumentosLineasPago DLP on DLP.codigoDocumento=D.codigoDocumento and  DLP.codigoTipoDocumento=D.codigoTipoDocumento and DLP.serieDocumento=D.serieDocumento  join MediosDePago MPO on MPO.codigoMedioPago=DLP.codigoMedioPago  join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  where D.codigoLiquidacion='"+_codigoLiquidacion+"' and D.codigoVendedorLiquidacion='"+_codigoVendedor+"'   and T.afectaTotales!=0  and D.codigoEstadoDocumento not in ('C','A','P')  and MPO.codigoTipoMedioDePago=3 and DLP.codigoTipoCheque=2 and DLP.monedaMedioPago=MP.monedaMedioPago  and DLP.montoCobrado<DLP.importePago and DLP.documentoChequeDiferido=0 and DLP.tipoDocumentoChequeDiferido=0) is null then 0 else    (select    sum(DLP.importePago*T.afectaTotales)  FROM  Documentos D  join DocumentosLineasPago DLP on DLP.codigoDocumento=D.codigoDocumento and  DLP.codigoTipoDocumento=D.codigoTipoDocumento  and DLP.serieDocumento=D.serieDocumento join MediosDePago MPO on MPO.codigoMedioPago=DLP.codigoMedioPago   join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  where D.codigoLiquidacion='"+_codigoLiquidacion+"' and D.codigoVendedorLiquidacion='"+_codigoVendedor+"'  and T.afectaTotales!=0  and D.codigoEstadoDocumento not in ('C','A','P')  and MPO.codigoTipoMedioDePago=3 and DLP.codigoTipoCheque=2 and DLP.monedaMedioPago=MP.monedaMedioPago and DLP.montoCobrado<DLP.importePago and DLP.documentoChequeDiferido=0 and DLP.tipoDocumentoChequeDiferido=0) end'importeTotalChequesDiferidos' FROM   MediosDePago MP  where MP.codigoTipoMedioDePago=3 group by MP.codigoMedioPago ");
        QSqlRecord rec = q.record();
        ModuloTotalChequesDiferidos::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloTotalChequesDiferidos::agregarTotalCheques(TotalCheques(q.value(rec.indexOf("codigoMoneda")).toInt(), q.value(rec.indexOf("importeTotalChequesDiferidos")).toString()));
            }
        }
    }
}
void ModuloTotalChequesDiferidos::buscarTotalOtrosCheques(QString _codigoLiquidacion, QString _codigoVendedor){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery q = Database::consultaSql("SELECT   MP.monedaMedioPago'codigoMoneda',  case when   (select  sum(DLP.importePago*T.afectaTotales)   FROM  Documentos D  join DocumentosLineasPago DLP on DLP.codigoDocumento=D.codigoDocumento and  DLP.codigoTipoDocumento=D.codigoTipoDocumento and DLP.serieDocumento=D.serieDocumento join MediosDePago MPO on MPO.codigoMedioPago=DLP.codigoMedioPago  join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  where D.codigoLiquidacion='"+_codigoLiquidacion+"' and D.codigoVendedorLiquidacion='"+_codigoVendedor+"'   and T.afectaTotales!=0  and D.codigoEstadoDocumento not in ('C','A','P')  and MPO.codigoTipoMedioDePago=3 and DLP.codigoTipoCheque!=2 and DLP.monedaMedioPago=MP.monedaMedioPago  and DLP.montoCobrado<DLP.importePago and DLP.documentoChequeDiferido=0 and DLP.tipoDocumentoChequeDiferido=0) is null then 0 else    (select    sum(DLP.importePago*T.afectaTotales)  FROM  Documentos D  join DocumentosLineasPago DLP on DLP.codigoDocumento=D.codigoDocumento and  DLP.codigoTipoDocumento=D.codigoTipoDocumento and DLP.serieDocumento=D.serieDocumento   join MediosDePago MPO on MPO.codigoMedioPago=DLP.codigoMedioPago   join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  where D.codigoLiquidacion='"+_codigoLiquidacion+"' and D.codigoVendedorLiquidacion='"+_codigoVendedor+"'  and T.afectaTotales!=0  and D.codigoEstadoDocumento not in ('C','A','P')  and MPO.codigoTipoMedioDePago=3 and DLP.codigoTipoCheque!=2 and DLP.monedaMedioPago=MP.monedaMedioPago and DLP.montoCobrado<DLP.importePago and DLP.documentoChequeDiferido=0 and DLP.tipoDocumentoChequeDiferido=0) end'importeTotalChequesDiferidos' FROM   MediosDePago MP  where MP.codigoTipoMedioDePago=3 group by MP.codigoMedioPago ");
        QSqlRecord rec = q.record();


        ModuloTotalChequesDiferidos::reset();
        if(q.record().count()>0){
            while (q.next()){
                ModuloTotalChequesDiferidos::agregarTotalCheques(TotalCheques(q.value(rec.indexOf("codigoMoneda")).toInt(), q.value(rec.indexOf("importeTotalChequesDiferidos")).toString()));
            }
        }
    }


}


int ModuloTotalChequesDiferidos::rowCount(const QModelIndex & parent) const {
    return m_TotalCheques.count();
}

QVariant ModuloTotalChequesDiferidos::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_TotalCheques.count()){
        return QVariant();

    }

    const TotalCheques &totalCheques = m_TotalCheques[index.row()];

    if (role == codigoMonedaRole){
        return totalCheques.codigoMoneda();

    }
    else if (role == importeTotalChequesDiferidosRole){
        return totalCheques.importeTotalChequesDiferidos();

    }

    return QVariant();
}
