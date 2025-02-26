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




    Rectangle {
        id: rectAutorizacion
        color: "#be231919"
        visible: false
        anchors.fill: parent
        //
        z: 8


        property alias visibilidadCuadro: rectAutorizacion.visible
        property string permisosAEvaluar: ""
        signal confirmacion
        signal precionarEscape

        signal noRequiereAutorizacion

        function evaluarPermisos(permiso){
            txtMensajeInformacionAutorizaciones.visible=false
            permisosAEvaluar=permiso
            serearCuadro()
            visibilidadCuadro=true
            tomarElFoco()
        }

        function noSeRequierenAutorizaciones(permiso){
            permisosAEvaluar=permiso
            noRequiereAutorizacion()
        }

        function tomarElFoco(){
            txtContraseniaDeUsuarioAutorizaciones.tomarElFoco()

            //txtNombreDeUsuarioAutorizaciones.forceActiveFocus()
            txtNombreDeUsuarioAutorizaciones.tomarElFoco()
        }

        function serearCuadro(){
            txtContraseniaDeUsuarioAutorizaciones.textoInputBox=""
            txtNombreDeUsuarioAutorizaciones.textoInputBox=""
        }




        MouseArea {
            id: mouse_area2
            anchors.fill: parent
            hoverEnabled: true


            Rectangle {
                id: rectAccesoAutorizaciones
                x: 238
                y: 210
                width: 400
                height: 200
                color: "#1d7195"
                radius: 5
                clip: true
                visible: true
                border.color: "#1d7195"
                //
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: txtAcceso
                    color: "#fdfbfb"
                    text: qsTr("Autorización")
                    font.family: "Arial"
                    //
                    font.pixelSize: 37
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    style: Text.Normal
                    font.italic: false
                    font.bold: false
                    focus: false
                    anchors.leftMargin: 30
                    anchors.left: parent.left
                }

                TextInputSimple {
                    id: txtNombreDeUsuarioAutorizaciones
                    x: 20
                    y: 83
                    width: 230
                    height: 35
                    //
                    textoInputBox: ""
                    anchors.horizontalCenter: parent.horizontalCenter
                    echoMode: 0
                    textoDeFondo: "usuario autorizado"
                    botonBorrarTextoVisible: true
                    textoTitulo: "Usuario:"

                    onEnter: txtContraseniaDeUsuarioAutorizaciones.tomarElFoco()

                    onTabulacion: txtContraseniaDeUsuarioAutorizaciones.tomarElFoco()

                    Keys.onEscapePressed: {
                        precionarEscape()                       
                        txtMensajeInformacionAutorizaciones.visible=false
                        serearCuadro()
                        visibilidadCuadro=false
                    }
                }

                TextInputSimple {
                    id: txtContraseniaDeUsuarioAutorizaciones
                    x: 20
                    y: 126
                    width: 230
                    height: 35
                    //
                    anchors.horizontalCenter: parent.horizontalCenter
                    echoMode: 2
                    largoMaximo: 25
                    textoDeFondo: "clave privada de autorización"
                    botonBorrarTextoVisible: true
                    textoTitulo: "Contraseña:"
                    onEnter: {

                        if(modeloUsuarios.conexionUsuario(txtNombreDeUsuarioAutorizaciones.textoInputBox.toString().trim(),txtContraseniaDeUsuarioAutorizaciones.textoInputBox.toString().trim())){

                            if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuarioAutorizaciones.textoInputBox.trim()),permisosAEvaluar)){



                                txtMensajeInformacionAutorizaciones.visible=false
                                serearCuadro()
                                confirmacion()
                                visibilidadCuadro=false

                            }else{
                                timeReajustarGradient.stop()
                                rectAccesoAutorizaciones.color="#ba3e2b"
                                rectAccesoAutorizaciones.border.color="#ba3e2b"
                                rectangle2.color="#ba3e2b"
                                timeReajustarGradient.start()
                                txtMensajeInformacionAutorizaciones.visible=true
                                txtMensajeInformacionAutorizaciones.text="Autorización rechazada"

                            }

                        }else{
                            timeReajustarGradient.stop()
                            rectAccesoAutorizaciones.color="#ba3e2b"
                            rectAccesoAutorizaciones.border.color="#ba3e2b"
                            rectangle2.color="#ba3e2b"
                            timeReajustarGradient.start()
                            txtMensajeInformacionAutorizaciones.visible=true
                            txtMensajeInformacionAutorizaciones.text="Autorización rechazada"

                        }

                    }
                    onTabulacion: txtNombreDeUsuarioAutorizaciones.tomarElFoco()

                    Keys.onEscapePressed: {
                        precionarEscape()                        
                        txtMensajeInformacionAutorizaciones.visible=false
                        serearCuadro()
                        visibilidadCuadro=false
                    }

                }

                Timer{
                    id:timeReajustarGradient
                    interval: 2000
                    repeat: false
                    running:false
                    onTriggered: {

                        rectAccesoAutorizaciones.color="#1d7195"
                        rectAccesoAutorizaciones.border.color="#1d7195"
                        rectangle2.color="#1d7195"
                        txtMensajeInformacionAutorizaciones.visible=false
                    }

                }

                Image {
                    id: imageIconoLogin
                    x: 308
                    width: 51
                    height: 51
                    //
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    asynchronous: true
                    source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Acceso.png"
                    anchors.rightMargin: 20
                    focus: false
                    anchors.right: parent.right
                    opacity: 0.680
                }

                Rectangle {
                    id: rectLiniaAcceso
                    height: 1
                    color: "#c2bfbf"
                    radius: 1
                    //
                    anchors.top: parent.top
                    anchors.topMargin: 72
                    anchors.rightMargin: 20
                    focus: false
                    anchors.right: parent.right
                    anchors.leftMargin: 30
                    anchors.left: parent.left
                }

                Text {
                    id: txtMensajeInformacionAutorizaciones
                    y: 7
                    color: "#ffffff"
                    text: qsTr("")
                    z: 1
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    //
                    font.pixelSize: 15
                    visible: false
                    styleColor: "#ffffff"
                    font.bold: true
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignTop
                    width: txtMensajeInformacionAutorizaciones.implicitWidth
                }

                Rectangle {
                    id: rectangle1
                    x: -1
                    y: 9
                    width: 10
                    anchors.top: parent.top
                    clip: true
                    Rectangle {
                        id: rectangle2
                        width: 3
                        height: parent.height/1.50
                        color: "#1e7597"
                        radius: 5
                        opacity: 0.8
                        anchors.leftMargin: 5
                        anchors.bottomMargin: -1
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                    }
                    gradient: Gradient {
                        GradientStop {
                            position: 0
                            color: "#0f4c7d"
                        }

                        GradientStop {
                            position: 1
                            color: "#1a2329"
                        }
                    }
                    anchors.leftMargin: 5
                    anchors.bottomMargin: -1
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.topMargin: -1
                }
                anchors.verticalCenter: parent.verticalCenter
                focus: false
                opacity: 1
            }

        }
    }
