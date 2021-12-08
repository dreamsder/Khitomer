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
import "../Listas"

Rectangle {
    id: rectListaTipoDocumentos
    color: "#be231919"
    visible: true
    anchors.fill: parent
    z: 8


    signal clicCancelar

    property alias modeloItems: listaDeGarantias.model

    property alias textoBoton: btnCancelarOperacion.text

    property string index:""

    signal sendInformacion(string id,string nombre)

    MouseArea {
        id: mouse_area2
        anchors.fill: parent

        Rectangle {
            id: rectListaItems
            width: 650
            height: 370
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
                id: lblTituloListado
                color: "#ffffff"
                text: qsTr("Lista de garantías, seleccione la indicada:")
                style: Text.Raised
                font.underline: true
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: true
                font.family: "Verdana"
                anchors.top: parent.top
                anchors.topMargin: 20
                font.pixelSize: 14
            }


            ListView {
                id: listaDeGarantias
                delegate: ListaGenerica {
                    onDoubleClicSend: {
                        sendInformacion(datoUno,datoDos)
                    }
                }
                anchors.bottom: btnCancelarOperacion.top
                anchors.right: parent.right
                anchors.left: parent.left
                interactive: {
                    if(listaDeGarantias.count>3){
                        true
                    }else{
                        false
                    }
                }
                anchors.top: lblTituloListado.bottom
                anchors.rightMargin: 20
                boundsBehavior: Flickable.DragAndOvershootBounds
                anchors.bottomMargin: 10
                highlightRangeMode: ListView.NoHighlightRange
                clip: true
                highlightFollowsCurrentItem: true
                anchors.leftMargin: 35
                spacing: 1
                anchors.topMargin: 50
                snapMode: ListView.NoSnap
                flickableDirection: Flickable.VerticalFlick
                keyNavigationWraps: true

                Rectangle {
                    id: scrollbar
                    y: listaDeGarantias.visibleArea.yPosition * listaDeGarantias.height+5
                    width: 10
                    height: listaDeGarantias.visibleArea.heightRatio * listaDeGarantias.height+18
                    color: "#000000"
                    radius: 2
                    anchors.rightMargin: 4
                    opacity: 0.5
                    visible: {
                        if(listaDeGarantias.count>3){
                            true
                        }else{
                            false
                        }
                    }
                    anchors.right: listaDeGarantias.right
                    //
                    z: 1
                }
            }

            Text {
                id: lblInformacionLista
                y: 7
                color: "#ffffff"
                text: qsTr("Haga clic, para que se cree automaticamente el nuevo documento; si no esta seguro, puede cancelar la operación.")
                style: Text.Normal
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                anchors.left: parent.left
                anchors.leftMargin: 35
                anchors.right: parent.right
                anchors.rightMargin: 15
                font.underline: false
                anchors.top: lblTituloListado.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 12
                font.family: "Verdana"
                font.bold: false
                anchors.topMargin: 5
            }

            BotonPaletaSistema {
                id: btnCancelarOperacion
                // text: "Cerrar"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 20
                border.color: "#787777"

                onClicked: clicCancelar()
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
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
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
                anchors.bottomMargin: 0
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
            }


        }
    }
}
