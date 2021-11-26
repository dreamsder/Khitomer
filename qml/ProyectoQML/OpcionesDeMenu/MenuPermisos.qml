/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2021>  <Cristian Montano>

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
import "../Listas"

Rectangle {
    id: rectPrincipalMenuPermisos
    width: 800
    height: 700
    color: "#00000000"
    smooth: true


    function cargarTipoDocumentos(_codigoPerfil){

        //Documentos por perfil
        cbxDocumentosPorPerfil.modeloItems=modeloListaTipoDocumentosVirtual
        modeloListaTipoDocumentosVirtual.clear()

        //Reportes por perfil
        cbxReportesPorPerfil.modeloItems=modeloListaReportesVirtual
        modeloListaReportesVirtual.clear()



        for(var i=0; i<modeloGenericoComboboxTipoDocumento.rowCount();i++){


            if(_codigoPerfil=="" || _codigoPerfil=="-1"){
                modeloListaTipoDocumentosVirtual.append({
                                                            codigoItem: modeloGenericoComboboxTipoDocumento.retornarCodigoItem(i),
                                                            descripcionItem: modeloGenericoComboboxTipoDocumento.retornarDescripcionItem(i),
                                                            checkBoxActivo: modeloGenericoComboboxTipoDocumento.retornarCheckBoxActivo(i),
                                                            codigoTipoItem:"0",
                                                            descripcionItemSegundafila:"",
                                                            valorItem:"0",
                                                            serieDoc:""

                                                        })
            }else{
                modeloListaTipoDocumentosVirtual.append({
                                                            codigoItem: modeloGenericoComboboxTipoDocumento.retornarCodigoItem(i),
                                                            descripcionItem: modeloGenericoComboboxTipoDocumento.retornarDescripcionItem(i),
                                                            checkBoxActivo: modeloListaTipoDocumentosComboBox.retornaTipoDocumentoActivoPorPerfil(modeloGenericoComboboxTipoDocumento.retornarCodigoItem(i),_codigoPerfil),
                                                            codigoTipoItem:"0",
                                                            descripcionItemSegundafila:"",
                                                            valorItem:"0",
                                                            serieDoc:""
                                                        })


                /*
                modeloListaTipoDocumentosVirtual.append({
                                                            codigoItem: modeloGenericoComboboxTipoDocumento.retornarCodigoItem(i),
                                                            descripcionItem: modeloGenericoComboboxTipoDocumento.retornarDescripcionItem(i),
                                                            checkBoxActivo: modeloListaTipoDocumentosComboBox.retornaTipoDocumentoActivoPorPerfil(modeloGenericoComboboxTipoDocumento.retornarCodigoItem(i),_codigoPerfil),
                                                            codigoTipoItem:"0",
                                                            valorItem:"0",
                                                            serieDoc:""
                                                        })


*/



            }
        }


        //Carga reportes
        for(var o=0; o<modeloGenericoComboboxReportesPermisos.rowCount();o++){

            if(_codigoPerfil=="" || _codigoPerfil=="-1"){
                modeloListaReportesVirtual.append({
                                                      codigoItem: modeloGenericoComboboxReportesPermisos.retornarCodigoItem(o),
                                                      descripcionItem: modeloGenericoComboboxReportesPermisos.retornarDescripcionItem(o),
                                                      checkBoxActivo: modeloGenericoComboboxReportesPermisos.retornarCheckBoxActivo(o),
                                                      codigoTipoItem:"0",
                                                      descripcionItemSegundafila:"",
                                                      valorItem:"0",
                                                      serieDoc:""

                                                  })
            }else{
                modeloListaReportesVirtual.append({
                                                      codigoItem: modeloGenericoComboboxReportesPermisos.retornarCodigoItem(o),
                                                      descripcionItem:modeloGenericoComboboxReportesPermisos.retornarDescripcionItem(o),
                                                      checkBoxActivo: modeloReportes.retornaReporteActivoPorPerfil(modeloGenericoComboboxReportesPermisos.retornarCodigoItem(o),_codigoPerfil),
                                                      codigoTipoItem:"0",
                                                      descripcionItemSegundafila:"",
                                                      valorItem:"0",
                                                      serieDoc:""
                                                  })
            }
        }


        cbxDocumentosPorPerfil.setearMensajeDeCantidad()
        cbxReportesPorPerfil.setearMensajeDeCantidad()
    }


    function serearPermisos(){

        txtCodigoPerfil.textoInputBox=""
        txtDescripcionPerfil.textoInputBox=""
        cbxpermiteUsarClientes.setActivo(false)
        cbxpermiteCrearClientes.setActivo(false)
        cbxpermiteBorrarClientes.setActivo(false)

        cbxpermiteUsarArticulos.setActivo(false)
        cbxpermiteCrearArticulos.setActivo(false)
        cbxpermiteBorrarArticulos.setActivo(false)

        cbxpermiteUsarFacturacion.setActivo(false)
        cbxpermiteCrearFacturas.setActivo(false)
        cbxpermiteBorrarFacturas.setActivo(false)
        cbxpermiteAnularFacturas.setActivo(false)
        cbxpermiteReimprimirFacturas.setActivo(false)
        cbxpermiteAutorizarAnulaciones.setActivo(false)
        cbxpermiteAutorizarDescuentoTotal.setActivo(false)
        cbxpermiteAutorizarDescuentoItem.setActivo(false)

        cbxpermiteUsarLiquidaciones.setActivo(false)
        cbxpermiteCrearLiquidaciones.setActivo(false)
        cbxpermiteBorrarLiquidaciones.setActivo(false)
        cbxpermiteCerrarLiquidaciones.setActivo(false)
        cbxpermiteAutorizarCierreLiquidaciones.setActivo(false)

        cbxpermiteUsarListaPrecios.setActivo(false)
        cbxpermiteCrearListaDePrecios.setActivo(false)
        cbxpermiteBorrarListaDePrecios.setActivo(false)

        cbxpermiteUsarReportes.setActivo(false)
        cbxpermiteExportarAPDF.setActivo(false)

        cbxpermiteUsarMenuAdministracion.setActivo(false)

        cbxpermiteUsarDocumentos.setActivo(false)

        cbxpermiteUsarCuentaCorriente.setActivo(false)
        cbxpermiteCargaRapidaDePrecioListaPrecio.setActivo(false)



        cbxAccedeAlMenuUsuarios.setActivo(false)
        cbxAccedeAlMenuPermisos.setActivo(false)
        cbxAccedeAlMenuMonedas.setActivo(false)
        cbxAccedeAlMenuRubros.setActivo(false)
        cbxAccedeAlMenuCuentasBancarias.setActivo(false)
        cbxAccedeAlMenuPagoDeFinacieras.setActivo(false)
        cbxAccedeAlMenuBancos.setActivo(false)
        cbxAccedeAlMenuLocalidades.setActivo(false)
        cbxAccedeAlMenuTiposDeDocumentos.setActivo(false)
        cbxAccedeAlMenuIvas.setActivo(false)
        cbxAccedeAlMenuConfiguraciones.setActivo(false)




        cargarTipoDocumentos("")

    }

    Text {
        id: txtTituloMenuOpcion
        x: 560
        color: "#4d5595"
        text: "mantenimiento de perfiles"
        font.family: "Arial"
        style: Text.Normal
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        anchors.top: parent.top
        anchors.topMargin: -10
        anchors.right: parent.right
        anchors.rightMargin: 40
        smooth: true
        font.pixelSize: 23
    }

    Row {
        id: rowBarraDeHerramientas
        x: 30
        height: 30
        anchors.top: parent.top
        anchors.topMargin: 25
        smooth: true
        spacing: 15
        BotonBarraDeHerramientas {
            id: botonNuevoPerfil
            x: 33
            y: 10
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Perfiles.png"
            toolTip: "Nuevo perfil"
            anchors.verticalCenter: parent.verticalCenter
            z: 8

            onClic: {
                serearPermisos()
                txtCodigoPerfil.textoInputBox=modeloListaPerfiles.ultimoRegistroDePerfil()
                txtDescripcionPerfil.textoInputBox=""
                txtDescripcionPerfil.tomarElFoco()
            }
        }

        BotonBarraDeHerramientas {
            id: botonGuardarPerfil
            x: 61
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            toolTip: "Gurardar perfil"
            anchors.verticalCenter: parent.verticalCenter
            z: 7
            onClic: {
                txtMensajeInformacion.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()


                var permiteUsarLiquidaciones   =0
                var permiteUsarFacturacion   =0
                var permiteUsarArticulos   =0
                var permiteUsarListaPrecios   =0
                var permiteUsarClientes   =0
                var permiteUsarMenuAvanzado   =0
                var permiteUsarDocumentos   =0
                var permiteUsarReportes   =0
                var permiteUsarCuentaCorriente   =0
                var permiteCrearLiquidaciones   =0
                var permiteBorrarLiquidaciones   =0
                var permiteCerrarLiquidaciones   =0
                var permiteAutorizarCierreLiquidaciones   =0
                var permiteCrearFacturas   =0
                var permiteBorrarFacturas   =0
                var permiteAnularFacturas   =0
                var permiteReimprimirFacturas   =0
                var permiteCrearClientes   =0
                var permiteBorrarClientes   =0
                var permiteCrearArticulos   =0
                var permiteBorrarArticulos   =0
                var permiteCrearListaDePrecios   =0
                var permiteBorrarListaDePrecios   =0
                var permiteAutorizarDescuentosArticulo   =0
                var permiteAutorizarDescuentosTotal   =0
                var permiteAutorizarAnulaciones   =0
                var permiteExportarAPDF   =0
                var permiteCambioRapidoDePrecios   =0


                var AccedeAlMenuUsuarios   =0
                var AccedeAlMenuPermisos   =0
                var AccedeAlMenuMonedas   =0
                var AccedeAlMenuRubros   =0
                var AccedeAlMenuCuentasBancarias   =0
                var AccedeAlMenuPagoDeFinacieras   =0
                var AccedeAlMenuBancos   =0
                var AccedeAlMenuLocalidades   =0
                var AccedeAlMenuTiposDeDocumentos   =0
                var AccedeAlMenuIvas   =0
                var AccedeAlMenuConfiguraciones   =0


                if(cbxpermiteUsarLiquidaciones.chekActivo){permiteUsarLiquidaciones    =1}
                if(cbxpermiteUsarFacturacion.chekActivo){  permiteUsarFacturacion    =1}
                if(cbxpermiteUsarArticulos.chekActivo){    permiteUsarArticulos    =1}
                if(cbxpermiteUsarListaPrecios.chekActivo){ permiteUsarListaPrecios    =1}
                if(cbxpermiteUsarClientes.chekActivo){     permiteUsarClientes    =1}
                if(cbxpermiteUsarMenuAdministracion.chekActivo){ permiteUsarMenuAvanzado    =1}
                if(cbxpermiteUsarDocumentos.chekActivo){   permiteUsarDocumentos    =1}
                if(cbxpermiteUsarReportes.chekActivo){     permiteUsarReportes    =1}
                if(cbxpermiteUsarCuentaCorriente.chekActivo){permiteUsarCuentaCorriente    =1}
                if(cbxpermiteCrearLiquidaciones.chekActivo){ permiteCrearLiquidaciones    =1}
                if(cbxpermiteBorrarLiquidaciones.chekActivo){permiteBorrarLiquidaciones    =1}
                if(cbxpermiteCerrarLiquidaciones.chekActivo){permiteCerrarLiquidaciones    =1}
                if(cbxpermiteAutorizarCierreLiquidaciones.chekActivo){        permiteAutorizarCierreLiquidaciones    =1}
                if(cbxpermiteCrearFacturas.chekActivo){    permiteCrearFacturas    =1}
                if(cbxpermiteBorrarFacturas.chekActivo){   permiteBorrarFacturas    =1}
                if(cbxpermiteAnularFacturas.chekActivo){   permiteAnularFacturas    =1}
                if(cbxpermiteReimprimirFacturas.chekActivo){   permiteReimprimirFacturas  =1}
                if(cbxpermiteCrearClientes.chekActivo){    permiteCrearClientes    =1}
                if(cbxpermiteBorrarClientes.chekActivo){   permiteBorrarClientes    =1}
                if(cbxpermiteCrearArticulos.chekActivo){   permiteCrearArticulos    =1}
                if(cbxpermiteBorrarArticulos.chekActivo){  permiteBorrarArticulos    =1}
                if(cbxpermiteCrearListaDePrecios.chekActivo){permiteCrearListaDePrecios    =1}
                if(cbxpermiteBorrarListaDePrecios.chekActivo){permiteBorrarListaDePrecios    =1}
                if(cbxpermiteAutorizarDescuentoItem.chekActivo){permiteAutorizarDescuentosArticulo    =1}
                if(cbxpermiteAutorizarDescuentoTotal.chekActivo){permiteAutorizarDescuentosTotal    =1}
                if(cbxpermiteAutorizarAnulaciones.chekActivo){    permiteAutorizarAnulaciones    =1}
                if(cbxpermiteExportarAPDF.chekActivo){     permiteExportarAPDF=1}
                if(cbxpermiteCargaRapidaDePrecioListaPrecio.chekActivo){     permiteCambioRapidoDePrecios=1}


                if(cbxAccedeAlMenuUsuarios.chekActivo){     AccedeAlMenuUsuarios=1}
                if(cbxAccedeAlMenuPermisos.chekActivo){     AccedeAlMenuPermisos=1}
                if(cbxAccedeAlMenuMonedas.chekActivo){     AccedeAlMenuMonedas=1}
                if(cbxAccedeAlMenuRubros.chekActivo){     AccedeAlMenuRubros=1}
                if(cbxAccedeAlMenuCuentasBancarias.chekActivo){     AccedeAlMenuCuentasBancarias=1}
                if(cbxAccedeAlMenuPagoDeFinacieras.chekActivo){     AccedeAlMenuPagoDeFinacieras=1}
                if(cbxAccedeAlMenuBancos.chekActivo){     AccedeAlMenuBancos=1}
                if(cbxAccedeAlMenuLocalidades.chekActivo){     AccedeAlMenuLocalidades=1}
                if(cbxAccedeAlMenuTiposDeDocumentos.chekActivo){     AccedeAlMenuTiposDeDocumentos=1}
                if(cbxAccedeAlMenuIvas.chekActivo){     AccedeAlMenuIvas=1}
                if(cbxAccedeAlMenuConfiguraciones.chekActivo){     AccedeAlMenuConfiguraciones=1}





                var resultadoConsulta = modeloListaPerfiles.insertarPerfil(txtCodigoPerfil.textoInputBox.trim(),txtDescripcionPerfil.textoInputBox.trim(), permiteUsarLiquidaciones, permiteUsarFacturacion,permiteUsarArticulos,permiteUsarListaPrecios, permiteUsarClientes, permiteUsarMenuAvanzado, permiteUsarDocumentos , permiteUsarReportes, permiteUsarCuentaCorriente, permiteCrearLiquidaciones , permiteBorrarLiquidaciones , permiteCerrarLiquidaciones , permiteAutorizarCierreLiquidaciones , permiteCrearFacturas  , permiteBorrarFacturas , permiteAnularFacturas    , permiteCrearClientes, permiteBorrarClientes  , permiteCrearArticulos , permiteBorrarArticulos   , permiteCrearListaDePrecios, permiteBorrarListaDePrecios  , permiteAutorizarDescuentosArticulo , permiteAutorizarDescuentosTotal, permiteAutorizarAnulaciones  , permiteExportarAPDF,permiteReimprimirFacturas,permiteCambioRapidoDePrecios,
                                                                           AccedeAlMenuUsuarios, AccedeAlMenuPermisos, AccedeAlMenuMonedas, AccedeAlMenuRubros, AccedeAlMenuCuentasBancarias,AccedeAlMenuPagoDeFinacieras,
                                                                           AccedeAlMenuBancos, AccedeAlMenuLocalidades, AccedeAlMenuTiposDeDocumentos, AccedeAlMenuIvas, AccedeAlMenuConfiguraciones   )

                if(resultadoConsulta==1){

                    //Eliminar documentos que ya no se usan en el perfil, y agregar los que si se van a usar
                    for(var i=0; i<modeloGenericoComboboxTipoDocumento.rowCount();i++){
                        if(modeloListaTipoDocumentosVirtual.get(i).checkBoxActivo){

                            modeloListaTipoDocumentosComboBox.insertarTipoDocumentoPerfil(modeloListaTipoDocumentosVirtual.get(i).codigoItem,txtCodigoPerfil.textoInputBox.trim())
                        }else{
                            modeloListaTipoDocumentosComboBox.eliminarTipoDocumentoPerfil(modeloListaTipoDocumentosVirtual.get(i).codigoItem,txtCodigoPerfil.textoInputBox.trim())
                        }
                    }


                    //Eliminar reportes que ya no se usan en el perfil, y agregar los que si se van a usar
                    for(var o=0; o<modeloGenericoComboboxReportesPermisos.rowCount();o++){
                        if(modeloListaReportesVirtual.get(o).checkBoxActivo){
                            modeloReportes.insertarReportesPerfil(modeloListaReportesVirtual.get(o).codigoItem,txtCodigoPerfil.textoInputBox.trim())
                        }else{
                            modeloReportes.eliminarReportesPerfil(modeloListaReportesVirtual.get(o).codigoItem,txtCodigoPerfil.textoInputBox.trim())
                        }
                    }


                    txtMensajeInformacion.color="#2f71a0"
                    txtMensajeInformacion.text="Perfil "+ txtCodigoPerfil.textoInputBox+" dado de alta correctamente"

                    modeloListaPerfiles.limpiarListaPerfiles()
                    modeloListaPerfiles.buscarPerfiles("codigoPerfil=",txtCodigoPerfil.textoInputBox.trim())
                    listaDePerfiles.currentIndex=0;

                    modeloListaTipoDocumentosComboBox.limpiarListaTipoDocumentos()
                    modeloListaTipoDocumentosComboBox.buscarTipoDocumentos("1=","1",txtCodigoPerfil.textoInputBox.trim())

                    serearPermisos()
                    txtCodigoPerfil.tomarElFoco()

                    modeloListaPerfilesComboBox.limpiarListaPerfiles()
                    modeloListaPerfilesComboBox.buscarPerfiles("1=","1")

                    cbxDocumentosPorPerfil.cerrarComboBox()
                    cbxReportesPorPerfil.cerrarComboBox()




                }else if(resultadoConsulta==2){
                    //Eliminar documentos que ya no se usan en el perfil, y agregar los que si se van a usar
                    for(var i=0; i<modeloGenericoComboboxTipoDocumento.rowCount();i++){
                        if(modeloListaTipoDocumentosVirtual.get(i).checkBoxActivo){

                            modeloListaTipoDocumentosComboBox.insertarTipoDocumentoPerfil(modeloListaTipoDocumentosVirtual.get(i).codigoItem,txtCodigoPerfil.textoInputBox.trim())
                        }else{
                            modeloListaTipoDocumentosComboBox.eliminarTipoDocumentoPerfil(modeloListaTipoDocumentosVirtual.get(i).codigoItem,txtCodigoPerfil.textoInputBox.trim())
                        }
                    }

                    //Eliminar reportes que ya no se usan en el perfil, y agregar los que si se van a usar
                    for(var o=0; o<modeloGenericoComboboxReportesPermisos.rowCount();o++){
                        if(modeloListaReportesVirtual.get(o).checkBoxActivo){
                            modeloReportes.insertarReportesPerfil(modeloListaReportesVirtual.get(o).codigoItem,txtCodigoPerfil.textoInputBox.trim())
                        }else{
                            modeloReportes.eliminarReportesPerfil(modeloListaReportesVirtual.get(o).codigoItem,txtCodigoPerfil.textoInputBox.trim())
                        }
                    }


                    txtMensajeInformacion.color="#2f71a0"
                    txtMensajeInformacion.text="Perfil "+ txtCodigoPerfil.textoInputBox+" actualizado correctamente"

                    serearPermisos()
                    txtCodigoPerfil.tomarElFoco()
                    modeloListaPerfiles.limpiarListaPerfiles()
                    modeloListaPerfiles.buscarPerfiles("1=","1")
                    listaDePerfiles.currentIndex=0;

                    modeloListaPerfilesComboBox.limpiarListaPerfiles()
                    modeloListaPerfilesComboBox.buscarPerfiles("1=","1")

                    cbxDocumentosPorPerfil.cerrarComboBox()
                    cbxReportesPorPerfil.cerrarComboBox()




                }else if(resultadoConsulta==-1){
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="No se pudo conectar a la base de datos."
                }else if(resultadoConsulta==-2){
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="No se pudo actualizar la información del perfil."
                }else if(resultadoConsulta==-3){
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="No se pudo dar de alta el perfil."
                }else if(resultadoConsulta==-4){
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="No se pudo realizar la consulta a la base de datos."
                }else if(resultadoConsulta==-5){
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="Faltan datos para guardar el perfil."

                }else if(resultadoConsulta==-6){
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="El perfil de administrador no se puede modificar, solo visualizar."
                }
            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarPerfil
            x: 54
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            toolTip: "Eliminar Perfil"
            anchors.verticalCenter: parent.verticalCenter
            z: 6
            onClic:{


                if(txtCodigoPerfil.textoInputBox.trim()!="")
                    if(funcionesmysql.mensajeAdvertencia("Realmente desea eliminar el perfil "+txtCodigoPerfil.textoInputBox.trim()+"?\n\nPresione [ Sí ] para confirmar.")){

                        txtMensajeInformacion.visible=true
                        txtMensajeInformacionTimer.stop()
                        txtMensajeInformacionTimer.start()

                        if(!modeloUsuarios.existenUsuariosConPerfilAsociado(txtCodigoPerfil.textoInputBox.trim())){
                            ///Esto elimina todos los documentos que tenga asociado el perfil en la tabla TipoDocumentoPerfilesUsuarios
                            for(var i=0; i<modeloGenericoComboboxTipoDocumento.rowCount();i++){
                                modeloListaTipoDocumentosComboBox.eliminarTipoDocumentoPerfil(modeloListaTipoDocumentosVirtual.get(i).codigoItem,txtCodigoPerfil.textoInputBox.trim())
                            }

                            ///Esto elimina todos los reportes que tenga asociado el perfil
                            for(var i=0; i<modeloGenericoComboboxReportesPermisos.rowCount();i++){
                                modeloReportes.eliminarReportesPerfil(modeloListaReportesVirtual.get(i).codigoItem,txtCodigoPerfil.textoInputBox.trim())
                            }


                            if(modeloListaPerfiles.eliminarPerfil(txtCodigoPerfil.textoInputBox.trim())){

                                txtMensajeInformacion.color="#2f71a0"
                                txtMensajeInformacion.text="Perfil "+txtCodigoPerfil.textoInputBox.trim()+" eliminado."

                                modeloListaPerfiles.limpiarListaPerfiles()
                                modeloListaPerfiles.buscarPerfiles("1=","1")
                                listaDePerfiles.currentIndex=0;

                                serearPermisos()
                                txtCodigoPerfil.tomarElFoco()

                                modeloListaPerfilesComboBox.limpiarListaPerfiles()
                                modeloListaPerfilesComboBox.buscarPerfiles("1=","1")

                                cbxDocumentosPorPerfil.cerrarComboBox()
                                cbxReportesPorPerfil.cerrarComboBox()

                            }else{
                                txtMensajeInformacion.color="#d93e3e"
                                txtMensajeInformacion.text="No se puede eliminar el perfil."
                            }
                        }else{
                            txtMensajeInformacion.color="#d93e3e"
                            txtMensajeInformacion.text="No se puede eliminar el perfil, un usuario lo tiene asignado."
                        }
                    }
            }
        }

        BotonBarraDeHerramientas {
            id: botonListarTodosLosPerfiles
            x: 47
            y: 10
            toolTip: "Listar todos los perfiles"
            z: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            anchors.verticalCenter: parent.verticalCenter
            onClic: {
                modeloListaPerfiles.limpiarListaPerfiles()
                modeloListaPerfiles.buscarPerfiles("1=","1")
                listaDePerfiles.currentIndex=0;
            }
        }

        Text {
            id: txtMensajeInformacion
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            font.family: "Arial"
            smooth: true
            font.pixelSize: 14
            style: Text.Raised
            visible: false
            styleColor: "#ffffff"
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignTop
        }
        //    anchors.bottom: row1.top
        anchors.rightMargin: 10
        //    anchors.bottomMargin: 15
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.left: parent.left
    }

    Rectangle {
        id: rectLineaVerticalMenuGris
        height: 1
        color: "#abb2b1"
        smooth: true
        anchors.top: rowBarraDeHerramientas.bottom
        anchors.topMargin: 5
        anchors.rightMargin: 0
        visible: true
        rotation: 0
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    Rectangle {
        id: rectLineaVerticalMenuBlanco
        x: -7
        height: 1
        color: "#ffffff"
        smooth: true
        anchors.top: rowBarraDeHerramientas.bottom
        anchors.topMargin: 4
        anchors.rightMargin: 0
        visible: true
        rotation: 0
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    Rectangle {
        id: rectListaDePerfiles
        height: 200
        color: "#C4C4C6"
        radius: 3
        clip: true
        //  anchors.top: row1.bottom
        //  anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        smooth: true
        ListView {
            id: listaDePerfiles
            clip: true
            highlightRangeMode: ListView.NoHighlightRange
            anchors.top: parent.top
            boundsBehavior: Flickable.DragAndOvershootBounds
            highlightFollowsCurrentItem: true
            anchors.right: parent.right
            delegate: ListaPerfiles {}
            snapMode: ListView.NoSnap
            anchors.bottomMargin: 25
            spacing: 2
            anchors.bottom: parent.bottom
            flickableDirection: Flickable.VerticalFlick
            anchors.leftMargin: 1
            keyNavigationWraps: true
            anchors.left: parent.left
            interactive: true
            smooth: true
            anchors.topMargin: 25
            anchors.rightMargin: 1
            model: modeloListaPerfiles

            Rectangle {
                id: scrollbarlistaDePerfiles
                y: listaDePerfiles.visibleArea.yPosition * listaDePerfiles.height+5
                width: 10
                color: "#000000"
                height: listaDePerfiles.visibleArea.heightRatio * listaDePerfiles.height+18
                radius: 2
                anchors.right: listaDePerfiles.right
                anchors.rightMargin: 4
                z: 1
                opacity: 0.500
                visible: true
                smooth: true
            }
        }

        Text {
            id: txtTituloListaPerfiles
            text: qsTr("Perfiles: "+listaDePerfiles.count)
            font.family: "Arial"
            anchors.top: parent.top
            anchors.topMargin: 5
            font.bold: false
            font.pointSize: 10
            anchors.leftMargin: 5
            anchors.left: parent.left
        }

        BotonBarraDeHerramientas {
            id: botonBajarListaFinal1
            x: 783
            y: 126
            width: 14
            height: 14
            anchors.right: parent.right
            anchors.rightMargin: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
            anchors.bottom: parent.bottom
            toolTip: ""
            anchors.bottomMargin: 5
            rotation: -90

            onClic: listaDePerfiles.positionViewAtIndex(listaDePerfiles.count-1,0)
        }

        BotonBarraDeHerramientas {
            id: botonSubirListaFinal1
            x: 783
            y: 35
            width: 14
            height: 14
            anchors.right: parent.right
            anchors.rightMargin: 3
            anchors.top: parent.top
            anchors.topMargin: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
            toolTip: ""
            rotation: 90


            onClic: listaDePerfiles.positionViewAtIndex(0,0)

        }
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
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
        id: rectSolapaPermisos
        x: 0
        y: 124
        color: "#00000000"
        clip: true
        anchors.top: flow8.bottom
        anchors.topMargin: 19
        anchors.bottom: rectListaDePerfiles.top
        anchors.bottomMargin: 6
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        Flickable {
            id: flickable1
            anchors.fill: parent
            contentWidth: row1.implicitWidth
            contentHeight: parent.height
            interactive: true
            clip: false
            focus: false

            Row {
                id: row1
                anchors.fill: parent

                Rectangle {
                    id: rectPerfilesClientes
                    width: 400
                    height: rectSolapaPermisos.height
                    color: "#643ca239"
                    smooth: true

                    Rectangle {
                        id: rectLineaVerticalMenuBlanco1
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        anchors.right: parent.right
                        anchors.rightMargin: 6
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.bottomMargin: 5
                        rotation: 0
                        //     anchors.leftMargin: 0
                        //     anchors.left: listview1.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris1
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.bottomMargin: 5
                        rotation: 0
                        //     anchors.leftMargin: 1
                        //     anchors.left: listview1.right
                    }

                    Text {
                        id: text3
                        color: "#fdfdfd"
                        text: qsTr("permisos clientes")
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        smooth: true
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        rotation: 0
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow1
                        clip: true
                        flow: Flow.TopToBottom
                        spacing: 5
                        anchors.right: parent.right
                        anchors.rightMargin: 30
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 10
                        anchors.top: cbxpermiteUsarClientes.bottom
                        anchors.topMargin: 20
                        anchors.left: parent.left
                        anchors.leftMargin: 60

                        CheckBox {
                            id: cbxpermiteCrearClientes
                            x: 147
                            y: 81
                            tamanioLetra: 12
                            textoValor: "Crear/modificar clientes/proveedores"
                        }

                        CheckBox {
                            id: cbxpermiteBorrarClientes
                            x: 153
                            y: 73
                            tamanioLetra: 12
                            textoValor: "Eliminar clientes/proveedores"
                        }
                    }

                    CheckBox {
                        id: cbxpermiteUsarClientes
                        x: 40
                        y: 45
                        opacidadTexto: 1
                        tamanioLetra: 15
                        textoValor: "Utiliza mantenimiento de Cliente/Proveedor"
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        anchors.left: parent.left
                        anchors.leftMargin: 30
                    }

                    Rectangle {
                        id: rectangle2
                        height: 1
                        color: "#ffffff"
                        anchors.top: cbxpermiteUsarClientes.bottom
                        anchors.topMargin: 10
                        anchors.right: parent.right
                        anchors.rightMargin: 30
                        anchors.left: parent.left
                        anchors.leftMargin: 30
                        smooth: true
                    }

                    Rectangle {
                        id: rectangle4
                        x: 8
                        y: 0
                        height: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: cbxpermiteUsarClientes.bottom
                        anchors.topMargin: 11
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }

                Rectangle {
                    id: rectPerfilesArticulos
                    width: 400
                    height: rectSolapaPermisos.height
                    color: "#6427acb3"
                    smooth: true

                    Rectangle {
                        id: rectLineaVerticalMenuBlanco2
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 6
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //     anchors.leftMargin: 0
                        //     anchors.left: listview1.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris2
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 5
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //      anchors.leftMargin: 1
                        //      anchors.left: listview1.right
                    }

                    Text {
                        id: text2
                        color: "#fdfdfd"
                        text: qsTr("permisos artículos")
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        style: Text.Outline
                        font.underline: true
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        smooth: true
                        font.pixelSize: 20
                        font.italic: false
                        font.bold: true
                        rotation: 0
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    CheckBox {
                        id: cbxpermiteUsarArticulos
                        x: 40
                        y: 45
                        tamanioLetra: 15
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        textoValor: "Utiliza mantenimiento de Artículos"
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow2
                        x: 4
                        clip: true
                        flow: Flow.TopToBottom
                        spacing: 5
                        anchors.top: cbxpermiteUsarArticulos.bottom
                        anchors.topMargin: 20
                        CheckBox {
                            id: cbxpermiteCrearArticulos
                            x: 147
                            y: 81
                            tamanioLetra: 12
                            textoValor: "Crear/modificar artículos"
                        }

                        CheckBox {
                            id: cbxpermiteBorrarArticulos
                            x: 153
                            y: 73
                            tamanioLetra: 12
                            textoValor: "Eliminar artículos"
                        }
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 30
                        anchors.bottomMargin: 10
                        anchors.right: parent.right
                        anchors.leftMargin: 60
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle5
                        x: 4
                        height: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: cbxpermiteUsarArticulos.bottom
                        anchors.topMargin: 10
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle6
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: rectangle5.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }
                Rectangle {
                    id: rectPerfilesFacturas
                    width: 580
                    height: rectSolapaPermisos.height
                    color: "#64db4d4d"
                    smooth: true

                    Rectangle {
                        id: rectLineaVerticalMenuBlanco3
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 6
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //    anchors.leftMargin: 0
                        //    anchors.left: listview1.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris3
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 5
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //     anchors.leftMargin: 1
                        //    anchors.left: listview1.right
                    }

                    Text {
                        id: text4
                        color: "#fdfdfd"
                        text: qsTr("permisos facturación")
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        smooth: true
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        rotation: 0
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    CheckBox {
                        id: cbxpermiteUsarFacturacion
                        x: 40
                        y: 45
                        tamanioLetra: 15
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        textoValor: "Utiliza mantenimiento de Facturación"
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow3
                        x: 4
                        clip: true
                        flow: Flow.TopToBottom
                        spacing: 5
                        anchors.top: cbxpermiteUsarFacturacion.bottom
                        anchors.topMargin: 20
                        CheckBox {
                            id: cbxpermiteCrearFacturas
                            x: 147
                            y: 81
                            tamanioLetra: 12
                            textoValor: "Crear/modificar facturas/documentos"
                        }

                        CheckBox {
                            id: cbxpermiteBorrarFacturas
                            x: 153
                            y: 73
                            tamanioLetra: 12
                            textoValor: "Eliminar facturas/documentos pendientes"
                        }

                        CheckBox {
                            id: cbxpermiteAnularFacturas
                            x: 144
                            y: 72
                            tamanioLetra: 12
                            textoValor: "Anular facturas/documentos emitidos"
                        }
                        CheckBox {
                            id: cbxpermiteReimprimirFacturas
                            x: 143
                            y: 70
                            tamanioLetra: 12
                            textoValor: "Reimprimir facturas/documentos emitidos"
                        }
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 30
                        anchors.bottomMargin: 10
                        anchors.right: parent.right
                        anchors.leftMargin: 60
                        anchors.left: parent.left
                        CheckBox {
                            id: cbxpermiteAutorizarDescuentoItem
                            x: 139
                            y: 78
                            tamanioLetra: 12
                            textoValor: "Autorizar descuentos al item"
                        }
                        CheckBox {
                            id: cbxpermiteAutorizarDescuentoTotal
                            x: 136
                            y: 69
                            tamanioLetra: 12
                            textoValor: "Autorizar descuentos al total"
                        }
                        CheckBox {
                            id: cbxpermiteAutorizarAnulaciones
                            x: 138
                            y: 76
                            tamanioLetra: 12
                            textoValor: "Autorizar anulaciones"
                        }
                    }

                    Rectangle {
                        id: rectangle7
                        x: -3
                        height: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: cbxpermiteUsarFacturacion.bottom
                        anchors.topMargin: 10
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle8
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: rectangle7.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }

                Rectangle {
                    id: rectPerfilesLiquidaciones
                    width: 450
                    height: rectSolapaPermisos.height
                    color: "#644c6bb5"
                    smooth: true
                    Rectangle {
                        id: rectLineaVerticalMenuBlanco4
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 6
                        visible: true
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //    anchors.leftMargin: 0
                        //    anchors.left: listview1.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris4
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 5
                        visible: true
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //   anchors.leftMargin: 1
                        //   anchors.left: listview1.right
                    }

                    Text {
                        id: text5
                        color: "#fdfdfd"
                        text: qsTr("permisos liquidaciones/cajas")
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        smooth: true
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        font.bold: true
                        rotation: 0
                        anchors.leftMargin: 10
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    CheckBox {
                        id: cbxpermiteUsarLiquidaciones
                        x: 40
                        y: 45
                        tamanioLetra: 15
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        textoValor: "Utiliza mantenimiento de Cajas/Liquidaciones"
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow4
                        x: 4
                        clip: true
                        flow: Flow.TopToBottom
                        spacing: 5
                        anchors.top: cbxpermiteUsarLiquidaciones.bottom
                        anchors.topMargin: 20
                        CheckBox {
                            id: cbxpermiteCrearLiquidaciones
                            x: 147
                            y: 81
                            tamanioLetra: 12
                            textoValor: "Crear/modificar cajas/liquidaciones"
                        }

                        CheckBox {
                            id: cbxpermiteBorrarLiquidaciones
                            x: 153
                            y: 73
                            tamanioLetra: 12
                            textoValor: "Eliminar cajas/liquidaciones"
                        }

                        CheckBox {
                            id: cbxpermiteCerrarLiquidaciones
                            x: 144
                            y: 72
                            tamanioLetra: 12
                            textoValor: "Cerrar cajas/liquidaciones"
                        }

                        CheckBox {
                            id: cbxpermiteAutorizarCierreLiquidaciones
                            x: 138
                            y: 76
                            tamanioLetra: 12
                            textoValor: "Permiso para  autorizar el cierre de cajas/liquidaciones"
                        }
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 30
                        anchors.bottomMargin: 10
                        anchors.right: parent.right
                        anchors.leftMargin: 60
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle9
                        x: -3
                        height: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: cbxpermiteUsarLiquidaciones.bottom
                        anchors.topMargin: 10
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle10
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: rectangle9.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }

                Rectangle {
                    id: rectPerfilesListaDePrecios
                    width: 400
                    height: rectSolapaPermisos.height
                    color: "#64f8a218"
                    smooth: true
                    Rectangle {
                        id: rectLineaVerticalMenuBlanco5
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 6
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //     anchors.leftMargin: 0
                        //     anchors.left: listview1.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris5
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 5
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //    anchors.leftMargin: 1
                        //    anchors.left: listview1.right
                    }

                    Text {
                        id: text6
                        color: "#fdfdfd"
                        text: qsTr("permisos lista de precios")
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        smooth: true
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        rotation: 0
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    CheckBox {
                        id: cbxpermiteUsarListaPrecios
                        x: 40
                        y: 45
                        tamanioLetra: 15
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        textoValor: "Utiliza mantenimiento de Lista de precios"
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow5
                        x: 4
                        clip: true
                        flow: Flow.TopToBottom
                        spacing: 5
                        anchors.top: cbxpermiteUsarListaPrecios.bottom
                        anchors.topMargin: 20
                        CheckBox {
                            id: cbxpermiteCrearListaDePrecios
                            x: 147
                            y: 81
                            tamanioLetra: 12
                            textoValor: "Crear/modificar listas de precios"
                        }

                        CheckBox {
                            id: cbxpermiteBorrarListaDePrecios
                            x: 153
                            y: 73
                            tamanioLetra: 12
                            textoValor: "Eliminar listas de precios"
                        }

                        CheckBox {
                            id: cbxpermiteCargaRapidaDePrecioListaPrecio
                            x: 145
                            y: 79
                            tamanioLetra: 12
                            textoValor: "Carga rápida de precios"
                        }
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 30
                        anchors.bottomMargin: 10
                        anchors.right: parent.right
                        anchors.leftMargin: 60
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle11
                        x: -3
                        height: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: cbxpermiteUsarListaPrecios.bottom
                        anchors.topMargin: 10
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle12
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: rectangle11.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }

                Rectangle {
                    id: rectPerfilesReportes
                    width: 400
                    height: rectSolapaPermisos.height
                    color: "#64e235dd"
                    smooth: true
                    Rectangle {
                        id: rectLineaVerticalMenuBlanco6
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 6
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //   anchors.leftMargin: 0
                        //   anchors.left: listview1.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris6
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 5
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //   anchors.leftMargin: 1
                        //   anchors.left: listview1.right
                    }

                    Text {
                        id: text7
                        color: "#fdfdfd"
                        text: qsTr("permisos reportes")
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        smooth: true
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        rotation: 0
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    CheckBox {
                        id: cbxpermiteUsarReportes
                        x: 40
                        y: 45
                        tamanioLetra: 15
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        textoValor: "Utiliza mantenimiento de Reportes"
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow6
                        x: 4
                        clip: true
                        flow: Flow.TopToBottom
                        spacing: 5
                        anchors.top: cbxpermiteUsarReportes.bottom
                        anchors.topMargin: 20

                        CheckBox {
                            id: cbxpermiteExportarAPDF
                            x: 153
                            y: 73
                            tamanioLetra: 12
                            textoValor: "Exportar a PDF"
                        }
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 30
                        anchors.bottomMargin: 10
                        anchors.right: parent.right
                        anchors.leftMargin: 60
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle13
                        x: -3
                        height: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: cbxpermiteUsarReportes.bottom
                        anchors.topMargin: 10
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle14
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: rectangle13.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }


                Rectangle {
                    id: rectPerfilesDocumentos
                    width: 400
                    height: rectSolapaPermisos.height
                    color: "#647a14be"
                    smooth: true
                    Rectangle {
                        id: rectLineaVerticalMenuBlanco8
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 6
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //     anchors.leftMargin: 0
                        //     anchors.left: listview1.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris8
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 5
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //    anchors.leftMargin: 1
                        //    anchors.left: listview1.right
                    }

                    Text {
                        id: text9
                        color: "#fdfdfd"
                        text: qsTr("permisos documentos")
                        smooth: true
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        rotation: 0
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    CheckBox {
                        id: cbxpermiteUsarDocumentos
                        x: 40
                        y: 45
                        tamanioLetra: 15
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        textoValor: "Utiliza mantenimiento de Documentos"
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow9
                        x: 4
                        clip: true
                        flow: Flow.TopToBottom
                        spacing: 5
                        anchors.top: cbxpermiteUsarDocumentos.bottom
                        anchors.topMargin: 20
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 30
                        anchors.bottomMargin: 10
                        anchors.right: parent.right
                        anchors.leftMargin: 60
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle17
                        x: -3
                        height: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: cbxpermiteUsarDocumentos.bottom
                        anchors.topMargin: 10
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle18
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: rectangle17.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }


                Rectangle {
                    id: rectPerfilesCuentaCorrientes
                    width: 400
                    height: rectSolapaPermisos.height
                    color: "#de5454"
                    visible: true
                    smooth: true
                    Rectangle {
                        id: rectLineaVerticalMenuBlanco9
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 6
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //  anchors.leftMargin: 0
                        //  anchors.left: listview1.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris9
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 5
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //  anchors.leftMargin: 1
                        //  anchors.left: listview1.right
                    }

                    Text {
                        id: text10
                        color: "#fdfdfd"
                        text: qsTr("permisos cuenta corriente")
                        smooth: true
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        styleColor: "#8d8b8b"
                        font.family: "Arial"
                        rotation: 0
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    CheckBox {
                        id: cbxpermiteUsarCuentaCorriente
                        x: 40
                        y: 45
                        visible: true
                        tamanioLetra: 15
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        textoValor: "Utiliza mantenimiento de Cuenta corriente"
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow10
                        x: 4
                        flow: Flow.TopToBottom
                        spacing: 5
                        anchors.top: cbxpermiteUsarCuentaCorriente.bottom
                        anchors.topMargin: 20
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 30
                        anchors.bottomMargin: 20
                        anchors.right: parent.right
                        anchors.leftMargin: 60
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle19
                        x: -3
                        height: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: cbxpermiteUsarCuentaCorriente.bottom
                        anchors.topMargin: 10
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle20
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: rectangle19.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }
                Rectangle {
                    id: rectPerfilesOtros
                    width: 750
                    height: rectSolapaPermisos.height
                    color: "#00000000"
                    smooth: true
                    Rectangle {
                        id: rectLineaVerticalMenuBlanco7
                        x: 180
                        y: 28
                        width: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 6
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //   anchors.leftMargin: 0
                        //   anchors.left: listview1.right
                    }

                    Rectangle {
                        id: rectLineaVerticalMenuGris7
                        x: 181
                        y: 28
                        width: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        visible: true
                        anchors.rightMargin: 5
                        anchors.bottomMargin: 5
                        rotation: 0
                        anchors.right: parent.right
                        //    anchors.leftMargin: 1
                        //    anchors.left: listview1.right
                    }

                    Text {
                        id: text8
                        color: "#fdfdfd"
                        text: qsTr("otros permisos")
                        styleColor: "#8d8b8b"
                        smooth: true
                        font.pixelSize: 20
                        anchors.top: parent.top
                        anchors.topMargin: 16
                        style: Text.Outline
                        font.underline: true
                        font.italic: false
                        font.family: "Arial"
                        rotation: 0
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                    }

                    CheckBox {
                        id: cbxpermiteUsarMenuAdministracion
                        x: 40
                        y: 45
                        tamanioLetra: 15
                        anchors.top: parent.top
                        anchors.topMargin: 40
                        textoValor: "Utiliza menú administración"
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Flow {
                        id: flow7
                        x: 4
                        clip: true
                        flow: Flow.TopToBottom
                        spacing: 5
                        anchors.top: cbxpermiteUsarMenuAdministracion.bottom
                        anchors.topMargin: 20
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 30
                        anchors.bottomMargin: 10
                        anchors.right: parent.right
                        anchors.leftMargin: 60
                        anchors.left: parent.left

                        CheckBox {
                            id: cbxAccedeAlMenuUsuarios
                            tamanioLetra: 12
                            textoValor: "Accede al menú Usuarios"
                        }

                        CheckBox {
                            id: cbxAccedeAlMenuPermisos
                            tamanioLetra: 12
                            textoValor: "Accede al menú Permisos"
                        }

                        CheckBox {
                            id: cbxAccedeAlMenuMonedas
                            tamanioLetra: 12
                            textoValor: "Accede al menú Monedas"
                        }
                        CheckBox {
                            id: cbxAccedeAlMenuRubros
                            tamanioLetra: 12
                            textoValor: "Accede al menú Rubros"
                        }


                        CheckBox {
                            id: cbxAccedeAlMenuCuentasBancarias
                            tamanioLetra: 12
                            textoValor: "Accede al menú Cuentas Bancarias"
                        }

                        CheckBox {
                            id: cbxAccedeAlMenuPagoDeFinacieras
                            tamanioLetra: 12
                            textoValor: "Accede al menú Pago De Finacieras"
                        }
                        CheckBox {
                            id: cbxAccedeAlMenuBancos
                            tamanioLetra: 12
                            textoValor: "Accede al menú Bancos"
                        }
                        CheckBox {
                            id: cbxAccedeAlMenuLocalidades
                            tamanioLetra: 12
                            textoValor: "Accede al menú Localidades"
                        }

                        CheckBox {
                            id: cbxAccedeAlMenuTiposDeDocumentos
                            tamanioLetra: 12
                            textoValor: "Accede al menú Tipos De Documentos"
                        }
                        CheckBox {
                            id: cbxAccedeAlMenuIvas
                            tamanioLetra: 12
                            textoValor: "Accede al menú Ivas"
                        }
                        CheckBox {
                            id: cbxAccedeAlMenuConfiguraciones
                            tamanioLetra: 12
                            textoValor: "Accede al menú Configuraciones"
                        }

                    }

                    Rectangle {
                        id: rectangle15
                        x: -3
                        height: 1
                        color: "#ffffff"
                        smooth: true
                        anchors.top: cbxpermiteUsarMenuAdministracion.bottom
                        anchors.topMargin: 10
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }

                    Rectangle {
                        id: rectangle16
                        x: 8
                        height: 1
                        color: "#abb2b1"
                        smooth: true
                        anchors.top: rectangle15.bottom
                        anchors.topMargin: 1
                        anchors.rightMargin: 30
                        anchors.right: parent.right
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                    }
                }
            }
        }

        Rectangle {
            id: rectangle1
            width: flickable1.visibleArea.widthRatio * flickable1.width+18
            height: 10
            x:flickable1.visibleArea.xPosition * flickable1.width+5
            color: "#000000"
            smooth: true
            opacity: 0.500
            radius: 2
            anchors.bottom: flickable1.top
            anchors.bottomMargin: -12
        }



    }

    Flow {
        id: flow8
        x: 30
        y: 101
        height: flow8.implicitHeight
        spacing: 5
        flow: Flow.LeftToRight
        anchors.top: parent.top
        anchors.topMargin: 70
        TextInputSimple {
            id: txtCodigoPerfil
            //   width: 120
            textoInputBox: ""
            botonBuscarTextoVisible: false
            inputMask: "000000;"
            largoMaximo: 6
            botonBorrarTextoVisible: true
            textoTitulo: "Código perfil:"
            colorDeTitulo: "#333333"
            onTabulacion: txtDescripcionPerfil.tomarElFoco()
            onEnter: txtDescripcionPerfil.tomarElFoco()
        }

        TextInputSimple {
            id: txtDescripcionPerfil
            //  width: 300
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            botonBorrarTextoVisible: true
            largoMaximo: 35
            textoTitulo: "Nombre perfil:"
            colorDeTitulo: "#333333"
            onTabulacion: txtCodigoPerfil.tomarElFoco()
            onEnter: txtCodigoPerfil.tomarElFoco()
        }

        ComboBoxCheckBoxGenerico{
            id:cbxDocumentosPorPerfil
            width: 250
            textoTitulo: "Documentos por perfil:"
            colorRectangulo: "#cac1bd"
            colorTitulo: "#333333"
        }
        ListModel{
            id:modeloListaTipoDocumentosVirtual
        }

        ComboBoxCheckBoxGenerico{
            id:cbxReportesPorPerfil
            width: 250
            textoTitulo: "Reportes por perfil:"
            colorRectangulo: "#cac1bd"
            colorTitulo: "#333333"
        }
        ListModel{
            id:modeloListaReportesVirtual
        }


        anchors.rightMargin: 10
        z: 1
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.left: parent.left
    }

}
