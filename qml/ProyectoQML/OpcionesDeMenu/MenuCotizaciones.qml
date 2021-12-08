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
import QtWebKit 1.1
import "../Controles"
import "../Listas"

Rectangle {
    id: rectPrincipalMenuCotizaciones
    width: 900
    height: 700
    color: "#00000000"
    radius: 0
    //

    Text {
        id: txtTituloMenuOpcion
        x: 560
        color: "#4d5595"
        text: qsTr("mantenimiento de monedas")
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
    Rectangle{
        id: rectangle1
        width: 391
        height: 190
        color: "#00000000"
        radius: 7
        anchors.right: parent.right
        anchors.rightMargin: 50
        //
        anchors.top: parent.top
        clip: true
        anchors.topMargin: 30
        WebView {
            id: web_view1
            anchors.topMargin: -280
            anchors.leftMargin: 0
            //anchors.fill: parent
            anchors.top: parent.top
            anchors.left: parent.left
            opacity: 1
            clip: true
            contentsScale: 1
            preferredWidth: 0
            preferredHeight: 0
            //
            visible: true
            url: "https://www.portal.brou.com.uy/web/guest/cotizaciones"
            enabled: false
            reload.enabled: false
            onLoadFailed: {

                txtInformacionProbemaDeCarga.visible=true
                web_view1.reload.visible=false
                web_view1.visible=false
            }
            onLoadFinished: {
                txtInformacionProbemaDeCarga.visible=false
                web_view1.reload.visible=false
                web_view1.visible=true
            }
        }

        Text {
            id: txtInformacionProbemaDeCarga
            x: 75
            y: -17
            color: "#474747"
            text: qsTr("Existen problemas para cargar las cotizacion online")
            visible: false
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            //
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 13
        }

    }

    Rectangle {
        id: rectLineaVerticalMenuGris
        height: 1
        color: "#abb2b1"
        anchors.top: rectangle1.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 0
        //
        visible: true
        rotation: 0
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    Rectangle {
        id: rectLineaVerticalMenuBlanco
        height: 1
        color: "#ffffff"
        anchors.top: rectangle1.bottom
        anchors.topMargin: 19
        anchors.right: parent.right
        anchors.rightMargin: 0
        //
        visible: true
        rotation: 0
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    Flow {
        id: flow1
        height: flow1.implicitHeight
        z: 7
        spacing: 5
        flow: Flow.LeftToRight
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.top: rectLineaVerticalMenuGris.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.topMargin: 10


        TextInputSimple {
            id: txtCodigoMoneda
          //  width: 120
            textoInputBox: ""
            botonBuscarTextoVisible: false
            inputMask: "000000;"
            largoMaximo: 6
            botonBorrarTextoVisible: true
            textoTitulo: "Código moneda:"
            colorDeTitulo: "#333333"
            onTabulacion: txtNombreMoneda.tomarElFoco()
            onEnter: txtNombreMoneda.tomarElFoco()
        }

        TextInputSimple {
            id: txtNombreMoneda
            x: -3
            y: -3
          //  width: 200
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            botonBorrarTextoVisible: true
            largoMaximo: 25
            textoTitulo: "Nombre moneda:"
            colorDeTitulo: "#333333"
            onTabulacion: txtCodigoISO3166.tomarElFoco()
            onEnter: txtCodigoISO3166.tomarElFoco()
        }

        TextInputSimple {
            id: txtCodigoISO3166
            x: -5
            y: 6
          //  width: 140
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            largoMaximo: 10
            botonBorrarTextoVisible: true
            textoTitulo: "Codigo ISO-3166:"
            colorDeTitulo: "#333333"
            onTabulacion: txtCodigoISO4217.tomarElFoco()
            onEnter: txtCodigoISO4217.tomarElFoco()
        }

        TextInputSimple {
            id: txtCodigoISO4217
            x: 0
            y: -1
        //    width: 140
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            botonBorrarTextoVisible: true
            largoMaximo: 10
            textoTitulo: "Codigo ISO-4217:"
            colorDeTitulo: "#333333"
            onTabulacion: txtSimboloDeLaMoneda.tomarElFoco()
            onEnter: txtSimboloDeLaMoneda.tomarElFoco()
        }

        TextInputSimple {
            id: txtSimboloDeLaMoneda
            x: 3
            y: -9
          //  width: 130
            enFocoSeleccionarTodo: true
            textoInputBox: ""
            botonBuscarTextoVisible: false
            largoMaximo: 5
            botonBorrarTextoVisible: true
            textoTitulo: "Simbolo moneda:"
            colorDeTitulo: "#333333"
            onTabulacion: txtCotizacionMoneda.tomarElFoco()
            onEnter: txtCotizacionMoneda.tomarElFoco()
        }
        TextInputSimple {
            id: txtCotizacionMoneda
            x: 0
            y: 0
         //   width: 130
            height: 35
            z: 2
            enFocoSeleccionarTodo: true
            textoInputBox: ""+modeloconfiguracion.retornaCantidadDecimalesString()+""
            botonBuscarTextoVisible: false
            inputMask: "0000"+modeloconfiguracion.retornaCantidadDecimalesString()+";"
            largoMaximo: 45
            textoTitulo: "Cotización:"
            colorDeTitulo: "#252424"
            onTabulacion: txtCotizacionMonedaOficial.tomarElFoco()
            onEnter: txtCotizacionMonedaOficial.tomarElFoco()
        }

        TextInputSimple {
            id: txtCotizacionMonedaOficial
            x: -2
            y: -6
          //  width: 130
            height: 35
            enFocoSeleccionarTodo: true
            textoInputBox: ""+modeloconfiguracion.retornaCantidadDecimalesString()+""
            botonBuscarTextoVisible: false
            inputMask: "0000"+modeloconfiguracion.retornaCantidadDecimalesString()+";"
            largoMaximo: 45
            textoTitulo: "Cotización oficial:"
            z: 2
            colorDeTitulo: "#252424"
            onTabulacion: txtCodigoMoneda.tomarElFoco()
            onEnter: txtCodigoMoneda.tomarElFoco()
        }

        CheckBox {
            id: cbesMonedaReferenciaSistema
            x: 396
            y: 97
            textoValor: "Es la moneda de referencia"
            chekActivo: true
            colorTexto: "#333333"
        }
    }

    Text {
        id: txtInformacionDeWeb
        x: 80
        height: 20
        color: "#474747"
        text: qsTr("Información obtenida de brou.com.uy")
        anchors.horizontalCenter: rectangle1.horizontalCenter
        font.family: "Arial"
        anchors.top: rectangle1.bottom
        anchors.topMargin: -2
        //
        font.pixelSize: 9
        visible: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Rectangle {
        id: rectListaDeMonedas
        x: 7
        y: -9
        color: "#c4c4c6"
        radius: 3
        clip: true
        //
        anchors.top: flow1.bottom
        anchors.topMargin: 20
        ListView {
            id: listaDeMonedas
            highlightRangeMode: ListView.NoHighlightRange
            anchors.top: parent.top
            boundsBehavior: Flickable.DragAndOvershootBounds
            highlightFollowsCurrentItem: true
            anchors.right: parent.right
            delegate: ListaMonedas {
            }
            snapMode: ListView.NoSnap
            anchors.bottomMargin: 25
            spacing: 1
            anchors.bottom: parent.bottom
            clip: true
            flickableDirection: Flickable.VerticalFlick
            anchors.leftMargin: 1
            Rectangle {
                id: rectangle3
                y: listaDeMonedas.visibleArea.yPosition * listaDeMonedas.height+5
                width: 10
                height: listaDeMonedas.visibleArea.heightRatio * listaDeMonedas.height+18
                color: "#000000"
                radius: 2
                //
                anchors.rightMargin: 4
                visible: true
                z: 1
                anchors.right: listaDeMonedas.right
                opacity: 0.500
            }
            keyNavigationWraps: true
            anchors.left: parent.left
            interactive: true
            //
            anchors.topMargin: 25
            anchors.rightMargin: 1
            model: modeloMonedas
        }

        Text {
            id: txtTituloListaMonedas
            text: qsTr("Monedas: "+listaDeMonedas.count)
            //
            anchors.top: parent.top
            anchors.topMargin: 5
            font.family: "Arial"
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
            anchors.top: parent.top
            anchors.topMargin: 5
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
            anchors.rightMargin: 3
            toolTip: ""
            rotation: 90
            anchors.right: parent.right

            onClic: listaDeMonedas.positionViewAtIndex(0,0)
        }

        BotonBarraDeHerramientas {
            id: botonBajarListaFinal1
            x: 483
            y: 231
            width: 14
            height: 14
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaFinal.png"
            anchors.bottom: parent.bottom
            anchors.rightMargin: 3
            toolTip: ""
            anchors.bottomMargin: 5
            rotation: -90
            anchors.right: parent.right

            onClic: listaDeMonedas.positionViewAtIndex(listaDeMonedas.count-1,0)

        }
        anchors.bottom: parent.bottom
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    Row {
        id: rowBarraDeHerramientas
        x: 30
        y: 55
        height: 30
        //
        spacing: 15
        BotonBarraDeHerramientas {
            id: botonNuevaMoneda
            x: 33
            y: 10
            //source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Monedas.png"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Nuevo.png"
            toolTip: "Nueva moneda"
            anchors.verticalCenter: parent.verticalCenter
            z: 8
            onClic: {


                txtCodigoMoneda.textoInputBox=modeloMonedas.ultimoRegistroDeMoneda()
                txtNombreMoneda.textoInputBox=""
                txtCodigoISO3166.textoInputBox=""
                txtCodigoISO4217.textoInputBox=""
                txtSimboloDeLaMoneda.textoInputBox=""
                txtCotizacionMoneda.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                txtCotizacionMonedaOficial.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                cbesMonedaReferenciaSistema.setActivo(false)
                txtNombreMoneda.tomarElFoco()

            }
        }

        BotonBarraDeHerramientas {
            id: botonGuardarMoneda
            x: 61
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/GuardarCliente.png"
            toolTip: "Gurardar moneda"
            anchors.verticalCenter: parent.verticalCenter
            z: 7
            onClic: {

                txtMensajeInformacion.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                var esMonedaReferenciaSistema=0

                if(cbesMonedaReferenciaSistema.chekActivo)
                    esMonedaReferenciaSistema=1

                    var resultadoConsulta = modeloMonedas.insertarMonedas(txtCodigoMoneda.textoInputBox.trim(),txtNombreMoneda.textoInputBox.trim(), txtCodigoISO3166.textoInputBox.trim(),txtCodigoISO4217.textoInputBox.trim(),txtSimboloDeLaMoneda.textoInputBox.trim(),txtCotizacionMoneda.textoInputBox.trim(),txtCotizacionMonedaOficial.textoInputBox.trim(),esMonedaReferenciaSistema)


                    if(resultadoConsulta==1){

                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text="Moneda "+ txtCodigoMoneda.textoInputBox+" dada de alta ok"

                        modeloMonedas.limpiarListaMonedas()
                        modeloMonedas.buscarMonedas("1=","1")
                        listaDeMonedas.currentIndex=0;

                        modeloListaMonedas.limpiarListaMonedas()
                        modeloListaMonedas.buscarMonedas("1=","1")

                        modeloMonedasTotales.limpiarListaMonedas()
                        modeloMonedasTotales.buscarMonedas("1=","1")

                        txtCodigoMoneda.textoInputBox=""
                        txtNombreMoneda.textoInputBox=""
                        txtCodigoISO3166.textoInputBox=""
                        txtCodigoISO4217.textoInputBox=""
                        txtSimboloDeLaMoneda.textoInputBox=""
                        txtCotizacionMoneda.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                        txtCotizacionMonedaOficial.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                        cbesMonedaReferenciaSistema.setActivo(false)
                        txtCodigoMoneda.tomarElFoco()

                    }else if(resultadoConsulta==2){
                        txtMensajeInformacion.color="#2f71a0"
                        txtMensajeInformacion.text="Moneda "+ txtCodigoMoneda.textoInputBox+" actualizada."

                        modeloMonedas.limpiarListaMonedas()
                        modeloMonedas.buscarMonedas("1=","1")
                        listaDeMonedas.currentIndex=0;

                        modeloListaMonedas.limpiarListaMonedas()
                        modeloListaMonedas.buscarMonedas("1=","1")

                        txtCodigoMoneda.textoInputBox=""
                        txtNombreMoneda.textoInputBox=""
                        txtCodigoISO3166.textoInputBox=""
                        txtCodigoISO4217.textoInputBox=""
                        txtSimboloDeLaMoneda.textoInputBox=""
                        txtCotizacionMoneda.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                        txtCotizacionMonedaOficial.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                        cbesMonedaReferenciaSistema.setActivo(false)
                        txtCodigoMoneda.tomarElFoco()

                    }else if(resultadoConsulta==-1){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="No se pudo conectar a la base de datos"


                    }else if(resultadoConsulta==-2){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="No se pudo actualizar la información de la moneda"


                    }else if(resultadoConsulta==-3){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="No se pudo dar de alta la moneda"


                    }else if(resultadoConsulta==-4){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="No se pudo realizar la consulta a la base de datos"


                    }else if(resultadoConsulta==-5){
                        txtMensajeInformacion.color="#d93e3e"
                        txtMensajeInformacion.text="Faltan datos para guardar la moneda"

                    }
            }
        }

        BotonBarraDeHerramientas {
            id: botonEliminarMoneda
            x: 54
            y: 3
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
            toolTip: "Eliminar moneda"
            anchors.verticalCenter: parent.verticalCenter
            z: 6
            onClic: {


                if(txtCodigoMoneda.textoInputBox.trim()!="")
                    if(funcionesmysql.mensajeAdvertencia("Realmente desea eliminar la moneda "+txtCodigoMoneda.textoInputBox.trim()+"?\n\nPresione [ Sí ] para confirmar.")){

                txtMensajeInformacion.visible=true
                txtMensajeInformacionTimer.stop()
                txtMensajeInformacionTimer.start()

                if(modeloMonedas.eliminarMonedas(txtCodigoMoneda.textoInputBox.trim())){

                    txtMensajeInformacion.color="#2f71a0"
                    txtMensajeInformacion.text="Moneda "+txtCodigoMoneda.textoInputBox.trim()+" eliminado."

                    modeloMonedas.limpiarListaMonedas()
                    modeloMonedas.buscarMonedas("1=","1")
                    listaDeMonedas.currentIndex=0;

                    modeloListaMonedas.limpiarListaMonedas()
                    modeloListaMonedas.buscarMonedas("1=","1")

                    modeloMonedasTotales.limpiarListaMonedas()
                    modeloMonedasTotales.buscarMonedas("1=","1")

                    txtCodigoMoneda.textoInputBox=""
                    txtNombreMoneda.textoInputBox=""
                    txtCodigoISO3166.textoInputBox=""
                    txtCodigoISO4217.textoInputBox=""
                    txtSimboloDeLaMoneda.textoInputBox=""
                    txtCotizacionMoneda.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                    txtCotizacionMonedaOficial.textoInputBox="0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
                    cbesMonedaReferenciaSistema.setActivo(false)
                    txtCodigoMoneda.tomarElFoco()

                }else{

                    txtMensajeInformacion.color="#d93e3e"
                    txtMensajeInformacion.text="No se puede eliminar la moneda."

                }}
            }
        }

        BotonBarraDeHerramientas {
            id: botonListarTodosLasMonedas
            x: 47
            y: 10
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Update.png"
            toolTip: "Listar todos las monedas"
            anchors.verticalCenter: parent.verticalCenter
            z: 5
            onClic: {

                modeloMonedas.limpiarListaMonedas()
                modeloMonedas.buscarMonedas("1=","1")
                listaDeMonedas.currentIndex=0;
            }
        }

        Text {
            id: txtMensajeInformacion
            y: 7
            color: "#d93e3e"
            text: qsTr("Información:")
            //
            font.pixelSize: 14
            style: Text.Raised
            visible: false
            styleColor: "#ffffff"
            font.family: "Arial"
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


    Timer{
        id:txtMensajeInformacionTimer
        repeat: false
        interval: 5000
        onTriggered: {

            txtMensajeInformacion.visible=false
            txtMensajeInformacion.color="#d93e3e"

        }
    }

    TextEdit {
        id: txtTituloListaMonedas1
        x: -3
        y: 2
        width: 350
        text: "Tips: Solo puede haber configurada una moneda de referencia del sistema; en caso de tener mas de una provocara inconsistencias en la información.\nLos códigos ISO son a modo de referencia, y no son obligatorios para el alta de nuevas monedas.\n"
        textFormat: TextEdit.RichText
        activeFocusOnPress: false
        readOnly: true
        //
        wrapMode: TextEdit.WordWrap
        anchors.top: parent.top
        anchors.topMargin: 30
        font.family: "Arial"
        font.bold: false
        font.pointSize: 10
        anchors.leftMargin: 20
        anchors.left: parent.left
    }

}
