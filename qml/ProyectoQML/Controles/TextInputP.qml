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
    id: rectangle1
    width: 500
    height: 32
    color: "#00000000"

    property alias textoTitulo: txtTitulo.text
    property alias textoInputBox: txtTextInput.text
    property alias echoMode: txtTextInput.echoMode
    property alias inputMask: txtTextInput.inputMask
    property double opacidadPorDefecto: 0.8
    property alias botonBorrarTextoVisible: rectBotonEliminarTexto.visible
    property alias cursor_Visible: txtTextInput.cursorVisible
    property alias botonBuscarTextoVisible : imageBuscar.visible
    property alias largoMaximo: txtTextInput.maximumLength
    property alias  validaFormato: txtTextInput.validator
    property bool enFocoSeleccionarTodo: false
    property alias textoDeFondo: txtTextoSombra.text
    property bool utilizaListaDesplegable: false
    property alias textoTituloFiltro: textinputsimple1.textoTitulo
    property alias tamanioRectPrincipalCombobox: rectPrincipalComboBox.width
    property alias tamanioRectPrincipalComboboxAlto: rectPrincipalComboBox.height
    property alias checkBoxActivoVisible: cbxActivo.visible
    property alias checkBoxActivoTexto: cbxActivo.textoValor
    property alias checkBoxActivoEstado: cbxActivo.chekActivo
    property alias comboboxVisible:rectPrincipalComboBox.visible


    property alias enable: txtTextInput.enabled

    property string textoAFiltrar: ""

    property alias colorDeTitulo: txtTitulo.color

    property alias listviewDelegate: listview1.delegate
    property alias listviewModel: listview1.model

    property alias botonNuevoTexto: botoncargardato1.texto

    property alias botonNuevoVisible: botoncargardato1.visible



    signal tabulacion
    signal enter
    signal clicEnBusqueda
    signal clicEnBusquedaFiltro

    signal clicBotonNuevoItem
    signal checkActivoCambia

    signal abrirComboBox
    signal cierreComboBox


    function tomarElFocoP(){
        txtTextInput.focus=true
        if(enFocoSeleccionarTodo){
            txtTextInput.selectAll()
        }

    }

    function tomarElFocoResultado(){
        listview1.currentIndex=0
        listview1.focus=true
        listview1.forceActiveFocus()
    }

    function mensajeError(mensaje){

        txtInformacionErrorTimer.stop()
        txtInformacionError.text=mensaje
        txtInformacionError.visible=true
        txtInformacionErrorTimer.start()


    }

    function cerrarComboBox(){
        rectPrincipalComboBoxAparecerYIn.stop()
        mouse_area1.enabled=true
        rectPrincipalComboBox.visible=false
        cierreComboBox()
    }



    Rectangle {
        id:recTextInput
        height: 18
        radius: 2
        anchors.right: parent.right
        anchors.rightMargin: 21
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        //
        border.width: 1
        border.color: "#686b71"




        opacity: opacidadPorDefecto

        PropertyAnimation{
            id: colorIn
            target: recTextInput
            property: "border.color"
            from:"#686b71"
            to: "#0470fd"
            duration: 500
        }
        PropertyAnimation{
            id: colorOff
            target: recTextInput
            property: "border.color"
            from: "#0470fd"
            to:"#686b71"
            duration: 500
        }

        PropertyAnimation{
            id: opacityIn
            target: recTextInput
            property: "opacity"
            from:opacidadPorDefecto
            to: 1
            duration: 200
        }
        PropertyAnimation{
            id: opacityOff
            target: recTextInput
            property: "opacity"
            from: 1
            to:opacidadPorDefecto
            duration: 200
        }


        TextInput {
            id: txtTextInput
            color: "#000000"
            text: qsTr("")
            font.family: "Arial"
            //
            anchors.topMargin: 1
            horizontalAlignment: TextInput.AlignHCenter
            anchors.rightMargin: 25
            anchors.leftMargin: 5
            anchors.fill: parent
            inputMask: ""
            echoMode: TextInput.Normal
            z: 2            
            font.pointSize: 9
            font.bold: false
            maximumLength: 45
            selectByMouse: true
            selectionColor: "gray"
            onActiveFocusChanged: {

                if(txtTextInput.activeFocus==true){
                    colorIn.start()
                    opacityIn.start()
                    txtTextoSombra.visible=false



                }
                if(txtTextInput.activeFocus==false){
                    colorOff.start()
                    opacityOff.start()
                    if(txtTextInput.text.trim()==""){
                        txtTextoSombra.visible=true
                    }

                }
            }

            onTextChanged:{
                if(txtTextInput.text.trim()=="" && txtTextInput.activeFocus==false){
                  txtTextoSombra.visible=true
                }else{
                    txtTextoSombra.visible=false
                }
            }


            Keys.onTabPressed: tabulacion()

            Keys.onEnterPressed: enter()

            Keys.onReturnPressed: enter()

            Keys.onDownPressed:  {
                if(utilizaListaDesplegable){
                    rectPrincipalComboBoxAparecerYIn.start()
                    rectPrincipalComboBox.visible=true
                    textinputsimple1.tomarElFoco()
                    abrirComboBox()
                }
            }

            Text {
                id: txtTextoSombra
                color:"#8b8888"
                font.family: "Arial"
                font.italic: true
                anchors.fill: parent
                font.pointSize: txtTextInput.font.pointSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }           
        }



        Rectangle {
            id: rectBotonEliminarTexto
            x: 441
            y: 0
            width: 15
            color: "#00000000"
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            anchors.top: parent.top
            anchors.topMargin: 2

            Text {
                id: txtBorrarContenido
                x: 6
                y: 8
                color: "#64000000"
                text: qsTr("<X")
                font.family: "Arial"
                //
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 9
            }

            MouseArea {
                id: mouse_area1
                anchors.fill: parent
                onClicked: {txtTextInput.text=""
                    tomarElFocoP()
                }
            }
        }


    }

    Text {
        id: txtTitulo
        y: 2
        width: txtTitulo.implicitWidth
        height: 13
        color: "#dbd8d8"
        text: qsTr("Titulo:")
        font.family: "Arial"
        verticalAlignment: Text.AlignBottom
        //
        font.bold: true
        anchors.bottom: recTextInput.top
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 5
        font.pixelSize: 11
    }

    Image {
        id: imageBuscar
        y: 16
        height: 20
        //
        anchors.left: recTextInput.right
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        asynchronous: true
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        visible: false
        opacity: 0.5
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Search.png"

        MouseArea {
            id: mouse_area2
            anchors.leftMargin: 1
            anchors.fill: parent
            hoverEnabled: true

            onPressed: {
                imageBuscarScaleOff.stop()
                imageBuscarScaleIn.start()
            }
            onReleased:  {
                imageBuscarScaleIn.stop()
                imageBuscarScaleOff.start()

            }
            onEntered: {
                imageBuscarOpacidadOut.stop()
                imageBuscarOpacidadIn.start()
            }
            onExited: {
                imageBuscarOpacidadIn.stop()
                imageBuscarOpacidadOut.start()

            }
            onClicked: clicEnBusqueda()

        }
    }
    PropertyAnimation{
        id:imageBuscarScaleIn
        target: imageBuscar
        property: "scale"
        from:1
        to:0.93
        duration: 70
    }

    PropertyAnimation{
        id:imageBuscarScaleOff
        target: imageBuscar
        property: "scale"
        to:1
        from:0.93
        duration: 50
    }



    PropertyAnimation{
        id:imageBuscarOpacidadIn
        target: imageBuscar
        property: "opacity"
        from:0.5
        to:1
        duration: 70
    }

    PropertyAnimation{
        id:imageBuscarOpacidadOut
        target: imageBuscar
        property: "opacity"
        from:1
        to:0.5
        duration: 50
    }

    Text {
        id: txtInformacionError
        x: -9
        y: 5
        width: txtInformacionError.implicitWidth
        height: 15
        color: "#d93e3e"
        text: qsTr("")
        font.family: "Arial"
        //
        visible: false
        font.pixelSize: 10
        anchors.bottom: recTextInput.top
        anchors.bottomMargin: 1
        font.bold: true
        anchors.leftMargin: 10
        anchors.left: txtTitulo.right
    }


    Timer{
        id:txtInformacionErrorTimer
        repeat: false
        interval: 5000
        onTriggered: {

            txtInformacionError.visible=false
            txtInformacionError.color="#d93e3e"

        }
    }

    Rectangle {
        id: rectPrincipalComboBox
        x: 0
        y: 39
        height: 300
        color: "#eceeee"
        radius: 3
        //
        border.color: "#a8a0a0"
        Rectangle {
            id: rectSombra
            x: -5
            y: -34
            color: "#1e646262"
            radius: 6
            //
            anchors.fill: parent
            anchors.topMargin: 5
            visible: true
            anchors.rightMargin: -5
            anchors.bottomMargin: -5
            z: -4
            anchors.leftMargin: -5
        }

        MouseArea {
            id: mouse_area4
            clip: false
            anchors.fill: parent

            BotonBarraDeHerramientas {
                id: botonCerrarLista
                x: 456
                y: 5
                width: 18
                height: 18
                //
                anchors.top: parent.top
                anchors.topMargin: 5
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/CerrarLista.png"
                visible: true
                anchors.rightMargin: 5
                anchors.right: parent.right
                onClic: {

                    tomarElFocoP()
                    rectPrincipalComboBoxAparecerYIn.stop()
                    mouse_area1.enabled=true
                    rectPrincipalComboBox.visible=false
                    cierreComboBox()

                }
            }

            Rectangle {
                id: rectangle3
                y: -6
                width: 25
                height: 25
                color: rectPrincipalComboBox.color
                anchors.left: parent.left
                anchors.leftMargin: 50
                anchors.top: parent.top
                anchors.topMargin: -6
                rotation: 45
                z: 1
            }

            Rectangle {
                id: rectLineaSuperior
                y: 5
                height: 2
                color: "#201c1c"
                radius: 1
                //
                anchors.bottom: parent.bottom
                visible: true
                anchors.rightMargin: 1
                anchors.bottomMargin: 0
                z: 4
                anchors.right: parent.right
                anchors.leftMargin: 1
                anchors.left: parent.left
            }

            Rectangle {
                id: rectangle2
                color: "#00000000"
                //
                clip: true
                visible: true
                anchors.right: parent.right
                anchors.rightMargin: 14
                anchors.left: parent.left
                anchors.leftMargin: 1
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 25
                anchors.top: textinputsimple1.bottom
                anchors.topMargin: 12

                ListView {
                    id: listview1
                    anchors.bottomMargin: 0
                    anchors.rightMargin: 0
                    anchors.fill: parent
                    spacing: 10
                    z: 1
                    focus: true
                }
            }

            TextInputSimple {
                id: textinputsimple1
                anchors.top: rowControles.bottom
                anchors.topMargin: 10
                colorDeTitulo: "#333333"
                botonBuscarTextoVisible: true
                botonBorrarTextoVisible: true
                enFocoSeleccionarTodo: true
                textoTitulo: ""
                visible: true
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 10
                onClicEnBusqueda: {
                    textoAFiltrar=textinputsimple1.textoInputBox.trim()
                    clicEnBusquedaFiltro()
                     txtItemsCb.text="Items: "+listview1.count
                }
                onEnter: {
                    textoAFiltrar=textinputsimple1.textoInputBox.trim()
                    clicEnBusquedaFiltro()
                     txtItemsCb.text="Items: "+listview1.count
                }

                Keys.onEscapePressed: {
                    tomarElFoco()
                    cerrarComboBox()
                }

            }

            Rectangle {
                id: rectangle4
                x: 504
                y: 65
                width: 14
                radius: 6
                gradient: Gradient {
                    GradientStop {
                        position: 0.090
                        color: "#eceeee"
                    }

                    GradientStop {
                        position: 0.470
                        color: "#b2b5b5"
                    }

                    GradientStop {
                        position: 0.830
                        color: "#eceeee"
                    }
                }
                z: 5
                visible: true
                //
                opacity: 1
                anchors.top: textinputsimple1.bottom
                anchors.topMargin: 9
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                clip: true
                anchors.right: parent.right
                anchors.rightMargin: 0

                Rectangle {
                    id: scrollbar
                    x: 2
                    width: 10
                    height: listview1.visibleArea.heightRatio * listview1.height+18
                    color: "#000000"
                    radius: height/2 - 1
                    visible: true
                    anchors.right: parent.right
                    anchors.rightMargin: 2
                    //
                    z: 2
                    y: listview1.visibleArea.yPosition * listview1.height+3
                    opacity: 0.550
                }
            }

            Text {
                id: txtItemsCb
                x: 6
                y: 258
                text: qsTr("Items: 0")
                font.family: "Arial"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 7
                //
                font.pixelSize: 9
                visible: true
                font.bold: false
                z: 2
                anchors.leftMargin: 5
                anchors.left: parent.left
            }

            BotonCargarDato {
                id: botoncargardato1
                y: 5
                z: 6
                anchors.left: parent.left
                anchors.leftMargin: 23
                onClic: clicBotonNuevoItem()
            }

            Row {
                id: rowControles
                spacing: 0
                anchors.top: botoncargardato1.bottom
                anchors.topMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 20

                CheckBox {
                    id: cbxActivo
                    chekActivo: false
                    visible: false
                    buscarActivo: false
                    onChekActivoChanged: {
                        checkActivoCambia()
                    }
                }
            }
        }
        visible: false
        border.width: 1
        z: 2001
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    PropertyAnimation{
        id:rectPrincipalComboBoxAparecerYIn
        target: rectPrincipalComboBox
        property: "y"
        from:39
        to: 50
        duration: 200
    }
}
