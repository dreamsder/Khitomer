/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2022>  <Cristian Montano>

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
    id: rectPrincipalMenu
    width: 500
    height: 500
    color: "#00000000"

    Text {
        id: txtTituloMenuOpcion
        x: 560
        color: "#4d5595"
        text: qsTr("mantenimiento de garantías")
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
            id: txtCodigoGarantia
            enFocoSeleccionarTodo: true
            colorDeTitulo: "#333333"
            textoInputBox: ""
            botonBuscarTextoVisible: false
            inputMask: "000000;"
            largoMaximo: 6
            botonBorrarTextoVisible: true
            textoTitulo: "Código garantía:"

            onEnter: txtNombreGarantia.tomarElFoco()

            onTabulacion: txtNombreGarantia.tomarElFoco()
        }


        TextInputSimple {
            id: txtNombreGarantia
         //   width: 200
            colorDeTitulo: "#333333"
            botonBorrarTextoVisible: true
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            largoMaximo: 45
            textoTitulo: "Nombre garantía:"

            onEnter: txtCodigoGarantia.tomarElFoco()

            onTabulacion: txtCodigoGarantia.tomarElFoco()
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
            id: botonNuevaGarantia
            x: 33
            y: 10
            //source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Bancos.png"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Nuevo.png"
            toolTip: "Nueva garantía"
            anchors.verticalCenter: parent.verticalCenter
            z: 8

            onClic: {
                txtCodigoGarantia.textoInputBox=modeloTipoGarantiaMantenimiento.retornaUltimoCodigo()
                txtNombreGarantia.textoInputBox=""
                txtNombreGarantia.tomarElFoco()
            }
        }

        BotonBarraDeHerramientas {
            id: botonGuardarGarantia
            x: 61
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            toolTip: "Gurardar garantía"
            anchors.verticalCenter: parent.verticalCenter
            z: 7
            onClic: {

                txtMensajeInformacion.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                var resultadoConsulta = modeloTipoGarantiaMantenimiento.insertarTipoGarantia(txtCodigoGarantia.textoInputBox.trim(),txtNombreGarantia.textoInputBox.trim())

                    if(resultadoConsulta==1){

                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text="Garantía "+ txtCodigoGarantia.textoInputBox+" dada de alta correctamente"

                        txtCodigoGarantia.textoInputBox=""
                        txtNombreGarantia.textoInputBox=""

                        txtCodigoGarantia.tomarElFoco()

                        modeloTipoGarantiaMantenimiento.limpiarListaTipoGarantia()
                        modeloTipoGarantiaMantenimiento.buscarTipoGarantia("1=","1")
                        listaGarantia.currentIndex=0;

                        modeloTipoGarantia.limpiarListaTipoGarantia()
                        modeloTipoGarantia.buscarTipoGarantia("1=","1")


                    }else if(resultadoConsulta==2){
                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text="Garantía "+ txtCodigoGarantia.textoInputBox+" actualizada correctamente"

                        txtCodigoGarantia.textoInputBox=""
                        txtNombreGarantia.textoInputBox=""

                        txtCodigoGarantia.tomarElFoco()

                        modeloTipoGarantiaMantenimiento.limpiarListaTipoGarantia()
                        modeloTipoGarantiaMantenimiento.buscarTipoGarantia("1=","1")
                        listaGarantia.currentIndex=0;

                        modeloTipoGarantia.limpiarListaTipoGarantia()
                        modeloTipoGarantia.buscarTipoGarantia("1=","1")


                    }else if(resultadoConsulta==-1){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="No se pudo conectar a la base de datos"


                    }else if(resultadoConsulta==-2){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="No se pudo actualizar la información de la garantía"


                    }else if(resultadoConsulta==-3){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="No se pudo dar de alta la garantía"


                    }else if(resultadoConsulta==-4){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="No se pudo realizar la consulta a la base de datos"


                    }else if(resultadoConsulta==-5){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="Faltan datos para guardar la garantía. Verifique antes de continuar"

                    }
            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarGarantia
            x: 54
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            toolTip: "Eliminar garantía"
            anchors.verticalCenter: parent.verticalCenter
            z: 6
            onClic: {


                if(txtCodigoGarantia.textoInputBox.trim()!="")
                    if(funcionesmysql.mensajeAdvertencia("Realmente desea eliminar la garantía "+txtCodigoGarantia.textoInputBox.trim()+"?\n\nPresione [ Sí ] para confirmar.")){

                txtMensajeInformacion.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                if(modeloTipoGarantiaMantenimiento.eliminar(txtCodigoGarantia.textoInputBox.trim())){

                    txtMensajeInformacion.color="#2f71a0"
                    txtMensajeInformacion.text="Garantía "+txtCodigoGarantia.textoInputBox.trim()+" eliminada correctamente"

                    modeloTipoGarantiaMantenimiento.limpiarListaTipoGarantia()
                    modeloTipoGarantiaMantenimiento.buscarTipoGarantia("1=","1")
                    listaGarantia.currentIndex=0;

                    modeloTipoGarantia.limpiarListaTipoGarantia()
                    modeloTipoGarantia.buscarTipoGarantia("1=","1")

                    txtCodigoGarantia.textoInputBox=""
                    txtNombreGarantia.textoInputBox=""
                    txtCodigoGarantia.tomarElFoco()

                }else{
                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="No se puede eliminar la garantía, verifique la información."

                }}
            }
        }

        BotonBarraDeHerramientas {
            id: botonListarTodosLasGarantias
            x: 47
            y: 10
            toolTip: "Listar todas las garantías"
            z: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            anchors.verticalCenter: parent.verticalCenter

            onClic: {

                modeloTipoGarantiaMantenimiento.limpiarListaTipoGarantia()
                modeloTipoGarantiaMantenimiento.buscarTipoGarantia("1=","1")
                listaGarantia.currentIndex=0;
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
        id: rectListaGarantia
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
            id: listaGarantia
            clip: true
            highlightRangeMode: ListView.NoHighlightRange
            anchors.top: parent.top
            boundsBehavior: Flickable.DragAndOvershootBounds
            highlightFollowsCurrentItem: true
            anchors.right: parent.right
            delegate: ListaGenerica {
                onSend: {
                    txtCodigoGarantia.textoInputBox=datoUno
                    txtNombreGarantia.textoInputBox=datoDos
                    txtNombreGarantia.tomarElFoco()
                }

            }
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
            model: modeloTipoGarantiaMantenimiento

            Rectangle {
                id: rectangle3
                y: listaGarantia.visibleArea.yPosition * listaGarantia.height+5
                width: 10
                color: "#000000"
                height: listaGarantia.visibleArea.heightRatio * listaGarantia.height+18
                radius: 2
                anchors.right: listaGarantia.right
                anchors.rightMargin: 4
                z: 1
                opacity: 0.500
                visible: true
                //
            }
        }

        Text {
            id: txtTituloListaGarantias
            text: qsTr("Garantias: "+listaGarantia.count)
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
            onClic: listaGarantia.positionViewAtIndex(0,0)
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

            onClic: listaGarantia.positionViewAtIndex(listaGarantia.count-1,0)
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
