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
        id:lblMonedas
        text: codigoMoneda + " - "+descripcionMoneda + " ( "+simboloMoneda+" )"
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
            txtMontoSaldo.forceActiveFocus()
            txtMontoSaldo.tomarElFoco()
        }



        TextInputSimple {
            property double nuevoMonto:0.00
            id: txtMontoSaldo
            enFocoSeleccionarTodo: true
            textoInputBox: limiteSaldo
            botonBuscarTextoVisible: false
            inputMask: "00000000"+modeloconfiguracion.retornaCantidadDecimalesString()+";"
            largoMaximo: 45

            textoTitulo: ""

            colorDeTitulo: "#333333"
            anchors.top: parent.top
            anchors.topMargin: 7
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter

            onEnter: {



            }

            onTextoInputBoxChanged: {

                if(txtMontoSaldo.textoInputBox.trim()!="."){
                   nuevoMonto=parseFloat(txtMontoSaldo.textoInputBox.trim())
                   nuevoMonto=nuevoMonto+0.00;
                    //modeloListasPreciosCuadroArticulosASetearPrecioGenerica.setProperty(index,"precioArticulo",precioNuevoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                   modeloListaMonedaSaldosDelegateVirtual.setProperty(index,"limiteSaldo",nuevoMonto.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                }


            }


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



    /*Text {
        id: lblCotizacion
        y: 6
        color: "#212121"
        text: "Cotización "+ modeloMonedas.retornaSimboloMoneda(modeloMonedas.retornaMonedaReferenciaSistema()) +":   "   +cotizacionMoneda
        anchors.verticalCenter: parent.verticalCenter
        horizontalAlignment: Text.AlignLeft
        anchors.left: parent.left
        anchors.leftMargin: rectListaItem.width-200
        //
        font.family: "Arial"
        font.bold: false
        font.pointSize: 10
        opacity: 0.900
        verticalAlignment: Text.AlignVCenter
    }*/
}
