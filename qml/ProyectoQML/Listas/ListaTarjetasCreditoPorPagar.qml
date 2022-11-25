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

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import "../Controles"

Rectangle{
    id: rectListaItem
    width: parent.width
    // width: 800
    height: 35
    color: "#e9e8e9"
    radius: 1
    border.width: 1
    border.color: "#aaaaaa"
    //
    opacity: 1

    property double montoMedioDePagoSeleccionado: parseFloat(montoMedioDePago)


    Text {
        id:txtDescripcionMediosDePago
        width: 80
        text:descripcionMedioDePago
        font.family: "Arial"
        opacity: 0.900
        //
        font.pointSize: 10
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.top: parent.top
        anchors.topMargin: 0
        color: "#212121"
        objectName: codigoMedioDePago


    }

    MouseArea{
        id: mousearea1
        z: 2
        anchors.fill: parent
        hoverEnabled: true
        visible: true
        onEntered: {
            rectListaItemColorDeseleccionado.stop()
            rectListaItemColorSeleccionado.start()
        }
        onExited: {
            rectListaItemColorSeleccionado.stop()
            rectListaItemColorDeseleccionado.start()
        }
        onClicked: {
            if(chbSeleccionado.chekActivo){
                chbSeleccionado.setActivo(false)
                modeloListaTarjetasCreditoACobrar.setProperty(index,"checkboxActivo",false)
            }else{
                chbSeleccionado.setActivo(true)
                modeloListaTarjetasCreditoACobrar.setProperty(index,"checkboxActivo",true)
            }
        }
        onDoubleClicked: {

            if(chbSeleccionado.chekActivo){
                chbSeleccionado.setActivo(false)
                modeloListaTarjetasCreditoACobrar.setProperty(index,"checkboxActivo",false)
            }else{
                chbSeleccionado.setActivo(true)
                modeloListaTarjetasCreditoACobrar.setProperty(index,"checkboxActivo",true)
            }

            mantenimientoFactura.cargoFacturaEnMantenimiento(codigoDoc,codigoTipoDoc,serieDocumento)

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

    Text {
        id: txtMontoAgregado
        height: 16
        color: "#4c6bb5"
        text: montoMedioDePagoSeleccionado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
        font.family: "Arial"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        //
        anchors.right: parent.right
        anchors.rightMargin: 30
        horizontalAlignment: Text.AlignRight
        font.pointSize: 10
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        objectName: monedaMedioPago
    }

    Text {
        id: txtSimboloMonedaMedioDePago
        x: 0
        y: 3
        height: 16
        color: "#4c6bb5"
        text: simboloMonedaMedioDePago
        font.family: "Arial"
        //
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        anchors.bottomMargin: 2
        font.bold: true
        font.pointSize: 10
        anchors.right: txtMontoAgregado.left
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: lblCantidadCuotasAgregadas

        width: implicitWidth
        color: "#212121"
        text: "Cuotas: "
        font.family: "Arial"
        opacity: 0.500
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        //
        font.bold: false
        font.pointSize: 10
        anchors.leftMargin: 50
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
    }

    Text {
        id: txtCantidadCuotasAgregadas
        color: "#212121"
        text: cantidadCuotas
        font.family: "Arial"
        horizontalAlignment: Text.AlignRight
        //
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        font.bold: false
        font.pointSize: 10
        anchors.leftMargin: 1
        verticalAlignment: Text.AlignVCenter
        opacity: 0.500
        width: 20
        anchors.left: lblCantidadCuotasAgregadas.right
    }

    Text {
        id: txtDetallesMedioDePago
        x: 1
        y: 9
        width: 80
        color: "#212121"
        text: nombreTarjetaCredito
        font.family: "Arial"
        horizontalAlignment: Text.AlignRight
        anchors.right: parent.right
        anchors.rightMargin: 30
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        font.bold: false
        font.pointSize: 10
        objectName: codigoTarjetaCredito
        verticalAlignment: Text.AlignVCenter
    }
    Text {
        id: txtDatosCheque
        visible: false
        text: numeroCheque
        font.pointSize: 11
        font.family: "Arial"
    }
    Text {
        id: txtDatosBanco
        visible: false
        text: numeroBanco
        font.pointSize: 11
        font.family: "Arial"
    }
    Text {
        id: txtDatosChequeFecha
        visible: false
        text: fechaCheque
        font.pointSize: 11
        font.family: "Arial"
    }
    Text {
        id: txtDatosChequeTipoCheque
        visible: false
        text: tipoCheque
        font.pointSize: 11
        font.family: "Arial"
    }
    Text {
        id: txtDatosChequesdiferidos
        visible: false
        text: codigoDoc
        enabled: esDiferido
        objectName: codigoTipoDoc
        height: numeroLineaDocumento


    }

    CheckBox {
        id: chbSeleccionado
        buscarActivo: false
        chekActivo: checkboxActivo
        anchors.top: parent.top
        anchors.topMargin: -8
        textoValor: ""
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    Text {
        id: txtClienteFactura
        color: "#212121"
        text: modeloLineasDePagoTarjetasCredito.retornaRazonDeCliente(codigoDoc,codigoTipoDoc, serieDocumento)
        //
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        font.family: "Arial"
        font.bold: false
        font.pointSize: 10
        horizontalAlignment: Text.AlignLeft
        anchors.leftMargin: 30
        verticalAlignment: Text.AlignVCenter
        opacity: 0.500
        anchors.left: txtCantidadCuotasAgregadas.right
    }

    Text {
        id: txtFechaFactura
        x: -7
        y: 3
        color: "#212121"
        text: "Fecha doc: "+modeloLineasDePagoTarjetasCredito.retornaFechaDocumento(codigoDoc,codigoTipoDoc,serieDocumento)
        //
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        font.bold: false
        font.family: "Arial"
        font.pointSize: 10
        anchors.leftMargin: 30
        horizontalAlignment: Text.AlignLeft
        opacity: 0.500
        verticalAlignment: Text.AlignVCenter
        anchors.left: txtClienteFactura.right
    }

}
