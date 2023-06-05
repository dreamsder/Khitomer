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

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import "../Controles"

Rectangle{
    id: rectListaItem
    width: parent.width
    // width: 1024
    height: 70
    color: "#e9e8e9"
    radius: 1
    border.color: "#aaaaaa"
    //
    opacity: 1



    Text {
        id:txtLiquidacion
        text: codigoLiquidacion + " - "+ nombreCompletoVendedor
        font.family: "Arial"
        opacity: 0.900
        //
        font.pointSize: 10
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.top: parent.top
        anchors.topMargin: 0
        color: "#212121"
    }

    FocusScope{
        id:focus_scope1
        anchors.fill: parent
        onFocusChanged: {

            if(focus_scope1.focus){

                listaDeTotalMonedas.visible=false
                listaDeTotalCehquesDiferidos.visible=false
                listaDeTotalOtrosCheques.visible=false

                listaDeTotalMonedas.height=listaDeTotalMonedas.contentHeight
                listaDeTotalCehquesDiferidos.height=listaDeTotalCehquesDiferidos.contentHeight

                listaDeTotalOtrosCheques.height=listaDeTotalOtrosCheques.contentHeight

                rectListaItemContraer.stop()
                rectListaItemExpandir.start()

                btnCerrarLiquidacion.visible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCerrarLiquidaciones")
                btnReporteCaja.visible=btnCerrarLiquidacion.visible

                rectListaItem.color="#9294C6"
                txtCantidadDeDocumentosEmitidos.text="Documentos emitidos: "+modeloLiquidaciones.retornaCantidadDocumentosEnLiquidacionSegunEstado(codigoLiquidacion,codigoVendedor,"E")

                txtCantidadDeDocumentosPendientes.text="Documentos pendientes: "+modeloLiquidaciones.retornaCantidadDocumentosEnLiquidacionSegunEstado(codigoLiquidacion,codigoVendedor,"P")

            }else{
                listaDeTotalMonedas.visible=false

                listaDeTotalCehquesDiferidos.visible=false
                listaDeTotalOtrosCheques.visible=false

                rectListaItemExpandir.stop()
                rectListaItemContraer.start()

                btnCerrarLiquidacion.visible=false
                btnReporteCaja.visible=false

                rectListaItemColorDeseleccionado.start()
                txtLiquidacion.color= "#212121"
                txtFechaDeLiquidacion.color="#000000"
                txtCantidadDeDocumentosPendientes.color="#000000"
                txtCantidadDeDocumentosEmitidos.color="#000000"
            }

        }

        MouseArea{
            id: mousearea1
            z: 1
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                if(focus_scope1.focus==false){

                    rectListaItemColorDeseleccionado.stop()
                    rectListaItemColorSeleccionado.start()
                    txtLiquidacion.color="white"
                    txtFechaDeLiquidacion.color="white"
                    txtCantidadDeDocumentosPendientes.color="white"
                    txtCantidadDeDocumentosEmitidos.color="white"

                }
            }
            onExited: {


                if(focus_scope1.focus==false){
                    rectListaItemColorSeleccionado.stop()
                    rectListaItemColorDeseleccionado.start()

                    txtLiquidacion.color= "#212121"
                    txtFechaDeLiquidacion.color="#000000"
                    txtCantidadDeDocumentosPendientes.color="#000000"
                    txtCantidadDeDocumentosEmitidos.color="#000000"
                }
            }

            onClicked: {
                modeloTotalChequesDiferidos.limpiarListaTotalCheques()
                modeloTotalChequesDiferidos.buscarTotalCheques(codigoLiquidacion,codigoVendedor)

                modeloTotalOtrosCheques.limpiarListaTotalCheques()
                modeloTotalOtrosCheques.buscarTotalOtrosCheques(codigoLiquidacion,codigoVendedor)



                focus_scope1.focus=true

                listaDeDocumentosEnLiquidaciones.positionViewAtIndex(0,0)

                txtVendedorDeLaLiquidacion.codigoValorSeleccion=codigoVendedor
                txtVendedorDeLaLiquidacion.textoComboBox=nombreCompletoVendedor+" ("+codigoVendedor+")"
                txtFechaLiquidacion.textoInputBox=fechaLiquidacion
                codigoDeLiquidacion=codigoLiquidacion


                mantenimientoLiquidaciones.codigoDeLiquidacion=codigoLiquidacion
                mantenimientoLiquidaciones.vendedorDeLiquidacio=codigoVendedor

                modeloDocumentosEnLiquidaciones.limpiarListaDocumentos()

                if(mODO_DOCUMENTOS_VISIBLES){
                    if(visualizarDocumentosEnmODO_DOCUMENTOS_VISIBLES){
                        modeloDocumentosEnLiquidaciones.buscarDocumentosEnLiquidaciones(codigoLiquidacion,codigoVendedor,modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),cbListaEstadoDocumentosEnMantenimientoLiquidaciones.codigoValorSeleccion.trim(),cbListaCantidadAniosHaciaAtrasEnDocumentosDeLiquidacion.codigoValorSeleccion.trim())
                    }else{
                        modeloDocumentosEnLiquidaciones.buscarDocumentosEnLiquidaciones(codigoLiquidacion,codigoVendedor,modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),cbListaEstadoDocumentosEnMantenimientoLiquidaciones.codigoValorSeleccion.trim(),"1")
                    }
                }else{
                    modeloDocumentosEnLiquidaciones.buscarDocumentosEnLiquidaciones(codigoLiquidacion,codigoVendedor,modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),cbListaEstadoDocumentosEnMantenimientoLiquidaciones.codigoValorSeleccion.trim(),cbListaCantidadAniosHaciaAtrasEnDocumentosDeLiquidacion.codigoValorSeleccion.trim())
                }


                listaDeDocumentosEnLiquidaciones.currentIndex=0;

            }
        }
    }
    PropertyAnimation{
        id:rectListaItemExpandir
        target: rectListaItem
        property: "height"
        from:70
        to: listaDeTotalMonedas.contentHeight+listaDeTotalCehquesDiferidos.contentHeight+75+listaDeTotalOtrosCheques.contentHeight
        duration: 100
        onCompleted: {

            listaDeTotalMonedas.visible=true
            listaDeTotalCehquesDiferidos.visible=true
            listaDeTotalOtrosCheques.visible=true
        }
    }
    PropertyAnimation{
        id:rectListaItemContraer
        target: rectListaItem
        property: "height"
        to:70
        from:listaDeTotalMonedas.contentHeight+listaDeTotalCehquesDiferidos.contentHeight+75+listaDeTotalOtrosCheques.contentHeight
        duration: 50
    }

    Rectangle {
        id: rectLinea
        y: 35
        height: 1
        color: "#975f5f"
        visible: false
        //
        opacity: 0.500
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.left: parent.left
        anchors.leftMargin: 20
    }

    Grid {
        id: gridDatosLiquidacion
        height: 50
        clip: true
        spacing: 2
        flow: Grid.TopToBottom
        rows: 5
        columns: 1
        anchors.top: txtLiquidacion.bottom
        anchors.topMargin: 1
        anchors.right: parent.right
        anchors.rightMargin: 60
        anchors.left: parent.left
        anchors.leftMargin: 30

        Text {
            id: txtFechaDeLiquidacion
            width: 210
            text: "Fecha de caja:  "+fechaLiquidacion
            font.family: "Arial"
            //
            opacity: 0.500
            font.pixelSize: 11
            height: txtFechaDeLiquidacion.implicitHeight
        }

        Text {
            id: txtCantidadDeDocumentosPendientes
            width: 210
            height: txtCantidadDeDocumentosPendientes.implicitHeight
            text: "Documentos pendientes: "+modeloLiquidaciones.retornaCantidadDocumentosEnLiquidacionSegunEstado(codigoLiquidacion,codigoVendedor,"P")
            font.family: "Arial"
            //
            font.pixelSize: 11
            opacity: 0.500
        }

        Text {
            id: txtCantidadDeDocumentosEmitidos
            width: 210
            height: txtCantidadDeDocumentosEmitidos.implicitHeight
            text: "Documentos emitidos: " +modeloLiquidaciones.retornaCantidadDocumentosEnLiquidacionSegunEstado(codigoLiquidacion,codigoVendedor,"E")
            font.family: "Arial"
            visible: true
            //
            font.pixelSize: 11
            opacity: 0.500
        }
    }

    PropertyAnimation{
        id:rectListaItemColorSeleccionado
        target: rectListaItem
        property: "color"
        from: "#e9e8e9"
        to:"#9294C6"
        duration: 100

    }
    PropertyAnimation{
        id:rectListaItemColorDeseleccionado
        target: rectListaItem
        property: "color"
        to: "#e9e8e9"
        from:"#9294C6"
        duration: 50

    }

    BotonCargarDato {
        id: btnCerrarLiquidacion
        height: 35
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        visible: false
        z: 1
        texto: "Cerrar caja"
        imagen: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Suma.png"
        textoColor: "#4f4f4f"

        onClic: {


            var valorCierre=modeloconfiguracion.retornaValorConfiguracion("TIPO_CIERRE_LIQUIDACION")


            /// 0 - Se cierran al precionar boton de cierre.
            /// 1 - Se cierran al precionar boton de cierre y pide autorizacion.
            /// 2 - Se abre la ventana de declaracion de valores para poder cerrarse, pide autorización.
            if(valorCierre=="0"){

                modeloDocumentosEnLiquidaciones.limpiarListaDocumentos()
                if(mODO_DOCUMENTOS_VISIBLES){
                    if(visualizarDocumentosEnmODO_DOCUMENTOS_VISIBLES){
                        modeloDocumentosEnLiquidaciones.buscarDocumentosEnLiquidaciones("null","null","null","-1",cbListaCantidadAniosHaciaAtrasEnDocumentosDeLiquidacion.codigoValorSeleccion.trim())
                    }else{
                        modeloDocumentosEnLiquidaciones.buscarDocumentosEnLiquidaciones("null","null","null","-1","1")
                    }
                }else{
                    modeloDocumentosEnLiquidaciones.buscarDocumentosEnLiquidaciones("null","null","null","-1",cbListaCantidadAniosHaciaAtrasEnDocumentosDeLiquidacion.codigoValorSeleccion.trim())
                }


                modeloLiquidaciones.cerrarLiquidacion(codigoLiquidacion,codigoVendedor)

                modeloLiquidaciones.clearLiquidaciones()
                modeloLiquidaciones.buscarLiquidacion("1=","1")

                modeloLiquidacionesComboBox.clearLiquidaciones()
                modeloLiquidacionesComboBox.buscarLiquidacion("1=","1")




            }else if(valorCierre=="1"){

                mantenimientoLiquidaciones.codigoDeLiquidacion=codigoLiquidacion
                mantenimientoLiquidaciones.vendedorDeLiquidacio=codigoVendedor

                if(modeloconfiguracion.retornaValorConfiguracion("MODO_AUTORIZACION")=="1"){
                    cuadroAutorizacionLiquidaciones.evaluarPermisos("permiteAutorizarCierreLiquidaciones")
                }else{
                    cuadroAutorizacionLiquidaciones.noSeRequierenAutorizaciones("permiteAutorizarCierreLiquidaciones")
                }



            }else if(valorCierre=="2"){

                rectOpcionesExtrasDesaparecer.stop()
                rectOpcionesExtrasAparecer.start()

                rowMenusDelSistema.z=-1
                btnLateralBusquedas.z=0
                menulista1.enabled=false

            }else if(valorCierre=="-1"){

                txtMensajeInformacionLiquidaciones.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()
                txtMensajeInformacionLiquidaciones.color="#d93e3e"
                txtMensajeInformacionLiquidaciones.text="ATENCION: Hay problemas para cerrar la caja. Verifiquelo."

            }
        }
    }

    ListView {
        id: listaDeTotalMonedas
        width: 200
        height: 10
        highlightRangeMode: ListView.NoHighlightRange
        anchors.top: gridDatosLiquidacion.bottom
        boundsBehavior: Flickable.StopAtBounds
        highlightFollowsCurrentItem: true
        delegate: ListaTotalMonedas {
        }
        snapMode: ListView.NoSnap
        spacing: 0
        clip: true
        flickableDirection: Flickable.VerticalFlick
        anchors.leftMargin: 30
        keyNavigationWraps: false
        anchors.left: parent.left
        interactive: false
        //
        anchors.topMargin: 3
        model: modeloMonedasTotales
        visible: false
        z: 2
    }

    ListView {
        id: listaDeTotalCehquesDiferidos
        width: 200
        height: 40
        highlightRangeMode: ListView.NoHighlightRange
        anchors.top: listaDeTotalMonedas.bottom
        boundsBehavior: Flickable.StopAtBounds
        highlightFollowsCurrentItem: true
        delegate: ListaTotalChequesDiferidos{
        }
        snapMode: ListView.NoSnap
        spacing: 0
        z: 2
        clip: true
        flickableDirection: Flickable.VerticalFlick
        anchors.leftMargin: 30
        anchors.left: parent.left
        keyNavigationWraps: false
        interactive: false
        //
        anchors.topMargin: 1
        model: modeloTotalChequesDiferidos
        visible: false
    }

    ListView {
        id: listaDeTotalOtrosCheques
        width: 200
        height: 40
        highlightRangeMode: ListView.NoHighlightRange
        anchors.top: listaDeTotalCehquesDiferidos.bottom
        boundsBehavior: Flickable.StopAtBounds
        highlightFollowsCurrentItem: true
        delegate: ListaTotalChequesDiferidos{
            textoLabel:  "Total cheques "
        }
        snapMode: ListView.NoSnap
        spacing: 0
        z: 2
        clip: true
        flickableDirection: Flickable.VerticalFlick
        anchors.leftMargin: 30
        anchors.left: parent.left
        keyNavigationWraps: false
        interactive: false
        //
        anchors.topMargin: 1
        model: modeloTotalOtrosCheques
        visible: false
    }

    BotonCargarDato {
        id: btnReporteCaja
        height: 35
        anchors.bottom: btnCerrarLiquidacion.top
        texto: "Reporte de caja"
        anchors.rightMargin: 15
        visible: false
        anchors.bottomMargin: 10
        z: 1
        anchors.right: parent.right
        imagen: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Suma.png"
        textoColor: "#4f4f4f"
        onClic: {


            mantenimientoReportes.codigoLiquidacionSeleccionada=codigoLiquidacion
            mantenimientoReportes.codigoVendedorLiquidacionSeleccionada=codigoVendedor
            mantenimientoReportes.nombreVendedorLiquidacionSeleccionada=nombreCompletoVendedor
            mantenimientoReportes.seleccionarReporte(25)
            mantenimientoReportes.cargarReporte(25)
            mostrarMantenimientos(5,"derecha")


        }
    }
}
