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

Rectangle{
    id: rectListaItem
  //  width: parent.width
    width: 900
    height: 23
    color: "#e9e8e9"
    radius: 1
    border.color: "#aaaaaa"
    //
    opacity: 1


    Text {
        id:lblCuentasBancarias
        text: numeroCuentaBancaria + " - "+descripcionCuentaBancaria + " - Banco: "+modeloListaBancos.retornaDescripcionBanco(codigoBanco)
        font.family: "Arial"
        opacity: 0.900
        //
        font.pointSize: 10
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.top: parent.top
        anchors.topMargin: 0
        color: "#212121"

    }
    PropertyAnimation{
        id:rectListaItemColorSeleccionado
        target: rectListaItem
        property: "color"
        from: "#e9e8e9"
        to:"#9294C6"
        duration: 100
    }
    PropertyAnimation{
        id:rectListaItemColorDeseleccionado
        target: rectListaItem
        property: "color"
        to: "#e9e8e9"
        from:"#9294C6"
        duration: 50

    }

    ListView {
        id: listaTotalporCuentaBancaria
        width: 300
        height: 20
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: lblCuentasBancarias.bottom
        anchors.topMargin: 9
        highlightRangeMode: ListView.NoHighlightRange
        boundsBehavior: Flickable.StopAtBounds
        highlightFollowsCurrentItem: true
        delegate: ListaTotalCuentaBancariaXMonedas {
            _numeroCuentaBancaria: numeroCuentaBancaria
            _codigoBancoCuentaBancaria: codigoBanco
        }
        snapMode: ListView.NoSnap
        spacing: 0
        clip: true
        visible: false
        flickableDirection: Flickable.VerticalFlick
        keyNavigationWraps: false
        model: modeloMonedasTotales

    }

    FocusScope {
        id: focus_scope1
        anchors.fill: parent

        onFocusChanged: {

            if(focus_scope1.focus){

                listaTotalporCuentaBancaria.visible=false

                listaTotalporCuentaBancaria.height=listaTotalporCuentaBancaria.contentHeight

                rectListaItemContraer.stop()
                rectListaItemExpandir.start()

                rectListaItem.color="#9294C6"
            }else{
                listaTotalporCuentaBancaria.visible=false


                rectListaItemExpandir.stop()
                rectListaItemContraer.start()

                lblCuentasBancarias.color= "#212121"
                rectListaItemColorDeseleccionado.start()

            }

        }

        MouseArea{
            id: mousearea1
            z: 1
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                if(focus_scope1.focus==false){

                    lblCuentasBancarias.color="white"
                    rectListaItemColorDeseleccionado.stop()
                    rectListaItemColorSeleccionado.start()
                }
            }
            onExited: {

                if(focus_scope1.focus==false){
                    lblCuentasBancarias.color= "#212121"
                    rectListaItemColorSeleccionado.stop()
                    rectListaItemColorDeseleccionado.start()

                }
            }
            onClicked: {
                modeloMonedasTotales.limpiarListaMonedas()
                modeloMonedasTotales.buscarMonedas("1=","1")

                txtNumeroCuentaBancaria.textoInputBox=numeroCuentaBancaria
                txtNombreCuentaBancaria.textoInputBox=descripcionCuentaBancaria
                cbxListaBancos.codigoValorSeleccion=codigoBanco
                cbxListaBancos.textoComboBox=modeloListaBancos.retornaDescripcionBanco(codigoBanco)
                txtObservacionesCuentaBancaria.textoInputBox=observaciones
                txtNombreCuentaBancaria.tomarElFoco()

                focus_scope1.focus=true
            }
        }
    }


    PropertyAnimation{
        id:rectListaItemExpandir
        target: rectListaItem
        property: "height"
        from:23
        to: listaTotalporCuentaBancaria.contentHeight+30
        duration: 100
        onCompleted: {
            listaTotalporCuentaBancaria.visible=true
        }
    }
    PropertyAnimation{
        id:rectListaItemContraer
        target: rectListaItem
        property: "height"
        to:23
        from:listaTotalporCuentaBancaria.contentHeight+30
        duration: 50
    }

}
