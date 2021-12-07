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



Rectangle {
    id: rectPrincipalMantenimientoArticulos
    width: 900
    height: 600
    color: "#ffffff"
    radius: 8
    //

    property alias botonNuevoArticuloVisible: botonNuevoArticulo.visible
    property alias botonEliminarArticuloVisible: botonEliminarArticulo.visible
    property alias botonGuardarArticuloVisible: botonGuardarArticulo.visible
    property alias codigoArticuloInputMask: txtCodigoArticulo.inputMask


    Rectangle {
        id: rectContenedorArticulos
        x: 0
        y: 30
        color: "#494747"
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
            z: 1
            spacing: 7
            anchors.right: rectCodigosDeBarra.left
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 10

            TextInputSimple {
                id: txtCodigoArticulo
                x: 53
                y: -36
             //   width: 280
                enFocoSeleccionarTodo: true
                textoDeFondo: ""
                largoMaximo: 30
                botonBuscarTextoVisible: true
                botonBorrarTextoVisible: true
                textoTitulo: "Código interno:"
                textoInputBox: ""
                onClicEnBusqueda: {

                    var valorArticuloInterno=modeloArticulos.existeArticulo(txtCodigoArticulo.textoInputBox.trim());
                    modeloArticulos.clearArticulos()
                    modeloArticulos.buscarArticulo("codigoArticulo=",valorArticuloInterno,0)

                    if(valorArticuloInterno!=""){
                        txtCodigoArticulo.textoInputBox=valorArticuloInterno
                        listaDeArticulos.currentIndex=0;

                    }else{

                        txtCodigoArticulo.tomarElFoco()
                    }

                }

                onEnter: {
                    var valorArticuloInterno=modeloArticulos.existeArticulo(txtCodigoArticulo.textoInputBox.trim());

                    if(valorArticuloInterno!=""){
                        txtCodigoArticulo.textoInputBox=valorArticuloInterno
                        modeloArticulos.clearArticulos()
                        modeloArticulos.buscarArticulo("codigoArticulo=",valorArticuloInterno,0)

                        listaDeArticulos.currentIndex=0;

                    }


                    txtDescripcionArticulo.tomarElFoco()
                }
                onTabulacion:     txtDescripcionArticulo.tomarElFoco()

            }

            TextInputSimple {
                id: txtDescripcionArticulo
                x: 37
                y: 90
             //   width: 350
                enFocoSeleccionarTodo: true
                botonBuscarTextoVisible: true
                textoTitulo: "Descripción:"
                textoInputBox: ""
                onClicEnBusqueda: {

                    modeloArticulos.clearArticulos()
                    modeloArticulos.buscarArticulo("descripcionArticulo rlike",txtDescripcionArticulo.textoInputBox.trim(),0)

                    listaDeArticulos.currentIndex=0;
                }

                onEnter: {
                    txtProveedorArticulo.tomarElFoco()
                }
                onTabulacion:     txtProveedorArticulo.tomarElFoco()
            }


            ComboBoxListaProveedores {
                id: txtProveedorArticulo
                width: 260
                textoComboBox: ""
                botonBuscarTextoVisible: true
                textoTitulo: "Proveedores:"
                z:111
                onClicEnBusqueda: {
                    modeloArticulos.clearArticulos()
                    modeloArticulos.buscarArticulo("codigoProveedor =",txtProveedorArticulo.codigoValorSeleccion.toString(),0)

                    listaDeArticulos.currentIndex=0;
                }
                onEnter: txtCodigoDeBarras.tomarElFoco()


            }

            ComboBoxListaIvas {
                id: txtListaDeIvas
                x: 292
                y: 133
                width: 110
                z: 110
                textoComboBox: modeloListaIvas.retornaDescripcionIva(1)
                codigoValorSeleccion: "1"
                botonBuscarTextoVisible: true
                textoTitulo: "Tipo de I.V.A.:"
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("articulosUsaTipoIVA")
                onClicEnBusqueda: {
                    modeloArticulos.clearArticulos()
                    modeloArticulos.buscarArticulo("codigoIva =",txtListaDeIvas.codigoValorSeleccion.trim(),0)

                    listaDeArticulos.currentIndex=0;
                }
                onEnter: txtCodigoDeBarras.tomarElFoco()
            }

            ComboBoxListaMonedas {
                id: txtMonedaArticulo
                x: 359
                y: 48
                width: 110
                z: 109
                textoTitulo: "Moneda:"
                botonBuscarTextoVisible: true
                codigoValorSeleccion: modeloconfiguracion.retornaValorConfiguracion("MONEDA_DEFAULT")
                textoComboBox: modeloListaMonedas.retornaDescripcionMoneda(txtMonedaArticulo.codigoValorSeleccion)
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("articulosUsaMoneda")
                onClicEnBusqueda: {
                    modeloArticulos.clearArticulos()
                    modeloArticulos.buscarArticulo("codigoMoneda =",txtMonedaArticulo.codigoValorSeleccion.trim(),0)

                    listaDeArticulos.currentIndex=0;
                }
                onEnter: txtCodigoDeBarras.tomarElFoco()
            }

            TextInputSimple {
                id: txtDescripcionExtendidaArticulo
                x: 29
                y: 86
            //    width: 450
                largoMaximo: 80
                botonBorrarTextoVisible: true
                textoDeFondo: "descripcion extendida del articulo"
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                botonBuscarTextoVisible: true
                textoTitulo: "Descripción extendida:"
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("articulosUsaDescripcionExtendida")

                onEnter: txtCodigoDeBarras.tomarElFoco()

                onTabulacion: txtCodigoDeBarras.tomarElFoco()

                onClicEnBusqueda: {

                    modeloArticulos.clearArticulos()
                    modeloArticulos.buscarArticulo("descripcionExtendida rlike",txtDescripcionExtendidaArticulo.textoInputBox.trim(),0)

                    listaDeArticulos.currentIndex=0;
                }

            }

            ComboBoxListaPrecios {
                id: cbListaDePrecioDeArticuloSeleccionado
                x: 371
                y: 219
                width: 240
                z: 108
                textoTitulo: "Lista de precio:"
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("articulosUsaListaDePrecio")
                onEnter: {

                    txtPrecioArticuloSeleccionado.tomarElFoco()
                }
            }

            TextInputSimple {
                id: txtPrecioArticuloSeleccionado
            //    width: 150
                enFocoSeleccionarTodo: true
                textoInputBox: ""+modeloconfiguracion.retornaCantidadDecimalesString()+""
                botonBuscarTextoVisible: false
                inputMask: "00000000"+modeloconfiguracion.retornaCantidadDecimalesString()+";"
                largoMaximo: 45
                textoTitulo: "Precio:"
                colorDeTitulo: "#dbd8d8"
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("articulosUsaListaDePrecio")


                onEnter: txtCodigoDeBarras.tomarElFoco()

                onTabulacion: txtCodigoDeBarras.tomarElFoco()
            }


            TextInputSimple {
                id: txtCodigoDeBarras
                x: 52
                y: -35
            //    width: 280
                textoInputBox: ""
                botonBuscarTextoVisible: false
                inputMask: ""
                largoMaximo: 30
                botonBorrarTextoVisible: false
                textoTitulo: "Código de barras:"
                enabled: true
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("articulosUsaCodigoBarras")

                onEnter: {

                    if(txtCodigoDeBarras.textoInputBox.trim().length>6){
                        if(modeloArticulosCodigoDeBarras.count!=0){
                            var valor=true;
                            for(var i=0; i<modeloArticulosCodigoDeBarras.count;i++){
                                if(modeloArticulosCodigoDeBarras.get(i).itemCodigoDeBarrasAgregado==txtCodigoDeBarras.textoInputBox.trim()){
                                    valor=false;
                                    break;
                                }
                            }

                            if(valor==true){
                                modeloArticulosCodigoDeBarras.append({
                                                                         itemCodigoDeBarrasAgregado:txtCodigoDeBarras.textoInputBox.trim()
                                                                     })
                                txtCodigoDeBarras.textoInputBox=""
                            }
                        }else{
                            modeloArticulosCodigoDeBarras.append({
                                                                     itemCodigoDeBarrasAgregado:txtCodigoDeBarras.textoInputBox.trim()
                                                                 })
                            txtCodigoDeBarras.textoInputBox=""
                        }
                    }
                }
                onTabulacion: {
                    txtCantidadMinimaStock.tomarElFoco()
                }
            }

            TextInputSimple {
                id: txtCantidadMinimaStock
                x: 54
                y: -26
            //    width: 120
                inputMask: "000000000;"
                enFocoSeleccionarTodo: true
                textoInputBox: "0"
                botonBuscarTextoVisible: true
                textoDeFondo: ""
                largoMaximo: 9
                botonBorrarTextoVisible: true
                textoTitulo: "Cantidad mínima:"
                onTabulacion: cbxListaSubRubrosArticulos.tomarElFoco()
                onEnter: cbxListaSubRubrosArticulos.tomarElFoco()
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("articulosUsaCantidadMinima")

                onClicEnBusqueda: {

                    modeloArticulos.clearArticulos()
                    modeloArticulos.buscarArticulo("cantidadMinimaStock =",txtCantidadMinimaStock.textoInputBox.trim(),0)
                    listaDeArticulos.currentIndex=0;
                }
            }

           /* ComboBoxListaSubRubros {
                id: cbxListaSubRubrosArticulos
                x: 124
                y: 258
                width: 200
                codigoValorSeleccion: "1"
                textoComboBox: modeloListaSubRubros.retornaDescripcionSubRubro(codigoValorSeleccion)
                botonBuscarTextoVisible: true
                textoTitulo: "Sub Rubros:"
                onTabulacion: txtCodigoArticulo.tomarElFoco()
                onEnter: txtCodigoArticulo.tomarElFoco()
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("articulosUsaSubRubro")

                onClicEnBusqueda: {
                    modeloArticulos.clearArticulos()
                    modeloArticulos.buscarArticulo("codigoSubRubro =",cbxListaSubRubrosArticulos.codigoValorSeleccion,0)
                    listaDeArticulos.currentIndex=0;
                }

            }*/
            ComboBoxListaSubRubrosXRubros {
                id: cbxListaSubRubrosArticulos
                x: 124
                y: 258
                width: 200
                codigoValorSeleccion: "1"
                textoComboBox: modeloListaSubRubros.retornaDescripcionSubRubro(codigoValorSeleccion)
                botonBuscarTextoVisible: true
                textoTitulo: "Sub Rubros:"
                onTabulacion: txtCodigoArticulo.tomarElFoco()
                onEnter: txtCodigoArticulo.tomarElFoco()
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("articulosUsaSubRubro")

                onClicEnBusqueda: {
                    modeloArticulos.clearArticulos()
                    modeloArticulos.buscarArticulo("codigoSubRubro =",cbxListaSubRubrosArticulos.codigoValorSeleccion,0)
                    listaDeArticulos.currentIndex=0;
                }

            }

            CheckBox {
                id: chbArticuloActivo
                x: 315
                y: 233
                buscarActivo: true
                chekActivo: true
                colorTexto: "#dbd8d8"
                textoValor: "Activo"
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("articulosUsaCheckActivo")
                onClicEnBusqueda: {

                    var _activo="0"
                    if(chekActivo)
                        _activo="1"

                    modeloArticulos.clearArticulos()
                    modeloArticulos.buscarArticulo("activo =",_activo,0)
                    listaDeArticulos.currentIndex=0;

                }
            }
        }

        Rectangle{
            id: rectangle2

            color: {
                if(listaDeArticulos.count==0){
                    "#C4C4C6"
                }else{
                    "#27abb4"
                }
            }
            radius: 3
            clip: true
            //
            anchors.top: flow1.bottom
            anchors.topMargin: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 20
            ListView {
                id: listaDeArticulos
                clip: true
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottomMargin: 25
                boundsBehavior: Flickable.DragAndOvershootBounds
                highlightFollowsCurrentItem: true
                interactive: {
                    if(listaDeArticulos.count>5){
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
                delegate:  ListaArticulos{}
                model: modeloArticulos

                Rectangle {
                    id: scrollbarlistaDeArticulos
                    y: listaDeArticulos.visibleArea.yPosition * listaDeArticulos.height+5
                    width: 10
                    color: "#000000"
                    height: listaDeArticulos.visibleArea.heightRatio * listaDeArticulos.height+18
                    radius: 2
                    anchors.right: listaDeArticulos.right
                    anchors.rightMargin: 4
                    z: 1
                    opacity: 0.500
                    visible: {
                        if(listaDeArticulos.count>5){
                            true
                        }else{
                            false
                        }
                    }
                    //
                }

            }

            Text {
                id: txtCantidadDeItemsTitulo
                x: 10
                width: txtCantidadDeItemsTitulo.implicitWidth
                height: 15
                color: "#000000"
                text: qsTr("Cantidad de artículos:")
                anchors.top: parent.top
                anchors.topMargin: 5
                font.family: "Arial"
                font.pointSize: 10
                font.bold: false
                anchors.left: parent.left
                anchors.leftMargin: 5
                //
            }

            Text {
                id: txtCantidadDeItemsValor
                x: 127
                width: 37
                height: 15
                color: "#000000"
                text: listaDeArticulos.count
                anchors.top: parent.top
                anchors.topMargin: 5
                font.family: "Arial"
                anchors.leftMargin: 5
                //
                font.bold: false
                font.pointSize: 10
                anchors.left: txtCantidadDeItemsTitulo.right
            }

            BotonBarraDeHerramientas {
                id: botonSubirListaFinal
                x: 848
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
                visible: scrollbarlistaDeArticulos.visible

                onClic: listaDeArticulos.positionViewAtIndex(0,0)
            }

            BotonBarraDeHerramientas {
                id: botonBajarListaFinal
                x: 848
                y: 159
                width: 14
                height: 14
                anchors.right: parent.right
                anchors.rightMargin: 3
                toolTip: ""
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                rotation: -90
                visible: scrollbarlistaDeArticulos.visible
                onClic: listaDeArticulos.positionViewAtIndex(listaDeArticulos.count-1,0)

            }
        }

        Rectangle {
            id: rectCodigosDeBarra
            color: "#C4C4C6"
            radius: 3
            width: {
                if(visible){
                    365
                }else{
                    0
                }
            }
            //
            anchors.bottom: btnCargarArticulosBatch.top
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 10
            visible: modeloControlesMantenimientos.retornaValorMantenimiento("articulosUsaCodigoBarras")

            ListView {
                id: listaDeArticulosBarrar
                clip: true
                highlightRangeMode: ListView.NoHighlightRange
                anchors.top: parent.top
                boundsBehavior: Flickable.DragAndOvershootBounds
                highlightFollowsCurrentItem: true
                anchors.right: parent.right
                delegate: ListaArticulosBarras {
                }
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
                anchors.topMargin: 25
                anchors.rightMargin: 1
                model: modeloArticulosCodigoDeBarras

                Rectangle {
                    id: scrollbarlistaDeArticulosBarrar
                    y: listaDeArticulosBarrar.visibleArea.yPosition * listaDeArticulosBarrar.height+5
                    width: 10
                    color: "#000000"
                    height: listaDeArticulosBarrar.visibleArea.heightRatio * listaDeArticulosBarrar.height+18
                    radius: 2
                    anchors.right: listaDeArticulosBarrar.right
                    anchors.rightMargin: 4
                    z: 1
                    opacity: 0.500
                    visible: true
                    //
                }
            }

            Text {
                id: txtTituloListaCodigosDeBarra
                text: qsTr("Barras: "+modeloArticulosCodigoDeBarras.count)
                anchors.top: parent.top
                anchors.topMargin: 5
                font.family: "Arial"
                //
                font.pointSize: 10
                font.bold: false
                anchors.left: parent.left
                anchors.leftMargin: 5
            }

            BotonBarraDeHerramientas {
                id: botonSubirListaFinal1
                x: 328
                y: 59
                width: 14
                height: 14
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.top: parent.top
                anchors.topMargin: 5
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                toolTip: ""
                rotation: 90
                onClic: listaDeArticulosBarrar.positionViewAtIndex(0,0)
            }

            BotonBarraDeHerramientas {
                id: botonBajarListaFinal1
                x: 328
                y: 238
                width: 14
                height: 14
                anchors.right: parent.right
                anchors.rightMargin: 3
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                anchors.bottom: parent.bottom
                toolTip: ""
                anchors.bottomMargin: 5
                rotation: -90

                onClic: listaDeArticulosBarrar.positionViewAtIndex(listaDeArticulosBarrar.count-1,0)
            }
        }

        BotonPaletaSistema {
            id: btnFiltrarArticulos
            y: 53
            text: "Filtrar artículos"
            anchors.bottom: rectangle2.top
            anchors.bottomMargin: 10
            anchors.leftMargin: 20
            anchors.left: parent.left

            onClicked: {

                var consultaSql="";

               if(txtCodigoArticulo.textoInputBox.trim()!=""){
                    consultaSql+=" codigoArticulo = '"+txtCodigoArticulo.textoInputBox.trim()+"' and ";
                }
                if(txtDescripcionArticulo.textoInputBox.trim()!=""){
                    consultaSql+=" descripcionArticulo rlike '"+txtDescripcionArticulo.textoInputBox.trim()+"' and "
                }
                if(txtProveedorArticulo.codigoValorSeleccion.trim()!="" && txtProveedorArticulo.codigoValorSeleccion.trim()!='-1'){
                    consultaSql+=" codigoProveedor = '"+txtProveedorArticulo.codigoValorSeleccion.trim()+"' and "
               }
                if(txtListaDeIvas.codigoValorSeleccion.trim()!="" && txtListaDeIvas.codigoValorSeleccion.trim()!="-1"){
                    consultaSql+=" codigoIva = '"+txtListaDeIvas.codigoValorSeleccion.trim()+"' and "
                }
                if(txtMonedaArticulo.codigoValorSeleccion.trim()!="" && txtMonedaArticulo.codigoValorSeleccion.trim()!="-1"){
                    consultaSql+=" codigoMoneda = '"+txtMonedaArticulo.codigoValorSeleccion.trim()+"' and "
                }
                if(txtDescripcionExtendidaArticulo.textoInputBox.trim()!=""){
                    consultaSql+=" descripcionExtendida rlike '"+txtDescripcionExtendidaArticulo.textoInputBox.trim()+"' and "
                }
                if(txtCantidadMinimaStock.textoInputBox.trim()!=""){
                    consultaSql+=" cantidadMinimaStock = '"+txtCantidadMinimaStock.textoInputBox.trim()+"' and "
                }
                if(cbxListaSubRubrosArticulos.codigoValorSeleccion.trim()!="" && cbxListaSubRubrosArticulos.codigoValorSeleccion.trim()!="-1"){
                    consultaSql+=" codigoSubRubro = '"+cbxListaSubRubrosArticulos.codigoValorSeleccion.trim()+"' and "
                }
                if(chbArticuloActivo.chekActivo){
                    consultaSql+=" activo = '1' and "
                }if(!chbArticuloActivo.chekActivo){
                    consultaSql+=" activo = '0' and "
                }

                if(consultaSql!=""){
                    modeloArticulos.clearArticulos()
                    modeloArticulos.buscarArticulo(consultaSql,"1=1",0)
                    listaDeArticulos.currentIndex=0;
                }
            }

        }

        BotonPaletaSistema {
            id: btnCargarArticulosBatch
            text: "Carga de artículos"
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.bottom: rectangle2.top
            anchors.bottomMargin: 10
            height: {
                if(visible){
                    btnFiltrarArticulos.height
                }else{
                    0
                }
            }
            visible: modeloControlesMantenimientos.retornaValorMantenimiento("articulosUsaCargaBatch")
            onClicked: {
                modeloDialogoQT.cargarArchivoMantenimiento("articulos")
            }
        }

    }

    ListModel{
        id:modeloArticulosCodigoDeBarras
    }

    Row {
        id: rowBarraDeHerramientasArticulos
        //
        anchors.bottom: rectContenedorArticulos.top
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        spacing: distanciaEntreBotonesBarraDeTareas

        BotonBarraDeHerramientas {
            id: botonNuevoArticulo
            x: 33
            y: 10
            toolTip: "Nuevo articulo"
            z: 8
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevoArticulo.png"
            anchors.verticalCenter: parent.verticalCenter


            onClic: {

                txtCodigoArticulo.textoInputBox=""
                txtDescripcionArticulo.textoInputBox=""
                txtDescripcionExtendidaArticulo.textoInputBox=""
                txtListaDeIvas.codigoValorSeleccion=1
                txtListaDeIvas.textoComboBox=modeloListaIvas.retornaDescripcionIva(1)

                chbArticuloActivo.setActivo(true)


                txtProveedorArticulo.codigoValorSeleccion=modeloListaProveedor.primerRegistroDeProveedorCodigoEnBase()
                txtProveedorArticulo.textoComboBox=modeloListaProveedor.primerRegistroDeProveedorNombreEnBase(txtProveedorArticulo.codigoValorSeleccion.toString())


                cbListaDePrecioDeArticuloSeleccionado.textoComboBox=modeloListasPreciosComboBox.retornaDescripcionListaPrecio(1)
                if(cbListaDePrecioDeArticuloSeleccionado.textoComboBox!="")
                    cbListaDePrecioDeArticuloSeleccionado.codigoValorSeleccion=1

                txtPrecioArticuloSeleccionado.textoInputBox=""+modeloconfiguracion.retornaCantidadDecimalesString()+""
                txtCantidadMinimaStock.textoInputBox="0"

                txtCodigoArticulo.enabled=true

                var modoCodigoArticulo=modeloconfiguracion.retornaValorConfiguracion("MODO_ARTICULO");

                if(modoCodigoArticulo=="0"){

                    txtCodigoArticulo.tomarElFoco()

                }else if(modoCodigoArticulo=="1"){

                    var nuevoArticulo=parseInt(modeloArticulos.ultimoRegistroDeArticuloEnBase());
                    txtCodigoArticulo.textoInputBox=nuevoArticulo
                    txtDescripcionArticulo.tomarElFoco()

                }


                modeloArticulosCodigoDeBarras.clear()


            }
        }

        BotonBarraDeHerramientas {
            id: botonGuardarArticulo
            x: 61
            y: 3
            toolTip: "Guardar articulo"
            z: 7
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            anchors.verticalCenter: parent.verticalCenter

            onClic: {

                var activo=0

                if(chbArticuloActivo.chekActivo)
                    activo=1

                var resultadoInsertArticulo = modeloArticulos.insertarArticulo(txtCodigoArticulo.textoInputBox,txtDescripcionArticulo.textoInputBox,txtDescripcionExtendidaArticulo.textoInputBox,txtProveedorArticulo.codigoValorSeleccion,txtListaDeIvas.codigoValorSeleccion,txtMonedaArticulo.codigoValorSeleccion,activo ,txtNombreDeUsuario.textoInputBox,txtCantidadMinimaStock.textoInputBox.trim(),cbxListaSubRubrosArticulos.codigoValorSeleccion);

                txtMensajeInformacionArticulos.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                if(resultadoInsertArticulo==1){
                    txtMensajeInformacionArticulos.color="#2f71a0"
                    txtMensajeInformacionArticulos.text="Artículo "+ txtCodigoArticulo.textoInputBox+" dado de alta correctamente"


                    if(modeloArticulosBarra.eliminarArticuloBarra(txtCodigoArticulo.textoInputBox)){

                        for(var i=0; i<modeloArticulosCodigoDeBarras.count;i++){

                            modeloArticulosBarra.insertarArticuloBarra(modeloArticulosCodigoDeBarras.get(i).itemCodigoDeBarrasAgregado,txtCodigoArticulo.textoInputBox)

                        }
                    }

                    modeloListaPrecioArticulos.actualizarArticuloDeListaPrecio(txtCodigoArticulo.textoInputBox.trim(),cbListaDePrecioDeArticuloSeleccionado.codigoValorSeleccion,txtPrecioArticuloSeleccionado.textoInputBox.trim())


                    modeloArticulos.clearArticulos()
                    modeloArticulos.buscarArticulo(" codigoArticulo=",txtCodigoArticulo.textoInputBox.trim(),0)
                    listaDeArticulos.currentIndex=0;

                    txtCodigoArticulo.textoInputBox=""
                    txtDescripcionArticulo.textoInputBox=""
                    txtDescripcionExtendidaArticulo.textoInputBox=""
                    txtListaDeIvas.codigoValorSeleccion=1
                    txtListaDeIvas.textoComboBox=modeloListaIvas.retornaDescripcionIva(1)
                    txtProveedorArticulo.textoComboBox=""

                    txtMonedaArticulo.codigoValorSeleccion=modeloconfiguracion.retornaValorConfiguracion("MONEDA_DEFAULT")
                    txtMonedaArticulo.textoComboBox=modeloListaMonedas.retornaDescripcionMoneda(txtMonedaArticulo.codigoValorSeleccion)

                    txtProveedorArticulo.codigoValorSeleccion=""
                    txtCodigoArticulo.enabled=true

                    txtPrecioArticuloSeleccionado.textoInputBox=""+modeloconfiguracion.retornaCantidadDecimalesString()+""

                    chbArticuloActivo.setActivo(true)
                    modeloArticulosCodigoDeBarras.clear()
                    txtCodigoArticulo.tomarElFoco()

                }else if(resultadoInsertArticulo==2){
                    txtMensajeInformacionArticulos.color="#2f71a0"
                    txtMensajeInformacionArticulos.text="Articulo "+ txtCodigoArticulo.textoInputBox+" actualizado correctamente"

                    if(modeloArticulosBarra.eliminarArticuloBarra(txtCodigoArticulo.textoInputBox)){

                        for(var i=0; i<modeloArticulosCodigoDeBarras.count;i++){

                            modeloArticulosBarra.insertarArticuloBarra(modeloArticulosCodigoDeBarras.get(i).itemCodigoDeBarrasAgregado,txtCodigoArticulo.textoInputBox)
                        }
                    }

                    modeloListaPrecioArticulos.actualizarArticuloDeListaPrecio(txtCodigoArticulo.textoInputBox.trim(),cbListaDePrecioDeArticuloSeleccionado.codigoValorSeleccion,txtPrecioArticuloSeleccionado.textoInputBox.trim())

                    modeloArticulos.clearArticulos()
                    modeloArticulos.buscarArticulo(" codigoArticulo=",txtCodigoArticulo.textoInputBox.trim(),0)
                    listaDeArticulos.currentIndex=0;


                    txtCodigoArticulo.textoInputBox=""
                    txtDescripcionArticulo.textoInputBox=""
                    txtDescripcionExtendidaArticulo.textoInputBox=""
                    txtListaDeIvas.codigoValorSeleccion=1
                    txtListaDeIvas.textoComboBox=modeloListaIvas.retornaDescripcionIva(1)

                    txtMonedaArticulo.codigoValorSeleccion=modeloconfiguracion.retornaValorConfiguracion("MONEDA_DEFAULT")
                    txtMonedaArticulo.textoComboBox=modeloListaMonedas.retornaDescripcionMoneda(txtMonedaArticulo.codigoValorSeleccion)


                    txtProveedorArticulo.textoComboBox=""
                    txtProveedorArticulo.codigoValorSeleccion=""
                    chbArticuloActivo.setActivo(true)
                    txtCodigoArticulo.enabled=true

                    txtPrecioArticuloSeleccionado.textoInputBox=""+modeloconfiguracion.retornaCantidadDecimalesString()+""

                    modeloArticulosCodigoDeBarras.clear()
                    txtCodigoArticulo.tomarElFoco()


                }else if(resultadoInsertArticulo==-1){
                    txtMensajeInformacionArticulos.color="#d93e3e"
                    txtMensajeInformacionArticulos.text="ATENCION: No se pudo conectar a la base de datos"


                }else if(resultadoInsertArticulo==-2){
                    txtMensajeInformacionArticulos.color="#d93e3e"
                    txtMensajeInformacionArticulos.text="ATENCION: No se pudo actualizar el articulo"


                }else if(resultadoInsertArticulo==-3){
                    txtMensajeInformacionArticulos.color="#d93e3e"
                    txtMensajeInformacionArticulos.text="ATENCION: No se pudo dar de alta el articulo"


                }else if(resultadoInsertArticulo==-4){
                    txtMensajeInformacionArticulos.color="#d93e3e"
                    txtMensajeInformacionArticulos.text="ATENCION: No se pudo realizar la consulta a la base de datos"


                }else if(resultadoInsertArticulo==-5){
                    txtMensajeInformacionArticulos.color="#d93e3e"
                    txtMensajeInformacionArticulos.text="ATENCION: Faltan datos para guardar el articulo. Verifique antes de continuar"

                }
            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarArticulo
            x: 54
            y: 3
            toolTip: "Eliminar articulo"
            z: 6
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            anchors.verticalCenter: parent.verticalCenter
            onClic: {

                if(txtCodigoArticulo.textoInputBox.trim()!="")
                    if(funcionesmysql.mensajeAdvertencia("Realmente desea eliminar el articulo "+txtCodigoArticulo.textoInputBox.trim()+"?\n\nPresione [ Sí ] para confirmar.")){

                        if(modeloArticulos.existeArticuloEnDocumentos(txtCodigoArticulo.textoInputBox)==false){

                            if(modeloListaPrecioArticulos.eliminarArticuloDeListaPrecio(txtCodigoArticulo.textoInputBox)){
                                if(modeloArticulosBarra.eliminarArticuloBarra(txtCodigoArticulo.textoInputBox)){

                                    if(modeloArticulos.eliminarArticulo(txtCodigoArticulo.textoInputBox.trim())){

                                        txtMensajeInformacionArticulos.visible=true
                                        txtMensajeInformacionTimer.stop()
                                        txtMensajeInformacionTimer.start()

                                        txtMensajeInformacionArticulos.color="#2f71a0"
                                        txtMensajeInformacionArticulos.text="Articulo "+txtCodigoArticulo.textoInputBox+" borrado correctamente"

                                        modeloArticulos.clearArticulos()                                        
                                        modeloArticulos.buscarArticulo("1=","0",0)
                                        listaDeArticulos.currentIndex=0;

                                        txtCodigoArticulo.textoInputBox=""
                                        txtDescripcionArticulo.textoInputBox=""
                                        txtDescripcionExtendidaArticulo.textoInputBox=""
                                        txtListaDeIvas.codigoValorSeleccion=1
                                        txtListaDeIvas.textoComboBox=modeloListaIvas.retornaDescripcionIva(1)

                                        txtMonedaArticulo.codigoValorSeleccion=modeloconfiguracion.retornaValorConfiguracion("MONEDA_DEFAULT")
                                        txtMonedaArticulo.textoComboBox=modeloListaMonedas.retornaDescripcionMoneda(txtMonedaArticulo.codigoValorSeleccion)

                                        txtProveedorArticulo.textoComboBox=""
                                        txtProveedorArticulo.codigoValorSeleccion=""
                                        chbArticuloActivo.setActivo(true)

                                        txtPrecioArticuloSeleccionado.textoInputBox=""+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                        txtCantidadMinimaStock.textoInputBox="0"
                                        modeloArticulosCodigoDeBarras.clear()
                                        txtCodigoArticulo.tomarElFoco()


                                    }else{
                                        txtMensajeInformacionArticulos.visible=true
                                        txtMensajeInformacionTimer.stop()
                                        txtMensajeInformacionTimer.start()
                                        txtMensajeInformacionArticulos.color="#d93e3e"
                                        txtMensajeInformacionArticulos.text="ATENCION: Se borraron los codigos de barras, pero no el articulo"
                                    }
                                }else{

                                    txtMensajeInformacionArticulos.visible=true
                                    txtMensajeInformacionTimer.stop()
                                    txtMensajeInformacionTimer.start()
                                    txtMensajeInformacionArticulos.color="#d93e3e"
                                    txtMensajeInformacionArticulos.text="ATENCION: No se pudo borrar el articulo "+txtCodigoArticulo.textoInputBox
                                }
                            }else{

                                txtMensajeInformacionArticulos.visible=true
                                txtMensajeInformacionTimer.stop()
                                txtMensajeInformacionTimer.start()
                                txtMensajeInformacionArticulos.color="#d93e3e"
                                txtMensajeInformacionArticulos.text="ATENCION: No se pudo borrar el articulo "+txtCodigoArticulo.textoInputBox +". Existe en una lista de precios aún."

                            }
                        }else{
                            txtMensajeInformacionArticulos.visible=true
                            txtMensajeInformacionTimer.stop()
                            txtMensajeInformacionTimer.start()
                            txtMensajeInformacionArticulos.color="#d93e3e"
                            txtMensajeInformacionArticulos.text="ATENCION: No se puede borrar el artículo porque existe en un documento."
                        }
                    }
            }
        }

        BotonBarraDeHerramientas {
            id: botonListarTodosLosArticulos
            x: 47
            y: 10
            toolTip: "Listar todos los artículos"
            z: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            anchors.verticalCenter: parent.verticalCenter
            onClic: {

                modeloArticulos.clearArticulos()
                modeloArticulos.buscarArticulo("1=","1",0)
                listaDeArticulos.currentIndex=0;
            }
        }

        Text {
            id: txtMensajeInformacionArticulos
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
            txtMensajeInformacionArticulos.visible=false
            txtMensajeInformacionArticulos.color="#d93e3e"
        }
    }

    Rectangle {
        id: rectangle4
        x: -4
        y: -1
        width: 10
        color: "#27abb4"
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: rectContenedorArticulos.top
        anchors.bottomMargin: -10
        z: 1
        anchors.leftMargin: 0
        anchors.left: parent.left
    }


}
