import QtQuick 1.1
import "../Listas"

Rectangle {
    id: raiz
    color: "#be231919"
    visible: true
    anchors.fill: parent
    z: 8

    signal clicCancelar
    // Emite: codigo, nombre, porcentaje (si es %; si es monto va 0), esRecargo
    signal sendDescuentoRecargo(string codigo, string nombre, real valoraDescontar, bool esRecargo, bool esPorMonto, string moneda, string indiceArticulo, string aplicaSobrePrecioUnitario)

    // API pública (como tu otro cuadro)
    property alias modeloItems: listaDescuentos.model
    property alias textoBoton: btnCancelarOperacion.text

    property string indexItem:""


    function limpiarBuscador() { txtBuscar.text = "" }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        Rectangle {
            id: rectPanel
            width: 700
            height: 430
            color: "#1e7597"
            radius: 5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            BotonFlecha {
                id: btnCerrar
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.topMargin: -15
                anchors.rightMargin: -15
                opacidadRectPrincipal: 0.800
                smooth: true
                z: 1
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/CerrarLista.png"
                onClic: clicCancelar()
            }

            Text {
                id: lblTitulo
                color: "#ffffff"
                text: qsTr("Descuentos y Recargos: seleccione uno")
                style: Text.Raised
                font.underline: true
                font.bold: true
                font.family: "Verdana"
                font.pixelSize: sizeTitulosControles
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
            }

            // --- Búsqueda ---
            Text {
                id: lblBuscar
                text: qsTr("Buscar:")
                color: "#ffffff"
                font.family: "Verdana"
                anchors.left: parent.left
                anchors.leftMargin: 35
                anchors.top: lblTitulo.bottom
                anchors.topMargin: 12
            }

            Rectangle {
                id: cajaBuscar
                width: 320
                height: 28
                radius: 3
                color: "#ffffff"
                anchors.left: lblBuscar.right
                anchors.leftMargin: 8
                anchors.verticalCenter: lblBuscar.verticalCenter

                TextInput {
                    id: txtBuscar
                    anchors.fill: parent
                    anchors.margins: 6
                    font.family: "Verdana"
                    clip: true
                    focus: true

                }

                Text {
                    // placeholder compatible 1.1
                    anchors.fill: parent
                    anchors.margins: 6
                    color: "#888888"
                    text: qsTr("Escriba para filtrar...")
                    visible: txtBuscar.text.length === 0 && !txtBuscar.activeFocus
                }

                MouseArea { anchors.fill: parent; onClicked: txtBuscar.forceActiveFocus() }
            }

            // --- Lista ---
            ListView {
                id: listaDescuentos
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 35
                anchors.rightMargin: 20
                anchors.top: cajaBuscar.bottom
                anchors.topMargin: 12
                anchors.bottom: btnCancelarOperacion.top
                anchors.bottomMargin: 10

                clip: true
                spacing: 1
                flickableDirection: Flickable.VerticalFlick
                boundsBehavior: Flickable.DragAndOvershootBounds
                highlightRangeMode: ListView.NoHighlightRange
                highlightFollowsCurrentItem: true
                keyNavigationWraps: true

                // Delegate SEGURO para Qt 4.8 (con guards y bindings vivos)
                delegate: Item {
                    id: fila
                    width: listaDescuentos.width

                    // --- Guards + bindings vivos a roles ---
                    // Nota: usamos typeof para evitar ReferenceError al instanciar,
                    // pero mantenemos la referencia directa al rol para que reaccione.

                    // Strings base
                    property string tipoStr: (typeof tipo !== "undefined" && tipo !== null) ? String(tipo) : ""
                    property string tipoValorStr: (typeof tipoValor !== "undefined" && tipoValor !== null) ? String(tipoValor) : ""
                    property string nombreStr: (typeof nombre !== "undefined" && nombre !== null) ? String(nombre)
                                           : ((typeof descripcion !== "undefined" && descripcion !== null) ? String(descripcion) : "")

                    // Números base
                    property real porcentajeVal: (typeof porcentaje !== "undefined" && porcentaje !== null) ? Number(porcentaje) : 0
                    property real montoVal: (typeof monto !== "undefined" && monto !== null) ? Number(monto) : 0

                    // Otros
                    property string simboloStr: (typeof simbolo !== "undefined" && simbolo !== null) ? String(simbolo) : ""
                    property int codigoVal: (typeof codigo !== "undefined" && codigo !== null) ? codigo : -1

                    // Derivados
                    property bool esRecargo: (tipoStr.toLowerCase() === "r" || tipoStr.toLowerCase() === "recargo")
                    property bool esMonto: (tipoValorStr.toLowerCase() === "monto" || tipoValorStr.toLowerCase() === "m")

                    // Filtro en vivo
                    property string textoComp: (nombreStr + " " + (esMonto ? montoVal : porcentajeVal) + " " + tipoStr).toLowerCase()
                    property string queryLower: String(txtBuscar.text).toLowerCase()
                    property bool coincide: (queryLower.length === 0) || (textoComp.indexOf(queryLower) !== -1)

                    height: coincide ? 40 : 0
                    visible: coincide

                    Rectangle {
                        anchors.fill: parent
                        color: ListView.isCurrentItem ? "#2a91b8" : (mouse.containsMouse ? "#247ea1" : "#1a6b86")
                        radius: 3
                        border.color: "#0d4155"
                        border.width: 1
                    }

                    Rectangle {
                        id: badge
                        width: 10; height: 10
                        radius: 2
                        color: esRecargo ? "#e74c3c" : "#2ecc71"
                        anchors.left: parent.left
                        anchors.leftMargin: 6
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    // NOMBRE (entre badge y etiqueta tipo)
                    Text {
                        color: "#ffffff"
                        text: nombreStr
                        elide: Text.ElideRight
                        font.family: "Verdana"
                        anchors.left: badge.right
                        anchors.leftMargin: 8
                        anchors.right: tipoLbl.left
                        anchors.rightMargin: 8
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    // Etiqueta tipo (DESCUENTO/RECARGO)
                    Text {
                        id: tipoLbl
                        color: "#ffffff"
                        font.family: "Verdana"
                        font.pixelSize: 12
                        text: esRecargo ? qsTr("RECARGO") : qsTr("DESCUENTO")
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: valorLbl.left
                        anchors.rightMargin: 16
                        opacity: 0.9
                    }

                    // Valor a la derecha
                    Text {
                        id: valorLbl
                        color: "#ffffff"
                        font.family: "Verdana"
                        font.bold: true
                        text: esMonto
                              ? ((simboloStr ? (simboloStr + " ") : "") + (montoVal.toFixed(2)))
                              : ((esRecargo ? "+" : "\u2212") + (porcentajeVal.toFixed(2)) + "%")
                        anchors.right: parent.right
                        anchors.rightMargin: 12
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    // Doble clic compatible 1.1
                    MouseArea {
                        id: mouse
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            listaDescuentos.currentIndex = index
                            if (dblTimer.running) { dblTimer.stop(); aplicar(); }
                            else dblTimer.start()
                        }
                    }
                    Timer { id: dblTimer; interval: 250; repeat: false; running: false }

                    function aplicar() {

                        var porc = esMonto ? montoVal.toFixed(2) : porcentajeVal.toFixed(2)
                        sendDescuentoRecargo(String(codigoVal), String(nombreStr), porc, esRecargo, esMonto, moneda,indexItem,aplicaSobrePrecioUnitario)
                    }
                }

                // Scrollbar
                Rectangle {
                    id: scrollbar
                    y: listaDescuentos.visibleArea.yPosition * listaDescuentos.height + 5
                    width: 10
                    height: listaDescuentos.visibleArea.heightRatio * listaDescuentos.height + 18
                    color: "#000000"
                    radius: 2
                    opacity: 0.5
                    anchors.right: listaDescuentos.right
                    anchors.rightMargin: 4
                    z: 1
                    visible: listaDescuentos.contentHeight > listaDescuentos.height + 2
                }
            }

            // Texto informativo
            Text {
                id: lblInfo
                color: "#ffffff"
                text: qsTr("Escriba para filtrar. Doble clic en un ítem para aplicarlo. O Cancelar para salir.")
                style: Text.Normal
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                font.family: "Verdana"
                font.pixelSize: sizeTitulosControles
                anchors.left: parent.left
                anchors.leftMargin: 35
                anchors.right: parent.right
                anchors.rightMargin: 15
                anchors.bottom: btnCancelarOperacion.top
                anchors.bottomMargin: 40
            }

            BotonPaletaSistema {
                id: btnCancelarOperacion
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 20
                border.color: "#787777"
                onClicked: clicCancelar()
            }

            // Barra lateral decorativa
            Rectangle {
                width: 10
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.leftMargin: 5
                clip: true

                Rectangle {
                    width: 3
                    height: parent.height / 1.50
                    color: "#1e7597"
                    radius: 5
                    opacity: 0.8
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -1
                }

                gradient: Gradient {
                    GradientStop { position: 0; color: "#0f4c7d" }
                    GradientStop { position: 1; color: "#1a2329" }
                }
            }
        }
    }
}
