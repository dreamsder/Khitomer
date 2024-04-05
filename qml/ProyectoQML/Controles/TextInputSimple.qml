/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2024>  <Cristian Montano>

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
    //width: 500
    property int altoControl: 32
    property int altoControlRecta: 18
    property int tamanioFuente: 9
    property int tamanioFuenteTitulo: 13
    width: {


        if(fijoTamanioPersonalizado!=0){
            fijoTamanioPersonalizado
        }else{

            if(txtTextInput.text=="" && (txtTextoSombra.text=="" && !txtTextoSombra.visible)){


                txtTitulo.implicitWidth+txtInformacionError.implicitWidth+50

            }else if(txtTextInput.text=="" && (txtTextoSombra.text!="" && txtTextoSombra.visible)){
                if(txtTextoSombra.implicitWidth>=(txtTitulo.implicitWidth+txtInformacionError.implicitWidth)){
                    txtTextoSombra.implicitWidth+50
                }else{
                    txtTitulo.implicitWidth+txtInformacionError.implicitWidth+50
                }
            }else if(txtTextInput.text=="" && (txtTextoSombra.text!="" && !txtTextoSombra.visible)){

                txtTitulo.implicitWidth+txtInformacionError.implicitWidth+50

            }
            else if(txtTextInput.text=="" && (txtTextoSombra.text=="" && txtTextoSombra.visible)){

                txtTitulo.implicitWidth+txtInformacionError.implicitWidth+50

            }
            else if(txtTextInput.text!="" && txtTextoSombra.text==""){
                if(txtTextInput.implicitWidth>=(txtTitulo.implicitWidth+txtInformacionError.implicitWidth)){
                    txtTextInput.implicitWidth+50
                }else{
                    txtTitulo.implicitWidth+txtInformacionError.implicitWidth+50
                }
            }else if(txtTextInput.text!="" && (txtTextoSombra.text!="" && !txtTextoSombra.visible)){
                if(txtTextInput.implicitWidth>=(txtTitulo.implicitWidth+txtInformacionError.implicitWidth)){
                    txtTextInput.implicitWidth+50
                }else{
                    txtTitulo.implicitWidth+txtInformacionError.implicitWidth+50
                }
            }
        }
    }

    height: altoControl
    color: "#00000000"

    property int fijoTamanioPersonalizado: 0

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

    property alias tituloImpricitWidth: txtTitulo.implicitWidth

    property int margenIzquierdo: 5

    property alias rectanguloTextoAlto: recTextInput.height
    property alias textoInputFontSize: txtTextInput.font.pointSize


    property alias enable: txtTextInput.enabled

    property alias colorDeTitulo: txtTitulo.color


    signal tabulacion
    signal enter
    signal clicEnBusqueda
    signal pierdoFoco

    function tomarElFoco(){
        txtTextInput.focus=true
        if(enFocoSeleccionarTodo){
            txtTextInput.selectAll()
        }

    }

    function mensajeError(mensaje){

        txtInformacionErrorTimer.stop()
        txtInformacionError.text=mensaje
        txtInformacionError.visible=true
        txtInformacionErrorTimer.start()


    }



    Rectangle {
        id:recTextInput
        height: altoControlRecta
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
            height: parent.height
            color: "#000000"
            text: qsTr("")
            anchors.rightMargin: 25
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.left: parent.left
            font.family: "Arial"
            //
            horizontalAlignment: TextInput.AlignHCenter

            inputMask: ""
            echoMode: TextInput.Normal
            z: 2
            font.pointSize: tamanioFuente
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
                    pierdoFoco()
                    colorOff.start()
                    opacityOff.start()
                    if(txtTextInput.text.trim()==""){
                        txtTextoSombra.visible=true
                    }

                }
            }

            onTextChanged: {

                if(txtTextInput.text.trim()=="" && txtTextInput.activeFocus==false){
                    txtTextoSombra.visible=true
                }else{
                    txtTextoSombra.visible=false

                }
            }



            Keys.onTabPressed: tabulacion()

            Keys.onEnterPressed: enter()

            Keys.onReturnPressed: enter()


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
                    tomarElFoco()
                }
            }
        }


    }

    Text {
        id: txtTitulo
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
        anchors.leftMargin: margenIzquierdo
        font.pixelSize: tamanioFuenteTitulo
    }

    Image {
        id: imageBuscar
        y: 16
        height: 20
        //
        anchors.left: recTextInput.right
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        asynchronous: true
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
        font.pixelSize: 12
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
}
