/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2025>  <Cristian Montano>

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
import CsvReader 1.0
import FileSelector 1.0

Rectangle {
    id: rectPrincipalMantenimientoListasDePrecios
    width: 900
    height: 500
    color: "#ffffff"
    radius: 8
    //

    property int codigoDeLiquidacion: 0
    property string codigoArticuloEnOpcionesExtras :""

    property bool opcionesExtrasActivas: botoncargardato1.enabled

    property alias botonNuevaListaDePrecioVisible: botonNuevaListaDePrecio.visible
    property alias  botonGuardarListaDePrecioVisible: botonGuardarListaDePrecio.visible
    property alias  botonEliminarListaDePrecioVisible: botonEliminarListaDePrecio.visible
    property alias  botonCambioRapidoDePreciosVisible: btnCargaRapidaDePrecios.visible

    property double  _precioActual: 0.00
    property double  _precioNuevo: 0.00
    property double _porcentaje: 0.00
    property double nuevoPrecioAAcomodar:0.00

    property alias codigoArticuloDesdeHastaCuadroListaPrecioInputMask: cuadroImpresionListaDePrecios.codigoArticuloDesdeHastaInputMask


    // Instancia para la carga de compras por medio de archivos CSV
    CsvReader {
        id: csvReaderListaDePrecios
    }

    FileSelector {
        id: fileSelectorListaDePrecios
    }



    function cargarArchivoCSVListaDePrecios() {
        var filePath = fileSelectorListaDePrecios.openFileDialog();
        if (filePath !== "") {
            var csvData = csvReaderListaDePrecios.readCsvFile(filePath);
            //console.log("Original CSV Data: " + csvData);

            var filteredData = [];
            var letterPattern = /[a-zA-Z]/;  // Expresión regular para detectar letras

            for (var i = 0; i < csvData.length; i++) {
                var row = csvData[i];
                var containsLetters = false;

                // Verificar cada campo en la fila
                for (var j = 0; j < row.length; j++) {
                    if (letterPattern.test(row[j])) {
                        containsLetters = true;
                        break;
                    }
                }

                // Si la fila no contiene letras, añadirla a filteredData
                if (!containsLetters) {
                    filteredData.push(row);
                }
            }

            var statusCarga=true;
            // Verifico que haya por lo menos 1 registro a cargar
            if(filteredData.length!==0){
                // Procedo a respaldar los precios actuales en caso de un problema grave en la tabla ListaPrecioArticulosBackup
                if(modeloListaPrecioArticulos.respaldarPrecios()){

                    // Iterar sobre los datos filtrados y mostrar cada registro
                    for (var k = 0; k < filteredData.length; k++) {



                        var record = filteredData[k];
                        if(record[0].trim()===""){
                            statusCarga=false;
                            funcionesmysql.mensajeAdvertenciaOk("Error,en carga de archivo CSV de precios, la linea "+k.toString()+" tiene un error.\nEl artículo esta vacio.\n\nSe cancela la carga");
                            break;
                        }

                        // Chequedo que la cantidad de campos sea mayor a 1, o sea que tenga el articulo y por lo menos 1 precio:
                        // Codigo de articulo, precio lista 1, precio lista 2, precio lista 3....precio lista 99
                        if(record.length>1){
                            // console.log("Record " + k + ": " + record.join(", "));


                            const articuloAConsultar=modeloArticulos.existeArticulo(record[0]);
                            // Reviso si el artículo existe, sino, aviso y cancelo.
                            if(articuloAConsultar===record[0]){

                                // console.log(record);
                                for (var jj = 1; jj < record.length; jj++) {
                                    var precioLista = record[jj];

                                    // Si el campo no está vacío, mostrarlo en el console.log
                                    if (precioLista.trim() !== "") {
                                        //  console.log("codigoArticulo: " + articuloAConsultar + ", lista" + jj + ": " + precioLista);
                                        const listaDePrecioACargar = jj;
                                        const codigoArticuloACargar = articuloAConsultar;
                                        const nuevoPrecioACargar = precioLista;

                                        if(modeloListaPrecioArticulos.insertarArticulosListaPrecio(listaDePrecioACargar,codigoArticuloACargar,nuevoPrecioACargar,txtNombreDeUsuario.textoInputBox.trim())!==1){
                                            const descripcionListaPrecioACargar= modeloListasPrecios.retornaDescripcionListaPrecio(listaDePrecioACargar);
                                            if(descripcionListaPrecioACargar===""){
                                                funcionesmysql.mensajeAdvertenciaOk("Hubo un error al querer cargar el siguiente artículo:\n\nArtículo: "+codigoArticuloACargar+"\nLista de precio: "+listaDePrecioACargar+" ("+descripcionListaPrecioACargar+")\nNuevo Precio: "+nuevoPrecioACargar+"\n\nSe cancela la carga, solo se actualizarón los primeros "+k+" registros.\n\n La lista de precios parece que no existe aún en el sistema.");
                                            }else{
                                                funcionesmysql.mensajeAdvertenciaOk("Hubo un error al querer cargar el siguiente artículo:\n\nArtículo: "+codigoArticuloACargar+"\nLista de precio: "+listaDePrecioACargar+" ("+descripcionListaPrecioACargar+")\nNuevo Precio: "+nuevoPrecioACargar+"\n\nSe cancela la carga, solo se actualizarón los primeros "+k+" registros.");
                                            }
                                            statusCarga=false;
                                            break;
                                        }
                                    }
                                }
                            }else{
                                funcionesmysql.mensajeAdvertenciaOk("Error,en carga de archivo CSV, la linea "+k.toString()+" tiene un error.\nArtículo: "+record+" no existe.\n\nSe cancela la carga");
                                statusCarga=false;
                                break;
                            }
                        }else{
                            funcionesmysql.mensajeAdvertenciaOk("Error,en carga de archivo CSV, la linea "+k.toString()+" tiene un error.\nArtículo: "+record+"\nDEBEN SER AL MENOS 2 COLUMNAS:codigo artículo, precioLista1...\n\nSe cancela la carga");
                            statusCarga=false;
                            break;
                        }
                    }

                }else{
                    funcionesmysql.mensajeAdvertenciaOk("Error al realizar el respaldo de los precios actuales.\n\nSe cancela la carga");
                    statusCarga=false;
                    break;
                }


                if(statusCarga){
                    modeloListasPrecios.clearListasPrecio()
                    modeloListasPrecios.buscarListasPrecio("1=","1")
                    listaListaDePrecios.currentIndex=0;
                    modeloListaPrecioArticulos.clearArticulosListaPrecio()
                    modeloListaPrecioArticulosAlternativa.clear()
                    txtPrecioArticuloParaLista.textoTitulo="Precio:"
                    funcionesmysql.mensajeAdvertenciaOk("Nuevos precios cargados ok.\n\nSe cargaron "+k+" registros.")
                }
            }else{
                funcionesmysql.mensajeAdvertenciaOk("Error, no hay registros validos para cargar.")
            }


        }
    }








    function cargarArticulosAModificarElPrecio(){

        modeloArticulosACambiarDePrecio.clear()
        for(var j=0;j<modeloListaPrecioArticulosACambiarDePrecio.rowCount();j++){

            _precioActual=modeloListaPrecioArticulosACambiarDePrecio.retornaPrecioArticulo(j)
            _precioNuevo=modeloListaPrecioArticulosACambiarDePrecio.retornaPrecioArticulo(j)
            modeloArticulosACambiarDePrecio.append({
                                                       codigoArticulo: modeloListaPrecioArticulosACambiarDePrecio.retornaCodigoArticulo(j),
                                                       precioActual:  _precioActual.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                       nuevoPrecio: _precioNuevo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                                                   })
        }
    }


    CuadroImpresionListaDePrecios{
        id:cuadroImpresionListaDePrecios
        anchors.fill: parent
        z:10
        visible: false
        onClicCancelar: cuadroImpresionListaDePrecios.visible=false
        onClicImprimir: {

            if(txtCodigoListaDePrecio.textoInputBox.trim()!="" && nombreImpresora.trim()!=""){
                modeloListasPrecios.emitirListaPrecioDuplex(txtCodigoListaDePrecio.textoInputBox.trim(),nombreImpresora, stringFiltroDeArticulosParaMostrar,tamanioDefuente)
                cuadroImpresionListaDePrecios.visible=false
            }
        }
    }

    Rectangle {
        id: rectContenedorListasDePrecios
        x: 0
        y: 30
        color: "#494747"
        radius: 8
        z: 1
        //
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 30
        anchors.fill: parent


        Flow {
            id: flow1
            height: flow1.implicitHeight
            z: 1
            spacing: 20
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 10




            TextInputSimple {
                id: txtCodigoListaDePrecio
                x: 53
                y: -36
                //   width: 100
                textoDeFondo: ""
                textoInputBox: ""
                botonBuscarTextoVisible: true
                inputMask: "000000;"
                largoMaximo: 6
                botonBorrarTextoVisible: true
                textoTitulo: "Código:"

                onEnter: txtNombreListaDePrecio.tomarElFoco()

                onTabulacion: txtNombreListaDePrecio.tomarElFoco()

                onClicEnBusqueda: {
                    modeloListasPrecios.clearListasPrecio()
                    modeloListasPrecios.buscarListasPrecio("codigoListaPrecio=",txtCodigoListaDePrecio.textoInputBox.trim())
                    listaListaDePrecios.currentIndex=0;
                    modeloListaPrecioArticulos.clearArticulosListaPrecio()
                    modeloListaPrecioArticulosAlternativa.clear()
                }
            }

            TextInputSimple {
                id: txtNombreListaDePrecio
                x: 37
                y: 90
                //   width: 230
                largoMaximo: 25
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                botonBuscarTextoVisible: true
                textoTitulo: "Nombre lista de precio:"

                onEnter: txtVigenciaDesde.tomarElFoco()

                onTabulacion: txtVigenciaDesde.tomarElFoco()

                onClicEnBusqueda: {
                    modeloListasPrecios.clearListasPrecio()
                    modeloListasPrecios.buscarListasPrecio("descripcionListaPrecio rlike",txtNombreListaDePrecio.textoInputBox.trim())
                    listaListaDePrecios.currentIndex=0;
                    modeloListaPrecioArticulos.clearArticulosListaPrecio()
                    modeloListaPrecioArticulosAlternativa.clear()

                }
            }

            TextInputSimple {
                id: txtVigenciaDesde
                x: 27
                y: 95
                //  width: 125
                textoInputBox: funcionesmysql.fechaDeHoy()
                textoTitulo: "Vigencia desde:"
                inputMask: "nnnn-nn-nn; "
                largoMaximo: 45
                enFocoSeleccionarTodo: true
                validaFormato: validacionFecha
                botonBuscarTextoVisible: false

                onEnter: txtVigenciaHasta.tomarElFoco()

                onTabulacion: txtVigenciaHasta.tomarElFoco()

            }
            RegExpValidator{
                id:validacionFecha
                ///Fecha AAAA/MM/DD
                regExp: new RegExp("(20|  |2 | 2)(0[0-9, ]| [0-9, ]|1[0123456789 ]|2[0123456789 ]|3[0123456789 ]|4[0123456789 ])\-(0[1-9, ]| [1-9, ]|1[012 ]| [012 ])\-(0[1-9, ]| [1-9, ]|[12 ][0-9, ]|3[01 ]| [01 ])")
            }

            TextInputSimple {
                id: txtVigenciaHasta
                x: 29
                y: 85
                //   width: 125
                enFocoSeleccionarTodo: true
                textoInputBox: funcionesmysql.fechaDeHoy()
                validaFormato: validacionFecha
                botonBuscarTextoVisible: false
                inputMask: "nnnn-nn-nn; "
                largoMaximo: 45
                textoTitulo: "Vigencia hasta:"

                onEnter: txtArticuloParaLista.tomarElFocoP()

                onTabulacion: txtArticuloParaLista.tomarElFocoP()
            }

            CheckBox {
                id: chbListaPrecioActiva
                x: 693
                y: 24
                textoValor: "Activa"
                chekActivo: true
                colorTexto: "#dbd8d8"
            }



            CheckBox {
                id: chbApareceEnBusquedaInteligente
                x: 689
                y: 20
                textoValor: "Se incluye en la busqueda inteligente"
                chekActivo: true
                colorTexto: "#dbd8d8"
            }

        }
        Rectangle{
            id: rectListasDePrecio
            width: (rectContenedorListasDePrecios.width-250)/2
            color: {
                if(listaListaDePrecios.count==0){
                    "#C4C4C6"
                }else{
                    "#f89e16"
                }
            }
            radius: 3
            clip: true
            //
            anchors.top: flow1.bottom
            anchors.topMargin: 35
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            ListView {
                id: listaListaDePrecios
                clip: true
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottomMargin: 25
                boundsBehavior: Flickable.DragAndOvershootBounds
                highlightFollowsCurrentItem: true
                interactive: {
                    if(listaListaDePrecios.count>5){
                        true
                    }else{
                        false
                    }
                }
                spacing: 1
                anchors.rightMargin: 1
                anchors.leftMargin: 1
                anchors.topMargin: 25
                snapMode: ListView.NoSnap
                keyNavigationWraps: true
                highlightRangeMode: ListView.NoHighlightRange
                flickableDirection: Flickable.VerticalFlick
                //

                delegate:  ListaListasDePrecios{}
                model: modeloListasPrecios

                Rectangle {
                    id: scrollbarlistaListaDePrecios
                    y: listaListaDePrecios.visibleArea.yPosition * listaListaDePrecios.height+5
                    width: 10
                    color: "#000000"
                    height: listaListaDePrecios.visibleArea.heightRatio * listaListaDePrecios.height+18
                    radius: 2
                    anchors.right: listaListaDePrecios.right
                    anchors.rightMargin: 4
                    z: 1
                    opacity: 0.500
                    visible: {
                        if(listaListaDePrecios.count>5){
                            true
                        }else{
                            false
                        }
                    }
                    //
                }

            }

            Text {
                id: txtCantidadDeItemsValor
                x: 107
                width: 37
                color: "#000000"
                text: listaListaDePrecios.count
                font.family: "Arial"
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.leftMargin: 5
                //
                font.bold: false
                font.pointSize: 10
                anchors.left: txtCantidadDeItemsTitulo.right
            }

            Text {
                id: txtCantidadDeItemsTitulo
                x: 0
                width: txtCantidadDeItemsTitulo.implicitWidth
                color: "#000000"
                text: qsTr("Cantidad de listas de precio:")
                font.family: "Arial"
                anchors.top: parent.top
                anchors.topMargin: 5
                font.pointSize: 10
                font.bold: false
                anchors.left: parent.left
                anchors.leftMargin: 5
                //
            }

            BotonBarraDeHerramientas {
                id: botonSubirListaFinal
                x: 300
                y: 60
                width: 14
                height: 14
                anchors.right: parent.right
                anchors.rightMargin: 3
                toolTip: ""
                anchors.top: parent.top
                anchors.topMargin: 5
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                rotation: 90
                visible: scrollbarlistaListaDePrecios.visible
                onClic: listaListaDePrecios.positionViewAtIndex(0,0)
            }

            BotonBarraDeHerramientas {
                id: botonBajarListaFinal
                x: 300
                y: 285
                width: 14
                height: 14
                anchors.right: parent.right
                anchors.rightMargin: 3
                toolTip: ""
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                rotation: -90
                visible: scrollbarlistaListaDePrecios.visible
                onClic: listaListaDePrecios.positionViewAtIndex(listaListaDePrecios.count-1,0)

            }

        }

        Rectangle {
            id: rectListasDePrecioArticulos
            color: {
                if(listaArticulosPrecio.count==0){
                    "#C4C4C6"
                }else{
                    "#f89e16"
                }
            }
            radius: 3
            clip: true
            //
            anchors.left: rectListasDePrecio.right
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.top: flow1.bottom
            anchors.topMargin: 70
            ListView {
                id: listaArticulosPrecio
                clip: true
                highlightRangeMode: ListView.NoHighlightRange
                anchors.top: parent.top
                boundsBehavior: Flickable.DragAndOvershootBounds
                highlightFollowsCurrentItem: true
                anchors.right: parent.right
                delegate: ListaPreciosArticulos{}
                // delegate: ListaPrecioArticulosNueva{}
                snapMode: ListView.NoSnap
                anchors.bottomMargin: 25
                spacing: 1
                cacheBuffer: 200000
                anchors.bottom: parent.bottom
                flickableDirection: Flickable.VerticalFlick
                anchors.leftMargin: 1
                keyNavigationWraps: true
                anchors.left: parent.left
                interactive: {
                    if(listaArticulosPrecio.count>5){
                        true
                    }else{
                        false
                    }
                }
                //
                anchors.topMargin: 48
                anchors.rightMargin: 1

                model: modeloListaPrecioArticulosAlternativa
                //  model:modeloListaPrecioArticulos





                Rectangle {
                    id: scrollbarlistaArticulosPrecio
                    y: listaArticulosPrecio.visibleArea.yPosition * listaArticulosPrecio.height+5
                    width: 10
                    color: "#000000"
                    height: listaArticulosPrecio.visibleArea.heightRatio * listaArticulosPrecio.height+18
                    radius: 2
                    anchors.right: listaArticulosPrecio.right
                    anchors.rightMargin: 4
                    z: 1
                    opacity: 0.500
                    visible: {
                        if(listaArticulosPrecio.count>5){
                            true
                        }else{
                            false
                        }
                    }
                    //
                }

            }

            ListModel{
                id:modeloListaPrecioArticulosAlternativa

            }

            TextInputP {
                id: txtArticuloParaLista
                width: 280
                largoMaximo: 30
                textoDeFondo: ""
                colorDeTitulo: "#252424"
                anchors.top: parent.top
                anchors.topMargin: 3
                anchors.left: parent.left
                anchors.leftMargin: 10
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                botonBuscarTextoVisible: false
                textoTitulo: "Artículo:"

                botonNuevoTexto: "Nuevo artículo..."
                utilizaListaDesplegable: true
                tamanioRectPrincipalCombobox: 320

                tamanioRectPrincipalComboboxAlto: {
                    if(checkBoxActivoVisible){
                        400
                    }else{
                        300
                    }
                }
                checkBoxActivoVisible: true
                checkBoxActivoTexto: "Incluir artículos inactivos"

                botonNuevoVisible:{
                    if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos") && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearArticulos")){
                        true
                    }else{
                        false
                    }
                }
                visible: true
                textoTituloFiltro: "Buscar por: descripción, proveedor, iva o moneda"
                listviewModel:modeloArticulosFiltrosListaPrecio1
                listviewDelegate: Delegate_ListaArticulosFiltros{
                    onSenialAlAceptarOClick: {
                        txtArticuloParaLista.textoInputBox=codigoValorSeleccion
                        txtArticuloParaLista.cerrarComboBox()
                        txtPrecioArticuloParaLista.textoTitulo="Precio en "+modeloListaMonedas.retornaSimboloMoneda(modeloListaMonedas.retornaCodigoMoneda(codigoValorSeleccion))
                        txtPrecioArticuloParaLista.tomarElFoco()
                    }
                    onKeyEscapeCerrar: {
                        txtArticuloParaLista.tomarElFocoP()
                        txtArticuloParaLista.cerrarComboBox()
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

                    modeloArticulosFiltrosListaPrecio1.clearArticulos()
                    modeloArticulosFiltrosListaPrecio1.buscarArticulo(consultaSqlArticulo,"1",0)

                    if(modeloArticulosFiltrosListaPrecio1.rowCount()!=0){
                        tomarElFocoResultado()
                    }

                }

                onEnter: {
                    var valorArticuloInterno=modeloArticulos.existeArticulo(txtArticuloParaLista.textoInputBox.trim());

                    console.log(valorArticuloInterno)

                    if(valorArticuloInterno!=""){
                        txtArticuloParaLista.textoInputBox=valorArticuloInterno
                        txtPrecioArticuloParaLista.textoTitulo="Precio en "+modeloListaMonedas.retornaSimboloMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                        txtPrecioArticuloParaLista.tomarElFoco()
                    }else{
                        txtArticuloParaLista.tomarElFocoP()
                    }
                }
                onTabulacion: txtPrecioArticuloParaLista.tomarElFoco()
            }

            TextInputSimple {
                id: txtPrecioArticuloParaLista
                x: 3
                y: -1
                //    width: 150
                colorDeTitulo: "#252424"
                largoMaximo: 45
                inputMask: "00000000"+modeloconfiguracion.retornaCantidadDecimalesString()+";"
                enFocoSeleccionarTodo: true
                textoInputBox: ""+modeloconfiguracion.retornaCantidadDecimalesString()+""
                anchors.top: parent.top
                anchors.topMargin: 3
                botonBuscarTextoVisible: false
                textoTitulo: "Precio:"
                anchors.leftMargin: 0
                anchors.left: txtArticuloParaLista.right

                onEnter: {
                    var valorArticuloInterno=modeloArticulos.existeArticulo(txtArticuloParaLista.textoInputBox.trim());
                    if(valorArticuloInterno!=""){
                        if(txtPrecioArticuloParaLista.textoInputBox.trim()!=""+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                            for(var i=0; i<modeloListaPrecioArticulosAlternativa.count;i++){
                                if(modeloListaPrecioArticulosAlternativa.get(i).itemCodigoAgregado==valorArticuloInterno){
                                    modeloListaPrecioArticulosAlternativa.remove(i)
                                }
                            }
                            modeloListaPrecioArticulosAlternativa.append({
                                                                             itemDescripcion:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                             itemCodigoAgregado:valorArticuloInterno,
                                                                             simboloMoneda:modeloMonedas.retornaSimboloMonedaPorArticulo(valorArticuloInterno),
                                                                             itemPrecioAgregado:txtPrecioArticuloParaLista.textoInputBox.trim(),
                                                                             precioModificado:true,
                                                                             eliminarPrecioArticulo:false
                                                                         })
                            txtArticuloParaLista.textoInputBox=""
                            txtPrecioArticuloParaLista.textoInputBox=""+modeloconfiguracion.retornaCantidadDecimalesString()+""
                            txtArticuloParaLista.tomarElFocoP()

                        }
                    }
                }
                onTabulacion: txtArticuloParaLista.tomarElFocoP()

            }

            BotonCargarDato {
                id: botoncargardato1
                imagen: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Suma.png"
                texto: "más articulos..."
                anchors.left: txtPrecioArticuloParaLista.right
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 9

                onClic: {

                    rectOpcionesExtrasDesaparecer.stop()
                    rectOpcionesExtrasAparecer.start()
                    rowBarraDeHerramientasListaDePrecios.enabled=false

                    botoncargardato1.volverAEstadoOriginalElControl()

                    modeloArticulosOpcionesExtra.clearArticulos()
                    modeloArticulosOpcionesExtra.buscarArticulo("1=","2",0)
                    lblDescripcionArticulo.text=""
                    txtPrecioArticuloParaLista1.textoInputBox=""+modeloconfiguracion.retornaCantidadDecimalesString()+""
                    txtPrecioArticuloParaLista1.textoTitulo="Precio:"
                    codigoArticuloEnOpcionesExtras=0
                    txtCodigoArticuloOpcionesExtras.textoInputBox=""
                    txtDescripcionArticuloOpcionesExtras.textoInputBox=""
                    cbxListaProveedoresOpcionesExtra.textoComboBox=""
                    cbxListaProveedoresOpcionesExtra.codigoValorSeleccion=""
                    botoncargardato1.enabled=false
                    txtCodigoArticuloOpcionesExtras.tomarElFoco()
                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=false

                }
            }

            BotonBarraDeHerramientas {
                id: botonBajarListaFinal1
                x: 510
                y: 265
                width: 14
                height: 14
                anchors.right: parent.right
                anchors.rightMargin: 3
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                anchors.bottom: parent.bottom
                toolTip: ""
                anchors.bottomMargin: 5
                rotation: -90
                visible: scrollbarlistaArticulosPrecio.visible
                onClic: listaArticulosPrecio.positionViewAtIndex(listaArticulosPrecio.count-1,0)
            }

            BotonBarraDeHerramientas {
                id: botonSubirListaFinal1
                x: 510
                y: 80
                width: 14
                height: 14
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.top: parent.top
                anchors.topMargin: 25
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                toolTip: ""
                rotation: 90
                visible: scrollbarlistaArticulosPrecio.visible
                onClic: listaArticulosPrecio.positionViewAtIndex(0,0)
            }
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
        }

        BotonCargarDato {
            id: btnCargaRapidaDePrecios
            visible: true
            textoColor: "#dbd8d8"
            anchors.right: btnCargarListaDePreciosDesdeCSV.left
            anchors.rightMargin: 20
            anchors.bottom: rectListasDePrecioArticulos.top
            anchors.bottomMargin: 10
            texto: "carga rapida de precios..."
            imagen: "qrc:/imagenes/qml/ProyectoQML/Imagenes/SumaBlanca.png"
            //   anchors.leftMargin: 0
            //   anchors.left: txtPrecioArticuloParaLista.right
            enabled: botoncargardato1.enabled
            onClic: {

                rectCargaRapidaDePreciosDesaparecer.stop()
                rectCargaRapidaDePreciosAparecer.start()

                rowBarraDeHerramientasListaDePrecios.enabled=false

                btnCargaRapidaDePrecios.volverAEstadoOriginalElControl()

                botoncargardato1.enabled=false
                btnCargaRapidaDePrecios.enabled=botoncargardato1.enabled

                rowMenusDelSistema.z=-1
                btnLateralBusquedas.z=0
                menulista1.enabled=false

            }
        }

        BotonCargarDato {
            id: btnCargarListaDePreciosDesdeCSV
            textoColor:{
                if(enabled){
                    "#dbd8d8"
                }else{
                    "#6d6c6c"
                }
            }
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: rectListasDePrecioArticulos.top
            anchors.bottomMargin: 10
            texto: "Cargar lista de precios desde CSV..."
            imagen: "qrc:/imagenes/qml/ProyectoQML/Imagenes/SumaBlanca.png"
            visible: true
            enabled: btnCargaRapidaDePrecios.visible

            onClic: {

                cargarArchivoCSVListaDePrecios()

            }

        }


        BotonPaletaSistema {
            id: btnEmitirListaDePrecio
            radius: 2
            visible: true
            text: "Imprimir lista de precio..."
            anchors.bottom: rectListasDePrecioArticulos.top
            anchors.bottomMargin: 10
            anchors.right: btnCargaRapidaDePrecios.left
            anchors.rightMargin: 10
            enabled: {
                if(txtCodigoListaDePrecio.textoInputBox.trim()!="" && txtNombreListaDePrecio.textoInputBox.trim()!="" && listaArticulosPrecio.count!=0){
                    true
                }else{
                    false
                }
            }

            onClicked: {
                if(modeloListasPrecios.retornaDescripcionListaPrecio(txtCodigoListaDePrecio.textoInputBox.trim())!=""){
                    cuadroImpresionListaDePrecios.visible=true
                }else{
                    btnEmitirListaDePrecio.mensajeError("No existe la lista de precios "+txtCodigoListaDePrecio.textoInputBox.trim())
                }
            }
        }
    }

    ListModel{
        id:modeloArticulosCodigoDeBarras

    }



    Row {
        id: rowBarraDeHerramientasListaDePrecios
        //
        anchors.bottom: rectContenedorListasDePrecios.top
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        spacing: distanciaEntreBotonesBarraDeTareas

        BotonBarraDeHerramientas {
            id: botonNuevaListaDePrecio
            x: 33
            y: 10
            toolTip: "Nueva lista de precio"
            z: 8
            //source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevaListaDePrecios.png"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Nuevo.png"
            anchors.verticalCenter: parent.verticalCenter
            onClic: {

                txtCodigoListaDePrecio.textoInputBox=modeloListasPrecios.ultimoRegistroDeListasPrecioEnBase()
                txtNombreListaDePrecio.textoInputBox=""
                txtVigenciaDesde.textoInputBox=funcionesmysql.fechaDeHoy()
                txtVigenciaHasta.textoInputBox=funcionesmysql.fechaDeHoy()
                txtNombreListaDePrecio.tomarElFoco()

                modeloListaPrecioArticulos.clearArticulosListaPrecio()
                modeloListaPrecioArticulosAlternativa.clear()
                txtArticuloParaLista.textoInputBox=""
                txtPrecioArticuloParaLista.textoInputBox=""+modeloconfiguracion.retornaCantidadDecimalesString()+""

            }
        }
        BotonBarraDeHerramientas {
            id: botonGuardarListaDePrecio
            x: 61
            y: 3
            toolTip: "Guardar lista de precio"
            z: 7
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            anchors.verticalCenter: parent.verticalCenter

            onClic: {

                var activo=1
                var participaBusquedaInteli=1

                if(!chbListaPrecioActiva.chekActivo)
                    activo=0

                if(!chbApareceEnBusquedaInteligente.chekActivo)
                    participaBusquedaInteli=0


                var resultadoInsertListaDePrecio = modeloListasPrecios.insertarListasPrecio(txtCodigoListaDePrecio.textoInputBox.trim(),txtNombreListaDePrecio.textoInputBox.trim(),txtVigenciaDesde.textoInputBox.trim(),txtVigenciaHasta.textoInputBox.trim(),txtNombreDeUsuario.textoInputBox,activo,participaBusquedaInteli);

                txtMensajeInformacionListaDePrecio.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                if(resultadoInsertListaDePrecio==1){
                    txtMensajeInformacionListaDePrecio.color="#2f71a0"
                    txtMensajeInformacionListaDePrecio.text="Lista de precio "+ txtCodigoListaDePrecio.textoInputBox+" dado de alta correctamente"


                    //if(modeloListaPrecioArticulos.eliminarArticulosListaPrecio(txtCodigoListaDePrecio.textoInputBox.trim())){

                    for(var i=0; i<modeloListaPrecioArticulosAlternativa.count;i++){

                        if(modeloListaPrecioArticulosAlternativa.get(i).precioModificado==true && modeloListaPrecioArticulosAlternativa.get(i).eliminarPrecioArticulo==false){
                            modeloListaPrecioArticulos.insertarArticulosListaPrecio(txtCodigoListaDePrecio.textoInputBox.trim(),modeloListaPrecioArticulosAlternativa.get(i).itemCodigoAgregado, modeloListaPrecioArticulosAlternativa.get(i).itemPrecioAgregado,txtNombreDeUsuario.textoInputBox)
                        }else if(modeloListaPrecioArticulosAlternativa.get(i).eliminarPrecioArticulo==true){
                            modeloListaPrecioArticulos.eliminarArticuloPorListaPrecio(txtCodigoListaDePrecio.textoInputBox.trim(),modeloListaPrecioArticulosAlternativa.get(i).itemCodigoAgregado);
                        }

                    }
                    //}


                    modeloListasPreciosComboBox.clearListasPrecio()
                    modeloListasPreciosComboBox.buscarListasPrecio("1=","1")

                    modeloListasPrecios.clearListasPrecio()
                    modeloListasPrecios.buscarListasPrecio("1=","1")
                    listaListaDePrecios.currentIndex=0;
                    txtCodigoListaDePrecio.textoInputBox=""
                    txtNombreListaDePrecio.textoInputBox=""
                    txtVigenciaDesde.textoInputBox=funcionesmysql.fechaDeHoy()
                    txtVigenciaHasta.textoInputBox=funcionesmysql.fechaDeHoy()
                    modeloListaPrecioArticulos.clearArticulosListaPrecio()
                    modeloListaPrecioArticulosAlternativa.clear()
                    txtPrecioArticuloParaLista.textoInputBox=""+modeloconfiguracion.retornaCantidadDecimalesString()+""
                    txtArticuloParaLista.textoInputBox=""


                }else if(resultadoInsertListaDePrecio==2){
                    txtMensajeInformacionListaDePrecio.color="#2f71a0"
                    txtMensajeInformacionListaDePrecio.text="Lista de precio "+ txtCodigoListaDePrecio.textoInputBox+" actualizada correctamente"

                    //if(modeloListaPrecioArticulos.eliminarArticulosListaPrecio(txtCodigoListaDePrecio.textoInputBox.trim())){

                    for(var i=0; i<modeloListaPrecioArticulosAlternativa.count;i++){

                        if(modeloListaPrecioArticulosAlternativa.get(i).precioModificado==true  && modeloListaPrecioArticulosAlternativa.get(i).eliminarPrecioArticulo==false){
                            modeloListaPrecioArticulos.insertarArticulosListaPrecio(txtCodigoListaDePrecio.textoInputBox.trim(),modeloListaPrecioArticulosAlternativa.get(i).itemCodigoAgregado, modeloListaPrecioArticulosAlternativa.get(i).itemPrecioAgregado,txtNombreDeUsuario.textoInputBox)
                        }else if(modeloListaPrecioArticulosAlternativa.get(i).eliminarPrecioArticulo==true){
                            modeloListaPrecioArticulos.eliminarArticuloPorListaPrecio(txtCodigoListaDePrecio.textoInputBox.trim(),modeloListaPrecioArticulosAlternativa.get(i).itemCodigoAgregado);
                        }
                    }
                    //}

                    modeloListasPrecios.clearListasPrecio()
                    modeloListasPrecios.buscarListasPrecio("1=","1")
                    listaListaDePrecios.currentIndex=0;
                    txtCodigoListaDePrecio.textoInputBox=""
                    txtNombreListaDePrecio.textoInputBox=""
                    txtVigenciaDesde.textoInputBox=funcionesmysql.fechaDeHoy()
                    txtVigenciaHasta.textoInputBox=funcionesmysql.fechaDeHoy()
                    modeloListaPrecioArticulos.clearArticulosListaPrecio()
                    modeloListaPrecioArticulosAlternativa.clear()
                    txtPrecioArticuloParaLista.textoInputBox=""+modeloconfiguracion.retornaCantidadDecimalesString()+""
                    txtArticuloParaLista.textoInputBox=""


                }else if(resultadoInsertListaDePrecio==-1){
                    txtMensajeInformacionListaDePrecio.color="#d93e3e"
                    txtMensajeInformacionListaDePrecio.text="ATENCION: No se pudo conectar a la base de datos"


                }else if(resultadoInsertListaDePrecio==-2){
                    txtMensajeInformacionListaDePrecio.color="#d93e3e"
                    txtMensajeInformacionListaDePrecio.text="ATENCION: No se pudo actualizar la lista de precio"


                }else if(resultadoInsertListaDePrecio==-3){
                    txtMensajeInformacionListaDePrecio.color="#d93e3e"
                    txtMensajeInformacionListaDePrecio.text="ATENCION: No se pudo dar de alta la lista de precio"


                }else if(resultadoInsertListaDePrecio==-4){
                    txtMensajeInformacionListaDePrecio.color="#d93e3e"
                    txtMensajeInformacionListaDePrecio.text="ATENCION: No se pudo realizar la consulta a la base de datos"


                }else if(resultadoInsertListaDePrecio==-5){
                    txtMensajeInformacionListaDePrecio.color="#d93e3e"
                    txtMensajeInformacionListaDePrecio.text="ATENCION: Faltan datos para guardar la lista. Verifique antes de continuar"

                }




            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarListaDePrecio
            x: 54
            y: 3
            toolTip: "Eliminar lista de precio"
            z: 6
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            anchors.verticalCenter: parent.verticalCenter
            onClic: {

                if(txtCodigoListaDePrecio.textoInputBox.trim()!="")
                    if(funcionesmysql.mensajeAdvertencia("Realmente desea eliminar la lista de precio "+txtNombreListaDePrecio.textoInputBox.trim()+"?\n\nPresione [ Sí ] para confirmar.")){

                        if(modeloListasPrecios.eliminarListasPrecio(txtCodigoListaDePrecio.textoInputBox.trim())){


                            txtMensajeInformacionListaDePrecio.visible=true
                            txtMensajeInformacionTimer.stop()
                            txtMensajeInformacionTimer.start()

                            txtMensajeInformacionListaDePrecio.color="#2f71a0"
                            txtMensajeInformacionListaDePrecio.text="Lista de precio "+txtCodigoListaDePrecio.textoInputBox.trim()+" eliminada correctamente"

                            modeloListasPrecios.clearListasPrecio()
                            modeloListasPrecios.buscarListasPrecio("1=","1")
                            listaListaDePrecios.currentIndex=0;


                            txtCodigoListaDePrecio.textoInputBox=""
                            txtNombreListaDePrecio.textoInputBox=""
                            txtVigenciaDesde.textoInputBox=funcionesmysql.fechaDeHoy()
                            txtVigenciaHasta.textoInputBox=funcionesmysql.fechaDeHoy()

                            modeloListaPrecioArticulosAlternativa.clear()
                            modeloListaPrecioArticulos.clearArticulosListaPrecio()


                        }else{
                            txtMensajeInformacionListaDePrecio.visible=true
                            txtMensajeInformacionTimer.stop()
                            txtMensajeInformacionTimer.start()
                            txtMensajeInformacionListaDePrecio.color="#d93e3e"
                            txtMensajeInformacionListaDePrecio.text="ATENCION: No se puede eliminar la lista de precios, verifique la información."

                        }
                    }
            }
        }

        BotonBarraDeHerramientas {
            id: botonListarTodasLasListasDePrecio
            x: 47
            y: 10
            toolTip: "Listar todas las listas de precios"
            z: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            anchors.verticalCenter: parent.verticalCenter


            onClic: {

                modeloListasPrecios.clearListasPrecio()
                modeloListasPrecios.buscarListasPrecio("1=","1")
                listaListaDePrecios.currentIndex=0;
                modeloListaPrecioArticulos.clearArticulosListaPrecio()
                modeloListaPrecioArticulosAlternativa.clear()
                txtPrecioArticuloParaLista.textoTitulo="Precio:"
            }
        }

        Text {
            id: txtMensajeInformacionListaDePrecio
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            font.family: "Arial"
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

            txtMensajeInformacionListaDePrecio.visible=false
            txtMensajeInformacionListaDePrecio.color="#d93e3e"

        }
    }

    Rectangle {
        id: rectColorBarraHerramientas
        width: 10
        height: 30
        color: "#f89e16"
        z: 0
        anchors.bottom: rectContenedorListasDePrecios.top
        anchors.bottomMargin: -20
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
    }


    PropertyAnimation{
        id:rectOpcionesExtrasAparecer
        target: rectOpcionesExtras
        property: "anchors.leftMargin"
        from:-515
        to:-53
        duration: 200
    }

    PropertyAnimation{
        id:rectOpcionesExtrasDesaparecer
        target: rectOpcionesExtras
        property: "anchors.leftMargin"
        to:-515
        from:-53
        duration: 50
    }
    PropertyAnimation{
        id:rectCargaRapidaDePreciosAparecer
        target: rectCargaRapidaDePrecios
        property: "anchors.leftMargin"
        from:-515
        to:-53
        duration: 200
    }

    PropertyAnimation{
        id:rectCargaRapidaDePreciosDesaparecer
        target: rectCargaRapidaDePrecios
        property: "anchors.leftMargin"
        to:-515
        from:-53
        duration: 50
    }

    Rectangle {
        id: rectOpcionesExtras
        width: 450
        color: rectColorBarraHerramientas.color
        radius: 2
        visible: true
        //
        anchors.left: parent.left
        anchors.leftMargin: -515
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -5
        anchors.top: parent.top
        anchors.topMargin: -68
        z: 6


        Keys.onEscapePressed: {

            rectOpcionesExtrasAparecer.stop()
            rectOpcionesExtrasDesaparecer.start()

            rowBarraDeHerramientasListaDePrecios.enabled=true
            botoncargardato1.enabled=true
            txtArticuloParaLista.tomarElFocoP()
            //   rowMenusDelSistema.z=0
            menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
        }

        Rectangle {
            id: rectSombraOpcionesExtras
            x: 333
            width: 17
            color: rectColorBarraHerramientas.color
            //
            opacity: 0.300
            anchors.right: parent.right
            anchors.rightMargin: -12
            z: -1
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
        }

        MouseArea {
            id: mouse_area1
            anchors.fill: parent

            BotonPaletaSistema {
                id: botonpaletasistema1
                x: 379
                y: 148
                text: "Apicar filtro"
                anchors.bottom: rectListasDePrecioArticulos1.top
                anchors.bottomMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 10
                visible: true
                onClicked: {

                    var consultaSql="";

                    if(txtCodigoArticuloOpcionesExtras.textoInputBox.trim()!=""){
                        consultaSql+=" AR.codigoArticulo rlike '"+txtCodigoArticuloOpcionesExtras.textoInputBox.trim()+"' and ";
                    }
                    if(txtDescripcionArticuloOpcionesExtras.textoInputBox.trim()!=""){
                        consultaSql+=" AR.descripcionArticulo rlike '"+txtDescripcionArticuloOpcionesExtras.textoInputBox.trim()+"' and "
                    }
                    if(cbxListaProveedoresOpcionesExtra.codigoValorSeleccion.trim()!=""){
                        consultaSql+=" AR.codigoProveedor rlike '"+cbxListaProveedoresOpcionesExtra.codigoValorSeleccion.trim()+"' and "
                    }
                    if(consultaSql!=""){
                        modeloArticulosOpcionesExtra.clearArticulos()
                        modeloArticulosOpcionesExtra.buscarArticulo(consultaSql,"1=1",0)
                    }
                }
            }

            Text {
                id: txtTituloOpcionesExtras
                x: 20
                y: 10
                color: "#ffffff"
                text: qsTr("filtros de artículos")
                font.family: "Arial"
                font.underline: false
                font.italic: false
                font.bold: true
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 20
                visible: true
                font.pixelSize: 23
            }

            Flow {
                id: flowOpcionesExtras
                x: 10
                y: 60
                height: flowOpcionesExtras.implicitHeight+10
                visible: true
                z: 3
                spacing: 5
                anchors.top: parent.top
                anchors.topMargin: 60
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 10

                TextInputSimple {
                    id: txtCodigoArticuloOpcionesExtras
                    x: 22
                    y: 43
                    //    width: 130
                    largoMaximo: 8
                    colorDeTitulo: "white"
                    botonBuscarTextoVisible: true
                    botonBorrarTextoVisible: true
                    textoTitulo: "SKU:"
                    z: 1
                    visible: true

                    onClicEnBusqueda: {
                        modeloArticulosOpcionesExtra.clearArticulos()
                        modeloArticulosOpcionesExtra.buscarArticulo(" AR.codigoArticulo =",txtCodigoArticuloOpcionesExtras.textoInputBox,0)
                    }
                    onEnter: {
                        txtDescripcionArticuloOpcionesExtras.tomarElFoco()
                    }
                    onTabulacion: {
                        txtDescripcionArticuloOpcionesExtras.tomarElFoco()
                    }

                }

                TextInputSimple {
                    id: txtDescripcionArticuloOpcionesExtras
                    x: 22
                    y: 43
                    //    width: 200
                    colorDeTitulo: "white"
                    botonBuscarTextoVisible: true
                    botonBorrarTextoVisible: true
                    textoTitulo: "Descripción:"
                    z: 1
                    largoMaximo: 20
                    visible: true
                    onClicEnBusqueda: {
                        modeloArticulosOpcionesExtra.clearArticulos()
                        modeloArticulosOpcionesExtra.buscarArticulo(" AR.descripcionArticulo rlike",txtDescripcionArticuloOpcionesExtras.textoInputBox,0)
                    }
                    onEnter: {
                        cbxListaProveedoresOpcionesExtra.tomarElFoco()
                    }
                    onTabulacion: {
                        cbxListaProveedoresOpcionesExtra.tomarElFoco()
                    }
                }

                ComboBoxListaProveedores {
                    id: cbxListaProveedoresOpcionesExtra
                    x: 22
                    y: 56
                    width: 250
                    visible: true
                    colorTitulo: "#ffffff"
                    botonBuscarTextoVisible: true
                    textoTitulo: "Proveedor:"
                    z: 2
                    onClicEnBusqueda: {
                        modeloArticulosOpcionesExtra.clearArticulos()
                        modeloArticulosOpcionesExtra.buscarArticulo(" AR.codigoProveedor rlike",cbxListaProveedoresOpcionesExtra.codigoValorSeleccion.trim(),0)
                    }
                    onEnter: {

                        txtCodigoArticuloOpcionesExtras.tomarElFoco()
                    }
                    onTabulacion: {

                        txtCodigoArticuloOpcionesExtras.tomarElFoco()
                    }
                }
            }

            Rectangle {
                id: rectListasDePrecioArticulos1
                x: 5
                y: 175
                color: "#64b7b6b6"
                radius: 3
                clip: true
                //
                z: 2
                anchors.top: flowOpcionesExtras.bottom
                anchors.topMargin: 30
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.rightMargin: 5
                anchors.leftMargin: 5
                anchors.bottomMargin: 5
                ListView {
                    id: listaArticulosEnOpcionesExtraListaPrecio
                    clip: true
                    z: 1
                    highlightRangeMode: ListView.NoHighlightRange
                    anchors.top: parent.top
                    boundsBehavior: Flickable.DragAndOvershootBounds
                    highlightFollowsCurrentItem: true
                    anchors.right: parent.right
                    delegate: ListaArticulosOpcionesExtras{}
                    snapMode: ListView.NoSnap
                    anchors.bottomMargin: 25
                    spacing: 1
                    anchors.bottom: parent.bottom
                    flickableDirection: Flickable.VerticalFlick
                    anchors.leftMargin: 1
                    keyNavigationWraps: true
                    anchors.left: parent.left
                    interactive: true
                    //
                    anchors.topMargin: 68
                    anchors.rightMargin: 1
                    model: modeloArticulosOpcionesExtra


                    Rectangle {
                        id: scrollbarlistaArticulosEnOpcionesExtraListaPrecio
                        y: listaArticulosEnOpcionesExtraListaPrecio.visibleArea.yPosition * listaArticulosEnOpcionesExtraListaPrecio.height+5
                        width: 10
                        color: "#000000"
                        height: listaArticulosEnOpcionesExtraListaPrecio.visibleArea.heightRatio * listaArticulosEnOpcionesExtraListaPrecio.height+18
                        radius: 2
                        anchors.right: listaArticulosEnOpcionesExtraListaPrecio.right
                        anchors.rightMargin: 4
                        z: 1
                        opacity: 0.500
                        visible: true
                        //


                    }
                }

                TextInputSimple {
                    id: txtPrecioArticuloParaLista1
                    x: 3
                    y: -1
                    //   width: 150
                    anchors.right: parent.right
                    anchors.rightMargin: -15
                    visible: true
                    enFocoSeleccionarTodo: true
                    textoInputBox: ""+modeloconfiguracion.retornaCantidadDecimalesString()+""
                    anchors.top: parent.top
                    anchors.topMargin: 3
                    botonBuscarTextoVisible: false
                    inputMask: "00000000"+modeloconfiguracion.retornaCantidadDecimalesString()+";"
                    largoMaximo: 45
                    textoTitulo: "Precio:"
                    colorDeTitulo: "#252424"
                    onEnter: {



                        if(txtPrecioArticuloParaLista1.textoInputBox.trim()!=""+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                            for(var i=0; i<modeloListaPrecioArticulosAlternativa.count;i++){
                                if(modeloListaPrecioArticulosAlternativa.get(i).itemCodigoAgregado==codigoArticuloEnOpcionesExtras){
                                    modeloListaPrecioArticulosAlternativa.remove(i)
                                }
                            }
                            modeloListaPrecioArticulosAlternativa.append({
                                                                             itemDescripcion:modeloArticulos.retornaDescripcionArticulo(codigoArticuloEnOpcionesExtras),
                                                                             itemCodigoAgregado:codigoArticuloEnOpcionesExtras,
                                                                             simboloMoneda:modeloMonedas.retornaSimboloMonedaPorArticulo(codigoArticuloEnOpcionesExtras),
                                                                             itemPrecioAgregado:txtPrecioArticuloParaLista1.textoInputBox.trim(),
                                                                             precioModificado:true,
                                                                             eliminarPrecioArticulo:false

                                                                         })

                            txtPrecioArticuloParaLista1.tomarElFoco()


                        }



                    }

                }

                Text {
                    id: lblDescripcionArticulo
                    height: 17
                    text: qsTr("")
                    font.family: "Arial"
                    horizontalAlignment: Text.AlignRight
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    verticalAlignment: Text.AlignVCenter
                    //
                    font.pointSize: 10
                    anchors.right: txtPrecioArticuloParaLista1.left
                    anchors.rightMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }

                BotonBarraDeHerramientas {
                    id: botonBajarListaFinal2
                    x: 415
                    y: 358
                    width: 14
                    height: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 3
                    source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                    anchors.bottom: parent.bottom
                    toolTip: ""
                    anchors.bottomMargin: 5
                    rotation: -90

                    onClic: listaArticulosEnOpcionesExtraListaPrecio.positionViewAtIndex(listaArticulosEnOpcionesExtraListaPrecio.count-1,0)
                }

                BotonBarraDeHerramientas {
                    id: botonSubirListaFinal2
                    x: 415
                    y: 110
                    width: 14
                    height: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 3
                    anchors.top: parent.top
                    anchors.topMargin: 46
                    source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                    toolTip: ""
                    rotation: 90

                    onClic: listaArticulosEnOpcionesExtraListaPrecio.positionViewAtIndex(0,0)
                }
                anchors.left: parent.left
            }

            BotonFlecha {
                id: botonflechaCerrarOpcionesAvanzadas
                x: 410
                y: 20
                opacidadRectPrincipal: 0.800
                z: 1
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 10
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaIzquierda.png"

                onClic: {
                    rectOpcionesExtrasAparecer.stop()
                    rectOpcionesExtrasDesaparecer.start()

                    rowBarraDeHerramientasListaDePrecios.enabled=true
                    botoncargardato1.enabled=true
                    txtArticuloParaLista.tomarElFocoP()
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                }
            }
        }
    }

    Rectangle {
        id: rectCargaRapidaDePrecios
        x: -4
        y: 1
        width: 450
        color: "#372f42"
        radius: 2
        //
        anchors.top: parent.top
        anchors.topMargin: -68
        Keys.onEscapePressed: {

            rectCargaRapidaDePreciosAparecer.stop()
            rectCargaRapidaDePreciosDesaparecer.start()

            rowBarraDeHerramientasListaDePrecios.enabled=true
            botoncargardato1.enabled=true
            btnCargaRapidaDePrecios.enabled=true
            txtArticuloParaLista.tomarElFocoP()
            menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
        }


        Rectangle {
            id: rectSombraOpcionesExtras1
            x: 333
            width: 17
            color: "#372f42"
            //
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.rightMargin: -12
            anchors.bottomMargin: 0
            z: -1
            anchors.right: parent.right
            opacity: 0.300
        }

        MouseArea {
            id: mouse_area2
            anchors.fill: parent

            Text {
                id: txtTituloOpcionesExtras1
                x: 20
                y: 10
                color: "#ffffff"
                text: qsTr("carga rapida de precios")
                font.pixelSize: 23
                anchors.top: parent.top
                anchors.topMargin: 10
                font.underline: false
                visible: true
                font.italic: false
                font.family: "Arial"
                font.bold: true
                anchors.leftMargin: 20
                anchors.left: parent.left
            }

            Flow {
                id: flowOpcionesExtras1
                x: 10
                y: 60
                height: flowOpcionesExtras1.implicitHeight+10
                spacing: 5
                anchors.top: rowBarraDeHerramientasListaDePrecios1.bottom
                anchors.topMargin: 10
                visible: true
                anchors.rightMargin: 10
                z: 5
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.left: parent.left

                ComboBoxGenerico {
                    id: cbxTipoCambioPrecio
                    width: 170
                    z: 110
                    textoTitulo: "Tipo de cambio de precio:"
                    modeloItems: modeloItemsTipoCambioPrecio
                    codigoValorSeleccion: "1"
                    textoComboBox: "Incremento por %"

                    ListModel{
                        id:modeloItemsTipoCambioPrecio
                        ListElement {
                            codigoItem: "1"
                            descripcionItem: "Incremento por %"
                        }
                        ListElement {
                            codigoItem: "2"
                            descripcionItem: "Decremento por %"
                        }
                    }
                }


                ComboBoxGenerico {
                    id: cbxTipoFiltroArticulos
                    width: 200
                    z: 109
                    textoTitulo: "Tipo de filtro de busqueda:"
                    modeloItems: modeloItemsTipoFiltroBusqueda
                    codigoValorSeleccion: "1"
                    textoComboBox: "Por rubros"
                    ListModel{
                        id:modeloItemsTipoFiltroBusqueda
                        ListElement {
                            codigoItem: "1"
                            descripcionItem: "Por rubros"
                        }
                        ListElement {
                            codigoItem: "2"
                            descripcionItem: "Por sub rubros"
                        }
                        ListElement {
                            codigoItem: "3"
                            descripcionItem: "Por tipo de IVA"
                        }
                        ListElement {
                            codigoItem: "4"
                            descripcionItem: "Por tipo de moneda"
                        }
                        ListElement {
                            codigoItem: "5"
                            descripcionItem: "Por proveedor"
                        }
                        ListElement {
                            codigoItem: "6"
                            descripcionItem: "Desde > hasta artículo"
                        }
                        ListElement {
                            codigoItem: "7"
                            descripcionItem: "Lista todos los artículos"
                        }
                    }
                    onSenialAlAceptarOClick: {

                        cbxListaRubrosCambioPrecio.visible=false
                        cbxListaRubrosCambioPrecio.cerrarComboBox()
                        cbxListaSubRubrosCambioPrecio.visible=false
                        cbxListaSubRubrosCambioPrecio.cerrarComboBox()
                        cbxListaIvasCambioPrecio.visible=false
                        cbxListaIvasCambioPrecio.cerrarComboBox()
                        cbxListaMonedasCambioPrecio.visible=false
                        cbxListaMonedasCambioPrecio.cerrarComboBox()
                        cbxListaProveedoresCambioPrecio.visible=false
                        cbxListaProveedoresCambioPrecio.cerrarComboBox()
                        txtCodigoArticuloDesdeCambioPrecio.visible=false
                        txtCodigoArticuloDesdeCambioPrecio.cerrarComboBox()
                        txtCodigoArticuloHastaCambioPrecio.visible=false
                        txtCodigoArticuloHastaCambioPrecio.cerrarComboBox()
                        btnAplicarFiltroArticulos.visible=false

                        cbxTipoCambioPrecio.cerrarComboBox()
                        cbListaDePrecioModificacionPrecios.cerrarComboBox()


                        if(cbxTipoFiltroArticulos.codigoValorSeleccion=="1"){
                            cbxListaRubrosCambioPrecio.visible=true
                            modeloListaPrecioArticulosACambiarDePrecio.clearArticulosListaPrecio()
                            modeloArticulosACambiarDePrecio.clear()
                        }else if(cbxTipoFiltroArticulos.codigoValorSeleccion=="2"){
                            cbxListaSubRubrosCambioPrecio.visible=true
                            modeloListaPrecioArticulosACambiarDePrecio.clearArticulosListaPrecio()
                            modeloArticulosACambiarDePrecio.clear()
                        }else if(cbxTipoFiltroArticulos.codigoValorSeleccion=="3"){
                            cbxListaIvasCambioPrecio.visible=true
                            modeloListaPrecioArticulosACambiarDePrecio.clearArticulosListaPrecio()
                            modeloArticulosACambiarDePrecio.clear()
                        }else if(cbxTipoFiltroArticulos.codigoValorSeleccion=="4"){
                            cbxListaMonedasCambioPrecio.visible=true
                            modeloListaPrecioArticulosACambiarDePrecio.clearArticulosListaPrecio()
                            modeloArticulosACambiarDePrecio.clear()
                        }else if(cbxTipoFiltroArticulos.codigoValorSeleccion=="5"){
                            cbxListaProveedoresCambioPrecio.visible=true
                            modeloListaPrecioArticulosACambiarDePrecio.clearArticulosListaPrecio()
                            modeloArticulosACambiarDePrecio.clear()
                        }else if(cbxTipoFiltroArticulos.codigoValorSeleccion=="6"){
                            txtCodigoArticuloDesdeCambioPrecio.visible=true
                            txtCodigoArticuloHastaCambioPrecio.visible=true
                            btnAplicarFiltroArticulos.visible=true
                            modeloListaPrecioArticulosACambiarDePrecio.clearArticulosListaPrecio()
                            modeloArticulosACambiarDePrecio.clear()

                        }else if(cbxTipoFiltroArticulos.codigoValorSeleccion=="7"){
                            modeloListaPrecioArticulosACambiarDePrecio.clearArticulosListaPrecio()
                            modeloListaPrecioArticulosACambiarDePrecio.buscarArticulosListaPrecio(" LA.codigoListaPrecio=",cbListaDePrecioModificacionPrecios.codigoValorSeleccion )
                            cargarArticulosAModificarElPrecio()
                        }
                    }
                }
                ComboBoxListaPrecios {
                    id: cbListaDePrecioModificacionPrecios
                    width: 240
                    textoTitulo: "Lista de precio:"
                    z: 108
                    codigoValorSeleccion: "1"
                    borrarDatosVidible: false
                    textoComboBox: modeloListasPrecios.retornaDescripcionListaPrecio("1")
                }
            }

            BotonFlecha {
                id: botonflechaCerrarCargaRapida
                x: 410
                y: 20
                opacidadRectPrincipal: 0.800
                anchors.top: parent.top
                anchors.topMargin: 20
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaIzquierda.png"
                anchors.rightMargin: 10
                z: 1
                anchors.right: parent.right
                onClic: {
                    rectCargaRapidaDePreciosAparecer.stop()
                    rectCargaRapidaDePreciosDesaparecer.start()
                    rowBarraDeHerramientasListaDePrecios.enabled=true
                    botoncargardato1.enabled=true
                    btnCargaRapidaDePrecios.enabled=true
                    txtArticuloParaLista.tomarElFocoP()
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
                }
            }

            Flow {
                id: rowBarraDeHerramientasListaDePrecios1
                //
                spacing: 15
                height: rowBarraDeHerramientasListaDePrecios1.implicitHeight
                anchors.top: txtTituloOpcionesExtras1.bottom
                anchors.topMargin: 20
                // anchors.bottom: rectContenedorListasDePrecios.top
                // anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 20



                BotonBarraDeHerramientas {
                    id: botonResetearFiltro
                    textoIconoVisible: false
                    source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevaListaDePrecios.png"
                    toolTip: "Nuevo filtro"
                    z: 8
                    onClic: {
                        modeloArticulosACambiarDePrecio.clear()
                        txtModificadorPorPorcentaje.textoInputBox="."
                        txtModificadorPorPorcentaje.tomarElFoco()
                    }
                }

                BotonBarraDeHerramientas {
                    id: botonGuardarNuevosPrecios
                    textoIconoTexto: "Guardar cambios"
                    source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
                    textoIconoVisible: false
                    toolTip: "Guardar nuevos precios"
                    z: 8
                    onClic: {
                        if(modeloArticulosACambiarDePrecio.count!=0){

                            txtMensajeInformacionFiltros.visible=true
                            txtMensajeInformacionFiltrosTimer.stop()
                            txtMensajeInformacionFiltrosTimer.start()

                            // if(modeloListaPrecioArticulos.eliminarArticulosListaPrecio(cbListaDePrecioModificacionPrecios.codigoValorSeleccion.trim())){

                            for(var i=0; i<modeloArticulosACambiarDePrecio.count;i++){
                                modeloListaPrecioArticulos.insertarArticulosListaPrecio(cbListaDePrecioModificacionPrecios.codigoValorSeleccion.trim(),modeloArticulosACambiarDePrecio.get(i).codigoArticulo, modeloArticulosACambiarDePrecio.get(i).nuevoPrecio,txtNombreDeUsuario.textoInputBox)
                            }

                            txtMensajeInformacionFiltros.color="#2f71a0"
                            txtMensajeInformacionFiltros.text="Precios actualizados ok"
                            modeloArticulosACambiarDePrecio.clear()
                            txtModificadorPorPorcentaje.textoInputBox="."
                            txtModificadorPorPorcentaje.tomarElFoco()
                            /*   }else{
                                txtMensajeInformacionFiltros.color="#d93e3e"
                                txtMensajeInformacionFiltros.text="No se pudieron actualizar los precios"
                                txtModificadorPorPorcentaje.tomarElFoco()
                            }*/
                        }
                    }
                }

                Text {
                    id: txtMensajeInformacionFiltros
                    y: 7
                    color: "#d93e3e"
                    text: qsTr("Información:")
                    //
                    font.pixelSize: 14
                    style: Text.Normal
                    visible: false
                    styleColor: "#ffffff"
                    font.family: "Arial"
                    font.bold: true
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignTop
                }


            }

            Timer{
                id:txtMensajeInformacionFiltrosTimer
                repeat: false
                interval: 5000
                onTriggered: {

                    txtMensajeInformacionFiltros.visible=false
                    txtMensajeInformacionFiltros.color="#d93e3e"

                }
            }

            Flow {
                id: flow2
                height: flow2.implicitHeight+10
                z: 4
                anchors.top: flowOpcionesExtras1.bottom
                anchors.topMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 10

                ComboBoxListaProveedores {
                    id: cbxListaProveedoresCambioPrecio
                    width: 300
                    textoTitulo: "Proveedores:"
                    visible: false
                    onSenialAlAceptarOClick: {
                        modeloListaPrecioArticulosACambiarDePrecio.clearArticulosListaPrecio()
                        modeloListaPrecioArticulosACambiarDePrecio.buscarArticulosListaPrecio("  LA.codigoListaPrecio='"+cbListaDePrecioModificacionPrecios.codigoValorSeleccion+"'  and   A.codigoProveedor=",cbxListaProveedoresCambioPrecio.codigoValorSeleccion )
                        cargarArticulosAModificarElPrecio()

                    }
                    onClicBorrarDatos: {
                        modeloListaPrecioArticulosACambiarDePrecio.clearArticulosListaPrecio()
                        modeloArticulosACambiarDePrecio.clear()
                    }
                }
                ComboBoxListaRubros {
                    id: cbxListaRubrosCambioPrecio
                    width: 300
                    textoTitulo: "Rubros:"
                    visible: true
                    onSenialAlAceptarOClick: {
                        modeloListaPrecioArticulosACambiarDePrecio.clearArticulosListaPrecio()
                        modeloListaPrecioArticulosACambiarDePrecio.buscarArticulosListaPrecio("  LA.codigoListaPrecio='"+cbListaDePrecioModificacionPrecios.codigoValorSeleccion+"'  and  RU.codigoRubro=",cbxListaRubrosCambioPrecio.codigoValorSeleccion)
                        cargarArticulosAModificarElPrecio()
                    }
                }
                ComboBoxListaSubRubrosXRubros {
                    id: cbxListaSubRubrosCambioPrecio
                    width: 300
                    textoTitulo: "Sub rubros:"
                    visible: false
                    onSenialAlAceptarOClick: {
                        modeloListaPrecioArticulosACambiarDePrecio.clearArticulosListaPrecio()
                        modeloListaPrecioArticulosACambiarDePrecio.buscarArticulosListaPrecio(" LA.codigoListaPrecio='"+cbListaDePrecioModificacionPrecios.codigoValorSeleccion+"'  and   A.codigoSubRubro=",cbxListaSubRubrosCambioPrecio.codigoValorSeleccion )
                        cargarArticulosAModificarElPrecio()
                    }
                }
                ComboBoxListaIvas {
                    id: cbxListaIvasCambioPrecio
                    width: 160
                    textoTitulo: "Ivas:"
                    visible: false
                    onSenialAlAceptarOClick: {
                        modeloListaPrecioArticulosACambiarDePrecio.clearArticulosListaPrecio()
                        modeloListaPrecioArticulosACambiarDePrecio.buscarArticulosListaPrecio(" LA.codigoListaPrecio='"+cbListaDePrecioModificacionPrecios.codigoValorSeleccion+"'  and   A.codigoIva=",cbxListaIvasCambioPrecio.codigoValorSeleccion )
                        cargarArticulosAModificarElPrecio()
                    }
                }
                ComboBoxListaMonedas {
                    id: cbxListaMonedasCambioPrecio
                    width: 160
                    textoTitulo: "Monedas:"
                    visible: false
                    onSenialAlAceptarOClick: {
                        modeloListaPrecioArticulosACambiarDePrecio.clearArticulosListaPrecio()
                        modeloListaPrecioArticulosACambiarDePrecio.buscarArticulosListaPrecio(" LA.codigoListaPrecio='"+cbListaDePrecioModificacionPrecios.codigoValorSeleccion+"'  and  A.codigoMoneda=",cbxListaMonedasCambioPrecio.codigoValorSeleccion )

                        //" LA.codigoListaPrecio=",cbListaDePrecioModificacionPrecios.codigoValorSeleccion )
                        cargarArticulosAModificarElPrecio()
                    }
                }

                TextInputP {
                    id: txtCodigoArticuloDesdeCambioPrecio
                    width: 300
                    z: 1
                    tamanioRectPrincipalCombobox: 320
                    botonNuevoTexto: "Nuevo artículo..."
                    utilizaListaDesplegable: true
                    enFocoSeleccionarTodo: true
                    textoInputBox: ""
                    botonBuscarTextoVisible: false
                    largoMaximo: 30
                    textoDeFondo: ""
                    textoTitulo: "Desde artículo:"
                    colorDeTitulo: "#dbd8d8"
                    botonNuevoVisible:{
                        if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos") && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearArticulos")){
                            true
                        }else{
                            false
                        }
                    }
                    visible: false
                    textoTituloFiltro: "Buscar por: descripción, proveedor, iva o moneda"
                    tamanioRectPrincipalComboboxAlto: {
                        if(checkBoxActivoVisible){
                            400
                        }else{
                            300
                        }
                    }
                    checkBoxActivoVisible: true
                    checkBoxActivoTexto: "Incluir artículos inactivos"
                    listviewModel:modeloArticulosFiltrosListaPrecio2
                    listviewDelegate: Delegate_ListaArticulosFiltros{
                        onSenialAlAceptarOClick: {
                            txtCodigoArticuloDesdeCambioPrecio.textoInputBox=codigoValorSeleccion
                            txtCodigoArticuloDesdeCambioPrecio.tomarElFocoP()
                            txtCodigoArticuloDesdeCambioPrecio.cerrarComboBox()
                        }
                        onKeyEscapeCerrar: {
                            txtCodigoArticuloDesdeCambioPrecio.tomarElFocoP()
                            txtCodigoArticuloDesdeCambioPrecio.cerrarComboBox()
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

                        modeloArticulosFiltrosListaPrecio2.clearArticulos()
                        modeloArticulosFiltrosListaPrecio2.buscarArticulo(consultaSqlArticulo,"1",0)

                        if(modeloArticulosFiltrosListaPrecio2.rowCount()!=0){
                            tomarElFocoResultado()
                        }
                    }
                    onTabulacion: txtCodigoArticuloHastaCambioPrecio.tomarElFocoP()
                    onEnter: txtCodigoArticuloHastaCambioPrecio.tomarElFocoP()
                }
                TextInputP {
                    id: txtCodigoArticuloHastaCambioPrecio
                    width: 300
                    z: 0
                    tamanioRectPrincipalCombobox: 320
                    botonNuevoTexto: "Nuevo artículo..."
                    utilizaListaDesplegable: true
                    enFocoSeleccionarTodo: true
                    textoInputBox: ""
                    botonBuscarTextoVisible: false
                    largoMaximo: 30
                    textoDeFondo: ""
                    textoTitulo: "Hasta artículo:"
                    colorDeTitulo: "#dbd8d8"
                    botonNuevoVisible:{
                        if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos") && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearArticulos")){
                            true
                        }else{
                            false
                        }
                    }
                    visible: false
                    textoTituloFiltro: "Buscar por: descripción, proveedor, iva o moneda"
                    tamanioRectPrincipalComboboxAlto: {
                        if(checkBoxActivoVisible){
                            400
                        }else{
                            300
                        }
                    }
                    checkBoxActivoVisible: true
                    checkBoxActivoTexto: "Incluir artículos inactivos"
                    listviewModel:modeloArticulosFiltrosListaPrecio3
                    listviewDelegate: Delegate_ListaArticulosFiltros{
                        onSenialAlAceptarOClick: {
                            txtCodigoArticuloHastaCambioPrecio.textoInputBox=codigoValorSeleccion
                            txtCodigoArticuloHastaCambioPrecio.tomarElFocoP()
                            txtCodigoArticuloHastaCambioPrecio.cerrarComboBox()
                        }
                        onKeyEscapeCerrar: {
                            txtCodigoArticuloHastaCambioPrecio.tomarElFocoP()
                            txtCodigoArticuloHastaCambioPrecio.cerrarComboBox()
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

                        modeloArticulosFiltrosListaPrecio3.clearArticulos()
                        modeloArticulosFiltrosListaPrecio3.buscarArticulo(consultaSqlArticulo,"1",0)

                        if(modeloArticulosFiltrosListaPrecio3.rowCount()!=0){
                            tomarElFocoResultado()
                        }
                    }
                    onTabulacion: txtCodigoArticuloDesdeCambioPrecio.tomarElFocoP()
                    onEnter: txtCodigoArticuloDesdeCambioPrecio.tomarElFocoP()
                }
            }

            BotonPaletaSistema {
                id: btnAplicarFiltroArticulos
                x: 310
                y: 189
                text: "Apicar filtro"
                anchors.bottom: rectListasDeArticulosACambiarDePrecio.top
                anchors.bottomMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 10
                visible: false
                onClicked: {
                    if(txtCodigoArticuloDesdeCambioPrecio.textoInputBox.trim()!="" && txtCodigoArticuloHastaCambioPrecio.textoInputBox.trim()!=""){

                        modeloListaPrecioArticulosACambiarDePrecio.clearArticulosListaPrecio()

                        if(modeloconfiguracion.retornaValorConfiguracion("MODO_ARTICULO")=="1"){
                            modeloListaPrecioArticulosACambiarDePrecio.buscarArticulosListaPrecio(" LA.codigoListaPrecio='"+cbListaDePrecioModificacionPrecios.codigoValorSeleccion+"'  and   A.codigoArticulo between CONVERT("+txtCodigoArticuloDesdeCambioPrecio.textoInputBox.trim()+", SIGNED INTEGER) and CONVERT("+txtCodigoArticuloHastaCambioPrecio.textoInputBox.trim()+", SIGNED INTEGER) and 1=","1")
                        }else{
                            modeloListaPrecioArticulosACambiarDePrecio.buscarArticulosListaPrecio(" LA.codigoListaPrecio='"+cbListaDePrecioModificacionPrecios.codigoValorSeleccion+"'  and   A.codigoArticulo between '"+txtCodigoArticuloDesdeCambioPrecio.textoInputBox.trim()+"' and ", txtCodigoArticuloHastaCambioPrecio.textoInputBox.trim())
                        }


                        cargarArticulosAModificarElPrecio()

                    }else{
                        if(txtCodigoArticuloDesdeCambioPrecio.textoInputBox.trim()==""){
                            txtCodigoArticuloDesdeCambioPrecio.tomarElFocoP()
                        }else if(txtCodigoArticuloHastaCambioPrecio.textoInputBox.trim()==""){
                            txtCodigoArticuloHastaCambioPrecio.tomarElFocoP()
                        }
                    }
                }
            }

            ListModel{
                id:modeloArticulosACambiarDePrecio
            }
            Rectangle {
                id: rectListasDeArticulosACambiarDePrecio
                x: 5
                color: "#64b7b6b6"
                radius: 3
                clip: true
                //
                anchors.top: flow2.bottom
                anchors.topMargin: 10
                ListView {
                    id: listaArticulosACambiarPrecioOpcionesExtra
                    highlightRangeMode: ListView.NoHighlightRange
                    anchors.top: parent.top
                    boundsBehavior: Flickable.DragAndOvershootBounds
                    highlightFollowsCurrentItem: true
                    anchors.right: parent.right
                    delegate: ListaArticulosACambiarDePrecio {
                    }
                    snapMode: ListView.NoSnap
                    anchors.bottomMargin: 25
                    anchors.bottom: parent.bottom
                    spacing: 1
                    z: 1
                    clip: true
                    flickableDirection: Flickable.VerticalFlick
                    anchors.leftMargin: 1
                    Rectangle {
                        id: scrollbarlistaArticulosEnOpcionesExtraListaPrecio1
                        y: listaArticulosACambiarPrecioOpcionesExtra.visibleArea.yPosition * listaArticulosACambiarPrecioOpcionesExtra.height+5
                        width: 10
                        height: listaArticulosACambiarPrecioOpcionesExtra.visibleArea.heightRatio * listaArticulosACambiarPrecioOpcionesExtra.height+18
                        color: "#000000"
                        radius: 2
                        //
                        anchors.rightMargin: 4
                        visible: true
                        z: 1
                        anchors.right: listaArticulosACambiarPrecioOpcionesExtra.right
                        opacity: 0.500
                    }
                    keyNavigationWraps: true
                    anchors.left: parent.left
                    interactive: true
                    //
                    anchors.topMargin: 70
                    anchors.rightMargin: 1
                    model: modeloArticulosACambiarDePrecio
                }

                TextInputSimple {
                    id: txtModificadorPorPorcentaje
                    x: 3
                    y: -1
                    //   width: 130
                    enFocoSeleccionarTodo: true
                    textoInputBox: ""
                    anchors.top: parent.top
                    anchors.topMargin: 7
                    anchors.rightMargin: 5
                    visible: true
                    botonBuscarTextoVisible: false
                    inputMask: "000.00;"
                    largoMaximo: 45
                    textoTitulo: "Porcentaje:"
                    anchors.right: btnAplicarModificacionPrecio.left
                    colorDeTitulo: "#dbd8d8"
                }

                BotonBarraDeHerramientas {
                    id: botonBajarListaFinal3
                    x: 415
                    y: 358
                    width: 14
                    height: 14
                    source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                    anchors.bottom: parent.bottom
                    anchors.rightMargin: 3
                    toolTip: ""
                    anchors.bottomMargin: 5
                    rotation: -90
                    anchors.right: parent.right
                    onClic: listaArticulosACambiarPrecioOpcionesExtra.positionViewAtIndex(listaArticulosACambiarPrecioOpcionesExtra.count-1,0)
                }








                BotonBarraDeHerramientas {
                    id: botonSubirListaFinal3
                    x: 423
                    y: 23
                    width: 14
                    height: 14
                    anchors.top: parent.top
                    anchors.topMargin: 50
                    source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                    anchors.rightMargin: 3
                    toolTip: ""
                    rotation: 90
                    anchors.right: parent.right
                    onClic: listaArticulosACambiarPrecioOpcionesExtra.positionViewAtIndex(0,0)
                }

                BotonPaletaSistema {
                    id: btnAplicarModificacionPrecio
                    text: "Modificar precio"
                    anchors.top: parent.top
                    anchors.topMargin: 15
                    z: 2
                    anchors.rightMargin: 5
                    visible: true
                    anchors.right: parent.right
                    onClicked: {

                        if(modeloArticulosACambiarDePrecio.count!=0){
                            if(txtModificadorPorPorcentaje.textoInputBox.trim()!="0.00" && txtModificadorPorPorcentaje.textoInputBox.trim()!="." && txtModificadorPorPorcentaje.textoInputBox.trim()!=".0" && txtModificadorPorPorcentaje.textoInputBox.trim()!="0.0" && txtModificadorPorPorcentaje.textoInputBox.trim()!=".00" && txtModificadorPorPorcentaje.textoInputBox.trim()!="00.00"&& txtModificadorPorPorcentaje.textoInputBox.trim()!="0." && txtModificadorPorPorcentaje.textoInputBox.trim()!="00." && txtModificadorPorPorcentaje.textoInputBox.trim()!="000."&& txtModificadorPorPorcentaje.textoInputBox.trim()!="000.00"){
                                calcularNuevoPrecio()
                            }else{
                                txtModificadorPorPorcentaje.tomarElFoco()
                            }
                        }
                    }
                }

                CheckBox {
                    id: chbRedondeoPrecioNuevo
                    colorTexto: "#dbd8d8"
                    chekActivo: false
                    buscarActivo: false
                    textoValor: "Redondear nuevo precio"
                    anchors.right: txtModificadorPorPorcentaje.left
                    anchors.rightMargin: 10
                    anchors.top: parent.top
                    anchors.topMargin: 7
                }
                anchors.bottom: parent.bottom
                anchors.rightMargin: 5
                anchors.bottomMargin: 5
                z: 2
                anchors.right: parent.right
                anchors.leftMargin: 5
                anchors.left: parent.left
            }
        }
        anchors.bottom: parent.bottom
        visible: true
        anchors.bottomMargin: -5
        z: 7
        anchors.leftMargin: -515
        anchors.left: parent.left
    }


    /// Carga los nuevos precios en la lista
    function calcularNuevoPrecio(){
        _porcentaje=parseFloat(txtModificadorPorPorcentaje.textoInputBox.trim())

        for(var i=0; i<modeloArticulosACambiarDePrecio.count;i++){

            var decimalesRedondeo=2;

            if(chbRedondeoPrecioNuevo.chekActivo){
                decimalesRedondeo=0;
            }

            if(cbxTipoCambioPrecio.codigoValorSeleccion=="1"){

                nuevoPrecioAAcomodar=(modeloArticulosACambiarDePrecio.get(i).precioActual*((_porcentaje/100)+1)).toFixed(decimalesRedondeo);

                modeloArticulosACambiarDePrecio.setProperty(i,"nuevoPrecio", nuevoPrecioAAcomodar.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")));

            }else if(cbxTipoCambioPrecio.codigoValorSeleccion=="2"){

                nuevoPrecioAAcomodar=(modeloArticulosACambiarDePrecio.get(i).precioActual-((modeloArticulosACambiarDePrecio.get(i).precioActual*((_porcentaje/100)+1))-modeloArticulosACambiarDePrecio.get(i).precioActual)).toFixed(decimalesRedondeo);

                modeloArticulosACambiarDePrecio.setProperty(i,"nuevoPrecio", nuevoPrecioAAcomodar.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")));
            }
        }

    }
}
