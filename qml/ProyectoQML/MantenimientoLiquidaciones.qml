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

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import "Controles"
import "Listas"

Rectangle {
    id: rectPrincipalMantenimientoLiquidaciones
    width: 800
    height: 600
    color: "#ffffff"
    radius: 8
    //

    property int codigoDeLiquidacion: 0
    property string vendedorDeLiquidacio: ""

    property alias botonNuevaLiquidacionVisible : botonNuevaLiquidacion.visible
    property alias botonEliminarLiquidacionVisible : botonEliminarLiquidacion.visible
    property alias botonCrearLiquidacionVisible : botonCrearLiquidacion.visible





    Rectangle {
        id: rectContenedorLiquidaciones
        x: 0
        y: 30
        color: "#494747"
        radius: 8
        z: 1
        //
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 30
        anchors.fill: parent

        Flow {
            id: flow1
            height: flow1.implicitHeight
            z: 2
            spacing: 7
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 10


            ComboBoxListaVendedores {
                id: txtVendedorDeLaLiquidacion
                width: 210
                textoComboBox: ""
                botonBuscarTextoVisible: true
                textoTitulo: "Vendedor de la caja:"
                z:102
                onClicEnBusqueda: {

                    modeloLiquidaciones.clearLiquidaciones()
                    modeloLiquidaciones.buscarLiquidacion("codigoVendedor =", txtVendedorDeLaLiquidacion.codigoValorSeleccion.toString())
                    listaDeLiquidaciones.currentIndex=0;
                }
                onEnter: {

                    txtFechaLiquidacion.tomarElFoco()

                }
                onSenialAlAceptarOClick: codigoDeLiquidacion=0

            }

            TextInputSimple {
                id: txtFechaLiquidacion
                x: 27
                y: 95
              //  width: 150
                textoInputBox: funcionesmysql.fechaDeHoy()
                textoTitulo: "Fecha (aaaa/mm/dd):"
                inputMask: "nnnn-nn-nn; "
                largoMaximo: 45
                enFocoSeleccionarTodo: true
                validaFormato: validacionFecha
                botonBuscarTextoVisible: false

            }
            RegExpValidator{
                id:validacionFecha
                ///Fecha AAAA/MM/DD
                regExp: new RegExp("(20|  |2 | 2)(0[0-9, ]| [0-9, ]|1[0123456789 ]|2[0123456789 ]|3[0123456789 ]|4[0123456789 ])\-(0[1-9, ]| [1-9, ]|1[012 ]| [012 ])\-(0[1-9, ]| [1-9, ]|[12 ][0-9, ]|3[01 ]| [01 ])")
            }
        }
        Rectangle{
            id: rectListaDeLiquidaciones
            width: (rectContenedorLiquidaciones.width-450)/2
            color: {
                if(listaDeLiquidaciones.count==0){
                    "#C4C4C6"
                }else{
                    "#b4c0df"
                }
            }
            radius: 3
            clip: true
            //
            anchors.top: flow1.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            ListView {
                id: listaDeLiquidaciones
                clip: true
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottomMargin: 25
                boundsBehavior: Flickable.DragAndOvershootBounds
                highlightFollowsCurrentItem: true
                interactive: {
                    if(listaDeLiquidaciones.count>4){
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

                delegate:  ListaLiquidaciones{}
                model: modeloLiquidaciones

                Rectangle {
                    id: rectangle3
                    y: listaDeLiquidaciones.visibleArea.yPosition * listaDeLiquidaciones.height+5
                    width: 10
                    color: "#000000"
                    height: listaDeLiquidaciones.visibleArea.heightRatio * listaDeLiquidaciones.height+18
                    radius: 2
                    anchors.right: listaDeLiquidaciones.right
                    anchors.rightMargin: 4
                    z: 1
                    opacity: 0.500
                    visible: {
                        if(listaDeLiquidaciones.count>4){
                            true
                        }else{
                            false
                        }
                    }

                    //
                }

            }

            Text {
                id: txtCantidadDeItemsValor
                x: 107
                width: 37
                height: 15
                color: "#000000"
                text: listaDeLiquidaciones.count
                font.family: "Arial"
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.leftMargin: 5
                //
                font.bold: false
                font.pointSize: 10
                anchors.left: txtCantidadDeItemsTitulo.right
            }

            Text {
                id: txtCantidadDeItemsTitulo
                x: 0
                width: txtCantidadDeItemsTitulo.implicitWidth
                height: 15
                color: "#000000"
                text: qsTr("Cantidad de cajas activas:")
                font.family: "Arial"
                anchors.top: parent.top
                anchors.topMargin: 5
                font.pointSize: 10
                font.bold: false
                anchors.left: parent.left
                anchors.leftMargin: 5
                //
            }

            BotonBarraDeHerramientas {
                id: botonSubirListaFinal
                x: 170
                y: 40
                width: 14
                height: 14
                anchors.right: parent.right
                anchors.rightMargin: 3
                toolTip: ""
                anchors.top: parent.top
                anchors.topMargin: 5
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                rotation: 90
                visible: rectangle3.visible
                onClic: listaDeLiquidaciones.positionViewAtIndex(0,0)
            }

            BotonBarraDeHerramientas {
                id: botonBajarListaFinal
                x: 170
                y: 405
                width: 14
                height: 14
                anchors.right: parent.right
                anchors.rightMargin: 3
                toolTip: ""
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                rotation: -90
                visible: rectangle3.visible
                onClic: listaDeLiquidaciones.positionViewAtIndex(listaDeLiquidaciones.count-1,0)

            }

        }

        Rectangle {
            id: rectListaDeDocumentos
            x: 3
            y: -2
            color: {
                if(listaDeDocumentosEnLiquidaciones.count==0){
                    "#C4C4C6"
                }else{
                    "#b4c0df"
                }
            }
            radius: 3
            clip: true
            //
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.top: flow1.bottom
            anchors.topMargin: 50
            ListView {
                id: listaDeDocumentosEnLiquidaciones
                clip: true
                highlightRangeMode: ListView.NoHighlightRange
                anchors.top: parent.top
                boundsBehavior: Flickable.DragAndOvershootBounds
                highlightFollowsCurrentItem: true
                anchors.right: parent.right
                delegate: ListaDocumentosEnLiquidaciones {
                }
                snapMode: ListView.NoSnap
                anchors.bottomMargin: 25
                spacing: 1
                anchors.bottom: parent.bottom
                flickableDirection: Flickable.VerticalFlick
                anchors.leftMargin: 1
                keyNavigationWraps: true
                anchors.left: parent.left

                interactive: {
                    if(listaDeDocumentosEnLiquidaciones.count>6){
                        true
                    }else{
                        false
                    }
                }
                //
                anchors.topMargin: 45
                anchors.rightMargin: 1
                model: modeloDocumentosEnLiquidaciones

                Rectangle {
                    id: scrollbarlistaDeDocumentosEnLiquidaciones
                    y: listaDeDocumentosEnLiquidaciones.visibleArea.yPosition * listaDeDocumentosEnLiquidaciones.height+5
                    width: 10
                    color: "#000000"
                    height: listaDeDocumentosEnLiquidaciones.visibleArea.heightRatio * listaDeDocumentosEnLiquidaciones.height+18
                    radius: 2
                    anchors.right: listaDeDocumentosEnLiquidaciones.right
                    anchors.rightMargin: 4
                    z: 1
                    opacity: 0.500
                    visible: {
                        if(listaDeDocumentosEnLiquidaciones.count>6){
                            true
                        }else{
                            false
                        }
                    }
                    //
                }

            }

            Text {
                id: txtCantidadDeItemsValorDocumentosdeLiquidacionValor
                x: 107
                width: 37
                height: 15
                color: "#000000"
                text: listaDeDocumentosEnLiquidaciones.count
                font.family: "Arial"
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.left: txtCantidadDeItemsTituloDocumentosDeLiquidacion.right
                anchors.leftMargin: 5
                //
                font.bold: false
                font.pointSize: 10
            }

            Text {
                id: txtCantidadDeItemsTituloDocumentosDeLiquidacion
                x: 0
                width: txtCantidadDeItemsTituloDocumentosDeLiquidacion.implicitWidth
                height: 15
                color: "#000000"
                text: qsTr("Cantidad de documentos:")
                font.family: "Arial"
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.leftMargin: ((rectListaDeDocumentos.width)*-1)+5
                anchors.left: rectListaDeDocumentos.right
                //
                font.bold: false
                font.pointSize: 10
            }

            Rectangle {
                id: rectTituloListaItemFacturacion
                x: 6
                y: -7
                height: 16
                color: "#2b2a2a"
                radius: 3
                anchors.top: parent.top
                anchors.topMargin: 25
                Text {
                    id: lbltemCodigoDocumento
                    width: 80
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
                    anchors.leftMargin: 40
                    anchors.left: lbltemCodigoDocumento.right
                }

                Text {
                    id: lbltemRazonSocialDocumento
                    x: 4
                    y: 0
                    width: 160
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
                    color: "#c3c3c7"
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
                anchors.rightMargin: 25
                anchors.right: parent.right
                anchors.leftMargin: 1
                opacity: 1
                anchors.left: parent.left
            }

            Text {
                id: txtInformacionDobleClic
                x: 454
                text: qsTr("Doble-clic para visualizar facturas.")
                font.family: "Arial"
                //
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 5
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 12
                visible: tagFacturacion.enabled
            }

            BotonBarraDeHerramientas {
                id: botonSubirListaFinal1
                x: -17
                y: 460
                width: 14
                height: 14
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.top: parent.top
                anchors.topMargin: 25
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                toolTip: ""
                rotation: 90
                visible: scrollbarlistaDeDocumentosEnLiquidaciones.visible
                onClic: listaDeDocumentosEnLiquidaciones.positionViewAtIndex(0,0)

            }

            BotonBarraDeHerramientas {
                id: botonBajarListaFinal1
                x: 543
                y: 391
                width: 14
                height: 14
                anchors.right: parent.right
                anchors.rightMargin: 3
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                anchors.bottom: parent.bottom
                toolTip: ""
                anchors.bottomMargin: 5
                rotation: -90
                visible: scrollbarlistaDeDocumentosEnLiquidaciones.visible
                onClic: listaDeDocumentosEnLiquidaciones.positionViewAtIndex(listaDeDocumentosEnLiquidaciones.count-1,0)

            }

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.leftMargin: 10
            anchors.left: rectListaDeLiquidaciones.right
        }


        ComboBoxGenerico {
            id: cbListaEstadoDocumentosEnMantenimientoLiquidaciones
            width: 200
            anchors.bottom: rectListaDeDocumentos.top
            anchors.bottomMargin: 10
            anchors.left: rectListaDeLiquidaciones.right
            anchors.leftMargin: 20
            textoTitulo: "Filtro por estado del documento:"
            modeloItems: modeloListaEstadoDocumentosVirtual
            codigoValorSeleccion: "-1"
            textoComboBox: "Todos"
            botonBuscarTextoVisible: true
            z: 102


            ListModel{
                id:modeloListaEstadoDocumentosVirtual
                ListElement {
                    codigoItem: "-1"
                    descripcionItem: "Todos"
                }
                ListElement {
                    codigoItem: "E"
                    descripcionItem: "Emitidos"
                }
                ListElement {
                    codigoItem: "G"
                    descripcionItem: "Guardados"
                }
                ListElement {
                    codigoItem: "P"
                    descripcionItem: "Pendientes"
                }
                ListElement {
                    codigoItem: "C"
                    descripcionItem: "Anulados"
                }
            }

            onClicEnBusqueda: {
                modeloDocumentosEnLiquidaciones.limpiarListaDocumentos()
                modeloDocumentosEnLiquidaciones.buscarDocumentosEnLiquidaciones(codigoDeLiquidacion,vendedorDeLiquidacio,modeloListaPerfiles.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),cbListaEstadoDocumentosEnMantenimientoLiquidaciones.codigoValorSeleccion.trim())
                listaDeDocumentosEnLiquidaciones.currentIndex=0;

            }
        }



    }

    ListModel{
        id:modeloArticulosCodigoDeBarras

    }



    Row {
        id: rowBarraDeHerramientasLiquidaciones
        //
        anchors.bottom: rectContenedorLiquidaciones.top
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        spacing: distanciaEntreBotonesBarraDeTareas

        BotonBarraDeHerramientas {
            id: botonNuevaLiquidacion
            x: 33
            y: 10
            toolTip: "Nueva caja"
            z: 8
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevaLiquidacion.png"
            anchors.verticalCenter: parent.verticalCenter
            onClic: {
                txtVendedorDeLaLiquidacion.tomarElFoco()
                txtFechaLiquidacion.textoInputBox=funcionesmysql.fechaDeHoy()
            }
        }
        BotonBarraDeHerramientas {
            id: botonCrearLiquidacion
            x: 61
            y: 3
            toolTip: "Crear nueva caja"
            z: 7
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            anchors.verticalCenter: parent.verticalCenter

            onClic: {
                var resultadoInsertLiquidacion = modeloLiquidaciones.insertarLiquidacion(txtVendedorDeLaLiquidacion.codigoValorSeleccion.toString(),txtFechaLiquidacion.textoInputBox.toString(),txtNombreDeUsuario.textoInputBox.trim())

                txtMensajeInformacionLiquidaciones.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                if(resultadoInsertLiquidacion==1){
                    txtMensajeInformacionLiquidaciones.color="#2f71a0"
                    txtMensajeInformacionLiquidaciones.text="Liquidación dada de alta correctamente"

                    modeloLiquidaciones.clearLiquidaciones()
                    modeloLiquidaciones.buscarLiquidacion("1=","1")
                    listaDeLiquidaciones.currentIndex=0;

                    txtVendedorDeLaLiquidacion.textoComboBox=""
                    txtVendedorDeLaLiquidacion.codigoValorSeleccion=""

                    txtFechaLiquidacion.textoInputBox=funcionesmysql.fechaDeHoy()


                }else if(resultadoInsertLiquidacion==-1){
                    txtMensajeInformacionLiquidaciones.color="#d93e3e"
                    txtMensajeInformacionLiquidaciones.text="ATENCION: No se pudo conectar a la base de datos"


                }else if(resultadoInsertLiquidacion==-3){
                    txtMensajeInformacionLiquidaciones.color="#d93e3e"
                    txtMensajeInformacionLiquidaciones.text="ATENCION: No se pudo dar de alta la caja"


                }else if(resultadoInsertLiquidacion==-5){
                    txtMensajeInformacionLiquidaciones.color="#d93e3e"
                    txtMensajeInformacionLiquidaciones.text="ATENCION: Faltan datos para dar de alta la caja. Verifique antes de continuar"

                }
            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarLiquidacion
            x: 54
            y: 3
            toolTip: "Eliminar caja"
            z: 6
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            anchors.verticalCenter: parent.verticalCenter
            onClic: {

                if(codigoDeLiquidacion.toString()!=0)
                    if(funcionesmysql.mensajeAdvertencia("Realmente desea eliminar la caja número"+codigoDeLiquidacion.toString()+"\ndel vendedor "+txtVendedorDeLaLiquidacion.textoComboBox.trim()+"?\n\nPresione [ Sí ] para confirmar.")){


                        if(modeloLiquidaciones.eliminarLiquidacion(codigoDeLiquidacion.toString(),txtVendedorDeLaLiquidacion.codigoValorSeleccion.toString())){

                            txtMensajeInformacionLiquidaciones.visible=true
                            txtMensajeInformacionTimer.stop()
                            txtMensajeInformacionTimer.start()

                            txtMensajeInformacionLiquidaciones.color="#2f71a0"
                            txtMensajeInformacionLiquidaciones.text="Liquidación "+codigoDeLiquidacion.toString()+" de "+txtVendedorDeLaLiquidacion.textoComboBox+" borrada correctamente"

                            modeloLiquidaciones.clearLiquidaciones()
                            modeloLiquidaciones.buscarLiquidacion("1=","1")
                            listaDeLiquidaciones.currentIndex=0;

                            txtVendedorDeLaLiquidacion.textoComboBox=""
                            txtVendedorDeLaLiquidacion.codigoValorSeleccion=""
                            codigoDeLiquidacion=0
                            txtFechaLiquidacion.textoInputBox=funcionesmysql.fechaDeHoy()

                        }else{
                            txtMensajeInformacionLiquidaciones.visible=true
                            txtMensajeInformacionTimer.stop()
                            txtMensajeInformacionTimer.start()
                            txtMensajeInformacionLiquidaciones.color="#d93e3e"
                            txtMensajeInformacionLiquidaciones.text="ATENCION: No se puede eliminar la caja, verifique que no contenga documentos."
                        }}}
        }

        BotonBarraDeHerramientas {
            id: botonListarTodasLasLiquidaciones
            x: 47
            y: 10
            toolTip: "Listar todas las cajas activas"
            z: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            anchors.verticalCenter: parent.verticalCenter


            onClic: {

                modeloLiquidaciones.clearLiquidaciones()
                modeloLiquidaciones.buscarLiquidacion("1=","1")
                listaDeLiquidaciones.currentIndex=0;




            }
        }

        Text {
            id: txtMensajeInformacionLiquidaciones
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

    Timer{
        id:txtMensajeInformacionTimer
        repeat: false
        interval: 5000
        onTriggered: {

            txtMensajeInformacionLiquidaciones.visible=false
            txtMensajeInformacionLiquidaciones.color="#d93e3e"

        }



    }

    Rectangle {
        id: rectangle4
        x: 9
        y: -5
        width: 10
        color: "#4a68b5"
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: rectContenedorLiquidaciones.top
        anchors.bottomMargin: -10
        z: 0
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    PropertyAnimation{
        id:rectOpcionesExtrasAparecer
        target: rectOpcionesExtras
        property: "anchors.leftMargin"
        from:-710
        to:-68
        duration: 200
    }

    PropertyAnimation{
        id:rectOpcionesExtrasDesaparecer
        target: rectOpcionesExtras
        property: "anchors.leftMargin"
        to:-710
        from:-68
        duration: 50
    }

    Rectangle {
        id: rectOpcionesExtras
        width: 610
        color: "#4a68b5"
        radius: 2
        //
        anchors.top: parent.top
        anchors.topMargin: -68

        Keys.onEscapePressed: {

            rectOpcionesExtrasAparecer.stop()
            rectOpcionesExtrasDesaparecer.start()

            menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuarioAutorizaciones.textoInputBox.trim(),"permiteUsarMenuAvanzado")
        }


        Rectangle {
            id: rectSombraOpcionesExtras
            x: 333
            width: 17
            color: rectangle4.color
            //
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.rightMargin: -12
            anchors.bottomMargin: 0
            z: -1
            anchors.right: parent.right
            opacity: 0.300
        }



        MouseArea {
            id: mouse_area1
            anchors.fill: parent

            Text {
                id: txtTituloOpcionesExtras
                x: 20
                y: 10
                color: "#ffffff"
                text: qsTr("cierre de caja")
                font.family: "Arial"
                font.pixelSize: 23
                anchors.top: parent.top
                anchors.topMargin: 10
                font.underline: false
                visible: true
                font.italic: false
                font.bold: true
                anchors.leftMargin: 20
                anchors.left: parent.left
            }

            Flow {
                id: flowOpcionesExtras
                x: 10
                y: 60
                height: flowOpcionesExtras.implicitHeight+10
                spacing: 5
                anchors.top: parent.top
                anchors.topMargin: 60
                TextInputSimple {
                    id: txtCodigoArticuloOpcionesExtras
                    x: 22
                    y: 43
                //    width: 130
                    visible: true
                    botonBuscarTextoVisible: true
                    largoMaximo: 8
                    botonBorrarTextoVisible: true
                    textoTitulo: "Codigo:"
                    z: 1
                    colorDeTitulo: "#ffffff"
                }

                TextInputSimple {
                    id: txtDescripcionArticuloOpcionesExtras
                    x: 22
                    y: 43
                 //   width: 200
                    visible: true
                    largoMaximo: 20
                    botonBuscarTextoVisible: true
                    botonBorrarTextoVisible: true
                    textoTitulo: "Descripción:"
                    z: 1
                    colorDeTitulo: "#ffffff"
                }

                ComboBoxListaProveedores {
                    id: cbxListaProveedoresOpcionesExtra
                    x: 22
                    y: 56
                    width: 250
                    colorTitulo: "#ffffff"
                    visible: true
                    botonBuscarTextoVisible: true
                    textoTitulo: "Proveedor:"
                    z: 2
                }
                visible: true
                anchors.rightMargin: 10
                z: 3
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.left: parent.left
            }

            BotonFlecha {
                id: botonflechaCerrarOpcionesAvanzadas
                x: 410
                y: 20
                opacidadRectPrincipal: 0.800
                anchors.top: parent.top
                anchors.topMargin: 20
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaIzquierda.png"
                anchors.rightMargin: 10
                z: 1
                anchors.right: parent.right
                onClic: {

                    rectOpcionesExtrasAparecer.stop()
                    rectOpcionesExtrasDesaparecer.start()
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuarioAutorizaciones.textoInputBox.trim(),"permiteUsarMenuAvanzado")
                    txtFechaLiquidacion.tomarElFoco()
                }
            }
        }
        anchors.bottom: parent.bottom
        visible: true
        anchors.bottomMargin: -5
        z: 6
        anchors.leftMargin: -710
        anchors.left: parent.left
    }


    CuadroAutorizaciones{
        id:cuadroAutorizacionLiquidaciones
        color: "#be231919"
        z: 9
        anchors.fill: parent
        onConfirmacion: {

            if(permisosAEvaluar=="permiteAutorizarCierreLiquidaciones"){
                modeloDocumentosEnLiquidaciones.limpiarListaDocumentos()
                modeloDocumentosEnLiquidaciones.buscarDocumentosEnLiquidaciones("null","null","null","-1")
                modeloLiquidaciones.cerrarLiquidacion(codigoDeLiquidacion,vendedorDeLiquidacio)
                modeloLiquidaciones.clearLiquidaciones()
                modeloLiquidaciones.buscarLiquidacion("1=","1")
                mantenimientoFactura.refrescarComboBoxs(codigoDeLiquidacion,vendedorDeLiquidacio)
            }
        }
        onNoRequiereAutorizacion: {
            if(permisosAEvaluar=="permiteAutorizarCierreLiquidaciones"){
                modeloDocumentosEnLiquidaciones.limpiarListaDocumentos()
                modeloDocumentosEnLiquidaciones.buscarDocumentosEnLiquidaciones("null","null","null","-1")
                modeloLiquidaciones.cerrarLiquidacion(codigoDeLiquidacion,vendedorDeLiquidacio)
                modeloLiquidaciones.clearLiquidaciones()
                modeloLiquidaciones.buscarLiquidacion("1=","1")
                mantenimientoFactura.refrescarComboBoxs(codigoDeLiquidacion,vendedorDeLiquidacio)
            }


        }
    }
}
