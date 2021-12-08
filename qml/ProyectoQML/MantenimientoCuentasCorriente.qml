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
import "Listas/Delegates"


Rectangle {
    id: rectPrincipalMantenimientoCuentaCorriente
    width: 900
    height: 600
    color: "#ffffff"
    radius: 8
    visible: true
    //


    property alias codigoClienteInputMask: cbCodigoClienteCuentaCorriente.inputMask

    
    
    property double montoDelPago: 0.00
    property double montoDelSaldo: 0.00


    property string _codigoDocumentoAPagar: ""
    property string _codigoTipoDocumentoAPagar: ""
    property string _codigoClienteAPagar: ""
    property string _codigoTipoClienteAPagar: ""
    property string _codigoMonedaAPagar: ""

    property string _codigoDocumentoDePago: ""
    property string _codigoTipoDocumentoDePago: ""
    property string _codigoClienteDePago: ""
    property string _codigoTipoClienteDePago: ""
    property string _codigoMonedaDePago: ""

    property string _serieDocumentoAPagar: ""
    property string _serieDocumentoDePago: ""



    property double montoADescontarFactura: 0.00






    function limpiarListasDeDocumentos(){
        modeloListaDocumentoConDeuda.clear()
        modeloListaDocumentoDePago.clear()
        modeloDocumentosConSaldoCuentaCorriente.limpiarListaDocumentos()
        modeloDocumentosDePagoCuentaCorriente.limpiarListaDocumentos()

        listaDeDocumentosAPagar.currentIndex=0;
        listaDeDocumentosDePago.currentIndex=0;
    }


    function cargarDocumentosTotales(){
        limpiarListasDeDocumentos()
        if(cbListaMonedasDeDocumentosCuentaCorriente.codigoValorSeleccion!="-1" && cbListaMonedasDeDocumentosCuentaCorriente.codigoValorSeleccion!="0" && cbListaMonedasDeDocumentosCuentaCorriente.codigoValorSeleccion!=""){
            if(cbTipoClienteCuentaCorriente.codigoValorSeleccion!="-1" && cbTipoClienteCuentaCorriente.codigoValorSeleccion!="0" && cbTipoClienteCuentaCorriente.codigoValorSeleccion!=""){
                if(cbCodigoClienteCuentaCorriente.textoInputBox.trim()!=""){
                    cargarDocumentoConDeuda()
                    cargarDocumentoDePago()
                }
            }
        }
    }


    function cargarDocumentoConDeuda(){

        modeloListaDocumentoConDeuda.clear()
        modeloDocumentosConSaldoCuentaCorriente.limpiarListaDocumentos()
        modeloDocumentosConSaldoCuentaCorriente.buscarDocumentosAPagarCuentaCorriente(cbListaMonedasDeDocumentosCuentaCorriente.codigoValorSeleccion,cbCodigoClienteCuentaCorriente.textoInputBox.trim(),cbTipoClienteCuentaCorriente.codigoValorSeleccion)
        listaDeDocumentosAPagar.currentIndex=0;

        for(var j=0;j<modeloDocumentosConSaldoCuentaCorriente.rowCount();j++){

            modeloListaDocumentoConDeuda.append({
                                                    numeroFactura:modeloDocumentosConSaldoCuentaCorriente.retornaCodigoDocumentoPorIndice(j),
                                                    codigoTipoDocumento:modeloDocumentosConSaldoCuentaCorriente.retornaCodigoTipoDocumentoPorIndice(j),
                                                    montoDeLaDeuda:modeloDocumentosConSaldoCuentaCorriente.retornaSaldoCuentaCorrientePorIndice(j),
                                                    montoTotalFactura:modeloDocumentosConSaldoCuentaCorriente.retornaTotalDocumentoPorIndice(j),
                                                    simboloMoneda:modeloMonedas.retornaSimboloMoneda(modeloDocumentosConSaldoCuentaCorriente.retornaCodigoMonedaPorIndice(j)),
                                                    BanderaParaDeseleccionarRegistros:"9",
                                                    fechaFactura:modeloDocumentosConSaldoCuentaCorriente.retornaFechaDocumentoPorIndice(j),
                                                    observaciones:modeloDocumentosConSaldoCuentaCorriente.retornaObservacionesDocumentoPorIndice(j),
                                                    //  montoMedioDePago: modeloLineasDePagoTarjetasCredito.retornaimportePago(j),
                                                    //monedaMedioPago:modeloLineasDePagoTarjetasCredito.retornamonedaMedioPago(j),
                                                    //  simboloMonedaMedioDePago: modeloListaMonedas.retornaSimboloMoneda(modeloLineasDePagoTarjetasCredito.retornamonedaMedioPago(j)),

                                                    checkboxActivo:false,
                                                    serieDocumento:modeloDocumentosConSaldoCuentaCorriente.retornaSerieDocumentoPorIndice(j)
                                                })
        }
    }

    /*
    Q_INVOKABLE qulonglong retornaCodigoDocumentoPorIndice(int indice) const;
    Q_INVOKABLE  int retornaCodigoTipoDocumentoPorIndice(int indice) const;
    Q_INVOKABLE  QString retornaTotalDocumentoPorIndice(int indice) const;
    Q_INVOKABLE  QString retornaSaldoCuentaCorrientePorIndice(int indice) const;
    Q_INVOKABLE  int retornaCodigoMonedaPorIndice(int indice) const;
    Q_INVOKABLE  QString retornaFechaDocumentoPorIndice(int indice) const;
    Q_INVOKABLE  QString retornaObservacionesDocumentoPorIndice(int indice) const;
*/

    ListModel{
        id:modeloListaDocumentoConDeuda
    }





    ///Funcion para deseleccionar todos los registros
    function deseleccionarTodosLosRegistros(){
        for(var i=0; i<modeloListaDocumentoConDeuda.count;i++){
            modeloListaDocumentoConDeuda.setProperty(i,"BanderaParaDeseleccionarRegistros","1")
            modeloListaDocumentoConDeuda.setProperty(i,"BanderaParaDeseleccionarRegistros","2")
        }

    }


    //////////////////////////////////////////////////////////////////////////////////////
    // Funcion para marcar los registros a seleccionar y los que hay que deseleccionar  //
    ///@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@////
    function deseleccionar(indice){
        for(var i=0; i<modeloListaDocumentoConDeuda.count;i++){
            if(i==indice){
                modeloListaDocumentoConDeuda.setProperty(i,"BanderaParaDeseleccionarRegistros","0")
            }else{
                modeloListaDocumentoConDeuda.setProperty(i,"BanderaParaDeseleccionarRegistros","1")
            }
        }
    }

    // Funcion que cuenta los registros seleccionados
    function cantRegistrosSeleccionados(){
        var o=0;
        for(var i=0; i<modeloListaDocumentoConDeuda.count;i++){
            if(modeloListaDocumentoConDeuda.get(i).BanderaParaDeseleccionarRegistros=="0")
                o++
        }
        return o;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////                                                                                               ///////////////
    ////    Se controlan documento de pago, como recibos, notas de credito, ajustes cuenta corriente - ///////////////
    ////                                                                                               ///////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    function cargarDocumentoDePago(){

        modeloListaDocumentoDePago.clear()
        modeloDocumentosDePagoCuentaCorriente.limpiarListaDocumentos()
        modeloDocumentosDePagoCuentaCorriente.buscarDocumentosDePagoCuentaCorriente(cbListaMonedasDeDocumentosCuentaCorriente.codigoValorSeleccion,cbCodigoClienteCuentaCorriente.textoInputBox.trim(),cbTipoClienteCuentaCorriente.codigoValorSeleccion)
        listaDeDocumentosDePago.currentIndex=0;

        for(var j=0;j<modeloDocumentosDePagoCuentaCorriente.rowCount();j++){

            modeloListaDocumentoDePago.append({
                                                  numeroFactura:modeloDocumentosDePagoCuentaCorriente.retornaCodigoDocumentoPorIndice(j),
                                                  codigoTipoDocumento:modeloDocumentosDePagoCuentaCorriente.retornaCodigoTipoDocumentoPorIndice(j),
                                                  montoDeLaDeuda:modeloDocumentosDePagoCuentaCorriente.retornaSaldoCuentaCorrientePorIndice(j),
                                                  montoTotalFactura:modeloDocumentosDePagoCuentaCorriente.retornaTotalDocumentoPorIndice(j),
                                                  simboloMoneda:modeloMonedas.retornaSimboloMoneda(modeloDocumentosDePagoCuentaCorriente.retornaCodigoMonedaPorIndice(j)),
                                                  BanderaParaDeseleccionarRegistros:"9",
                                                  fechaFactura:modeloDocumentosDePagoCuentaCorriente.retornaFechaDocumentoPorIndice(j),
                                                  observaciones:modeloDocumentosDePagoCuentaCorriente.retornaObservacionesDocumentoPorIndice(j),
                                                  //  montoMedioDePago: modeloLineasDePagoTarjetasCredito.retornaimportePago(j),
                                                  //monedaMedioPago:modeloLineasDePagoTarjetasCredito.retornamonedaMedioPago(j),
                                                  //  simboloMonedaMedioDePago: modeloListaMonedas.retornaSimboloMoneda(modeloLineasDePagoTarjetasCredito.retornamonedaMedioPago(j)),

                                                  checkboxActivo:false,
                                                  serieDocumento:modeloDocumentosDePagoCuentaCorriente.retornaSerieDocumentoPorIndice(j)
                                              })
        }
    }

    ListModel{
        id:modeloListaDocumentoDePago
    }


    ///Funcion para deseleccionar todos los registros
    function deseleccionarTodosLosRegistrosDocumentosDePago(){
        for(var i=0; i<modeloListaDocumentoDePago.count;i++){
            modeloListaDocumentoDePago.setProperty(i,"BanderaParaDeseleccionarRegistros","1")
            modeloListaDocumentoDePago.setProperty(i,"BanderaParaDeseleccionarRegistros","2")
        }

    }


    // Funcion para marcar los registros a seleccionar y los que hay que deseleccionar  //
    function deseleccionarDocumentosDePago(indice){
        for(var i=0; i<modeloListaDocumentoDePago.count;i++){
            if(i==indice){
                modeloListaDocumentoDePago.setProperty(i,"BanderaParaDeseleccionarRegistros","0")
            }else{
                modeloListaDocumentoDePago.setProperty(i,"BanderaParaDeseleccionarRegistros","1")
            }
        }
    }

    // Funcion que cuenta los registros seleccionados
    function cantRegistrosSeleccionadosDocumentosDePago(){
        var o=0;
        for(var i=0; i<modeloListaDocumentoDePago.count;i++){
            if(modeloListaDocumentoDePago.get(i).BanderaParaDeseleccionarRegistros=="0")
                o++
        }
        return o;
    }

    
    // Funcion que cuenta los registros seleccionados
    function retornaMontoADescontarDeFatura(){
        
        montoDelPago=0.00;
        montoDelSaldo=0.00;
        montoADescontarFactura=0.00

        _codigoDocumentoAPagar= ""
        _codigoTipoDocumentoAPagar= ""
        _codigoClienteAPagar= ""
        _codigoTipoClienteAPagar= ""
        _codigoMonedaAPagar= ""

        _codigoDocumentoDePago= ""
        _codigoTipoDocumentoDePago= ""
        _codigoClienteDePago= ""
        _codigoTipoClienteDePago= ""
        _codigoMonedaDePago= ""



        for(var i=0; i<modeloListaDocumentoConDeuda.count;i++){
            if(modeloListaDocumentoConDeuda.get(i).BanderaParaDeseleccionarRegistros=="0"){
                montoDelSaldo=modeloListaDocumentoConDeuda.get(i).montoDeLaDeuda;

                _codigoDocumentoAPagar=modeloListaDocumentoConDeuda.get(i).numeroFactura;
                _codigoTipoDocumentoAPagar= modeloListaDocumentoConDeuda.get(i).codigoTipoDocumento;
                _codigoClienteAPagar= cbCodigoClienteCuentaCorriente.textoInputBox.trim();
                _codigoTipoClienteAPagar= cbTipoClienteCuentaCorriente.codigoValorSeleccion.trim();
                _codigoMonedaAPagar= cbListaMonedasDeDocumentosCuentaCorriente.codigoValorSeleccion.trim();


                _serieDocumentoAPagar=modeloListaDocumentoConDeuda.get(i).serieDocumento



                break;
            }
        }
        for(var i=0; i<modeloListaDocumentoDePago.count;i++){
            if(modeloListaDocumentoDePago.get(i).BanderaParaDeseleccionarRegistros=="0"){
                montoDelPago=modeloListaDocumentoDePago.get(i).montoDeLaDeuda;

                _codigoDocumentoDePago= modeloListaDocumentoDePago.get(i).numeroFactura;
                _codigoTipoDocumentoDePago= modeloListaDocumentoDePago.get(i).codigoTipoDocumento;
                _codigoClienteDePago= cbCodigoClienteCuentaCorriente.textoInputBox.trim();
                _codigoTipoClienteDePago= cbTipoClienteCuentaCorriente.codigoValorSeleccion.trim();
                _codigoMonedaDePago= cbListaMonedasDeDocumentosCuentaCorriente.codigoValorSeleccion.trim();
                _serieDocumentoDePago=modeloListaDocumentoDePago.get(i).serieDocumento;
                break;
            }
        }

        if(montoDelSaldo>montoDelPago){
            montoADescontarFactura=montoDelPago;
        }else if(montoDelSaldo==montoDelPago){
            montoADescontarFactura=montoDelPago;
        }else if(montoDelSaldo<montoDelPago){
            montoADescontarFactura=montoDelSaldo;
        }

        return modeloMonedas.retornaSimboloMoneda(cbListaMonedasDeDocumentosCuentaCorriente.codigoValorSeleccion)+" "+ montoADescontarFactura.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"));
    }


    
    function retornaFacturaAPagar(){
        var datosFactura="";
        for(var i=0; i<modeloListaDocumentoConDeuda.count;i++){
            if(modeloListaDocumentoConDeuda.get(i).BanderaParaDeseleccionarRegistros=="0"){
                datosFactura=modeloListaTipoDocumentosComboBox.retornaDescripcionTipoDocumento(modeloListaDocumentoConDeuda.get(i).codigoTipoDocumento)+"("+modeloListaDocumentoConDeuda.get(i).numeroFactura+")";
                break;
            }
        }
        return datosFactura;
    }

    


    Rectangle {
        id: rectContenedorCuentaCorriente
        x: 0
        y: 30
        color: "#484646"
        radius: 8
        z: 2
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
            anchors.rightMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 10


            ComboBoxListaMonedas {
                id: cbListaMonedasDeDocumentosCuentaCorriente
                width: 150
                height: 35
                botonBuscarTextoVisible: false
                textoTitulo: "Moneda documentos:"
                codigoValorSeleccion: modeloconfiguracion.retornaValorConfiguracion("MONEDA_DEFAULT")
                textoComboBox: modeloListaMonedas.retornaDescripcionMoneda(cbListaMonedasDeDocumentosCuentaCorriente.codigoValorSeleccion)
                onSenialAlAceptarOClick: {

                    cargarDocumentosTotales()

                }
            }


            ComboBoxListaTipoCliente {
                id: cbTipoClienteCuentaCorriente
                width: 120
                botonBuscarTextoVisible: false
                textoTitulo: "Tipo de Cliente:"
                codigoValorSeleccion: "1"
                textoComboBox: modeloTipoClientes.primerRegistroDeTipoClienteEnBase("1")
                visible: true//modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaTipoCliente")

                onEnter: {
                    if(cbCodigoClienteCuentaCorriente.visible){
                        limpiarListasDeDocumentos()
                        cbCodigoClienteCuentaCorriente.tomarElFocoP()
                    }
                }
                onCodigoValorSeleccionChanged: {
                    limpiarListasDeDocumentos()
                    cbCodigoClienteCuentaCorriente.textoInputBox=""
                    if(cbTipoClienteCuentaCorriente.codigoValorSeleccion=="1"){
                        lblRazonSocialClienteEnCuentaCorriente.text="Cliente: "
                    }else{
                        lblRazonSocialClienteEnCuentaCorriente.text="Proveedor: "
                    }
                    if(cbCodigoClienteCuentaCorriente.visible){
                        cbCodigoClienteCuentaCorriente.tomarElFocoP()
                    }
                }

            }


            TextInputP {
                id: cbCodigoClienteCuentaCorriente
                width: 150
                tamanioRectPrincipalCombobox: 285
                botonNuevoTexto: "Nuevo cliente..."
                utilizaListaDesplegable: true
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                botonBuscarTextoVisible: true
                inputMask: "000000;"
                largoMaximo: 6
                botonBorrarTextoVisible: true
                textoTitulo: "Cliente/Proveedor:"
                botonNuevoVisible: {
                    if(modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarClientes") && modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteCrearClientes")){
                        true
                    }else{
                        false
                    }
                }
                textoTituloFiltro: "Buscar por: dirección, nombre, razon o rut"
                listviewModel:modeloClientesFiltros
                listviewDelegate: Delegate_ListaClientesFiltros{
                    onSenialAlAceptarOClick: {
                        cbCodigoClienteCuentaCorriente.textoInputBox=codigoValorSeleccion
                        cbTipoClienteCuentaCorriente.codigoValorSeleccion=codigoValorSeleccionTipoCliente
                        cbTipoClienteCuentaCorriente.textoComboBox=modeloTipoClientes.primerRegistroDeTipoClienteEnBase(codigoValorSeleccionTipoCliente)
                        cbCodigoClienteCuentaCorriente.tomarElFocoP()
                        cbCodigoClienteCuentaCorriente.cerrarComboBox()


                        var datosDeCliente=modeloClientes.retornaDescripcionDeCliente(cbCodigoClienteCuentaCorriente.textoInputBox.trim(),cbTipoClienteCuentaCorriente.codigoValorSeleccion);
                        if(datosDeCliente==""){
                            cbTipoClienteCuentaCorriente.activo(true)
                            cbCodigoClienteCuentaCorriente.tomarElFocoP()
                        }else{
                            if(cbTipoClienteCuentaCorriente.codigoValorSeleccion=="1"){
                                lblRazonSocialClienteEnCuentaCorriente.text="Cliente: "+datosDeCliente
                            }else{
                                lblRazonSocialClienteEnCuentaCorriente.text="Proveedor: "+datosDeCliente
                            }
                            cargarDocumentosTotales()
                        }

                    }
                    onKeyEscapeCerrar: {
                        cbCodigoClienteCuentaCorriente.tomarElFocoP()
                        cbCodigoClienteCuentaCorriente.cerrarComboBox()
                    }
                }
                onClicBotonNuevoItem: {
                    mostrarMantenimientos(1,"derecha")
                }

                onClicEnBusquedaFiltro: {
                    var consultaSqlCliente=" (razonSocial rlike '"+textoAFiltrar+"' or direccion rlike '"+textoAFiltrar+"' or rut rlike '"+textoAFiltrar+"' or nombreCliente rlike '"+textoAFiltrar+"') and Clientes.tipoCliente=";
                    modeloClientesFiltros.clearClientes()
                    modeloClientesFiltros.buscarCliente(consultaSqlCliente,cbTipoClienteCuentaCorriente.codigoValorSeleccion)
                    if(modeloClientesFiltros.rowCount()!=0){
                        tomarElFocoResultado()
                    }
                }


                onClicEnBusqueda: {
                    lblRazonSocialClienteEnCuentaCorriente.text=""

                    var datosDeCliente=modeloClientes.retornaDescripcionDeCliente(cbCodigoClienteCuentaCorriente.textoInputBox.trim(),cbTipoClienteCuentaCorriente.codigoValorSeleccion);

                    if(datosDeCliente==""){
                        cbTipoClienteCuentaCorriente.activo(true)
                        cbCodigoClienteCuentaCorriente.tomarElFocoP()
                    }else{
                        if(cbTipoClienteCuentaCorriente.codigoValorSeleccion=="1"){
                            lblRazonSocialClienteEnCuentaCorriente.text="Cliente: "+datosDeCliente
                        }else{
                            lblRazonSocialClienteEnCuentaCorriente.text="Proveedor: "+datosDeCliente
                        }
                        cargarDocumentosTotales()

                    }
                }
                onTabulacion: {

                }

                onEnter: {

                    var datosDeCliente=modeloClientes.retornaDescripcionDeCliente(cbCodigoClienteCuentaCorriente.textoInputBox.trim(),cbTipoClienteCuentaCorriente.codigoValorSeleccion);
                    if(datosDeCliente==""){
                        cbTipoClienteCuentaCorriente.activo(true)
                        cbCodigoClienteCuentaCorriente.tomarElFocoP()
                    }else{
                        if(cbTipoClienteCuentaCorriente.codigoValorSeleccion=="1"){
                            lblRazonSocialClienteEnCuentaCorriente.text="Cliente: "+datosDeCliente
                        }else{
                            lblRazonSocialClienteEnCuentaCorriente.text="Proveedor: "+datosDeCliente
                        }
                        cargarDocumentosTotales()
                    }
                }
            }
        }

        Text {
            id: lblRazonSocialClienteEnCuentaCorriente
            height: 35
            color: "#dbd8d8"
            text: {
                if(cbTipoClienteCuentaCorriente.codigoValorSeleccion=="1"){
                    "Cliente: "
                }else{
                    "Proveedor: "
                }
            }
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: flow1.bottom
            anchors.topMargin: 10
            styleColor: "#be5e5e"
            font.family: "Arial"
            font.underline: false
            font.italic: false
            style: Text.Raised
            //
            font.pixelSize: 17
            font.bold: true
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignBottom
        }



        Rectangle{
            id: rectDocumentosAPagar
            color: {
                if(listaDeDocumentosAPagar.count==0){
                    "#C4C4C6"
                }else{
                    "#ff9999"
                }
            }
            radius: 3
            //
            anchors.top: lblRazonSocialClienteEnCuentaCorriente.bottom
            anchors.topMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: (parent.width+220)/2
            ListView {
                id: listaDeDocumentosAPagar
                anchors.rightMargin: 2
                anchors.leftMargin: 1
                anchors.bottomMargin: 10
                anchors.topMargin: 25
                anchors.fill: parent
                clip: true
                boundsBehavior: Flickable.DragAndOvershootBounds
                highlightFollowsCurrentItem: true
                interactive: {
                    if(listaDeDocumentosAPagar.count>10){
                        true
                    }else{
                        false
                    }
                }
                spacing: 1
                snapMode: ListView.NoSnap
                keyNavigationWraps: true
                highlightRangeMode: ListView.NoHighlightRange
                flickableDirection: Flickable.VerticalFlick
                //
                delegate:  ListaDocumentosCuentaCorriente{
                    id:delegadas

                    onClicSolo: {
                        deseleccionarTodosLosRegistros()
                        deseleccionar(index)
                    }
                }
                model: modeloListaDocumentoConDeuda


                Rectangle {
                    id: rectangle4ScroollBar
                    y: listaDeDocumentosAPagar.visibleArea.yPosition * listaDeDocumentosAPagar.height+5
                    width: 10
                    color: "#000000"
                    height: listaDeDocumentosAPagar.visibleArea.heightRatio * listaDeDocumentosAPagar.height+18
                    radius: 2
                    anchors.right: listaDeDocumentosAPagar.right
                    anchors.rightMargin: 4
                    z: 1
                    opacity: 0.500
                    visible: {
                        if(listaDeDocumentosAPagar.interactive){
                            true
                        }else{
                            false
                        }
                    }

                    //
                }
            }
        }

        Rectangle {
            id: rectDocumentoDePago
            color:{
                if(listaDeDocumentosDePago.count==0){
                    "#C4C4C6"
                }else{
                    "#b3ffbc"
                }
            }

            radius: 3
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 30
            ListView {
                id: listaDeDocumentosDePago
                anchors.rightMargin: 2
                anchors.leftMargin: 1
                anchors.bottomMargin: 10
                anchors.topMargin: 25
                anchors.fill: parent
                delegate: ListaDocumentosCuentaCorrienteDePago {

                    id:delegadasDePago

                    onClicSolo: {
                        deseleccionarTodosLosRegistrosDocumentosDePago()
                        deseleccionarDocumentosDePago(index)
                    }

                }
                anchors.right: rectDocumentosAPagar.left
                snapMode: ListView.NoSnap
                highlightFollowsCurrentItem: true
                spacing: 1
                boundsBehavior: Flickable.DragAndOvershootBounds
                clip: true
                model: modeloListaDocumentoDePago
                flickableDirection: Flickable.VerticalFlick
                interactive: {
                    if(listaDeDocumentosDePago.count>10){
                        true
                    }else{
                        false
                    }
                }
                keyNavigationWraps: true
                //
                highlightRangeMode: ListView.NoHighlightRange


                Rectangle {
                    id: rectangle3ScroollBar
                    y: listaDeDocumentosDePago.visibleArea.yPosition * listaDeDocumentosDePago.height+5
                    width: 10
                    color: "#000000"
                    height: listaDeDocumentosDePago.visibleArea.heightRatio * listaDeDocumentosDePago.height+18
                    radius: 2
                    anchors.right: listaDeDocumentosDePago.right
                    anchors.rightMargin: 4
                    z: 1
                    opacity: 0.500
                    visible: {
                        if(listaDeDocumentosDePago.interactive){
                            true
                        }else{
                            false
                        }
                    }
                    //
                }

            }
            anchors.left: rectDocumentosAPagar.right
            anchors.leftMargin: 120
            anchors.topMargin: 15
            anchors.bottom: parent.bottom
            //
            anchors.top: lblRazonSocialClienteEnCuentaCorriente.bottom



        }

        BotonPaletaSistema {
            id: btnCruzarPagos
            text: "<< Cruzar"
            anchors.top: lblRazonSocialClienteEnCuentaCorriente.bottom
            anchors.topMargin: 100
            anchors.right: rectDocumentoDePago.left
            anchors.rightMargin: 10
            anchors.left: rectDocumentosAPagar.right
            anchors.leftMargin: 10
            border.color: "#787777"
            colorTexto: {
                if(cantRegistrosSeleccionados()!=0 && cantRegistrosSeleccionadosDocumentosDePago()!=0){
                    "#212121"
                }else{
                    "gray"
                }

            }

            enabled: {
                if(cantRegistrosSeleccionados()!=0 && cantRegistrosSeleccionadosDocumentosDePago()!=0){
                    true
                }else{
                    false
                }
            }
            onClicked: {


                /// -5 Atencion, error al actualizar el documento de pago, y no se pudo restaurar el documento original, esto provoca incongruencias en el sistema
                /// -4 Datos no concuerdan para realizar la actualización
                /// -3 - Error en monto a debitar
                /// -2 - Error al actualizar el documento de pago
                /// -1 - Error al actualizar el documento a pagar
                /// 0 - Error en conexion a mysql server
                /// 1 - Actualizado con exito



                if(cantRegistrosSeleccionados()!=0 && cantRegistrosSeleccionadosDocumentosDePago()!=0 && funcionesmysql.mensajeAdvertencia("Se van a debitar "+retornaMontoADescontarDeFatura()+" del documento "+retornaFacturaAPagar()+", desea continuar?\n\nPresione [ Sí ] para confirmar.")){

                    //                     _codigoDocumentoAPagar
                    //                     _codigoTipoDocumentoAPagar
                    //                     _codigoClienteAPagar
                    //                     _codigoTipoClienteAPagar
                    //                     _codigoMonedaAPagar

                    //                     _codigoDocumentoDePago
                    //                     _codigoTipoDocumentoDePago
                    //                     _codigoClienteDePago
                    //                     _codigoTipoClienteDePago
                    //                     _codigoMonedaDePago
                    //                     _montoADebitar


                    txtMensajeInformacionArticulos.text=""
                    txtMensajeInformacionArticulos.visible=true
                    txtMensajeInformacionTimer.stop()
                    txtMensajeInformacionTimer.start()

                    var resultado = modeloDocumentosConSaldoCuentaCorriente.actualizarCuentaCorriente(_codigoDocumentoAPagar,_codigoTipoDocumentoAPagar,
                                                                                                      _codigoClienteAPagar,_codigoTipoClienteAPagar,
                                                                                                      _codigoMonedaAPagar,
                                                                                                      _codigoDocumentoDePago,_codigoTipoDocumentoDePago,
                                                                                                      _codigoClienteDePago,_codigoTipoClienteDePago,
                                                                                                      _codigoMonedaDePago,montoADescontarFactura,montoDelSaldo,
                                                                                                      _serieDocumentoAPagar,_serieDocumentoDePago
                                                                                                      );



                    if(resultado==0){
                        txtMensajeInformacionArticulos.color="#d93e3e"
                        txtMensajeInformacionArticulos.text="ATENCION: No hay acceso a la base de datos en Mysql Server."
                    }else if(resultado==-1){
                        txtMensajeInformacionArticulos.color="#d93e3e"
                        txtMensajeInformacionArticulos.text="ATENCION: No se pudo actualizar el documento a pagar."
                    }else if(resultado==-2){
                        txtMensajeInformacionArticulos.color="#d93e3e"
                        txtMensajeInformacionArticulos.text="ATENCION: No se pudo actualizar el documento de pago."
                    }else if(resultado==-3){
                        txtMensajeInformacionArticulos.color="#d93e3e"
                        txtMensajeInformacionArticulos.text="ATENCION: El monto a debitar es incorrecto."
                    }else if(resultado==-4){
                        txtMensajeInformacionArticulos.color="#d93e3e"
                        txtMensajeInformacionArticulos.text="ATENCION: Los datos no concuerdan, se aborta la actualizacion."
                    }else if(resultado==-5){
                        txtMensajeInformacionArticulos.color="#d93e3e"
                        txtMensajeInformacionArticulos.text="ATENCION: Error grave, datos del documento generaron inconsistencias, no continue!!!."
                    }else if(resultado==1){
                        txtMensajeInformacionArticulos.color="#2f71a0"
                        txtMensajeInformacionArticulos.text="Documento actualizado correctamente."
                        cargarDocumentosTotales()
                    }
                }
            }
        }
    }


    Row {
        id: rowBarraDeHerramientasCuentaCorriente
        //
        anchors.bottom: rectContenedorCuentaCorriente.top
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        spacing: distanciaEntreBotonesBarraDeTareas

        BotonBarraDeHerramientas {
            id: botonNuevoFiltro
            x: 33
            y: 10
            toolTip: "Nuevo filtro"
            z: 8
            //source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Search.png"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Nuevo.png"
            anchors.verticalCenter: parent.verticalCenter

            onClic: {


                limpiarListasDeDocumentos()

                cbListaMonedasDeDocumentosCuentaCorriente.codigoValorSeleccion=modeloconfiguracion.retornaValorConfiguracion("MONEDA_DEFAULT")
                cbListaMonedasDeDocumentosCuentaCorriente.textoComboBox=modeloListaMonedas.retornaDescripcionMoneda(cbListaMonedasDeDocumentosCuentaCorriente.codigoValorSeleccion)
                cbTipoClienteCuentaCorriente.cerrarComboBox()

                cbTipoClienteCuentaCorriente.codigoValorSeleccion=1
                cbTipoClienteCuentaCorriente.textoComboBox=modeloTipoClientes.primerRegistroDeTipoClienteEnBase(cbTipoClienteCuentaCorriente.codigoValorSeleccion)
                cbTipoClienteCuentaCorriente.cerrarComboBox()

                cbCodigoClienteCuentaCorriente.cerrarComboBox()
                cbCodigoClienteCuentaCorriente.textoInputBox=""

                if(cbTipoClienteCuentaCorriente.codigoValorSeleccion=="1"){
                    lblRazonSocialClienteEnCuentaCorriente.text="Cliente: "
                }else{
                    lblRazonSocialClienteEnCuentaCorriente.text="Proveedor: "
                }
                cbCodigoClienteCuentaCorriente.tomarElFocoP()
            }
        }

        Text {
            id: txtMensajeInformacionArticulos
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
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

            txtMensajeInformacionArticulos.visible=false
            txtMensajeInformacionArticulos.color="#d93e3e"
        }



    }

    Rectangle {
        id: rectangle4
        x: -4
        y: -1
        width: 10
        color: "#880000"
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: rectContenedorCuentaCorriente.top
        anchors.bottomMargin: -10
        z: 1
        anchors.leftMargin: 0
        anchors.left: parent.left
    }



}
