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
import "../Listas"

Rectangle {
    id: rectPrincipalMenuRubros
    width: 900
    height: 500
    color: "#00000000"
    //

    Text {
        id: txtTituloMenuOpcion
        x: 560
        color: "#4d5595"
        text: qsTr("mantenimiento de rubros y sub rubros")
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
        width: 340
        spacing: 5
        height: flow1.implicitHeight
        z: 1
        flow: Flow.LeftToRight
        anchors.top: parent.top
        anchors.topMargin: 70
        anchors.leftMargin: 10
        anchors.left: parent.left

        TextInputSimple {
            id: txtCodigoRubro
         //   width: 100
            colorDeTitulo: "#333333"
            textoInputBox: ""
            botonBuscarTextoVisible: false
            inputMask: "000000;"
            largoMaximo: 6
            botonBorrarTextoVisible: true
            textoTitulo: "Código rubro:"

            onEnter: txtNombreRubro.tomarElFoco()

            onTabulacion: txtNombreRubro.tomarElFoco()
        }

        TextInputSimple {
            id: txtNombreRubro
          //  width: 200
            colorDeTitulo: "#333333"
            botonBorrarTextoVisible: true
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            largoMaximo: 35
            textoTitulo: "Nombre rubro:"

            onEnter: txtCodigoRubro.tomarElFoco()

            onTabulacion: txtCodigoRubro.tomarElFoco()
        }

    }

    Row {
        id: rowBarraDeHerramientas
        x: 30
        y: 55
        height: 30
        z: 2
        //
        spacing: 15
        BotonBarraDeHerramientas {
            id: botonNuevoRubro
            x: 33
            y: 10
            //source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Rubros.png"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Nuevo.png"
            toolTip: "Nuevo Rubro"
            anchors.verticalCenter: parent.verticalCenter
            z: 8

            onClic: {

                txtCodigoRubro.textoInputBox=modeloListaRubros.ultimoRegistroDeRubro()
                txtNombreRubro.textoInputBox=""
                txtNombreRubro.tomarElFoco()

            }
        }

        BotonBarraDeHerramientas {
            id: botonGuardarRubro
            x: 61
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            toolTip: "Gurardar Rubro"
            anchors.verticalCenter: parent.verticalCenter
            z: 7

            onClic: {

                txtMensajeInformacionRubros.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                    var resultadoConsulta = modeloListaRubros.insertarRubro(txtCodigoRubro.textoInputBox,txtNombreRubro.textoInputBox)

                    if(resultadoConsulta==1){

                        txtMensajeInformacionRubros.color="#2f71a0"
                        txtMensajeInformacionRubros.text="Rubro "+ txtCodigoRubro.textoInputBox+" dado de alta ok"

                        modeloListaRubros.limpiarListaRubros()
                        modeloListaRubros.buscarRubros("codigoRubro=",txtCodigoRubro.textoInputBox)
                        listaDeRubros.currentIndex=0;

                        txtCodigoRubro.textoInputBox=""
                        txtNombreRubro.textoInputBox=""
                        txtCodigoRubro.tomarElFoco()

                        modeloListaRubrosComboBox.limpiarListaRubros()
                        modeloListaRubrosComboBox.buscarRubros("1=","1")

                    }else if(resultadoConsulta==2){
                        txtMensajeInformacionRubros.color="#2f71a0"
                        txtMensajeInformacionRubros.text="Rubro "+ txtCodigoRubro.textoInputBox+" actualizado."

                        modeloListaRubros.limpiarListaRubros()
                        modeloListaRubros.buscarRubros("codigoRubro=",txtCodigoRubro.textoInputBox)
                        listaDeRubros.currentIndex=0;

                        txtCodigoRubro.textoInputBox=""
                        txtNombreRubro.textoInputBox=""
                        txtCodigoRubro.tomarElFoco()

                        modeloListaRubrosComboBox.limpiarListaRubros()
                        modeloListaRubrosComboBox.buscarRubros("1=","1")

                    }else if(resultadoConsulta==-1){
                        txtMensajeInformacionRubros.color="#d93e3e"
                        txtMensajeInformacionRubros.text="No se pudo conectar a la base de datos"


                    }else if(resultadoConsulta==-2){
                        txtMensajeInformacionRubros.color="#d93e3e"
                        txtMensajeInformacionRubros.text="No se pudo actualizar la información del rubro"


                    }else if(resultadoConsulta==-3){
                        txtMensajeInformacionRubros.color="#d93e3e"
                        txtMensajeInformacionRubros.text="No se pudo dar de alta el rubro"


                    }else if(resultadoConsulta==-4){
                        txtMensajeInformacionRubros.color="#d93e3e"
                        txtMensajeInformacionRubros.text="No se pudo realizar la consulta a la base de datos"


                    }else if(resultadoConsulta==-5){
                        txtMensajeInformacionRubros.color="#d93e3e"
                        txtMensajeInformacionRubros.text="Faltan datos para guardar el rubro"

                    }               
            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarRubro
            x: 54
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            toolTip: "Eliminar Rubro"
            anchors.verticalCenter: parent.verticalCenter
            z: 6
            onClic: {


                if(txtCodigoRubro.textoInputBox.trim()!="")
                    if(funcionesmysql.mensajeAdvertencia("Realmente desea eliminar el rubro "+txtCodigoRubro.textoInputBox.trim()+"?\n\nPresione [ Sí ] para confirmar.")){

                txtMensajeInformacionRubros.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                if(modeloListaRubros.eliminarRubro(txtCodigoRubro.textoInputBox.trim())){

                    txtMensajeInformacionRubros.color="#2f71a0"
                    txtMensajeInformacionRubros.text="Rubro "+txtCodigoRubro.textoInputBox.trim()+" eliminado."

                    modeloListaRubros.limpiarListaRubros()
                    modeloListaRubros.buscarRubros("1=","1")
                    listaDeRubros.currentIndex=0;

                    txtCodigoRubro.textoInputBox=""
                    txtNombreRubro.textoInputBox=""
                    txtCodigoRubro.tomarElFoco()

                    modeloListaRubrosComboBox.limpiarListaRubros()
                    modeloListaRubrosComboBox.buscarRubros("1=","1")

                }else{

                    txtMensajeInformacionRubros.color="#d93e3e"
                    txtMensajeInformacionRubros.text="No se puede eliminar el rubro."

                }}
            }
        }

        BotonBarraDeHerramientas {
            id: botonListarTodosLosRubros
            x: 47
            y: 10
            toolTip: "Listar todos los Rubros"
            z: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            anchors.verticalCenter: parent.verticalCenter

            onClic: {

                modeloListaRubros.limpiarListaRubros()
                modeloListaRubros.buscarRubros("1=","1")
                listaDeRubros.currentIndex=0;


            }
        }

        Text {
            id: txtMensajeInformacionRubros
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            //
            font.pixelSize: 15
            style: Text.Raised
            visible: false
            styleColor: "#ffffff"
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignTop
        }
        anchors.bottom: flow1.top
        anchors.bottomMargin: 15
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
        id: rectListaDeRubros
        width: 350
        color: "#C4C4C6"
        radius: 3
        clip: true
        anchors.top: flow1.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 0
        //
        ListView {
            id: listaDeRubros
            clip: true
            highlightRangeMode: ListView.NoHighlightRange
            anchors.top: parent.top
            boundsBehavior: Flickable.DragAndOvershootBounds
            highlightFollowsCurrentItem: true
            anchors.right: parent.right
            delegate: ListaRubros{}
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
            model: modeloListaRubros

            Rectangle {
                id: rectangle3
                y: listaDeRubros.visibleArea.yPosition * listaDeRubros.height+5
                width: 10
                color: "#000000"
                height: listaDeRubros.visibleArea.heightRatio * listaDeRubros.height+18
                radius: 2
                anchors.right: listaDeRubros.right
                anchors.rightMargin: 4
                z: 1
                opacity: 0.500
                visible: true
                //
            }
        }

        Text {
            id: txtTituloListaRubros
            text: "Rubros: "+listaDeRubros.count
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
            x: 333
            y: 355
            width: 14
            height: 14
            anchors.right: parent.right
            anchors.rightMargin: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
            anchors.bottom: parent.bottom
            toolTip: ""
            anchors.bottomMargin: 5
            rotation: -90

            onClic: listaDeRubros.positionViewAtIndex(listaDeRubros.count-1,0)

        }

        BotonBarraDeHerramientas {
            id: botonSubirListaFinal1
            x: 333
            y: 6
            width: 14
            height: 14
            anchors.right: parent.right
            anchors.rightMargin: 3
            anchors.top: parent.top
            anchors.topMargin: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
            toolTip: ""
            rotation: 90


            onClic: listaDeRubros.positionViewAtIndex(0,0)


        }
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }


    Timer{
        id:txtMensajeInformacionTimer
        repeat: false
        interval: 5000
        onTriggered: {

            txtMensajeInformacionRubros.visible=false
            txtMensajeInformacionRubros.color="#d93e3e"

            txtMensajeInformacionSubRubros.visible=false
            txtMensajeInformacionSubRubros.color="#d93e3e"
        }
    }

    Row {
        id: rowBarraDeHerramientasSubRubros
        x: 36
        y: 51
        height: 30
        anchors.right: parent.right
        anchors.rightMargin: 10
        //
        spacing: 15
        BotonBarraDeHerramientas {
            id: botonNuevoSubRubro
            x: 33
            y: 10
            //source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/SubRubros.png"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Nuevo.png"
            toolTip: "Nuevo Sub Rubro"
            anchors.verticalCenter: parent.verticalCenter
            z: 8
            onClic: {                               

                txtCodigoSubRubro.textoInputBox=modeloListaSubRubros.ultimoRegistroDeSubRubro()
                txtNombreSubRubro.textoInputBox=""
                cbxListaRubrosMantenimiento.codigoValorSeleccion=1
                cbxListaRubrosMantenimiento.textoComboBox=modeloListaRubros.retornaNombreRubro(1)
                txtNombreSubRubro.tomarElFoco()
            }
        }

        BotonBarraDeHerramientas {
            id: botonGuardarSubRubro
            x: 61
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            toolTip: "Gurardar Sub Rubro"
            anchors.verticalCenter: parent.verticalCenter
            z: 7
            onClic: {

                txtMensajeInformacionSubRubros.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                    var resultadoConsulta = modeloListaSubRubros.insertarSubRubro(txtCodigoSubRubro.textoInputBox,cbxListaRubrosMantenimiento.codigoValorSeleccion, txtNombreSubRubro.textoInputBox)

                    if(resultadoConsulta==1){

                        txtMensajeInformacionSubRubros.color="#2f71a0"
                        txtMensajeInformacionSubRubros.text="Sub rubro "+ txtCodigoSubRubro.textoInputBox+" dado de alta ok"

                        modeloListaSubRubros.limpiarListaSubRubros()
                        modeloListaSubRubros.buscarSubRubros("codigoSubRubro=",txtCodigoSubRubro.textoInputBox)
                        listaDeSubRubros.currentIndex=0;

                        txtCodigoSubRubro.textoInputBox=""
                        txtNombreSubRubro.textoInputBox=""
                        txtCodigoSubRubro.tomarElFoco()

                        modeloListaSubRubrosComboBox.limpiarListaSubRubros()
                        modeloListaSubRubrosComboBox.buscarSubRubros("1=","1")

                    }else if(resultadoConsulta==2){
                        txtMensajeInformacionSubRubros.color="#2f71a0"
                        txtMensajeInformacionSubRubros.text="Sub rubro "+ txtCodigoSubRubro.textoInputBox+" actualizado."

                        modeloListaSubRubros.limpiarListaSubRubros()
                        modeloListaSubRubros.buscarSubRubros("codigoSubRubro=",txtCodigoSubRubro.textoInputBox)
                        listaDeSubRubros.currentIndex=0;

                        txtCodigoSubRubro.textoInputBox=""
                        txtNombreSubRubro.textoInputBox=""
                        txtCodigoSubRubro.tomarElFoco()

                        modeloListaSubRubrosComboBox.limpiarListaSubRubros()
                        modeloListaSubRubrosComboBox.buscarSubRubros("1=","1")

                    }else if(resultadoConsulta==-1){
                        txtMensajeInformacionSubRubros.color="#d93e3e"
                        txtMensajeInformacionSubRubros.text="No se pudo conectar a la base de datos"


                    }else if(resultadoConsulta==-2){
                        txtMensajeInformacionSubRubros.color="#d93e3e"
                        txtMensajeInformacionSubRubros.text="No se pudo actualizar la información del sub rubro"


                    }else if(resultadoConsulta==-3){
                        txtMensajeInformacionSubRubros.color="#d93e3e"
                        txtMensajeInformacionSubRubros.text="No se pudo dar de alta el sub rubro"


                    }else if(resultadoConsulta==-4){
                        txtMensajeInformacionSubRubros.color="#d93e3e"
                        txtMensajeInformacionSubRubros.text="No se pudo realizar la consulta a la base de datos"


                    }else if(resultadoConsulta==-5){
                        txtMensajeInformacionSubRubros.color="#d93e3e"
                        txtMensajeInformacionSubRubros.text="Faltan datos para guardar el rubro"

                    }
            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarSubRubro
            x: 54
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            toolTip: "Eliminar Sub Rubro"
            anchors.verticalCenter: parent.verticalCenter
            z: 6
            onClic: {

                if(txtCodigoSubRubro.textoInputBox.trim()!="")
                    if(funcionesmysql.mensajeAdvertencia("Realmente desea eliminar el sub rubro "+txtCodigoSubRubro.textoInputBox.trim()+"?\n\nPresione [ Sí ] para confirmar.")){

                txtMensajeInformacionSubRubros.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                if(modeloListaSubRubros.eliminarSubRubro(txtCodigoSubRubro.textoInputBox.trim())){

                    txtMensajeInformacionSubRubros.color="#2f71a0"
                    txtMensajeInformacionSubRubros.text="Sub rubro "+txtCodigoSubRubro.textoInputBox.trim()+" eliminado."

                    modeloListaSubRubros.limpiarListaSubRubros()
                    modeloListaSubRubros.buscarSubRubros("1=","1")
                    listaDeSubRubros.currentIndex=0;

                    txtCodigoSubRubro.textoInputBox=""
                    txtNombreSubRubro.textoInputBox=""
                    txtCodigoSubRubro.tomarElFoco()

                    modeloListaSubRubrosComboBox.limpiarListaSubRubros()
                    modeloListaSubRubrosComboBox.buscarSubRubros("1=","1")

                }else{

                    txtMensajeInformacionSubRubros.color="#d93e3e"
                    txtMensajeInformacionSubRubros.text="No se puede eliminar el sub rubro."

                }}


            }
        }

        BotonBarraDeHerramientas {
            id: botonListarTodosLosSubRubros
            x: 47
            y: 10
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            toolTip: "Listar todos los Sub Rubros"
            anchors.verticalCenter: parent.verticalCenter
            z: 5
            onClic: {
                modeloListaSubRubros.limpiarListaSubRubros()
                modeloListaSubRubros.buscarSubRubros("1=","1")
            }
        }

        Text {
            id: txtMensajeInformacionSubRubros
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            //
            font.pixelSize: 15
            style: Text.Raised
            visible: false
            styleColor: "#ffffff"
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignTop
        }
        anchors.bottom: flow1.top
        anchors.bottomMargin: 15
        anchors.leftMargin: 40
        anchors.left: rectListaDeRubros.right
    }

    Flow {
        id: flowSubRubros
        x: 22
        y: 93
        height: flowSubRubros.implicitHeight
        anchors.right: parent.right
        anchors.rightMargin: 0
        spacing: 5
        flow: Flow.LeftToRight
        anchors.top: parent.top
        anchors.topMargin: 70
        TextInputSimple {
            id: txtCodigoSubRubro
          //  width: 130
            textoInputBox: ""
            botonBuscarTextoVisible: false
            inputMask: "000000;"
            largoMaximo: 6
            botonBorrarTextoVisible: true
            textoTitulo: "Código sub rubro:"
            colorDeTitulo: "#333333"
            onTabulacion: txtNombreSubRubro.tomarElFoco()
            onEnter: txtNombreSubRubro.tomarElFoco()
        }

        TextInputSimple {
            id: txtNombreSubRubro
          //  width: 190
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            botonBorrarTextoVisible: true
            largoMaximo: 35
            textoTitulo: "Nombre sub rubro:"
            colorDeTitulo: "#333333"
            onTabulacion: cbxListaRubrosMantenimiento.tomarElFoco()
            onEnter: cbxListaRubrosMantenimiento.tomarElFoco()
        }

        ComboBoxListaRubros {
            id: cbxListaRubrosMantenimiento
            x: 391
            y: 0
            width: 170
            z: 1
            colorRectangulo: "#cac1bd"
            colorTitulo: "#333333"
            textoTitulo: "Rubros:"
            codigoValorSeleccion: "1"
            textoComboBox: modeloListaRubros.retornaNombreRubro(1)
            onEnter: txtCodigoSubRubro.tomarElFoco()
            onTabulacion: txtCodigoSubRubro.tomarElFoco()
        }
        z: 1
        anchors.leftMargin: 40
        anchors.left: rectListaDeRubros.right
    }

    Rectangle {
        id: rectListaDeRubros1
        x: 2
        y: -9
        color: "#c4c4c6"
        radius: 3
        clip: true
        anchors.right: parent.right
        anchors.rightMargin: 0
        //
        anchors.top: flowSubRubros.bottom
        anchors.topMargin: 20
        ListView {
            id: listaDeSubRubros
            highlightRangeMode: ListView.NoHighlightRange
            anchors.top: parent.top
            boundsBehavior: Flickable.DragAndOvershootBounds
            highlightFollowsCurrentItem: true
            anchors.right: parent.right
            delegate: ListaSubRubros {
            }
            snapMode: ListView.NoSnap
            anchors.bottomMargin: 25
            spacing: 1
            anchors.bottom: parent.bottom
            clip: true
            flickableDirection: Flickable.VerticalFlick
            anchors.leftMargin: 1
            keyNavigationWraps: true
            anchors.left: parent.left
            interactive: true
            //
            anchors.topMargin: 25
            anchors.rightMargin: 1
            model: modeloListaSubRubros            

            Rectangle {
                id: rectangle4
                y: listaDeSubRubros.visibleArea.yPosition * listaDeSubRubros.height+5
                width: 10
                color: "#000000"
                height: listaDeSubRubros.visibleArea.heightRatio * listaDeSubRubros.height+18
                radius: 2
                anchors.right: listaDeSubRubros.right
                anchors.rightMargin: 4
                z: 1
                opacity: 0.500
                visible: true
                //
            }
        }

        Text {
            id: txtTituloListaSubRubros
            text: "Sub Rubros: "+listaDeSubRubros.count
            font.family: "Arial"
            anchors.top: parent.top
            anchors.topMargin: 5
            font.bold: false
            font.pointSize: 10
            anchors.leftMargin: 5
            anchors.left: parent.left
        }

        BotonBarraDeHerramientas {
            id: botonBajarListaFinal2
            x: 333
            y: 355
            width: 14
            height: 14
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
            anchors.bottom: parent.bottom
            anchors.rightMargin: 3
            toolTip: ""
            anchors.bottomMargin: 5
            rotation: -90
            anchors.right: parent.right

            onClic: listaDeSubRubros.positionViewAtIndex(listaDeSubRubros.count-1,0)

        }

        BotonBarraDeHerramientas {
            id: botonSubirListaFinal2
            x: 333
            y: 6
            width: 14
            height: 14
            anchors.top: parent.top
            anchors.topMargin: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
            anchors.rightMargin: 3
            toolTip: ""
            rotation: 90
            anchors.right: parent.right

            onClic: listaDeSubRubros.positionViewAtIndex(0,0)

        }
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.leftMargin: 30
        anchors.left: rectListaDeRubros.right
    }

}
