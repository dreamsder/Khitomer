import QtQuick 1.1
import "../Controles"   // para ComboBoxListaMonedas y tus otros controles

Rectangle {
    id: raiz
    anchors.fill: parent
    color: "#00000000"

    Text {
        id: txtTituloMenuOpcion
        x: 560
        color: "#4d5595"
        text: qsTr("mantenimiento de descuentos/recargos")
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

    // === Contexto esperado ===
    // setContextProperty("modeloListaDescuentosRecargos", instanciaModC++);
    property alias modeloDescuentos: lista.model
    property int   defaultMoneda: 0

    // === Estado edición ===
    property int    ed_id: -1
    property bool   ed_activo: true
    property bool   ed_aplicaSobrePrecioUnitario: true
    property string ed_tipo: "DESCUENTO"        // "DESCUENTO" | "RECARGO"
    property string ed_tipoValor: "PORCENTAJE"  // "PORCENTAJE" | "MONTO"
    property string ed_descripcion: ""
    property real   ed_porcentaje: 0
    property real   ed_monto: 0
    property int    ed_moneda: 0

    // === Validación ===
    property bool guardarHabilitado: (
                                         String(ed_descripcion).replace(/^\s+|\s+$/g, "").length > 0
                                         )

                                     /*&& (
                                         ed_tipoValor === "PORCENTAJE"
                                         ? (!isNaN(parseFloat(inpPct.textoInputBox))  && parseFloat(inpPct.textoInputBox)  > 0)
                                         : (!isNaN(parseFloat(inpMonto.textoInputBox)) && parseFloat(inpMonto.textoInputBox) > 0 && ed_moneda > 0)

                                         )*/

    // === Util ===
    function normalizarHora(h) { return h && h.length === 5 ? (h + ":00") : h }

    function limpiarFormulario() {
        ed_id = -1;
        ed_activo = true;
        ed_aplicaSobrePrecioUnitario = true;
        ed_tipo = "DESCUENTO";
        ed_tipoValor = "PORCENTAJE"
        colPct.visible=true;
        colMonto.visible=false
        ed_descripcion = ""; ed_porcentaje = 0; ed_monto = 0;
        ed_moneda = (defaultMoneda>0 ? defaultMoneda : 0)
        dtDesde.textoInputBox=funcionesmysql.fechaDeHoy()
        dtHasta.textoInputBox=funcionesmysql.fechaDeHoy()
        txtDesc.textoInputBox = ""; inpPct.textoInputBox = "0.00"; inpMonto.textoInputBox = "0.00"
        if (cmbMoneda){

            cmbMoneda.codigoValorSeleccion = ed_moneda
            cmbMoneda.textoComboBox= modeloListaMonedas.retornaDescripcionMoneda(cmbMoneda.codigoValorSeleccion)
        }
        recFechas.listaFechasModel = []
        recDiasHoras.diasSeleccion = [false,false,false,false,false,false,false]
        recDiasHoras.listaHorariosModel = []
    }

    function cargarActual(idSel) {
        if (!idSel || idSel <= 0) return
        ed_id = idSel



        // Si tenés obtenerFila() la usamos; si no, cargá con roles desde ListView.currentItem
        if (modeloDescuentos.obtenerFila) {
            var row = modeloDescuentos.obtenerFila(idSel)
            ed_activo = !!row.activo
            ed_aplicaSobrePrecioUnitario= !!row.aplicaSobrePrecioUnitario
            ed_tipo   = row.tipo
            ed_tipoValor = row.tipoValor || row.tipo_valor
            ed_descripcion = row.descripcion
            ed_porcentaje = Number(row.porcentaje) || 0
            ed_monto = Number(row.monto) || 0
            ed_moneda = Number(row.moneda) || 0
        }



        if(ed_tipoValor==="PORCENTAJE"){
            colPct.visible=true;
            colMonto.visible=false;
        }else{
            colPct.visible=false;
            colMonto.visible=true;
        }


        txtDesc.textoInputBox = ed_descripcion
        inpPct.textoInputBox  = ed_porcentaje.toFixed(2)
        inpMonto.textoInputBox= ed_monto.toFixed(2)
        if (cmbMoneda){

            cmbMoneda.codigoValorSeleccion = (ed_moneda>0 ? ed_moneda : defaultMoneda)
            cmbMoneda.textoComboBox= modeloListaMonedas.retornaDescripcionMoneda(cmbMoneda.codigoValorSeleccion)
        }


        refrescarRangosFechas()
        refrescarDias()
        refrescarHorarios()
    }

    function guardarActual() {
        if (!guardarHabilitado) return

        var p = undefined, m = undefined, mon = undefined
        if (ed_tipoValor === "PORCENTAJE") {
            var n1 = parseFloat(inpPct.textoInputBox); if (isNaN(n1) || n1<0) n1 = 0
            ed_porcentaje = n1; p = n1
        } else {
            var n2 = parseFloat(inpMonto.textoInputBox); if (isNaN(n2) || n2<0) n2 = 0
            ed_monto = n2; m = n2; mon = cmbMoneda.codigoValorSeleccion
        }


        var ok = false
        if (ed_id <= 0) {                            // INSERTAR
            var nuevoId = modeloDescuentos.insertar(ed_activo?1:0, ed_tipo, ed_tipoValor,
                                                               ed_descripcion, p, m, mon,ed_aplicaSobrePrecioUnitario?1:0)
            ok = (nuevoId && nuevoId > 0)
            if (ok) ed_id = nuevoId
        } else {
            // MODIFICAR
            console.log(m)
            console.log(mon)
            ok = modeloDescuentos.modificar(ed_id, ed_activo?1:0, ed_tipo, ed_tipoValor,
                                                              ed_descripcion, p, m, mon,ed_aplicaSobrePrecioUnitario?1:0)
        }

        if (ok) modeloDescuentos.buscarDescuentosRecargos("", "", false)
    }

    /*function refrescarRangosFechas() {
        recFechas.listaFechasModel = (ed_id>0 && modeloDescuentos.listarRangosFecha)
            ? modeloDescuentos.listarRangosFecha(ed_id) : []
    }*/
    function refrescarRangosFechas() {
        var arr = (ed_id > 0 && modeloDescuentos.listarRangosFecha)
                ? modeloDescuentos.listarRangosFecha(ed_id)
                : [];
        console.log("[rangos-fecha] ed_id=", ed_id, " -> items:", (arr && arr.length) ? arr.length : 0);
        recFechas.listaFechasModel = arr || [];
    }
    function refrescarDias() {
        if (!(ed_id>0 && modeloDescuentos.listarDiasSemana)) {
            recDiasHoras.diasSeleccion = [false,false,false,false,false,false,false]; return
        }
        var arr = modeloDescuentos.listarDiasSemana(ed_id)
        var flags = [false,false,false,false,false,false,false]
        for (var i=0;i<arr.length;i++) { var d = arr[i]["dia_semana"]; if (d>=1 && d<=7) flags[d-1] = true }
        recDiasHoras.diasSeleccion = flags
    }
    function refrescarHorarios() {
        recDiasHoras.listaHorariosModel = (ed_id>0 && modeloDescuentos.listarHorarios)
                ? modeloDescuentos.listarHorarios(ed_id) : []
    }

    // ===== LAYOUT =========================================================
    Row {
        anchors.fill: parent;
        anchors.margins: 0;
        spacing: 10

        // -------- Panel izquierdo (lista) --------
        Rectangle {
            id: panelIzq;
            width: 300;
            color: "#00000000"

            anchors.top: parent.top; anchors.bottom: parent.bottom

            Column {
                anchors.fill: parent; anchors.margins: 10; spacing: 8

                TextInputSimple{
                    id:txtBuscar
                    textoInputBox: ""
                    botonBorrarTextoVisible: true
                    textoTitulo: qsTr("Descuentos/Recargos:")
                    colorDeTitulo: "#333333"
                    onTextoCambia: modeloDescuentos.buscarDescuentosRecargos(txtBuscar.textoInputBox.trim(), "", false)
                }


                ListView {
                    id: lista; clip: true; spacing: 4
                    anchors {
                        left: parent.left; right: parent.right; bottom: parent.bottom; top:txtBuscar.bottom


                    }
                    anchors.rightMargin: 0
                    anchors.topMargin: 10

                    delegate: Rectangle {
                        width: lista.width-10;
                        height: 44;
                        radius: 4
                        clip: true
                        smooth: true
                        color: ListView.isCurrentItem ? "#e6f4fb" : (index%2 ? "#ffffff" : "#fbfbfb")
                        border.color: ListView.isCurrentItem ? "#7ec2df" : "#e6e6e6"
                        Row {
                            anchors.fill: parent; anchors.margins: 8; spacing: 8
                            Rectangle { width: 8; height: 8; radius: 4; color: model.activo ? "#26c281" : "#c0392b" }
                            Text { text: model.descripcion; elide: Text.ElideRight; anchors.verticalCenter: parent.verticalCenter }
                            //// Rectangle { width: 8; height: 8; radius: 4; color: (activo ? "#26c281" : "#c0392b") }
                            //// Text { text: (descripcion || ""); elide: Text.ElideRight; anchors.verticalCenter: parent.verticalCenter }
                            // //MouseArea { anchors.fill: parent; onClicked: { lista.currentIndex = index; cargarActual((typeof codigo !== "undefined") ? codigo : id) } }
                        }
                        MouseArea { anchors.fill: parent; onClicked: { lista.currentIndex = index;
                                cargarActual(model.codigo || model.id)
                            }
                        }



                    }
                }
            }
        }

        // -------- Panel derecho (formulario + scroll) --------
        Rectangle {
            id: panelDer;

            color: "#00000000"
            anchors {
                left: panelIzq.right;
                right: parent.right;
                top: parent.top;
                bottom: parent.bottom }
            anchors.leftMargin: 10
            // Contenido scrollable
            Flickable {
                id: scroll
                anchors { left: parent.left; right: parent.right;
                    top: parent.top;
                    bottom: btnRow.top;
                    bottomMargin: 10
                    topMargin: 10
                }
                contentWidth: width; contentHeight: form.height; clip: true

                Column {
                    id: form; width: scroll.width; anchors.margins: 10; spacing: 13



                    Row {
                        id:alineacionDescripcionActivo
                        spacing: 20


                        TextInputSimple{
                            id:txtDesc
                            textoInputBox: ""
                            botonBorrarTextoVisible: true
                            textoTitulo: qsTr("Descripción:")
                            colorDeTitulo: "#333333"
                            onTextoCambia:ed_descripcion = txtDesc.textoInputBox.trim()
                            width: 300
                            largoMaximo: 60
                        }

                        CheckBox {
                            id: chkActivo
                            textoValor: "Activo"
                            chekActivo: ed_activo
                            visible: true
                            colorTexto: "#333333"
                            onChekActivoChanged: {
                                ed_activo = chekActivo;
                                //  nuevoEstadochkSistenaAdmiteVerDocumentosAnterioresA6meses=chekActivo
                                //  cuadroAutorizacionConfiguracion.evaluarPermisos("permiteAutorizarConfiguraciones")
                            }
                        }



                    }

                    // Tipo
                    Text { text: "Tipo/Tipo valor"; color:"#333"; font.pixelSize: 12
                        font.bold: true
                    }
                    Row {
                        spacing: 6
                        Rectangle {
                            width: 110; height: 28; radius: 14
                            color: ed_tipo==="DESCUENTO" ? "#239BA7" : "#F0F0F0"
                            Text { anchors.centerIn: parent;

                                color: ed_tipo==="DESCUENTO" ? "white" : "grey"
                                text:"DESCUENTO" }
                            MouseArea { anchors.fill: parent; onClicked: ed_tipo = "DESCUENTO" }
                        }
                        Rectangle {
                            width: 110; height: 28; radius: 14
                            color: ed_tipo==="RECARGO" ? "#239BA7" : "#F0F0F0"
                            Text { anchors.centerIn: parent;
                                color: ed_tipo==="RECARGO" ? "white" : "grey"

                                text:"RECARGO" }
                            MouseArea { anchors.fill: parent; onClicked: ed_tipo = "RECARGO" }
                        }

                        Rectangle {
                            width: 115; height: 28; radius: 14
                            color: ed_tipoValor==="PORCENTAJE" ? "#239BA7" : "#F0F0F0"
                            Text { anchors.centerIn: parent;
                                color: ed_tipoValor==="PORCENTAJE" ? "white" : "grey"
                                text:"PORCENTAJE" }
                            MouseArea { anchors.fill: parent; onClicked: { ed_tipoValor = "PORCENTAJE"; colPct.visible=true; colMonto.visible=false } }
                        }
                        Rectangle {
                            width: 100; height: 28; radius: 14
                            color: ed_tipoValor==="MONTO" ? "#239BA7" : "#F0F0F0"
                            Text { anchors.centerIn: parent;
                                color: ed_tipoValor==="MONTO" ? "white" : "grey"
                                text:"MONTO" }
                            MouseArea { anchors.fill: parent; onClicked: { ed_tipoValor = "MONTO"; colPct.visible=false; colMonto.visible=true } }
                        }
                    }


                    // Porcentaje / Monto + Moneda
                    Row {
                        spacing: 10
                        z:1000
                        Column {
                            id: colPct; visible: ed_tipoValor==="PORCENTAJE"; spacing: 4


                            TextInputSimple {
                                id: inpPct
                                colorDeTitulo: "#333333"
                                enFocoSeleccionarTodo: true
                                textoInputBox: "0.00"
                                inputMask: "000.00%; "
                                largoMaximo: 6
                                textoTitulo: "Porcentaje:"
                                validaFormato: validacionMontoPorcentaje
                            }

                            RegExpValidator{
                                id:validacionMontoPorcentaje
                                regExp: new RegExp( "([0-1, ][0-9, ][0-9, ]\.[0-9, ][0-9, ])\%" )
                            }
                        }
                        Row{
                            spacing: 10
                            ComboBoxListaMonedas {
                                id: cmbMoneda; width: 160;

                                colorRectangulo: "#cac1bd"
                                colorTitulo: "#333333"
                                textoTitulo: "Moneda:"; botonBuscarTextoVisible: false
                                codigoValorSeleccion: modeloconfiguracion.retornaValorConfiguracion("MONEDA_DEFAULT")
                                textoComboBox: modeloListaMonedas.retornaDescripcionMoneda(cmbMoneda.codigoValorSeleccion)
                                visible: colMonto.visible
                                z:1000
                                onCodigoValorSeleccionChanged: if (ed_moneda !== codigoValorSeleccion) ed_moneda = codigoValorSeleccion
                            }
                            Column {
                                id: colMonto;
                                visible: {
                                    if(ed_tipoValor==="MONTO"){
                                        true
                                    }else{
                                        false
                                    }

                                }



                                TextInputSimple {
                                    id: inpMonto
                                    colorDeTitulo: "#333333"
                                    enFocoSeleccionarTodo: true
                                    textoInputBox: "0.00"

                                    inputMask: "0000000.00; "
                                    largoMaximo: 6
                                    textoTitulo: "Monto:"

                                }

                            }
                            CheckBox {
                                id: chkaplicaSobrePrecioUnitario
                                textoValor: "Aplica sobre Precio Unitario"
                                chekActivo: ed_aplicaSobrePrecioUnitario
                                visible: {
                                    ed_tipo==="RECARGO"?true:false
                                }

                                colorTexto: "#333333"
                                onChekActivoChanged: {
                                    ed_aplicaSobrePrecioUnitario = chekActivo;
                                    //  nuevoEstadochkSistenaAdmiteVerDocumentosAnterioresA6meses=chekActivo
                                    //  cuadroAutorizacionConfiguracion.evaluarPermisos("permiteAutorizarConfiguraciones")
                                }
                            }
                        }


                    }

                    // Rangos de FECHA
                    Rectangle {
                        enabled: {
                             if(ed_id!==-1){
                                 true
                             }else{
                                 false
                             }
                        }
                        opacity: {
                            if(ed_id!==-1){
                                1
                            }else{
                                0.5
                            }
                        }

                        id: recFechas; radius: 4; color: "#fafafa"; border.color: "#e0e0e0"; height: 199
                        anchors.left: parent.left; anchors.right: parent.right

                        property variant listaFechasModel: []

                        Column {
                            anchors.fill: parent; anchors.margins: 10; spacing: 6
                            Text { text:"Rango de fechas:"; color:"#2a91b8"; font.bold: true }
                            Row {
                                spacing: 6

                                TextInputSimple {
                                    id: dtDesde
                                    colorDeTitulo: "#333333"
                                    enFocoSeleccionarTodo: true
                                    textoInputBox: funcionesmysql.fechaDeHoy()
                                    validaFormato: validacionFecha
                                    botonBuscarTextoVisible: false
                                    inputMask: "nnnn-nn-nn; "
                                    textoTitulo: "Desde:"
                                    visible:true

                                }

                                RegExpValidator{
                                    id:validacionFecha
                                    ///Fecha AAAA/MM/DD
                                    regExp: new RegExp("(20|  |2 | 2)(0[0-9, ]| [0-9, ]|1[0123456789 ]|2[0123456789 ]|3[0123456789 ]|4[0123456789 ])\-(0[1-9, ]| [1-9, ]|1[012 ]| [012 ])\-(0[1-9, ]| [1-9, ]|[12 ][0-9, ]|3[01 ]| [01 ])")
                                }

                                TextInputSimple {
                                    id: dtHasta
                                    colorDeTitulo: "#333333"
                                    enFocoSeleccionarTodo: true
                                    textoInputBox: funcionesmysql.fechaDeHoy()
                                    validaFormato: validacionFecha
                                    botonBuscarTextoVisible: false
                                    inputMask: "nnnn-nn-nn; "
                                    textoTitulo: "Hasta:"
                                    visible:true

                                }



                                // Agregar
                                Rectangle {
                                    width: 92; height: 26; radius: 6; color: "#2a91b8"; border.color: "#0f4c7d"
                                    Text { anchors.centerIn: parent; color: "white"; text: "Agregar" }
                                    MouseArea { anchors.fill: parent
                                        onPressed: parent.opacity = 0.8; onReleased: parent.opacity = 1.0
                                        onClicked: { modeloDescuentos.agregarRangoFecha(ed_id, dtDesde.textoInputBox, dtHasta.textoInputBox); refrescarRangosFechas() } }
                                }
                                // Eliminar
                                Rectangle {
                                    width: 192; height: 26; radius: 6; color: "#a32c2c"; border.color: "#6d1b1b"
                                    Text { anchors.centerIn: parent; color: "white"; text: "Eliminar rangos" }
                                    MouseArea { anchors.fill: parent
                                        onPressed: parent.opacity = 0.8; onReleased: parent.opacity = 1.0
                                        onClicked: {
                                            if(ed_id!==-1){
                                                modeloDescuentos.eliminarRangoFechas(ed_id); refrescarRangosFechas();
                                            }
                                        }
                                    }
                                }
                            }

                            ListView {
                                id: lvFechas; clip: true;
                                anchors { left: parent.left; right: parent.right; bottom: parent.bottom
                                    top:parent.top
                                }
                                anchors.topMargin: 60
                                model: recFechas.listaFechasModel
                                delegate: Rectangle {
                                    width: lvFechas.width; height: 28; color: index%2 ? "#ffffff" : "#fbfbfb"; border.color: "#eeeeee"
                                    Row { anchors.fill: parent; anchors.margins: 6; spacing: 8
                                        Text{
                                            text:" * "
                                            color: "#5D866C"
                                        }
                                        Text {
                                            font.bold: true
                                            color: "#34656D"
                                            font.italic: true
                                            text: (modelData && (modelData.fecha_desde || modelData.fechaDesde)) ? ("" + (modelData.fecha_desde || modelData.fechaDesde)) : "" }
                                        Text{
                                            text:" <  -  > "
                                            color: "#5D866C"
                                        }
                                        Text {
                                            color: "#34656D"
                                            font.bold: true
                                            font.italic: true
                                            text: (modelData && (modelData.fecha_hasta || modelData.fechaHasta)) ? ("" + (modelData.fecha_hasta || modelData.fechaHasta)) : "" }


                                        BotonBarraDeHerramientas {
                                            id: botonEliminarFechaRango
                                            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
                                            toolTip: "Eliminar Rango fecha"
                                            anchors.verticalCenter: parent.verticalCenter
                                            width: 16
                                            height: 16
                                            z: 6
                                            onClic: {
                                                lvFechas.currentIndex = index
                                                var sel = lvFechas.currentIndex; if (sel >= 0) {
                                                    var row = lvFechas.model[sel];
                                                    modeloDescuentos.eliminarRangoFecha(row.id); refrescarRangosFechas();
                                                }

                                            }
                                        }

                                    }
                                }
                            }

                        }
                    }

                    // DÍAS + horarios
                    Rectangle {
                        enabled: {
                             if(ed_id!==-1){
                                 true
                             }else{
                                 false
                             }
                        }
                        opacity: {
                            if(ed_id!==-1){
                                1
                            }else{
                                0.5
                            }
                        }
                        id: recDiasHoras; radius: 4; color: "#fafafa"; border.color: "#e0e0e0"; height: 230
                        anchors.left: parent.left; anchors.right: parent.right
                        property variant diasSeleccion: [false,false,false,false,false,false,false]
                        property variant listaHorariosModel: []

                        Column {
                            anchors.fill: parent; anchors.margins: 10; spacing: 6
                            Text { text:"Días de semana:"; color:"#2a91b8"; font.bold: true }
                            Row {
                                spacing: 6
                                Repeater {
                                    model: ["Dom","Lun","Mar","Mié","Jue","Vie","Sáb"]
                                    Rectangle {
                                        width: 48; height: 24; radius: 12
                                        color: recDiasHoras.diasSeleccion[index] ? "#2a91b8" : "#d0d8de"
                                        Text { anchors.centerIn: parent; color: "white"; text: modelData }
                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: {
                                                var a = recDiasHoras.diasSeleccion; a[index] = !a[index]; recDiasHoras.diasSeleccion = a
                                                if (a[index]) modeloDescuentos.agregarDiaSemana(ed_id, index+1)
                                                else          modeloDescuentos.eliminarDiaSemana(ed_id, index+1)
                                            }
                                        }
                                    }
                                }
                            }
                            Text { text:"Rango de horas:"; color:"#2a91b8"; font.bold: true }
                            Row {
                                spacing: 6

                                /*Text { text:"Desde"; anchors.verticalCenter: parent.verticalCenter }
                                Rectangle { width: 90; height: 24; radius: 4; color: "#fff"; border.color: "#d0d0d0"
                                    TextInput { id: hhDesde; anchors.fill: parent; anchors.margins: 4; text: "" } }
                                */

                                TextInputSimple {
                                    id: hhDesde
                                    colorDeTitulo: "#333333"
                                    enFocoSeleccionarTodo: true
                                    textoInputBox: "09:00"
                                    validaFormato: validacionHoraHHMM
                                    botonBuscarTextoVisible: false
                                    inputMask: "nn:nn; "
                                    textoTitulo: "Desde:"
                                    visible:true

                                }
                                TextInputSimple {
                                    id: hhHasta
                                    colorDeTitulo: "#333333"
                                    enFocoSeleccionarTodo: true
                                    textoInputBox: "18:00"
                                    validaFormato: validacionHoraHHMM
                                    largoMaximo: 5
                                    botonBuscarTextoVisible: false
                                    inputMask: "nn:nn; "
                                    textoTitulo: "Hasta:"
                                    visible:true
                                    onTextoCambia: {

                                    }

                                }

                                RegExpValidator {
                                    id: validacionHoraHHMM
                                    // Acepta: "  :  ", "1 :  ", "12:  ", "12:3 ", "12:34"
                                    // Rango final válido: 00–23 para HH y 00–59 para MM
                                    regExp: new RegExp("^([01 ][0-9 ]|2[0-3 ]):([0-5 ][0-9 ])$")
                                }



                                // Agregar horario
                                Rectangle {
                                    width: 92; height: 26; radius: 6; color: "#2a91b8"; border.color: "#0f4c7d"
                                    Text { anchors.centerIn: parent; color: "white"; text: "Agregar" }
                                    MouseArea { anchors.fill: parent
                                        onPressed: parent.opacity = 0.8; onReleased: parent.opacity = 1.0
                                        onClicked: { modeloDescuentos.agregarHorario(ed_id, normalizarHora(hhDesde.textoInputBox), normalizarHora(hhHasta.textoInputBox)); refrescarHorarios() } }
                                }
                                // Eliminar horario
                               /* Rectangle {
                                    width: 92; height: 26; radius: 6; color: "#a32c2c"; border.color: "#6d1b1b"
                                    Text { anchors.centerIn: parent; color: "white"; text: "Eliminar" }
                                    MouseArea { anchors.fill: parent
                                        onPressed: parent.opacity = 0.8; onReleased: parent.opacity = 1.0
                                        onClicked: {
                                            var s = lvHoras.currentIndex; if (s >= 0) {
                                                var r = lvHoras.model[s]; modeloDescuentos.eliminarHorario(r.id); refrescarHorarios();
                                            }
                                        } }
                                }*/

                                // Eliminar
                                Rectangle {
                                    width: 192; height: 26; radius: 6; color: "#a32c2c"; border.color: "#6d1b1b"
                                    Text { anchors.centerIn: parent; color: "white"; text: "Eliminar rangos" }
                                    MouseArea { anchors.fill: parent
                                        onPressed: parent.opacity = 0.8; onReleased: parent.opacity = 1.0
                                        onClicked: {
                                            if(ed_id!==-1){
                                                modeloDescuentos.eliminarRangoHoras(ed_id); refrescarHorarios();
                                            }
                                        }
                                    }
                                }
                            }




                            ListView {
                                id: lvHoras; clip: true;
                                anchors { left: parent.left; right: parent.right; bottom: parent.bottom
                                    top:parent.top
                                }
                                anchors.topMargin: 115
                                model: recDiasHoras.listaHorariosModel
                                delegate: Rectangle {
                                    width: lvHoras.width; height: 28; color: index%2 ? "#ffffff" : "#fbfbfb"; border.color: "#eeeeee"
                                    Row { anchors.fill: parent; anchors.margins: 6; spacing: 8
                                        Text{
                                            text:" * "
                                            color: "#5D866C"
                                        }
                                        Text {
                                            font.bold: true
                                            color: "#34656D"
                                            font.italic: true
                                            text: (modelData && (modelData.hora_desde || modelData.horaDesde)) ? ("" + (modelData.hora_desde || modelData.horaDesde)) : "" }
                                        Text{
                                            text:" <  -  > "
                                            color: "#5D866C"
                                        }
                                        Text {
                                            color: "#34656D"
                                            font.bold: true
                                            font.italic: true
                                            text: (modelData && (modelData.hora_hasta || modelData.horaHasta)) ? ("" + (modelData.hora_hasta || modelData.horaHasta)) : "" }

                                        BotonBarraDeHerramientas {
                                            id: botonEliminarHoraRango
                                            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/BorrarCliente.png"
                                            toolTip: "Eliminar Rango fecha"
                                            anchors.verticalCenter: parent.verticalCenter
                                            width: 16
                                            height: 16
                                            z: 6
                                            onClic: {
                                                lvHoras.currentIndex = index
                                                var sel = lvHoras.currentIndex; if (sel >= 0) {
                                                    var row = lvHoras.model[sel];
                                                    modeloDescuentos.eliminarRangoHora(row.id); refrescarHorarios();
                                                }

                                            }
                                        }


                                    }
                                }
                            }




                        }
                    }
                }
            }

            // Botonera fija (siempre visible)
            Row {
                id: btnRow; spacing: 10
                anchors.right: parent.right; anchors.bottom: parent.bottom; anchors.margins: 12

                // Nuevo
                Rectangle {
                    width: 92; height: 26; radius: 6; color: "#2a91b8"; border.color: "#0f4c7d"
                    Text { anchors.centerIn: parent; color: "white"; text: "Nuevo" }
                    MouseArea { anchors.fill: parent; onPressed: parent.opacity = 0.8; onReleased: parent.opacity = 1.0; onClicked: limpiarFormulario() }
                }
                // Guardar
                Rectangle {
                    width: 92; height: 26; radius: 6; color: guardarHabilitado ? "#2a91b8" : "#9aa3a8"; border.color: "#0f4c7d"
                    Text { anchors.centerIn: parent; color: "white"; text: "Guardar" }
                    MouseArea { anchors.fill: parent; enabled: guardarHabilitado
                        onPressed: if (enabled) parent.opacity = 0.8
                        onReleased: parent.opacity = 1.0
                        onClicked: if (enabled) guardarActual() }
                }
                // Eliminar
                Rectangle {
                    width: 92; height: 26; radius: 6; color: "#a32c2c"; border.color: "#6d1b1b"
                    Text { anchors.centerIn: parent; color: "white"; text: "Eliminar" }
                    MouseArea { anchors.fill: parent; onPressed: parent.opacity = 0.8; onReleased: parent.opacity = 1.0; onClicked: if (ed_id > 0) dlgConfirm.visible = true }
                }
            }
        }
    }

    // Confirmación de borrado
    Rectangle {
        id: dlgConfirm; visible: false
        anchors.centerIn: parent; width: 360; height: 160; radius: 8
        color: "white"; border.color: "#cccccc"
        Column {
            anchors.fill: parent; anchors.margins: 16; spacing: 12
            Text { text: "¿Eliminar el descuento/recargo actual?"; wrapMode: Text.WordWrap; color: "#333" }
            Row {
                spacing: 8; anchors.right: parent.right
                Rectangle { width: 92; height: 26; radius: 6; color: "#9aa3a8"; border.color: "#666"
                    Text { anchors.centerIn: parent; color: "white"; text: "Cancelar" }
                    MouseArea { anchors.fill: parent; onClicked: dlgConfirm.visible = false } }
                Rectangle { width: 92; height: 26; radius: 6; color: "#a32c2c"; border.color: "#6d1b1b"
                    Text { anchors.centerIn: parent; color: "white"; text: "Eliminar" }
                    MouseArea { anchors.fill: parent; onClicked: {
                            modeloDescuentos.eliminar(ed_id);
                            dlgConfirm.visible = false;
                            modeloDescuentos.buscarDescuentosRecargos("", "", false);
                            limpiarFormulario();
                        }} }
            }
        }
    }

    // Init
    Component.onCompleted: {
        // if (typeof modeloListaDescuentosRecargos !== "undefined")
        //     modeloDescuentos = modeloListaDescuentosRecargos;

        if (typeof modeloconfiguracion !== "undefined" &&
                typeof modeloconfiguracion.retornaValorConfiguracion === "function") {
            defaultMoneda = Number(modeloconfiguracion.retornaValorConfiguracion("MONEDA_DEFAULT")) || 0
        }
        if (ed_moneda<=0 && defaultMoneda>0) ed_moneda = defaultMoneda
        if (modeloDescuentos && modeloDescuentos.buscarDescuentosRecargos)
            modeloDescuentos.buscarDescuentosRecargos("", "", false)
        inpPct.textoInputBox   = ed_porcentaje.toFixed(2)
        inpMonto.textoInputBox = ed_monto.toFixed(2)

        if (cmbMoneda){

            cmbMoneda.codigoValorSeleccion = ed_moneda
            cmbMoneda.textoComboBox= modeloListaMonedas.retornaDescripcionMoneda(cmbMoneda.codigoValorSeleccion)
    }

        console.log("[lista] model conectado?", !!lista.model);
        console.log("[lista] count inicial:", lista.count);

    }
}
