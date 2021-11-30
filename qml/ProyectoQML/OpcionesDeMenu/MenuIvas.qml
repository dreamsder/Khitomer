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
    id: rectPrincipalMenuIvas
    width: 600
    height: 500
    color: "#00000000"
    //

    Text {
        id: txtTituloMenuOpcion
        x: 560
        color: "#4d5595"
        text: qsTr("mantenimiento de ivas")
        font.family: "Arial"
        style: Text.Normal
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        anchors.top: parent.top
        anchors.topMargin: -10
        anchors.right: parent.right
        anchors.rightMargin: 40
        //
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
            id: txtCodigoIva
          //  width: 120
            enFocoSeleccionarTodo: true
            colorDeTitulo: "#333333"
            textoInputBox: ""
            botonBuscarTextoVisible: false
            inputMask: "000000;"
            largoMaximo: 6
            botonBorrarTextoVisible: true
            textoTitulo: "Código iva:"

            onEnter: txtNombreIva.tomarElFoco()

            onTabulacion: txtNombreIva.tomarElFoco()
        }


        TextInputSimple {
            id: txtNombreIva
          //  width: 200
            colorDeTitulo: "#333333"
            botonBorrarTextoVisible: true
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            largoMaximo: 45
            textoTitulo: "Nombre iva:"

            onEnter: txtCodigoIva.tomarElFoco()

            onTabulacion: txtCodigoIva.tomarElFoco()
        }

        TextInputSimple {
            id: txtPorcentajeIva
            x: -7
            y: 3
          //  width: 120
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            inputMask: "00.00;0"
            largoMaximo: 4
            botonBorrarTextoVisible: true
            textoTitulo: "Porcentaje iva:"
            colorDeTitulo: "#333333"
        }

        TextInputSimple {
            id: txtFactorMultiplicadorIVa
          //  width: 170
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            inputMask: "00.00;0"
            botonBorrarTextoVisible: true
            largoMaximo: 4
            textoTitulo: "Multiplicador (requerido):"
            colorDeTitulo: "#333333"
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
            id: botonNuevoIva
            x: 33
            y: 10
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Bancos.png"
            toolTip: "Nuevo iva"
            anchors.verticalCenter: parent.verticalCenter
            z: 8

            onClic: {
                txtCodigoIva.textoInputBox=modeloListaBancos.retornaUltimoCodigoBanco()
                txtNombreIva.textoInputBox=""
                txtNombreIva.tomarElFoco()
            }
        }

        BotonBarraDeHerramientas {
            id: botonGuardarIva
            x: 61
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            toolTip: "Gurardar iva"
            anchors.verticalCenter: parent.verticalCenter
            z: 7
            onClic: {

                txtMensajeInformacion.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                var resultadoConsulta = modeloListaBancos.insertarBanco(txtCodigoIva.textoInputBox.trim(),txtNombreIva.textoInputBox.trim())

                    if(resultadoConsulta==1){

                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text="Banco "+ txtCodigoIva.textoInputBox+" dado de alta correctamente"

                        txtCodigoIva.textoInputBox=""
                        txtNombreIva.textoInputBox=""

                        txtCodigoIva.tomarElFoco()

                        modeloListaBancos.limpiarListaBancos()
                        modeloListaBancos.buscarBancos("1=","1")
                        listaDeIvas.currentIndex=0;

                        modeloListaBancosComboBox.limpiarListaBancos()
                        modeloListaBancosComboBox.buscarBancos("1=","1")


                    }else if(resultadoConsulta==2){
                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text="Banco "+ txtCodigoIva.textoInputBox+" actualizado correctamente"

                        txtCodigoIva.textoInputBox=""
                        txtNombreIva.textoInputBox=""

                        txtCodigoIva.tomarElFoco()

                        modeloListaBancos.limpiarListaBancos()
                        modeloListaBancos.buscarBancos("1=","1")
                        listaDeIvas.currentIndex=0;

                        modeloListaBancosComboBox.limpiarListaBancos()
                        modeloListaBancosComboBox.buscarBancos("1=","1")


                    }else if(resultadoConsulta==-1){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="No se pudo conectar a la base de datos"


                    }else if(resultadoConsulta==-2){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="No se pudo actualizar la información del banco"


                    }else if(resultadoConsulta==-3){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="No se pudo dar de alta el banco"


                    }else if(resultadoConsulta==-4){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="No se pudo realizar la consulta a la base de datos"


                    }else if(resultadoConsulta==-5){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="Faltan datos para guardar el banco. Verifique antes de continuar"

                    }
            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarIva
            x: 54
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            toolTip: "Eliminar iva"
            anchors.verticalCenter: parent.verticalCenter
            z: 6
            onClic: {


                if(txtCodigoIva.textoInputBox.trim()!="")
                    if(funcionesmysql.mensajeAdvertencia("Realmente desea eliminar el banco "+txtCodigoIva.textoInputBox.trim()+"?\n\nPresione [ Sí ] para confirmar.")){

                txtMensajeInformacion.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                if(modeloListaBancos.eliminarBanco(txtCodigoIva.textoInputBox.trim())){

                    txtMensajeInformacion.color="#2f71a0"
                    txtMensajeInformacion.text="Banco "+txtCodigoIva.textoInputBox.trim()+" eliminado correctamente"

                    modeloListaBancos.limpiarListaBancos()
                    modeloListaBancos.buscarBancos("1=","1")
                    listaDeIvas.currentIndex=0;

                    modeloListaBancosComboBox.limpiarListaBancos()
                    modeloListaBancosComboBox.buscarBancos("1=","1")

                    txtCodigoIva.textoInputBox=""
                    txtNombreIva.textoInputBox=""
                    txtCodigoIva.tomarElFoco()

                }else{
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="No se puede eliminar el banco, verifique la información."

                }}
            }
        }

        BotonBarraDeHerramientas {
            id: botonListarTodosLosIvas
            x: 47
            y: 10
            toolTip: "Listar todas los ivas"
            z: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            anchors.verticalCenter: parent.verticalCenter

            onClic: {

                modeloListaBancos.limpiarListaBancos()
                modeloListaBancos.buscarBancos("1=","1")
                listaDeIvas.currentIndex=0;
            }
        }

        Text {
            id: txtMensajeInformacion
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            font.family: "Arial"
            //
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
        //
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
        //
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
        id: rectListaDeIvas
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
            id: listaDeIvas
            clip: true
            highlightRangeMode: ListView.NoHighlightRange
            anchors.top: parent.top
            boundsBehavior: Flickable.DragAndOvershootBounds
            highlightFollowsCurrentItem: true
            anchors.right: parent.right
            delegate: ListaBancos {}
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
            model: modeloListaBancos

            Rectangle {
                id: rectangle3
                y: listaDeIvas.visibleArea.yPosition * listaDeIvas.height+5
                width: 10
                color: "#000000"
                height: listaDeIvas.visibleArea.heightRatio * listaDeIvas.height+18
                radius: 2
                anchors.right: listaDeIvas.right
                anchors.rightMargin: 4
                z: 1
                opacity: 0.500
                visible: true
                //
            }
        }

        Text {
            id: txtTituloListaIvas
            text: qsTr("Ivas: "+listaDeIvas.count)
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
            onClic: listaDeIvas.positionViewAtIndex(0,0)
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

            onClic: listaDeIvas.positionViewAtIndex(listaDeIvas.count-1,0)
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
