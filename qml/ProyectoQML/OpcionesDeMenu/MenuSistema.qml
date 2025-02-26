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
    id: rectPrincipalMenuSistemas
    width: 700
    height: 500
    color: "#00000000"
    radius: 0
    //
    Text {
        id: txtTituloMenuOpcion
        x: 560
        color: "#4d5595"
        text: qsTr("información del sistema")
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
    Column {
        id: column1
        anchors.rightMargin: 30
        anchors.bottomMargin: 10
        spacing: 10
        anchors.leftMargin: 30
        anchors.topMargin: 40
        anchors.fill: parent
        Text {
            id: txtInformacionModeloAplicacion
            color: "#2b2a2a"
            text: qsTr("Clase:  Ambassador")
            font.family: "Arial"
            //
            font.pixelSize: 12
            font.bold: false
        }
        Text {
            id: txtVersionDelPrograma
            x: 0
            y: 0
            color: "#2b2a2a"
            text: qsTr("Versión: "+ versionKhitomer + " - " + funcionesmysql.versionDeBaseDeDatos())
            font.family: "Arial"
            //
            font.bold: false
            font.pixelSize: 12
        }


        Text {
            id: txtCopyright
            x: 0
            y: 138
            color: "#2b2a2a"
            text: qsTr("Copyright (C) <2012-2025>  Dreamsder")
            wrapMode: Text.NoWrap
            font.family: "Arial"
            font.bold: false
            //
            font.pixelSize: 12
        }


        Text {
            id: txtTelefono
            color: "#2b2a2a"
            text: qsTr("Teléfono: (+598) 097225884")
            //
            font.pixelSize: 12
            font.family: "Arial"
        }


        Text {
            id: txtWeb
            color: "#2b2a2a"
            text: qsTr("Sitio Web: www.khitomer-software.org")
            //
            visible: false
            font.pixelSize: 12
            font.family: "Arial"
        }

        Text {
            id: txtEmails
            x: 0
            y: 2
            color: "#2b2a2a"
            text: qsTr("E-mail: cristianmontano@gmail.com")
            //
            visible: false
            font.pixelSize: 12
            font.family: "Arial"
        }
        Text {
            id: txtLicencia
            x: 0
            y: 232
            color: "#2b2a2a"
            text: qsTr("Licencia Pública General GNU versión 3")
            font.family: "Arial"
            font.bold: false
            //
            font.pixelSize: 12
        }
        Text {
            id: txtImpresoraPredeterminada
            x: 0
            y: 0
            color: "#2b2a2a"
            text: qsTr("Impresora predeterminada:  "+funcionesmysql.impresoraPorDefecto())
            font.family: "Arial"
            //
            font.pixelSize: 12
        }

        TextEdit {
            id: txtCreditos
            color: "#2b2a2a"
            text: "Contribuyentes: Maria Montano - mmontano@dreamsder.com\n                          Cristian Montano - cristianmontano@gmail.com\nLibreria XLS creada por: Yap Chun Wei - Martin Fuchs - Ami Castonguay - Long Wenbiao\nLibreria JSON creada por: Eeli Reilin\nLibreria base64 creada por: René Nyffenegger\nLibreria base64-NibbleAndAHalf creada por:  William Sherif\nLibreria CURL creada por:  Daniel Stenberg"
            //
            font.pixelSize: 12
            font.family: "Arial"
        }
    }

   /* Image {
        id: imgFacebook
        x: 243
        y: 338
        width: 100
        height: 100
        opacity: 0.600
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        asynchronous: true
        anchors.right: parent.right
        anchors.rightMargin: 50
        smooth: true

        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Facebook.png"


    }*/

   /* Image {
        id: imgYouTube
        x: 240
        y: 336
        width: 100
        height: 100
        opacity: 0.600
        asynchronous: true

        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/YouTube.png"
        anchors.bottom: parent.bottom
        anchors.rightMargin: 25
        anchors.bottomMargin: 40
        anchors.right: imgFacebook.left
        smooth: true
    }*/

    PropertyAnimation{
        id:opacidadIn
        property: "opacity"
        to:1
        duration: 200
    }

  /*  Particles {
        anchors.fill: parent
        clip: true
        source:
        {
            if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1"){
                "qrc:/imagenes/qml/ProyectoQML/Imagenes/LogoKhitomerCFE-20-03-2018_512px.png"
            }else{
                "qrc:/imagenes/qml/ProyectoQML/Imagenes/LogoKhitomer-19-07-2016_512px.png"
            }
        }


        lifeSpan: 6000
        count: 2
        angle: 70
        opacity: 0.1
        angleDeviation: 36
        velocity: 30
        velocityDeviation: 10
        ParticleMotionWander {
            xvariance: 1
            pace: 100
        }
    }*/

    PropertyAnimation{
        id:opacidadOff
        property: "opacity"
        to:0.600
        duration: 50
    }

    Image {
        id: imgLogoKhitomer
        width: 200
        height: 200
        anchors.top: parent.top
        anchors.topMargin: 70
        asynchronous: true
        anchors.right: parent.right
        anchors.rightMargin: 50
        smooth: true
        opacity: 1
        source:

        {
            if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1"){
                "qrc:/imagenes/qml/ProyectoQML/Imagenes/LogoKhitomerCFE-20-03-2018_512px.png"
            }else{
                "qrc:/imagenes/qml/ProyectoQML/Imagenes/LogoKhitomer-19-07-2016_512px.png"
            }
        }



        /*MouseArea {
            id: mouse_area1
            hoverEnabled: true
            anchors.fill: parent
            onClicked: {
                funcionesmysql.abrirPaginaWeb("http://www.khitomer-software.org")
            }
            onEntered: {
                opacidadOff.from=imgFacebook.opacity
                opacidadOff.target=imgLogoKhitomer
                opacidadOff.start()

                opacidadIn.target=imgLogoKhitomer
                opacidadIn.from=imgLogoKhitomer.opacity
                opacidadIn.start()
            }
            onExited: {
                opacidadIn.target=imgLogoKhitomer
                opacidadOff.target=imgLogoKhitomer
                opacidadIn.stop()
                opacidadOff.start()
            }
        }*/
    }

    Image {
        id: imgQtdigia
        y: 345
        width: 92
        height: 100
        anchors.left: parent.left
        anchors.leftMargin: 50
        opacity: 0.6
        asynchronous: true
        anchors.bottomMargin: 40
        MouseArea {
            id: mouse_areaFacebook1
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                funcionesmysql.abrirPaginaWeb("http://www.qt.io/")
            }

            onEntered: {
                opacidadOff.from=imgQtdigia.opacity
                opacidadOff.target=imgQtdigia
                opacidadOff.start()

                opacidadIn.target=imgQtdigia
                opacidadIn.from=imgQtdigia.opacity
                opacidadIn.start()
            }
            onExited: {
                opacidadIn.target=imgQtdigia
                opacidadOff.target=imgQtdigia
                opacidadIn.stop()
                opacidadOff.start()
            }
        }
        anchors.bottom: parent.bottom
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Built_with_Qt_logo_RGB_vertical.png"
        smooth: true
    }








}
