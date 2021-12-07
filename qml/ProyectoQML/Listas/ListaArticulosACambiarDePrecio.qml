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
 //   width: 1024
    height: 45
    color: "#e9e8e9"
    radius: 1
    border.width: 1
    border.color: "#aaaaaa"
    //
    opacity: 1

    Text {
        id:txtArticulo
        width: 80
        text: codigoArticulo+" - "+modeloArticulos.retornaDescripcionArticulo(codigoArticulo)
        font.family: "Arial"
        opacity: 0.900
        //
        font.pointSize: 10
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 3
        color: "#212121"
    }

    MouseArea{
        id: mousearea1
        anchors.rightMargin: 40
        visible: false
        z: 1
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            txtArticulo.color="white"
            rectListaItemColorDeseleccionado.stop()
            rectListaItemColorSeleccionado.start()
        }
        onExited: {
            txtArticulo.color="#212121"

            rectListaItemColorSeleccionado.stop()
            rectListaItemColorDeseleccionado.start()
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
        id: lblPrecioActual
        height: 16
        color: "#4c6bb5"
        text: "Precio actual: "+modeloMonedas.retornaSimboloMoneda(modeloMonedas.retornaCodigoMoneda(codigoArticulo))+" "+precioActual+"  "
        anchors.right: lblNuevoPrecio.left
        anchors.rightMargin: 10
        //
        font.family: "Arial"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        horizontalAlignment: Text.AlignRight
        font.pointSize: 10
        font.bold: true
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: lblNuevoPrecio
        y: -5
        height: 16
        color: "#ee7416"
        text: nuevoPrecio +" "+modeloMonedas.retornaSimboloMoneda(modeloMonedas.retornaCodigoMoneda(codigoArticulo))+" :Nuevo precio"
        anchors.left: parent.left
        anchors.leftMargin: rectListaItem.width/2
        //
        anchors.right: parent.right
        anchors.rightMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        font.family: "Arial"
        font.bold: true
        font.pointSize: 10
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: txtEliminarItem
        x: -4
        y: 5
        text: qsTr("<x")
        //
        font.pixelSize: 10
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        font.family: "Arial"
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        anchors.leftMargin: 5
        verticalAlignment: Text.AlignVCenter
        anchors.left: mousearea1.right
        MouseArea {
            id: mouse_area1
            anchors.fill: parent

            onClicked:  modeloArticulosACambiarDePrecio.remove(index)
        }
    }
}
