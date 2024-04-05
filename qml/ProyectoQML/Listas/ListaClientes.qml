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

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import "../Controles"

Rectangle{
    id: rectListaItem
    width: parent.width
  //  width: 1300
    height: 52
    color: "#e9e8e9"
    radius: 1
    border.color: "#aaaaaa"
    //
    opacity: 1

    property string  tipoDeCliente: ""

    Text {
        id:clientes
        text: razonSocial + "  ("+nombreCliente+")"
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

    MouseArea{
        id: mousearea1
        z: 1
        anchors.fill: parent
        hoverEnabled: true



        onEntered: {
            clientes.color="white"
            txtCodigoClienteEnLista.color="white"
            txtRutEnLista.color="white"
            txtTelefonoEnLista.color="white"
            txtDireccionEnLista.color="white"
            txtTipoClienteEnLista.color="white"
            rectListaItemColorDeseleccionado.stop()
            rectListaItemColorSeleccionado.start()
        }
        onExited: {
            clientes.color="#212121"
            txtCodigoClienteEnLista.color="#000000"
            txtRutEnLista.color="#000000"
            txtTelefonoEnLista.color="#000000"
            txtDireccionEnLista.color="#000000"
            txtTipoClienteEnLista.color="#000000"

            rectListaItemColorSeleccionado.stop()
            rectListaItemColorDeseleccionado.start()

        }

        onClicked: {

            txtCodigoCliente.textoInputBox=codigoCliente
            txtCodigoPostal.textoInputBox=codigoPostal
            txtDireccion.textoInputBox=direccion
            txtEmail.textoInputBox=email
            txtEsquina.textoInputBox=esquina
            txtNombre.textoInputBox=nombreCliente
            txtNumeroPuerta.textoInputBox=numeroPuerta
            txtObservaciones.textoInputBox=observaciones
            txtRazonSocial.textoInputBox=razonSocial
            txtRut.textoInputBox=rut
            txtSitioWeb.textoInputBox=sitioWeb
            txtTelefono.textoInputBox=telefono
            txtTelefono2.textoInputBox=telefono2
            txtTipoCliente.textoComboBox=descripcionTipoCliente
            txtTipoCliente.codigoValorSeleccion=codigoTipoCliente

            txtTipoDocumentoCliente.codigoValorSeleccion=codigoTipoDocumentoCliente
            txtTipoDocumentoCliente.textoComboBox= modeloTipoDocumentoClientes.retornaDescripcionTipoDocumentoCliente(codigoTipoDocumentoCliente)


            txtTipoProcedenciaCliente.codigoValorSeleccion=codigoTipoProcedenciaCliente
            txtTipoProcedenciaCliente.textoComboBox= modeloTipoProcedenciaCliente.retornaDescripcionTipoProcedenciaCliente(codigoTipoProcedenciaCliente)


            cbListaMonedaCliente.codigoValorSeleccion=codigoMonedaDefault
            cbListaMonedaCliente.textoComboBox=modeloMonedas.retornaDescripcionMoneda(codigoMonedaDefault)
            cbListaFormasDePagoCliente.codigoValorSeleccion=codigoFormasDePagoDefault
            cbListaFormasDePagoCliente.textoComboBox=modeloFormasDePago.retornaDescripcionFormaDePago(codigoFormasDePagoDefault)

            cbListaDocumentosCliente.codigoValorSeleccion=codigoTipoDocumentoDefault
            cbListaDocumentosCliente.textoComboBox=modeloListaTipoDocumentosComboBox.retornaDescripcionTipoDocumento(codigoTipoDocumentoDefault)

            txtTipoValoracion.textoComboBox=descripcionTipoClasificacion
            txtTipoValoracion.codigoValorSeleccion=codigoTipoClasificacion
            txtCodigoCliente.enabled=false
            txtTipoCliente.enabled=false
            txtContacto.textoInputBox=contacto
            txtHorario.textoInputBox=horario
            cbxListaLocalidades.codigoDePaisSeleccionado=codigoPais
            cbxListaLocalidades.codigoDeDepartamentoSeleccionado=codigoDepartamento
            cbxListaLocalidades.codigoDeLocalidadSeleccionado=codigoLocalidad
            cbxListaLocalidades.codigoValorSeleccion=codigoLocalidad
            cbxListaLocalidades.textoComboBox=modeloLocalidadesComboBox.retornaDescripcionLocalidad(codigoPais,codigoDepartamento,codigoLocalidad)
            txtDescuentoCliente.textoInputBox=porcentajeDescuento

            txtFechaNacimiento.textoInputBox=fechaNacimiento

            if(permiteFacturaCredito=="1"){
                chbEsClienteCredito.setActivo(true)
            }else{
                chbEsClienteCredito.setActivo(false)
            }




            txtRut.tomarElFoco()

            mantenimientoClientes.cargarListasDePrecioCliente(codigoCliente,codigoTipoCliente)

        }
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
        id: grid1
        spacing: 2
        flow: Grid.TopToBottom
        rows: 2
        columns: 5
        anchors.top: clientes.bottom
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 200
        anchors.left: parent.left
        anchors.leftMargin: 30

        Text {
            id: txtCodigoClienteEnLista
            x: 1
            y: -15
            width: 210
            text: qsTr("Codigo:  "+codigoCliente)
            font.family: "Arial"
            //
            opacity: 0.500
            font.pixelSize: 11
            height: txtCodigoClienteEnLista.implicitHeight
        }

        Text {
            id: txtRutEnLista
            x: 1
            y: 0
            width: 210
            text: qsTr(modeloTipoDocumentoClientes.retornaDescripcionTipoDocumentoCliente(codigoTipoDocumentoCliente)+": "+rut)
            font.family: "Arial"
            //
            font.pixelSize: 11
            opacity: 0.500
            height: txtRutEnLista.implicitHeight
        }

        Text {
            id: txtTelefonoEnLista
            x: -4
            y: -5
            height: txtTelefonoEnLista.implicitHeight
            width: 250
            text: qsTr("Telefono:  "+telefono)
            font.family: "Arial"
            //
            font.pixelSize: 11

            opacity: 0.500

        }

        Text {
            id: txtDireccionEnLista
            x: -11
            y: 2
            width: 210
            height: txtDireccionEnLista.implicitHeight
            text: qsTr("Dirección:  "+direccion + " " +numeroPuerta + " - "+esquina)
            font.family: "Arial"
            //
            font.pixelSize: 11
            opacity: 0.500
        }

        Text {
            id: txtTipoClienteEnLista
            x: -19
            y: 6
            width: 210
            height: txtTipoClienteEnLista.implicitHeight

            text: qsTr("Tipo:  "+descripcionTipoCliente)
            font.family: "Arial"
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

    Image {
        id: image1
        x: 1242
        width: 42
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        asynchronous: true
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 30
        //
        visible: modeloClientes.retornaSiEsClienteWeb(codigoCliente,codigoTipoCliente)
        z: 2
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/ClienteWeb.png"
    }
}
