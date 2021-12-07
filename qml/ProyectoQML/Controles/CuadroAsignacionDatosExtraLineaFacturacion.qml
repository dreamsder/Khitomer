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




    Rectangle {
        id: rectRoot
        color: "#be231919"
        visible: true
        anchors.fill: parent
        //
        z: 8


        property alias visibilidadCuadro: rectRoot.visible
        property string permisosAEvaluar: ""
        property int indiceDeLineaDocumento: 0
        signal confirmacion
        signal precionarEscape

        property string valorDato: ""
        property string nuevoValorDato: ""


        function cargarDatoActual(_datoActual,_indiceLinea){
            var dato=_datoActual
            indiceDeLineaDocumento=_indiceLinea
            txtDatoAModificar.textoInputBox=dato.trim()
            valorDato=dato.trim()
        }


        function  mostrarErrorCuadroDatosExtra(){

            timeReajustarGradientCambiarDatosExtra.stop()
            timeReajustarGradientCambiarDatosExtra.start()
            txtMensajeInformacionCambiarDatosExtra.visible=true
            txtMensajeInformacionCambiarDatosExtra.text="ATENCION: Error al actualizar artículo"

        }


        MouseArea {
            id: mouse_area2
            anchors.fill: parent


            Rectangle {
                id: rectContenedor
                x: 238
                y: 210
                width: 500
                height: 180
                color: "#1d7195"
                radius: 0
                clip: true
                visible: true
                border.color: "#1d7195"
                //
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: lblTitulo
                    color: "#ffffff"
                    text: modeloListaTipoDocumentosComboBox.retornaDescripcionCodigoADemanda(cbListatipoDocumentos.codigoValorSeleccion)
                    style: Text.Raised
                    font.underline: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.bold: true
                    font.family: "Verdana"
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    font.pixelSize: 14
                }


                TextInputSimple {
                    id: txtDatoAModificar
                    textoInputBox: ""
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 400
                    anchors.top: parent.top
                    anchors.topMargin: 70                                        
                  //  largoMaximo: 30
                    largoMaximo: {

                        if(modeloconfiguracion.retornaValorConfiguracion("CODIGO_BARRAS_A_DEMANDA_EXTENDIDO")=="1"){
                            600
                        }else{
                            30
                        }
                    }

                    fijoTamanioPersonalizado:{
                                                  if(modeloconfiguracion.retornaValorConfiguracion("CODIGO_BARRAS_A_DEMANDA_EXTENDIDO")=="1"){
                                                        400
                                                  }else{
                                                        0
                                                  }
                                              }



                    botonBorrarTextoVisible: true
                    textoTitulo: {
                                      if(visible){
                                         modeloListaTipoDocumentosComboBox.retornaDescripcionCodigoADemanda(cbListatipoDocumentos.codigoValorSeleccion)
                                      }else{
                                          ""
                                      }
                     }

                    Keys.onEscapePressed: {
                        precionarEscape()
                    }
                }


                BotonPaletaSistema {
                    id: btnCancelarOperacion
                    text: "Cancelar"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    anchors.right: btnGuardar.left
                    anchors.rightMargin: 10
                    border.color: "#787777"
                    colorTextoMensajeError: "White"

                    onClicked: precionarEscape()
                }

                BotonPaletaSistema {
                    id: btnGuardar
                    x: 6
                    y: 9
                    text: "Guardar"
                    anchors.right: parent.right
                    anchors.rightMargin: 25
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    border.color: "#787777"
                    colorTextoMensajeError: "White"

                    onClicked: {

                        nuevoValorDato=txtDatoAModificar.textoInputBox.trim()
                        confirmacion()

                    }


                }

                Timer{
                    id:timeReajustarGradientCambiarDatosExtra
                    interval: 3000
                    repeat: false
                    running:false
                    onTriggered: {

                        rectangle2.color="#1d7195"
                        txtMensajeInformacionCambiarDatosExtra.visible=false
                    }

                }


                Text {
                    id: txtMensajeInformacionCambiarDatosExtra
                    y: 7
                    color: "#ffffff"
                    text: qsTr("ffff")
                    anchors.right: btnCancelarOperacion.left
                    anchors.rightMargin: 10
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
