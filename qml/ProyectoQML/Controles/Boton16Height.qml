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
import QtQuick 1.1

Rectangle {
    id: rectBoton16HeightPrincipal
    width: 16
    height: 16
    color: "#00000000"
    clip: true
    smooth: true

    property alias imagen: image1.source
    property double opacidad: 0.600


    signal clic
    Image {
        id: image1
        anchors.rightMargin: -2
        anchors.leftMargin: -2
        anchors.bottomMargin: -2
        anchors.topMargin: -2
        opacity: opacidad
        visible: true
        asynchronous: true
        smooth: true
        anchors.fill: parent
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Mas.png"
    }

    MouseArea {
        id: mouse_area1
        smooth: true
        anchors.fill: parent
        hoverEnabled: true
        z: 1
        onEntered: {
            imagenOpacidadOff.stop()
            imagenOpacidadIn.start()

        }
        onExited: {
            imagenOpacidadIn.stop()
            imagenOpacidadOff.start()

        }

        onReleased: {
            imagenScaleIn.stop()
            imagenScaleOut.start()

        }
        onPressed: {
            imagenScaleOut.stop()
            imagenScaleIn.start()

        }

        onClicked: clic()
    }

    PropertyAnimation{
        id:imagenOpacidadIn
        target: image1
        property: "opacity"
        from:opacidad
        to:1
        duration: 200
    }

    PropertyAnimation{
        id:imagenOpacidadOff
        target: image1
        property: "opacity"
        to:opacidad
        from:1
        duration: 50
    }

    PropertyAnimation{
        id:imagenScaleIn
        target: image1
        property: "scale"
        from:1
        to:0.80
        duration: 50
    }
    PropertyAnimation{
        id:imagenScaleOut
        target: image1
        property: "scale"
        from:0.80
        to:1
        duration: 50
    }
}
