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
import "../Controles"

Rectangle{
    id: rectListaItem
    width: parent.width
    //  width: 1024
    height: 32
    color: "#e9e8e9"
    radius: 1
    border.color: "#aaaaaa"
    opacity: 1


    Text {
        id:txtItem
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        //
        font.pointSize: 10
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: txtItem2.left
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        color: "#212121"
        text: codigoCliente +" - "+ nombreCliente + " - "+ modeloTipoClientes.primerRegistroDeTipoClienteEnBase(tipoCliente)
        font.family: "Arial"
        opacity: 0.600
    }


    MouseArea{
        id: mousearea1
        anchors.rightMargin: 0
        z: 1
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            rectListaItemColorDeseleccionado.stop()
            rectListaItemColorSeleccionado.start()
        }
        onExited: {
            rectListaItemColorSeleccionado.stop()
            rectListaItemColorDeseleccionado.start()

        }
        onClicked: {

            if(txtCodigoClienteFacturacion.visible){

                var datosDeCliente=modeloClientes.retornaDescripcionDeCliente(codigoCliente,tipoCliente);
                if(datosDeCliente!=""){
                    lblRazonSocialCliente.text=""
                    lblRazonSocialCliente.text="Facturar a: "+datosDeCliente
                    cargarDocumentosConDeuda()

                    txtTipoClienteFacturacion.codigoValorSeleccion=tipoCliente
                    txtTipoClienteFacturacion.textoComboBox=modeloTipoClientes.primerRegistroDeTipoClienteEnBase(tipoCliente)
                    txtTipoClienteFacturacion.activo(false)

                    txtCodigoClienteFacturacion.textoInputBox=codigoCliente


                    if(modeloconfiguracion.retornaValorConfiguracion("UTILIZA_CONTROL_CLIENTE_CREDITO")=="1"){
                        if(txtCodigoClienteFacturacion.textoInputBox.trim()!="" && lblRazonSocialCliente.text.trim()!=""){
                            if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"afectaCuentaCorriente")!="0"){
                                if(modeloClientes.retornaSiPermiteFacturaCredito(txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion)==false){

                                    setearEstadoActivoBotonesGuardar(false)
                                    funcionesmysql.mensajeAdvertenciaOk("El cliente no esta habilitado para documentos CRÉDITO.\n\n No se podrá emitir el documento ni guardarlo.")

                                }else{
                                    setearEstadoActivoBotonesGuardar(true)
                                }
                            }
                        }
                    }



                }
                txtCodigoClienteFacturacionOpcionesExtras.tomarElFoco()


            }

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

    Text {
        id: txtItem2
        width: txtItem2.implicitWidth
        color: "#212121"
        text:  modeloTipoClientes.primerRegistroDeTipoClienteEnBase(tipoCliente)
        font.family: "Arial"
        horizontalAlignment: Text.AlignRight
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        anchors.bottomMargin: 0
        font.bold: false
        font.pointSize: 10
        anchors.right: parent.right
        verticalAlignment: Text.AlignVCenter
    }
}
