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

import QtQuick 1.1
import QtWebKit 1.1
import "Controles"
import "Listas"
import "Listas/Delegates"



Rectangle {
    id: rectPrincipalMantenimientoReportes
    width: 900
    height: 600
    color: "#ffffff"
    radius: 8
    //


    property alias botonGenerarPDFVisible: btnGenerarPDF.visible

    property alias codigoLiquidacionSeleccionada: txtCodigoLiquidacionReporte.textoInputBox
    property alias codigoVendedorLiquidacionSeleccionada: txtVendedorReporte.codigoValorSeleccion
    property alias nombreVendedorLiquidacionSeleccionada: txtVendedorReporte.textoComboBox
    property alias codigoCodigoClienteReporteInputMask: txtCodigoClienteReporte.inputMask
    property alias codigoCodigoProveedorReporteInputMask: txtCodigoProveedorReporte.inputMask
    property string  consultaSqlRealizada: ""
    property string  consultaSqlGraficaRealizada: ""
    property string  consultaSqlCabezalRealizada: ""
    property string codigoReporteRealizado : ""

    property alias codigoArticuloReporteInputMask: txtCodigoArticuloReporte.inputMask



  /*  function randomNumber(from, to) {
       return Math.floor(Math.random(10) * (to - from + 1) + from);
    }*/

    function seleccionarReporte(codigoReporte){

        cbxListaReportes.codigoValorSeleccion=codigoReporte

        txtCodigoClienteReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaCodigoCliente")
        txtCodigoProveedorReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaCodigoProveedor")
        txtCodigoArticuloReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaCodigoArticulo")
        txtCantidadRankingReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaCantidadItemRanking")
        txtFechaReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaFecha")
        txtFechaDesdeReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaFechaDesde")
        txtFechaHastaReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaFechaHasta")
        txtVendedorReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaVendedor")
        txtTipoDocumentoReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaTipoDocumento")
        cbxSubRubrosReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaSubRubros")
        cbxRubrosReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaRubros")
        txtCodigoLiquidacionReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaCodigoLiquidacionCaja")
        txtDesdeCodigoArticuloReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaDesdeCodigoArticulo")
        txtHastaCodigoArticuloReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaHastaCodigoArticulo")
        cbxListaPrecioReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaListaPrecio")


        cbxListaPrecio2Reporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaListaPrecio2")

        cbxCuentasBancariasReporte.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaCuentaBancaria")
        cbxMonedasReportes.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaMonedas")
        cbxOrdenReportes.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaOrdenEnReporte")
        cbxIncluirGrafica.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaGraficas")        
        cbxDepartamentoRepote.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaLocalidad")
        txtPrincipioCodigoCliente.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaCoincidenciaCodigoCliente")

        cbxTipoClasificacionCliente.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaTipoClasificacionCliente")

        cbxTipoProcedenciaCliente.visible=modeloReportes.retornaPermisosDelReporte(codigoReporte,"utilizaProcedenciaEnReporte")


    }




    function cargarReporte(codigoReporte){

        var consultaSqlPrevia
        var consultaSqlPreviaGrafica
        var consultaSqlPreviaCabezal

        if(codigoReporte!=""){
            cbxListaReportes.codigoValorSeleccion=codigoReporte
            cbxListaReportes.textoComboBox=modeloReportes.retornaDescripcionDelReporte(codigoReporte)


            consultaSqlPrevia=modeloReportes.retornaSqlReporte(codigoReporte)
            consultaSqlPreviaGrafica=modeloReportes.retornaSqlReporteGraficas(codigoReporte)
            consultaSqlPreviaCabezal=modeloReportes.retornaSqlReporteCabezal(codigoReporte)

        }else{
            consultaSqlPrevia=cbxListaReportes.codigoSql.trim()
            consultaSqlPreviaGrafica=cbxListaReportes.codigoSqlGraficas.trim()
            consultaSqlPreviaCabezal=cbxListaReportes.codigoSqlCabezal.trim()
        }

        while(consultaSqlPrevia.match("@_codigoCliente")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoCliente",txtCodigoClienteReporte.textoInputBox.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoCliente",txtCodigoClienteReporte.textoInputBox.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoCliente",txtCodigoClienteReporte.textoInputBox.trim())



        }

        while(consultaSqlPrevia.match("@_codigoProveedor")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoProveedor",txtCodigoProveedorReporte.textoInputBox.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoProveedor",txtCodigoProveedorReporte.textoInputBox.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoProveedor",txtCodigoProveedorReporte.textoInputBox.trim())
        }

        while(consultaSqlPrevia.match("@_codigoArticulo")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoArticulo",txtCodigoArticuloReporte.textoInputBox.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoArticulo",txtCodigoArticuloReporte.textoInputBox.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoArticulo",txtCodigoArticuloReporte.textoInputBox.trim())
        }

        while(consultaSqlPrevia.match("@_fecha")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_fecha",txtFechaReporte.textoInputBox.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_fecha",txtFechaReporte.textoInputBox.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_fecha",txtFechaReporte.textoInputBox.trim())
        }

        while(consultaSqlPrevia.match("@_desde")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_desde",txtFechaDesdeReporte.textoInputBox.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_desde",txtFechaDesdeReporte.textoInputBox.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_desde",txtFechaDesdeReporte.textoInputBox.trim())
        }

        while(consultaSqlPrevia.match("@_hasta")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_hasta",txtFechaHastaReporte.textoInputBox.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_hasta",txtFechaHastaReporte.textoInputBox.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_hasta",txtFechaHastaReporte.textoInputBox.trim())
        }

        while(consultaSqlPrevia.match("@_cantidad")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_cantidad",txtCantidadRankingReporte.textoInputBox.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_cantidad",txtCantidadRankingReporte.textoInputBox.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_cantidad",txtCantidadRankingReporte.textoInputBox.trim())
        }

        while(consultaSqlPrevia.match("@_codigoVendedor")){
            if(txtVendedorReporte.codigoValorSeleccion.trim()=="-1" || txtVendedorReporte.codigoValorSeleccion.trim()=="0" || txtVendedorReporte.codigoValorSeleccion.trim()==""){
                consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoVendedor","null")
                consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoVendedor","null")
                consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoVendedor","null")
            }else{
                consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoVendedor",txtVendedorReporte.codigoValorSeleccion.trim())
                consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoVendedor",txtVendedorReporte.codigoValorSeleccion.trim())
                consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoVendedor",txtVendedorReporte.codigoValorSeleccion.trim())
            }
        }

        while(consultaSqlPrevia.match("@_codigoSubRubro")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoSubRubro",cbxSubRubrosReporte.codigoValorSeleccion.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoSubRubro",cbxSubRubrosReporte.codigoValorSeleccion.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoSubRubro",cbxSubRubrosReporte.codigoValorSeleccion.trim())
        }
        while(consultaSqlPrevia.match("@_codigoRubro")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoRubro",cbxRubrosReporte.codigoValorSeleccion.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoRubro",cbxRubrosReporte.codigoValorSeleccion.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoRubro",cbxRubrosReporte.codigoValorSeleccion.trim())
        }

        while(consultaSqlPrevia.match("@_codigoDocumento")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoDocumento",txtTipoDocumentoReporte.codigoValorSeleccion.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoDocumento",txtTipoDocumentoReporte.codigoValorSeleccion.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoDocumento",txtTipoDocumentoReporte.codigoValorSeleccion.trim())
        }

        while(consultaSqlPrevia.match("@_codigoLiquidacionCaja")){
            if(txtCodigoLiquidacionReporte.textoInputBox.trim()!=""){
                consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoLiquidacionCaja",txtCodigoLiquidacionReporte.textoInputBox.trim())
                consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoLiquidacionCaja",txtCodigoLiquidacionReporte.textoInputBox.trim())
                consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoLiquidacionCaja",txtCodigoLiquidacionReporte.textoInputBox.trim())
            }else{
                consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoLiquidacionCaja","null")
                consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoLiquidacionCaja","null")
                consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoLiquidacionCaja","null")
            }
        }

        while(consultaSqlPrevia.match("@_ArticulodesdeCodigoArticulo")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_ArticulodesdeCodigoArticulo",txtDesdeCodigoArticuloReporte.textoInputBox.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_ArticulodesdeCodigoArticulo",txtDesdeCodigoArticuloReporte.textoInputBox.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_ArticulodesdeCodigoArticulo",txtDesdeCodigoArticuloReporte.textoInputBox.trim())
        }

        while(consultaSqlPrevia.match("@_ArticulohastaCodigoArticulo")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_ArticulohastaCodigoArticulo",txtHastaCodigoArticuloReporte.textoInputBox.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_ArticulohastaCodigoArticulo",txtHastaCodigoArticuloReporte.textoInputBox.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_ArticulohastaCodigoArticulo",txtHastaCodigoArticuloReporte.textoInputBox.trim())
        }

        while(consultaSqlPrevia.match("@_codigoListaPrecio")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoListaPrecio",cbxListaPrecioReporte.codigoValorSeleccion.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoListaPrecio",cbxListaPrecioReporte.codigoValorSeleccion.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoListaPrecio",cbxListaPrecioReporte.codigoValorSeleccion.trim())
        }

        while(consultaSqlPrevia.match("@_codigoLista2Precio")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoLista2Precio",cbxListaPrecio2Reporte.codigoValorSeleccion.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoLista2Precio",cbxListaPrecio2Reporte.codigoValorSeleccion.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoLista2Precio",cbxListaPrecio2Reporte.codigoValorSeleccion.trim())
        }


        while(consultaSqlPrevia.match("@_numeroCuentaBancaria")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_numeroCuentaBancaria",cbxCuentasBancariasReporte.codigoValorSeleccion.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_numeroCuentaBancaria",cbxCuentasBancariasReporte.codigoValorSeleccion.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_numeroCuentaBancaria",cbxCuentasBancariasReporte.codigoValorSeleccion.trim())
        }
        while(consultaSqlPrevia.match("@_numeroBancoCuentaBancaria")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_numeroBancoCuentaBancaria",cbxCuentasBancariasReporte.codigoValorSeleccion2.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_numeroBancoCuentaBancaria",cbxCuentasBancariasReporte.codigoValorSeleccion2.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_numeroBancoCuentaBancaria",cbxCuentasBancariasReporte.codigoValorSeleccion2.trim())
        }
        while(consultaSqlPrevia.match("@_codigoMonedaReporte")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoMonedaReporte",cbxMonedasReportes.codigoValorSeleccion.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoMonedaReporte",cbxMonedasReportes.codigoValorSeleccion.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoMonedaReporte",cbxMonedasReportes.codigoValorSeleccion.trim())
        }
        while(consultaSqlPrevia.match("@_codigoOrdenReporte")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoOrdenReporte",cbxOrdenReportes.codigoValorSeleccion.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoOrdenReporte",cbxOrdenReportes.codigoValorSeleccion.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoOrdenReporte",cbxOrdenReportes.codigoValorSeleccion.trim())
        }
        while(consultaSqlPrevia.match("@_codigoClasificacionClienteReporte")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoClasificacionClienteReporte",cbxTipoClasificacionCliente.codigoValorSeleccion.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoClasificacionClienteReporte",cbxTipoClasificacionCliente.codigoValorSeleccion.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoClasificacionClienteReporte",cbxTipoClasificacionCliente.codigoValorSeleccion.trim())
        }

        while(consultaSqlPrevia.match("@_codigoProcedenciaClienteReporte")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoProcedenciaClienteReporte",cbxTipoProcedenciaCliente.codigoValorSeleccion.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoProcedenciaClienteReporte",cbxTipoProcedenciaCliente.codigoValorSeleccion.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoProcedenciaClienteReporte",cbxTipoProcedenciaCliente.codigoValorSeleccion.trim())
        }




        while(consultaSqlPrevia.match("@_codigoLocalidadPais")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoLocalidadPais",cbxDepartamentoRepote.codigoDePaisSeleccionado.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoLocalidadPais",cbxDepartamentoRepote.codigoDePaisSeleccionado.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoLocalidadPais",cbxDepartamentoRepote.codigoDePaisSeleccionado.trim())
        }
        while(consultaSqlPrevia.match("@_codigoLocalidadDepartamento")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_codigoLocalidadDepartamento",cbxDepartamentoRepote.codigoDeDepartamentoSeleccionado.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_codigoLocalidadDepartamento",cbxDepartamentoRepote.codigoDeDepartamentoSeleccionado.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_codigoLocalidadDepartamento",cbxDepartamentoRepote.codigoDeDepartamentoSeleccionado.trim())
        }

        while(consultaSqlPrevia.match("@_principioCodigoDelCliente")){
            consultaSqlPrevia=consultaSqlPrevia.replace("@_principioCodigoDelCliente",txtPrincipioCodigoCliente.textoInputBox.trim())
            consultaSqlPreviaGrafica=consultaSqlPreviaGrafica.replace("@_principioCodigoDelCliente",txtPrincipioCodigoCliente.textoInputBox.trim())
            consultaSqlPreviaCabezal=consultaSqlPreviaCabezal.replace("@_principioCodigoDelCliente",txtPrincipioCodigoCliente.textoInputBox.trim())
        }



        var estadoGeneracionReporte=modeloReportes.generarReporte(consultaSqlPrevia,cbxListaReportes.codigoValorSeleccion.trim(),consultaSqlPreviaGrafica,cbxIncluirGrafica.chekActivo,consultaSqlPreviaCabezal);

        txtMensajeInformacionReportes.visible=true
        txtMensajeInformacionTimer.stop()
        txtMensajeInformacionTimer.start()

        if(estadoGeneracionReporte=="1"){

            botonNuevoReporteEnWebview.visible=false
            botonAbrirCarpetaReportes.visible=true
            txtNuevoReporte.visible=false

            web_view1.url="file://"+modeloReportes.retornaDirectorioReporteWeb()
            web_view1.reload.trigger()
            txtMensajeInformacionReportes.color="#2f71a0"
            txtMensajeInformacionReportes.text="Reporte generado correctamente."
            consultaSqlRealizada=consultaSqlPrevia
            consultaSqlGraficaRealizada=consultaSqlPreviaGrafica
            consultaSqlCabezalRealizada=consultaSqlPreviaCabezal
            codigoReporteRealizado=cbxListaReportes.codigoValorSeleccion.trim()

        }else if(estadoGeneracionReporte=="0"){

            txtMensajeInformacionReportes.color="#d93e3e"
            txtMensajeInformacionReportes.text="El reporte se genero con 0 información. Por lo tanto no se mostrara."

        }else if(estadoGeneracionReporte=="-1"){

            txtMensajeInformacionReportes.color="#d93e3e"
            txtMensajeInformacionReportes.text="ATENCION: No se pudo generar el reporte, comuniquese con el administrador."

        }
    }



    function cargarReporteXLS(){

        var consultaSqlPrevia=consultaSqlRealizada

        var estadoGeneracionReporte=modeloReportes.generarReporteXLS(consultaSqlPrevia,codigoReporteRealizado);

        txtMensajeInformacionReportes.visible=true
        txtMensajeInformacionTimer.stop()
        txtMensajeInformacionTimer.start()

        if(estadoGeneracionReporte=="1"){

            txtMensajeInformacionReportes.color="#2f71a0"
            txtMensajeInformacionReportes.text="XLS generado correctamente."

        }else if(estadoGeneracionReporte=="0"){

            txtMensajeInformacionReportes.color="#d93e3e"
            txtMensajeInformacionReportes.text="El XLS no se pudo generar por falta de datos."

        }else if(estadoGeneracionReporte=="-1"){

            txtMensajeInformacionReportes.color="#d93e3e"
            txtMensajeInformacionReportes.text="ATENCION: No se pudo generar el XLS, comuniquese con el administrador."

        }
    }


    Rectangle {
        id: rectContenedorReportes
        x: 0
        y: 30
        color: "#494747"
        radius: 8
        z: 2
        //
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 30
        anchors.fill: parent

        Flow {
            id: flow1
            height: flow1.implicitHeight
            z: 1
            spacing: 3
            anchors.right: cbListaImpresorasReportes.left
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 10

            TextInputP {
                id: txtCodigoClienteReporte             
                width: 150
                visible: false
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                botonBuscarTextoVisible: false
                inputMask: "000000;"
                largoMaximo: 6
                botonBorrarTextoVisible: true
                textoTitulo: "Código cliente:"
                tamanioRectPrincipalCombobox: 285
                botonNuevoTexto: "Nuevo cliente..."
                utilizaListaDesplegable: true
                textoTituloFiltro: "Buscar por: dirección, nombre, razon o rut"
                listviewModel:modeloClientesFiltros
                botonNuevoVisible: {
                    if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarClientes") && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearClientes")){
                        true
                    }else{
                        false
                    }
                }
                listviewDelegate: Delegate_ListaClientesFiltros{
                    onSenialAlAceptarOClick: {
                        txtCodigoClienteReporte.textoInputBox=codigoValorSeleccion
                        txtCodigoClienteReporte.tomarElFocoP()
                        txtCodigoClienteReporte.cerrarComboBox()
                    }
                    onKeyEscapeCerrar: {
                        txtCodigoClienteReporte.tomarElFocoP()
                        txtCodigoClienteReporte.cerrarComboBox()
                    }
                }
                onClicBotonNuevoItem: {
                    mostrarMantenimientos(1,"derecha")
                }
                onClicEnBusquedaFiltro: {
                    var consultaSqlCliente=" (razonSocial rlike '"+textoAFiltrar+"' or direccion rlike '"+textoAFiltrar+"' or rut rlike '"+textoAFiltrar+"' or nombreCliente rlike '"+textoAFiltrar+"') and Clientes.tipoCliente=";
                    modeloClientesFiltros.clearClientes()
                    modeloClientesFiltros.buscarCliente(consultaSqlCliente,"1")
                    if(modeloClientesFiltros.rowCount()!=0){
                        tomarElFocoResultado()
                    }
                }

            }

            TextInputP {
                id: txtCodigoProveedorReporte
                width: 150
                visible: false
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                botonBuscarTextoVisible: false
                inputMask: "000000;"
                botonBorrarTextoVisible: true
                largoMaximo: 6
                textoTitulo: "Código proveedor:"
                tamanioRectPrincipalCombobox: 285
                botonNuevoTexto: "Nuevo proveedor..."
                utilizaListaDesplegable: true
                textoTituloFiltro: "Buscar por: dirección, nombre, razon o rut"
                listviewModel:modeloClientesFiltrosProveedor
                botonNuevoVisible: {
                    if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarClientes") && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearClientes")){
                        true
                    }else{
                        false
                    }
                }
                listviewDelegate: Delegate_ListaClientesFiltros{
                    onSenialAlAceptarOClick: {
                        txtCodigoProveedorReporte.textoInputBox=codigoValorSeleccion
                        txtCodigoProveedorReporte.tomarElFocoP()
                        txtCodigoProveedorReporte.cerrarComboBox()
                    }
                    onKeyEscapeCerrar: {
                        txtCodigoProveedorReporte.tomarElFocoP()
                        txtCodigoProveedorReporte.cerrarComboBox()
                    }
                }
                onClicBotonNuevoItem: {
                    mostrarMantenimientos(1,"derecha")
                }
                onClicEnBusquedaFiltro: {
                    var consultaSqlCliente=" (razonSocial rlike '"+textoAFiltrar+"' or direccion rlike '"+textoAFiltrar+"' or rut rlike '"+textoAFiltrar+"' or nombreCliente rlike '"+textoAFiltrar+"') and Clientes.tipoCliente=";
                    modeloClientesFiltrosProveedor.clearClientes()
                    modeloClientesFiltrosProveedor.buscarCliente(consultaSqlCliente,"2")
                    if(modeloClientesFiltrosProveedor.rowCount()!=0){
                        tomarElFocoResultado()
                    }
                }

            }

            TextInputP {
                id: txtCodigoArticuloReporte
                width: 300
                visible: false
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                botonBuscarTextoVisible: false
                textoDeFondo: ""
                largoMaximo: 30
                botonBorrarTextoVisible: true
                textoTitulo: "Código artículo:"
                tamanioRectPrincipalCombobox: 320
                botonNuevoTexto: "Nuevo artículo..."
                utilizaListaDesplegable: true
                checkBoxActivoVisible: true
                checkBoxActivoTexto: "Incluir artículos inactivos"
                textoTituloFiltro: "Buscar por: descripción, proveedor, iva o moneda"                
                tamanioRectPrincipalComboboxAlto: {
                    if(checkBoxActivoVisible){
                        400
                    }else{
                        300
                    }
                }
                botonNuevoVisible:{
                    if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos") && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearArticulos")){
                        true
                    }else{
                        false
                    }
                }
                listviewModel:modeloArticulosFiltros
                listviewDelegate: Delegate_ListaArticulosFiltros{
                    permiteOperarConArticulosInactivos: true
                    onSenialAlAceptarOClick: {
                        txtCodigoArticuloReporte.textoInputBox=codigoValorSeleccion
                        txtCodigoArticuloReporte.tomarElFocoP()
                        txtCodigoArticuloReporte.cerrarComboBox()
                    }
                    onKeyEscapeCerrar: {
                        txtCodigoArticuloReporte.tomarElFocoP()
                        txtCodigoArticuloReporte.cerrarComboBox()
                    }
                }
                onClicBotonNuevoItem: {
                    mostrarMantenimientos(2,"derecha")
                }
                onClicEnBusquedaFiltro: {

                    var consultaSqlArticulo="";
                    if(!checkBoxActivoEstado){
                        consultaSqlArticulo="  ((Clientes.razonSocial rlike '"+textoAFiltrar+"'  or Clientes.nombreCliente rlike '"+textoAFiltrar+"')  or codigoIva=(SELECT codigoIva FROM Ivas where descripcionIva rlike '"+textoAFiltrar+"' limit 1)  or codigoMoneda=(SELECT codigoMoneda FROM Monedas where descripcionMoneda rlike '"+textoAFiltrar+"' limit 1) or descripcionExtendida rlike '"+textoAFiltrar+"' or descripcionArticulo rlike'"+textoAFiltrar+"') and Articulos.activo=";
                    }else{
                        consultaSqlArticulo="  ((Clientes.razonSocial rlike '"+textoAFiltrar+"'  or Clientes.nombreCliente rlike '"+textoAFiltrar+"')  or codigoIva=(SELECT codigoIva FROM Ivas where descripcionIva rlike '"+textoAFiltrar+"' limit 1)  or codigoMoneda=(SELECT codigoMoneda FROM Monedas where descripcionMoneda rlike '"+textoAFiltrar+"' limit 1) or descripcionExtendida rlike '"+textoAFiltrar+"' or descripcionArticulo rlike'"+textoAFiltrar+"') and Articulos.activo=0 or Articulos.activo=";
                    }

                    modeloArticulosFiltros.clearArticulos()
                    modeloArticulosFiltros.buscarArticulo(consultaSqlArticulo,"1",0)

                    if(modeloArticulosFiltros.rowCount()!=0){
                        tomarElFocoResultado()
                    }
                }
            }





            TextInputSimple {
                id: txtFechaReporte
                x: 35
                y: 100
             //   width: 130
                visible: false
                enFocoSeleccionarTodo: true
                textoInputBox: funcionesmysql.fechaDeHoy()
                validaFormato: validacionFecha
                botonBuscarTextoVisible: false
                inputMask: "nnnn-nn-nn; "
                textoTitulo: "Fecha:"
            }
            RegExpValidator{
                id:validacionFecha
                ///Fecha AAAA/MM/DD

                regExp: new RegExp("(20|  |2 | 2)(0[0-9, ]| [0-9, ]|1[0123456789 ]|2[0123456789 ]|3[0123456789 ]|4[0123456789 ])\-(0[1-9, ]| [1-9, ]|1[012 ]| [012 ])\-(0[1-9, ]| [1-9, ]|[12 ][0-9, ]|3[01 ]| [01 ])")
            }



            TextInputSimple {
                id: txtFechaDesdeReporte
                x: 35
                y: 107
             //   width: 130
                visible: false
                enFocoSeleccionarTodo: true
                textoInputBox: funcionesmysql.fechaDeHoy()
                validaFormato: validacionFecha
                botonBuscarTextoVisible: false
                inputMask: "nnnn-nn-nn; "
                textoTitulo: "Desde fecha:"
                onTabulacion: {
                    if(txtFechaHastaReporte.visible)
                    txtFechaHastaReporte.tomarElFoco()
                }
                onEnter: {
                    if(txtFechaHastaReporte.visible)
                    txtFechaHastaReporte.tomarElFoco()
                }
            }

            TextInputSimple {
                id: txtFechaHastaReporte
                x: 40
                y: 98
             //   width: 130
                visible: false
                enFocoSeleccionarTodo: true
                textoInputBox: funcionesmysql.fechaDeHoy()
                validaFormato: validacionFecha
                botonBuscarTextoVisible: false
                inputMask: "nnnn-nn-nn; "
                textoTitulo: "Hasta fecha:"
                onTabulacion: {
                    if(txtDesdeCodigoArticuloReporte.visible){
                        txtDesdeCodigoArticuloReporte.tomarElFoco()
                    }else if(txtFechaDesdeReporte.visible){
                        txtFechaDesdeReporte.tomarElFoco()
                    }
                }
                onEnter: {
                    if(txtDesdeCodigoArticuloReporte.visible){
                        txtDesdeCodigoArticuloReporte.tomarElFoco()
                    }else if(txtFechaDesdeReporte.visible){
                        txtFechaDesdeReporte.tomarElFoco()
                    }
                }
            }


            ComboBoxListaVendedores {
                id: txtVendedorReporte
                width: 170
                visible: false
                textoComboBox: ""
                botonBuscarTextoVisible: false
                textoTitulo: "Vendedor:"
                z: 2
            }
            TextInputSimple {
                id: txtCantidadRankingReporte
                x: 4
                y: 2
              //  width: 110
                visible: false
                enFocoSeleccionarTodo: true
                textoInputBox: "10"
                botonBuscarTextoVisible: false
                inputMask: "000;"
                largoMaximo: 3
                textoDeFondo: ""
                textoTitulo: "Cantidad:"
                colorDeTitulo: "#dbd8d8"
            }

            ComboBoxListaTipoDocumentos {
                id: txtTipoDocumentoReporte
                width: 260
                z: 3
                visible: false
                codigoValorSeleccion: ""
                botonBuscarTextoVisible: false
                textoTitulo: "Documento:"
            }
            ComboBoxListaSubRubrosXRubros {
                id: cbxSubRubrosReporte
                width: 230
                textoComboBox: ""
                visible: false
                botonBuscarTextoVisible: false
                textoTitulo: "Sub rubros:"
                z: 2
            }

            TextInputSimple {
                id: txtCodigoLiquidacionReporte
              //  width: 120
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                visible: false
                botonBuscarTextoVisible: false
                inputMask: "000000;"
                largoMaximo: 6
                botonBorrarTextoVisible: true
                textoTitulo: "Código caja/liquidación:"
            }

            ComboBoxListaRubros {
                id: cbxRubrosReporte
                width: 230
                textoComboBox: ""
                visible: false
                botonBuscarTextoVisible: false
                textoTitulo: "Rubros:"
                z: 2
            }
/*
            TextInputSimple {
                id: txtDesdeCodigoArticuloReporte
                onEnter: txtHastaCodigoArticuloReporte.tomarElFoco()
                onTabulacion: txtHastaCodigoArticuloReporte.tomarElFoco()
            }*/


            TextInputP {
                id: txtDesdeCodigoArticuloReporte
                width: 300
                z: 5
                visible: false
                inputMask: txtCodigoArticuloReporte.inputMask
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                botonBuscarTextoVisible: false
                textoDeFondo: ""
                largoMaximo: 30
                botonBorrarTextoVisible: true
                textoTitulo: "Desde código artículo:"
                tamanioRectPrincipalCombobox: 320
                botonNuevoTexto: "Nuevo artículo..."
                utilizaListaDesplegable: true
                checkBoxActivoVisible: true
                checkBoxActivoTexto: "Incluir artículos inactivos"
                textoTituloFiltro: "Buscar por: descripción, proveedor, iva o moneda"
                onEnter: txtHastaCodigoArticuloReporte.tomarElFocoP()
                onTabulacion: txtHastaCodigoArticuloReporte.tomarElFocoP()
                tamanioRectPrincipalComboboxAlto: {
                    if(checkBoxActivoVisible){
                        400
                    }else{
                        300
                    }
                }
                botonNuevoVisible:{
                    if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos") && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearArticulos")){
                        true
                    }else{
                        false
                    }
                }
                listviewModel:modeloArticulosFiltros
                listviewDelegate: Delegate_ListaArticulosFiltros{
                    permiteOperarConArticulosInactivos: true
                    onSenialAlAceptarOClick: {
                        txtDesdeCodigoArticuloReporte.textoInputBox=codigoValorSeleccion
                        txtDesdeCodigoArticuloReporte.tomarElFocoP()
                        txtDesdeCodigoArticuloReporte.cerrarComboBox()
                    }
                    onKeyEscapeCerrar: {
                        txtDesdeCodigoArticuloReporte.tomarElFocoP()
                        txtDesdeCodigoArticuloReporte.cerrarComboBox()
                    }
                }
                onClicBotonNuevoItem: {
                    mostrarMantenimientos(2,"derecha")
                }
                onClicEnBusquedaFiltro: {

                    var consultaSqlArticulo="";
                    if(!checkBoxActivoEstado){
                        consultaSqlArticulo="  ((Clientes.razonSocial rlike '"+textoAFiltrar+"'  or Clientes.nombreCliente rlike '"+textoAFiltrar+"')  or codigoIva=(SELECT codigoIva FROM Ivas where descripcionIva rlike '"+textoAFiltrar+"' limit 1)  or codigoMoneda=(SELECT codigoMoneda FROM Monedas where descripcionMoneda rlike '"+textoAFiltrar+"' limit 1) or descripcionExtendida rlike '"+textoAFiltrar+"' or descripcionArticulo rlike'"+textoAFiltrar+"') and Articulos.activo=";
                    }else{
                        consultaSqlArticulo="  ((Clientes.razonSocial rlike '"+textoAFiltrar+"'  or Clientes.nombreCliente rlike '"+textoAFiltrar+"')  or codigoIva=(SELECT codigoIva FROM Ivas where descripcionIva rlike '"+textoAFiltrar+"' limit 1)  or codigoMoneda=(SELECT codigoMoneda FROM Monedas where descripcionMoneda rlike '"+textoAFiltrar+"' limit 1) or descripcionExtendida rlike '"+textoAFiltrar+"' or descripcionArticulo rlike'"+textoAFiltrar+"') and Articulos.activo=0 or Articulos.activo=";
                    }

                    modeloArticulosFiltros.clearArticulos()
                    modeloArticulosFiltros.buscarArticulo(consultaSqlArticulo,"1",0)

                    if(modeloArticulosFiltros.rowCount()!=0){
                        tomarElFocoResultado()
                    }
                }
            }



            TextInputP {
                id: txtHastaCodigoArticuloReporte
                width: 300
                z: 4
                visible: false
                inputMask: txtCodigoArticuloReporte.inputMask
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                botonBuscarTextoVisible: false
                textoDeFondo: ""
                largoMaximo: 30
                botonBorrarTextoVisible: true
                textoTitulo: "Hasta código artículo:"
                tamanioRectPrincipalCombobox: 320
                botonNuevoTexto: "Nuevo artículo..."
                utilizaListaDesplegable: true
                checkBoxActivoVisible: true
                checkBoxActivoTexto: "Incluir artículos inactivos"
                textoTituloFiltro: "Buscar por: descripción, proveedor, iva o moneda"
                onEnter: txtDesdeCodigoArticuloReporte.tomarElFocoP()
                onTabulacion: txtDesdeCodigoArticuloReporte.tomarElFocoP()
                tamanioRectPrincipalComboboxAlto: {
                    if(checkBoxActivoVisible){
                        400
                    }else{
                        300
                    }
                }
                botonNuevoVisible:{
                    if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos") && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearArticulos")){
                        true
                    }else{
                        false
                    }
                }
                listviewModel:modeloArticulosFiltros
                listviewDelegate: Delegate_ListaArticulosFiltros{
                    permiteOperarConArticulosInactivos: true
                    onSenialAlAceptarOClick: {
                        txtHastaCodigoArticuloReporte.textoInputBox=codigoValorSeleccion
                        txtHastaCodigoArticuloReporte.tomarElFocoP()
                        txtHastaCodigoArticuloReporte.cerrarComboBox()
                    }
                    onKeyEscapeCerrar: {
                        txtHastaCodigoArticuloReporte.tomarElFocoP()
                        txtHastaCodigoArticuloReporte.cerrarComboBox()
                    }
                }
                onClicBotonNuevoItem: {
                    mostrarMantenimientos(2,"derecha")
                }
                onClicEnBusquedaFiltro: {

                    var consultaSqlArticulo="";
                    if(!checkBoxActivoEstado){
                        consultaSqlArticulo="  ((Clientes.razonSocial rlike '"+textoAFiltrar+"'  or Clientes.nombreCliente rlike '"+textoAFiltrar+"')  or codigoIva=(SELECT codigoIva FROM Ivas where descripcionIva rlike '"+textoAFiltrar+"' limit 1)  or codigoMoneda=(SELECT codigoMoneda FROM Monedas where descripcionMoneda rlike '"+textoAFiltrar+"' limit 1) or descripcionExtendida rlike '"+textoAFiltrar+"' or descripcionArticulo rlike'"+textoAFiltrar+"') and Articulos.activo=";
                    }else{
                        consultaSqlArticulo="  ((Clientes.razonSocial rlike '"+textoAFiltrar+"'  or Clientes.nombreCliente rlike '"+textoAFiltrar+"')  or codigoIva=(SELECT codigoIva FROM Ivas where descripcionIva rlike '"+textoAFiltrar+"' limit 1)  or codigoMoneda=(SELECT codigoMoneda FROM Monedas where descripcionMoneda rlike '"+textoAFiltrar+"' limit 1) or descripcionExtendida rlike '"+textoAFiltrar+"' or descripcionArticulo rlike'"+textoAFiltrar+"') and Articulos.activo=0 or Articulos.activo=";
                    }

                    modeloArticulosFiltros.clearArticulos()
                    modeloArticulosFiltros.buscarArticulo(consultaSqlArticulo,"1",0)

                    if(modeloArticulosFiltros.rowCount()!=0){
                        tomarElFocoResultado()
                    }
                }
            }

            ComboBoxListaPrecios {
                id: cbxListaPrecioReporte
                width: 230
                textoTitulo: "Listas de precio:"
                visible: false
            }

            ComboBoxListaPrecios {
                id: cbxListaPrecio2Reporte
                width: 230
                textoTitulo: "Listas de precio 2:"
                visible: false
            }

            ComboBoxListaCuentasBancarias {
                id: cbxCuentasBancariasReporte
                width: 200
                visible: false
                textoTitulo: "Lista de cuentas bancarias:"
            }

            ComboBoxListaDepartamentos {
                id: cbxDepartamentoRepote
                width: 140
                visible: false
                altoListaDesplegable: 400
                textoTitulo: "Pais/Departamento"
            }

            ComboBoxListaMonedas {
                id: cbxMonedasReportes
                width: 130
                visible: false
                textoTitulo: "Lista de monedas:"
            }

            TextInputSimple {
                id: txtPrincipioCodigoCliente
             //   width: 150
                botonBorrarTextoVisible: true
                textoInputBox: ""
                largoMaximo: 9
                botonBuscarTextoVisible: false
                visible: false
                enFocoSeleccionarTodo: true
                textoTitulo: "1a letra codigo cliente:"
            }

            ComboBoxOrdenReportes {
                id: cbxOrdenReportes
                width: 130
                visible: false
                textoTitulo: "Orden del reporte:"
            }

            ComboBoxListaTipoClasificacion {
                id: cbxTipoClasificacionCliente
                width: 230
                visible: false
                textoTitulo: "Clasificacion cliente"
            }

            ComboBoxListaTipoProcedenciaCliente {
                id: cbxTipoProcedenciaCliente
                width: 230
                visible: false
                textoTitulo: "Procedencia cliente"
            }

        }

        Rectangle{
            id: rectangle2
            color: "#e6e6e6"
            radius: 3
            clip: true
            anchors.top: flow1.bottom
            anchors.topMargin: 60
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 20
            onWidthChanged: {

                web_view1.preferredWidth=rectangle2.width
                flickable.contentWidth=web_view1.implicitWidth

            }
            onHeightChanged: {


                web_view1.preferredHeight=rectangle2.height
                flickable.contentHeight=web_view1.implicitHeight

            }


            Flickable {
                id: flickable
                anchors.bottomMargin: 0
                anchors.topMargin: 0
                anchors.fill: parent
                contentWidth: parent.width
                contentHeight: web_view1.preferredHeight
                interactive: true




                clip: false
                focus: false
                WebView {
                    id: web_view1
                    anchors.bottomMargin: 0
                    anchors.topMargin: 0
                    anchors.fill: parent
                    z: 1
                    focus: false
                    preferredHeight: rectangle2.height
                    preferredWidth: rectangle2.width
                    settings.javaEnabled: true
                    settings.javascriptEnabled: true
                    settings.standardFontFamily: "Arial"
                    settings.defaultFontSize: 13
                    settings.minimumFontSize: 13
                    settings.defaultFixedFontSize: 13
                    smooth: false
                    visible: true                    

                    javaScriptWindowObjects: QtObject {
                        WebView.windowObjectName: "qml"

                        function qmlCall(codigo) {
                            var arrayDeCadenas = codigo.split("-");
                            mantenimientoFactura.cargoFacturaEnMantenimiento(arrayDeCadenas[0],arrayDeCadenas[1],arrayDeCadenas[2])
                        }
                    }


                    /*WebView {
                        javaScriptWindowObjects: QtObject {
                            WebView.windowObjectName: "qml"

                            function qmlCall() {
                                console.log("This call is in QML!");
                            }
                        }
                        html: "<script>window.qml.qmlCall();</script>"
                    }*/

                    enabled: true

                    onLoadFinished: {

                        web_view1.preferredWidth=rectangle2.width
                        web_view1.preferredHeight=rectangle2.height
                        flickable.contentWidth=web_view1.implicitWidth
                        flickable.contentHeight=web_view1.implicitHeight


                    }
                    reload.onTriggered: {

                        web_view1.preferredWidth=rectangle2.width
                        web_view1.preferredHeight=rectangle2.height
                        flickable.contentWidth=web_view1.implicitWidth
                        flickable.contentHeight=web_view1.implicitHeight                        

                    }


                }
            }



            BotonPaletaSistema {
                id: botonNuevoReporteEnWebview
                x: 376
                y: 242
                text: "Nuevo reporte"
                z: 3
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: cbxListaReportes.tomarElFoco()
            }

            Text {
                id: txtNuevoReporte
                x: 101
                y: 188
                color: "#ee900c"
                text: qsTr("Comience a explorar los reportes, dando clic en el botón")
                z: 2
                font.family: "Arial"
                //
                styleColor: "#888282"
                style: Text.Raised
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: true
                anchors.verticalCenterOffset: -80
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 24
            }

            Rectangle {
                id: scrollbar
                anchors.right: flickable.right
                y: flickable.visibleArea.yPosition * flickable.height
                width: 10
                height: flickable.visibleArea.heightRatio * flickable.height
                color: "#000000"
                //radius: height/2 - 1
                //
                opacity: 0.700
                z: 1
                anchors.rightMargin: 2
            }

            Rectangle {
                id: rectangle1
                width: 15
                color: "#ffffff"
                //
                opacity: 0.600
                z: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
            }

            BotonPaletaSistema {
                id: botonAbrirCarpetaReportes
                text: "Abrir carpeta de reportes"
                z: 4
                visible: false
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 20
                onClicked:{


                    modeloReportes.abrirNavegadorArchivos()



                }



            }

            CheckBox {
                id: cbxIncluirGrafica
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.top: parent.top
                anchors.topMargin: 0
                textoValor: "Incluir grafica en reporte"
                visible: false
                z: 4
                onChekActivoChanged: {

                    if(cbxListaReportes.codigoSql!="" && cbxListaReportes.codigoValorSeleccion!="")
                    cargarReporte("")

                }
            }

        }
        ComboBoxListaReportes {
            id: cbxListaReportes
            x: 20
            y: -30
            width: 370
            height: 25
            z: 2
            textoTitulo: ""
            onSenialAlAceptarOClick: {

                seleccionarReporte(cbxListaReportes.codigoValorSeleccion)

            }
        }

        BotonPaletaSistema {
            id: btnCargarReporte
            y: 10
            text: "Visualizar reporte"
            anchors.bottom: rectangle2.top
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            onClicked: {

                if(cbxListaReportes.codigoSql!="" && cbxListaReportes.codigoValorSeleccion!="")
                cargarReporte("")

            }
        }

        BotonPaletaSistema {
            id: btnGenerarPDF
            text: "Exportar PDF"
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.bottom: rectangle2.top
            anchors.bottomMargin: 10
            onClicked:{

                if(web_view1.url!="")
                    modeloReportes.imprimirReporteEnPDF(cbxListaReportes.codigoValorSeleccion)

            }
        }

        BotonPaletaSistema {
            id: btnImprimirEnImpresora
            x: -6
            y: 8
            text: "Imprimir"
            anchors.bottom: rectangle2.top
            anchors.rightMargin: 10
            anchors.bottomMargin: 10
            anchors.right: btnGenerarXls.left
            onClicked: {

                if(web_view1.url!="")
                    modeloReportes.imprimirReporteEnImpresora(cbListaImpresorasReportes.textoComboBox.trim())

            }
        }

        ComboBoxListaImpresoras {
            id: cbListaImpresorasReportes
            x: 636
            y: 444
            width: 200
            textoComboBox: funcionesmysql.impresoraPorDefecto()
            anchors.bottom: rectangle2.top
            anchors.rightMargin: 0
            anchors.bottomMargin: 10
            textoTitulo: "Impresoras:"
            anchors.right: btnImprimirEnImpresora.left
        }

        BotonPaletaSistema {
            id: btnGenerarXls
            text: "Exportar XLS"
            anchors.bottom: rectangle2.top
            anchors.rightMargin: 10
            anchors.bottomMargin: 10
            anchors.right: btnGenerarPDF.left
            onClicked:{

                if(web_view1.url!="")
                    cargarReporteXLS()

            }
        }

    }

    Row {
        id: rowBarraDeHerramientasReportes
        //
        anchors.bottom: rectContenedorReportes.top
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 380
        spacing: distanciaEntreBotonesBarraDeTareas

        BotonBarraDeHerramientas {
            id: botonNuevoReporte
            x: 33
            y: 10
            toolTip: "Nuevo reporte"
            z: 8
            //source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Reportes.png"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Nuevo.png"
            anchors.verticalCenter: parent.verticalCenter
            onClic: {

                txtCodigoClienteReporte.textoInputBox=""
                txtCodigoProveedorReporte.textoInputBox=""
                txtCodigoArticuloReporte.textoInputBox=""
                txtCantidadRankingReporte.textoInputBox=""
                txtFechaReporte.textoInputBox=funcionesmysql.fechaDeHoy()
                txtFechaDesdeReporte.textoInputBox=funcionesmysql.fechaDeHoy()
                txtFechaHastaReporte.textoInputBox=funcionesmysql.fechaDeHoy()
                txtVendedorReporte.codigoValorSeleccion="-1"
                txtVendedorReporte.textoComboBox=""
                txtTipoDocumentoReporte.codigoValorSeleccion="-1"
                txtTipoDocumentoReporte.textoComboBox=""
                cbxSubRubrosReporte.textoComboBox=""
                cbxSubRubrosReporte.codigoValorSeleccion="-1"
                cbxRubrosReporte.textoComboBox=""
                cbxRubrosReporte.codigoValorSeleccion="-1"
                txtCodigoLiquidacionReporte.textoInputBox=""
                txtDesdeCodigoArticuloReporte.textoInputBox=""
                txtHastaCodigoArticuloReporte.textoInputBox=""
                cbxListaPrecioReporte.textoComboBox=""
                cbxListaPrecioReporte.codigoValorSeleccion="-1"

                cbxListaPrecio2Reporte.textoComboBox=""
                cbxListaPrecio2Reporte.codigoValorSeleccion="-1"

                cbxCuentasBancariasReporte.textoComboBox=""
                cbxCuentasBancariasReporte.codigoValorSeleccion="-1"
                cbxCuentasBancariasReporte.codigoValorSeleccion2="-1"
                cbxMonedasReportes.textoComboBox=""
                cbxMonedasReportes.codigoValorSeleccion="-1"                
                cbxOrdenReportes.textoComboBox="Columna 1"
                cbxOrdenReportes.codigoValorSeleccion="1"

                cbxTipoClasificacionCliente.textoComboBox=""
                cbxTipoClasificacionCliente.codigoValorSeleccion="-1"

                cbxTipoProcedenciaCliente.textoComboBox=""
                cbxTipoProcedenciaCliente.codigoValorSeleccion="-1"

                cbxDepartamentoRepote.codigoDePaisSeleccionado="-1"
                cbxDepartamentoRepote.codigoDeDepartamentoSeleccionado="-1"
                cbxDepartamentoRepote.codigoDeLocalidadSeleccionado="-1"
                cbxDepartamentoRepote.textoComboBox=""

                txtPrincipioCodigoCliente.textoInputBox=""

            }
        }

        Text {
            id: txtMensajeInformacionReportes
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            font.family: "Arial"
            visible: false
            font.pixelSize: 14
            styleColor: "white"
            style: Text.Raised
            font.bold: true
            verticalAlignment: Text.AlignTop
            horizontalAlignment: Text.AlignRight
            //
        }
    }
    Timer{
        id:txtMensajeInformacionTimer
        repeat: false
        interval: 5000
        onTriggered: {

            txtMensajeInformacionReportes.visible=false
            txtMensajeInformacionReportes.color="#d93e3e"
        }
    }

    Rectangle {
        id: rectangle4
        x: -4
        y: -1
        width: 10
        color: "#e235dd"
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: rectContenedorReportes.top
        anchors.bottomMargin: -10
        z: 1
        anchors.leftMargin: 0
        anchors.left: parent.left
    }



}
