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

Rectangle {
    id: rectPrincipalBotonFlechaSiguiente
    width: 25
    height: 25
    color: "#00030202"
    radius: 100
    opacity: opacidadRectPrincipal
    //
    border.width: 2
    border.color: "#fffdfd"

    signal clic
    property double scaleValorActual: 1
    property alias colorBorder: rectPrincipalBotonFlechaSiguiente.border
    property double opacidadRectPrincipal: 0.5

    property alias source : image1.source

    //property alias toolTip: toolTipText.text



    MouseArea {
        id: mouse_area1
        hoverEnabled: true
        anchors.fill: parent

        onEntered: {


            rectPrincipalBotonFlechaSiguienteScaleAlSalir.stop()
            rectPrincipalBotonFlechaSiguienteOpacityOff.stop()

            rectPrincipalBotonFlechaSiguienteScaleAlEntrar.start()
            scaleValorActual=rectPrincipalBotonFlechaSiguienteScaleAlEntrar.to
            rectPrincipalBotonFlechaSiguienteOpacityIn.start()

        }

        onExited: {

            rectPrincipalBotonFlechaSiguienteScaleAlEntrar.stop()
            rectPrincipalBotonFlechaSiguienteOpacityIn.stop()

            rectPrincipalBotonFlechaSiguienteScaleAlSalir.start()
            scaleValorActual=rectPrincipalBotonFlechaSiguienteScaleAlSalir.to
            rectPrincipalBotonFlechaSiguienteOpacityOff.start()
        }

        onPressed: {        
            rectPrincipalBotonFlechaSiguienteScaleOff.stop()
            rectPrincipalBotonFlechaSiguienteScaleIn.start()
        }

        onReleased: {
            rectPrincipalBotonFlechaSiguienteScaleIn.stop()
            rectPrincipalBotonFlechaSiguienteScaleOff.start()
        }

        onClicked: clic()
    }


    PropertyAnimation{
        id:rectPrincipalBotonFlechaSiguienteScaleIn
        target: rectPrincipalBotonFlechaSiguiente
        property: "scale"
        from:scaleValorActual
        to:1
        duration:100
    }

    PropertyAnimation{
        id:rectPrincipalBotonFlechaSiguienteScaleOff
        target: rectPrincipalBotonFlechaSiguiente
        property: "scale"
        from:1
        to:scaleValorActual
        duration:40
    }


    PropertyAnimation{
        id:rectPrincipalBotonFlechaSiguienteScaleAlEntrar
        target: rectPrincipalBotonFlechaSiguiente
        property: "scale"
        from:scaleValorActual
        to:1.15
        duration:40
    }

    PropertyAnimation{
        id:rectPrincipalBotonFlechaSiguienteScaleAlSalir
        target: rectPrincipalBotonFlechaSiguiente
        property: "scale"
        from:scaleValorActual
        to:1
        duration:40
    }

    PropertyAnimation{
        id:rectPrincipalBotonFlechaSiguienteOpacityIn
        target: rectPrincipalBotonFlechaSiguiente
        property: "opacity"
        from:opacidadRectPrincipal
        to:1
        duration:100
    }

    PropertyAnimation{
        id:rectPrincipalBotonFlechaSiguienteOpacityOff
        target: rectPrincipalBotonFlechaSiguiente
        property: "opacity"
        from:1
        to:opacidadRectPrincipal
        duration:40
    }



    Image {
        id: image1
        clip: true
        smooth: true
        asynchronous: true
        anchors.fill: parent
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaDerecha.png"
    }
}
