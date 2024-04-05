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
import "Controles"
import "Listas"

Rectangle {
    id: rectangle2
    width: 1000
    height: 700
    color: "#764fc7"
    border.width: 0
    clip: true
    visible: true



    function guardarConfiguracion(){

        if(txtHost.textoInputBox.trim()!="" && txtBaseDeDatos.textoInputBox.trim()!="" && txtPassword.textoInputBox.trim()!="" && txtPuerto.textoInputBox.trim()!="" && txtUsuario.textoInputBox.trim()!=""){
            if(funcionesmysql.guardarConfiguracionXML(txtHost.textoInputBox.trim(),txtUsuario.textoInputBox.trim(),txtPassword.textoInputBox.trim(),txtPuerto.textoInputBox.trim(),txtBaseDeDatos.textoInputBox.trim())){
                funcionesmysql.mensajeAdvertenciaOk("La configuración se guardo satisfactoriamente, se procedera a cargar la aplicación Khitomer.");
                Qt.quit();
            }else{
                funcionesmysql.mensajeAdvertenciaOk("No se pudo guardar la configuración, reintente nuevamente.");
                txtHost.tomarElFoco()
            }
        }else{
            funcionesmysql.mensajeAdvertenciaOk("Faltan datos a cargar para poder guardar la configuración.\nRevise los campos y reintente.")
            txtHost.tomarElFoco()
        }


    }



    Rectangle {
        id: rectangle1
        // color: "#4ab2c7"
        color: "#ef7930"
        radius: 41
        border.width: 0
        anchors.rightMargin: 150
        anchors.leftMargin: 150
        anchors.bottomMargin: 150
        anchors.topMargin: 150
        anchors.fill: parent

        Column {
            id: column1
            anchors.rightMargin: 30
            anchors.leftMargin: 50
            anchors.bottomMargin: 50
            anchors.topMargin: 30
            anchors.fill: parent
            spacing: 10

            TextInputSimple {
                id: txtHost
                width: 200
                textoDeFondo: "ip del servidor mysql"
                textoInputBox: "localhost"
                botonBorrarTextoVisible: true
                botonBuscarTextoVisible: false
                largoMaximo: 30
                textoTitulo: "Host:"



                Component.onCompleted: txtHost.tomarElFoco()
            }

            TextInputSimple {
                id: txtPuerto
                width: 200
                textoDeFondo: "puerto servidor mysql"
                textoInputBox: "3306"
                botonBuscarTextoVisible: false
                largoMaximo: 30
                botonBorrarTextoVisible: true
                textoTitulo: "Puerto:"
            }

            TextInputSimple {
                id: txtBaseDeDatos
                width: 200
                textoDeFondo: "nombre base de datos"
                textoInputBox: ""
                botonBuscarTextoVisible: false
                largoMaximo: 30
                botonBorrarTextoVisible: true
                textoTitulo: "Base de datos:"
            }

            TextInputSimple {
                id: txtUsuario
                width: 200
                textoDeFondo: "usuario base de datos"
                textoInputBox: ""
                botonBuscarTextoVisible: false
                largoMaximo: 30
                botonBorrarTextoVisible: true
                textoTitulo: "Usuario:"
            }

            TextInputSimple {
                id: txtPassword
                width: 200
                textoDeFondo: "contraseña base de datos"
                inputMask: ""
                textoInputBox: ""
                botonBuscarTextoVisible: false
                largoMaximo: 30
                botonBorrarTextoVisible: true
                textoTitulo: "Contraseña:"
                echoMode: 2
            }
        }

        BotonCargarDato {
            id: btnGuardarConfiguracion
            textoColor: "#ffffff"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            anchors.right: parent.right
            anchors.rightMargin: 50
            texto: "Guardar configuración"

            onClic: {

                guardarConfiguracion()

            }
        }

        BotonCargarDato {
            id: btnCancelarYSalir
            anchors.bottomMargin: 30
            anchors.right: btnGuardarConfiguracion.left
            anchors.rightMargin: 30
            texto: "Salir sin configurar"
            textoColor: "#ffffff"
            anchors.bottom: parent.bottom

            onClic: {
                Qt.quit();
            }
        }

        BotonCargarDato {
            id: btnPredeterminado
            y: 3
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.bottomMargin: 30
            texto: "Configuración predeterminada"
            textoColor: "#ffffff"
            anchors.bottom: parent.bottom

            onClic: {
                txtHost.textoInputBox="localhost"
                txtPuerto.textoInputBox="3306"
                txtBaseDeDatos.textoInputBox="khitomer"
                txtUsuario.textoInputBox="khitomer"
                txtPassword.textoInputBox="khitomer"
            }
        }

        Text {
            id: text1
            height: 19
            color: "#ffffff"
            text: qsTr("Desde aquí podrá configurar el acceso a la base de datos del sistema. Esta configuración se genera por usuario del sistema operativo, por lo tanto, si ingresa al sistema con un usuario diferente, deberá volver a crear esta configuración.")
            wrapMode: Text.WordWrap
            anchors.left: parent.left
            anchors.leftMargin: 270
            textFormat: Text.RichText
            font.bold: true
            anchors.top: parent.top
            anchors.topMargin: 40
            anchors.right: parent.right
            anchors.rightMargin: 30
            z: 2
            font.pixelSize: 16
        }

        Text {
            id: text2
            height: 19
            color: "#ffffff"
            text: qsTr("* El host o IP, es la dirección de acceso a la maquina que contiene el motor de base de datos MySqlm si no esta seguro de que dato ingresar, consulte con su administrador de sistema. ")
            anchors.left: parent.left
            font.pixelSize: 16
            z: 2
            anchors.rightMargin: 30
            anchors.top: text1.bottom
            textFormat: Text.RichText
            anchors.leftMargin: 270
            font.bold: true
            anchors.right: parent.right
            wrapMode: Text.WordWrap
            anchors.topMargin: 20+text1.implicitHeight
        }
    }

    Text {
        id: txtTituloInformativo
        y: 8
        color: "#3d3d4b"
        text: qsTr("configuración de acceso")
        font.italic: true
        font.underline: false
        font.strikeout: false
        anchors.bottom: rectangle1.top
        anchors.bottomMargin: 20
        styleColor: "#f89d2c"
        style: Text.Outline
        textFormat: Text.AutoText
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        clip: false
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: true
        z: 1
        font.pixelSize: 80
    }


}

