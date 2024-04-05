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
    // width: 1524
    height: 59
    color: "#e9e8e9"
    radius: 1
    border.width: 1
    border.color: "#aaaaaa"
    //
    opacity: 1

    property double totalVentas: parseFloat(precioTotalVenta)



    Text {
        id:txtCodigoDocumento
        width: 80
        text:codigoDocumento+"("+serieDocumento+")"
        font.family: "Arial"
        opacity: 0.900
        //
        font.pointSize: 10
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
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
            txtCodigoDocumento.color="white"
            txtTotalDocumento.color="white"
            rectListaItemColorDeseleccionado.stop()
            rectListaItemColorSeleccionado.start()
        }
        onExited: {
            txtCodigoDocumento.color="#212121"
            txtTotalDocumento.color="#000000"
            rectListaItemColorSeleccionado.stop()
            rectListaItemColorDeseleccionado.start()
        }
        onDoubleClicked: {
            mantenimientoFactura.cargoFacturaEnMantenimiento(codigoDocumento,codigoTipoDocumento,serieDocumento)

        }


    }

    Grid {
        id: grid1
        spacing: 40
        flow: Grid.LeftToRight
        rows: 2
        height: grid1.implicitHeight
        columns: 5
        anchors.top: txtCodigoDocumento.bottom
        anchors.topMargin: -1
        anchors.right: parent.right
        anchors.rightMargin: 300
        anchors.left: parent.left
        anchors.leftMargin: 10

        Text {
            id: txtTotalDocumento
            width: 190
            font.bold: false
            //
            opacity: 0.500
            font.pixelSize: 11
            height: txtTotalDocumento.implicitHeight
            text: qsTr("Total "+modeloListaMonedas.retornaSimboloMoneda(codigoMonedaDocumento)+":  "+totalVentas.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
            font.family: "Arial"
            onTextChanged: {


            }
        }

        Text {
            id: txtEstadoDocumento
            height: txtEstadoDocumento.implicitHeight
            text: qsTr("Estado:  "+descripcionEstadoDocumento)
            font.family: "Arial"
            //
            font.pixelSize: 11
            opacity: 0.500
            width: 250
            onTextChanged: {

                if(descripcionEstadoDocumento=="Pendiente"){
                    color="blue"
                    font.bold=true
                }else if(descripcionEstadoDocumento=="Anulado"){
                    color="#d93e3e"
                    font.bold=true

                }else{
                    color="#000000"
                    font.bold=false
                }

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
        id: txtTipoDeDocumentoListado
        height: 16
        color: "#4c6bb5"
        text: descripcionTipoDocumento
        font.family: "Arial"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.right: imgEsDocumentoCFE.left
        anchors.rightMargin: 5
        horizontalAlignment: Text.AlignRight
        font.pointSize: 11
        font.bold: true
        verticalAlignment: Text.AlignVCenter
    }

    Rectangle {
        id: rectLineaSeparacion
        y: 0
        width: 2
        height: 20
        color: "#C4C4C6"
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.leftMargin: 40
        anchors.left: txtCodigoDocumento.right
    }

    Text {
        id: txtSerieDocumento
        x: 1
        y: 9
        width: 80
        color: "#080707"
        text:
        {
            if(cae_numeroCae==""){
                ""
            }else{
                if(cae_serie==""){
                    cae_numeroCae
                }else{
                    cae_numeroCae+"("+cae_serie+")"
                }
            }
        }

        font.family: "Arial"
        horizontalAlignment: Text.AlignHCenter
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        font.bold: false
        font.pointSize: 10
        anchors.leftMargin: 10
        verticalAlignment: Text.AlignVCenter
        anchors.left: rectLineaSeparacion.right
    }

    Rectangle {
        id: rectLineaSeparacion1
        x: 9
        y: 1
        width: 2
        height: 20
        color: "#C4C4C6"
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.leftMargin: 10
        anchors.left: txtSerieDocumento.right
    }

    Text {
        id: txtRazonSocialDocumento
        x: 3
        y: 5
        width: 200
        color: "#212121"
        text: razonSocial
        clip: true
        font.family: "Arial"
        horizontalAlignment: Text.AlignLeft
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        font.bold: false
        font.pointSize: 10
        anchors.leftMargin: 10
        verticalAlignment: Text.AlignVCenter
        anchors.left: rectLineaSeparacion1.right
    }

    Rectangle {
        id: rectLineaSeparacion2
        x: 6
        y: 4
        width: 2
        height: 20
        color: "#C4C4C6"
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.leftMargin: 10
        anchors.left: txtRazonSocialDocumento.right
    }

    Text {
        id: txtNombreClienteDocumento
        x: 0
        y: 5
        width: 180
        color: "#080707"
        text: nombreCliente
        clip: true
        font.family: "Arial"
        horizontalAlignment: Text.AlignLeft
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        font.bold: false
        font.pointSize: 10
        anchors.leftMargin: 10
        verticalAlignment: Text.AlignVCenter
        anchors.left: rectLineaSeparacion2.right
    }

    Image {
        id: imgEsDocumentoCFE
        x: 1480
        asynchronous: true
        width: {
         if(visible){
             25
         }else{
             0
         }
        }
        visible: {
            if(esDocumentoCFE=="1"){
                true
            }else{
                false
            }
        }

        anchors.top: parent.top
        anchors.topMargin: 17
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 17
        anchors.right: imgEsDocumentoWeb.left
        anchors.rightMargin: 5
        //
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/IconCFE.png"
    }

    Image {
        id: imgEsDocumentoWeb
        x: 1480
        asynchronous: true
        width: {
         if(visible){
             25
         }else{
             0
         }
        }
        visible: {
            if(esDocumentoWeb=="1"){
                true
            }else{
                false
            }
        }

        anchors.top: parent.top
        anchors.topMargin: 17
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 17
        anchors.right: parent.right
        anchors.rightMargin: 15
        //
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/ClienteWeb.png"
    }


    Text {
        id: txtComentarios
        text: {
            if(comentarios==""){
                ""
            }else{
                qsTr("Comentario:  "+comentarios)
            }
        }
        anchors.right: txtTipoDeDocumentoListado.left
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10
        clip: true
        anchors.bottom: txtObservaciones.top
        anchors.bottomMargin: 1
        font.pixelSize: 10
        font.family: "Arial"
        opacity: 0.800
        color: "purple"
    }

    Text {
        id: txtObservaciones
        text: {
            if(observaciones==""){
                ""
            }else{
                qsTr("Observación:  "+observaciones)
            }
        }
        anchors.right: txtTipoDeDocumentoListado.left
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10
        clip: true
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        font.pixelSize: 10
        font.family: "Arial"
        opacity: 0.500
    }
}
