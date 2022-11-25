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

import QtQuick 1.1
import "Controles"
import "Listas"
import "Listas/Delegates"

Rectangle {
    id: rectPrincipalMantenimiento
    width: 1000
    height: 800
    color: "#ffffff"
    radius: 8
    //





    property string codigobarrasademandaextendido: "0"


    property double valorPrecioArticulo: 0.00
    property double valorPrecioArticulo2: 0.00
    property double valorPrecioArticuloRecalculoTotal: 0.00
    property double valorReutilizar: 0.00
    property double costoArticulo : 0.00
    property double cantidadItemsVendidos: 0.00
    property double montoDelMedioDePago: 0.0
    property string valorArticuloInterno:""

    property string nuevoDocumento: ""

    property string codigoDeBarraArticulo:""

    property alias botonNuevaFacturaVisible : botonNuevaFactura.visible
    property alias botonGuardarFacturaEmitirVisible : botonGuardarFacturaEmitir.visible
    property alias botonGuardarFacturaPendienteVisible : botonGuardarFacturaPendiente.visible


    property alias codigoClienteInputMask: txtCodigoClienteFacturacion.inputMask
    property alias codigoClienteOpcionesExtrasInputMask: txtCodigoClienteFacturacionOpcionesExtras.inputMask

    property double montoDelPago: 0.00
    property double montoDelSaldo: 0.00
    property double montoADescontarFactura: 0.00


    property string numeroDocumentoCFEADevolver: ""
    property string tipoDocumentoCFEADevolver: ""
    property string fechaDocumentoCFEADevolver: ""

    property string codigoTipoDocumentoUsadoAnteriormente: "1"


    property bool esUnDocumentoDeVenta: false
    property bool elDocumentoUsaArticulos: false




    function guardarFacturaPendiente(){

        var resultadoInsertDocumento=0;



        if(!txtSerieFacturacion.visible && txtSerieFacturacion.textoInputBox.trim()==""){

            txtSerieFacturacion.textoInputBox=modeloListaTipoDocumentosComboBox.retornaSerieTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion)

        }


        if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaCliente")){
            if(txtCodigoClienteFacturacion.textoInputBox.trim()=="" || lblRazonSocialCliente.text.trim()==""){
                resultadoInsertDocumento=-5;
            }else{
                if(!modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")){
                    if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")){
                        if(listaDeMediosDePagoSeleccionados.count==0){
                            resultadoInsertDocumento=-5;
                        }
                    }
                }
            }
        }else if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")){
            if(listaDeItemsFactura.count==0){
                resultadoInsertDocumento=-5;
            }
        }else if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")){
            if(listaDeMediosDePagoSeleccionados.count==0){
                resultadoInsertDocumento=-5;
            }
        }

        if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")){
            if(listaDeMediosDePagoSeleccionados.count==0){
                if(!funcionesmysql.mensajeAdvertencia("No se ingresaron medios de pago, desea guardar de todos modos el documento?\n\nPresione [ Sí ] para confirmar.")){
                    resultadoInsertDocumento=-11
                }
            }
        }


        if(modeloconfiguracion.retornaValorConfiguracion("UTILIZA_CONTROL_CLIENTE_CREDITO")=="1"){
            if(txtCodigoClienteFacturacion.textoInputBox.trim()!="" && lblRazonSocialCliente.text.trim()!=""){
                if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"afectaCuentaCorriente")!="0"){
                    if(modeloClientes.retornaSiPermiteFacturaCredito(txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion)==false){
                        resultadoInsertDocumento=-12
                    }
                }
            }
        }



        if(resultadoInsertDocumento==0){


            if(!txtNumeroDocumentoFacturacion.visible && txtNumeroDocumentoFacturacion.textoInputBox.trim()==""){

                txtNumeroDocumentoFacturacion.textoInputBox=modeloDocumentos.retornoCodigoUltimoDocumentoDisponible(cbListatipoDocumentos.codigoValorSeleccion)
            }

            if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago") &&
                    modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")){



                resultadoInsertDocumento =modeloDocumentos.guardarDocumentos(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim().toUpperCase(),
                                                                             txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion,cbListaMonedasEnFacturacion.codigoValorSeleccion,
                                                                             txtFechaDocumentoFacturacion.textoInputBox.trim(),etiquetaTotal.retornaTotal(),etiquetaTotal.retornaSubTotal(),
                                                                             etiquetaTotal.retornaIvaTotal(),cbListaLiquidacionesFacturacion.codigoValorSeleccion,txtVendedorDeFactura.codigoValorSeleccion,txtNombreDeUsuario.textoInputBox.trim(),
                                                                             "PENDIENTE",cbListaLiquidacionesFacturacion.codigoValorSeleccionExtra,etiquetaTotal.retornaIva1(),etiquetaTotal.retornaIva2(),etiquetaTotal.retornaIva3(),modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion),txtObservacionesFactura.textoInputBox.trim(),txtComentariosFactura.textoInputBox.trim(),
                                                                             cbxAfectaCuentaBancaria.codigoValorSeleccion,cbxAfectaCuentaBancaria.codigoValorSeleccion2,
                                                                             etiquetaTotal.retornaTotalDescuento(),etiquetaTotal.retornaSubTotalSinDescuento(),cbListaFormasDePago.textoComboBox.trim(),etiquetaTotal.retornaPorcentajeDescuento(),etiquetaTotalMedioDePago.retornaTotal());



            }else if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago") &&
                     modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")==false){

                resultadoInsertDocumento =modeloDocumentos.guardarDocumentos(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim().toUpperCase(),
                                                                             txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion,cbListaMonedasEnFacturacion.codigoValorSeleccion,
                                                                             txtFechaDocumentoFacturacion.textoInputBox.trim(),etiquetaTotalMedioDePago.retornaTotal(),etiquetaTotalMedioDePago.retornaSubTotal(),
                                                                             etiquetaTotalMedioDePago.retornaIvaTotal(),cbListaLiquidacionesFacturacion.codigoValorSeleccion,txtVendedorDeFactura.codigoValorSeleccion,txtNombreDeUsuario.textoInputBox.trim(),
                                                                             "PENDIENTE",cbListaLiquidacionesFacturacion.codigoValorSeleccionExtra,etiquetaTotalMedioDePago.retornaIva1(),etiquetaTotalMedioDePago.retornaIva2(),etiquetaTotalMedioDePago.retornaIva3(),modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion),txtObservacionesFactura.textoInputBox.trim(),txtComentariosFactura.textoInputBox.trim(),
                                                                             cbxAfectaCuentaBancaria.codigoValorSeleccion,cbxAfectaCuentaBancaria.codigoValorSeleccion2,
                                                                             etiquetaTotal.retornaTotalDescuento(),etiquetaTotal.retornaSubTotalSinDescuento(),cbListaFormasDePago.textoComboBox.trim(),etiquetaTotal.retornaPorcentajeDescuento(),etiquetaTotalMedioDePago.retornaTotal());


            }else if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")==false &&
                     modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")){

                resultadoInsertDocumento =modeloDocumentos.guardarDocumentos(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim().toUpperCase(),
                                                                             txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion,cbListaMonedasEnFacturacion.codigoValorSeleccion,
                                                                             txtFechaDocumentoFacturacion.textoInputBox.trim(),etiquetaTotal.retornaTotal(),etiquetaTotal.retornaSubTotal(),
                                                                             etiquetaTotal.retornaIvaTotal(),cbListaLiquidacionesFacturacion.codigoValorSeleccion,txtVendedorDeFactura.codigoValorSeleccion,txtNombreDeUsuario.textoInputBox.trim(),
                                                                             "PENDIENTE",cbListaLiquidacionesFacturacion.codigoValorSeleccionExtra,etiquetaTotal.retornaIva1(),etiquetaTotal.retornaIva2(),etiquetaTotal.retornaIva3(),modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion),txtObservacionesFactura.textoInputBox.trim(),txtComentariosFactura.textoInputBox.trim(),
                                                                             cbxAfectaCuentaBancaria.codigoValorSeleccion,cbxAfectaCuentaBancaria.codigoValorSeleccion2,
                                                                             etiquetaTotal.retornaTotalDescuento(),etiquetaTotal.retornaSubTotalSinDescuento(),cbListaFormasDePago.textoComboBox.trim(),etiquetaTotal.retornaPorcentajeDescuento(),etiquetaTotalMedioDePago.retornaTotal());
            }

            txtMensajeInformacion .visible=true
            txtMensajeInformacionTimer.stop()
            txtMensajeInformacionTimer.start()

            if(resultadoInsertDocumento==1){

                if(modeloDocumentos.eliminarLineaDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion, txtSerieFacturacion.textoInputBox.trim())){

                    var cantidad=1;
                    var estatusProcesoLineas=true;
                    var estatusProcesoMedioDePago=true;

                    var costoPonderado=0.00;
                    var esDocumentoValidoParaCalculoPonderado=modeloDocumentos.documentoValidoParaCalculoPonderado(cbListatipoDocumentos.codigoValorSeleccion);


                    var _insertLineasDocumentos="insert INTO DocumentosLineas (codigoDocumento, codigoTipoDocumento, serieDocumento , numeroLinea, codigoArticulo, codigoArticuloBarras, cantidad, precioTotalVenta, precioArticuloUnitario, precioIvaArticulo,costoArticuloMonedaReferencia,costoArticuloPonderado,montoDescuento,codigoTipoGarantia)values"

                    for(var i=0; i<modeloItemsFactura.count;i++){

                        cantidad=modeloItemsFactura.get(i).cantidadItems

                        if(modeloItemsFactura.get(i).asignarGarantiaAArticulo)
                            modeloArticulos.actualizarGarantia(modeloItemsFactura.get(i).codigoArticulo,modeloItemsFactura.get(i).codigoTipoGarantia);

                        if(esDocumentoValidoParaCalculoPonderado){
                            ///codigoArticulo, cantidad, costoTotal
                            costoPonderado = modeloDocumentos.retonaCostoPonderadoSegunStock(modeloItemsFactura.get(i).codigoArticulo,cantidad,modeloItemsFactura.get(i).costoArticuloMonedaReferencia)
                        }else{
                            costoPonderado=0.00
                        }


                        if(i==0){
                            _insertLineasDocumentos+="('"+txtNumeroDocumentoFacturacion.textoInputBox.trim()+"','"+cbListatipoDocumentos.codigoValorSeleccion+"','"+txtSerieFacturacion.textoInputBox.trim()+"','"+i.toString()+"','"+modeloItemsFactura.get(i).codigoArticulo+"','"+modeloItemsFactura.get(i).codigoBarrasArticulo+"','"+cantidad+"','"+(modeloItemsFactura.get(i).precioArticulo*cantidad)+"','"+modeloItemsFactura.get(i).precioArticulo+"','"+((modeloItemsFactura.get(i).precioArticulo*cantidad) - ((modeloItemsFactura.get(i).precioArticulo*cantidad)/modeloListaIvas.retornaFactorMultiplicador(modeloItemsFactura.get(i).codigoArticulo)))+"','"+modeloItemsFactura.get(i).costoArticuloMonedaReferencia+"','"+costoPonderado+"','"+modeloItemsFactura.get(i).descuentoLineaItem+"','"+modeloItemsFactura.get(i).codigoTipoGarantia+"')"
                            modeloDocumentos.marcoArticulosincronizarWeb(modeloItemsFactura.get(i).codigoArticulo)
                        }else{
                            _insertLineasDocumentos+=",('"+txtNumeroDocumentoFacturacion.textoInputBox.trim()+"','"+cbListatipoDocumentos.codigoValorSeleccion+"','"+txtSerieFacturacion.textoInputBox.trim()+"','"+i.toString()+"','"+modeloItemsFactura.get(i).codigoArticulo+"','"+modeloItemsFactura.get(i).codigoBarrasArticulo+"','"+cantidad+"','"+(modeloItemsFactura.get(i).precioArticulo*cantidad)+"','"+modeloItemsFactura.get(i).precioArticulo+"','"+((modeloItemsFactura.get(i).precioArticulo*cantidad) - ((modeloItemsFactura.get(i).precioArticulo*cantidad)/modeloListaIvas.retornaFactorMultiplicador(modeloItemsFactura.get(i).codigoArticulo)))+"','"+modeloItemsFactura.get(i).costoArticuloMonedaReferencia+"','"+costoPonderado+"','"+modeloItemsFactura.get(i).descuentoLineaItem+"','"+modeloItemsFactura.get(i).codigoTipoGarantia+"')"
                            modeloDocumentos.marcoArticulosincronizarWeb(modeloItemsFactura.get(i).codigoArticulo)
                        }

                    }



                    if(modeloItemsFactura.count!=0)
                        if(!modeloDocumentos.guardarLineaDocumento(_insertLineasDocumentos))
                            estatusProcesoLineas=false;


                    //Si guardo las lineas de venta correctamente procedo a informar que se guardo correctamente.
                    if(estatusProcesoLineas){


                        // Comienzo el guardado de los medios de pago seleccionados.
                        if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")){
                            if(modeloListaMediosDePagoAgregados.count==0){
                                modeloMediosDePago.eliminarLineaMedioDePagoDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim());
                                estatusProcesoMedioDePago=true;
                            }else{

                                if(modeloMediosDePago.eliminarLineaMedioDePagoDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim())){
                                    for(var i=0; i<modeloListaMediosDePagoAgregados.count;i++){

                                        if(modeloMediosDePago.guardarLineaMedioDePago(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,
                                                                                      i.toString(),modeloListaMediosDePagoAgregados.get(i).codigoMedioDePago,
                                                                                      modeloListaMediosDePagoAgregados.get(i).monedaMedioPago,
                                                                                      modeloListaMediosDePagoAgregados.get(i).montoMedioDePago,
                                                                                      modeloListaMediosDePagoAgregados.get(i).cantidadCuotas,
                                                                                      modeloListaMediosDePagoAgregados.get(i).numeroBanco,
                                                                                      modeloListaMediosDePagoAgregados.get(i).codigoTarjetaCredito,
                                                                                      modeloListaMediosDePagoAgregados.get(i).numeroCheque,
                                                                                      modeloListaMediosDePagoAgregados.get(i).tipoCheque,
                                                                                      modeloListaMediosDePagoAgregados.get(i).fechaCheque,
                                                                                      modeloListaMediosDePagoAgregados.get(i).codigoDoc,
                                                                                      modeloListaMediosDePagoAgregados.get(i).codigoTipoDoc,
                                                                                      modeloListaMediosDePagoAgregados.get(i).numeroLineaDocumento,
                                                                                      modeloListaMediosDePagoAgregados.get(i).numeroCuentaBancariaAgregado,
                                                                                      modeloListaMediosDePagoAgregados.get(i).numeroBancoCuentaBancaria,
                                                                                      txtSerieFacturacion.textoInputBox.trim()
                                                                                      )){

                                            if(modeloListaMediosDePagoAgregados.get(i).esDiferido){
                                                if(!modeloLineasDePagoListaChequesDiferidosComboBox.actualizarLineaDePagoChequeDiferido(modeloListaMediosDePagoAgregados.get(i).codigoDoc, modeloListaMediosDePagoAgregados.get(i).codigoTipoDoc,  modeloListaMediosDePagoAgregados.get(i).numeroLineaDocumento,modeloListaMediosDePagoAgregados.get(i).montoMedioDePago,modeloListaMediosDePagoAgregados.get(i).serieDoc)){
                                                    estatusProcesoMedioDePago=false;
                                                    break;
                                                }
                                            }
                                        }else{
                                            estatusProcesoMedioDePago=false;
                                            break;
                                        }
                                    }
                                }else{
                                    estatusProcesoMedioDePago=false;
                                }
                            }
                        }
                        if(estatusProcesoMedioDePago){
                            modeloLineasDePagoListaChequesDiferidosComboBox.limpiarListaLineasDePago()
                            modeloLineasDePagoListaChequesDiferidosComboBox.buscarLineasDePagoChequesDiferidos("1=","1")

                            txtMensajeInformacion.color="#2f71a0"
                            txtMensajeInformacion.text="El documento "+txtNumeroDocumentoFacturacion.textoInputBox.trim()+" se guardo correctamente"
                            crearNuevaFactura()
                            cuadroListaDocumentosNuevo.visible=modeloconfiguracion.retornaModoAvisoDocumentosNuevoVisible();
                        }else{
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="ATENCION: No se pudieron guardar los medios de pago. Intente nuevamente."
                        }
                    }else{
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: No se pudieron grabar las lineas de factura. Intente nuevamente"
                    }
                }else{
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="ATENCION: No se pudieron grabar las lineas de factura. Intente nuevamente"
                }

            }else if(resultadoInsertDocumento==-1){
                txtMensajeInformacion.color="#d93e3e"
                txtMensajeInformacion.text="ATENCION: No se pudo conectar a la base de datos"


            }else if(resultadoInsertDocumento==-2){
                txtMensajeInformacion.color="#d93e3e"
                txtMensajeInformacion.text="ATENCION: Documento existente con estado invalido. Llame al soporte tecnico"


            }else if(resultadoInsertDocumento==-3){
                txtMensajeInformacion.color="#d93e3e"
                txtMensajeInformacion.text="ATENCION: No se pudo guardar el documento"


            }else if(resultadoInsertDocumento==-4){
                txtMensajeInformacion.color="#d93e3e"
                txtMensajeInformacion.text="ATENCION: No se pudo realizar la consulta a la base de datos"


            }else if(resultadoInsertDocumento==-5){
                txtMensajeInformacion.color="#d93e3e"
                txtMensajeInformacion.text="ATENCION: Faltan datos para guardar el documento. Verifique antes de continuar"

            }
            else if(resultadoInsertDocumento==-6){
                txtMensajeInformacion.color="#d93e3e"
                txtMensajeInformacion.text="ATENCION: El documento ya existe en estado cancelado. Verifique antes de continuar"
            }
            else if(resultadoInsertDocumento==-7){
                txtMensajeInformacion.color="#d93e3e"
                txtMensajeInformacion.text="ATENCION: El documento ya existe como emitido/impreso/finalizado. Verifique antes de continuar"
            }
            else if(resultadoInsertDocumento==-8){
                txtMensajeInformacion.color="#d93e3e"
                txtMensajeInformacion.text="ATENCION: El documento ya existe como guardado/finalizado. Verifique antes de continuar"
            }
            else if(resultadoInsertDocumento==-9){
                txtMensajeInformacion.color="#d93e3e"
                txtMensajeInformacion.text="ATENCION: El documento ya existe en proceso de guardado en otra instancia de Khitomer"
            }
            else if(resultadoInsertDocumento==-10){
                txtMensajeInformacion.color="#d93e3e"
                txtMensajeInformacion.text="ATENCION: No se realizaron cambios en el documento existente como pendiente"
            }
        }
        else if(resultadoInsertDocumento==-11){
            /// Esta es la salida para cuando el medio de pago no fue ingresado
            if(!contenedorFlipable.flipped){
                btnAgregarMediosDePago.texto="medios de pago"
                contenedorFlipable.flipped = !contenedorFlipable.flipped
            }
        }
        else if(resultadoInsertDocumento==-12){
            setearEstadoActivoBotonesGuardar(false)
            funcionesmysql.mensajeAdvertenciaOk("El cliente no esta habilitado para documentos CRÉDITO.\n\n No se podrá emitir el documento ni guardarlo.")
        }
        else{
            txtMensajeInformacion .visible=true
            txtMensajeInformacionTimer.stop()
            txtMensajeInformacionTimer.start()
            txtMensajeInformacion.color="#d93e3e"
            txtMensajeInformacion.text="ATENCION: Faltan datos para guardar el documento. Verifique antes de continuar"
        }

    }




    function setearFormaDePagoYMonedaDefaulCliente(){


        var borrarArticulosPorMoneda=false;
        var borrarArticulosPorTipoDocumento=false;

        var monedaDefaulCliente=modeloClientes.retornaDatoGenericoCliente(txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion,"codigoMonedaDefault");
        var formaDePagoDefaulCliente=modeloClientes.retornaDatoGenericoCliente(txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion,"codigoFormasDePagoDefault");
        var tipoDocumentoDefaulCliente=modeloClientes.retornaDatoGenericoCliente(txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion,"codigoTipoDocumentoDefault");

        // Seteo la forma de pago por defecto para el cliente
        if(formaDePagoDefaulCliente!="0" && modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaFormaDePago")){
            if(cbListaFormasDePago.visible){
                cbListaFormasDePago.codigoValorSeleccion=formaDePagoDefaulCliente
                cbListaFormasDePago.textoComboBox=modeloFormasDePago.retornaDescripcionFormaDePago(formaDePagoDefaulCliente)
            }
        }


        if(monedaDefaulCliente!="0" && modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaMoneda")){
            if(cbListaMonedasEnFacturacion.codigoValorSeleccion!=monedaDefaulCliente){
                // si hay articulo, aviso que voy a borrarlos
                if(modeloItemsFactura.count!=0){
                    borrarArticulosPorMoneda=true
                }
                cbListaMonedasEnFacturacion.codigoValorSeleccion=monedaDefaulCliente
                cbListaMonedasEnFacturacion.textoComboBox=modeloMonedas.retornaDescripcionMoneda(monedaDefaulCliente)
                cbListaMonedasEnFacturacion.aceptarOClic()
                borrarArticulos()
            }
        }


        if(tipoDocumentoDefaulCliente!="0" &&  modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaTipoDocumentoDefault")){
            if(cbListatipoDocumentos.codigoValorSeleccion!=tipoDocumentoDefaulCliente){
                if(modeloItemsFactura.count!=0){

                    borrarArticulosPorTipoDocumento=true

                }
                if(esUnDocumentoDeVenta && elDocumentoUsaArticulos){
                    cbListatipoDocumentos.codigoValorSeleccion=tipoDocumentoDefaulCliente
                    cbListatipoDocumentos.textoComboBox=modeloListaTipoDocumentosComboBox.retornaDescripcionTipoDocumento(tipoDocumentoDefaulCliente)
                    borrarArticulos()
                }else{
                    borrarArticulosPorTipoDocumento=false
                }




            }
        }

        if(borrarArticulosPorMoneda && borrarArticulosPorTipoDocumento){
            funcionesmysql.mensajeAdvertenciaOk("Se van a borrar los artículos ya facturados,\nel nuevo cliente tiene un tipo de documento diferente al documento actual y una moneda diferente a la actual.")
        }else if (borrarArticulosPorMoneda && !borrarArticulosPorTipoDocumento){
            funcionesmysql.mensajeAdvertenciaOk("Se van a borrar los artículos ya facturados,\nel nuevo cliente tiene una moneda diferente a la del documento actual.")
        }else if(!borrarArticulosPorMoneda && borrarArticulosPorTipoDocumento){
            funcionesmysql.mensajeAdvertenciaOk("Se van a borrar los artículos ya facturados,\nel nuevo cliente tiene un tipo de documento diferente al documento actual.")
        }





    }



    function retornaCantidadDeUnArticuloEnFacturacion(articuloEnFacturacion){


        var cantidadArticuloEnVenta=0
        for(var i=0; i<modeloItemsFactura.count;i++){


            if(modeloItemsFactura.get(i).codigoArticulo===articuloEnFacturacion){

                cantidadArticuloEnVenta+=modeloItemsFactura.get(i).cantidadItems;

            }
        }
        return cantidadArticuloEnVenta;
    }


    function recalcularTotales(){

        etiquetaTotal.sereaTotalesSinDescuento()

        var modoCalculoTotalRecalculo=modeloconfiguracion.retornaValorConfiguracion("MODO_CALCULOTOTAL");

        for(var i=0; i<modeloItemsFactura.count;i++){

            valorPrecioArticuloRecalculoTotal=(modeloItemsFactura.get(i).precioArticulo)*modeloItemsFactura.get(i).cantidadItems

            modeloItemsFactura.set(i,{"descuentoLineaItem": 0})


            if(modoCalculoTotalRecalculo=="1"){
                etiquetaTotal.setearTotal(valorPrecioArticuloRecalculoTotal.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),modeloItemsFactura.get(i).codigoArticulo,cbListatipoDocumentos.codigoValorSeleccion,false,i )
            }else if(modoCalculoTotalRecalculo=="2"){
                etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticuloRecalculoTotal.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),modeloItemsFactura.get(i).codigoArticulo,cbListatipoDocumentos.codigoValorSeleccion,false,i)
            }
        }

    }

    //(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),


    /*

                                            modeloItemsFactura.append({
                                                                          codigoArticulo:valorArticuloInterno,
                                                                          codigoBarrasArticulo:"",
                                                                          descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                          descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                          precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          cantidadItems:1,
                                                                          costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          activo:true,
                                                                          consideraDescuento:false,
                                                                          indiceLinea:-1,
                                                                          descuentoLineaItem:0,
                                                                          codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                          descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno))
                                                                      })*/




    //Setea el tipo de documento desde una llamada externa
    function setearTipoDeDocumento(_codigoTipoDocumento,_observaciones){
        cbListatipoDocumentos.codigoValorSeleccion=_codigoTipoDocumento
        cbListatipoDocumentos.textoComboBox=modeloListaTipoDocumentosComboBox.retornaDescripcionTipoDocumento(_codigoTipoDocumento)
        txtObservacionesFactura.textoInputBox=_observaciones
    }

    /// Funciona para agregar un nuevo medio de pago a la lista de selecionados
    /// Se debe incluir monto, y cuota si el medio de pago lo requiere.


    function mostrarCuadroDeActulizacionDePrecioEnFacturacion(codigoArticuloAModificar,llamado){

        //si el llamado es desde el menu lateral(LATERAL)

        if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaSeteoDePreciosEnListasDePrecioPorArticulo")){
            if(llamado=="LATERAL"){
                rectOpcionesExtrasArticulosFacturacionAparecer.stop()
                rectOpcionesExtrasArticulosFacturacionDesaparecer.start()
                menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
            }
            cuadroListaArticulosACambiarElPrecio.cargarPrecioDeArticulo(codigoArticuloAModificar)

            cuadroListaArticulosACambiarElPrecio.visible=true
            cuadroListaArticulosACambiarElPrecio.forceActiveFocus()
        }
    }






    function cargarDocumentosConDeuda(){

        cbListaDocumentosCuentaCorrienteConDeuda.cerrarComboBox()
        if(cbListaDocumentosCuentaCorrienteConDeuda.visible){


            modeloComboBoxDocumentosConSaldoCuentaCorriente.limpiarListaDocumentos()
            modeloComboBoxDocumentosConSaldoCuentaCorriente.buscarDocumentosAPagarCuentaCorriente(cbListaMonedasEnFacturacion.codigoValorSeleccion,txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion);

            cbListaDocumentosCuentaCorrienteConDeuda.modeloItems=modeloListaTipoDocumentosConDeudaVirtual
            modeloListaTipoDocumentosConDeudaVirtual.clear()

            for(var i=0; i<modeloComboBoxDocumentosConSaldoCuentaCorriente.rowCount();i++){



                modeloListaTipoDocumentosConDeudaVirtual.append({
                                                                    codigoItem: modeloComboBoxDocumentosConSaldoCuentaCorriente.retornaCodigoDocumentoPorIndice(i),
                                                                    descripcionItem: modeloListaTipoDocumentosComboBox.retornaDescripcionTipoDocumento(modeloComboBoxDocumentosConSaldoCuentaCorriente.retornaCodigoTipoDocumentoPorIndice(i))+"("+modeloComboBoxDocumentosConSaldoCuentaCorriente.retornaCodigoDocumentoPorIndice(i)+")",
                                                                    checkBoxActivo: false,
                                                                    codigoTipoItem:modeloComboBoxDocumentosConSaldoCuentaCorriente.retornaCodigoTipoDocumentoPorIndice(i),
                                                                    descripcionItemSegundafila:"Saldo: "+ modeloMonedas.retornaSimboloMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)+" " +modeloComboBoxDocumentosConSaldoCuentaCorriente.retornaSaldoCuentaCorrientePorIndice(i) ,
                                                                    valorItem:modeloComboBoxDocumentosConSaldoCuentaCorriente.retornaSaldoCuentaCorrientePorIndice(i),
                                                                    serieDoc: modeloComboBoxDocumentosConSaldoCuentaCorriente.retornaSerieDocumentoPorIndice(i)
                                                                })

            }

            cbListaDocumentosCuentaCorrienteConDeuda.setearMensajeDeCantidad()
        }else{
            modeloListaTipoDocumentosConDeudaVirtual.clear()
        }
    }


    function actualizarCuentaCorriente(_numeroDocumentoRecibo,_tipoDocumentoRecibo, _codigoiClienteRecibo,_codigoTipoclienteRecibo,_codigoMonedaRecibo,_totalAPagar,_serieDocumentoRecibo){

        montoDelPago= _totalAPagar

        for(var i=0; i<modeloListaTipoDocumentosConDeudaVirtual.count;i++){
            montoDelSaldo=0.00
            montoADescontarFactura=0.00

            if(modeloListaTipoDocumentosConDeudaVirtual.get(i).checkBoxActivo && montoDelPago.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))!=0.00){
                montoDelSaldo=modeloListaTipoDocumentosConDeudaVirtual.get(i).valorItem;

                if(montoDelSaldo>montoDelPago){
                    montoADescontarFactura=montoDelPago;
                }else if(montoDelSaldo==montoDelPago){
                    montoADescontarFactura=montoDelPago;
                }else if(montoDelSaldo<montoDelPago){
                    montoADescontarFactura=montoDelSaldo;
                }

                modeloDocumentosConSaldoCuentaCorriente.actualizarCuentaCorriente(modeloListaTipoDocumentosConDeudaVirtual.get(i).codigoItem,modeloListaTipoDocumentosConDeudaVirtual.get(i).codigoTipoItem,
                                                                                  _codigoiClienteRecibo,_codigoTipoclienteRecibo,
                                                                                  _codigoMonedaRecibo,
                                                                                  _numeroDocumentoRecibo,_tipoDocumentoRecibo,
                                                                                  _codigoiClienteRecibo,_codigoTipoclienteRecibo,
                                                                                  _codigoMonedaRecibo,montoADescontarFactura,montoDelSaldo,
                                                                                  modeloListaTipoDocumentosConDeudaVirtual.get(i).serieDoc,
                                                                                  _serieDocumentoRecibo
                                                                                  );

                montoDelPago=montoDelPago-montoADescontarFactura

            }
        }
    }


    function setearVendedorDeFacturasEnNotaDeCreditoORecibo(){

        var tieneCliente=false;
        for(var i=0; i<modeloListaTipoDocumentosConDeudaVirtual.count;i++){
            if(modeloListaTipoDocumentosConDeudaVirtual.get(i).checkBoxActivo){


                txtVendedorDeFactura.codigoValorSeleccion=modeloDocumentos.retornacodigoVendedorComisionaDocumento(modeloListaTipoDocumentosConDeudaVirtual.get(i).codigoItem,modeloListaTipoDocumentosConDeudaVirtual.get(i).codigoTipoItem,modeloListaTipoDocumentosConDeudaVirtual.get(i).serieDoc)
                txtVendedorDeFactura.textoComboBox=modeloListaVendedores.retornaVendedorSiEstaLogueado(txtVendedorDeFactura.codigoValorSeleccion.trim())

                if(txtVendedorDeFactura.codigoValorSeleccion.trim()!=""  && txtVendedorDeFactura.textoComboBox.trim()!=""){
                    tieneCliente=true;
                    break;
                }else{
                    tieneCliente=false;
                }
            }

            if(tieneCliente){
                break;
            }
        }
        if(tieneCliente==false){
            txtVendedorDeFactura.codigoValorSeleccion=""
            txtVendedorDeFactura.textoComboBox=""
        }
    }



    function superaCantidadMaximaLineasDocumento(){

        var _cantidadLineasTipoDocumento = modeloListaTipoDocumentosMantenimiento.cantidadMaximaLineasTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion);

        if(_cantidadLineasTipoDocumento==0){

            txtMensajeLimiteLineasMaximas.visible=false;
            return false;

        }else{

            if(listaDeItemsFactura.count >=_cantidadLineasTipoDocumento){
                txtMensajeLimiteLineasMaximas.text= "Se superó el límite de lineas para el documento ( "+modeloListaTipoDocumentosMantenimiento.cantidadMaximaLineasTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion)+" )"
                txtMensajeLimiteLineasMaximas.visible=true;
                return true;

            }else if(listaDeItemsFactura.count ==_cantidadLineasTipoDocumento){
                txtMensajeLimiteLineasMaximas.text= "Se alcanzó el límite de lineas para el documento ( "+modeloListaTipoDocumentosMantenimiento.cantidadMaximaLineasTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion)+" )"
                txtMensajeLimiteLineasMaximas.visible=true;
                return true;
            }
            else{

                txtMensajeLimiteLineasMaximas.visible=false;
                return false;
            }
        }
    }


    function agregarMedioDePago(){

        if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaCuentaBancaria")){
            cbxCuentasBancarias.codigoValorSeleccion=cbxAfectaCuentaBancaria.codigoValorSeleccion
            cbxCuentasBancarias.codigoValorSeleccion2=cbxAfectaCuentaBancaria.codigoValorSeleccion2
        }

        if(txtMontoMedioDePago.textoInputBox.trim()!="."){

            montoDelMedioDePago=txtMontoMedioDePago.textoInputBox.trim()



            if(txtCodigoMedioDePago.text.trim()!="" && montoDelMedioDePago!=0){

                modeloListaMediosDePagoAgregados.append({
                                                            descripcionMedioDePago: modeloMediosDePago.retornaDescripcionMedioDePago(txtCodigoMedioDePago.text.trim()),
                                                            codigoMedioDePago: txtCodigoMedioDePago.text.trim(),
                                                            montoMedioDePago: montoDelMedioDePago.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                            monedaMedioPago:modeloMediosDePago.retornaMonedaMedioDePago(txtCodigoMedioDePago.text.trim()),
                                                            simboloMonedaMedioDePago: modeloListaMonedas.retornaSimboloMoneda(modeloMediosDePago.retornaMonedaMedioDePago(txtCodigoMedioDePago.text.trim())),
                                                            cantidadCuotas: txtCuotasMedioDePago.textoInputBox.trim(),
                                                            nombreTarjetaCredito:cbxTarjetaCreditoMedioDePago.textoComboBox,
                                                            codigoTarjetaCredito:cbxTarjetaCreditoMedioDePago.codigoValorSeleccion,
                                                            numeroCheque:txtNumeroChequeMedioDePago.textoInputBox,
                                                            numeroBanco:cbxBancosMedioDePago.codigoValorSeleccion,
                                                            fechaCheque:txtFechaCheque.textoInputBox.trim(),
                                                            tipoCheque:cbxTipoCheque.codigoValorSeleccion,
                                                            codigoDoc:0,
                                                            esDiferido:false,
                                                            codigoTipoDoc:0,
                                                            numeroLineaDocumento:0,
                                                            numeroCuentaBancariaAgregado:cbxCuentasBancarias.codigoValorSeleccion,
                                                            numeroBancoCuentaBancaria:cbxCuentasBancarias.codigoValorSeleccion2,
                                                            activo:true,
                                                            serieDoc:""

                                                        })

                var cotizacion=1;
                if(modeloMediosDePago.retornaMonedaMedioDePago(txtCodigoMedioDePago.text.trim())!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                    if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloMediosDePago.retornaMonedaMedioDePago(txtCodigoMedioDePago.text.trim())){
                        cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                        montoDelMedioDePago=txtMontoMedioDePago.textoInputBox.trim()/cotizacion
                    }else{


                        if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                            cotizacion=modeloListaMonedas.retornaCotizacionMoneda(modeloMediosDePago.retornaMonedaMedioDePago(txtCodigoMedioDePago.text.trim()))
                            montoDelMedioDePago=txtMontoMedioDePago.textoInputBox.trim()*cotizacion
                        }else{
                            montoDelMedioDePago=(txtMontoMedioDePago.textoInputBox.trim()*modeloListaMonedas.retornaCotizacionMoneda(modeloMediosDePago.retornaMonedaMedioDePago(txtCodigoMedioDePago.text.trim())))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                        }

                    }
                }
                etiquetaTotalMedioDePago.setearTotal(montoDelMedioDePago.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),-1,cbListatipoDocumentos.codigoValorSeleccion)

                txtMontoMedioDePago.textoInputBox=""
                txtCuotasMedioDePago.textoInputBox="0"
                txtNumeroChequeMedioDePago.textoInputBox=""
                txtMontoMedioDePago.tomarElFoco()
                txtFechaCheque.textoInputBox=funcionesmysql.fechaDeHoy()
            }
        }
    }


    /// Setea el vendedor de un documento, y la ultima liquidacion/caja de ese vendedor como la contenedora del documento
    /// Si el usuario no es vendedor, el vendedor del documento queda vacio y la liquidacion/caja tambien.
    function setearVendedorDelSistema(){

        var usuarioVendedor=modeloListaVendedores.retornaVendedorSiEstaLogueado(txtNombreDeUsuario.textoInputBox.trim());

        if(usuarioVendedor!=""){
            txtVendedorDeFactura.textoComboBox=usuarioVendedor
            txtVendedorDeFactura.codigoValorSeleccion=txtNombreDeUsuario.textoInputBox.trim()

            cbListaLiquidacionesFacturacion.textoComboBox=modeloLiquidaciones.retornaDescripcionLiquidacionDeVendedorPorDefault(txtNombreDeUsuario.textoInputBox.trim())
            cbListaLiquidacionesFacturacion.codigoValorSeleccionExtra=txtNombreDeUsuario.textoInputBox.trim()
            cbListaLiquidacionesFacturacion.codigoValorSeleccion=modeloLiquidaciones.retornaNumeroLiquidacionDeVendedor(txtNombreDeUsuario.textoInputBox.trim())

        }else{

            var numeroLiquidacionActiva=modeloLiquidaciones.retornaNumeroPrimeraLiquidacionActiva()
            var codigoVendedorLiquidacionActiva=modeloLiquidaciones.retornaCodigoVendedorPrimeraLiquidacionActiva()
            if(numeroLiquidacionActiva!="" && codigoVendedorLiquidacionActiva!=""){


                cbListaLiquidacionesFacturacion.codigoValorSeleccion=numeroLiquidacionActiva
                cbListaLiquidacionesFacturacion.codigoValorSeleccionExtra=codigoVendedorLiquidacionActiva
                cbListaLiquidacionesFacturacion.textoComboBox=modeloLiquidaciones.retornaDescripcionLiquidacionDeVendedor(numeroLiquidacionActiva,codigoVendedorLiquidacionActiva)
            }
        }
    }


    function setearEstadoActivoBotonesGuardar(activos){
        botonGuardarFacturaEmitir.visible=activos
        botonGuardarFacturaPendiente.visible=activos
    }


    function setearVerificoEstadoActivoBotonesGuardar(){
        if(modeloconfiguracion.retornaValorConfiguracion("UTILIZA_CONTROL_CLIENTE_CREDITO")=="1"){
            if(txtCodigoClienteFacturacion.textoInputBox.trim()!="" && lblRazonSocialCliente.text.trim()!=""){
                if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"afectaCuentaCorriente")!="0"){
                    if(modeloClientes.retornaSiPermiteFacturaCredito(txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion)==false){
                        setearEstadoActivoBotonesGuardar(false)
                    }
                }
            }
        }
    }


    ///
    /// Setea el nuevo tipo de documento selecionado desde el combobox con la lista de documentos
    function setearDocumento(){

        setearEstadoActivoBotonesGuardar(true)


        cbListaFormasDePago.textoComboBox=""
        cbListaFormasDePago.codigoValorSeleccion=""

        cbListaDocumentosCuentaCorrienteConDeuda.cerrarComboBox()
        cbListaDocumentosCuentaCorrienteConDeuda.textoComboBox=""
        modeloComboBoxDocumentosConSaldoCuentaCorriente.limpiarListaDocumentos()
        modeloListaTipoDocumentosConDeudaVirtual.clear()


        txtTipoClienteFacturacion.cerrarComboBox()
        txtVendedorDeFactura.cerrarComboBox()
        cbxListaPrecioManualFijadaPorUsuario.cerrarComboBox()

        txtCodigoClienteFacturacion.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaCliente")
        if(txtCodigoClienteFacturacion.visible){
            lblRazonSocialCliente.visible=true
            btnBuscarMasClientes.visible=true
        }else{
            lblRazonSocialCliente.visible=false
            btnBuscarMasClientes.visible=false
        }

        txtNumeroDocumentoFacturacion.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaNumeroDocumento")
        txtSerieFacturacion.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaSerieDocumento")


        txtFechaPrecioFacturacion.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaFechaPrecio")
        txtFechaDocumentoFacturacion.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaFechaDocumento")
        txtVendedorDeFactura.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaVendedor")
        txtTipoClienteFacturacion.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaTipoCliente")
        rectListaDeArticulos.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")
        etiquetaTotal.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaTotales")
        if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaDescuentoTotal") || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaDescuentoArticulo")){
            etiquetaTotal.descuentosVisible=true
        }else{
            etiquetaTotal.descuentosVisible=false
        }

        txtCantidadArticulosFacturacion.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaCantidades")
        txtPrecioItemManualFacturacion.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaPrecioManual")

        txtComentariosFactura.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaComentarios")
        txtObservacionesFactura.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaObservaciones")

        txtCodigoDeBarrasADemanda.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaCodigoBarrasADemanda")

        cbListaFormasDePago.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaFormasDePago")


        if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"afectaCuentaCorriente")=="-1"){
            cbListaDocumentosCuentaCorrienteConDeuda.visible= true
        }else{
            cbListaDocumentosCuentaCorrienteConDeuda.visible=false
        }

        if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaSoloProveedores")){
            txtTipoClienteFacturacion.codigoValorSeleccion=2
            txtTipoClienteFacturacion.textoComboBox=modeloTipoClientes.primerRegistroDeTipoClienteEnBase(2)
            txtTipoClienteFacturacion.enabled=false
        }else{
            txtTipoClienteFacturacion.enabled=true
        }

        if(etiquetaTotal.visible){
            contenedorFlipable.anchors.bottomMargin=75
        }else{
            contenedorFlipable.anchors.bottomMargin=10
        }

        var ivaYSubtotalVisible=!modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"noAfectaIva")
        etiquetaTotal.labelIvaVisible=ivaYSubtotalVisible

        txtArticuloParaFacturacion.visible=rectListaDeArticulos.visible


        /// Si se pueden usar articulos pero no medios de pago, dejo activa la vista de articulos
        if(rectListaDeArticulos.visible==false && modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")==true){

            contenedorFlipable.flipped=true
            btnAgregarMediosDePago.visible=false


        }else if(rectListaDeArticulos.visible==true && modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")==false){

            contenedorFlipable.flipped=false
            btnAgregarMediosDePago.visible=false

        }else if(rectListaDeArticulos.visible==true && modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")==true){

            contenedorFlipable.flipped=false
            btnAgregarMediosDePago.visible=true

        }else{

            contenedorFlipable.flipped=false
            btnAgregarMediosDePago.visible=false
        }
        if(!contenedorFlipable.flipped){
            btnAgregarMediosDePago.texto="medios de pago"
        }else{
            btnAgregarMediosDePago.texto="items facturación"
        }

        btnBuscarMasArticulos.visible=rectListaDeArticulos.visible
        cbxListaChequesDiferidos.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaPagoChequeDiferido")
        cbxAfectaCuentaBancaria.visible=modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaCuentaBancaria")

        if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaSoloMediosDePagoCheque")){
            modeloMediosDePago.limpiarListaMediosDePago()
            modeloMediosDePago.buscarMediosDePago(" codigoTipoMedioDePago=","3")
        }else{
            modeloMediosDePago.limpiarListaMediosDePago()
            modeloMediosDePago.buscarMediosDePago("1=","1")
        }
        if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaCuentaBancaria")){
            cbxAfectaCuentaBancaria.codigoValorSeleccion=modeloCuentasBancarias.retornaPrimeraCuentaBancariaDisponible()
            cbxAfectaCuentaBancaria.codigoValorSeleccion2=modeloCuentasBancarias.retornaBancoCuentaBancaria(cbxAfectaCuentaBancaria.codigoValorSeleccion)
            cbxAfectaCuentaBancaria.textoComboBox=cbxAfectaCuentaBancaria.codigoValorSeleccion+" - "+modeloListaBancos.retornaDescripcionBanco(cbxAfectaCuentaBancaria.codigoValorSeleccion2)

            modeloMediosDePago.limpiarListaMediosDePago()
            modeloMediosDePago.buscarMediosDePago(" codigoTipoMedioDePago!=4 and codigoTipoMedioDePago!=","2")
        }

    }



    function cargoFacturaEnMantenimiento(codigoDocumento, codigoTipoDocumento,serieDocumento){

        if(tagFacturacion.enabled && funcionesmysql.mensajeAdvertencia("Se va a cargar la factura seleccionada, \nsi tiene datos en uso se perderan, desea continuar?\n\nPresione [ Sí ] para confirmar.")){

            if(modeloDocumentos.existeDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento)){

                mostrarMantenimientos(0,"derecha")

                cargarFactura(codigoDocumento,
                              codigoTipoDocumento,
                              modeloDocumentos.retornacodigoEstadoDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornatipoClienteDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornacodigoClienteDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              serieDocumento,
                              modeloDocumentos.retornacodigoVendedorComisionaDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornacodigoLiquidacionDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornacodigoVendedorLiquidacionDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornafechaEmisionDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornafechaEmisionDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornacodigoMonedaDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornaprecioIvaVentaDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornaprecioSubTotalVentaDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornaprecioTotalVentaDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornatotalIva1Documento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornatotalIva2Documento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornatotalIva3Documento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornaobservacionesDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornaonumeroCuentaBancariaDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornaocodigoBancoDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornaMontoDescuentoTotalDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornaFormaDePagoDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),
                              modeloDocumentos.retornaPorcentajeDescuentoAlTotalDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento),

                              "","",
                              modeloDocumentos.retornacomentariosDocumento(codigoDocumento,codigoTipoDocumento,serieDocumento)
                              )


            }else{
                funcionesmysql.mensajeAdvertenciaOk("El documento ya no existe, actualice la liquidacion y verifique.")
            }
        }

    }



    /////
    ///// Carga la factura pendiente o en otro estado a la que se le da dobe clic en las liquidaciones/caja
    ///// Lista: ListaDocumentosEnLiquidaciones.qml
    function cargarFactura(numeroFactura, tipoDocumento, estadoDocumento,tipoCliente,codigoCliente,serieDocumento, codigoVendedorComision,codigoLiquidacion, codigoVendedorLiquidacion,fechaPrecio,fechaEmision,monedaDocumento,precioIvaVenta,precioSubTotalVenta,precioTotalVenta,totalIva1,totalIva2,totalIva3,observacion,numeroCuentaBancaria,codigoBanco,montoDescuentoTotal,formaDePago,porcentajeDescuentoAlTotal,indicadorDeNuevoDocumento,tipoDocumentoDevolucion,comentarios){

        cuadroListaDocumentosNuevo.visible=false;
        lblNumeroDocumentoyCFE.text=""


        nuevoDocumento=indicadorDeNuevoDocumento;

        cbxAfectaCuentaBancaria.codigoValorSeleccion=numeroCuentaBancaria
        cbxAfectaCuentaBancaria.codigoValorSeleccion2=codigoBanco
        cbxAfectaCuentaBancaria.textoComboBox=cbxAfectaCuentaBancaria.codigoValorSeleccion+" - "+modeloListaBancos.retornaDescripcionBanco(cbxAfectaCuentaBancaria.codigoValorSeleccion2)

        if(indicadorDeNuevoDocumento==""){
            cbListatipoDocumentos.codigoValorSeleccion=tipoDocumento
            cbListatipoDocumentos.textoComboBox=modeloListaTipoDocumentosComboBox.retornaDescripcionTipoDocumento(tipoDocumento)
        }
        setearDocumento()
        etiquetaTotal.sereaTotales()
        etiquetaTotalMedioDePago.sereaTotales()

        txtTipoClienteFacturacion.codigoValorSeleccion=tipoCliente
        txtTipoClienteFacturacion.textoComboBox=modeloTipoClientes.primerRegistroDeTipoClienteEnBase(tipoCliente)

        txtCodigoClienteFacturacion.textoInputBox=codigoCliente

        if(indicadorDeNuevoDocumento=="")
            txtNumeroDocumentoFacturacion.textoInputBox=numeroFactura

        cbListaFormasDePago.textoComboBox=formaDePago;

        if(indicadorDeNuevoDocumento=="")
            txtSerieFacturacion.textoInputBox=serieDocumento.toUpperCase()

        if(txtVendedorDeFactura.visible){
            txtVendedorDeFactura.codigoValorSeleccion=codigoVendedorComision
            txtVendedorDeFactura.textoComboBox=modeloListaVendedores.retornaVendedorSiEstaLogueado(codigoVendedorComision)
        }else{
            txtVendedorDeFactura.codigoValorSeleccion=""
            txtVendedorDeFactura.textoComboBox=""
        }

        if(indicadorDeNuevoDocumento==""){

            cbListaLiquidacionesFacturacion.codigoValorSeleccion=codigoLiquidacion
            cbListaLiquidacionesFacturacion.codigoValorSeleccionExtra=codigoVendedorLiquidacion
            cbListaLiquidacionesFacturacion.textoComboBox=modeloLiquidacionesComboBox.retornaDescripcionLiquidacionDeVendedor(codigoLiquidacion,codigoVendedorLiquidacion)

        }

        txtFechaPrecioFacturacion.textoInputBox=fechaPrecio

        if(indicadorDeNuevoDocumento=="")
            txtFechaDocumentoFacturacion.textoInputBox=fechaEmision


        cbListaMonedasEnFacturacion.codigoValorSeleccion=monedaDocumento
        cbListaMonedasEnFacturacion.textoComboBox=modeloListaMonedas.retornaDescripcionMoneda(monedaDocumento)

        lblRazonSocialCliente.text="Facturar a: "+modeloClientes.retornaDescripcionDeCliente(txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion);

        txtComentariosFactura.textoInputBox=comentarios
        txtObservacionesFactura.textoInputBox=observacion

        var cantidadLineasDocumento=modeloDocumentosEnLiquidaciones.retornaCantidadLineasDocumento(numeroFactura,tipoDocumento, serieDocumento);


        var _simboloMoneda=modeloListaMonedas.retornaSimboloMoneda(monedaDocumento)
        etiquetaTotal.labelTotal=qsTr("Total "+_simboloMoneda)
        etiquetaTotal.labelTotalDescuentos=qsTr("Descuento "+_simboloMoneda)
        etiquetaTotalMedioDePago.labelTotal=qsTr("Total medios de pago "+_simboloMoneda)

        if(cantidadLineasDocumento==0 && indicadorDeNuevoDocumento!=""){

            etiquetaTotal.totalIva1=0.00;
            etiquetaTotal.totalIva2=0.00;
            etiquetaTotal.totalIva3=0.00;

            etiquetaTotal.txtValorIvaText= "0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
            etiquetaTotal.txtValorSubTotalText="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
            etiquetaTotal.txtValorTotalText= "0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
            valorReutilizar=0.00;
            montoDescuentoTotal=valorReutilizar.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
            etiquetaTotal.txtvalorTotalDescuentoText=montoDescuentoTotal

            etiquetaTotal.valorIvaAcumulado=0.00;
            etiquetaTotal.valorSubTotalAcumulado=0.00;
            etiquetaTotal.valorFinalDelTotal=0.00;
            etiquetaTotal.valorTotalAcumulado=0.00;
            etiquetaTotal.valorTotalDescuentoAcumulado=0.00;
        }else{

            valorReutilizar=precioIvaVenta
            precioIvaVenta=valorReutilizar.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))

            valorReutilizar=precioSubTotalVenta
            precioSubTotalVenta=valorReutilizar.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))

            valorReutilizar=precioTotalVenta
            precioTotalVenta=valorReutilizar.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))

            valorReutilizar=totalIva1
            totalIva1=valorReutilizar.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))

            valorReutilizar=totalIva2
            totalIva2=valorReutilizar.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))

            valorReutilizar=totalIva3
            totalIva3=valorReutilizar.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))

            etiquetaTotal.totalIva1=totalIva1
            etiquetaTotal.totalIva2=totalIva2
            etiquetaTotal.totalIva3=totalIva3

            etiquetaTotal.txtValorIvaText= precioIvaVenta
            etiquetaTotal.txtValorSubTotalText= precioSubTotalVenta
            etiquetaTotal.txtValorTotalText= precioTotalVenta
            valorReutilizar=montoDescuentoTotal
            montoDescuentoTotal=valorReutilizar.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))

            etiquetaTotal.txtvalorTotalDescuentoText=montoDescuentoTotal

            etiquetaTotal.valorIvaAcumulado=precioIvaVenta
            etiquetaTotal.valorSubTotalAcumulado=precioSubTotalVenta
            etiquetaTotal.valorFinalDelTotal=precioTotalVenta
            etiquetaTotal.valorTotalAcumulado=precioTotalVenta
            etiquetaTotal.valorTotalDescuentoAcumulado=montoDescuentoTotal


            etiquetaTotal.setearPorcenjeDescuento(porcentajeDescuentoAlTotal)

            if(porcentajeDescuentoAlTotal!==0){
                etiquetaTotal.descuentosVisible=true
            }

        }

        lbltemTotalVentaFacturacion.text=qsTr("Unidad "+_simboloMoneda)

        if(indicadorDeNuevoDocumento==""){
            if(modeloDocumentos.retornaEsDocumentoWebDocumento(numeroFactura, tipoDocumento,serieDocumento)=="1"){
                imgEsDocumentoWeb.visible=true;
            }else{
                imgEsDocumentoWeb.visible=false;
            }
            if(modeloDocumentos.retornaEsDocumentoCFEDocumento(numeroFactura, tipoDocumento,serieDocumento)=="1"){
                imgEsDocumentoCFE.visible=true;
            }else{
                imgEsDocumentoCFE.visible=false;
            }


        }




        //#############################################################
        //############ Cargo las lineas del documento #################
        //#############################################################


        modeloItemsFactura.clear();

        if(cantidadLineasDocumento!=0){


            for(var i=0;i<cantidadLineasDocumento;i++){

                var valorArticuloInterno=modeloDocumentosEnLiquidaciones.retornoCodigoArticuloDeLineaDocumento(numeroFactura,tipoDocumento,i,serieDocumento)
                var valorArticuloInternoBarras=modeloDocumentosEnLiquidaciones.retornoCodigoArticuloBarrasDeLineaDocumento(numeroFactura,tipoDocumento,i,serieDocumento)
                var valorPrecioArticulo=modeloDocumentosEnLiquidaciones.retornoPrecioArticuloDeLineaDocumento(numeroFactura,tipoDocumento,i,serieDocumento)

                var valorCantidadDeArticulos=modeloDocumentosEnLiquidaciones.retornoCantidadArticuloDeLineaDocumento(numeroFactura,tipoDocumento,i,serieDocumento)
                var valorCostoArticuloMonedaReferencia=modeloDocumentosEnLiquidaciones.retornoCostoArticuloMonedaReferenciaDeLineaDocumento(numeroFactura,tipoDocumento,i,serieDocumento)
                var valorDescuentoLinea= modeloDocumentosEnLiquidaciones.retornoDescuentoLineaArticuloDeLineaDocumento(numeroFactura,tipoDocumento,i,serieDocumento)
                var valorCodigoTipoGarantia = modeloDocumentosEnLiquidaciones.retornoCodigoTipoGarantiaLineaArticuloDeLineaDocumento(numeroFactura,tipoDocumento,i,serieDocumento)

                if(estadoDocumento=="P"){

                    modeloItemsFactura.append({
                                                  codigoArticulo:valorArticuloInterno,
                                                  codigoBarrasArticulo:valorArticuloInternoBarras,
                                                  descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                  descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                  precioArticulo:valorPrecioArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                  precioArticuloSubTotal:(valorPrecioArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*valorCantidadDeArticulos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                  cantidadItems:valorCantidadDeArticulos,
                                                  costoArticuloMonedaReferencia:valorCostoArticuloMonedaReferencia.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                  activo:true,
                                                  consideraDescuento:true,
                                                  indiceLinea:i,
                                                  descuentoLineaItem:valorDescuentoLinea.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                  codigoTipoGarantia:valorCodigoTipoGarantia,
                                                  descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(valorCodigoTipoGarantia),
                                                  asignarGarantiaAArticulo:false
                                              })


                }else{
                    modeloItemsFactura.append({
                                                  codigoArticulo:valorArticuloInterno,
                                                  codigoBarrasArticulo:valorArticuloInternoBarras,
                                                  descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                  descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                  precioArticulo:valorPrecioArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                  precioArticuloSubTotal:(valorPrecioArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*valorCantidadDeArticulos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                  cantidadItems:valorCantidadDeArticulos,
                                                  costoArticuloMonedaReferencia:valorCostoArticuloMonedaReferencia.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                  activo:false,
                                                  consideraDescuento:false,
                                                  indiceLinea:i,
                                                  descuentoLineaItem:valorDescuentoLinea.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                  codigoTipoGarantia:valorCodigoTipoGarantia,
                                                  descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(valorCodigoTipoGarantia),
                                                  asignarGarantiaAArticulo:false
                                              })
                }



            }
        }

        //#############################################################
        //############ Fin de cargo las lineas del documento ##########
        //#############################################################

        //#####################################################################
        //############ Cargo los medios de pago del documento #################
        //#####################################################################
        var cantidadLineasMediosDePago=modeloMediosDePago.retornaCantidadLineasMedioDePago(numeroFactura,tipoDocumento,serieDocumento);

        modeloListaMediosDePagoAgregados.clear()

        if(cantidadLineasMediosDePago!=0){


            for(var j=0;j<cantidadLineasMediosDePago;j++){

                var valorCodigoMedioDePago=modeloMediosDePago.retornoCodigoMedioPago(numeroFactura,tipoDocumento,j,serieDocumento);
                var valorMontoMedioDePago=modeloMediosDePago.retornoImportePago(numeroFactura,tipoDocumento,j,serieDocumento);
                var valorMonedaMedioDePago=modeloMediosDePago.retornoMonedaMedioPago(numeroFactura,tipoDocumento,j,serieDocumento);
                var cotizacion=1;


                if(estadoDocumento=="P"){

                    modeloListaMediosDePagoAgregados.append({
                                                                descripcionMedioDePago: modeloMediosDePago.retornaDescripcionMedioDePago(valorCodigoMedioDePago),
                                                                codigoMedioDePago: valorCodigoMedioDePago,
                                                                montoMedioDePago:valorMontoMedioDePago.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                monedaMedioPago:valorMonedaMedioDePago,
                                                                simboloMonedaMedioDePago: modeloListaMonedas.retornaSimboloMoneda(valorMonedaMedioDePago),
                                                                cantidadCuotas: modeloMediosDePago.retornoCuotas(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                nombreTarjetaCredito:modeloListaTarjetasCredito.retornaDescripcionTarjetaCredito(modeloMediosDePago.retornoCodigoTarjetaCredito(numeroFactura,tipoDocumento,j,serieDocumento)),
                                                                codigoTarjetaCredito:modeloMediosDePago.retornoCodigoTarjetaCredito(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                numeroCheque:modeloMediosDePago.retornoNumeroCheque(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                numeroBanco:modeloMediosDePago.retornoCodigoBanco(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                fechaCheque:modeloMediosDePago.retornoFechaCheque(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                tipoCheque:modeloMediosDePago.retornoTipoCheque(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                codigoDoc:modeloMediosDePago.retornoCodigoDocumentoCheque(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                esDiferido: modeloMediosDePago.retornoEsDiferidoCheque(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                codigoTipoDoc:modeloMediosDePago.retornoCodigoTipoDocumentoCheque(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                numeroLineaDocumento:modeloMediosDePago.retornoNumeroLineaDocumentoCheque(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                numeroCuentaBancariaAgregado:modeloMediosDePago.retornoCuentaBancaria(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                numeroBancoCuentaBancaria:modeloMediosDePago.retornoBancoCuentaBancaria(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                activo:true,
                                                                serieDoc:modeloMediosDePago.retornoSerieDocumentoCheque(numeroFactura,tipoDocumento,j,serieDocumento)
                                                            })
                }else{
                    modeloListaMediosDePagoAgregados.append({
                                                                descripcionMedioDePago: modeloMediosDePago.retornaDescripcionMedioDePago(valorCodigoMedioDePago),
                                                                codigoMedioDePago: valorCodigoMedioDePago,
                                                                montoMedioDePago:valorMontoMedioDePago.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                monedaMedioPago:valorMonedaMedioDePago,
                                                                simboloMonedaMedioDePago: modeloListaMonedas.retornaSimboloMoneda(valorMonedaMedioDePago),
                                                                cantidadCuotas: modeloMediosDePago.retornoCuotas(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                nombreTarjetaCredito:modeloListaTarjetasCredito.retornaDescripcionTarjetaCredito(modeloMediosDePago.retornoCodigoTarjetaCredito(numeroFactura,tipoDocumento,j,serieDocumento)),
                                                                codigoTarjetaCredito:modeloMediosDePago.retornoCodigoTarjetaCredito(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                numeroCheque:modeloMediosDePago.retornoNumeroCheque(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                numeroBanco:modeloMediosDePago.retornoCodigoBanco(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                fechaCheque:modeloMediosDePago.retornoFechaCheque(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                tipoCheque:modeloMediosDePago.retornoTipoCheque(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                codigoDoc:modeloMediosDePago.retornoCodigoDocumentoCheque(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                esDiferido: modeloMediosDePago.retornoEsDiferidoCheque(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                codigoTipoDoc:modeloMediosDePago.retornoCodigoTipoDocumentoCheque(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                numeroLineaDocumento:modeloMediosDePago.retornoNumeroLineaDocumentoCheque(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                numeroCuentaBancariaAgregado:modeloMediosDePago.retornoCuentaBancaria(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                numeroBancoCuentaBancaria:modeloMediosDePago.retornoBancoCuentaBancaria(numeroFactura,tipoDocumento,j,serieDocumento),
                                                                activo:false,
                                                                serieDoc:modeloMediosDePago.retornoSerieDocumentoCheque(numeroFactura,tipoDocumento,j,serieDocumento)
                                                            })
                }




                if(valorMonedaMedioDePago!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                    if(modeloListaMonedas.retornaMonedaReferenciaSistema()==valorMonedaMedioDePago){
                        cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                        valorMontoMedioDePago=valorMontoMedioDePago/cotizacion
                    }else{

                        if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                            cotizacion=modeloListaMonedas.retornaCotizacionMoneda(valorMonedaMedioDePago)
                            valorMontoMedioDePago=valorMontoMedioDePago*cotizacion
                        }else{
                            valorMontoMedioDePago=(valorMontoMedioDePago*modeloListaMonedas.retornaCotizacionMoneda(valorMonedaMedioDePago))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                        }



                    }
                }
                etiquetaTotalMedioDePago.setearTotal(valorMontoMedioDePago.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),-1,tipoDocumento)
            }
        }

        //#####################################################################
        //############ Fin de cargo los medios de pago del documento ##########
        //#####################################################################

        if(estadoDocumento=="P"){


            cbListatipoDocumentos.activo(false)

            if(indicadorDeNuevoDocumento==""){



                txtTipoClienteFacturacion.activo(false)
                txtCodigoClienteFacturacion.enable=false
                txtCodigoClienteFacturacion.enabled=false

                btnBuscarMasClientes.enabled=false

                txtNumeroDocumentoFacturacion.enable=false
                txtNumeroDocumentoFacturacion.enabled=false

                txtSerieFacturacion.enable=false
                txtSerieFacturacion.enabled=false
            }

            txtVendedorDeFactura.activo(true)

            txtFechaPrecioFacturacion.enable=true
            txtFechaPrecioFacturacion.enabled=true

            txtFechaDocumentoFacturacion.enable=true
            txtFechaDocumentoFacturacion.enabled=true
            txtFechaDocumentoFacturacion.textoInputBox=funcionesmysql.fechaDeHoy()

            txtArticuloParaFacturacion.enable= true

            txtArticuloParaFacturacion.enabled=txtArticuloParaFacturacion.enable

            txtPrecioItemManualFacturacion.enable=true
            txtPrecioItemManualFacturacion.enabled=true

            txtObservacionesFactura.enable=true
            txtObservacionesFactura.enabled=true

            txtComentariosFactura.enable=true
            txtComentariosFactura.enabled=true

            txtCantidadArticulosFacturacion.enable=true
            txtCantidadArticulosFacturacion.enabled=true

            txtCodigoDeBarrasADemanda.enable=true
            txtCodigoDeBarrasADemanda.enabled=true

            cbListaLiquidacionesFacturacion.activo(true)

            btnBuscarMasArticulos.enabled=true


            botonGuardarFacturaEmitir.enabled=true
            botonGuardarFacturaPendiente.enabled=true
            if(indicadorDeNuevoDocumento==""){
                botonEliminarFactura.visible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteBorrarFacturas");
            }
            botonAnularFactura.visible=false
            botonReimprimirFactura.visible=false
            botonDevolverFactura.visible=false

            btnAgregarNuevoMedioDePago.enabled=true
            txtMontoMedioDePago.enable=true
            txtCuotasMedioDePago.enable=true
            txtMontoMedioDePago.enabled=true
            txtCuotasMedioDePago.enabled=true

            txtNumeroChequeMedioDePago.enable=true
            txtNumeroChequeMedioDePago.enabled=true

            txtFechaCheque.enable=true
            txtFechaCheque.enabled=true

            cbxTipoCheque.activo(true)
            if(indicadorDeNuevoDocumento==""){
                cbxCuentasBancarias.activo(false)
                cbxBancosMedioDePago.activo(false)
            }
            cbxListaChequesDiferidos.activo(true)

            cbxAfectaCuentaBancaria.activo(true)

            cbListaFormasDePago.activo(true)
            cbListaFormasDePago.enabled=true

            if(cbListaDocumentosCuentaCorrienteConDeuda.visible){
                cargarDocumentosConDeuda()
            }


            if(modeloconfiguracion.retornaValorConfiguracion("UTILIZA_CONTROL_CLIENTE_CREDITO")=="1"){
                if(txtCodigoClienteFacturacion.textoInputBox.trim()!="" && lblRazonSocialCliente.text.trim()!=""){
                    if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"afectaCuentaCorriente")!="0"){
                        if(modeloClientes.retornaSiPermiteFacturaCredito(txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion)==false){

                            setearEstadoActivoBotonesGuardar(false)
                            funcionesmysql.mensajeAdvertenciaOk("El cliente no esta habilitado para documentos CRÉDITO.\n\n No se podrá emitir el documento ni volver a guardarlo.")

                        }
                    }
                }
            }



        }else  if(estadoDocumento=="E" || estadoDocumento=="G"){

            var atributoDeudaContadoPermiteModificar=modeloListaTipoDocumentosComboBox.retornaPermiteModificacionMedioPagoPorDeudaContado(tipoDocumento,numeroFactura,serieDocumento)

            lblNumeroDocumentoyCFE.text="#"+numeroFactura+"("+serieDocumento+")";

            if(modeloDocumentos.retornaEsDocumentoCFEDocumento(numeroFactura,tipoDocumento,serieDocumento)=="1"){
                lblNumeroDocumentoyCFE.text+=" - CFE: "+modeloDocumentos.retornaNumeroCFEOriginal(numeroFactura,tipoDocumento,serieDocumento);
            }

            txtFechaDocumentoFacturacion.visible=true;

            cbListaDocumentosCuentaCorrienteConDeuda.cerrarComboBox()
            cbListaDocumentosCuentaCorrienteConDeuda.visible=false
            btnAgregarNuevoMedioDePago.enabled=atributoDeudaContadoPermiteModificar
            txtMontoMedioDePago.enable=atributoDeudaContadoPermiteModificar
            txtCuotasMedioDePago.enable=atributoDeudaContadoPermiteModificar
            txtMontoMedioDePago.enabled=atributoDeudaContadoPermiteModificar
            txtCuotasMedioDePago.enabled=atributoDeudaContadoPermiteModificar
            txtNumeroChequeMedioDePago.enable=atributoDeudaContadoPermiteModificar
            txtNumeroChequeMedioDePago.enabled=atributoDeudaContadoPermiteModificar

            txtFechaCheque.enable=atributoDeudaContadoPermiteModificar
            txtFechaCheque.enabled=atributoDeudaContadoPermiteModificar

            cbxTipoCheque.activo(atributoDeudaContadoPermiteModificar)
            cbxListaChequesDiferidos.activo(atributoDeudaContadoPermiteModificar)
            cbxCuentasBancarias.activo(false)
            cbxBancosMedioDePago.activo(atributoDeudaContadoPermiteModificar)

            cbListatipoDocumentos.activo(false)

            txtTipoClienteFacturacion.activo(false)

            txtCodigoClienteFacturacion.enable=false
            txtCodigoClienteFacturacion.enabled=false

            btnBuscarMasClientes.enabled=false

            txtNumeroDocumentoFacturacion.enable=false
            txtNumeroDocumentoFacturacion.enabled=false

            txtSerieFacturacion.enable=false
            txtSerieFacturacion.enabled=false

            txtVendedorDeFactura.activo(false)

            txtFechaPrecioFacturacion.enable=false
            txtFechaPrecioFacturacion.enabled=false

            txtFechaDocumentoFacturacion.enable=false
            txtFechaDocumentoFacturacion.enabled=false

            txtArticuloParaFacturacion.enable=false
            txtArticuloParaFacturacion.enabled=false

            txtPrecioItemManualFacturacion.enable=false
            txtPrecioItemManualFacturacion.enabled=false

            txtObservacionesFactura.enable=true
            txtObservacionesFactura.enabled=true

            txtComentariosFactura.enable=true
            txtComentariosFactura.enabled=true

            txtCantidadArticulosFacturacion.enable=false
            txtCantidadArticulosFacturacion.enabled=false

            txtCodigoDeBarrasADemanda.enable=false
            txtCodigoDeBarrasADemanda.enabled=false

            cbListaLiquidacionesFacturacion.activo(false)

            btnBuscarMasArticulos.enabled=false

            botonGuardarFacturaEmitir.enabled=atributoDeudaContadoPermiteModificar
            botonGuardarFacturaPendiente.enabled=false
            botonEliminarFactura.visible=false

            if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1" && modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"emiteCFEImprime")){
                botonAnularFactura.visible=false;
            }else if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1" && modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"emiteCFEImprime")===false){
                botonAnularFactura.visible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteAnularFacturas");
            }else{
                botonAnularFactura.visible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteAnularFacturas");
            }



            if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteReimprimirFacturas")){
                if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"emiteEnImpresora"))
                {
                    botonReimprimirFactura.visible=true;
                }else{
                    botonReimprimirFactura.visible=false;
                }
            }else{
                botonReimprimirFactura.visible=false;
            }
            cbListaMonedasEnFacturacion.activo(false)

            cbxAfectaCuentaBancaria.activo(false)

            cbListaFormasDePago.activo(false)
            cbListaFormasDePago.enabled=false

            modeloListaTipoDocumentosParaDevoluciones.limpiarListaTipoDocumentos()
            botonDevolverFactura.visible=modeloListaTipoDocumentosParaDevoluciones.permiteDevolucionTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion)
        }
        else{

            cbListaDocumentosCuentaCorrienteConDeuda.cerrarComboBox()
            cbListaDocumentosCuentaCorrienteConDeuda.visible=false


            btnAgregarNuevoMedioDePago.enabled=false
            txtMontoMedioDePago.enable=false
            txtCuotasMedioDePago.enable=false
            txtMontoMedioDePago.enabled=false
            txtCuotasMedioDePago.enabled=false
            txtNumeroChequeMedioDePago.enable=false
            txtNumeroChequeMedioDePago.enabled=false

            txtFechaCheque.enable=false
            txtFechaCheque.enabled=false

            cbxTipoCheque.activo(false)
            cbxListaChequesDiferidos.activo(false)
            cbxCuentasBancarias.activo(false)
            cbxBancosMedioDePago.activo(false)

            cbListatipoDocumentos.activo(false)

            txtTipoClienteFacturacion.activo(false)

            txtCodigoClienteFacturacion.enable=false
            txtCodigoClienteFacturacion.enabled=false

            btnBuscarMasClientes.enabled=false

            txtNumeroDocumentoFacturacion.enable=false
            txtNumeroDocumentoFacturacion.enabled=false

            txtSerieFacturacion.enable=false
            txtSerieFacturacion.enabled=false

            txtVendedorDeFactura.activo(false)

            txtFechaPrecioFacturacion.enable=false
            txtFechaPrecioFacturacion.enabled=false

            txtFechaDocumentoFacturacion.enable=false
            txtFechaDocumentoFacturacion.enabled=false

            txtArticuloParaFacturacion.enable=false
            txtArticuloParaFacturacion.enabled=false

            txtPrecioItemManualFacturacion.enable=false
            txtPrecioItemManualFacturacion.enabled=false

            txtObservacionesFactura.enable=true
            txtObservacionesFactura.enabled=true

            txtComentariosFactura.enable=true
            txtComentariosFactura.enabled=true

            txtCantidadArticulosFacturacion.enable=false
            txtCantidadArticulosFacturacion.enabled=false

            txtCodigoDeBarrasADemanda.enable=false
            txtCodigoDeBarrasADemanda.enabled=false

            cbListaLiquidacionesFacturacion.activo(false)

            btnBuscarMasArticulos.enabled=false

            botonGuardarFacturaEmitir.enabled=false
            botonGuardarFacturaPendiente.enabled=false
            botonEliminarFactura.visible=false

            if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1" && modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"emiteCFEImprime")){
                botonAnularFactura.visible=false;
            }else if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1" && modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"emiteCFEImprime")===false){
                botonAnularFactura.visible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteAnularFacturas");
            }else{
                botonAnularFactura.visible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteAnularFacturas");
            }




            if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteReimprimirFacturas")){
                if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"emiteEnImpresora"))
                {
                    botonReimprimirFactura.visible=true;
                }else{
                    botonReimprimirFactura.visible=false;
                }
            }else{
                botonReimprimirFactura.visible=false;
            }
            cbListaMonedasEnFacturacion.activo(false)

            cbxAfectaCuentaBancaria.activo(false)

            cbListaFormasDePago.activo(false)
            cbListaFormasDePago.enabled=false

            modeloListaTipoDocumentosParaDevoluciones.limpiarListaTipoDocumentos()
            botonDevolverFactura.visible=modeloListaTipoDocumentosParaDevoluciones.permiteDevolucionTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion)

        }
    }



    function borrarArticulos(){

        etiquetaTotal.setearPorcenjeDescuento(0.00)
        etiquetaTotal.sereaTotalesSinDescuento();
        etiquetaTotal.sereaTotales()
        etiquetaTotalMedioDePago.sereaTotalesSinDescuento();
        etiquetaTotalMedioDePago.sereaTotales()
        modeloListaMediosDePagoAgregados.clear()
        modeloItemsFactura.clear();

    }

    /////
    ///// Crea una nueva factura, borrando todos los datos, y restaurando los controles
    function crearNuevaFactura(){


        setearEstadoActivoBotonesGuardar(true)


        etiquetaTotal.setearPorcenjeDescuento(0.00)
        nuevoDocumento="NUEVO";
        cbListaDocumentosCuentaCorrienteConDeuda.cerrarComboBox()
        cbListaDocumentosCuentaCorrienteConDeuda.textoComboBox=""
        modeloComboBoxDocumentosConSaldoCuentaCorriente.limpiarListaDocumentos()
        modeloListaTipoDocumentosConDeudaVirtual.clear()

        if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"afectaCuentaCorriente")=="-1"){
            cbListaDocumentosCuentaCorrienteConDeuda.visible= true
        }else{
            cbListaDocumentosCuentaCorrienteConDeuda.visible=false
        }


        lblNumeroDocumentoyCFE.text=""

        cbListaFormasDePago.activo(true)
        cbListaFormasDePago.enabled=true
        cbListaFormasDePago.textoComboBox=""
        cbListaFormasDePago.codigoValorSeleccion=""

        imgEsDocumentoWeb.visible=false
        imgEsDocumentoCFE.visible=false

        cbListatipoDocumentos.activo(true)
        cbListatipoDocumentos.enabled=true
        txtTipoClienteFacturacion.activo(true)
        txtCodigoClienteFacturacion.enable=true
        txtCodigoClienteFacturacion.enabled=true

        txtNumeroDocumentoFacturacion.enable=true
        txtNumeroDocumentoFacturacion.enabled=true

        txtSerieFacturacion.enable=true
        txtSerieFacturacion.enabled=true

        txtVendedorDeFactura.activo(true)
        cbListaMonedasEnFacturacion.activo(true)

        txtFechaPrecioFacturacion.enable=true
        txtFechaPrecioFacturacion.enabled=true

        txtFechaDocumentoFacturacion.enable=true
        txtFechaDocumentoFacturacion.enabled=true

        txtArticuloParaFacturacion.enable=true
        txtArticuloParaFacturacion.enabled=txtArticuloParaFacturacion.enable

        cbListaLiquidacionesFacturacion.activo(true)

        if(!modeloLiquidaciones.liquidacionActiva(cbListaLiquidacionesFacturacion.codigoValorSeleccion.trim(),cbListaLiquidacionesFacturacion.codigoValorSeleccionExtra.trim())){
            setearVendedorDelSistema()
        }

        btnBuscarMasArticulos.enabled=true


        botonGuardarFacturaEmitir.enabled=true
        botonGuardarFacturaPendiente.enabled=true
        botonEliminarFactura.visible=false
        botonAnularFactura.visible=false
        botonReimprimirFactura.visible=false
        botonDevolverFactura.visible=false

        btnBuscarMasClientes.enabled=true


        txtCodigoClienteFacturacion.textoInputBox=""
        if(txtTipoClienteFacturacion.textoComboBox.trim()==""){
            txtTipoClienteFacturacion.codigoValorSeleccion=1
            txtTipoClienteFacturacion.textoComboBox=modeloTipoClientes.primerRegistroDeTipoClienteEnBase(txtTipoClienteFacturacion.codigoValorSeleccion)
        }
        lblRazonSocialCliente.text=""
        txtNumeroDocumentoFacturacion.textoInputBox=""
        txtSerieFacturacion.textoInputBox=""
        txtVendedorDeFactura.cerrarComboBox()
        txtTipoClienteFacturacion.cerrarComboBox()
        cbListaLiquidacionesFacturacion.cerrarComboBox()

        txtVendedorDeFactura.codigoValorSeleccion=0
        txtVendedorDeFactura.textoComboBox=""
        txtPrecioItemManualFacturacion.textoInputBox=""
        txtObservacionesFactura.textoInputBox=""
        txtComentariosFactura.textoInputBox=""

        txtFechaDocumentoFacturacion.textoInputBox=funcionesmysql.fechaDeHoy()
        txtFechaPrecioFacturacion.textoInputBox=funcionesmysql.fechaDeHoy()

        etiquetaTotal.sereaTotales()
        modeloItemsFactura.clear()

        txtArticuloParaFacturacion.textoInputBox=""

        etiquetaTotalMedioDePago.sereaTotales()
        modeloListaMediosDePagoAgregados.clear()


        btnAgregarNuevoMedioDePago.enabled=true

        txtMontoMedioDePago.textoInputBox=""
        txtCuotasMedioDePago.textoInputBox=""
        txtMontoMedioDePago.enabled=true
        txtCuotasMedioDePago.enabled=true
        txtMontoMedioDePago.enable=true
        txtCuotasMedioDePago.enable=true
        txtNumeroChequeMedioDePago.textoInputBox=""
        txtNumeroChequeMedioDePago.enable=true
        txtNumeroChequeMedioDePago.enabled=true

        txtFechaCheque.enable=true
        txtFechaCheque.enabled=true
        cbxTipoCheque.activo(true)
        cbxListaChequesDiferidos.cerrarComboBox()
        cbxListaChequesDiferidos.activo(true)

        if(txtCodigoClienteFacturacion.visible)
            txtCodigoClienteFacturacion.tomarElFocoP()

        cbxBancosMedioDePago.activo(true)
        cbxCuentasBancarias.activo(true)
        cbxBancosMedioDePago.cerrarComboBox()
        cbxCuentasBancarias.cerrarComboBox()
        cbxAfectaCuentaBancaria.activo(true)
        cbxAfectaCuentaBancaria.cerrarComboBox()

        if(!cbxAfectaCuentaBancaria.visible){
            cbxAfectaCuentaBancaria.codigoValorSeleccion="0"
            cbxAfectaCuentaBancaria.codigoValorSeleccion2="0"
            cbxAfectaCuentaBancaria.textoComboBox=""
        }

        cbxListaPrecioManualFijadaPorUsuario.cerrarComboBox()
        cbxListaPrecioManualFijadaPorUsuario.activo(true)
        cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=""
        cbxListaPrecioManualFijadaPorUsuario.textoComboBox=""

        txtCantidadArticulosFacturacion.enable=true
        txtCantidadArticulosFacturacion.enabled=true

        txtPrecioItemManualFacturacion.enable=true
        txtPrecioItemManualFacturacion.enabled=true

        txtObservacionesFactura.enable=true
        txtObservacionesFactura.enabled=true

        txtComentariosFactura.enable=true
        txtComentariosFactura.enabled=true

        txtCodigoDeBarrasADemanda.enable=true
        txtCodigoDeBarrasADemanda.enabled=true

    }


    //Refresca los combobox de la facturación, por ejemplo cuando se cierra una liquidacion
    function refrescarComboBoxs(codigoDeLiquidacion,vendedorDeLiquidacio){
        if(cbListaLiquidacionesFacturacion.codigoValorSeleccion==codigoDeLiquidacion && cbListaLiquidacionesFacturacion.codigoValorSeleccionExtra==vendedorDeLiquidacio){
            cbListaLiquidacionesFacturacion.textoComboBox=""
            cbListaLiquidacionesFacturacion.codigoValorSeleccion=""
            cbListaLiquidacionesFacturacion.codigoValorSeleccionExtra=""
        }
    }

    Rectangle {
        id: rectContenedor
        x: 0
        y: 30
        color: "#484646"
        radius: 8
        z: 1
        //
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 30
        anchors.fill: parent

        Flow {
            id: flowCuerpoFacturacion
            height: flowCuerpoFacturacion.implicitHeight
            z: 21
            spacing: 5
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: flowCabezalFacturacion.bottom
            anchors.topMargin: 8


            TextInputSimple {
                id: txtNumeroDocumentoFacturacion
                x: 53
                y: -36
                //  width: 130
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                botonBuscarTextoVisible: false
                inputMask: "0000000000;"
                largoMaximo: 9
                botonBorrarTextoVisible: true
                textoTitulo: "Num. documento:"
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaNumeroDocumento")
                onTabulacion: {

                    if(txtSerieFacturacion.visible){
                        txtSerieFacturacion.tomarElFoco()
                    }else if(txtFechaPrecioFacturacion.visible){
                        txtFechaPrecioFacturacion.tomarElFoco()
                    }else if(txtFechaDocumentoFacturacion.visible){
                        txtFechaDocumentoFacturacion.tomarElFoco()
                    }else if(txtArticuloParaFacturacion.visible){
                        txtArticuloParaFacturacion.tomarElFocoP()
                    }
                }
                onEnter: {
                    if(txtSerieFacturacion.visible){
                        txtSerieFacturacion.tomarElFoco()
                    }else if(txtFechaPrecioFacturacion.visible){
                        txtFechaPrecioFacturacion.tomarElFoco()
                    }else if(txtFechaDocumentoFacturacion.visible){
                        txtFechaDocumentoFacturacion.tomarElFoco()
                    }else if(txtArticuloParaFacturacion.visible){
                        txtArticuloParaFacturacion.tomarElFocoP()
                    }
                }
            }

            TextInputSimple {
                id: txtSerieFacturacion
                //  width: 90
                textoInputBox: ""
                botonBuscarTextoVisible: false
                inputMask: ""
                botonBorrarTextoVisible: true
                largoMaximo: 4
                textoTitulo: "Serie:"
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaSerieDocumento")
                onTabulacion: {
                    if(txtFechaPrecioFacturacion.visible){
                        txtFechaPrecioFacturacion.tomarElFoco()
                    }else if(txtFechaDocumentoFacturacion.visible){
                        txtFechaDocumentoFacturacion.tomarElFoco()
                    }else if(txtArticuloParaFacturacion.visible){
                        txtArticuloParaFacturacion.tomarElFocoP()
                    }
                }
                onEnter: {
                    if(txtFechaPrecioFacturacion.visible){
                        txtFechaPrecioFacturacion.tomarElFoco()
                    }else if(txtFechaDocumentoFacturacion.visible){
                        txtFechaDocumentoFacturacion.tomarElFoco()
                    }else if(txtArticuloParaFacturacion.visible){
                        txtArticuloParaFacturacion.tomarElFocoP()
                    }
                }
            }

            ComboBoxListaVendedores {
                id: txtVendedorDeFactura
                width: 170
                z: 2
                textoComboBox: ""
                botonBuscarTextoVisible: false
                textoTitulo: "Vendedor:"
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaVendedor")
                onEnter: {

                    if(txtFechaPrecioFacturacion.visible){
                        txtFechaPrecioFacturacion.tomarElFoco()
                    }else if(txtFechaDocumentoFacturacion.visible){
                        txtFechaDocumentoFacturacion.tomarElFoco()
                    }else if(txtArticuloParaFacturacion.visible){
                        txtArticuloParaFacturacion.tomarElFocoP()
                    }
                }
            }
            ComboBoxListaLiquidaciones {
                id: cbListaLiquidacionesFacturacion
                width: 200
                textoTitulo: "Cajas activas:"
            }

            TextInputSimple {
                id: txtFechaPrecioFacturacion
                x: 27
                y: 95
                //  width: 130
                enFocoSeleccionarTodo: true
                textoInputBox: funcionesmysql.fechaDeHoy()
                validaFormato: validacionFecha
                botonBuscarTextoVisible: false
                inputMask: "nnnn-nn-nn; "
                largoMaximo: 45
                textoTitulo: "Fecha precio:"
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaFechaPrecio")
                onTabulacion: {
                    if(txtFechaDocumentoFacturacion.visible){
                        txtFechaDocumentoFacturacion.tomarElFoco()
                    }else if(txtArticuloParaFacturacion.visible){
                        txtArticuloParaFacturacion.tomarElFocoP()
                    }

                }
                onEnter: {
                    if(txtFechaDocumentoFacturacion.visible){
                        txtFechaDocumentoFacturacion.tomarElFoco()
                    }else if(txtArticuloParaFacturacion.visible){
                        txtArticuloParaFacturacion.tomarElFocoP()
                    }
                }
            }

            TextInputSimple {
                id: txtFechaDocumentoFacturacion
                x: 35
                y: 100
                //   width: 130
                enFocoSeleccionarTodo: true
                textoInputBox: funcionesmysql.fechaDeHoy()
                validaFormato: validacionFecha
                botonBuscarTextoVisible: false
                inputMask: "nnnn-nn-nn; "
                textoTitulo: "Fecha emision:"
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaFechaDocumento")
                onTabulacion: {
                    if(txtArticuloParaFacturacion.visible){
                        txtArticuloParaFacturacion.tomarElFocoP()
                    }
                }
                onEnter: {
                    if(txtArticuloParaFacturacion.visible){
                        txtArticuloParaFacturacion.tomarElFocoP()
                    }
                }
            }

            RegExpValidator{
                id:validacionFecha
                ///Fecha AAAA/MM/DD
                regExp: new RegExp("(20|  |2 | 2)(0[0-9, ]| [0-9, ]|1[0123456789 ]|2[0123456789 ]|3[0123456789 ]|4[0123456789 ])\-(0[1-9, ]| [1-9, ]|1[012 ]| [012 ])\-(0[1-9, ]| [1-9, ]|[12 ][0-9, ]|3[01 ]| [01 ])")
            }

            ComboBoxListaCuentasBancarias {
                id: cbxAfectaCuentaBancaria
                width: 250
                textoTitulo: "Cuenta bancaria afectada:"
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaCuentaBancaria")
            }




        }

        Flipable {
            id: contenedorFlipable
            anchors.top: {

                if(cbListaFormasDePago.visible && cbListaDocumentosCuentaCorrienteConDeuda.visible){
                    flowItemsFijosdocumentoImpresora.bottom
                }else{
                    flowPieFacturacion2.bottom
                }
            }
            anchors.topMargin: 10/*{
                if(cbListaFormasDePago.visible && cbListaDocumentosCuentaCorrienteConDeuda.visible){
                    10
                }else{
                    10
                }

            }*/
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 75
            anchors.right: parent.right
            anchors.rightMargin: 20

            property bool flipped: false
            property int xAxis: 0
            property int yAxis: 1
            property int angle: 180
            //

            transform: Rotation {
                id: rotation
                origin.x: contenedorFlipable.width /2
                origin.y: contenedorFlipable.height / 2
                axis.x: contenedorFlipable.xAxis
                axis.y: contenedorFlipable.yAxis
                axis.z: 0
            }
            states: State {
                name: "back"; when: contenedorFlipable.flipped
                PropertyChanges { target: rotation; angle: contenedorFlipable.angle }
            }
            transitions: Transition {
                ParallelAnimation {

                    NumberAnimation { target: rotation; properties: "angle"; duration: 0 }

                    SequentialAnimation {
                        NumberAnimation { target: contenedorFlipable; property: "scale"; to: 0.85; duration: 120 }
                        NumberAnimation { target: contenedorFlipable; property: "scale"; to: 1.0; duration: 500 }
                    }
                }
            }




            //front
            front:  Rectangle{
                id: rectListaDeArticulos
                color: "#C4C4C6"
                radius: 3
                clip: true
                anchors.fill: parent
                //

                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")
                ListView {
                    id: listaDeItemsFactura
                    x: 5
                    y: 10
                    clip: true
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottomMargin: 25
                    boundsBehavior: Flickable.DragAndOvershootBounds
                    highlightFollowsCurrentItem: true
                    interactive: true
                    spacing: 1
                    anchors.rightMargin: 1
                    anchors.leftMargin: 1
                    anchors.topMargin: 25
                    snapMode: ListView.NoSnap
                    keyNavigationWraps: true
                    highlightRangeMode: ListView.NoHighlightRange
                    flickableDirection: Flickable.VerticalFlick
                    //

                    delegate:  ListaItemsFacturacion{id: itemsFactura


                        onAbrirGarantias: {
                            cuadroListaGarantias.marcaActivoCheckbox(false)
                            cuadroListaGarantias.visible=true
                            cuadroListaGarantias.index=index

                        }

                    }
                    model: modeloItemsFactura
                    onCountChanged: {


                        if(listaDeItemsFactura.count==0 && listaDeMediosDePagoSeleccionados.count==0){
                            cbListaMonedasEnFacturacion.activo(true)
                        }else if(listaDeItemsFactura.count!=0 || listaDeMediosDePagoSeleccionados.count!=0){
                            cbListaMonedasEnFacturacion.activo(false)
                        }
                    }

                    Rectangle {
                        id: scrollbarlistaDeItemsFactura
                        y: listaDeItemsFactura.visibleArea.yPosition * listaDeItemsFactura.height+5
                        width: 10
                        color: "#000000"
                        height: listaDeItemsFactura.visibleArea.heightRatio * listaDeItemsFactura.height+18
                        radius: 2
                        anchors.right: listaDeItemsFactura.right
                        anchors.rightMargin: 4
                        z: 1
                        opacity: 0.500
                        visible: true
                        //
                    }


                }

                ListModel{
                    id:modeloItemsFactura

                }

                Rectangle {
                    id: rectTituloListaItemFacturacion
                    height: 16
                    color: "#2b2a2a"
                    radius: 3
                    anchors.top: parent.top
                    anchors.topMargin: 5
                    anchors.right: parent.right
                    anchors.rightMargin: 25
                    anchors.left: parent.left
                    anchors.leftMargin: 1
                    Text {
                        id: lbltemCodigoArticuloFacturacion
                        width: 70
                        color: "#ffffff"
                        text: "Código"
                        font.family: "Arial"
                        style: Text.Normal
                        horizontalAlignment: Text.AlignHCenter
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        font.bold: true
                        font.pointSize: 10
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectLineaSeparacionTitulo
                        y: 0
                        width: 2
                        color: "#C4C4C6"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.leftMargin: 10
                        anchors.left: lbltemCodigoArticuloFacturacion.right
                    }

                    Text {
                        id: lbltemDescripcionArticuloFacturacion
                        x: 4
                        y: 0
                        width: /// Chequeo si el item comodin esta activo o no, para saber si acorto o dejo como esta el largo de la descripcion
                               /// del item para que no interfiera con el monto referencia del sistema
                               if(txtCodigoDeBarrasADemanda.visible==false){

                                   300

                               }else{

                                   if(lblCostoItemMonedaReferenciaFacturacion.visible){
                                       200
                                   }else{
                                       300
                                   }
                               }



                        //lblCostoItemMonedaReferenciaFacturacion



                        color: "#ffffff"
                        text: "Descripción"
                        font.family: "Arial"
                        style: Text.Normal
                        horizontalAlignment: Text.AlignHCenter
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        font.bold: true
                        font.pointSize: 10
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: rectLineaSeparacion2Titulo.right
                    }

                    Rectangle {
                        id: rectLineaSeparacion2Titulo
                        x: -1
                        y: -4
                        width: {
                            if(lbltemCodigoArticuloBarrasFacturacion.width==0){
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

                            if(lbltemCodigoArticuloBarrasFacturacion.width==0){
                                0
                            }else{
                                10
                            }


                        }
                        anchors.left: lbltemCodigoArticuloBarrasFacturacion.right
                    }

                    Rectangle {
                        id: rectLineaSeparacion3Titulo
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
                        anchors.left: lbltemDescripcionArticuloFacturacion.right
                    }

                    Text {
                        id:lblSubTotalVentaArticuloFacturacion
                        x: 16
                        y: 3
                        width: 100
                        color: "#ffffff"

                        text: "Sub total "+modeloListaMonedas.retornaSimboloMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                        font.family: "Arial"
                        style: Text.Normal
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 50
                        anchors.bottomMargin: 0
                        font.bold: true
                        font.pointSize: 10
                        anchors.right: parent.right
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    Rectangle {
                        id: rectLineaSeparacion4Titulo
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
                        anchors.left: lblSubTotalVentaArticuloFacturacion.right
                    }

                    Text {
                        id: lbltemCodigoArticuloBarrasFacturacion
                        x: 2
                        y: 0
                        width: {
                            if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaCodigoBarrasADemanda")){
                                280
                            }else{
                                0
                            }
                        }
                        color: "#ffffff"
                        text:  {
                            if(width!=0){
                                modeloListaTipoDocumentosComboBox.retornaDescripcionCodigoADemanda(cbListatipoDocumentos.codigoValorSeleccion)
                            }else{
                                ""
                            }
                        }
                        font.family: "Arial"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.bottom: parent.bottom
                        style: Text.Normal
                        anchors.bottomMargin: 0
                        font.bold: true
                        font.pointSize: 10
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: rectLineaSeparacionTitulo.right
                    }

                    Text {
                        id: lbltemCantidadArticuloFacturacion
                        x: 0
                        y: 2
                        width: 82
                        color: "#ffffff"
                        text: "Cantidad"
                        font.family: "Arial"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.bottom: parent.bottom
                        style: Text.Normal
                        anchors.bottomMargin: 0
                        font.bold: true
                        font.pointSize: 10
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 5
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: rectLineaSeparacion3Titulo.right
                    }

                    Rectangle {
                        id: rectLineaSeparacion3Titulo1
                        x: 7
                        y: -2
                        width: 2
                        color: "#C4C4C6"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.leftMargin: 5
                        anchors.left: lbltemCantidadArticuloFacturacion.right
                    }


                    Text {
                        id: lbltemGarantiaArticuloFacturacion
                        x: 0
                        y: 2
                        width: 23
                        color: "#ffffff"
                        text: "GA"
                        font.family: "Arial"

                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.bottom: parent.bottom
                        style: Text.Normal
                        anchors.bottomMargin: 0
                        font.bold: true
                        font.pointSize: 10
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 5
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: rectLineaSeparacion3Titulo1.right
                    }

                    Rectangle {
                        id: rectLineaSeparacion3TituloGarantia
                        x: 7
                        y: -2
                        width: 2
                        color: "#C4C4C6"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.leftMargin: 5
                        anchors.left: lbltemGarantiaArticuloFacturacion.right
                    }



                    Text {
                        id: lbltemTotalVentaFacturacion
                        x: 4
                        y: 2
                        width: 82
                        color: "#ffffff"
                        text: "Unidad "+modeloListaMonedas.retornaSimboloMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                        anchors.top: parent.top
                        font.pointSize: 10
                        anchors.bottomMargin: 0
                        verticalAlignment: Text.AlignVCenter
                        anchors.bottom: parent.bottom
                        font.family: "Arial"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        anchors.left: rectLineaSeparacion3TituloGarantia.right
                        style: Text.Normal
                        //
                        anchors.topMargin: 0
                    }

                    Rectangle {
                        id: rectLineaSeparacion3Titulo2
                        x: 10
                        y: 5
                        width: 2
                        color: "#c4c4c6"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.leftMargin: 10
                        anchors.left: lbltemTotalVentaFacturacion.right

                    }


                    Text {
                        id: lblCostoItemMonedaReferenciaFacturacion
                        x: 4
                        y: 2
                        width: 82
                        color: "#ffffff"
                        text: "Costo en "+modeloMonedas.retornaSimboloMoneda(modeloMonedas.retornaMonedaReferenciaSistema())
                        anchors.top: parent.top
                        font.pointSize: 10
                        anchors.bottomMargin: 0
                        verticalAlignment: Text.AlignVCenter
                        anchors.bottom: parent.bottom
                        font.family: "Arial"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        anchors.left: rectLineaSeparacion3Titulo2.right
                        style: Text.Normal
                        //
                        anchors.topMargin: 0
                        visible: txtCostoArticuloMonedaReferencia.visible
                    }

                    Rectangle {
                        id: rectLineaSeparacion3Titulo3
                        x: 10
                        y: 5
                        width: 2
                        visible: txtCostoArticuloMonedaReferencia.visible
                        color: "#c4c4c6"
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.leftMargin: 10
                        anchors.left: lblCostoItemMonedaReferenciaFacturacion.right
                    }



                    opacity: 1
                }

                Text {
                    id: txtCantidadDeItemsFacturacionValor
                    x: 107
                    width: 37
                    color: "#000000"
                    text: listaDeItemsFactura.count
                    font.family: "Arial"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5
                    //
                    font.bold: false
                    font.pointSize: 10
                    anchors.leftMargin: 5
                    anchors.left: txtCantidadDeItemsFacturacionTitulo.right
                    visible: true

                    onTextChanged: superaCantidadMaximaLineasDocumento()
                }




                Text {
                    id: txtMensajeLimiteLineasMaximas
                    x: 107
                    width: 37
                    color: "#ff0000"
                    text: "Se alcanzó el limite de lineas para el documento ( "+modeloListaTipoDocumentosMantenimiento.cantidadMaximaLineasTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion)+" )"
                    font.family: "Arial"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5
                    //
                    font.bold: true
                    font.pointSize: 10
                    anchors.leftMargin: 10
                    anchors.left: txtCantidadDeItemsFacturacionValor.right
                    visible: false
                }

                Text {
                    id: txtCantidadDeItemsFacturacionTitulo
                    x: 0
                    width: txtCantidadDeItemsFacturacionTitulo.implicitWidth
                    color: "#000000"
                    text: qsTr("Cantidad de items:")
                    font.family: "Arial"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5
                    //
                    font.bold: false
                    font.pointSize: 10
                    anchors.leftMargin: 5
                    anchors.left: parent.left
                    visible: true
                }

                BotonBarraDeHerramientas {
                    id: botonBajarListaFinal
                    x: 848
                    y: 263
                    width: 14
                    height: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 3
                    toolTip: ""
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5
                    source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                    rotation: -90

                    onClic: listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                }

                BotonBarraDeHerramientas {
                    id: botonSubirListaFinal
                    x: 845
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

                    onClic: listaDeItemsFactura.positionViewAtIndex(0,0)
                }

            }
            //back
            back: Rectangle {
                id: rectMediosDePago
                color: "#ebf0f0"
                radius: 3
                //
                anchors.fill: parent
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")

                Rectangle {
                    id: rectContenedorListaMediosDePago
                    width: 280
                    color: "#C4C4C6"
                    anchors.top: parent.top
                    anchors.topMargin: 28
                    anchors.bottom: btnAgregarNuevoMedioDePago.top
                    anchors.bottomMargin: 10
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    //

                    ListView {
                        id: listaDeMediosDePago
                        clip: true
                        anchors.topMargin: 5
                        anchors.right: rectangle3.left
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.bottomMargin: 10
                        anchors.leftMargin: 1
                        anchors.rightMargin: 2
                        highlightRangeMode: ListView.NoHighlightRange
                        boundsBehavior: Flickable.DragAndOvershootBounds
                        highlightFollowsCurrentItem: true
                        delegate: ListaMediosDePago {
                        }
                        snapMode: ListView.NoSnap
                        spacing: 1
                        flickableDirection: Flickable.VerticalFlick
                        keyNavigationWraps: true
                        interactive: true
                        //
                        model: modeloMediosDePago
                    }

                    Rectangle {
                        id: rectangle3
                        x: 625
                        width: 14
                        color: "#e9e8e9"
                        radius: 3
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5

                        BotonBarraDeHerramientas {
                            id: botonBajarListaFinal1
                            x: 12
                            y: 171
                            width: 14
                            height: 14
                            anchors.horizontalCenter: parent.horizontalCenter
                            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                            anchors.bottom: parent.bottom
                            anchors.horizontalCenterOffset: 0
                            toolTip: ""
                            anchors.bottomMargin: 5
                            rotation: -90
                            onClic: listaDeMediosDePago.positionViewAtIndex(listaDeMediosDePago.count-1,0)
                        }

                        BotonBarraDeHerramientas {
                            id: botonSubirListaFinal1
                            x: 0
                            width: 14
                            height: 14
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: parent.top
                            anchors.topMargin: 10
                            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                            toolTip: ""
                            rotation: 90
                            onClic:  listaDeMediosDePago.positionViewAtIndex(0,0)

                        }
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 3
                        anchors.bottomMargin: 5
                        anchors.right: parent.right
                    }
                }

                Rectangle {
                    id: rectContenedorListaMediosDePagoRealizados
                    x: 449
                    y: 28
                    width: 400
                    height: 55
                    color: "#C4C4C6"
                    anchors.top: parent.top
                    anchors.topMargin: 50
                    anchors.bottom: etiquetaTotalMedioDePago.top
                    anchors.bottomMargin: 5
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    //
                    ListView {
                        id: listaDeMediosDePagoSeleccionados
                        clip: true
                        anchors.right: rectangle6.left
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.rightMargin: 2
                        anchors.leftMargin: 1
                        anchors.bottomMargin: 10
                        anchors.topMargin: 5
                        //
                        interactive: true
                        spacing: 1
                        snapMode: ListView.NoSnap
                        keyNavigationWraps: true
                        flickableDirection: Flickable.VerticalFlick
                        highlightFollowsCurrentItem: true
                        delegate: ListaMediosDePagoAgregadosAFacturacion {
                        }
                        model: modeloListaMediosDePagoAgregados
                        boundsBehavior: Flickable.DragAndOvershootBounds
                        highlightRangeMode: ListView.NoHighlightRange

                        onCountChanged: {


                            if(listaDeItemsFactura.count==0 && listaDeMediosDePagoSeleccionados.count==0){
                                cbListaMonedasEnFacturacion.activo(true)
                            }else if(listaDeItemsFactura.count!=0 || listaDeMediosDePagoSeleccionados.count!=0){
                                cbListaMonedasEnFacturacion.activo(false)
                            }

                        }

                    }


                    ListModel{
                        id:modeloListaMediosDePagoAgregados
                    }

                    Rectangle {
                        id: rectangle6
                        x: 625
                        width: 14
                        color: "#e9e8e9"
                        radius: 3
                        //
                        anchors.top: parent.top
                        anchors.topMargin: 5

                        BotonBarraDeHerramientas {
                            id: botonBajarListaFinal4
                            x: 12
                            y: 171
                            width: 14
                            height: 14
                            anchors.horizontalCenter: parent.horizontalCenter
                            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                            anchors.bottom: parent.bottom
                            anchors.horizontalCenterOffset: 0
                            toolTip: ""
                            anchors.bottomMargin: 5
                            rotation: -90
                        }

                        BotonBarraDeHerramientas {
                            id: botonSubirListaFinal4
                            x: 0
                            width: 14
                            height: 14
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: parent.top
                            anchors.topMargin: 10
                            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                            toolTip: ""
                            rotation: 90
                        }
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 3
                        anchors.bottomMargin: 5
                        anchors.right: parent.right
                    }
                }

                Text {
                    id: txtMedioDePagoSeleccionado
                    color: "#333333"
                    text: qsTr("Medio de pago: ")
                    font.family: "Arial"
                    font.bold: true
                    anchors.top: parent.top
                    anchors.topMargin: 28
                    anchors.left: rectContenedorListaMediosDePago.right
                    anchors.leftMargin: 10
                    font.pixelSize: 12
                }

                Text {
                    id: lblInformacionMediosDePago
                    x: 0
                    color: "#333333"
                    text: qsTr("Clic para seleccionar medio de pago.")
                    font.family: "Arial"
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    //
                    font.pixelSize: 12
                    //     anchors.bottom: rectArticulosFacturacion.top
                    //     anchors.bottomMargin: 5
                    anchors.leftMargin: 10
                    anchors.left: parent.left
                }

                BotonPaletaSistema {
                    id: btnAgregarNuevoMedioDePago
                    text: "Agregar medio de pago"
                    border.color: "#787777"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    onClicked: {

                        agregarMedioDePago()

                    }
                }

                Text {
                    id: txtCodigoMedioDePago
                    x: 265
                    y: 13
                    text: qsTr("")
                    font.family: "Arial"
                    visible: false
                    anchors.bottom: txtMedioDePagoSeleccionado.top
                    anchors.bottomMargin: 1
                    font.pixelSize: 12
                }

                EtiquetaTotal {
                    id: etiquetaTotalMedioDePago
                    styleLabeltotal: 0
                    tamanioPixelLabeltotal: 15
                    labelTotal: qsTr("Total medios de pago "+modeloListaMonedas.retornaSimboloMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion))
                    colorLabelTotal: "#2b2a2a"
                    colorTotales: "#0eb91c"
                    labelSubTotalVisible: true
                    labelIvaVisible: true
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5
                    descuentosVisible: false
                }

                Flow {
                    id: column1
                    flow: Flow.TopToBottom
                    spacing: 5
                    anchors.right: rectContenedorListaMediosDePagoRealizados.left
                    anchors.rightMargin: 20
                    anchors.top: parent.top
                    anchors.topMargin: 50
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    anchors.left: rectContenedorListaMediosDePago.right
                    anchors.leftMargin: 10

                    TextInputSimple {
                        id: txtMontoMedioDePago
                        //   width: 150
                        enFocoSeleccionarTodo: true
                        textoInputBox: ""+modeloconfiguracion.retornaCantidadDecimalesString()+""
                        botonBuscarTextoVisible: false
                        inputMask: "00000000"+modeloconfiguracion.retornaCantidadDecimalesString()+";"
                        largoMaximo: 45
                        textoTitulo: "Monto a grabar:"
                        colorDeTitulo: "#333333"

                        onTabulacion: {

                            if(txtCuotasMedioDePago.visible)
                            {
                                txtCuotasMedioDePago.tomarElFoco()
                            }else if(txtNumeroChequeMedioDePago.visible){
                                txtNumeroChequeMedioDePago.tomarElFoco()
                            }else if(cbxCuentasBancarias.visible){
                                cbxCuentasBancarias.tomarElFoco()
                            }
                        }
                        onEnter: {

                            if(txtCuotasMedioDePago.visible)
                            {
                                txtCuotasMedioDePago.tomarElFoco()
                            }else if(txtNumeroChequeMedioDePago.visible){
                                txtNumeroChequeMedioDePago.tomarElFoco()
                            }else if(cbxCuentasBancarias.visible){
                                cbxCuentasBancarias.tomarElFoco()
                            }else{
                                agregarMedioDePago()
                            }

                        }

                    }

                    TextInputSimple {
                        id: txtCuotasMedioDePago
                        //      width: 80
                        visible: false
                        colorDeTitulo: "#333333"
                        enFocoSeleccionarTodo: true
                        textoInputBox: "0"
                        botonBuscarTextoVisible: false
                        inputMask: "00;"
                        largoMaximo: 2
                        botonBorrarTextoVisible: true
                        textoTitulo: "Cuotas:"
                        onTabulacion: txtMontoMedioDePago.tomarElFoco()

                        onEnter: cbxTarjetaCreditoMedioDePago.tomarElFoco()
                    }

                    ComboBoxListaTarjetasCredito {
                        id: cbxTarjetaCreditoMedioDePago
                        width: 200
                        visible: false
                        z: 6
                        colorTitulo: "#333333"
                        textoTitulo: "Tarjeta credito:"
                        colorRectangulo: "#cac1bd"

                        onEnter: {
                            agregarMedioDePago()
                        }
                    }

                    TextInputSimple {
                        id: txtNumeroChequeMedioDePago
                        //   width: 200
                        enFocoSeleccionarTodo: true
                        textoInputBox: "0"
                        visible: false
                        botonBuscarTextoVisible: false
                        inputMask: ""
                        largoMaximo: 20
                        botonBorrarTextoVisible: true
                        textoTitulo: "Número cheque:"
                        colorDeTitulo: "#333333"
                        onEnter: {

                            cbxBancosMedioDePago.tomarElFoco()

                        }
                    }

                    ComboBoxListaBancos {
                        id: cbxBancosMedioDePago
                        width: 200
                        z: 5
                        visible: false
                        textoTitulo: "Banco:"
                        colorTitulo: "#333333"
                        colorRectangulo: "#cac1bd"
                        onEnter: {
                            if(cbxTipoCheque.visible){
                                cbxTipoCheque.tomarElFoco()
                            }
                        }
                    }

                    ComboBoxListaTipoCheque {
                        id: cbxTipoCheque
                        width: 200
                        colorRectangulo: "#cac1bd"
                        z: 4
                        visible: false
                        textoTitulo: "Tipo de cheque:"
                        colorTitulo: "#333333"
                        onEnter: {
                            txtFechaCheque.tomarElFoco()
                        }
                    }

                    TextInputSimple {
                        id: txtFechaCheque
                        // width: 130
                        colorDeTitulo: "#333333"
                        visible: false
                        enFocoSeleccionarTodo: true
                        textoInputBox: funcionesmysql.fechaDeHoy()
                        validaFormato: validacionFecha
                        botonBuscarTextoVisible: false
                        inputMask: "nnnn-nn-nn; "
                        largoMaximo: 45
                        textoTitulo: "Fecha cheque:"
                        onEnter: {
                            agregarMedioDePago()
                        }
                        onTabulacion: {
                            txtMontoMedioDePago.tomarElFoco()
                        }
                    }

                    ComboBoxListaCuentasBancarias {
                        id: cbxCuentasBancarias
                        width: 300
                        textoTitulo: "Cuenta bancaria:"
                        colorTitulo: "#333333"
                        colorRectangulo: "#cac1bd"
                        visible: false
                        onSenialAlAceptarOClick: {

                            agregarMedioDePago()
                        }
                    }
                }

                ComboBoxListaChequesDiferidos {
                    id: cbxListaChequesDiferidos
                    width: 380
                    colorRectangulo: "#cac1bd"
                    anchors.left: rectContenedorListaMediosDePagoRealizados.right
                    anchors.leftMargin: rectContenedorListaMediosDePagoRealizados.width*-1
                    textoTitulo: "Lista cheques disponibles:"
                    colorTitulo: "#333333"
                    z: 1
                    anchors.top: parent.top
                    anchors.topMargin: 10

                    visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaPagoChequeDiferido")
                }
            }

            state: "front"
        }

        ComboBoxListaTipoDocumentos {
            id: cbListatipoDocumentos
            x: 20
            y: -30
            width: 250
            height: 25
            colorRectangulo: "#eceeee"
            textoTitulo: ""
            botonBuscarTextoVisible: false
            z: 22
            codigoValorSeleccion: "1"
            textoComboBox: modeloListaTipoDocumentosComboBox.retornaDescripcionTipoDocumento("1")
            Component.onCompleted: {
                if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")=="1" ){
                    elDocumentoUsaArticulos=true
                }else{
                    elDocumentoUsaArticulos=false
                }

                if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"esDocumentoDeVenta")=="1" ){
                    esUnDocumentoDeVenta=true
                }else{
                    esUnDocumentoDeVenta=false
                }
            }

            onCodigoValorSeleccionChanged: {


                setearDocumento()

                //if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento())

                if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")=="1" ){
                    elDocumentoUsaArticulos=true
                }else{
                    elDocumentoUsaArticulos=false
                }

                if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"esDocumentoDeVenta")=="1" ){
                    esUnDocumentoDeVenta=true
                }else{
                    esUnDocumentoDeVenta=false
                }





                // control para saber si borrar los articulos de la lista de item de la factura al cambiar de documento
                if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")=="1"  &&
                        modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaTotales")=="1" &&
                        modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"afectaTotales")==modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(codigoTipoDocumentoUsadoAnteriormente,"afectaTotales") &&
                        modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"esDocumentoDeVenta")=="1"

                        ){

                    if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaDescuentoTotal")!=modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(codigoTipoDocumentoUsadoAnteriormente,"utilizaDescuentoTotal")  ){
                        crearNuevaFactura()
                        txtCodigoClienteFacturacion.textoInputBox=""
                        lblRazonSocialCliente.text=""
                        txtCodigoClienteFacturacion.tomarElFocoP()
                    }


                }else{
                    crearNuevaFactura()
                    txtCodigoClienteFacturacion.textoInputBox=""
                    lblRazonSocialCliente.text=""
                    txtCodigoClienteFacturacion.tomarElFocoP()
                }



                if(txtNumeroDocumentoFacturacion.visible){
                    txtNumeroDocumentoFacturacion.textoInputBox=modeloDocumentos.retornoCodigoUltimoDocumentoDisponible(cbListatipoDocumentos.codigoValorSeleccion)
                }else{
                    txtNumeroDocumentoFacturacion.textoInputBox=""
                }



                txtTipoClienteFacturacion.activo(false)
                txtTipoClienteFacturacion.enabled=false

                codigoTipoDocumentoUsadoAnteriormente=cbListatipoDocumentos.codigoValorSeleccion

                if(modeloconfiguracion.retornaValorConfiguracion("UTILIZA_CONTROL_CLIENTE_CREDITO")=="1"){
                    if(txtCodigoClienteFacturacion.textoInputBox.trim()!="" && lblRazonSocialCliente.text.trim()!=""){
                        if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"afectaCuentaCorriente")!="0"){
                            if(modeloClientes.retornaSiPermiteFacturaCredito(txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion)==false){

                                setearEstadoActivoBotonesGuardar(false)
                                funcionesmysql.mensajeAdvertenciaOk("El cliente no esta habilitado para documentos CRÉDITO.\n\n No se podrá emitir el documento ni guardarlo.")

                            }
                        }
                    }
                }



            }

        }




        EtiquetaTotal {
            id: etiquetaTotal
            x: 440
            y: 395
            labelSubTotalVisible: true
            labelIvaVisible: true
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            labelTotal: qsTr("Total "+modeloListaMonedas.retornaSimboloMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion))
            labelTotalDescuentos: qsTr("Descuento "+modeloListaMonedas.retornaSimboloMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion))
            visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaTotales")
            descuentosVisible: {

                if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaDescuentoTotal") || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaDescuentoArticulo")){
                    true
                }else{
                    false
                }
            }
            onRequieroPermisoParaDescuento: {

                if(rectOpcionesExtras.anchors.leftMargin==-68){
                    rectOpcionesExtrasDesaparecer.start()
                    rowBarraDeHerramientas.enabled=true
                    btnBuscarMasClientes.enabled=true
                    btnBuscarMasArticulos.enabled=true
                }
                if(rectOpcionesExtrasArticulosFacturacion.anchors.leftMargin==-68){
                    rectOpcionesExtrasArticulosFacturacionDesaparecer.start()
                    rowBarraDeHerramientas.enabled=true
                    btnBuscarMasClientes.enabled=true
                    btnBuscarMasArticulos.enabled=true
                }


                if(modeloconfiguracion.retornaValorConfiguracion("MODO_AUTORIZACION")=="1"){
                    rectContenedor.enabled=false
                    cuadroAutorizacionFacturacion.evaluarPermisos("permiteAutorizarDescuentosTotal")
                }else{
                    cuadroAutorizacionFacturacion.noSeRequierenAutorizaciones("permiteAutorizarDescuentosTotal")
                }


            }
        }

        Flow {
            id: flowCabezalFacturacion
            height: flowCabezalFacturacion.implicitHeight
            spacing: 5
            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.rightMargin: 10
            z: 21
            anchors.right: parent.right
            anchors.leftMargin: 10
            anchors.left: parent.left

            ComboBoxListaTipoCliente {
                id: txtTipoClienteFacturacion
                width: 120
                botonBuscarTextoVisible: false
                textoTitulo: "Tipo de Cliente:"
                z: 102
                codigoValorSeleccion: "1"
                textoComboBox: modeloTipoClientes.primerRegistroDeTipoClienteEnBase("1")
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaTipoCliente")

                onEnter: {

                    if(txtCodigoClienteFacturacion.visible){
                        txtCodigoClienteFacturacion.tomarElFocoP()
                    }else if(txtNumeroDocumentoFacturacion.visible){
                        txtNumeroDocumentoFacturacion.tomarElFoco()
                    }else if(txtSerieFacturacion.visible){
                        txtSerieFacturacion.tomarElFoco()
                    }else if(txtFechaPrecioFacturacion.visible){
                        txtFechaPrecioFacturacion.tomarElFoco()
                    }else if(txtFechaDocumentoFacturacion.visible){
                        txtFechaDocumentoFacturacion.tomarElFoco()
                    }else if(txtArticuloParaFacturacion.visible){
                        txtArticuloParaFacturacion.tomarElFocoP()
                    }

                }

            }




            TextInputP {
                id: txtCodigoClienteFacturacion
                x: 53
                y: -36
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


                onTextoInputBoxChanged: {

                    lblRazonSocialCliente.text=""
                    modeloComboBoxDocumentosConSaldoCuentaCorriente.limpiarListaDocumentos()
                    modeloListaTipoDocumentosConDeudaVirtual.clear()
                    cbListaDocumentosCuentaCorrienteConDeuda.cerrarComboBox()

                }

                botonNuevoVisible: {
                    if(modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarClientes") && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearClientes")){
                        true
                    }else{
                        false
                    }
                }
                textoTituloFiltro: "Buscar por: dirección, nombre, razon o rut"
                listviewModel:modeloClientesFiltros
                listviewDelegate: Delegate_ListaClientesFiltros{
                    onSenialAlAceptarOClick: {
                        txtCodigoClienteFacturacion.textoInputBox=codigoValorSeleccion
                        txtTipoClienteFacturacion.codigoValorSeleccion=codigoValorSeleccionTipoCliente
                        txtTipoClienteFacturacion.textoComboBox=modeloTipoClientes.primerRegistroDeTipoClienteEnBase(codigoValorSeleccionTipoCliente)
                        txtCodigoClienteFacturacion.tomarElFocoP()
                        txtCodigoClienteFacturacion.cerrarComboBox()

                        setearFormaDePagoYMonedaDefaulCliente();

                    }
                    onKeyEscapeCerrar: {
                        txtCodigoClienteFacturacion.tomarElFocoP()
                        txtCodigoClienteFacturacion.cerrarComboBox()
                    }
                }
                onClicBotonNuevoItem: {
                    mostrarMantenimientos(1,"derecha")
                }

                onClicEnBusquedaFiltro: {
                    var consultaSqlCliente=" (razonSocial rlike '"+textoAFiltrar+"' or direccion rlike '"+textoAFiltrar+"' or rut rlike '"+textoAFiltrar+"' or nombreCliente rlike '"+textoAFiltrar+"') and Clientes.tipoCliente=";
                    modeloClientesFiltros.clearClientes()
                    modeloClientesFiltros.buscarCliente(consultaSqlCliente,txtTipoClienteFacturacion.codigoValorSeleccion)
                    if(modeloClientesFiltros.rowCount()!=0){
                        tomarElFocoResultado()
                    }
                }


                onClicEnBusqueda: {
                    lblRazonSocialCliente.text=""

                    var datosDeCliente=modeloClientes.retornaDescripcionDeCliente(txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion);

                    if(datosDeCliente==""){
                        txtTipoClienteFacturacion.activo(true)
                        txtCodigoClienteFacturacion.tomarElFocoP()
                    }else{
                        lblRazonSocialCliente.text="Facturar a: "+datosDeCliente
                        cargarDocumentosConDeuda()
                        txtTipoClienteFacturacion.activo(false)
                    }
                }
                onTabulacion: {

                    if(txtSerieFacturacion.visible){
                        txtSerieFacturacion.tomarElFoco()
                    }else if(txtFechaPrecioFacturacion.visible){
                        txtFechaPrecioFacturacion.tomarElFoco()
                    }else if(txtFechaDocumentoFacturacion.visible){
                        txtFechaDocumentoFacturacion.tomarElFoco()
                    }else if(txtArticuloParaFacturacion.visible){
                        txtArticuloParaFacturacion.tomarElFocoP()
                    }
                }

                onEnter: {
                    lblRazonSocialCliente.text=""


                    var datosDeCliente=modeloClientes.retornaDescripcionDeCliente(txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion);
                    if(datosDeCliente==""){
                        txtTipoClienteFacturacion.activo(true)
                        txtCodigoClienteFacturacion.tomarElFocoP()
                    }else{
                        lblRazonSocialCliente.text="Facturar a: "+datosDeCliente
                        cargarDocumentosConDeuda()
                        txtTipoClienteFacturacion.activo(false)

                        if(txtSerieFacturacion.visible){
                            txtSerieFacturacion.tomarElFoco()
                        }else if(txtFechaPrecioFacturacion.visible){
                            txtFechaPrecioFacturacion.tomarElFoco()
                        }else if(txtFechaDocumentoFacturacion.visible){
                            txtFechaDocumentoFacturacion.tomarElFoco()
                        }else if(txtArticuloParaFacturacion.visible){
                            txtArticuloParaFacturacion.tomarElFocoP()
                        }




                        setearFormaDePagoYMonedaDefaulCliente();





                        if(modeloconfiguracion.retornaValorConfiguracion("UTILIZA_CONTROL_CLIENTE_CREDITO")=="1"){
                            if(txtCodigoClienteFacturacion.textoInputBox.trim()!="" && lblRazonSocialCliente.text.trim()!=""){
                                if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"afectaCuentaCorriente")!="0"){
                                    if(modeloClientes.retornaSiPermiteFacturaCredito(txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion)==false){

                                        setearEstadoActivoBotonesGuardar(false)
                                        funcionesmysql.mensajeAdvertenciaOk("El cliente no esta habilitado para documentos CRÉDITO.\n\n No se podrá emitir el documento ni guardarlo.")

                                    }else{
                                        setearEstadoActivoBotonesGuardar(true)
                                    }
                                }
                            }
                        }

                    }
                }// fin onEnter
            }



            BotonCargarDato {
                id: btnBuscarMasClientes
                height: 35
                anchors.top: parent.top
                anchors.topMargin: 7
                textoColor: "#dbd8d8"
                texto: "mas clientes..."
                imagen: "qrc:/imagenes/qml/ProyectoQML/Imagenes/SumaBlanca.png"
                onClic: {

                    rectOpcionesExtrasDesaparecer.stop()
                    rectOpcionesExtrasAparecer.start()
                    cbListatipoDocumentos.cerrarComboBox()
                    rowBarraDeHerramientas.enabled=false

                    btnBuscarMasClientes.volverAEstadoOriginalElControl()

                    btnBuscarMasClientes.enabled=false

                    txtCodigoClienteFacturacionOpcionesExtras.tomarElFoco()

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=false



                }
            }


            Rectangle{
                width: lblRazonSocialCliente.implicitWidth -10
                height: 25
                color: "#f55858"
                radius: 7
                visible: txtCodigoClienteFacturacion.visible
                clip: true
                Text {
                    id: lblRazonSocialCliente
                    color: "#ffffff"
                    text: ""
                    anchors.rightMargin: 5
                    anchors.leftMargin: 5
                    anchors.fill: parent
                    styleColor: "#be5e5e"
                    font.family: "Arial"
                    font.underline: false
                    font.italic: false
                    style: Text.Raised
                    //
                    font.pixelSize: 14
                    font.bold: true
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }
            }


        }

        Flow {
            id: flowPieFacturacion
            height: flowPieFacturacion.implicitHeight
            spacing: 5
            z: 19
            anchors.top: flowCuerpoFacturacion.bottom
            anchors.topMargin: 8
            anchors.right: flowItemsFijosdocumentoImpresora.left
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10

            TextInputP {
                id: txtArticuloParaFacturacion
                width: 297
                tamanioRectPrincipalCombobox: 320
                tamanioRectPrincipalComboboxAlto: {
                    if(checkBoxActivoVisible){
                        400
                    }else{
                        300
                    }
                }
                z: 1
                botonNuevoTexto: "Nuevo artículo..."
                utilizaListaDesplegable: true
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                botonBuscarTextoVisible: false
                largoMaximo: 30
                textoDeFondo: ""
                textoTitulo: "Artículo:"
                colorDeTitulo: "#dbd8d8"
                checkBoxActivoVisible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")
                checkBoxActivoTexto: "Incluir artículos inactivos"
                botonNuevoVisible:{
                    if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos") && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearArticulos")){
                        true
                    }else{
                        false
                    }
                }




                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")
                textoTituloFiltro: "Buscar por: descripción, proveedor, iva o moneda"
                listviewModel:modeloArticulosFiltros
                listviewDelegate: Delegate_ListaArticulosFiltros{
                    permiteOperarConArticulosInactivos:  txtArticuloParaFacturacion.checkBoxActivoVisible
                    onSenialAlAceptarOClick: {
                        txtArticuloParaFacturacion.textoInputBox=codigoValorSeleccion
                        txtArticuloParaFacturacion.tomarElFocoP()
                        txtArticuloParaFacturacion.cerrarComboBox()
                    }
                    onKeyEscapeCerrar: {
                        txtArticuloParaFacturacion.tomarElFocoP()
                        txtArticuloParaFacturacion.cerrarComboBox()
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

                    modeloArticulosFiltros.clearArticulos()
                    modeloArticulosFiltros.buscarArticulo(consultaSqlArticulo,"1",0)

                    if(modeloArticulosFiltros.rowCount()!=0){
                        tomarElFocoResultado()
                    }
                }


                onEnter: {

                    funcionesmysql.loguear("QML::txtArticuloParaFacturacion::onEnter")



                    valorArticuloInterno=modeloArticulos.existeArticulo(txtArticuloParaFacturacion.textoInputBox.trim());

                    if(valorArticuloInterno!="" && !superaCantidadMaximaLineasDocumento()){
                        codigoDeBarraArticulo=''

                        ///Chequeo que modo de calculo de total esta seteado
                        var modoCalculoTotal=modeloconfiguracion.retornaValorConfiguracion("MODO_CALCULOTOTAL");

                        if(txtArticuloParaFacturacion.textoInputBox.trim().length>6)
                            codigoDeBarraArticulo =txtArticuloParaFacturacion.textoInputBox.trim()

                        txtArticuloParaFacturacion.textoInputBox=valorArticuloInterno

                        if(modeloArticulos.retornaArticuloActivo(valorArticuloInterno) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")){





                            /// Si cantidad no esta visible
                            if(txtCantidadArticulosFacturacion.visible==false){

                                funcionesmysql.loguear("QML::txtCantidadArticulosFacturacion.visible==false")


                                if(txtPrecioItemManualFacturacion.visible==false){

                                    funcionesmysql.loguear("QML::txtPrecioItemManualFacturacion.visible==false")

                                    if(txtCostoArticuloMonedaReferencia.visible==false){

                                        funcionesmysql.loguear("QML::txtCostoArticuloMonedaReferencia.visible==false")

                                        if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaCodigoBarrasADemanda")){

                                            codigoDeBarraArticulo=''
                                            txtCodigoDeBarrasADemanda.textoInputBox=""
                                            txtCodigoDeBarrasADemanda.tomarElFoco()

                                        }
                                        else{


                                            if(txtCodigoClienteFacturacion.textoInputBox!=""){ //Hay un cliente seleccionado

                                                funcionesmysql.loguear("QML::Hay un cliente seleccionado")

                                                var listaPrecioSeleccionada
                                                if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                    listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(txtFechaPrecioFacturacion.textoInputBox.trim(), txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim())
                                                }else{
                                                    listaPrecioSeleccionada=cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion
                                                }

                                                funcionesmysql.loguear("QML::listaPrecioSeleccionada: "+listaPrecioSeleccionada)


                                                if(listaPrecioSeleccionada!=""){

                                                    funcionesmysql.loguear("QML::Con lista de precios seleccionada")

                                                    funcionesmysql.loguear("QML::listaPrecioSeleccionada: "+listaPrecioSeleccionada)


                                                    var precioArticuloSelecionado=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,listaPrecioSeleccionada)

                                                    var cotizacion=1;
                                                    valorPrecioArticulo2=precioArticuloSelecionado

                                                    if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                        if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                            cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                            valorPrecioArticulo2=precioArticuloSelecionado/cotizacion
                                                        }else{

                                                            if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                                cotizacion=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                                valorPrecioArticulo2=precioArticuloSelecionado*cotizacion
                                                            }else{
                                                                valorPrecioArticulo2=(precioArticuloSelecionado*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                            }
                                                        }
                                                    }

                                                    costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();
                                                    //costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                    //txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""


                                                    //Controlo si se peude vender sin stock previsto
                                                    if(modeloArticulos.retornaSiPuedeVenderSinStock(1,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                        funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                        funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)

                                                        funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                        funcionesmysql.loguear("QML::cantidadItems: 1")



                                                        modeloItemsFactura.append({
                                                                                      codigoArticulo:valorArticuloInterno,
                                                                                      codigoBarrasArticulo:codigoDeBarraArticulo,
                                                                                      descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                                      descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                                      precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                      precioArticuloSubTotal:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                      cantidadItems:1,
                                                                                      costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                      activo:true,
                                                                                      consideraDescuento:false,
                                                                                      indiceLinea:-1,
                                                                                      descuentoLineaItem:0,
                                                                                      codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                                      descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                                      asignarGarantiaAArticulo:false
                                                                                  })
                                                        listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)




                                                        if(modoCalculoTotal=="1"){
                                                            etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                        }else if(modoCalculoTotal=="2"){
                                                            etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                        }

                                                        mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")

                                                        txtCantidadArticulosFacturacion.textoInputBox=""
                                                        txtArticuloParaFacturacion.textoInputBox=""
                                                        txtPrecioItemManualFacturacion.textoInputBox=""
                                                        txtCodigoDeBarrasADemanda.textoInputBox=""
                                                        txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

                                                        txtArticuloParaFacturacion.tomarElFocoP()

                                                    }

                                                }else{

                                                    funcionesmysql.loguear("QML::Sin lista de precios seleccionada")

                                                    var precioArticuloSelecionadoSinLista
                                                    if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                        precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                                    }else{
                                                        precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                                    }



                                                    var cotizacion2=1;
                                                    valorPrecioArticulo2=precioArticuloSelecionadoSinLista

                                                    if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                        if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                            cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                            valorPrecioArticulo2=precioArticuloSelecionadoSinLista/cotizacion2
                                                        }else{

                                                            if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                                cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                                valorPrecioArticulo2=precioArticuloSelecionadoSinLista*cotizacion2
                                                            }else{
                                                                valorPrecioArticulo2=(precioArticuloSelecionadoSinLista*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                            }



                                                        }
                                                    }


                                                    costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                                    //Controlo si se peude vender sin stock previsto
                                                    if(modeloArticulos.retornaSiPuedeVenderSinStock(1,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                        funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                        funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)

                                                        funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                        funcionesmysql.loguear("QML::cantidadItems: 1")


                                                        modeloItemsFactura.append({
                                                                                      codigoArticulo:valorArticuloInterno,
                                                                                      codigoBarrasArticulo:codigoDeBarraArticulo,
                                                                                      descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                                      descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                                      precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                      precioArticuloSubTotal:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                      cantidadItems:1,
                                                                                      costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                      activo:true,
                                                                                      consideraDescuento:false,
                                                                                      indiceLinea:-1,
                                                                                      descuentoLineaItem:0,
                                                                                      codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                                      descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                                      asignarGarantiaAArticulo:false
                                                                                  })
                                                        listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                                        if(modoCalculoTotal=="1"){
                                                            etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                        }else if(modoCalculoTotal=="2"){
                                                            etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                        }

                                                        mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")

                                                        txtCantidadArticulosFacturacion.textoInputBox=""
                                                        txtArticuloParaFacturacion.textoInputBox=""
                                                        txtPrecioItemManualFacturacion.textoInputBox=""
                                                        txtCodigoDeBarrasADemanda.textoInputBox=""
                                                        txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

                                                        txtArticuloParaFacturacion.tomarElFocoP()
                                                    }
                                                }

                                            }else{

                                                funcionesmysql.loguear("QML::No hay un cliente seleccionado")

                                                var precioArticuloSelecionadoSinListaySinCliente
                                                if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                    precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                                }else{
                                                    precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                                }

                                                var cotizacion3=1;
                                                valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente

                                                if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                    if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){

                                                        cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                        valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente/cotizacion3

                                                    }else{
                                                        if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                            cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                            valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente*cotizacion3
                                                        }else{
                                                            valorPrecioArticulo2=(precioArticuloSelecionadoSinListaySinCliente*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                        }
                                                    }
                                                }

                                                costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                                //Controlo si se peude vender sin stock previsto
                                                if(modeloArticulos.retornaSiPuedeVenderSinStock(1,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                    funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                    funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)

                                                    funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                    funcionesmysql.loguear("QML::cantidadItems: 1")


                                                    modeloItemsFactura.append({
                                                                                  codigoArticulo:valorArticuloInterno,
                                                                                  codigoBarrasArticulo:codigoDeBarraArticulo,
                                                                                  descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                                  descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                                  precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  precioArticuloSubTotal:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  cantidadItems:1,
                                                                                  costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  activo:true,
                                                                                  consideraDescuento:false,
                                                                                  indiceLinea:-1,
                                                                                  descuentoLineaItem:0,
                                                                                  codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                                  descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                                  asignarGarantiaAArticulo:false
                                                                              })
                                                    listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                                    if(modoCalculoTotal=="1"){
                                                        etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                    }else if(modoCalculoTotal=="2"){
                                                        etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                    }

                                                    mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")

                                                    txtCantidadArticulosFacturacion.textoInputBox=""
                                                    txtArticuloParaFacturacion.textoInputBox=""
                                                    txtPrecioItemManualFacturacion.textoInputBox=""
                                                    txtCodigoDeBarrasADemanda.textoInputBox=""
                                                    txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

                                                    txtArticuloParaFacturacion.tomarElFocoP()
                                                }
                                            }
                                        }

                                    }else{
                                        txtCostoArticuloMonedaReferencia.tomarElFoco()
                                    }
                                }else{
                                    //////////////////////////
                                    //////////////////////////
                                    /////////////////////////
                                    if(txtCodigoClienteFacturacion.textoInputBox!=""){ //Hay un cliente seleccionado
                                        var listaPrecioSeleccionada
                                        if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                            listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(txtFechaPrecioFacturacion.textoInputBox.trim(), txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim())
                                        }else{
                                            listaPrecioSeleccionada=cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion
                                        }


                                        if(listaPrecioSeleccionada!=""){

                                            var precioArticuloSelecionado=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,listaPrecioSeleccionada)

                                            var cotizacion=1;
                                            valorPrecioArticulo2=precioArticuloSelecionado

                                            if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                    cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    valorPrecioArticulo2=precioArticuloSelecionado/cotizacion
                                                }else{

                                                    if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                        cotizacion=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                        valorPrecioArticulo2=precioArticuloSelecionado*cotizacion
                                                    }else{
                                                        valorPrecioArticulo2=(precioArticuloSelecionado*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    }
                                                }
                                            }

                                            txtPrecioItemManualFacturacion.textoInputBox=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                                            txtPrecioItemManualFacturacion.tomarElFoco()

                                        }else{

                                            var precioArticuloSelecionadoSinLista
                                            if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                            }else{
                                                precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                            }

                                            var cotizacion2=1;
                                            valorPrecioArticulo2=precioArticuloSelecionadoSinLista

                                            if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                    cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    valorPrecioArticulo2=precioArticuloSelecionadoSinLista/cotizacion2
                                                }else{
                                                    if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                        cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                        valorPrecioArticulo2=precioArticuloSelecionadoSinLista*cotizacion2
                                                    }else{
                                                        valorPrecioArticulo2=(precioArticuloSelecionadoSinLista*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    }
                                                }
                                            }

                                            txtPrecioItemManualFacturacion.textoInputBox=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                                            txtPrecioItemManualFacturacion.tomarElFoco()
                                        }

                                    }else{
                                        var precioArticuloSelecionadoSinListaySinCliente
                                        if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                            precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                        }else{
                                            precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                        }

                                        var cotizacion3=1;
                                        valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente

                                        if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                            if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){

                                                cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente/cotizacion3

                                            }else{
                                                if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                    cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                    valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente*cotizacion3
                                                }else{
                                                    valorPrecioArticulo2=(precioArticuloSelecionadoSinListaySinCliente*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                }
                                            }
                                        }
                                        txtPrecioItemManualFacturacion.textoInputBox=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                                        txtPrecioItemManualFacturacion.tomarElFoco()
                                    }
                                    //////////////////////////
                                    //////////////////////////
                                    //////////////////////////
                                }


                            }else{
                                txtCantidadArticulosFacturacion.tomarElFoco()
                            }

                        }else{
                            txtArticuloParaFacturacion.mensajeError("Artículo "+valorArticuloInterno+" incativo.")
                            txtArticuloParaFacturacion.textoInputBox=""

                            txtArticuloParaFacturacion.tomarElFocoP()
                        }



                    }else{
                        txtArticuloParaFacturacion.tomarElFocoP()
                    }


                }
            }

            TextInputSimple {
                id: txtCantidadArticulosFacturacion
                //   width: 100
                inputMask: "00000;"
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaCantidades")
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                botonBuscarTextoVisible: false
                largoMaximo: 5
                textoDeFondo: ""
                textoTitulo: "Cantidad:"
                colorDeTitulo: "#dbd8d8"

                onEnter: {

                    funcionesmysql.loguear("QML::txtCantidadArticulosFacturacion::onEnter")

                    if(txtCodigoDeBarrasADemanda.visible){
                        if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){
                            txtCodigoDeBarrasADemanda.tomarElFoco()
                        }
                    }
                    else if(txtPrecioItemManualFacturacion.visible){
                        if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){


                            ////////////////////////////
                            /////////////////////////////
                            /////////////////////////////
                            valorArticuloInterno=modeloArticulos.existeArticulo(txtArticuloParaFacturacion.textoInputBox.trim());

                            if(valorArticuloInterno!=""){



                                if(modeloArticulos.retornaArticuloActivo(valorArticuloInterno) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")){


                                    if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){

                                        if(txtCodigoClienteFacturacion.textoInputBox!=""){ //Hay un cliente seleccionado

                                            var listaPrecioSeleccionada
                                            if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(txtFechaPrecioFacturacion.textoInputBox.trim(), txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim())
                                            }else{
                                                listaPrecioSeleccionada=cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion
                                            }
                                            if(listaPrecioSeleccionada!=""){
                                                var precioArticuloSelecionado=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,listaPrecioSeleccionada)
                                                var cotizacion=1;
                                                valorPrecioArticulo2=precioArticuloSelecionado

                                                if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                    if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                        cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                        valorPrecioArticulo2=precioArticuloSelecionado/cotizacion

                                                    }else{
                                                        if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                            cotizacion=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                            valorPrecioArticulo2=precioArticuloSelecionado*cotizacion

                                                        }else{
                                                            valorPrecioArticulo2=(precioArticuloSelecionado*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)

                                                        }
                                                    }
                                                }
                                                txtPrecioItemManualFacturacion.textoInputBox=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                                                txtPrecioItemManualFacturacion.tomarElFoco()

                                            }else{

                                                var precioArticuloSelecionadoSinLista
                                                if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                    precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                                }else{
                                                    precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                                }


                                                var cotizacion2=1;
                                                valorPrecioArticulo2=precioArticuloSelecionadoSinLista

                                                if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                    if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                        cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                        valorPrecioArticulo2=precioArticuloSelecionadoSinLista/cotizacion2
                                                    }else{
                                                        if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                            cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                            valorPrecioArticulo2=precioArticuloSelecionadoSinLista*cotizacion2
                                                        }else{
                                                            valorPrecioArticulo2=(precioArticuloSelecionadoSinLista*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                        }
                                                    }
                                                }
                                                txtPrecioItemManualFacturacion.textoInputBox=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                                                txtPrecioItemManualFacturacion.tomarElFoco()
                                            }
                                        }else{

                                            var precioArticuloSelecionadoSinListaySinCliente
                                            if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                            }else{
                                                precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                            }

                                            var cotizacion3=1;
                                            valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente

                                            if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                    cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente/cotizacion3
                                                }else{

                                                    if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                        cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                        valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente*cotizacion3
                                                    }else{
                                                        valorPrecioArticulo2=(precioArticuloSelecionadoSinListaySinCliente*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    }
                                                }
                                            }
                                            txtPrecioItemManualFacturacion.textoInputBox=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                                            txtPrecioItemManualFacturacion.tomarElFoco()
                                        }
                                    }else{
                                        txtCantidadArticulosFacturacion.tomarElFoco()
                                    }
                                }else{
                                    txtArticuloParaFacturacion.mensajeError("Artículo "+valorArticuloInterno+" incativo.")
                                    txtArticuloParaFacturacion.textoInputBox=""
                                    txtArticuloParaFacturacion.tomarElFocoP()
                                }







                            }else{
                                txtArticuloParaFacturacion.tomarElFocoP()
                            }
                            //////////////////////////////
                            //////////////////////////////
                            ///////////////////////////////

                        }
                    }else if(txtCostoArticuloMonedaReferencia.visible){
                        if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){
                            txtCostoArticuloMonedaReferencia.tomarElFoco()
                        }
                    }else{
                        valorArticuloInterno=modeloArticulos.existeArticulo(txtArticuloParaFacturacion.textoInputBox.trim());


                        if(valorArticuloInterno!="" && !superaCantidadMaximaLineasDocumento()){
                            codigoDeBarraArticulo=''

                            ///Chequeo que modo de calculo de total esta seteado
                            var modoCalculoTotal=modeloconfiguracion.retornaValorConfiguracion("MODO_CALCULOTOTAL");

                            txtArticuloParaFacturacion.textoInputBox=valorArticuloInterno





                            if(modeloArticulos.retornaArticuloActivo(valorArticuloInterno) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")){

                                if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){

                                    if(txtCodigoClienteFacturacion.textoInputBox!=""){ //Hay un cliente seleccionado

                                        funcionesmysql.loguear("QML::Hay un cliente seleccionado")


                                        var listaPrecioSeleccionada
                                        if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                            listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(txtFechaPrecioFacturacion.textoInputBox.trim(), txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim())
                                        }else{
                                            listaPrecioSeleccionada=cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion
                                        }



                                        if(listaPrecioSeleccionada!=""){

                                            funcionesmysql.loguear("QML::Con lista de precios seleccionada")

                                            cantidadItemsVendidos=txtCantidadArticulosFacturacion.textoInputBox.trim()

                                            var precioArticuloSelecionado=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,listaPrecioSeleccionada)


                                            var cotizacion=1;
                                            valorPrecioArticulo2=precioArticuloSelecionado

                                            if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                    cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    valorPrecioArticulo2=precioArticuloSelecionado/cotizacion

                                                }else{
                                                    if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                        cotizacion=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                        valorPrecioArticulo2=precioArticuloSelecionado*cotizacion

                                                    }else{
                                                        valorPrecioArticulo2=(precioArticuloSelecionado*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)

                                                    }



                                                }
                                            }


                                            costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                            //Controlo si se peude vender sin stock previsto
                                            if(modeloArticulos.retornaSiPuedeVenderSinStock(cantidadItemsVendidos,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                                funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                funcionesmysql.loguear("QML::cantidadItems: "+cantidadItemsVendidos)


                                                modeloItemsFactura.append({
                                                                              codigoArticulo:valorArticuloInterno,
                                                                              codigoBarrasArticulo:txtCodigoDeBarrasADemanda.textoInputBox.trim(),
                                                                              descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                              descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                              precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              cantidadItems:cantidadItemsVendidos,
                                                                              costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              activo:true,
                                                                              consideraDescuento:false,
                                                                              indiceLinea:-1,
                                                                              descuentoLineaItem:0,
                                                                              codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                              descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                              asignarGarantiaAArticulo:false
                                                                          })

                                                listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)


                                                valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos


                                                if(modoCalculoTotal=="1"){
                                                    etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }else if(modoCalculoTotal=="2"){
                                                    etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }

                                                mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")

                                                txtCantidadArticulosFacturacion.textoInputBox=""
                                                txtArticuloParaFacturacion.textoInputBox=""
                                                txtPrecioItemManualFacturacion.textoInputBox=""
                                                txtCodigoDeBarrasADemanda.textoInputBox=""
                                                txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                txtArticuloParaFacturacion.tomarElFocoP()

                                            }

                                        }else{

                                            funcionesmysql.loguear("QML::Sin lista de precios seleccionada")

                                            var precioArticuloSelecionadoSinLista
                                            if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                            }else{
                                                precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                            }


                                            var cotizacion2=1;
                                            valorPrecioArticulo2=precioArticuloSelecionadoSinLista

                                            if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                    cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    valorPrecioArticulo2=precioArticuloSelecionadoSinLista/cotizacion2
                                                }else{
                                                    if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                        cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                        valorPrecioArticulo2=precioArticuloSelecionadoSinLista*cotizacion2
                                                    }else{
                                                        valorPrecioArticulo2=(precioArticuloSelecionadoSinLista*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    }



                                                }
                                            }

                                            cantidadItemsVendidos=txtCantidadArticulosFacturacion.textoInputBox.trim()

                                            costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                            //Controlo si se peude vender sin stock previsto
                                            if(modeloArticulos.retornaSiPuedeVenderSinStock(cantidadItemsVendidos,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                                funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                funcionesmysql.loguear("QML::cantidadItems: "+cantidadItemsVendidos)

                                                modeloItemsFactura.append({
                                                                              codigoArticulo:valorArticuloInterno,
                                                                              codigoBarrasArticulo:txtCodigoDeBarrasADemanda.textoInputBox.trim(),
                                                                              descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                              descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                              precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              cantidadItems:cantidadItemsVendidos,
                                                                              costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              activo:true,
                                                                              consideraDescuento:false,
                                                                              indiceLinea:-1,
                                                                              descuentoLineaItem:0,
                                                                              codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                              descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                              asignarGarantiaAArticulo:false
                                                                          })

                                                listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)



                                                valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos


                                                if(modoCalculoTotal=="1"){
                                                    etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }else if(modoCalculoTotal=="2"){
                                                    etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }

                                                mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")


                                                txtCantidadArticulosFacturacion.textoInputBox=""
                                                txtArticuloParaFacturacion.textoInputBox=""
                                                txtPrecioItemManualFacturacion.textoInputBox=""
                                                txtCodigoDeBarrasADemanda.textoInputBox=""
                                                txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                txtArticuloParaFacturacion.tomarElFocoP()
                                            }
                                        }

                                    }else{

                                        funcionesmysql.loguear("QML::No hay un cliente seleccionado")

                                        var precioArticuloSelecionadoSinListaySinCliente
                                        if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                            precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                        }else{
                                            precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                        }




                                        var cotizacion3=1;
                                        valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente

                                        if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                            if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente/cotizacion3
                                            }else{

                                                if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                    cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                    valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente*cotizacion3
                                                }else{
                                                    valorPrecioArticulo2=(precioArticuloSelecionadoSinListaySinCliente*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                }




                                            }
                                        }

                                        cantidadItemsVendidos=txtCantidadArticulosFacturacion.textoInputBox.trim()

                                        costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                        //Controlo si se peude vender sin stock previsto
                                        if(modeloArticulos.retornaSiPuedeVenderSinStock(cantidadItemsVendidos,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                            funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                            funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                            funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                            funcionesmysql.loguear("QML::cantidadItems: "+cantidadItemsVendidos)

                                            modeloItemsFactura.append({
                                                                          codigoArticulo:valorArticuloInterno,
                                                                          codigoBarrasArticulo:txtCodigoDeBarrasADemanda.textoInputBox.trim(),
                                                                          descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                          descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                          precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          cantidadItems:cantidadItemsVendidos,
                                                                          costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          activo:true,
                                                                          consideraDescuento:false,
                                                                          indiceLinea:-1,
                                                                          descuentoLineaItem:0,
                                                                          codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                          descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                          asignarGarantiaAArticulo:false
                                                                      })

                                            listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)


                                            valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos

                                            if(modoCalculoTotal=="1"){
                                                etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                            }else if(modoCalculoTotal=="2"){
                                                etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                            }

                                            mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")


                                            txtCantidadArticulosFacturacion.textoInputBox=""
                                            txtArticuloParaFacturacion.textoInputBox=""
                                            txtPrecioItemManualFacturacion.textoInputBox=""
                                            txtCodigoDeBarrasADemanda.textoInputBox=""
                                            txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

                                            txtArticuloParaFacturacion.tomarElFocoP()
                                        }
                                    }


                                }else{
                                    txtCantidadArticulosFacturacion.tomarElFoco()
                                }

                            }else{

                                txtArticuloParaFacturacion.mensajeError("Artículo "+valorArticuloInterno+" incativo.")
                                txtArticuloParaFacturacion.textoInputBox=""

                                txtArticuloParaFacturacion.tomarElFocoP()
                            }



                        }else{
                            txtArticuloParaFacturacion.tomarElFocoP()
                        }
                    }




                }

            }


            BotonCargarDato {
                id: btnBuscarMasArticulos
                textoColor: "#dbd8d8"
                anchors.top: parent.top
                anchors.topMargin: 7
                texto: "mas artículos..."
                imagen: "qrc:/imagenes/qml/ProyectoQML/Imagenes/SumaBlanca.png"
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")
                onClic: {

                    rectOpcionesExtrasArticulosFacturacionDesaparecer.stop()
                    rectOpcionesExtrasArticulosFacturacionAparecer.start()
                    cbListatipoDocumentos.cerrarComboBox()
                    rowBarraDeHerramientas.enabled=false

                    btnBuscarMasArticulos.volverAEstadoOriginalElControl()

                    btnBuscarMasArticulos.enabled=false
                    btnBuscarMasClientes.enabled=false

                    txtCodigoArticuloOpcionesExtrasFacturacion.tomarElFoco()
                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=false

                    modeloListasPreciosComboBox.clearListasPrecio()
                    modeloListasPreciosComboBox.buscarListasPrecio("1=","1")

                }

            }

            BotonCargarDato {
                id: btnAgregarMediosDePago
                anchors.top: parent.top
                anchors.topMargin: 7
                texto: "medios de pago"
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")
                imagen: "qrc:/imagenes/qml/ProyectoQML/Imagenes/SumaBlanca.png"
                textoColor: "#dbd8d8"
                onClic: {

                    contenedorFlipable.flipped = !contenedorFlipable.flipped
                    if(!contenedorFlipable.flipped){
                        btnAgregarMediosDePago.texto="medios de pago"
                    }else{
                        btnAgregarMediosDePago.texto="items facturación"
                    }

                }


            }

            CheckBox {
                id: chbImprimirEnvios
                textoValor: "Imprimir envios"
                chekActivo: true
                colorTexto: "#dbd8d8"
                visible: {


                        if(modeloconfiguracion.retornaValorConfiguracion("IMPRESION_ENVIOS")==="1"){
                            if(txtCodigoClienteFacturacion.visible && txtArticuloParaFacturacion.visible){
                                true
                            }else{
                                false
                            }
                        }else{
                            false
                        }
                   

                }

            }




        }

        Flow {
            id: flowPieFacturacion2
            x: 8
            y: -2
            height: flowPieFacturacion2.implicitHeight
            spacing: 5
            anchors.top: flowPieFacturacion.bottom
            anchors.topMargin: 8



            TextInputSimple {
                id: txtCodigoDeBarrasADemanda
                largoMaximo: {

                    if(modeloconfiguracion.retornaValorConfiguracion("CODIGO_BARRAS_A_DEMANDA_EXTENDIDO")=="1"){
                        600
                    }else{
                        30
                    }
                }

                fijoTamanioPersonalizado:{
                    if(modeloconfiguracion.retornaValorConfiguracion("CODIGO_BARRAS_A_DEMANDA_EXTENDIDO")=="1"){
                        300
                    }else{
                        0
                    }
                }

                botonBorrarTextoVisible: true
                textoTitulo: {
                    if(visible){
                        modeloListaTipoDocumentosComboBox.retornaDescripcionCodigoADemanda(cbListatipoDocumentos.codigoValorSeleccion)
                    }else{
                        ""
                    }
                }


                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaCodigoBarrasADemanda")

                onTabulacion: {

                    if(modeloconfiguracion.retornaValorConfiguracion("CODIGO_BARRAS_A_DEMANDA_EXTENDIDO")=="1"){

                        funcionesmysql.loguear("QML::txtCodigoDeBarrasADemanda::onEnter")


                        if(txtPrecioItemManualFacturacion.visible){
                            if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){

                                //////////////////////////////
                                /////////////////////////////
                                /////////////////////////////
                                valorArticuloInterno=modeloArticulos.existeArticulo(txtArticuloParaFacturacion.textoInputBox.trim());

                                if(valorArticuloInterno!=""){



                                    if(modeloArticulos.retornaArticuloActivo(valorArticuloInterno) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")){

                                        if(txtCodigoClienteFacturacion.textoInputBox!=""){ //Hay un cliente seleccionado

                                            var listaPrecioSeleccionada
                                            if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(txtFechaPrecioFacturacion.textoInputBox.trim(), txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim())
                                            }else{
                                                listaPrecioSeleccionada=cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion
                                            }
                                            if(listaPrecioSeleccionada!=""){

                                                var precioArticuloSelecionado=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,listaPrecioSeleccionada)

                                                var cotizacion=1;
                                                valorPrecioArticulo2=precioArticuloSelecionado

                                                if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                    if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                        cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                        valorPrecioArticulo2=precioArticuloSelecionado/cotizacion
                                                    }else{

                                                        if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                            cotizacion=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                            valorPrecioArticulo2=precioArticuloSelecionado*cotizacion
                                                        }else{
                                                            valorPrecioArticulo2=(precioArticuloSelecionado*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                        }
                                                    }
                                                }

                                                txtPrecioItemManualFacturacion.textoInputBox=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                                                txtPrecioItemManualFacturacion.tomarElFoco()

                                            }else{

                                                var precioArticuloSelecionadoSinLista
                                                if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                    precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                                }else{
                                                    precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                                }


                                                var cotizacion2=1;
                                                valorPrecioArticulo2=precioArticuloSelecionadoSinLista

                                                if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                    if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                        cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                        valorPrecioArticulo2=precioArticuloSelecionadoSinLista/cotizacion2
                                                    }else{
                                                        if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                            cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                            valorPrecioArticulo2=precioArticuloSelecionadoSinLista*cotizacion2
                                                        }else{
                                                            valorPrecioArticulo2=(precioArticuloSelecionadoSinLista*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                        }
                                                    }
                                                }

                                                txtPrecioItemManualFacturacion.textoInputBox=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                                                txtPrecioItemManualFacturacion.tomarElFoco()
                                            }

                                        }else{

                                            var precioArticuloSelecionadoSinListaySinCliente
                                            if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                            }else{
                                                precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                            }

                                            var cotizacion3=1;
                                            valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente

                                            if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){
                                                if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                    cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente/cotizacion3
                                                }else{
                                                    if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                        cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                        valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente*cotizacion3
                                                    }else{
                                                        valorPrecioArticulo2=(precioArticuloSelecionadoSinListaySinCliente*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    }

                                                }
                                            }

                                            txtPrecioItemManualFacturacion.textoInputBox=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                                            txtPrecioItemManualFacturacion.tomarElFoco()
                                        }

                                    }else{
                                        txtArticuloParaFacturacion.mensajeError("Artículo "+valorArticuloInterno+" incativo.")
                                        txtArticuloParaFacturacion.textoInputBox=""
                                        txtArticuloParaFacturacion.tomarElFocoP()
                                    }

                                }else{
                                    txtArticuloParaFacturacion.tomarElFocoP()

                                }

                                ////////////////////////////
                                /////////////////////////////
                                /////////////////////////////
                            }
                        }else if(txtCostoArticuloMonedaReferencia.visible){
                            if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){
                                txtCostoArticuloMonedaReferencia.tomarElFoco()
                            }
                        }else{


                            valorArticuloInterno=modeloArticulos.existeArticulo(txtArticuloParaFacturacion.textoInputBox.trim());

                            if(valorArticuloInterno!="" && !superaCantidadMaximaLineasDocumento()){

                                ///Chequeo que modo de calculo de total esta seteado
                                var modoCalculoTotal=modeloconfiguracion.retornaValorConfiguracion("MODO_CALCULOTOTAL");

                                txtArticuloParaFacturacion.textoInputBox=valorArticuloInterno

                                if(modeloArticulos.retornaArticuloActivo(valorArticuloInterno) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")){


                                    if(txtCodigoClienteFacturacion.textoInputBox!=""){ //Hay un cliente seleccionado

                                        var listaPrecioSeleccionada
                                        if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                            listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(txtFechaPrecioFacturacion.textoInputBox.trim(), txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim())
                                        }else{
                                            listaPrecioSeleccionada=cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion
                                        }

                                        var cantidadArticulos=1;


                                        if(listaPrecioSeleccionada!=""){


                                            var precioArticuloSelecionado=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,listaPrecioSeleccionada)

                                            var cotizacion=1;
                                            valorPrecioArticulo2=precioArticuloSelecionado

                                            if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                    cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    valorPrecioArticulo2=precioArticuloSelecionado/cotizacion
                                                }else{

                                                    if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                        cotizacion=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                        valorPrecioArticulo2=precioArticuloSelecionado*cotizacion
                                                    }else{
                                                        valorPrecioArticulo2=(precioArticuloSelecionado*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    }


                                                }
                                            }

                                            if(txtCantidadArticulosFacturacion.visible){
                                                if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){
                                                    cantidadArticulos=txtCantidadArticulosFacturacion.textoInputBox.trim()
                                                }
                                            }else{
                                                cantidadArticulos=1;
                                            }

                                            codigoDeBarraArticulo=txtCodigoDeBarrasADemanda.textoInputBox.trim()

                                            costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();
                                            //costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                            //txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

                                            //Controlo si se peude vender sin stock previsto
                                            if(modeloArticulos.retornaSiPuedeVenderSinStock(parseInt(cantidadArticulos),cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){


                                                funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                                funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                funcionesmysql.loguear("QML::cantidadItems: "+parseInt(cantidadArticulos))

                                                modeloItemsFactura.append({
                                                                              codigoArticulo:valorArticuloInterno,
                                                                              codigoBarrasArticulo:codigoDeBarraArticulo,
                                                                              descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                              descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                              precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              cantidadItems:parseInt(cantidadArticulos),
                                                                              costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              activo:true,
                                                                              consideraDescuento:false,
                                                                              indiceLinea:-1,
                                                                              descuentoLineaItem:0,
                                                                              codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                              descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                              asignarGarantiaAArticulo:false
                                                                          })

                                                listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)


                                                if(modoCalculoTotal=="1"){
                                                    etiquetaTotal.setearTotal((valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }else if(modoCalculoTotal=="2"){
                                                    etiquetaTotal.setearTotalModoArticuloSinIva((valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }

                                                mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")


                                                txtCantidadArticulosFacturacion.textoInputBox=""
                                                txtArticuloParaFacturacion.textoInputBox=""
                                                txtPrecioItemManualFacturacion.textoInputBox=""
                                                txtCodigoDeBarrasADemanda.textoInputBox=""
                                                txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                txtArticuloParaFacturacion.tomarElFocoP()
                                            }
                                        }else{

                                            var precioArticuloSelecionadoSinLista
                                            if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                            }else{
                                                precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                            }



                                            var cotizacion2=1;
                                            valorPrecioArticulo2=precioArticuloSelecionadoSinLista

                                            if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                    cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    valorPrecioArticulo2=precioArticuloSelecionadoSinLista/cotizacion2
                                                }else{
                                                    if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                        cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                        valorPrecioArticulo2=precioArticuloSelecionadoSinLista*cotizacion2
                                                    }else{
                                                        valorPrecioArticulo2=(precioArticuloSelecionadoSinLista*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    }
                                                }
                                            }

                                            if(txtCantidadArticulosFacturacion.visible){
                                                if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){
                                                    cantidadArticulos=txtCantidadArticulosFacturacion.textoInputBox.trim()
                                                }
                                            }else{
                                                cantidadArticulos=1;
                                            }

                                            codigoDeBarraArticulo=txtCodigoDeBarrasADemanda.textoInputBox.trim()

                                            costoArticulo=parseFloat(txtCostoArticuloMonedaReferencia.textoInputBox.trim());
                                            //costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                            //txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

                                            //Controlo si se peude vender sin stock previsto
                                            if(modeloArticulos.retornaSiPuedeVenderSinStock(parseInt(cantidadArticulos),cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                                funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                funcionesmysql.loguear("QML::cantidadItems: "+parseInt(cantidadArticulos))

                                                modeloItemsFactura.append({
                                                                              codigoArticulo:valorArticuloInterno,
                                                                              codigoBarrasArticulo:codigoDeBarraArticulo,
                                                                              descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                              descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                              precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              cantidadItems:parseInt(cantidadArticulos),
                                                                              costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              activo:true,
                                                                              consideraDescuento:false,
                                                                              indiceLinea:-1,
                                                                              descuentoLineaItem:0,
                                                                              codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                              descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                              asignarGarantiaAArticulo:false
                                                                          })

                                                listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                                if(modoCalculoTotal=="1"){
                                                    etiquetaTotal.setearTotal((valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }else if(modoCalculoTotal=="2"){
                                                    etiquetaTotal.setearTotalModoArticuloSinIva((valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }


                                                mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")

                                                txtCantidadArticulosFacturacion.textoInputBox=""
                                                txtArticuloParaFacturacion.textoInputBox=""
                                                txtPrecioItemManualFacturacion.textoInputBox=""
                                                txtCodigoDeBarrasADemanda.textoInputBox=""
                                                txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                txtArticuloParaFacturacion.tomarElFocoP()
                                            }
                                        }

                                    }else{

                                        var precioArticuloSelecionadoSinListaySinCliente
                                        if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                            precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                        }else{
                                            precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                        }



                                        var cotizacion3=1;
                                        valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente

                                        if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){
                                            if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente/cotizacion3
                                            }else{
                                                if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                    cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                    valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente*cotizacion3
                                                }else{
                                                    valorPrecioArticulo2=(precioArticuloSelecionadoSinListaySinCliente*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                }

                                            }
                                        }


                                        if(txtCantidadArticulosFacturacion.visible){
                                            if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){
                                                cantidadArticulos=txtCantidadArticulosFacturacion.textoInputBox.trim()
                                            }
                                        }else{
                                            cantidadArticulos=1;
                                        }



                                        codigoDeBarraArticulo=txtCodigoDeBarrasADemanda.textoInputBox.trim()

                                        costoArticulo=parseFloat(txtCostoArticuloMonedaReferencia.textoInputBox.trim());

                                        //Controlo si se peude vender sin stock previsto
                                        if(modeloArticulos.retornaSiPuedeVenderSinStock(parseInt(cantidadArticulos),cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                            funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                            funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                            funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                            funcionesmysql.loguear("QML::cantidadItems: "+parseInt(cantidadArticulos))


                                            modeloItemsFactura.append({
                                                                          codigoArticulo:valorArticuloInterno,
                                                                          codigoBarrasArticulo:codigoDeBarraArticulo,
                                                                          descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                          descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                          precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          cantidadItems:parseInt(cantidadArticulos),
                                                                          costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          activo:true,
                                                                          consideraDescuento:false,
                                                                          indiceLinea:-1,
                                                                          descuentoLineaItem:0,
                                                                          codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                          descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                          asignarGarantiaAArticulo:false
                                                                      })

                                            listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                            if(modoCalculoTotal=="1"){
                                                etiquetaTotal.setearTotal((valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                            }else if(modoCalculoTotal=="2"){
                                                etiquetaTotal.setearTotalModoArticuloSinIva((valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                            }

                                            mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")

                                            txtCantidadArticulosFacturacion.textoInputBox=""
                                            txtArticuloParaFacturacion.textoInputBox=""
                                            txtPrecioItemManualFacturacion.textoInputBox=""
                                            txtCodigoDeBarrasADemanda.textoInputBox=""
                                            txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                            txtArticuloParaFacturacion.tomarElFocoP()
                                        }

                                    }

                                }else{
                                    txtArticuloParaFacturacion.mensajeError("Artículo "+valorArticuloInterno+" incativo.")
                                    txtArticuloParaFacturacion.textoInputBox=""

                                    txtArticuloParaFacturacion.tomarElFocoP()
                                }

                            }else{
                                txtArticuloParaFacturacion.tomarElFocoP()

                            }
                        }


                    }

                }

                onEnter: {

                    if(modeloconfiguracion.retornaValorConfiguracion("CODIGO_BARRAS_A_DEMANDA_EXTENDIDO")=="0"){

                        funcionesmysql.loguear("QML::txtCodigoDeBarrasADemanda::onEnter")


                        if(txtPrecioItemManualFacturacion.visible){
                            if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){

                                //////////////////////////////
                                /////////////////////////////
                                /////////////////////////////
                                valorArticuloInterno=modeloArticulos.existeArticulo(txtArticuloParaFacturacion.textoInputBox.trim());

                                if(valorArticuloInterno!=""){



                                    if(modeloArticulos.retornaArticuloActivo(valorArticuloInterno) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")){

                                        if(txtCodigoClienteFacturacion.textoInputBox!=""){ //Hay un cliente seleccionado

                                            var listaPrecioSeleccionada
                                            if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(txtFechaPrecioFacturacion.textoInputBox.trim(), txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim())
                                            }else{
                                                listaPrecioSeleccionada=cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion
                                            }
                                            if(listaPrecioSeleccionada!=""){

                                                var precioArticuloSelecionado=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,listaPrecioSeleccionada)

                                                var cotizacion=1;
                                                valorPrecioArticulo2=precioArticuloSelecionado

                                                if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                    if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                        cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                        valorPrecioArticulo2=precioArticuloSelecionado/cotizacion
                                                    }else{

                                                        if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                            cotizacion=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                            valorPrecioArticulo2=precioArticuloSelecionado*cotizacion
                                                        }else{
                                                            valorPrecioArticulo2=(precioArticuloSelecionado*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                        }
                                                    }
                                                }

                                                txtPrecioItemManualFacturacion.textoInputBox=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                                                txtPrecioItemManualFacturacion.tomarElFoco()

                                            }else{

                                                var precioArticuloSelecionadoSinLista
                                                if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                    precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                                }else{
                                                    precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                                }


                                                var cotizacion2=1;
                                                valorPrecioArticulo2=precioArticuloSelecionadoSinLista

                                                if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                    if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                        cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                        valorPrecioArticulo2=precioArticuloSelecionadoSinLista/cotizacion2
                                                    }else{
                                                        if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                            cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                            valorPrecioArticulo2=precioArticuloSelecionadoSinLista*cotizacion2
                                                        }else{
                                                            valorPrecioArticulo2=(precioArticuloSelecionadoSinLista*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                        }
                                                    }
                                                }

                                                txtPrecioItemManualFacturacion.textoInputBox=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                                                txtPrecioItemManualFacturacion.tomarElFoco()
                                            }

                                        }else{

                                            var precioArticuloSelecionadoSinListaySinCliente
                                            if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                            }else{
                                                precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                            }

                                            var cotizacion3=1;
                                            valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente

                                            if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){
                                                if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                    cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente/cotizacion3
                                                }else{
                                                    if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                        cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                        valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente*cotizacion3
                                                    }else{
                                                        valorPrecioArticulo2=(precioArticuloSelecionadoSinListaySinCliente*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    }

                                                }
                                            }

                                            txtPrecioItemManualFacturacion.textoInputBox=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                                            txtPrecioItemManualFacturacion.tomarElFoco()
                                        }

                                    }else{
                                        txtArticuloParaFacturacion.mensajeError("Artículo "+valorArticuloInterno+" incativo.")
                                        txtArticuloParaFacturacion.textoInputBox=""
                                        txtArticuloParaFacturacion.tomarElFocoP()
                                    }

                                }else{
                                    txtArticuloParaFacturacion.tomarElFocoP()

                                }

                                ////////////////////////////
                                /////////////////////////////
                                /////////////////////////////
                            }
                        }else if(txtCostoArticuloMonedaReferencia.visible){
                            if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){
                                txtCostoArticuloMonedaReferencia.tomarElFoco()
                            }
                        }else{


                            valorArticuloInterno=modeloArticulos.existeArticulo(txtArticuloParaFacturacion.textoInputBox.trim());

                            if(valorArticuloInterno!="" && !superaCantidadMaximaLineasDocumento()){

                                ///Chequeo que modo de calculo de total esta seteado
                                var modoCalculoTotal=modeloconfiguracion.retornaValorConfiguracion("MODO_CALCULOTOTAL");

                                txtArticuloParaFacturacion.textoInputBox=valorArticuloInterno

                                if(modeloArticulos.retornaArticuloActivo(valorArticuloInterno) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")){


                                    if(txtCodigoClienteFacturacion.textoInputBox!=""){ //Hay un cliente seleccionado

                                        var listaPrecioSeleccionada
                                        if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                            listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(txtFechaPrecioFacturacion.textoInputBox.trim(), txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim())
                                        }else{
                                            listaPrecioSeleccionada=cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion
                                        }

                                        var cantidadArticulos=1;


                                        if(listaPrecioSeleccionada!=""){


                                            var precioArticuloSelecionado=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,listaPrecioSeleccionada)

                                            var cotizacion=1;
                                            valorPrecioArticulo2=precioArticuloSelecionado

                                            if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                    cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    valorPrecioArticulo2=precioArticuloSelecionado/cotizacion
                                                }else{

                                                    if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                        cotizacion=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                        valorPrecioArticulo2=precioArticuloSelecionado*cotizacion
                                                    }else{
                                                        valorPrecioArticulo2=(precioArticuloSelecionado*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    }


                                                }
                                            }

                                            if(txtCantidadArticulosFacturacion.visible){
                                                if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){
                                                    cantidadArticulos=txtCantidadArticulosFacturacion.textoInputBox.trim()
                                                }
                                            }else{
                                                cantidadArticulos=1;
                                            }

                                            codigoDeBarraArticulo=txtCodigoDeBarrasADemanda.textoInputBox.trim()

                                            costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();
                                            //costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                            //txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

                                            //Controlo si se peude vender sin stock previsto
                                            if(modeloArticulos.retornaSiPuedeVenderSinStock(parseInt(cantidadArticulos),cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){


                                                funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                                funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                funcionesmysql.loguear("QML::cantidadItems: "+parseInt(cantidadArticulos))

                                                modeloItemsFactura.append({
                                                                              codigoArticulo:valorArticuloInterno,
                                                                              codigoBarrasArticulo:codigoDeBarraArticulo,
                                                                              descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                              descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                              precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              cantidadItems:parseInt(cantidadArticulos),
                                                                              costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              activo:true,
                                                                              consideraDescuento:false,
                                                                              indiceLinea:-1,
                                                                              descuentoLineaItem:0,
                                                                              codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                              descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                              asignarGarantiaAArticulo:false
                                                                          })

                                                listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)


                                                if(modoCalculoTotal=="1"){
                                                    etiquetaTotal.setearTotal((valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }else if(modoCalculoTotal=="2"){
                                                    etiquetaTotal.setearTotalModoArticuloSinIva((valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }

                                                mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")


                                                txtCantidadArticulosFacturacion.textoInputBox=""
                                                txtArticuloParaFacturacion.textoInputBox=""
                                                txtPrecioItemManualFacturacion.textoInputBox=""
                                                txtCodigoDeBarrasADemanda.textoInputBox=""
                                                txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                txtArticuloParaFacturacion.tomarElFocoP()
                                            }
                                        }else{

                                            var precioArticuloSelecionadoSinLista
                                            if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                                precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                            }else{
                                                precioArticuloSelecionadoSinLista=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                            }



                                            var cotizacion2=1;
                                            valorPrecioArticulo2=precioArticuloSelecionadoSinLista

                                            if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                                if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                    cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    valorPrecioArticulo2=precioArticuloSelecionadoSinLista/cotizacion2
                                                }else{
                                                    if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                        cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                        valorPrecioArticulo2=precioArticuloSelecionadoSinLista*cotizacion2
                                                    }else{
                                                        valorPrecioArticulo2=(precioArticuloSelecionadoSinLista*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                    }
                                                }
                                            }

                                            if(txtCantidadArticulosFacturacion.visible){
                                                if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){
                                                    cantidadArticulos=txtCantidadArticulosFacturacion.textoInputBox.trim()
                                                }
                                            }else{
                                                cantidadArticulos=1;
                                            }

                                            codigoDeBarraArticulo=txtCodigoDeBarrasADemanda.textoInputBox.trim()

                                            costoArticulo=parseFloat(txtCostoArticuloMonedaReferencia.textoInputBox.trim());
                                            //costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                            //txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

                                            //Controlo si se peude vender sin stock previsto
                                            if(modeloArticulos.retornaSiPuedeVenderSinStock(parseInt(cantidadArticulos),cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                                funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                funcionesmysql.loguear("QML::cantidadItems: "+parseInt(cantidadArticulos))

                                                modeloItemsFactura.append({
                                                                              codigoArticulo:valorArticuloInterno,
                                                                              codigoBarrasArticulo:codigoDeBarraArticulo,
                                                                              descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                              descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                              precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              cantidadItems:parseInt(cantidadArticulos),
                                                                              costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              activo:true,
                                                                              consideraDescuento:false,
                                                                              indiceLinea:-1,
                                                                              descuentoLineaItem:0,
                                                                              codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                              descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                              asignarGarantiaAArticulo:false
                                                                          })

                                                listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                                if(modoCalculoTotal=="1"){
                                                    etiquetaTotal.setearTotal((valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }else if(modoCalculoTotal=="2"){
                                                    etiquetaTotal.setearTotalModoArticuloSinIva((valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }


                                                mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")

                                                txtCantidadArticulosFacturacion.textoInputBox=""
                                                txtArticuloParaFacturacion.textoInputBox=""
                                                txtPrecioItemManualFacturacion.textoInputBox=""
                                                txtCodigoDeBarrasADemanda.textoInputBox=""
                                                txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                txtArticuloParaFacturacion.tomarElFocoP()
                                            }
                                        }

                                    }else{

                                        var precioArticuloSelecionadoSinListaySinCliente
                                        if(cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="" || cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion=="-1"){
                                            precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,1)
                                        }else{
                                            precioArticuloSelecionadoSinListaySinCliente=modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(valorArticuloInterno,cbxListaPrecioManualFijadaPorUsuario.codigoValorSeleccion)
                                        }



                                        var cotizacion3=1;
                                        valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente

                                        if(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)!=cbListaMonedasEnFacturacion.codigoValorSeleccion){
                                            if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)){
                                                cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente/cotizacion3
                                            }else{
                                                if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                    cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno))
                                                    valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente*cotizacion3
                                                }else{
                                                    valorPrecioArticulo2=(precioArticuloSelecionadoSinListaySinCliente*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(valorArticuloInterno)))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                }

                                            }
                                        }


                                        if(txtCantidadArticulosFacturacion.visible){
                                            if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){
                                                cantidadArticulos=txtCantidadArticulosFacturacion.textoInputBox.trim()
                                            }
                                        }else{
                                            cantidadArticulos=1;
                                        }



                                        codigoDeBarraArticulo=txtCodigoDeBarrasADemanda.textoInputBox.trim()

                                        costoArticulo=parseFloat(txtCostoArticuloMonedaReferencia.textoInputBox.trim());

                                        //Controlo si se peude vender sin stock previsto
                                        if(modeloArticulos.retornaSiPuedeVenderSinStock(parseInt(cantidadArticulos),cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                            funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                            funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                            funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                            funcionesmysql.loguear("QML::cantidadItems: "+parseInt(cantidadArticulos))


                                            modeloItemsFactura.append({
                                                                          codigoArticulo:valorArticuloInterno,
                                                                          codigoBarrasArticulo:codigoDeBarraArticulo,
                                                                          descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                          descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                          precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          cantidadItems:parseInt(cantidadArticulos),
                                                                          costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          activo:true,
                                                                          consideraDescuento:false,
                                                                          indiceLinea:-1,
                                                                          descuentoLineaItem:0,
                                                                          codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                          descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                          asignarGarantiaAArticulo:false
                                                                      })

                                            listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                            if(modoCalculoTotal=="1"){
                                                etiquetaTotal.setearTotal((valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                            }else if(modoCalculoTotal=="2"){
                                                etiquetaTotal.setearTotalModoArticuloSinIva((valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*parseInt(cantidadArticulos)).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                            }

                                            mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")

                                            txtCantidadArticulosFacturacion.textoInputBox=""
                                            txtArticuloParaFacturacion.textoInputBox=""
                                            txtPrecioItemManualFacturacion.textoInputBox=""
                                            txtCodigoDeBarrasADemanda.textoInputBox=""
                                            txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                            txtArticuloParaFacturacion.tomarElFocoP()
                                        }

                                    }

                                }else{
                                    txtArticuloParaFacturacion.mensajeError("Artículo "+valorArticuloInterno+" incativo.")
                                    txtArticuloParaFacturacion.textoInputBox=""

                                    txtArticuloParaFacturacion.tomarElFocoP()
                                }

                            }else{
                                txtArticuloParaFacturacion.tomarElFocoP()

                            }
                        }


                    }


                }
            }

            TextInputSimple {
                id: txtPrecioItemManualFacturacion
                y: -1
                //  width: 170
                height: 35
                enFocoSeleccionarTodo: true
                textoInputBox: ""+modeloconfiguracion.retornaCantidadDecimalesString()+""
                botonBuscarTextoVisible: false
                inputMask: "00000000"+modeloconfiguracion.retornaCantidadDecimalesString()+";"
                botonBorrarTextoVisible: true
                largoMaximo: 45
                textoTitulo: "Precio unitario "+modeloListaMonedas.retornaSimboloMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)+":"
                enable: true
                //    anchors.leftMargin: 5
                //     anchors.left: txtCodigoArticuloParaAgregarFacturacion.right
                colorDeTitulo: "#dbd8d8"
                visible:modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaPrecioManual")
                onEnter: {

                    funcionesmysql.loguear("QML::txtPrecioItemManualFacturacion::onEnter")


                    if(txtCostoArticuloMonedaReferencia.visible){
                        if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){
                            txtCostoArticuloMonedaReferencia.tomarElFoco()
                        }
                    }else{

                        if(txtPrecioItemManualFacturacion.textoInputBox.trim()!="" && txtPrecioItemManualFacturacion.textoInputBox.trim()!="0" && txtPrecioItemManualFacturacion.textoInputBox.trim()!="."){

                            valorArticuloInterno=modeloArticulos.existeArticulo(txtArticuloParaFacturacion.textoInputBox.trim());

                            if(valorArticuloInterno!="" && !superaCantidadMaximaLineasDocumento()){
                                codigoDeBarraArticulo=''

                                ///Chequeo que modo de calculo de total esta seteado
                                var modoCalculoTotal=modeloconfiguracion.retornaValorConfiguracion("MODO_CALCULOTOTAL");

                                txtArticuloParaFacturacion.textoInputBox=valorArticuloInterno

                                if(modeloArticulos.retornaArticuloActivo(valorArticuloInterno) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")){

                                    if(txtCantidadArticulosFacturacion.visible){

                                        if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){

                                            if(txtCodigoClienteFacturacion.textoInputBox!=""){ //Hay un cliente seleccionado
                                                var listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(txtFechaPrecioFacturacion.textoInputBox.trim(), txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim())

                                                if(listaPrecioSeleccionada!=""){

                                                    var precioArticuloSelecionado=txtPrecioItemManualFacturacion.textoInputBox.trim()

                                                    var cotizacion=1;
                                                    valorPrecioArticulo2=precioArticuloSelecionado

                                                    cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)

                                                    cantidadItemsVendidos=txtCantidadArticulosFacturacion.textoInputBox.trim()
                                                    costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();
                                                    //costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                    //txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

                                                    //Controlo si se peude vender sin stock previsto
                                                    if(modeloArticulos.retornaSiPuedeVenderSinStock(cantidadItemsVendidos,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                        funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                        funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                                        funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                        funcionesmysql.loguear("QML::cantidadItems: "+cantidadItemsVendidos)

                                                        modeloItemsFactura.append({
                                                                                      codigoArticulo:valorArticuloInterno,
                                                                                      codigoBarrasArticulo:"",
                                                                                      descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                                      descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                                      precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                      precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                      cantidadItems:cantidadItemsVendidos,
                                                                                      costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                      activo:true,
                                                                                      consideraDescuento:false,
                                                                                      indiceLinea:-1,
                                                                                      descuentoLineaItem:0,
                                                                                      codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                                      descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                                      asignarGarantiaAArticulo:false
                                                                                  })

                                                        listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                                        valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos


                                                        if(modoCalculoTotal=="1"){
                                                            etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                        }else if(modoCalculoTotal=="2"){
                                                            etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                        }

                                                        mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")

                                                        txtCantidadArticulosFacturacion.textoInputBox=""
                                                        txtArticuloParaFacturacion.textoInputBox=""
                                                        txtPrecioItemManualFacturacion.textoInputBox=""
                                                        txtCodigoDeBarrasADemanda.textoInputBox=""
                                                        txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""


                                                        txtArticuloParaFacturacion.tomarElFocoP()
                                                    }

                                                }else{

                                                    var precioArticuloSelecionadoSinLista=txtPrecioItemManualFacturacion.textoInputBox.trim()

                                                    var cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion);
                                                    valorPrecioArticulo2=precioArticuloSelecionadoSinLista

                                                    cantidadItemsVendidos=txtCantidadArticulosFacturacion.textoInputBox.trim()
                                                    costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                                    //Controlo si se peude vender sin stock previsto
                                                    if(modeloArticulos.retornaSiPuedeVenderSinStock(cantidadItemsVendidos,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                        funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                        funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                                        funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                        funcionesmysql.loguear("QML::cantidadItems: "+cantidadItemsVendidos)

                                                        modeloItemsFactura.append({
                                                                                      codigoArticulo:valorArticuloInterno,
                                                                                      codigoBarrasArticulo:"",
                                                                                      descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                                      descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                                      precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                      precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                      cantidadItems:cantidadItemsVendidos,
                                                                                      costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                      activo:true,
                                                                                      consideraDescuento:false,
                                                                                      indiceLinea:-1,
                                                                                      descuentoLineaItem:0,
                                                                                      codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                                      descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                                      asignarGarantiaAArticulo:false
                                                                                  })


                                                        listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                                        valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos




                                                        if(modoCalculoTotal=="1"){
                                                            etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                        }else if(modoCalculoTotal=="2"){
                                                            etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                        }

                                                        mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")


                                                        txtCantidadArticulosFacturacion.textoInputBox=""
                                                        txtArticuloParaFacturacion.textoInputBox=""
                                                        txtPrecioItemManualFacturacion.textoInputBox=""
                                                        txtCodigoDeBarrasADemanda.textoInputBox=""
                                                        txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                        txtArticuloParaFacturacion.tomarElFocoP()
                                                    }
                                                }

                                            }else{

                                                var precioArticuloSelecionadoSinListaySinCliente=txtPrecioItemManualFacturacion.textoInputBox.trim()


                                                var cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion);
                                                valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente


                                                cantidadItemsVendidos=txtCantidadArticulosFacturacion.textoInputBox.trim()
                                                costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                                //Controlo si se peude vender sin stock previsto
                                                if(modeloArticulos.retornaSiPuedeVenderSinStock(cantidadItemsVendidos,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                    funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                    funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                                    funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                    funcionesmysql.loguear("QML::cantidadItems: "+cantidadItemsVendidos)

                                                    modeloItemsFactura.append({
                                                                                  codigoArticulo:valorArticuloInterno,
                                                                                  codigoBarrasArticulo:"",
                                                                                  descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                                  descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                                  precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  cantidadItems:cantidadItemsVendidos,
                                                                                  costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  activo:true,
                                                                                  consideraDescuento:false,
                                                                                  indiceLinea:-1,
                                                                                  descuentoLineaItem:0,
                                                                                  codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                                  descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                                  asignarGarantiaAArticulo:false
                                                                              })


                                                    listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                                    valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos

                                                    if(modoCalculoTotal=="1"){
                                                        etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                    }else if(modoCalculoTotal=="2"){
                                                        etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                    }

                                                    mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")


                                                    txtCantidadArticulosFacturacion.textoInputBox=""
                                                    txtArticuloParaFacturacion.textoInputBox=""
                                                    txtPrecioItemManualFacturacion.textoInputBox=""
                                                    txtCodigoDeBarrasADemanda.textoInputBox=""
                                                    txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                    txtArticuloParaFacturacion.tomarElFocoP()
                                                }
                                            }


                                        }else{
                                            txtCantidadArticulosFacturacion.tomarElFoco()
                                        }

                                        ///
                                    }else{
                                        if(txtCodigoClienteFacturacion.textoInputBox!=""){ //Hay un cliente seleccionado
                                            var listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(txtFechaPrecioFacturacion.textoInputBox.trim(), txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim())

                                            if(listaPrecioSeleccionada!=""){

                                                var precioArticuloSelecionado=txtPrecioItemManualFacturacion.textoInputBox.trim()

                                                var cotizacion=1;
                                                valorPrecioArticulo2=precioArticuloSelecionado

                                                cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)

                                                cantidadItemsVendidos=1
                                                costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                                //Controlo si se peude vender sin stock previsto
                                                if(modeloArticulos.retornaSiPuedeVenderSinStock(1,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                    funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                    funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                                    funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                    funcionesmysql.loguear("QML::cantidadItems: 1")

                                                    modeloItemsFactura.append({
                                                                                  codigoArticulo:valorArticuloInterno,
                                                                                  codigoBarrasArticulo:"",
                                                                                  descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                                  descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                                  precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  cantidadItems:1,
                                                                                  costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  activo:true,
                                                                                  consideraDescuento:false,
                                                                                  indiceLinea:-1,
                                                                                  descuentoLineaItem:0,
                                                                                  codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                                  descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                                  asignarGarantiaAArticulo:false
                                                                              })


                                                    listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)
                                                    valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos



                                                    if(modoCalculoTotal=="1"){
                                                        etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                    }else if(modoCalculoTotal=="2"){
                                                        etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                    }

                                                    mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")


                                                    txtCantidadArticulosFacturacion.textoInputBox=""
                                                    txtArticuloParaFacturacion.textoInputBox=""
                                                    txtPrecioItemManualFacturacion.textoInputBox=""
                                                    txtCodigoDeBarrasADemanda.textoInputBox=""
                                                    txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                    txtArticuloParaFacturacion.tomarElFocoP()
                                                }

                                            }else{

                                                var precioArticuloSelecionadoSinLista=txtPrecioItemManualFacturacion.textoInputBox.trim()

                                                var cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion);
                                                valorPrecioArticulo2=precioArticuloSelecionadoSinLista
                                                cantidadItemsVendidos=1
                                                costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                                //Controlo si se peude vender sin stock previsto
                                                if(modeloArticulos.retornaSiPuedeVenderSinStock(1,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                    funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                    funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                                    funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                    funcionesmysql.loguear("QML::cantidadItems: 1")

                                                    modeloItemsFactura.append({
                                                                                  codigoArticulo:valorArticuloInterno,
                                                                                  codigoBarrasArticulo:"",
                                                                                  descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                                  descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                                  precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  cantidadItems:1,
                                                                                  costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  activo:true,
                                                                                  consideraDescuento:false,
                                                                                  indiceLinea:-1,
                                                                                  descuentoLineaItem:0,
                                                                                  codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                                  descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                                  asignarGarantiaAArticulo:false
                                                                              })

                                                    listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)


                                                    valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos



                                                    if(modoCalculoTotal=="1"){
                                                        etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                    }else if(modoCalculoTotal=="2"){
                                                        etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                    }

                                                    mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")

                                                    txtCantidadArticulosFacturacion.textoInputBox=""
                                                    txtArticuloParaFacturacion.textoInputBox=""
                                                    txtPrecioItemManualFacturacion.textoInputBox=""
                                                    txtCodigoDeBarrasADemanda.textoInputBox=""
                                                    txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                    txtArticuloParaFacturacion.tomarElFocoP()
                                                }
                                            }

                                        }else{

                                            var precioArticuloSelecionadoSinListaySinCliente=txtPrecioItemManualFacturacion.textoInputBox.trim()


                                            var cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion);
                                            valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente
                                            cantidadItemsVendidos=1
                                            costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                            //Controlo si se peude vender sin stock previsto
                                            if(modeloArticulos.retornaSiPuedeVenderSinStock(1,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                                funcionesmysql.loguear("QML::codigoArticulo: "+valorArticuloInterno)
                                                funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                                funcionesmysql.loguear("QML::cantidadItems: 1")

                                                modeloItemsFactura.append({
                                                                              codigoArticulo:valorArticuloInterno,
                                                                              codigoBarrasArticulo:"",
                                                                              descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                              descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                              precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              cantidadItems:1,
                                                                              costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              activo:true,
                                                                              consideraDescuento:false,
                                                                              indiceLinea:-1,
                                                                              descuentoLineaItem:0,
                                                                              codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                              descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                              asignarGarantiaAArticulo:false
                                                                          })

                                                listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                                valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos
                                                if(modoCalculoTotal=="1"){
                                                    etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }else if(modoCalculoTotal=="2"){
                                                    etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }

                                                mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")

                                                txtCantidadArticulosFacturacion.textoInputBox=""
                                                txtArticuloParaFacturacion.textoInputBox=""
                                                txtPrecioItemManualFacturacion.textoInputBox=""
                                                txtCodigoDeBarrasADemanda.textoInputBox=""
                                                txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                txtArticuloParaFacturacion.tomarElFocoP()
                                            }
                                        }
                                    }




                                }else{

                                    txtArticuloParaFacturacion.mensajeError("Artículo "+valorArticuloInterno+" incativo.")
                                    txtArticuloParaFacturacion.textoInputBox=""

                                    txtArticuloParaFacturacion.tomarElFocoP()
                                }
                            }else{
                                txtArticuloParaFacturacion.tomarElFocoP()
                            }
                        }

                    }
                }
            }

            TextInputSimple {
                id: txtObservacionesFactura
                x: 65
                y: 200
                //    width: 370
                enFocoSeleccionarTodo: false
                textoInputBox: ""
                botonBuscarTextoVisible: false
                textoDeFondo: "escriba aquí información adicional"
                largoMaximo: 80
                textoTitulo: "Observaciones:"
                cursor_Visible: false
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaObservaciones")
            }
            TextInputSimple {
                id: txtComentariosFactura
                x: 65
                y: 200
                enFocoSeleccionarTodo: false
                textoInputBox: ""
                botonBuscarTextoVisible: false
                textoDeFondo: "Comentarios internos"
                largoMaximo: 80
                textoTitulo: "Comentarios:"
                cursor_Visible: false
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaComentarios")
            }

            ComboBoxListaPrecios {
                id: cbxListaPrecioManualFijadaPorUsuario
                width: 230
                codigoValorSeleccion: ""
                textoTitulo: "Lista precio manual:"
                textoComboBox: ""
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaListaPrecioManual")
            }

            TextInputSimple {
                id: txtCostoArticuloMonedaReferencia
                //   width: 170
                height: 35
                enFocoSeleccionarTodo: true
                textoInputBox: ""+modeloconfiguracion.retornaCantidadDecimalesString()+""
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaPrecioManualEnMonedaReferencia")
                botonBuscarTextoVisible: false
                inputMask: "00000000"+modeloconfiguracion.retornaCantidadDecimalesString()+";"
                botonBorrarTextoVisible: true
                largoMaximo: 45
                textoTitulo: "Costo en moneda ref. "+modeloListaMonedas.retornaSimboloMoneda(modeloListaMonedas.retornaMonedaReferenciaSistema())+":"
                enable: true
                colorDeTitulo: "#dbd8d8"
                onEnter: {


                    if(txtCostoArticuloMonedaReferencia.textoInputBox.trim()!="" && txtCostoArticuloMonedaReferencia.textoInputBox.trim()!="0" && txtCostoArticuloMonedaReferencia.textoInputBox.trim()!="."){

                        valorArticuloInterno=modeloArticulos.existeArticulo(txtArticuloParaFacturacion.textoInputBox.trim());

                        if(valorArticuloInterno!="" && !superaCantidadMaximaLineasDocumento()){
                            codigoDeBarraArticulo=''

                            ///Chequeo que modo de calculo de total esta seteado
                            var modoCalculoTotal=modeloconfiguracion.retornaValorConfiguracion("MODO_CALCULOTOTAL");

                            txtArticuloParaFacturacion.textoInputBox=valorArticuloInterno

                            if(modeloArticulos.retornaArticuloActivo(valorArticuloInterno) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")){

                                if(txtCantidadArticulosFacturacion.visible){

                                    if(txtCantidadArticulosFacturacion.textoInputBox.trim()!="" && txtCantidadArticulosFacturacion.textoInputBox.trim()!="0"){

                                        if(txtCodigoClienteFacturacion.textoInputBox!=""){ //Hay un cliente seleccionado
                                            var listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(txtFechaPrecioFacturacion.textoInputBox.trim(), txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim())

                                            if(listaPrecioSeleccionada!=""){

                                                var precioArticuloSelecionado=txtPrecioItemManualFacturacion.textoInputBox.trim()

                                                var cotizacion=1;
                                                valorPrecioArticulo2=precioArticuloSelecionado

                                                cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)

                                                cantidadItemsVendidos=txtCantidadArticulosFacturacion.textoInputBox.trim()
                                                costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                                //Controlo si se peude vender sin stock previsto
                                                if(modeloArticulos.retornaSiPuedeVenderSinStock(cantidadItemsVendidos,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                    modeloItemsFactura.append({
                                                                                  codigoArticulo:valorArticuloInterno,
                                                                                  codigoBarrasArticulo:"",
                                                                                  descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                                  descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                                  precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  cantidadItems:cantidadItemsVendidos,
                                                                                  costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  activo:true,
                                                                                  consideraDescuento:false,
                                                                                  indiceLinea:-1,
                                                                                  descuentoLineaItem:0,
                                                                                  codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                                  descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                                  asignarGarantiaAArticulo:false
                                                                              })


                                                    listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                                    valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos


                                                    if(modoCalculoTotal=="1"){
                                                        etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                    }else if(modoCalculoTotal=="2"){
                                                        etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                    }

                                                    mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")

                                                    txtCantidadArticulosFacturacion.textoInputBox=""
                                                    txtArticuloParaFacturacion.textoInputBox=""
                                                    txtPrecioItemManualFacturacion.textoInputBox=""
                                                    txtCodigoDeBarrasADemanda.textoInputBox=""
                                                    txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""


                                                    txtArticuloParaFacturacion.tomarElFocoP()
                                                }

                                            }else{

                                                var precioArticuloSelecionadoSinLista=txtPrecioItemManualFacturacion.textoInputBox.trim()

                                                var cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion);
                                                valorPrecioArticulo2=precioArticuloSelecionadoSinLista

                                                cantidadItemsVendidos=txtCantidadArticulosFacturacion.textoInputBox.trim()
                                                costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                                //Controlo si se peude vender sin stock previsto
                                                if(modeloArticulos.retornaSiPuedeVenderSinStock(cantidadItemsVendidos,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){
                                                    modeloItemsFactura.append({
                                                                                  codigoArticulo:valorArticuloInterno,
                                                                                  codigoBarrasArticulo:"",
                                                                                  descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                                  descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                                  precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  cantidadItems:cantidadItemsVendidos,
                                                                                  costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                                  activo:true,
                                                                                  consideraDescuento:false,
                                                                                  indiceLinea:-1,
                                                                                  descuentoLineaItem:0,
                                                                                  codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                                  descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                                  asignarGarantiaAArticulo:false
                                                                              })

                                                    listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)


                                                    valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos




                                                    if(modoCalculoTotal=="1"){
                                                        etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                    }else if(modoCalculoTotal=="2"){
                                                        etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                    }

                                                    mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")


                                                    txtCantidadArticulosFacturacion.textoInputBox=""
                                                    txtArticuloParaFacturacion.textoInputBox=""
                                                    txtPrecioItemManualFacturacion.textoInputBox=""
                                                    txtCodigoDeBarrasADemanda.textoInputBox=""
                                                    txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                    txtArticuloParaFacturacion.tomarElFocoP()
                                                }
                                            }

                                        }else{

                                            var precioArticuloSelecionadoSinListaySinCliente=txtPrecioItemManualFacturacion.textoInputBox.trim()


                                            var cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion);
                                            valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente


                                            cantidadItemsVendidos=txtCantidadArticulosFacturacion.textoInputBox.trim()
                                            costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                            //Controlo si se peude vender sin stock previsto
                                            if(modeloArticulos.retornaSiPuedeVenderSinStock(cantidadItemsVendidos,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                modeloItemsFactura.append({
                                                                              codigoArticulo:valorArticuloInterno,
                                                                              codigoBarrasArticulo:"",
                                                                              descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                              descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                              precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              cantidadItems:cantidadItemsVendidos,
                                                                              costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              activo:true,
                                                                              consideraDescuento:false,
                                                                              indiceLinea:-1,
                                                                              descuentoLineaItem:0,
                                                                              codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                              descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                              asignarGarantiaAArticulo:false
                                                                          })
                                                listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)


                                                valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos

                                                if(modoCalculoTotal=="1"){
                                                    etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }else if(modoCalculoTotal=="2"){
                                                    etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }

                                                mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")


                                                txtCantidadArticulosFacturacion.textoInputBox=""
                                                txtArticuloParaFacturacion.textoInputBox=""
                                                txtPrecioItemManualFacturacion.textoInputBox=""
                                                txtCodigoDeBarrasADemanda.textoInputBox=""
                                                txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                txtArticuloParaFacturacion.tomarElFocoP()
                                            }
                                        }


                                    }else{
                                        txtCantidadArticulosFacturacion.tomarElFoco()
                                    }

                                    ///
                                }else{
                                    if(txtCodigoClienteFacturacion.textoInputBox!=""){ //Hay un cliente seleccionado
                                        var listaPrecioSeleccionada=modeloListasPrecios.retornaListaPrecioDeCliente(txtFechaPrecioFacturacion.textoInputBox.trim(), txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim())

                                        if(listaPrecioSeleccionada!=""){

                                            var precioArticuloSelecionado=txtPrecioItemManualFacturacion.textoInputBox.trim()

                                            var cotizacion=1;
                                            valorPrecioArticulo2=precioArticuloSelecionado

                                            //Controlo si se peude vender sin stock previsto
                                            if(modeloArticulos.retornaSiPuedeVenderSinStock(1,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                                cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)

                                                cantidadItemsVendidos=1
                                                costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();
                                                modeloItemsFactura.append({
                                                                              codigoArticulo:valorArticuloInterno,
                                                                              codigoBarrasArticulo:"",
                                                                              descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                              descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                              precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              cantidadItems:1,
                                                                              costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              activo:true,
                                                                              consideraDescuento:false,
                                                                              indiceLinea:-1,
                                                                              descuentoLineaItem:0,
                                                                              codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                              descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                              asignarGarantiaAArticulo:false
                                                                          })

                                                listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                                valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos



                                                if(modoCalculoTotal=="1"){
                                                    etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }else if(modoCalculoTotal=="2"){
                                                    etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }

                                                mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")


                                                txtCantidadArticulosFacturacion.textoInputBox=""
                                                txtArticuloParaFacturacion.textoInputBox=""
                                                txtPrecioItemManualFacturacion.textoInputBox=""
                                                txtCodigoDeBarrasADemanda.textoInputBox=""
                                                txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                txtArticuloParaFacturacion.tomarElFocoP()

                                            }
                                        }else{

                                            var precioArticuloSelecionadoSinLista=txtPrecioItemManualFacturacion.textoInputBox.trim()

                                            var cotizacion2=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion);
                                            valorPrecioArticulo2=precioArticuloSelecionadoSinLista

                                            cantidadItemsVendidos=1

                                            costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                            //Controlo si se peude vender sin stock previsto
                                            if(modeloArticulos.retornaSiPuedeVenderSinStock(1,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){


                                                modeloItemsFactura.append({
                                                                              codigoArticulo:valorArticuloInterno,
                                                                              codigoBarrasArticulo:"",
                                                                              descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                              descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                              precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              cantidadItems:1,
                                                                              costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                              activo:true,
                                                                              consideraDescuento:false,
                                                                              indiceLinea:-1,
                                                                              descuentoLineaItem:0,
                                                                              codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                              descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                              asignarGarantiaAArticulo:false
                                                                          })

                                                listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                                valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos



                                                if(modoCalculoTotal=="1"){
                                                    etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }else if(modoCalculoTotal=="2"){
                                                    etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                                }

                                                mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")


                                                txtCantidadArticulosFacturacion.textoInputBox=""
                                                txtArticuloParaFacturacion.textoInputBox=""
                                                txtPrecioItemManualFacturacion.textoInputBox=""
                                                txtCodigoDeBarrasADemanda.textoInputBox=""
                                                txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                                txtArticuloParaFacturacion.tomarElFocoP()
                                            }
                                        }

                                    }else{

                                        var precioArticuloSelecionadoSinListaySinCliente=txtPrecioItemManualFacturacion.textoInputBox.trim()


                                        var cotizacion3=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion);
                                        valorPrecioArticulo2=precioArticuloSelecionadoSinListaySinCliente


                                        cantidadItemsVendidos=1

                                        costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();
                                        //costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                        //txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

                                        //Controlo si se peude vender sin stock previsto
                                        if(modeloArticulos.retornaSiPuedeVenderSinStock(1,cbListatipoDocumentos.codigoValorSeleccion,valorArticuloInterno,retornaCantidadDeUnArticuloEnFacturacion(valorArticuloInterno)   )){

                                            modeloItemsFactura.append({
                                                                          codigoArticulo:valorArticuloInterno,
                                                                          codigoBarrasArticulo:"",
                                                                          descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(valorArticuloInterno),
                                                                          descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(valorArticuloInterno),
                                                                          precioArticulo:valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          precioArticuloSubTotal:(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos).toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          cantidadItems:1,
                                                                          costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                          activo:true,
                                                                          consideraDescuento:false,
                                                                          indiceLinea:-1,
                                                                          descuentoLineaItem:0,
                                                                          codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno),
                                                                          descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(valorArticuloInterno)),
                                                                          asignarGarantiaAArticulo:false
                                                                      })

                                            listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                            valorPrecioArticulo2=valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))*cantidadItemsVendidos
                                            if(modoCalculoTotal=="1"){
                                                etiquetaTotal.setearTotal(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                            }else if(modoCalculoTotal=="2"){
                                                etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo2.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),valorArticuloInterno,cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                            }

                                            mostrarCuadroDeActulizacionDePrecioEnFacturacion(valorArticuloInterno,"")

                                            txtCantidadArticulosFacturacion.textoInputBox=""
                                            txtArticuloParaFacturacion.textoInputBox=""
                                            txtPrecioItemManualFacturacion.textoInputBox=""
                                            txtCodigoDeBarrasADemanda.textoInputBox=""
                                            txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                                            txtArticuloParaFacturacion.tomarElFocoP()

                                        }
                                    }
                                }




                            }else{

                                txtArticuloParaFacturacion.mensajeError("Artículo "+valorArticuloInterno+" incativo.")
                                txtArticuloParaFacturacion.textoInputBox=""

                                txtArticuloParaFacturacion.tomarElFocoP()
                            }
                        }else{
                            txtArticuloParaFacturacion.tomarElFocoP()
                        }
                    }
                }
            }
            anchors.rightMargin: 10
            z: 18
            anchors.right: flowItemsFijosdocumentoImpresora.left
            anchors.leftMargin: 10
            anchors.left: parent.left
        }

        Flow{
            id: flowItemsFijosdocumentoImpresora
            width: 400
            anchors.top: flowCuerpoFacturacion.bottom
            anchors.topMargin: 8
            layoutDirection: Qt.LeftToRight
            anchors.right: parent.right
            anchors.rightMargin: 10
            z: 15

            ComboBoxCheckBoxGenerico {
                id: cbListaDocumentosCuentaCorrienteConDeuda
                width: 350
                z: 16
                visible: {
                    ///Si el documento es recibo o nota de credito, o sea de pago a cuenta corriente, es visible el control
                    if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"afectaCuentaCorriente")=="-1"){
                        true
                    }else{
                        false
                    }
                }
                codigoValorSeleccion: ""
                textoTitulo: "Documentos con deuda:"
                textoComboBox: ""

                onSenialAlAceptarOClick: {
                    if(txtVendedorDeFactura.visible){
                        setearVendedorDeFacturasEnNotaDeCreditoORecibo()
                    }

                }


            }

            ListModel{
                id:modeloListaTipoDocumentosConDeudaVirtual
            }


            ComboBoxListaFormasDePago {
                id: cbListaFormasDePago
                width: 300
                z: 15
                visible: modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaFormasDePago")
                textoTitulo: "Formas de pago:"
                textoComboBox: ""
                codigoValorSeleccion: ""
            }



            ComboBoxListaImpresoras {
                id: cbListaImpresoras
                width: 230
                //     anchors.right: cbListaMonedasEnFacturacion.left
                //     anchors.rightMargin: 0
                //      anchors.bottom: contenedorFlipable.top
                //      anchors.bottomMargin: 10
                textoTitulo: "Impresoras:"
                textoComboBox: funcionesmysql.impresoraPorDefecto()
            }

            ComboBoxListaMonedas {
                id: cbListaMonedasEnFacturacion
                width: 150
                height: 35
                //    anchors.bottom: contenedorFlipable.top
                //    anchors.bottomMargin: 10
                //    anchors.right: parent.right
                //    anchors.rightMargin: 45
                z: 14
                botonBuscarTextoVisible: false
                textoTitulo: "Facturar en moneda:"
                codigoValorSeleccion: modeloconfiguracion.retornaValorConfiguracion("MONEDA_DEFAULT")
                textoComboBox: modeloListaMonedas.retornaDescripcionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                onSenialAlAceptarOClick: {

                    var simboloMoneda=modeloListaMonedas.retornaSimboloMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)

                    etiquetaTotal.labelTotal=qsTr("Total "+simboloMoneda)
                    etiquetaTotal.labelTotalDescuentos=qsTr("Descuento "+simboloMoneda)
                    etiquetaTotalMedioDePago.labelTotal=qsTr("Total medios de pago "+simboloMoneda)

                    lbltemTotalVentaFacturacion.text=qsTr("Unidad "+simboloMoneda)

                    txtPrecioItemManualFacturacion.textoTitulo="Precio unitario "+simboloMoneda+":"

                    modeloComboBoxDocumentosConSaldoCuentaCorriente.limpiarListaDocumentos()
                    modeloListaTipoDocumentosConDeudaVirtual.clear()
                    cbListaDocumentosCuentaCorrienteConDeuda.cerrarComboBox()

                    if(cbListaDocumentosCuentaCorrienteConDeuda.visible && txtCodigoClienteFacturacion.textoInputBox.trim()!="" && lblRazonSocialCliente.text.trim()!=""){
                        cargarDocumentosConDeuda()
                    }



                }
            }
        }
    }

    Row {
        id: rowBarraDeHerramientas
        z: 0
        //
        anchors.bottom: rectContenedor.top
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 260
        width: rowBarraDeHerramientas.implicitWidth
        spacing: distanciaEntreBotonesBarraDeTareas

        BotonBarraDeHerramientas {
            id: botonNuevaFactura
            toolTip: "Nueva factura"
            z: 8
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Nuevo.png"
            //source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevaFacturacion.png"


            onClic: {

                if(txtCodigoClienteFacturacion.textoInputBox!="" || listaDeItemsFactura.count!=0){

                    if(funcionesmysql.mensajeAdvertencia("Es posible que una factura se encuentre en proceso.\nRealmente desea crear una nueva?\n\nPresione [ Sí ] para confirmar.")){
                        crearNuevaFactura()
                        if(txtNumeroDocumentoFacturacion.visible && txtNumeroDocumentoFacturacion.textoInputBox==""){
                            txtNumeroDocumentoFacturacion.textoInputBox=modeloDocumentos.retornoCodigoUltimoDocumentoDisponible(cbListatipoDocumentos.codigoValorSeleccion)
                        }

                    }
                }else{
                    crearNuevaFactura()
                    if(txtNumeroDocumentoFacturacion.visible && txtNumeroDocumentoFacturacion.textoInputBox==""){
                        txtNumeroDocumentoFacturacion.textoInputBox=modeloDocumentos.retornoCodigoUltimoDocumentoDisponible(cbListatipoDocumentos.codigoValorSeleccion)
                    }

                }
            }
        }

        BotonBarraDeHerramientas {
            id: separador
            toolTip: ""
            source: ""
            enabled: false
        }




        BotonBarraDeHerramientas {
            id: botonGuardarFacturaEmitir
            toolTip: "Guardar factura"
            z: 7
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            onClic: {


                txtMensajeInformacion.text="";
                var resultadoInsertDocumento=0;
                var estatusProcesoMedioDePago=true;

                var estadoDocumento=modeloDocumentos.retornacodigoEstadoDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim())

                ///Funcionalidad incorporada en versión 1.10.0
                ///Chequeo si el documento que se intenta guardar ya fue guardado, si es así, es porque es un documento que tiene marcada
                ///la opcion de deuda para contados en tipo de documentos documentoAceptaIngresoDeMediosDePagoLuegoDeEmitido
                if((estadoDocumento=="E" || estadoDocumento=="G") && nuevoDocumento==""){
                    txtMensajeInformacion.visible=true
                    txtMensajeInformacionTimer.stop()
                    txtMensajeInformacionTimer.start()
                    // Comienzo el guardado de los medios de pago seleccionados.
                    if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")){
                        if(modeloListaMediosDePagoAgregados.count==0){
                            estatusProcesoMedioDePago=true;
                        }else{

                            if(modeloMediosDePago.eliminarLineaMedioDePagoDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim())){
                                for(var i=0; i<modeloListaMediosDePagoAgregados.count;i++){

                                    if(modeloMediosDePago.guardarLineaMedioDePago(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,
                                                                                  i.toString(),modeloListaMediosDePagoAgregados.get(i).codigoMedioDePago,
                                                                                  modeloListaMediosDePagoAgregados.get(i).monedaMedioPago,
                                                                                  modeloListaMediosDePagoAgregados.get(i).montoMedioDePago,
                                                                                  modeloListaMediosDePagoAgregados.get(i).cantidadCuotas,

                                                                                  modeloListaMediosDePagoAgregados.get(i).numeroBanco,
                                                                                  modeloListaMediosDePagoAgregados.get(i).codigoTarjetaCredito,
                                                                                  modeloListaMediosDePagoAgregados.get(i).numeroCheque,
                                                                                  modeloListaMediosDePagoAgregados.get(i).tipoCheque,
                                                                                  modeloListaMediosDePagoAgregados.get(i).fechaCheque,

                                                                                  modeloListaMediosDePagoAgregados.get(i).codigoDoc,
                                                                                  modeloListaMediosDePagoAgregados.get(i).codigoTipoDoc,
                                                                                  modeloListaMediosDePagoAgregados.get(i).numeroLineaDocumento,
                                                                                  modeloListaMediosDePagoAgregados.get(i).numeroCuentaBancariaAgregado,
                                                                                  modeloListaMediosDePagoAgregados.get(i).numeroBancoCuentaBancaria,
                                                                                  txtSerieFacturacion.textoInputBox.trim()
                                                                                  )){

                                        if(modeloListaMediosDePagoAgregados.get(i).esDiferido){
                                            if(!modeloLineasDePagoListaChequesDiferidosComboBox.actualizarLineaDePagoChequeDiferido(modeloListaMediosDePagoAgregados.get(i).codigoDoc, modeloListaMediosDePagoAgregados.get(i).codigoTipoDoc,  modeloListaMediosDePagoAgregados.get(i).numeroLineaDocumento,modeloListaMediosDePagoAgregados.get(i).montoMedioDePago,modeloListaMediosDePagoAgregados.get(i).serieDoc)){
                                                estatusProcesoMedioDePago=false;
                                                break;
                                            }
                                        }
                                    }else{
                                        estatusProcesoMedioDePago=false;
                                        break;
                                    }
                                }
                                if(estatusProcesoMedioDePago){
                                    modeloDocumentos.actualizoSaldoClientePagoContadoDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,etiquetaTotalMedioDePago.retornaTotal(),txtSerieFacturacion.textoInputBox.trim());
                                }

                            }else{
                                estatusProcesoMedioDePago=false;
                            }
                        }
                        if(estatusProcesoMedioDePago){

                            if(modeloDocumentos.actualizoSaldoClientePagoContadoDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,etiquetaTotalMedioDePago.retornaTotal(),txtSerieFacturacion.textoInputBox.trim())){
                                txtMensajeInformacion.color="#2f71a0"
                                txtMensajeInformacion.text="El documento "+txtNumeroDocumentoFacturacion.textoInputBox.trim()+" se actualizo correctamente."
                                crearNuevaFactura()

                                cuadroListaDocumentosNuevo.visible=modeloconfiguracion.retornaModoAvisoDocumentosNuevoVisible();


                            }else{
                                txtMensajeInformacion.color="#d93e3e"
                                txtMensajeInformacion.text="ATENCION: Ocurrió un error al intentar actualizar la deuda en medios de pago, intentenlo nuevamente."
                                funcionesmysql.mensajeAdvertenciaOk("ATENCION: Ocurrió un error al intentar actualizar la deuda en medios de pago, intentenlo nuevamente.")
                            }
                        }else{
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="ATENCION: Ocurrió un error al intentar actualizar los medios de pago."
                        }
                    }else{
                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text="El documento "+txtNumeroDocumentoFacturacion.textoInputBox.trim()+" no tenia datos para actualizar."
                        crearNuevaFactura()
                        cuadroListaDocumentosNuevo.visible=modeloconfiguracion.retornaModoAvisoDocumentosNuevoVisible();
                    }



                }else{



                    if(!txtSerieFacturacion.visible && txtSerieFacturacion.textoInputBox==""){

                        txtSerieFacturacion.textoInputBox=modeloListaTipoDocumentosComboBox.retornaSerieTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion)
                    }

                    if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaCliente")){
                        if(txtCodigoClienteFacturacion.textoInputBox.trim()=="" || lblRazonSocialCliente.text.trim()==""){
                            resultadoInsertDocumento=-5;
                        }else{
                            if(!modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")){
                                if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")){
                                    if(listaDeMediosDePagoSeleccionados.count==0){
                                        resultadoInsertDocumento=-5;
                                    }
                                }
                            }
                        }
                    }else if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")){
                        if(listaDeItemsFactura.count==0){
                            resultadoInsertDocumento=-5;
                        }
                    }else if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")){
                        if(listaDeMediosDePagoSeleccionados.count==0){
                            resultadoInsertDocumento=-5;
                        }
                    }

                    if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")){
                        if(listaDeMediosDePagoSeleccionados.count==0){
                            if(!funcionesmysql.mensajeAdvertencia("No se ingresaron medios de pago, desea guardar de todos modos el documento?\n\nPresione [ Sí ] para confirmar.")){
                                resultadoInsertDocumento=-11
                            }
                        }
                    }


                    if(modeloconfiguracion.retornaValorConfiguracion("UTILIZA_CONTROL_CLIENTE_CREDITO")=="1"){
                        if(txtCodigoClienteFacturacion.textoInputBox.trim()!="" && lblRazonSocialCliente.text.trim()!=""){
                            if(modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"afectaCuentaCorriente")!="0"){
                                if(modeloClientes.retornaSiPermiteFacturaCredito(txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion)==false){
                                    resultadoInsertDocumento=-12
                                }
                            }
                        }
                    }





                    if(resultadoInsertDocumento==0){

                        if(!txtNumeroDocumentoFacturacion.visible && txtNumeroDocumentoFacturacion.textoInputBox==""){

                            txtNumeroDocumentoFacturacion.textoInputBox=modeloDocumentos.retornoCodigoUltimoDocumentoDisponible(cbListatipoDocumentos.codigoValorSeleccion)

                        }


                        if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago") &&
                                modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")){

                            if(etiquetaTotal.retornaTotal()==0.00 && modeloItemsFactura.count==0){

                                resultadoInsertDocumento =modeloDocumentos.guardarDocumentos(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim().toUpperCase(),
                                                                                             txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion,cbListaMonedasEnFacturacion.codigoValorSeleccion,
                                                                                             txtFechaDocumentoFacturacion.textoInputBox.trim(),etiquetaTotalMedioDePago.retornaTotal(),etiquetaTotalMedioDePago.retornaSubTotal(),
                                                                                             etiquetaTotalMedioDePago.retornaIvaTotal(),cbListaLiquidacionesFacturacion.codigoValorSeleccion,txtVendedorDeFactura.codigoValorSeleccion,txtNombreDeUsuario.textoInputBox.trim(),
                                                                                             "EMITIR",cbListaLiquidacionesFacturacion.codigoValorSeleccionExtra,etiquetaTotalMedioDePago.retornaIva1(),etiquetaTotalMedioDePago.retornaIva2(),etiquetaTotalMedioDePago.retornaIva3(),modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion),txtObservacionesFactura.textoInputBox.trim(),txtComentariosFactura.textoInputBox.trim(),
                                                                                             cbxAfectaCuentaBancaria.codigoValorSeleccion,cbxAfectaCuentaBancaria.codigoValorSeleccion2,
                                                                                             etiquetaTotal.retornaTotalDescuento(),etiquetaTotal.retornaSubTotalSinDescuento(),cbListaFormasDePago.textoComboBox.trim(),etiquetaTotal.retornaPorcentajeDescuento(),etiquetaTotalMedioDePago.retornaTotal());

                            }else{
                                resultadoInsertDocumento =modeloDocumentos.guardarDocumentos(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim().toUpperCase(),
                                                                                             txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion,cbListaMonedasEnFacturacion.codigoValorSeleccion,
                                                                                             txtFechaDocumentoFacturacion.textoInputBox.trim(),etiquetaTotal.retornaTotal(),etiquetaTotal.retornaSubTotal(),
                                                                                             etiquetaTotal.retornaIvaTotal(),cbListaLiquidacionesFacturacion.codigoValorSeleccion,txtVendedorDeFactura.codigoValorSeleccion,txtNombreDeUsuario.textoInputBox.trim(),
                                                                                             "EMITIR",cbListaLiquidacionesFacturacion.codigoValorSeleccionExtra,etiquetaTotal.retornaIva1(),etiquetaTotal.retornaIva2(),etiquetaTotal.retornaIva3(),modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion),txtObservacionesFactura.textoInputBox.trim(),txtComentariosFactura.textoInputBox.trim(),
                                                                                             cbxAfectaCuentaBancaria.codigoValorSeleccion,cbxAfectaCuentaBancaria.codigoValorSeleccion2,
                                                                                             etiquetaTotal.retornaTotalDescuento(),etiquetaTotal.retornaSubTotalSinDescuento(),cbListaFormasDePago.textoComboBox.trim(),etiquetaTotal.retornaPorcentajeDescuento(),etiquetaTotalMedioDePago.retornaTotal());
                            }




                        }else if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago") &&
                                 modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")==false){


                            resultadoInsertDocumento =modeloDocumentos.guardarDocumentos(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim().toUpperCase(),
                                                                                         txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion,cbListaMonedasEnFacturacion.codigoValorSeleccion,
                                                                                         txtFechaDocumentoFacturacion.textoInputBox.trim(),etiquetaTotalMedioDePago.retornaTotal(),etiquetaTotalMedioDePago.retornaSubTotal(),
                                                                                         etiquetaTotalMedioDePago.retornaIvaTotal(),cbListaLiquidacionesFacturacion.codigoValorSeleccion,txtVendedorDeFactura.codigoValorSeleccion,txtNombreDeUsuario.textoInputBox.trim(),
                                                                                         "EMITIR",cbListaLiquidacionesFacturacion.codigoValorSeleccionExtra,etiquetaTotalMedioDePago.retornaIva1(),etiquetaTotalMedioDePago.retornaIva2(),etiquetaTotalMedioDePago.retornaIva3(),modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion),txtObservacionesFactura.textoInputBox.trim(),txtComentariosFactura.textoInputBox.trim(),
                                                                                         cbxAfectaCuentaBancaria.codigoValorSeleccion,cbxAfectaCuentaBancaria.codigoValorSeleccion2,
                                                                                         etiquetaTotal.retornaTotalDescuento(),etiquetaTotal.retornaSubTotalSinDescuento(),cbListaFormasDePago.textoComboBox.trim(),etiquetaTotal.retornaPorcentajeDescuento(),etiquetaTotalMedioDePago.retornaTotal());

                        }else if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")==false &&
                                 modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulos")){

                            resultadoInsertDocumento =modeloDocumentos.guardarDocumentos(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim().toUpperCase(),
                                                                                         txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion,cbListaMonedasEnFacturacion.codigoValorSeleccion,
                                                                                         txtFechaDocumentoFacturacion.textoInputBox.trim(),etiquetaTotal.retornaTotal(),etiquetaTotal.retornaSubTotal(),
                                                                                         etiquetaTotal.retornaIvaTotal(),cbListaLiquidacionesFacturacion.codigoValorSeleccion,txtVendedorDeFactura.codigoValorSeleccion,txtNombreDeUsuario.textoInputBox.trim(),
                                                                                         "EMITIR",cbListaLiquidacionesFacturacion.codigoValorSeleccionExtra,etiquetaTotal.retornaIva1(),etiquetaTotal.retornaIva2(),etiquetaTotal.retornaIva3(),modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion),txtObservacionesFactura.textoInputBox.trim(),txtComentariosFactura.textoInputBox.trim(),
                                                                                         cbxAfectaCuentaBancaria.codigoValorSeleccion,cbxAfectaCuentaBancaria.codigoValorSeleccion2,
                                                                                         etiquetaTotal.retornaTotalDescuento(),etiquetaTotal.retornaSubTotalSinDescuento(),cbListaFormasDePago.textoComboBox.trim(),etiquetaTotal.retornaPorcentajeDescuento(),etiquetaTotalMedioDePago.retornaTotal());
                        }



                        txtMensajeInformacion.visible=true
                        txtMensajeInformacionTimer.stop()
                        txtMensajeInformacionTimer.start()

                        if(resultadoInsertDocumento==1){

                            if(modeloDocumentos.eliminarLineaDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion, txtSerieFacturacion.textoInputBox.trim()))
                            {


                                var cantidad=1;
                                var estatusProcesoLineas=true;
                                var costoPonderado=0.00;
                                var esDocumentoValidoParaCalculoPonderado=modeloDocumentos.documentoValidoParaCalculoPonderado(cbListatipoDocumentos.codigoValorSeleccion);

                                var _insertLineasDocumentos="insert INTO DocumentosLineas (codigoDocumento, codigoTipoDocumento, serieDocumento , numeroLinea, codigoArticulo, codigoArticuloBarras, cantidad, precioTotalVenta, precioArticuloUnitario, precioIvaArticulo,costoArticuloMonedaReferencia,costoArticuloPonderado,montoDescuento,codigoTipoGarantia)values"

                                for(var i=0; i<modeloItemsFactura.count;i++){
                                    cantidad=modeloItemsFactura.get(i).cantidadItems

                                    if(modeloItemsFactura.get(i).asignarGarantiaAArticulo)
                                        modeloArticulos.actualizarGarantia(modeloItemsFactura.get(i).codigoArticulo,modeloItemsFactura.get(i).codigoTipoGarantia);


                                    if(esDocumentoValidoParaCalculoPonderado){
                                        ///codigoArticulo, cantidad, costoTotal
                                        costoPonderado = modeloDocumentos.retonaCostoPonderadoSegunStock(modeloItemsFactura.get(i).codigoArticulo,cantidad,modeloItemsFactura.get(i).costoArticuloMonedaReferencia)
                                    }else{
                                        costoPonderado=0.00
                                    }




                                    if(i==0){
                                        _insertLineasDocumentos+="('"+txtNumeroDocumentoFacturacion.textoInputBox.trim()+"','"+cbListatipoDocumentos.codigoValorSeleccion+"','"+txtSerieFacturacion.textoInputBox.trim()+"','"+i.toString()+"','"+modeloItemsFactura.get(i).codigoArticulo+"','"+modeloItemsFactura.get(i).codigoBarrasArticulo+"','"+cantidad+"','"+(modeloItemsFactura.get(i).precioArticulo*cantidad)+"','"+modeloItemsFactura.get(i).precioArticulo+"','"+((modeloItemsFactura.get(i).precioArticulo*cantidad) - ((modeloItemsFactura.get(i).precioArticulo*cantidad)/modeloListaIvas.retornaFactorMultiplicador(modeloItemsFactura.get(i).codigoArticulo)))+"','"+modeloItemsFactura.get(i).costoArticuloMonedaReferencia+"','"+costoPonderado+"','"+modeloItemsFactura.get(i).descuentoLineaItem+"','"+modeloItemsFactura.get(i).codigoTipoGarantia+"' )"
                                        modeloDocumentos.marcoArticulosincronizarWeb(modeloItemsFactura.get(i).codigoArticulo)
                                    }else{
                                        _insertLineasDocumentos+=",('"+txtNumeroDocumentoFacturacion.textoInputBox.trim()+"','"+cbListatipoDocumentos.codigoValorSeleccion+"','"+txtSerieFacturacion.textoInputBox.trim()+"','"+i.toString()+"','"+modeloItemsFactura.get(i).codigoArticulo+"','"+modeloItemsFactura.get(i).codigoBarrasArticulo+"','"+cantidad+"','"+(modeloItemsFactura.get(i).precioArticulo*cantidad)+"','"+modeloItemsFactura.get(i).precioArticulo+"','"+((modeloItemsFactura.get(i).precioArticulo*cantidad) - ((modeloItemsFactura.get(i).precioArticulo*cantidad)/modeloListaIvas.retornaFactorMultiplicador(modeloItemsFactura.get(i).codigoArticulo)))+"','"+modeloItemsFactura.get(i).costoArticuloMonedaReferencia+"','"+costoPonderado+"','"+modeloItemsFactura.get(i).descuentoLineaItem+"','"+modeloItemsFactura.get(i).codigoTipoGarantia+"')"
                                        modeloDocumentos.marcoArticulosincronizarWeb(modeloItemsFactura.get(i).codigoArticulo)
                                    }

                                }


                                if(modeloItemsFactura.count!=0)
                                    if(!modeloDocumentos.guardarLineaDocumento(_insertLineasDocumentos))
                                        estatusProcesoLineas=false;





                                //Si guardo las lineas de venta correctamente proceso a actualizar el estado del documento a G - Guardado, sin imprimir
                                if(estatusProcesoLineas){
                                    if(modeloDocumentos.actualizoEstadoDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,"G",txtNombreDeUsuario.textoInputBox.trim(),txtSerieFacturacion.textoInputBox.trim())){

                                        var continuarVenta = true;

                                        ///Aca tengo que controlar si el documento se emite o no con CFE IMIX
                                        ///Entro en IMIX
                                        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1" && modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"emiteCFEImprime")==="1" && modelo_CFE_ParametrosGenerales.retornaValor("modoFuncionCFE")==="0"){
                                            txtMensajeInformacion.text="";


                                            if(modeloDocumentos.emitirDocumentoCFEImix(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,lblEstadoDocumento.text.trim(),txtSerieFacturacion.textoInputBox.trim())){

                                                continuarVenta = true;

                                            }else{
                                                continuarVenta=false;
                                            }

                                        }else if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1" && modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"emiteCFEImprime")==="1" && modelo_CFE_ParametrosGenerales.retornaValor("modoFuncionCFE")==="2"){
                                            ///Entro en modo Imix en la nube

                                            txtMensajeInformacion.text="";
                                            if(modeloDocumentos.emitirDocumentoCFE_Imix_Nube(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,numeroDocumentoCFEADevolver,fechaDocumentoCFEADevolver,tipoDocumentoCFEADevolver,lblEstadoDocumento.text.trim(),txtSerieFacturacion.textoInputBox.trim())){

                                                continuarVenta = true;

                                            }else{
                                                continuarVenta=false;

                                            }


                                        }else if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1" && modeloListaTipoDocumentosComboBox.retornaValorCampoTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion,"emiteCFEImprime")==="1" && modelo_CFE_ParametrosGenerales.retornaValor("modoFuncionCFE")==="1"){
                                            ///Entro en modo Dynamia

                                            txtMensajeInformacion.text="";
                                            if(modeloDocumentos.emitirDocumentoCFEDynamia(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,numeroDocumentoCFEADevolver,fechaDocumentoCFEADevolver,tipoDocumentoCFEADevolver,lblEstadoDocumento.text.trim(),txtSerieFacturacion.textoInputBox.trim())){

                                                continuarVenta = true;

                                            }else{
                                                continuarVenta=false;

                                            }


                                        }



                                        if(continuarVenta){

                                            // Comienzo el guardado de los medios de pago seleccionados.
                                            if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaMediosDePago")){
                                                if(modeloListaMediosDePagoAgregados.count==0){
                                                    estatusProcesoMedioDePago=true;
                                                }else{

                                                    if(modeloMediosDePago.eliminarLineaMedioDePagoDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim())){
                                                        for(var i=0; i<modeloListaMediosDePagoAgregados.count;i++){

                                                            if(modeloMediosDePago.guardarLineaMedioDePago(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,
                                                                                                          i.toString(),modeloListaMediosDePagoAgregados.get(i).codigoMedioDePago,
                                                                                                          modeloListaMediosDePagoAgregados.get(i).monedaMedioPago,
                                                                                                          modeloListaMediosDePagoAgregados.get(i).montoMedioDePago,
                                                                                                          modeloListaMediosDePagoAgregados.get(i).cantidadCuotas,

                                                                                                          modeloListaMediosDePagoAgregados.get(i).numeroBanco,
                                                                                                          modeloListaMediosDePagoAgregados.get(i).codigoTarjetaCredito,
                                                                                                          modeloListaMediosDePagoAgregados.get(i).numeroCheque,
                                                                                                          modeloListaMediosDePagoAgregados.get(i).tipoCheque,
                                                                                                          modeloListaMediosDePagoAgregados.get(i).fechaCheque,

                                                                                                          modeloListaMediosDePagoAgregados.get(i).codigoDoc,
                                                                                                          modeloListaMediosDePagoAgregados.get(i).codigoTipoDoc,
                                                                                                          modeloListaMediosDePagoAgregados.get(i).numeroLineaDocumento,
                                                                                                          modeloListaMediosDePagoAgregados.get(i).numeroCuentaBancariaAgregado,
                                                                                                          modeloListaMediosDePagoAgregados.get(i).numeroBancoCuentaBancaria,
                                                                                                          txtSerieFacturacion.textoInputBox.trim()
                                                                                                          )){

                                                                if(modeloListaMediosDePagoAgregados.get(i).esDiferido){
                                                                    if(!modeloLineasDePagoListaChequesDiferidosComboBox.actualizarLineaDePagoChequeDiferido(modeloListaMediosDePagoAgregados.get(i).codigoDoc, modeloListaMediosDePagoAgregados.get(i).codigoTipoDoc,  modeloListaMediosDePagoAgregados.get(i).numeroLineaDocumento,modeloListaMediosDePagoAgregados.get(i).montoMedioDePago,modeloListaMediosDePagoAgregados.get(i).serieDoc)){
                                                                        estatusProcesoMedioDePago=false;
                                                                        break;
                                                                    }

                                                                }


                                                            }else{
                                                                estatusProcesoMedioDePago=false;
                                                                break;
                                                            }
                                                        }
                                                    }else{
                                                        estatusProcesoMedioDePago=false;
                                                    }
                                                }

                                            }

                                            if(estatusProcesoMedioDePago){
                                                modeloLineasDePagoListaChequesDiferidosComboBox.limpiarListaLineasDePago()
                                                modeloLineasDePagoListaChequesDiferidosComboBox.buscarLineasDePagoChequesDiferidos("1=","1")
                                                //Chequea si emite en impresora
                                                if(modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"emiteEnImpresora")){

                                                    if(modeloDocumentos.emitirDocumentoEnImpresora(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,cbListaImpresoras.textoComboBox.trim(),txtSerieFacturacion.textoInputBox.trim())){

                                                        if(modeloDocumentos.actualizoEstadoDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,"E",txtNombreDeUsuario.textoInputBox.trim(),txtSerieFacturacion.textoInputBox.trim())){


                                                            for(var i=0; i<modeloItemsFactura.count;i++){

                                                                var _stockReal=modeloArticulos.retornaStockTotalArticuloReal(modeloItemsFactura.get(i).codigoArticulo);
                                                                var _cantidadMinimaStockDeArticulo=modeloArticulos.retornaCantidadMinimaAvisoArticulo(modeloItemsFactura.get(i).codigoArticulo);

                                                                if(_stockReal<=_cantidadMinimaStockDeArticulo){

                                                                    modeloArticulos.reemplazaCantidadArticulosSinStock(modeloItemsFactura.get(i).codigoArticulo,"1");
                                                                }else{
                                                                    modeloArticulos.reemplazaCantidadArticulosSinStock(modeloItemsFactura.get(i).codigoArticulo,"0");
                                                                }
                                                            }

                                                            if(cbListaDocumentosCuentaCorrienteConDeuda.visible && cbListaDocumentosCuentaCorrienteConDeuda.retornaCantidadItemSeleccionados()!=0){

                                                                var totalAPagar=0.00;

                                                                if(etiquetaTotal.retornaTotal()==0.00){

                                                                    if(etiquetaTotalMedioDePago.retornaTotal()==0.00){
                                                                        totalAPagar=0.00
                                                                    }else{
                                                                        totalAPagar=etiquetaTotalMedioDePago.retornaTotal()
                                                                    }

                                                                }else{
                                                                    totalAPagar=etiquetaTotal.retornaTotal()
                                                                }




                                                                if(totalAPagar!=0.00){
                                                                    actualizarCuentaCorriente(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion, txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion,cbListaMonedasEnFacturacion.codigoValorSeleccion,totalAPagar,txtSerieFacturacion.textoInputBox.trim())
                                                                }



                                                            }

                                                            txtMensajeInformacion.color="#2f71a0"
                                                            txtMensajeInformacion.text="Documento "+txtNumeroDocumentoFacturacion.textoInputBox.trim()+" emitido correctamente"
                                                            crearNuevaFactura()
                                                            cuadroListaDocumentosNuevo.visible=modeloconfiguracion.retornaModoAvisoDocumentosNuevoVisible();
                                                        }else{
                                                            txtMensajeInformacion.color="#d93e3e"
                                                            txtMensajeInformacion.text="ATENCION: El documento no se guardó como Emitido. Revise la comunicación con el servidor."
                                                        }

                                                    }else{

                                                        txtMensajeInformacion.color="#d93e3e"
                                                        txtMensajeInformacion.text="ATENCION: El documento se guardo correctamente, pero no se pudo emitir. Revise la impresora."
                                                    }

                                                }else{

                                                    for(var i=0; i<modeloItemsFactura.count;i++){

                                                        var _stockReal=modeloArticulos.retornaStockTotalArticuloReal(modeloItemsFactura.get(i).codigoArticulo);
                                                        var _cantidadMinimaStockDeArticulo=modeloArticulos.retornaCantidadMinimaAvisoArticulo(modeloItemsFactura.get(i).codigoArticulo);

                                                        if(_stockReal<=_cantidadMinimaStockDeArticulo){

                                                            modeloArticulos.reemplazaCantidadArticulosSinStock(modeloItemsFactura.get(i).codigoArticulo,"1");
                                                        }else{
                                                            modeloArticulos.reemplazaCantidadArticulosSinStock(modeloItemsFactura.get(i).codigoArticulo,"0");
                                                        }
                                                    }


                                                    if(cbListaDocumentosCuentaCorrienteConDeuda.visible && cbListaDocumentosCuentaCorrienteConDeuda.retornaCantidadItemSeleccionados()!=0){
                                                        var totalAPagar=0.00;

                                                        if(etiquetaTotal.retornaTotal()==0.00){

                                                            if(etiquetaTotalMedioDePago.retornaTotal()==0.00){
                                                                totalAPagar=0.00
                                                            }else{
                                                                totalAPagar=etiquetaTotalMedioDePago.retornaTotal()
                                                            }

                                                        }else{
                                                            totalAPagar=etiquetaTotal.retornaTotal()
                                                        }



                                                        if(totalAPagar!=0.00){
                                                            actualizarCuentaCorriente(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion, txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion,cbListaMonedasEnFacturacion.codigoValorSeleccion,totalAPagar,txtSerieFacturacion.textoInputBox.trim())
                                                        }


                                                    }

                                                    txtMensajeInformacion.color="#2f71a0"
                                                    txtMensajeInformacion.text="El documento "+txtNumeroDocumentoFacturacion.textoInputBox.trim()+" se guardo correctamente"
                                                    crearNuevaFactura()
                                                    cuadroListaDocumentosNuevo.visible=modeloconfiguracion.retornaModoAvisoDocumentosNuevoVisible();

                                                }
                                            }else{
                                                txtMensajeInformacion.color="#d93e3e"
                                                txtMensajeInformacion.text="ATENCION: No se pudieron guardar los medios de pago. Intente nuevamente."
                                            }

                                        }else{
                                            txtMensajeInformacion.color="#d93e3e"
                                            txtMensajeInformacion.text="ATENCION: No se pudo emitir CFE."
                                        }
                                    }else{
                                        txtMensajeInformacion.color="#d93e3e"
                                        txtMensajeInformacion.text="ATENCION: No se pudo actualizar estado de documento a Guardado/Finalizado."
                                    }
                                }else{

                                    txtMensajeInformacion.color="#d93e3e"
                                    txtMensajeInformacion.text="ATENCION: No se pudieron grabar las lineas de factura. Intente nuevamente"
                                }



                            }else{
                                txtMensajeInformacion.color="#d93e3e"
                                txtMensajeInformacion.text="ATENCION: No se pudieron grabar las lineas de factura. Intente nuevamente"
                                funcionesmysql.mensajeAdvertenciaOk("Cuidado, no se puedieron eliminar los articulo, ni guardar los nuevos, intente nuevamente.")
                            }

                        }else if(resultadoInsertDocumento==-1){
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="ATENCION: No se pudo conectar a la base de datos"
                            funcionesmysql.mensajeAdvertenciaOk("Cuidado, el sistema no se pudo conectar a la base de datos.")


                        }else if(resultadoInsertDocumento==-2){
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="ATENCION: Documento existente con estado invalido. Llame al soporte tecnico"


                        }else if(resultadoInsertDocumento==-3){
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="ATENCION: No se pudo guardar el documento"


                        }else if(resultadoInsertDocumento==-4){
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="ATENCION: No se pudo realizar la consulta a la base de datos"


                        }else if(resultadoInsertDocumento==-5){
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="ATENCION: Faltan datos para guardar el documento. Verifique antes de continuar"

                        }
                        else if(resultadoInsertDocumento==-6){
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="ATENCION: El documento ya existe en estado cancelado. Verifique antes de continuar"
                        }
                        else if(resultadoInsertDocumento==-7){
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="ATENCION: El documento ya existe como emitido/impreso/finalizado. Verifique antes de continuar"
                        }
                        else if(resultadoInsertDocumento==-8){
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="ATENCION: El documento ya existe como guardado/finalizado. Verifique antes de continuar"
                        }
                        else if(resultadoInsertDocumento==-9){
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="ATENCION: El documento ya existe en proceso de guardado en otra instancia de Khitomer"
                        }
                        else if(resultadoInsertDocumento==-10){
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="ATENCION: No se realizaron cambios en el documento existente como pendiente"
                        }
                    }else if(resultadoInsertDocumento==-11){
                        /// Esta es la salida para cuando el medio de pago no fue ingresado
                        if(!contenedorFlipable.flipped){
                            btnAgregarMediosDePago.texto="medios de pago"
                            contenedorFlipable.flipped = !contenedorFlipable.flipped
                        }
                    }
                    else if(resultadoInsertDocumento==-12){
                        setearEstadoActivoBotonesGuardar(false)
                        funcionesmysql.mensajeAdvertenciaOk("El cliente no esta habilitado para documentos CRÉDITO.\n\n No se podrá emitir el documento ni guardarlo.")
                    }
                    else{
                        txtMensajeInformacion .visible=true
                        txtMensajeInformacionTimer.stop()
                        txtMensajeInformacionTimer.start()
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: Faltan datos para guardar el documento. Verifique antes de continuar"
                    }



                }
            }

        }

        BotonBarraDeHerramientas {
            id: separador2
            toolTip: ""
            source: ""
            enabled: false
        }



        BotonBarraDeHerramientas {
            id: botonGuardarFacturaPendiente
            rectanguloSecundarioVisible: true
            opacidad: 0.200
            toolTip: "Guardar factura pendiente"
            z: 6
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            onClic: {

                // Verifico si esta visible el checkbox de imprimir envios.
                if(chbImprimirEnvios.visible){
                    // Verifico si el CheckBox de imprimir envios esta marcado.
                    if(chbImprimirEnvios.chekActivo){
                        // Abro el cuadro de dialogo de impresión de envíos.
                        cuadroImprimirEnviosEnFacturacion.visible=true
                    }else{
                        // Guardo la factura pendiente
                        guardarFacturaPendiente()
                    }
                }else{
                    // Guardo la factura pendiente
                    guardarFacturaPendiente()
                }
            }

        }

        BotonBarraDeHerramientas {
            id: separador3
            toolTip: ""
            source: ""
            enabled: false
        }

        BotonBarraDeHerramientas {
            id: botonEliminarFactura
            visible: false
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            toolTip: "Eliminar factura pendiente"
            z: 6
            onClic: {

                if(funcionesmysql.mensajeAdvertencia("Se va a eliminar el documento pendiente.\nDesea proceder?\n\nPresione [ Sí ] para confirmar.")){
                    txtMensajeInformacion .visible=true
                    txtMensajeInformacionTimer.stop()
                    txtMensajeInformacionTimer.start()

                    if(modeloDocumentos.eliminarDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim())){

                        var terminaEliminacionOk=true

                        for(var i=0; i<modeloListaMediosDePagoAgregados.count;i++){

                            if(modeloListaMediosDePagoAgregados.get(i).esDiferido){
                                if(!modeloLineasDePagoListaChequesDiferidosComboBox.actualizarLineaDePagoChequeDiferido(modeloListaMediosDePagoAgregados.get(i).codigoDoc, modeloListaMediosDePagoAgregados.get(i).codigoTipoDoc,  modeloListaMediosDePagoAgregados.get(i).numeroLineaDocumento,"0"+modeloconfiguracion.retornaCantidadDecimalesString()+"",modeloListaMediosDePagoAgregados.get(i).serieDoc)){
                                    terminaEliminacionOk=false
                                }
                            }
                        }

                        if(terminaEliminacionOk){
                            txtMensajeInformacion.color="#2f71a0"
                            txtMensajeInformacion.text="El documento se elimino correctamente"
                            crearNuevaFactura()
                            cuadroListaDocumentosNuevo.visible=modeloconfiguracion.retornaModoAvisoDocumentosNuevoVisible();
                            modeloLineasDePagoListaChequesDiferidosComboBox.limpiarListaLineasDePago()
                            modeloLineasDePagoListaChequesDiferidosComboBox.buscarLineasDePagoChequesDiferidos("1=","1")
                        }else{
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="ATENCION: No se pudo restaurar un cheque diferido"
                        }

                    }else{
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: El documento no puede ser eliminado"
                    }
                }
            }
        }






        BotonBarraDeHerramientas {
            id: botonAnularFactura
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Anular.png"
            visible: false
            toolTip: "Anular documento"
            z: 6
            onClic: {

                if(txtNumeroDocumentoFacturacion.textoInputBox.trim()!="" && cbListatipoDocumentos.codigoValorSeleccion!=""){

                    if(modeloconfiguracion.retornaValorConfiguracion("MODO_AUTORIZACION")=="1"){
                        cuadroAutorizacionFacturacion.evaluarPermisos("permiteAutorizarAnulaciones")
                    }else{
                        cuadroAutorizacionFacturacion.noSeRequierenAutorizaciones("permiteAutorizarAnulaciones")
                    }


                }
            }
        }

        BotonBarraDeHerramientas {
            id: botonReimprimirFactura
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Imprimir.png"
            visible: false
            toolTip: "Reimprimir factura"
            z: 6
            onClic: {
                if(txtNumeroDocumentoFacturacion.textoInputBox.trim()!="" && cbListatipoDocumentos.codigoValorSeleccion!=""){
                    txtMensajeInformacion.visible=true
                    txtMensajeInformacionTimer.stop()
                    txtMensajeInformacionTimer.start()

                    if(modeloDocumentos.emitirDocumentoEnImpresora(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,cbListaImpresoras.textoComboBox.trim(),txtSerieFacturacion.textoInputBox.trim())){
                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text="Documento "+txtNumeroDocumentoFacturacion.textoInputBox.trim()+" emitido correctamente"
                    }else{
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: El documento no pudo ser emitido. Revise la comunicacion con el servidor."
                    }
                }
            }
        }

        BotonBarraDeHerramientas {
            id: botonDevolverFactura
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Devolucion.png"
            toolTip: "Devolver factura"
            visible: false
            z: 6
            onClic: {

                if(funcionesmysql.mensajeAdvertencia("Se va a realizar el documento contrario al que esta visualizando.\nA continuación se mostraran los documentos disponibles.\nDesea proceder?\n\nPresione [ Sí ] para confirmar.")){
                    modeloListaTipoDocumentosParaDevoluciones.limpiarListaTipoDocumentos()
                    if(modeloListaTipoDocumentosParaDevoluciones.permiteDevolucionTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion)){

                        cuadroListaDocumentosDevolucion.visible=true;


                    }
                }

            }

        }

        BotonBarraDeHerramientas {
            id: botonGuardarComentarios
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Comentarios.png"
            toolTip: "Guardar comentario"
            visible: {
                var estadoDocumento=modeloDocumentos.retornacodigoEstadoDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim())
                if((estadoDocumento=="E" || estadoDocumento=="G") && nuevoDocumento==""){
                    txtComentariosFactura.visible
                }else{
                    false
                }
            }

            z: 6
            onClic: {
                var estadoDocumento=modeloDocumentos.retornacodigoEstadoDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim())
                if((estadoDocumento=="E" || estadoDocumento=="G") && nuevoDocumento==""){

                    modeloDocumentos.actualizoComentarios(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim(),txtComentariosFactura.textoInputBox.trim())
                    txtMensajeInformacion.color="#2f71a0"
                    txtMensajeInformacion.text="Comentario actualizado"
                    txtMensajeInformacion.visible=true
                    txtMensajeInformacionTimer.stop()
                    txtMensajeInformacionTimer.start()

                }

                /*if(funcionesmysql.mensajeAdvertencia("Se va a realizar el documento contrario al que esta visualizando.\nA continuación se mostraran los documentos disponibles.\nDesea proceder?\n\nPresione [ Sí ] para confirmar.")){
                    modeloListaTipoDocumentosParaDevoluciones.limpiarListaTipoDocumentos()
                    if(modeloListaTipoDocumentosParaDevoluciones.permiteDevolucionTipoDocumento(cbListatipoDocumentos.codigoValorSeleccion)){

                        cuadroListaDocumentosDevolucion.visible=true;


                    }
                }*/

            }

        }



        Text {
            id: txtMensajeInformacion
            color: "#d93e3e"
            text: qsTr("Información:")
            anchors.verticalCenter: parent.verticalCenter
            font.family: "Arial"
            visible: false
            font.pixelSize:14
            styleColor: "white"
            style: Text.Raised
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            //
        }
    }

    Timer{
        id:txtMensajeInformacionTimer
        repeat: false
        interval: 5000
        onTriggered: {

            txtMensajeInformacion.visible=false
            txtMensajeInformacion.color="#d93e3e"

        }
    }

    Rectangle {
        id: rectColorBarraHerramientas
        x: -4
        y: -1
        width: 10
        color: "#db4d4d"
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: rectContenedor.top
        anchors.bottomMargin: -10
        z: 0
        anchors.leftMargin: 0
        anchors.left: parent.left
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
        id:rectOpcionesExtrasArticulosFacturacionAparecer
        target: rectOpcionesExtrasArticulosFacturacion
        property: "anchors.leftMargin"
        from:-515
        to:-53
        duration: 200
    }

    PropertyAnimation{
        id:rectOpcionesExtrasArticulosFacturacionDesaparecer
        target: rectOpcionesExtrasArticulosFacturacion
        property: "anchors.leftMargin"
        to:-515
        from:-53
        duration: 50
    }

    Rectangle {
        id: rectOpcionesExtras
        x: 5
        y: 9
        width: 450
        color: rectColorBarraHerramientas.color
        radius: 2
        //
        anchors.top: parent.top
        anchors.topMargin: -68

        Keys.onEscapePressed: {

            rectOpcionesExtrasAparecer.stop()
            rectOpcionesExtrasDesaparecer.start()

            rowBarraDeHerramientas.enabled=true

            btnBuscarMasClientes.enabled=true
            btnBuscarMasArticulos.enabled=true


            menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
            txtArticuloParaFacturacion.tomarElFocoP()
        }

        Rectangle {
            id: rectSombraOpcionesExtras
            x: 333
            width: 17
            color: rectColorBarraHerramientas.color
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
            id: mouse_area1
            anchors.fill: parent

            BotonFlecha {
                id: botonflechaCerrarOpcionesAvanzadas
                x: 410
                y: 20
                opacidadRectPrincipal: 0.800
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.rightMargin: 10
                z: 1
                anchors.right: parent.right
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaIzquierda.png"

                onClic: {

                    rectOpcionesExtrasAparecer.stop()
                    rectOpcionesExtrasDesaparecer.start()
                    rowBarraDeHerramientas.enabled=true

                    btnBuscarMasClientes.enabled=true
                    btnBuscarMasArticulos.enabled=true

                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
                    txtArticuloParaFacturacion.tomarElFocoP()
                }
            }

            Rectangle {
                id: rectListasClientesFacturacion
                x: 5
                y: 215
                color: "#64b7b6b6"
                radius: 3
                clip: true
                //
                anchors.top: flowOpcionesExtras.bottom
                anchors.topMargin: 30
                ListView {
                    id: listaClientesEnOpcionesExtraFacturacion
                    clip: true
                    highlightRangeMode: ListView.NoHighlightRange
                    anchors.top: parent.top
                    boundsBehavior: Flickable.DragAndOvershootBounds
                    highlightFollowsCurrentItem: true
                    anchors.right: parent.right
                    delegate: ListaClientesOpcionesExtras {
                    }
                    snapMode: ListView.NoSnap
                    anchors.bottomMargin: 25
                    spacing: 1
                    anchors.bottom: parent.bottom
                    z: 1
                    flickableDirection: Flickable.VerticalFlick
                    anchors.leftMargin: 1
                    keyNavigationWraps: true
                    anchors.left: parent.left
                    interactive: true
                    //
                    anchors.topMargin: 25
                    anchors.rightMargin: 1
                    model: modeloClientesOpcionesExtra

                    Rectangle {
                        id: scrollbarlistaClientesEnOpcionesExtraFacturacion
                        y: listaClientesEnOpcionesExtraFacturacion.visibleArea.yPosition * listaClientesEnOpcionesExtraFacturacion.height+5
                        width: 10
                        color: "#000000"
                        height: listaClientesEnOpcionesExtraFacturacion.visibleArea.heightRatio * listaClientesEnOpcionesExtraFacturacion.height+18
                        radius: 2
                        anchors.right: listaClientesEnOpcionesExtraFacturacion.right
                        anchors.rightMargin: 4
                        z: 1
                        opacity: 0.500
                        visible: true
                        //
                    }
                }

                BotonBarraDeHerramientas {
                    id: botonBajarListaFinal2
                    x: 418
                    y: 579
                    width: 14
                    height: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 3
                    source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                    anchors.bottom: parent.bottom
                    toolTip: ""
                    anchors.bottomMargin: 5
                    rotation: -90
                }

                BotonBarraDeHerramientas {
                    id: botonSubirListaFinal2
                    x: 418
                    y: -190
                    width: 14
                    height: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 3
                    anchors.top: parent.top
                    anchors.topMargin: 5
                    source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                    toolTip: ""
                    rotation: 90
                }
                anchors.bottom: parent.bottom
                anchors.rightMargin: 5
                anchors.bottomMargin: 5
                z: 2
                anchors.right: parent.right
                anchors.leftMargin: 5
                anchors.left: parent.left
            }

            Flow {
                id: flowOpcionesExtras
                x: 10
                y: 60
                height: flowOpcionesExtras.implicitHeight+10
                spacing: 5
                anchors.top: parent.top
                anchors.topMargin: 60
                TextInputSimple {
                    id: txtCodigoClienteFacturacionOpcionesExtras
                    x: 22
                    y: 43
                    //   width: 150
                    inputMask: "000000;"
                    visible: true
                    botonBuscarTextoVisible: true
                    largoMaximo: 6
                    botonBorrarTextoVisible: true
                    textoTitulo: "Cliente/Proveedor:"
                    z: 1
                    colorDeTitulo: "#ffffff"
                    onClicEnBusqueda: {
                        modeloClientesOpcionesExtra.clearClientes()
                        modeloClientesOpcionesExtra.buscarCliente("codigoCliente =",txtCodigoClienteFacturacionOpcionesExtras.textoInputBox)
                    }
                    onEnter: {
                        txtRazonSocialOpcionesExtras.tomarElFoco()
                    }
                    onTabulacion: {
                        txtRazonSocialOpcionesExtras.tomarElFoco()
                    }


                }

                TextInputSimple {
                    id: txtRazonSocialOpcionesExtras
                    x: 22
                    y: 43
                    //     width: 200
                    visible: true
                    botonBuscarTextoVisible: true
                    botonBorrarTextoVisible: true
                    textoTitulo: "Razon social:"
                    z: 1
                    largoMaximo: 30
                    colorDeTitulo: "#ffffff"
                    onClicEnBusqueda: {
                        modeloClientesOpcionesExtra.clearClientes()
                        modeloClientesOpcionesExtra.buscarCliente("razonSocial rlike",txtRazonSocialOpcionesExtras.textoInputBox.trim())
                    }
                    onEnter: {
                        txtNombreOpcionesExtras.tomarElFoco()
                    }
                    onTabulacion: {
                        txtNombreOpcionesExtras.tomarElFoco()
                    }
                }

                TextInputSimple {
                    id: txtNombreOpcionesExtras
                    x: 19
                    y: 52
                    //   width: 200
                    visible: true
                    botonBuscarTextoVisible: true
                    botonBorrarTextoVisible: true
                    textoTitulo: "Nombre:"
                    largoMaximo: 30
                    z: 1
                    colorDeTitulo: "#ffffff"
                    onClicEnBusqueda: {
                        modeloClientesOpcionesExtra.clearClientes()
                        modeloClientesOpcionesExtra.buscarCliente("nombreCliente rlike",txtNombreOpcionesExtras.textoInputBox.trim())
                    }
                    onEnter: {
                        txtRutOpcionesExtras.tomarElFoco()
                    }
                    onTabulacion: {
                        txtRutOpcionesExtras.tomarElFoco()
                    }
                }

                TextInputSimple {
                    id: txtRutOpcionesExtras
                    x: 25
                    y: 57
                    //    width: 200
                    visible: true
                    botonBuscarTextoVisible: true
                    botonBorrarTextoVisible: true
                    textoTitulo: "Documento:"
                    largoMaximo: 15
                    z: 1
                    colorDeTitulo: "#ffffff"
                    onClicEnBusqueda: {
                        modeloClientesOpcionesExtra.clearClientes()
                        modeloClientesOpcionesExtra.buscarCliente("rut rlike",txtRutOpcionesExtras.textoInputBox.trim())
                    }
                    onEnter: {
                        txtDireccionOpcionesExtras.tomarElFoco()
                    }
                    onTabulacion: {
                        txtDireccionOpcionesExtras.tomarElFoco()
                    }
                }

                TextInputSimple {
                    id: txtDireccionOpcionesExtras
                    x: 20
                    y: 51
                    //    width: 200
                    visible: true
                    botonBuscarTextoVisible: true
                    botonBorrarTextoVisible: true
                    largoMaximo: 20
                    textoTitulo: "Dirección:"
                    z: 1
                    colorDeTitulo: "#ffffff"
                    onClicEnBusqueda: {
                        modeloClientesOpcionesExtra.clearClientes()
                        modeloClientesOpcionesExtra.buscarCliente("direccion rlike",txtDireccionOpcionesExtras.textoInputBox.trim())
                    }
                    onEnter: {
                        txtTipoValoracionFacturacion.tomarElFoco()
                    }
                    onTabulacion: {
                        txtTipoValoracionFacturacion.tomarElFoco()
                    }
                }

                ComboBoxListaTipoClasificacion {
                    id: txtTipoValoracionFacturacion
                    width: 200
                    colorTitulo: "#ffffff"
                    botonBuscarTextoVisible: true
                    textoTitulo: "Valoración:"
                    z: 104
                    onClicEnBusqueda: {
                        modeloClientesOpcionesExtra.clearClientes()
                        modeloClientesOpcionesExtra.buscarCliente("tipoClasificacion =",txtTipoValoracionFacturacion.codigoValorSeleccion)
                    }

                }
                visible: true
                anchors.rightMargin: 10
                z: 3
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.left: parent.left
            }

            BotonPaletaSistema {
                id: btnFiltrarClientesFacturacion
                x: 379
                y: 188
                text: "Filtrar"
                anchors.bottom: rectListasClientesFacturacion.top
                anchors.rightMargin: 10
                visible: true
                anchors.bottomMargin: 5
                anchors.right: parent.right

                onClicked: {

                    var consultaSql="";

                    if(txtCodigoClienteFacturacionOpcionesExtras.textoInputBox.trim()!=""){
                        consultaSql+="codigoCliente rlike '"+txtCodigoClienteFacturacionOpcionesExtras.textoInputBox.trim()+"' and ";
                    }
                    if(txtRazonSocialOpcionesExtras.textoInputBox.trim()!=""){
                        consultaSql+="razonSocial rlike '"+txtRazonSocialOpcionesExtras.textoInputBox.trim()+"' and "
                    }
                    if(txtNombreOpcionesExtras.textoInputBox.trim()!=""){
                        consultaSql+="nombreCliente rlike '"+txtNombreOpcionesExtras.textoInputBox.trim()+"' and "
                    }
                    if(txtRutOpcionesExtras.textoInputBox.trim()!=""){
                        consultaSql+="rut rlike '"+txtRutOpcionesExtras.textoInputBox.trim()+"' and "
                    }
                    if(txtDireccionOpcionesExtras.textoInputBox.trim()!=""){
                        consultaSql+="direccion rlike '"+txtDireccionOpcionesExtras.textoInputBox.trim()+"' and "
                    }
                    if(txtTipoValoracionFacturacion.codigoValorSeleccion.trim()!=""){
                        consultaSql+="tipoClasificacion = '"+txtTipoValoracionFacturacion.codigoValorSeleccion.trim()+"' and "
                    }
                    if(consultaSql!=""){
                        modeloClientesOpcionesExtra.clearClientes()
                        modeloClientesOpcionesExtra.buscarCliente(consultaSql,"1=1")
                    }
                }
            }

            Text {
                id: txtTituloOpcionesExtras
                x: 20
                y: 10
                color: "#ffffff"
                text: qsTr("filtros de clientes")
                font.family: "Arial"
                font.pixelSize: 23
                anchors.top: parent.top
                anchors.topMargin: 10
                font.underline: false
                visible: true
                font.italic: false
                font.bold: true
                anchors.leftMargin: 20
                anchors.left: parent.left
            }
        }
        anchors.bottom: parent.bottom
        visible: true
        anchors.bottomMargin: -5
        z: 6
        anchors.leftMargin: -515
        anchors.left: parent.left
    }

    Rectangle {
        id: rectOpcionesExtrasArticulosFacturacion
        x: 11
        y: 9
        width: 450
        color: "#27acb3"
        radius: 2
        //
        anchors.top: parent.top
        anchors.topMargin: -68


        Keys.onEscapePressed: {

            rectOpcionesExtrasArticulosFacturacionAparecer.stop()
            rectOpcionesExtrasArticulosFacturacionDesaparecer.start()

            rowBarraDeHerramientas.enabled=true
            btnBuscarMasClientes.enabled=true
            btnBuscarMasArticulos.enabled=true


            menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
            txtArticuloParaFacturacion.tomarElFocoP()
        }

        Rectangle {
            id: rectSombraOpcionesExtras1
            x: 333
            width: 17
            color: "#27acb3"
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

            Flow {
                id: flowOpcionesExtras1
                x: 10
                y: 60
                height: flowOpcionesExtras1.implicitHeight+10
                flow: Qt.LeftToRight
                layoutDirection: Qt.LeftToRight
                spacing: 5
                anchors.top: parent.top
                anchors.topMargin: 60
                TextInputSimple {
                    id: txtCodigoArticuloOpcionesExtrasFacturacion
                    x: 22
                    y: 43
                    //    width: 280
                    enFocoSeleccionarTodo: true
                    visible: true
                    botonBuscarTextoVisible: true
                    largoMaximo: 30
                    botonBorrarTextoVisible: true
                    textoTitulo: "Código:"
                    z: 1
                    colorDeTitulo: "#ffffff"
                    onClicEnBusqueda: {

                        var valorArticuloInterno=modeloArticulosOpcionesExtraFacturacion.existeArticulo(txtCodigoArticuloOpcionesExtrasFacturacion.textoInputBox.trim());

                        if(valorArticuloInterno!=""){

                            txtCodigoArticuloOpcionesExtrasFacturacion.textoInputBox=valorArticuloInterno
                            modeloArticulosOpcionesExtraFacturacion.clearArticulos()
                            modeloArticulosOpcionesExtraFacturacion.buscarArticulo("codigoArticulo rlike",txtCodigoArticuloOpcionesExtrasFacturacion.textoInputBox,1)

                        }

                    }
                    onEnter: {

                        var valorArticuloInterno=modeloArticulosOpcionesExtraFacturacion.existeArticulo(txtCodigoArticuloOpcionesExtrasFacturacion.textoInputBox.trim());

                        if(valorArticuloInterno!=""){

                            txtCodigoArticuloOpcionesExtrasFacturacion.textoInputBox=valorArticuloInterno
                            modeloArticulosOpcionesExtraFacturacion.clearArticulos()
                            modeloArticulosOpcionesExtraFacturacion.buscarArticulo("codigoArticulo rlike",txtCodigoArticuloOpcionesExtrasFacturacion.textoInputBox,1)

                        }

                        txtDescripcionArticuloOpcionesExtrasFacturacion.tomarElFoco()
                    }
                    onTabulacion: {
                        txtDescripcionArticuloOpcionesExtrasFacturacion.tomarElFoco()
                    }
                }

                TextInputSimple {
                    id: txtDescripcionArticuloOpcionesExtrasFacturacion
                    x: 22
                    y: 43
                    //   width: 280
                    visible: true
                    botonBuscarTextoVisible: true
                    botonBorrarTextoVisible: true
                    textoTitulo: "Nombre:"
                    z: 1
                    largoMaximo: 20
                    colorDeTitulo: "#ffffff"
                    onClicEnBusqueda: {
                        modeloArticulosOpcionesExtraFacturacion.clearArticulos()
                        modeloArticulosOpcionesExtraFacturacion.buscarArticulo("descripcionArticulo rlike",txtDescripcionArticuloOpcionesExtrasFacturacion.textoInputBox.trim(),1)
                    }
                    onEnter: {
                        cbxListaProveedoresOpcionesExtraFacturacion.tomarElFoco()
                    }
                    onTabulacion: {
                        cbxListaProveedoresOpcionesExtraFacturacion.tomarElFoco()
                    }
                }

                ComboBoxListaProveedores {
                    id: cbxListaProveedoresOpcionesExtraFacturacion
                    x: 22
                    y: 56
                    width: 280
                    colorTitulo: "#ffffff"
                    visible: true
                    botonBuscarTextoVisible: true
                    textoTitulo: "Proveedor:"
                    z: 2
                    onClicEnBusqueda: {
                        modeloArticulosOpcionesExtraFacturacion.clearArticulos()
                        modeloArticulosOpcionesExtraFacturacion.buscarArticulo("codigoProveedor rlike",cbxListaProveedoresOpcionesExtraFacturacion.codigoValorSeleccion.trim(),1)
                    }
                    onEnter: {

                        txtCodigoArticuloOpcionesExtrasFacturacion.tomarElFoco()
                    }
                    onTabulacion: {

                        txtCodigoArticuloOpcionesExtrasFacturacion.tomarElFoco()
                    }

                }

                CheckBox {
                    id: chbIncluirArticulosInactivos
                    textoValor: "Incluir inactivos"
                }
                visible: true
                anchors.rightMargin: 10
                z: 3
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.left: parent.left
            }

            Rectangle {
                id: rectArticulosFacturacion
                x: 5
                y: 175
                color: "#64b9b7b7"
                radius: 3
                visible: true
                //
                anchors.top: flowOpcionesExtras1.bottom
                anchors.topMargin: 30
                ListView {
                    id: listaArticulosEnOpcionesExtraFacturacion
                    x: 2
                    y: 91
                    clip: true
                    highlightRangeMode: ListView.NoHighlightRange
                    anchors.top: parent.top
                    boundsBehavior: Flickable.DragAndOvershootBounds
                    highlightFollowsCurrentItem: true
                    anchors.right: parent.right
                    delegate: ListaArticulosOpcionesExtrasFacturacion {

                    }
                    snapMode: ListView.NoSnap
                    anchors.bottomMargin: 24
                    spacing: 1
                    anchors.bottom: parent.bottom
                    z: 1
                    flickableDirection: Flickable.VerticalFlick
                    anchors.leftMargin: 2
                    keyNavigationWraps: true
                    anchors.left: parent.left
                    interactive: true
                    //
                    anchors.topMargin: 110
                    anchors.rightMargin: 0
                    model: modeloArticulosOpcionesExtraFacturacion

                    Rectangle {
                        id: scrollbarlistaArticulosEnOpcionesExtraFacturacion
                        y: listaArticulosEnOpcionesExtraFacturacion.visibleArea.yPosition * listaArticulosEnOpcionesExtraFacturacion.height+5
                        width: 10
                        color: "#000000"
                        height: listaArticulosEnOpcionesExtraFacturacion.visibleArea.heightRatio * listaArticulosEnOpcionesExtraFacturacion.height+18
                        radius: 2
                        anchors.right: listaArticulosEnOpcionesExtraFacturacion.right
                        anchors.rightMargin: 4
                        z: 1
                        opacity: 0.500
                        visible: true
                        //
                    }
                }

                BotonPaletaSistema {
                    id: btnAgregarArticuloAFactura
                    text: "Agregar artículo"
                    anchors.top: parent.top
                    anchors.topMargin: 53
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    onClicked: {

                        funcionesmysql.loguear("QML::btnAgregarArticuloAFactura::onClicked")

                        ///Chequeo que modo de calculo de total esta seteado
                        var modoCalculoTotal=modeloconfiguracion.retornaValorConfiguracion("MODO_CALCULOTOTAL");


                        if(txtCantidadArticulosFacturacion.visible){

                            funcionesmysql.loguear("QML::txtCantidadArticulosFacturacion.visible")


                            if(modeloArticulos.retornaArticuloActivo(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")){

                                funcionesmysql.loguear("QML::modeloArticulos.retornaArticuloActivo(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,utilizaArticulosInactivos)")
                                txtArticuloParaFacturacion.textoInputBox=txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()
                                valorArticuloInterno=txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()
                                funcionesmysql.loguear("QML::valorArticuloInterno: "+valorArticuloInterno)
                                rectOpcionesExtrasArticulosFacturacionAparecer.stop()
                                rectOpcionesExtrasArticulosFacturacionDesaparecer.start()
                                rowBarraDeHerramientas.enabled=true

                                btnBuscarMasClientes.enabled=true
                                btnBuscarMasArticulos.enabled=true

                                menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                                txtCantidadArticulosFacturacion.tomarElFoco()

                            }else{
                                funcionesmysql.loguear("QML::ERROR::modeloArticulos.retornaArticuloActivo(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,utilizaArticulosInactivos)")
                                mensajeError("Artículo "+txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()+" inactivo.")
                            }

                        }else if(txtCodigoDeBarrasADemanda.visible){
                            funcionesmysql.loguear("QML::txtCodigoDeBarrasADemanda.visible")


                            if(modeloArticulos.retornaArticuloActivo(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")){

                                funcionesmysql.loguear("QML::modeloArticulos.retornaArticuloActivo(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,utilizaArticulosInactivos)")

                                txtCodigoDeBarrasADemanda.textoInputBox=""
                                txtArticuloParaFacturacion.textoInputBox=txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()
                                valorArticuloInterno=txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()

                                funcionesmysql.loguear("QML::valorArticuloInterno: "+valorArticuloInterno)

                                rectOpcionesExtrasArticulosFacturacionAparecer.stop()
                                rectOpcionesExtrasArticulosFacturacionDesaparecer.start()
                                rowBarraDeHerramientas.enabled=true

                                btnBuscarMasClientes.enabled=true
                                btnBuscarMasArticulos.enabled=true

                                menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                                txtCodigoDeBarrasADemanda.tomarElFoco()

                            }else{
                                funcionesmysql.loguear("QML::ERROR::modeloArticulos.retornaArticuloActivo(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,utilizaArticulosInactivos)")
                                mensajeError("Artículo "+txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()+" inactivo.")
                            }


                        }/*else if(!txtCodigoDeBarrasADemanda.visible && txtCantidadArticulosFacturacion.visible){

                            if(modeloArticulos.retornaArticuloActivo(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")){

                                txtArticuloParaFacturacion.textoInputBox=txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()
                                valorArticuloInterno=txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()
                                rectOpcionesExtrasArticulosFacturacionAparecer.stop()
                                rectOpcionesExtrasArticulosFacturacionDesaparecer.start()
                                rowBarraDeHerramientas.enabled=true

                                btnBuscarMasClientes.enabled=true
                                btnBuscarMasArticulos.enabled=true

                                menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarMenuAvanzado")

                                txtCantidadArticulosFacturacion.tomarElFoco()

                            }else{
                                mensajeError("Artículo "+txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()+" inactivo.")
                            }

                        }*/else{


                            if(txtArticuloParaFacturacion.visible &&  txtCodigoArticuloParaAgregarFacturacion.textoInputBox!="" && txtPrecioArticuloAgregarFacturacion.textoInputBox.trim()!=""+modeloconfiguracion.retornaCantidadDecimalesString()+"" && !superaCantidadMaximaLineasDocumento()){

                                if(modeloArticulos.retornaArticuloActivo(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()) || modeloListaTipoDocumentosComboBox.retornaPermisosDelDocumento(cbListatipoDocumentos.codigoValorSeleccion,"utilizaArticulosInactivos")){
                                    var cotizacion=1;
                                    valorPrecioArticulo=txtPrecioArticuloAgregarFacturacion.textoInputBox.trim()

                                    funcionesmysql.loguear("QML::valorPrecioArticulo: "+valorPrecioArticulo)



                                    if(modeloListaMonedas.retornaCodigoMoneda(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim())!=cbListaMonedasEnFacturacion.codigoValorSeleccion){

                                        if(modeloListaMonedas.retornaMonedaReferenciaSistema()==modeloListaMonedas.retornaCodigoMoneda(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim())){
                                            cotizacion=modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                            valorPrecioArticulo=txtPrecioArticuloAgregarFacturacion.textoInputBox.trim()/cotizacion

                                            funcionesmysql.loguear("QML::valorPrecioArticulo: "+valorPrecioArticulo)

                                        }else{

                                            if(cbListaMonedasEnFacturacion.codigoValorSeleccion==modeloListaMonedas.retornaMonedaReferenciaSistema()){
                                                cotizacion=modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()))
                                                valorPrecioArticulo=txtPrecioArticuloAgregarFacturacion.textoInputBox.trim()*cotizacion
                                                funcionesmysql.loguear("QML::valorPrecioArticulo: "+valorPrecioArticulo)
                                            }else{
                                                valorPrecioArticulo2=(txtPrecioArticuloAgregarFacturacion.textoInputBox.trim()*modeloListaMonedas.retornaCotizacionMoneda(modeloListaMonedas.retornaCodigoMoneda(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim())))/modeloListaMonedas.retornaCotizacionMoneda(cbListaMonedasEnFacturacion.codigoValorSeleccion)
                                                funcionesmysql.loguear("QML::valorPrecioArticulo2: "+valorPrecioArticulo2)
                                            }


                                        }
                                    }


                                    //Controlo si se peude vender sin stock previsto
                                    if(modeloArticulos.retornaSiPuedeVenderSinStock(1,cbListatipoDocumentos.codigoValorSeleccion,txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim(),retornaCantidadDeUnArticuloEnFacturacion(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim())   )){

                                        costoArticulo=txtCostoArticuloMonedaReferencia.textoInputBox.trim();

                                        funcionesmysql.loguear("QML::costoArticulo: "+costoArticulo)

                                        //costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                        //txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""


                                        funcionesmysql.loguear("QML::modeloItemsFactura.append:")
                                        funcionesmysql.loguear("QML::codigoArticulo: "+txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim())

                                        funcionesmysql.loguear("QML::precioArticulo: "+valorPrecioArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
                                        funcionesmysql.loguear("QML::costoArticuloMonedaReferencia: "+costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))


                                        modeloItemsFactura.append({
                                                                      codigoArticulo:txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim(),
                                                                      codigoBarrasArticulo:"",
                                                                      descripcionArticulo:modeloArticulos.retornaDescripcionArticulo(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()),
                                                                      descripcionArticuloExtendido:modeloArticulos.retornaDescripcionArticuloExtendida(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()),
                                                                      precioArticulo:valorPrecioArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                      precioArticuloSubTotal:valorPrecioArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                      cantidadItems:1,
                                                                      costoArticuloMonedaReferencia:costoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),
                                                                      activo:true,
                                                                      consideraDescuento:false,
                                                                      indiceLinea:-1,
                                                                      descuentoLineaItem:0,
                                                                      codigoTipoGarantia:modeloArticulos.retornaCodigoTipoGarantia(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()),
                                                                      descripcionTipoGarantia:modeloTipoGarantia.retornaDescripcionTipoGarantia(modeloArticulos.retornaCodigoTipoGarantia(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim())),
                                                                      asignarGarantiaAArticulo:false
                                                                  })

                                        listaDeItemsFactura.positionViewAtIndex(listaDeItemsFactura.count-1,0)

                                        txtCostoArticuloMonedaReferencia.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""

                                        if(modoCalculoTotal=="1"){
                                            etiquetaTotal.setearTotal(valorPrecioArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                        }else if(modoCalculoTotal=="2"){
                                            etiquetaTotal.setearTotalModoArticuloSinIva(valorPrecioArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")),txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,false,listaDeItemsFactura.count-1)
                                        }

                                        mostrarCuadroDeActulizacionDePrecioEnFacturacion(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim(),"LATERAL")



                                    }
                                }else{
                                    mensajeError("Artículo "+txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()+" inactivo.")
                                }

                            }
                        }

                    }

                }

                TextInputSimple {
                    id: txtCodigoArticuloParaAgregarFacturacion
                    //  width: 120
                    height: 35
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.top: parent.top
                    anchors.topMargin: 3
                    enable: false
                    textoInputBox: ""
                    enFocoSeleccionarTodo: true
                    visible: true
                    botonBuscarTextoVisible: false
                    largoMaximo: 6
                    botonBorrarTextoVisible: false
                    textoTitulo: "Código artículo:"
                    z: 1
                    colorDeTitulo: "#ffffff"
                }

                ComboBoxListaPrecios {
                    id: cbListaDePreciosFacturacionOpcionesExtras
                    width: 230
                    colorTitulo: "#ffffff"
                    anchors.top: parent.top
                    anchors.topMargin: 45
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    textoTitulo: "Listas de precio:"
                    z: 104

                    onSenialAlAceptarOClick: {


                        if(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim()!=""){


                            txtPrecioArticuloAgregarFacturacion.textoInputBox= modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(txtCodigoArticuloParaAgregarFacturacion.textoInputBox.trim(),cbListaDePreciosFacturacionOpcionesExtras.codigoValorSeleccion)

                        }


                    }

                }

                TextInputSimple {
                    id: txtPrecioArticuloAgregarFacturacion
                    y: -1
                    //    width: 150
                    enable: false
                    botonBorrarTextoVisible: false
                    enFocoSeleccionarTodo: false
                    textoInputBox: ""+modeloconfiguracion.retornaCantidadDecimalesString()+""
                    anchors.top: parent.top
                    anchors.topMargin: 3
                    botonBuscarTextoVisible: false
                    inputMask: "00000000"+modeloconfiguracion.retornaCantidadDecimalesString()+";"
                    largoMaximo: 45
                    textoTitulo: "Precio:"
                    anchors.leftMargin: 5
                    anchors.left: txtCodigoArticuloParaAgregarFacturacion.right
                    colorDeTitulo: "#ffffff"
                }

                BotonBarraDeHerramientas {
                    id: botonBajarListaFinal3
                    x: 415
                    y: 613
                    width: 14
                    height: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 3
                    source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                    anchors.bottom: parent.bottom
                    toolTip: ""
                    anchors.bottomMargin: 5
                    rotation: -90
                }

                BotonBarraDeHerramientas {
                    id: botonSubirListaFinal3
                    x: 415
                    y: 160
                    width: 14
                    height: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 3
                    anchors.top: parent.top
                    anchors.topMargin: 90
                    source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                    toolTip: ""
                    rotation: 90
                }
                anchors.bottom: parent.bottom
                anchors.rightMargin: 5
                anchors.bottomMargin: 5
                z: 2
                anchors.right: parent.right
                anchors.leftMargin: 5
                anchors.left: parent.left
            }

            Text {
                id: lblInformacionOpcionesExtraFacturacion
                x: 10
                y: 155
                color: "#2b2a2a"
                text: qsTr("Doble-clic para agregar artículos a la venta.")
                font.pixelSize: 12
                font.family: "Arial"
                anchors.left: parent.left
                anchors.leftMargin: 10
                //
                anchors.bottom: rectArticulosFacturacion.top
                anchors.bottomMargin: 5
            }

            BotonPaletaSistema {
                id: btnFiltrarArticuloFacturacion
                x: 379
                y: 148
                text: "Filtrar"
                border.color: "#787777"
                anchors.bottom: rectArticulosFacturacion.top
                anchors.rightMargin: 10
                visible: true
                anchors.bottomMargin: 5
                anchors.right: parent.right
                onClicked: {

                    var consultaSql="";

                    if(txtCodigoArticuloOpcionesExtrasFacturacion.textoInputBox.trim()!=""){
                        consultaSql+=" codigoArticulo rlike '"+txtCodigoArticuloOpcionesExtrasFacturacion.textoInputBox.trim()+"' and ";
                    }
                    if(txtDescripcionArticuloOpcionesExtrasFacturacion.textoInputBox.trim()!=""){
                        consultaSql+=" descripcionArticulo rlike '"+txtDescripcionArticuloOpcionesExtrasFacturacion.textoInputBox.trim()+"' and "
                    }
                    if(cbxListaProveedoresOpcionesExtraFacturacion.codigoValorSeleccion.trim()!=""){
                        consultaSql+=" codigoProveedor rlike '"+cbxListaProveedoresOpcionesExtraFacturacion.codigoValorSeleccion.trim()+"' and "
                    }
                    if(!chbIncluirArticulosInactivos.chekActivo){
                        consultaSql+=" activo=1  and "
                    }

                    if(consultaSql!=""){
                        modeloArticulosOpcionesExtraFacturacion.clearArticulos()
                        modeloArticulosOpcionesExtraFacturacion.buscarArticulo(consultaSql,"1=1",1)
                    }
                }
            }

            Text {
                id: txtTituloOpcionesExtrasArticulosFacturacion
                x: 20
                y: 10
                color: "#ffffff"
                text: qsTr("filtros de artículos")
                font.family: "Arial"
                font.pixelSize: 23
                anchors.top: parent.top
                anchors.topMargin: 10
                font.underline: false
                visible: true
                font.italic: false
                font.bold: true
                anchors.leftMargin: 20
                anchors.left: parent.left
            }

            BotonFlecha {
                id: botonflechaCerrarOpcionesAvanzadasArticulosFacturacion
                x: 410
                y: 20
                border.color: "#ffffff"
                opacidadRectPrincipal: 0.800
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.rightMargin: 10
                z: 1
                anchors.right: parent.right
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaIzquierda.png"
                onClic: {

                    rectOpcionesExtrasArticulosFacturacionAparecer.stop()
                    rectOpcionesExtrasArticulosFacturacionDesaparecer.start()
                    rowBarraDeHerramientas.enabled=true

                    btnBuscarMasClientes.enabled=true
                    btnBuscarMasArticulos.enabled=true


                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
                    txtArticuloParaFacturacion.tomarElFocoP()



                }

            }
        }
        anchors.bottom: parent.bottom
        visible: true
        anchors.bottomMargin: -5
        z: 6
        anchors.leftMargin: -515
        anchors.left: parent.left
    }

    CuadroListaDocumentos{
        id:cuadroListaDocumentosDevolucion
        anchors.fill: parent
        z:9
        visible: false
        onClicCancelar: cuadroListaDocumentosDevolucion.visible=false
        modeloItems: modeloListaTipoDocumentosParaDevoluciones
        textoBoton:  "Cancelar documento contrario"
        onTipoDocumentoSeleccionado: {

            var _codigoTipoDocumentoOriginal=cbListatipoDocumentos.codigoValorSeleccion
            var _numeroDocumento=txtNumeroDocumentoFacturacion.textoInputBox.trim()
            var _serieDocumento=txtSerieFacturacion.textoInputBox.trim()
            var _codigoTipoDocumentoSeleccionadoParaDevolucion=_codigoTipoDocumentoSeleccionado
            var _tipoCliente=txtTipoClienteFacturacion.codigoValorSeleccion
            cuadroListaDocumentosDevolucion.visible=false


            setearTipoDeDocumento(_codigoTipoDocumentoSeleccionadoParaDevolucion,"")
            setearDocumento()
            crearNuevaFactura()


            tipoDocumentoCFEADevolver=_codigoTipoDocumentoOriginal;
            numeroDocumentoCFEADevolver= modeloDocumentos.retornaNumeroCFEOriginal(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento);
            fechaDocumentoCFEADevolver= modeloDocumentos.retornafechaEmisionDocumento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento);

            if(txtNumeroDocumentoFacturacion.visible && txtNumeroDocumentoFacturacion.textoInputBox==""){
                txtNumeroDocumentoFacturacion.textoInputBox=modeloDocumentos.retornoCodigoUltimoDocumentoDisponible(_codigoTipoDocumentoSeleccionadoParaDevolucion)
            }



            cargarFactura(_numeroDocumento,_codigoTipoDocumentoOriginal,"P",
                          _tipoCliente,modeloDocumentos.retornacodigoClienteDocumento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento),
                          _serieDocumento,
                          modeloDocumentos.retornacodigoVendedorComisionaDocumento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento),
                          "","",modeloDocumentos.retornafechaEmisionDocumento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento),
                          "",modeloDocumentos.retornacodigoMonedaDocumento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento),
                          modeloDocumentos.retornaprecioIvaVentaDocumento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento),
                          modeloDocumentos.retornaprecioSubTotalVentaDocumento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento),
                          modeloDocumentos.retornaprecioTotalVentaDocumento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento),
                          modeloDocumentos.retornatotalIva1Documento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento),
                          modeloDocumentos.retornatotalIva2Documento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento),
                          modeloDocumentos.retornatotalIva3Documento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento),
                          "",modeloDocumentos.retornaonumeroCuentaBancariaDocumento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento),
                          modeloDocumentos.retornaocodigoBancoDocumento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento),
                          modeloDocumentos.retornaMontoDescuentoTotalDocumento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento),
                          "",modeloDocumentos.retornaPorcentajeDescuentoAlTotalDocumento(_numeroDocumento,_codigoTipoDocumentoOriginal,_serieDocumento),"NUEVO",_codigoTipoDocumentoSeleccionadoParaDevolucion,
                          ""
                          )
        }
    }


    CuadroListaDocumentos{
        id:cuadroListaDocumentosNuevo
        anchors.fill: parent
        z:9
        visible: modeloconfiguracion.retornaModoAvisoDocumentosNuevoVisible();
        onClicCancelar: cuadroListaDocumentosNuevo.visible=false
        modeloItems: modeloListaTipoDocumentosComboBox
        textoBoton:  "Cerrar lista de documentos"
        onTipoDocumentoSeleccionado: {

            var _codigoTipoDocumentoSeleccionadoParaDevolucion=_codigoTipoDocumentoSeleccionado
            cuadroListaDocumentosNuevo.visible=false

            setearTipoDeDocumento(_codigoTipoDocumentoSeleccionadoParaDevolucion,"")
            setearDocumento()
            crearNuevaFactura()

            if(txtNumeroDocumentoFacturacion.visible && txtNumeroDocumentoFacturacion.textoInputBox==""){
                txtNumeroDocumentoFacturacion.textoInputBox=modeloDocumentos.retornoCodigoUltimoDocumentoDisponible(_codigoTipoDocumentoSeleccionadoParaDevolucion)
            }

        }
    }


    CuadroListaGarantias{
        id:cuadroListaGarantias
        anchors.fill: parent
        z:9
        visible: false
        onClicCancelar: cuadroListaGarantias.visible=false
        modeloItems: modeloTipoGarantia
        textoBoton:  "Cerrar"
        onSendInformacion: {
            modeloItemsFactura.set(index,{"codigoTipoGarantia": id,"descripcionTipoGarantia": nombre,"asignarGarantiaAArticulo":check})
            cuadroListaGarantias.visible=false

        }
    }


    CuadroListaArticulosEnListaDePrecio{
        id:cuadroListaArticulosACambiarElPrecio
        anchors.fill: parent
        z:9
        visible: false

        onClicActualizar: {
            rowBarraDeHerramientas.enabled=true
            btnBuscarMasClientes.enabled=true
            btnBuscarMasArticulos.enabled=true
            visible=false
        }
        onPrecionarEscape: {
            rowBarraDeHerramientas.enabled=true
            btnBuscarMasClientes.enabled=true
            btnBuscarMasArticulos.enabled=true
            visible=false
        }


    }

    CuadroAsignacionDatosExtraLineaFacturacion{
        id:cuadroDatosACambiarLineaFacturacion
        anchors.fill: parent
        z:9
        visible: false
        onPrecionarEscape: {
            rowBarraDeHerramientas.enabled=true
            btnBuscarMasClientes.enabled=true
            btnBuscarMasArticulos.enabled=true
            visible=false
        }
        onConfirmacion: {

            if(valorDato==nuevoValorDato){
                rowBarraDeHerramientas.enabled=true
                btnBuscarMasClientes.enabled=true
                btnBuscarMasArticulos.enabled=true
                visible=false
            }else{

                modeloItemsFactura.setProperty(indiceDeLineaDocumento,"codigoBarrasArticulo",nuevoValorDato)
                var datoNuevoActualizado=true

                if(lblEstadoDocumento.text.trim()=="Emitido" || lblEstadoDocumento.text.trim()=="Guardado"){


                    if(!modeloDocumentos.actualizarDatoExtraLineaDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion.trim(),indiceDeLineaDocumento,nuevoValorDato,txtSerieFacturacion.textoInputBox.trim())){
                        datoNuevoActualizado=false
                    }
                }

                if(datoNuevoActualizado){
                    rowBarraDeHerramientas.enabled=true
                    btnBuscarMasClientes.enabled=true
                    btnBuscarMasArticulos.enabled=true
                    visible=false
                }else{

                    mostrarErrorCuadroDatosExtra()

                }

            }

        }
    }







    CuadroAutorizaciones{
        id:cuadroAutorizacionFacturacion
        color: "#be231919"
        z: 9
        anchors.fill: parent
        onConfirmacion: {



            if(permisosAEvaluar=="permiteAutorizarAnulaciones"){
                txtMensajeInformacion .visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()
                var terminaAnulacionOk=true
                for(var i=0; i<modeloListaMediosDePagoAgregados.count;i++){
                    if(modeloLineasDePagoListaChequesDiferidosComboBox.verificaMedioPagoEstaUtilizado(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion, i.toString(),txtSerieFacturacion.textoInputBox.trim())){
                        terminaAnulacionOk=false
                    }
                }
                if(terminaAnulacionOk && modeloDocumentos.actualizoEstadoDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,"C",txtNombreDeUsuario.textoInputBox.trim(),txtSerieFacturacion.textoInputBox.trim())){

                    for(var j=0; j<modeloListaMediosDePagoAgregados.count;j++){
                        if(!modeloLineasDePagoListaChequesDiferidosComboBox.actualizarLineaDePagoChequeDiferido(modeloListaMediosDePagoAgregados.get(j).codigoDoc, modeloListaMediosDePagoAgregados.get(j).codigoTipoDoc,  modeloListaMediosDePagoAgregados.get(j).numeroLineaDocumento,"0"+modeloconfiguracion.retornaCantidadDecimalesString()+"",modeloListaMediosDePagoAgregados.get(j).serieDoc)){
                            terminaAnulacionOk=false
                        }
                    }
                    if(terminaAnulacionOk){
                        if(!modeloDocumentosConSaldoCuentaCorriente.anuloMontosDebitadosCuentaCorriente(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim())){
                            terminaAnulacionOk=false;
                        }
                    }

                    if(terminaAnulacionOk){


                        for(var i=0; i<modeloItemsFactura.count;i++){

                            var _stockReal=modeloArticulos.retornaStockTotalArticuloReal(modeloItemsFactura.get(i).codigoArticulo);
                            var _cantidadMinimaStockDeArticulo=modeloArticulos.retornaCantidadMinimaAvisoArticulo(modeloItemsFactura.get(i).codigoArticulo);

                            if(_stockReal<=_cantidadMinimaStockDeArticulo){

                                modeloArticulos.reemplazaCantidadArticulosSinStock(modeloItemsFactura.get(i).codigoArticulo,"1");
                            }else{
                                modeloArticulos.reemplazaCantidadArticulosSinStock(modeloItemsFactura.get(i).codigoArticulo,"0");
                            }
                        }



                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text="Documento "+txtNumeroDocumentoFacturacion.textoInputBox.trim()+" anulado correctamente"
                        crearNuevaFactura()
                        cuadroListaDocumentosNuevo.visible=modeloconfiguracion.retornaModoAvisoDocumentosNuevoVisible();
                        modeloLineasDePagoListaChequesDiferidosComboBox.limpiarListaLineasDePago()
                        modeloLineasDePagoListaChequesDiferidosComboBox.buscarLineasDePagoChequesDiferidos("1=","1")
                    }else{
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: No pudieron anularse los cheques."
                    }


                }else{
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="ATENCION: El documento no pudo ser anulado."
                }
            }else if(permisosAEvaluar=="permiteAutorizarDescuentosTotal"){

                rectContenedor.enabled=true
                txtArticuloParaFacturacion.tomarElFocoP()
                recalcularTotales()
            }
        }
        onNoRequiereAutorizacion: {
            if(permisosAEvaluar=="permiteAutorizarAnulaciones"){
                txtMensajeInformacion .visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()
                var terminaAnulacionOk=true
                for(var i=0; i<modeloListaMediosDePagoAgregados.count;i++){
                    if(modeloLineasDePagoListaChequesDiferidosComboBox.verificaMedioPagoEstaUtilizado(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion, i.toString(),txtSerieFacturacion.textoInputBox.trim())){
                        terminaAnulacionOk=false
                    }
                }
                if(terminaAnulacionOk && modeloDocumentos.actualizoEstadoDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,"C",txtNombreDeUsuario.textoInputBox.trim(),txtSerieFacturacion.textoInputBox.trim())){

                    for(var j=0; j<modeloListaMediosDePagoAgregados.count;j++){
                        if(!modeloLineasDePagoListaChequesDiferidosComboBox.actualizarLineaDePagoChequeDiferido(modeloListaMediosDePagoAgregados.get(j).codigoDoc, modeloListaMediosDePagoAgregados.get(j).codigoTipoDoc,  modeloListaMediosDePagoAgregados.get(j).numeroLineaDocumento,"0"+modeloconfiguracion.retornaCantidadDecimalesString()+"",modeloListaMediosDePagoAgregados.get(j).serieDoc)){
                            terminaAnulacionOk=false
                        }
                    }
                    if(terminaAnulacionOk){
                        if(!modeloDocumentosConSaldoCuentaCorriente.anuloMontosDebitadosCuentaCorriente(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion,txtSerieFacturacion.textoInputBox.trim())){
                            terminaAnulacionOk=false;
                        }
                    }
                    if(terminaAnulacionOk){

                        for(var i=0; i<modeloItemsFactura.count;i++){

                            var _stockReal=modeloArticulos.retornaStockTotalArticuloReal(modeloItemsFactura.get(i).codigoArticulo);
                            var _cantidadMinimaStockDeArticulo=modeloArticulos.retornaCantidadMinimaAvisoArticulo(modeloItemsFactura.get(i).codigoArticulo);

                            if(_stockReal<=_cantidadMinimaStockDeArticulo){

                                modeloArticulos.reemplazaCantidadArticulosSinStock(modeloItemsFactura.get(i).codigoArticulo,"1");
                            }else{
                                modeloArticulos.reemplazaCantidadArticulosSinStock(modeloItemsFactura.get(i).codigoArticulo,"0");
                            }
                        }


                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text="Documento "+txtNumeroDocumentoFacturacion.textoInputBox.trim()+" anulado correctamente"
                        crearNuevaFactura()
                        cuadroListaDocumentosNuevo.visible=modeloconfiguracion.retornaModoAvisoDocumentosNuevoVisible();
                        modeloLineasDePagoListaChequesDiferidosComboBox.limpiarListaLineasDePago()
                        modeloLineasDePagoListaChequesDiferidosComboBox.buscarLineasDePagoChequesDiferidos("1=","1")
                    }else{
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: No pudieron anularse los cheques."
                    }


                }else{
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="ATENCION: El documento no pudo ser anulado."
                }
            }else if(permisosAEvaluar=="permiteAutorizarDescuentosTotal"){

                rectContenedor.enabled=true
                txtArticuloParaFacturacion.tomarElFocoP()
                recalcularTotales()
            }
        }

        onPrecionarEscape: {

            if(permisosAEvaluar=="permiteAutorizarDescuentosTotal"){

                rectContenedor.enabled=true
                etiquetaTotal.tomarElFocoCuadroDescuento()

            }
        }
    }


    CuadroImprimirEnvios{

        id:cuadroImprimirEnviosEnFacturacion
        color: "#be231919"
        z: 9
        anchors.fill: parent
        visible: false
        onClicCancelar: visible=false


        onClicCancelarImprimir: {
             visible=false
             guardarFacturaPendiente()
        }

        onClicImprimir: {

            if(modeloDocumentos.emitirEnvioEnImpresoraTicket(codigoTipoImpresion,nombreImpresora,txtCodigoClienteFacturacion.textoInputBox.trim(),txtTipoClienteFacturacion.codigoValorSeleccion.trim(),txtObservacionesFactura.textoInputBox.trim())){
                visible=false
                guardarFacturaPendiente()
            }else{
                funcionesmysql.mensajeAdvertenciaOk("Error: No se pudo imprimir la información de envio, verifique la impresora.")
            }
        }

    }



    Text {
        id: lblEstadoDocumento
        x: 801
        color:"white"
        text: modeloDocumentos.retornaDescripcionEstadoDocumento(modeloDocumentos.retornacodigoEstadoDocumento(txtNumeroDocumentoFacturacion.textoInputBox.trim(),cbListatipoDocumentos.codigoValorSeleccion, txtSerieFacturacion.textoInputBox.trim()))
        clip: true
        style: Text.Sunken
        font.bold: true
        font.family: "Arial"
        styleColor: "#212121"
        //
        anchors.right: parent.right
        anchors.rightMargin: 50
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        anchors.top: parent.top
        anchors.topMargin: 2
        opacity: 1
        anchors.bottom: rectContenedor.top
        anchors.bottomMargin: 0
        font.pixelSize: 14
        z:1
    }

    Rectangle {
        id: rectColorBarraHerramientas1
        y: 0
        color: "#db4d4d"
        //
        anchors.left: lblEstadoDocumento.right
        anchors.leftMargin: (lblEstadoDocumento.implicitWidth+40)*-1
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: rectContenedor.top
        anchors.bottomMargin: -10
        z: 0


        Text {
            id: lblNumeroDocumentoyCFE
            text: ""
            anchors.top: parent.top
            anchors.topMargin: 7
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 12
            anchors.right: imgEsDocumentoCFE.left
            anchors.rightMargin: 5
            visible: true

            color:"orange"
            clip: true
            font.bold: true
            font.family: "Arial"
            styleColor: "white"
            //

        }



        Image {
            id: imgEsDocumentoCFE
            width: {
                if(visible){
                    23
                }else{
                    0
                }
            }
            //
            anchors.top: parent.top
            anchors.topMargin: 4
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 14
            anchors.right: imgEsDocumentoWeb.left
            asynchronous: true
            anchors.rightMargin: 5
            visible: false
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/IconCFE.png"
        }

        Image {
            id: imgEsDocumentoWeb
            width: {
                if(visible){
                    23
                }else{
                    0
                }
            }
            //
            anchors.top: parent.top
            anchors.topMargin: 4
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 14
            anchors.right: parent.left
            asynchronous: true
            anchors.rightMargin: 5
            visible: false
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/ClienteWeb.png"
        }
    }



}
