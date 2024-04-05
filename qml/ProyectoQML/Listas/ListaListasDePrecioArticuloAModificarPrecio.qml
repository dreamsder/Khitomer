/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2024>  <Cristian Montano>

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
    width: parent.width
    height: 32
    color: "#e9e8e9"
    radius: 1
    border.color: "#aaaaaa"
    //
    opacity: 1

    property double precioActualArticulo: modeloListaPrecioArticulos.retornarPrecioDeArticuloEnBaseDeDatos(codigoArticulo,codigoListaDePrecio)
    property double precioActualArticuloItem: precioArticulo


    Text {
        id:lblListaDePrecioArticulo
        text: descripcionListaDePreciosAModificar+" - <b style=\" color: '#4c6bb5'\">Precio actual: "+modeloMonedas.retornaSimboloMoneda(modeloMonedas.retornaCodigoMoneda(codigoArticulo))+" "+precioActualArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO"))+"</b>"
        clip: true
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: txtPrecioArticuloParaLista.left
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        font.family: "Arial"
        opacity: 0.900
        //
        font.pointSize: 10
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        color: "#212121"
    }


    TextInputSimple {

        property double precioNuevoArticulo:0.00

        id: txtPrecioArticuloParaLista
        margenIzquierdo: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        botonBorrarTextoVisible: false
        anchors.right: parent.right
        anchors.rightMargin: 0
        colorDeTitulo: "#252424"
        largoMaximo: 45
        inputMask: "00000000"+modeloconfiguracion.retornaCantidadDecimalesString()+";"
        enFocoSeleccionarTodo: true
        textoInputBox: "0"+modeloconfiguracion.retornaCantidadDecimalesString()+""
        botonBuscarTextoVisible: false
        textoTitulo: ""
        onTextoInputBoxChanged: {
            if(txtPrecioArticuloParaLista.textoInputBox.trim()!="."){
               precioNuevoArticulo=parseFloat(txtPrecioArticuloParaLista.textoInputBox.trim())
                precioNuevoArticulo=precioNuevoArticulo+0.00;
                modeloListasPreciosCuadroArticulosASetearPrecioGenerica.setProperty(index,"precioArticulo",precioNuevoArticulo.toFixed(modeloconfiguracion.retornaValorConfiguracion("CANTIDAD_DIGITOS_DECIMALES_MONTO")))
            }
        }


    }
}
