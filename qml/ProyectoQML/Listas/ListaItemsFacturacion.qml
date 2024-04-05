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


    height: descripcionArticuloExtendido=="" ? 32 : 42
    width: parent.width
    // height: 400
    // width: 2500
    color: "#e9e8e9"

    radius: 1
    border.color: "#aaaaaa"
    opacity: 1

    property double suma : 0
    property double resta : 0

    property double precioArticuloParseado : 0.00

    property double descuentoLineaItem: 0.00


    property string idGarantia: codigoTipoGarantia
    property string nombreGarantia: descripcionTipoGarantia

    property bool _asignarGarantiaAArticulo: asignarGarantiaAArticulo


    signal abrirGarantias

    Text {
        id:txtDescuentoLineaItem
        text: descuentoLineaItem
        visible: false
    }



    Text {
        id:txtItemCodigoArticuloFacturacion
        width: 70
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        //
        font.pointSize: 10
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 0
        color: "#212121"
        text: codigoArticulo
        font.family: "Arial"
        opacity: 1
        horizontalAlignment: Text.AlignHCenter


    }


    MouseArea{
        id: mousearea1
        anchors.rightMargin: 50
        z: 1
        anchors.fill: parent
        hoverEnabled: activo
        // visible: activo

        onEntered: {
            if(activo){
                rectListaItemColorDeseleccionado.stop()
                rectListaItemColorSeleccionado.start()
            }
        }
        onExited: {
            if(activo){
                rectListaItemColorSeleccionado.stop()
                rectListaItemColorDeseleccionado.start()
            }

        }

        onDoubleClicked: {

            if(txtItemCodigoArticuloBarrasFacturacion.width!=0){
                if(lblEstadoDocumento.text.trim()=="Emitido" || lblEstadoDocumento.text.trim()=="Guardado" || lblEstadoDocumento.text.trim()=="Pendiente"){
                    cuadroDatosACambiarLineaFacturacion.cargarDatoActual(txtItemCodigoArticuloBarrasFacturacion.text,indiceLinea)
                    cuadroDatosACambiarLineaFacturacion.visible=true
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
        id: txtEliminarItem
        text: qsTr("<x")
        font.family: "Arial"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: mousearea1.right
        anchors.leftMargin: 5
        //
        font.bold: true
        font.pixelSize: 10
        visible: activo

        MouseArea {
            id: mouse_area1
            anchors.fill: parent
            enabled: activo

            onClicked: {


                ///Chequeo que modo de calculo de total esta seteado
                var modoCalculoTotal=modeloconfiguracion.retornaValorConfiguracion("MODO_CALCULOTOTAL");

                if(modoCalculoTotal=="1"){
                    etiquetaTotal.setearTotalAnulacion((precioArticulo*cantidadItems).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),codigoArticulo,cbListatipoDocumentos.codigoValorSeleccion,consideraDescuento,index)
                }else if(modoCalculoTotal=="2"){
                    etiquetaTotal.setearTotalAnulacionModoArticuloSinIva((precioArticulo*cantidadItems).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),codigoArticulo,cbListatipoDocumentos.codigoValorSeleccion,consideraDescuento,index)
                }


                modeloItemsFactura.remove(index)




            }
        }
    }

    Rectangle {
        id: rectLineaSeparacion
        y: 0
        width: 2
        color: "#C4C4C6"
        anchors.left: txtItemCodigoArticuloFacturacion.right
        anchors.leftMargin: 10
        //
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    Text {
        id: txtItemDescripcionArticuloFacturacion
        x: 4
        y: 0
        width: {
            /// Chequeo si el item comodin esta activo o no, para saber si acorto o dejo como esta el largo de la descripcion
            /// del item para que no interfiera con el monto referencia del sistema
            if(txtItemCodigoArticuloBarrasFacturacion.width==0){

                300

            }else{

                if(txtItemPrecioMonedaReferenciaFacturacion.visible){
                    200
                }else{
                    300
                }
            }
        }
        color: "#212121"
        text: descripcionArticulo
        font.family: "Arial"
        clip: true
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        font.bold: false
        font.pointSize: 10
        anchors.leftMargin: 10
        verticalAlignment: Text.AlignVCenter
        anchors.left: rectLineaSeparacion2.right
    }

    Text {
        id: txtItemDescripcionExtendidaArticuloFacturacion
        width: txtItemDescripcionArticuloFacturacion.width
        color: "#757575"
        text: "<b><i>EXT:</i></b> "+descripcionArticuloExtendido
        horizontalAlignment: Text.AlignRight
        font.family: "Arial"
        visible: descripcionArticuloExtendido=="" ? false : true
        clip: true
        //
        //anchors.top: parent.bottom
        // anchors.topMargin: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        font.bold: false
        font.pointSize: 9
        anchors.leftMargin: 10
        verticalAlignment: Text.AlignVCenter
        anchors.left: rectLineaSeparacion2.right
    }


    Rectangle {
        id: rectLineaSeparacion2
        x: -1
        y: -4
        width: {
            if(txtItemCodigoArticuloBarrasFacturacion.width==0){
                0
            }else{
                2
            }
        }
        color: "#C4C4C6"
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.leftMargin: {
            if(txtItemCodigoArticuloBarrasFacturacion.width==0){
                0
            }else{
                10
            }
        }
        anchors.left: txtItemCodigoArticuloBarrasFacturacion.right
    }


    Rectangle {
        id: rectLineaSeparacion3
        x: 3
        y: -7
        width: 2
        color: "#C4C4C6"
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.leftMargin: 10
        anchors.left: txtItemDescripcionArticuloFacturacion.right
    }

    Text {
        id: txtItemSubTotalTotalItemArticuloFacturacion
        x: 16
        y: 3
        width: 120
        color: "#212121"
        text: precioArticuloSubTotal
        font.family: "Arial"
        anchors.right: parent.right
        anchors.rightMargin: 74
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        font.bold: false
        font.pointSize: 10
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        visible: etiquetaTotal.visible
    }

    Rectangle {
        id: rectLineaSeparacion4
        x: 7
        y: -7
        width: 2
        color: "#C4C4C6"
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.leftMargin: 10
        anchors.left: txtItemPrecioTotalItemArticuloFacturacion.right
    }

    Text {
        id: txtItemCodigoArticuloBarrasFacturacion
        x: -4
        y: 7
        width: {
            if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaCodigoBarrasADemanda")){
                280
            }else{
                0
            }
        }
        color: "#212121"
        text: codigoBarrasArticulo
        clip: true
        font.family: "Arial"
        horizontalAlignment: Text.AlignHCenter
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        font.bold: false
        font.pointSize: 10
        anchors.leftMargin: 10
        verticalAlignment: Text.AlignVCenter
        anchors.left: rectLineaSeparacion.right
        visible: {
            if(txtItemCodigoArticuloBarrasFacturacion.width==0){
                false
            }else{
                true
            }
        }

        property string respaldoDescripcionTexto: ""
        onVisibleChanged: {
            if(txtItemCodigoArticuloBarrasFacturacion.width==0){
                respaldoDescripcionTexto=txtItemCodigoArticuloBarrasFacturacion.text
                modeloItemsFactura.set(index,{"codigoBarrasArticulo": ""})

            }else{
                respaldoDescripcionTexto=txtItemCodigoArticuloBarrasFacturacion.text
                modeloItemsFactura.set(index,{"codigoBarrasArticulo": respaldoDescripcionTexto})
            }
        }
    }

    Text {
        id: txtItemCantidadArticuloFacturacion
        x: 13
        y: 9
        width: 45
        color: "#212121"
        text: cantidadItems
        horizontalAlignment: Text.AlignRight
        font.family: "Arial"
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        font.bold: false
        font.pointSize: 10
        anchors.leftMargin: 37
        verticalAlignment: Text.AlignVCenter
        anchors.left: rectLineaSeparacion3.right
    }

    Rectangle {
        id: rectLineaSeparacionGarantia
        x: 8
        y: 0
        width: 2
        color: "#C4C4C6"
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.leftMargin: 10
        anchors.left: txtItemCantidadArticuloFacturacion.right
    }

    Image {
        id: imgGarantia
        y: 4
        width: 16
        height: 16
        clip: true
        opacity: 0.900
        smooth: true
        asynchronous: true
        z: 2
        anchors.left: rectLineaSeparacionGarantia.right
        anchors.leftMargin: 7
        anchors.verticalCenter: parent.verticalCenter

        source: {
            if(idGarantia=="" || idGarantia=="0"){
                "qrc:/imagenes/qml/ProyectoQML/Imagenes/SinGarantia.png"
            }else{
                "qrc:/imagenes/qml/ProyectoQML/Imagenes/Garantia.png"
            }
        }

        MouseArea {
            id: mouse_areaGarantia
            clip: true
            hoverEnabled: true
            anchors.fill: parent
            visible: activo
            onDoubleClicked: {
                abrirGarantias()
            }

            onEntered: {
                timer1.start()
            }

            onExited: {
                timer1.stop()
                rectToolTipText.visible=false
            }
        }
    }

    Rectangle{
        id:rectToolTipText
        visible: false
        width: toolTipText.implicitWidth+20
        height: toolTipText.implicitHeight
        color: "#4d7dc0"
        radius: 6
        opacity: 1
        z: 3
        Text {
            id: toolTipText
            color: "#fdfbfb"
            font.family: "Arial"
            font.bold: false
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.fill: parent
            text: {
              if(idGarantia=="" || idGarantia=="0"){
               "Sin garantia establecida"
              }else{
                  nombreGarantia
              }
            }
            visible: true
        }
    }
    Timer {
           id:timer1
           interval: 600;
           running: false;
           repeat: false;
           onTriggered: {
               if(toolTipText.text!=""){
                   rectToolTipText.x=imgGarantia.x+20
                   rectToolTipText.y=imgGarantia.y
                   rectToolTipText.visible=true
               }
           }
       }



    Rectangle {
        id: rectLineaSeparacion5
        x: 8
        y: 0
        width: 2
        color: "#C4C4C6"
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.leftMargin: 10
        anchors.left: imgGarantia.right
    }

    Image {
        id: imgIncrementarCantidad
        y: 4
        width: 16
        height: 16
        clip: true
        opacity: 0.900
        asynchronous: true
        z: 2
        anchors.left: rectLineaSeparacion3.right
        anchors.leftMargin: 3
        anchors.verticalCenter: parent.verticalCenter
        smooth: true
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Mas.png"
        visible: txtCantidadArticulosFacturacion.visible
        MouseArea {
            id: mouse_area2
            clip: true
            //
            anchors.fill: parent
            visible: activo
            onClicked: {


                //Controlo si se peude vender sin stock previsto
                if(modeloArticulos.retornaSiPuedeVenderSinStock(1,cbListatipoDocumentos.codigoValorSeleccion,codigoArticulo,retornaCantidadDeUnArticuloEnFacturacion(codigoArticulo)   )){


                    ///Chequeo que modo de calculo de total esta seteado
                    var modoCalculoTotal=modeloconfiguracion.retornaValorConfiguracion("MODO_CALCULOTOTAL");

                    suma=0

                    if(cantidadItems!=99999){
                        suma=parseFloat(precioArticuloSubTotal)
                        suma+=parseFloat(precioArticulo)

                        precioArticuloParseado=precioArticulo


                        if(modoCalculoTotal=="1"){
                            etiquetaTotal.setearTotal(precioArticuloParseado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),codigoArticulo,cbListatipoDocumentos.codigoValorSeleccion,consideraDescuento,index)
                        }else if(modoCalculoTotal=="2"){
                            etiquetaTotal.setearTotalModoArticuloSinIva(precioArticuloParseado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),codigoArticulo,cbListatipoDocumentos.codigoValorSeleccion,consideraDescuento,index)
                        }


                        modeloItemsFactura.set(index,{"cantidadItems": cantidadItems+1})
                        modeloItemsFactura.set(index,{"precioArticuloSubTotal": suma.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))})
                    }


                }
            }
        }
    }

    Image {
        id: imgDecrementarCantidad
        y: -5
        width: 16
        height: 16
        clip: true
        opacity: 0.900
        z: 3
        anchors.left: imgIncrementarCantidad.right
        anchors.leftMargin: 2
        asynchronous: true
        anchors.verticalCenter: parent.verticalCenter
        smooth: true
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Menos.png"
        visible: txtCantidadArticulosFacturacion.visible

        MouseArea {
            id: mouse_area3
            //
            clip: true
            visible: activo
            anchors.fill: parent
            onClicked: {

                ///Chequeo que modo de calculo de total esta seteado
                var modoCalculoTotal=modeloconfiguracion.retornaValorConfiguracion("MODO_CALCULOTOTAL");

                resta=0
                if(cantidadItems!=1){
                    resta=precioArticuloSubTotal
                    resta-=precioArticulo

                    precioArticuloParseado=precioArticulo

                    if(modoCalculoTotal=="1"){
                        etiquetaTotal.setearTotalAnulacion(precioArticuloParseado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),codigoArticulo,cbListatipoDocumentos.codigoValorSeleccion,consideraDescuento,index)
                    }else if(modoCalculoTotal=="2"){
                        etiquetaTotal.setearTotalAnulacionModoArticuloSinIva(precioArticuloParseado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),codigoArticulo,cbListatipoDocumentos.codigoValorSeleccion,consideraDescuento,index)
                    }

                    modeloItemsFactura.set(index,{"cantidadItems": cantidadItems-1})
                    modeloItemsFactura.set(index,{"precioArticuloSubTotal": resta.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))})


                }
            }
        }
    }

    Text {
        //id:
        id:txtItemPrecioTotalItemArticuloFacturacion
        y: 3
        width: 82
        color: "#212121"
        // text: precioArticuloSubTotal
        text: precioArticulo
        anchors.left: rectLineaSeparacion5.right
        anchors.leftMargin: 10
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        font.family: "Arial"
        font.bold: false
        font.pointSize: 10
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        visible: etiquetaTotal.visible
    }

    Rectangle {
        id: rectLineaSeparacion6
        x: 17
        y: -4
        width: 2
        color: "#c4c4c6"
        //
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.leftMargin: 10
        anchors.left: txtItemSubTotalTotalItemArticuloFacturacion.right
        visible: etiquetaTotal.visible
    }

    Text {
        id: txtItemPrecioMonedaReferenciaFacturacion
        width: 82
        color: "#212121"
        text: costoArticuloMonedaReferencia
        verticalAlignment: Text.AlignVCenter
        //
        font.pointSize: 10
        horizontalAlignment: Text.AlignRight
        font.bold: false
        anchors.leftMargin: 10
        anchors.topMargin: 0
        font.family: "Arial"
        visible: {
            if(etiquetaTotal.visible){
                if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaPrecioManualEnMonedaReferencia")){
                    true
                }else{
                    false
                }
            }else{
                false
            }
        }
        anchors.top: parent.top
        anchors.bottomMargin: 0
        anchors.left: rectLineaSeparacion4.right
        anchors.bottom: parent.bottom
    }

    Rectangle {
        id: rectLineaSeparacion7
        x: 13
        y: 2
        width: 2
        color: "#c4c4c6"
        anchors.leftMargin: 10
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        anchors.left: txtItemPrecioMonedaReferenciaFacturacion.right
        //
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        visible: txtItemPrecioMonedaReferenciaFacturacion.visible
    }

}
