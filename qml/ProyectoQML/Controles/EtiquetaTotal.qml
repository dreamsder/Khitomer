/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2023>  <Cristian Montano>

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

Rectangle {
    id: rectPrincipalEtiquetaTotales
    width: 250
    height: 65
    color: "#00000000"


    property double valorTotal: 0.00
    property double valorTotalDescuento: 0.00
    property double valorIva: 0.00
    property double valorSubTotal: 0.00
    property double valorSubTotalSinDescuento: 0.00

    property double valorTotalAcumulado: 0.00
    property double valorIvaAcumulado: 0.00
    property double valorSubTotalAcumulado: 0.00
    property double valorSubTotalAcumuladoSinDescuento: 0.00
    property double valorTotalDescuentoAcumulado: 0.00

    property double valorFinalDelTotal: 0.00

    property double variableTemporalRedondeo: 0.00

    property double totalIva1: 0.00  ///Iva Basico
    property double totalIva2: 0.00  ///Iva Minimo
    property double totalIva3: 0.00  ///Iva Exento

    property alias  txtValorIvaText: txtValorIva.text
    property alias  txtValorSubTotalText: txtValorSubTotal.text
    property alias  txtValorTotalText: txtValorTotal.text
    property alias  txtvalorTotalDescuentoText: txtValorTotalDescuento.text

    property alias colorTotales : rectMontoTotales.color

    property alias labelSubTotalVisible: lblSubTotal.visible
    property alias labelIvaVisible: lblIva.visible

    property alias  colorLabelTotal: lblTotal.color

    property alias  tamanioPixelLabeltotal: lblTotal.font.pixelSize

    property alias  styleLabeltotal: lblTotal.style

    property double _descuento: 0.00

    property double _descuentoChequeoValor: 0.00

    property double _valor: 0.00


     property double _descuentoLinea: 0.00


    property alias labelTotal: lblTotal.text
    property alias labelTotalDescuentos: lblTotalDescuentos.text
    property alias descuentosVisible: rectTotalDescuentos.visible
    property alias colorTotalDescuentos : rectTotalDescuentos.color

    signal requieroPermisoParaDescuento

    function tomarElFocoCuadroDescuento(){
        forceActiveFocus()
        txtDescuentoPrevisto.forceActiveFocus()
        txtDescuentoPrevisto.tomarElFoco()
    }

    function retornaSubTotal(){

        return txtValorSubTotal.text.trim();
    }
    function retornaSubTotalSinDescuento(){

        return valorSubTotalAcumuladoSinDescuento.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString();
    }
    function retornaIvaTotal(){

        return txtValorIva.text.trim();
    }

    function retornaTotal(){

        return txtValorTotal.text.trim();
    }

    function retornaTotalDescuento(){

        return txtValorTotalDescuento.text.trim();
    }

    function retornaPorcentajeDescuento(){

        return _descuento.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString();
    }



    function retornaIva1(){

        return totalIva1.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
    }
    function retornaIva2(){

        return totalIva2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
    }
    function retornaIva3(){

        return totalIva3.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
    }

    function setearPorcenjeDescuento(porcentaje){
        _descuento=porcentaje
        txtDescuentoPrevisto.textoInputBox=_descuento.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))

    }

    //Esta funciona setea el total, cuando en la configuración el MODO_CALCULOTOTAL esta seteado en 1
    function setearTotal(valor,articulo,tipoDocumento,consideraDescuento,indice){

        /// Si articulo es -1 quiere decir que no voy a utilizar sub total ni ivas.
        if(articulo!=-1){

            if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(tipoDocumento,"noAfectaIva")){
                valorSubTotalSinDescuento=valor
            }else{
                valorSubTotalSinDescuento=valor/modeloListaIvas.retornaFactorMultiplicador(articulo)
            }


            _descuentoChequeoValor=0.00
            _descuentoChequeoValor=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
            _descuentoChequeoValor=_descuentoChequeoValor+0.00

            if(rectTotalDescuentos.visible || (_descuentoChequeoValor!=0.00 && consideraDescuento)){


                _descuento=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
                _descuento=_descuento+0.00

                valorTotalDescuento=(valor*_descuento)/100
                valorTotalDescuentoAcumulado+=valorTotalDescuento
                valor=valor-valorTotalDescuento
                txtValorTotalDescuento.text=valorTotalDescuentoAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))

               /* funcionesmysql.mensajeAdvertenciaOk("Indice: "+indice)
                funcionesmysql.mensajeAdvertenciaOk("Valor: "+valor)
                funcionesmysql.mensajeAdvertenciaOk("Descuento total: "+valorTotalDescuento)
                funcionesmysql.mensajeAdvertenciaOk("Articulo: "+articulo)
*/
                _descuentoLinea = parseFloat(modeloItemsFactura.get(indice).descuentoLineaItem)
  //              funcionesmysql.mensajeAdvertenciaOk("Descuento linea: "+_descuentoLinea)

                modeloItemsFactura.set(indice,{"descuentoLineaItem": (_descuentoLinea+valorTotalDescuento).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))})

    //            funcionesmysql.mensajeAdvertenciaOk("El descuento de la linea es: "+modeloItemsFactura.get(indice).descuentoLineaItem)
            }

            if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(tipoDocumento,"noAfectaIva")){
                //Calculo del subTotal
                valorSubTotal=valor
            }else{
                //Calculo del subTotal
                valorSubTotal=valor/modeloListaIvas.retornaFactorMultiplicador(articulo)
            }


            valorSubTotalAcumulado+=valorSubTotal
            valorSubTotalAcumuladoSinDescuento+=valorSubTotalSinDescuento

            if(valorSubTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorSubTotalAcumulado=0.00
            }
            if(valorSubTotalAcumuladoSinDescuento.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorSubTotalAcumuladoSinDescuento=0.00
            }

            txtValorSubTotal.text=valorSubTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()

            if(!modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(tipoDocumento,"noAfectaIva")){
                //Calculo del Iva
                valorIva=valor-valorSubTotal
                valorIvaAcumulado+=valorIva
            }




            if(modeloListaIvas.retornaCodigoIva(articulo)=="1"){
                totalIva1+=valorIva
            }
            if(modeloListaIvas.retornaCodigoIva(articulo)=="2"){
                totalIva2+=valorIva
            }
            if(modeloListaIvas.retornaCodigoIva(articulo)=="3"){
              //  console.log(valorIva)
              //  console.log(valor)
                totalIva3+=valor
            }


            if(valorIvaAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorIvaAcumulado=0.00
            }

            txtValorIva.text=valorIvaAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()

        }else{


            ///Acá se calcula el iva y sub total del medio de pago
            valorSubTotalSinDescuento=valor/modeloListaIvas.retornaFactorMultiplicadorIVAPorDefecto()

            //Calculo del subTotal
            valorSubTotal=valor/modeloListaIvas.retornaFactorMultiplicadorIVAPorDefecto()



            valorSubTotalAcumulado+=valorSubTotal
            valorSubTotalAcumuladoSinDescuento+=valorSubTotalSinDescuento

            if(valorSubTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorSubTotalAcumulado=0.00
            }
            if(valorSubTotalAcumuladoSinDescuento.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorSubTotalAcumuladoSinDescuento=0.00
            }

            txtValorSubTotal.text=valorSubTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()



            //Calculo del Iva
            valorIva=valor-valorSubTotal
            valorIvaAcumulado+=valorIva





            var _ivaDefault=modeloconfiguracion.retornaValorConfiguracion("IVA_DEFAULT_SISTEMA")

            if(_ivaDefault=="1"){
                totalIva1+=valorIva
            }
            if(_ivaDefault=="2"){
                totalIva2+=valorIva
            }
            if(_ivaDefault=="3"){
                totalIva3+=valor

            }


            if(valorIvaAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorIvaAcumulado=0.00
            }

            txtValorIva.text=valorIvaAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()


        }

        ///Calculo del valor TOTAL
        valorTotal=valor;
        valorTotalAcumulado+=valorTotal
        valorFinalDelTotal=valorTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))

        if(valorFinalDelTotal.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
            valorFinalDelTotal=0.00
        }

        /// Funcion de redondeo
        /// Chequeo si se usa el cuadro como medio de pago o para totales
        if(articulo!=-1){
            if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(tipoDocumento,"utilizaRedondeoEnTotal") && modeloListaTipoDocumentosComboBox.retornaDocumentoSegunMonedaRedondea(tipoDocumento,cbListaMonedasEnFacturacion.codigoValorSeleccion)){

                variableTemporalRedondeo=0.00
                variableTemporalRedondeo=valorFinalDelTotal.toFixed(0)
                txtValorTotal.text=variableTemporalRedondeo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()
                variableTemporalRedondeo=0.00


            }else{
                txtValorTotal.text=valorFinalDelTotal.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()
            }
        }else{
            txtValorTotal.text=valorFinalDelTotal.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()

        }





    }

    //Esta funciona setea el total, cuando enla configuración el MODO_CALCULOTOTAL esta seteado en 2
    function setearTotalModoArticuloSinIva(valor,articulo,tipoDocumento,consideraDescuento,indice){


        /// Si articulo es -1 quiere decir que no voy a utilizar sub total ni ivas.
        if(articulo!=-1){

            valorSubTotalSinDescuento=valor

            _descuentoChequeoValor=0.00
            _descuentoChequeoValor=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
            _descuentoChequeoValor=_descuentoChequeoValor+0.00

            if(rectTotalDescuentos.visible || (_descuentoChequeoValor!=0.00 && consideraDescuento)){



                _descuento=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
                _descuento=_descuento+0.00

                valorTotalDescuento=(valor*_descuento)/100
                valorTotalDescuentoAcumulado+=valorTotalDescuento
                valor=valor-valorTotalDescuento
                txtValorTotalDescuento.text=valorTotalDescuentoAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))

                _descuentoLinea = parseFloat(modeloItemsFactura.get(indice).descuentoLineaItem)
                modeloItemsFactura.set(indice,{"descuentoLineaItem": (_descuentoLinea+valorTotalDescuento).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))})
            }




            //Calculo del subTotal
            valorSubTotal=valor///modeloListaIvas.retornaFactorMultiplicador(articulo)
            valorSubTotalAcumulado+=valorSubTotal
            valorSubTotalAcumuladoSinDescuento+=valorSubTotalSinDescuento

            if(valorSubTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorSubTotalAcumulado=0.00
            }
            if(valorSubTotalAcumuladoSinDescuento.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorSubTotalAcumuladoSinDescuento=0.00
            }

            txtValorSubTotal.text=valorSubTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()


            if(!modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(tipoDocumento,"noAfectaIva")){
                //Calculo del Iva
                valorIva=(valor*modeloListaIvas.retornaFactorMultiplicador(articulo))-valor
                valorIvaAcumulado+=valorIva
            }




            if(modeloListaIvas.retornaCodigoIva(articulo)=="1"){
                totalIva1+=valorIva
            }
            if(modeloListaIvas.retornaCodigoIva(articulo)=="2"){
                totalIva2+=valorIva
            }
            if(modeloListaIvas.retornaCodigoIva(articulo)=="3"){
                totalIva3+=valor
            }


            if(valorIvaAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorIvaAcumulado=0.00
            }


            txtValorIva.text=valorIvaAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()

        }

        ///Calculo del valor TOTAL
        if(!modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(tipoDocumento,"noAfectaIva")){
            valorTotal=valor*modeloListaIvas.retornaFactorMultiplicador(articulo);
        }else{
            valorTotal=valor
        }


        valorTotalAcumulado+=valorTotal
        valorFinalDelTotal=valorTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))

        if(valorFinalDelTotal.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
            valorFinalDelTotal=0.00
        }

        /// Funcion de redondeo
        /// Chequeo si se usa el cuadro como medio de pago o para totales
        if(articulo!=-1){
            if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(tipoDocumento,"utilizaRedondeoEnTotal")&& modeloListaTipoDocumentosComboBox.retornaDocumentoSegunMonedaRedondea(tipoDocumento,cbListaMonedasEnFacturacion.codigoValorSeleccion)){


                variableTemporalRedondeo=0.00
                variableTemporalRedondeo=valorFinalDelTotal.toFixed(0)
                txtValorTotal.text=variableTemporalRedondeo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()
                variableTemporalRedondeo=0.00

            }else{
                txtValorTotal.text=valorFinalDelTotal.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()
            }
        }else{
            txtValorTotal.text=valorFinalDelTotal.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()
        }




    }

    function setearTotalAnulacion(valor,articulo,tipoDocumento,consideraDescuento,indice){




        /// Si articulo es -1 quiere decir que no voy a utilizar sub total ni ivas.
        if(articulo!=-1){

            if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(tipoDocumento,"noAfectaIva")){
                valorSubTotalSinDescuento=valor
            }else{
                valorSubTotalSinDescuento=valor/modeloListaIvas.retornaFactorMultiplicador(articulo)
            }

            _descuentoChequeoValor=0.00
            _descuentoChequeoValor=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
            _descuentoChequeoValor=_descuentoChequeoValor+0.00

            if(rectTotalDescuentos.visible || (_descuentoChequeoValor!=0.00 && consideraDescuento)){

                _descuento=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
                _descuento=_descuento+0.00

                valorTotalDescuento=(valor*_descuento)/100
                valorTotalDescuentoAcumulado-=valorTotalDescuento
                valor=valor-valorTotalDescuento

                if(valorTotalDescuentoAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                    valorTotalDescuentoAcumulado=0.00
                }

                txtValorTotalDescuento.text=valorTotalDescuentoAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))


                _descuentoLinea = parseFloat(modeloItemsFactura.get(indice).descuentoLineaItem)
                modeloItemsFactura.set(indice,{"descuentoLineaItem": (_descuentoLinea-valorTotalDescuento).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))})

            }

            if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(tipoDocumento,"noAfectaIva")){
                //Recalculo del subTotal
                valorSubTotal=valor
            }else{
                //Recalculo del subTotal
                valorSubTotal=valor/modeloListaIvas.retornaFactorMultiplicador(articulo)
            }



            valorSubTotalAcumulado-=valorSubTotal
            valorSubTotalAcumuladoSinDescuento-=valorSubTotalSinDescuento

            if(valorSubTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorSubTotalAcumulado=0.00
            }
            if(valorSubTotalAcumuladoSinDescuento.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorSubTotalAcumuladoSinDescuento=0.00
            }

            txtValorSubTotal.text=valorSubTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()


            if(!modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(tipoDocumento,"noAfectaIva")){
                //Recalculo del Iva
                valorIva=valor-valorSubTotal
                valorIvaAcumulado-=valorIva
            }



            if(modeloListaIvas.retornaCodigoIva(articulo)=="1"){
                totalIva1-=valorIva
            }
            if(modeloListaIvas.retornaCodigoIva(articulo)=="2"){
                totalIva2-=valorIva
            }
            if(modeloListaIvas.retornaCodigoIva(articulo)=="3"){
                totalIva3-=valor
            }

            if(valorIvaAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorIvaAcumulado=0.00
            }



            txtValorIva.text=valorIvaAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()

        }else{


            valorSubTotalSinDescuento=valor/modeloListaIvas.retornaFactorMultiplicadorIVAPorDefecto()

            if(rectTotalDescuentos.visible){
                _descuento=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
                _descuento=_descuento+0.00

                valorTotalDescuento=(valor*_descuento)/100
                valorTotalDescuentoAcumulado-=valorTotalDescuento
                valor=valor-valorTotalDescuento

                if(valorTotalDescuentoAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                    valorTotalDescuentoAcumulado=0.00
                }

                txtValorTotalDescuento.text=valorTotalDescuentoAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
            }


            //Recalculo del subTotal
            valorSubTotal=valor/modeloListaIvas.retornaFactorMultiplicadorIVAPorDefecto()


            valorSubTotalAcumulado-=valorSubTotal
            valorSubTotalAcumuladoSinDescuento-=valorSubTotalSinDescuento

            if(valorSubTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorSubTotalAcumulado=0.00
            }
            if(valorSubTotalAcumuladoSinDescuento.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorSubTotalAcumuladoSinDescuento=0.00
            }

            txtValorSubTotal.text=valorSubTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()


            //Recalculo del Iva
            valorIva=valor-valorSubTotal
            valorIvaAcumulado-=valorIva


            var _ivaDefaultAnulacion=modeloconfiguracion.retornaValorConfiguracion("IVA_DEFAULT_SISTEMA")

            if(_ivaDefaultAnulacion=="1"){
                totalIva1-=valorIva
            }
            if(_ivaDefaultAnulacion=="2"){
                totalIva2-=valorIva
            }
            if(_ivaDefaultAnulacion=="3"){
                totalIva3-=valor
            }

            if(valorIvaAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorIvaAcumulado=0.00
            }

            txtValorIva.text=valorIvaAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()
        }

        //Recalculo total
        valorTotal=valor;
        valorTotalAcumulado-=valorTotal
        valorFinalDelTotal=valorTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))


        if(valorFinalDelTotal.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
            valorFinalDelTotal=0.00
        }

        /// Funcion de redondeo
        /// Chequeo si se usa el cuadro como medio de pago o para totales
        if(articulo!=-1){
            if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(tipoDocumento,"utilizaRedondeoEnTotal")&& modeloListaTipoDocumentosComboBox.retornaDocumentoSegunMonedaRedondea(tipoDocumento,cbListaMonedasEnFacturacion.codigoValorSeleccion)){
                variableTemporalRedondeo=0.00
                variableTemporalRedondeo=valorFinalDelTotal.toFixed(0)
                txtValorTotal.text=variableTemporalRedondeo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()
                variableTemporalRedondeo=0.00
            }else{
                txtValorTotal.text=valorFinalDelTotal.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()
            }
        }else{
            txtValorTotal.text=valorFinalDelTotal.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()
        }





    }

    function setearTotalAnulacionModoArticuloSinIva(valor,articulo,tipoDocumento,consideraDescuento,indice){



        valorSubTotalSinDescuento=valor
        /// Si articulo es -1 quiere decir que no voy a utilizar sub total ni ivas.
        if(articulo!=-1){

            _descuentoChequeoValor=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
            _descuentoChequeoValor=_descuentoChequeoValor+0.00

            if(rectTotalDescuentos.visible || (_descuentoChequeoValor!=0.00 && consideraDescuento)){
                _descuento=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
                _descuento=_descuento+0.00

                valorTotalDescuento=(valor*_descuento)/100
                valorTotalDescuentoAcumulado-=valorTotalDescuento
                valor=valor-valorTotalDescuento

                if(valorTotalDescuentoAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                    valorTotalDescuentoAcumulado=0.00
                }

                txtValorTotalDescuento.text=valorTotalDescuentoAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))

                _descuentoLinea = parseFloat(modeloItemsFactura.get(indice).descuentoLineaItem)
                modeloItemsFactura.set(indice,{"descuentoLineaItem": (_descuentoLinea-valorTotalDescuento).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))})
            }

            //Recalculo del subTotal
            valorSubTotal=valor ////modeloListaIvas.retornaFactorMultiplicador(articulo)
            valorSubTotalAcumulado-=valorSubTotal
            valorSubTotalAcumuladoSinDescuento-=valorSubTotalSinDescuento

            if(valorSubTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorSubTotalAcumulado=0.00
            }
            if(valorSubTotalAcumuladoSinDescuento.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorSubTotalAcumuladoSinDescuento=0.00
            }

            txtValorSubTotal.text=valorSubTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()


            if(!modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(tipoDocumento,"noAfectaIva")){
                //Recalculo del Iva
                valorIva=(valor*modeloListaIvas.retornaFactorMultiplicador(articulo))-valor
                valorIvaAcumulado-=valorIva
            }


            if(modeloListaIvas.retornaCodigoIva(articulo)=="1"){
                totalIva1-=valorIva
            }
            if(modeloListaIvas.retornaCodigoIva(articulo)=="2"){
                totalIva2-=valorIva
            }
            if(modeloListaIvas.retornaCodigoIva(articulo)=="3"){
                totalIva3-=valor
            }


            if(valorIvaAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
                valorIvaAcumulado=0.00
            }

            txtValorIva.text=valorIvaAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()
        }

        //Recalculo total
        if(!modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(tipoDocumento,"noAfectaIva")){
            valorTotal=valor*modeloListaIvas.retornaFactorMultiplicador(articulo);
        }else{
            valorTotal=valor
        }

        valorTotalAcumulado-=valorTotal
        valorFinalDelTotal=valorTotalAcumulado.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))


        if(valorFinalDelTotal.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()=="-0"+modeloconfiguracion.retornaCantidadDecimalesString()+""){
            valorFinalDelTotal=0.00
        }

        /// Funcion de redondeo
        /// Chequeo si se usa el cuadro como medio de pago o para totales
        if(articulo!=-1){
            if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(tipoDocumento,"utilizaRedondeoEnTotal")&& modeloListaTipoDocumentosComboBox.retornaDocumentoSegunMonedaRedondea(tipoDocumento,cbListaMonedasEnFacturacion.codigoValorSeleccion)){
                variableTemporalRedondeo=0.00
                variableTemporalRedondeo=valorFinalDelTotal.toFixed(0)
                txtValorTotal.text=variableTemporalRedondeo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()
                variableTemporalRedondeo=0.00
            }else{
                txtValorTotal.text=valorFinalDelTotal.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()
            }
        }else{
            txtValorTotal.text=valorFinalDelTotal.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")).toString()
        }
    }


    function sereaTotales(){


        valorSubTotal=0.00
        valorSubTotalAcumulado=0.00
        txtValorSubTotal.text="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

        valorSubTotalSinDescuento=0.00
        valorSubTotalAcumuladoSinDescuento=0.00

        valorIva=0.00
        valorIvaAcumulado=0.00
        txtValorIva.text="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

        valorTotal=0.00
        valorTotalAcumulado=0.00
        valorFinalDelTotal=0.00
        txtValorTotal.text="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

        txtValorTotalDescuento.text="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
        valorTotalDescuento=0.00
        valorTotalDescuentoAcumulado=0.00

        totalIva1=0.00
        totalIva2=0.00
        totalIva3=0.00
        txtDescuentoPrevisto.textoInputBox="000.00"


    }


    function sereaTotalesSinDescuento(){


        valorSubTotal=0.00
        valorSubTotalAcumulado=0.00
        txtValorSubTotal.text="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

        valorSubTotalSinDescuento=0.00
        valorSubTotalAcumuladoSinDescuento=0.00

        valorIva=0.00
        valorIvaAcumulado=0.00
        txtValorIva.text="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

        valorTotal=0.00
        valorTotalAcumulado=0.00
        valorFinalDelTotal=0.00
        txtValorTotal.text="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

        txtValorTotalDescuento.text="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
        valorTotalDescuento=0.00
        valorTotalDescuentoAcumulado=0.00

        totalIva1=0.00
        totalIva2=0.00
        totalIva3=0.00


    }



    MouseArea {
        id: mouse_area1
        anchors.fill: parent

        Rectangle {
            id: rectMontoTotales
            color: "#db4d4d"
            radius: 3
            opacity: 1
            //
            anchors.left: parent.left
            anchors.leftMargin: 67
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            Text {
                id: txtValorTotal
                y: 37
                color: "#ffffff"
                text: "0.00"
                font.family: "Arial"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 2
                //
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignRight
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 15
                font.pixelSize: 23
                style: Text.Sunken
                font.bold: true
            }

            Text {
                id: txtValorIva
                y: 25
                color: "#bbb7b7"
                text: "0.00"
                font.family: "Arial"
                horizontalAlignment: Text.AlignRight
                anchors.right: parent.right
                anchors.rightMargin: 15
                anchors.left: parent.left
                anchors.leftMargin: 5
                //
                font.pixelSize: 11
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                font.bold: true
                visible: lblIva.visible
            }

            Text {
                id: txtValorSubTotal
                x: 5
                y: 5
                color: "#bbb7b7"
                text: "0.00"
                font.family: "Arial"
                //
                font.pixelSize: 11
                anchors.bottom: parent.bottom
                anchors.rightMargin: 15
                anchors.bottomMargin: 50
                font.bold: true
                anchors.right: parent.right
                anchors.leftMargin: 5
                horizontalAlignment: Text.AlignRight
                anchors.left: parent.left
                visible: lblSubTotal.visible
            }
        }

        Text {
            id: lblIva
            x: 33
            y: 20
            color: "#bbb7b7"
            text: qsTr("I.V.A.")
            font.family: "Arial"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            //
            anchors.right: rectMontoTotales.left
            anchors.rightMargin: 5
            font.pixelSize: 11
            font.bold: true
        }

        Text {
            id: lblSubTotal
            x: 11
            y: 0
            color: "#bbb7b7"
            text: qsTr("Subtotal")
            font.family: "Arial"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            //
            anchors.right: rectMontoTotales.left
            anchors.rightMargin: 5
            font.pixelSize: 11
            font.bold: true
        }

        Text {
            id: lblTotal
            x: -49
            y: 35
            color: "#ffffff"
            text: qsTr("Total U$S")
            font.family: "Arial"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            //
            style: Text.Sunken
            anchors.right: rectMontoTotales.left
            anchors.rightMargin: 5
            font.bold: true
            font.pixelSize: 21
        }

        Rectangle {
            id: rectTotalDescuentos
            y: -83
            width: 183
            color: "#e48c25"
            radius: 3
            clip: true
            visible: false
            //
            anchors.top: parent.top
            anchors.topMargin: 0
            enabled: true//cbListaMonedasEnFacturacion.enabled
            Text {
                id: txtValorTotalDescuento
                y: 37
                color: "#ffffff"
                text: "0.00"
                //
                font.pixelSize: 23
                anchors.bottom: parent.bottom
                style: Text.Sunken
                anchors.rightMargin: 15
                anchors.bottomMargin: 2
                font.family: "Arial"
                font.bold: true
                anchors.right: parent.right
                horizontalAlignment: Text.AlignRight
                anchors.leftMargin: 5
                verticalAlignment: Text.AlignTop
                anchors.left: parent.left
            }

            TextInputSimple {
                id: txtDescuentoPrevisto
                enFocoSeleccionarTodo: true
                textoInputBox: "000.00"
                inputMask: "000.00%; "
                largoMaximo: 6
                textoTitulo: ""
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 40
                anchors.right: parent.right
                anchors.rightMargin: -15
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 5
                validaFormato: validacionMontoPorcentaje
                onTabulacion: {
                    if(parseFloat(textoInputBox)!=0){
                        _descuento=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
                        _descuento=_descuento+0.00
                        setearPorcenjeDescuento(_descuento)
                        requieroPermisoParaDescuento()
                    }else{
                        _descuento=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
                        _descuento=_descuento+0.00
                        setearPorcenjeDescuento(_descuento)
                        requieroPermisoParaDescuento()
                        if(txtArticuloParaFacturacion.visible)
                            txtArticuloParaFacturacion.tomarElFocoP()
                    }
                }
                onEnter: {
                    if(parseFloat(textoInputBox)!=0){
                        _descuento=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
                        _descuento=_descuento+0.00
                        setearPorcenjeDescuento(_descuento)
                        requieroPermisoParaDescuento()
                    }else{
                        _descuento=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
                        _descuento=_descuento+0.00
                        setearPorcenjeDescuento(_descuento)
                        requieroPermisoParaDescuento()

                        if(txtArticuloParaFacturacion.visible)
                            txtArticuloParaFacturacion.tomarElFocoP()
                    }
                }

                onTextoInputBoxChanged: {

                    if(textoInputBox==".%"){
                        textoInputBox="000.00"
                        tomarElFoco()
                    }

                    if(rectTotalDescuentos.visible){

                        var _valor=parseFloat(textoInputBox)
                        if(_valor>100){
                            textoInputBox="100.00"
                        }


                    }
                }
                onPierdoFoco: {
                    if(parseFloat(textoInputBox)!=0){
                        _descuento=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
                        _descuento=_descuento+0.00
                        setearPorcenjeDescuento(_descuento)
                        requieroPermisoParaDescuento()
                    }else{
                        _descuento=parseFloat(txtDescuentoPrevisto.textoInputBox.trim().replace("%","0"))
                        _descuento=_descuento+0.00
                        setearPorcenjeDescuento(_descuento)
                        requieroPermisoParaDescuento()
                    }

                }
            }


            RegExpValidator{
                id:validacionMontoPorcentaje
                regExp: new RegExp( "([0-1, ][0-9, ][0-9, ]\.[0-9, ][0-9, ])\%" )
            }

            anchors.bottom: parent.bottom
            anchors.rightMargin: 50
            anchors.bottomMargin: 0
            anchors.right: lblTotal.left
            opacity: 1
        }

        Text {
            id: lblTotalDescuentos
            x: -248
            y: 36
            color: "#ffffff"
            text: qsTr("Descuento U$S")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            //
            font.pixelSize: 21
            style: Text.Sunken
            anchors.rightMargin: 5
            font.family: "Arial"
            font.bold: true
            anchors.right: rectTotalDescuentos.left
            visible: rectTotalDescuentos.visible
        }
    }
}
