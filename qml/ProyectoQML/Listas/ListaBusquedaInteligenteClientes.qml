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
import "../Listas/Delegates"

Rectangle{
    id: rectListaItem
    width: parent.width
    // width: 800
    height: {
        if(txtArticulo.visible){
            70
        }else{
            35
        }

    }
    color: "#e9e8e9"
    radius: 1
    clip: false
    border.width: 1
    border.color: "#bebbbb"
    //
    opacity: 1



    function calculoPrecioArticulo(){

        if(txtArticulo.textoInputBox.trim()!=""){
            if(tipoItem=="CLIENTE"){
                var articulosseleccionado= modeloArticulos.existeArticulo(txtArticulo.textoInputBox.trim())
                if(articulosseleccionado!=""){
                    txtArticulo.textoInputBox=articulosseleccionado

                    var precioArticuloSelecionado=0.00
                    var listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(funcionesmysql.fechaDeHoy(),codigoItem,1)

                    if(listaPrecioSeleccionada!=""){
                        precioArticuloSelecionado=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(articulosseleccionado,listaPrecioSeleccionada)
                        text1.text=modeloArticulos.retornaDescripcionArticulo(articulosseleccionado)+" "+modeloMonedas.retornaSimboloMoneda(modeloMonedas.retornaCodigoMoneda(articulosseleccionado))+" "+precioArticuloSelecionado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                        txtArticulo.tomarElFocoP()
                    }else{
                        precioArticuloSelecionado=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(articulosseleccionado,1)
                        text1.text=modeloArticulos.retornaDescripcionArticulo(articulosseleccionado)+" "+modeloMonedas.retornaSimboloMoneda(modeloMonedas.retornaCodigoMoneda(articulosseleccionado))+" "+precioArticuloSelecionado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                        txtArticulo.tomarElFocoP()
                    }
                }else{
                    txtArticulo.tomarElFocoP()
                }
            }
        }
        txtArticulo.tomarElFocoP()



    }

    Rectangle {
        id: rectangle1
        height: 19
        color: "#e9e8e9"
        clip: false
        //
        anchors.right: parent.right
        anchors.rightMargin: 1
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.left: parent.left
        anchors.leftMargin: 1

        Text {
            id:txtDescripcionItem
            x: 17
            y: -3
            width: 80
            font.family: "Arial"
            opacity: 0.900
            //
            font.pointSize: 10
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 0
            color: "#2d2c2c"
            text: modeloClientes.retornaDescripcionDeCliente(codigoItem,1)+" ("+codigoItem+")"
            styleColor: "#41638f"
            style: Text.Raised

            onTextChanged: {
                modeloListasPreciosBusquedaInteligente.clearListasPrecio()
                txtArticulo.visible=true
                text1.visible=true

            }
        }

        Text {
            id: txtInfoExtendida
            x: 8
            y: -9
            width: 80
            color: "#2d2c2c"
            text: "Cantidad de ventas: "+ modeloDocumentos.retornoCantidadDocumentosPorCliente(codigoItem,1,"EMITIDOS")
            horizontalAlignment: Text.AlignRight
            anchors.right: parent.right
            anchors.rightMargin: 30
            //
            anchors.top: parent.top
            anchors.topMargin: 0
            style: Text.Normal
            styleColor: "#41638f"
            font.family: "Arial"
            font.pointSize: 10
            opacity: 0.900
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: txtInfoExtendida2
            x: 0
            y: -13
            width: 80
            color: "#2d2c2c"
            text: "Cantidad de anulaciones: "+ modeloDocumentos.retornoCantidadDocumentosPorCliente(codigoItem,1,"ANULADOS")
            font.bold: false
            anchors.top: txtInfoExtendida.bottom
            anchors.right: parent.right
            styleColor: "#41638f"
            font.pointSize: 10
            verticalAlignment: Text.AlignVCenter
            font.family: "Arial"
            horizontalAlignment: Text.AlignRight
            style: Text.Normal
            opacity: 0.900
            //
            anchors.topMargin: 1
            anchors.rightMargin: 30
        }
    }
    TextInputP {
        id: txtArticulo
        width: 270
        tamanioRectPrincipalComboboxAlto: 230
        visible: false
        colorDeTitulo: "#333333"
        largoMaximo: 30
        textoTitulo: "Ingrese artículo para obtener su precio:"
        enFocoSeleccionarTodo: true
        anchors.top: rectangle1.bottom
        anchors.topMargin: 1
        z: 3
        anchors.left: parent.left
        anchors.leftMargin: 20
        textoDeFondo: ""
        textoInputBox: ""
        botonBuscarTextoVisible: false

        botonNuevoTexto: "Nuevo artículo..."
        utilizaListaDesplegable: true
        tamanioRectPrincipalCombobox: 320

        botonNuevoVisible:{
            if(modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarArticulos") && modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteCrearArticulos")){
                true
            }else{
                false
            }
        }

        checkBoxActivoVisible: true
        checkBoxActivoTexto: "Incluir artículos inactivos"
        textoTituloFiltro: "Buscar por: descripción, proveedor, iva o moneda"
        listviewModel:modeloArticulosFiltrosBusquedaInteligente
        listviewDelegate: Delegate_ListaArticulosFiltros{
            onSenialAlAceptarOClick: {
                txtArticulo.textoInputBox=codigoValorSeleccion
                txtArticulo.cerrarComboBox()
                txtArticulo.tomarElFocoP()
                calculoPrecioArticulo()

            }
            onKeyEscapeCerrar: {
                txtArticulo.tomarElFocoP()
                txtArticulo.cerrarComboBox()
            }
        }
        onClicBotonNuevoItem: {
            mostrarMantenimientos(2,"derecha")
        }


        onClicEnBusquedaFiltro: {
            var consultaSqlArticulo="";
            if(!checkBoxActivoEstado){
                consultaSqlArticulo="  ((Clientes.razonSocial rlike '"+textoAFiltrar+"'  or Clientes.nombreCliente rlike '"+textoAFiltrar+"')  or codigoIva=(SELECT codigoIva FROM Ivas where descripcionIva rlike '"+textoAFiltrar+"' limit 1)  or codigoMoneda=(SELECT codigoMoneda FROM Monedas where descripcionMoneda rlike '"+textoAFiltrar+"' limit 1) or descripcionExtendida rlike '"+textoAFiltrar+"' or descripcionArticulo rlike'"+textoAFiltrar+"') and Articulos.activo=";
            }else{
                consultaSqlArticulo="  ((Clientes.razonSocial rlike '"+textoAFiltrar+"'  or Clientes.nombreCliente rlike '"+textoAFiltrar+"')  or codigoIva=(SELECT codigoIva FROM Ivas where descripcionIva rlike '"+textoAFiltrar+"' limit 1)  or codigoMoneda=(SELECT codigoMoneda FROM Monedas where descripcionMoneda rlike '"+textoAFiltrar+"' limit 1) or descripcionExtendida rlike '"+textoAFiltrar+"' or descripcionArticulo rlike'"+textoAFiltrar+"') and Articulos.activo=0 or Articulos.activo=";
            }

            modeloArticulosFiltrosBusquedaInteligente.clearArticulos()
            modeloArticulosFiltrosBusquedaInteligente.buscarArticulo(consultaSqlArticulo,"1",0)

            if(modeloArticulosFiltrosBusquedaInteligente.rowCount()!=0){
                tomarElFocoResultado()
            }

        }

        onEnter: {
            calculoPrecioArticulo()
        }
        onAbrirComboBox: {
            rectListaItem.height=302
        }
        onCierreComboBox: {
            if(txtArticulo.visible){
                rectListaItem.height=70
            }else{
                rectListaItem.height=35
            }
        }

    }
    Text {
        id: text1
        y: 62
        width: 200
        color: "#333333"
        text: qsTr("$ 0"+modeloconfiguracion.retornaCantidadDecimalesString()+"")
        anchors.verticalCenterOffset: 6
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        anchors.left: txtArticulo.right
        anchors.leftMargin: 10
        anchors.verticalCenter: txtArticulo.verticalCenter
        //
        font.family: "Arial"
        visible: false
        font.pixelSize: 12
    }
}
