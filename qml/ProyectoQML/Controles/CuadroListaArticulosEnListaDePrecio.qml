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

Rectangle {

    id: rectListaListaDePrecios
    color: "#be231919"
    visible: true
    anchors.fill: parent
    //
    z: 8

    signal clicActualizar
    signal precionarEscape

    property string nombreArticulo: ""



    function cargarPrecioDeArticulo(_codigoArticulo){

        modeloListasPreciosCuadroArticulosASetearPrecioGenerica.clear()
        modeloListasPreciosCuadroArticulosASetearPrecio.clearArticulosListaPrecio()        

        modeloListasPreciosCuadroArticulosASetearPrecio.buscarArticulosListaPrecioParaModificar(_codigoArticulo)

        nombreArticulo=modeloArticulos.retornaDescripcionArticulo(_codigoArticulo)


        for(var j=0;j<modeloListasPreciosCuadroArticulosASetearPrecio.rowCount();j++){

            var _codigoListadePrecio = modeloListasPreciosCuadroArticulosASetearPrecio.retornaCodigoListaPrecio(j)

            modeloListasPreciosCuadroArticulosASetearPrecioGenerica.append({
                                             descripcionListaDePreciosAModificar: modeloListasPrecios.retornaDescripcionListaPrecio(_codigoListadePrecio),
                                             precioArticulo: modeloListasPreciosCuadroArticulosASetearPrecio.retornaPrecioArticulo(j),
                                             codigoArticulo:_codigoArticulo,
                                             codigoListaDePrecio: _codigoListadePrecio
                                         })
        }
    }


    function actulizarListasDePrecio(){

        for(var j=0;j<modeloListasPreciosCuadroArticulosASetearPrecioGenerica.count;j++){

            ///Verifico si el nuevo precio es igual al precio actual, en ese caso no hago nada.
            if(modeloListasPreciosCuadroArticulosASetearPrecioGenerica.get(j).precioArticulo!=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(modeloListasPreciosCuadroArticulosASetearPrecioGenerica.get(j).codigoArticulo,modeloListasPreciosCuadroArticulosASetearPrecioGenerica.get(j).codigoListaDePrecio)){

                ///Verifico que el nuevo precio no sea 0, en ese caso no hago nada.
                if(modeloListasPreciosCuadroArticulosASetearPrecioGenerica.get(j).precioArticulo!=0.00){

                    var resultado = modeloListaPrecioArticulos.insertarArticulosListaPrecio(modeloListasPreciosCuadroArticulosASetearPrecioGenerica.get(j).codigoListaDePrecio,modeloListasPreciosCuadroArticulosASetearPrecioGenerica.get(j).codigoArticulo,modeloListasPreciosCuadroArticulosASetearPrecioGenerica.get(j).precioArticulo)

                    if(resultado==-1){
                        funcionesmysql.mensajeAdvertencia("ERROR: No hay conexión con la base de datos, no se pudo actualizar la lista de precios.")
                    }else if(resultado==-3){
                        funcionesmysql.mensajeAdvertencia("ERROR: No se pudo insertar o actualizar el artículo en la lista de precios.")
                    }else if(resultado==-5){
                        funcionesmysql.mensajeAdvertencia("ERROR: Datos incompletos, imposible actualizar.")
                    }
                }
            }
        }
    }




    MouseArea {
        id: mouse_area2
        anchors.fill: parent
        hoverEnabled: true

        Rectangle {
            id: rectListasDePreciosConArticulos
            width: 600
            height: 450
            color: "#1e7597"
            radius: 2
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

                    precionarEscape()

                }
            }


            Text {
                id: lblListaListaPrecios
                color: "#ffffff"
                text: qsTr("Lista de precios:")
                style: Text.Raised
                font.underline: true
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: true
                font.family: "Verdana"
                anchors.top: parent.top
                anchors.topMargin: 20
                font.pixelSize: sizeTitulosControles
            }



            ListModel{
                id:modeloListasPreciosCuadroArticulosASetearPrecioGenerica
            }


            ListView {
                id: listaDePreciosDondeSeModificaraElArticulo
                delegate: ListaListasDePrecioArticuloAModificarPrecio {
                    Keys.onEscapePressed: {
                        precionarEscape()
                    }

                }
                anchors.bottom: btnGuardarCambioDePrecios.top
                anchors.right: parent.right
                anchors.left: parent.left
                interactive: {
                    if(listaDePreciosDondeSeModificaraElArticulo.count>8){
                        true
                    }else{
                        false
                    }
                }
                model:modeloListasPreciosCuadroArticulosASetearPrecioGenerica
                anchors.top: lblNombreArticuloAModificar.bottom
                anchors.rightMargin: 20
                boundsBehavior: Flickable.DragAndOvershootBounds
                anchors.bottomMargin: 10
                highlightRangeMode: ListView.NoHighlightRange
                clip: true
                highlightFollowsCurrentItem: true
                anchors.leftMargin: 35
                spacing: 1
                //
                anchors.topMargin: 7
                snapMode: ListView.NoSnap
                flickableDirection: Flickable.VerticalFlick
                keyNavigationWraps: true
                cacheBuffer: 2000

                Rectangle {
                    id: scrollbarlistaDeDocumentosEnLiquidaciones
                    y: listaDePreciosDondeSeModificaraElArticulo.visibleArea.yPosition * listaDePreciosDondeSeModificaraElArticulo.height+5
                    width: 10
                    height: listaDePreciosDondeSeModificaraElArticulo.visibleArea.heightRatio * listaDePreciosDondeSeModificaraElArticulo.height+18
                    color: "#000000"
                    radius: 2
                    anchors.rightMargin: 4
                    opacity: 0.5
                    visible: listaDePreciosDondeSeModificaraElArticulo.interactive
                    anchors.right: listaDePreciosDondeSeModificaraElArticulo.right
                    //
                    z: 1
                }

                Keys.onEscapePressed: {
                    precionarEscape()
                }
            }

            Text {
                id: lblInformacionLustaDePrecios
                y: 7
                color: "#ffffff"
                text: qsTr("Desde aquí puede setear el precio del artículo, en todas las listas de precio del sistema que esten activas. Si no desea cargar el precio del artículo en una lista, alcanza con dejarlo en precio 0 y se omitira al guardar.")
                visible: true
                style: Text.Normal
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                anchors.left: parent.left
                anchors.leftMargin: 35
                anchors.right: parent.right
                anchors.rightMargin: 15
                font.underline: false
                anchors.top: lblListaListaPrecios.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: sizeTitulosControles
                font.family: "Verdana"
                font.bold: false
                anchors.topMargin: 5
                Keys.onEscapePressed: {
                    precionarEscape()
                }
            }

            BotonPaletaSistema {
                id: btnGuardarCambioDePrecios
                text: "Actulizar listas de precios"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 20
                border.color: "#787777"

                onClicked: {

                    if(modeloListasPreciosCuadroArticulosASetearPrecioGenerica.count!=0){
                        actulizarListasDePrecio()
                    }
                    clicActualizar()
                }
            }

            Rectangle {
                id: rectangle1
                x: -1
                y: 9
                width: 10
                anchors.top: parent.top
                clip: true
                Rectangle {
                    id: rectangle2
                    width: 3
                    height: parent.height/1.50
                    color: "#1e7597"
                    radius: 5
                    opacity: 0.8
                    anchors.leftMargin: 5
                    anchors.bottomMargin: -1
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                }
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
                anchors.leftMargin: 5
                anchors.bottomMargin: 0
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
            }

            Text {
                id: lblNombreArticuloAModificar
                x: -8
                y: 2
                color: "#ffffff"
                text: "Artículo: "+nombreArticulo
                anchors.rightMargin: 20
                clip: true
                style: Text.Normal
                font.underline: false
                anchors.top: lblInformacionLustaDePrecios.bottom
                anchors.leftMargin: 35
                anchors.topMargin: 7
                visible: true
                font.family: "Verdana"
                anchors.right: lblNuevoPrecio.left
                font.pixelSize: 12
                font.bold: true
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                anchors.left: parent.left
            }

            Text {
                id: lblNuevoPrecio
                x: -4
                y: 7
                color: "#ffffff"
                text: "Nuevo precio:"
                horizontalAlignment: Text.AlignRight
                clip: true
                font.pixelSize: sizeTitulosControles
                anchors.topMargin: 7
                font.family: "Verdana"
                font.bold: true
                font.underline: false
                visible: true
                style: Text.Normal
                anchors.top: lblInformacionLustaDePrecios.bottom
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                anchors.rightMargin: 40
                anchors.right: parent.right
            }


        }
        Keys.onEscapePressed: {
            precionarEscape()
        }
    }
    Keys.onEscapePressed: {
        precionarEscape()
    }
}
