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
   // width: 1024
    height: 35
    color: "#e9e8e9"
    radius: 1
    border.width: 1
    border.color: "#aaaaaa"
    smooth: true
    opacity: 1

    property double montoMedioDePagoSelecionado: 0.0

    property double totalidad: parseFloat(montoMedioDePago)


    Text {
        id:txtDescripcionMediosDePago
        width: 80
        text:descripcionMedioDePago
        font.family: "Arial"
        opacity: 0.900
        smooth: true
        font.pointSize: 10
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 0
        color: "#212121"
        objectName: codigoMedioDePago


    }

    MouseArea{
        id: mousearea1
        z: 1
        anchors.fill: parent
        hoverEnabled: activo
        visible: activo

        onEntered: {
            rectListaItemColorDeseleccionado.stop()
            rectListaItemColorSeleccionado.start()
        }
        onExited: {
            rectListaItemColorSeleccionado.stop()
            rectListaItemColorDeseleccionado.start()
        }
    }

    Grid {
        id: grid1
        visible: false
        spacing: 2
        flow: Grid.LeftToRight
        rows: 2
        columns: 5
        anchors.top: txtDescripcionMediosDePago.bottom
        anchors.topMargin: -1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 300
        anchors.left: parent.left
        anchors.leftMargin: 10
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
        text: totalidad.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
        font.family: "Arial"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        smooth: true
        anchors.right: parent.right
        anchors.rightMargin: 30
        horizontalAlignment: Text.AlignRight
        font.pointSize: 10
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        objectName: monedaMedioPago
    }

    Text {
        id: txtEliminarItem
        height: 16
        text: qsTr("<x")
        font.family: "Arial"
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        z: 2
        smooth: true
        font.pixelSize: 10
        visible: activo
        MouseArea {
            id: mouse_area1
            anchors.fill: parent
            enabled: activo
            onClicked: {
                montoMedioDePagoSelecionado=txtMontoAgregado.text

                var cotizacion=1;

                if(modeloMediosDePago.retornaMonedaMedioDePago(txtDescripcionMediosDePago.objectName)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                    if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloMediosDePago.retornaMonedaMedioDePago(txtDescripcionMediosDePago.objectName)){
                        cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                        montoMedioDePagoSelecionado=txtMontoAgregado.text/cotizacion
                    }else{

                        if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                            cotizacion=modeloListaMonedas.retornaCotizacionMoneda(modeloMediosDePago.retornaMonedaMedioDePago(txtDescripcionMediosDePago.objectName))
                            montoMedioDePagoSelecionado=txtMontoAgregado.text*cotizacion
                        }else{
                            montoMedioDePagoSelecionado=(txtMontoAgregado.text*modeloListaMonedas.retornaCotizacionMoneda(modeloMediosDePago.retornaMonedaMedioDePago(txtDescripcionMediosDePago.objectName)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                        }




                    }
                }
                etiquetaTotalMedioDePago.setearTotalAnulacion(montoMedioDePagoSelecionado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),-1)
                modeloListaMediosDePagoAgregados.remove(index)
            }

        }
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: txtSimboloMonedaMedioDePago
        x: 0
        y: 3
        height: 16
        color: "#4c6bb5"
        text: simboloMonedaMedioDePago
        font.family: "Arial"
        smooth: true
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
        smooth: true
        font.bold: false
        font.pointSize: 10
        anchors.leftMargin: 10
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
    }

    Text {
        id: txtCantidadCuotasAgregadas
        color: "#212121"
        text: cantidadCuotas
        font.family: "Arial"
        horizontalAlignment: Text.AlignRight
        smooth: true
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
        smooth: true
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
    Text {
        id: txtDatosCuentaBancaria
        visible: false
        text: numeroCuentaBancariaAgregado
        objectName: numeroBancoCuentaBancaria
    }
}
