/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2021>  <Cristian Montano>

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

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import "../Controles"

Rectangle{
    id: rectListaItem
    width: parent.width
    height: 32
    color: "#e9e8e9"
    radius: 1
    border.color: "#aaaaaa"
    smooth: true
    opacity: 1


    Text {
        id:lblTipoDocumento
        text: codigoTipoDocumento + " - "+descripcionTipoDocumento
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.verticalCenter: parent.verticalCenter
        font.family: "Arial"
        opacity: 0.900
        smooth: true
        font.pointSize: 10
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        color: "#212121"
    }

    MouseArea{
        id: mousearea1
        z: 1
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            rectListaItemColorDeseleccionado.stop()
            rectListaItemColorSeleccionado.start()
        }
        onExited: {
            rectListaItemColorSeleccionado.stop()
            rectListaItemColorDeseleccionado.start()
        }
        onClicked: {

            txtCodigoTipoDocumento.textoInputBox=codigoTipoDocumento
            txtDescripcionTipoDocumento.textoInputBox=descripcionTipoDocumento
            if(utilizaArticulos==0){
                chbPermitIngresoDeArticulosTipoDocumentos.setActivo(false)
            }else{
                chbPermitIngresoDeArticulosTipoDocumentos.setActivo(true)
            }
            if(utilizaCodigoBarrasADemanda==0){
                chbUtilizacampoInfoExtendidoTipoDocumentos.setActivo(false)
            }else{
                chbUtilizacampoInfoExtendidoTipoDocumentos.setActivo(true)
            }
            if(utilizaTotales==0){
                chbUtilizaTotalesTipoDocumento.setActivo(false)
            }else{
                chbUtilizaTotalesTipoDocumento.setActivo(true)
            }
            if(utilizaMediosDePago==0){
                chbIngresoMedioDePago.setActivo(false)
            }else{
                chbIngresoMedioDePago.setActivo(true)
            }
            if(utilizaFechaPrecio==0){
                chbModificacionFechaPrecioManual.setActivo(false)
            }else{
                chbModificacionFechaPrecioManual.setActivo(true)
            }
            if(utilizaFechaDocumento==0){
                chbModificacionFechEmisionManual.setActivo(false)
            }else{
                chbModificacionFechEmisionManual.setActivo(true)
            }
            if(utilizaNumeroDocumento==0){
                chbIngredoDeNumeroDeDocumentoManual.setActivo(false)
            }else{
                chbIngredoDeNumeroDeDocumentoManual.setActivo(true)
            }
            if(utilizaSerieDocumento==0){
                chbIngredoDeSerieManual.setActivo(false)
            }else{
                chbIngredoDeSerieManual.setActivo(true)
            }
            txtSerieTipoDocumento.textoInputBox=serieDocumento
            if(utilizaVendedor==0){
                chbUtilizaVendedorParaComisionar.setActivo(false)
            }else{
                chbUtilizaVendedorParaComisionar.setActivo(true)
            }
            if(utilizaCliente==0){
                chbpermiteBuscarClientesYProveedores.setActivo(false)
            }else{
                chbpermiteBuscarClientesYProveedores.setActivo(true)
            }
            if(utilizaTipoCliente==0){
                chbPermiteSeleccionarTipoClienteYProveedor.setActivo(false)
            }else{
                chbPermiteSeleccionarTipoClienteYProveedor.setActivo(true)
            }
            if(utilizaSoloProveedores==0){
                chbPermiteSoloFacturarAProveedores.setActivo(false)
            }else{
                chbPermiteSoloFacturarAProveedores.setActivo(true)
            }

            cbxModoAfectaCuentaCorrienteDinero.codigoValorSeleccion=afectaCuentaCorriente
            if(afectaCuentaCorriente=="0"){
                cbxModoAfectaCuentaCorrienteDinero.textoComboBox=cbxModoAfectaCuentaCorrienteDinero.retornaDescripcion(0)
            }else if(afectaCuentaCorriente=="1"){
                cbxModoAfectaCuentaCorrienteDinero.textoComboBox=cbxModoAfectaCuentaCorrienteDinero.retornaDescripcion(1)
            }else if(afectaCuentaCorriente=="-1"){
                cbxModoAfectaCuentaCorrienteDinero.textoComboBox=cbxModoAfectaCuentaCorrienteDinero.retornaDescripcion(2)
            }

            cbxModoAfectaCuentaCorrienteMercaderia.codigoValorSeleccion=afectaCuentaCorrienteMercaderia
            if(afectaCuentaCorrienteMercaderia=="0"){
                cbxModoAfectaCuentaCorrienteMercaderia.textoComboBox=cbxModoAfectaCuentaCorrienteMercaderia.retornaDescripcion(0)
            }else if(afectaCuentaCorrienteMercaderia=="1"){
                cbxModoAfectaCuentaCorrienteMercaderia.textoComboBox=cbxModoAfectaCuentaCorrienteMercaderia.retornaDescripcion(1)
            }else if(afectaCuentaCorrienteMercaderia=="-1"){
                cbxModoAfectaCuentaCorrienteMercaderia.textoComboBox=cbxModoAfectaCuentaCorrienteMercaderia.retornaDescripcion(2)
            }

            cbxModoAfectaStockTipoDocumento.codigoValorSeleccion=afectaStock
            if(afectaStock=="0"){
                cbxModoAfectaStockTipoDocumento.textoComboBox=cbxModoAfectaStockTipoDocumento.retornaDescripcion(0)
            }else if(afectaStock=="1"){
                cbxModoAfectaStockTipoDocumento.textoComboBox=cbxModoAfectaStockTipoDocumento.retornaDescripcion(1)
            }else if(afectaStock=="-1"){
                cbxModoAfectaStockTipoDocumento.textoComboBox=cbxModoAfectaStockTipoDocumento.retornaDescripcion(2)
            }

            cbxModoAfectaTotalesTipoDocumento.codigoValorSeleccion=afectaTotales
            if(afectaTotales=="0"){
                cbxModoAfectaTotalesTipoDocumento.textoComboBox=cbxModoAfectaTotalesTipoDocumento.retornaDescripcion(0)
            }else if(afectaTotales=="1"){
                cbxModoAfectaTotalesTipoDocumento.textoComboBox=cbxModoAfectaTotalesTipoDocumento.retornaDescripcion(1)
            }else if(afectaTotales=="-1"){
                cbxModoAfectaTotalesTipoDocumento.textoComboBox=cbxModoAfectaTotalesTipoDocumento.retornaDescripcion(2)
            }

            if(utilizaCantidades==0){
                chbCampoDeIngresoDeCantidadTipoDocumento.setActivo(false)
            }else{
                chbCampoDeIngresoDeCantidadTipoDocumento.setActivo(true)
            }
            if(utilizaPrecioManual==0){
                chbCampoIngresoPrecioTipoDocumento.setActivo(false)
            }else{
                chbCampoIngresoPrecioTipoDocumento.setActivo(true)
            }
            if(utilizaDescuentoTotal==0){
                chbUtilizaDescuentosAlTotalTipoDocumentos.setActivo(false)
            }else{
                chbUtilizaDescuentosAlTotalTipoDocumentos.setActivo(true)
            }
            if(emiteEnImpresora==0){
                chbEmitenEnImpresoras.setActivo(false)
            }else{
                chbEmitenEnImpresoras.setActivo(true)
            }

            cbxListaModelosDeImpresion.codigoValorSeleccion=codigoModeloImpresion
            cbxListaModelosDeImpresion.textoComboBox=modeloModelosDeImpresion.retornaDescripcionModeloImpresion(codigoModeloImpresion)

            cbxCantidadCopiasTipoDocumento.codigoValorSeleccion=cantidadCopias
            cbxCantidadCopiasTipoDocumento.textoComboBox=cbxCantidadCopiasTipoDocumento.retornaDescripcion(cantidadCopias)

            if(utilizaObservaciones==0){
                chbUtilizaObservaciones.setActivo(false)
            }else{
                chbUtilizaObservaciones.setActivo(true)
            }
            if(utilizaComentarios==0){
                chbUtilizaComentarios.setActivo(false)
            }else{
                chbUtilizaComentarios.setActivo(true)
            }


            cbxModoAfectaCuentaBancaria.codigoValorSeleccion=afectaCuentaBancaria
            if(afectaCuentaBancaria=="0"){
                cbxModoAfectaCuentaBancaria.textoComboBox=cbxModoAfectaCuentaBancaria.retornaDescripcion(0)
            }else if(afectaCuentaBancaria=="1"){
                cbxModoAfectaCuentaBancaria.textoComboBox=cbxModoAfectaCuentaBancaria.retornaDescripcion(1)
            }else if(afectaCuentaBancaria=="-1"){
                cbxModoAfectaCuentaBancaria.textoComboBox=cbxModoAfectaCuentaBancaria.retornaDescripcion(2)
            }

            if(utilizaCuentaBancaria==0){
                chbUtilizaCuentasBancarias.setActivo(false)
            }else{
                chbUtilizaCuentasBancarias.setActivo(true)
            }
            if(utilizaPagoChequeDiferido==0){
                chbPermitechequesEnCajaParaPagoAProveedores.setActivo(false)
            }else{
                chbPermitechequesEnCajaParaPagoAProveedores.setActivo(true)
            }
            if(utilizaSoloMediosDePagoCheque==0){
                chbUtilizaSoloMedioPagoCheque.setActivo(false)
            }else{
                chbUtilizaSoloMedioPagoCheque.setActivo(true)
            }
            if(imprimeEnFormatoTicket==0){
                chbEmitenEnImpresorasTicket.setActivo(false)
            }else{
                chbEmitenEnImpresorasTicket.setActivo(true)
            }
            if(imprimeObservacionesEnTicket==0){
                chbEmiteObservacionesEnImpresorasTicket.setActivo(false)
            }else{
                chbEmiteObservacionesEnImpresorasTicket.setActivo(true)
            }


            if(esDocumentoDeVenta==0){
                chbEsDocumentoDeVenta.setActivo(false)
            }else{
                chbEsDocumentoDeVenta.setActivo(true)
            }
            txtDescripcionImpresionTipoDocumento.textoInputBox=descripcionTipoDocumentoImpresora

            if(utilizaArticulosInactivos==0){
                chbpermiteOperarConArticulosInactivosTipoDocumento.setActivo(false)
            }else{
                chbpermiteOperarConArticulosInactivosTipoDocumento.setActivo(true)
            }

            if(utilizaRedondeoEnTotal==0){
                chbUtilizaRedondeoDelTotalTipoDocumentos.setActivo(false)
            }else{
                chbUtilizaRedondeoDelTotalTipoDocumentos.setActivo(true)
            }
            if(utilizaPrecioManualEnMonedaReferencia==0){
                chbCampoIngresoPrecioMonedaReferenciaTipoDocumento.setActivo(false)
            }else{
                chbCampoIngresoPrecioMonedaReferenciaTipoDocumento.setActivo(true)
            }
            if(utilizaSeteoDePreciosEnListasDePrecioPorArticulo==0){
                chbSolicitarIngresoPrecioEnListasDePrecioTipoDocumento.setActivo(false)
            }else{
                chbSolicitarIngresoPrecioEnListasDePrecioTipoDocumento.setActivo(true)
            }

            if(noPermiteFacturarConStockPrevistoCero==0){
                chbNoPermiteFacturarConStockPrevistoCero.setActivo(false)
            }else{
                chbNoPermiteFacturarConStockPrevistoCero.setActivo(true)
            }




            txtDescripcionCampoDatosExtraTipoDocumento.textoInputBox=descripcionCodigoBarrasADemanda

            if(utilizaListaPrecioManual==0){
                chbUtilizaListaDePrecioManualTipoDocumentos.setActivo(false)
            }else{
                chbUtilizaListaDePrecioManualTipoDocumentos.setActivo(true)
            }
            if(utilizaFormasDePago==0){
                chbUtilizaFormaDePagoTipoDocumentos.setActivo(false)
            }else{
                chbUtilizaFormaDePagoTipoDocumentos.setActivo(true)
            }
            if(noAfectaIva==0){
                chbNoAfectaElIvaTipoDocumentos.setActivo(false)
            }else{
                chbNoAfectaElIvaTipoDocumentos.setActivo(true)
            }



            txtDescripcionTipoDocumento.tomarElFoco()

        }
    }

    PropertyAnimation{
        id:rectListaItemColorSeleccionado
        target: rectListaItem
        property: "color"
        from: "#e9e8e9"
        to:"#9294C6"
        duration: 100

    }
    PropertyAnimation{
        id:rectListaItemColorDeseleccionado
        target: rectListaItem
        property: "color"
        to: "#e9e8e9"
        from:"#9294C6"
        duration: 50

    }
}
