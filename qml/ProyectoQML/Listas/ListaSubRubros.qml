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
   //width: 1024
    height: 38
    color: "#e9e8e9"
    radius: 1
    border.width: 1
    border.color: "#aaaaaa"
    //
    opacity: 1


    Text {
        id:subrubros
        text: descripcionSubRubro
        font.family: "Arial"
        opacity: 0.900
        //
        font.pointSize: 10
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.top: parent.top
        anchors.topMargin: 0
        color: "#212121"

    }

    MouseArea{
        id: mousearea1
        z: 1
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            subrubros.color="white"
            txtCodigoSubRubroEnLista.color="white"
            rectListaItemColorDeseleccionado.stop()
            rectListaItemColorSeleccionado.start()
        }
        onExited: {
            subrubros.color="#212121"
            txtCodigoSubRubroEnLista.color="#000000"

            rectListaItemColorSeleccionado.stop()
            rectListaItemColorDeseleccionado.start()
        }
        onClicked: {
            txtCodigoSubRubro.textoInputBox=codigoSubRubro
            txtNombreSubRubro.textoInputBox=descripcionSubRubro
            cbxListaRubrosMantenimiento.codigoValorSeleccion=codigoRubro
            cbxListaRubrosMantenimiento.textoComboBox=modeloListaRubros.retornaNombreRubro(codigoRubro)
            txtNombreSubRubro.tomarElFoco()
        }
    }
    Rectangle {
        id: rectLinea
        y: 35
        height: 1
        color: "#975f5f"
        visible: false
        //
        opacity: 0.500
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.left: parent.left
        anchors.leftMargin: 20
    }

    Grid {
        id: grid1
        spacing: 2
        flow: Grid.TopToBottom
        rows: 2
        columns: 5
        anchors.top: subrubros.bottom
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 200
        anchors.left: parent.left
        anchors.leftMargin: 30

        Text {
            id: txtCodigoSubRubroEnLista
            x: 1
            y: -15
            width: 210
            text: qsTr("Código:  "+codigoSubRubro)
            font.family: "Arial"
            //
            opacity: 0.500
            font.pixelSize: 11
            height: txtCodigoSubRubroEnLista.implicitHeight
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
