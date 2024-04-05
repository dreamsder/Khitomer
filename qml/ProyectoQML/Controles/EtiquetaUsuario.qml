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
    id: rectPrincipalEtiqueUsuario
    width: txtNombreUsuarioLogueado.implicitWidth+20
    height: 25
    color: "#00000000"
    //
    rotation: -90
    Keys.onEscapePressed: {
        rectPrincipalComboBox.visible=false
    }


    property bool visibleComboBox: false
    signal clic

    function setearUsuario(usuario){
        txtNombreUsuarioLogueado.text=usuario;
    }

    function setarEstadoMysql(valor){
        if(valor==true){
            rectStatusConectividadMysql.color ="#639559"
        }else if(valor==false){
            rectStatusConectividadMysql.color="#e0634d"
        }
    }
    function setarEstadoServidor(valor){
        if(valor==true){
            rectStatusConectividadServidor.color ="#639559"
        }else if(valor==false){
            rectStatusConectividadServidor.color="#e0634d"
        }
    }
    function cerrarComboBox(){
        rectPrincipalComboBox.visible=false
    }



    Rectangle {
        id: rectangle1
        color: "#00000000"
        clip: true
        opacity: 1
        anchors.fill: parent

        Rectangle {
            id: rectangle4
            x: 3
            y: 3
            color: "#2f2c2c"
            radius: 2
            z: 1
            //
            anchors.rightMargin: 2
            anchors.leftMargin: 2
            anchors.bottomMargin: 2
            anchors.topMargin: 2
            anchors.fill: parent

            Text {
                id: txtNombreUsuarioLogueado
               // x: 44
               // y: 9
                color: "#ffffff"
                text: qsTr("Cristian Montano")
                font.family: "Arial"
                style: Text.Sunken
                font.bold: true
                //
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: sizeTitulosControles

                MouseArea {
                    id: mouse_area1
                    anchors.topMargin: -5
                    anchors.bottomMargin: -5
                    anchors.rightMargin: -9
                    anchors.leftMargin: -9
                    anchors.fill: parent
                    onClicked: {
                        if(!rectPrincipalComboBox.visible){
                            visibleComboBox=true
                            rectPrincipalComboBox.visible=true
                            txtContraseniaDeUsuarioActual.textoInputBox=""
                            txtContraseniaDeUsuarioNueva.textoInputBox=""
                            txtContraseniaDeUsuarioReingreso.textoInputBox=""
                            txtContraseniaDeUsuarioActual.tomarElFoco()

                        }else{
                            visibleComboBox=false
                            rectPrincipalComboBox.visible=false
                        }
                        clic()
                    }
                }
        }
        }

        Rectangle {
            id: rectStatusConectividadServidor
            x: 83
            y: -81
            width: 129
            height: 153
            color: "#639559"
            anchors.left: parent.left
            anchors.leftMargin: (rectPrincipalEtiqueUsuario.width/2)+10
            //
            rotation: -40
        }

        Rectangle {
            id: rectStatusConectividadMysql
            x: -66
            y: -47
            width: 129
            height: 153
            color: "#639559"
            anchors.right: parent.right
            anchors.rightMargin: (rectPrincipalEtiqueUsuario.width/2)+10
            rotation: -40
            //
        }
    }

    Rectangle {
        id: rectPrincipalComboBox
        x: 0
        y: 39
        rotation: 90
        width: 300
        height: 242
        color: "#eceeee"
        radius: 3
        border.color: "#a8a0a0"
        anchors.rightMargin: -250
        visible: false
        border.width: 1
        z: 2000
        anchors.right: parent.right


        MouseArea {
            id: mouse_area4
            anchors.fill: parent

            BotonBarraDeHerramientas {
                id: botonCerrarLista
                x: 456
                y: 5
                width: 18
                height: 18
                z: 4
                //
                anchors.top: parent.top
                anchors.topMargin: 5
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/CerrarLista.png"
                visible: true
                anchors.rightMargin: 5
                anchors.right: parent.right

                onClic: {
                    cerrarComboBox()
                }
            }

           /* Rectangle {
                id: rectangle3
                x: 194
                y: -6
                width: 25
                height: 25
                color: rectPrincipalComboBox.color
                anchors.right: parent.right
                anchors.rightMargin: 25
                anchors.top: parent.top
                anchors.topMargin: -6
                rotation: 45
                z: 1
            }*/

            Rectangle {
                id: rectLineaSuperior
                y: 5
                height: 2
                color: "#201c1c"
                radius: 1
                //
                anchors.bottom: parent.bottom
                visible: true
                anchors.rightMargin: 1
                anchors.bottomMargin: 0
                z: 3
                anchors.right: parent.right
                anchors.leftMargin: 1
                anchors.left: parent.left
            }

            TextInputSimple {
                id: txtContraseniaDeUsuarioActual
                y: 48
                height: 35
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 10
                //
                echoMode: 2
                largoMaximo: 25
                textoDeFondo: "clave privada"
                botonBorrarTextoVisible: true
                textoTitulo: "Contraseña actual:"
                colorDeTitulo: "#333333"
                onTabulacion: txtContraseniaDeUsuarioNueva.tomarElFoco()
                onEnter: txtContraseniaDeUsuarioNueva.tomarElFoco()


            }

            TextInputSimple {
                id: txtContraseniaDeUsuarioNueva
                x: 0
                height: 35
                anchors.top: txtContraseniaDeUsuarioActual.bottom
                anchors.topMargin: 24
                //
                echoMode: 2
                anchors.rightMargin: 0
                botonBorrarTextoVisible: true
                textoDeFondo: "ingrese la nueva clave"
                largoMaximo: 25
                textoTitulo: "Nueva contraseña:"
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.left: parent.left
                colorDeTitulo: "#333333"
                onTabulacion: txtContraseniaDeUsuarioReingreso.tomarElFoco()
                onEnter: txtContraseniaDeUsuarioReingreso.tomarElFoco()
            }

            TextInputSimple {
                id: txtContraseniaDeUsuarioReingreso
                x: 6
                y: 9
                height: 35
                //
                anchors.top: txtContraseniaDeUsuarioNueva.bottom
                anchors.topMargin: 5
                echoMode: 2
                anchors.rightMargin: 0
                largoMaximo: 25
                textoDeFondo: "reingrese la nueva clave"
                botonBorrarTextoVisible: true
                textoTitulo: "Reingrese nueva contraseña:"
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.left: parent.left
                colorDeTitulo: "#333333"
                onTabulacion: txtContraseniaDeUsuarioActual.tomarElFoco()
                onEnter: txtContraseniaDeUsuarioActual.tomarElFoco()
            }

            BotonPaletaSistema {
                id: btnActualizarContrasenia
                x: 160
                text: "Guardar cambios"
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.top: txtContraseniaDeUsuarioReingreso.bottom
                anchors.topMargin: 20
                onClicked: {
                    mensajeError("")
                    if(txtContraseniaDeUsuarioActual.textoInputBox.trim()!="" && txtContraseniaDeUsuarioNueva.textoInputBox.trim()!="" && txtContraseniaDeUsuarioReingreso.textoInputBox.trim()!=""){
                        if(txtContraseniaDeUsuarioNueva.textoInputBox.trim()==txtContraseniaDeUsuarioReingreso.textoInputBox.trim()){
                            if(modeloUsuarios.conexionUsuario(txtNombreDeUsuario.textoInputBox.trim(),txtContraseniaDeUsuarioActual.textoInputBox.trim())){

                                var resultadoActualizacion=modeloUsuarios.actualizarClave(txtNombreDeUsuario.textoInputBox.trim(),txtContraseniaDeUsuarioNueva.textoInputBox.trim())
                                if(resultadoActualizacion==-4){
                                    mensajeError("Error acceso a base de datos")
                                    txtContraseniaDeUsuarioActual.tomarElFoco()
                                }else if(resultadoActualizacion==-2){
                                    mensajeError("No se pudo actualizar la clave")
                                    txtContraseniaDeUsuarioActual.tomarElFoco()
                                }else if(resultadoActualizacion==-1){
                                    mensajeError("Sin conexión a la base de datos")
                                    txtContraseniaDeUsuarioActual.tomarElFoco()
                                }else if(resultadoActualizacion==2){
                                    mensajeError("Actualización ok")
                                    txtContraseniaDeUsuarioActual.textoInputBox=""
                                    txtContraseniaDeUsuarioNueva.textoInputBox=""
                                    txtContraseniaDeUsuarioReingreso.textoInputBox=""
                                    txtContraseniaDeUsuarioActual.tomarElFoco()
                                }
                            }else{
                                mensajeError("Contraseña actual incorrecta")
                                txtContraseniaDeUsuarioActual.tomarElFoco()
                            }
                        }else{
                            mensajeError("Contraseñas no coinciden")
                            txtContraseniaDeUsuarioNueva.tomarElFoco()
                        }
                    }else{
                        mensajeError("Faltan datos a ingresar")
                        txtContraseniaDeUsuarioActual.tomarElFoco()
                    }
                }
            }

            Text {
                id: lblCambioDeContrasenia
                text: qsTr("Cambio de contraseña:")
                font.family: "Arial"
                //
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 10
                font.pixelSize: 12
            }
        }

    }

}
