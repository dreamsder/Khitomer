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
import "../Controles"
import "../Listas"

Rectangle {
    id: rectPrincipalMenuUsuarios
    width: 500
    height: 500
    color: "#00000000"

    Text {
        id: txtTituloMenuOpcion
        x: 560
        color: "#4d5595"
        text: qsTr("mantenimiento de usuarios")
        font.family: "Arial"
        style: Text.Normal
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        anchors.top: parent.top
        anchors.topMargin: -10
        anchors.right: parent.right
        anchors.rightMargin: 40
        font.pixelSize: 23
    }

    Flow {
        id: flow1
        x: 30
        y: 101
        spacing: 5
        height: flow1.implicitHeight
        z: 1
        flow: Flow.LeftToRight
        anchors.top: parent.top
        anchors.topMargin: 70
        anchors.rightMargin: 10
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.left: parent.left

        TextInputSimple {
            id: txtIdUsuario
          //  width: 200
            colorDeTitulo: "#333333"
            textoInputBox: ""
            botonBuscarTextoVisible: false
            inputMask: ""
            largoMaximo: 35
            botonBorrarTextoVisible: true
            textoTitulo: "Login usuario:"

            onEnter: txtNombreUsuario.tomarElFoco()

            onTabulacion: txtNombreUsuario.tomarElFoco()
        }

        TextInputSimple {
            id: txtNombreUsuario
          //  width: 150
            colorDeTitulo: "#333333"
            botonBorrarTextoVisible: true
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            largoMaximo: 25
            textoTitulo: "Nombre:"

            onEnter: txtApellidoUsuario.tomarElFoco()

            onTabulacion: txtApellidoUsuario.tomarElFoco()
        }

        TextInputSimple {
            id: txtApellidoUsuario
          //  width: 150
            colorDeTitulo: "#333333"
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            largoMaximo: 25
            botonBorrarTextoVisible: true
            textoTitulo: "Apellido:"

            onEnter: comboboxlistaperfiles1.tomarElFoco()
        }

        ComboBoxListaPerfiles {
            id: comboboxlistaperfiles1
            x: 0
            y: 0
            width: 215
            height: 35
            visible: true
            botonBuscarTextoVisible: true
            z: 4
            colorRectangulo: "#cac1bd"
            textoTitulo: "Perfil:"
            colorTitulo: "#333333"

            onEnter: txtContraseniaDeUsuario.tomarElFoco()

            onTabulacion: txtContraseniaDeUsuario.tomarElFoco()

            onClicEnBusqueda: {

                modeloListaUsuarios.clearUsuarios()
                modeloListaUsuarios.buscarUsuarios(" tipoUsuario=2 and codigoPerfil=",comboboxlistaperfiles1.codigoValorSeleccion)
                listaDeUsuarios.currentIndex=0;

            }
        }

        TextInputSimple {
            id: txtContraseniaDeUsuario
          //  width: 230
            height: 35
            largoMaximo: 25
            colorDeTitulo: "#333333"
            echoMode: 2
            textoDeFondo: "clave privada"
            botonBorrarTextoVisible: true
            textoTitulo: "Contraseña:"

            onEnter: txtReingresarContraseniaDeUsuario.tomarElFoco()

            onTabulacion: txtReingresarContraseniaDeUsuario.tomarElFoco()
        }

        TextInputSimple {
            id: txtReingresarContraseniaDeUsuario
            x: -9
            y: 9
         //   width: 230
            height: 35
            largoMaximo: 25
            //
            echoMode: 2
            botonBorrarTextoVisible: true
            textoDeFondo: "reingrese clave privada"
            textoTitulo: "Reingresar contraseña:"
            colorDeTitulo: "#333333"

            onEnter: txtEmail.tomarElFoco()

            onTabulacion: txtEmail.tomarElFoco()
        }



        TextInputSimple {
            id: txtEmail
          //  width: 150
            colorDeTitulo: "#333333"
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            largoMaximo: 100
            botonBorrarTextoVisible: true
            textoTitulo: "Email:"

            onEnter: txtIdUsuario.tomarElFoco()

            onTabulacion: txtIdUsuario.tomarElFoco()

        }

        CheckBox {
            id: cbEsVendedor
            x: 396
            y: 97
            chekActivo: true
            colorTexto: "#333333"
            textoValor: "Puede operar como vendedor"
        }

    }

    Row {
        id: rowBarraDeHerramientas
        x: 30
        y: 55
        height: 30
        //
        spacing: 15
        BotonBarraDeHerramientas {
            id: botonNuevoUsuario
            x: 33
            y: 10
            //source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Usuarios.png"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Nuevo.png"
            toolTip: "Nuevo usuario"
            anchors.verticalCenter: parent.verticalCenter
            z: 8

            onClic: {

                txtIdUsuario.textoInputBox=""
                txtNombreUsuario.textoInputBox=""
                txtApellidoUsuario.textoInputBox=""
                comboboxlistaperfiles1.textoComboBox=""
                comboboxlistaperfiles1.codigoValorSeleccion=""
                txtContraseniaDeUsuario.textoInputBox=""
                txtReingresarContraseniaDeUsuario.textoInputBox=""
                txtEmail.textoInputBox=""
                cbEsVendedor.setActivo(true)
                txtIdUsuario.tomarElFoco()


            }
        }

        BotonBarraDeHerramientas {
            id: botonGuardarUsuario
            x: 61
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            toolTip: "Gurardar usuario"
            anchors.verticalCenter: parent.verticalCenter
            z: 7

            onClic: {

                txtMensajeInformacion.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()


                if(txtContraseniaDeUsuario.textoInputBox.trim()==txtReingresarContraseniaDeUsuario.textoInputBox.trim()) {
                    var esVendedor=0

                    if(cbEsVendedor.chekActivo)
                        esVendedor=1

                    var resultadoConsulta = modeloListaUsuarios.insertarUsuario(txtIdUsuario.textoInputBox,txtNombreUsuario.textoInputBox,txtApellidoUsuario.textoInputBox,esVendedor,comboboxlistaperfiles1.codigoValorSeleccion,txtContraseniaDeUsuario.textoInputBox.trim(),txtEmail.textoInputBox.trim())


                    if(resultadoConsulta==1){

                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text="Usuario "+ txtIdUsuario.textoInputBox+" dado de alta correctamente"

                        txtIdUsuario.textoInputBox=""
                        txtNombreUsuario.textoInputBox=""
                        txtApellidoUsuario.textoInputBox=""
                        comboboxlistaperfiles1.textoComboBox=""
                        comboboxlistaperfiles1.codigoValorSeleccion=""
                        txtContraseniaDeUsuario.textoInputBox=""
                        txtReingresarContraseniaDeUsuario.textoInputBox=""
                        txtEmail.textoInputBox=""
                        cbEsVendedor.setActivo(true)
                        txtIdUsuario.tomarElFoco()

                        modeloListaUsuarios.clearUsuarios()
                        modeloListaUsuarios.buscarUsuarios(" tipoUsuario= ",2)
                        listaDeUsuarios.currentIndex=0;

                        modeloListaVendedores.clearUsuarios()
                        modeloListaVendedores.buscarUsuarios("esVendedor=","1")


                    }else if(resultadoConsulta==2){
                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text="Usuario "+ txtIdUsuario.textoInputBox+" actualizado correctamente"

                        txtIdUsuario.textoInputBox=""
                        txtNombreUsuario.textoInputBox=""
                        txtApellidoUsuario.textoInputBox=""
                        comboboxlistaperfiles1.textoComboBox=""
                        comboboxlistaperfiles1.codigoValorSeleccion=""
                        txtContraseniaDeUsuario.textoInputBox=""
                        txtReingresarContraseniaDeUsuario.textoInputBox=""
                        txtEmail.textoInputBox=""
                        cbEsVendedor.setActivo(true)
                        txtIdUsuario.tomarElFoco()

                        modeloListaUsuarios.clearUsuarios()
                        modeloListaUsuarios.buscarUsuarios(" tipoUsuario= ",2)
                        listaDeUsuarios.currentIndex=0;

                        modeloListaVendedores.clearUsuarios()
                        modeloListaVendedores.buscarUsuarios("esVendedor=","1")



                    }else if(resultadoConsulta==-1){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: No se pudo conectar a la base de datos"


                    }else if(resultadoConsulta==-2){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: No se pudo actualizar la información de usuario"


                    }else if(resultadoConsulta==-3){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: No se pudo dar de alta el usuario"


                    }else if(resultadoConsulta==-4){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: No se pudo realizar la consulta a la base de datos"


                    }else if(resultadoConsulta==-5){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="ATENCION: Faltan datos para guardar el usuario. Verifique antes de continuar"

                    }


                }else{
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="ATENCION: Las contraseña son invalidas"
                    txtContraseniaDeUsuario.tomarElFoco()
                }
            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarUsuario
            x: 54
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            toolTip: "Eliminar usuario"
            anchors.verticalCenter: parent.verticalCenter
            z: 6
            onClic: {


                if(txtIdUsuario.textoInputBox.trim()!="")
                    if(funcionesmysql.mensajeAdvertencia("Realmente desea eliminar el usuario "+txtIdUsuario.textoInputBox.trim()+"?\n\nPresione [ Sí ] para confirmar.")){

                txtMensajeInformacion.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                if(modeloListaUsuarios.eliminarUsuario(txtIdUsuario.textoInputBox.trim())){

                    txtMensajeInformacion.color="#2f71a0"
                    txtMensajeInformacion.text="Usuario "+txtIdUsuario.textoInputBox.trim()+" eliminado correctamente"

                    modeloListaUsuarios.clearUsuarios()
                    modeloListaUsuarios.buscarUsuarios(" tipoUsuario= ",2)
                    listaDeUsuarios.currentIndex=0;

                    modeloListaVendedores.clearUsuarios()
                    modeloListaVendedores.buscarUsuarios("esVendedor=","1")

                    txtIdUsuario.textoInputBox=""
                    txtNombreUsuario.textoInputBox=""
                    txtApellidoUsuario.textoInputBox=""
                    comboboxlistaperfiles1.textoComboBox=""
                    comboboxlistaperfiles1.codigoValorSeleccion=""
                    txtContraseniaDeUsuario.textoInputBox=""
                    txtReingresarContraseniaDeUsuario.textoInputBox=""
                    txtEmail.textoInputBox=""
                    cbEsVendedor.setActivo(true)
                    txtIdUsuario.tomarElFoco()

                }else{


                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="ATENCION: No se puede eliminar el usuario, verifique la información."

                }}
            }
        }

        BotonBarraDeHerramientas {
            id: botonListarTodosLosUsuarios
            x: 47
            y: 10
            toolTip: "Listar todos los usuarios"
            z: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            anchors.verticalCenter: parent.verticalCenter

            onClic: {

                modeloListaUsuarios.clearUsuarios()
                modeloListaUsuarios.buscarUsuarios(" tipoUsuario= ",2)
                listaDeUsuarios.currentIndex=0;


            }
        }

        Text {
            id: txtMensajeInformacion
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            font.family: "Arial"
            font.pixelSize: 14
            style: Text.Raised
            visible: false
            styleColor: "#ffffff"
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignTop
        }
        anchors.bottom: flow1.top
        anchors.rightMargin: 10
        anchors.bottomMargin: 15
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.left: parent.left
    }

    Rectangle {
        id: rectLineaVerticalMenuGris
        height: 1
        color: "#abb2b1"
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
        id: rectListaDeUsuarios
        color: "#C4C4C6"
        radius: 3
        clip: true
        anchors.top: flow1.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        //
        ListView {
            id: listaDeUsuarios
            clip: true
            highlightRangeMode: ListView.NoHighlightRange
            anchors.top: parent.top
            boundsBehavior: Flickable.DragAndOvershootBounds
            highlightFollowsCurrentItem: true
            anchors.right: parent.right
            delegate: ListaUsuarios {}
            snapMode: ListView.NoSnap
            anchors.bottomMargin: 25
            spacing: 1
            anchors.bottom: parent.bottom
            flickableDirection: Flickable.VerticalFlick
            anchors.leftMargin: 1
            keyNavigationWraps: true
            anchors.left: parent.left
            interactive: true
            //
            anchors.topMargin: 25
            anchors.rightMargin: 1
            model: modeloListaUsuarios


            Rectangle {
                id: rectangle3
                y: listaDeUsuarios.visibleArea.yPosition * listaDeUsuarios.height+5
                width: 10
                color: "#000000"
                height: listaDeUsuarios.visibleArea.heightRatio * listaDeUsuarios.height+18
                radius: 2
                anchors.right: listaDeUsuarios.right
                anchors.rightMargin: 4
                z: 1
                opacity: 0.500
                visible: true
            }
        }

        Text {
            id: txtTituloListaUsuarios
            text: qsTr("Usuarios: "+listaDeUsuarios.count)
            font.family: "Arial"
            anchors.top: parent.top
            anchors.topMargin: 5
            font.bold: false
            font.pointSize: 10
            anchors.leftMargin: 5
            anchors.left: parent.left
        }

        BotonBarraDeHerramientas {
            id: botonSubirListaFinal1
            x: 457
            y: 5
            width: 14
            height: 14
            anchors.right: parent.right
            anchors.rightMargin: 3
            anchors.top: parent.top
            anchors.topMargin: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
            toolTip: ""
            rotation: 90


            onClic: listaDeUsuarios.positionViewAtIndex(0,0)

        }

        BotonBarraDeHerramientas {
            id: botonBajarListaFinal1
            x: 483
            y: 231
            width: 14
            height: 14
            anchors.right: parent.right
            anchors.rightMargin: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
            anchors.bottom: parent.bottom
            toolTip: ""
            anchors.bottomMargin: 5
            rotation: -90

            onClic: listaDeUsuarios.positionViewAtIndex(listaDeUsuarios.count-1,0)
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

}
