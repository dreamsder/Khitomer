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
import "../Listas/Delegates"

Rectangle{
    id: rectListaItem
    width: parent.width
    // width: 800
    height: 35
    color: "#e9e8e9"
    radius: 1
    clip: false
    border.width: 1
    border.color: "#bebbbb"
    //
    opacity: 1

    Rectangle {
        id: rectangle1
        height: 19
        color: "#e9e8e9"
        clip: false
        //
        anchors.right: parent.right
        anchors.rightMargin: 1
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.left: parent.left
        anchors.leftMargin: 1

        Text {
            id:txtDescripcionItem
            x: 17
            y: -3
            width: 80
            font.family: "Arial"
            opacity: 0.900
            //
            font.pointSize: 10
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 0
            color: "#2d2c2c"
            text: modeloClientes.retornaDescripcionDeCliente(codigoItem,2)+" ("+codigoItem+")"
            styleColor: "#41638f"
            style: Text.Raised
        }

        Text {
            id: txtInfoExtendida
            x: 8
            y: -9
            width: 80
            color: "#2d2c2c"
            text: "Cantidad de compras: "+ modeloDocumentos.retornoCantidadDocumentosPorCliente(codigoItem,2,"EMITIDOS")
            horizontalAlignment: Text.AlignRight
            anchors.right: parent.right
            anchors.rightMargin: 30
            //
            anchors.top: parent.top
            anchors.topMargin: 0
            style: Text.Normal
            styleColor: "#41638f"
            font.family: "Arial"
            font.pointSize: 10
            opacity: 0.900
            verticalAlignment: Text.AlignVCenter
        }
    }
}
