/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2023>  <Cristian Montano>

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
        id: rectMantenimientoBatch
        color: "#be251a1a"
        anchors.fill: parent
        //
        z: 8


        MouseArea {
            id: mouse_area2
            anchors.fill: parent


            Rectangle {
                id: rectCargaMantenimientoBatch
                x: 238
                y: 210
                width: 650
                height: 400
                radius: 5
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#8f8f8f"
                    }

                    GradientStop {
                        position: 0.100
                        color: "#1e7597"
                    }
                }
                //
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                focus: false
                opacity: 1

                Text {
                    id: txtTituloMantenimiento
                    y: 14
                    color: "#ffffff"
                    text: qsTr("carga de clientes desde archivo")
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    //
                    font.pixelSize: 25
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    style: Text.Normal
                    font.family: "Arial"
                    font.bold: true
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                }

                BotonPaletaSistema {
                    id: btnCargarBatch
                    x: 405
                    text: "Comenzar la carga"
                    anchors.top: parent.top
                    anchors.topMargin: 50
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                }

                Text {
                    id: lblCantidadDeRegistrosACargar
                    color: "#ffffff"
                    text: qsTr("* Se van a cargar registros desde el archivo.")
                    anchors.top: parent.top
                    anchors.topMargin: 60
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    font.bold: true
                    font.family: "Arial"
                    //
                    font.pixelSize: 12
                }

                Text {
                    id: lblSeInformara
                    x: -8
                    y: 1
                    color: "#ffffff"
                    text: qsTr("* Se informarán los registros que no se cargaron exitosamente.")
                    //
                    font.pixelSize: 12
                    anchors.top: lblCantidadDeRegistrosACargar.bottom
                    anchors.topMargin: 10
                    font.family: "Arial"
                    font.bold: true
                    anchors.leftMargin: 30
                    anchors.left: parent.left
                }

                Text {
                    id: lblNombreArchivoBatch
                    x: -5
                    y: 0
                    color: "#ffffff"
                    text: qsTr("* El archivo a cargar es: ")
                    //
                    font.pixelSize: 12
                    anchors.top: lblSeInformara.bottom
                    anchors.topMargin: 10
                    font.bold: true
                    font.family: "Arial"
                    anchors.leftMargin: 30
                    anchors.left: parent.left
                }

                Text {
                    id: lblRutaArchivoBatch
                    x: -13
                    y: 2
                    color: "#ffffff"
                    text: qsTr("* Ubicado en:")
                    //
                    font.pixelSize: 12
                    anchors.top: lblNombreArchivoBatch.bottom
                    anchors.topMargin: 10
                    font.family: "Arial"
                    font.bold: true
                    anchors.leftMargin: 30
                    anchors.left: parent.left
                }

                Rectangle {
                    id: rectListaDeItemsSinCargar
                    x: -9
                    height: 200
                    color: "#c4c4c6"
                    radius: 3
                    clip: true
                    //
                    ListView {
                        id: listaDeItemsSinCargar
                        highlightRangeMode: ListView.NoHighlightRange
                        anchors.top: parent.top
                        boundsBehavior: Flickable.DragAndOvershootBounds
                        highlightFollowsCurrentItem: true
                        anchors.right: parent.right
                        delegate: ListaPerfiles {
                        }
                        snapMode: ListView.NoSnap
                        anchors.bottomMargin: 25
                        spacing: 2
                        anchors.bottom: parent.bottom
                        clip: true
                        flickableDirection: Flickable.VerticalFlick
                        anchors.leftMargin: 1
                        Rectangle {
                            id: scrollbarlistaDePerfiles
                            y: listaDeItemsSinCargar.visibleArea.yPosition * listaDeItemsSinCargar.height+5
                            width: 10
                            height: listaDeItemsSinCargar.visibleArea.heightRatio * listaDeItemsSinCargar.height+18
                            color: "#000000"
                            radius: 2
                            //
                            anchors.rightMargin: 4
                            visible: true
                            z: 1
                            anchors.right: listaDeItemsSinCargar.right
                            opacity: 0.500
                        }
                        keyNavigationWraps: true
                        anchors.left: parent.left
                        interactive: true
                        //
                        anchors.topMargin: 25
                        anchors.rightMargin: 1
                        model: modeloListaPerfiles
                    }

                    Text {
                        id: lblCantidadItems
                        text: qsTr("Items: "+listaDeItemsSinCargar.count)
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        font.family: "Arial"
                        font.bold: false
                        font.pointSize: 10
                        anchors.leftMargin: 5
                        anchors.left: parent.left
                    }

                    BotonBarraDeHerramientas {
                        id: botonBajarListaFinal1
                        x: 783
                        y: 126
                        width: 14
                        height: 14
                        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 3
                        toolTip: ""
                        anchors.bottomMargin: 5
                        rotation: -90
                        anchors.right: parent.right
                    }

                    BotonBarraDeHerramientas {
                        id: botonSubirListaFinal1
                        x: 783
                        y: 35
                        width: 14
                        height: 14
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                        anchors.rightMargin: 3
                        toolTip: ""
                        rotation: 90
                        anchors.right: parent.right
                    }
                    anchors.bottom: parent.bottom
                    anchors.rightMargin: 5
                    anchors.bottomMargin: 5
                    anchors.right: parent.right
                    anchors.leftMargin: 5
                    anchors.left: parent.left
                }

                CheckBox {
                    id: cbxExcluirPrimeraLineaArchivo
                    x: 472
                    y: 143
                    colorTexto: "#ffffff"
                    anchors.bottom: rectListaDeItemsSinCargar.top
                    anchors.bottomMargin: 20
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    textoValor: "No incluir la primera linea del archivo"
                }
            }

        }
    }
