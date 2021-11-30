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
import "../Listas"

Item {
    id: itemBotonLateralBusquedas
    width: 40
    height: 40

    onZChanged: {

        if(itemBotonLateralBusquedas.z==0){
            rectPrincipalAparecerXIn.stop()
            rectPrincipalBusqueda.visible=false
        }
    }


    signal clic
    property double opacidad:0.7
    property alias rectanguloSecundarioVisible: rectColorSecundario.visible
    property alias rectPrincipalVisible: rectPrincipalBusqueda.visible

    property alias source: imagenIcono.source
    property alias toolTip: toolTipText.text

    Image {
        id: imagenIcono
        opacity: opacidad
        smooth: true
        asynchronous: true
        anchors.fill: parent
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Buscar48x48.png"


        Rectangle{
            id:rectColorSecundario
            anchors.fill: parent
            opacity: 0.15
            color: "red"
            //
            anchors.rightMargin: 2
            anchors.leftMargin: 2
            anchors.bottomMargin: 2
            anchors.topMargin: 2
            visible: false
        }

        MouseArea {
            id: mouse_areaItemBotonLateralBusquedas
            hoverEnabled: true
            anchors.fill: parent

            onClicked: {

                clic()

                if(rectPrincipalBusqueda.visible==false){
                    rectPrincipalBusqueda.visible=true
                    rectPrincipalAparecerXIn.start();
                    if(!btnBusquedaInteligente.estaPrecionado && !btnBusquedaArticulos.estaPrecionado && !btnBusquedaClientes.estaPrecionado && !btnBusquedaProveedores.estaPrecionado)
                        btnBusquedaInteligente.setearEstadoBoton()

                    txtBusquedaInteligente.tomarElFoco()

                }else if(rectPrincipalBusqueda.visible){

                    rectPrincipalBusqueda.visible=false

                }

            }


            onEntered: {

                timer1.start()
                imagenIconoOpacidadOut.stop()
                imagenIconoOpacidadIn.start()
            }

            onExited: {

                timer1.stop()
                rectToolTipTextBarraHerramientas.visible=false
                imagenIconoOpacidadIn.stop()
                imagenIconoOpacidadOut.start()
            }


            onPressed: {
                timer1.stop()
                rectToolTipTextBarraHerramientas.visible=false
                imagenIconoScaleOut.stop()
                imagenIconoScaleIn.start()

            }
            onReleased: {
                timer1.start()
                imagenIconoScaleIn.stop()
                imagenIconoScaleOut.start()

            }
        }
    }



    PropertyAnimation{
        id:imagenIconoOpacidadIn
        target: imagenIcono
        property: "opacity"
        from:opacidad
        to:1
        duration: 100
    }

    PropertyAnimation{
        id:imagenIconoOpacidadOut
        target: imagenIcono
        property: "opacity"
        to:opacidad
        from:1
        duration: 100
    }

    PropertyAnimation{
        id:imagenIconoScaleIn
        target: itemBotonLateralBusquedas
        property: "scale"
        from:1
        to:0.90
        duration: 50
    }
    PropertyAnimation{
        id:imagenIconoScaleOut
        target: itemBotonLateralBusquedas
        property: "scale"
        from:0.90
        to:1
        duration: 50
    }

    Rectangle{
        id:rectToolTipTextBarraHerramientas
        visible: false
        width: toolTipText.implicitWidth+20
        height: toolTipText.implicitHeight
        color: "#4d7dc0"
        radius: 6
        opacity: 1
        z: 3
        //
        Text {
            id: toolTipText
            color: "#fdfbfb"
            font.family: "Arial"
            font.bold: false
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.fill: parent
            //
            visible: true
        }

    }
    Timer {
        id:timer1
        interval: 1500;
        running: false;
        repeat: false;
        onTriggered: {
            if(toolTipText.text!=""){
                rectToolTipTextBarraHerramientas.x=itemBotonLateralBusquedas.width+10
                rectToolTipTextBarraHerramientas.y=itemBotonLateralBusquedas.height/4
                rectToolTipTextBarraHerramientas.visible=true
            }
        }


    }

    Rectangle {
        id: rectPrincipalBusqueda
        x: 39
        width: 900
        height: 550
        color: "#eceeee"
        radius: 6
        clip: true
        anchors.top: parent.top
        anchors.topMargin: -6
        //
        border.color: "#a8a0a0"



        MouseArea {
            id: mouse_area2
            visible: true
            clip: false
            anchors.fill: parent

            BotonBarraDeHerramientas {
                id: botonCerrarLista
                x: 922
                y: 10
                width: 18
                height: 18
                //
                anchors.top: parent.top
                anchors.topMargin: 10
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/CerrarLista.png"
                visible: true
                anchors.rightMargin: 10
                z: 2
                anchors.right: parent.right
                onClic: itemBotonLateralBusquedas.z=0
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

            Rectangle {
                id: rectangle1
                x: -69
                y: 51
                width: 270
                height: 53
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#4d4b86"
                    }

                    GradientStop {
                        position: 1
                        color: "#4d4b86"
                    }
                }
                anchors.top: parent.top
                anchors.topMargin: 51
                rotation: -50
                clip: false
                smooth: true
                visible: true

                Text {
                    id: lblBusquedaInteligenteDeKhitomer
                    x: 98
                    y: 19
                    width: 178
                    height: 38
                    color: "#fbfbfb"
                    text: qsTr("Busqueda inteligente de Khitomer")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap
                    styleColor: "#2e4186"
                    style: Text.Sunken
                    font.family: "Arial"
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    visible: true
                    smooth: true
                    font.pixelSize: 14
                }
            }

            TextInputSimple {
                id: txtBusquedaInteligente
                height: 42
                colorDeTitulo: "#333333"
                margenIzquierdo: (txtBusquedaInteligente.width-tituloImpricitWidth)/2
                textoInputFontSize: 15
                textoInputBox: ""
                textoTitulo: ""
                opacidadPorDefecto: 0.700
                rectanguloTextoAlto: 25
                anchors.top: parent.top
                anchors.topMargin: 140
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: -14
                textoDeFondo: "introduzca su información a buscar"
                largoMaximo: 100
                enFocoSeleccionarTodo: true
                cursor_Visible: false
                botonBuscarTextoVisible: false
                botonBorrarTextoVisible: true
                visible: true
                onEnter: {
                    if(textoInputBox.trim()!=""){

                        modeloBusquedaInteligenteArticulos.limpiarBusquedaInteligente()
                        modeloBusquedaInteligenteClientes.limpiarBusquedaInteligente()
                        modeloBusquedaInteligenteProveedores.limpiarBusquedaInteligente()


                        modeloBusquedaInteligenteArticulos.buscarArticulosInteligente(textoInputBox.trim(),chbIncluirArticulosInactivos.chekActivo)




                        modeloBusquedaInteligenteClientes.buscarClientesInteligente(textoInputBox.trim())
                        modeloBusquedaInteligenteProveedores.buscarProveedorInteligente(textoInputBox.trim())
                        listaResultadoBusquedaInteligenteArticulos.currentIndex=0
                        listaResultadoBusquedaInteligenteClientes.currentIndex=0
                        listaResultadoBusquedaInteligenteProveedores.currentIndex=0

                        /// Esta precionado el boton de busqueda inteligente
                        if(btnBusquedaInteligente.estaPrecionado){

                            if(modeloBusquedaInteligenteArticulos.rowCount()<=modeloBusquedaInteligenteClientes.rowCount()){
                                if(modeloBusquedaInteligenteClientes.rowCount()<=modeloBusquedaInteligenteProveedores.rowCount()){
                                    ///La lista de proveedores tiene mas registros
                                    listaResultadoBusquedaInteligenteProveedores.model=modeloBusquedaInteligenteProveedores
                                    textoTitulo="Proveedores:"
                                    listaResultadoBusquedaInteligenteArticulos.visible=false
                                    listaResultadoBusquedaInteligenteClientes.visible=false
                                    listaResultadoBusquedaInteligenteProveedores.visible=true

                                }else{
                                    ///La lista de clientes tiene mas registros
                                    listaResultadoBusquedaInteligenteClientes.model=modeloBusquedaInteligenteClientes
                                    textoTitulo="Clientes:"
                                    listaResultadoBusquedaInteligenteArticulos.visible=false
                                    listaResultadoBusquedaInteligenteClientes.visible=true
                                    listaResultadoBusquedaInteligenteProveedores.visible=false
                                }
                            }else{
                                if(modeloBusquedaInteligenteArticulos.rowCount()<=modeloBusquedaInteligenteProveedores.rowCount()){
                                    ///La lista de proveedores tiene mas registros
                                    listaResultadoBusquedaInteligenteProveedores.model=modeloBusquedaInteligenteProveedores
                                    textoTitulo="Proveedores:"
                                    listaResultadoBusquedaInteligenteArticulos.visible=false
                                    listaResultadoBusquedaInteligenteClientes.visible=false
                                    listaResultadoBusquedaInteligenteProveedores.visible=true
                                }else{
                                    ///La lista de articulos tiene mas registros
                                    listaResultadoBusquedaInteligenteArticulos.model=modeloBusquedaInteligenteArticulos
                                    textoTitulo="Artículos:"
                                    listaResultadoBusquedaInteligenteArticulos.visible=true
                                    listaResultadoBusquedaInteligenteClientes.visible=false
                                    listaResultadoBusquedaInteligenteProveedores.visible=false
                                }
                            }


                            /// Esta precionado el boton de articulos
                        }else if(btnBusquedaArticulos.estaPrecionado){
                            listaResultadoBusquedaInteligenteArticulos.model=modeloBusquedaInteligenteArticulos
                            textoTitulo="Artículos:"
                            listaResultadoBusquedaInteligenteArticulos.visible=true
                            listaResultadoBusquedaInteligenteClientes.visible=false
                            listaResultadoBusquedaInteligenteProveedores.visible=false

                            /// Esta precionado el boton de Clientes
                        }else if(btnBusquedaClientes.estaPrecionado){
                            listaResultadoBusquedaInteligenteClientes.model=modeloBusquedaInteligenteClientes
                            textoTitulo="Clientes:"
                            listaResultadoBusquedaInteligenteArticulos.visible=false
                            listaResultadoBusquedaInteligenteClientes.visible=true
                            listaResultadoBusquedaInteligenteProveedores.visible=false

                            /// Esta precionado el boton de proveedores
                        }else if(btnBusquedaProveedores.estaPrecionado){
                            listaResultadoBusquedaInteligenteProveedores.model=modeloBusquedaInteligenteProveedores
                            textoTitulo="Proveedores:"
                            listaResultadoBusquedaInteligenteArticulos.visible=false
                            listaResultadoBusquedaInteligenteClientes.visible=false
                            listaResultadoBusquedaInteligenteProveedores.visible=true
                        }

                    }
                }
            }

            Flow {
                id: flow1
                spacing: 20
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.top: parent.top
                anchors.topMargin: 100
                anchors.left: parent.left
                anchors.leftMargin: 150

                BotonIns {
                    id: btnBusquedaInteligente
                    negrita: false
                    z: 4
                    textoBoton: "Busqueda inteligente"
                    onClicBoton: {
                        txtBusquedaInteligente.textoTitulo=""
                        btnBusquedaArticulos.restaurarBoton()
                        btnBusquedaClientes.restaurarBoton()
                        btnBusquedaProveedores.restaurarBoton()
                        if(!estaPrecionado){
                            btnBusquedaArticulos.setearEstadoBoton()
                        }
                    }
                }

                BotonIns {
                    id: btnBusquedaArticulos
                    textoBoton: "Por artículos"
                    z: 4
                    onClicBoton: {
                        txtBusquedaInteligente.textoTitulo="Artículos:"
                        btnBusquedaInteligente.restaurarBoton()
                        btnBusquedaClientes.restaurarBoton()
                        btnBusquedaProveedores.restaurarBoton()
                        if(!estaPrecionado){

                            btnBusquedaClientes.setearEstadoBoton()
                        }else{
                            listaResultadoBusquedaInteligenteArticulos.model=modeloBusquedaInteligenteArticulos
                            listaResultadoBusquedaInteligenteArticulos.visible=true
                            listaResultadoBusquedaInteligenteClientes.visible=false
                            listaResultadoBusquedaInteligenteProveedores.visible=false
                        }
                    }
                }

                BotonIns {
                    id: btnBusquedaClientes
                    textoBoton: "Por clientes"
                    z: 4
                    onClicBoton: {
                        txtBusquedaInteligente.textoTitulo="Clientes:"
                        btnBusquedaArticulos.restaurarBoton()
                        btnBusquedaInteligente.restaurarBoton()
                        btnBusquedaProveedores.restaurarBoton()
                        if(!estaPrecionado){

                            btnBusquedaProveedores.setearEstadoBoton()
                        }else{
                            listaResultadoBusquedaInteligenteClientes.model=modeloBusquedaInteligenteClientes
                            listaResultadoBusquedaInteligenteArticulos.visible=false
                            listaResultadoBusquedaInteligenteClientes.visible=true
                            listaResultadoBusquedaInteligenteProveedores.visible=false
                        }
                    }
                }

                BotonIns {
                    id: btnBusquedaProveedores
                    textoBoton: "Por proveedores"
                    z: 4
                    onClicBoton: {
                        txtBusquedaInteligente.textoTitulo="Proveedores:"
                        btnBusquedaArticulos.restaurarBoton()
                        btnBusquedaClientes.restaurarBoton()
                        btnBusquedaInteligente.restaurarBoton()
                        if(!estaPrecionado){

                            btnBusquedaClientes.setearEstadoBoton()

                        }else{
                            listaResultadoBusquedaInteligenteProveedores.model=modeloBusquedaInteligenteProveedores
                            listaResultadoBusquedaInteligenteArticulos.visible=false
                            listaResultadoBusquedaInteligenteClientes.visible=false
                            listaResultadoBusquedaInteligenteProveedores.visible=true
                        }
                    }

                }
            }

            TextEdit {
                id: lblInformacionBusquedaInteligente
                x: 360
                y: 10
                width: 654
                text: "Tips: La busqueda inteligente  evaluara los resultados entre artículos, clientes y proveedores, y presentará la información que obtenga mas registros. El resto de busquedas es especifica para artículos, clientes y proveedores. Si se equivoco de filtro de busqueda, alcanza con que precione el filtro correcto, y se cargaran los resultados esperados."
                horizontalAlignment: TextEdit.AlignLeft
                anchors.right: parent.right
                anchors.rightMargin: 40
                //
                anchors.top: parent.top
                anchors.topMargin: 10
                activeFocusOnPress: false
                wrapMode: TextEdit.WordWrap
                readOnly: true
                font.family: "Arial"
                font.bold: false
                font.pointSize: 10
                textFormat: TextEdit.RichText
            }

            ListView {
                id: listaResultadoBusquedaInteligenteArticulos
                visible: false
                cacheBuffer: 500
                z: 4
                highlightRangeMode: ListView.NoHighlightRange
                anchors.top: txtBusquedaInteligente.bottom
                boundsBehavior: Flickable.DragAndOvershootBounds
                highlightFollowsCurrentItem: true
                anchors.right: parent.right
                delegate: ListaBusquedaInteligenteArticulos {
                }
                snapMode: ListView.NoSnap
                anchors.bottomMargin: 15
                spacing: 1
                anchors.bottom: parent.bottom
                clip: true
                flickableDirection: Flickable.VerticalFlick
                anchors.leftMargin: 5
                Rectangle {
                    id: rectangle4
                    y: listaResultadoBusquedaInteligenteArticulos.visibleArea.yPosition * listaResultadoBusquedaInteligenteArticulos.height+5
                    width: 10
                    height: listaResultadoBusquedaInteligenteArticulos.visibleArea.heightRatio * listaResultadoBusquedaInteligenteArticulos.height+18
                    color: "#000000"
                    radius: 2
                    //
                    anchors.rightMargin: 4
                    visible: true
                    z: 1
                    anchors.right: listaResultadoBusquedaInteligenteArticulos.right
                    opacity: 0.500
                }
                keyNavigationWraps: true
                anchors.left: parent.left
                interactive: true
                //
                anchors.topMargin: 40
                anchors.rightMargin: 5
            }

            ListView {
                id: listaResultadoBusquedaInteligenteClientes
                visible: false
                anchors.top: txtBusquedaInteligente.bottom
                boundsBehavior: Flickable.DragAndOvershootBounds
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.leftMargin: 5
                Rectangle {
                    id: rectangle5
                    y: listaResultadoBusquedaInteligenteClientes.visibleArea.yPosition * listaResultadoBusquedaInteligenteClientes.height+5
                    width: 10
                    height: listaResultadoBusquedaInteligenteClientes.visibleArea.heightRatio * listaResultadoBusquedaInteligenteClientes.height+18
                    color: "#000000"
                    radius: 2
                    z: 1
                    //
                    anchors.right: listaResultadoBusquedaInteligenteClientes.right
                    anchors.rightMargin: 4
                    opacity: 0.5
                    visible: true
                }
                anchors.left: parent.left
                z: 4
                anchors.topMargin: 25
                flickableDirection: Flickable.VerticalFlick
                delegate: ListaBusquedaInteligenteClientes {
                }
                spacing: 1
                anchors.rightMargin: 5
                clip: true
                highlightFollowsCurrentItem: true
                highlightRangeMode: ListView.NoHighlightRange
                keyNavigationWraps: true
                interactive: true
                anchors.bottomMargin: 15
                snapMode: ListView.NoSnap
                //
            }

            ListView {
                id: listaResultadoBusquedaInteligenteProveedores
                anchors.top: txtBusquedaInteligente.bottom
                boundsBehavior: Flickable.DragAndOvershootBounds
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.leftMargin: 5
                Rectangle {
                    id: rectangle6
                    y: listaResultadoBusquedaInteligenteProveedores.visibleArea.yPosition * listaResultadoBusquedaInteligenteProveedores.height+5
                    width: 10
                    height: listaResultadoBusquedaInteligenteProveedores.visibleArea.heightRatio * listaResultadoBusquedaInteligenteProveedores.height+18
                    color: "#000000"
                    radius: 2
                    z: 1
                    //
                    anchors.right: listaResultadoBusquedaInteligenteProveedores.right
                    anchors.rightMargin: 4
                    opacity: 0.5
                    visible: true
                }
                anchors.left: parent.left
                z: 4
                anchors.topMargin: 25
                flickableDirection: Flickable.VerticalFlick
                delegate: ListaBusquedaInteligenteProveedores {
                }
                spacing: 1
                anchors.rightMargin: 5
                clip: true
                highlightFollowsCurrentItem: true
                highlightRangeMode: ListView.NoHighlightRange
                keyNavigationWraps: true
                interactive: true
                visible: false
                anchors.bottomMargin: 15
                snapMode: ListView.NoSnap
                //
            }

            CheckBox {
                id: chbIncluirArticulosInactivos
                textoValor: "Incluir artículos inactivos"
                anchors.left: parent.left
                anchors.leftMargin: 150
                anchors.bottom: listaResultadoBusquedaInteligenteArticulos.top
                anchors.bottomMargin: 10
                visible: listaResultadoBusquedaInteligenteArticulos.visible

                onChekActivoChanged: {

                    if(txtBusquedaInteligente.textoInputBox.trim()!=""){

                        modeloBusquedaInteligenteArticulos.limpiarBusquedaInteligente()
                        modeloBusquedaInteligenteArticulos.buscarArticulosInteligente(txtBusquedaInteligente.textoInputBox.trim(),chbIncluirArticulosInactivos.chekActivo)
                        listaResultadoBusquedaInteligenteArticulos.currentIndex=0

                        listaResultadoBusquedaInteligenteArticulos.model=modeloBusquedaInteligenteArticulos
                        listaResultadoBusquedaInteligenteArticulos.visible=true
                        listaResultadoBusquedaInteligenteClientes.visible=false
                        listaResultadoBusquedaInteligenteProveedores.visible=false

                    }
                }
            }
        }
        visible: true
        border.width: 1
        z: 2002
    }

    PropertyAnimation{
        id:rectPrincipalAparecerXIn
        target: rectPrincipalBusqueda
        property: "x"
        from:39
        to: 48
        duration: 200
    }

    Rectangle {
        id: rectangle3
        x: 28
        y: 8
        width: 25
        height: 25
        color: rectPrincipalBusqueda.color
        anchors.right: rectPrincipalBusqueda.left
        anchors.rightMargin: -14
        //
        rotation: 45
        z: 2003
        visible: rectPrincipalBusqueda.visible
    }

}
