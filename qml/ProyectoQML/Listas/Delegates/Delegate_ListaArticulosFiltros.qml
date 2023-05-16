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
import "../../Controles"
import "../../"

FocusScope {
    x: childrenRect.x
    y: childrenRect.y
    //width: childrenRect.width
    height: childrenRect.height



    width: 300

    property string codigoValorSeleccion
    property bool permiteOperarConArticulosInactivos: false

    signal senialAlAceptarOClick
    signal keyEscapeCerrar


    Rectangle {
        id: rect1
        width: rectPrincipalComboBox.width
        height: 32
        color: "#00000000"
        Text {
            id: texto1
            color: "#000000"
            text: descripcionArticulo
            font.family: "Arial"
            clip: false
            //

            onActiveFocusChanged: {

                if(activeFocus){
                    opacityOff.stop()
                    opacityIn.start()
                    texto1.color="white"
                    texto1.style= Text.Normal
                    texto1.font.bold= true

                }else{
                    opacityIn.stop()
                    opacityOff.start()
                    texto1.color="#212121"
                    texto1.style= Text.Raised
                    texto1.font.bold= false
                }

            }

            PropertyAnimation{
                id: opacityIn
                target: rectTextComboBox
                property: "opacity"
                from:0
                to: 0.60
                duration: 200
            }
            PropertyAnimation{
                id: opacityOff
                target: rectTextComboBox
                property: "opacity"
                from: 0.60
                to:0
                duration: 50
            }

            Rectangle {
                id: rectTextComboBox
                y: 12
                width: listview1.width+20
                height: 19
                color: "#5358be"
                radius: 1
                //
                anchors.top: parent.top
                border.color: "#000000"
                anchors.topMargin: -3
                anchors.bottom: parent.bottom
                border.width: 0
                anchors.bottomMargin: -17
                z: -50
                anchors.leftMargin: -10
                opacity: 0
                anchors.left: parent.left
            }

            PropertyAnimation {
                id: opacityIn1
                target: rectTextComboBox
                property: "opacity"
                to: 0.600
                from: 0
                duration: 200
            }

            PropertyAnimation {
                id: opacityOff1
                target: rectTextComboBox
                property: "opacity"
                to: 0
                from: 0.600
                duration: 50
            }

            MouseArea {
                id: mouseArea
                width: listview1.width
                height: texto1.height+texto2.height
                hoverEnabled: true
                onEntered: {
                    listview1.forceActiveFocus()
                    opacityOff.stop()
                    opacityIn.start()

                    texto1.color="white"
                    texto1.style= Text.Normal
                    texto1.font.bold= true
                }
                onExited:{
                    opacityIn.stop()
                    opacityOff.start()

                    texto1.color="#212121"
                    texto1.style= Text.Raised
                    texto1.font.bold= false
                }
                onClicked: {
                    if(modeloArticulos.retornaArticuloActivo(codigoArticulo) || permiteOperarConArticulosInactivos){
                        codigoValorSeleccion=codigoArticulo
                        senialAlAceptarOClick()
                    }


                }
            }

            Keys.onReturnPressed: {
                if(modeloArticulos.retornaArticuloActivo(codigoArticulo) || permiteOperarConArticulosInactivos){
                    codigoValorSeleccion=codigoArticulo
                    senialAlAceptarOClick()
                }
            }
            Keys.onEscapePressed: keyEscapeCerrar()

            style: Text.Raised
            styleColor: "#ffffff"
            font.pointSize: 10
            z: 100
            anchors.leftMargin: 10
            anchors.left: parent.left
            focus: true
        }

        Text {
            id: texto2
            text: "INACTIVO"
            font.bold: false
            verticalAlignment: Text.AlignBottom
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            horizontalAlignment: Text.AlignLeft
            //
            clip: false
            color: "#d93e3e"
            font.pointSize: 10
            z: 100
            visible: !modeloArticulos.retornaArticuloActivo(codigoArticulo)
        }

        Text {
            id: txtStockActual
            color: "#d93e3e"
           // text: "Stock previsto: "+modeloArticulos.retornaStockTotalArticulo(codigoArticulo)
            text:"Stock previsto:  "+stockPrevisto
            anchors.right: parent.right
            anchors.rightMargin: 20
            //
            clip: false
            anchors.bottom: parent.bottom
            visible: true
            anchors.bottomMargin: 0
            font.bold: false
            font.pointSize: 10
            z: 100
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignBottom
        }
    }
}
