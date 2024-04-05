/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2024>  <Cristian Montano>

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

Rectangle {
    id: rectangle1
    width: txtTextoBoton.implicitWidth+30

    height: 32
    color: "#00000000"
    //


    property alias textoBoton: txtTextoBoton.text
    property alias colorTextoBoton: txtTextoBoton.color
    property alias estilo: txtTextoBoton.style
    property alias negrita: txtTextoBoton.font.bold
    property bool  modoBotonPrecionado: true
    property bool  estaPrecionado: false
    property alias opacidadTexto : txtTextoBoton.opacity

    signal clicBoton


    function setearEstadoBoton(){
        if(modoBotonPrecionado){
            if(estaPrecionado){
                rectangle3.anchors.rightMargin=1
                rectangle3.anchors.leftMargin=1
                rectangle3.anchors.bottomMargin=1
                rectangle3.anchors.topMargin=2
                rectangle2.border.width=1
                rectangle3.border.width=1
                estaPrecionado=false

            }else{
                rectangle3.anchors.rightMargin=0
                rectangle3.anchors.leftMargin=3
                rectangle3.anchors.bottomMargin=0
                rectangle3.anchors.topMargin=3
                rectangle2.border.width=2
                rectangle3.border.width=3
                estaPrecionado=true
                rectangle2.opacity=1
            }
        }
    }

    function restaurarBoton(){
        rectangle3.anchors.rightMargin=1
        rectangle3.anchors.leftMargin=1
        rectangle3.anchors.bottomMargin=1
        rectangle3.anchors.topMargin=2
        rectangle2.border.width=1
        rectangle3.border.width=1
        estaPrecionado=false
        rectangle2.opacity=0
    }



    Text {
        id: txtTextoBoton
        y: 34
        text: "test"
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.right: parent.right
        anchors.rightMargin: 15


        wrapMode: Text.WordWrap
        styleColor: "#2c3f7e"
        style: Text.Raised
        font.italic: false
        font.family: "Arial"
        anchors.verticalCenter: parent.verticalCenter
        opacity: 0.670
        z: 1
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: false
        //
        font.pixelSize: 14
    }

    MouseArea {
        id: mouseAreaBoton
        hoverEnabled: true
        //
        anchors.fill: parent
        onEntered: {
            if(!estaPrecionado)
                rectangle2.opacity=1
        }
        onExited: {
            if(!estaPrecionado)
                rectangle2.opacity=0
        }
        onClicked: {
            setearEstadoBoton()
            clicBoton()
        }
        onPressed: {
            if(!modoBotonPrecionado){
                scalaFin.stop()
                scalaComienzo.start()
            }
        }
        onReleased: {
            if(!modoBotonPrecionado){
                scalaComienzo.stop()
                scalaFin.start()
            }
        }
    }

    Rectangle {
        id: rectangle2
        color: "#f1f1f0"
        radius: 4
        border.width: 1
        border.color: "#d1d0d0"
        opacity: 0
        anchors.fill: parent

        Rectangle {
            id: rectangle3
            color: "#00000000"
            radius: 4
            border.width: 1
            opacity: 0.450
            anchors.rightMargin: 1
            anchors.leftMargin: 1
            anchors.bottomMargin: 1
            anchors.topMargin: 2
            border.color: "#ffffff"
            anchors.fill: parent
        }
    }
    PropertyAnimation{
        id:scalaComienzo
        target: rectangle1
        property: "scale"
        from:1
        to:0.95
        duration: 100
    }
    PropertyAnimation{
        id:scalaFin
        target: rectangle1
        property: "scale"
        from:0.95
        to:1
        duration: 50
    }
}
