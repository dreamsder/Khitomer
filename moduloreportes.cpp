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

/********************************************************************
Las librearias para poder realizar la generación del archivo .xls,
fueron creadas por Yap Chun Wei y sus colaboradores Martin Fuchs, Ami Castonguay y Long Wenbiao
http://www.codeproject.com/Articles/13852/BasicExcel-A-Class-to-Read-and-Write-to-Microsoft
http://www.codeproject.com/Articles/42504/ExcelFormat-Library
*********************************************************************/

#include "moduloreportes.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QDebug>
#include <funciones.h>
#include <QDesktopServices>
#include <QDateTime>
#include <moduloreportesmenu.h>

#ifdef UNIX
#include "BasicExcel.hpp"
#include "ExcelFormat.h"
#endif
#ifdef WIN32
#include "BasicExcelWin.hpp"
#include "ExcelFormatWin.h"
#endif
#ifdef WIN64
#include "BasicExcelWin.hpp"
#include "ExcelFormatWin.h"
#endif


#include <Utilidades/moduloconfiguracion.h>
#include <CFE/modulo_cfe_parametrosgenerales.h>

#include <moduloreportesconfiguracion.h>

ModuloConfiguracion func_configuracionReportes;
Modulo_CFE_ParametrosGenerales func_cfe_ParametrosGenerales;

Funciones funcion_reporte;

ModuloReportesMenu func_moduloReportesMenu;

ModuloReportesConfiguracion moduloReportesConfiguracion;

using namespace YExcel;



ModuloReportes::ModuloReportes(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoReporteRole] = "codigoReporte";
    roles[CodigoMenuReporteRole] = "codigoMenuReporte";
    roles[DescripcionReporteRole] = "descripcionReporte";
    roles[ConsultaSqlRole] = "consultaSql";
    roles[ConsultaSqlGraficasRole] = "consultaSqlGraficas";
    roles[ConsultaSqlCabezalRole] = "consultaSqlCabezal";
    roles[utilizaCodigoClienteRole]="utilizaCodigoCliente";
    roles[utilizaCodigoProveedorRole]="utilizaCodigoProveedor";
    roles[utilizaCodigoArticuloRole]="utilizaCodigoArticulo";
    roles[utilizaCantidadItemRankingRole]="utilizaCantidadItemRanking";
    roles[utilizaFechaRole]="utilizaFecha";
    roles[utilizaFechaDesdeRole]="utilizaFechaDesde";
    roles[utilizaFechaHastaRole]="utilizaFechaHasta";
    roles[utilizaVendedorRole]="utilizaVendedor";
    roles[utilizaTipoDocumentoRole]="utilizaTipoDocumento";
    roles[utilizaSubRubrosRole]="utilizaSubRubros";
    roles[utilizaCodigoLiquidacionCajaRole]="utilizaCodigoLiquidacionCaja";
    roles[utilizaRubrosRole]="utilizaRubros";
    roles[utilizaDesdeCodigoArticuloRole]="utilizaDesdeCodigoArticulo";
    roles[utilizaHastaCodigoArticuloRole]="utilizaHastaCodigoArticulo";
    roles[utilizaListaPrecioRole]="utilizaListaPrecio";
    roles[utilizaGraficasRole]="utilizaGraficas";
    roles[utilizaCuentaBancariaRole]="utilizaCuentaBancaria";
    roles[utilizaMonedasRole]="utilizaMonedas";
    roles[utilizaPaisRole]="utilizaPais";
    roles[utilizaDepartamentoRole]="utilizaDepartamento";
    roles[utilizaLocalidadRole]="utilizaLocalidad";
    roles[utilizaCoincidenciaCodigoClienteRole]="utilizaCoincidenciaCodigoCliente";
    roles[utilizaOrdenEnReporteRole]="utilizaOrdenEnReporte";
    roles[utilizaTipoClasificacionClienteRole]="utilizaTipoClasificacionCliente";
    roles[utilizaListaPrecio2Role]="utilizaListaPrecio2";
    roles[utilizaProcedenciaEnReporteRole]="utilizaProcedenciaEnReporte";
    roles[utilizaAbrirDocumentosRole]="utilizaAbrirDocumentos";

    setRoleNames(roles);


}


Reportes::Reportes(const qlonglong &codigoReporte, const int &codigoMenuReporte,const QString &descripcionReporte,const QString &consultaSql,const QString &consultaSqlGraficas
                   ,const QString &consultaSqlCabezal,
                   const QString &utilizaCodigoCliente,
                   const QString &utilizaCodigoProveedor,
                   const QString &utilizaCodigoArticulo,
                   const QString &utilizaCantidadItemRanking,
                   const QString &utilizaFecha,
                   const QString &utilizaFechaDesde,
                   const QString &utilizaFechaHasta,
                   const QString &utilizaVendedor,
                   const QString &utilizaTipoDocumento,
                   const QString &utilizaSubRubros,
                   const QString &utilizaCodigoLiquidacionCaja,
                   const QString &utilizaRubros,
                   const QString &utilizaDesdeCodigoArticulo,
                   const QString &utilizaHastaCodigoArticulo,
                   const QString &utilizaListaPrecio,
                   const QString &utilizaGraficas,
                   const QString &utilizaCuentaBancaria,
                   const QString &utilizaMonedas,
                   const QString &utilizaPais,
                   const QString &utilizaDepartamento,
                   const QString &utilizaLocalidad,
                   const QString &utilizaCoincidenciaCodigoCliente,
                   const QString &utilizaOrdenEnReporte,
                   const QString &utilizaTipoClasificacionCliente,
                   const QString &utilizaListaPrecio2,
                   const QString &utilizaProcedenciaEnReporte,
                   const QString &utilizaAbrirDocumentos



                   )
    : m_codigoReporte(codigoReporte), m_codigoMenuReporte(codigoMenuReporte), m_descripcionReporte(descripcionReporte), m_consultaSql(consultaSql), m_consultaSqlGraficas(consultaSqlGraficas)
    , m_consultaSqlCabezal(consultaSqlCabezal),
      m_utilizaCodigoCliente(utilizaCodigoCliente),
      m_utilizaCodigoProveedor(utilizaCodigoProveedor),
      m_utilizaCodigoArticulo(utilizaCodigoArticulo),
      m_utilizaCantidadItemRanking(utilizaCantidadItemRanking),
      m_utilizaFecha(utilizaFecha),
      m_utilizaFechaDesde(utilizaFechaDesde),
      m_utilizaFechaHasta(utilizaFechaHasta),
      m_utilizaVendedor(utilizaVendedor),
      m_utilizaTipoDocumento(utilizaTipoDocumento),
      m_utilizaSubRubros(utilizaSubRubros),
      m_utilizaCodigoLiquidacionCaja(utilizaCodigoLiquidacionCaja),
      m_utilizaRubros(utilizaRubros),
      m_utilizaDesdeCodigoArticulo(utilizaDesdeCodigoArticulo),
      m_utilizaHastaCodigoArticulo(utilizaHastaCodigoArticulo),
      m_utilizaListaPrecio(utilizaListaPrecio),
      m_utilizaGraficas(utilizaGraficas),
      m_utilizaCuentaBancaria(utilizaCuentaBancaria),
      m_utilizaMonedas(utilizaMonedas),
      m_utilizaPais(utilizaPais),
      m_utilizaDepartamento(utilizaDepartamento),
      m_utilizaLocalidad(utilizaLocalidad),
      m_utilizaCoincidenciaCodigoCliente(utilizaCoincidenciaCodigoCliente),
      m_utilizaOrdenEnReporte(utilizaOrdenEnReporte),
      m_utilizaTipoClasificacionCliente(utilizaTipoClasificacionCliente),
      m_utilizaListaPrecio2(utilizaListaPrecio2),
      m_utilizaProcedenciaEnReporte(utilizaProcedenciaEnReporte),
      m_utilizaAbrirDocumentos(utilizaAbrirDocumentos)
{
}

qlonglong Reportes::codigoReporte() const
{
    return m_codigoReporte;
}
int Reportes::codigoMenuReporte() const
{
    return m_codigoMenuReporte;
}
QString Reportes::descripcionReporte() const
{
    return m_descripcionReporte;
}
QString Reportes::consultaSql() const
{
    return m_consultaSql;
}
QString Reportes::consultaSqlGraficas() const
{
    return m_consultaSqlGraficas;
}
QString Reportes::consultaSqlCabezal() const
{
    return m_consultaSqlCabezal;
}
QString Reportes::utilizaCodigoCliente()const{
    return m_utilizaCodigoCliente;}
QString Reportes::utilizaCodigoProveedor()const{
    return m_utilizaCodigoProveedor;}
QString Reportes::utilizaCodigoArticulo()const{
    return m_utilizaCodigoArticulo;}
QString Reportes::utilizaCantidadItemRanking()const{
    return m_utilizaCantidadItemRanking;}
QString Reportes::utilizaFecha()const{
    return m_utilizaFecha;}
QString Reportes::utilizaFechaDesde()const{
    return m_utilizaFechaDesde;}
QString Reportes::utilizaFechaHasta()const{
    return m_utilizaFechaHasta;}
QString Reportes::utilizaVendedor()const{
    return m_utilizaVendedor;}
QString Reportes::utilizaTipoDocumento()const{
    return m_utilizaTipoDocumento;}
QString Reportes::utilizaSubRubros()const{
    return m_utilizaSubRubros;}
QString Reportes::utilizaCodigoLiquidacionCaja()const{
    return m_utilizaCodigoLiquidacionCaja;}
QString Reportes::utilizaRubros()const{
    return m_utilizaRubros;}
QString Reportes::utilizaDesdeCodigoArticulo()const{
    return m_utilizaDesdeCodigoArticulo;}
QString Reportes::utilizaHastaCodigoArticulo()const{
    return m_utilizaHastaCodigoArticulo;}
QString Reportes::utilizaListaPrecio()const{
    return m_utilizaListaPrecio;}
QString Reportes::utilizaGraficas()const{
    return m_utilizaGraficas;}
QString Reportes::utilizaCuentaBancaria()const{
    return m_utilizaCuentaBancaria;}
QString Reportes::utilizaMonedas()const{
    return m_utilizaMonedas;}
QString Reportes::utilizaPais()const{
    return m_utilizaPais;}
QString Reportes::utilizaDepartamento()const{
    return m_utilizaDepartamento;}
QString Reportes::utilizaLocalidad()const{
    return m_utilizaLocalidad;}
QString Reportes::utilizaCoincidenciaCodigoCliente()const{
    return m_utilizaCoincidenciaCodigoCliente;}
QString Reportes::utilizaOrdenEnReporte()const{
    return m_utilizaOrdenEnReporte;}
QString Reportes::utilizaTipoClasificacionCliente()const{
    return m_utilizaTipoClasificacionCliente;}
QString Reportes::utilizaListaPrecio2()const{
    return m_utilizaListaPrecio2;}
QString Reportes::utilizaProcedenciaEnReporte()const{
    return m_utilizaProcedenciaEnReporte;}
QString Reportes::utilizaAbrirDocumentos()const{
    return m_utilizaAbrirDocumentos;}





void ModuloReportes::agregarReportes(const Reportes &reportes)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Reportes << reportes;
    endInsertRows();
}

void ModuloReportes::limpiarListaReportes(){
    m_Reportes.clear();
}

void ModuloReportes::buscarReportes(QString campo, QString datoABuscar,QString _codigoPerfil){

    moduloReportesConfiguracion.buscarReportesConfiguracion();

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
        QSqlRecord rec;

        if(func_moduloReportesMenu.listaCodigoMenusPorPerfil(_codigoPerfil)==""){

            q = Database::consultaSql("select * from Reportes where "+campo+"'"+datoABuscar+"' order by descripcionReporte");
            rec = q.record();
            ModuloReportes::reset();
            if(q.record().count()>0){

                while (q.next()){
                    ModuloReportes::agregarReportes(Reportes(q.value(rec.indexOf("codigoReporte")).toLongLong()
                                                             , q.value(rec.indexOf("codigoMenuReporte")).toInt()
                                                             , q.value(rec.indexOf("descripcionReporte")).toString()
                                                             , q.value(rec.indexOf("consultaSql")).toString()
                                                             , q.value(rec.indexOf("consultaSqlGraficas")).toString()
                                                             , q.value(rec.indexOf("consultaSqlCabezal")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoProveedor")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaCantidadItemRanking")).toString(),
                                                             q.value(rec.indexOf("utilizaFecha")).toString(),
                                                             q.value(rec.indexOf("utilizaFechaDesde")).toString(),
                                                             q.value(rec.indexOf("utilizaFechaHasta")).toString(),
                                                             q.value(rec.indexOf("utilizaVendedor")).toString(),
                                                             q.value(rec.indexOf("utilizaTipoDocumento")).toString(),
                                                             q.value(rec.indexOf("utilizaSubRubros")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoLiquidacionCaja")).toString(),
                                                             q.value(rec.indexOf("utilizaRubros")).toString(),
                                                             q.value(rec.indexOf("utilizaDesdeCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaHastaCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaListaPrecio")).toString(),
                                                             q.value(rec.indexOf("utilizaGraficas")).toString(),
                                                             q.value(rec.indexOf("utilizaCuentaBancaria")).toString(),
                                                             q.value(rec.indexOf("utilizaMonedas")).toString(),
                                                             q.value(rec.indexOf("utilizaPais")).toString(),
                                                             q.value(rec.indexOf("utilizaDepartamento")).toString(),
                                                             q.value(rec.indexOf("utilizaLocalidad")).toString(),
                                                             q.value(rec.indexOf("utilizaCoincidenciaCodigoCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaOrdenEnReporte")).toString(),
                                                             q.value(rec.indexOf("utilizaTipoClasificacionCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaListaPrecio2")).toString(),
                                                             q.value(rec.indexOf("utilizaProcedenciaEnReporte")).toString(),
                                                             q.value(rec.indexOf("utilizaAbrirDocumentos")).toString()
                                                             ));
                }
            }
        }else{
            q = Database::consultaSql("select RE.* from Reportes RE join ReportesPerfilesUsuarios RPU on RPU.codigoReporte=RE.codigoReporte where "+campo+"'"+datoABuscar+"' and RPU.codigoPerfil='"+_codigoPerfil+"' order by RE.descripcionReporte");

            rec = q.record();
            ModuloReportes::reset();
            if(q.record().count()>0){

                while (q.next()){
                    ModuloReportes::agregarReportes(Reportes(q.value(rec.indexOf("codigoReporte")).toLongLong()
                                                             , q.value(rec.indexOf("codigoMenuReporte")).toInt()
                                                             , q.value(rec.indexOf("descripcionReporte")).toString()
                                                             , q.value(rec.indexOf("consultaSql")).toString()
                                                             , q.value(rec.indexOf("consultaSqlGraficas")).toString()
                                                             , q.value(rec.indexOf("consultaSqlCabezal")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoProveedor")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaCantidadItemRanking")).toString(),
                                                             q.value(rec.indexOf("utilizaFecha")).toString(),
                                                             q.value(rec.indexOf("utilizaFechaDesde")).toString(),
                                                             q.value(rec.indexOf("utilizaFechaHasta")).toString(),
                                                             q.value(rec.indexOf("utilizaVendedor")).toString(),
                                                             q.value(rec.indexOf("utilizaTipoDocumento")).toString(),
                                                             q.value(rec.indexOf("utilizaSubRubros")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoLiquidacionCaja")).toString(),
                                                             q.value(rec.indexOf("utilizaRubros")).toString(),
                                                             q.value(rec.indexOf("utilizaDesdeCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaHastaCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaListaPrecio")).toString(),
                                                             q.value(rec.indexOf("utilizaGraficas")).toString(),
                                                             q.value(rec.indexOf("utilizaCuentaBancaria")).toString(),
                                                             q.value(rec.indexOf("utilizaMonedas")).toString(),
                                                             q.value(rec.indexOf("utilizaPais")).toString(),
                                                             q.value(rec.indexOf("utilizaDepartamento")).toString(),
                                                             q.value(rec.indexOf("utilizaLocalidad")).toString(),
                                                             q.value(rec.indexOf("utilizaCoincidenciaCodigoCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaOrdenEnReporte")).toString(),
                                                             q.value(rec.indexOf("utilizaTipoClasificacionCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaListaPrecio2")).toString(),
                                                             q.value(rec.indexOf("utilizaProcedenciaEnReporte")).toString(),
                                                             q.value(rec.indexOf("utilizaAbrirDocumentos")).toString()
                                                             ));
                }
            }
        }
    }
}


void ModuloReportes::buscarReportesSegunMenu(QString campo, QString datoABuscar,QString _codigoPerfil){

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
        QSqlRecord rec;

        if(func_moduloReportesMenu.listaCodigoMenusPorPerfil(_codigoPerfil)==""){

            q = Database::consultaSql("select * from Reportes where "+campo+"'"+datoABuscar+"' order by descripcionReporte");
            rec = q.record();
            ModuloReportes::reset();
            if(q.record().count()>0){

                while (q.next()){
                    ModuloReportes::agregarReportes(Reportes(q.value(rec.indexOf("codigoReporte")).toLongLong()
                                                             , q.value(rec.indexOf("codigoMenuReporte")).toInt()
                                                             , q.value(rec.indexOf("descripcionReporte")).toString()
                                                             , q.value(rec.indexOf("consultaSql")).toString()
                                                             , q.value(rec.indexOf("consultaSqlGraficas")).toString()
                                                             , q.value(rec.indexOf("consultaSqlCabezal")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoProveedor")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaCantidadItemRanking")).toString(),
                                                             q.value(rec.indexOf("utilizaFecha")).toString(),
                                                             q.value(rec.indexOf("utilizaFechaDesde")).toString(),
                                                             q.value(rec.indexOf("utilizaFechaHasta")).toString(),
                                                             q.value(rec.indexOf("utilizaVendedor")).toString(),
                                                             q.value(rec.indexOf("utilizaTipoDocumento")).toString(),
                                                             q.value(rec.indexOf("utilizaSubRubros")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoLiquidacionCaja")).toString(),
                                                             q.value(rec.indexOf("utilizaRubros")).toString(),
                                                             q.value(rec.indexOf("utilizaDesdeCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaHastaCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaListaPrecio")).toString(),
                                                             q.value(rec.indexOf("utilizaGraficas")).toString(),
                                                             q.value(rec.indexOf("utilizaCuentaBancaria")).toString(),
                                                             q.value(rec.indexOf("utilizaMonedas")).toString(),
                                                             q.value(rec.indexOf("utilizaPais")).toString(),
                                                             q.value(rec.indexOf("utilizaDepartamento")).toString(),
                                                             q.value(rec.indexOf("utilizaLocalidad")).toString(),
                                                             q.value(rec.indexOf("utilizaCoincidenciaCodigoCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaOrdenEnReporte")).toString(),
                                                             q.value(rec.indexOf("utilizaTipoClasificacionCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaListaPrecio2")).toString(),
                                                             q.value(rec.indexOf("utilizaProcedenciaEnReporte")).toString(),
                                                             q.value(rec.indexOf("utilizaAbrirDocumentos")).toString()
                                                             ));
                }
            }
        }else{
            q = Database::consultaSql("select RE.* from Reportes RE join ReportesPerfilesUsuarios RPU on RPU.codigoReporte=RE.codigoReporte where "+campo+"'"+datoABuscar+"' and RPU.codigoPerfil='"+_codigoPerfil+"' order by RE.descripcionReporte");

            rec = q.record();
            ModuloReportes::reset();
            if(q.record().count()>0){

                while (q.next()){
                    ModuloReportes::agregarReportes(Reportes(q.value(rec.indexOf("codigoReporte")).toLongLong()
                                                             , q.value(rec.indexOf("codigoMenuReporte")).toInt()
                                                             , q.value(rec.indexOf("descripcionReporte")).toString()
                                                             , q.value(rec.indexOf("consultaSql")).toString()
                                                             , q.value(rec.indexOf("consultaSqlGraficas")).toString()
                                                             , q.value(rec.indexOf("consultaSqlCabezal")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoProveedor")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaCantidadItemRanking")).toString(),
                                                             q.value(rec.indexOf("utilizaFecha")).toString(),
                                                             q.value(rec.indexOf("utilizaFechaDesde")).toString(),
                                                             q.value(rec.indexOf("utilizaFechaHasta")).toString(),
                                                             q.value(rec.indexOf("utilizaVendedor")).toString(),
                                                             q.value(rec.indexOf("utilizaTipoDocumento")).toString(),
                                                             q.value(rec.indexOf("utilizaSubRubros")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoLiquidacionCaja")).toString(),
                                                             q.value(rec.indexOf("utilizaRubros")).toString(),
                                                             q.value(rec.indexOf("utilizaDesdeCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaHastaCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaListaPrecio")).toString(),
                                                             q.value(rec.indexOf("utilizaGraficas")).toString(),
                                                             q.value(rec.indexOf("utilizaCuentaBancaria")).toString(),
                                                             q.value(rec.indexOf("utilizaMonedas")).toString(),
                                                             q.value(rec.indexOf("utilizaPais")).toString(),
                                                             q.value(rec.indexOf("utilizaDepartamento")).toString(),
                                                             q.value(rec.indexOf("utilizaLocalidad")).toString(),
                                                             q.value(rec.indexOf("utilizaCoincidenciaCodigoCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaOrdenEnReporte")).toString(),
                                                             q.value(rec.indexOf("utilizaTipoClasificacionCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaListaPrecio2")).toString(),
                                                             q.value(rec.indexOf("utilizaProcedenciaEnReporte")).toString(),
                                                             q.value(rec.indexOf("utilizaAbrirDocumentos")).toString()
                                                             ));
                }
            }
        }
    }
}




void ModuloReportes::buscarReportesDeBusquedas(QString campo, QString datoABuscar,QString _codigoPerfil, QString _usuario){

    moduloReportesConfiguracion.buscarReportesConfiguracion();



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
        QSqlRecord rec;

        if(func_moduloReportesMenu.listaCodigoMenusPorPerfil(_codigoPerfil)==""){

            q = Database::consultaSql("SELECT RE.* FROM Reportes RE LEFT JOIN ReportesMasUsados u ON RE.codigoReporte = u.codigoReporte  AND u.idUsuario='"+_usuario+"'  where "+campo+"'"+datoABuscar+"' ORDER BY u.cantidad DESC, RE.codigoReporte");


            //qDebug()<< "De Admin: " << q.lastQuery();

            rec = q.record();
            ModuloReportes::reset();
            if(q.record().count()>0){

                while (q.next()){
                    ModuloReportes::agregarReportes(Reportes(q.value(rec.indexOf("codigoReporte")).toLongLong()
                                                             , q.value(rec.indexOf("codigoMenuReporte")).toInt()
                                                             , q.value(rec.indexOf("descripcionReporte")).toString()
                                                             , q.value(rec.indexOf("consultaSql")).toString()
                                                             , q.value(rec.indexOf("consultaSqlGraficas")).toString()
                                                             , q.value(rec.indexOf("consultaSqlCabezal")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoProveedor")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaCantidadItemRanking")).toString(),
                                                             q.value(rec.indexOf("utilizaFecha")).toString(),
                                                             q.value(rec.indexOf("utilizaFechaDesde")).toString(),
                                                             q.value(rec.indexOf("utilizaFechaHasta")).toString(),
                                                             q.value(rec.indexOf("utilizaVendedor")).toString(),
                                                             q.value(rec.indexOf("utilizaTipoDocumento")).toString(),
                                                             q.value(rec.indexOf("utilizaSubRubros")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoLiquidacionCaja")).toString(),
                                                             q.value(rec.indexOf("utilizaRubros")).toString(),
                                                             q.value(rec.indexOf("utilizaDesdeCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaHastaCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaListaPrecio")).toString(),
                                                             q.value(rec.indexOf("utilizaGraficas")).toString(),
                                                             q.value(rec.indexOf("utilizaCuentaBancaria")).toString(),
                                                             q.value(rec.indexOf("utilizaMonedas")).toString(),
                                                             q.value(rec.indexOf("utilizaPais")).toString(),
                                                             q.value(rec.indexOf("utilizaDepartamento")).toString(),
                                                             q.value(rec.indexOf("utilizaLocalidad")).toString(),
                                                             q.value(rec.indexOf("utilizaCoincidenciaCodigoCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaOrdenEnReporte")).toString(),
                                                             q.value(rec.indexOf("utilizaTipoClasificacionCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaListaPrecio2")).toString(),
                                                             q.value(rec.indexOf("utilizaProcedenciaEnReporte")).toString(),
                                                             q.value(rec.indexOf("utilizaAbrirDocumentos")).toString()
                                                             ));
                }
            }
        }else{
          //  q = Database::consultaSql("select RE.* from Reportes RE join ReportesPerfilesUsuarios RPU on RPU.codigoReporte=RE.codigoReporte where "+campo+"'"+datoABuscar+"' and RPU.codigoPerfil='"+_codigoPerfil+"' order by RE.descripcionReporte");


            q = Database::consultaSql("SELECT RE.* FROM Reportes RE join ReportesPerfilesUsuarios RPU on RPU.codigoReporte=RE.codigoReporte LEFT JOIN ReportesMasUsados u ON RE.codigoReporte = u.codigoReporte  AND u.idUsuario='"+_usuario+"'  where "+campo+"'"+datoABuscar+"' and RPU.codigoPerfil='"+_codigoPerfil+"' ORDER BY u.cantidad DESC, RE.codigoReporte;");


            //qDebug()<<    q.lastQuery();

            rec = q.record();
            ModuloReportes::reset();
            if(q.record().count()>0){

                while (q.next()){
                    ModuloReportes::agregarReportes(Reportes(q.value(rec.indexOf("codigoReporte")).toLongLong()
                                                             , q.value(rec.indexOf("codigoMenuReporte")).toInt()
                                                             , q.value(rec.indexOf("descripcionReporte")).toString()
                                                             , q.value(rec.indexOf("consultaSql")).toString()
                                                             , q.value(rec.indexOf("consultaSqlGraficas")).toString()
                                                             , q.value(rec.indexOf("consultaSqlCabezal")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoProveedor")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaCantidadItemRanking")).toString(),
                                                             q.value(rec.indexOf("utilizaFecha")).toString(),
                                                             q.value(rec.indexOf("utilizaFechaDesde")).toString(),
                                                             q.value(rec.indexOf("utilizaFechaHasta")).toString(),
                                                             q.value(rec.indexOf("utilizaVendedor")).toString(),
                                                             q.value(rec.indexOf("utilizaTipoDocumento")).toString(),
                                                             q.value(rec.indexOf("utilizaSubRubros")).toString(),
                                                             q.value(rec.indexOf("utilizaCodigoLiquidacionCaja")).toString(),
                                                             q.value(rec.indexOf("utilizaRubros")).toString(),
                                                             q.value(rec.indexOf("utilizaDesdeCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaHastaCodigoArticulo")).toString(),
                                                             q.value(rec.indexOf("utilizaListaPrecio")).toString(),
                                                             q.value(rec.indexOf("utilizaGraficas")).toString(),
                                                             q.value(rec.indexOf("utilizaCuentaBancaria")).toString(),
                                                             q.value(rec.indexOf("utilizaMonedas")).toString(),
                                                             q.value(rec.indexOf("utilizaPais")).toString(),
                                                             q.value(rec.indexOf("utilizaDepartamento")).toString(),
                                                             q.value(rec.indexOf("utilizaLocalidad")).toString(),
                                                             q.value(rec.indexOf("utilizaCoincidenciaCodigoCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaOrdenEnReporte")).toString(),
                                                             q.value(rec.indexOf("utilizaTipoClasificacionCliente")).toString(),
                                                             q.value(rec.indexOf("utilizaListaPrecio2")).toString(),
                                                             q.value(rec.indexOf("utilizaProcedenciaEnReporte")).toString(),
                                                             q.value(rec.indexOf("utilizaAbrirDocumentos")).toString()
                                                             ));
                }
            }
        }
    }
}





bool ModuloReportes::retornaSiReportaEstaHabilitadoEnPerfil(QString _codigoReporte,QString _codigoPerfil) const {

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }


    if(conexion){

        if(func_moduloReportesMenu.listaCodigoMenusPorPerfil(_codigoPerfil)==""){
            return true;
        }else{
            QSqlQuery query(Database::connect());

            if(query.exec("SELECT * FROM ReportesPerfilesUsuarios where codigoReporte='"+_codigoReporte+"' and codigoPerfil='"+_codigoPerfil+"';")) {
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
        }
    }else{return false;}
}



void ModuloReportes::eliminarReportesPerfil(QString _codigoReporte,QString _codigoPerfil) const{

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

        query.exec("delete from ReportesPerfilesUsuarios where codigoReporte='"+_codigoReporte+"' and codigoPerfil='"+_codigoPerfil+"' ");
    }
}

void ModuloReportes::insertarReportesPerfil(QString _codigoReporte,QString _codigoPerfil) const {

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

        query.exec("REPLACE INTO ReportesPerfilesUsuarios(codigoReporte,codigoPerfil) VALUES('"+_codigoReporte+"','"+_codigoPerfil+"')  ");
    }
}


int ModuloReportes::rowCount(const QModelIndex & parent) const {
    return m_Reportes.count();
}



qlonglong ModuloReportes::retornarCodigoReporte(int indice) const{
                return m_Reportes[indice].codigoReporte();
}
QString ModuloReportes::retornarDescripcionReporte(int indice) const{
                return m_Reportes[indice].descripcionReporte();
}


QVariant ModuloReportes::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Reportes.count()){
        return QVariant();

    }

    const Reportes &variable = m_Reportes[index.row()];

    if (role == CodigoReporteRole){
        return variable.codigoReporte();

    }else if (role == CodigoMenuReporteRole){
        return variable.codigoMenuReporte();

    }else if (role == DescripcionReporteRole){
        return variable.descripcionReporte();

    }else if (role == ConsultaSqlRole){
        return variable.consultaSql();
    }else if (role == ConsultaSqlGraficasRole){
        return variable.consultaSqlGraficas();
    }else if (role == ConsultaSqlCabezalRole){
        return variable.consultaSqlCabezal();
    }
    else if (role == utilizaCodigoClienteRole)
    {
        return variable.utilizaCodigoCliente();
    }
    else if (role == utilizaCodigoProveedorRole)
    {
        return variable.utilizaCodigoProveedor();
    }
    else if (role == utilizaCodigoArticuloRole)
    {
        return variable.utilizaCodigoArticulo();
    }
    else if (role == utilizaCantidadItemRankingRole)
    {
        return variable.utilizaCantidadItemRanking();
    }
    else if (role == utilizaFechaRole)
    {
        return variable.utilizaFecha();
    }
    else if (role == utilizaFechaDesdeRole)
    {
        return variable.utilizaFechaDesde();
    }
    else if (role == utilizaFechaHastaRole)
    {
        return variable.utilizaFechaHasta();
    }
    else if (role == utilizaVendedorRole)
    {
        return variable.utilizaVendedor();
    }
    else if (role == utilizaTipoDocumentoRole)
    {
        return variable.utilizaTipoDocumento();
    }
    else if (role == utilizaSubRubrosRole)
    {
        return variable.utilizaSubRubros();
    }

    else if (role == utilizaCodigoLiquidacionCajaRole)
    {
        return variable.utilizaCodigoLiquidacionCaja();
    }
    else if (role == utilizaRubrosRole)
    {
        return variable.utilizaRubros();
    }
    else if (role == utilizaDesdeCodigoArticuloRole)
    {
        return variable.utilizaDesdeCodigoArticulo();
    }
    else if (role == utilizaHastaCodigoArticuloRole)
    {
        return variable.utilizaHastaCodigoArticulo();
    }
    else if (role == utilizaListaPrecioRole)
    {
        return variable.utilizaListaPrecio();
    }
    else if (role == utilizaGraficasRole)
    {
        return variable.utilizaGraficas();
    }
    else if (role == utilizaCuentaBancariaRole)
    {
        return variable.utilizaCuentaBancaria();
    }
    else if (role == utilizaMonedasRole)
    {
        return variable.utilizaMonedas();
    }
    else if (role == utilizaPaisRole)
    {
        return variable.utilizaPais();
    }
    else if (role == utilizaDepartamentoRole)
    {
        return variable.utilizaDepartamento();
    }

    else if (role == utilizaLocalidadRole)
    {
        return variable.utilizaLocalidad();
    }
    else if (role == utilizaCoincidenciaCodigoClienteRole)
    {
        return variable.utilizaCoincidenciaCodigoCliente();
    }
    else if (role == utilizaOrdenEnReporteRole)
    {
        return variable.utilizaOrdenEnReporte();
    }
    else if (role == utilizaTipoClasificacionClienteRole)
    {
        return variable.utilizaTipoClasificacionCliente();
    }
    else if (role == utilizaListaPrecio2Role)
    {
        return variable.utilizaListaPrecio2();
    }
    else if (role == utilizaProcedenciaEnReporteRole)
    {
        return variable.utilizaProcedenciaEnReporte();
    }
    else if (role == utilizaAbrirDocumentosRole)
    {
        return variable.utilizaAbrirDocumentos();
    }


    return QVariant();
}





bool ModuloReportes::retornaPermisosDelReporte(QString _codigoReporte,QString _permisoReporte) const {


    /* bool _valor=false;

    for (int var = 0; var < m_Reportes.size(); ++var) {
        if(QString::number(m_Reportes[var].codigoReporte())==_codigoReporte){
            if(_permisoReporte=="utilizaCodigoCliente"){
                if(m_Reportes[var].utilizaCodigoCliente()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaCodigoProveedor"){
                if(m_Reportes[var].utilizaCodigoProveedor()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaCodigoArticulo"){
                if(m_Reportes[var].utilizaCodigoArticulo()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaCantidadItemRanking"){
                if(m_Reportes[var].utilizaCantidadItemRanking()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaFecha"){
                if(m_Reportes[var].utilizaFecha()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaFechaDesde"){
                if(m_Reportes[var].utilizaFechaDesde()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaFechaHasta"){
                if(m_Reportes[var].utilizaFechaHasta()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaVendedor"){
                if(m_Reportes[var].utilizaVendedor()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaTipoDocumento"){
                if(m_Reportes[var].utilizaTipoDocumento()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaSubRubros"){
                if(m_Reportes[var].utilizaSubRubros()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaCodigoLiquidacionCaja"){
                if(m_Reportes[var].utilizaCodigoLiquidacionCaja()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaRubros"){
                if(m_Reportes[var].utilizaRubros()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaDesdeCodigoArticulo"){
                if(m_Reportes[var].utilizaDesdeCodigoArticulo()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaHastaCodigoArticulo"){
                if(m_Reportes[var].utilizaHastaCodigoArticulo()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaListaPrecio"){
                if(m_Reportes[var].utilizaListaPrecio()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaGraficas"){
                if(m_Reportes[var].utilizaGraficas()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaCuentaBancaria"){
                if(m_Reportes[var].utilizaCuentaBancaria()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaMonedas"){
                if(m_Reportes[var].utilizaMonedas()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaPais"){
                if(m_Reportes[var].utilizaPais()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaDepartamento"){
                if(m_Reportes[var].utilizaDepartamento()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaLocalidad"){
                if(m_Reportes[var].utilizaLocalidad()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaCoincidenciaCodigoCliente"){
                if(m_Reportes[var].utilizaCoincidenciaCodigoCliente()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaOrdenEnReporte"){
                if(m_Reportes[var].utilizaOrdenEnReporte()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaTipoClasificacionCliente"){
                if(m_Reportes[var].utilizaTipoClasificacionCliente()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaListaPrecio2"){
                if(m_Reportes[var].utilizaListaPrecio2()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaProcedenciaEnReporte"){
                if(m_Reportes[var].utilizaProcedenciaEnReporte()=="1"){_valor=true;}
            }
            else if(_permisoReporte=="utilizaAbrirDocumentos"){
                if(m_Reportes[var].utilizaAbrirDocumentos()=="1"){_valor=true;}
            }

        }
    }

    if(m_Reportes.size()==0 && _valor==false){*/
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

        if(query.exec("select  "+_permisoReporte+"  from Reportes where codigoReporte='"+_codigoReporte+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    if(query.value(0).toString()=="1"){
                        return true;
                    }else{
                        return  false;
                    }
                }else{
                    return false;
                }
            }else{return false;}
        }else{
            return false;
        }
    }else{return false;}
    /* }else{
        return _valor;
    }*/
}

QString ModuloReportes::retornaDescripcionDelReporte(QString _codigoReporte) const {

    /* QString _valor="";
    for (int var = 0; var < m_Reportes.size(); ++var) {
        if(QString::number(m_Reportes[var].codigoReporte())==_codigoReporte){
            _valor = m_Reportes[var].descripcionReporte();
        }
    }

    if(m_Reportes.size()==0 && _valor==""){*/
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

        if(query.exec("select descripcionReporte from Reportes where codigoReporte='"+_codigoReporte+"'")) {
            if(query.first()){
                return query.value(0).toString();
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

QString ModuloReportes::retornaSqlReporte(QString _codigoReporte) const {

    /* QString _valor="";
    for (int var = 0; var < m_Reportes.size(); ++var) {
        if(QString::number(m_Reportes[var].codigoReporte())==_codigoReporte){
            _valor = m_Reportes[var].consultaSql();
        }
    }


    if(m_Reportes.size()==0 && _valor==""){*/
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

        if(query.exec("select consultaSql from Reportes where codigoReporte='"+_codigoReporte+"'")) {
            if(query.first()){
                return query.value(0).toString();
            }else{
                return "";
            }
        }else{
            return "";
        }
    }else{return "";}
    /* }else{
        return _valor;
    }*/

    /*
    */
}
QString ModuloReportes::retornaSqlReporteGraficas(QString _codigoReporte) const {

    /* QString _valor="";
    for (int var = 0; var < m_Reportes.size(); ++var) {
        if(QString::number(m_Reportes[var].codigoReporte())==_codigoReporte){
            _valor = m_Reportes[var].consultaSqlGraficas();
        }
    }

    if(m_Reportes.size()==0 && _valor==""){*/
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

        if(query.exec("select consultaSqlGraficas from Reportes where codigoReporte='"+_codigoReporte+"'")) {
            if(query.first()){
                return query.value(0).toString();
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
}

QString ModuloReportes::retornaSqlReporteCabezal(QString _codigoReporte) const {

    /* QString _valor="";
    for (int var = 0; var < m_Reportes.size(); ++var) {
        if(QString::number(m_Reportes[var].codigoReporte())==_codigoReporte){
            _valor = m_Reportes[var].consultaSqlCabezal();
        }
    }


    if(m_Reportes.size()==0 && _valor==""){*/
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

        if(query.exec("select consultaSqlCabezal from Reportes where codigoReporte='"+_codigoReporte+"'")) {
            if(query.first()){
                return query.value(0).toString();
            }else{
                return "";
            }
        }else{
            return "";
        }
    }else{return "";}
    /* }else{
        return _valor;
    }*/
}

QString ModuloReportes::retornaConfiguracionAlineacionDeColumnaDelReporte(QString _codigoReporte,QString _columnaReporte) const {

    /* QString _valor="-1";
    for (int var = 0; var < moduloReportesConfiguracion.m_ReportesConfiguracion.size(); ++var) {
        if(moduloReportesConfiguracion.m_ReportesConfiguracion[var].codigoReporte()==_codigoReporte && moduloReportesConfiguracion.m_ReportesConfiguracion[var].columnaReporte()==_columnaReporte){

            _valor= moduloReportesConfiguracion.m_ReportesConfiguracion[var].alineacionColumna();

        }
    }

    if(moduloReportesConfiguracion.m_ReportesConfiguracion.size()==0 && _valor=="-1"){*/
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

        if(query.exec("select alineacionColumna from ReportesConfiguracion where codigoReporte='"+_codigoReporte+"' and columnaReporte='"+_columnaReporte+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    return query.value(0).toString();
                }else{
                    return "-1";
                }
            }else{
                return "-1";
            }
        }else{
            return "-1";
        }
    }else{return "-1";}

    /* }else{
        return _valor;
    }*/



}

QString ModuloReportes::retornaConfiguracionTipoDeDatoDeColumnaDelReporte(QString _codigoReporte,QString _columnaReporte) const {

    /* QString _valor="TEXTO";
    for (int var = 0; var < moduloReportesConfiguracion.m_ReportesConfiguracion.size(); ++var) {
        if(moduloReportesConfiguracion.m_ReportesConfiguracion[var].codigoReporte()==_codigoReporte && moduloReportesConfiguracion.m_ReportesConfiguracion[var].columnaReporte()==_columnaReporte){

            _valor= moduloReportesConfiguracion.m_ReportesConfiguracion[var].tipoDatoColumna();

        }
    }

    if(moduloReportesConfiguracion.m_ReportesConfiguracion.size()==0 && _valor=="TEXTO"){*/
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

        if(query.exec("select tipoDatoColumna from ReportesConfiguracion where codigoReporte='"+_codigoReporte+"' and columnaReporte='"+_columnaReporte+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    return query.value(0).toString();
                }else{
                    return "TEXTO";
                }
            }else{
                return "TEXTO";
            }
        }else{
            return "TEXTO";
        }
    }else{return "TEXTO";}
    /* }else{
        return _valor;
    }*/
}

QString ModuloReportes::retornaConfiguracionTotalizadorDeColumnaDelReporte(QString _codigoReporte,QString _columnaReporte) const {

    /*QString _valor="-1";
    for (int var = 0; var < moduloReportesConfiguracion.m_ReportesConfiguracion.size(); ++var) {
        if(moduloReportesConfiguracion.m_ReportesConfiguracion[var].codigoReporte()==_codigoReporte && moduloReportesConfiguracion.m_ReportesConfiguracion[var].columnaReporte()==_columnaReporte){

            _valor= moduloReportesConfiguracion.m_ReportesConfiguracion[var].totalizacionColumna();

        }
    }

    if(moduloReportesConfiguracion.m_ReportesConfiguracion.size()==0 && _valor=="-1"){*/
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

        if(query.exec("select totalizacionColumna from ReportesConfiguracion where codigoReporte='"+_codigoReporte+"' and columnaReporte='"+_columnaReporte+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){
                    return query.value(0).toString();
                }else{
                    return "-1";
                }
            }else{
                return "-1";
            }

        }else{
            return "-1";
        }
    }else{return "-1";}
    /* }else{
        return _valor;
    }*/



}

QString ModuloReportes::generarReporte(QString _consultaSql,QString _codigoReporte, QString _consultaSqlGraficas, bool _incluirGrafica,QString _consultaSqlCabezal) const {


    //qDebug()<<_consultaSqlCabezal;


    int cantidadDecimalesMontoReportes=func_configuracionReportes.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO").toInt(0);

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
        int cantidadLineas=0;
        QStringList listaConsultas = _consultaSql.split(";");


        if(listaConsultas.length()==1 && listaConsultas.at(0).trimmed()=="")
            return "0";


        QFile previewHTML(retornaDirectorioReporteWeb());
        previewHTML.open(QIODevice::WriteOnly);
        QTextStream out(&previewHTML);

        out << "<!DOCTYPE html>";
        out << "\n<html lang=\"es\">";
        out << "\n<head>";
        out << "\n<meta charset=\"UTF-8\"/>";
        out << "\n<title>Reporte</title>";
        out << "\n<link rel=\"stylesheet\" href=\""+retornaDirectorioEstiloCssHTML()+"\">";


        bool _utilizaAbrirDocumentos=retornaPermisosDelReporte(_codigoReporte,"utilizaAbrirDocumentos");

        bool _utilizaGraficas=retornaPermisosDelReporte(_codigoReporte,"utilizaGraficas");
        if(_utilizaGraficas && _incluirGrafica){

            float _cantidadTotalRegistros=0;

            //Los campos en el resultado de la grafica deben ser, value(0) descripcion, values(1) monto o cantidad a mostrar, value(2) simbolo moenda, o sino va vacio; value(3) cantidad de registros.
            //Aca averiguamos la totalidad de registros, para saber cuando es el 100%, así calcular el resto de los porcentajes.
            if(query.exec(_consultaSqlGraficas)) {
                if(query.first()){
                    query.previous();
                    while(query.next()){
                        _cantidadTotalRegistros+=query.value(3).toFloat();
                    }
                }
            }

            out << "\n<script type=\"text/javascript\" src=\""+retornaDirectorioJquery_min_js()+"\"></script>";
            out << "\n<script type=\"text/javascript\">";


            out << "\n$(function () { $('#container').highcharts({";
            out << "\nplotOptions: {";
            out << "\npie: {";
            out << "\nallowPointSelect: true,";
            out << "\ncursor: 'pointer',";
            out << "\ndataLabels: {";
            out << "\nenabled: true,";
            out << "\ncolor: '#000000',";
            out << "\nconnectorColor: '#000000',";
            out << "\nformatter: function() {";
            out << "\n                 return '<b>'+ this.point.name +'</b>: '+ parseFloat(this.percentage).toFixed(2) +' %';";
            out << "\n             }";
            out << "\n         }";
            out << "\n     }";
            out << "\n },";
            out << "\n series: [{";
            out << "\n    type: 'pie',";
            out << "\n    name: '',";
            out << "\n      data: [";



            query.clear();
            bool _primerRegistro=true;
            if(query.exec(_consultaSqlGraficas)) {
                if(query.first()){
                    query.previous();

                    double _sumaDeregistros=0.00;
                    double _porcentajes=0.00;

                    while(query.next()){
                        if(_primerRegistro){

                            _sumaDeregistros+= QString::number((query.value(3).toDouble()*100)/_cantidadTotalRegistros,'f',cantidadDecimalesMontoReportes).toDouble();

                            out << "\n            { name: '"+query.value(0).toString()+" ("+query.value(2).toString()+" "+query.value(1).toString()+" )',y: "+QString::number((query.value(3).toDouble()*100)/_cantidadTotalRegistros,'f',cantidadDecimalesMontoReportes)+", sliced: false,selected: false }";
                            _primerRegistro=false;
                        }else{
                            _sumaDeregistros+= QString::number((query.value(3).toDouble()*100)/_cantidadTotalRegistros,'f',cantidadDecimalesMontoReportes).toDouble();
                            _porcentajes=QString::number((query.value(3).toDouble()*100)/_cantidadTotalRegistros,'f',cantidadDecimalesMontoReportes).toDouble();

                            if((query.at()+1)==query.numRowsAffected()){

                                if(_sumaDeregistros<100){
                                    _porcentajes+=(100-_sumaDeregistros);
                                }else if(_sumaDeregistros>100){
                                    _porcentajes-=(_sumaDeregistros-100);
                                }
                            }
                            out << "\n            ,['"+query.value(0).toString()+" ("+query.value(2).toString()+" "+query.value(1).toString()+" )',   "+QString::number(_porcentajes,'f',cantidadDecimalesMontoReportes)+"]";
                        }
                    }
                }
            }

            out << "\n      ]";
            out << "\n }]";
            out << "\n      });});";

            out <<"function myfunction() {    window.qml.qmlCall();     }";


            out << "</script>";
        }
        out << "\n</head>";
        out << "\n<body>";

        if(_utilizaGraficas && _incluirGrafica){
            out << "\n<script src=\""+retornaDirectorioJs_highcharts_js()+"\"></script>";
            out << "\n<script src=\""+retornaDirectorioJs_modules_exporting_js()+"\"></script>";
        }


        out << "\n<header>";
        out << "\n<h3 id=\"titulo\" align=\"center\">"+retornaDescripcionDelReporte(_codigoReporte)+"</h3>";
        out << "\n</header>";



        if(_consultaSqlCabezal.trimmed()!=""){
            out << "\n<section>";
            out << "\n<article >";

            query.clear();

            //if(query.exec("SET SESSION TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;"+_consultaSqlCabezal.trimmed())){
            if(query.exec(_consultaSqlCabezal.trimmed())){

                query.next();


                int totalquery=query.record().count();

                for(int i=0;i< totalquery;i++)
                    out << "<p   >"+query.value(i).toString()+"<br></p>";


            }
            out << "\n</article>";
            out << "\n</section>";
        }







        int totallistaConsultas=listaConsultas.length()-1;

        for(int j=0; j<totallistaConsultas;j++){

            if(listaConsultas.at(j).trimmed()!=""){

                query.clear();



                if(query.exec(listaConsultas.at(j))) {

                    query.next();
                    //  qDebug()<< QDateTime::currentDateTime();
                    if(query.value(0).toString()!=""){

                        out << "\n<section>";

                        out << "\n<article>";
                        out << "\n<table class=\"rtable \">";
                        //out << "\n<table class=\"rtable\" width=\"100%\" align=\"center\">";

                        out << "\n<thead>";
                        out << "\n<tr>";

                        int totalquery=query.record().count();



                        for(int i=0;i< totalquery;i++){

                            if(query.record().fieldName(i)=="LINK_CLI"){

                            }else{
                                out << "\n<th>"+query.record().fieldName(i)+"</th>";
                            }
                        }

                        out << "\n</tr>";
                        out << "\n</thead>";


                        out << "\n<tbody>";
                        query.previous();

                        while(query.next()){

                            //if(query.record().fieldName(0)=="LINK_CLI"){
                            //    out << "\n<tr hidden>";
                            //}else{
                            out << "\n<tr>";
                            // }


                            cantidadLineas++;

                            int totalquery=query.record().count();


                            for(int j=0;j< totalquery;j++){

                                /*if(query.record().fieldName(j)=="LINK_DOC"){
                                    qDebug()<< query.value(j).toString().split("#");
                                    continue;
                                }else if(query.record().fieldName(j)=="LINK_CLI"){
                                    qDebug()<< query.value(j).toString().split("#");
                                    continue;
                                }*/

                                //qDebug()<<query.record().fieldName(j);


                                QString _alineacion=retornaConfiguracionAlineacionDeColumnaDelReporte(_codigoReporte,QString::number(j));
                                QString _tipoDatoColumna=retornaConfiguracionTipoDeDatoDeColumnaDelReporte(_codigoReporte,QString::number(j));

                                if(_alineacion=="-1" ){
                                    if(_utilizaAbrirDocumentos && j==(totalquery-1)){

                                    }else{
                                        if(_tipoDatoColumna=="TEXTO"){
                                            out << "\n<td>"+query.value(j).toString()+"</td>";
                                        }else if(_tipoDatoColumna=="MONTO"){
                                            out << "\n<td>"+QString::number(query.value(j).toFloat(),'f',cantidadDecimalesMontoReportes)+"</td>";
                                        }
                                    }


                                }else if(_alineacion=="0" ){
                                    if(_utilizaAbrirDocumentos && j==(totalquery-1)){

                                    }else{
                                        if(_tipoDatoColumna=="TEXTO"){
                                            out << "\n<td align=\"left\">"+query.value(j).toString()+"</td>";
                                        }else if(_tipoDatoColumna=="MONTO"){
                                            out << "\n<td align=\"left\">"+QString::number(query.value(j).toFloat(),'f',cantidadDecimalesMontoReportes)+"</td>";
                                        }
                                    }


                                }else if(_alineacion=="1" ){


                                    if(_utilizaAbrirDocumentos && j==(totalquery-1)){

                                    }else{
                                        if(_tipoDatoColumna=="TEXTO"){
                                            out << "\n<td  align=\"center\">"+query.value(j).toString()+"</td>";
                                        }else if(_tipoDatoColumna=="MONTO"){
                                            out << "\n<td  align=\"center\">"+QString::number(query.value(j).toFloat(),'f',cantidadDecimalesMontoReportes)+"</td>";
                                        }
                                    }


                                }else if(_alineacion=="2" ){

                                    if(_utilizaAbrirDocumentos && j==(totalquery-1)){

                                    }else{
                                        if(_tipoDatoColumna=="TEXTO"){
                                            out << "\n<td  align=\"right\">"+query.value(j).toString()+"</td>";
                                        }else if(_tipoDatoColumna=="MONTO"){
                                            out << "\n<td  align=\"right\">"+QString::number(query.value(j).toFloat(),'f',cantidadDecimalesMontoReportes)+"</td>";
                                        }
                                    }

                                }

                            }

                            if(_utilizaAbrirDocumentos){
                                out << "\n<td><input class=\"button-12\" type = \"button\" onclick = \"window.qml.qmlCall('"+query.value(totalquery-1).toString()+"')\" value = \" Abrir \">  </td>";
                            }

                            out << "\n</tr>";


                        }

                        out << "\n</tbody>";


                        out << "\n<tfoot>";
                        out << "\n<tr>";

                        totalquery=query.record().count();

                        for(int k=0;k< totalquery;k++){

                            QString _totalizador=retornaConfiguracionTotalizadorDeColumnaDelReporte(_codigoReporte,QString::number(k));

                            if(_totalizador=="-1" || _totalizador=="0"){
                                out << "\n<th></th>";
                            }else if(_totalizador=="1"){

                                QString _alineacion=retornaConfiguracionAlineacionDeColumnaDelReporte(_codigoReporte,QString::number(k));
                                QString _tipoDatoColumna=retornaConfiguracionTipoDeDatoDeColumnaDelReporte(_codigoReporte,QString::number(k));

                                if(_alineacion=="-1"){
                                    out << "\n<th>";
                                }else if(_alineacion=="0"){
                                    out << "\n<th align=\"left\">";
                                }else if(_alineacion=="1"){
                                    out << "\n<th align=\"center\">";
                                }else if(_alineacion=="2"){
                                    out << "\n<th align=\"right\">";
                                }

                                if(_tipoDatoColumna=="TEXTO"){
                                    out << totalizoSumando(query,k)+"</th>";
                                }else if(_tipoDatoColumna=="MONTO"){
                                    out << QString::number(totalizoSumando(query,k).toFloat(),'f',cantidadDecimalesMontoReportes)+"</th>";
                                }


                            }else if(_totalizador=="2"){

                                QString _alineacion=retornaConfiguracionAlineacionDeColumnaDelReporte(_codigoReporte,QString::number(k));

                                if(_alineacion=="-1"){
                                    out << "\n<th>";
                                }else if(_alineacion=="0"){
                                    out << "\n<th align=\"left\">";
                                }else if(_alineacion=="1"){
                                    out << "\n<th align=\"center\">";
                                }else if(_alineacion=="2"){
                                    out << "\n<th align=\"right\">";
                                }

                                out << totalizoContando(query,k)+"</th>";
                            }

                        }
                        out << "\n</tr>";

                        out << "\n</tfoot>";

                        out << "\n</table>";
                        out << "\n</article>";
                        out << "\n</section>";


                    }else{

                        if(listaConsultas.length()==1 || listaConsultas.length()==2 || listaConsultas.length()==0)
                            return "0";

                    }
                    //  qDebug()<< QDateTime::currentDateTime();
                }else{
                    return "-1";
                }
            }
        }


        if(cantidadLineas==0){
            return "0";
        }

        out << "\n<footer >";


        /// Acá aparecen las graficas
        if(_utilizaGraficas && _incluirGrafica){
            out << "\n<article id=\"container\">";
            out << "\n</article>";
        }



        out << "\n<article>";
        out << "\n<h3 align=\"center\">Cantidad de registros: "+QString::number(cantidadLineas)+"</h3>";
        out << "\n</article>";


        out << "\n</footer>";
        out << "\n</body>";
        out << "\n</html>";

        previewHTML.close();
        return "1";


    }else{return "-1";}
}


QString ModuloReportes::generarReporteXLS(QString _consultaSql,QString _codigoReporte) const {

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
        int cantidadLineas=0;
        QStringList listaConsultas = _consultaSql.split(";");

        if(listaConsultas.length()==1 && listaConsultas.at(0).trimmed()=="")
            return "0";

        BasicExcel planillaXLS;

        planillaXLS.New(listaConsultas.count()-1);

        int totallistaConsultas=listaConsultas.length()-1;

        ///Esto renombra las hojas
        for(int a=0; a<totallistaConsultas;a++){

            QString _reporte="Reporte";
            _reporte.append(QString::number(a+1));



            planillaXLS.RenameWorksheet(a,_reporte.toStdString().c_str());
        }


        //Crea una hoja llamada sheet para manejar su contenido y la vincula a la hoja creada.
        BasicExcelWorksheet* sheet;// = planillaXLS.GetWorksheet("caracter");


        for(int j=0; j<totallistaConsultas;j++){

            sheet = planillaXLS.GetWorksheet(j);

            if(listaConsultas.at(j).trimmed()!=""){

                query.clear();

                if(query.exec(listaConsultas.at(j))) {
                    query.next();

                    if(query.value(0).toString()!=""){


                        int totalquery=query.record().count();
                        /// Escribo el cabezal de la tabla
                        for(int i=0;i< totalquery;i++){

                            sheet->Cell(0,i)->Set(query.record().fieldName(i).replace("ú","u",Qt::CaseInsensitive).replace("á","a",Qt::CaseInsensitive).replace("é","e",Qt::CaseInsensitive).replace("í","i",Qt::CaseInsensitive).replace("ó","o",Qt::CaseInsensitive).replace("ñ","n",Qt::CaseInsensitive).toUpper().toStdString().c_str());


                        }

                        query.previous();

                        int valor=1;

                        while(query.next()){

                            cantidadLineas++;

                            int totalquery=query.record().count();

                            /// Escribo el cuerpo de la tabla
                            for(int j=0;j<totalquery ;j++){

                                QString _tipo = query.value(j).typeName();

                                if(_tipo=="qlonglong" || _tipo=="int" || _tipo=="long"){

                                    sheet->Cell(valor,j)->SetInteger(query.value(j).toLongLong());

                                }else if(_tipo=="QString"){

                                    sheet->Cell(valor,j)->SetString(query.value(j).toString().replace("ú","u",Qt::CaseInsensitive).replace("á","a",Qt::CaseInsensitive).replace("é","e",Qt::CaseInsensitive).replace("í","i",Qt::CaseInsensitive).replace("ó","o",Qt::CaseInsensitive).replace("ñ","n",Qt::CaseInsensitive).toUpper().toStdString().c_str());

                                }else if(_tipo=="QDateTime" || _tipo=="QDate"){

                                    sheet->Cell(valor,j)->SetString(query.value(j).toDateTime().toString("dd/MM/yyyy HH:mm:ss").toStdString().c_str());

                                }else if(_tipo=="double" || _tipo=="float"){


                                    sheet->Cell(valor,j)->SetDouble(query.value(j).toDouble());

                                }else{

                                    sheet->Cell(valor,j)->SetString(query.value(j).toString().replace("ú","u",Qt::CaseInsensitive).replace("á","a",Qt::CaseInsensitive).replace("é","e",Qt::CaseInsensitive).replace("í","i",Qt::CaseInsensitive).replace("ó","o",Qt::CaseInsensitive).replace("ñ","n",Qt::CaseInsensitive).toUpper().toStdString().c_str());


                                }
                            }
                            valor++;
                        }

                        totalquery=query.record().count();

                        for(int k=0;k<totalquery ;k++){

                            QString _totalizador=retornaConfiguracionTotalizadorDeColumnaDelReporte(_codigoReporte,QString::number(k));

                            if(_totalizador=="-1" || _totalizador=="0"){

                            }else if(_totalizador=="1"){

                                QString _tipo = totalizoSumandoXLS(query,k).typeName();

                                if(_tipo=="qlonglong" || _tipo=="int" || _tipo=="long"){


                                    sheet->Cell(valor,k)->SetInteger(totalizoSumando(query,k).toLongLong());

                                }else if(_tipo=="QString" || _tipo=="QDateTime" || _tipo=="QDate"){


                                    sheet->Cell(valor,k)->SetString(totalizoSumando(query,k).replace("ú","u",Qt::CaseInsensitive).replace("á","a",Qt::CaseInsensitive).replace("é","e",Qt::CaseInsensitive).replace("í","i",Qt::CaseInsensitive).replace("ó","o",Qt::CaseInsensitive).replace("ñ","n",Qt::CaseInsensitive).toStdString().c_str());

                                }else if(_tipo=="double" || _tipo=="float"){


                                    sheet->Cell(valor,k)->SetDouble(totalizoSumando(query,k).toDouble());

                                }else{


                                    sheet->Cell(valor,k)->SetString(totalizoSumando(query,k).replace("ú","u",Qt::CaseInsensitive).replace("á","a",Qt::CaseInsensitive).replace("é","e",Qt::CaseInsensitive).replace("í","i",Qt::CaseInsensitive).replace("ó","o",Qt::CaseInsensitive).replace("ñ","n",Qt::CaseInsensitive).toStdString().c_str());

                                }


                            }else if(_totalizador=="2"){

                                sheet->Cell(valor,k)->SetString(totalizoContando(query,k).toStdString().c_str());

                            }
                        }

                    }else{

                        if(listaConsultas.length()==1 || listaConsultas.length()==2 || listaConsultas.length()==0)
                            return "0";
                    }
                }else{
                    return "-1";
                }
            }
        }

        if(cantidadLineas==0){
            return "0";
        }

        planillaXLS.SaveAs(retornaDirectorioReporteXLS(_codigoReporte).trimmed().replace("ú","u",Qt::CaseInsensitive).replace("á","a",Qt::CaseInsensitive).replace("é","e",Qt::CaseInsensitive).replace("í","i",Qt::CaseInsensitive).replace("ó","o",Qt::CaseInsensitive).replace("ñ","n",Qt::CaseInsensitive).toStdString().c_str());
        return "1";


    }else{return "-1";}
}





QString ModuloReportes::totalizoSumando(QSqlQuery query,int _columna) const {

    double total=0;
    query.first();
    query.previous();
    while(query.next()){
        if(_columna==2){
        }
        total+=query.value(_columna).toDouble();
    }
    return QString::number(total);
}

QVariant ModuloReportes::totalizoSumandoXLS(QSqlQuery query,int _columna) const {

    double total=0;
    query.first();
    query.previous();
    while(query.next()){
        if(_columna==2){
        }
        total+=query.value(_columna).toDouble();
    }
    QVariant valor=total;
    return valor;
}
QString ModuloReportes::totalizoContando(QSqlQuery query,int _columna) const {

    int total=0;
    query.first();
    query.previous();
    while(query.next()){

        if(!query.value(_columna).toString().isEmpty() && !query.value(_columna).toString().isNull())
            total+=1;

    }

    return QString::number(total);
}



QString ModuloReportes::generarCSV(QString sqlConsulta,QString _codigoReporte, QString _separadorCSV,QString fecha)const{

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
        QStringList listaConsultas = sqlConsulta.split(";");

        if(listaConsultas.length()==1 && listaConsultas.at(0).trimmed()=="")
            return "0";

        if(query.exec(listaConsultas.at(0))) {
            QString nombreArchivoCSV=retornaDescripcionDelReporte(_codigoReporte)+funcion_reporte.fechaHoraDeHoyTrimeado()+".csv";
            if(_codigoReporte=="82"){

                QString nombreEmpresa=func_configuracionReportes.retornaValorConfiguracion("NOMBRE_EMPRESA");
                QString rutEmpresa=func_cfe_ParametrosGenerales.retornoValorPatrametro("rutEmpresa");

                nombreArchivoCSV=nombreEmpresa.toUpper()+"_"+fecha+"-Anexo2181-"+rutEmpresa+".txt";

                       // TANDICLASS_ABRIL2023-Anexo2181-216039210013.txt
            }


            QString rutaArchivo=retornaDirectorioReporteCSV()+nombreArchivoCSV;

            QFile archivo(rutaArchivo);

            if(archivo.open(QIODevice::WriteOnly)) {
                QTextStream salida(&archivo);

                while(query.next()){

                    int totalquery=query.record().count();

                    /// Escribo el cuerpo del csv
                    for(int j=0;j<totalquery ;j++){

                        salida << query.value(j).toString()<< _separadorCSV;

                    }
                    salida<< "\n";
                }
                archivo.close();
                return "1";

            }else{
                // No se puede grabar el archivo csv
                return "-1";
            }

        }else{
            return "0";
        }


    }else{
        return "-1";
    }
}




bool ModuloReportes::imprimirReporteEnPDF(QString _codigoReporte)const{

    QFile previewHTML(retornaDirectorioReporteWeb());
    previewHTML.open(QIODevice::ReadOnly);

    QFile estiloCSS(retornaDirectorioEstiloCssPDF());
    estiloCSS.open(QIODevice::ReadOnly);

    QString const html = QString::fromAscii(previewHTML.readAll());
    QString const estilo = QString::fromAscii(estiloCSS.readAll());

    QTextDocument doc;
    QFont fuente;

    fuente.setPointSize(8);
    doc.setDefaultFont(fuente);
    doc.setDocumentMargin(10);
    doc.setDefaultStyleSheet(estilo);
    doc.setHtml(html);

    QPrinter printer;
    printer.setPageMargins(0,0,0,0,QPrinter::Millimeter);


    if(QDir::rootPath()=="/"){
    }else{
        if(!QDir(QDir::rootPath()+"/Khitomer/Reporte" ).exists()){
            QDir directorio;
            if(!directorio.mkdir(QDir::rootPath()+"/Khitomer/Reporte")){
                return false;
            }
        }
    }

    if(QDir::rootPath()=="/"){
        printer.setOutputFileName(QDir::homePath()+"/"+retornaDescripcionDelReporte(_codigoReporte)+funcion_reporte.fechaHoraDeHoyTrimeado()+".pdf");
    }else{
        printer.setOutputFileName(QDir::rootPath()+"/Khitomer/Reporte/"+retornaDescripcionDelReporte(_codigoReporte)+funcion_reporte.fechaHoraDeHoyTrimeado()+".pdf");
    }

    printer.setOutputFormat(QPrinter::PdfFormat);
    doc.print(&printer);
    return true;

}


QString ModuloReportes::retornaDirectorioReporteCSV()const{

    if(QDir::rootPath()=="/"){
    }else{
        if(!QDir(QDir::rootPath()+"/Khitomer/Reporte" ).exists()){
            QDir directorio;
            if(!directorio.mkdir(QDir::rootPath()+"/Khitomer/Reporte")){

            }
        }
    }

    if(QDir::rootPath()=="/"){
        return QDir::homePath()+"/";
    }else{
        return QDir::rootPath()+"/Khitomer/Reporte/";
    }
}


QString ModuloReportes::retornaDirectorioReporteXLS(QString _codigoReporte)const{

    if(QDir::rootPath()=="/"){
    }else{
        if(!QDir(QDir::rootPath()+"/Khitomer/Reporte" ).exists()){
            QDir directorio;
            if(!directorio.mkdir(QDir::rootPath()+"/Khitomer/Reporte")){

            }
        }
    }

    if(QDir::rootPath()=="/"){
        return QDir::homePath()+"/"+retornaDescripcionDelReporte(_codigoReporte)+funcion_reporte.fechaHoraDeHoyTrimeado()+".xls";
    }else{
        return QDir::rootPath()+"/Khitomer/Reporte/"+retornaDescripcionDelReporte(_codigoReporte)+funcion_reporte.fechaHoraDeHoyTrimeado()+".xls";
    }
}

QString ModuloReportes::retornaDirectorioReporteWeb() const{

    if(QDir::rootPath()=="/"){
        return  QDir::homePath()+"/.config/Khitomer/preview.html";
    }else{
        return  "/Khitomer/preview.html";
    }
}
QString ModuloReportes::retornaDirectorioEstiloCssPDF() const{

    if(QDir::rootPath()=="/"){
        return  "/opt/Khitomer/estiloPDF.css";
    }else{
        return  QDir::rootPath()+"/Khitomer/estiloPDF.css";
    }
}
QString ModuloReportes::retornaDirectorioEstiloCssHTML() const{

    if(QDir::rootPath()=="/"){
        return  "/opt/Khitomer/estilo.css";
    }else{
        return  "estilo.css";
    }
}
QString ModuloReportes::retornaDirectorioJquery_min_js() const{

    if(QDir::rootPath()=="/"){
        return  "/opt/Khitomer/js/jquery.min.js";
    }else{
        return  "js/jquery.min.js";
    }
}
QString ModuloReportes::retornaDirectorioJs_highcharts_js() const{

    if(QDir::rootPath()=="/"){
        return  "/opt/Khitomer/js/highcharts.js";
    }else{
        return  "js/highcharts.js";
    }
}
QString ModuloReportes::retornaDirectorioJs_modules_exporting_js() const{

    if(QDir::rootPath()=="/"){
        return  "/opt/Khitomer/js/modules/exporting.js";
    }else{
        return  "js/modules/exporting.js";
    }
}
void ModuloReportes::abrirNavegadorArchivos()const{
    if(QDir::rootPath()=="/"){
        QDesktopServices::openUrl(QUrl(QDir::homePath()));
    }else{
        QDesktopServices::openUrl(QUrl(QDir::rootPath()+"/Khitomer/Reporte"));
    }
}
bool ModuloReportes::imprimirReporteEnImpresora(QString _impresora)const{



    QFile previewHTML(retornaDirectorioReporteWeb());
    previewHTML.open(QIODevice::ReadOnly);

    QFile estiloCSS(retornaDirectorioEstiloCssPDF());
    estiloCSS.open(QIODevice::ReadOnly);

    QString const html = QString::fromAscii(previewHTML.readAll());
    QString const estilo = QString::fromAscii(estiloCSS.readAll());

    QTextDocument doc;
    QFont fuente;

    fuente.setPointSize(8);
    doc.setDefaultFont(fuente);
    doc.setDocumentMargin(10);
    doc.setDefaultStyleSheet(estilo);
    doc.setHtml(html);

    QPrinter printer;

    printer.setPaperSize(QPrinter::A4);
    printer.setPageSize(QPrinter::A4);

    printer.setOrientation(QPrinter::Portrait);
    printer.setCreator("Khitomer");
    printer.setColorMode(QPrinter::GrayScale);
    printer.setFullPage(true);

    qreal ok=5;

    printer.setPageMargins(ok,ok,ok,ok,QPrinter::Millimeter);



    printer.setPrinterName(_impresora);
    printer.setOutputFormat(QPrinter::NativeFormat);

    doc.print(&printer);
    return true;

}




void ModuloReportes::insertarReportesMasUsados(QString _codigoReporte,QString _idUsuario){


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

        query.exec("INSERT INTO ReportesMasUsados (codigoReporte, idUsuario, cantidad)  VALUES ('"+_codigoReporte+"', '"+_idUsuario+"', 1)  ON DUPLICATE KEY UPDATE cantidad = cantidad + 1;");

    }
}
