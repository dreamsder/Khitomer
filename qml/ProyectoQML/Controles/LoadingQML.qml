import QtQuick 1.1

Rectangle {
    id: loadingOverlay
    anchors.fill: parent
    color: "#000000"    // Fondo negro
    opacity: 0.8        // Opacidad para efecto semi-transparente
    visible: false       // Inicialmente oculto

    // Imagen del spinner (debes proveer un ícono o imagen propia)
    // Una opción es un ícono circular o un gif animado. Aquí usaremos un PNG estático y lo haremos rotar.
    Image {
        id: spinner
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Busy.png"  // Reemplazar con el icono que desees
        width: 64
        height: 64
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        smooth: true

        // Animación de rotación continua
        NumberAnimation on rotation {
            duration: 1000
            from: 0
            to: 360
            loops: Animation.Infinite
        }
    }

    // Texto opcional debajo del spinner
    Text {
        id: loadingText
        text: "Procesando..."
        color: "#ffffff"
        font.family: "Arial"
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: spinner.bottom
        anchors.topMargin: 10
    }

    // Métodos para controlar
    function start() {
        visible = true
        spinner.rotation = 0  // Reiniciar la animación
    }

    function stop() {
        visible = false
    }
}
