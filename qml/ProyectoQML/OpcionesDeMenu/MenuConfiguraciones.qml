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
    id: rectPrincipalMenuConfiguracion
    width: 900
    height: 700
    color: "#00000000"
    radius: 0
    property bool nuevoEstadochkSistenaAdmiteVerDocumentosAnterioresA6meses: false

    Text {
        id: txtTituloMenuOpcion
        x: 560
        color: "#4d5595"
        text: qsTr("configuraciones")
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

    Rectangle {
        id: rectLineaVerticalMenuGris
        height: 1
        color: "#abb2b1"
        anchors.top: parent.top
        anchors.topMargin: 60
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
        anchors.top: parent.top
        anchors.topMargin: 59
        anchors.rightMargin: 0
        visible: true
        rotation: 0
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    Flow {
        id: flow1
        height: flow1.implicitHeight
        spacing: 5
        flow: Flow.TopToBottom
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.top: rectLineaVerticalMenuBlanco.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        CheckBox {
            id: chkSistenaAdmiteVerDocumentosAnterioresA6meses
            x: 396
            y: 97
            textoValor: "Es sistema permite observar documentos."
            chekActivo: false
            visible: mODO_DOCUMENTOS_VISIBLES
            colorTexto: "#333333"
            onChekActivoChanged: {
                nuevoEstadochkSistenaAdmiteVerDocumentosAnterioresA6meses=chekActivo
                cuadroAutorizacionConfiguracion.evaluarPermisos("permiteAutorizarConfiguraciones")
            }
        }

    }



    CuadroAutorizaciones{
        id:cuadroAutorizacionConfiguracion
        color: "#be231919"
        z: 9
        anchors.fill: parent
        onConfirmacion: {
           chkSistenaAdmiteVerDocumentosAnterioresA6meses.setActivo(nuevoEstadochkSistenaAdmiteVerDocumentosAnterioresA6meses)
           visualizarDocumentosEnmODO_DOCUMENTOS_VISIBLES=nuevoEstadochkSistenaAdmiteVerDocumentosAnterioresA6meses
        }
        onPrecionarEscape: {
            chkSistenaAdmiteVerDocumentosAnterioresA6meses.setActivo(!nuevoEstadochkSistenaAdmiteVerDocumentosAnterioresA6meses)
            visualizarDocumentosEnmODO_DOCUMENTOS_VISIBLES=!nuevoEstadochkSistenaAdmiteVerDocumentosAnterioresA6meses
        }
    }
}
