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

Rectangle {
    id: rectBotonCargarDato
    width: txtBotonCargarDato.implicitWidth+imageBotonCargarDato.width+10
    height: 32
    //color: "#28000000"
    color: "#00000000"
    radius: 5
    opacity: 1
    //

    signal clic
    property alias texto: txtBotonCargarDato.text
    property alias imagen: imageBotonCargarDato.source

    property alias textoColor:txtBotonCargarDato.color

    function volverAEstadoOriginalElControl(){


        rectBotonCargarDatoScale_In.stop()
        rectBotonCargarDatoScale_Off.start()
        imageBotonCargarDatoOpacidad_In.stop()
        imageBotonCargarDatoOpacidad_Off.start()

    }

    Image {
        id: imageBotonCargarDato
        width: 24
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        asynchronous: true
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        opacity: 0.500
        //
        fillMode: Image.PreserveAspectFit
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Suma.png"
    }

    Text {
        id: txtBotonCargarDato
        color: "#4f4f4f"
        text: qsTr("")
        font.family: "Arial"
        anchors.left: imageBotonCargarDato.right
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        //
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 13
        }

        MouseArea {
            id: mouse_areaBotonCargarDato
            anchors.fill: parent
            hoverEnabled: true

            onPressed: {
                rectBotonCargarDatoScale_Off.stop()
                rectBotonCargarDatoScale_In.start()

            }
            onReleased: {

                rectBotonCargarDatoScale_In.stop()
                rectBotonCargarDatoScale_Off.start()                

            }
            onEntered: {

                imageBotonCargarDatoOpacidad_Off.stop()
                imageBotonCargarDatoOpacidad_In.start()
                rectBotonCargarDato.color="#28000000"

            }
            onExited: {
                imageBotonCargarDatoOpacidad_In.stop()
                imageBotonCargarDatoOpacidad_Off.start()
                rectBotonCargarDato.color="#00000000"
            }
            onClicked: clic()
        }



        PropertyAnimation{
            id:rectBotonCargarDatoScale_In
            target: rectBotonCargarDato
            property: "scale"
            from:1
            to:0.95
            duration: 200



        }

        PropertyAnimation{
            id:rectBotonCargarDatoScale_Off
            target: rectBotonCargarDato
            property: "scale"
            to:1
            from:0.95
            duration: 40



        }




        PropertyAnimation{
            id:imageBotonCargarDatoOpacidad_In
            target: imageBotonCargarDato
            property: "opacity"
            from:0.5
            to:1
            duration: 400



        }
        PropertyAnimation{
            id:imageBotonCargarDatoOpacidad_Off
            target: imageBotonCargarDato
            property: "opacity"
            to:0.5
            from:1
            duration: 200



        }

}
