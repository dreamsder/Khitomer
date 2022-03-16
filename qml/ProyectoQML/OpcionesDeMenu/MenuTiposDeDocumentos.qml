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
    id: rectPrincipalMenuTipoDeDocumento
    width: 800
    height: 700
    color: "#00000000"
    //

    function serearPermisos(){

        txtCodigoTipoDocumento.textoInputBox=""
        txtDescripcionTipoDocumento.textoInputBox=""
        txtSerieTipoDocumento.textoInputBox=""
        txtDescripcionImpresionTipoDocumento.textoInputBox=""


        chbEsDocumentoDeVenta.setActivo(false)
        chbUtilizaObservaciones.setActivo(false)
        chbUtilizaComentarios.setActivo(false)
        chbUtilizaVendedorParaComisionar.setActivo(false)
        chbIngredoDeSerieManual.setActivo(false)
        chbIngredoDeNumeroDeDocumentoManual.setActivo(false)
        chbModificacionFechaPrecioManual.setActivo(false)
        chbModificacionFechEmisionManual.setActivo(false)
        chbpermiteBuscarClientesYProveedores.setActivo(false)
        chbPermiteSeleccionarTipoClienteYProveedor.setActivo(false)
        chbPermiteSoloFacturarAProveedores.setActivo(false)
        chbPermitIngresoDeArticulosTipoDocumentos.setActivo(false)
        cbxModoAfectaStockTipoDocumento.textoComboBox=qsTr("No afecta Stock")
        cbxModoAfectaStockTipoDocumento.codigoValorSeleccion="0"
        chbpermiteOperarConArticulosInactivosTipoDocumento.setActivo(false)
        chbCampoIngresoPrecioTipoDocumento.setActivo(false)
        chbCampoDeIngresoDeCantidadTipoDocumento.setActivo(false)
        chbUtilizacampoInfoExtendidoTipoDocumentos.setActivo(false)
        txtDescripcionCampoDatosExtraTipoDocumento.textoInputBox=""

        chbIngresoMedioDePago.setActivo(false)
        chbPermitechequesEnCajaParaPagoAProveedores.setActivo(false)
        chbUtilizaSoloMedioPagoCheque.setActivo(false)

        chbUtilizaTotalesTipoDocumento.setActivo(false)
        cbxModoAfectaTotalesTipoDocumento.textoComboBox=qsTr("No afecta Totales")
        cbxModoAfectaTotalesTipoDocumento.codigoValorSeleccion="0"
        chbUtilizaDescuentosAlTotalTipoDocumentos.setActivo(false)
        chbUtilizaRedondeoDelTotalTipoDocumentos.setActivo(false)


        chbEmitenEnImpresoras.setActivo(false)
        cbxCantidadCopiasTipoDocumento.textoComboBox=qsTr("0 copias")
        cbxCantidadCopiasTipoDocumento.codigoValorSeleccion="0"
        cbxListaModelosDeImpresion.textoComboBox=""
        cbxListaModelosDeImpresion.codigoValorSeleccion=""

        chbEmitenEnImpresorasTicket.setActivo(false)

        chbEmiteObservacionesEnImpresorasTicket.setActivo(false)

        cbxModoAfectaCuentaCorrienteDinero.textoComboBox=qsTr("No afecta CC")
        cbxModoAfectaCuentaCorrienteDinero.codigoValorSeleccion="0"
        cbxModoAfectaCuentaCorrienteMercaderia.textoComboBox=qsTr("No afecta CC")
        cbxModoAfectaCuentaCorrienteMercaderia.codigoValorSeleccion="0"
        chbUtilizaCuentasBancarias.setActivo(false)
        cbxModoAfectaCuentaBancaria.textoComboBox=qsTr("No afecta CB")
        cbxModoAfectaCuentaBancaria.codigoValorSeleccion="0"


        chbCampoIngresoPrecioMonedaReferenciaTipoDocumento.setActivo(false)
        chbSolicitarIngresoPrecioEnListasDePrecioTipoDocumento.setActivo(false)        
        chbNoPermiteFacturarConStockPrevistoCero.setActivo(false)

        chbUtilizaListaDePrecioManualTipoDocumentos.setActivo(false)

        chbUtilizaFormaDePagoTipoDocumentos.setActivo(false)

        chbNoAfectaElIvaTipoDocumentos.setActivo(false)


    }

    Text {
        id: txtTituloMenuOpcion
        x: 560
        color: "#4d5595"
        text: qsTr("mantenimiento de tipo de documentos")
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

    Row {
        id: rowBarraDeHerramientas
        x: 30
        height: 30
        anchors.top: parent.top
        anchors.topMargin: 20
        //
        spacing: 15
        BotonBarraDeHerramientas {
            id: botonNuevoDocumento
            x: 33
            y: 10
            //source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/TipoDocumentos.png"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Nuevo.png"
            toolTip: qsTr("Nuevo documento")
            anchors.verticalCenter: parent.verticalCenter
            z: 8

            onClic: {
                serearPermisos()
                txtCodigoTipoDocumento.textoInputBox=modeloListaTipoDocumentosMantenimiento.ultimoRegistroDeTipoDeDocumento()
                txtDescripcionTipoDocumento.tomarElFoco()
            }
        }

        BotonBarraDeHerramientas {
            id: botonGuardarDocumento
            x: 61
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            toolTip: qsTr("Guardar documento")
            anchors.verticalCenter: parent.verticalCenter
            z: 7
            onClic: {


                txtMensajeInformacion.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()


                var _chbPermitIngresoDeArticulosTipoDocumentos=0
                var _chbUtilizacampoInfoExtendidoTipoDocumentos=0
                var _chbUtilizaTotalesTipoDocumento=0
                var _chbIngresoMedioDePago=0
                var _chbModificacionFechaPrecioManual=0
                var _chbModificacionFechEmisionManual=0
                var _chbIngredoDeNumeroDeDocumentoManual=0
                var _chbIngredoDeSerieManual=0
                var _chbUtilizaVendedorParaComisionar=0
                var _chbpermiteBuscarClientesYProveedores=0
                var _chbPermiteSeleccionarTipoClienteYProveedor=0
                var _chbPermiteSoloFacturarAProveedores=0
                var _cbxModoAfectaCuentaCorrienteDinero=cbxModoAfectaCuentaCorrienteDinero.codigoValorSeleccion
                var _cbxModoAfectaCuentaCorrienteMercaderia=cbxModoAfectaCuentaCorrienteMercaderia.codigoValorSeleccion
                var _cbxModoAfectaStockTipoDocumento=cbxModoAfectaStockTipoDocumento.codigoValorSeleccion
                var _cbxModoAfectaTotalesTipoDocumento=cbxModoAfectaTotalesTipoDocumento.codigoValorSeleccion
                var _chbCampoDeIngresoDeCantidadTipoDocumento=0
                var _chbCampoIngresoPrecioTipoDocumento=0
                var _chbUtilizaDescuentosAlTotalTipoDocumentos=0
                var _chbEmitenEnImpresoras=0
                var _cbxListaModelosDeImpresion=cbxListaModelosDeImpresion.codigoValorSeleccion
                var _cbxCantidadCopiasTipoDocumento=cbxCantidadCopiasTipoDocumento.codigoValorSeleccion
                var _chbUtilizaObservaciones=0
                var _chbUtilizaComentarios=0
                var _cbxModoAfectaCuentaBancaria=cbxModoAfectaCuentaBancaria.codigoValorSeleccion
                var _chbUtilizaCuentasBancarias=0
                var _chbPermitechequesEnCajaParaPagoAProveedores=0
                var _chbUtilizaSoloMedioPagoCheque=0
                var _chbEsDocumentoDeVenta=0
                var _chbpermiteOperarConArticulosInactivosTipoDocumento=0
                var _chbUtilizaRedondeoDelTotalTipoDocumentos=0

                var _chbUtilizaListaDePrecioManualTipoDocumentos=0
                var _chbCampoIngresoPrecioMonedaReferenciaTipoDocumento=0
                var _chbSolicitarIngresoPrecioEnListasDePrecioTipoDocumento=0

                var _chbNoPermiteFacturarConStockPrevistoCero=0

                var _chbUtilizaFormaDePagoTipoDocumentos=0

                var _chbNoAfectaElIvaTipoDocumentos=0

                var _chbEmitenEnImpresorasTicket=0

                var _chbEmiteObservacionesEnImpresorasTicket=0


                if(chbPermitIngresoDeArticulosTipoDocumentos.chekActivo){_chbPermitIngresoDeArticulosTipoDocumentos    =1}
                if(chbUtilizacampoInfoExtendidoTipoDocumentos.chekActivo){  _chbUtilizacampoInfoExtendidoTipoDocumentos    =1}
                if(chbUtilizaTotalesTipoDocumento.chekActivo){    _chbUtilizaTotalesTipoDocumento    =1}
                if(chbIngresoMedioDePago.chekActivo){ _chbIngresoMedioDePago    =1}
                if(chbModificacionFechaPrecioManual.chekActivo){     _chbModificacionFechaPrecioManual    =1}
                if(chbModificacionFechEmisionManual.chekActivo){ _chbModificacionFechEmisionManual    =1}
                if(chbIngredoDeNumeroDeDocumentoManual.chekActivo){   _chbIngredoDeNumeroDeDocumentoManual    =1}
                if(chbIngredoDeSerieManual.chekActivo){     _chbIngredoDeSerieManual    =1}
                if(chbUtilizaVendedorParaComisionar.chekActivo){_chbUtilizaVendedorParaComisionar    =1}
                if(chbpermiteBuscarClientesYProveedores.chekActivo){ _chbpermiteBuscarClientesYProveedores    =1}
                if(chbPermiteSeleccionarTipoClienteYProveedor.chekActivo){_chbPermiteSeleccionarTipoClienteYProveedor    =1}
                if(chbPermiteSoloFacturarAProveedores.chekActivo){_chbPermiteSoloFacturarAProveedores    =1}
                if(chbCampoDeIngresoDeCantidadTipoDocumento.chekActivo){        _chbCampoDeIngresoDeCantidadTipoDocumento    =1}
                if(chbCampoIngresoPrecioTipoDocumento.chekActivo){    _chbCampoIngresoPrecioTipoDocumento    =1}
                if(chbUtilizaDescuentosAlTotalTipoDocumentos.chekActivo){   _chbUtilizaDescuentosAlTotalTipoDocumentos    =1}
                if(chbEmitenEnImpresoras.chekActivo){   _chbEmitenEnImpresoras    =1}
                if(chbUtilizaObservaciones.chekActivo){   _chbUtilizaObservaciones  =1}
                if(chbUtilizaComentarios.chekActivo){   _chbUtilizaComentarios  =1}


                if(chbUtilizaCuentasBancarias.chekActivo){    _chbUtilizaCuentasBancarias    =1}
                if(chbPermitechequesEnCajaParaPagoAProveedores.chekActivo){   _chbPermitechequesEnCajaParaPagoAProveedores    =1}
                if(chbUtilizaSoloMedioPagoCheque.chekActivo){   _chbUtilizaSoloMedioPagoCheque    =1}
                if(chbEmitenEnImpresorasTicket.chekActivo){   _chbEmitenEnImpresorasTicket    =1}
                if(chbEmiteObservacionesEnImpresorasTicket.chekActivo){   _chbEmiteObservacionesEnImpresorasTicket    =1}


                if(chbEsDocumentoDeVenta.chekActivo){  _chbEsDocumentoDeVenta    =1}
                if(chbpermiteOperarConArticulosInactivosTipoDocumento.chekActivo){_chbpermiteOperarConArticulosInactivosTipoDocumento    =1}
                if(chbUtilizaRedondeoDelTotalTipoDocumentos.chekActivo){  _chbUtilizaRedondeoDelTotalTipoDocumentos    =1}
                if(chbUtilizaListaDePrecioManualTipoDocumentos.chekActivo){  _chbUtilizaListaDePrecioManualTipoDocumentos    =1}
                if(chbCampoIngresoPrecioMonedaReferenciaTipoDocumento.chekActivo){  _chbCampoIngresoPrecioMonedaReferenciaTipoDocumento    =1}
                if(chbSolicitarIngresoPrecioEnListasDePrecioTipoDocumento.chekActivo){  _chbSolicitarIngresoPrecioEnListasDePrecioTipoDocumento    =1}
               if(chbNoPermiteFacturarConStockPrevistoCero.chekActivo){  _chbNoPermiteFacturarConStockPrevistoCero    =1}


                if(chbUtilizaFormaDePagoTipoDocumentos.chekActivo){  _chbUtilizaFormaDePagoTipoDocumentos    =1}
                if(chbNoAfectaElIvaTipoDocumentos.chekActivo){  _chbNoAfectaElIvaTipoDocumentos    =1}


                var resultadoConsulta = modeloListaTipoDocumentosMantenimiento.insertarTipoDocumento(
                            txtCodigoTipoDocumento.textoInputBox.trim(),
                            txtDescripcionTipoDocumento.textoInputBox.trim(),
                            _chbPermitIngresoDeArticulosTipoDocumentos,
                            _chbUtilizacampoInfoExtendidoTipoDocumentos,
                            _chbUtilizaTotalesTipoDocumento,
                            _chbIngresoMedioDePago,
                            _chbModificacionFechaPrecioManual,
                            _chbModificacionFechEmisionManual,
                            _chbIngredoDeNumeroDeDocumentoManual,
                            _chbIngredoDeSerieManual,
                            txtSerieTipoDocumento.textoInputBox.trim(),
                            _chbUtilizaVendedorParaComisionar,
                            _chbpermiteBuscarClientesYProveedores,
                            _chbPermiteSeleccionarTipoClienteYProveedor,
                            _chbPermiteSoloFacturarAProveedores,
                            _cbxModoAfectaCuentaCorrienteDinero,
                            _cbxModoAfectaCuentaCorrienteMercaderia,
                            _cbxModoAfectaStockTipoDocumento,
                            _cbxModoAfectaTotalesTipoDocumento,
                            _chbCampoDeIngresoDeCantidadTipoDocumento,
                            _chbCampoIngresoPrecioTipoDocumento,
                            _chbUtilizaDescuentosAlTotalTipoDocumentos,
                            _chbEmitenEnImpresoras,
                            _cbxListaModelosDeImpresion,
                            _cbxCantidadCopiasTipoDocumento,
                            _chbUtilizaObservaciones,
                            _chbUtilizaComentarios,
                            _cbxModoAfectaCuentaBancaria,
                            _chbUtilizaCuentasBancarias,
                            _chbPermitechequesEnCajaParaPagoAProveedores,
                            _chbUtilizaSoloMedioPagoCheque,
                            _chbEsDocumentoDeVenta,
                            txtDescripcionImpresionTipoDocumento.textoInputBox.trim(),
                            _chbpermiteOperarConArticulosInactivosTipoDocumento,



                            _chbUtilizaRedondeoDelTotalTipoDocumentos,
                            _chbCampoIngresoPrecioMonedaReferenciaTipoDocumento,
                            txtDescripcionCampoDatosExtraTipoDocumento.textoInputBox.trim(),
                            _chbUtilizaListaDePrecioManualTipoDocumentos,
                            _chbUtilizaFormaDePagoTipoDocumentos,
                            _chbNoAfectaElIvaTipoDocumentos,
                            _chbSolicitarIngresoPrecioEnListasDePrecioTipoDocumento,
                            _chbNoPermiteFacturarConStockPrevistoCero,
                            _chbEmitenEnImpresorasTicket,
                            _chbEmiteObservacionesEnImpresorasTicket

                            )

                if(resultadoConsulta==1){

                    txtMensajeInformacion.color="#2f71a0"
                    txtMensajeInformacion.text=qsTr("Tipo de Documento "+ txtCodigoTipoDocumento.textoInputBox+" dado de alta correctamente")

                    modeloListaTipoDocumentosMantenimiento.limpiarListaTipoDocumentos()
                    modeloListaTipoDocumentosMantenimiento.buscarTodosLosTipoDocumentos("codigoTipoDocumento=",txtCodigoTipoDocumento.textoInputBox.trim())
                    listaDeTiposDeDocumentos.currentIndex=0;

                    serearPermisos()
                    txtCodigoTipoDocumento.tomarElFoco()

                    modeloListaTipoDocumentosComboBox.limpiarListaTipoDocumentos()
                    modeloListaTipoDocumentosComboBox.buscarTipoDocumentos("1=","1",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))


                }else if(resultadoConsulta==2){
                    txtMensajeInformacion.color="#2f71a0"
                    txtMensajeInformacion.text=qsTr("Tipo de Documento "+ txtCodigoTipoDocumento.textoInputBox+" actualizado correctamente")

                    serearPermisos()
                    txtCodigoTipoDocumento.tomarElFoco()
                    modeloListaTipoDocumentosMantenimiento.limpiarListaTipoDocumentos()
                    modeloListaTipoDocumentosMantenimiento.buscarTodosLosTipoDocumentos("codigoTipoDocumento=",txtCodigoTipoDocumento.textoInputBox.trim())
                    listaDeTiposDeDocumentos.currentIndex=0;

                    modeloListaTipoDocumentosComboBox.limpiarListaTipoDocumentos()
                    modeloListaTipoDocumentosComboBox.buscarTipoDocumentos("1=","1",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))

                }else if(resultadoConsulta==-1){
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text=qsTr("No se pudo conectar a la base de datos.")
                }else if(resultadoConsulta==-2){
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text=qsTr("No se pudo actualizar la información del tipo de documento.")
                }else if(resultadoConsulta==-3){
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text=qsTr("No se pudo dar de alta el tipo de documento.")
                }else if(resultadoConsulta==-4){
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text=qsTr("No se pudo realizar la consulta a la base de datos.")
                }else if(resultadoConsulta==-5){
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text=qsTr("Faltan datos para guardar el tipo de documento.")
                }
            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarDocumento
            x: 54
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            toolTip: qsTr("Eliminar documento")
            anchors.verticalCenter: parent.verticalCenter
            z: 6
            onClic:{


                if(txtCodigoTipoDocumento.textoInputBox.trim()!="")
                    if(funcionesmysql.mensajeAdvertencia(qsTr("Realmente desea eliminar el tipo de documento "+txtCodigoTipoDocumento.textoInputBox.trim()+"?\n\nPresione [ Sí ] para confirmar."))){

                        txtMensajeInformacion.visible=true
                        txtMensajeInformacionTimer.stop()
                        txtMensajeInformacionTimer.start()

                        if(modeloListaTipoDocumentosMantenimiento.eliminarTipoDocumento(txtCodigoTipoDocumento.textoInputBox.trim())){

                            txtMensajeInformacion.color="#2f71a0"
                            txtMensajeInformacion.text=qsTr("Tipo de documento "+txtCodigoTipoDocumento.textoInputBox.trim()+" eliminado.")

                            modeloListaTipoDocumentosMantenimiento.limpiarListaTipoDocumentos()
                            modeloListaTipoDocumentosMantenimiento.buscarTodosLosTipoDocumentos("1=","1")
                            listaDeTiposDeDocumentos.currentIndex=0;

                            serearPermisos()
                            txtCodigoTipoDocumento.tomarElFoco()

                            modeloListaTipoDocumentosComboBox.limpiarListaTipoDocumentos()
                            modeloListaTipoDocumentosComboBox.buscarTipoDocumentos("1=","1",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))

                        }else{
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text=qsTr("No se puede eliminar el tipo de documento.")
                        }}
            }
        }

        BotonBarraDeHerramientas {
            id: botonListarTodosLosDocumentos
            x: 47
            y: 10
            toolTip: qsTr("Listar todos los documentos")
            z: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            anchors.verticalCenter: parent.verticalCenter
            onClic: {
                modeloListaTipoDocumentosMantenimiento.limpiarListaTipoDocumentos()
                modeloListaTipoDocumentosMantenimiento.buscarTodosLosTipoDocumentos("1=","1")
                listaDeTiposDeDocumentos.currentIndex=0;
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
        anchors.rightMargin: 10
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.left: parent.left
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

    Rectangle {
        id: rectListaDeTipoDeDocumentos
        height: 200
        color: "#c3c3c7"
        radius: 3
        clip: true
        //  anchors.top: row1.bottom
        //  anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        //
        ListView {
            id: listaDeTiposDeDocumentos
            clip: true
            highlightRangeMode: ListView.NoHighlightRange
            anchors.top: parent.top
            boundsBehavior: Flickable.DragAndOvershootBounds
            highlightFollowsCurrentItem: true
            anchors.right: parent.right
            delegate: ListaTipoDocumentos{}
            snapMode: ListView.NoSnap
            anchors.bottomMargin: 25
            spacing: 2
            anchors.bottom: parent.bottom
            flickableDirection: Flickable.VerticalFlick
            anchors.leftMargin: 1
            keyNavigationWraps: true
            anchors.left: parent.left
            interactive: true
            //
            anchors.topMargin: 25
            anchors.rightMargin: 1
            model: modeloListaTipoDocumentosMantenimiento

            Rectangle {
                id: scrollbarlistaDeTipoDocumentos
                y: listaDeTiposDeDocumentos.visibleArea.yPosition * listaDeTiposDeDocumentos.height+5
                width: 10
                color: "#000000"
                height: listaDeTiposDeDocumentos.visibleArea.heightRatio * listaDeTiposDeDocumentos.height+18
                radius: 2
                anchors.right: listaDeTiposDeDocumentos.right
                anchors.rightMargin: 4
                z: 1
                opacity: 0.500
                visible: true
                //
            }
        }

        Text {
            id: txtTituloListaTipoDocumentos
            text: qsTr("Tipos de Documentos: "+listaDeTiposDeDocumentos.count)
            font.family: "Arial"
            anchors.top: parent.top
            anchors.topMargin: 5
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
            anchors.right: parent.right
            anchors.rightMargin: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
            anchors.bottom: parent.bottom
            toolTip: ""
            anchors.bottomMargin: 5
            rotation: -90

            onClic: listaDeTiposDeDocumentos.positionViewAtIndex(listaDeTiposDeDocumentos.count-1,0)
        }

        BotonBarraDeHerramientas {
            id: botonSubirListaFinal1
            x: 783
            y: 35
            width: 14
            height: 14
            anchors.right: parent.right
            anchors.rightMargin: 3
            anchors.top: parent.top
            anchors.topMargin: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
            toolTip: ""
            rotation: 90


            onClic: listaDeTiposDeDocumentos.positionViewAtIndex(0,0)

        }
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
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

    Rectangle {
        id: rectSolapaTipoDocumentos
        color: "#00000000"
        clip: true
        anchors.top: flow8.bottom
        anchors.topMargin: 10
        anchors.bottom: rectListaDeTipoDeDocumentos.top
        anchors.bottomMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        Flickable {
            id: flickable1
            anchors.fill: parent
            contentWidth: row1.implicitWidth
            contentHeight: parent.height
            interactive: true
            clip: false
            focus: false

            Row {
                id: row1
                z: 1
                anchors.bottomMargin: 0
                anchors.fill: parent

                Rectangle {
                    id: rectConfiguracionGeneralTipoDocumento
                    width: 650
                    height: rectSolapaTipoDocumentos.height
                    color: "#a4a4ea"
                    clip: false
                    //

                    Rectangle {
                        id: rectLineaVerticalMenuBlanco1
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        anchors.right: parent.right
                        anchors.rightMargin: 6
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.bottomMargin: 5
                        rotation: 0
                        //     anchors.leftMargin: 0
                        //     anchors.left: listview1.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris1
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.bottomMargin: 5
                        rotation: 0
                    }

                    Text {
                        id: text3
                        color: "#fdfdfd"
                        text: qsTr("configuración general del documento")
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        //
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        rotation: 0
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow1
                        clip: true
                        flow: Flow.TopToBottom
                        spacing: 5
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 10
                        anchors.top: rectangle4.bottom
                        anchors.topMargin: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 30

                        CheckBox {
                            id: chbEsDocumentoDeVenta
                            x: 147
                            y: 81
                            tamanioLetra: 12
                            textoValor: qsTr("Es un documento de venta(Indicador de reportes)")
                        }

                        CheckBox {
                            id: chbUtilizaObservaciones
                            x: 153
                            y: 73
                            tamanioLetra: 12
                            textoValor: qsTr("Utiliza observaciones")
                        }


                        CheckBox {
                            id: chbEmiteObservacionesEnImpresorasTicket
                            textoValor: qsTr("Imprime observaciones en ticket")
                        }

                        CheckBox {
                            id: chbUtilizaComentarios
                            tamanioLetra: 12
                            textoValor: qsTr("Utiliza comentarios")
                        }

                        CheckBox {
                            id: chbUtilizaVendedorParaComisionar
                            x: 146
                            y: 82
                            tamanioLetra: 12
                            textoValor: qsTr("Utiliza vendedor para comisionar")
                        }

                        CheckBox {
                            id: chbIngredoDeSerieManual
                            x: 141
                            y: 75
                            tamanioLetra: 12
                            textoValor: qsTr("Ingreso de serie del documento manual")
                        }

                        CheckBox {
                            id: chbIngredoDeNumeroDeDocumentoManual
                            x: 146
                            y: 79
                            tamanioLetra: 12
                            textoValor: qsTr("Ingreso de numero del documento manual")
                        }

                        CheckBox {
                            id: chbModificacionFechaPrecioManual
                            x: 150
                            y: 76
                            tamanioLetra: 12
                            textoValor: qsTr("Ingreso de fecha de precio manual")
                        }

                        CheckBox {
                            id: chbModificacionFechEmisionManual
                            x: 151
                            y: 85
                            tamanioLetra: 12
                            textoValor: qsTr("Ingreso de fecha de emisión manual")
                        }
                    }

                    Rectangle {
                        id: rectangle2
                        height: 1
                        color: "#ffffff"
                        anchors.top: text3.bottom
                        anchors.topMargin: 15
                        anchors.right: parent.right
                        anchors.rightMargin: 30
                        anchors.left: parent.left
                        anchors.leftMargin: 30
                        //
                    }

                    Rectangle {
                        id: rectangle4
                        x: 8
                        y: 0
                        height: 1
                        color: "#abb2b1"
                        //
                        anchors.top: text3.bottom
                        anchors.topMargin: 16
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }

                Rectangle {
                    id: rectConfiguracionClientesProveedoresTipoDocumento
                    width: 530
                    height: rectSolapaTipoDocumentos.height
                    color: "#a6a4ea"
                    //

                    Rectangle {
                        id: rectLineaVerticalMenuBlanco2
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 6
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //     anchors.leftMargin: 0
                        //     anchors.left: listview1.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris2
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 5
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //      anchors.leftMargin: 1
                        //      anchors.left: listview1.right
                    }

                    Text {
                        id: text2
                        color: "#fdfdfd"
                        text: qsTr("clientes/proveedores")
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        style: Text.Outline
                        font.underline: true
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        //
                        font.pixelSize: 20
                        font.italic: false
                        font.bold: true
                        rotation: 0
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    CheckBox {
                        id: chbpermiteBuscarClientesYProveedores
                        x: 40
                        y: 45
                        tamanioLetra: 15
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        textoValor: qsTr("Búsqueda de clientes/proveedores")
                        anchors.leftMargin: 20
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow2
                        x: 4
                        clip: true
                        flow: Flow.TopToBottom
                        spacing: 5
                        anchors.top: chbpermiteBuscarClientesYProveedores.bottom
                        anchors.topMargin: 20
                        CheckBox {
                            id: chbPermiteSeleccionarTipoClienteYProveedor
                            x: 147
                            y: 81
                            tamanioLetra: 12
                            textoValor: qsTr("Seleccion manual de tipo (cliente o proveedor)")
                        }

                        CheckBox {
                            id: chbPermiteSoloFacturarAProveedores
                            x: 153
                            y: 73
                            tamanioLetra: 12
                            textoValor: qsTr("Solo se factura a proveedores (Opción que re-escribe a las anteriores)")
                        }
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 20
                        anchors.bottomMargin: 10
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle5
                        x: 4
                        height: 1
                        color: "#ffffff"
                        //
                        anchors.top: chbpermiteBuscarClientesYProveedores.bottom
                        anchors.topMargin: 10
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle6
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        //
                        anchors.top: rectangle5.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }

                Rectangle {
                    id: rectConfiguracionArticulosTipoDocumento
                    width: 600
                    height: rectSolapaTipoDocumentos.height
                    color: "#a4a4ea"
                    //
                    Rectangle {
                        id: rectLineaVerticalMenuBlanco4
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 6
                        visible: true
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris4
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 5
                        visible: true
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                    }

                    Text {
                        id: text5
                        color: "#fdfdfd"
                        text: qsTr("artículos")
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        //
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        font.bold: true
                        rotation: 0
                        anchors.leftMargin: 10
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    CheckBox {
                        id: chbPermitIngresoDeArticulosTipoDocumentos
                        x: 40
                        y: 45
                        tamanioLetra: 15
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        textoValor: qsTr("Ingreso de artículos activado")
                        anchors.leftMargin: 20
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow4
                        x: 4
                        flow: Flow.TopToBottom
                        clip: true
                        spacing: 3
                        anchors.top: chbPermitIngresoDeArticulosTipoDocumentos.bottom
                        anchors.topMargin: 20




                        ComboBoxGenerico {
                            id: cbxModoAfectaStockTipoDocumento
                            width: 170
                            z: 1
                            colorTitulo: "#333333"
                            colorRectangulo: "#cac1bd"
                            textoTitulo: qsTr("Modo afecta stock:")
                            modeloItems: modeloModoAfectaStock
                            codigoValorSeleccion: "0"
                            textoComboBox: qsTr("No afecta Stock")

                            ListModel{
                                id:modeloModoAfectaStock
                                ListElement {
                                    codigoItem: "0"
                                    descripcionItem: "No afecta Stock"
                                }
                                ListElement {
                                    codigoItem: "1"
                                    descripcionItem: "Suma al Stock+"
                                }
                                ListElement {
                                    codigoItem: "-1"
                                    descripcionItem: "Resta al Stock-"
                                }
                            }
                        }
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 20
                        anchors.bottomMargin: 10
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                        CheckBox {
                            id: chbpermiteOperarConArticulosInactivosTipoDocumento
                            x: 138
                            y: 76
                            tamanioLetra: 12
                            textoValor: qsTr("Permite operar con artículos inactivos")
                        }
                        CheckBox {
                            id: chbCampoIngresoPrecioTipoDocumento
                            x: 144
                            y: 72
                            tamanioLetra: 12
                            textoValor: qsTr("Campo para ingreso de precio")
                        }
                        CheckBox {
                            id: chbCampoDeIngresoDeCantidadTipoDocumento
                            x: 153
                            y: 73
                            tamanioLetra: 12
                            textoValor: qsTr("Campo de ingreso de cantidad")
                        }
                        CheckBox {
                            id: chbUtilizacampoInfoExtendidoTipoDocumentos
                            x: 147
                            y: 81
                            tamanioLetra: 12
                            textoValor: qsTr("Campo extra de datos para item's de factura")
                            onChekActivoChanged: {
                                if(chekActivo){
                                    txtDescripcionCampoDatosExtraTipoDocumento.enable=true
                                    txtDescripcionCampoDatosExtraTipoDocumento.enabled=true
                                    txtDescripcionCampoDatosExtraTipoDocumento.tomarElFoco()
                                }else{
                                    txtDescripcionCampoDatosExtraTipoDocumento.enable=false
                                    txtDescripcionCampoDatosExtraTipoDocumento.enabled=false
                                    txtDescripcionTipoDocumento.tomarElFoco()
                                }
                            }
                        }

                        TextInputSimple {
                            id: txtDescripcionCampoDatosExtraTipoDocumento
                        //    width: 200
                            enFocoSeleccionarTodo: true
                            textoInputBox: ""
                            botonBuscarTextoVisible: false
                            largoMaximo: 20
                            botonBorrarTextoVisible: true
                            textoTitulo: qsTr("Descripción campo extra:")
                            colorDeTitulo: "#333333"
                            enable: {
                                if(chbUtilizacampoInfoExtendidoTipoDocumentos.chekActivo){
                                    true
                                }else{
                                    false
                                }
                            }
                            enabled: {
                                if(chbUtilizacampoInfoExtendidoTipoDocumentos.chekActivo){
                                    true
                                }else{
                                    false
                                }
                            }
                        }

                        CheckBox {
                            id: chbCampoIngresoPrecioMonedaReferenciaTipoDocumento
                            tamanioLetra: 12
                            textoValor: qsTr("Ingreso de costo en moneda referencia( "+modeloMonedas.retornaSimboloMoneda(modeloMonedas.retornaMonedaReferenciaSistema())+" )")
                        }

                        CheckBox {
                            id: chbSolicitarIngresoPrecioEnListasDePrecioTipoDocumento
                            tamanioLetra: 12
                            textoValor: qsTr("Ingreso de precios en listas de precios")
                        }

                        CheckBox {
                            id: chbNoPermiteFacturarConStockPrevistoCero
                            textoValor: qsTr("No permitir facturar con stock previsto cero")
                            tamanioLetra: 12
                        }
                    }

                    Rectangle {
                        id: rectangle9
                        x: -3
                        height: 1
                        color: "#ffffff"
                        //
                        anchors.top: chbPermitIngresoDeArticulosTipoDocumentos.bottom
                        anchors.topMargin: 10
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle10
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        //
                        anchors.top: rectangle9.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }

                Rectangle {
                    id: rectConfiguracionMediosDePago
                    width: 450
                    height: rectSolapaTipoDocumentos.height
                    color: "#a4a4ea"
                    //
                    Rectangle {
                        id: rectLineaVerticalMenuBlanco5
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 6
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris5
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 5
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                    }

                    Text {
                        id: text6
                        color: "#fdfdfd"
                        text: qsTr("medios de pago")
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        //
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        rotation: 0
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    CheckBox {
                        id: chbIngresoMedioDePago
                        x: 40
                        y: 45
                        tamanioLetra: 15
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        textoValor: qsTr("Ingreso de medio de pago activado")
                        anchors.leftMargin: 20
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow5
                        x: 4
                        clip: true
                        flow: Flow.TopToBottom
                        spacing: 5
                        anchors.top: chbIngresoMedioDePago.bottom
                        anchors.topMargin: 20
                        CheckBox {
                            id: chbPermitechequesEnCajaParaPagoAProveedores
                            x: 147
                            y: 81
                            tamanioLetra: 12
                            textoValor: qsTr("Cheques en caja disponibles para pago a proveedores")
                        }

                        CheckBox {
                            id: chbUtilizaSoloMedioPagoCheque
                            x: 153
                            y: 73
                            tamanioLetra: 12
                            textoValor: qsTr("Utilizar solo medio de pago Cheque (Oculta los demas)")
                        }
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 30
                        anchors.bottomMargin: 10
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle11
                        x: -3
                        height: 1
                        color: "#ffffff"
                        //
                        anchors.top: chbIngresoMedioDePago.bottom
                        anchors.topMargin: 10
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle12
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        //
                        anchors.top: rectangle11.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }

                Rectangle {
                    id: rectConfiguracionTotalesTipoDocumento
                    width: 550
                    height: rectSolapaTipoDocumentos.height
                    color: "#a4a4ea"
                    //
                    Rectangle {
                        id: rectLineaVerticalMenuBlanco6
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 6
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris6
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 5
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                    }

                    Text {
                        id: text7
                        color: "#fdfdfd"
                        text: qsTr("total del documento")
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        //
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        rotation: 0
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    CheckBox {
                        id: chbUtilizaTotalesTipoDocumento
                        x: 40
                        y: 45
                        tamanioLetra: 15
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        textoValor: qsTr("El documento utiliza totales")
                        anchors.leftMargin: 20
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow6
                        x: 4
                        flow: Flow.TopToBottom
                        clip: true
                        spacing: 5
                        anchors.top: chbUtilizaTotalesTipoDocumento.bottom
                        anchors.topMargin: 20
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 20
                        anchors.bottomMargin: 10
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left



                        ComboBoxGenerico {
                            id: cbxModoAfectaTotalesTipoDocumento
                            width: 170
                            z: 2
                            colorTitulo: "#333333"
                            colorRectangulo: "#cac1bd"
                            textoTitulo: qsTr("Modo afecta totales:")
                            modeloItems: modeloModoAfectaTotales
                            codigoValorSeleccion: "0"
                            textoComboBox: qsTr("No afecta Totales")

                            ListModel{
                                id:modeloModoAfectaTotales
                                ListElement {
                                    codigoItem: "0"
                                    descripcionItem: "No afecta Totales"
                                }
                                ListElement {
                                    codigoItem: "1"
                                    descripcionItem: "Suma al Total+"
                                }
                                ListElement {
                                    codigoItem: "-1"
                                    descripcionItem: "Resta al Total-"
                                }
                            }
                        }

                        CheckBox {
                            id: chbUtilizaDescuentosAlTotalTipoDocumentos
                            x: 153
                            y: 73
                            tamanioLetra: 12
                            textoValor: qsTr("Utiliza Descuentos al Total")
                        }

                        CheckBox {
                            id: chbUtilizaRedondeoDelTotalTipoDocumentos
                            x: 161
                            y: 73
                            tamanioLetra: 12
                            textoValor: qsTr("Redondear total del documento")
                        }

                        CheckBox {
                            id: chbUtilizaListaDePrecioManualTipoDocumentos
                            tamanioLetra: 12
                            textoValor: qsTr("Utiliza lista de precio manual")
                        }

                        CheckBox {
                            id: chbUtilizaFormaDePagoTipoDocumentos
                            textoValor: qsTr("Utiliza formas de pago")
                            tamanioLetra: 12
                        }

                        CheckBox {
                            id: chbNoAfectaElIvaTipoDocumentos
                            tamanioLetra: 12
                            textoValor: qsTr("El documento no afecta IVA")
                        }


                     /*
                        ComboBoxCheckBoxGenerico{
                            id:cbxRedondeoPorMoneda
                            width: 300
                            textoTitulo: "Redondeo por monedas:"
                            //modeloItems: modeloListaMonedas

                         //   colorRectangulo: "#cac1bd"
                         //   colorTitulo: "#333333"
                        }*/

                    }

                    Rectangle {
                        id: rectangle13
                        x: -3
                        height: 1
                        color: "#ffffff"
                        //
                        anchors.top: chbUtilizaTotalesTipoDocumento.bottom
                        anchors.topMargin: 10
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle14
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        //
                        anchors.top: rectangle13.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }


                Rectangle {
                    id: rectConfiguracionImpresionTipoDocumento
                    width: 400
                    height: rectSolapaTipoDocumentos.height
                    color: "#a4a4ea"
                    //
                    Rectangle {
                        id: rectLineaVerticalMenuBlanco8
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 6
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris8
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 5
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                    }

                    Text {
                        id: text9
                        color: "#fdfdfd"
                        text: qsTr("impresión")
                        //
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        rotation: 0
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    CheckBox {
                        id: chbEmitenEnImpresoras
                        x: 40
                        y: 45
                        tamanioLetra: 15
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        textoValor: qsTr("Emite en impresoras")
                        anchors.leftMargin: 20
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow9
                        x: 4
                        flow: Flow.TopToBottom
                        spacing: 5
                        anchors.top: chbEmitenEnImpresoras.bottom
                        anchors.topMargin: 20
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 20
                        anchors.bottomMargin: 10
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                        z:1000

                        ComboBoxGenerico {
                            id: cbxCantidadCopiasTipoDocumento
                            width: 170
                            codigoValorSeleccion: "0"
                            colorTitulo: "#333333"
                            textoComboBox: qsTr("0 copias")
                            colorRectangulo: "#cac1bd"
                            textoTitulo: qsTr("Cantidad de copias:")
                            modeloItems: modeloCantidadCopiasImpresion
                            z: 2
                            ListModel {
                                id: modeloCantidadCopiasImpresion
                                ListElement {
                                    descripcionItem: "0 copias"
                                    codigoItem: "0"
                                }
                                ListElement {
                                    descripcionItem: "1 copia"
                                    codigoItem: "1"
                                }

                                ListElement {
                                    descripcionItem: "2 copias"
                                    codigoItem: "2"
                                }

                                ListElement {
                                    descripcionItem: "3 copias"
                                    codigoItem: "3"
                                }
                            }
                        }
                        ComboBoxGenerico {
                            id: cbxListaModelosDeImpresion
                            width: 170
                            codigoValorSeleccion: ""
                            colorTitulo: "#333333"
                            textoComboBox: ""
                            colorRectangulo: "#cac1bd"
                            textoTitulo: qsTr("Modelo de impresión:")
                            modeloItems: modeloModelosDeImpresion
                            z: 1
                        }
                        CheckBox {
                            id: chbEmitenEnImpresorasTicket
                            textoValor: qsTr("Emite en impresora de ticket")
                        }                        
                    }

                    Rectangle {
                        id: rectangle17
                        x: -3
                        height: 1
                        color: "#ffffff"
                        //
                        anchors.top: chbEmitenEnImpresoras.bottom
                        anchors.topMargin: 10
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle18
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        //
                        anchors.top: rectangle17.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }

                Rectangle {
                    id: rectCuentasCorrientesTipoDocumento
                    width: 400
                    height: rectSolapaTipoDocumentos.height
                    color: "#a4a4ea"
                    //
                    Rectangle {
                        id: rectLineaVerticalMenuBlanco7
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 6
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris7
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 5
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                    }

                    Text {
                        id: text8
                        color: "#fdfdfd"
                        text: qsTr("cuentas corrientes")
                        styleColor: "#8d8b8b"
                        //
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        font.family: "Arial"
                        rotation: 0
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow7
                        x: 4
                        flow: Flow.TopToBottom
                        clip: true
                        spacing: 5
                        anchors.top: rectangle16.bottom
                        anchors.topMargin: 10
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 30
                        anchors.bottomMargin: 10
                        anchors.right: parent.right
                        anchors.leftMargin: 60
                        anchors.left: parent.left

                        ComboBoxGenerico {
                            id: cbxModoAfectaCuentaCorrienteDinero
                            width: 185
                            textoTitulo: qsTr("Modo afecta CC dinero:")
                            codigoValorSeleccion: "0"
                            colorTitulo: "#333333"
                            ListModel {
                                id: modeloModoAfectaCuentaCorrienteDinero
                                ListElement {
                                    descripcionItem: "No afecta CC"
                                    codigoItem: "0"
                                }

                                ListElement {
                                    descripcionItem: "Suma a la CC+"
                                    codigoItem: "1"
                                }

                                ListElement {
                                    descripcionItem: "Resta a la CC-"
                                    codigoItem: "-1"
                                }
                            }
                            textoComboBox: qsTr("No afecta CC")
                            colorRectangulo: "#cac1bd"
                            modeloItems: modeloModoAfectaCuentaCorrienteDinero
                            z: 3
                        }
                        ComboBoxGenerico {
                            id: cbxModoAfectaCuentaCorrienteMercaderia
                            width: 185
                            textoTitulo: qsTr("Modo afecta CC mercaderia:")
                            codigoValorSeleccion: "0"
                            colorTitulo: "#333333"
                            ListModel {
                                id: modeloModoAfectaCuentaCorrienteMercaderia
                                ListElement {
                                    descripcionItem: "No afecta CC"
                                    codigoItem: "0"
                                }

                                ListElement {
                                    descripcionItem: "Suma a la CC+"
                                    codigoItem: "1"
                                }

                                ListElement {
                                    descripcionItem: "Resta a la CC-"
                                    codigoItem: "-1"
                                }
                            }
                            textoComboBox: qsTr("No afecta CC")
                            colorRectangulo: "#cac1bd"
                            modeloItems: modeloModoAfectaCuentaCorrienteMercaderia
                            z: 2
                        }
                    }

                    Rectangle {
                        id: rectangle15
                        x: -3
                        height: 1
                        color: "#ffffff"
                        //
                        anchors.top: text8.bottom
                        anchors.topMargin: 15
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle16
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        //
                        anchors.top: rectangle15.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }

                Rectangle {
                    id: rectConfiguracionCuentasBancariasTipoDocumento
                    width: 400
                    height: rectSolapaTipoDocumentos.height
                    color: "#a4a4ea"
                    //
                    Rectangle {
                        id: rectLineaVerticalMenuBlanco9
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 6
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris9
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 5
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                    }

                    Text {
                        id: text10
                        color: "#fdfdfd"
                        text: qsTr("cuentas bancarias")
                        //
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        rotation: 0
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    CheckBox {
                        id: chbUtilizaCuentasBancarias
                        x: 40
                        y: 45
                        tamanioLetra: 15
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        textoValor: qsTr("Utiliza cuentas bancarias")
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow10
                        x: 4
                        spacing: 5
                        flow: Flow.TopToBottom
                        anchors.top: chbUtilizaCuentasBancarias.bottom
                        anchors.topMargin: 20
                        ComboBoxGenerico {
                            id: cbxModoAfectaCuentaBancaria
                            width: 187
                            textoTitulo: qsTr("Modo afecta cuenta bancaria:")
                            codigoValorSeleccion: "0"
                            colorTitulo: "#333333"
                            ListModel {
                                id: modeloModoAfectaCuentaBancaria
                                ListElement {
                                    descripcionItem: "No afecta CB"
                                    codigoItem: "0"
                                }

                                ListElement {
                                    descripcionItem: "Suma a la CB+"
                                    codigoItem: "1"
                                }

                                ListElement {
                                    descripcionItem: "Resta a la CB-"
                                    codigoItem: "-1"
                                }
                            }
                            textoComboBox: qsTr("No afecta CB")
                            colorRectangulo: "#cac1bd"
                            modeloItems: modeloModoAfectaCuentaBancaria
                            z: 2
                        }
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 30
                        anchors.bottomMargin: 10
                        z: 1000
                        anchors.right: parent.right
                        anchors.leftMargin: 60
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle19
                        x: -3
                        height: 1
                        color: "#ffffff"
                        //
                        anchors.top: chbUtilizaCuentasBancarias.bottom
                        anchors.topMargin: 10
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle20
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        //
                        anchors.top: rectangle19.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }
            }
        }

        Rectangle {
            id: rectangle1
            width: flickable1.visibleArea.widthRatio * flickable1.width+18
            height: 10
            x:flickable1.visibleArea.xPosition * flickable1.width+5
            color: "#000000"
            //
            opacity: 0.500
            radius: 2
            anchors.bottom: flickable1.top
            anchors.bottomMargin: -12
        }



    }

    Flow {
        id: flow8
        x: 30
        y: 101
        height: flow8.implicitHeight
        spacing: 5
        flow: Flow.LeftToRight
        anchors.top: parent.top
        anchors.topMargin: 60
        TextInputSimple {
            id: txtCodigoTipoDocumento
          //  width: 120
            textoInputBox: ""
            botonBuscarTextoVisible: false
            inputMask: "000000;"
            largoMaximo: 6
            botonBorrarTextoVisible: true
            textoTitulo: qsTr("Código:")
            colorDeTitulo: "#333333"
            onEnter: txtDescripcionTipoDocumento.tomarElFoco()
            onTabulacion: txtDescripcionTipoDocumento.tomarElFoco()
        }

        TextInputSimple {
            id: txtDescripcionTipoDocumento
          //  width: 300
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            botonBorrarTextoVisible: true
            largoMaximo: 35
            textoTitulo: qsTr("Nombre tipo documento:")
            colorDeTitulo: "#333333"
            onEnter: txtSerieTipoDocumento.tomarElFoco()
            onTabulacion: txtSerieTipoDocumento.tomarElFoco()
        }

        TextInputSimple {
            id: txtSerieTipoDocumento
            x: -9
            y: -6
         //   width: 100
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            botonBorrarTextoVisible: true
            largoMaximo: 4
            textoTitulo: qsTr("Serie doc.:")
            colorDeTitulo: "#333333"
            onEnter: txtDescripcionImpresionTipoDocumento.tomarElFoco()
            onTabulacion: txtDescripcionImpresionTipoDocumento.tomarElFoco()
        }

        TextInputSimple {
            id: txtDescripcionImpresionTipoDocumento
            x: -2
            y: -5
         //   width: 200
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            largoMaximo: 20
            botonBorrarTextoVisible: true
            textoTitulo: qsTr("Descripción a imprimir:")
            colorDeTitulo: "#333333"
            onEnter: txtCodigoTipoDocumento.tomarElFoco()
            onTabulacion: txtCodigoTipoDocumento.tomarElFoco()
        }
        anchors.rightMargin: 10
        z: 1
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.left: parent.left
    }

}
