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
import "../Listas"
import "../Listas/Delegates"

Rectangle {

    id: rectImpresionListasDePrecioPrincipal
    color: "#be231919"
    visible: true
    anchors.fill: parent
    z: 8

    signal clicCancelar

    signal clicCancelarImprimir

    signal clicImprimir

    property string nombreImpresora: ""

    property string codigoTipoImpresion:"1"

    MouseArea {
        id: mouse_area2
        anchors.fill: parent
        hoverEnabled: true

        Rectangle {
            id: rectImpresionListaPrecios
            width: 500
            height: 300
            color: "#1e7597"
            radius: 5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            BotonFlecha {
                id: botonflechaCerrarVentana
                x: 410
                y: 20
                opacidadRectPrincipal: 0.800
                anchors.top: parent.top
                anchors.topMargin: -15
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/CerrarLista.png"
                anchors.rightMargin: -15
                z: 1
                anchors.right: parent.right
                onClic: {

                    clicCancelar()

                }
            }

            Text {
                id: lblTituloImpresionListaPrecios
                color: "#ffffff"
                text: qsTr("Impresión de envíos")
                style: Text.Raised
                font.underline: true
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: true
                font.family: "Verdana"
                anchors.top: parent.top
                anchors.topMargin: 20
                font.pixelSize: sizeTitulosControles
            }


            Text {
                id: lblInformacionImpresionListaPrecio
                y: 7
                color: "#ffffff"
                text: qsTr("Desde aquí se podran imprimir las hojas de envío.")
                style: Text.Normal
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                anchors.left: parent.left
                anchors.leftMargin: 35
                anchors.right: parent.right
                anchors.rightMargin: 15
                font.underline: false
                anchors.top: lblTituloImpresionListaPrecios.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: sizeTitulosControles
                font.family: "Verdana"
                font.bold: false
                anchors.topMargin: 5
            }


            ComboBoxGenerico{

                id: cbxListaTipoEnvios
                width: 130
                codigoValorSeleccion: "1"
                textoComboBox: "Retira ahora en el local"
                textoTitulo: qsTr("Tipo impresión envío:")
                visible: true
                modeloItems: modeloListaTipoEnvios


                anchors.left: parent.left
                anchors.leftMargin: 35
                anchors.right: parent.right
                anchors.rightMargin: 15
                anchors.top: lblInformacionImpresionListaPrecio.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 5



            }

            ListModel {
                id: modeloListaTipoEnvios

                ListElement {
                    codigoItem: "1"
                    descripcionItem: "Retira ahora en el local"
                }
                ListElement {
                    codigoItem: "2"
                    descripcionItem: "Cadeteria nuestra"
                }
                ListElement {
                    codigoItem: "3"
                    descripcionItem: "Agencia interior"
                }
                ListElement {
                    codigoItem: "4"
                    descripcionItem: "Retira mas adelante"
                }


            }




            BotonPaletaSistema {
                id: btnCancelarOperacion
                text: "No Imprimir"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.right: btnImprimir.left
                anchors.rightMargin: 10
                border.color: "#787777"
                colorTextoMensajeError: "White"

                onClicked: clicCancelarImprimir()
            }

            BotonPaletaSistema {
                id: btnImprimir
                x: 6
                y: 9
                text: "Imprimir"
                anchors.right: parent.right
                anchors.rightMargin: 25
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                border.color: "#787777"
                colorTextoMensajeError: "White"

                onClicked: {

                    codigoTipoImpresion=cbxListaTipoEnvios.codigoValorSeleccion
                    nombreImpresora=cbxListaImpresoras.textoComboBox.trim()

                    clicImprimir()



                }
            }

            ComboBoxListaImpresoras {
                id: cbxListaImpresoras
                y: 142
                textoTitulo: "Impresoras:"
                anchors.right: btnCancelarOperacion.left
                anchors.rightMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 16
                anchors.left: parent.left
                anchors.leftMargin: 35
                textoComboBox: funcionesmysql.impresoraPorDefecto()
            }





            Rectangle {
                id: rectangle1
                width: 10
                clip: true
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
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 5

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
            }


        }
    }
}
