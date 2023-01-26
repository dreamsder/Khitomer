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


Rectangle {
    id: rectPrincipal
    width: 900; height: 600
    //color: "#041c24"
    color: "#000000"
    clip: true

    property int   opcionEnCurso: 0
    property bool  estadoConexionMysql: true
    property bool  estadoConexionServidor: true

    property string versionKhitomer: "1.17.9"



    property int distanciaEntreBotonesBarraDeTareas: modeloconfiguracion.retornaValorConfiguracion("DISTANCIAENTREBOTONESMENU")

    // setea los permisos de la barra de herramientas del mantenimiento de liquidaciones
    function permisosMantenimientoLiquidaciones(){
        mantenimientoLiquidaciones.botonNuevaLiquidacionVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearLiquidaciones");
        mantenimientoLiquidaciones.botonCrearLiquidacionVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearLiquidaciones");
        mantenimientoLiquidaciones.botonEliminarLiquidacionVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteBorrarLiquidaciones");
    }
    // setea los permisos de la barra de herramientas del mantenimiento de facturacion
    function permisosMantenimientoFacturacion(){
        mantenimientoFactura.botonNuevaFacturaVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearFacturas");
        mantenimientoFactura.botonGuardarFacturaEmitirVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearFacturas");
        mantenimientoFactura.botonGuardarFacturaPendienteVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearFacturas");


        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CLIENTE")=="1"){
            mantenimientoFactura.codigoClienteInputMask="000000;"
            mantenimientoFactura.codigoClienteOpcionesExtrasInputMask="000000;"

        }else{
            mantenimientoFactura.codigoClienteInputMask=""
            mantenimientoFactura.codigoClienteOpcionesExtrasInputMask=""
        }


        mantenimientoFactura.setearVerificoEstadoActivoBotonesGuardar()




    }
    // setea los permisos de la barra de herramientas del mantenimiento de articulos
    function permisosMantenimientoArticulos(){
        mantenimientoArticulos.botonNuevoArticuloVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearArticulos");
        mantenimientoArticulos.botonGuardarArticuloVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearArticulos");
        mantenimientoArticulos.botonEliminarArticuloVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteBorrarArticulos");
        if(modeloconfiguracion.retornaValorConfiguracion("MODO_ARTICULO")=="1"){
            mantenimientoArticulos.codigoArticuloInputMask="000000;"
        }else{
            mantenimientoArticulos.codigoArticuloInputMask=""
        }
    }
    // setea los permisos de la barra de herramientas del mantenimiento de clientes
    function permisosMantenimientoClientes(){
        mantenimientoClientes.botonNuevoClienteVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearClientes");
        mantenimientoClientes.botonGuardarClienteVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearClientes");
        mantenimientoClientes.botonEliminarClienteVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteBorrarClientes");
        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CLIENTE")=="1"){
            mantenimientoClientes.codigoClienteInputMask="000000;"
        }else{
            mantenimientoClientes.codigoClienteInputMask=""
        }



    }



    // setea los permisos de la barra de herramientas del mantenimiento de lista de precios
    function permisosMantenimientoListaDePrecios(){
        mantenimientoListaPrecios.botonNuevaListaDePrecioVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearLiquidaciones");
        mantenimientoListaPrecios.botonGuardarListaDePrecioVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearLiquidaciones");
        mantenimientoListaPrecios.botonEliminarListaDePrecioVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteBorrarLiquidaciones");
        mantenimientoListaPrecios.botonCambioRapidoDePreciosVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCambioRapidoDePrecios");
        if(modeloconfiguracion.retornaValorConfiguracion("MODO_ARTICULO")=="1"){
            mantenimientoListaPrecios.codigoArticuloDesdeHastaCuadroListaPrecioInputMask="000000;"
        }else{
            mantenimientoListaPrecios.codigoArticuloDesdeHastaCuadroListaPrecioInputMask=""
        }


    }

    // setea los permisos del mantenimiento de reportes
    function permisosMantenimientoReportes(){
        mantenimientoReportes.botonGenerarPDFVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteExportarAPDF");
        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CLIENTE")=="1"){
            mantenimientoReportes.codigoCodigoClienteReporteInputMask="000000;"
            mantenimientoReportes.codigoCodigoProveedorReporteInputMask="000000;"
        }else{
            mantenimientoReportes.codigoCodigoClienteReporteInputMask=""
            mantenimientoReportes.codigoCodigoProveedorReporteInputMask=""
        }
        if(modeloconfiguracion.retornaValorConfiguracion("MODO_ARTICULO")=="1"){
            mantenimientoReportes.codigoArticuloReporteInputMask="000000;"
        }else{
            mantenimientoReportes.codigoArticuloReporteInputMask=""
        }


    }


    // setea los permisos del mantenimiento de reportes
    function permisosMantenimientoCuentacorriente(){

        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CLIENTE")=="1"){
            mantenimientoCuentasCorriente.codigoClienteInputMask="000000;"
        }else{
            mantenimientoCuentasCorriente.codigoClienteInputMask=""
        }
    }



    function setearTipoDocumentoEnMantenimientoFacturacion(_codigoTipoDeDocumento,_observacionesRecabadas){
        mantenimientoFactura.setearTipoDeDocumento(_codigoTipoDeDocumento,_observacionesRecabadas)
    }

    function mostrarMantenimientos(posicion,lado){

        if(posicion==0){

            if(lado=="home"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarLiquidaciones")){

                    permisosMantenimientoLiquidaciones()
                    mantenimientoLiquidaciones.enabled=true
                    mantenimientoLiquidaciones.visible=true

                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false

                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false

                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false

                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false

                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=0

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0

                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    modeloListaVendedores.clearUsuarios()
                    modeloListaVendedores.buscarUsuarios("esVendedor=","1")

                }else if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarFacturacion")){

                    permisosMantenimientoFacturacion()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=true
                    mantenimientoFactura.visible=true

                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=1

                    modeloLiquidacionesComboBox.clearLiquidaciones()
                    modeloLiquidacionesComboBox.buscarLiquidacion("1=","1")

                    modeloListaVendedores.clearUsuarios()
                    modeloListaVendedores.buscarUsuarios("esVendedor=","1")


                    btnLateralBusquedas.z=0
                    rowMenusDelSistema.z=-1
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")


                }else if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarClientes")){
                    mantenimientoClientes.enabled=true
                    permisosMantenimientoClientes()


                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false

                    mantenimientoClientes.visible=true
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=2
                    btnLateralBusquedas.z=0
                    rowMenusDelSistema.z=-1
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    var cantidadRegistrosListaPrecioCliente=mantenimientoClientes.retornaCantidadRegistrosListaPrecioCliente()

                    if(cantidadRegistrosListaPrecioCliente=="" || cantidadRegistrosListaPrecioCliente=="0"){
                        mantenimientoClientes.cargarListasDePrecioCliente("","")
                    }

                }else if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos")){

                    permisosMantenimientoArticulos()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=true
                    mantenimientoArticulos.visible=true
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=3

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    modeloListaProveedor.clearClientes();
                    modeloListaProveedor.buscarCliente("tipoCliente=","2")


                    modeloListasPreciosComboBox.clearListasPrecio()
                    modeloListasPreciosComboBox.buscarListasPrecio("1=","1")




                }else if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarListaPrecios")){

                    permisosMantenimientoListaDePrecios()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false

                    mantenimientoListaPrecios.enabled=true
                    mantenimientoListaPrecios.visible=true
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=4

                    if(mantenimientoListaPrecios.opcionesExtrasActivas){

                        rowMenusDelSistema.z=-1
                        btnLateralBusquedas.z=0

                        menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
                    }else{
                        rowMenusDelSistema.z=0
                        btnLateralBusquedas.z=0
                        menulista1.enabled=false
                    }
                }else{


                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=0

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
                }




            }else if(lado=="derecha"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarFacturacion")){
                    permisosMantenimientoFacturacion()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false

                    mantenimientoFactura.enabled=true
                    mantenimientoFactura.visible=true

                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=1

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    modeloLiquidacionesComboBox.clearLiquidaciones()
                    modeloLiquidacionesComboBox.buscarLiquidacion("1=","1")

                    modeloListaVendedores.clearUsuarios()
                    modeloListaVendedores.buscarUsuarios("esVendedor=","1")



                }else{
                    mostrarMantenimientos(1,"derecha")
                }



            }
        }else if(posicion==1){
            if(lado=="izquierda"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarLiquidaciones")){
                    permisosMantenimientoLiquidaciones()

                    mantenimientoLiquidaciones.enabled=true
                    mantenimientoLiquidaciones.visible=true
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=0

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    modeloListaVendedores.clearUsuarios()
                    modeloListaVendedores.buscarUsuarios("esVendedor=","1")
                }



            }else if(lado=="derecha"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarClientes")){
                    mantenimientoClientes.enabled=true
                    permisosMantenimientoClientes()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false

                    mantenimientoClientes.visible=true
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=2

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    var cantidadRegistrosListaPrecioCliente=mantenimientoClientes.retornaCantidadRegistrosListaPrecioCliente()

                    if(cantidadRegistrosListaPrecioCliente=="" || cantidadRegistrosListaPrecioCliente=="0"){
                        mantenimientoClientes.cargarListasDePrecioCliente("","")
                    }
                }else{
                    mostrarMantenimientos(2,"derecha")
                }
            }


        }else if(posicion==2){
            if(lado=="izquierda"){


                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarFacturacion")){

                    permisosMantenimientoFacturacion()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=true
                    mantenimientoFactura.visible=true
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=1

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    modeloLiquidacionesComboBox.clearLiquidaciones()
                    modeloLiquidacionesComboBox.buscarLiquidacion("1=","1")

                    modeloListaVendedores.clearUsuarios()
                    modeloListaVendedores.buscarUsuarios("esVendedor=","1")


                }else{
                    mostrarMantenimientos(1,"izquierda")
                }



            }else if(lado=="derecha"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos")){
                    permisosMantenimientoArticulos()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=true
                    mantenimientoArticulos.visible=true
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=3

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    modeloListaProveedor.clearClientes();
                    modeloListaProveedor.buscarCliente("tipoCliente=","2")

                    modeloListasPreciosComboBox.clearListasPrecio()
                    modeloListasPreciosComboBox.buscarListasPrecio("1=","1")

                }else{
                    mostrarMantenimientos(3,"derecha")
                }

            }


        }else if(posicion==3){
            if(lado=="izquierda"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarClientes")){

                    mantenimientoClientes.enabled=true
                    permisosMantenimientoClientes()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.visible=true
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=2

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    var cantidadRegistrosListaPrecioCliente=mantenimientoClientes.retornaCantidadRegistrosListaPrecioCliente()

                    if(cantidadRegistrosListaPrecioCliente=="" || cantidadRegistrosListaPrecioCliente=="0"){
                        mantenimientoClientes.cargarListasDePrecioCliente("","")
                    }
                }else{

                    mostrarMantenimientos(2,"izquierda")

                }

            }else if(lado=="derecha"){


                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarListaPrecios")){
                    permisosMantenimientoListaDePrecios()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=true
                    mantenimientoListaPrecios.visible=true
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=4

                    if(mantenimientoListaPrecios.opcionesExtrasActivas){

                        rowMenusDelSistema.z=-1
                        btnLateralBusquedas.z=0
                        menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
                    }else{
                        btnLateralBusquedas.z=0
                        rowMenusDelSistema.z=-1
                        menulista1.enabled=false
                    }
                }


            }
        }else if(posicion==4){
            if(lado=="izquierda"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos")){
                    permisosMantenimientoArticulos()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=true
                    mantenimientoArticulos.visible=true
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    modeloListaProveedor.clearClientes();
                    modeloListaProveedor.buscarCliente("tipoCliente=","2")

                    modeloListasPreciosComboBox.clearListasPrecio()
                    modeloListasPreciosComboBox.buscarListasPrecio("1=","1")

                    opcionEnCurso=3
                    btnLateralBusquedas.z=0
                    rowMenusDelSistema.z=-1
                }else{

                    mostrarMantenimientos(3,"izquierda")
                }
            }else if(lado=="derecha"){


                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarDocumentos")){

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=true
                    mantenimientoDocumentos.visible=true
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false

                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=5

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                }

            }
        }else if(posicion==5){
            if(lado=="izquierda"){


                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarListaPrecios")){
                    permisosMantenimientoListaDePrecios()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=true
                    mantenimientoListaPrecios.visible=true
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=4

                    if(mantenimientoListaPrecios.opcionesExtrasActivas){

                        rowMenusDelSistema.z=-1
                        btnLateralBusquedas.z=0
                        menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
                    }else{
                        btnLateralBusquedas.z=0
                        rowMenusDelSistema.z=-1
                        menulista1.enabled=false

                    }
                }else{
                    mostrarMantenimientos(3,"izquierda")
                }

            }else if(lado=="derecha"){


                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarReportes")){
                    permisosMantenimientoReportes()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=true
                    mantenimientoReportes.visible=true
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=6
                    btnLateralBusquedas.z=0
                    rowMenusDelSistema.z=-1

                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                }

            }
        }else if(posicion==6){
            if(lado=="izquierda"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarDocumentos")){


                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=true
                    mantenimientoDocumentos.visible=true
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=5

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                }else{
                    mostrarMantenimientos(4,"izquierda")
                }



            }else if(lado=="derecha"){


                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarCuentaCorriente")){

                    permisosMantenimientoCuentacorriente()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=true
                    mantenimientoCuentasCorriente.visible=true

                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=7

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                }

            }
        }else if(posicion==7){
            if(lado=="izquierda"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarReportes")){
                    permisosMantenimientoReportes()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=true
                    mantenimientoReportes.visible=true
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false

                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false


                    opcionEnCurso=6
                    btnLateralBusquedas.z=0
                    rowMenusDelSistema.z=-1

                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                }else{
                    mostrarMantenimientos(5,"izquierda")
                }



            }else if(lado=="derecha"){
                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarPromociones")){

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false

                    mantenimientoPromociones.enabled=true
                    mantenimientoPromociones.visible=true

                    opcionEnCurso=8

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                }

            }
        }
         else if(posicion==8){
                    if(lado=="izquierda"){

                        if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarCuentaCorriente")){

                            permisosMantenimientoCuentacorriente()

                            mantenimientoLiquidaciones.enabled=false
                            mantenimientoLiquidaciones.visible=false
                            mantenimientoFactura.enabled=false
                            mantenimientoFactura.visible=false
                            mantenimientoClientes.enabled=false
                            mantenimientoClientes.visible=false
                            mantenimientoArticulos.enabled=false
                            mantenimientoArticulos.visible=false
                            mantenimientoListaPrecios.enabled=false
                            mantenimientoListaPrecios.visible=false
                            mantenimientoDocumentos.enabled=false
                            mantenimientoDocumentos.visible=false
                            mantenimientoReportes.enabled=false
                            mantenimientoReportes.visible=false
                            mantenimientoCuentasCorriente.enabled=true
                            mantenimientoCuentasCorriente.visible=true

                            mantenimientoPromociones.enabled=false
                            mantenimientoPromociones.visible=false

                            opcionEnCurso=7

                            rowMenusDelSistema.z=-1
                            btnLateralBusquedas.z=0
                            menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                        }else{
                            mostrarMantenimientos(6,"izquierda")
                        }




                    }else if(lado=="derecha"){


                    }
                }





    }

    Rectangle {
        id: navegador
        x: 60
        y: 60
        height: 480
        color: "#525151"
        radius: 0
        z: 1
        anchors.right: parent.right
        anchors.rightMargin: -20
        anchors.top: parent.top
        anchors.topMargin: 10
        opacity: 1
        anchors.left: parent.left
        anchors.leftMargin: 45
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        enabled: false


        MantenimientoLiquidaciones{
            id: mantenimientoLiquidaciones
            z: 1
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            enabled: true
            visible: true
        }

        MantenimientoFacturacion{
            id: mantenimientoFactura
            x: 5
            y: 5
            z: 1
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5
            enabled: false
            visible: false
        }

        MantenimientoClientes {
            id: mantenimientoClientes
            x: 5
            y: 5
            z: 1
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5
            enabled: false
            visible: false
        }

        MantenimientoArticulos {
            id: mantenimientoArticulos
            z: 1
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            enabled: false
            visible: false
        }

        MantenimientoListasDePrecios{
            id: mantenimientoListaPrecios
            z: 1
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            enabled: false
            visible: false

        }

        MantenimientoDocumentos{
            id: mantenimientoDocumentos
            z: 1
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            enabled: false
            visible: false

        }


        MantenimientoReportes{
            id: mantenimientoReportes
            z: 1
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            enabled: false
            visible: false

        }

        MantenimientoCuentasCorriente{
            id: mantenimientoCuentasCorriente
            z: 1
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            enabled: false
            visible: false

        }

        MantenimientoPromociones{
            id: mantenimientoPromociones
            z: 1
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            enabled: false
            visible: false
        }



        Row {
            id: rowMenusDelSistema
            x: 0
            y: 0
            height: 30
            anchors.leftMargin: (navegador.width*-1)-40
            anchors.right: parent.right
            anchors.rightMargin: 900
            anchors.left: navegador.right
            z: 1
            anchors.top: parent.top
            anchors.topMargin: 0
            spacing: 20

            onZChanged: {

                menulista1.rectPrincipalVisible=false
            }

            MenuLista {
                id: menulista1
                z: 1
                textoBoton: qsTr("    ")
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Notebook.png"
                visible: menulista1.enabled
                onClic: {
                    etUsuario.z=0
                    btnLateralBusquedas.z=0
                    rowMenusDelSistema.z=1
                    etUsuario.cerrarComboBox()

                }
            }
        }



        Text {
            id: txtMensajeErrorSinConexionMysql
            x: 510
            y: 185
            text: ""
            z: 0
            font.bold: true
            styleColor: "#747c93"
            style: Text.Outline
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.NoWrap
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 29
        }

        Text {
            id: txtMensajeErrorSinConexionServidor
            x: 512
            height: 34
            text: ""
            anchors.top: txtMensajeErrorSinConexionMysql.bottom
            anchors.topMargin: 20
            font.pixelSize: 29
            anchors.horizontalCenter: parent.horizontalCenter
            style: Text.Outline
            wrapMode: Text.NoWrap
            styleColor: "#747c93"
            font.bold: true
            z: 0
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }



  /*  BotonFlecha {
        id: botonflechaAvanzar
        x: 121
        y: 555
        toolTip: ""
        border.color: "white"
        anchors.bottom: botonflechaRetroceder.top
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        anchors.left: parent.left

        onClic: {
            mostrarMantenimientos(opcionEnCurso,"derecha")
        }
    }
    BotonFlecha {
        id: botonflechaRetroceder
        x: 78
        y: 555
        color: "#00faf6f6"
        toolTip: ""
        border.color: "white"
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: botonHome.top
        anchors.bottomMargin: 30
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaIzquierda.png"


        onClic: {
            mostrarMantenimientos(opcionEnCurso,"izquierda")

        }
    }

    BotonBarraDeHerramientas {
        id: botonHome
        y: 560
        width: 25
        height: 25
        toolTip: ""
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Home.png"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 10

        onClic: {

            mostrarMantenimientos(0,"home")
        }
    }*/

    Rectangle {
        id: rectLogin        
        color: rectPrincipal.color
        radius: 0
        visible: true
        opacity: 1
        anchors.rightMargin: -20
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        z: 7

        focus: true
        onFocusChanged: txtNombreDeUsuario.tomarElFoco()

        /* Image {
            id: imageLogin
            visible: true
            fillMode: Image.Tile
            anchors.fill: parent

            focus: false*/

        MouseArea {
            id: mouse_area1
            anchors.fill: parent
            hoverEnabled: true


            Rectangle {
                id: rectAcceso
                x: 184
                y: 19
                width: 376
                height: 200
                radius: 4
                clip: false
                color: "#1d7195"
                border.color: "#1d7195"
                focus: false
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

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
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
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
                    anchors.leftMargin: 15
                    anchors.bottomMargin: -1
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.topMargin: 0
                }


                Text {
                    id: txtAcceso
                    color: "#fdfbfb"
                    text: qsTr("Acceso")
                    font.family: "Arial"
                    style: Text.Normal
                    font.italic: false
                    anchors.left: parent.left
                    anchors.leftMargin: 45
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    font.bold: false
                    font.pixelSize: 37
                    focus: false
                }

                TextInputSimple {
                    id: txtNombreDeUsuario
                    x: 20
                    y: 83
                    width: 230
                 //   height: 35
                    textoDeFondo: qsTr("login de usuario")
                    textoInputBox: ""
                    anchors.horizontalCenter: parent.horizontalCenter
                    echoMode: 0
                    textoTitulo: qsTr("Usuario:")
                    botonBorrarTextoVisible: true



                    onEnter: txtContraseniaDeUsuario.tomarElFoco()

                    onTabulacion: txtContraseniaDeUsuario.tomarElFoco()


                }

                TextInputSimple {
                    id: txtContraseniaDeUsuario
                    x: 20
                    y: 126
                    width: 230
                //    height: 35
                    largoMaximo: 25
                    textoDeFondo: qsTr("clave privada de acceso")
                    echoMode: 2
                    anchors.horizontalCenter: parent.horizontalCenter
                    textoTitulo: qsTr("Contraseña:")
                    botonBorrarTextoVisible: true


                    onEnter: {

                        if(modeloUsuarios.conexionUsuario(txtNombreDeUsuario.textoInputBox.toString().trim(),txtContraseniaDeUsuario.textoInputBox.toString().trim())){
                            //rectLoginOpacidadOut.stop()
                            //rectAccesoWHOut.stop()
                           // rectLoginOpacidadOut.start()
                            //rectAccesoWHOut.start()
                            navegador.enabled=true
                            timeReajustarGradient.stop()
                            rectLogin.enabled=false
                            rectLogin.visible=false
                            rectAcceso.visible=rectLogin.visible


                            etUsuario.setearUsuario(modeloUsuarios.retornaNombreUsuarioLogueado(txtNombreDeUsuario.textoInputBox.trim()))

                            //Mantenimientos
                            mantenimientoLiquidaciones.enabled= modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarLiquidaciones")
                            tagLiquidaciones.enabled=mantenimientoLiquidaciones.enabled;
                            tagLiquidaciones.visible=mantenimientoLiquidaciones.enabled;

                            tagFacturacion.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarFacturacion")
                            tagFacturacion.visible=tagFacturacion.enabled

                            mantenimientoClientes.enabled= modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarClientes")
                            tagClientes.enabled=mantenimientoClientes.enabled
                            tagClientes.visible=mantenimientoClientes.enabled

                            mantenimientoListaPrecios.enabled= modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarListaPrecios")
                            tagListaDePrecios.enabled=mantenimientoListaPrecios.enabled
                            tagListaDePrecios.visible=mantenimientoListaPrecios.enabled

                            mantenimientoArticulos.enabled= modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos")
                            tagArticulos.enabled=mantenimientoArticulos.enabled
                            tagArticulos.visible=mantenimientoArticulos.enabled

                            mantenimientoDocumentos.enabled= modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarDocumentos")
                            tagDocumentos.enabled=mantenimientoDocumentos.enabled
                            tagDocumentos.visible=mantenimientoDocumentos.enabled

                            mantenimientoReportes.enabled= modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarReportes")
                            tagReportes.enabled=mantenimientoReportes.enabled
                            tagReportes.visible=mantenimientoReportes.enabled

                            mantenimientoCuentasCorriente.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarCuentaCorriente")
                            tagCuentaCorriente.enabled=mantenimientoCuentasCorriente.enabled
                            tagCuentaCorriente.visible=mantenimientoCuentasCorriente.enabled

                            mantenimientoPromociones.enabled= false// modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarPromociones")
                            //tagPromociones.enabled=mantenimientoPromociones.enabled
                            //tagPromociones.visible=mantenimientoPromociones.enabled




                            menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")



                            if(menulista1.enabled)
                                menulista1.cargarValores()

                            mostrarMantenimientos(0,"home")

                            mantenimientoFactura.setearVendedorDelSistema()

                            modeloListaTipoDocumentosComboBox.limpiarListaTipoDocumentos()
                            modeloListaTipoDocumentosComboBox.buscarTipoDocumentos("1=","1",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))

                            modeloReportesMenuComboBox.limpiarListaReportesMenu()
                            modeloReportesMenuComboBox.buscarReportesMenu("1=","1",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))


                            if(modeloReportes.retornaSiReportaEstaHabilitadoEnPerfil("22",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))){
                                var cantidadSinStock=modeloArticulos.retornaCantidadArticulosSinStock()
                                if(cantidadSinStock!="0"){
                                    btnAvisoFaltaStock.textoBoton=cantidadSinStock
                                    btnAvisoFaltaStock.timerRuning=true
                                    btnAvisoFaltaStock.visible=true
                                }else{
                                    btnAvisoFaltaStock.visible=false
                                    btnAvisoFaltaStock.timerRuning=false
                                }
                            }



                        }else{
                            timeReajustarGradient.stop()
                            rectAcceso.color="#ba3e2b"
                            rectAcceso.border.color="#ba3e2b"
                            rectangle2.color="#ba3e2b"
                            timeReajustarGradient.start()

                        }

                    }
                    onTabulacion: txtNombreDeUsuario.tomarElFoco()
                }

                Image {
                    id: imageIconoLogin
                    x: 308
                    width: 51
                    height: 51
                    smooth: true
                    opacity: 0.680
                    anchors.right: parent.right
                    anchors.rightMargin: 15
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    asynchronous: true
                    focus: false
                    source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Acceso.png"
                }

                Rectangle {
                    id: rectLiniaAcceso
                    height: 1
                    color: "#c2bfbf"
                    radius: 1
                    anchors.top: parent.top
                    anchors.topMargin: 72
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    focus: false
                }

                Rectangle {
                    id: rectangle3
                    color: rectAcceso.color
                    border.color: rectAcceso.color
                    z: 1
                    anchors.left: parent.right
                    anchors.leftMargin: -30
                    anchors.top: parent.bottom
                    anchors.topMargin: -30
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                }
            }

            Rectangle {
                id: rectLiniaAcceso1
                x: -38
                y: 398
                height: 1
                color: "#c2bfbf"
                radius: 1
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                anchors.rightMargin: 70
                anchors.right: parent.right
                anchors.leftMargin: 50
                anchors.left: parent.left
                focus: false
            }

            Rectangle {
                id: rectLiniaAcceso2
                x: -38
                y: -161
                height: 1
                color: "#c2bfbf"
                radius: 1
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.rightMargin: 70
                anchors.right: parent.right
                anchors.leftMargin: 50
                anchors.left: parent.left
                focus: false
            }
            
            
            Image {
                property string fechaImportante:funcionesmysql.retornaFechaImportante()
                id: imgLogoKhitomer
                smooth: true
                width: {
                    if(fechaImportante=="reyes_magos"){
                        150
                    }else{
                        96
                    }
                }
                
                height: 96
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                anchors.right: parent.right
                anchors.rightMargin: 70
                z: 1
                asynchronous: true
                enabled: false
                source:   {
                    
                    if(fechaImportante=="navidad"){
                        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1"){
                            "qrc:/imagenes/qml/ProyectoQML/Imagenes/LogoKhitomerCFE-20-03-2018_128pxNavidad.png"
                        }else{
                            "qrc:/imagenes/qml/ProyectoQML/Imagenes/navidad.png"
                        }
                    }
                    else if(fechaImportante=="reyes_magos"){
                        "qrc:/imagenes/qml/ProyectoQML/Imagenes/reyesmagos.png"
                    }
                    else if(fechaImportante=="dia_normal"){
                        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1"){
                            "qrc:/imagenes/qml/ProyectoQML/Imagenes/LogoKhitomerCFE-20-03-2018_128px.png"
                        }else{
                            "qrc:/imagenes/qml/ProyectoQML/Imagenes/LogoKhitomer-19-07-2016_128px.png"
                        }
                    }
                    else{
                        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1"){
                            "qrc:/imagenes/qml/ProyectoQML/Imagenes/LogoKhitomerCFE-20-03-2018_128px.png"
                        }else{
                            "qrc:/imagenes/qml/ProyectoQML/Imagenes/LogoKhitomer-19-07-2016_128px.png"
                        }
                    }
                }
            }
            
            Image {
                id: imgLogoQt
                width: 188
                height: 45
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Built_with_Qt_logo_RGB.png"
                anchors.left: parent.left
                anchors.leftMargin: 50
                anchors.bottomMargin: 30
                asynchronous: true
                z: 1
                smooth: true
                enabled: false
                anchors.bottom: parent.bottom
            }

            Text {
                id: txtVersionKhitomer
                color: "#ffffff"
                text: qsTr("Versión: "+versionKhitomer)
                anchors.right: rectLiniaAcceso1.right
                anchors.rightMargin: 1
                anchors.top: rectLiniaAcceso1.bottom
                anchors.topMargin: 2
                style: Text.Normal
                font.bold: true
                textFormat: Text.AutoText
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 10
            }

            


        }








        Timer{
            id:timeReajustarGradient
            interval: 2000
            repeat: false
            running:false
            onTriggered: {

                rectAcceso.color="#1d7195"
                rectAcceso.border.color="#1d7195"
                rectangle2.color="#1d7195"


            }

        }
    }

    Row {
        id: rowTagsInferior
        spacing: 8
        anchors.top: navegador.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 45
        //enabled: false

        Tag {
            id: tagLiquidaciones
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevaLiquidacion.png"
            texto: qsTr("Cajas")
            _gradietMedioIndicador:"#4c6bb5"
            indicadorColor: "#4a68b5"
            toolTip: ""
            opacidadPorDefecto: mantenimientoLiquidaciones.visible ? "1" : "0.3"
            onClic: {
                mostrarMantenimientos(0,"home")
            }
        }

        Tag {
            id: tagFacturacion
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevaFacturacion.png"
            texto: qsTr("Facturación")
            _gradietMedioIndicador:"#db4d4d"
            opacidadPorDefecto: mantenimientoFactura.visible ? "1" : "0.3"
            toolTip: ""
            indicadorColor: "#db4d4d"
            onClic: {
                mostrarMantenimientos(0,"derecha")
            }
        }

        Tag {
            id: tagClientes
            texto: qsTr("Cliente/Proveedor")
            toolTip: ""
            indicadorColor: "#3ca239"
            opacidadPorDefecto: mantenimientoClientes.visible ? "1" : "0.3"
            _gradietMedioIndicador:"#3ca239"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevoCliente.png"
            onClic: {
                mostrarMantenimientos(1,"derecha")
            }
        }

        Tag {
            id: tagArticulos
            visible: true
            texto: qsTr("Artículos")
            opacidadPorDefecto: mantenimientoArticulos.visible ? "1" : "0.3"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevoArticulo.png"
            toolTip: ""
            indicadorColor: "#27abb4"
            _gradietMedioIndicador:"#27acb3"
            onClic: {
                mostrarMantenimientos(2,"derecha")
            }
        }

        Tag {
            id: tagListaDePrecios
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevaListaDePrecios.png"
            texto: qsTr("Lista de precios")
            _gradietMedioIndicador:"#f8a218"
            opacidadPorDefecto: mantenimientoListaPrecios.visible ? "1" : "0.3"
            toolTip: ""
            indicadorColor: "#f89e16"
            onClic: {
                mostrarMantenimientos(3,"derecha")
            }
        }

        Tag {
            id: tagDocumentos
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Documentos.png"
            texto: qsTr("Documentos")
            _gradietMedioIndicador:"#7a14be"
            indicadorColor: "#7e0cc5"
            toolTip: ""
            opacidadPorDefecto: mantenimientoDocumentos.visible ? "1" : "0.3"

            onClic: {

                mostrarMantenimientos(4,"derecha")

            }


        }

        Tag {
            id: tagReportes
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Reportes.png"
            texto: qsTr("Reportes")
            toolTip: ""
            _gradietMedioIndicador:"#e235dd"
            indicadorColor: "#e235dd"
            opacidadPorDefecto: mantenimientoReportes.visible ? "1" : "0.3"
            onClic: {

                mostrarMantenimientos(5,"derecha")

            }
        }

        Tag {
            id: tagCuentaCorriente
            texto: qsTr("Cuentas corrientes")
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/CuentasCorrientes.png"
            toolTip: ""
            _gradietMedioIndicador: "#4c6bb5"
            indicadorColor: "#880000"
            opacidadPorDefecto: mantenimientoCuentasCorriente.visible ? "1" : "0.3"

            onClic: {

                mostrarMantenimientos(6,"derecha")

            }
        }


    }

   /* EtiquetaUsuario {
        id: etUsuario
        //x: 742
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 10
        z: 1
    }*/


    EtiquetaUsuario {
        id: etUsuario
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 85
        anchors.left: parent.left
        anchors.leftMargin: -35
        z: 1
        onClic: {
            if(visibleComboBox){
                etUsuario.z=1
            }else{
                etUsuario.z=0
            }


         }
    }


   /* Timer{
        id:timeVerificaConectividadMysql
        interval: 5432//Milisegundos para realizar una consulta. La idea es que no se pise con otra cosulta a la base. Hasta que no implemente los threads
        repeat: false
        running: false
        onTriggered: {


            estadoConexionMysql=funcionesmysql.consutlaMysqlEstaViva()
            if(!estadoConexionMysql){

                txtMensajeErrorSinConexionMysql.color="#212121"
                txtMensajeErrorSinConexionMysql.styleColor= "#747c93"

                txtMensajeErrorSinConexionMysql.text=qsTr("No hay conexion con la base de datos MySql del servidor.")
                mostrarMantenimientos(0,"home")


            }else{

                txtMensajeErrorSinConexionMysql.color="#148826"
                txtMensajeErrorSinConexionMysql.styleColor= "#171a25"
                txtMensajeErrorSinConexionMysql.text=qsTr("Conexion con base de datos ok, puede continuar operando.")
            }

            etUsuario.setarEstadoMysql(estadoConexionMysql)

        }

    }*/

    /*Timer{
        id:timeReseteaConexionMysql
        interval: 25212345
        repeat: true
        running: true
        onTriggered: {
            //resetea cada 7 horas aproximadamente
            funcionesmysql.reseteaConexionMysql()
        }
    }*/


   /* Timer{
        id:timeVerificaConectividadServidor
        interval: 60000
        repeat: false
        running: false
        onTriggered: {

            estadoConexionServidor=funcionesmysql.consultaPingServidor()
            if(!estadoConexionServidor){

                txtMensajeErrorSinConexionServidor.color="#212121"
                txtMensajeErrorSinConexionServidor.styleColor= "#747c93"

                txtMensajeErrorSinConexionServidor.text=qsTr("No hay conexion con el servidor, revise conectividad.")
                mostrarMantenimientos(0,"home")

            }else{

                txtMensajeErrorSinConexionServidor.color="#148826"
                txtMensajeErrorSinConexionServidor.styleColor= "#171a25"
                txtMensajeErrorSinConexionServidor.text=qsTr("Conexion con servidor ok.")
            }

            etUsuario.setarEstadoServidor(estadoConexionServidor)

        }

    }*/

    BotonLateral {
        id: btnAvisoFaltaStock
        z: 0
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.left: parent.left
        anchors.leftMargin: 8
        visible: false
        onClic: {
            mantenimientoReportes.seleccionarReporte(22)
            mantenimientoReportes.cargarReporte(22)
            mostrarMantenimientos(5,"derecha")
        }

        /*Component.onCompleted: {

            if(modeloReportes.retornaSiReportaEstaHabilitadoEnPerfil("22",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))){
                var cantidadSinStock=modeloArticulos.retornaCantidadArticulosSinStock()
                if(cantidadSinStock!="0"){
                    btnAvisoFaltaStock.textoBoton=cantidadSinStock
                    btnAvisoFaltaStock.timerRuning=true
                    btnAvisoFaltaStock.visible=true
                }else{
                    btnAvisoFaltaStock.visible=false
                    btnAvisoFaltaStock.timerRuning=false
                }
            }


        }*/
    }

    Timer{
        running:true
        interval: 7254321
        repeat: true
        onTriggered: {
            if(modeloReportes.retornaSiReportaEstaHabilitadoEnPerfil("22",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))){
                var cantidadSinStock=modeloArticulos.retornaCantidadArticulosSinStock()
                if(cantidadSinStock!="0"){
                    btnAvisoFaltaStock.textoBoton=cantidadSinStock
                    btnAvisoFaltaStock.timerRuning=true
                    btnAvisoFaltaStock.visible=true
                }else{
                    btnAvisoFaltaStock.visible=false
                    btnAvisoFaltaStock.timerRuning=false
                }
            }
        }
    }

    BotonLateralBusquedas {
        id: btnLateralBusquedas
        width: 40
        height: 40
        visible: true
        rectanguloSecundarioVisible: false
        opacidad: 0.700
        anchors.top: btnAvisoFaltaStock.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 3
        rectPrincipalVisible: false
        onClic:  {
            rowMenusDelSistema.z=-1
            btnLateralBusquedas.z=1

        }
    }

   /* Row {
        id: rowTagsSuperior
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        Tag {
            id: tagCuentaCorriente
            texto: qsTr("Cuentas corrientes")
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/CuentasCorrientes.png"
            toolTip: ""
            _gradietMedioIndicador: "#4c6bb5"
            indicadorColor: "#880000"
            opacidadPorDefecto: mantenimientoCuentasCorriente.visible ? "1" : "0.3"

            onClic: {

                mostrarMantenimientos(6,"derecha")

            }
        }

        Tag {            
            id: tagPromociones
            texto: qsTr("Promociones")
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/MantenimientoPromociones.png"
            toolTip: ""
            _gradietMedioIndicador: "#CDDC39"
            indicadorColor: "#CDDC39"
            opacidadPorDefecto: mantenimientoPromociones.visible ? "1" : "0.3"

            onClic: {

                mostrarMantenimientos(7,"derecha")

            }
        }





        anchors.left: parent.left
        spacing: 5
        anchors.leftMargin: 125
        anchors.topMargin: 15
        anchors.bottom: navegador.top
        anchors.top: parent.top
    }*/




}



