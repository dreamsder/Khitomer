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
import QtQuick 1.1
import "Controles"
import "Listas"

Rectangle {
    id: rectPrincipalMantenimiento
    width: 900
    height: 600
    color: "#ffffff"
    radius: 8
    //

    property alias botonNuevoClienteVisible: botonNuevoCliente.visible
    property alias botonEliminarClienteVisible: botonEliminarCliente.visible
    property alias botonGuardarClienteVisible: botonGuardarCliente.visible
    property alias codigoClienteInputMask: txtCodigoCliente.inputMask


    function retornaCantidadRegistrosListaPrecioCliente(){
        return modeloListaPrecioDeClienteVirtual.count
    }


    function cargarListasDePrecioCliente(_codigoCliente,_codigoTipoCliente){

        cbListaDePreciosDeClientesNuevo.cerrarComboBox()
        if(cbListaDePreciosDeClientesNuevo.visible){

            modeloListasPreciosComboBox.clearListasPrecio()
            modeloListasPreciosComboBox.buscarListasPrecio("1=","1")


            cbListaDePreciosDeClientesNuevo.modeloItems=modeloListaPrecioDeClienteVirtual
            modeloListaPrecioDeClienteVirtual.clear()

            for(var i=0; i<modeloListasPreciosComboBox.rowCount() ;i++){


                if((_codigoCliente=="" || _codigoCliente=="-1") && (_codigoTipoCliente=="" || _codigoTipoCliente=="-1")){

                    modeloListaPrecioDeClienteVirtual.append({
                                                                 codigoItem: modeloListasPreciosComboBox.retornaCodigoListaPrecioPorIndice(i),
                                                                 descripcionItem: modeloListasPreciosComboBox.retornaDescripcionListaPrecioPorIndice(i) ,
                                                                 checkBoxActivo: false,
                                                                 codigoTipoItem:"",
                                                                 descripcionItemSegundafila:"",
                                                                 valorItem:"",
                                                                 serieDoc:""
                                                             })

                }else{



                    modeloListaPrecioDeClienteVirtual.append({
                                                                 codigoItem: modeloListasPreciosComboBox.retornaCodigoListaPrecioPorIndice(i),
                                                                 descripcionItem: modeloListasPreciosComboBox.retornaDescripcionListaPrecioPorIndice(i) ,
                                                                 checkBoxActivo: modeloListasPreciosClientes.retornaSiClienteTieneListaPrecio(modeloListasPreciosComboBox.retornaCodigoListaPrecioPorIndice(i),_codigoCliente,_codigoTipoCliente),
                                                                 codigoTipoItem:"",
                                                                 descripcionItemSegundafila:"",
                                                                 valorItem:"",
                                                                 serieDoc:""
                                                             })
                }
            }

            cbListaDePreciosDeClientesNuevo.setearMensajeDeCantidad()
        }else{
            modeloListaPrecioDeClienteVirtual.clear()
        }
    }

    Rectangle {
        id: rectContenedor
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
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 10


            ComboBoxListaTipoCliente {
                id: txtTipoCliente
                width: 120
                textoTitulo: "Tipo de Cliente:"
                botonBuscarTextoVisible: true
                codigoValorSeleccion: "1"
                textoComboBox: "Cliente"
                z:106
                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente("tipoCliente =",txtTipoCliente.codigoValorSeleccion)
                    listaDeClientes.currentIndex=0;
                }
                onEnter: txtCodigoCliente.tomarElFoco()
            }
            TextInputSimple {
                id: txtCodigoCliente
                x: 53
                y: -36
                //   width: 150
                largoMaximo: 6
                inputMask: "000000;"
                botonBuscarTextoVisible: true
                botonBorrarTextoVisible: true
                textoTitulo: "Código:"
                textoInputBox: ""
                onClicEnBusqueda: {

                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente("codigoCliente=",txtCodigoCliente.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {

                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente("codigoCliente=",txtCodigoCliente.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                    txtTipoDocumentoCliente.tomarElFoco()

                }
                onTabulacion: txtTipoDocumentoCliente.tomarElFoco()

            }

            ComboBoxListaTipoDocumentoCliente {
                id: txtTipoDocumentoCliente
                width: 120
                textoTitulo: "Tipo documento:"
                botonBuscarTextoVisible: true
                codigoValorSeleccion: "2"
                textoComboBox: "RUT"
                z:106
                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente("codigoTipoDocumentoCliente =",txtTipoDocumentoCliente.codigoValorSeleccion)
                    listaDeClientes.currentIndex=0;
                }
                onEnter: txtRut.tomarElFoco()
            }


            TextInputSimple {
                id: txtRut
                x: 64
                y: 25
                //  width: 150
                enFocoSeleccionarTodo: true
                largoMaximo: 12
                botonBuscarTextoVisible: true
                textoTitulo: txtTipoDocumentoCliente.textoComboBox.trim()+":"
                textoInputBox: ""
                onClicEnBusqueda: {

                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente("rut rlike",txtRut.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {
                    txtNombre.tomarElFoco()
                }
                onTabulacion: txtNombre.tomarElFoco()
            }

            TextInputSimple {
                id: txtNombre
                x: 37
                y: 90
                //  width: 225
                enFocoSeleccionarTodo: true
                botonBuscarTextoVisible: true
                largoMaximo: 40
                textoTitulo: "Nombre fantasía:"
                textoInputBox: ""
                onClicEnBusqueda: {

                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente("nombreCliente rlike",txtNombre.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {
                    txtRazonSocial.tomarElFoco()
                }
                onTabulacion: txtRazonSocial.tomarElFoco()
            }

            TextInputSimple {
                id: txtRazonSocial
                x: 68
                y: 134
                // width: 165
                enFocoSeleccionarTodo: true
                botonBuscarTextoVisible: true
                textoInputBox: ""
                textoTitulo: "Razon social:"
                largoMaximo: 40

                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente("razonSocial rlike",txtRazonSocial.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {
                    txtDireccion.tomarElFoco()

                }
                onTabulacion: txtDireccion.tomarElFoco()
            }



            TextInputSimple {
                id: txtDireccion
                x: 52
                y: 205
                //   width: 250
                enFocoSeleccionarTodo: true
                botonBuscarTextoVisible: true
                textoTitulo: "Dirección:"
                textoInputBox: ""
                largoMaximo: 45
                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente("direccion rlike",txtDireccion.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {
                    cbxListaLocalidades.tomarElFoco()
                }
                onTabulacion: {
                    cbxListaLocalidades.tomarElFoco()
                }
            }

            ComboBoxListaLocalidades{
                id:cbxListaLocalidades
                width: 190
                botonBuscarTextoVisible: true
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaLocalidad")
                textoTitulo: "Localidad"
                codigoValorSeleccion: "1"
                codigoDePaisSeleccionado: "1"
                orientacionSubMenu: false
                codigoDeDepartamentoSeleccionado: "1"
                codigoDeLocalidadSeleccionado: "1"
                textoComboBox: modeloLocalidadesComboBox.retornaDescripcionLocalidad("1","1","1")
                z:105
                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente(" codigoPais='"+codigoDePaisSeleccionado+"' and codigoDepartamento='"+codigoDeDepartamentoSeleccionado+"' and codigoLocalidad=",codigoDeLocalidadSeleccionado)
                    listaDeClientes.currentIndex=0;
                }
                onSenialAlAceptarOClick:  {
                    if(txtEsquina.visible){
                        txtEsquina.tomarElFoco()
                    }else if(txtEsquina.visible==false && txtNumeroPuerta.visible){
                        txtNumeroPuerta.tomarElFoco()
                    }else{
                        txtTelefono.tomarElFoco()
                    }
                }
            }


            TextInputSimple {
                id: txtEsquina
                x: 84
                y: 275
                //  width: 175
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaEsquina")
                botonBuscarTextoVisible: true
                textoInputBox: ""
                textoTitulo: "Esquina:"
                largoMaximo: 20

                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente(" esquina rlike ",txtEsquina.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {
                    if(txtNumeroPuerta.visible){
                        txtNumeroPuerta.tomarElFoco()

                    }else{
                        txtTelefono.tomarElFoco()
                    }
                }
                onTabulacion: {
                    if(txtNumeroPuerta.visible){
                        txtNumeroPuerta.tomarElFoco()

                    }else{
                        txtTelefono.tomarElFoco()
                    }
                }
            }

            TextInputSimple {
                id: txtNumeroPuerta
                x: 60
                y: 61
                //  width: 110
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaNumeroPuerta")
                largoMaximo: 6
                botonBuscarTextoVisible: true
                textoInputBox: ""
                textoTitulo: "Número puerta:"

                onClicEnBusqueda: {

                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente(" numeroPuerta rlike ",txtNumeroPuerta.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {
                    txtTelefono.tomarElFoco()
                }
                onTabulacion: txtTelefono.tomarElFoco()

            }

            TextInputSimple {
                id: txtTelefono
                x: 31
                y: 145
                // width: 155
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaTelefono")
                enFocoSeleccionarTodo: true
                largoMaximo: 14
                botonBuscarTextoVisible: true
                textoInputBox: ""
                textoTitulo: "Teléfono:"

                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente(" telefono rlike ",txtTelefono.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {
                    if(txtTelefono2.visible){
                        txtTelefono2.tomarElFoco()

                    }else if(txtTelefono2.visible==false && txtCodigoPostal.visible==false){
                        txtEmail.tomarElFoco()
                    }else{
                        txtCodigoPostal.tomarElFoco()
                    }


                }
                onTabulacion: {
                    if(txtTelefono2.visible){
                        txtTelefono2.tomarElFoco()

                    }else if(txtTelefono2.visible==false && txtCodigoPostal.visible==false){
                        txtEmail.tomarElFoco()
                    }else{
                        txtCodigoPostal.tomarElFoco()
                    }
                }
            }

            TextInputSimple {
                id: txtTelefono2
                x: 74
                y: 183
                // width: 170
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaTelefono2")
                largoMaximo: 14
                botonBuscarTextoVisible: true
                textoInputBox: ""
                textoTitulo: "Teléfono 2:"

                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente(" telefono2 rlike ",txtTelefono2.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {
                    if(txtCodigoPostal.visible){
                        txtCodigoPostal.tomarElFoco()

                    }else{
                        txtEmail.tomarElFoco()
                    }
                }
                onTabulacion: {
                    if(txtCodigoPostal.visible){
                        txtCodigoPostal.tomarElFoco()

                    }else{
                        txtEmail.tomarElFoco()
                    }
                }
            }

            TextInputSimple {
                id: txtCodigoPostal
                x: 80
                y: 117
                // width: 110
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaCodigoPostal")
                largoMaximo: 6
                botonBuscarTextoVisible: true
                textoInputBox: ""
                textoTitulo: "Código postal:"

                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente(" codigoPostal rlike ",txtCodigoPostal.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {
                    txtEmail.tomarElFoco()
                }
                onTabulacion: txtEmail.tomarElFoco()
            }

            TextInputSimple {
                id: txtEmail
                x: 45
                y: 130
                //  width: 250
                textoDeFondo: "email@empresa.com"
                largoMaximo: 70
                botonBuscarTextoVisible: true
                textoTitulo: "E-mail:"
                textoInputBox: ""
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaEmail")
                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente(" email rlike ",txtEmail.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {
                    if(txtEmail2.visible){
                        txtEmail2.tomarElFoco()

                    }else{
                        txtSitioWeb.tomarElFoco()
                    }
                }
                onTabulacion: {
                    if(txtEmail2.visible){
                        txtEmail2.tomarElFoco()

                    }else{
                        txtSitioWeb.tomarElFoco()
                    }
                }
            }

            TextInputSimple {
                id: txtEmail2
                x: 45
                y: 130
                //  width: 250
                textoDeFondo: "email@empresa.com"
                largoMaximo: 70
                botonBuscarTextoVisible: true
                textoTitulo: "E-mail 2:"
                textoInputBox: ""
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaEmail")
                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente(" email2 rlike ",txtEmail2.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {
                    if(txtSitioWeb.visible){
                        txtSitioWeb.tomarElFoco()

                    }else{
                        txtContacto.tomarElFoco()
                    }
                }
                onTabulacion: {
                    if(txtSitioWeb.visible){
                        txtSitioWeb.tomarElFoco()

                    }else{
                        txtContacto.tomarElFoco()
                    }
                }
            }

            TextInputSimple {
                id: txtSitioWeb
                x: 60
                y: 191
                //   width: 280
                botonBorrarTextoVisible: true
                textoDeFondo: "http://www.empresa.com"
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaSitioWeb")
                largoMaximo: 40
                botonBuscarTextoVisible: true
                textoInputBox: ""
                textoTitulo: "Sitio web:"

                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente(" sitioWeb rlike ",txtSitioWeb.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {
                    txtContacto.tomarElFoco()
                }
                onTabulacion: txtContacto.tomarElFoco()
            }

            TextInputSimple {
                id: txtContacto
                x: 27
                y: 98
                // width: 150
                largoMaximo: 30
                textoInputBox: ""
                botonBuscarTextoVisible: true
                textoTitulo: "Contacto:"
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaContacto")
                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente(" contacto rlike ",txtContacto.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {
                    txtHorario.tomarElFoco()
                }
                onTabulacion: txtHorario.tomarElFoco()
            }
            TextInputSimple {
                id: txtHorario
                x: 27
                y: 95
                //  width: 128
                textoInputBox: ""
                enFocoSeleccionarTodo: true
                inputMask: "NN:NN - NN:NN; "
                botonBuscarTextoVisible: false
                textoTitulo: "Horario:"
                validaFormato: validacionHora
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaHorario")

                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente("horario rlike",txtHorario.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }
                onEnter: {
                    txtTipoValoracion.tomarElFoco()
                }
                onTabulacion: txtTipoValoracion.tomarElFoco()
            }

            RegExpValidator{
                id:validacionHora
                regExp: new RegExp( "([0-1, ][0-9, ]|2[0-3, ])\:[0-5, ][0-9, ] \- ([0-1, ][0-9, ]|2[0-3, ])\:[0-5, ][0-9, ]" )

            }


            ComboBoxListaTipoClasificacion {
                id: txtTipoValoracion
                width: 190
                botonBuscarTextoVisible: true
                textoTitulo: "Valoración"
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaValoracion")
                z:104
                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente(" tipoClasificacion = ",txtTipoValoracion.codigoValorSeleccion)
                    listaDeClientes.currentIndex=0;
                }
                onEnter: txtObservaciones.tomarElFoco()
            }

            TextInputSimple {
                id: txtObservaciones
                x: 65
                y: 200
                //  width: 370
                textoDeFondo: "escriba aquí información adicional"
                enFocoSeleccionarTodo: false
                largoMaximo: 80
                cursor_Visible: false
                textoInputBox: ""
                botonBuscarTextoVisible: true
                textoTitulo: "Observaciones:"
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaObservaciones")
                onClicEnBusqueda: {
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente(" observaciones rlike ",txtObservaciones.textoInputBox.trim())
                    listaDeClientes.currentIndex=0;
                }

                onEnter: {

                    txtCodigoCliente.tomarElFoco()
                }
                onTabulacion:     txtCodigoCliente.tomarElFoco()
            }



            ComboBoxCheckBoxGenerico {
                id: cbListaDePreciosDeClientesNuevo
                width: 240
                z: 103
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaAgregarListaPrecio")
                codigoValorSeleccion: ""
                textoTitulo: "Agregar listas de precio a cliente:"
                textoComboBox: ""
            }

            ListModel{
                id:modeloListaPrecioDeClienteVirtual
            }


            ComboBoxListaTipoProcedenciaCliente {
                id: txtTipoProcedenciaCliente
                width: 130
                textoTitulo: "Procedencia:"
                botonBuscarTextoVisible: true
                codigoValorSeleccion: "-1"
                textoComboBox: ""
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaProcedencia")
                z:102
                onClicEnBusqueda: {
                    modeloTipoProcedenciaCliente.limpiar()
                    modeloTipoProcedenciaCliente.buscar("codigoTipoProcedenciaCliente =",txtTipoProcedenciaCliente.codigoValorSeleccion)
                    listaDeClientes.currentIndex=0;
                }
            }

            TextInputSimple {
                id: txtFechaNacimiento
                // width: 130
                enFocoSeleccionarTodo: true
                textoInputBox: ""
                validaFormato: validacionFechaNacimiento
                botonBuscarTextoVisible: true
                inputMask: "nnnn-nn-nn; "
                textoTitulo: "Fecha cumpleaños:"
                onClicEnBusqueda: {


                }
            }



            RegExpValidator{
                id:validacionFechaNacimiento
                ///Fecha AAAA/MM/DD
                regExp: new RegExp("(20|  |2 | 2|19|  |1 | 1)(0[0-9, ]| [0-9, ]|1[0123456789 ]|2[0123456789 ]|3[0123456789 ]|4[0123456789 ]|5[0123456789 ]|6[0123456789 ]|7[0123456789 ]|8[0123456789 ]|9[0123456789 ])\-(0[1-9, ]| [1-9, ]|1[012 ]| [012 ])\-(0[1-9, ]| [1-9, ]|[12 ][0-9, ]|3[01 ]| [01 ])")
            }


            CheckBox {
                id: chbEsClienteCredito
                x: 315
                y: 233
                buscarActivo: true
                chekActivo: false
                colorTexto: "#dbd8d8"
                textoValor: "Permite facturar a credito"
                visible: false
                Component.onCompleted: {
                    var _UTILIZA_CONTROL_CLIENTE_CREDITO=modeloconfiguracion.retornaValorConfiguracion("UTILIZA_CONTROL_CLIENTE_CREDITO");
                    if(_UTILIZA_CONTROL_CLIENTE_CREDITO=="1"){
                        visible=true
                    }else{
                        visible=false
                    }
                }

                onClicEnBusqueda: {

                    var _activo="0"
                    if(chekActivo)
                        _activo="1"

                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente("permiteFacturaCredito =",_activo)
                    listaDeClientes.currentIndex=0;



                }
            }

            ComboBoxListaFormasDePago {
                id: cbListaFormasDePagoCliente
                width: 250
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaFormaDePago")
                textoTitulo: "Forma de pago por defecto:"
                textoComboBox: ""
                codigoValorSeleccion: ""
            }

            ComboBoxListaMonedas {
                id: cbListaMonedaCliente
                width: 130
                textoTitulo: "Moneda por defecto:"
                botonBuscarTextoVisible: false
                codigoValorSeleccion: ""
                textoComboBox: ""
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaMoneda")
            }

            ComboBoxListaTipoDocumentosClientesFacturacion{
                id: cbListaDocumentosCliente
                width: 220
                textoTitulo: "Documento por defecto:"
                botonBuscarTextoVisible: false
                codigoValorSeleccion: "-1"
                textoComboBox: "Sin documento seleccionado"
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaTipoDocumentoDefault")



            }


            TextInputSimple {
                id: txtDescuentoCliente
                enFocoSeleccionarTodo: true
                textoInputBox: "000.00"
                inputMask: "000.00%; "
                largoMaximo: 6
                textoTitulo: "Descuento %"
                validaFormato: validacionMontoPorcentaje
                visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaDescuentoDeMantenimiento")
            }





        }

        Rectangle{
            id: rectangle2
            color: "#C4C4C6"
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
                id: listaDeClientes
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

                delegate:  ListaClientes{}
                model: modeloClientes



                Rectangle {
                    id: scrollbarlistaDeClientes
                    y: listaDeClientes.visibleArea.yPosition * listaDeClientes.height+5
                    width: 10
                    color: "#000000"
                    height: listaDeClientes.visibleArea.heightRatio * listaDeClientes.height+18
                    radius: 2
                    anchors.right: listaDeClientes.right
                    anchors.rightMargin: 4
                    z: 1
                    opacity: 0.500
                    visible: true
                    //
                }

            }

            Text {
                id: txtCantidadDeItemsValor
                x: 107
                width: 37
                height: 15
                color: "#000000"
                text: listaDeClientes.count
                anchors.top: parent.top
                anchors.topMargin: 5
                font.family: "Arial"
                anchors.leftMargin: 5
                //
                font.bold: false
                font.pointSize: 10
                anchors.left: txtCantidadDeItemsTitulo.right
            }

            Text {
                id: txtCantidadDeItemsTitulo
                x: 5
                width: txtCantidadDeItemsTitulo.implicitWidth
                height: 15
                color: "#000000"
                text: qsTr("Cantidad de clientes:")
                anchors.top: parent.top
                anchors.topMargin: 5
                font.family: "Arial"
                font.pointSize: 10
                font.bold: false
                anchors.left: parent.left
                anchors.leftMargin: 5
                //
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

                onClic: listaDeClientes.positionViewAtIndex(0,0)
            }

            BotonBarraDeHerramientas {
                id: botonBajarListaFinal
                x: 845
                y: 185
                width: 14
                height: 14
                anchors.right: parent.right
                anchors.rightMargin: 3
                toolTip: ""
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
                rotation: -90

                onClic: listaDeClientes.positionViewAtIndex(listaDeClientes.count-1,0)

            }

        }

        BotonPaletaSistema {
            id: btnFiltrarClientesProveedores
            y: 53
            text: "Filtrar "+txtTipoCliente.textoComboBox.trim().toLowerCase()
            anchors.bottom: rectangle2.top
            anchors.bottomMargin: 10
            anchors.leftMargin: 20
            anchors.left: parent.left
            onClicked: {
                var consultaSql="";
                if(txtTipoCliente.codigoValorSeleccion.trim()!="" && txtTipoCliente.codigoValorSeleccion.trim()!='-1'){
                    consultaSql+=" tipoCliente = "+txtTipoCliente.codigoValorSeleccion.trim()+" and "
                }
                if(txtCodigoCliente.textoInputBox.trim()!=""){
                    consultaSql+=" codigoCliente = '"+txtCodigoCliente.textoInputBox.trim()+"' and ";
                }
                if(txtTipoDocumentoCliente.codigoValorSeleccion.trim()!="" && txtTipoDocumentoCliente.codigoValorSeleccion.trim()!='-1'){
                    consultaSql+=" codigoTipoDocumentoCliente = "+txtTipoDocumentoCliente.codigoValorSeleccion.trim()+" and "
                }
                if(txtRut.textoInputBox.trim()!=""){
                    consultaSql+=" rut rlike '"+txtRut.textoInputBox.trim()+"' and ";
                }
                if(txtNombre.textoInputBox.trim()!=""){
                    consultaSql+=" nombreCliente rlike '"+txtNombre.textoInputBox.trim()+"' and ";
                }
                if(txtRazonSocial.textoInputBox.trim()!=""){
                    consultaSql+=" razonSocial rlike '"+txtRazonSocial.textoInputBox.trim()+"' and ";
                }
                if(txtDireccion.textoInputBox.trim()!=""){
                    consultaSql+=" direccion rlike '"+txtDireccion.textoInputBox.trim()+"' and ";
                }
                if(cbxListaLocalidades.codigoValorSeleccion.trim()!="" && cbxListaLocalidades.codigoValorSeleccion.trim()!='-1'){
                    consultaSql+=" codigoPais='"+cbxListaLocalidades.codigoDePaisSeleccionado+"' and codigoDepartamento='"+cbxListaLocalidades.codigoDeDepartamentoSeleccionado+"' and codigoLocalidad='"+cbxListaLocalidades.codigoDeLocalidadSeleccionado+"'  and  ";
                }
                if(txtEsquina.textoInputBox.trim()!=""){
                    consultaSql+=" esquina rlike '"+txtEsquina.textoInputBox.trim()+"' and ";
                }
                if(txtNumeroPuerta.textoInputBox.trim()!=""){
                    consultaSql+=" numeroPuerta rlike '"+txtNumeroPuerta.textoInputBox.trim()+"' and ";
                }
                if(txtTelefono.textoInputBox.trim()!=""){
                    consultaSql+=" telefono rlike '"+txtTelefono.textoInputBox.trim()+"' and ";
                }
                if(txtTelefono2.textoInputBox.trim()!=""){
                    consultaSql+=" telefono2 rlike '"+txtTelefono2.textoInputBox.trim()+"' and ";
                }
                if(txtCodigoPostal.textoInputBox.trim()!=""){
                    consultaSql+=" codigoPostal rlike '"+txtCodigoPostal.textoInputBox.trim()+"' and ";
                }
                if(txtEmail.textoInputBox.trim()!=""){
                    consultaSql+=" email rlike '"+txtEmail.textoInputBox.trim()+"' and ";
                }
                if(txtEmail2.textoInputBox.trim()!=""){
                    consultaSql+=" email2 rlike '"+txtEmail2.textoInputBox.trim()+"' and ";
                }
                if(txtSitioWeb.textoInputBox.trim()!=""){
                    consultaSql+=" sitioWeb rlike '"+txtSitioWeb.textoInputBox.trim()+"' and ";
                }
                if(txtContacto.textoInputBox.trim()!=""){
                    consultaSql+=" contacto rlike '"+txtContacto.textoInputBox.trim()+"' and ";
                }
                if(txtTipoValoracion.codigoValorSeleccion.trim()!="" && txtTipoValoracion.codigoValorSeleccion.trim()!='-1'){
                    consultaSql+=" tipoClasificacion = '"+txtTipoValoracion.codigoValorSeleccion.trim()+"' and "
                }
                if(txtObservaciones.textoInputBox.trim()!=""){
                    consultaSql+=" observaciones rlike '"+txtObservaciones.textoInputBox.trim()+"' and ";
                }

                if(chbEsClienteCredito.chekActivo){
                    consultaSql+=" permiteFacturaCredito = '1' and ";
                }else{
                    consultaSql+=" permiteFacturaCredito = '0' and ";
                }


                //



                if(consultaSql!=""){
                    modeloClientes.clearClientes()
                    modeloClientes.buscarCliente(consultaSql,"1=1")
                    listaDeClientes.currentIndex=0;
                }
            }
        }


        BotonPaletaSistema {
            id: btnCargarSaldosPorMonedaCliente
            text: "Configuración de saldos..."
            anchors.right:
            {
                if(btnCargarClientesYProveedoresBatch.visible){
                    btnCargarClientesYProveedoresBatch.left
                }else{
                    parent.right
                }
            }

            anchors.rightMargin: 30
            anchors.bottom: rectangle2.top
            anchors.bottomMargin: 10
            height: {
                if(visible){
                    btnFiltrarClientesProveedores.height
                }else{
                    0
                }
            }

            visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaControlDeSaldos")

            onClicked: {

                if(txtCodigoCliente.textoInputBox.trim()!=="0" && txtRazonSocial.textoInputBox.trim()!==""){
                    if(modeloconfiguracion.retornaValorConfiguracion("MODO_AUTORIZACION")=="1"){
                        cuadroAutorizacionClienteSaldo.evaluarPermisos("permiteAutorizarModificacionSaldoCliente")
                    }else{
                        cuadroAutorizacionClienteSaldo.noSeRequierenAutorizaciones("permiteAutorizarModificacionSaldoCliente")
                    }
                }else{
                    funcionesmysql.mensajeAdvertenciaOk("Debe seleccionar un cliente/proveedor para setear un limite de Saldo.")
                }




            }

        }


        BotonPaletaSistema {
            id: btnCargarClientesYProveedoresBatch
            text: "Carga de "+txtTipoCliente.textoComboBox.trim().toLowerCase()+"..."
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.bottom: rectangle2.top
            anchors.bottomMargin: 10
            height: {
                if(visible){
                    btnFiltrarClientesProveedores.height
                }else{
                    0
                }
            }

            visible: modeloControlesMantenimientos.retornaValorMantenimiento("clientesUsaCargaBatch")

        }
    }

    Row {
        id: rowBarraDeHerramientas
        //
        anchors.bottom: rectContenedor.top
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        spacing: distanciaEntreBotonesBarraDeTareas

        BotonBarraDeHerramientas {
            id: botonNuevoCliente
            x: 33
            y: 10
            toolTip: "Nuevo cliente"
            z: 8
            //source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevoCliente.png"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Nuevo.png"
            anchors.verticalCenter: parent.verticalCenter


            onClic: {

                cargarListasDePrecioCliente("","")

                if(txtTipoCliente.textoComboBox.trim()==""){
                    txtTipoCliente.codigoValorSeleccion=1
                    txtTipoCliente.textoComboBox=modeloTipoClientes.primerRegistroDeTipoClienteEnBase(txtTipoCliente.codigoValorSeleccion)
                }
                var nuevoCliente=""

                var modoCodigoCliente=modeloconfiguracion.retornaValorConfiguracion("MODO_CLIENTE");

                if(modoCodigoCliente=="0"){

                    txtCodigoCliente.tomarElFoco()


                }else if(modoCodigoCliente=="1"){

                    //   nuevoCliente=parseInt(modeloClientes.ultimoRegistroDeClienteEnBase(txtTipoCliente.codigoValorSeleccion));

                }



                if(nuevoCliente==-1){

                }else{

                    txtCodigoCliente.textoInputBox=nuevoCliente
                    txtCodigoPostal.textoInputBox=""
                    txtDireccion.textoInputBox=""
                    txtEmail.textoInputBox=""
                    txtEmail2.textoInputBox=""
                    txtEsquina.textoInputBox=""
                    txtNombre.textoInputBox=""
                    txtNumeroPuerta.textoInputBox=""
                    txtObservaciones.textoInputBox=""
                    txtRazonSocial.textoInputBox=""
                    txtTipoDocumentoCliente.codigoValorSeleccion=2
                    txtTipoDocumentoCliente.textoComboBox="RUT"
                    txtRut.textoInputBox=""
                    txtSitioWeb.textoInputBox=""
                    txtTelefono.textoInputBox=""
                    txtTelefono2.textoInputBox=""
                    txtTipoValoracion.textoComboBox=modeloTipoClasificacion.primerRegistroDeTipoClasificacionEnBase()
                    txtTipoValoracion.codigoValorSeleccion=1
                    txtCodigoCliente.enabled=true
                    txtTipoCliente.enabled=true
                    txtContacto.textoInputBox=""
                    txtHorario.textoInputBox=""
                    txtFechaNacimiento.textoInputBox=""
                    chbEsClienteCredito.setActivo(false)
                    txtDescuentoCliente.textoInputBox="000.00"

                    /*if(nuevoCliente==""){
                        txtCodigoCliente.tomarElFoco()
                    }else{*/
                    txtRut.tomarElFoco()
                    // }


                }
            }
        }

        BotonBarraDeHerramientas {
            id: botonGuardarCliente
            x: 61
            y: 3
            toolTip: "Gurardar cliente"
            z: 7
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            anchors.verticalCenter: parent.verticalCenter

            onClic: {
                var errorProcedencia=false;
                if(txtTipoProcedenciaCliente.visible){

                    if(txtTipoProcedenciaCliente.codigoValorSeleccion!="-1"){
                        errorProcedencia=false;
                    }else{
                        errorProcedencia=true;
                    }

                }else{
                    txtTipoProcedenciaCliente.codigoValorSeleccion="1";
                }
                if(!cbListaMonedaCliente.visible){
                    cbListaMonedaCliente.codigoValorSeleccion="0";
                }
                if(!cbListaFormasDePagoCliente.visible){
                    cbListaFormasDePagoCliente.codigoValorSeleccion="0";
                }
                if(!cbListaDocumentosCliente.visible){
                    cbListaDocumentosCliente.codigoValorSeleccion="0";
                }


                txtMensajeInformacion.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                if(!errorProcedencia){


                    var resultadoInsertarCliente=""


                    var esClienteCredito="0"

                    if(chbEsClienteCredito.chekActivo){
                        esClienteCredito="1"
                    }

                    if(txtTipoDocumentoCliente.codigoValorSeleccion==="3"){
                        var cedulaIdentidad=funcionesmysql.verificarCedula(txtRut.textoInputBox.trim());
                        if(cedulaIdentidad==="-1ERROR"){
                            resultadoInsertarCliente="-6";
                        }else{
                            txtRut.textoInputBox=cedulaIdentidad;                            
                            resultadoInsertarCliente = modeloClientes.insertarCliente(txtCodigoCliente.textoInputBox,txtTipoCliente.codigoValorSeleccion,txtNombre.textoInputBox,txtRazonSocial.textoInputBox,txtRut.textoInputBox,txtTipoValoracion.codigoValorSeleccion,txtDireccion.textoInputBox,txtEsquina.textoInputBox,txtNumeroPuerta.textoInputBox,txtTelefono.textoInputBox,txtTelefono2.textoInputBox,txtCodigoPostal.textoInputBox,txtEmail.textoInputBox,txtSitioWeb.textoInputBox,txtContacto.textoInputBox,txtObservaciones.textoInputBox,txtNombreDeUsuario.textoInputBox,txtHorario.textoInputBox,cbxListaLocalidades.codigoDePaisSeleccionado,cbxListaLocalidades.codigoDeDepartamentoSeleccionado,cbxListaLocalidades.codigoDeLocalidadSeleccionado,txtTipoDocumentoCliente.codigoValorSeleccion,txtTipoProcedenciaCliente.codigoValorSeleccion,txtFechaNacimiento.textoInputBox,esClienteCredito,cbListaMonedaCliente.codigoValorSeleccion,cbListaFormasDePagoCliente.codigoValorSeleccion,cbListaDocumentosCliente.codigoValorSeleccion,txtDescuentoCliente.textoInputBox.trim(),txtEmail2.textoInputBox);
                        }
                    }else{
                        resultadoInsertarCliente = modeloClientes.insertarCliente(txtCodigoCliente.textoInputBox,txtTipoCliente.codigoValorSeleccion,txtNombre.textoInputBox,txtRazonSocial.textoInputBox,txtRut.textoInputBox,txtTipoValoracion.codigoValorSeleccion,txtDireccion.textoInputBox,txtEsquina.textoInputBox,txtNumeroPuerta.textoInputBox,txtTelefono.textoInputBox,txtTelefono2.textoInputBox,txtCodigoPostal.textoInputBox,txtEmail.textoInputBox,txtSitioWeb.textoInputBox,txtContacto.textoInputBox,txtObservaciones.textoInputBox,txtNombreDeUsuario.textoInputBox,txtHorario.textoInputBox,cbxListaLocalidades.codigoDePaisSeleccionado,cbxListaLocalidades.codigoDeDepartamentoSeleccionado,cbxListaLocalidades.codigoDeLocalidadSeleccionado,txtTipoDocumentoCliente.codigoValorSeleccion,txtTipoProcedenciaCliente.codigoValorSeleccion,txtFechaNacimiento.textoInputBox,esClienteCredito,cbListaMonedaCliente.codigoValorSeleccion,cbListaFormasDePagoCliente.codigoValorSeleccion,cbListaDocumentosCliente.codigoValorSeleccion,txtDescuentoCliente.textoInputBox.trim(),txtEmail2.textoInputBox);
                    }




                    if(resultadoInsertarCliente!="-6" && resultadoInsertarCliente!="-1"
                            && resultadoInsertarCliente!="-2"
                            && resultadoInsertarCliente!="-3"
                            && resultadoInsertarCliente!="-4"
                            && resultadoInsertarCliente!="-5"
                            && resultadoInsertarCliente!="-7"
                            ){


                        var modoCodigoClienteTipo=modeloconfiguracion.retornaValorConfiguracion("MODO_CLIENTE");

                        if(modoCodigoClienteTipo=="0"){

                            txtCodigoCliente.textoInputBox=resultadoInsertarCliente

                        }else if(modoCodigoClienteTipo=="1"){

                            txtCodigoCliente.textoInputBox=parseInt(resultadoInsertarCliente)
                            // nuevoCliente=parseInt(modeloClientes.ultimoRegistroDeClienteEnBase(txtTipoCliente.codigoValorSeleccion));

                        }





                        if(modeloListasPreciosComboBox.eliminaListaPrecioDeCliente(txtCodigoCliente.textoInputBox,txtTipoCliente.codigoValorSeleccion)){

                            for(var i=0; i<modeloListaPrecioDeClienteVirtual.count;i++){
                                if(modeloListaPrecioDeClienteVirtual.get(i).checkBoxActivo){
                                    modeloListasPreciosComboBox.insertarListaPrecioCliente(modeloListaPrecioDeClienteVirtual.get(i).codigoItem,txtCodigoCliente.textoInputBox,txtTipoCliente.codigoValorSeleccion)
                                }
                            }
                        }



                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text=txtTipoCliente.textoComboBox +" "+txtCodigoCliente.textoInputBox+" dado de alta correctamente"

                        modeloClientes.clearClientes()
                        modeloClientes.buscarCliente(" codigoCliente='"+txtCodigoCliente.textoInputBox.trim()+"' and tipoCliente=",txtTipoCliente.codigoValorSeleccion)
                        listaDeClientes.currentIndex=0;

                        txtCodigoCliente.textoInputBox=""
                        txtCodigoPostal.textoInputBox=""
                        txtDireccion.textoInputBox=""
                        txtEmail.textoInputBox=""
                        txtEmail2.textoInputBox=""
                        txtEsquina.textoInputBox=""
                        txtNombre.textoInputBox=""
                        txtNumeroPuerta.textoInputBox=""
                        txtObservaciones.textoInputBox=""
                        txtRazonSocial.textoInputBox=""
                        txtRut.textoInputBox=""
                        txtSitioWeb.textoInputBox=""
                        txtTelefono.textoInputBox=""
                        txtTelefono2.textoInputBox=""
                        txtTipoValoracion.textoComboBox=modeloTipoClasificacion.primerRegistroDeTipoClasificacionEnBase()
                        txtTipoValoracion.codigoValorSeleccion=1
                        txtCodigoCliente.enabled=true
                        txtTipoCliente.enabled=true
                        txtContacto.textoInputBox=""
                        txtHorario.textoInputBox=""
                        chbEsClienteCredito.setActivo(false)

                        txtTipoProcedenciaCliente.textoComboBox=""
                        txtTipoProcedenciaCliente.codigoValorSeleccion="-1"
                        txtFechaNacimiento.textoInputBox=""

                        cbListaMonedaCliente.codigoValorSeleccion="0"
                        cbListaMonedaCliente.textoComboBox=""
                        cbListaFormasDePagoCliente.codigoValorSeleccion="0"
                        cbListaFormasDePagoCliente.textoComboBox=""

                        cbListaDocumentosCliente.codigoValorSeleccion="0"
                        cbListaDocumentosCliente.textoComboBox=""
                        txtDescuentoCliente.textoInputBox="000.00"

                        cargarListasDePrecioCliente("","")

                        txtCodigoCliente.tomarElFoco()


                    }else if(resultadoInsertarCliente=="-7"){

                        if(modeloListasPreciosComboBox.eliminaListaPrecioDeCliente(txtCodigoCliente.textoInputBox,txtTipoCliente.codigoValorSeleccion)){

                            for(var j=0; j<modeloListaPrecioDeClienteVirtual.count;j++){
                                if(modeloListaPrecioDeClienteVirtual.get(j).checkBoxActivo){
                                    modeloListasPreciosComboBox.insertarListaPrecioCliente(modeloListaPrecioDeClienteVirtual.get(j).codigoItem,txtCodigoCliente.textoInputBox,txtTipoCliente.codigoValorSeleccion)
                                }
                            }

                        }

                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text=txtTipoCliente.textoComboBox+" "+txtCodigoCliente.textoInputBox+" actualizado correctamente"

                        modeloClientes.clearClientes()
                        modeloClientes.buscarCliente(" codigoCliente='"+txtCodigoCliente.textoInputBox.trim()+"' and tipoCliente=",txtTipoCliente.codigoValorSeleccion)
                        listaDeClientes.currentIndex=0;



                        txtCodigoCliente.textoInputBox=""
                        txtCodigoPostal.textoInputBox=""
                        txtDireccion.textoInputBox=""
                        txtEmail.textoInputBox=""
                        txtEmail2.textoInputBox=""
                        txtEsquina.textoInputBox=""
                        txtNombre.textoInputBox=""
                        txtNumeroPuerta.textoInputBox=""
                        txtObservaciones.textoInputBox=""
                        txtRazonSocial.textoInputBox=""
                        txtRut.textoInputBox=""
                        txtSitioWeb.textoInputBox=""
                        txtTelefono.textoInputBox=""
                        txtTelefono2.textoInputBox=""
                        txtTipoValoracion.textoComboBox=modeloTipoClasificacion.primerRegistroDeTipoClasificacionEnBase()
                        txtTipoValoracion.codigoValorSeleccion=1
                        txtCodigoCliente.enabled=true
                        txtTipoCliente.enabled=true
                        txtContacto.textoInputBox=""
                        txtHorario.textoInputBox=""
                        txtTipoProcedenciaCliente.textoComboBox=""
                        txtTipoProcedenciaCliente.codigoValorSeleccion="-1"                                                
                        txtFechaNacimiento.textoInputBox=""
                        chbEsClienteCredito.setActivo(false)

                        cbListaMonedaCliente.codigoValorSeleccion="0"
                        cbListaMonedaCliente.textoComboBox=""
                        cbListaFormasDePagoCliente.codigoValorSeleccion="0"
                        cbListaFormasDePagoCliente.textoComboBox=""


                        cbListaDocumentosCliente.codigoValorSeleccion="0"
                        cbListaDocumentosCliente.textoComboBox=""
                        txtDescuentoCliente.textoInputBox="000.00"

                        cargarListasDePrecioCliente("","")

                        txtCodigoCliente.tomarElFoco()

                    }else if(resultadoInsertarCliente=="-1"){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: No se pudo conectar a la base de datos"


                    }else if(resultadoInsertarCliente=="-2"){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: No se pudo actualizar el cliente"


                    }else if(resultadoInsertarCliente=="-3"){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: No se pudo dar de alta el cliente"


                    }else if(resultadoInsertarCliente=="-4"){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: No se pudo realizar la consulta a la base de datos"


                    }else if(resultadoInsertarCliente=="-5"){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: Faltan datos para guardar el cliente. Verifique antes de continuar"

                    }
                    else if(resultadoInsertarCliente=="-6"){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: La cedula es incorrecta. Verifique antes de continuar"

                    }


                }else{
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="ATENCION: Debe elegir una procedencia para continuar"
                }

            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarCliente
            x: 54
            y: 3
            toolTip: "Eliminar cliente"
            z: 6
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            anchors.verticalCenter: parent.verticalCenter
            onClic: {

                if(txtCodigoCliente.textoInputBox.trim()!=""){

                    if(!modeloDocumentos.retornoSiClienteTieneDocumentos(txtCodigoCliente.textoInputBox.trim())){

                        if(funcionesmysql.mensajeAdvertencia("Realmente desea eliminar el "+txtTipoCliente.textoComboBox.trim().toLowerCase()+" "+txtCodigoCliente.textoInputBox.trim()+"?\n\nPresione [ Sí ] para confirmar.")){

                            txtMensajeInformacion.visible=true
                            txtMensajeInformacionTimer.stop()
                            txtMensajeInformacionTimer.start()

                            if(modeloListasPreciosClientes.eliminaListaPrecioDeCliente(txtCodigoCliente.textoInputBox,txtTipoCliente.codigoValorSeleccion)){

                                if(modeloClientes.eliminarCliente(txtCodigoCliente.textoInputBox,txtTipoCliente.codigoValorSeleccion)){



                                    txtMensajeInformacion.color="#2f71a0"
                                    txtMensajeInformacion.text=txtTipoCliente.textoComboBox+" "+txtCodigoCliente.textoInputBox+" borrado correctamente"

                                    modeloClientes.clearClientes()
                                    modeloClientes.buscarCliente("1=","0")
                                    listaDeClientes.currentIndex=0;


                                    txtCodigoCliente.textoInputBox=""
                                    txtCodigoPostal.textoInputBox=""
                                    txtDireccion.textoInputBox=""
                                    txtEmail.textoInputBox=""
                                    txtEmail2.textoInputBox=""
                                    txtEsquina.textoInputBox=""
                                    txtNombre.textoInputBox=""
                                    txtNumeroPuerta.textoInputBox=""
                                    txtObservaciones.textoInputBox=""
                                    txtRazonSocial.textoInputBox=""
                                    txtRut.textoInputBox=""
                                    txtSitioWeb.textoInputBox=""
                                    txtTelefono.textoInputBox=""
                                    txtTelefono2.textoInputBox=""
                                    txtTipoValoracion.textoComboBox=modeloTipoClasificacion.primerRegistroDeTipoClasificacionEnBase()
                                    txtTipoValoracion.codigoValorSeleccion=1
                                    txtCodigoCliente.enabled=true
                                    txtTipoCliente.enabled=true
                                    txtContacto.textoInputBox=""
                                    txtHorario.textoInputBox=""
                                    txtFechaNacimiento.textoInputBox=""
                                    txtDescuentoCliente.textoInputBox="000.00"

                                    cargarListasDePrecioCliente("","")

                                    txtCodigoCliente.tomarElFoco()


                                }else{

                                    txtMensajeInformacion.color="#d93e3e"
                                    txtMensajeInformacion.text="ATENCION: No se pudo borrar el "+txtTipoCliente.textoComboBox.toLowerCase()+" "+txtCodigoCliente.textoInputBox
                                }
                            }else{

                                txtMensajeInformacion.color="#d93e3e"
                                txtMensajeInformacion.text="ATENCION: No se pudieron borrar las listas de precio asociadas al cliente. Verifique. "
                            }
                        }

                    }else{
                        txtMensajeInformacion.visible=true
                        txtMensajeInformacionTimer.stop()
                        txtMensajeInformacionTimer.start()

                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: El "+txtTipoCliente.textoComboBox.trim()+" no se puede eliminar ya que tiene documentos asociados. "

                    }

                }
            }
        }

        BotonBarraDeHerramientas {
            id: botonListarTodosLosClientes
            x: 47
            y: 10
            toolTip: "Listar todos los clientes"
            z: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            anchors.verticalCenter: parent.verticalCenter


            onClic: {

                modeloClientes.clearClientes()
                modeloClientes.buscarCliente("1=","1")
                listaDeClientes.currentIndex=0;



            }
        }

        Text {
            id: txtMensajeInformacion
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

            txtMensajeInformacion.visible=false
            txtMensajeInformacion.color="#d93e3e"

        }

    }

    Rectangle {
        id: rectangle3
        x: -4
        y: -1
        width: 10
        color: "#3ca239"
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: rectContenedor.top
        anchors.bottomMargin: -10
        z: 0
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    MantenimientoBatch {
        id: mntClientesYProveedores
        anchors.fill: parent
        visible: false

    }


    RegExpValidator{
        id:validacionMontoPorcentaje
        regExp: new RegExp( "([0-1, ][0-9, ][0-9, ]\.[0-9, ][0-9, ])\%" )
    }


    CuadroAutorizaciones{
        id:cuadroAutorizacionClienteSaldo
        color: "#be231919"
        z: 9
        anchors.fill: parent
        onConfirmacion: {

            if(permisosAEvaluar=="permiteAutorizarModificacionSaldoCliente"){

                modeloListaMonedaSaldosDelegateVirtual.clear()
                // Reviso que las monedas del sistema existan
                if(modeloListaMonedas.rowCount()!==0){

                    modeloLimiteSaldoCuentaCorriente.limpiar()
                    modeloLimiteSaldoCuentaCorriente.buscar(txtCodigoCliente.textoInputBox.trim(),txtTipoCliente.codigoValorSeleccion.trim())

                    // Itero sobre las monedas del sistema y agrego las entradas para setear los saldos
                    for(var i=0; i<modeloListaMonedas.rowCount() ;i++){
                        var limiteSaldo=0.00;
                        for(var j=0; j<modeloLimiteSaldoCuentaCorriente.rowCount() ;j++){
                            var itemData = modeloLimiteSaldoCuentaCorriente.get(j)
                            if(itemData.codigoMoneda===modeloListaMonedas.retornaCodigoMonedaPorIndice(i)){
                                limiteSaldo=itemData.limiteSaldo;
                            }
                        }

                        modeloListaMonedaSaldosDelegateVirtual.append({
                                                                      codigoMoneda:modeloListaMonedas.retornaCodigoMonedaPorIndice(i),
                                                                      descripcionMoneda:modeloListaMonedas.retornaDescripcionMonedaPorIndice(i) ,
                                                                      simboloMoneda:modeloListaMonedas.retornaSimboloMonedaPorIndice(i),
                                                                      limiteSaldo:limiteSaldo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))
                                                                      })
                    }

                    cuadroSeteoSaldoCuentaCorrienteEnCliente.visible=true
                }else{
                    funcionesmysql.mensajeAdvertencia("ERROR: No se encontraron monedas definidas en el sistema.")
                }



            }
        }

    }

    ListModel{
        id: modeloListaMonedaSaldosDelegateVirtual
    }


    CuadroSeteoSaldoCuentaCorrienteEnCliente{
        id:cuadroSeteoSaldoCuentaCorrienteEnCliente
        anchors.fill: parent
        z:9
        visible: false
        onClicCancelar: cuadroSeteoSaldoCuentaCorrienteEnCliente.visible=false
        modeloItems: modeloListaMonedaSaldosDelegateVirtual
        textoBotonCancelar:  "Cancelar"
        textoBotonGuardar:  "Guardar Saldo"

        onClicGuardar: {
            for(var i=0; i<modeloListaMonedaSaldosDelegateVirtual.count ;i++){
                    console.log(modeloListaMonedaSaldosDelegateVirtual.get(i).limiteSaldo)
            }
        }


    }

}

