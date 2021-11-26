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
Rectangle{
    id:rectPrincipal
    width: text1.implicitWidth + 5 + image1.width
    height: 32
    color: "#00000000"


    property bool chekActivo: false

    property alias colorTexto: text1.color
    property alias textoValor: text1.text
    property alias buscarActivo: imageBuscar.visible
    property alias tamanioLetra : text1.font.pixelSize
    property alias  opacidadTexto: text1.opacity


    property double opacidadPorDefecto: 0.8

    signal clicEnBusqueda



    function setActivo(atributo){
        chekActivo=atributo
        image1.visible=chekActivo
    }

Rectangle {
    id: rectangle1

    color: "#00000000"
    anchors.topMargin: 16
    anchors.fill: parent
    smooth: true



    Rectangle {
        id: rectangle2
        width: 18
        height: 18
        color: "#ffffff"
        smooth: true
        radius: 2
        border.color: "#686b71"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        border.width: 1
        opacity: {

            if(chekActivo){
                1
            }else{
                opacidadPorDefecto
            }
        }

        Image {
            id: image1
            visible: chekActivo
            smooth: true
            anchors.rightMargin: -6
            anchors.leftMargin: 2
            anchors.bottomMargin: 2
            anchors.topMargin: -4
            asynchronous: true
            anchors.fill: parent
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/VistoOk.png"
        }
    }

    Text {
        id: text1
        color: "#333333"
        text: qsTr("checkbox")
        font.family: "Arial"
        smooth: true
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        anchors.left: rectangle2.right
        anchors.leftMargin: 10
        font.pixelSize: 12
    }

    MouseArea {
        id: mouse_area1
        anchors.fill: parent

        onClicked: {

            if(chekActivo){
                setActivo(false)
                opacityIn.stop()
                opacityOff.start()
            }else{
                setActivo(true)
                opacityOff.stop()
                opacityIn.start()
            }

        }


    }

    PropertyAnimation{
        id: opacityIn
        target: rectangle2
        property: "opacity"
        from:opacidadPorDefecto
        to: 1
        duration: 200
    }
    PropertyAnimation{
        id: opacityOff
        target: rectangle2
        property: "opacity"
        from: 1
        to:opacidadPorDefecto
        duration: 200
    }

    PropertyAnimation{
        id:imageBuscarScaleIn
        target: imageBuscar
        property: "scale"
        from:1
        to:0.93
        duration: 70
    }

    PropertyAnimation{
        id:imageBuscarScaleOff
        target: imageBuscar
        property: "scale"
        to:1
        from:0.93
        duration: 50
    }



    PropertyAnimation{
        id:imageBuscarOpacidadIn
        target: imageBuscar
        property: "opacity"
        from:0.5
        to:1
        duration: 70
    }

    PropertyAnimation{
        id:imageBuscarOpacidadOut
        target: imageBuscar
        property: "opacity"
        from:1
        to:0.5
        duration: 50
    }

    Image {
        id: imageBuscar
        width: 21
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        asynchronous: true
        smooth: true
        MouseArea {
            id: mouse_area2
            visible: true
            hoverEnabled: true
            anchors.fill: parent
            anchors.leftMargin: 0
            onPressed: {
                imageBuscarScaleOff.stop()
                imageBuscarScaleIn.start()
            }
            onReleased:  {
                imageBuscarScaleIn.stop()
                imageBuscarScaleOff.start()

            }
            onEntered: {
                imageBuscarOpacidadOut.stop()
                imageBuscarOpacidadIn.start()
            }
            onExited: {
                imageBuscarOpacidadIn.stop()
                imageBuscarOpacidadOut.start()

            }
            onClicked: clicEnBusqueda()
        }
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Search.png"
        visible: false
        anchors.leftMargin: 2
        opacity: 0.500
        anchors.left: text1.right
    }


}
}
