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

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1



Rectangle {
    id: rectangle2
    width: 500
    height: 32
    color: "#00000000"


    property alias botonBuscarTextoVisible : imageBuscar.visible
    property alias textoTitulo: txtTitulo.text
    property alias textoComboBox: txtTextoSeleccionado.text
    property string codigoValorSeleccion
    property double opacidadPorDefecto: 0.8
    property alias colorTitulo: txtTitulo.color
    property string codigoDePaisSeleccionado:"1"
    property string codigoDeDepartamentoSeleccionado:"1"
    property string codigoDeLocalidadSeleccionado:"1"
    property bool orientacionSubMenu: true

    property string _codigoDePaisSeleccionado:"1"
    property string _codigoDeDepartamentoSeleccionado:"1"
    property string _codigoDeLocalidadSeleccionado:"1"

    property int altoListaDesplegable:200


    property alias colorRectangulo: rectPrincipalComboBox.color

    signal clicEnBusqueda
    signal tabulacion
    signal enter
    signal senialAlAceptarOClick

    function tomarElFoco(){
        if(listview1.count>=10){
            listview1.highlightRangeMode=ListView.StrictlyEnforceRange
            txtItemsCb.text="Items: "+listview1.count
            txtItemsCb.visible=true
            listview1.interactive=true

        }else{
            txtItemsCb.visible=false
            listview1.highlightRangeMode=ListView.NoHighlightRange
            listview1.interactive=false
        }
        if(txtTextoSeleccionado.enabled)
            txtTextoSeleccionado.focus=true

    }
    function activo(valor){
        cerrarComboBox()

        mouse_area1.enabled=valor
        mouse_area2.enabled=valor
        mouse_area3.enabled=valor
        rectangle2.enabled=valor
        txtTextoSeleccionado.enabled=valor

    }

    function cerrarComboBox(){
        rectPrincipalComboBoxAparecerYIn.stop()
        mouse_area1.enabled=true
        rectPrincipalComboBox.visible=false
        modeloDepartamentosComboBox.limpiarListaDepartamentos()
        modeloLocalidadesComboBox.limpiarListaLocalidades()
        rectPrincipalSubMenu.visible=false
        txtTextoSeleccionado.enabled=true

    }

    Keys.onEscapePressed: {

        cerrarComboBox()
    }

    Rectangle {
        id: rectPrincipalComboBox
        x: 0
        y: 39
        radius: 3
        border.width: 1
        border.color: "#a8a0a0"
        color:"#eceeee"
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: -20
        //
        height: listview1.contentHeight+40

        visible: false
        z:2000

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
            anchors.topMargin: 30
            clip: true
            anchors.fill: parent

            ListView {
                id:listview1
                x: 0
                y: 30
                z: 1
                spacing: 10
                anchors.bottomMargin: 10
                anchors.rightMargin: 20
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.fill: parent
                focus: true

                model: modeloPaisesComboBox

                delegate:

                    FocusScope {
                    id: focus
                    width: childrenRect.width; height: childrenRect.height
                    x:childrenRect.x; y: childrenRect.y


                    Rectangle{
                        id:rect1
                        height: texto1.implicitHeight
                        width: rectPrincipalComboBox.width
                        color: "transparent"

                        Image {
                            id: imagenReporte
                            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaDerecha.png"
                            //
                            width: rect1.height
                            anchors.right: parent.right
                            anchors.rightMargin: 3
                            asynchronous: true
                            anchors.top: parent.top
                            anchors.topMargin: 0
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                        }

                        Text {
                            id: texto1
                            focus: true
                            text: descripcionPais
                            //
                            font.pointSize: 10
                            color:"#212121"
                            styleColor: "white"
                            font.family: "Arial"
                            style: Text.Raised
                            z: 100
                            anchors.left: parent.left
                            anchors.leftMargin: 10

                            onActiveFocusChanged: {

                                if(activeFocus){
                                    opacityOff.stop()
                                    opacityIn.start()
                                    texto1.color="white"
                                    texto1.style= Text.Normal
                                    texto1.font.bold= true
                                }else{
                                    opacityIn.stop()
                                    opacityOff.start()
                                    texto1.color="#212121"
                                    texto1.style= Text.Raised
                                    texto1.font.bold= false
                                }



                            }

                            Rectangle {
                                id: rectTextComboBox
                                y: 12
                                height: 19
                                color: "#5358be"
                                width: listview1.width+20
                                radius: 1
                                //
                                opacity: 0
                                border.width: 0
                                border.color: "#000000"
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: -3
                                anchors.left: parent.left
                                anchors.leftMargin: -10
                                anchors.top: parent.top
                                anchors.topMargin: -3
                                z:-50



                            }
                            PropertyAnimation{
                                id: opacityIn
                                target: rectTextComboBox
                                property: "opacity"
                                from:0
                                to: 0.60
                                duration: 200
                            }
                            PropertyAnimation{
                                id: opacityOff
                                target: rectTextComboBox
                                property: "opacity"
                                from: 0.60
                                to:0
                                duration: 50
                            }

                            Keys.onReturnPressed: {

                                modeloDepartamentosComboBox.limpiarListaDepartamentos()
                                modeloDepartamentosComboBox.buscarDepartamentos(" codigoPais=",codigoPais)
                                _codigoDePaisSeleccionado=codigoPais
                                if(rectPrincipalSubMenu.visible==false){
                                    listview2.forceActiveFocus()
                                    rectPrincipalSubMenu.visible=true
                                }

                            }
                            MouseArea{
                                id:mouseArea
                                height: texto1.height
                                width: listview1.width
                                hoverEnabled: true
                                onClicked: {

                                    listview2.forceActiveFocus()

                                    modeloDepartamentosComboBox.limpiarListaDepartamentos()
                                    modeloDepartamentosComboBox.buscarDepartamentos(" codigoPais=",codigoPais)
                                    _codigoDePaisSeleccionado=codigoPais

                                    if(rectPrincipalSubMenu.visible==false){
                                        listview2.forceActiveFocus()
                                        rectPrincipalSubMenu.visible=true
                                    }

                                }

                                onEntered: {

                                    opacityOff.stop()
                                    opacityIn.start()
                                    texto1.color="white"
                                    texto1.style= Text.Normal
                                    texto1.font.bold= true

                                }
                                onExited:{

                                    opacityIn.stop()
                                    opacityOff.start()
                                    texto1.color="#212121"
                                    texto1.style= Text.Raised
                                    texto1.font.bold= false

                                }
                            }
                        }
                    }
                }
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
                z: 3
                anchors.right: parent.right
                anchors.leftMargin: 1
                anchors.left: parent.left
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
            z: 2
        }

        Text {
            id: txtItemsCb
            x: 60
            y: 40
            text: qsTr("Items:")
            font.family: "Arial"
            visible: false
            font.bold: false
            z: 4
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            //
            font.pixelSize: 9
        }

        BotonBarraDeHerramientas {
            id: botonCerrarLista
            x: 497
            y: 35
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
                cerrarComboBox()

            }
        }
    }

    Rectangle {
        id: rectTextComboBox2
        x: 0
        y: -19
        height: 18
        color: "#ffffff"
        radius: 2
        border.color: "#686b71"
        TextInput {
            id: txtTextoSeleccionado
            color: "#000000"
            text: qsTr("")
            font.family: "Arial"
            //
            anchors.topMargin: 1
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.rightMargin: 0
            font.bold: false
            font.pointSize: 9
            z: 1
            anchors.right: imageBotonComboBoxAbajo.left
            horizontalAlignment: TextInput.AlignHCenter
            anchors.left: parent.left

            onActiveFocusChanged: {




                if(txtTextoSeleccionado.activeFocus==true){
                    colorIn2.start()
                    opacityIn2.start()


                    if(rectPrincipalComboBox.visible==false){
                        tomarElFoco()
                        listview1.forceActiveFocus()
                        rectPrincipalComboBox.visible=true
                        rectPrincipalComboBoxAparecerYIn.start();
                        txtTextoSeleccionado.enabled=false
                    }


                }
                if(txtTextoSeleccionado.activeFocus==false){
                    colorOff2.start()
                    opacityOff2.start()

                }
            }

        }
        MouseArea {
            id: mouse_area1
            visible: false
            anchors.fill: parent
            onClicked: {
                mouse_area1.enabled=false
            }
        }
        Image {
            id: imageBotonComboBoxAbajo
            x: 425
            y: 56
            width: 16
            height: 16
            asynchronous: true
            z: 2
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaAbajoComboBox.png"
            anchors.rightMargin: 2
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right

            MouseArea {
                id: mouse_area3
                anchors.fill: parent
                onClicked: tomarElFoco()
            }
        }
        anchors.bottom: parent.bottom
        anchors.rightMargin: 21
        border.width: 1
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.leftMargin: 0
        opacity: opacidadPorDefecto
        anchors.left: parent.left
    }

    Text {
        id: txtTitulo
        x: 0
        y: -34
        height: 13
        width: txtTitulo.implicitWidth
        color: "#dbd8d8"
        text: qsTr("Titulo:")
        font.family: "Arial"
        //
        verticalAlignment: Text.AlignBottom
        font.pixelSize: 10
        anchors.top: parent.top
        anchors.topMargin: 0
        font.bold: true
        anchors.leftMargin: 5
        anchors.left: parent.left
    }

    PropertyAnimation{
        id:rectPrincipalComboBoxAparecerYIn
        target: rectPrincipalComboBox
        property: "y"
        from:39
        to: 48
        duration: 200
    }

    PropertyAnimation{
        id: colorIn2
        target: rectTextComboBox2
        property: "border.color"
        from:"#686b71"
        to: "#0470fd"
        duration: 500
    }
    PropertyAnimation{
        id: colorOff2
        target: rectTextComboBox2
        property: "border.color"
        from: "#0470fd"
        to:"#686b71"
        duration: 500
    }

    PropertyAnimation{
        id: opacityIn2
        target: rectTextComboBox2
        property: "opacity"
        from:opacidadPorDefecto
        to: 1
        duration: 200
    }
    PropertyAnimation{
        id: opacityOff2
        target: rectTextComboBox2
        property: "opacity"
        from: 1
        to:opacidadPorDefecto
        duration: 200
    }

    Image {
        id: imageBuscar
        y: 16
        height: 20
        anchors.left: rectTextComboBox2.right
        anchors.right: parent.right
        anchors.rightMargin: 0
        //
        asynchronous: true
        MouseArea {
            id: mouse_area2
            hoverEnabled: true
            anchors.fill: parent
            anchors.leftMargin: 1

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
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Search.png"
        anchors.bottom: parent.bottom
        visible: false
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        opacity: 0.500
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

    Rectangle {
        id: rectPrincipalSubMenu
        x: 501
        y: 49
        width: 250
        height: altoListaDesplegable
        color: "#ecf0f0"
        radius: 3
        anchors.top: parent.top
        anchors.topMargin: 80
        anchors.leftMargin: {

            if(orientacionSubMenu){
                1
            }else{
                (rectPrincipalSubMenu.width*-1)+1
            }
        }
        anchors.left: rectPrincipalComboBox.right
        visible: false
        border.width: 1
        z: 2001

        //
        border.color: "#a7a0a0"

        onVisibleChanged: {

            if(listview2.count>=6){
                listview2.highlightRangeMode=ListView.StrictlyEnforceRange
                txtItemsCb1.text="Items: "+listview2.count
                txtItemsCb1.visible=true


            }else{
                txtItemsCb1.visible=false
                listview2.highlightRangeMode=ListView.NoHighlightRange

            }

        }

        Rectangle {
            id: rectSombra1
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
            anchors.leftMargin: 0
        }

        MouseArea {
            id: mouse_area5
            clip: true
            anchors.fill: parent
            ListView {
                id: listview2
                x: 0
                y: 30
                snapMode: ListView.SnapToItem
                highlightRangeMode: ListView.StrictlyEnforceRange
                clip: false
                spacing: 10
                anchors.fill: parent
                anchors.topMargin: 30
                anchors.rightMargin: 20
                anchors.bottomMargin: 10
                delegate: FocusScope {
                    x: childrenRect.x
                    y: childrenRect.y
                    width: childrenRect.width
                    height: childrenRect.height
                    Rectangle {
                        id: rect2
                        width: rectPrincipalSubMenu.width
                        height: texto2.implicitHeight
                        color: "#00000000"


                        Text {
                            id: texto2
                            color: "#000000"
                            text: descripcionDepartamento
                            //
                            style: Text.Raised
                            styleColor: "#ffffff"
                            font.family: "Arial"
                            focus: true
                            font.pointSize: 10
                            z: 100
                            anchors.leftMargin: 10
                            anchors.left: parent.left

                            onActiveFocusChanged: {


                                if(activeFocus){

                                    opacityOff1.stop()
                                    opacityIn1.start()
                                    texto2.color="white"
                                    texto2.style= Text.Normal
                                    texto2.font.bold= true
                                }else{
                                    opacityIn1.stop()
                                    opacityOff1.start()
                                    texto2.color="#212121"
                                    texto2.style= Text.Raised
                                    texto2.font.bold= false
                                }



                            }
                            Rectangle {
                                id: rectTextComboBox1
                                y: 12
                                width: listview2.width+20
                                height: 19
                                color: "#5358be"
                                radius: 1
                                //
                                anchors.top: parent.top
                                border.color: "#000000"
                                anchors.topMargin: -3
                                anchors.bottom: parent.bottom
                                border.width: 0
                                anchors.bottomMargin: -3
                                z: -50
                                anchors.leftMargin: -10
                                opacity: 0
                                anchors.left: parent.left
                            }

                            PropertyAnimation {
                                id: opacityIn1
                                target: rectTextComboBox1
                                property: "opacity"
                                to: 0.600
                                from: 0
                                duration: 200
                            }

                            PropertyAnimation {
                                id: opacityOff1
                                target: rectTextComboBox1
                                property: "opacity"
                                to: 0
                                from: 0.600
                                duration: 50
                            }

                            Keys.onReturnPressed: {


                                codigoDePaisSeleccionado=_codigoDePaisSeleccionado
                                codigoDeDepartamentoSeleccionado=codigoDepartamento
                                listview1.forceActiveFocus()
                                rectPrincipalComboBox.visible=false
                                txtTextoSeleccionado.text=descripcionDepartamento
                                txtTextoSeleccionado.enabled=true
                                codigoValorSeleccion=codigoDepartamento
                                cerrarComboBox()
                                senialAlAceptarOClick()

                            }

                            MouseArea {
                                id: mouseArea1
                                width: listview2.width
                                height: texto2.height
                                hoverEnabled: true
                                onClicked: {

                                    codigoDePaisSeleccionado=_codigoDePaisSeleccionado
                                    codigoDeDepartamentoSeleccionado=codigoDepartamento
                                    listview1.forceActiveFocus()
                                    rectPrincipalComboBox.visible=false
                                    txtTextoSeleccionado.text=descripcionDepartamento
                                    txtTextoSeleccionado.enabled=true
                                    codigoValorSeleccion=codigoDepartamento
                                    cerrarComboBox()
                                    senialAlAceptarOClick()

                                }

                                onEntered: {

                                    opacityOff1.stop()
                                    opacityIn1.start()
                                    texto2.color="white"
                                    texto2.style= Text.Normal
                                    texto2.font.bold= true

                                }
                                onExited:{
                                    opacityIn1.stop()
                                    opacityOff1.start()
                                    texto2.color="#212121"
                                    texto2.style= Text.Raised
                                    texto2.font.bold= false

                                }
                            }
                        }
                    }
                }
                model: modeloDepartamentosComboBox
                z: 1
                focus: true
                anchors.leftMargin: 0              
            }

            BotonBarraDeHerramientas {
                id: botonCerrarLista1
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
                    rectPrincipalSubMenu.visible=false
                    listview1.forceActiveFocus()
                }
            }

            Rectangle {
                id: rectLineaSuperior1
                y: 5
                height: 2
                color: "#201c1c"
                radius: 1
                //
                anchors.bottom: parent.bottom
                visible: true
                anchors.rightMargin: 1
                anchors.bottomMargin: 0
                z: 3
                anchors.right: parent.right
                anchors.leftMargin: 1
                anchors.left: parent.left
            }

            Text {
                id: txtItemsCb1
                x: 5
                y: 10
                text: qsTr("Items:")
                //
                font.pixelSize: 9
                anchors.top: parent.top
                anchors.topMargin: 10
                visible: false
                font.family: "Arial"
                font.bold: false
                z: 2
                anchors.leftMargin: 60
                anchors.left: parent.left
            }
        }

    }

}
