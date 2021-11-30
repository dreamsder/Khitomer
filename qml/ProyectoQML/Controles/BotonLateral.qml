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


Rectangle {
    id: rectAdvertencia
    width: 30
    height: 30
    color: "#00000000"
    //


    property alias textoBoton: txtTextoAdvertencia.text
    property alias timerRuning: timer1.running
    signal clic

    Image {
        id: imgIconoAdvertencia
        opacity: 1
        //
        anchors.fill: parent
        asynchronous: true
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Advertencia.png"
    }

    Rectangle {
        id: rectangle1
        width: txtTextoAdvertencia.implicitWidth+3
        height: txtTextoAdvertencia.implicitHeight+1
        color: "#64716c6c"
        radius: 3
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: -5

        Text {
            id: txtTextoAdvertencia
            x: 0
            y: 1
            width: 11
            height: 16
            color: "#ffffff"
            text: ""
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignTop
            anchors.verticalCenter: parent.verticalCenter
            style: Text.Sunken
            opacity: 1
            visible: true
            horizontalAlignment: Text.AlignHCenter
            //
            font.family: "Arial"
            font.bold: true
            z: 1
            font.pixelSize: 12
    }
    }

    MouseArea {
        id: mouseAreaAdvertenvia
        hoverEnabled: true
        anchors.fill: parent
        z: 1
        onEntered: {
            rectangle1ColorOff.stop()
            rectangle1ColorIn.start()
        }
        onExited: {
            rectangle1ColorIn.stop()
            rectangle1ColorOff.start()
        }
        onReleased: {
            imgIconoAdvertenciaScaleIn.stop()
            imgIconoAdvertenciaScaleOut.start()
        }
        onPressed: {
            imgIconoAdvertenciaScaleOut.stop()
            imgIconoAdvertenciaScaleIn.start()

        }
        onClicked: clic()
    }

    PropertyAnimation{
        id:rectangle1ColorIn
        target: rectangle1
        property: "color"
        from:"#64716c6c"
        to:"#716c6c"
        duration: 300
    }
    PropertyAnimation{
        id:rectangle1ColorOff
        target: rectangle1
        property: "color"
        to:"#64716c6c"
        from:"#716c6c"
        duration: 100
    }
    PropertyAnimation{
        id: imgIconoAdvertenciaScaleIn
        target: imgIconoAdvertencia
        property: "scale"
        from:1
        to:0.96
        duration: 200
    }
    PropertyAnimation{
        id: imgIconoAdvertenciaScaleOut
        target: imgIconoAdvertencia
        property: "scale"
        to:1
        from:0.96
        duration: 50
    }

    SequentialAnimation {
            id:secuenciaAnimacion1
             running: true
             NumberAnimation { target: imgIconoAdvertencia; property: "opacity"; from:1 ;to: 0.3; duration: 1000 }
             NumberAnimation { target: imgIconoAdvertencia; property: "opacity"; from:0.3 ;to: 1; duration: 1000 }
         }

    Timer{
        id:timer1
        running: false
        interval: 3000
        repeat: true
        onTriggered: secuenciaAnimacion1.start()
    }



}
