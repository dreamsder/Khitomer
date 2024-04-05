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

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {
    id: itemBotonBarraHerramientas
    width: 25
    height: 25

    signal clic

    property double opacidad:0.7
    property alias rectanguloSecundarioVisible: rectColorSecundario.visible
    property alias textoIconoVisible: txtTextoIcono.visible
    property alias textoIconoTexto: txtTextoIcono.text

    property alias source: imagenIcono.source
    property alias toolTip: toolTipText.text


    Image {
        id: imagenIcono
        opacity: opacidad
        asynchronous: true
        anchors.fill: parent
        smooth: true


        Rectangle{
            id:rectColorSecundario
            anchors.fill: parent
            opacity: 0.15
            color: "red"
            anchors.rightMargin: 2
            anchors.leftMargin: 2
            anchors.bottomMargin: 2
            anchors.topMargin: 2
            visible: false
        }

        MouseArea {
            id: mouse_areaItemBarraHerramientas
            hoverEnabled: true
            anchors.fill: parent

            onClicked: clic()


            onEntered: {
                timer1.start()
                imagenIconoOpacidadOut.stop()
                imagenIconoOpacidadIn.start()
            }

            onExited: {
                timer1.stop()
                rectToolTipTextBarraHerramientas.visible=false
                imagenIconoOpacidadIn.stop()
                imagenIconoOpacidadOut.start()
            }

            onPressed: {
                timer1.stop()
                rectToolTipTextBarraHerramientas.visible=false
                imagenIconoScaleOut.stop()
                imagenIconoScaleIn.start()                
            }
            onReleased: {
                timer1.start()
                imagenIconoScaleIn.stop()
                imagenIconoScaleOut.start()                
            }
        }
    }



    PropertyAnimation{
        id:imagenIconoOpacidadIn
        target: imagenIcono
        property: "opacity"
        from:opacidad
        to:1
        duration: 100
    }

    PropertyAnimation{
        id:imagenIconoOpacidadOut
        target: imagenIcono
        property: "opacity"
        to:opacidad
        from:1
        duration: 100
    }

    PropertyAnimation{
        id:imagenIconoScaleIn
        target: itemBotonBarraHerramientas
        property: "scale"
        from:1
        to:0.90
        duration: 50
    }
    PropertyAnimation{
        id:imagenIconoScaleOut
        target: itemBotonBarraHerramientas
        property: "scale"
        from:0.90
        to:1
        duration: 50
    }

    Rectangle{
        id:rectToolTipTextBarraHerramientas
        visible: false
        width: toolTipText.implicitWidth+20
        height: toolTipText.implicitHeight
        color: "#4d7dc0"
        radius: 6
        opacity: 1
        z: 3
        Text {
            id: toolTipText
            color: "#fdfbfb"
            font.family: "Arial"
            font.bold: false
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.fill: parent
            visible: true
        }

    }

    Timer {
           id:timer1
           interval: 600;
           running: false;
           repeat: false;
           onTriggered: {
               if(toolTipText.text!=""){
                   rectToolTipTextBarraHerramientas.x=itemBotonBarraHerramientas.width+10
                   rectToolTipTextBarraHerramientas.y=itemBotonBarraHerramientas.height/4
                   rectToolTipTextBarraHerramientas.visible=true
               }
           }


       }


    Text {
        id: txtTextoIcono
        y: 10
        color: "#e2e2e2"
        text: qsTr("Nuevo filtro")
        visible: false
        verticalAlignment: Text.AlignVCenter
        style: Text.Raised
        font.bold: true
        font.family: "Arial"
        anchors.left: imagenIcono.right
        anchors.leftMargin: 8
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 14

        MouseArea {
            id: mouse_areaItemBarraHerramientas1
            hoverEnabled: true
            anchors.fill: parent
            onClicked: clic()


            onEntered: {

                imagenIconoOpacidadOut.stop()
                imagenIconoOpacidadIn.start()
            }

            onExited: {

                rectToolTipTextBarraHerramientas.visible=false
                imagenIconoOpacidadIn.stop()
                imagenIconoOpacidadOut.start()
            }


            onPressed: {
                rectToolTipTextBarraHerramientas.visible=false
                imagenIconoScaleOut.stop()
                imagenIconoScaleIn.start()

            }
            onReleased: {
                imagenIconoScaleIn.stop()
                imagenIconoScaleOut.start()

            }
        }
    }

}
