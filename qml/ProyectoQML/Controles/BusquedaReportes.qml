import QtQuick 1.1

Rectangle {
    width: 400
    height: 400
    color: "#1c1c1c"
    radius: 0
    border.color: "#2a2a2a"
    border.width: 0





    function cargarModeloListaReportesEnBusqueda() {

        dataModel.clear()
        filteredModel.clear()
        modeloReportesBusqueda.limpiarListaReportes();
        modeloReportesBusqueda.buscarReportesDeBusquedas("1=","1",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),txtNombreDeUsuario.textoInputBox.trim());


        for(var i=0; i<modeloReportesBusqueda.rowCount();i++){
                dataModel.append({
                                                            codigo: modeloReportesBusqueda.retornarCodigoReporte(i),
                                                            nombre: modeloReportesBusqueda.retornarDescripcionReporte(i)
                })
        }
        searchField.textoInputBox="1";
        searchField.textoInputBox="";
    }

    ListModel {
        id: dataModel

    }


    ListModel {
        id: filteredModel
    }

    Column {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 25



        TextInputSimple {
            id: searchField
            width: 360
            altoControlRecta: 35
            altoControl: 55
            radioControl: 10
            largoMaximo: 25
            tamanioFuente: 20
            tamanioFuenteTitulo: 16
            colorDeTitulo: "#7f7f7f"
            textoDeFondo: qsTr("Buscar reportes...")
            textoInputBox: ""
            anchors.horizontalCenter: parent.horizontalCenter
            echoMode: 0
            textoTitulo: qsTr("")
            botonBorrarTextoVisible: true

            onTextoCambia: {


                filteredModel.clear();
                for (var i = 0; i < dataModel.count; i++) {
                    var item = dataModel.get(i);
                    if (item.nombre.toLowerCase().indexOf(searchField.textoInputBox.trim().toLowerCase()) !== -1) {
                        filteredModel.append(item);
                    }
                }
            }
        }

        ListView {
            width: parent.width-200
            height: parent.height - searchField.height - 60
            anchors.horizontalCenter: parent.horizontalCenter
            clip: true
            spacing: 10
            model: filteredModel

            delegate: Rectangle {
                width: parent.width
                height: 60
                radius: 10
                smooth: true
                color: "#4d4d4d"

                Rectangle {
                    smooth: true
                    width: parent.width-1
                    height: parent.height
                    color: {
                        if(String(index).length===1){
                           //  "#2e2e"+String(index)+"e"

                            "#2e2e"+String(9-index)+String(9-index)
                            //"#051"+String(9-index)+"1"+String(index)
                        }else{
                            "#2e2e2e"
                        }



                    }
                    radius: 10
                    border.color: "#4d4d4d"
                    border.width: 1

                    Gradient {
                        GradientStop { position: 0.0; color: "#3b3b3b" }
                        GradientStop { position: 1.0; color: "#1e1e1e" }
                    }

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        text: nombre
                        smooth: true
                        color: "#d3d3d3"
                        font.pointSize: 16
                    }

                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent

                        onClicked: {           
                            cbxListaReportes.codigoSql=modeloReportes.retornaSqlReporte(codigo)
                            cbxListaReportes.codigoSqlGraficas=modeloReportes.retornaSqlReporteGraficas(codigo)
                            cbxListaReportes.codigoSqlCabezal=modeloReportes.retornaSqlReporteCabezal(codigo)
                            seleccionarReporte(codigo)
                        }

                        Rectangle {
                            smooth: true
                            anchors.fill: parent
                            color: "transparent"
                            border.color: "#00ffcc"
                            border.width: 3
                            radius: 10
                            visible: mouseArea.pressed
                        }
                    }
                }
            }
        }

        Component.onCompleted: {
            for (var i = 0; i < dataModel.count; i++) {
                filteredModel.append(dataModel.get(i));
            }
        }
    }
}
