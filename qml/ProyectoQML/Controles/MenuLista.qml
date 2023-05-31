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
import "../OpcionesDeMenu"

Rectangle {
    id: rectMenuPrincipal
    width: txtTextoMenu.implicitWidth+20
    height: 30
    color: "#14ffffff"
    radius: 1



    property alias source: imageTextMenu.source


    Keys.onEscapePressed: {

    //    rectPrincipalAparecerYIn.stop()
        rectPrincipalListaMenu.visible=false

    }

    signal clic

    function cargarValores(){
        menuPermisos.cargarTipoDocumentos("")

    }

    function mostrarMenu(codigoDelMenu){


        if(codigoDelMenu==1){
            menusistema1.visible=true
            menucotizaciones1.visible=false
            menuusuarios1.visible=false
            menuPermisos.visible=false
            menuConfiguraciones.visible=false
            menuRubros.visible=false
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=false
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=false
            menuGarantias.visible=false
            menuGarantias.visible=false

        }else if(codigoDelMenu==2){

            menusistema1.visible=false
            menucotizaciones1.visible=false
            menuusuarios1.visible=false
            menuPermisos.visible=false
            menuConfiguraciones.visible=false
            menuRubros.visible=false
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=false
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=false
            menuGarantias.visible=false

        }else if(codigoDelMenu==3){
            menusistema1.visible=false
            menucotizaciones1.visible=false
            menuusuarios1.visible=true
            menuPermisos.visible=false
            menuConfiguraciones.visible=false
            menuRubros.visible=false
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=false
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=false
            menuGarantias.visible=false

        }else if(codigoDelMenu==4){

            menusistema1.visible=false
            menucotizaciones1.visible=false
            menuusuarios1.visible=false
            menuPermisos.visible=true
            menuConfiguraciones.visible=false
            menuRubros.visible=false
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=false
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=false
            menuGarantias.visible=false

        }else if(codigoDelMenu==5){
            menusistema1.visible=false
            menucotizaciones1.visible=false
            menuusuarios1.visible=false
            menuPermisos.visible=false
            menuConfiguraciones.visible=true
            menuRubros.visible=false
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=false
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=false
            menuGarantias.visible=false
        }
        else if(codigoDelMenu==6){
            menusistema1.visible=false
            menucotizaciones1.visible=true
            menuusuarios1.visible=false
            menuPermisos.visible=false
            menuConfiguraciones.visible=false
            menuRubros.visible=false
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=false
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=false
            menuGarantias.visible=false
        }else if(codigoDelMenu==7){
            menusistema1.visible=false
            menucotizaciones1.visible=false
            menuusuarios1.visible=false
            menuPermisos.visible=false
            menuConfiguraciones.visible=false
            menuRubros.visible=true
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=false
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=false
            menuGarantias.visible=false
        }else if(codigoDelMenu==8){
            menusistema1.visible=false
            menucotizaciones1.visible=false
            menuusuarios1.visible=false
            menuPermisos.visible=false
            menuConfiguraciones.visible=false
            menuRubros.visible=false
            menuCuentasBancarias.visible=true
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=false
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=false
            menuGarantias.visible=false
        }else if(codigoDelMenu==9){
            menusistema1.visible=false
            menucotizaciones1.visible=false
            menuusuarios1.visible=false
            menuPermisos.visible=false
            menuConfiguraciones.visible=false
            menuRubros.visible=false
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=true
            menuBancos.visible=false
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=false
            menuGarantias.visible=false
        }else if(codigoDelMenu==10){
            menusistema1.visible=false
            menucotizaciones1.visible=false
            menuusuarios1.visible=false
            menuPermisos.visible=false
            menuConfiguraciones.visible=false
            menuRubros.visible=false
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=true
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=false
            menuGarantias.visible=false
        }else if(codigoDelMenu==11){
            menusistema1.visible=false
            menucotizaciones1.visible=false
            menuusuarios1.visible=false
            menuPermisos.visible=false
            menuConfiguraciones.visible=false
            menuRubros.visible=false
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=false
            menuLocalidades.visible=true
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=false
            menuGarantias.visible=false
        }else if(codigoDelMenu==12){
            menusistema1.visible=false
            menucotizaciones1.visible=false
            menuusuarios1.visible=false
            menuPermisos.visible=false
            menuConfiguraciones.visible=false
            menuRubros.visible=false
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=false
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=true
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=false
            menuGarantias.visible=false
        }else if(codigoDelMenu==13){
            menusistema1.visible=false
            menucotizaciones1.visible=false
            menuusuarios1.visible=false
            menuPermisos.visible=false
            menuConfiguraciones.visible=false
            menuRubros.visible=false
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=false
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=false
            menuGarantias.visible=false
        }
        else if(codigoDelMenu==14){
            menusistema1.visible=false
            menucotizaciones1.visible=false
            menuusuarios1.visible=false
            menuPermisos.visible=false
            menuConfiguraciones.visible=false
            menuRubros.visible=false
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=false
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=true
            menuLogSistema.visible=false
            menuGarantias.visible=false
        }
        else if(codigoDelMenu==15){
            menusistema1.visible=false
            menucotizaciones1.visible=false
            menuusuarios1.visible=false
            menuPermisos.visible=false
            menuConfiguraciones.visible=false
            menuRubros.visible=false
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=false
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=true
            menuGarantias.visible=false
        }
        else if(codigoDelMenu==16){
            menusistema1.visible=false
            menucotizaciones1.visible=false
            menuusuarios1.visible=false
            menuPermisos.visible=false
            menuConfiguraciones.visible=false
            menuRubros.visible=false
            menuCuentasBancarias.visible=false
            menuPagoDeFinancieras.visible=false
            menuBancos.visible=false
            menuLocalidades.visible=false
            menuTipoDeDocumentos.visible=false
            menuIvas.visible=false
            menuFacturaElectronica.visible=false
            menuLogSistema.visible=false
            menuGarantias.visible=true
        }

    }

    property alias rectPrincipalVisible: rectPrincipalListaMenu.visible

    property alias textoBoton: txtTextoMenu.text

    //
    border.color: "#272525"


    Rectangle {
        id: rectCapaTransparente
        color: "#00000000"
        radius: 1
        //
        visible: true
        enabled: false
        anchors.fill: parent
    }


    PropertyAnimation{
        id:rectCapaTransparenteColorIn
        target: rectCapaTransparente
        property: "color"
        from:"#00000000"
        to:"#0fffffff"
        duration: 200
    }
    PropertyAnimation{
        id:rectCapaTransparenteColorOff
        target: rectCapaTransparente
        property: "color"
        from:"#0fffffff"
        to:"#00000000"
        duration: 40
    }



    /*PropertyAnimation{
        id:rectPrincipalAparecerYIn
        target: rectPrincipalListaMenu
        property: "y"
        from:20
        to: 30
        duration: 150
    }*/

    Text {
        id: txtTextoMenu
        x: 20
        y: 10
        color: "#fdfdfd"
        text: qsTr("A")
        font.family: "Arial"
        //
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 12
    }

    Image {
        id: imageTextMenu
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        //
        asynchronous: true
        source: ""
    }

    Rectangle {
        id: rectPrincipalListaMenu
        x: 0
        y: 30
        color: "#eceeee"
        radius: 6
        width: 1160
        height: 670
        //
        border.color: "#a8a0a0"

        MouseArea {
            id: mouse_area2
            anchors.fill: parent

            Rectangle {
                id: navegadorMenus
                x: 192
                y: 30
                color: rectPrincipalListaMenu.color
                visible: true
                anchors.left: rectLineaVerticalMenuGris.right
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 30

                MenuSistema {
                    id: menusistema1
                    visible: true
                    anchors.fill: parent
                }
                MenuCotizaciones {
                    id: menucotizaciones1
                    visible: false
                    anchors.fill: parent
                }

                MenuUsuarios {
                    id: menuusuarios1
                    anchors.fill: parent
                    visible: false
                }

                MenuPermisos{
                    id: menuPermisos
                    anchors.fill: parent
                    visible: false
                }
                MenuConfiguraciones{
                    id: menuConfiguraciones
                    anchors.fill: parent
                    visible: false
                }

                MenuRubros{
                    id: menuRubros
                    anchors.fill: parent
                    visible: false
                }
                MenuCuentasBancarias{
                    id: menuCuentasBancarias
                    anchors.fill: parent
                    visible: false
                }
                MenuPagoDeFinancieras{
                    id: menuPagoDeFinancieras
                    anchors.fill: parent
                    visible: false
                }
                MenuBancos{
                    id: menuBancos
                    anchors.fill: parent
                    visible: false
                }
                MenuLocalidades{
                    id: menuLocalidades
                    anchors.fill: parent
                    visible: false
                }
                MenuTiposDeDocumentos{
                    id: menuTipoDeDocumentos
                    anchors.fill: parent
                    visible: false
                }
                MenuIvas{
                    id: menuIvas
                    anchors.fill: parent
                    visible: false
                }
                MenuFacturaElectronica{
                    id: menuFacturaElectronica
                    anchors.fill: parent
                    visible: false
                }
                MenuLog{
                    id: menuLogSistema
                    anchors.fill: parent
                    visible: false
                }
                MenuGarantias{
                    id: menuGarantias
                    anchors.fill: parent
                    visible: false
                }
            }

            Rectangle {
                id: rectLineaVerticalMenuBlanco
                x: 180
                y: 28
                width: 1
                color: "#ffffff"
                //
                anchors.top: parent.top
                anchors.topMargin: 28
                anchors.bottom: parent.bottom
                visible: true
                anchors.bottomMargin: 7
                rotation: 0
                anchors.leftMargin: 0
                anchors.left: listview1.right
            }

            Rectangle {
                id: rectLineaVerticalMenuGris
                x: 181
                y: 28
                width: 1
                color: "#abb2b1"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 7
                anchors.left: rectLineaVerticalMenuBlanco.right
                anchors.leftMargin: 1
                anchors.top: parent.top
                anchors.topMargin: 28
                //
                rotation: 0
                visible: true
            }

            BotonBarraDeHerramientas {
                id: botonCerrarLista
                x: 922
                y: 10
                width: 18
                height: 18
                z: 2
                //
                anchors.top: parent.top
                anchors.topMargin: 10
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/CerrarLista.png"
                visible: true
                anchors.rightMargin: 10
                anchors.right: parent.right

                onClic: {

                 //   rectPrincipalAparecerYIn.stop()
                    rectPrincipalListaMenu.visible=false
                }
            }

            /*Rectangle {
                id: rectangle3
                x: 0//23
                y: -12
                width: 25
                height: 25
                color: rectPrincipalListaMenu.color
                //
                anchors.top: parent.top
                anchors.topMargin: -12
                rotation: 20
                z: 1
            }*/

            ListView {
                id: listview1
                x: 10
                y: 30
                width: 200
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.top: parent.top
                boundsBehavior: Flickable.StopAtBounds
                spacing: 20
                anchors.topMargin: 30
                anchors.bottomMargin: 10
                focus: true

                delegate:

                    FocusScope {
                    id:focusScopeListview1
                    x: childrenRect.x
                    y: childrenRect.y
                    width: childrenRect.width
                    height: childrenRect.height
                    //                    focus: true


                    Rectangle {
                        id: rect1
                        width: rectPrincipalListaMenu.width
                        height: texto1.implicitHeight
                        color: "#00000000"


                        Text {
                            id: texto1
                            color: "#000000"


                            text: nombreMenu
                            //
                            font.family: "Arial"
                            font.bold: false
                            Rectangle {
                                id: rectTextComboBox
                                y: 12
                                width: listview1.width+11
                                height: 19
                                color: "#5358be"
                                radius: 1
                                //
                                anchors.top: parent.top
                                border.color: "#000000"
                                anchors.topMargin: -5
                                anchors.bottom: parent.bottom
                                border.width: 0
                                anchors.bottomMargin: -5
                                z: -50
                                anchors.leftMargin: -20
                                opacity: 0

                                anchors.left: parent.left
                            }



                            PropertyAnimation {
                                id: opacityIn
                                target: rectTextComboBox
                                property: "opacity"
                                to: 0.600
                                from: 0
                                duration: 200
                            }

                            PropertyAnimation {
                                id: opacityOff
                                target: rectTextComboBox
                                property: "opacity"
                                to: 0
                                from: 0.600
                                duration: 50
                            }

                            MouseArea {
                                id: mouseArea
                                width: listview1.width
                                height: texto1.height+4
                                hoverEnabled: true
                                //  anchors.left: rectTextComboBox.left
                                //  anchors.leftMargin: 0
                                //  anchors.right: rectTextComboBox.left
                                //  anchors.rightMargin: 0

                                onEntered: {
                                    if(focusScopeListview1.focus==false){
                                        opacityOff.stop()
                                        opacityIn.start()
                                        texto1.color="white"
                                        texto1.style= Text.Normal
                                        texto1.font.bold= true
                                    }
                                }
                                onExited:{
                                    opacityIn.stop()
                                    opacityOff.start()
                                    texto1.color="#212121"
                                    texto1.style= Text.Raised
                                    texto1.font.bold= false
                                }

                                onClicked: {
                                    focusScopeListview1.forceActiveFocus()
                                    // mostrarMenu(codigoMenu)


                                    if(codigoMenu==1){
                                        mostrarMenu(codigoMenu)
                                    }

                                    if(codigoMenu==3 && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzadoUsuarios")){
                                        mostrarMenu(codigoMenu)
                                    }

                                    if(codigoMenu==4 && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzadoPermisos")){
                                        mostrarMenu(codigoMenu)
                                    }

                                    if(codigoMenu==5 && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzadoConfiguraciones")){
                                        mostrarMenu(codigoMenu)
                                    }

                                    if(codigoMenu==6 && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzadoMonedas")){

                                        mostrarMenu(codigoMenu)
                                    }
                                    if(codigoMenu==7 && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzadoRubros")){

                                        mostrarMenu(codigoMenu)
                                    }
                                    if(codigoMenu==8 && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzadoCuentasBancarias")){

                                        mostrarMenu(codigoMenu)
                                    }
                                    if(codigoMenu==9 && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzadoPagoDeFinacieras")){

                                        mostrarMenu(codigoMenu)
                                    }
                                    if(codigoMenu==10 && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzadoBancos")){

                                        mostrarMenu(codigoMenu)
                                    }
                                    if(codigoMenu==11 && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzadoLocalidades")){

                                        mostrarMenu(codigoMenu)
                                    }
                                    if(codigoMenu==12 && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzadoTiposDeDocumentos")){

                                        mostrarMenu(codigoMenu)
                                    }
                                    if(codigoMenu==13 && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzadoIvas")){

                                        mostrarMenu(codigoMenu)
                                    }
                                    if(codigoMenu==14 && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzadoFacturaElectronica")){

                                        mostrarMenu(codigoMenu)
                                    }
                                    if(codigoMenu==15 && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzadoLogDelSistema")){

                                        mostrarMenu(codigoMenu)
                                    }
                                    if(codigoMenu==16 && modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzadoGarantia")){

                                        mostrarMenu(codigoMenu)
                                    }



                                }


                            }
                            style: Text.Raised
                            styleColor: "#ffffff"
                            focus: true
                            font.pointSize: 11
                            z: 100
                            anchors.leftMargin: 10
                            anchors.left: parent.left
                        }

                        enabled: {


                            true

                            /*  if(codigoMenu==1){
                                true
                            }


                            if(codigoMenu==3){
                                modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarMenuAvanzadoUsuarios");
                            }


                            if(codigoMenu==4){
                                modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarMenuAvanzadoPermisos");
                            }

                            if(codigoMenu==5){
                                modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarMenuAvanzadoConfiguraciones");
                            }

                            if(codigoMenu==6){
                                modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarMenuAvanzadoMonedas");
                            }
                            if(codigoMenu==7){
                                modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarMenuAvanzadoRubros");
                            }
                            if(codigoMenu==8){
                                modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarMenuAvanzadoCuentasBancarias");
                            }
                            if(codigoMenu==9){
                                modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarMenuAvanzadoPagoDeFinacieras");
                            }
                            if(codigoMenu==10){
                                modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarMenuAvanzadoBancos");
                            }
                            if(codigoMenu==11){
                                modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarMenuAvanzadoLocalidades");
                            }
                            if(codigoMenu==12){
                                modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarMenuAvanzadoTiposDeDocumentos");
                            }
                            if(codigoMenu==13){
                                modeloListaPerfilesComboBox.retornaValorDePermiso(txtNombreDeUsuario.textoInputBox.trim(),"permiteUsarMenuAvanzadoIvas");
                            }*/



                        }
                    }
                    Keys.onEscapePressed: {

                       // rectPrincipalAparecerYIn.stop()
                        rectPrincipalListaMenu.visible=false

                    }
                }

                model: modeloListaMenues
                z: 3
                anchors.leftMargin: 10
            }

            Rectangle {
                id: rectLineaSuperior
                y: 5
                height: 2
                color: "#201c1c"
                radius: 1
                //
                anchors.bottom: parent.bottom
                anchors.rightMargin: 1
                visible: true
                anchors.bottomMargin: 0
                z: 3
                anchors.right: parent.right
                anchors.leftMargin: 1
                anchors.left: parent.left
            }
        }

        /*Rectangle {
            id: rectSombra
            x: -5
            y: 5
            color: "#1e646262"
            radius: 6
            //
            anchors.fill: parent
            anchors.topMargin: 5
            visible: true
            anchors.rightMargin: -5
            anchors.bottomMargin: -5
            z: -6
            anchors.leftMargin: -5
        }*/
        visible: false
        border.width: 1
        z: 2002
        anchors.leftMargin: 20
        anchors.left: parent.left
    }

    MouseArea {
        id: mouse_area1
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            rectCapaTransparenteColorOff.stop()
            rectCapaTransparenteColorIn.start()
        }
        onExited: {
            rectCapaTransparenteColorIn.stop()
            rectCapaTransparenteColorOff.start()
        }
        onClicked: {

            clic()
            if(rectPrincipalListaMenu.visible==false){
                listview1.forceActiveFocus()
                rectPrincipalListaMenu.visible=true
             //   rectPrincipalAparecerYIn.start();

            }else if(rectPrincipalListaMenu.visible){

                rectPrincipalListaMenu.visible=false

            }

        }
    }



}
