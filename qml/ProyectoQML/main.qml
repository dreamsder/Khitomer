/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2023>  <Cristian Montano>

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

import QtQuick 1.1
import "Controles"
import "Listas"


Rectangle {
    id: rectPrincipal
    width: 900; height: 600
    //color: "#041c24"
    color: "#000000"
    clip: true

    property int   opcionEnCurso: 0
    property bool  estadoConexionMysql: true
    property bool  estadoConexionServidor: true

    property string versionKhitomer: "1.17.23"


    /// 1.2.0: Se habilita el calculo de totales si el modo de configuración esta setado para
    ///        que el articulo no tenga iva incluido.
    /// 1.2.1: Se agrega el control para la conexión a la base de datos, antiguamente sin el control, no cerraba la conexion.
    /// 1.2.2: Se modifica la inserción de las lineas de documento para hacerlas por lote, en lugar de linea por linea,
    ///        esto aumenta la velocidad drasticamente y previene los errores. Ademas se cambio la visualización de la carga
    ///        rapida de precios.
    /// 1.2.3: Se finaliza el modudo de descuentos al total, y se implementa un cuadro de autorizaciones.
    /// 1.2.4: Se realiza la correción del guardado de items de factura, cuando el documento no tiene item.
    /// 1.2.5: Se agrega soporte a la base de datos para el campo direccionWeb. Se agregan 3 reportes de cuentas bancarias.
    ///        Se agrega soporte para monedas y cuentas bancarias en los reportes. Se agrega un reporte de ventas totales.
    /// 1.2.6: Se realizó la corrección de todos los reportes de ventas. Se agrego un nuevo parametro a los tipos de documentos(esdocumentoDeVenta).
    /// 1.2.7: Se arreglan los indices para que sea mas efectivas las consultas a la base de datos.
    ///        Se cambia el nombre del menú de administración: Reportes por Mantenimientos.
    /// 1.2.8: Se agregan nuevos indices para mejorar la velocidad del sistema.
    ///        Se cambia el sitio de la configuración del sistema de /opt/Khitomer a $home/.config/Khitomer
    /// 1.3.0: Se finaliza el soporte para graficas estadisticas.
    ///        Se arregla error en el manejo de los botones de bajar y subir la lista en cambio rapido de precios.
    ///        Se quita el indicador de menú donde estamos parados, para hacerlo mas realista a los permisos que tengamos.
    ///        Se agrega el mantenimiento de tipo de documentos. Se arregla la busqueda del proveedores en los reportes.
    ///        Se cambia algunos textos al tipo de letra Arial, remplazando a Arial.
    ///        Se agrega un nuevo control (ComboBoxCheckBoxGenerico). Se agrega en le mantenimiento de permisos la posibilidad
    ///        de asignar los doucmentos que va a usar cada perfil del sistema.
    /// 1.3.1: Se corrige el cierre de opciones extras en mantenimiento facturacion, cuando se pide autorizar un descuento al total.
    ///        Se corrige un error en los permisos de los tipos de documento por perfil, para el mantenimeinto de documentos y liquidaciones.
    /// 1.3.2: Se agrega el campo subtotalsindescuento en la base de datos, y en la impresión. Se corrige en la impresión que salga 0.00 cuando el monto es vacio.
    ///        Se agrega el redondeo en las facturas, configurable desde los tipos de documentos.
    /// 1.4.0: Se agrega un nuevo combobox en el mantenimiento de facturacion para fijar el precio del articulo a vender.
    ///        Se modifican algunos combobox para soportar scrollbars. Se agregan nuevos reportes para clientes y proveedores.
    ///        Se vuelve a habilitar el manejo de stock cuando se guarda una factura. Se calcula el stock y se guarda la bandera en la tabla FaltaStock por artículo.
    /// 1.4.1: Se corrige un error si varios equipos creaban al mismo tiempo una factura, cuando el sistema numera automaticamente.
    /// 1.5.0: Se agrega control en facturación para guardar el costo del articulo.
    ///        Se agrega soporte para tamaño de fuente en la impresión de las facturas por tipo de linea.
    ///        Se agrega busqueda por observaciones en el mantenimiento de los documentos.
    ///        Se agregan reportes de saldos por cuenta corriente por cliente y moneda y por proveedor y moneda.
    ///        Se agrega control de cantidad de lineas en la facturacion por tipo de documento.
    ///        Se agrega reporte de stock segun costo.
    /// 1.5.1: Se corrige el separador de item factura para mostrar el costo.
    ///        Se agrego en el item del articulo información de costo en moneda referencia, y costo en origen
    /// 1.6.0: Se implementa el soporte para el mantenimiento de cuentas corrientes dinero.
    ///        Se agregaron nuevos reportes de cuenta corriente para contemplar las nueva funcionalidad.
    ///        Se agregaron formas de pago para seleccionar antes de emitir una factura.
    ///        Los medios de pago ahora afectan el iva y los subtotales
    ///        Se agrego un nuevo parametro en la configuracion donde se indica el iva por defecto del sistema para los medios de pago.
    ///        En el mantenimiento de facturacion, el campo de precio manual unitario, se rellena con el precio que corresponda para el articulo.
    /// 1.7.0: Se agrega la posibilidad de devolver un documento, hacer un documento contrario al ya facturado.
    ///        Se agrega la posibilidad de debitar el monto de un documento con cuenta corriente positivo a las facturas con deudas del cliente.
    ///        Se corrge la validacion de fecha/hora para quitar las z que componian el validador. Se agrega new reg para arreglar le validador.
    /// 1.8.0: Se agrega soporte para calculo de costo ponderado segun stock, cuando se graba una linea de compra de una factura compra provededor.
    /// 1.8.1: Se implemento un parametro de configuracion, el cual anula el uso de autorizaciones. Este parametro es superior jerarquicamente a los permisos del perfil de usuarios.
    /// 1.8.2: Se implemento el redondeo segun la moneda del documento. Esto aún no es configurable por interfaz grafica, pero si desde la base de datos.
    /// 1.9.0: Se agrega control en la anulación de documentos que pagaron cuenta corriente. Se corrige problema al ingresar documento que pide articulos y medios de pago, si no se ingresan articulos, el medio de pago impacta sus totales en los totales del documento.
    /// 1.9.1: Se agrego la posibilidad de order la lista de articulo al imprimirse tal cual se armo la factura. Por defecto el documento agrupa los items, pero con el valor en 1, los imprime tal cual salieron.
    /// 1.9.2: Se corrige un problema con el ingreso de cantidad, cuando esta habilitado el campo de de codigo de barras a demanda.
    ///        Soporte para consultas sql del cabezal del reporte.
    /// 1.9.3: Se arregla la busqueda inteligente para que sea mas rapida, separando los tipos de listas a independientes.
    ///        Se corrigen los campos de entrada de información para que la pantalla no quede en negro cuando volvemos a tomar el control del campo.
    /// 1.10.0:Se arreglan problemas en los combobox de rubros y sub rubros.
    ///        Se finaliza el soporte para deudas en medios de pago, de pagos contados.
    ///        Se agrega reporte Facturas con deuda de Medios de Pago y una nueva Configuracion para manejar porcentajes de deuda minima en contados con medios de pago.
    /// 1.10.1:Se realizo corrección sobre la eliminación de clientes que tenian una factura ya emitida. El sistema permitia eliminar estos clientes por error.
    ///        Se agrego el reporte Stock por proveedor, que ademas muetsra costo y fechas de venta entre otras cosas.
    ///        Se modificaron los reportes de ventas por vendedor para comisiones, se le quito el nombre del vendedor y se puso el del cliente; se le agrego un cabezal con el vendedor.
    /// 1.10.2:Se corrige un error en el campo de facturación del dato comodin.
    /// 1.10.3:Cambios en varios reportes para Orion. Se agrega reporte de ventas detalladas sin impuestos.
    /// 1.11.0:Se cambia la forma de asignar listas de precios a clientes y proveedores.
    ///       :Se realizan correcciones en el control ComboBoxCheckBoxGenerico.
    ///       :Se corrige un error grabe en el guardado de documentos, que permitia que se actualizaran documentos emitidos y guardados.
    ///       :Se mejora el combobox de cheques diferidos para que muestre barra de desplazamiento y se ajuste su tamaño.
    /// 1.12.0:Se mejora el combobox de localides para que sea mas inteligente
    ///       :Se le agrega a los textinpux simples la capacidad de adaptarse en tamaño segun texto y titulo.
    ///       :Se agrega al mantenimiento de listas de precios la posibilidad de imprimir un listida en formato duplex.
    ///       :Se modifica la forma de guardar las listas de precios para que sean mas rapidas.
    /// 1.12.1:Se corrige la impresión del formato duplex de listas de precios.
    /// 1.12.2:Se realiza una nueva corrección de la impresión del formato duplex de listas de precios.
    /// 1.12.3:Se corrige la devolucion de documentos.
    /// 1.12.4:Se corrigen reportes y se da un nuevo look a algunos dialogos. Ademas se termina la implemnetación de la impreción duplex de lista de precios.
    /// 1.12.5:Se agrega un nuevo reporte llamado Saldo Total de clientes por moneda y se agrega el vendedor automatico al hacer devolucion completa o seleccionar facturar con deuda.
    ///       :Se agrega una nueva opción en los tipos de documentos para que un documento no afecte el IVA
    /// 1.12.6:Se agrega un nuevo reporte llamado Ventas entre fechas por rubro y lista de precio
    /// 1.12.7:Se agrega un nuevo reporte llamado Articulos sin venta por rubro entre fechas.
    ///       :Se arregla un error cuando una venta tiene descuento y se hace una devolución, pero el documento de devolución no tenia el campo descuento activo.
    ///       :Se agrega una nueva funcionalidad que permite modificar el precio de un articulo en las listas de precios, cuando se esta facturando un documento; por ejemplo una factura compra proveedor.
    ///       :Se agrega en las busquedas avanzadas un checkbox para los articulo que permite se listen los inactivos. Por defecto no se listan.
    /// 1.12.8:Se realiza corrección en los 3 reportes de ranking.
    /// 1.12.9:Se modifica el orden de muestra de los articulos desde hasta en el filtro de cambios rapido de precios en las listas de precios a pedido de Jaime Magariños ya que usa artículos con codigo numerico.
    ///       :Se modifica el orden de los artículo en el filtro de mas articulos en la facturación a pedido de Jaime Magariños.
    ///       :Se modifica el orden de los proveedores en la lista desplegable en el mantenimiento de Artículos a pedido de Jaime Magariños.
    /// 1.12.10:Se amplia el campo cantidad en las facturas a 5 digitos.
    ///       :Se modifican los reportes Stock por Proveedor, Lista de clientes y Stock Total Real.
    ///       :Se modifica la salida de los reportes por impresora para que se aproveche mejor la hoja total.
    /// 1.12.11:Se agrega soporte para 4 decimales en los montos.
    ///       :Se modifica la lectura de la configuración para que no tenga que establecer una conexion a la base de datos cada vez.
    ///       :Se agrega un nuevo reporte llamado "Ventas de clientes entre fechas por clasificación"
    /// 1.12.12:Corrección de error en campo totales con 4 digitos en la impresión.
    /// 1.12.13:Nuevo reporte llamado Ventas de clientes entre fechas por lista de precio
    ///        :Se agrego un nuevo cuadro de dialogo que permite seleccinar el proximo tipo de documento. Depende de configuación.
    /// 1.12.14:Se agrega un nuevo parametro para la cantidad de decimales en la impreción.
    ///        :Se agrega soporte en los permisos para habilitar o deshabilitar reportes por perfil.
    ///        :Se modifica el ingreso a la aplicación para que si necesita configuración, la misma aplicación provea una interfaz sin tener que recurrir a otra aplicación externa.
    ///        :Se agrega un nuevo reporte llamado Balance por moneda y lista de precio a pedido de Jaime Magariños.
    /// 1.12.15:Se arregla error de control de stock bajo minimo en las anulaciones de documentos.
    ///        :Se modifica el control ComboBoxCheckBoxGenerico para que pueda mostras una seguna fila de información.
    ///        :Se agrega un nuevo reporte llamado Balance por moneda y lista de precio detallado para Jaime Magariños.
    ///        :Se agrega un nuevo reporte llamado Ventas entre fechas detallado por tipo documento para Jaime Magariños.
    ///        :Se agrega un nuevo reporte llamado Ventas por documento con detalle medios de pago para Digital World.
    /// 1.12.16:Corrección de error en perfiles al listar los tipos de documentos.
    ///        :Se modifica el reporte Balance por moneda y lista de precio detallado para que muestre nombre de articulos.
    /// 1.12.17:Se agrego una primera etapa de logueo de información de facturación, para detectar problemas.
    ///        :Se realiza corrección al agregar un artículo a la factura cuando el campo cantidad esta inactivo.
    ///        :Se agrego la fecha de emision del documento en el mantenimiento de documentos.
    ///        :Se realiza la modificación del icono del sistema y se agrega el icono de Qt.
    ///        :Se agrega el reporte Stock con listas de precios a pedido de Jaime Magariños.
    /// 1.12.18:Se modifica la carga de facturas pendientes para que se actualize la fecha de emision del documento a la del día.
    /// 1.12.19:Se agrega soporte para configurar los menues de administración.
    ///        :Se modofica la carga de facturas para que cuando son emitidas o guardadas se muestre siempre la fecha de emision.
    /// 1.12.20:Modificación de los permisos para permitir ocultar el menu de cuenta corriente.
    /// 1.12.21:Se agregan 2 reportes nuevos: Ventas entre fechas deta. x tipo documento y moneda, Artículos desde > hasta
    /// 1.12.22:Se agrega soporte para mostrar la descripción extendida del articulo en las lineas vendidas de facturación del mantenimiento facturación
    /// 1.12.23:Se agrega soporte para identificar al cliente segun su procedencia de llegada al comercio(Funconalidad pedida por DigitalWorld).
    /// 1.12.24:Se agrega soporte para modificar los codigos de barras de una linea de facturación ya emitida o en cualquier momento(Funconalidad pedida por DigitalWorld).
    /// 1.13.0 :Primera versión con CFE funcional via conexión empresa IMIX
    /// 1.13.1 :Se corrige un problema al guardar el cliente cuanto el campo procedencia no es visible
    /// 1.13.2 :Se agrega soporte para Enviar información de articulo y cliente en 1 para Imix, de manera opcional.
    /// 1.13.3 :Corrección de la modificación de versión 1.12.24. para modificar linea de codigos de barra.
    /// 1.13.4 :Primera versión con CFE funcional via conexión empresa Dynamia.
    /// 1.13.5 :Se finaliza implementación de CFE para Dynamia
    /// 1.13.6 :Correcciones varias sobre CFE
    /// 1.13.7 :Correcciones de codificación UTF-8 para envio datos a IMIX
    ///        :Implementación del menu administrativo Factura electronica para actualizar información rapidamente
    /// 1.13.8 :Se implementa log por medio de la interfaz grafica y se apaga la fecha para el envio de CFE Imix
    /// 1.13.9 :Corrección en el envio de información a Imix cuando hay comillas en los textos
    /// 1.13.12 :Corrección en procesamiento desde Dynamia. Agregado de campo observaciones en envio a Imix. Se agranda el tamaño de impresión de campos. Se agrega mas información para el envio a Dynamia.
    /// 1.13.13 :Se agrega soporte utf8 para CFE Dynamia
    /// 1.13.14 :Se agrega control configurable por tipo de documento para no permitir facturar con stock previsto en cero.
    ///         :Se agrega mejora en la lista de items a facturar, cuando se agfrega un nuevo item, la lista se desplaza al final.
    /// 1.14.0  :Se quitan los saltos de linea de los textos a enviar para CFE.
    ///         :Se agrega la posibilidad de intercambiar entre tipos de documentos sin perder los artículos ingresados, siempre que ambos documentos tengan configuraciones similares.
    ///         :Se cambia la forma de interactuar con los descuentos, ahora se pueden cambiar en cualquier momento de realizada la factura.
    ///         :Se agregan nuevos campos al modelos de impresión.
    /// 1.14.1  :Cambio de fecha en reporte "Saldo por cliente y moneda".
    /// 1.14.2  :Corrección en el alta de clientes, ahora se asigna un nuevo numero de cliente al guardarlo y no al crearlo.
    ///         :Se hicieron varios cambios en los tamaños y distancias de la interfaz para mejorar el contenido.
    /// 1.14.3  :Corrección en la validación de las cedulas que terminan en 0.
    /// 1.14.4  :Se corrige el problema de los descuentos en las lineas de articulos, ahora se refleja el descuento al total en cada linea del articulo. Se modifico el reporte de venta entre fechas por rubro para adecuarlo a esta nueva modalidad.
    ///         :Se agrego la posibilidad de imprimir el descuento por linea.
    /// 1.14.5  :Se agrega en todos los reportes con documentos el numero de CFE.
    ///         :Se muestra en todos los lugares que hay documentos el numero de CFE. Se permite en el manteimiento de documentos buscar por numero de CFE
    /// 1.14.6  :Se agrega soporte para e-remitos en Imix.
    /// 1.14.7  :Corrección sobre descuentos para Dynamia. Cambiar el tipo_descuento de 2 a 1 para indicar por porcentaje.
    /// 1.14.8  :Se agrega soporte para fecha de nacimiento en el mantenimiento de clientes.
    ///         :Se agrega nuevo parametro de configuración CODIGO_BARRAS_A_DEMANDA_EXTENDIDO el cual permite ingresar muchos datos en el campo codigo de barras a demanda e intercambia el ENTER por tabulación.
    /// 1.14.9  :Se realizo corrección de reporte "Saldo proveedor por moneda entre fechas".
    /// 1.14.10 :Se realizo corrección sobre control de cantidad de articulos con stock previsto, cuando se da clic en el boton signo de mas de la lista de items al facturar.
    /// 1.15.0  :Se agrega soporte para imrpesoras de ticket citizen Ct-e351 y ct-s310ii.
    ///         :Se agrego parametro de configuración DISTANCIAENTREBOTONESMENU para setear la distancia entre los botones de la barra de herramientas.
    /// 1.15.1  :Se agrega soporte para imprimir segun las cantidades de copias configuradas en los tipos de documentos.
    ///         :Se agrega información sobre la descripción a imprimir del tipo de documento en la Adenda, para saber si es contado o credito.
    /// 1.15.2  :Se llama varias veces a la busqueda de impresoras para elimianr problemas de timeout con cups ya que al iniciar el sistema operativo queda en modo zombie.
    /// 1.15.3  :Se corrige el modo impresión de ticket, para que cuando un documento no es de cfe, se imprima información del nombre del documento como salia anteriormente.
    /// 1.16.0  :Se agrega el soporte para la clave de documentos codigo, tipo y serie. GRAN CAMBIO, cuidado. Se modificaron también los reportes.
    /// 1.16.1  :Se corrige problema de carga de tarjetas pendientes de pago en el menu administración.
    /// 1.16.1  :Se corrige problema de carga de modificación de codigos de barras a demanda en una factura modificada.
    /// 1.16.2  :Correcciones varias.
    /// 1.16.3  :se agranda el campo de email. Se corrige el error de serie en cruce de cuentas corrientes.
    /// 1.16.4  :Correcciones varias.
    /// 1.16.5  :Se agrega filtro por documentos para encontrarlos por los estados del mismo a pedido de Digital World.
    ///         :Se agregan filtros por estado de documento para encontrar mas rapido los penditnes en las liquidaciones.
    ///         :Se quitan los sistemas de particulas para reducir la carga del programa.
    ///         :Se agregan las observaciones a los datos del cliente a facturar.
    /// 1.16.6  :Se corrige error de calculo de stock previsto, excluyendo al documento de compra proveedor.
    /// 1.16.7  :Se agrega la configuración para Imix del envio de codigo de articulo concatenado a la descripción del articulo.
    ///         :Se crea el parametro articuloUsaConcatenacionImix, en 0 no manda codigo, en 1 manda codigo articulo concatenado.
    /// 1.16.8  :Se agrega el soporte para ivas diferentes en IMIX. 1 - basico, 2 - excento, 3 - minimo.
    /// 1.16.9  :Se agrega parametro de CFE envioClienteGenerico, para separar el envio de articulo generico y cliente.
    /// 1.16.10 :Se agrega en la tabla Ivas información de mapeo del iva para CFE de Imix.
    /// 1.16.11 :Se agregan varios reportes para discriminar ventas por IVA.
    /// 1.16.12 :Se incorporo posibilidad de enviar la CIUDAD en la dirección por parametro general de CFE para imix.
    ///         :Se incorporo el envio del campo Adicional para Imix, donde se envia la forma de pago del documento.
    ///         :Se agrega reporte "Ventas entre fechas por rubro y lista de precio y compras"
    /// 1.16.13 :Implementación finalizada de imix_nube.
    /// 1.16.14 :Correcciones sobre comunicación de imix_nube.
    /// 1.16.15 :Cambios para adaptar el sistema a weeCommerce.
    ///         :Se creron las tablas DocumentosShipping y DocumentosBilling para sistema weeCommerce.
    /// 1.16.16 :Nuevo reporta Venta entre fechas por procedencia.
    /// 1.16.17 :Corrección en el calculo de stock por el cambio en la serie de los documentos.
    /// 1.16.18 :Se agrega el simbolo de la moneda en el total del ticket impreso.
    /// 1.16.19 :Se agregan 2 reportes a pedido de Cynthia de DigitalWorld: Ventas web entre fechas, y Ventas entre fechas por artículo y vendedor.
    ///         :Se agrega filtro para documentos web en Mantenimiento de Documentos.
    /// 1.16.20 :Se agrega soporte para clientes con credito. Si el cliente tiene marcada el combobox Puede hcaer documentos credito, podra facturar tipos de documentos credito, sino, sera solo contado.
    /// 1.16.21 :Se agrega soporte para imix Nube y facturas con iva excento. Se agrega Tabla TipoDocumentoImix para tener a mano los tipos de envios segun documento.
    ///         :Se agrega el campo Comentario en la tabla Documentos y se agrega en el mantenimiento de facturación.
    ///         :Corrección en reportes por procedencia, dado que la fecha de alta es diferente a la fecha por defecto y hay que recortarla a 10 caracteres.
    ///         :Se agregan 3 nuevos reportes para marketing a pedido de Cynthia de Digital World.
    /// 1.16.22 :Se corrige reporte de stock bajo, para que no tome inactivos.
    ///         :Se agrega un boton para guardar los comentarios en documentos emitidos.
    ///         :Se corrige error con descuento en tipo de documento devolución.
    ///         :Se corrige error en carga de cliente.
    ///         :Soporte para abrir documentos desde los reportes. La ultima columna debe tener codigoDocumento-tipoDocumento-seriesDocumento separado por guiones, y el reprte debe
    ///         :debe tener activo el parametro que indica que usa abrir documento.
    ///         :Se modifico la forma de ver los documentos con deuda de medios de pago, para evitar posibles problemas de calculo.
    ///         :Se finalizo el agregado de tipo de documento, moneda y forma de pago por defecto para los clientes.
    /// 1.16.23 :Correcciones varias.
    /// 1.16.24 :Corrección en reporte Stock bajo minimo.
    /// 1.17.0  :Se optimiza el sistema para mejorar la intensidad de consultas a la base de datos.
    ///         :Se agrega el reporte "Listado de clientes x lista precio y fecha de alta" para digital world.
    /// 1.17.1  :Corrección del sistema general.
    /// 1.17.2  :Se agrega comentario a la lista de documentos del mantenimiento.
    ///         :Se agrega busqueda por vendedor del documento o el que comisiona.
    /// 1.17.3  :Correcciones varias.
    /// 1.17.4  :Se agrega soporte para impresión de envios en las facturas pendientes.
    /// 1.17.5  :Corrección en impresión de envios.
    /// 1.17.6  :Se agrega el modo de impresión para recibos, apedido de Jaime de likaren. SOLO sirve para recibos, no para otro documento.
    /// 1.17.7  :Se corrige error en modo de impresión de recibos.
    /// 1.17.8  :Corrección en la impresión de envios.
    ///         :Corrección en el reporte Listado de clientes x lista precio y fecha de alta.
    ///         :Se agrega soporte para descuentos desde el cliente en base a un porcentaje definido en el cliente.
    /// 1.17.9  :Mas correcciónes en la impresión de envios.Se cambia el campo observacion de la factura por comentario.
    /// 1.17.10 :Mas correcciónes en la impresión de envios.
    /// 1.17.11 :Se modifican 3 reportes a pedido de Sandra de DW: Ventas entre fechas detallado / Ventas entre fechas detallo con iva / Ventas entre fechas detallo sin imp.
    ///         :Se agrega telefono 2 a reporte Listado de clientes x lista precio y fecha de alta
    /// 1.17.12 :Se modifican los reportes de Sandra para agregarle Fechas
    /// 1.17.13 :Se modifica la busqueda de stock previsto y real para que se consulte desde las tablas vistas: vStockReal vStockPrevisto
    ///         :Se agrega filtro por año y mes para el mantenimieto de documentos y las liquidaciones.
    /// 1.17.14 :Se corrige reporte de ventas detalladas.
    /// 1.17.15 :Se optimiza la busqueda de stock.
    /// 1.17.16 :Se arregla error en carga de perfiles.
    ///         :Se incorpora reporte Formulario 2181 para DGI y se incorpora soporte para exportar reportes como CSV.
    /// 1.17.17 :Se implementa nueva forma de cargar el stock real y previsto para hacer mas rapido el programa, por medio de tablas de sumario.
    ///         :Se habilitan los event schedule en mysql.
    /// 1.17.18 :Se implementa nueva forma de controlar la cantidad de documentos, con la confguracion: MODO_DOCUMENTOS_VISIBLES
    /// 1.17.19 :Se reconfigura la opción de MODO_DOCUMENTOS_VISIBLES para que por defecto puedan ver hasta 1 años hacia atras.
    ///         :Se modifica el reporte Listado de clientes x lista precio y fecha de alta para agrgarle información del cumpleaños del cliente.
    ///         :Se agrega reporte Documentos que afectan en negativo por fecha, a pedido de Digital World
    /// 1.17.20 :Se ajusta el event schelude del stock a 1 minuto. Se modifica la busqueda de articulos en la facturación para que el stock se muestre el real, como era originalmente.
    ///         :Se ajusta el tamaño de los font para trabajarlos desde una variable unica en el main.qml
    /// 1.17.21 :Corrección en el Formulario de DGI 2181, ya que se mostraba el subtotal y no solo el iva.
    ///         :Corrección en reporte Documentos que afectan en negativo por fecha, para que solo tome documentos con medios de pago.
    ///         :Se agrega reporte "Información de clientes entre fechas" a pedido de digital world, es el mismo reporte que se envia mensualmente de los clientes, pero entre fechas.
    /// 1.17.22 :Se corrige reporte Informaciòn de clientes entre fechas, agregado telefono 2.
    /// 1.17.23 :Se modifica el orden de información de documentos en el mantenimiento de documentos a fecha de emision del documento. Antes estaba por fecha de ultima modificación.


    ///property para tamaño de fuentes
    property int sizeTagsInferiores: 15
    property int sizeTitulosControles: 13


    property bool mODO_DOCUMENTOS_VISIBLES: modeloconfiguracion.retornaValorConfiguracionBooleano("MODO_DOCUMENTOS_VISIBLES")
    property bool visualizarDocumentosEnmODO_DOCUMENTOS_VISIBLES: false

    property int distanciaEntreBotonesBarraDeTareas: modeloconfiguracion.retornaValorConfiguracion("DISTANCIAENTREBOTONESMENU")

    // setea los permisos de la barra de herramientas del mantenimiento de liquidaciones
    function permisosMantenimientoLiquidaciones(){
        mantenimientoLiquidaciones.botonNuevaLiquidacionVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearLiquidaciones");
        mantenimientoLiquidaciones.botonCrearLiquidacionVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearLiquidaciones");
        mantenimientoLiquidaciones.botonEliminarLiquidacionVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteBorrarLiquidaciones");
    }
    // setea los permisos de la barra de herramientas del mantenimiento de facturacion
    function permisosMantenimientoFacturacion(){
        mantenimientoFactura.botonNuevaFacturaVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearFacturas");
        mantenimientoFactura.botonGuardarFacturaEmitirVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearFacturas");
        mantenimientoFactura.botonGuardarFacturaPendienteVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearFacturas");


        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CLIENTE")=="1"){
            mantenimientoFactura.codigoClienteInputMask="000000;"
            mantenimientoFactura.codigoClienteOpcionesExtrasInputMask="000000;"

        }else{
            mantenimientoFactura.codigoClienteInputMask=""
            mantenimientoFactura.codigoClienteOpcionesExtrasInputMask=""
        }


        mantenimientoFactura.setearVerificoEstadoActivoBotonesGuardar()




    }
    // setea los permisos de la barra de herramientas del mantenimiento de articulos
    function permisosMantenimientoArticulos(){
        mantenimientoArticulos.botonNuevoArticuloVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearArticulos");
        mantenimientoArticulos.botonGuardarArticuloVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearArticulos");
        mantenimientoArticulos.botonEliminarArticuloVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteBorrarArticulos");
        if(modeloconfiguracion.retornaValorConfiguracion("MODO_ARTICULO")=="1"){
            mantenimientoArticulos.codigoArticuloInputMask="000000;"
        }else{
            mantenimientoArticulos.codigoArticuloInputMask=""
        }
    }
    // setea los permisos de la barra de herramientas del mantenimiento de clientes
    function permisosMantenimientoClientes(){
        mantenimientoClientes.botonNuevoClienteVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearClientes");
        mantenimientoClientes.botonGuardarClienteVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearClientes");
        mantenimientoClientes.botonEliminarClienteVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteBorrarClientes");
        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CLIENTE")=="1"){
            mantenimientoClientes.codigoClienteInputMask="000000;"
        }else{
            mantenimientoClientes.codigoClienteInputMask=""
        }



    }



    // setea los permisos de la barra de herramientas del mantenimiento de lista de precios
    function permisosMantenimientoListaDePrecios(){
        mantenimientoListaPrecios.botonNuevaListaDePrecioVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearLiquidaciones");
        mantenimientoListaPrecios.botonGuardarListaDePrecioVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCrearLiquidaciones");
        mantenimientoListaPrecios.botonEliminarListaDePrecioVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteBorrarLiquidaciones");
        mantenimientoListaPrecios.botonCambioRapidoDePreciosVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteCambioRapidoDePrecios");
        if(modeloconfiguracion.retornaValorConfiguracion("MODO_ARTICULO")=="1"){
            mantenimientoListaPrecios.codigoArticuloDesdeHastaCuadroListaPrecioInputMask="000000;"
        }else{
            mantenimientoListaPrecios.codigoArticuloDesdeHastaCuadroListaPrecioInputMask=""
        }


    }

    // setea los permisos del mantenimiento de reportes
    function permisosMantenimientoReportes(){
        mantenimientoReportes.botonGenerarPDFVisible=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteExportarAPDF");
        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CLIENTE")=="1"){
            mantenimientoReportes.codigoCodigoClienteReporteInputMask="000000;"
            mantenimientoReportes.codigoCodigoProveedorReporteInputMask="000000;"
        }else{
            mantenimientoReportes.codigoCodigoClienteReporteInputMask=""
            mantenimientoReportes.codigoCodigoProveedorReporteInputMask=""
        }
        if(modeloconfiguracion.retornaValorConfiguracion("MODO_ARTICULO")=="1"){
            mantenimientoReportes.codigoArticuloReporteInputMask="000000;"
        }else{
            mantenimientoReportes.codigoArticuloReporteInputMask=""
        }


    }


    // setea los permisos del mantenimiento de reportes
    function permisosMantenimientoCuentacorriente(){

        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CLIENTE")=="1"){
            mantenimientoCuentasCorriente.codigoClienteInputMask="000000;"
        }else{
            mantenimientoCuentasCorriente.codigoClienteInputMask=""
        }
    }



    function setearTipoDocumentoEnMantenimientoFacturacion(_codigoTipoDeDocumento,_observacionesRecabadas){
        mantenimientoFactura.setearTipoDeDocumento(_codigoTipoDeDocumento,_observacionesRecabadas)
    }

    function mostrarMantenimientos(posicion,lado){

        if(posicion==0){

            if(lado=="home"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarLiquidaciones")){

                    permisosMantenimientoLiquidaciones()
                    mantenimientoLiquidaciones.enabled=true
                    mantenimientoLiquidaciones.visible=true

                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false

                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false

                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false

                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false

                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=0

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0

                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    modeloListaVendedores.clearUsuarios()
                    modeloListaVendedores.buscarUsuarios("esVendedor=","1")

                }else if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarFacturacion")){

                    permisosMantenimientoFacturacion()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=true
                    mantenimientoFactura.visible=true

                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=1

                    modeloLiquidacionesComboBox.clearLiquidaciones()
                    modeloLiquidacionesComboBox.buscarLiquidacion("1=","1")

                    modeloListaVendedores.clearUsuarios()
                    modeloListaVendedores.buscarUsuarios("esVendedor=","1")


                    btnLateralBusquedas.z=0
                    rowMenusDelSistema.z=-1
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")


                }else if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarClientes")){
                    mantenimientoClientes.enabled=true
                    permisosMantenimientoClientes()


                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false

                    mantenimientoClientes.visible=true
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=2
                    btnLateralBusquedas.z=0
                    rowMenusDelSistema.z=-1
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    var cantidadRegistrosListaPrecioCliente=mantenimientoClientes.retornaCantidadRegistrosListaPrecioCliente()

                    if(cantidadRegistrosListaPrecioCliente=="" || cantidadRegistrosListaPrecioCliente=="0"){
                        mantenimientoClientes.cargarListasDePrecioCliente("","")
                    }

                }else if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos")){

                    permisosMantenimientoArticulos()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=true
                    mantenimientoArticulos.visible=true
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=3

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    modeloListaProveedor.clearClientes();
                    modeloListaProveedor.buscarCliente("tipoCliente=","2")


                    modeloListasPreciosComboBox.clearListasPrecio()
                    modeloListasPreciosComboBox.buscarListasPrecio("1=","1")




                }else if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarListaPrecios")){

                    permisosMantenimientoListaDePrecios()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false

                    mantenimientoListaPrecios.enabled=true
                    mantenimientoListaPrecios.visible=true
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=4

                    if(mantenimientoListaPrecios.opcionesExtrasActivas){

                        rowMenusDelSistema.z=-1
                        btnLateralBusquedas.z=0

                        menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
                    }else{
                        rowMenusDelSistema.z=0
                        btnLateralBusquedas.z=0
                        menulista1.enabled=false
                    }
                }else{


                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=0

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
                }




            }else if(lado=="derecha"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarFacturacion")){
                    permisosMantenimientoFacturacion()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false

                    mantenimientoFactura.enabled=true
                    mantenimientoFactura.visible=true

                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=1

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    modeloLiquidacionesComboBox.clearLiquidaciones()
                    modeloLiquidacionesComboBox.buscarLiquidacion("1=","1")

                    modeloListaVendedores.clearUsuarios()
                    modeloListaVendedores.buscarUsuarios("esVendedor=","1")



                }else{
                    mostrarMantenimientos(1,"derecha")
                }



            }
        }else if(posicion==1){
            if(lado=="izquierda"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarLiquidaciones")){
                    permisosMantenimientoLiquidaciones()

                    mantenimientoLiquidaciones.enabled=true
                    mantenimientoLiquidaciones.visible=true
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=0

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    modeloListaVendedores.clearUsuarios()
                    modeloListaVendedores.buscarUsuarios("esVendedor=","1")
                }



            }else if(lado=="derecha"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarClientes")){
                    mantenimientoClientes.enabled=true
                    permisosMantenimientoClientes()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false

                    mantenimientoClientes.visible=true
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=2

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    var cantidadRegistrosListaPrecioCliente=mantenimientoClientes.retornaCantidadRegistrosListaPrecioCliente()

                    if(cantidadRegistrosListaPrecioCliente=="" || cantidadRegistrosListaPrecioCliente=="0"){
                        mantenimientoClientes.cargarListasDePrecioCliente("","")
                    }
                }else{
                    mostrarMantenimientos(2,"derecha")
                }
            }


        }else if(posicion==2){
            if(lado=="izquierda"){


                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarFacturacion")){

                    permisosMantenimientoFacturacion()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=true
                    mantenimientoFactura.visible=true
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=1

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    modeloLiquidacionesComboBox.clearLiquidaciones()
                    modeloLiquidacionesComboBox.buscarLiquidacion("1=","1")

                    modeloListaVendedores.clearUsuarios()
                    modeloListaVendedores.buscarUsuarios("esVendedor=","1")


                }else{
                    mostrarMantenimientos(1,"izquierda")
                }



            }else if(lado=="derecha"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos")){
                    permisosMantenimientoArticulos()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=true
                    mantenimientoArticulos.visible=true
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=3

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    modeloListaProveedor.clearClientes();
                    modeloListaProveedor.buscarCliente("tipoCliente=","2")

                    modeloListasPreciosComboBox.clearListasPrecio()
                    modeloListasPreciosComboBox.buscarListasPrecio("1=","1")

                }else{
                    mostrarMantenimientos(3,"derecha")
                }

            }


        }else if(posicion==3){
            if(lado=="izquierda"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarClientes")){

                    mantenimientoClientes.enabled=true
                    permisosMantenimientoClientes()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.visible=true
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=2

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                    var cantidadRegistrosListaPrecioCliente=mantenimientoClientes.retornaCantidadRegistrosListaPrecioCliente()

                    if(cantidadRegistrosListaPrecioCliente=="" || cantidadRegistrosListaPrecioCliente=="0"){
                        mantenimientoClientes.cargarListasDePrecioCliente("","")
                    }
                }else{

                    mostrarMantenimientos(2,"izquierda")

                }

            }else if(lado=="derecha"){


                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarListaPrecios")){
                    permisosMantenimientoListaDePrecios()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=true
                    mantenimientoListaPrecios.visible=true
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=4

                    if(mantenimientoListaPrecios.opcionesExtrasActivas){

                        rowMenusDelSistema.z=-1
                        btnLateralBusquedas.z=0
                        menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
                    }else{
                        btnLateralBusquedas.z=0
                        rowMenusDelSistema.z=-1
                        menulista1.enabled=false
                    }
                }


            }
        }else if(posicion==4){
            if(lado=="izquierda"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos")){
                    permisosMantenimientoArticulos()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=true
                    mantenimientoArticulos.visible=true
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    modeloListaProveedor.clearClientes();
                    modeloListaProveedor.buscarCliente("tipoCliente=","2")

                    modeloListasPreciosComboBox.clearListasPrecio()
                    modeloListasPreciosComboBox.buscarListasPrecio("1=","1")

                    opcionEnCurso=3
                    btnLateralBusquedas.z=0
                    rowMenusDelSistema.z=-1
                }else{

                    mostrarMantenimientos(3,"izquierda")
                }
            }else if(lado=="derecha"){


                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarDocumentos")){

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=true
                    mantenimientoDocumentos.visible=true
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false

                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=5

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                }

            }
        }else if(posicion==5){
            if(lado=="izquierda"){


                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarListaPrecios")){
                    permisosMantenimientoListaDePrecios()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=true
                    mantenimientoListaPrecios.visible=true
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false
                    opcionEnCurso=4

                    if(mantenimientoListaPrecios.opcionesExtrasActivas){

                        rowMenusDelSistema.z=-1
                        btnLateralBusquedas.z=0
                        menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")
                    }else{
                        btnLateralBusquedas.z=0
                        rowMenusDelSistema.z=-1
                        menulista1.enabled=false

                    }
                }else{
                    mostrarMantenimientos(3,"izquierda")
                }

            }else if(lado=="derecha"){


                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarReportes")){
                    permisosMantenimientoReportes()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=true
                    mantenimientoReportes.visible=true
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=6
                    btnLateralBusquedas.z=0
                    rowMenusDelSistema.z=-1

                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                }

            }
        }else if(posicion==6){
            if(lado=="izquierda"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarDocumentos")){


                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=true
                    mantenimientoDocumentos.visible=true
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false
                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=5

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                }else{
                    mostrarMantenimientos(4,"izquierda")
                }



            }else if(lado=="derecha"){


                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarCuentaCorriente")){

                    permisosMantenimientoCuentacorriente()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=true
                    mantenimientoCuentasCorriente.visible=true

                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false

                    opcionEnCurso=7

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                }

            }
        }else if(posicion==7){
            if(lado=="izquierda"){

                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarReportes")){
                    permisosMantenimientoReportes()

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=true
                    mantenimientoReportes.visible=true
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false

                    mantenimientoPromociones.enabled=false
                    mantenimientoPromociones.visible=false


                    opcionEnCurso=6
                    btnLateralBusquedas.z=0
                    rowMenusDelSistema.z=-1

                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                }else{
                    mostrarMantenimientos(5,"izquierda")
                }



            }else if(lado=="derecha"){
                if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarPromociones")){

                    mantenimientoLiquidaciones.enabled=false
                    mantenimientoLiquidaciones.visible=false
                    mantenimientoFactura.enabled=false
                    mantenimientoFactura.visible=false
                    mantenimientoClientes.enabled=false
                    mantenimientoClientes.visible=false
                    mantenimientoArticulos.enabled=false
                    mantenimientoArticulos.visible=false
                    mantenimientoListaPrecios.enabled=false
                    mantenimientoListaPrecios.visible=false
                    mantenimientoDocumentos.enabled=false
                    mantenimientoDocumentos.visible=false
                    mantenimientoReportes.enabled=false
                    mantenimientoReportes.visible=false
                    mantenimientoCuentasCorriente.enabled=false
                    mantenimientoCuentasCorriente.visible=false

                    mantenimientoPromociones.enabled=true
                    mantenimientoPromociones.visible=true

                    opcionEnCurso=8

                    rowMenusDelSistema.z=-1
                    btnLateralBusquedas.z=0
                    menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                }

            }
        }
         else if(posicion==8){
                    if(lado=="izquierda"){

                        if(modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarCuentaCorriente")){

                            permisosMantenimientoCuentacorriente()

                            mantenimientoLiquidaciones.enabled=false
                            mantenimientoLiquidaciones.visible=false
                            mantenimientoFactura.enabled=false
                            mantenimientoFactura.visible=false
                            mantenimientoClientes.enabled=false
                            mantenimientoClientes.visible=false
                            mantenimientoArticulos.enabled=false
                            mantenimientoArticulos.visible=false
                            mantenimientoListaPrecios.enabled=false
                            mantenimientoListaPrecios.visible=false
                            mantenimientoDocumentos.enabled=false
                            mantenimientoDocumentos.visible=false
                            mantenimientoReportes.enabled=false
                            mantenimientoReportes.visible=false
                            mantenimientoCuentasCorriente.enabled=true
                            mantenimientoCuentasCorriente.visible=true

                            mantenimientoPromociones.enabled=false
                            mantenimientoPromociones.visible=false

                            opcionEnCurso=7

                            rowMenusDelSistema.z=-1
                            btnLateralBusquedas.z=0
                            menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")

                        }else{
                            mostrarMantenimientos(6,"izquierda")
                        }




                    }else if(lado=="derecha"){


                    }
                }





    }

    Rectangle {
        id: navegador
        x: 60
        y: 60
        height: 480
        color: "#525151"
        radius: 0
        z: 1
        anchors.right: parent.right
        anchors.rightMargin: -20
        anchors.top: parent.top
        anchors.topMargin: 10
        opacity: 1
        anchors.left: parent.left
        anchors.leftMargin: 45
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        enabled: false


        MantenimientoLiquidaciones{
            id: mantenimientoLiquidaciones
            z: 1
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            enabled: true
            visible: true
        }

        MantenimientoFacturacion{
            id: mantenimientoFactura
            x: 5
            y: 5
            z: 1
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5
            enabled: false
            visible: false
        }

        MantenimientoClientes {
            id: mantenimientoClientes
            x: 5
            y: 5
            z: 1
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5
            enabled: false
            visible: false
        }

        MantenimientoArticulos {
            id: mantenimientoArticulos
            z: 1
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            enabled: false
            visible: false
        }

        MantenimientoListasDePrecios{
            id: mantenimientoListaPrecios
            z: 1
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            enabled: false
            visible: false

        }

        MantenimientoDocumentos{
            id: mantenimientoDocumentos
            z: 1
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            enabled: false
            visible: false

        }


        MantenimientoReportes{
            id: mantenimientoReportes
            z: 1
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            enabled: false
            visible: false

        }

        MantenimientoCuentasCorriente{
            id: mantenimientoCuentasCorriente
            z: 1
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            enabled: false
            visible: false

        }

        MantenimientoPromociones{
            id: mantenimientoPromociones
            z: 1
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            enabled: false
            visible: false
        }



        Row {
            id: rowMenusDelSistema
            x: 0
            y: 0
            height: 30
            anchors.leftMargin: (navegador.width*-1)-40
            anchors.right: parent.right
            anchors.rightMargin: 900
            anchors.left: navegador.right
            z: 1
            anchors.top: parent.top
            anchors.topMargin: 0
            spacing: 20

            onZChanged: {

                menulista1.rectPrincipalVisible=false
            }

            MenuLista {
                id: menulista1
                z: 1
                textoBoton: qsTr("    ")
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Notebook.png"
                visible: menulista1.enabled
                onClic: {
                    etUsuario.z=0
                    btnLateralBusquedas.z=0
                    rowMenusDelSistema.z=1
                    etUsuario.cerrarComboBox()

                }
            }
        }



        Text {
            id: txtMensajeErrorSinConexionMysql
            x: 510
            y: 185
            text: ""
            z: 0
            font.bold: true
            styleColor: "#747c93"
            style: Text.Outline
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.NoWrap
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 29
        }

        Text {
            id: txtMensajeErrorSinConexionServidor
            x: 512
            height: 34
            text: ""
            anchors.top: txtMensajeErrorSinConexionMysql.bottom
            anchors.topMargin: 20
            font.pixelSize: 29
            anchors.horizontalCenter: parent.horizontalCenter
            style: Text.Outline
            wrapMode: Text.NoWrap
            styleColor: "#747c93"
            font.bold: true
            z: 0
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }



  /*  BotonFlecha {
        id: botonflechaAvanzar
        x: 121
        y: 555
        toolTip: ""
        border.color: "white"
        anchors.bottom: botonflechaRetroceder.top
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        anchors.left: parent.left

        onClic: {
            mostrarMantenimientos(opcionEnCurso,"derecha")
        }
    }
    BotonFlecha {
        id: botonflechaRetroceder
        x: 78
        y: 555
        color: "#00faf6f6"
        toolTip: ""
        border.color: "white"
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: botonHome.top
        anchors.bottomMargin: 30
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/FlechaIzquierda.png"


        onClic: {
            mostrarMantenimientos(opcionEnCurso,"izquierda")

        }
    }

    BotonBarraDeHerramientas {
        id: botonHome
        y: 560
        width: 25
        height: 25
        toolTip: ""
        source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Home.png"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 10

        onClic: {

            mostrarMantenimientos(0,"home")
        }
    }*/

    Rectangle {
        id: rectLogin        
        color: rectPrincipal.color
        radius: 0
        visible: true
        opacity: 1
        anchors.rightMargin: -20
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        z: 7

        focus: true
        onFocusChanged: txtNombreDeUsuario.tomarElFoco()

        /* Image {
            id: imageLogin
            visible: true
            fillMode: Image.Tile
            anchors.fill: parent

            focus: false*/

        MouseArea {
            id: mouse_area1
            anchors.fill: parent
            hoverEnabled: true


            Rectangle {
                id: rectAcceso
                x: 184
                y: 19
                width: 376
                height: 200
                radius: 6
                clip: false
                color: "#1d7195"
                border.color: "#1d7195"
                focus: false
                opacity: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                Rectangle {
                    id: rectangle1
                    x: -1
                    y: 9
                    width: 10
                    anchors.top: parent.top
                    clip: true
                    Rectangle {
                        id: rectangle2
                        width: 3
                        height: parent.height/1.50
                        color: "#1e7597"
                        radius: 5
                        opacity: 0.8
                        anchors.leftMargin: 5
                        anchors.bottomMargin: -1
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                    }
                    gradient: Gradient {
                        GradientStop {
                            position: 0
                            color: "#0f4c7d"
                        }

                        GradientStop {
                            position: 1
                            color: "#1a2329"
                        }
                    }
                    anchors.leftMargin: 15
                    anchors.bottomMargin: -1
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.topMargin: 0
                }


                Text {
                    id: txtAcceso
                    color: "#fdfbfb"
                    text: qsTr("Acceso")
                    font.family: "Arial"
                    style: Text.Normal
                    font.italic: false
                    anchors.left: parent.left
                    anchors.leftMargin: 45
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    font.bold: false
                    font.pixelSize: 37
                    focus: false
                }

                TextInputSimple {
                    id: txtNombreDeUsuario
                    x: 20
                    y: 93
                    width: 240
                   // height: 50

                    tamanioFuenteTitulo: 13
                    textoDeFondo: qsTr("ingrese usuario...")
                    textoInputBox: ""
                    anchors.horizontalCenter: parent.horizontalCenter

                    echoMode: 0
                    textoTitulo: qsTr("Usuario:")
                    botonBorrarTextoVisible: true



                    onEnter: txtContraseniaDeUsuario.tomarElFoco()

                    onTabulacion: txtContraseniaDeUsuario.tomarElFoco()


                }

                TextInputSimple {
                    id: txtContraseniaDeUsuario
                    x: 20
                    y: 136
                    width: 240
                    //height: 50
tamanioFuenteTitulo: 13
                    largoMaximo: 25
                    textoDeFondo: qsTr("ingrese contraseña...")
                    echoMode: 2
                    anchors.horizontalCenter: parent.horizontalCenter
                    textoTitulo: qsTr("Contraseña:")
                    botonBorrarTextoVisible: true


                    onEnter: {

                        if(modeloUsuarios.conexionUsuario(txtNombreDeUsuario.textoInputBox.toString().trim(),txtContraseniaDeUsuario.textoInputBox.toString().trim())){
                            //rectLoginOpacidadOut.stop()
                            //rectAccesoWHOut.stop()
                           // rectLoginOpacidadOut.start()
                            //rectAccesoWHOut.start()
                            navegador.enabled=true
                            timeReajustarGradient.stop()
                            rectLogin.enabled=false
                            rectLogin.visible=false
                            rectAcceso.visible=rectLogin.visible


                            etUsuario.setearUsuario(modeloUsuarios.retornaNombreUsuarioLogueado(txtNombreDeUsuario.textoInputBox.trim()))

                            //Mantenimientos
                            mantenimientoLiquidaciones.enabled= modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarLiquidaciones")
                            tagLiquidaciones.enabled=mantenimientoLiquidaciones.enabled;
                            tagLiquidaciones.visible=mantenimientoLiquidaciones.enabled;

                            tagFacturacion.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarFacturacion")
                            tagFacturacion.visible=tagFacturacion.enabled

                            mantenimientoClientes.enabled= modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarClientes")
                            tagClientes.enabled=mantenimientoClientes.enabled
                            tagClientes.visible=mantenimientoClientes.enabled

                            mantenimientoListaPrecios.enabled= modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarListaPrecios")
                            tagListaDePrecios.enabled=mantenimientoListaPrecios.enabled
                            tagListaDePrecios.visible=mantenimientoListaPrecios.enabled

                            mantenimientoArticulos.enabled= modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarArticulos")
                            tagArticulos.enabled=mantenimientoArticulos.enabled
                            tagArticulos.visible=mantenimientoArticulos.enabled

                            mantenimientoDocumentos.enabled= modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarDocumentos")
                            tagDocumentos.enabled=mantenimientoDocumentos.enabled
                            tagDocumentos.visible=mantenimientoDocumentos.enabled

                            mantenimientoReportes.enabled= modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarReportes")
                            tagReportes.enabled=mantenimientoReportes.enabled
                            tagReportes.visible=mantenimientoReportes.enabled

                            mantenimientoCuentasCorriente.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarCuentaCorriente")
                            tagCuentaCorriente.enabled=mantenimientoCuentasCorriente.enabled
                            tagCuentaCorriente.visible=mantenimientoCuentasCorriente.enabled

                            mantenimientoPromociones.enabled= false// modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarPromociones")
                            //tagPromociones.enabled=mantenimientoPromociones.enabled
                            //tagPromociones.visible=mantenimientoPromociones.enabled




                            menulista1.enabled=modeloListaPerfilesComboBox.retornaValorDePermiso(modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()),"permiteUsarMenuAvanzado")



                            if(menulista1.enabled)
                                menulista1.cargarValores()

                            mostrarMantenimientos(0,"home")

                            mantenimientoFactura.setearVendedorDelSistema()

                            modeloListaTipoDocumentosComboBox.limpiarListaTipoDocumentos()
                            modeloListaTipoDocumentosComboBox.buscarTipoDocumentos("1=","1",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))

                            modeloReportesMenuComboBox.limpiarListaReportesMenu()
                            modeloReportesMenuComboBox.buscarReportesMenu("1=","1",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))


                            if(modeloReportes.retornaSiReportaEstaHabilitadoEnPerfil("22",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))){
                                var cantidadSinStock=modeloArticulos.retornaCantidadArticulosSinStock()
                                if(cantidadSinStock!="0"){
                                    btnAvisoFaltaStock.textoBoton=cantidadSinStock
                                    btnAvisoFaltaStock.timerRuning=true
                                    btnAvisoFaltaStock.visible=true
                                }else{
                                    btnAvisoFaltaStock.visible=false
                                    btnAvisoFaltaStock.timerRuning=false
                                }
                            }



                        }else{
                            timeReajustarGradient.stop()
                            rectAcceso.color="#ba3e2b"
                            rectAcceso.border.color="#ba3e2b"
                            rectangle2.color="#ba3e2b"
                            timeReajustarGradient.start()

                        }

                    }
                    onTabulacion: txtNombreDeUsuario.tomarElFoco()
                }

                Image {
                    id: imageIconoLogin
                    x: 308
                    width: 51
                    height: 51
                    smooth: true
                    opacity: 0.680
                    anchors.right: parent.right
                    anchors.rightMargin: 15
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    asynchronous: true
                    focus: false
                    source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Acceso.png"
                }

                Rectangle {
                    id: rectLiniaAcceso
                    height: 1
                    color: "#c2bfbf"
                    radius: 1
                    anchors.top: parent.top
                    anchors.topMargin: 72
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    focus: false
                }

                Rectangle {
                    id: rectangle3
                    color: rectAcceso.color
                    border.color: rectAcceso.color
                    z: 1
                    anchors.left: parent.right
                    anchors.leftMargin: -30
                    anchors.top: parent.bottom
                    anchors.topMargin: -30
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                }
            }

            Rectangle {
                id: rectLiniaAcceso1
                x: -38
                y: 398
                height: 1
                color: "#c2bfbf"
                radius: 1
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                anchors.rightMargin: 70
                anchors.right: parent.right
                anchors.leftMargin: 50
                anchors.left: parent.left
                focus: false
            }

            Rectangle {
                id: rectLiniaAcceso2
                x: -38
                y: -161
                height: 1
                color: "#c2bfbf"
                radius: 1
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.rightMargin: 70
                anchors.right: parent.right
                anchors.leftMargin: 50
                anchors.left: parent.left
                focus: false
            }
            
            
            Image {
                property string fechaImportante:funcionesmysql.retornaFechaImportante()
                id: imgLogoKhitomer
                smooth: true
                width: {
                    if(fechaImportante=="reyes_magos"){
                        150
                    }else{
                        96
                    }
                }
                
                height: 96
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                anchors.right: parent.right
                anchors.rightMargin: 70
                z: 1
                asynchronous: true
                enabled: false
                source:   {
                    
                    if(fechaImportante=="navidad"){
                        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1"){
                            "qrc:/imagenes/qml/ProyectoQML/Imagenes/LogoKhitomerCFE-20-03-2018_128pxNavidad.png"
                        }else{
                            "qrc:/imagenes/qml/ProyectoQML/Imagenes/navidad.png"
                        }
                    }
                    else if(fechaImportante=="reyes_magos"){
                        "qrc:/imagenes/qml/ProyectoQML/Imagenes/reyesmagos.png"
                    }
                    else if(fechaImportante=="dia_normal"){
                        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1"){
                            "qrc:/imagenes/qml/ProyectoQML/Imagenes/LogoKhitomerCFE-20-03-2018_128px.png"
                        }else{
                            "qrc:/imagenes/qml/ProyectoQML/Imagenes/LogoKhitomer-19-07-2016_128px.png"
                        }
                    }
                    else{
                        if(modeloconfiguracion.retornaValorConfiguracion("MODO_CFE")==="1"){
                            "qrc:/imagenes/qml/ProyectoQML/Imagenes/LogoKhitomerCFE-20-03-2018_128px.png"
                        }else{
                            "qrc:/imagenes/qml/ProyectoQML/Imagenes/LogoKhitomer-19-07-2016_128px.png"
                        }
                    }
                }
            }
            
            Image {
                id: imgLogoQt
                width: 188
                height: 45
                source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Built_with_Qt_logo_RGB.png"
                anchors.left: parent.left
                anchors.leftMargin: 50
                anchors.bottomMargin: 30
                asynchronous: true
                z: 1
                smooth: true
                enabled: false
                anchors.bottom: parent.bottom
            }

            Text {
                id: txtVersionKhitomer
                color: "#ffffff"
                text: qsTr("Versión: "+versionKhitomer)
                anchors.right: rectLiniaAcceso1.right
                anchors.rightMargin: 1
                anchors.top: rectLiniaAcceso1.bottom
                anchors.topMargin: 2
                style: Text.Normal
                font.bold: true
                textFormat: Text.AutoText
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 10
            }

            


        }








        Timer{
            id:timeReajustarGradient
            interval: 2000
            repeat: false
            running:false
            onTriggered: {

                rectAcceso.color="#1d7195"
                rectAcceso.border.color="#1d7195"
                rectangle2.color="#1d7195"


            }

        }
    }

    Row {
        id: rowTagsInferior
        spacing: 8
        anchors.top: navegador.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 45
        //enabled: false

        Tag {
            id: tagLiquidaciones
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevaLiquidacion.png"
            texto: qsTr("Cajas")
            _gradietMedioIndicador:"#4c6bb5"
            indicadorColor: "#4a68b5"
            toolTip: ""
            opacidadPorDefecto: mantenimientoLiquidaciones.visible ? "1" : "0.5"
            onClic: {
                mostrarMantenimientos(0,"home")
            }
        }

        Tag {
            id: tagFacturacion
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevaFacturacion.png"
            texto: qsTr("Facturación")
            _gradietMedioIndicador:"#db4d4d"
            opacidadPorDefecto: mantenimientoFactura.visible ? "1" : "0.5"
            toolTip: ""
            indicadorColor: "#db4d4d"
            onClic: {
                mostrarMantenimientos(0,"derecha")
            }
        }

        Tag {
            id: tagClientes
            texto: qsTr("Cliente/Proveedor")
            toolTip: ""
            indicadorColor: "#3ca239"
            opacidadPorDefecto: mantenimientoClientes.visible ? "1" : "0.5"
            _gradietMedioIndicador:"#3ca239"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevoCliente.png"
            onClic: {
                mostrarMantenimientos(1,"derecha")
            }
        }

        Tag {
            id: tagArticulos
            visible: true
            texto: qsTr("Artículos")
            opacidadPorDefecto: mantenimientoArticulos.visible ? "1" : "0.5"
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevoArticulo.png"
            toolTip: ""
            indicadorColor: "#27abb4"
            _gradietMedioIndicador:"#27acb3"
            onClic: {
                mostrarMantenimientos(2,"derecha")
            }
        }

        Tag {
            id: tagListaDePrecios
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/NuevaListaDePrecios.png"
            texto: qsTr("Lista de precios")
            _gradietMedioIndicador:"#f8a218"
            opacidadPorDefecto: mantenimientoListaPrecios.visible ? "1" : "0.5"
            toolTip: ""
            indicadorColor: "#f89e16"
            onClic: {
                mostrarMantenimientos(3,"derecha")
            }
        }

        Tag {
            id: tagDocumentos
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Documentos.png"
            texto: qsTr("Documentos")
            _gradietMedioIndicador:"#7a14be"
            indicadorColor: "#7e0cc5"
            toolTip: ""
            opacidadPorDefecto: mantenimientoDocumentos.visible ? "1" : "0.5"

            onClic: {

                mostrarMantenimientos(4,"derecha")

            }


        }

        Tag {
            id: tagReportes
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/Reportes.png"
            texto: qsTr("Reportes")
            toolTip: ""
            _gradietMedioIndicador:"#e235dd"
            indicadorColor: "#e235dd"
            opacidadPorDefecto: mantenimientoReportes.visible ? "1" : "0.5"
            onClic: {

                mostrarMantenimientos(5,"derecha")

            }
        }

        Tag {
            id: tagCuentaCorriente
            texto: qsTr("Cuentas corrientes")
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/CuentasCorrientes.png"
            toolTip: ""
            _gradietMedioIndicador: "#4c6bb5"
            indicadorColor: "#880000"
            opacidadPorDefecto: mantenimientoCuentasCorriente.visible ? "1" : "0.5"

            onClic: {

                mostrarMantenimientos(6,"derecha")

            }
        }


    }

   /* EtiquetaUsuario {
        id: etUsuario
        //x: 742
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 10
        z: 1
    }*/


    EtiquetaUsuario {
        id: etUsuario
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 85
        anchors.left: parent.left
        anchors.leftMargin: -35
        z: 1
        onClic: {
            if(visibleComboBox){
                etUsuario.z=1
            }else{
                etUsuario.z=0
            }


         }
    }


   /* Timer{
        id:timeVerificaConectividadMysql
        interval: 5432//Milisegundos para realizar una consulta. La idea es que no se pise con otra cosulta a la base. Hasta que no implemente los threads
        repeat: false
        running: false
        onTriggered: {


            estadoConexionMysql=funcionesmysql.consutlaMysqlEstaViva()
            if(!estadoConexionMysql){

                txtMensajeErrorSinConexionMysql.color="#212121"
                txtMensajeErrorSinConexionMysql.styleColor= "#747c93"

                txtMensajeErrorSinConexionMysql.text=qsTr("No hay conexion con la base de datos MySql del servidor.")
                mostrarMantenimientos(0,"home")


            }else{

                txtMensajeErrorSinConexionMysql.color="#148826"
                txtMensajeErrorSinConexionMysql.styleColor= "#171a25"
                txtMensajeErrorSinConexionMysql.text=qsTr("Conexion con base de datos ok, puede continuar operando.")
            }

            etUsuario.setarEstadoMysql(estadoConexionMysql)

        }

    }*/

    /*Timer{
        id:timeReseteaConexionMysql
        interval: 25212345
        repeat: true
        running: true
        onTriggered: {
            //resetea cada 7 horas aproximadamente
            funcionesmysql.reseteaConexionMysql()
        }
    }*/


   /* Timer{
        id:timeVerificaConectividadServidor
        interval: 60000
        repeat: false
        running: false
        onTriggered: {

            estadoConexionServidor=funcionesmysql.consultaPingServidor()
            if(!estadoConexionServidor){

                txtMensajeErrorSinConexionServidor.color="#212121"
                txtMensajeErrorSinConexionServidor.styleColor= "#747c93"

                txtMensajeErrorSinConexionServidor.text=qsTr("No hay conexion con el servidor, revise conectividad.")
                mostrarMantenimientos(0,"home")

            }else{

                txtMensajeErrorSinConexionServidor.color="#148826"
                txtMensajeErrorSinConexionServidor.styleColor= "#171a25"
                txtMensajeErrorSinConexionServidor.text=qsTr("Conexion con servidor ok.")
            }

            etUsuario.setarEstadoServidor(estadoConexionServidor)

        }

    }*/

    BotonLateral {
        id: btnAvisoFaltaStock
        z: 0
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.left: parent.left
        anchors.leftMargin: 8
        visible: false
        onClic: {
            mantenimientoReportes.seleccionarReporte(22)
            mantenimientoReportes.cargarReporte(22)
            mostrarMantenimientos(5,"derecha")
        }

        /*Component.onCompleted: {

            if(modeloReportes.retornaSiReportaEstaHabilitadoEnPerfil("22",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))){
                var cantidadSinStock=modeloArticulos.retornaCantidadArticulosSinStock()
                if(cantidadSinStock!="0"){
                    btnAvisoFaltaStock.textoBoton=cantidadSinStock
                    btnAvisoFaltaStock.timerRuning=true
                    btnAvisoFaltaStock.visible=true
                }else{
                    btnAvisoFaltaStock.visible=false
                    btnAvisoFaltaStock.timerRuning=false
                }
            }


        }*/
    }

    Timer{
        running:true
        interval: 7254321
        repeat: true
        onTriggered: {
            if(modeloReportes.retornaSiReportaEstaHabilitadoEnPerfil("22",modeloUsuarios.retornaCodigoPerfil(txtNombreDeUsuario.textoInputBox.trim()))){
                var cantidadSinStock=modeloArticulos.retornaCantidadArticulosSinStock()
                if(cantidadSinStock!="0"){
                    btnAvisoFaltaStock.textoBoton=cantidadSinStock
                    btnAvisoFaltaStock.timerRuning=true
                    btnAvisoFaltaStock.visible=true
                }else{
                    btnAvisoFaltaStock.visible=false
                    btnAvisoFaltaStock.timerRuning=false
                }
            }
        }
    }

    BotonLateralBusquedas {
        id: btnLateralBusquedas
        width: 40
        height: 40
        visible: true
        rectanguloSecundarioVisible: false
        opacidad: 0.700
        anchors.top: btnAvisoFaltaStock.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 3
        rectPrincipalVisible: false
        onClic:  {
            rowMenusDelSistema.z=-1
            btnLateralBusquedas.z=1

        }
    }

   /* Row {
        id: rowTagsSuperior
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        Tag {
            id: tagCuentaCorriente
            texto: qsTr("Cuentas corrientes")
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/CuentasCorrientes.png"
            toolTip: ""
            _gradietMedioIndicador: "#4c6bb5"
            indicadorColor: "#880000"
            opacidadPorDefecto: mantenimientoCuentasCorriente.visible ? "1" : "0.5"

            onClic: {

                mostrarMantenimientos(6,"derecha")

            }
        }

        Tag {            
            id: tagPromociones
            texto: qsTr("Promociones")
            source: "qrc:/imagenes/qml/ProyectoQML/Imagenes/MantenimientoPromociones.png"
            toolTip: ""
            _gradietMedioIndicador: "#CDDC39"
            indicadorColor: "#CDDC39"
            opacidadPorDefecto: mantenimientoPromociones.visible ? "1" : "0.5"

            onClic: {

                mostrarMantenimientos(7,"derecha")

            }
        }





        anchors.left: parent.left
        spacing: 5
        anchors.leftMargin: 125
        anchors.topMargin: 15
        anchors.bottom: navegador.top
        anchors.top: parent.top
    }*/




}



