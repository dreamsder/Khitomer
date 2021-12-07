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
    //
    opacity: 1


    Text {
        id:lblUsuarios
        text: codigoPerfil + " - "+descripcionPerfil
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.verticalCenter: parent.verticalCenter
        font.family: "Arial"
        opacity: 0.900
        //
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

            txtCodigoPerfil.textoInputBox=codigoPerfil
            txtDescripcionPerfil.textoInputBox=descripcionPerfil
            menuPermisos.cargarTipoDocumentos(codigoPerfil)

            if(permiteUsarClientes==0){
                cbxpermiteUsarClientes.setActivo(false)
            }else{
                cbxpermiteUsarClientes.setActivo(true)
            }

            if(permiteCrearClientes==0){
                cbxpermiteCrearClientes.setActivo(false)
            }else{
                cbxpermiteCrearClientes.setActivo(true)
            }

            if(permiteBorrarClientes==0){
                cbxpermiteBorrarClientes.setActivo(false)
            }else{
                cbxpermiteBorrarClientes.setActivo(true)
            }

            if(permiteUsarArticulos==0){
                cbxpermiteUsarArticulos.setActivo(false)
            }else{
                cbxpermiteUsarArticulos.setActivo(true)
            }

            if(permiteUsarArticulos==0){
                cbxpermiteUsarArticulos.setActivo(false)
            }else{
                cbxpermiteUsarArticulos.setActivo(true)
            }

            if(permiteCrearArticulos==0){
                cbxpermiteCrearArticulos.setActivo(false)
            }else{
                cbxpermiteCrearArticulos.setActivo(true)
            }

            if(permiteBorrarArticulos==0){
                cbxpermiteBorrarArticulos.setActivo(false)
            }else{
                cbxpermiteBorrarArticulos.setActivo(true)
            }

            if(permiteUsarFacturacion==0){
                cbxpermiteUsarFacturacion.setActivo(false)
            }else{
                cbxpermiteUsarFacturacion.setActivo(true)
            }

            if(permiteCrearFacturas==0){
                cbxpermiteCrearFacturas.setActivo(false)
            }else{
                cbxpermiteCrearFacturas.setActivo(true)
            }

            if(permiteBorrarFacturas==0){
                cbxpermiteBorrarFacturas.setActivo(false)
            }else{
                cbxpermiteBorrarFacturas.setActivo(true)
            }

            if(permiteAnularFacturas==0){
                cbxpermiteAnularFacturas.setActivo(false)
            }else{
                cbxpermiteAnularFacturas.setActivo(true)
            }
            if(permiteReimprimirFacturas==0){
                cbxpermiteReimprimirFacturas.setActivo(false)
            }else{
                cbxpermiteReimprimirFacturas.setActivo(true)
            }

            if(permiteAutorizarAnulaciones==0){
                cbxpermiteAutorizarAnulaciones.setActivo(false)
            }else{
                cbxpermiteAutorizarAnulaciones.setActivo(true)
            }

            if(permiteAutorizarDescuentosTotal==0){
                cbxpermiteAutorizarDescuentoTotal.setActivo(false)
            }else{
                cbxpermiteAutorizarDescuentoTotal.setActivo(true)
            }

            if(permiteAutorizarDescuentosArticulo==0){
                cbxpermiteAutorizarDescuentoItem.setActivo(false)
            }else{
                cbxpermiteAutorizarDescuentoItem.setActivo(true)
            }

            if(permiteUsarLiquidaciones==0){
                cbxpermiteUsarLiquidaciones.setActivo(false)
            }else{
                cbxpermiteUsarLiquidaciones.setActivo(true)
            }

            if(permiteCrearLiquidaciones==0){
                cbxpermiteCrearLiquidaciones.setActivo(false)
            }else{
                cbxpermiteCrearLiquidaciones.setActivo(true)
            }

            if(permiteBorrarLiquidaciones==0){
                cbxpermiteBorrarLiquidaciones.setActivo(false)
            }else{
                cbxpermiteBorrarLiquidaciones.setActivo(true)
            }

            if(permiteCerrarLiquidaciones==0){
                cbxpermiteCerrarLiquidaciones.setActivo(false)
            }else{
                cbxpermiteCerrarLiquidaciones.setActivo(true)
            }

            if(permiteAutorizarCierreLiquidaciones==0){
                cbxpermiteAutorizarCierreLiquidaciones.setActivo(false)
            }else{
                cbxpermiteAutorizarCierreLiquidaciones.setActivo(true)
            }

            if(permiteUsarListaPrecios==0){
                cbxpermiteUsarListaPrecios.setActivo(false)
            }else{
                cbxpermiteUsarListaPrecios.setActivo(true)
            }

            if(permiteCrearListaDePrecios==0){
                cbxpermiteCrearListaDePrecios.setActivo(false)
            }else{
                cbxpermiteCrearListaDePrecios.setActivo(true)
            }

            if(permiteBorrarListaDePrecios==0){
                cbxpermiteBorrarListaDePrecios.setActivo(false)
            }else{
                cbxpermiteBorrarListaDePrecios.setActivo(true)
            }

            if(permiteUsarReportes==0){
                cbxpermiteUsarReportes.setActivo(false)
            }else{
                cbxpermiteUsarReportes.setActivo(true)
            }

            if(permiteExportarAPDF==0){
                cbxpermiteExportarAPDF.setActivo(false)
            }else{
                cbxpermiteExportarAPDF.setActivo(true)
            }

            if(permiteUsarMenuAvanzado==0){
                cbxpermiteUsarMenuAdministracion.setActivo(false)
            }else{
                cbxpermiteUsarMenuAdministracion.setActivo(true)
            }

            if(permiteUsarDocumentos==0){
                cbxpermiteUsarDocumentos.setActivo(false)
            }else{
                cbxpermiteUsarDocumentos.setActivo(true)
            }
            if(permiteUsarCuentaCorriente==0){
                cbxpermiteUsarCuentaCorriente.setActivo(false)
            }else{
                cbxpermiteUsarCuentaCorriente.setActivo(true)
            }
            if(permiteCambioRapidoDePrecios==0){
                cbxpermiteCargaRapidaDePrecioListaPrecio.setActivo(false)
            }else{
                cbxpermiteCargaRapidaDePrecioListaPrecio.setActivo(true)
            }
            if(permiteUsarMenuAvanzadoPermisos==0){
                cbxAccedeAlMenuPermisos.setActivo(false)
            }else{
                cbxAccedeAlMenuPermisos.setActivo(true)
            }
            if(permiteUsarMenuAvanzadoMonedas==0){
                cbxAccedeAlMenuMonedas.setActivo(false)
            }else{
                cbxAccedeAlMenuMonedas.setActivo(true)
            }
            if(permiteUsarMenuAvanzadoRubros==0){
                cbxAccedeAlMenuRubros.setActivo(false)
            }else{
                cbxAccedeAlMenuRubros.setActivo(true)
            }
            if(permiteUsarMenuAvanzadoCuentasBancarias==0){
                cbxAccedeAlMenuCuentasBancarias.setActivo(false)
            }else{
                cbxAccedeAlMenuCuentasBancarias.setActivo(true)
            }
            if(permiteUsarMenuAvanzadoPagoDeFinacieras==0){
                cbxAccedeAlMenuPagoDeFinacieras.setActivo(false)
            }else{
                cbxAccedeAlMenuPagoDeFinacieras.setActivo(true)
            }
            if(permiteUsarMenuAvanzadoBancos==0){
                cbxAccedeAlMenuBancos.setActivo(false)
            }else{
                cbxAccedeAlMenuBancos.setActivo(true)
            }
            if(permiteUsarMenuAvanzadoLocalidades==0){
                cbxAccedeAlMenuLocalidades.setActivo(false)
            }else{
                cbxAccedeAlMenuLocalidades.setActivo(true)
            }
            if(permiteUsarMenuAvanzadoTiposDeDocumentos==0){
                cbxAccedeAlMenuTiposDeDocumentos.setActivo(false)
            }else{
                cbxAccedeAlMenuTiposDeDocumentos.setActivo(true)
            }
            if(permiteUsarMenuAvanzadoIvas==0){
                cbxAccedeAlMenuIvas.setActivo(false)
            }else{
                cbxAccedeAlMenuIvas.setActivo(true)
            }
            if(permiteUsarMenuAvanzadoConfiguraciones==0){
                cbxAccedeAlMenuConfiguraciones.setActivo(false)
            }else{
                cbxAccedeAlMenuConfiguraciones.setActivo(true)
            }


            txtDescripcionPerfil.tomarElFoco()
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
