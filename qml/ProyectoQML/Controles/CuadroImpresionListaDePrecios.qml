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
import QtQuick 1.1
import "../Listas"
import "../Listas/Delegates"

Rectangle {

    id: rectImpresionListasDePrecioPrincipal
    color: "#be231919"
    visible: true
    anchors.fill: parent
    //
    z: 8



    signal clicCancelar

    signal clicImprimir


    property alias codigoArticuloDesdeHastaInputMask: txtDesdeCodigoArticuloCuadroListaPrecio.inputMask

    property string nombreImpresora: ""

    property string stringFiltroDeArticulosParaMostrar: ""

    property int  tamanioDefuente: 9

    MouseArea {
        id: mouse_area2
        anchors.fill: parent
        hoverEnabled: true

        Rectangle {
            id: rectImpresionListaPrecios
            width: 500
            height: 300
            color: "#1e7597"
            radius: 5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            BotonFlecha {
                id: botonflechaCerrarVentana
                x: 410
                y: 20
                opacidadRectPrincipal: 0.800
                anchors.top: parent.top
                anchors.topMargin: -15
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/CerrarLista.png"
                anchors.rightMargin: -15
                z: 1
                anchors.right: parent.right
                onClic: {

                    clicCancelar()

                }
            }

            Text {
                id: lblTituloImpresionListaPrecios
                color: "#ffffff"
                text: qsTr("Impresión de lista de precio")
                style: Text.Raised
                font.underline: true
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: true
                font.family: "Verdana"
                anchors.top: parent.top
                anchors.topMargin: 20
                font.pixelSize: sizeTitulosControles
            }


            Text {
                id: lblInformacionImpresionListaPrecio
                y: 7
                color: "#ffffff"
                text: qsTr("Desde aquí podras imprimir la lista de precios seleccionada en formato simple, o formato duplex(en ambas caras de la hoja).")
                style: Text.Normal
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                anchors.left: parent.left
                anchors.leftMargin: 35
                anchors.right: parent.right
                anchors.rightMargin: 15
                font.underline: false
                anchors.top: lblTituloImpresionListaPrecios.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: sizeTitulosControles
                font.family: "Verdana"
                font.bold: false
                anchors.topMargin: 5
            }

            TextInputP {
                id: txtDesdeCodigoArticuloCuadroListaPrecio
                z: 2
                anchors.top: lblInformacionImpresionListaPrecio.bottom
                anchors.topMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 35
                visible: true
                enable: !chbImprimirTodosLosArticulos.chekActivo
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                botonBuscarTextoVisible: false
                textoDeFondo: ""
                largoMaximo: 30
                botonBorrarTextoVisible: true
                textoTitulo: "Desde código artículo:"
                tamanioRectPrincipalCombobox: 320
                botonNuevoTexto: "Nuevo artículo..."
                utilizaListaDesplegable: true
                checkBoxActivoVisible: true
                checkBoxActivoTexto: "Incluir artículos inactivos"
                textoTituloFiltro: "Buscar por: descripción, proveedor, iva o moneda"
                onEnter: txtHastaCodigoArticuloCuadroListaPrecio.tomarElFocoP()
                onTabulacion: txtHastaCodigoArticuloCuadroListaPrecio.tomarElFocoP()
                tamanioRectPrincipalComboboxAlto: {
                    if(checkBoxActivoVisible){
                        400
                    }else{
                        300
                    }
                }
                botonNuevoVisible:{
                    if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos") && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearArticulos")){
                        true
                    }else{
                        false
                    }
                }
                listviewModel:modeloArticulosFiltros
                listviewDelegate: Delegate_ListaArticulosFiltros{
                    permiteOperarConArticulosInactivos: true
                    onSenialAlAceptarOClick: {
                        txtDesdeCodigoArticuloCuadroListaPrecio.textoInputBox=codigoValorSeleccion
                        txtDesdeCodigoArticuloCuadroListaPrecio.tomarElFocoP()
                        txtDesdeCodigoArticuloCuadroListaPrecio.cerrarComboBox()
                    }
                    onKeyEscapeCerrar: {
                        txtDesdeCodigoArticuloCuadroListaPrecio.tomarElFocoP()
                        txtDesdeCodigoArticuloCuadroListaPrecio.cerrarComboBox()
                    }
                }
                onClicBotonNuevoItem: {
                    mostrarMantenimientos(2,"derecha")
                }
                onClicEnBusquedaFiltro: {

                    var consultaSqlArticulo="";
                    if(!checkBoxActivoEstado){
                        consultaSqlArticulo="  ((CLI.razonSocial rlike '"+textoAFiltrar+"'  or CLI.nombreCliente rlike '"+textoAFiltrar+"')  or AR.codigoIva=(SELECT I.codigoIva FROM Ivas I  where I.descripcionIva rlike '"+textoAFiltrar+"' limit 1)  or AR.codigoMoneda=(SELECT M.codigoMoneda FROM Monedas M where M.descripcionMoneda rlike '"+textoAFiltrar+"' limit 1) or AR.descripcionExtendida rlike '"+textoAFiltrar+"' or AR.descripcionArticulo rlike'"+textoAFiltrar+"') and AR.activo=";
                    }else{
                        consultaSqlArticulo="  ((CLI.razonSocial rlike '"+textoAFiltrar+"'  or CLI.nombreCliente rlike '"+textoAFiltrar+"')  or AR.codigoIva=(SELECT I.codigoIva FROM Ivas I where I.descripcionIva rlike '"+textoAFiltrar+"' limit 1)  or AR.codigoMoneda=(SELECT M.codigoMoneda FROM Monedas M where M.descripcionMoneda rlike '"+textoAFiltrar+"' limit 1) or AR.descripcionExtendida rlike '"+textoAFiltrar+"' or AR.descripcionArticulo rlike'"+textoAFiltrar+"') and AR.activo=0 or AR.activo=";
                    }

                    modeloArticulosFiltros.clearArticulos()
                    modeloArticulosFiltros.buscarArticulo(consultaSqlArticulo,"1",0)

                    if(modeloArticulosFiltros.rowCount()!=0){
                        tomarElFocoResultado()
                    }
                }
            }



            TextInputP {
                id: txtHastaCodigoArticuloCuadroListaPrecio
                z: 1
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 35
                anchors.top: txtDesdeCodigoArticuloCuadroListaPrecio.bottom
                anchors.topMargin: 10
                visible: true
                enable: !chbImprimirTodosLosArticulos.chekActivo
                inputMask: txtDesdeCodigoArticuloCuadroListaPrecio.inputMask
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                botonBuscarTextoVisible: false
                textoDeFondo: ""
                largoMaximo: 30
                botonBorrarTextoVisible: true
                textoTitulo: "Hasta código artículo:"
                tamanioRectPrincipalCombobox: 320
                botonNuevoTexto: "Nuevo artículo..."
                utilizaListaDesplegable: true
                checkBoxActivoVisible: true
                checkBoxActivoTexto: "Incluir artículos inactivos"
                textoTituloFiltro: "Buscar por: descripción, proveedor, iva o moneda"
                onEnter: txtDesdeCodigoArticuloCuadroListaPrecio.tomarElFocoP()
                onTabulacion: txtDesdeCodigoArticuloCuadroListaPrecio.tomarElFocoP()
                tamanioRectPrincipalComboboxAlto: {
                    if(checkBoxActivoVisible){
                        400
                    }else{
                        300
                    }
                }
                botonNuevoVisible:{
                    if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos") && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearArticulos")){
                        true
                    }else{
                        false
                    }
                }
                listviewModel:modeloArticulosFiltros
                listviewDelegate: Delegate_ListaArticulosFiltros{
                    permiteOperarConArticulosInactivos: true
                    onSenialAlAceptarOClick: {
                        txtHastaCodigoArticuloCuadroListaPrecio.textoInputBox=codigoValorSeleccion
                        txtHastaCodigoArticuloCuadroListaPrecio.tomarElFocoP()
                        txtHastaCodigoArticuloCuadroListaPrecio.cerrarComboBox()
                    }
                    onKeyEscapeCerrar: {
                        txtHastaCodigoArticuloCuadroListaPrecio.tomarElFocoP()
                        txtHastaCodigoArticuloCuadroListaPrecio.cerrarComboBox()
                    }
                }
                onClicBotonNuevoItem: {
                    mostrarMantenimientos(2,"derecha")
                }
                onClicEnBusquedaFiltro: {

                    var consultaSqlArticulo="";
                    if(!checkBoxActivoEstado){
                        consultaSqlArticulo="  ((CLI.razonSocial rlike '"+textoAFiltrar+"'  or CLI.nombreCliente rlike '"+textoAFiltrar+"')  or AR.codigoIva=(SELECT I.codigoIva FROM Ivas I where I.descripcionIva rlike '"+textoAFiltrar+"' limit 1)  or AR.codigoMoneda=(SELECT M.codigoMoneda FROM Monedas M where M.descripcionMoneda rlike '"+textoAFiltrar+"' limit 1) or AR.descripcionExtendida rlike '"+textoAFiltrar+"' or AR.descripcionArticulo rlike'"+textoAFiltrar+"') and AR.activo=";
                    }else{
                        consultaSqlArticulo="  ((CLI.razonSocial rlike '"+textoAFiltrar+"'  or CLI.nombreCliente rlike '"+textoAFiltrar+"')  or AR.codigoIva=(SELECT I.codigoIva FROM Ivas I where I.descripcionIva rlike '"+textoAFiltrar+"' limit 1)  or AR.codigoMoneda=(SELECT M.codigoMoneda FROM Monedas M where M.descripcionMoneda rlike '"+textoAFiltrar+"' limit 1) or AR.descripcionExtendida rlike '"+textoAFiltrar+"' or AR.descripcionArticulo rlike'"+textoAFiltrar+"') and AR.activo=0 or AR.activo=";
                    }

                    modeloArticulosFiltros.clearArticulos()
                    modeloArticulosFiltros.buscarArticulo(consultaSqlArticulo,"1",0)

                    if(modeloArticulosFiltros.rowCount()!=0){
                        tomarElFocoResultado()
                    }
                }
            }



            BotonPaletaSistema {
                id: btnCancelarOperacion
                text: "Cancelar"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.right: btnImprimir.left
                anchors.rightMargin: 10
                border.color: "#787777"
                colorTextoMensajeError: "White"

                onClicked: clicCancelar()
            }

            BotonPaletaSistema {
                id: btnImprimir
                x: 6
                y: 9
                text: "Imprimir"
                anchors.right: parent.right
                anchors.rightMargin: 25
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                border.color: "#787777"
                colorTextoMensajeError: "White"

                onClicked: {
                    var impresionOk=false;

                    if(!chbImprimirTodosLosArticulos.chekActivo){

                        if(txtDesdeCodigoArticuloCuadroListaPrecio.textoInputBox.trim()!="" && txtHastaCodigoArticuloCuadroListaPrecio.textoInputBox.trim()!=""){

                            if(txtDesdeCodigoArticuloCuadroListaPrecio.inputMask!=""){
                                stringFiltroDeArticulosParaMostrar="   and   cast(LPA.codigoArticulo as SIGNED)   between '"+txtDesdeCodigoArticuloCuadroListaPrecio.textoInputBox.trim()+"' and '"+txtHastaCodigoArticuloCuadroListaPrecio.textoInputBox.trim()+"'    "
                            }else{
                                stringFiltroDeArticulosParaMostrar="   and   LPA.codigoArticulo   between '"+txtDesdeCodigoArticuloCuadroListaPrecio.textoInputBox.trim()+"' and '"+txtHastaCodigoArticuloCuadroListaPrecio.textoInputBox.trim()+"'    "
                            }
                            impresionOk=true;
                        }else{                            
                            mensajeError("Falta información de artículos.")
                        }

                    }else{
                        stringFiltroDeArticulosParaMostrar=""
                        impresionOk=true;
                    }

                    if(txtTamanioFuenteListaPrecio.textoInputBox.trim()!=""){

                        if(parseInt(txtTamanioFuenteListaPrecio.textoInputBox.trim())!=0){
                            impresionOk=true;
                        }else{
                            impresionOk=false;
                            mensajeError("Tamaño de fuente invalido.")
                        }
                    }else{
                        impresionOk=false;
                        mensajeError("No hay tamaño de letra definido.")
                    }


                    if(impresionOk==true){
                        if(cbxListaImpresoras.textoComboBox.trim()!=""){
                            nombreImpresora=cbxListaImpresoras.textoComboBox.trim()
                            tamanioDefuente=parseInt(txtTamanioFuenteListaPrecio.textoInputBox.trim())
                            clicImprimir()
                        }else{
                            mensajeError("No hay impresora seleccionada.")
                        }
                    }
                }
            }

            ComboBoxListaImpresoras {
                id: cbxListaImpresoras
                y: 142
                textoTitulo: "Impresoras:"
                anchors.right: btnCancelarOperacion.left
                anchors.rightMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 16
                anchors.left: parent.left
                anchors.leftMargin: 35
                textoComboBox: funcionesmysql.impresoraPorDefecto()
            }

            CheckBox {
                id: chbImprimirTodosLosArticulos
                chekActivo: false
                textoValor: "Incluir todos los artículos de la lista"
                anchors.top: txtHastaCodigoArticuloCuadroListaPrecio.bottom
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 35
                colorTexto: "White"
                onChekActivoChanged: {
                    if(!chekActivo){
                        stringFiltroDeArticulosParaMostrar=""
                        txtDesdeCodigoArticuloCuadroListaPrecio.cerrarComboBox()
                        txtHastaCodigoArticuloCuadroListaPrecio.cerrarComboBox()
                        txtDesdeCodigoArticuloCuadroListaPrecio.tomarElFocoP()
                    }
                }
            }

            TextInputSimple {
                id: txtTamanioFuenteListaPrecio
                inputMask: "00;"
                largoMaximo: 2
                cursor_Visible: false
                botonBuscarTextoVisible: false
                botonBorrarTextoVisible: false
                enFocoSeleccionarTodo: true
                textoTitulo: "Tamaño de letra:"
                textoInputBox: "9"
                textoDeFondo: "font size"
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.top: txtHastaCodigoArticuloCuadroListaPrecio.bottom
                anchors.topMargin: 10
                anchors.left: chbImprimirTodosLosArticulos.right
                anchors.leftMargin: 40
            }

            Rectangle {
                id: rectangle1
                width: 10
                clip: true
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#0f4c7d"
                    }

                    GradientStop {
                        position: 1
                        color: "#1a2329"
                    }
                }
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 5

                Rectangle {
                    id: rectangle2
                    width: 3
                    height: parent.height/1.50
                    color: "#1e7597"
                    radius: 5
                    opacity: 0.8
                    anchors.leftMargin: 5
                    anchors.bottomMargin: -1
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                }
            }


        }
    }
}
