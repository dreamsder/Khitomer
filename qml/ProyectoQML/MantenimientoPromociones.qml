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
import "Controles"
import "Listas"
import "Listas/Delegates"
Rectangle {
    id: rectPrincipalMantenimientoPromociones
    width: 900
    height: 600
    color: "#ffffff"
    radius: 8
    visible: true
    //


    Rectangle {
        id: rectContenedorPromociones
        x: 0
        y: 30
        color: "#484646"
        radius: 8
        z: 2
        //
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 30
        anchors.fill: parent


        Flow {
            id: flow1
            height: flow1.implicitHeight
            z: 1
            spacing: 7
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 10



            ComboBoxGenerico {
                id: cbxTipoPromocion
                width: 170
                codigoValorSeleccion: "1"
                textoComboBox: "Mail de cumpleaños"
                botonBuscarTextoVisible: false
                textoTitulo: qsTr("Tipo Promoción:")
                modeloItems: modeloGenericoTipoPromocion
            }


            TextInputSimple {
                id: txtNumeroDocumento
                enFocoSeleccionarTodo: true
                textoDeFondo: ""
                largoMaximo: 9
                inputMask: "0000000000;"
                botonBuscarTextoVisible: true
                botonBorrarTextoVisible: true
                textoTitulo: "Num. documento:"
                textoInputBox: ""
                onClicEnBusqueda: {
                //    modeloDocumentosMantenimiento.limpiarListaDocumentos()
                //    modeloDocumentosMantenimiento.buscarDocumentosEnMantenimiento("D.codigoDocumento =",txtNumeroDocumento.textoInputBox.trim(),modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))
                //    listaDeDocumentosFiltrados.currentIndex=0
                }
                onEnter:txtSerieDocumento.tomarElFoco()
                onTabulacion: txtSerieDocumento.tomarElFoco()
            }





            TextInputSimple {
                id: txtFechaDocumento
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                validaFormato: validacionFecha
                botonBuscarTextoVisible: true
                inputMask: "nnnn-nn-nn; "
                textoTitulo: "Fecha emision:"
                onClicEnBusqueda: {
                //    modeloDocumentosMantenimiento.limpiarListaDocumentos()
                //    modeloDocumentosMantenimiento.buscarDocumentosEnMantenimiento("D.fechaEmisionDocumento =",txtFechaDocumento.textoInputBox.trim(),modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))
                //    listaDeDocumentosFiltrados.currentIndex=0
                }
                onEnter:txtCodigoClienteDocumento.tomarElFoco()
                onTabulacion: txtCodigoClienteDocumento.tomarElFoco()

            }
            RegExpValidator{
                id:validacionFecha
                ///Fecha AAAA/MM/DD
                regExp: new RegExp("(20|  |2 | 2)(0[0-9, ]| [0-9, ]|1[0123456789 ]|2[0123456789 ]|3[0123456789 ]|4[0123456789 ])\-(0[1-9, ]| [1-9, ]|1[012 ]| [012 ])\-(0[1-9, ]| [1-9, ]|[12 ][0-9, ]|3[01 ]| [01 ])")
            }



            TextInputSimple {
                id: txtCodigoArticuloEnDocumento
                enFocoSeleccionarTodo: true
                botonBuscarTextoVisible: true
                largoMaximo: 30
                botonBorrarTextoVisible: true
                textoTitulo: "Artículo en documento:"
                onClicEnBusqueda: {
                //    modeloDocumentosMantenimiento.limpiarListaDocumentos()
                //    modeloDocumentosMantenimiento.buscarDocumentosEnMantenimiento(" ( DL.codigoArticulo='"+txtCodigoArticuloEnDocumento.textoInputBox.trim()+"' or DL.codigoArticuloBarras='"+txtCodigoArticuloEnDocumento.textoInputBox.trim()+"') and ","1=1",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))
                //    listaDeDocumentosFiltrados.currentIndex=0
                }
                onEnter:cbListaTipoDeDocumentosEnMantenimiento.tomarElFoco()
                onTabulacion: cbListaTipoDeDocumentosEnMantenimiento.tomarElFoco()
            }




            CheckBox {
                id: chbDocumentoSinLiquidacion
                buscarActivo: false
                chekActivo: true
                colorTexto: "#dbd8d8"
                textoValor: "Habilitada"

                onClicEnBusqueda: {

                    /*
                    modeloDocumentosMantenimiento.limpiarListaDocumentos()
                    if(chekActivo){
                        modeloDocumentosMantenimiento.buscarDocumentosEnMantenimiento(" ( D.codigoLiquidacion=0 and (D.codigoVendedorLiquidacion is null or D.codigoVendedorLiquidacion='' or D.codigoVendedorLiquidacion='0') ) and ","1=1",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))
                    }else{
                        modeloDocumentosMantenimiento.buscarDocumentosEnMantenimiento(" ( D.codigoLiquidacion!=0 and (D.codigoVendedorLiquidacion is not null and D.codigoVendedorLiquidacion!='' and D.codigoVendedorLiquidacion!='0') ) and ","1=1",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))
                    }
                    listaDeDocumentosFiltrados.currentIndex=0*/

                }
            }
        }

        Rectangle{
            id: rectangle2
            color: {
                if(listaDePromocionesFiltrados.count==0){
                    "#C4C4C6"
                }else{
                    "#dbb5f9"
                }
            }
            radius: 3
            clip: true
            //
            anchors.top: flow1.bottom
            anchors.topMargin: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 20
            ListView {
                id: listaDePromocionesFiltrados
                clip: true
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottomMargin: 25
                boundsBehavior: Flickable.DragAndOvershootBounds
                highlightFollowsCurrentItem: true
                interactive: {
                    if(listaDePromocionesFiltrados.count>5){
                        true
                    }else{
                        false
                    }
                }

                spacing: 1
                anchors.rightMargin: 1
                anchors.leftMargin: 1
                anchors.topMargin: 25
                snapMode: ListView.NoSnap
                keyNavigationWraps: true
                highlightRangeMode: ListView.NoHighlightRange
                flickableDirection: Flickable.VerticalFlick
                //
                delegate:  ListaDocumentos{}
                model: modeloDocumentosMantenimiento

                Rectangle {
                    id: scrollbarlistaDePromocionesFiltrados
                    y: listaDePromocionesFiltrados.visibleArea.yPosition * listaDePromocionesFiltrados.height+5
                    width: 10
                    color: "#000000"
                    height: listaDePromocionesFiltrados.visibleArea.heightRatio * listaDePromocionesFiltrados.height+18
                    radius: 2
                    anchors.right: listaDePromocionesFiltrados.right
                    anchors.rightMargin: 4
                    z: 1
                    opacity: 0.500
                    visible: {
                        if(listaDePromocionesFiltrados.count>5){
                            true
                        }else{
                            false
                        }
                    }
                    //
                }
            }

            Text {
                id: lblCantidadDeDocumentosFiltrados
                x: 10
                width: lblCantidadDeDocumentosFiltrados.implicitWidth
                color: "#000000"
                text: qsTr("Promociones filtradas:")
                font.family: "Arial"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                font.pointSize: 10
                font.bold: false
                anchors.left: parent.left
                anchors.leftMargin: 5
                //
            }

            Text {
                id: txtCantidadDedocumentosFiltrados
                x: 127
                width: 37
                color: "#000000"
                text: listaDePromocionesFiltrados.count
                font.family: "Arial"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                anchors.leftMargin: 5
                //
                font.bold: false
                font.pointSize: 10
                anchors.left: lblCantidadDeDocumentosFiltrados.right
            }

            Rectangle {
                id: rectTituloListaItemFacturacion
                x: 6
                y: -7
                height: 16
                color: "#2b2a2a"
                radius: 3
                anchors.top: parent.top
                anchors.topMargin: 5
                Text {
                    id: lbltemCodigoDocumento
                    width: 110
                    color: "#ffffff"
                    text: "# Doc. interno"
                    font.family: "Arial"
                    //
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    style: Text.Normal
                    anchors.bottomMargin: 0
                    font.bold: true
                    font.pointSize: 10
                    horizontalAlignment: Text.AlignHCenter
                    anchors.leftMargin: 10
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: parent.left
                }

                Rectangle {
                    id: rectLineaSeparacionTitulo
                    y: 0
                    width: 2
                    color: "#C4C4C6"
                    //
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 10
                    anchors.left: lbltemCodigoDocumento.right
                }

                Text {
                    id: lbltemRazonSocialDocumento
                    x: 4
                    y: 0
                    width: 220
                    color: "#ffffff"
                    text: "Razón social"
                    font.family: "Arial"
                    //
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    style: Text.Normal
                    anchors.bottomMargin: 0
                    font.bold: true
                    font.pointSize: 10
                    horizontalAlignment: Text.AlignHCenter
                    anchors.leftMargin: 10
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: rectLineaSeparacion2Titulo.right
                }

                Rectangle {
                    id: rectLineaSeparacion2Titulo
                    x: -1
                    y: -4
                    width: 2
                    color: "#C4C4C6"
                    //
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 10
                    anchors.left: lbltemSerieDocumento.right
                }

                Rectangle {
                    id: rectLineaSeparacion3Titulo
                    x: 3
                    y: -7
                    width: 2
                    color: "#C4C4C6"
                    //
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 10
                    anchors.left: lbltemRazonSocialDocumento.right
                }

                Text {
                    id: lbltemSerieDocumento
                    x: 2
                    y: 0
                    width: 80
                    color: "#ffffff"
                    text: "# CFE"
                    font.family: "Arial"
                    //
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    style: Text.Normal
                    anchors.bottomMargin: 0
                    font.bold: true
                    font.pointSize: 10
                    horizontalAlignment: Text.AlignHCenter
                    anchors.leftMargin: 10
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: rectLineaSeparacionTitulo.right
                }

                Text {
                    id: lbltemNombreClienteDocumento
                    x: 3
                    y: 7
                    width: 160
                    color: "#ffffff"
                    text: "Nombre"
                    font.family: "Arial"
                    //
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    style: Text.Normal
                    anchors.bottomMargin: 0
                    font.bold: true
                    font.pointSize: 10
                    anchors.leftMargin: 10
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: rectLineaSeparacion3Titulo.right
                }
                anchors.rightMargin: 1
                anchors.right: parent.right
                anchors.leftMargin: 1
                opacity: 1
                anchors.left: parent.left
            }

            BotonBarraDeHerramientas {
                id: botonSubirListaFinal
                x: 845
                y: 60
                width: 14
                height: 14
                anchors.right: parent.right
                anchors.rightMargin: 3
                toolTip: ""
                anchors.top: parent.top
                anchors.topMargin: 5
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                rotation: 90
                visible: scrollbarlistaDePromocionesFiltrados.visible
                onClic: listaDePromocionesFiltrados.positionViewAtIndex(0,0)
            }

            BotonBarraDeHerramientas {
                id: botonBajarListaFinal
                x: 845
                y: 343
                width: 14
                height: 14
                anchors.right: parent.right
                anchors.rightMargin: 3
                toolTip: ""
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                rotation: -90
                visible: scrollbarlistaDePromocionesFiltrados.visible
                onClic: listaDePromocionesFiltrados.positionViewAtIndex(listaDePromocionesFiltrados.count-1,0)

            }
        }



    }





    Row {
        id: rowBarraDeHerramientasPromociones
        //
        anchors.bottom: rectContenedorPromociones.top
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        spacing: distanciaEntreBotonesBarraDeTareas

        BotonBarraDeHerramientas {
            id: botonNuevoFiltro
            x: 33
            y: 10
            toolTip: "Nueva promoción"
            z: 8
            //source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/MantenimientoPromociones.png"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Nuevo.png"
            anchors.verticalCenter: parent.verticalCenter


            onClic: {


            }
        }


        BotonBarraDeHerramientas {
            id: botonGuardarPromocion
            x: 61
            y: 3
            toolTip: "Guardar promoción"
            z: 7
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            anchors.verticalCenter: parent.verticalCenter

            onClic: {


            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarPromocion
            x: 54
            y: 3
            toolTip: "Eliminar promoción"
            z: 6
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            anchors.verticalCenter: parent.verticalCenter
            onClic: {



            }
        }




        BotonBarraDeHerramientas {
            id: botonListarTodasLasPromociones
            x: 47
            y: 10
            toolTip: "Listar todas las promociones"
            z: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"            
            anchors.verticalCenter: parent.verticalCenter
            onClic: {

             //   modeloArticulos.clearArticulos()
             //   modeloArticulos.buscarArticulo("1=","1",0)
             //   listaDeArticulos.currentIndex=0;
            }
        }





        Text {
            id: txtMensajeInformacionPromociones
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            font.family: "Arial"
            visible: false
            font.pixelSize: 14
            styleColor: "white"
            style: Text.Raised
            font.bold: true
            verticalAlignment: Text.AlignTop
            horizontalAlignment: Text.AlignRight
            //
        }
    }

    Rectangle {
        id: rectangle4
        x: -4
        y: -1
        width: 10
        color: "#CDDC39"
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: rectContenedorPromociones.top
        anchors.bottomMargin: -10
        z: 1
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

}
