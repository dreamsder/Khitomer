/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2021>  <Cristian Montano>

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
import "../Listas"

Rectangle {
    id: rectPrincipalPagoDeFinancieras
    width: 500
    height: 500
    color: "#00000000"
    smooth: true





    function cargarTarjetasACobrar(){

        modeloListaTarjetasCreditoACobrar.clear()
        modeloLineasDePagoTarjetasCredito.limpiarListaLineasDePago()
        modeloLineasDePagoTarjetasCredito.buscarLineasDePagoTarjetasDeCreditoPendientesDePago("1=","1")
        listaDePagosPendientes.currentIndex=0;

        for(var j=0;j<modeloLineasDePagoTarjetasCredito.rowCount();j++){

            modeloListaTarjetasCreditoACobrar.append({
                                                         descripcionMedioDePago: modeloMediosDePago.retornaDescripcionMedioDePago(modeloLineasDePagoTarjetasCredito.retornacodigoMedioPago(j)),
                                                         codigoMedioDePago: modeloLineasDePagoTarjetasCredito.retornacodigoMedioPago(j),
                                                         montoMedioDePago: modeloLineasDePagoTarjetasCredito.retornaimportePago(j),
                                                         monedaMedioPago:modeloLineasDePagoTarjetasCredito.retornamonedaMedioPago(j),
                                                         simboloMonedaMedioDePago: modeloListaMonedas.retornaSimboloMoneda(modeloLineasDePagoTarjetasCredito.retornamonedaMedioPago(j)),
                                                         cantidadCuotas: modeloLineasDePagoTarjetasCredito.retornacuotas(j),
                                                         nombreTarjetaCredito:modeloListaTarjetasCredito.retornaDescripcionTarjetaCredito(modeloLineasDePagoTarjetasCredito.retornacodigoTarjetaCredito(j)),
                                                         codigoTarjetaCredito:modeloLineasDePagoTarjetasCredito.retornacodigoTarjetaCredito(j),
                                                         numeroCheque:"0",
                                                         numeroBanco:modeloLineasDePagoTarjetasCredito.retornacodigoBanco(j),
                                                         fechaCheque:"0",
                                                         tipoCheque:"0",
                                                         codigoDoc:modeloLineasDePagoTarjetasCredito.retornacodigoDocumento(j),
                                                         esDiferido: "0",
                                                         codigoTipoDoc:modeloLineasDePagoTarjetasCredito.retornacodigoTipoDocumento(j),
                                                         numeroLineaDocumento:modeloLineasDePagoTarjetasCredito.retornanumeroLinea(j),
                                                         checkboxActivo:false,
                                                         serieDocumento:modeloLineasDePagoTarjetasCredito.retornaSerieDocumento(j)
                                                     })
        }
    }

    ListModel{
        id:modeloListaTarjetasCreditoACobrar
    }


    Text {
        id: txtTituloMenuOpcion
        x: 560
        color: "#4d5595"
        text: qsTr("mantenimiento de pagos de financieras")
        font.family: "Arial"
        style: Text.Normal
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        anchors.top: parent.top
        anchors.topMargin: -10
        anchors.right: parent.right
        anchors.rightMargin: 40
        smooth: true
        font.pixelSize: 23
    }

    Flow {
        id: flow1
        x: 30
        y: 101
        spacing: 5
        height: flow1.implicitHeight
        z: 1
        flow: Flow.LeftToRight
        anchors.top: parent.top
        anchors.topMargin: 70
        anchors.rightMargin: 10
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.left: parent.left
    }

    Row {
        id: rowBarraDeHerramientas
        x: 30
        y: 55
        height: 30
        smooth: true
        spacing: 15

        BotonBarraDeHerramientas {
            id: botonGuardarPagosDeFinancieras
            x: 61
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            toolTip: "Gurardar pagos recibidos"
            anchors.verticalCenter: parent.verticalCenter
            z: 7
            onClic: {

                var razonClientesCobrados="";
                var seGuardoRegistro=false
                if(listaDePagosPendientes.count!=0){
                    txtMensajeInformacion.visible=true
                    txtMensajeInformacionTimer.stop()
                    txtMensajeInformacionTimer.start()

                    for(var i=0; i<modeloListaTarjetasCreditoACobrar.count;i++){

                        if(modeloListaTarjetasCreditoACobrar.get(i).checkboxActivo){

                            if(!modeloLineasDePagoListaChequesDiferidosComboBox.actualizarLineaDePagoTarjetaCredito(modeloListaTarjetasCreditoACobrar.get(i).codigoDoc, modeloListaTarjetasCreditoACobrar.get(i).codigoTipoDoc,  modeloListaTarjetasCreditoACobrar.get(i).numeroLineaDocumento,modeloListaTarjetasCreditoACobrar.get(i).montoMedioDePago,modeloListaTarjetasCreditoACobrar.get(i).serieDocumento)){
                                txtMensajeInformacion.color="#d93e3e"
                                txtMensajeInformacion.text="ATENCION: Error al actualizar el pago de una tarjeta. Factura número: "+ modeloListaTarjetasCreditoACobrar.get(i).codigoDoc +" - "+modeloListaTipoDocumentosComboBox.retornaDescripcionTipoDocumento(modeloListaTarjetasCreditoACobrar.get(i).codigoTipoDoc)
                                break;
                            }else{
                                if(i==0){
                                    razonClientesCobrados+=modeloLineasDePagoTarjetasCredito.retornaRazonDeCliente(modeloListaTarjetasCreditoACobrar.get(i).codigoDoc,modeloListaTarjetasCreditoACobrar.get(i).codigoTipoDoc,modeloListaTarjetasCreditoACobrar.get(i).serieDocumento)
                                }else{
                                    razonClientesCobrados+=" - "+modeloLineasDePagoTarjetasCredito.retornaRazonDeCliente(modeloListaTarjetasCreditoACobrar.get(i).codigoDoc,modeloListaTarjetasCreditoACobrar.get(i).codigoTipoDoc,modeloListaTarjetasCreditoACobrar.get(i).serieDocumento)
                                }


                                seGuardoRegistro=true
                                txtMensajeInformacion.color="#2f71a0"
                                txtMensajeInformacion.text="Pagos actualizados correctamente"
                            }
                        }
                    }

                    cargarTarjetasACobrar()
                    if(seGuardoRegistro){
                        if(modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarFacturacion")){
                               if(funcionesmysql.mensajeAdvertencia("Se actualizaron tarjetas pendientes de pago.\nDesea hacer el ingreso del comprobante asociado a estas tarjetas?\n\nPresione [ Sí ] para confirmar.")){
                                   mostrarMantenimientos(0,"derecha")
                                   setearTipoDocumentoEnMantenimientoFacturacion("16",razonClientesCobrados)
                               }
                        }
                    }else{
                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text="No existen registros para modificar"
                    }
                }
            }
        }

        BotonBarraDeHerramientas {
            id: botonListarTodasLosPagosDeFinancierasPendientes
            x: 47
            y: 10
            toolTip: "Listar todas los pagos pendientes"
            z: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            anchors.verticalCenter: parent.verticalCenter

            onClic: {
                cargarTarjetasACobrar();
            }
        }

        Text {
            id: txtMensajeInformacion
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            font.family: "Arial"
            smooth: true
            font.pixelSize: 14
            style: Text.Raised
            visible: false
            styleColor: "#ffffff"
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignTop
        }
        anchors.bottom: flow1.top
        anchors.rightMargin: 10
        anchors.bottomMargin: 15
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.left: parent.left
    }

    Rectangle {
        id: rectLineaVerticalMenuGris
        height: 1
        color: "#abb2b1"
        smooth: true
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
        smooth: true
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
        id: rectListaDePagosPendientes
        color: "#C4C4C6"
        radius: 3
        clip: true
        anchors.top: flow1.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        smooth: true
        ListView {
            id: listaDePagosPendientes
            clip: true
            highlightRangeMode: ListView.NoHighlightRange
            anchors.top: parent.top
            boundsBehavior: Flickable.DragAndOvershootBounds
            highlightFollowsCurrentItem: true
            anchors.right: parent.right
            delegate: ListaTarjetasCreditoPorPagar {}
            snapMode: ListView.NoSnap
            anchors.bottomMargin: 25
            spacing: 1
            anchors.bottom: parent.bottom
            flickableDirection: Flickable.VerticalFlick
            anchors.leftMargin: 1
            keyNavigationWraps: true
            anchors.left: parent.left
            interactive: true
            smooth: true
            anchors.topMargin: 25
            anchors.rightMargin: 1
            model: modeloListaTarjetasCreditoACobrar

            Rectangle {
                id: rectangle3
                y: listaDePagosPendientes.visibleArea.yPosition * listaDePagosPendientes.height+5
                width: 10
                color: "#000000"
                height: listaDePagosPendientes.visibleArea.heightRatio * listaDePagosPendientes.height+18
                radius: 2
                anchors.right: listaDePagosPendientes.right
                anchors.rightMargin: 4
                z: 1
                opacity: 0.500
                visible: true
                smooth: true
            }
        }

        Text {
            id: txtTituloListaPagosPendientes
            text: qsTr("Tarjetas: "+listaDePagosPendientes.count)
            font.family: "Arial"
            anchors.top: parent.top
            anchors.topMargin: 5
            font.bold: false
            font.pointSize: 10
            anchors.leftMargin: 5
            anchors.left: parent.left
        }

        BotonBarraDeHerramientas {
            id: botonSubirListaFinal1
            x: 457
            y: 5
            width: 14
            height: 14
            anchors.right: parent.right
            anchors.rightMargin: 3
            anchors.top: parent.top
            anchors.topMargin: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
            toolTip: ""
            rotation: 90
            onClic: listaDePagosPendientes.positionViewAtIndex(0,0)
        }

        BotonBarraDeHerramientas {
            id: botonBajarListaFinal1
            x: 483
            y: 231
            width: 14
            height: 14
            anchors.right: parent.right
            anchors.rightMargin: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
            anchors.bottom: parent.bottom
            toolTip: ""
            anchors.bottomMargin: 5
            rotation: -90

            onClic: listaDePagosPendientes.positionViewAtIndex(listaDePagosPendientes.count-1,0)
        }

        Text {
            id: txtInformacionDobleClic
            x: 454
            text: qsTr("Doble-clic para visualizar facturas.")
            smooth: true
            font.pixelSize: 12
            anchors.top: parent.top
            anchors.topMargin: 5
            visible: tagFacturacion.enabled
            anchors.rightMargin: 30
            font.family: "Arial"
            anchors.right: parent.right
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
        }
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 90
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

    TextEdit {
        id: txtTituloListaMonedas1
        x: -3
        y: 2
        width: 500
        text: "Atención: en este listado usted podra encontrar todas las tarjetas de credito con las que sus facturas fueron pagas, pero aún no fueron recibidos los pagos por parte de las financieras.\nCuando el pago de la financiera este en sus manos, marque la o las tarjetas ya pagas, y precione el boton de guardar."
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        smooth: true
        activeFocusOnPress: false
        wrapMode: TextEdit.WordWrap
        readOnly: true
        font.family: "Arial"
        font.bold: false
        font.pointSize: 10
        anchors.leftMargin: 20
        anchors.left: parent.left
        textFormat: TextEdit.RichText
    }

}
