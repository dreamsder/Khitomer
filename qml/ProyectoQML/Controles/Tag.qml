import QtQuick 1.1

Rectangle {
    id: rectTagPrincipal
    width: txtTextoTag.implicitWidth+50
    height: 20
    color: "#00000000"
    opacity: opacidadPorDefecto

    signal clic
    property double scaleValorActual: 1
    property alias colorTag:txtTextoTag.color
    property alias texto: txtTextoTag.text
    property alias toolTip: toolTipText.text
    property alias source: imageTag.source
    property double opacidadPorDefecto: 0.3
    property color _gradietMedioIndicador: "#f7960e"

    property alias  indicadorColor: rectangle4.color

    Image {
        id: imageTag
        width: 20
        height: 20
        smooth: true
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        asynchronous: true
        source: ""
    }

    Text {
        id: txtTextoTag
        color: "#ffffff"
        text: qsTr("TAG generico")
        font.family: "Arial"
        styleColor: "#183ccc"
        style: Text.Sunken
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        smooth: true
        font.pixelSize: 12
    }

    MouseArea {
        id: mouse_areaTag
        anchors.rightMargin: 20
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            rectTagPrincipalOpacityOff.stop()
            rectTagPrincipalOpacityIn.start()
        }
        onExited: {
            rectToolTipText.visible=false
            rectTagPrincipalOpacityIn.stop()
            rectTagPrincipalOpacityOff.start()
        }
        onPressed: {
            rectToolTipText.visible=false
        }

        onClicked: clic()
    }
    PropertyAnimation{
        id:rectTagPrincipalOpacityIn
        target: rectTagPrincipal
        property: "opacity"
        from:opacidadPorDefecto
        to:1
        duration:100
    }

    PropertyAnimation{
        id:rectTagPrincipalOpacityOff
        target: rectTagPrincipal
        property: "opacity"
        from:1
        to:opacidadPorDefecto
        duration:40
    }
    Rectangle{
        id:rectToolTipText
        visible: false
        width: toolTipText.implicitWidth+20
        height: toolTipText.implicitHeight
        color: "#4d7dc0"
        radius: 6
        z: 1
        smooth: true
        Text {
            id: toolTipText
            color: "#fdfbfb"
            text: ""
            font.family: "Arial"
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.fill: parent
            smooth: true
            visible: true
        }
    }
    Rectangle {
        id: rectangle4
        width: 4
        radius: 2
        border.width: 0
        clip: false
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 10
    }



    Rectangle {
        id: recIndicadorOpcion
        height: 30
        color: "#00000000"
        anchors.left: parent.left
        anchors.leftMargin: 1
        anchors.right: parent.right
        anchors.rightMargin: 10
        visible: opacidadPorDefecto==1 ? "true" : "false"
        anchors.bottom: parent.top
        anchors.bottomMargin: 2
        clip: true



        Rectangle {
            id: rectangle2
            y: 6
            height: 2
            color: "#ffffff"
            radius: 4
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            smooth: true
            anchors.bottom: parent.bottom
            visible: true
            anchors.bottomMargin: 0
            z: -1
            opacity: 1
        }
    }

    Rectangle {
        id: rectangle3
        height: 2
        color: "#ffffff"
        radius: 4
        anchors.top: parent.bottom
        anchors.topMargin: 2
        smooth: true
        visible: opacidadPorDefecto==1 ? "true" : "false"
        anchors.rightMargin: 10
        z: -1
        anchors.right: parent.right
        anchors.leftMargin: 1
        opacity: 1
        anchors.left: parent.left
    }

}
