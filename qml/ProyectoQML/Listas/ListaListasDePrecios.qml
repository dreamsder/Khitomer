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
    height: 52
    color: "#e9e8e9"
    radius: 1
    border.color: "#aaaaaa"
    //
    opacity: 1


    Text {
        id:txtListaDePrecio
        text: codigoListaPrecio + " - "+ descripcionListaPrecio
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


    FocusScope{
        id:focus_scope1
        anchors.fill: parent
        onFocusChanged: {

            if(focus_scope1.focus){
              //  rectListaItemContraer.stop()
              //  rectListaItemExpandir.start()

                rectListaItem.color="#9294C6"

            }else{

               // rectListaItemExpandir.stop()
               // rectListaItemContraer.start()

                rectListaItemColorDeseleccionado.start()
                txtListaDePrecio.color= "#212121"
                txtFechaVigenciaDesde.color="#000000"
                txtCantidadDeArticulos.color="#000000"

            }

        }

        MouseArea{
            id: mousearea1
            z: 1
            anchors.fill: parent
            hoverEnabled: true



            onEntered: {
                if(focus_scope1.focus==false){
                    txtListaDePrecio.color= "white"
                    txtFechaVigenciaDesde.color="white"
                    txtCantidadDeArticulos.color="white"
                    rectListaItemColorDeseleccionado.stop()
                    rectListaItemColorSeleccionado.start()
                }
            }
            onExited: {
                if(focus_scope1.focus==false){

                    txtListaDePrecio.color= "#212121"
                    txtFechaVigenciaDesde.color="#000000"
                    txtCantidadDeArticulos.color="#000000"

                    rectListaItemColorSeleccionado.stop()
                    rectListaItemColorDeseleccionado.start()
                }
            }

            onClicked: {
                var listaActiva=true
                var participaBusquedaInt=true


                if(participaEnBusquedaInteligente==0)
                    participaBusquedaInt=false


                if(activo==0)
                    listaActiva=false

                chbListaPrecioActiva.setActivo(listaActiva)
                chbApareceEnBusquedaInteligente.setActivo(participaBusquedaInt)

                focus_scope1.focus=true
                txtCodigoListaDePrecio.textoInputBox=codigoListaPrecio
                txtNombreListaDePrecio.textoInputBox =descripcionListaPrecio
                txtVigenciaDesde.textoInputBox=vigenciaDesdeFecha
                txtVigenciaHasta.textoInputBox=vigenciaHastaFecha

                modeloListaPrecioArticulosAlternativa.clear()
                modeloListaPrecioArticulos.clearArticulosListaPrecio()
              /*  var currentDate = new Date();
                console.log(currentDate)*/
                modeloListaPrecioArticulos.buscarArticulosListaPrecio("codigoListaPrecio=",codigoListaPrecio)


                for(var i=0; i<modeloListaPrecioArticulos.rowCount();i++){

                    modeloListaPrecioArticulosAlternativa.append({
                                                                     itemCodigoAgregado:modeloListaPrecioArticulos.retornarArticulosEnLista(i,codigoListaPrecio),
                                                                     itemDescripcion:modeloListaPrecioArticulos.retornarDescripcionArticulosEnLista(i,codigoListaPrecio),
                                                                     simboloMoneda:modeloListaPrecioArticulos.retornarSimboloMonedaEnLista(i,codigoListaPrecio),
                                                                     //modeloArticulos.retornaDescripcionArticulo(modeloListaPrecioArticulos.retornarArticulosEnLista(i,codigoListaPrecio)),
                                                                     itemPrecioAgregado:modeloListaPrecioArticulos.retornarPrecioEnLista(i,codigoListaPrecio),
                                                                     precioModificado:false,
                                                                     eliminarPrecioArticulo:false
                                                                 })
                }


              /*  console.log("Fin carga lista de articulos de lista de precio en QML")
                currentDate = new Date();
                                console.log(currentDate)*/

                txtNombreListaDePrecio.tomarElFoco()
                txtArticuloParaLista.textoInputBox=""
                txtPrecioArticuloParaLista.textoInputBox=""+modeloconfiguracion.retornaCantidadDecimalesString()+""

            }

        }
    }
    PropertyAnimation{
        id:rectListaItemExpandir
        target: rectListaItem
        property: "height"
        from:52
        to:100
        duration: 200
    }
    PropertyAnimation{
        id:rectListaItemContraer
        target: rectListaItem
        property: "height"
        to:52
        from:100
        duration: 100
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
        id: gridDatos
        spacing: 2
        flow: Grid.TopToBottom
        rows: 2
        columns: 5
        anchors.top: txtListaDePrecio.bottom
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30

        Text {
            id: txtFechaVigenciaDesde
            x: 1
            y: -15
            width: 210
            text: "Vigencia:  desde  "+vigenciaDesdeFecha+"  hasta  "+vigenciaHastaFecha
            font.family: "Arial"
            //
            opacity: 0.500
            font.pixelSize: 11
            height: txtFechaVigenciaDesde.implicitHeight
        }


        Text {
            id: txtCantidadDeArticulos
            width: 210
            height: txtCantidadDeArticulos.implicitHeight
            text: "Cantidad de artículos: "+ modeloListaPrecioArticulos.retornaCantidadArticulosEnListaPrecio(codigoListaPrecio)
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
}
