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
    //width: 1524
    height: 52
    color: "#e9e8e9"
    radius: 1
    border.width: 1
    border.color: "#aaaaaa"
    //
    opacity: 1

    property double precioArticuloListaGenerica : parseFloat(modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(codigoArticulo,"1"))
    property double costoMonedaExtrangeraArticulo : parseFloat(modeloListaPrecioArticulos.retornarCostoEnMonedaExtrangera(codigoArticulo))
    property double costoMonedaReferenciaArticulo : parseFloat(modeloListaPrecioArticulos.retornarCostoMonedaReferenciaDelSistema(codigoArticulo))
    property string simboloCostoMonedaExtrangeraArticulo : modeloListaPrecioArticulos.retornarSimboloMonedaDocumentoArticuloCosto(codigoArticulo)



    Text {
        id:articulos
        text: descripcionArticulo
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
            articulos.color= "white"
            txtCodigoArticuloEnLista.color="white"
            txtNombreProveedorEnLista.color="white"
            txtStockArticuloEnListaPrevisto.color="white"
            txtStockArticuloEnListaReal.color="white"
            txtPrecioArticuloEnListaGenerica.color="white"
            rectListaItemColorDeseleccionado.stop()
            rectListaItemColorSeleccionado.start()
        }
        onExited: {
            articulos.color= "#212121"
            txtCodigoArticuloEnLista.color="#000000"
            txtNombreProveedorEnLista.color="#000000"
            txtStockArticuloEnListaPrevisto.color="#000000"
            txtStockArticuloEnListaReal.color="#000000"
            txtPrecioArticuloEnListaGenerica.color="#000000"


            rectListaItemColorSeleccionado.stop()
            rectListaItemColorDeseleccionado.start()
        }

        onClicked: {

            txtCodigoArticulo.textoInputBox=codigoArticulo
            txtDescripcionArticulo.textoInputBox=descripcionArticulo
            txtDescripcionExtendidaArticulo.textoInputBox=descripcionExtendida
            txtProveedorArticulo.codigoValorSeleccion=codigoProveedor
            txtProveedorArticulo.textoComboBox=modeloListaProveedor.primerRegistroDeProveedorNombreEnBase(txtProveedorArticulo.codigoValorSeleccion.toString())

            txtListaDeIvas.codigoValorSeleccion=codigoIva
            txtListaDeIvas.textoComboBox=modeloListaIvas.retornaDescripcionIva(codigoIva)

            txtMonedaArticulo.codigoValorSeleccion=codigoMoneda
            txtMonedaArticulo.textoComboBox=modeloListaMonedas.retornaDescripcionMoneda(codigoMoneda)
            txtCantidadMinimaStock.textoInputBox=cantidadMinimaStock

            cbxListaSubRubrosArticulos.codigoValorSeleccion=codigoSubRubro
            cbxListaSubRubrosArticulos.textoComboBox=modeloListaSubRubros.retornaDescripcionSubRubro(codigoSubRubro)

            if(activo==0){
                chbArticuloActivo.setActivo(false)
            }else{
                chbArticuloActivo.setActivo(true)
            }

            if(cbListaDePrecioDeArticuloSeleccionado.codigoValorSeleccion.trim()!="")
                txtPrecioArticuloSeleccionado.textoInputBox=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(txtCodigoArticulo.textoInputBox,cbListaDePrecioDeArticuloSeleccionado.codigoValorSeleccion)

            cbxListaTipoGarantias.codigoValorSeleccion=codigoTipoGarantia
            cbxListaTipoGarantias.textoComboBox=modeloTipoGarantia.retornaDescripcionTipoGarantia(codigoTipoGarantia)

            txtCodigoDeBarras.enabled=true
            listaDeArticulosBarrar.enabled=true
            modeloArticulosCodigoDeBarras.clear()
            modeloArticulosBarra.clearArticulosBarra()
            modeloArticulosBarra.buscarArticuloBarra(codigoArticulo)

            var totalmodeloArticulosBarra=modeloArticulosBarra.rowCount()

            for(var i=0; i<totalmodeloArticulosBarra;i++){

                modeloArticulosCodigoDeBarras.append({
                                                         itemCodigoDeBarrasAgregado:modeloArticulosBarra.retornarCodigoBarras(i,codigoArticulo)
                                                     })
            }

            txtDescripcionArticulo.tomarElFoco()


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
        anchors.top: articulos.bottom
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 200
        anchors.left: parent.left
        anchors.leftMargin: 30

        Text {
            id: txtCodigoArticuloEnLista
            x: 1
            y: -15
            width: 210
            text: qsTr("Codigo:  "+codigoArticulo)
            font.family: "Arial"
            //
            opacity: 0.500
            font.pixelSize: 11
            height: txtCodigoArticuloEnLista.implicitHeight
        }

        Text {
            id: txtNombreProveedorEnLista
            y: 3
            height: txtNombreProveedorEnLista.implicitHeight
            text: qsTr("Proveedor:  "+modeloListaProveedor.primerRegistroDeProveedorNombreEnBase(codigoProveedor)+" ("+codigoProveedor+")")
            font.family: "Arial"
            //
            font.pixelSize: 11
            opacity: 0.500
            width: 270
        }

        Text {
            id: txtStockArticuloEnListaPrevisto
            y: -16
            width: 210
            height: txtStockArticuloEnListaPrevisto.implicitHeight
            //text: qsTr("Stock previsto:  "+modeloArticulos.retornaStockTotalArticulo(codigoArticulo))
            text: "Stock previsto:  "+stockPrevisto
            font.family: "Arial"
            //
            font.pixelSize: 11
            opacity: 0.500
        }

        Text {
            id: txtStockArticuloEnListaReal
            x: -7
            y: -16
            width: 210
            height: txtStockArticuloEnListaReal.implicitHeight
            //text: qsTr("Stock real:  "+modeloArticulos.retornaStockTotalArticuloReal(codigoArticulo))
            text:  "Stock real:  "+stockReal
            font.family: "Arial"
            //
            font.pixelSize: 11
            opacity: 0.500
        }

        Text {
            id: txtPrecioArticuloEnListaGenerica            
            width: 210
            height: txtPrecioArticuloEnListaGenerica.implicitHeight
            text: qsTr("Precio generico:  "+modeloListaMonedas.retornaSimboloMoneda(modeloListaMonedas.retornaCodigoMoneda(codigoArticulo))+"   " +precioArticuloListaGenerica.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))   )
            font.family: "Arial"
            //
            font.pixelSize: 11
            opacity: 0.500
        }

        Text {
            id: txtCostoEnMonedaExtrangera
            width: 210
            height: txtCostoEnMonedaExtrangera.implicitHeight
            text: qsTr("Costo en origen:  "+simboloCostoMonedaExtrangeraArticulo+"   "+costoMonedaExtrangeraArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
            font.family: "Arial"
            //
            font.pixelSize: 11
            opacity: 0.500
            visible: {
                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteVerCostosDeArticulos")){
                    true
                }else{
                    false
                }
            }

            color: txtCodigoArticuloEnLista.color
        }
        Text {
            id: txtCostoEnMonedaReferencia
            width: 210
            height: txtCostoEnMonedaReferencia.implicitHeight
            text: qsTr("Costo en moneda referencia:  "+modeloListaMonedas.retornaSimboloMoneda(modeloListaMonedas.retornaMonedaReferenciaSistema())+"   " +costoMonedaReferenciaArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
            font.family: "Arial"
            visible: txtCostoEnMonedaExtrangera.visible
            font.pixelSize: 11
            opacity: 0.500
            color: txtCodigoArticuloEnLista.color
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
}
