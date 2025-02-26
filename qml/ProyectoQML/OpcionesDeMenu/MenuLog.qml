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

import QtQuick 1.1
import "../Controles"
import "../Listas"

Rectangle {
    id: rectPrincipalMenuLOG
    width: 500
    height: 500
    color: "#00000000"
    //


    function scrollToEnd() {
                 var ratio = 1.0-flickable1.visibleArea.heightRatio
                 var endPos = flickable1.contentHeight*(1.0-flickable1.visibleArea.heightRatio)
                 flickable1.contentY = flickable1.contentHeight*(1.0-flickable1.visibleArea.heightRatio)
    }

    Text {
        id: txtTituloMenuOpcion
        x: 560
        color: "#4d5595"
        text: qsTr("log del sistema")
        font.family: "Arial"
        style: Text.Normal
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        anchors.top: parent.top
        anchors.topMargin: -10
        anchors.right: parent.right
        anchors.rightMargin: 40
        //
        font.pixelSize: 23
    }

    Row {
        id: rowBarraDeHerramientas
        x: 30
        height: 30
        anchors.top: txtTituloMenuOpcion.bottom
        anchors.topMargin: 20
        visible: true
        //
        spacing: 15
        anchors.rightMargin: 10
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.left: parent.left

        BotonBarraDeHerramientas {
            id: botonRecargarLog
            x: 61
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            toolTip: "Recargar log"
            anchors.verticalCenter: parent.verticalCenter
            z: 7

            onClic: {

                lblLog.text=funcionesmysql.leerLog()

                scrollToEnd()


            }
        }

        Text {
            id: txtMensajeInformacion
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            font.family: "Arial"
            //
            font.pixelSize: 14
            style: Text.Raised
            visible: false
            styleColor: "#ffffff"
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignTop
        }

    }

    Rectangle {
        id: rectLineaVerticalMenuGris
        height: 1
        color: "#abb2b1"
        //
        anchors.top: rowBarraDeHerramientas.bottom
        anchors.topMargin: 5
        anchors.rightMargin: 0
        visible: true
        rotation: 0
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    Rectangle {
        id: rectLineaVerticalMenuBlanco
        x: -7
        height: 1
        color: "#ffffff"
        //
        anchors.top: rowBarraDeHerramientas.bottom
        anchors.topMargin: 4
        anchors.rightMargin: 0
        visible: true
        rotation: 0
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.left: parent.left
    }


    Timer{
        id:txtMensajeInformacionTimer
        repeat: false
        interval: 5000
        onTriggered: {

            txtMensajeInformacion.visible=false
            txtMensajeInformacion.color="#d93e3e"

        }
    }


    Rectangle {
        id: rectangle1
        color: "#00ffffff"
        radius: 10
        border.width: 5
        border.color: "#e82929"
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: rectLineaVerticalMenuGris.bottom
        anchors.topMargin: 10
        clip: true


        Flickable {
             id: flickable1

             anchors.rightMargin: 15
             anchors.leftMargin: 15
             anchors.bottomMargin: 15
             anchors.topMargin: 15
             anchors.fill: parent

             //width: 300; height: 200;
            // contentWidth: parent.width
             contentHeight: lblLog.implicitHeight
             clip: true
            // flickableDirection: Flickable.VerticalFlick



          //   contentWidth: row1.implicitWidth
          //   contentHeight: parent.height
             interactive: true
             focus: false

             function ensureVisible(r)
             {

                 if (contentY >= r.y)
                     contentY = r.y;
                 else if (contentY+height <= r.y+r.height)
                     contentY = r.y+r.height-height;
             }

             TextEdit {
                 id: lblLog
                 width: flickable1.width
               //  focus: true
                 wrapMode: TextEdit.Wrap
                 selectByMouse: true
                 cursorVisible: true
                 textFormat: TextEdit.PlainText
                 readOnly: true
                 onCursorRectangleChanged: flickable1.ensureVisible(cursorRectangle)
             }
         }

        Rectangle {
            id: rectangle2
            width: 10
            height: flickable1.visibleArea.heightRatio * flickable1.height+18
            y:flickable1.visibleArea.yPosition * flickable1.height-5
            color: "#000000"
            //
            opacity: 0.500
            radius: 2
            anchors.right: flickable1.right
            anchors.rightMargin: -12
        }


        /*TextEdit {
            id: lblLog
            text: qsTr("")
            readOnly: true
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.bottomMargin: 0
            anchors.topMargin: 10
            anchors.fill: parent
            font.pixelSize: 12
            wrapMode: TextEdit.Wrap
            textFormat: TextEdit.PlainText
            selectByMouse: true
            cursorVisible: true

        }*/
    }

}
