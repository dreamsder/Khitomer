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
    id: rectPrincipalLocalidades
    width: 900
    height: 600
    color: "#00000000"
    smooth: true

    Text {
        id: txtTituloMenuOpcion
        x: 560
        color: "#4d5595"
        text: qsTr("mantenimiento de localidades")
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

    Flow {
        id: flowDepartamento
        x: 30
        y: 101
        width: 340
        spacing: 5
        height: flowDepartamento.implicitHeight
        z: 1
        flow: Flow.LeftToRight
        anchors.top: parent.top
        anchors.topMargin: 300
        anchors.leftMargin: 10
        anchors.left: parent.left

        TextInputSimple {
            id: txtCodigoDepartamento
          //  width: 150
            colorDeTitulo: "#333333"
            textoInputBox: ""
            botonBuscarTextoVisible: false
            inputMask: "000000;"
            largoMaximo: 6
            botonBorrarTextoVisible: true
            textoTitulo: "Código departamento:"

            onEnter: txtNombreDepartamento.tomarElFoco()

            onTabulacion: txtNombreDepartamento.tomarElFoco()
        }

        TextInputSimple {
            id: txtNombreDepartamento
          //  width: 180
            colorDeTitulo: "#333333"
            botonBorrarTextoVisible: true
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            largoMaximo: 20
            textoTitulo: "Nombre departamento:"

            onEnter: txtCodigoDepartamento.tomarElFoco()

            onTabulacion: txtCodigoDepartamento.tomarElFoco()
        }

        ComboBoxListaPaises {
            id: cbxListaPaises
            width: 150
            colorRectangulo: "#cac1bd"
            colorTitulo: "#333333"
            textoTitulo: "País:"
            textoComboBox: modeloPaisesComboBox.retornaDescripcionPais("1")
            codigoValorSeleccion: "1"
        }

    }

    Row {
        id: rowBarraDeHerramientasDepartamentos
        x: 30
        y: 55
        height: 30
        z: 2
        smooth: true
        spacing: 15
        BotonBarraDeHerramientas {
            id: botonNuevoDepartamento
            x: 33
            y: 10
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Departamentos.png"
            toolTip: "Nuevo Departamento"
            anchors.verticalCenter: parent.verticalCenter
            z: 8

            onClic: {

                txtCodigoDepartamento.textoInputBox=modeloDepartamentos.retornaUltimoCodigoDepartamento(cbxListaPaises.codigoValorSeleccion)
                txtNombreDepartamento.textoInputBox=""
                txtNombreDepartamento.tomarElFoco()

            }
        }

        BotonBarraDeHerramientas {
            id: botonGuardarDepartamento
            x: 61
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            toolTip: "Gurardar Departamento"
            anchors.verticalCenter: parent.verticalCenter
            z: 7

            onClic: {

                txtMensajeInformacionDepartamentos.visible=true
                txtMensajeInformacionTimerDepartamento.stop()
                txtMensajeInformacionTimerDepartamento.start()

                var resultadoConsulta = modeloDepartamentos.insertarDepartamento(txtCodigoDepartamento.textoInputBox.trim(),txtNombreDepartamento.textoInputBox.trim(),cbxListaPaises.codigoValorSeleccion.trim())

                if(resultadoConsulta==1){

                    txtMensajeInformacionDepartamentos.color="#2f71a0"
                    txtMensajeInformacionDepartamentos.text="Departamento "+ txtCodigoDepartamento.textoInputBox+" dado de alta ok"

                    modeloDepartamentos.limpiarListaDepartamentos()
                    modeloDepartamentos.buscarDepartamentos("4=","1")
                    listaDeDepartamentos.currentIndex=0;

                    txtCodigoDepartamento.textoInputBox=""
                    txtNombreDepartamento.textoInputBox=""
                    txtCodigoDepartamento.tomarElFoco()

                }else if(resultadoConsulta==2){
                    txtMensajeInformacionDepartamentos.color="#2f71a0"
                    txtMensajeInformacionDepartamentos.text="Departamento "+ txtCodigoDepartamento.textoInputBox+" actualizado."

                    modeloDepartamentos.limpiarListaDepartamentos()
                    modeloDepartamentos.buscarDepartamentos("4=","1")
                    listaDeDepartamentos.currentIndex=0;

                    txtCodigoDepartamento.textoInputBox=""
                    txtNombreDepartamento.textoInputBox=""
                    txtCodigoDepartamento.tomarElFoco()

                }else if(resultadoConsulta==-1){
                    txtMensajeInformacionDepartamentos.color="#d93e3e"
                    txtMensajeInformacionDepartamentos.text="No se pudo conectar a la base de datos"


                }else if(resultadoConsulta==-2){
                    txtMensajeInformacionDepartamentos.color="#d93e3e"
                    txtMensajeInformacionDepartamentos.text="No se pudo actualizar la información del departamento"


                }else if(resultadoConsulta==-3){
                    txtMensajeInformacionDepartamentos.color="#d93e3e"
                    txtMensajeInformacionDepartamentos.text="No se pudo dar de alta el departamento"


                }else if(resultadoConsulta==-4){
                    txtMensajeInformacionDepartamentos.color="#d93e3e"
                    txtMensajeInformacionDepartamentos.text="No se pudo realizar la consulta a la base de datos"


                }else if(resultadoConsulta==-5){
                    txtMensajeInformacionDepartamentos.color="#d93e3e"
                    txtMensajeInformacionDepartamentos.text="Faltan datos para guardar el departamento"

                }
            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarDepartamento
            x: 54
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            toolTip: "Eliminar Departamento"
            anchors.verticalCenter: parent.verticalCenter
            z: 6
            onClic: {


                if(txtCodigoDepartamento.textoInputBox.trim()!="")
                    if(funcionesmysql.mensajeAdvertencia("Realmente desea eliminar el departamento "+txtCodigoDepartamento.textoInputBox.trim()+"?\n\nPresione [ Sí ] para confirmar.")){

                        txtMensajeInformacionDepartamentos.visible=true
                        txtMensajeInformacionTimerDepartamento.stop()
                        txtMensajeInformacionTimerDepartamento.start()

                        if(modeloDepartamentos.eliminarDepartamento(txtCodigoDepartamento.textoInputBox.trim(),cbxListaPaises.codigoValorSeleccion.trim())){

                            txtMensajeInformacionDepartamentos.color="#2f71a0"
                            txtMensajeInformacionDepartamentos.text="Departamento "+txtCodigoDepartamento.textoInputBox.trim()+" eliminado."

                            modeloDepartamentos.limpiarListaDepartamentos()
                            modeloDepartamentos.buscarDepartamentos("4=","1")
                            listaDeDepartamentos.currentIndex=0;

                            txtCodigoDepartamento.textoInputBox=""
                            txtNombreDepartamento.textoInputBox=""
                            txtCodigoDepartamento.tomarElFoco()

                        }else{

                            txtMensajeInformacionDepartamentos.color="#d93e3e"
                            txtMensajeInformacionDepartamentos.text="No se puede eliminar el Departamento."

                        }}
            }
        }

        BotonBarraDeHerramientas {
            id: botonListarTodosLosDepartamentos
            x: 47
            y: 10
            toolTip: "Listar todos los Departamentos"
            z: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            anchors.verticalCenter: parent.verticalCenter

            onClic: {

                modeloDepartamentos.limpiarListaDepartamentos()
                modeloDepartamentos.buscarDepartamentos("1=","1")
                listaDeDepartamentos.currentIndex=0;
            }
        }

        Text {
            id: txtMensajeInformacionDepartamentos
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            smooth: true
            font.pixelSize: 15
            style: Text.Raised
            visible: false
            styleColor: "#ffffff"
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignTop
        }
        anchors.bottom: flowDepartamento.top
        anchors.bottomMargin: 15
        anchors.leftMargin: 10
        anchors.left: parent.left
    }

    Rectangle {
        id: rectLineaVerticalMenuGris
        height: 1
        color: "#abb2b1"
        smooth: true
        anchors.top: rowBarraDeHerramientasDepartamentos.bottom
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
        anchors.top: rowBarraDeHerramientasDepartamentos.bottom
        anchors.topMargin: 4
        anchors.rightMargin: 0
        visible: true
        rotation: 0
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    Rectangle {
        id: rectListaDeDepartamentos
        width: 350
        color: "#C4C4C6"
        radius: 3
        clip: true
        anchors.top: flowDepartamento.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 0
        smooth: true
        ListView {
            id: listaDeDepartamentos
            clip: true
            highlightRangeMode: ListView.NoHighlightRange
            anchors.top: parent.top
            boundsBehavior: Flickable.DragAndOvershootBounds
            highlightFollowsCurrentItem: true
            anchors.right: parent.right
            delegate: ListaDepartamentos{}
            snapMode: ListView.NoSnap
            anchors.bottomMargin: 25
            spacing: 1
            anchors.bottom: parent.bottom
            flickableDirection: Flickable.VerticalFlick
            anchors.leftMargin: 1
            keyNavigationWraps: true
            anchors.left: parent.left
            interactive: true
            smooth: true
            anchors.topMargin: 25
            anchors.rightMargin: 1
            model: modeloDepartamentos

            Rectangle {
                id: rectangle3
                y: listaDeDepartamentos.visibleArea.yPosition * listaDeDepartamentos.height+5
                width: 10
                color: "#000000"
                height: listaDeDepartamentos.visibleArea.heightRatio * listaDeDepartamentos.height+18
                radius: 2
                anchors.right: listaDeDepartamentos.right
                anchors.rightMargin: 4
                z: 1
                opacity: 0.500
                visible: true
                smooth: true
            }
        }

        Text {
            id: txtTituloListaDepartamentos
            color: "#333333"
            text: "Departamentos: "+listaDeDepartamentos.count
            font.family: "Arial"
            anchors.top: parent.top
            anchors.topMargin: 5
            font.bold: true
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

            onClic: listaDeDepartamentos.positionViewAtIndex(listaDeDepartamentos.count-1,0)

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


            onClic: listaDeDepartamentos.positionViewAtIndex(0,0)


        }
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }


    Timer{
        id:txtMensajeInformacionTimerLocalidad
        repeat: false
        interval: 5000
        onTriggered: {

            txtMensajeInformacionLocalidad.visible=false
            txtMensajeInformacionLocalidad.color="#d93e3e"
        }
    }
    Timer{
        id:txtMensajeInformacionTimerPais
        repeat: false
        interval: 5000
        onTriggered: {

            txtMensajeInformacionPais.visible=false
            txtMensajeInformacionPais.color="#d93e3e"
        }
    }
    Timer{
        id:txtMensajeInformacionTimerDepartamento
        repeat: false
        interval: 5000
        onTriggered: {

            txtMensajeInformacionDepartamentos.visible=false
            txtMensajeInformacionDepartamentos.color="#d93e3e"
        }
    }

    Row {
        id: rowBarraDeHerramientasLocalidades
        x: 36
        y: 51
        height: 30
        anchors.right: parent.right
        anchors.rightMargin: 10
        smooth: true
        spacing: 15
        BotonBarraDeHerramientas {
            id: botonNuevaLocalidad
            x: 33
            y: 10
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Localidades.png"
            toolTip: "Nueva Localidad"
            anchors.verticalCenter: parent.verticalCenter
            z: 8
            onClic: {
                txtCodigoLocalidad.textoInputBox=modeloLocalidades.retornaUltimoCodigoLocalidad(cbxListaDepartamentos.codigoDePaisSeleccionado.trim(),cbxListaDepartamentos.codigoDeDepartamentoSeleccionado.trim())
                txtNombreLocalidad.textoInputBox=""
                txtNombreLocalidad.tomarElFoco()
            }
        }

        BotonBarraDeHerramientas {
            id: botonGuardarLocalidad
            x: 61
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            toolTip: "Gurardar Localidad"
            anchors.verticalCenter: parent.verticalCenter
            z: 7
            onClic: {

                txtMensajeInformacionLocalidad.visible=true
                txtMensajeInformacionTimerLocalidad.stop()
                txtMensajeInformacionTimerLocalidad.start()

                var resultadoConsulta = modeloLocalidades.insertarLocalidad(txtCodigoLocalidad.textoInputBox.trim(),txtNombreLocalidad.textoInputBox.trim(),cbxListaDepartamentos.codigoDeDepartamentoSeleccionado.trim(),cbxListaDepartamentos.codigoDePaisSeleccionado.trim())

                if(resultadoConsulta==1){

                    txtMensajeInformacionLocalidad.color="#2f71a0"
                    txtMensajeInformacionLocalidad.text="Localidad "+ txtCodigoLocalidad.textoInputBox+" dada de alta ok"

                    listaDeLocalidades.currentIndex=0;

                    txtCodigoLocalidad.textoInputBox=""
                    txtNombreLocalidad.textoInputBox=""
                    txtCodigoLocalidad.tomarElFoco()

                }else if(resultadoConsulta==2){
                    txtMensajeInformacionLocalidad.color="#2f71a0"
                    txtMensajeInformacionLocalidad.text="Localidad "+ txtCodigoLocalidad.textoInputBox+" actualizada."

                    listaDeLocalidades.currentIndex=0;

                    txtCodigoLocalidad.textoInputBox=""
                    txtNombreLocalidad.textoInputBox=""
                    txtCodigoLocalidad.tomarElFoco()

                }else if(resultadoConsulta==-1){
                    txtMensajeInformacionLocalidad.color="#d93e3e"
                    txtMensajeInformacionLocalidad.text="No se pudo conectar a la base de datos"


                }else if(resultadoConsulta==-2){
                    txtMensajeInformacionLocalidad.color="#d93e3e"
                    txtMensajeInformacionLocalidad.text="Error en actualización de localidad"


                }else if(resultadoConsulta==-3){
                    txtMensajeInformacionLocalidad.color="#d93e3e"
                    txtMensajeInformacionLocalidad.text="Error en alta de localidad"


                }else if(resultadoConsulta==-4){
                    txtMensajeInformacionLocalidad.color="#d93e3e"
                    txtMensajeInformacionLocalidad.text="Error en consulta a la base de datos"


                }else if(resultadoConsulta==-5){
                    txtMensajeInformacionLocalidad.color="#d93e3e"
                    txtMensajeInformacionLocalidad.text="Faltan datos para guardar localidad"

                }
            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarLocalidad
            x: 54
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            toolTip: "Eliminar Localidad"
            anchors.verticalCenter: parent.verticalCenter
            z: 6
            onClic: {

                if(txtCodigoLocalidad.textoInputBox.trim()!="")
                    if(funcionesmysql.mensajeAdvertencia("Realmente desea eliminar la localidad "+txtCodigoLocalidad.textoInputBox.trim()+"?\n\nPresione [ Sí ] para confirmar.")){

                        txtMensajeInformacionLocalidad.visible=true
                        txtMensajeInformacionTimerLocalidad.stop()
                        txtMensajeInformacionTimerLocalidad.start()

                        if(modeloLocalidades.eliminarLocalidad(txtCodigoLocalidad.textoInputBox.trim(),cbxListaDepartamentos.codigoDeDepartamentoSeleccionado.trim(),cbxListaDepartamentos.codigoDePaisSeleccionado.trim())){

                            txtMensajeInformacionLocalidad.color="#2f71a0"
                            txtMensajeInformacionLocalidad.text="Localidad "+txtCodigoLocalidad.textoInputBox.trim()+" eliminada"

                            listaDeLocalidades.currentIndex=0;

                            txtCodigoLocalidad.textoInputBox=""
                            txtNombreLocalidad.textoInputBox=""
                            txtCodigoLocalidad.tomarElFoco()

                        }else{
                            txtMensajeInformacionLocalidad.color="#d93e3e"
                            txtMensajeInformacionLocalidad.text="No se puede eliminar la localidad"
                        }}
            }
        }

        BotonBarraDeHerramientas {
            id: botonListarTodasLasLocalidades
            x: 47
            y: 10
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            toolTip: "Listar todas las localidades"
            anchors.verticalCenter: parent.verticalCenter
            z: 5
            onClic: {

                modeloLocalidades.limpiarListaLocalidades()
                modeloLocalidades.buscarLocalidades("1=","1")
            }
        }

        Text {
            id: txtMensajeInformacionLocalidad
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            smooth: true
            font.pixelSize: 15
            style: Text.Raised
            visible: false
            styleColor: "#ffffff"
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignTop
        }
        anchors.bottom: flowDepartamento.top
        anchors.bottomMargin: 15
        anchors.leftMargin: 40
        anchors.left: rectListaDeDepartamentos.right
    }

    Flow {
        id: flowLocalidades
        x: 22
        y: 93
        height: flowLocalidades.implicitHeight
        anchors.right: parent.right
        anchors.rightMargin: 0
        spacing: 5
        flow: Flow.LeftToRight
        anchors.top: parent.top
        anchors.topMargin: 300
        TextInputSimple {
            id: txtCodigoLocalidad
         //   width: 130
            textoInputBox: ""
            botonBuscarTextoVisible: false
            inputMask: "000000;"
            largoMaximo: 6
            botonBorrarTextoVisible: true
            textoTitulo: "Código localidad:"
            colorDeTitulo: "#333333"
            onTabulacion: txtNombreLocalidad.tomarElFoco()
            onEnter: txtNombreLocalidad.tomarElFoco()
        }

        TextInputSimple {
            id: txtNombreLocalidad
          //  width: 190
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            botonBorrarTextoVisible: true
            largoMaximo: 35
            textoTitulo: "Nombre localidad:"
            colorDeTitulo: "#333333"
            onTabulacion: cbxListaRubrosMantenimiento.tomarElFoco()
            onEnter: cbxListaRubrosMantenimiento.tomarElFoco()
        }

        ComboBoxListaDepartamentos {
            id: cbxListaDepartamentos
            width: 180
            colorRectangulo: "#cac1bd"
            colorTitulo: "#333333"
            textoTitulo: "Departamentos:"
            orientacionSubMenu: false
            codigoDePaisSeleccionado: "1"
            codigoDeDepartamentoSeleccionado: "1"
            codigoValorSeleccion: "1"
            textoComboBox: modeloDepartamentos.retornaDescripcionDepartamento("1","1")
        }
        z: 1
        anchors.leftMargin: 40
        anchors.left: rectListaDeDepartamentos.right
    }

    Rectangle {
        id: rectListaDeLocalidades
        x: 2
        y: -9
        color: "#c4c4c6"
        radius: 3
        clip: true
        anchors.right: parent.right
        anchors.rightMargin: 0
        smooth: true
        anchors.top: flowLocalidades.bottom
        anchors.topMargin: 10
        ListView {
            id: listaDeLocalidades
            highlightRangeMode: ListView.NoHighlightRange
            anchors.top: parent.top
            boundsBehavior: Flickable.DragAndOvershootBounds
            highlightFollowsCurrentItem: true
            anchors.right: parent.right
            delegate: ListaLocalidades {
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
            smooth: true
            anchors.topMargin: 25
            anchors.rightMargin: 1
            model: modeloLocalidades

            Rectangle {
                id: rectangle4
                y: listaDeLocalidades.visibleArea.yPosition * listaDeLocalidades.height+5
                width: 10
                color: "#000000"
                height: listaDeLocalidades.visibleArea.heightRatio * listaDeLocalidades.height+18
                radius: 2
                anchors.right: listaDeLocalidades.right
                anchors.rightMargin: 4
                z: 1
                opacity: 0.500
                visible: true
                smooth: true
            }
        }

        Text {
            id: txtTituloListaLocalidades
            color: "#333333"
            text: "Localidades: "+listaDeLocalidades.count
            font.family: "Arial"
            anchors.top: parent.top
            anchors.topMargin: 5
            font.bold: true
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

            onClic: listaDeLocalidades.positionViewAtIndex(listaDeLocalidades.count-1,0)

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

            onClic: listaDeLocalidades.positionViewAtIndex(0,0)

        }
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.leftMargin: 30
        anchors.left: rectListaDeDepartamentos.right
    }

    Rectangle {
        id: rectListaDePaises
        x: -9
        y: -1
        color: "#c4c4c6"
        radius: 3
        anchors.right: parent.right
        anchors.rightMargin: 0
        clip: true
        smooth: true
        anchors.top: flowPais.bottom
        anchors.topMargin: 10
        ListView {
            id: listaDePaises
            highlightRangeMode: ListView.NoHighlightRange
            anchors.top: parent.top
            boundsBehavior: Flickable.DragAndOvershootBounds
            highlightFollowsCurrentItem: true
            anchors.right: parent.right
            delegate: ListaPaises {
            }
            snapMode: ListView.NoSnap
            anchors.bottomMargin: 25
            spacing: 1
            anchors.bottom: parent.bottom
            clip: true
            flickableDirection: Flickable.VerticalFlick
            anchors.leftMargin: 1
            Rectangle {
                id: rectangle5
                y: listaDePaises.visibleArea.yPosition * listaDePaises.height+5
                width: 10
                height: listaDePaises.visibleArea.heightRatio * listaDePaises.height+18
                color: "#000000"
                radius: 2
                smooth: true
                anchors.rightMargin: 4
                visible: true
                z: 1
                anchors.right: listaDePaises.right
                opacity: 0.500
            }
            keyNavigationWraps: true
            anchors.left: parent.left
            interactive: true
            smooth: true
            anchors.topMargin: 25
            anchors.rightMargin: 1
            model: modeloPaises
        }

        Text {
            id: txtTituloListaPaises
            color: "#333333"
            text: "Paises: "+listaDePaises.count
            anchors.top: parent.top
            anchors.topMargin: 5
            font.family: "Arial"
            font.bold: true
            font.pointSize: 10
            anchors.leftMargin: 5
            anchors.left: parent.left
        }

        BotonBarraDeHerramientas {
            id: botonBajarListaFinal3
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
            onClic: listaDePaises.positionViewAtIndex(listaDePaises.count-1,0)
        }

        BotonBarraDeHerramientas {
            id: botonSubirListaFinal3
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

            onClic: listaDePaises.positionViewAtIndex(0,0)
        }
        anchors.bottom: rectLineaVerticalMenuGris.top
        anchors.bottomMargin: 50
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    Flow {
        id: flowPais
        x: 34
        y: 98
        height: flowPais.implicitHeight
        anchors.right: parent.right
        anchors.rightMargin: 0
        spacing: 5
        flow: Flow.LeftToRight
        anchors.top: parent.top
        anchors.topMargin: 70

        z: 1
        anchors.leftMargin: 10
        anchors.left: parent.left
        TextInputSimple {
            id: txtCodigoPais
          //  width: 105
            textoInputBox: ""
            botonBuscarTextoVisible: false
            inputMask: "000000;"
            largoMaximo: 6
            botonBorrarTextoVisible: true
            textoTitulo: "Código pais:"
            colorDeTitulo: "#333333"

            onEnter: txtNombrePais.tomarElFoco()

            onTabulacion: txtNombrePais.tomarElFoco()
        }
        TextInputSimple {
            id: txtNombrePais
          //  width: 200
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            botonBorrarTextoVisible: true
            largoMaximo: 35
            textoTitulo: "Nombre pais:"
            colorDeTitulo: "#333333"
            onEnter: txtCodigoPais.tomarElFoco()

            onTabulacion: txtCodigoPais.tomarElFoco()
        }
    }

    Row {
        id: rowBarraDeHerramientasPais
        x: 25
        y: 64
        height: 30
        anchors.right: parent.right
        anchors.rightMargin: 10
        smooth: true
        spacing: 15
        BotonBarraDeHerramientas {
            id: botonNuevoPais
            x: 33
            y: 10
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Paises.png"
            toolTip: "Nuevo Pais"
            anchors.verticalCenter: parent.verticalCenter
            z: 8
            onClic: {

                txtCodigoPais.textoInputBox=modeloPaises.retornaUltimoCodigoPais()
                txtNombrePais.textoInputBox=""
                txtNombrePais.tomarElFoco()

            }
        }

        BotonBarraDeHerramientas {
            id: botonGuardarPais
            x: 61
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            toolTip: "Gurardar Pais"
            anchors.verticalCenter: parent.verticalCenter
            z: 7
            onClic: {

                txtMensajeInformacionPais.visible=true
                txtMensajeInformacionTimerPais.stop()
                txtMensajeInformacionTimerPais.start()

                var resultadoConsulta = modeloPaises.insertarPais(txtCodigoPais.textoInputBox,txtNombrePais.textoInputBox)

                if(resultadoConsulta==1){

                    txtMensajeInformacionPais.color="#2f71a0"
                    txtMensajeInformacionPais.text="Pais "+ txtCodigoPais.textoInputBox+" dado de alta ok"

                    modeloPaises.limpiarListaPaises()
                    modeloPaises.buscarPaises("1=","1","")
                    listaDePaises.currentIndex=0;

                    txtCodigoPais.textoInputBox=""
                    txtNombrePais.textoInputBox=""
                    txtCodigoPais.tomarElFoco()

                    modeloPaisesComboBox.limpiarListaPaises()
                    modeloPaisesComboBox.buscarPaises("1=","1","descripcionPais")

                }else if(resultadoConsulta==2){
                    txtMensajeInformacionPais.color="#2f71a0"
                    txtMensajeInformacionPais.text="Pais "+ txtCodigoPais.textoInputBox+" actualizado."

                    modeloPaises.limpiarListaPaises()
                    modeloPaises.buscarPaises("1=","1","")
                    listaDePaises.currentIndex=0;

                    txtCodigoPais.textoInputBox=""
                    txtNombrePais.textoInputBox=""
                    txtCodigoPais.tomarElFoco()

                    modeloPaisesComboBox.limpiarListaPaises()
                    modeloPaisesComboBox.buscarPaises("1=","1","descripcionPais")

                }else if(resultadoConsulta==-1){
                    txtMensajeInformacionPais.color="#d93e3e"
                    txtMensajeInformacionPais.text="No se pudo conectar a la base de datos"


                }else if(resultadoConsulta==-2){
                    txtMensajeInformacionPais.color="#d93e3e"
                    txtMensajeInformacionPais.text="No se pudo actualizar la información del pais"


                }else if(resultadoConsulta==-3){
                    txtMensajeInformacionPais.color="#d93e3e"
                    txtMensajeInformacionPais.text="No se pudo dar de alta el pais"


                }else if(resultadoConsulta==-4){
                    txtMensajeInformacionPais.color="#d93e3e"
                    txtMensajeInformacionPais.text="No se pudo realizar la consulta a la base de datos"


                }else if(resultadoConsulta==-5){
                    txtMensajeInformacionPais.color="#d93e3e"
                    txtMensajeInformacionPais.text="Faltan datos para guardar el pais"

                }


            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarPais
            x: 54
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            toolTip: "Eliminar Pais"
            anchors.verticalCenter: parent.verticalCenter
            z: 6

            onClic: {
                if(txtCodigoPais.textoInputBox.trim()!="")
                    if(funcionesmysql.mensajeAdvertencia("Realmente desea eliminar el pais "+txtCodigoPais.textoInputBox.trim()+"?\n\nPresione [ Sí ] para confirmar.")){

                        txtMensajeInformacionPais.visible=true
                        txtMensajeInformacionTimerPais.stop()
                        txtMensajeInformacionTimerPais.start()

                        if(modeloPaises.eliminarPais(txtCodigoPais.textoInputBox.trim())){
                            txtMensajeInformacionPais.color="#2f71a0"
                            txtMensajeInformacionPais.text="Pais "+txtCodigoPais.textoInputBox.trim()+" eliminado correctamente"

                            modeloPaisesComboBox.limpiarListaPaises()
                            modeloPaisesComboBox.buscarPaises("1=","1","descripcionPais")
                            modeloPaises.limpiarListaPaises()
                            modeloPaises.buscarPaises("1=","1","")
                            listaDePaises.currentIndex=0;

                            txtCodigoPais.textoInputBox=""
                            txtNombrePais.textoInputBox=""
                            txtCodigoPais.tomarElFoco()
                        }else{
                            txtMensajeInformacionPais.color="#d93e3e"
                            txtMensajeInformacionPais.text="ATENCION: No se puede eliminar el pais, verifique la información."
                            txtNombrePais.tomarElFoco()
                        }
                    }
            }

        }

        BotonBarraDeHerramientas {
            id: botonListarTodosLosPaises
            x: 47
            y: 10
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            toolTip: "Listar todos los Paises"
            anchors.verticalCenter: parent.verticalCenter
            z: 5
            onClic: {
                modeloPaises.limpiarListaPaises()
                modeloPaises.buscarPaises("1=","1","")
                listaDePaises.currentIndex=0
            }
        }

        Text {
            id: txtMensajeInformacionPais
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            smooth: true
            font.pixelSize: 15
            style: Text.Raised
            visible: false
            styleColor: "#ffffff"
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignTop
        }
        anchors.bottom: flowPais.top
        anchors.bottomMargin: 15
        z: 2
        anchors.leftMargin: 10
        anchors.left: parent.left
    }

    Rectangle {
        id: rectLineaVerticalMenuGris1
        x: -4
        y: -4
        height: 1
        color: "#abb2b1"
        smooth: true
        anchors.top: rowBarraDeHerramientasPais.bottom
        anchors.topMargin: 5
        anchors.rightMargin: 0
        visible: true
        rotation: 0
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    Rectangle {
        id: rectLineaVerticalMenuBlanco1
        x: -11
        y: -4
        height: 1
        color: "#ffffff"
        smooth: true
        anchors.top: rowBarraDeHerramientasPais.bottom
        anchors.topMargin: 4
        anchors.rightMargin: 0
        visible: true
        rotation: 0
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

}
