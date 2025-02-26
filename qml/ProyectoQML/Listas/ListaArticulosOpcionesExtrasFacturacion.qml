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
import "../Controles"

Rectangle{
    id: rectListaItem
    width: parent.width
    //  width: 1024
    height: 40
    color: "#e9e8e9"
    radius: 1
    border.color: "#aaaaaa"
    opacity: 1

    property double precioArticuloDobleClic: 0.00

    property double costoArticuloOpcionesExtraFacturacion : 0.00

    Text {
        id:txtItemArticulo
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        //
        font.pointSize: 10
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 0
        color: "#212121"
        text: codigoArticulo +" - "+ descripcionArticulo
        clip: true
        font.family: "Arial"
        opacity: 0.900

        onTextChanged: {

            if(activo==1)
            {
                txtItemArticuloInactivo.visible=false
            }else{
                txtItemArticuloInactivo.visible=true
            }

        }
    }


    MouseArea{
        id: mousearea1
        anchors.rightMargin: 0
        z: 1
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {

            rectListaItemColorDeseleccionado.stop()
            rectListaItemColorSeleccionado.start()
        }
        onExited: {
            rectListaItemColorSeleccionado.stop()
            rectListaItemColorDeseleccionado.start()

        }

        onDoubleClicked: {



        if(!superaCantidadMaximaLineasDocumento()){

            funcionesmysql.loguear("QML::DoubleClic lista articulos opciones extras Facturacion")

            //cbxListaPrecioManualFijadaPorUsuario
            if(modeloArticulos.retornaArticuloActivo(codigoArticulo) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")){




                ///Chequeo que modo de calculo de total esta seteado
                var modoCalculoTotal=modeloconfiguracion.retornaValorConfiguracion("MODO_CALCULOTOTAL");

                if(txtCodigoClienteFacturacion.textoInputBox!=""){ //Hay un cliente seleccionado

                    funcionesmysql.loguear("QML::Hay un cliente seleccionado")


                    var listaPrecioSeleccionada;
                    if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                        listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(txtFechaPrecioFacturacion.textoInputBox.trim(), txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim())
                    }else{
                        listaPrecioSeleccionada=cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion
                    }

                    funcionesmysql.loguear("QML::Lista de precios seleccionada: "+listaPrecioSeleccionada)


                    if(listaPrecioSeleccionada!=""){



                        var precioArticuloSelecionado=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(codigoArticulo,listaPrecioSeleccionada)

                        funcionesmysql.loguear("QML::precioArticuloSelecionado: "+precioArticuloSelecionado)

                        var cotizacion=1;
                        precioArticuloDobleClic=precioArticuloSelecionado

                        if(modeloListaMonedas.retornaCodigoMoneda(codigoArticulo)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                            if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(codigoArticulo)){
                                cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                precioArticuloDobleClic=precioArticuloSelecionado/cotizacion
                            }else{
                                if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                    cotizacion=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(codigoArticulo))
                                    precioArticuloDobleClic=precioArticuloSelecionado*cotizacion
                                }else{
                                    precioArticuloDobleClic=(precioArticuloSelecionado*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(codigoArticulo)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                }

                            }
                        }

                        costoArticuloOpcionesExtraFacturacion=txtCostoArticuloMonedaReferencia.textoInputBox.trim();


                        funcionesmysql.loguear("QML::modeloItemsFactura.append: ")
                        funcionesmysql.loguear("QML::codigoArticulo: "+codigoArticulo)
                        funcionesmysql.loguear("QML::precioArticulo: "+precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))

                        if(txtArticuloParaFacturacion.visible){




                            //Controlo si se peude vender sin stock previsto
                            if(modeloArticulos.retornaSiPuedeVenderSinStock(1,cbListatipoDocumentos.codigoValorSeleccion,codigoArticulo,retornaCantidadDeUnArticuloEnFacturacion(codigoArticulo)   )){


                            precioArticuloDobleClic=calcularDescuentoPorCliente(precioArticuloDobleClic)
                            modeloItemsFactura.append({
                                                          codigoArticulo:codigoArticulo,
                                                          codigoBarrasArticulo:"",
                                                          descripcionArticulo:descripcionArticulo,
                                                          descripcionArticuloExtendido:descripcionExtendida,
                                                          precioArticulo:precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                          precioArticuloSubTotal:precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                          cantidadItems:1,
                                                          costoArticuloMonedaReferencia:costoArticuloOpcionesExtraFacturacion.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                          activo:true,
                                                          consideraDescuento:false,
                                                          indiceLinea:-1,
                                                          descuentoLineaItem:0,
                                                          codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(codigoArticulo),
                                                          descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(codigoArticulo)),
                                                          asignarGarantiaAArticulo:false

                                                      })

                            listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                            if(modoCalculoTotal=="1"){
                                etiquetaTotal.setearTotal(precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),codigoArticulo,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                            }else if(modoCalculoTotal=="2"){
                                etiquetaTotal.setearTotalModoArticuloSinIva(precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),codigoArticulo,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                            }

                            mostrarCuadroDeActulizacionDePrecioEnFacturacion(codigoArticulo,"LATERAL")
}
                        }


                    }else{

                        funcionesmysql.loguear("QML::Sin Lista de precios seleccionada: ")

                        var precioArticuloSelecionadoSinLista

                        if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                            precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(codigoArticulo,1)
                        }else{
                            precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(codigoArticulo,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                        }



                        var cotizacion2=1;
                        precioArticuloDobleClic=precioArticuloSelecionadoSinLista

                        if(modeloListaMonedas.retornaCodigoMoneda(codigoArticulo)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                            if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(codigoArticulo)){
                                cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                precioArticuloDobleClic=precioArticuloSelecionadoSinLista/cotizacion2
                            }else{
                                if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                    cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(codigoArticulo))
                                    precioArticuloDobleClic=precioArticuloSelecionadoSinLista*cotizacion2
                                }else{
                                    precioArticuloDobleClic=(precioArticuloSelecionadoSinLista*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(codigoArticulo)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                }

                            }
                        }
                        costoArticuloOpcionesExtraFacturacion=txtCostoArticuloMonedaReferencia.textoInputBox.trim();


                        funcionesmysql.loguear("QML::modeloItemsFactura.append: ")
                        funcionesmysql.loguear("QML::codigoArticulo: "+codigoArticulo)
                        funcionesmysql.loguear("QML::precioArticulo: "+precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))


                        if(txtArticuloParaFacturacion.visible){
                            //Controlo si se peude vender sin stock previsto
                            if(modeloArticulos.retornaSiPuedeVenderSinStock(1,cbListatipoDocumentos.codigoValorSeleccion,codigoArticulo,retornaCantidadDeUnArticuloEnFacturacion(codigoArticulo))){
                            precioArticuloDobleClic=calcularDescuentoPorCliente(precioArticuloDobleClic)
                            modeloItemsFactura.append({
                                                          codigoArticulo:codigoArticulo,
                                                          codigoBarrasArticulo:"",
                                                          descripcionArticulo:descripcionArticulo,
                                                          descripcionArticuloExtendido:descripcionExtendida,
                                                          precioArticulo:precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                          precioArticuloSubTotal:precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                          cantidadItems:1,
                                                          costoArticuloMonedaReferencia:costoArticuloOpcionesExtraFacturacion.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                          activo:true,
                                                          consideraDescuento:false,
                                                          indiceLinea:-1,
                                                          descuentoLineaItem:0,
                                                          codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(codigoArticulo),
                                                          descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(codigoArticulo)),
                                                          asignarGarantiaAArticulo:false
                                                      })

                            listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                            if(modoCalculoTotal=="1"){
                                etiquetaTotal.setearTotal(precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),codigoArticulo,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                            }else if(modoCalculoTotal=="2"){
                                etiquetaTotal.setearTotalModoArticuloSinIva(precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),codigoArticulo,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                            }
                            mostrarCuadroDeActulizacionDePrecioEnFacturacion(codigoArticulo,"LATERAL")

                        }

                        }

                    }

                }else{


                    funcionesmysql.loguear("QML::No hay un cliente seleccionado")

                    var precioArticuloSelecionadoSinListaySinCliente
                    if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                        precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(codigoArticulo,1)
                    }else{
                        precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(codigoArticulo,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                    }


                    var cotizacion3=1;
                    precioArticuloDobleClic=precioArticuloSelecionadoSinListaySinCliente

                    if(modeloListaMonedas.retornaCodigoMoneda(codigoArticulo)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                        if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(codigoArticulo)){
                            cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                            precioArticuloDobleClic=precioArticuloSelecionadoSinListaySinCliente/cotizacion3
                        }else{
                            if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(codigoArticulo))
                                precioArticuloDobleClic=precioArticuloSelecionadoSinListaySinCliente*cotizacion3
                            }else{
                                precioArticuloDobleClic=(precioArticuloSelecionadoSinListaySinCliente*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(codigoArticulo)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                            }

                        }
                    }
                     costoArticuloOpcionesExtraFacturacion=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                    if(txtArticuloParaFacturacion.visible){

                        //Controlo si se peude vender sin stock previsto
                        if(modeloArticulos.retornaSiPuedeVenderSinStock(1,cbListatipoDocumentos.codigoValorSeleccion,codigoArticulo,retornaCantidadDeUnArticuloEnFacturacion(codigoArticulo))){

                        funcionesmysql.loguear("QML::modeloItemsFactura.append: ")
                        funcionesmysql.loguear("QML::codigoArticulo: "+codigoArticulo)
                        funcionesmysql.loguear("QML::precioArticulo: "+precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))

                        precioArticuloDobleClic=calcularDescuentoPorCliente(precioArticuloDobleClic)
                        modeloItemsFactura.append({
                                                      codigoArticulo:codigoArticulo,
                                                      codigoBarrasArticulo:"",
                                                      descripcionArticulo:descripcionArticulo,
                                                      descripcionArticuloExtendido:descripcionExtendida,
                                                      precioArticulo:precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                      precioArticuloSubTotal:precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                      cantidadItems:1,
                                                      costoArticuloMonedaReferencia:costoArticuloOpcionesExtraFacturacion.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                      activo:true,
                                                      consideraDescuento:false,
                                                      indiceLinea:-1,
                                                      codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(codigoArticulo),
                                                      descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(codigoArticulo)),
                                                      asignarGarantiaAArticulo:false
                                                  })

                        listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                        if(modoCalculoTotal=="1"){
                            etiquetaTotal.setearTotal(precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),codigoArticulo,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                        }else if(modoCalculoTotal=="2"){
                            etiquetaTotal.setearTotalModoArticuloSinIva(precioArticuloDobleClic.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),codigoArticulo,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                        }
                        mostrarCuadroDeActulizacionDePrecioEnFacturacion(codigoArticulo,"LATERAL")

                    }

                    }
                }
            }
        }
        }
        onClicked: {


            txtCodigoArticuloParaAgregarFacturacion.textoInputBox=codigoArticulo

            txtPrecioArticuloAgregarFacturacion.textoTitulo="Precio en "+modeloListaMonedas.retornaSimboloMoneda(modeloListaMonedas.retornaCodigoMoneda(codigoArticulo))

            if(txtCodigoClienteFacturacion.textoInputBox!=""){
                var listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(txtFechaPrecioFacturacion.textoInputBox.trim(), txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim())

                if(listaPrecioSeleccionada!=""){

                    cbListaDePreciosFacturacionOpcionesExtras.codigoValorSeleccion=listaPrecioSeleccionada
                    cbListaDePreciosFacturacionOpcionesExtras.textoComboBox=modeloListasPrecios.retornaDescripcionListaPrecio(listaPrecioSeleccionada)

                    var precioArticuloSelecionado=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(codigoArticulo,listaPrecioSeleccionada)
                    if(precioArticuloSelecionado!=""+modeloconfiguracion.retornaCantidadDecimalesString()+""){

                        txtPrecioArticuloAgregarFacturacion.textoInputBox=precioArticuloSelecionado;

                    }else{
                        txtPrecioArticuloAgregarFacturacion.textoInputBox=precioArticuloSelecionado;
                        txtPrecioArticuloAgregarFacturacion.tomarElFoco()
                    }

                }else{
                    cbListaDePreciosFacturacionOpcionesExtras.codigoValorSeleccion=1
                    cbListaDePreciosFacturacionOpcionesExtras.textoComboBox=modeloListasPrecios.retornaDescripcionListaPrecio(1)

                    txtPrecioArticuloAgregarFacturacion.textoInputBox=""+modeloconfiguracion.retornaCantidadDecimalesString()+"";
                    txtPrecioArticuloAgregarFacturacion.tomarElFoco()
                }

            }else{

                cbListaDePreciosFacturacionOpcionesExtras.codigoValorSeleccion=1
                cbListaDePreciosFacturacionOpcionesExtras.textoComboBox=modeloListasPrecios.retornaDescripcionListaPrecio(1)


                var precioArticuloSelecion=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(codigoArticulo,1)
                if(precioArticuloSelecion!=""+modeloconfiguracion.retornaCantidadDecimalesString()+""){

                    txtPrecioArticuloAgregarFacturacion.textoInputBox=precioArticuloSelecion;

                }else{
                    txtPrecioArticuloAgregarFacturacion.textoInputBox=precioArticuloSelecion;
                    txtPrecioArticuloAgregarFacturacion.tomarElFoco()
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
        id: txtItemArticuloInactivo
        x: 0
        y: 8
        color: "#d93e3e"
        horizontalAlignment: Text.AlignRight
        //
        anchors.top: parent.top
        text:"Inactivo"
        font.family: "Arial"
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.rightMargin: 20
        anchors.bottomMargin: 0
        font.bold: false
        font.pointSize: 10
        anchors.right: parent.right
        verticalAlignment: Text.AlignVCenter
        width: txtItemArticuloInactivo.implicitWidth
    }

    Text {
        id: txtStockReal
        color: "#3e58d9"
        text: "Stock real: "+modeloArticulos.retornaStockTotalArticuloReal(codigoArticulo)
        clip: true
        anchors.right: txtItemArticuloInactivo.left
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottomMargin: 0
        font.family: "Arial"
        anchors.bottom: parent.bottom
        font.bold: true
        font.pointSize: 10
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        anchors.top: txtItemArticulo.bottom
        //
        anchors.topMargin: 0
    }


}
