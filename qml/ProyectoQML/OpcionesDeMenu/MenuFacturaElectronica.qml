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

import QtQuick 1.1
import "../Controles"
import "../Listas"

Rectangle {
    id: rectPrincipalMenuCFE
    width: 500
    height: 500
    color: "#00000000"
    //

    Text {
        id: txtTituloMenuOpcion
        x: 560
        color: "#4d5595"
        text: qsTr("mantenimiento factura electronica")
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

    Flow {
        id: flow1
        x: 30
        y: 101
        layoutDirection: Qt.LeftToRight
        spacing: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        z: 1
        flow: Flow.TopToBottom
        anchors.top: parent.top
        anchors.topMargin: 70
        anchors.rightMargin: 10
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.left: parent.left



        BotonPaletaSistema {
            id: btnCargarClavePublica
            text: "Cargar clave publica"
            border.color: "#787777"
            colorTextoMensajeError: "White"

            onClicked: modelo_CFE_ParametrosGenerales.cargarClavePublica()


        }

        TextInputSimple {
            id: txtIdUsuarioWSCFE
            colorDeTitulo: "#333333"
            textoInputBox: modelo_CFE_ParametrosGenerales.retornaValor("username")
            botonBuscarTextoVisible: false
            inputMask: ""
            largoMaximo: 35
            botonBorrarTextoVisible: true
            textoTitulo: "Usuario WS:"

            onEnter: txtContraseniaWSCFE.tomarElFoco()

            onTabulacion: txtContraseniaWSCFE.tomarElFoco()
        }

        TextInputSimple {
            id: txtContraseniaWSCFE
            height: 35
            largoMaximo: 25
            colorDeTitulo: "#333333"
            textoInputBox: modelo_CFE_ParametrosGenerales.retornaValor("password")
            //
            echoMode: 2
            textoDeFondo: "clave privada"
            botonBorrarTextoVisible: true
            textoTitulo: "Contraseña WS:"

            onEnter: txturlImixProduccion.tomarElFoco()

            onTabulacion: txturlImixProduccion.tomarElFoco()
        }


        TextInputSimple {
            id: txturlImixProduccion
            textoInputBox: modelo_CFE_ParametrosGenerales.retornaValor("urlImixProduccion")
            botonBorrarTextoVisible: true
            textoTitulo: "url Imix Produccion:"
            inputMask: ""
            colorDeTitulo: "#333333"
            botonBuscarTextoVisible: false
            largoMaximo: 300


            onEnter: txturlImixTesting.tomarElFoco()

            onTabulacion: txturlImixTesting.tomarElFoco()
        }



        TextInputSimple {
            id: txturlImixTesting
            textoInputBox: modelo_CFE_ParametrosGenerales.retornaValor("urlImixTesting")
            botonBorrarTextoVisible: true
            textoTitulo: "url Imix Testing:       "
            inputMask: ""
            colorDeTitulo: "#333333"
            botonBuscarTextoVisible: false
            largoMaximo: 300

            onEnter: txturlDynamia.tomarElFoco()

            onTabulacion: txturlDynamia.tomarElFoco()

        }

        TextInputSimple {
            id: txturlDynamia
            textoTitulo: "url Dynamia:"
            largoMaximo: 300
            inputMask: ""
            colorDeTitulo: "#333333"
            botonBorrarTextoVisible: true
            botonBuscarTextoVisible: false
            textoInputBox: modelo_CFE_ParametrosGenerales.retornaValor("urlWS")

        }

        TextInputSimple {
            id: txtToken
            textoTitulo: "Token:"
            largoMaximo: 300
            inputMask: ""
            colorDeTitulo: "#333333"
            botonBorrarTextoVisible: true
            botonBuscarTextoVisible: false
            textoInputBox: modelo_CFE_ParametrosGenerales.retornaValor("token")
        }

        TextInputSimple {
            id: txtUrlDGI
            textoTitulo: "url para ver Comprobantes:"
            largoMaximo: 300
            inputMask: ""
            colorDeTitulo: "#333333"
            botonBorrarTextoVisible: true
            botonBuscarTextoVisible: false
            textoInputBox: modelo_CFE_ParametrosGenerales.retornaValor("urlDGI")
        }

        CheckBox {
            id: cbModoProduccion
            x: 396
            y: 97
            chekActivo: {

                if(modelo_CFE_ParametrosGenerales.retornaValor("modoTrabajoCFE")==="1"){
                    true
                }else{
                    false
                }

            }

            colorTexto: "#333333"
            textoValor: "Operar con datos de Produccion"
        }

        BotonPaletaSistema {
            id: btnCargarLogoTicket
            text: "Cargar logo Ticket"
            border.color: "#787777"
            colorTextoMensajeError: "White"
            onClicked: {
                if(modelo_CFE_ParametrosGenerales.cargarLogoImpresora()){
                    imgLogoImpresora.source="data:image/png;base64," + modelo_CFE_ParametrosGenerales.retornaValor("logoImpresoraTicket")
                }
            }
        }
        Image {
            id: imgLogoImpresora
            width: 212
            height: 70
            source:{

                if(modelo_CFE_ParametrosGenerales.retornaValor("logoImpresoraTicket")==""){
                    ""
                }else{
                    "data:image/png;base64," + modelo_CFE_ParametrosGenerales.retornaValor("logoImpresoraTicket")
                }

            }



        }
    }

    Row {
        id: rowBarraDeHerramientas
        x: 30
        y: 55
        height: 30
        visible: true
        //
        spacing: 15
        anchors.bottom: flow1.top
        anchors.rightMargin: 10
        anchors.bottomMargin: 15
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.left: parent.left

        BotonBarraDeHerramientas {
            id: botonGuardarConfiguracionCFE
            x: 61
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            toolTip: "Gurardar configuracion CFE"
            anchors.verticalCenter: parent.verticalCenter
            z: 7

            onClic: {

                txtMensajeInformacion.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                    var esProduccion=0

                    if(cbModoProduccion.chekActivo)
                        esProduccion=1



                    if(modelo_CFE_ParametrosGenerales.actualizarDatoParametroCFE(txtIdUsuarioWSCFE.textoInputBox.trim(),"username")){
                        if(modelo_CFE_ParametrosGenerales.actualizarDatoParametroCFE(txtContraseniaWSCFE.textoInputBox.trim(),"password")){
                            if(modelo_CFE_ParametrosGenerales.actualizarDatoParametroCFE(txturlImixProduccion.textoInputBox.trim(),"urlImixProduccion")){
                                if(modelo_CFE_ParametrosGenerales.actualizarDatoParametroCFE(txturlImixTesting.textoInputBox.trim(),"urlImixTesting")){
                                    if(modelo_CFE_ParametrosGenerales.actualizarDatoParametroCFE(txturlDynamia.textoInputBox.trim(),"urlWS")){
                                        if(modelo_CFE_ParametrosGenerales.actualizarDatoParametroCFE(txtToken.textoInputBox.trim(),"token")){
                                            if(modelo_CFE_ParametrosGenerales.actualizarDatoParametroCFE(txtUrlDGI.textoInputBox.trim(),"urlDGI")){

                                                var valor="0"
                                                if(esProduccion){
                                                    valor="1"
                                                }

                                                if(modelo_CFE_ParametrosGenerales.actualizarDatoParametroCFE(valor,"modoTrabajoCFE")){

                                                    txtMensajeInformacion.color="#2f71a0"
                                                    txtMensajeInformacion.text="Información actualizada correctamente"

                                                }else{
                                                    txtMensajeInformacion.color="#d93e3e"
                                                    txtMensajeInformacion.text="ATENCION: No se pudo guardar la configuración el modo"
                                                }
                                            }else{
                                                txtMensajeInformacion.color="#d93e3e"
                                                txtMensajeInformacion.text="ATENCION: No se pudo guardar la configuración de url DGI"
                                            }
                                        }else{
                                            txtMensajeInformacion.color="#d93e3e"
                                            txtMensajeInformacion.text="ATENCION: No se pudo guardar la configuración de token"
                                        }
                                    }else{
                                        txtMensajeInformacion.color="#d93e3e"
                                        txtMensajeInformacion.text="ATENCION: No se pudo guardar la configuración de url Dynamia"
                                    }
                                }else{
                                    txtMensajeInformacion.color="#d93e3e"
                                    txtMensajeInformacion.text="ATENCION: No se pudo guardar la configuración de url Imix Testing"
                                }
                            }else{
                                txtMensajeInformacion.color="#d93e3e"
                                txtMensajeInformacion.text="ATENCION: No se pudo guardar la configuración de url Imix Produccion de CFE"
                            }
                        }else{
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="ATENCION: No se pudo guardar la configuración de contraseña de CFE"
                        }
                    }else{
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: No se pudo guardar la configuración del usuario de CFE"
                    }
            }
        }

        Text {
            id: txtMensajeInformacion
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            font.family: "Arial"
            //
            font.pixelSize: 14
            style: Text.Raised
            visible: false
            styleColor: "#ffffff"
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignTop
        }

    }

    Rectangle {
        id: rectLineaVerticalMenuGris
        height: 1
        color: "#abb2b1"
        //
        anchors.top: rowBarraDeHerramientas.bottom
        anchors.topMargin: 5
        anchors.rightMargin: 0
        visible: true
        rotation: 0
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    Rectangle {
        id: rectLineaVerticalMenuBlanco
        x: -7
        height: 1
        color: "#ffffff"
        //
        anchors.top: rowBarraDeHerramientas.bottom
        anchors.topMargin: 4
        anchors.rightMargin: 0
        visible: true
        rotation: 0
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.left: parent.left
    }


    Timer{
        id:txtMensajeInformacionTimer
        repeat: false
        interval: 5000
        onTriggered: {

            txtMensajeInformacion.visible=false
            txtMensajeInformacion.color="#d93e3e"

        }
    }

}
