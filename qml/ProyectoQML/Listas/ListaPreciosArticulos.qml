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
    clip: true
    border.color: "#aaaaaa"
    opacity: 1

    property double precioItem: parseFloat(itemPrecioAgregado)



    Text {
        id:txtItemArticulo
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        //
        font.pointSize: 10
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 180
        anchors.top: parent.top
        anchors.topMargin: 0
        color: "#212121"
        text: itemDescripcion + " ("+itemCodigoAgregado+")"
        font.family: "Arial"
        opacity: 0.900
    }



    Text {
        id:txtPrecioArticulo
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        //
        font.pointSize: 10
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: parent.top
        anchors.topMargin: 0
        color: "#212121"
        //text: itemPrecioAgregado
        text:precioItem.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
        font.family: "Arial"
        horizontalAlignment: Text.AlignLeft
    }


    MouseArea{
        id: mousearea1
        anchors.rightMargin: 40
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

            txtArticuloParaLista.textoInputBox=itemCodigoAgregado
            txtPrecioArticuloParaLista.textoInputBox=itemPrecioAgregado
            txtPrecioArticuloParaLista.textoTitulo="Precio en "+modeloListaMonedas.retornaSimboloMoneda(modeloListaMonedas.retornaCodigoMoneda(itemCodigoAgregado))
            txtPrecioArticuloParaLista.tomarElFoco()


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
        id: txtMonedaEnLista
        x: 9
        y: 7
        color: "#212121"
        text: modeloListaMonedas.retornaSimboloMoneda(modeloListaMonedas.retornaCodigoMoneda(itemCodigoAgregado))
        font.family: "Arial"
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        font.bold: false
        font.pointSize: 10
        anchors.leftMargin: 0
        verticalAlignment: Text.AlignVCenter
        anchors.left: txtItemArticulo.right
    }
    Item {
        id: modificado
        visible: false
        enabled: precioModificado
        focus: eliminarPrecioArticulo

    }

    Rectangle {
        id: rectangle1
        //color: "#fa8585"
        color: {
            if(txtEliminarItem.color=="Red")   {
                "#fa8585"
            }else{
                "#00ffffff"
            }
        }
        //
        radius: 20
        clip: true
        border.width: 0
        z: 3
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: mousearea1.right
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 3
        anchors.top: parent.top
        anchors.topMargin: 3

        Text {
            id: txtEliminarItem
            x: 0
            y: -1
            color: "#000000"
            text: qsTr("<x")
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "Arial"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -1
            //
            font.bold: true
            font.pixelSize: 10
        }

        MouseArea {
            id: mouse_area1
            anchors.fill: parent

            onClicked: {

                if(modeloListaPrecioArticulosAlternativa.get(index).eliminarPrecioArticulo){
                    txtEliminarItem.text=qsTr("<x")
                    txtEliminarItem.color="#212121"
                    rectangle1.color="#00ffffff"

                    modeloListaPrecioArticulosAlternativa.setProperty(index,"eliminarPrecioArticulo",false)
                }else{
                    txtEliminarItem.text=qsTr("X")
                    txtEliminarItem.color="White"
                    rectangle1.color="#fa8585"

                    modeloListaPrecioArticulosAlternativa.setProperty(index,"eliminarPrecioArticulo",true)
                }
            }
            }
    }
}
