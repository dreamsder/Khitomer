-- MySQL dump 10.13  Distrib 5.5.29, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: khitomer
-- ------------------------------------------------------
-- Server version	5.5.29-0ubuntu0.12.04.2

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Articulos`
--

DROP TABLE IF EXISTS `Articulos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Articulos` (
  `codigoArticulo` varchar(10) NOT NULL,
  `descripcionArticulo` varchar(45) DEFAULT NULL,
  `descripcionExtendida` varchar(100) DEFAULT NULL,
  `codigoProveedor` bigint(10) unsigned NOT NULL,
  `tipoCliente` int(10) unsigned NOT NULL DEFAULT '2',
  `codigoIva` int(10) unsigned NOT NULL,
  `codigoMoneda` int(10) unsigned NOT NULL,
  `activo` char(1) NOT NULL DEFAULT '1',
  `usuarioAlta` varchar(45) DEFAULT NULL,
  `usuarioUltimaModificacion` varchar(45) DEFAULT NULL,
  `fechaAlta` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `fechaUltimaModificacion` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `codigoSubRubro` int(10) unsigned NOT NULL,
  `cantidadMinimaStock` bigint(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoArticulo`),
  KEY `fk_CodigoIva` (`codigoIva`),
  KEY `fk_CodigoMoneda` (`codigoMoneda`),
  KEY `fk_CodigoProveedor` (`codigoProveedor`,`tipoCliente`),
  KEY `fk_CodigoSubRubro` (`codigoSubRubro`),
  CONSTRAINT `fk_CodigoIva` FOREIGN KEY (`codigoIva`) REFERENCES `Ivas` (`codigoIva`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_CodigoMoneda` FOREIGN KEY (`codigoMoneda`) REFERENCES `Monedas` (`codigoMoneda`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_CodigoProveedor` FOREIGN KEY (`codigoProveedor`, `tipoCliente`) REFERENCES `Clientes` (`codigoCliente`, `tipoCliente`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_CodigoSubRubro` FOREIGN KEY (`codigoSubRubro`) REFERENCES `SubRubros` (`codigoSubRubro`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Articulos`
--

LOCK TABLES `Articulos` WRITE;
/*!40000 ALTER TABLE `Articulos` DISABLE KEYS */;
/*!40000 ALTER TABLE `Articulos` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`khitomer`@`localhost`*/ /*!50003 TRIGGER ins_suma_stock_faltante_Articulos AFTER UPDATE ON Articulos
    FOR EACH ROW BEGIN
   delete from FaltaStock;
   
   
   insert into FaltaStock (cantidadArticulosSinStock,codigoArticulo)
  
SELECT 

  case when AR.cantidadMinimaStock<= (SELECT
  sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)

from

   Documentos DOC

   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  

  and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento

  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento

  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in ('E','G','P') and DOCL.codigoArticulo=AR.codigoArticulo

  and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS

  where DOCS.codigoTipoDocumento=8

  and DOCS.codigoEstadoDocumento in ('E','G')

  order by DOCS.codigoDocumento desc limit 1))
  then 0 else 1 end,
  AR.codigoArticulo

  from Articulos AR
  group by AR.codigoArticulo;

 
  END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `ArticulosBarras`
--

DROP TABLE IF EXISTS `ArticulosBarras`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ArticulosBarras` (
  `codigoArticuloBarras` varchar(45) NOT NULL,
  `codigoArticuloInterno` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`codigoArticuloBarras`),
  KEY `fk_CodigoArticulo` (`codigoArticuloInterno`),
  CONSTRAINT `fk_CodigoArticulo` FOREIGN KEY (`codigoArticuloInterno`) REFERENCES `Articulos` (`codigoArticulo`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ArticulosBarras`
--

LOCK TABLES `ArticulosBarras` WRITE;
/*!40000 ALTER TABLE `ArticulosBarras` DISABLE KEYS */;
/*!40000 ALTER TABLE `ArticulosBarras` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Bancos`
--

DROP TABLE IF EXISTS `Bancos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Bancos` (
  `codigoBanco` int(10) unsigned NOT NULL,
  `descripcionBanco` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoBanco`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Bancos`
--

LOCK TABLES `Bancos` WRITE;
/*!40000 ALTER TABLE `Bancos` DISABLE KEYS */;
INSERT INTO `Bancos` VALUES (1,'CITIBANK'),(2,'BANDES'),(3,'BROU'),(4,'NBC'),(5,'BBVA'),(6,'SANTANDER');
/*!40000 ALTER TABLE `Bancos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Clientes`
--

DROP TABLE IF EXISTS `Clientes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Clientes` (
  `codigoCliente` bigint(10) unsigned NOT NULL,
  `tipoCliente` int(10) unsigned NOT NULL DEFAULT '1',
  `nombreCliente` varchar(45) DEFAULT NULL,
  `razonSocial` varchar(45) DEFAULT NULL,
  `rut` varchar(45) DEFAULT NULL,
  `tipoClasificacion` int(10) NOT NULL DEFAULT '1',
  `direccion` varchar(45) DEFAULT NULL,
  `esquina` varchar(45) DEFAULT NULL,
  `numeroPuerta` varchar(45) DEFAULT NULL,
  `telefono` varchar(45) DEFAULT NULL,
  `telefono2` varchar(45) DEFAULT NULL,
  `documento` varchar(45) DEFAULT NULL,
  `codigoPostal` varchar(45) DEFAULT NULL,
  `email` varchar(45) DEFAULT NULL,
  `sitioWeb` varchar(45) DEFAULT NULL,
  `contacto` varchar(45) DEFAULT NULL,
  `horario` varchar(45) DEFAULT NULL,
  `observaciones` varchar(100) DEFAULT NULL,
  `fechaUltimaModificacion` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `fechaAlta` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `usuarioAlta` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoCliente`,`tipoCliente`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='latin1_swedish_ci';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Clientes`
--

LOCK TABLES `Clientes` WRITE;
/*!40000 ALTER TABLE `Clientes` DISABLE KEYS */;
/*!40000 ALTER TABLE `Clientes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Configuracion`
--

DROP TABLE IF EXISTS `Configuracion`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Configuracion` (
  `codigoConfiguracion` varchar(45) NOT NULL,
  `valorConfiguracion` varchar(45) NOT NULL DEFAULT '0',
  `descripcionConfiguracion` varchar(300) DEFAULT NULL,
  PRIMARY KEY (`codigoConfiguracion`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Configuraciones del sistema, modalidad de funcionamiento de ';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Configuracion`
--

LOCK TABLES `Configuracion` WRITE;
/*!40000 ALTER TABLE `Configuracion` DISABLE KEYS */;
INSERT INTO `Configuracion` VALUES ('MODO_AFECTACION_CAJA','2','Parametro que indica como afectar los valores de caja, 0 no afecta, 1 afectan los totales de documentos, 2 afectan los medios de pago.'),('MODO_ARTICULO','1','Parametro que indica la modalidad de uso del codigo de articulo, 0 es alfanumerico, 1 es numerico.'),('MODO_IMPRESION_A4','1','Parametro que indica si la hoja se toma como A4 a pesar de las configuraciones pre establecidas.'),('MULTI_EMPRESA','0','Parametro que indica si se usa multiempresa, 1 - sí, 0 - no.'),('TIPO_CIERRE_LIQUIDACION','1','Parametro que indica como se cierran las liquidaciones. 0 - Se cierran al precionar boton de cierre. 1 - Se cierran al precionar boton de cierre y pide autorizacion. 2 - Se abre la ventana de declaracion de valores para poder cerrarse, requiere autorización.'),('VERSION_BD','60','Muestra la verisión de la base de datos. Este dato se utiliza para indicarle a la aplicación la versión de la base de datos, y que la misma realice las actualizaciones necesarias.');
/*!40000 ALTER TABLE `Configuracion` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `CuentaBancaria`
--

DROP TABLE IF EXISTS `CuentaBancaria`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CuentaBancaria` (
  `numeroCuentaBancaria` varchar(45) NOT NULL,
  `codigoBanco` int(10) unsigned NOT NULL,
  `descripcionCuentaBancaria` varchar(45) DEFAULT NULL,
  `observaciones` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`numeroCuentaBancaria`,`codigoBanco`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CuentaBancaria`
--

LOCK TABLES `CuentaBancaria` WRITE;
/*!40000 ALTER TABLE `CuentaBancaria` DISABLE KEYS */;
/*!40000 ALTER TABLE `CuentaBancaria` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Documentos`
--

DROP TABLE IF EXISTS `Documentos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Documentos` (
  `codigoDocumento` bigint(10) unsigned NOT NULL,
  `codigoTipoDocumento` int(10) unsigned NOT NULL,
  `serieDocumento` varchar(45) NOT NULL DEFAULT '',
  `codigoEstadoDocumento` char(1) NOT NULL DEFAULT '',
  `codigoCliente` bigint(10) unsigned NOT NULL DEFAULT '0',
  `tipoCliente` int(10) unsigned NOT NULL DEFAULT '0',
  `codigoMonedaDocumento` int(10) unsigned DEFAULT NULL,
  `cotizacionMoneda` decimal(45,8) unsigned NOT NULL DEFAULT '1.00000000',
  `fechaHoraGuardadoDocumentoSQL` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `fechaUltimaModificacionDocumento` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `fechaEmisionDocumento` date NOT NULL DEFAULT '0000-00-00',
  `usuarioUltimaModificacion` varchar(45) NOT NULL,
  `precioTotalVenta` decimal(45,2) NOT NULL DEFAULT '0.00',
  `precioSubTotalVenta` decimal(45,2) NOT NULL DEFAULT '0.00',
  `precioIvaVenta` decimal(45,2) NOT NULL DEFAULT '0.00',
  `codigoLiquidacion` bigint(100) unsigned NOT NULL,
  `codigoVendedorLiquidacion` varchar(45) NOT NULL,
  `codigoVendedorComisiona` varchar(45) NOT NULL,
  `totalIva1` decimal(45,2) NOT NULL DEFAULT '0.00',
  `totalIva2` decimal(45,2) NOT NULL DEFAULT '0.00',
  `totalIva3` decimal(45,2) NOT NULL DEFAULT '0.00',
  `usuarioAlta` varchar(45) NOT NULL,
  `tieneDescuentoAlTotal` char(1) NOT NULL DEFAULT '0',
  `montoDescuentoTotal` decimal(45,2) NOT NULL DEFAULT '0.00',
  `usuarioAutorizaDescuentoTotal` varchar(45) DEFAULT NULL,
  `codigoPromocion` int(10) unsigned NOT NULL DEFAULT '0',
  `codigoBeneficio` int(10) unsigned NOT NULL DEFAULT '0',
  `observaciones` varchar(100) DEFAULT NULL,
  `numeroCuentaBancaria` varchar(45) NOT NULL DEFAULT '0',
  `codigoBanco` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoDocumento`,`codigoTipoDocumento`),
  KEY `fk_TipoDocumento` (`codigoTipoDocumento`),
  KEY `index_codigoDocumento` (`codigoDocumento`,`codigoTipoDocumento`,`serieDocumento`,`codigoEstadoDocumento`),
  KEY `fk_TipoEstadoDocumento` (`codigoEstadoDocumento`),
  KEY `fk_CodigoMonedas` (`codigoMonedaDocumento`),
  CONSTRAINT `fk_CodigoMonedas` FOREIGN KEY (`codigoMonedaDocumento`) REFERENCES `Monedas` (`codigoMoneda`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TipoDocumento` FOREIGN KEY (`codigoTipoDocumento`) REFERENCES `TipoDocumento` (`codigoTipoDocumento`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TipoEstadoDocumento` FOREIGN KEY (`codigoEstadoDocumento`) REFERENCES `TipoEstadoDocumento` (`codigoEstadoDocumento`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Documentos`
--

LOCK TABLES `Documentos` WRITE;
/*!40000 ALTER TABLE `Documentos` DISABLE KEYS */;
/*!40000 ALTER TABLE `Documentos` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`khitomer`@`localhost`*/ /*!50003 TRIGGER ins_suma_stock_faltante AFTER UPDATE ON Documentos
    FOR EACH ROW BEGIN
   delete from FaltaStock;
   
   
   insert into FaltaStock (cantidadArticulosSinStock,codigoArticulo)
  
SELECT 

  case when AR.cantidadMinimaStock<= (SELECT
  sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)

from

   Documentos DOC

   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  

  and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento

  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento

  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in ('E','G','P') and DOCL.codigoArticulo=AR.codigoArticulo

  and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS

  where DOCS.codigoTipoDocumento=8

  and DOCS.codigoEstadoDocumento in ('E','G')

  order by DOCS.codigoDocumento desc limit 1))
  then 0 else 1 end,
  AR.codigoArticulo

  from Articulos AR
  group by AR.codigoArticulo;

 
  END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `DocumentosLineas`
--

DROP TABLE IF EXISTS `DocumentosLineas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `DocumentosLineas` (
  `codigoDocumento` bigint(10) unsigned NOT NULL,
  `codigoTipoDocumento` int(10) unsigned NOT NULL,
  `numeroLinea` int(10) unsigned NOT NULL,
  `codigoArticulo` varchar(10) NOT NULL DEFAULT '',
  `codigoArticuloBarras` varchar(45) NOT NULL DEFAULT '',
  `cantidad` int(10) NOT NULL,
  `precioTotalVenta` decimal(45,2) NOT NULL DEFAULT '0.00',
  `precioArticuloUnitario` decimal(45,2) NOT NULL DEFAULT '0.00',
  `precioIvaArticulo` decimal(45,2) NOT NULL DEFAULT '0.00',
  `fechaHoraGuardadoLineaSQL` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `tieneDescuento` char(1) NOT NULL DEFAULT '0',
  `montoDescuento` decimal(45,2) NOT NULL DEFAULT '0.00',
  `usuarioAutorizaDescuento` varchar(45) DEFAULT NULL,
  `codigoPromocion` int(10) unsigned NOT NULL DEFAULT '0',
  `codigoBeneficio` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`numeroLinea`,`codigoDocumento`,`codigoTipoDocumento`),
  KEY `fk_DocumentoExiste` (`codigoDocumento`,`codigoTipoDocumento`),
  CONSTRAINT `fk_DocumentoExiste` FOREIGN KEY (`codigoDocumento`, `codigoTipoDocumento`) REFERENCES `Documentos` (`codigoDocumento`, `codigoTipoDocumento`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `DocumentosLineas`
--

LOCK TABLES `DocumentosLineas` WRITE;
/*!40000 ALTER TABLE `DocumentosLineas` DISABLE KEYS */;
/*!40000 ALTER TABLE `DocumentosLineas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `DocumentosLineasPago`
--

DROP TABLE IF EXISTS `DocumentosLineasPago`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `DocumentosLineasPago` (
  `codigoDocumento` bigint(10) unsigned NOT NULL,
  `codigoTipoDocumento` int(10) unsigned NOT NULL,
  `numeroLinea` int(10) unsigned NOT NULL,
  `codigoMedioPago` int(10) unsigned DEFAULT NULL,
  `monedaMedioPago` int(10) unsigned DEFAULT NULL,
  `importePago` decimal(45,2) DEFAULT NULL,
  `cuotas` int(10) unsigned DEFAULT NULL,
  `codigoBanco` int(10) unsigned NOT NULL DEFAULT '0',
  `codigoTarjetaCredito` int(10) unsigned NOT NULL DEFAULT '0',
  `numeroCheque` varchar(45) NOT NULL DEFAULT '0',
  `tarjetaCobrada` char(1) NOT NULL DEFAULT '0',
  `montoCobrado` decimal(45,2) NOT NULL DEFAULT '0.00',
  `codigoTipoCheque` int(10) unsigned NOT NULL DEFAULT '1',
  `fechaCheque` date DEFAULT NULL,
  `documentoChequeDiferido` bigint(10) NOT NULL DEFAULT '0',
  `tipoDocumentoChequeDiferido` int(10) NOT NULL DEFAULT '0',
  `lineaDocumentoChequeDiferido` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoDocumento`,`codigoTipoDocumento`,`numeroLinea`),
  KEY `fk_MediosDePago` (`codigoMedioPago`),
  KEY `fk_DocumentosMediosDePago` (`codigoDocumento`,`codigoTipoDocumento`),
  KEY `fk_CodigoMonedaDocLineasPago` (`monedaMedioPago`),
  CONSTRAINT `fk_CodigoMonedaDocLineasPago` FOREIGN KEY (`monedaMedioPago`) REFERENCES `Monedas` (`codigoMoneda`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_DocumentosMediosDePago` FOREIGN KEY (`codigoDocumento`, `codigoTipoDocumento`) REFERENCES `Documentos` (`codigoDocumento`, `codigoTipoDocumento`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_MediosDePago` FOREIGN KEY (`codigoMedioPago`) REFERENCES `MediosDePago` (`codigoMedioPago`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `DocumentosLineasPago`
--

LOCK TABLES `DocumentosLineasPago` WRITE;
/*!40000 ALTER TABLE `DocumentosLineasPago` DISABLE KEYS */;
/*!40000 ALTER TABLE `DocumentosLineasPago` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `FaltaStock`
--

DROP TABLE IF EXISTS `FaltaStock`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `FaltaStock` (
  `cantidadArticulosSinStock` int(11) DEFAULT NULL,
  `codigoArticulo` varchar(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `FaltaStock`
--

LOCK TABLES `FaltaStock` WRITE;
/*!40000 ALTER TABLE `FaltaStock` DISABLE KEYS */;
/*!40000 ALTER TABLE `FaltaStock` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ImpresionCampos`
--

DROP TABLE IF EXISTS `ImpresionCampos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ImpresionCampos` (
  `codigoCampoImpresion` int(10) unsigned NOT NULL,
  `descripcionCampoImpresion` varchar(45) DEFAULT NULL,
  `tipoCampo` int(10) unsigned NOT NULL DEFAULT '1',
  `codigoEtiqueta` varchar(45) DEFAULT NULL,
  `campoEnTabla` varchar(45) NOT NULL,
  PRIMARY KEY (`codigoCampoImpresion`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='tipoCampo 1-Cabezal   2-Cuerpo   3-Pie ';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ImpresionCampos`
--

LOCK TABLES `ImpresionCampos` WRITE;
/*!40000 ALTER TABLE `ImpresionCampos` DISABLE KEYS */;
INSERT INTO `ImpresionCampos` VALUES (1,'Razón Social',1,'txtRazonSocialCampo','razonSocial'),(2,'Nombre',1,'txtNombreCampo','nombreCliente'),(3,'R.U.T.',1,'txtRutCampo','rut'),(4,'Direc.',1,'txtDireccionCampo','direccion'),(5,'Tel.',1,'txtTelefonoCampo','telefono'),(6,'Cód Art.',2,'txtCodigoArticuloCampo','codigoArticulo'),(7,'Des. Art.',2,'txtDescripcionArticuloCampo','descripcionArticulo'),(8,'Pre. U Art.',2,'txtPrecioListaArticuloCampo','precioArticuloUnitario'),(9,'Total linea art.',2,'txtTotalLineaArticuloCampo','precioTotalVenta'),(10,'Fecha doc.',1,'txtFechaDocumentoCampo','fechaEmisionDocumento'),(11,'Sub total',3,'txtSubTotalCampo','precioSubTotalVenta'),(12,'Total',3,'txtTotalCampo','precioTotalVenta'),(13,'Iva total',3,'txtIvaTotalCampo','precioIvaVenta'),(14,'Iva bas.',3,'txtIvaBasicoCampo','totalIva1'),(15,'Iva min.',3,'txtIvaMinimoCampo','totalIva2'),(16,'Iva exe.',3,'txtIvaExentoCampo','totalIva3'),(17,'Cant. art.',2,'txtCantidadArticuloCampo','CANTIDAD'),(18,'Sim. Mon.',3,'txtSimboloMonedaCampo','simboloMoneda');
/*!40000 ALTER TABLE `ImpresionCampos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Ivas`
--

DROP TABLE IF EXISTS `Ivas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Ivas` (
  `codigoIva` int(10) unsigned NOT NULL,
  `descripcionIva` varchar(45) DEFAULT NULL,
  `porcentajeIva` decimal(45,2) unsigned DEFAULT NULL,
  `factorMultiplicador` decimal(45,2) unsigned DEFAULT NULL,
  PRIMARY KEY (`codigoIva`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Ivas`
--

LOCK TABLES `Ivas` WRITE;
/*!40000 ALTER TABLE `Ivas` DISABLE KEYS */;
INSERT INTO `Ivas` VALUES (1,'Basico',22.00,1.22),(2,'Minimo',10.00,1.10),(3,'Exento',0.00,1.00);
/*!40000 ALTER TABLE `Ivas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Liquidaciones`
--

DROP TABLE IF EXISTS `Liquidaciones`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Liquidaciones` (
  `codigoLiquidacion` bigint(100) unsigned NOT NULL,
  `codigoVendedor` varchar(45) NOT NULL,
  `fechaDiaLiquidacion` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `fechaLiquidacion` date NOT NULL DEFAULT '0000-00-00',
  `fechaCierreLiquidacion` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `estadoLiquidacion` char(1) DEFAULT NULL,
  `usuarioAlta` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoLiquidacion`,`codigoVendedor`),
  KEY `fk_TipoEstadoLiquidacion` (`estadoLiquidacion`),
  KEY `fk_VendedorLiquidacion` (`codigoVendedor`),
  CONSTRAINT `fk_TipoEstadoLiquidacion` FOREIGN KEY (`estadoLiquidacion`) REFERENCES `TipoEstadoLiquidacion` (`codigoTipoEstadoLiquidacion`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_VendedorLiquidacion` FOREIGN KEY (`codigoVendedor`) REFERENCES `Usuarios` (`idUsuario`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Liquidaciones`
--

LOCK TABLES `Liquidaciones` WRITE;
/*!40000 ALTER TABLE `Liquidaciones` DISABLE KEYS */;
/*!40000 ALTER TABLE `Liquidaciones` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ListaPrecio`
--

DROP TABLE IF EXISTS `ListaPrecio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ListaPrecio` (
  `codigoListaPrecio` int(10) unsigned NOT NULL,
  `descripcionListaPrecio` varchar(45) DEFAULT NULL,
  `vigenciaDesdeFecha` date DEFAULT NULL,
  `vigenciaHastaFecha` date DEFAULT NULL,
  `usuarioAlta` varchar(45) DEFAULT NULL,
  `activo` char(1) NOT NULL DEFAULT '1',
  `participaEnBusquedaInteligente` char(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`codigoListaPrecio`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ListaPrecio`
--

LOCK TABLES `ListaPrecio` WRITE;
/*!40000 ALTER TABLE `ListaPrecio` DISABLE KEYS */;
INSERT INTO `ListaPrecio` VALUES (1,'Lista de precio Generica','2011-01-01','2049-12-31','admin','1','1');
/*!40000 ALTER TABLE `ListaPrecio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ListaPrecioArticulos`
--

DROP TABLE IF EXISTS `ListaPrecioArticulos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ListaPrecioArticulos` (
  `codigoListaPrecio` int(10) unsigned NOT NULL,
  `codigoArticulo` varchar(10) NOT NULL,
  `precioArticulo` decimal(45,2) DEFAULT NULL,
  PRIMARY KEY (`codigoListaPrecio`,`codigoArticulo`),
  KEY `fk_CodigoListaPrecio` (`codigoListaPrecio`),
  KEY `fk_CodigoArticuloEnLista` (`codigoArticulo`),
  CONSTRAINT `fk_CodigoArticuloEnLista` FOREIGN KEY (`codigoArticulo`) REFERENCES `Articulos` (`codigoArticulo`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_CodigoListaPrecio` FOREIGN KEY (`codigoListaPrecio`) REFERENCES `ListaPrecio` (`codigoListaPrecio`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ListaPrecioArticulos`
--

LOCK TABLES `ListaPrecioArticulos` WRITE;
/*!40000 ALTER TABLE `ListaPrecioArticulos` DISABLE KEYS */;
/*!40000 ALTER TABLE `ListaPrecioArticulos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ListaPrecioClientes`
--

DROP TABLE IF EXISTS `ListaPrecioClientes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ListaPrecioClientes` (
  `codigoListaPrecio` int(10) unsigned NOT NULL,
  `codigoCliente` bigint(10) unsigned NOT NULL,
  `tipoCliente` int(10) unsigned NOT NULL,
  PRIMARY KEY (`codigoListaPrecio`,`codigoCliente`,`tipoCliente`),
  KEY `fk_ListaPrecio` (`codigoListaPrecio`),
  KEY `fk_CodigoCliente` (`codigoCliente`,`tipoCliente`),
  CONSTRAINT `fk_CodigoCliente` FOREIGN KEY (`codigoCliente`, `tipoCliente`) REFERENCES `Clientes` (`codigoCliente`, `tipoCliente`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_ListaPrecio` FOREIGN KEY (`codigoListaPrecio`) REFERENCES `ListaPrecio` (`codigoListaPrecio`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ListaPrecioClientes`
--

LOCK TABLES `ListaPrecioClientes` WRITE;
/*!40000 ALTER TABLE `ListaPrecioClientes` DISABLE KEYS */;
/*!40000 ALTER TABLE `ListaPrecioClientes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `MediosDePago`
--

DROP TABLE IF EXISTS `MediosDePago`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `MediosDePago` (
  `codigoMedioPago` int(10) unsigned NOT NULL,
  `descripcionMedioPago` varchar(45) DEFAULT NULL,
  `monedaMedioPago` int(10) unsigned NOT NULL,
  `codigoTipoMedioDePago` int(10) unsigned DEFAULT NULL,
  PRIMARY KEY (`codigoMedioPago`),
  KEY `fk_TipoMedioDePago` (`codigoTipoMedioDePago`),
  KEY `fk_MediosDePagoCodigomoneda` (`monedaMedioPago`),
  CONSTRAINT `fk_MediosDePagoCodigomoneda` FOREIGN KEY (`monedaMedioPago`) REFERENCES `Monedas` (`codigoMoneda`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TipoMedioDePago` FOREIGN KEY (`codigoTipoMedioDePago`) REFERENCES `TipoMedioDePago` (`codigoTipoMedioDePago`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Tabla con la informacion de medios de pago';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `MediosDePago`
--

LOCK TABLES `MediosDePago` WRITE;
/*!40000 ALTER TABLE `MediosDePago` DISABLE KEYS */;
INSERT INTO `MediosDePago` VALUES (1,'Efectivo Pesos',1,1),(2,'Efectivo Dolares',2,1),(3,'Tarjeta de Credito Pesos',1,2),(4,'Tarjeta de Credito Dolares',2,2),(5,'Cheque Pesos',1,3),(6,'Cheque Dolares',2,3);
/*!40000 ALTER TABLE `MediosDePago` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `MenuSistema`
--

DROP TABLE IF EXISTS `MenuSistema`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `MenuSistema` (
  `codigoMenu` int(10) unsigned NOT NULL,
  `nombreMenu` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoMenu`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `MenuSistema`
--

LOCK TABLES `MenuSistema` WRITE;
/*!40000 ALTER TABLE `MenuSistema` DISABLE KEYS */;
INSERT INTO `MenuSistema` VALUES (1,'Sistema'),(2,'Reportes'),(3,'Usuarios'),(4,'Permisos'),(5,'Configuraciones'),(6,'Monedas'),(7,'Rubros'),(8,'Cuentas bancarias'),(9,'Pago de financieras');
/*!40000 ALTER TABLE `MenuSistema` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ModeloImpresion`
--

DROP TABLE IF EXISTS `ModeloImpresion`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ModeloImpresion` (
  `codigoModeloImpresion` int(10) unsigned NOT NULL,
  `descripcionModeloImpresion` varchar(45) DEFAULT NULL,
  `altoPagina` decimal(45,2) NOT NULL DEFAULT '0.00',
  `anchoPagina` decimal(45,2) NOT NULL DEFAULT '0.00',
  `comienzoCuerpo` decimal(45,2) NOT NULL DEFAULT '0.00',
  `comienzoPie` decimal(45,2) NOT NULL DEFAULT '0.00',
  `fuenteSizePoints` int(11) NOT NULL DEFAULT '8',
  PRIMARY KEY (`codigoModeloImpresion`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ModeloImpresion`
--

LOCK TABLES `ModeloImpresion` WRITE;
/*!40000 ALTER TABLE `ModeloImpresion` DISABLE KEYS */;
INSERT INTO `ModeloImpresion` VALUES (1,'Modelo Contado',14.50,21.50,6.50,11.00,9),(2,'modelo 2',20.00,20.00,5.00,7.00,7);
/*!40000 ALTER TABLE `ModeloImpresion` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ModeloImpresionLineas`
--

DROP TABLE IF EXISTS `ModeloImpresionLineas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ModeloImpresionLineas` (
  `codigoModeloImpresion` int(10) unsigned NOT NULL,
  `codigoCampoImpresion` int(10) unsigned NOT NULL,
  `posicionX` decimal(45,2) NOT NULL DEFAULT '0.00',
  `posicionY` decimal(45,2) NOT NULL DEFAULT '0.00',
  `largoDeCampo` decimal(45,2) NOT NULL DEFAULT '0.00',
  `alineacion` int(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoModeloImpresion`,`codigoCampoImpresion`),
  KEY `fk_ModeloImpresion` (`codigoModeloImpresion`),
  KEY `fk_CamposModelo` (`codigoCampoImpresion`),
  CONSTRAINT `fk_CamposModelo` FOREIGN KEY (`codigoCampoImpresion`) REFERENCES `ImpresionCampos` (`codigoCampoImpresion`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_ModeloImpresion` FOREIGN KEY (`codigoModeloImpresion`) REFERENCES `ModeloImpresion` (`codigoModeloImpresion`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Las posiciones y largo de campo se cargan en centimetros';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ModeloImpresionLineas`
--

LOCK TABLES `ModeloImpresionLineas` WRITE;
/*!40000 ALTER TABLE `ModeloImpresionLineas` DISABLE KEYS */;
INSERT INTO `ModeloImpresionLineas` VALUES (1,1,4.00,4.20,10.00,0),(1,3,10.00,3.50,4.00,0),(1,4,4.00,4.80,10.00,0),(1,7,3.50,7.50,10.00,0),(1,8,17.80,7.50,2.00,2),(1,9,19.70,7.50,2.00,2),(1,10,18.50,5.00,2.00,2),(1,11,19.70,12.80,2.00,2),(1,12,19.70,13.80,2.00,2),(1,13,19.70,13.30,2.00,2),(1,17,3.00,7.50,2.00,2),(2,1,17.46,3.08,2.00,0);
/*!40000 ALTER TABLE `ModeloImpresionLineas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Monedas`
--

DROP TABLE IF EXISTS `Monedas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Monedas` (
  `codigoMoneda` int(10) unsigned NOT NULL,
  `descripcionMoneda` varchar(45) DEFAULT NULL,
  `codigoISO3166` varchar(10) DEFAULT NULL,
  `codigoISO4217` varchar(10) DEFAULT NULL,
  `simboloMoneda` varchar(10) DEFAULT NULL,
  `cotizacionMoneda` decimal(45,8) unsigned DEFAULT NULL,
  `cotizacionMonedaOficial` decimal(45,8) unsigned DEFAULT NULL,
  `esMonedaReferenciaSistema` char(1) DEFAULT '0',
  PRIMARY KEY (`codigoMoneda`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Monedas`
--

LOCK TABLES `Monedas` WRITE;
/*!40000 ALTER TABLE `Monedas` DISABLE KEYS */;
INSERT INTO `Monedas` VALUES (1,'Pesos','858','UYU','$',1.00000000,1.00000000,'1'),(2,'Dolares','840','USD','U$S',19.35000000,0.00000000,'0');
/*!40000 ALTER TABLE `Monedas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `PerfilesUsuarios`
--

DROP TABLE IF EXISTS `PerfilesUsuarios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `PerfilesUsuarios` (
  `codigoPerfil` int(10) unsigned NOT NULL,
  `descripcionPerfil` varchar(45) DEFAULT NULL,
  `permiteUsarLiquidaciones` char(1) NOT NULL DEFAULT '0',
  `permiteUsarFacturacion` char(1) NOT NULL DEFAULT '0',
  `permiteUsarArticulos` char(1) NOT NULL DEFAULT '0',
  `permiteUsarListaPrecios` char(1) NOT NULL DEFAULT '0',
  `permiteUsarClientes` char(1) NOT NULL DEFAULT '0',
  `permiteUsarDocumentos` char(1) NOT NULL DEFAULT '0',
  `permiteUsarReportes` char(1) NOT NULL DEFAULT '0',
  `permiteUsarCuentaCorriente` char(1) NOT NULL DEFAULT '0',
  `permiteUsarMenuAvanzado` char(1) NOT NULL DEFAULT '0',
  `permiteExportarAPDF` char(1) NOT NULL DEFAULT '0',
  `permiteCrearLiquidaciones` char(1) NOT NULL DEFAULT '0',
  `permiteBorrarLiquidaciones` char(1) NOT NULL DEFAULT '0',
  `permiteCerrarLiquidaciones` char(1) NOT NULL DEFAULT '0',
  `permiteAutorizarCierreLiquidaciones` char(1) NOT NULL DEFAULT '0',
  `permiteCrearFacturas` char(1) NOT NULL DEFAULT '0',
  `permiteBorrarFacturas` char(1) NOT NULL DEFAULT '0',
  `permiteAnularFacturas` char(1) NOT NULL DEFAULT '0',
  `permiteReimprimirFacturas` char(1) NOT NULL DEFAULT '0',
  `permiteCrearClientes` char(1) NOT NULL DEFAULT '0',
  `permiteBorrarClientes` char(1) NOT NULL DEFAULT '0',
  `permiteCrearArticulos` char(1) NOT NULL DEFAULT '0',
  `permiteBorrarArticulos` char(1) NOT NULL DEFAULT '0',
  `permiteCrearListaDePrecios` char(1) NOT NULL DEFAULT '0',
  `permiteBorrarListaDePrecios` char(1) NOT NULL DEFAULT '0',
  `permiteAutorizarDescuentosArticulo` char(1) NOT NULL DEFAULT '0',
  `permiteAutorizarDescuentosTotal` char(1) NOT NULL DEFAULT '0',
  `permiteAutorizarAnulaciones` char(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoPerfil`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PerfilesUsuarios`
--

LOCK TABLES `PerfilesUsuarios` WRITE;
/*!40000 ALTER TABLE `PerfilesUsuarios` DISABLE KEYS */;
INSERT INTO `PerfilesUsuarios` VALUES (1,'Administrador','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'),(2,'Administracion-vendedor','1','1','1','1','1','1','1','0','0','1','0','0','0','0','1','1','0','0','1','1','1','1','1','1','0','0','0'),(3,'Vendedores','1','1','0','1','1','1','0','0','0','0','0','0','0','0','1','1','0','1','1','1','1','1','1','1','0','0','0');
/*!40000 ALTER TABLE `PerfilesUsuarios` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Reportes`
--

DROP TABLE IF EXISTS `Reportes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Reportes` (
  `codigoReporte` bigint(10) unsigned NOT NULL,
  `codigoMenuReporte` int(10) unsigned NOT NULL,
  `descripcionReporte` varchar(45) DEFAULT NULL,
  `consultaSql` varchar(10000) DEFAULT NULL,
  `utilizaCodigoCliente` char(1) NOT NULL DEFAULT '0',
  `utilizaCodigoProveedor` char(1) NOT NULL DEFAULT '0',
  `utilizaCodigoArticulo` char(1) NOT NULL DEFAULT '0',
  `utilizaCantidadItemRanking` char(1) NOT NULL DEFAULT '0',
  `utilizaFecha` char(1) NOT NULL DEFAULT '0',
  `utilizaFechaDesde` char(1) NOT NULL DEFAULT '0',
  `utilizaFechaHasta` char(1) NOT NULL DEFAULT '0',
  `utilizaVendedor` char(1) NOT NULL DEFAULT '0',
  `utilizaTipoDocumento` char(1) NOT NULL DEFAULT '0',
  `utilizaSubRubros` char(1) NOT NULL DEFAULT '0',
  `utilizaCodigoLiquidacionCaja` char(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoReporte`),
  KEY `fk_CodigoMenu` (`codigoMenuReporte`),
  CONSTRAINT `fk_CodigoMenu` FOREIGN KEY (`codigoMenuReporte`) REFERENCES `ReportesMenu` (`codigoMenuReporte`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Reportes`
--

LOCK TABLES `Reportes` WRITE;
/*!40000 ALTER TABLE `Reportes` DISABLE KEYS */;
INSERT INTO `Reportes` VALUES (1,1,'Lista de artículos inactivos','SELECT codigoArticulo\'Código\',descripcionArticulo\'Nombre\', fechaAlta\'Fecha de alta\',fechaUltimaModificacion\'Fecha de última modificación\'   FROM Articulos where activo=0; ','0','0','0','0','0','0','0','0','0','0','0'),(2,1,'Artículos x proveedor','SELECT CLI.nombreCliente\'Proveedor\',concat(AR.codigoArticulo,\' - \',AR.descripcionArticulo)\'Artículo\', AR.fechaAlta\'Fecha de alta\',AR.fechaUltimaModificacion\'Fecha de última modificación\'   FROM Articulos AR join Clientes CLI on CLI.codigoCliente=AR.codigoProveedor and CLI.tipoCliente=AR.tipoCliente where AR.tipoCliente=2 and AR.codigoProveedor=\'@_codigoProveedor\';','0','1','0','0','0','0','0','0','0','0','0'),(3,2,'Listado de clientes','SELECT concat(codigoCliente,\' - \',nombreCliente)\'Cliente\',razonSocial\'Razón social\',direccion\'Dirección\',telefono\'Telefono\',fechaAlta\'Fecha de alta\'  FROM Clientes where tipoCliente=1;','0','0','0','0','0','0','0','0','0','0','0'),(4,3,'Listado de proveedores','SELECT concat(codigoCliente,\' - \',nombreCliente)\'Cliente\',razonSocial\'Razón social\',direccion\'Dirección\',telefono\'Telefono\',fechaAlta\'Fecha de alta\'  FROM Clientes where tipoCliente=2;','0','0','0','0','0','0','0','0','0','0','0'),(5,5,'Movimientos x cliente','select concat(CLI.codigoCliente,\' - \',(case when CLI.razonSocial=\'\' then CLI.nombreCliente else CLI.razonSocial end))\'Cliente\', concat(TDOC.descripcionTipoDocumento,\' (\',DOC.serieDocumento,\'-\',DOC.codigoDocumento,\')\')\'Documento\', DOC.fechaEmisionDocumento\'Fecha Doc.\', MON.simboloMoneda\'\', case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(0.00,2) end \'Debe\', case when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \'Haber\' from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente where DOC.tipoCliente=1 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\'@_codigoCliente\' order by DOC.fechaEmisionDocumento asc ;','1','0','0','0','0','0','0','0','0','0','0'),(6,5,'Movimientos x proveedor','select concat(CLI.codigoCliente,\' - \',(case when CLI.razonSocial=\'\' then CLI.nombreCliente else CLI.razonSocial end))\'Proveedor\', concat(TDOC.descripcionTipoDocumento,\' (\',DOC.serieDocumento,\'-\',DOC.codigoDocumento,\')\')\'Documento\', DOC.fechaEmisionDocumento\'Fecha Doc.\', MON.simboloMoneda\'\', case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(0.00,2) end \'Debe\', case when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \'Haber\' from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente where DOC.tipoCliente=2 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\'@_codigoProveedor\' order by DOC.fechaEmisionDocumento asc ;','0','1','0','0','0','0','0','0','0','0','0'),(7,5,'Saldo de cliente en Pesos','select concat(CLI.codigoCliente,\' - \',(case when CLI.razonSocial=\'\' then CLI.nombreCliente else CLI.razonSocial end))\'Cliente\', MON.simboloMoneda\'\', sum(case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(DOC.precioTotalVenta*-1,2) end)\'Saldo en Pesos\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.tipoCliente=1 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\'@_codigoCliente\' and DOC.codigoMonedaDocumento=1 ;','1','0','0','0','0','0','0','0','0','0','0'),(8,5,'Saldo de cliente en Dolares','select concat(CLI.codigoCliente,\' - \',(case when CLI.razonSocial=\'\' then CLI.nombreCliente else CLI.razonSocial end))\'Cliente\', MON.simboloMoneda\'\', sum(case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(DOC.precioTotalVenta*-1,2) end)\'Saldo en Dolares\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.tipoCliente=1  and DOC.codigoEstadoDocumento in (\'E\',\'G\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\'@_codigoCliente\' and DOC.codigoMonedaDocumento=2;','1','0','0','0','0','0','0','0','0','0','0'),(9,5,'Saldo de proveedores en Pesos','select concat(CLI.codigoCliente,\' - \',(case when CLI.razonSocial=\'\' then CLI.nombreCliente else CLI.razonSocial end))\'Proveedor\', MON.simboloMoneda\'\', sum(case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(DOC.precioTotalVenta*-1,2) end)\'Saldo en Pesos\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.tipoCliente=2 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\'@_codigoProveedor\' and DOC.codigoMonedaDocumento=1;','0','1','0','0','0','0','0','0','0','0','0'),(10,5,'Saldo de proveedores en Dolares','select concat(CLI.codigoCliente,\' - \',(case when CLI.razonSocial=\'\' then CLI.nombreCliente else CLI.razonSocial end))\'Proveedor\', MON.simboloMoneda\'\', sum(case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(DOC.precioTotalVenta*-1,2) end)\'Saldo en Pesos\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.tipoCliente=2 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\'@_codigoProveedor\' and DOC.codigoMonedaDocumento=2;','0','1','0','0','0','0','0','0','0','0','0'),(11,6,'Artículos mas vendidos','select concat(DOCL.codigoArticulo,\' - \',AR.descripcionArticulo)\'Artículo\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\'Cantidad ventas\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo where DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.afectaTotales!=0 group by DOCL.codigoArticulo order by 2 desc limit @_cantidad ;','0','0','0','1','0','0','0','0','0','0','0'),(12,6,'Artículos mas vendidos entre fechas','select concat(DOCL.codigoArticulo,\' - \',AR.descripcionArticulo)\'Artículo\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\'Cantidad ventas\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo  where DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.afectaTotales!=0 and DOC.fechaEmisionDocumento between \'@_desde\' and \'@_hasta\'  group by DOCL.codigoArticulo order by 2 desc limit @_cantidad ;','0','0','0','1','0','1','1','0','0','0','0'),(13,3,'Alta de proveedores entre fechas','SELECT  concat(CLI.codigoCliente,\' - \',CLI.nombreCliente)\'Proveedor\', CLI.razonSocial\'Razón Social\', CLI.fechaAlta\'Alta en sistema\', concat(USU.nombreUsuario,\' \',USU.apellidoUsuario)\'Usuario del alta\' FROM Clientes CLI  join Usuarios USU on USU.idUsuario=CLI.usuarioAlta where CLI.tipoCliente=2 and CLI.fechaAlta between \'@_desde\' and \'@_hasta\' + INTERVAL 1 DAY order by CLI.fechaAlta asc;','0','0','0','0','0','1','1','0','0','0','0'),(14,4,'Ventas x vendedor entre fechas','SELECT concat(USU.nombreUsuario,\' \',USU.apellidoUsuario)\'Vendedor\', concat(TDOC.descripcionTipoDocumento,\' (\',DOC.codigoDocumento,\'-\',DOC.serieDocumento,\')\')\'Documento\', case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta,2)  else ROUND(DOC.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda ),2) end \'Total $\', case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta,2)  else ROUND(DOC.precioTotalVenta/(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=2 ),2) end \'Total U$S\' FROM Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where  DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.afectaTotales!=0 and DOC.fechaEmisionDocumento  between \'@_desde\' and \'@_hasta\' and DOC.codigoVendedorComisiona=\'@_codigoVendedor\' order by DOC.fechaEmisionDocumento asc ;','0','0','0','0','0','1','1','1','0','0','0'),(15,2,'Alta de clientes entre fechas','SELECT  concat(CLI.codigoCliente,\' - \',CLI.nombreCliente)\'Cliente\', CLI.razonSocial\'Razón Social\', CLI.fechaAlta\'Alta en sistema\', concat(USU.nombreUsuario,\' \',USU.apellidoUsuario)\'Usuario del alta\' FROM Clientes CLI  join Usuarios USU on USU.idUsuario=CLI.usuarioAlta where CLI.tipoCliente=1 and CLI.fechaAlta between \'@_desde\' and \'@_hasta\' + INTERVAL 1 DAY order by CLI.fechaAlta asc;','0','0','0','0','0','1','1','0','0','0','0'),(16,7,'Documentos anulados entre fechas','SELECT concat(TDOC.descripcionTipoDocumento,\' (\',DOC.serieDocumento,\'-\',DOC.codigoDocumento,\')\')\'Documento\', case when CLI.nombreCliente is null then \'\' else CLI.nombreCliente end  \'Cliente\', concat(MON.simboloMoneda,\'      \',DOC.precioTotalVenta)\'Total\', DOC.fechaEmisionDocumento\'Fecha Doc.\', concat(USU.nombreUsuario,\' \',USU.apellidoUsuario)\'Usuario que anulo\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento left join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento join Usuarios USU on USU.idUsuario=DOC.usuarioUltimaModificacion where DOC.codigoEstadoDocumento=\'C\' and DOC.fechaEmisionDocumento between \'@_desde\' and \'@_hasta\' ;','0','0','0','0','0','1','1','0','0','0','0'),(17,7,'Total de documentos entre fechas','SELECT TDOC.descripcionTipoDocumento\'Documentos\', count(DOC.codigoDocumento+DOC.codigoTipoDocumento)\'Cantidad\' FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento where DOC.codigoEstadoDocumento in (\'G\',\'E\') and DOC.fechaEmisionDocumento between \'@_desde\' and \'@_hasta\' group by TDOC.descripcionTipoDocumento ;','0','0','0','0','0','1','1','0','0','0','0'),(18,8,'Stock total real','SELECT AR.codigoArticulo\'Código\',AR.descripcionArticulo\'Nombre\',AR.descripcionExtendida\'Descripción extendida\',case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \'cantidad\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\'E\',\'G\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \'cantidad\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\'E\',\'G\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end \'Cantidad Real\'  ,case when AR.activo=1 then \'activo\' else \'¡ARTÍCULO INACTIVO!\' end\'Estado\' FROM Articulos AR ;','0','0','0','0','0','0','0','0','0','0','0'),(19,4,'Ventas por cliente entre fechas','SELECT  concat((case when CLI.razonSocial=\'\' then CLI.nombreCliente else CLI.razonSocial end),\' (\',DOC.codigoCliente,\')\')\'CLIENTE\', concat(TDOC.descripcionTipoDocumento,\' (\',DOC.codigoDocumento,\'-\',DOC.serieDocumento,\')\')\'Documento\', DOC.fechaEmisionDocumento\'FECHA DOCUMENTO\', case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta,2)  else ROUND(DOC.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda ),2) end \'Total $\', case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta,2)  else ROUND(DOC.precioTotalVenta/(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=2 ),2) end \'Total U$S\' FROM Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where  DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.afectaTotales!=0 and DOC.codigoCliente=\'@_codigoCliente\' and  DOC.tipoCliente=1 and DOC.fechaEmisionDocumento  between \'@_desde\' and \'@_hasta\' order by DOC.fechaEmisionDocumento desc ;','1','0','0','0','0','1','1','0','0','0','0'),(20,6,'Artículos menos vendidos','select concat(DOCL.codigoArticulo,\' - \',AR.descripcionArticulo)\'Artículo\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\'Cantidad ventas\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo where DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.afectaTotales!=0 group by DOCL.codigoArticulo order by 2 asc limit @_cantidad ;','0','0','0','1','0','0','0','0','0','0','0'),(21,4,'Venta de artículo entre fechas','select DOC.fechaEmisionDocumento\'Fecha\', concat(DOCL.codigoArticulo,\' - \',AR.descripcionArticulo)\'Artículo\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\'Cantidad ventas\'   from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo    where DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.afectaTotales!=0  and DOC.fechaEmisionDocumento between \'@_desde\' and \'@_hasta\'  and DOCL.codigoArticulo=\'@_codigoArticulo\' group by DOC.fechaEmisionDocumento,DOCL.codigoArticulo order by 1,2 asc;','0','0','1','0','0','1','1','0','0','0','0'),(22,8,'Control stock bajo mínimo','select concat(AR.codigoArticulo,\' - \',AR.descripcionArticulo)\'ARTÍCULO\', AR.cantidadMinimaStock \'MÍNIMO STOCK\', case when (SELECT  sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)  from    Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\'E\',\'G\') and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS   where DOCS.codigoTipoDocumento=8   and DOCS.codigoEstadoDocumento in (\'E\',\'G\')   order by DOCS.codigoDocumento desc limit 1)) is null then 0 else  (SELECT   sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)   from    Documentos DOC     join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento      and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\'E\',\'G\') and DOCL.codigoArticulo=AR.codigoArticulo   and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS   where DOCS.codigoTipoDocumento=8   and DOCS.codigoEstadoDocumento in (\'E\',\'G\')  order by DOCS.codigoDocumento desc limit 1))  end \'STOCK REAL\', case when  (SELECT  sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) from    Documentos DOC    join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento     and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\'E\',\'G\',\'P\') and DOCL.codigoArticulo=AR.codigoArticulo   and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS   where DOCS.codigoTipoDocumento=8   and DOCS.codigoEstadoDocumento in (\'E\',\'G\')   order by DOCS.codigoDocumento desc limit 1)) is null then 0 else (SELECT   sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) from    Documentos DOC    join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento     and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\'E\',\'G\',\'P\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS   where DOCS.codigoTipoDocumento=8   and DOCS.codigoEstadoDocumento in (\'E\',\'G\')   order by DOCS.codigoDocumento desc limit 1)) end  \'STOCK PREVISTO\'  from  FaltaStock FS join Articulos AR on AR.codigoArticulo=FS.codigoArticulo where cantidadArticulosSinStock!=0 ;','0','0','0','0','0','0','0','0','0','0','0'),(23,8,'Stock por sub rubro','SELECT AR.codigoArticulo\'Código\',AR.descripcionArticulo\'Nombre\',AR.descripcionExtendida\'Descripción extendida\' ,case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \'cantidad\'  FROM Documentos DOC   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\'E\',\'G\')  and DOCL.codigoArticulo=AR.codigoArticulo     and DOC.fechaHoraGuardadoDocumentoSQL>=    (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\'E\',\'G\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \'cantidad\'  FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos  where codigoTipoDocumento=8 and codigoEstadoDocumento in (\'E\',\'G\')  order by codigoDocumento desc limit 1)  group by DOCL.codigoArticulo) end \'Stock Real\'  FROM Articulos AR  where AR.codigoSubRubro=\'@_codigoSubRubro\' order by CAST(AR.codigoArticulo AS SIGNED)  ;','0','0','0','0','0','0','0','0','0','1','0'),(24,9,'Total por Medios de Pago','select  concat(MP.descripcionMedioPago,\' \',MON.simboloMoneda) \'Total Medios de pago Efectivo: \', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\'Valor Total:\' from MediosDePago MP join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and D.codigoTipoDocumento=DLP.codigoTipoDocumento join TipoDocumento T on   T.codigoTipoDocumento=D.codigoTipoDocumento join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago where  MP.codigoTipoMedioDePago=1 and  T.afectaTotales!=0  \r\nand D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\') and D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and D.codigoVendedorLiquidacion=\'@_codigoVendedor\' group by MP.monedaMedioPago; select   concat(MP.descripcionMedioPago,\' \',MON.simboloMoneda) \'Total Medios de pago Tarjetas: \', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\'Valor Total:\' from MediosDePago MP\r\njoin DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and   D.codigoTipoDocumento=DLP.codigoTipoDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago\r\nwhere  MP.codigoTipoMedioDePago=2 and  T.afectaTotales!=0  and D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\') and D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and  D.codigoVendedorLiquidacion=\'@_codigoVendedor\' group by MP.monedaMedioPago; select  concat(MP.descripcionMedioPago,\' \',MON.simboloMoneda) \'Total Medios de pago Cheques : \', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\'Valor Total:\' from MediosDePago MP  join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago where  MP.codigoTipoMedioDePago=3 and T.afectaTotales!=0  and D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\') and D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and  D.codigoVendedorLiquidacion=\'@_codigoVendedor\' group by MP.monedaMedioPago;','0','0','0','0','0','0','0','1','0','0','1'),(25,9,'Total por Documentos y Medios de Pago','select concat(\'Total en \',M.descripcionMoneda,\' \',M.simboloMoneda) as \'Total en documentos:\', sum(D.precioTotalVenta*T.afectaTotales ) as \'Valor Total:\' FROM Documentos D  join Monedas M on M.codigoMoneda=D.codigoMonedaDocumento  join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  where D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and D.codigoVendedorLiquidacion=\'@_codigoVendedor\' and T.afectaTotales!=0 and D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\')  group by M.codigoMoneda;select  concat(MP.descripcionMedioPago,\' \',MON.simboloMoneda) \'Total Medios de pago Efectivo: \', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\'Valor Total:\' from MediosDePago MP join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and D.codigoTipoDocumento=DLP.codigoTipoDocumento join TipoDocumento T on   T.codigoTipoDocumento=D.codigoTipoDocumento join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago where  MP.codigoTipoMedioDePago=1 and  T.afectaTotales!=0  \r\nand D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\') and D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and D.codigoVendedorLiquidacion=\'@_codigoVendedor\' group by MP.monedaMedioPago; select   concat(MP.descripcionMedioPago,\' \',MON.simboloMoneda) \'Total Medios de pago Tarjetas: \', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\'Valor Total:\' from MediosDePago MP\r\njoin DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and   D.codigoTipoDocumento=DLP.codigoTipoDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago\r\nwhere  MP.codigoTipoMedioDePago=2 and  T.afectaTotales!=0  and D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\') and D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and  D.codigoVendedorLiquidacion=\'@_codigoVendedor\' group by MP.monedaMedioPago; select  concat(MP.descripcionMedioPago,\' \',MON.simboloMoneda) \'Total Medios de pago Cheques : \', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\'Valor Total:\' from MediosDePago MP  join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago where  MP.codigoTipoMedioDePago=3 and T.afectaTotales!=0  and D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\') and D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and  D.codigoVendedorLiquidacion=\'@_codigoVendedor\' group by MP.monedaMedioPago;','0','0','0','0','0','0','0','1','0','0','1');
/*!40000 ALTER TABLE `Reportes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ReportesConfiguracion`
--

DROP TABLE IF EXISTS `ReportesConfiguracion`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ReportesConfiguracion` (
  `codigoReporte` bigint(10) unsigned NOT NULL,
  `columnaReporte` int(10) unsigned NOT NULL,
  `alineacionColumna` char(1) NOT NULL DEFAULT '0',
  `totalizacionColumna` char(1) NOT NULL DEFAULT '0',
  `textoPieOpcional` varchar(45) NOT NULL DEFAULT '',
  `tipoDatoColumna` varchar(45) NOT NULL DEFAULT 'TEXTO',
  PRIMARY KEY (`codigoReporte`,`columnaReporte`),
  KEY `fk_codigoReporte` (`codigoReporte`),
  CONSTRAINT `fk_codigoReporte` FOREIGN KEY (`codigoReporte`) REFERENCES `Reportes` (`codigoReporte`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Configuracion de las columnas del reporte';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ReportesConfiguracion`
--

LOCK TABLES `ReportesConfiguracion` WRITE;
/*!40000 ALTER TABLE `ReportesConfiguracion` DISABLE KEYS */;
INSERT INTO `ReportesConfiguracion` VALUES (5,4,'2','0','','MONTO'),(5,5,'2','0','','MONTO'),(6,4,'2','0','','MONTO'),(6,5,'2','0','','MONTO'),(7,2,'2','0','','MONTO'),(8,2,'2','0','','MONTO'),(9,2,'2','0','','MONTO'),(10,2,'2','0','','MONTO'),(14,2,'2','1','','MONTO'),(14,3,'2','1','','MONTO'),(17,1,'1','1','','TEXTO'),(18,3,'1','0','','TEXTO'),(18,4,'1','0','','TEXTO'),(19,3,'2','0','','MONTO'),(19,4,'2','0','','MONTO'),(22,0,'0','0','','TEXTO'),(24,1,'2','0','','MONTO'),(25,1,'2','0','','MONTO');
/*!40000 ALTER TABLE `ReportesConfiguracion` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ReportesMenu`
--

DROP TABLE IF EXISTS `ReportesMenu`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ReportesMenu` (
  `codigoMenuReporte` int(10) unsigned NOT NULL,
  `descripcionMenuReporte` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoMenuReporte`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ReportesMenu`
--

LOCK TABLES `ReportesMenu` WRITE;
/*!40000 ALTER TABLE `ReportesMenu` DISABLE KEYS */;
INSERT INTO `ReportesMenu` VALUES (1,'Artículos'),(2,'Clientes'),(3,'Proveedores'),(4,'Ventas'),(5,'Cuentas corrientes'),(6,'Ranking\'s'),(7,'Documentos'),(8,'Stock'),(9,'Caja');
/*!40000 ALTER TABLE `ReportesMenu` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Rubros`
--

DROP TABLE IF EXISTS `Rubros`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Rubros` (
  `codigoRubro` int(10) unsigned NOT NULL,
  `descripcionRubro` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoRubro`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Rubros`
--

LOCK TABLES `Rubros` WRITE;
/*!40000 ALTER TABLE `Rubros` DISABLE KEYS */;
INSERT INTO `Rubros` VALUES (1,'Sin clasificar');
/*!40000 ALTER TABLE `Rubros` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SubRubros`
--

DROP TABLE IF EXISTS `SubRubros`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `SubRubros` (
  `codigoSubRubro` int(10) unsigned NOT NULL,
  `codigoRubro` int(10) unsigned NOT NULL,
  `descripcionSubRubro` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoSubRubro`),
  KEY `fk_codigoRubro` (`codigoRubro`),
  KEY `fk_CodigoRubros` (`codigoRubro`),
  CONSTRAINT `fk_CodigoRubros` FOREIGN KEY (`codigoRubro`) REFERENCES `Rubros` (`codigoRubro`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `SubRubros`
--

LOCK TABLES `SubRubros` WRITE;
/*!40000 ALTER TABLE `SubRubros` DISABLE KEYS */;
INSERT INTO `SubRubros` VALUES (1,1,'Sin clasificar');
/*!40000 ALTER TABLE `SubRubros` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TarjetasCredito`
--

DROP TABLE IF EXISTS `TarjetasCredito`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TarjetasCredito` (
  `codigoTarjetaCredito` int(10) unsigned NOT NULL,
  `descripcionTarjetaCredito` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoTarjetaCredito`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TarjetasCredito`
--

LOCK TABLES `TarjetasCredito` WRITE;
/*!40000 ALTER TABLE `TarjetasCredito` DISABLE KEYS */;
INSERT INTO `TarjetasCredito` VALUES (1,'VISA'),(2,'OCA'),(3,'CABAL'),(4,'ANDA'),(5,'MASTER'),(6,'PASSCARD'),(7,'DINERS'),(8,'CREDITEL'),(9,'CREDITOS DIRECTOS');
/*!40000 ALTER TABLE `TarjetasCredito` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TipoCheque`
--

DROP TABLE IF EXISTS `TipoCheque`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TipoCheque` (
  `codigoTipoCheque` int(10) unsigned NOT NULL,
  `descripcionTipoCheque` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoTipoCheque`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TipoCheque`
--

LOCK TABLES `TipoCheque` WRITE;
/*!40000 ALTER TABLE `TipoCheque` DISABLE KEYS */;
INSERT INTO `TipoCheque` VALUES (1,'Sin clasificación'),(2,'Diferido');
/*!40000 ALTER TABLE `TipoCheque` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TipoClasificacion`
--

DROP TABLE IF EXISTS `TipoClasificacion`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TipoClasificacion` (
  `codigoTipoClasificacion` int(10) unsigned NOT NULL,
  `descripcionTipoClasificacion` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoTipoClasificacion`),
  KEY `fk_TipoClasificacion_1` (`codigoTipoClasificacion`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TipoClasificacion`
--

LOCK TABLES `TipoClasificacion` WRITE;
/*!40000 ALTER TABLE `TipoClasificacion` DISABLE KEYS */;
INSERT INTO `TipoClasificacion` VALUES (1,'Final'),(2,'Tecnico'),(3,'Casa de Informatica'),(4,'Mayorista'),(5,'Organismo público');
/*!40000 ALTER TABLE `TipoClasificacion` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TipoCliente`
--

DROP TABLE IF EXISTS `TipoCliente`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TipoCliente` (
  `codigoTipoCliente` int(11) NOT NULL,
  `descripcionTipoCliente` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoTipoCliente`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TipoCliente`
--

LOCK TABLES `TipoCliente` WRITE;
/*!40000 ALTER TABLE `TipoCliente` DISABLE KEYS */;
INSERT INTO `TipoCliente` VALUES (1,'Cliente'),(2,'Proveedor');
/*!40000 ALTER TABLE `TipoCliente` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TipoDocumento`
--

DROP TABLE IF EXISTS `TipoDocumento`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TipoDocumento` (
  `codigoTipoDocumento` int(10) unsigned NOT NULL,
  `descripcionTipoDocumento` varchar(45) DEFAULT NULL,
  `utilizaArticulos` char(1) NOT NULL DEFAULT '0',
  `utilizaCodigoBarrasADemanda` char(1) NOT NULL DEFAULT '0',
  `utilizaTotales` char(1) NOT NULL DEFAULT '0',
  `utilizaListaPrecio` char(1) NOT NULL DEFAULT '0',
  `utilizaMediosDePago` char(1) NOT NULL DEFAULT '0',
  `utilizaFechaPrecio` char(1) NOT NULL DEFAULT '0',
  `utilizaFechaDocumento` char(1) NOT NULL DEFAULT '0',
  `utilizaNumeroDocumento` char(1) NOT NULL DEFAULT '0',
  `utilizaSerieDocumento` char(1) NOT NULL DEFAULT '0',
  `serieDocumento` varchar(45) DEFAULT 'A',
  `utilizaVendedor` char(1) NOT NULL DEFAULT '0',
  `utilizaCliente` char(1) NOT NULL DEFAULT '0',
  `utilizaTipoCliente` char(1) NOT NULL DEFAULT '0',
  `utilizaSoloProveedores` char(1) NOT NULL DEFAULT '0',
  `afectaCuentaCorriente` int(11) NOT NULL DEFAULT '0',
  `afectaStock` int(11) NOT NULL DEFAULT '0',
  `afectaTotales` int(11) NOT NULL DEFAULT '0',
  `utilizaCantidades` char(1) NOT NULL DEFAULT '0',
  `utilizaPrecioManual` char(1) NOT NULL DEFAULT '0',
  `utilizaDescuentoArticulo` char(1) NOT NULL DEFAULT '0',
  `utilizaDescuentoTotal` char(1) NOT NULL DEFAULT '0',
  `emiteEnImpresora` char(1) NOT NULL DEFAULT '0',
  `codigoModeloImpresion` int(10) unsigned NOT NULL DEFAULT '0',
  `cantidadCopias` int(10) unsigned NOT NULL DEFAULT '0',
  `utilizaObservaciones` char(1) NOT NULL DEFAULT '0',
  `afectaCuentaBancaria` int(11) NOT NULL DEFAULT '0',
  `utilizaCuentaBancaria` char(1) NOT NULL DEFAULT '0',
  `utilizaPagoChequeDiferido` char(1) NOT NULL DEFAULT '0',
  `utilizaSoloMediosDePagoCheque` char(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoTipoDocumento`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TipoDocumento`
--

LOCK TABLES `TipoDocumento` WRITE;
/*!40000 ALTER TABLE `TipoDocumento` DISABLE KEYS */;
INSERT INTO `TipoDocumento` VALUES (1,'Factura CONTADO','1','1','1','1','1','1','1','1','0','A','1','1','1','0',0,-1,1,'0','0','0','0','1',1,1,'0',0,'0','0','0'),(2,'Factura CREDITO','1','1','1','1','1','1','1','1','0','A','1','1','1','0',1,-1,1,'0','0','0','0','1',1,1,'0',0,'0','0','0'),(3,'Factura NOTA DEVOLUCION','1','1','1','1','1','1','1','1','0','A','1','1','1','0',0,1,-1,'0','0','0','0','1',1,1,'0',0,'0','0','0'),(4,'Factura NOTA CREDITO','1','1','1','1','1','1','1','1','0','A','1','1','1','0',-1,1,-1,'0','0','0','0','1',1,1,'0',0,'0','0','0'),(5,'Factura COMPRA PROVEEDOR','1','0','1','1','1','1','1','1','0','A','0','1','1','1',0,1,-1,'1','1','0','0','0',0,0,'0',0,'0','1','0'),(6,'Ajuste de Stock +','1','0','0','0','0','0','1','0','0','A','0','0','0','0',0,1,0,'1','0','0','0','0',0,0,'1',0,'0','0','0'),(7,'Ajuste de Stock -','1','0','0','0','0','0','1','0','0','A','0','0','0','0',0,-1,0,'1','0','0','0','0',0,0,'1',0,'0','0','0'),(8,'Ingreso Inventario Maestro','1','0','0','0','0','0','1','0','0','A','0','0','0','0',0,1,0,'1','0','0','0','0',0,0,'1',0,'0','0','0'),(9,'Recibo','0','0','0','0','1','0','1','1','0','A','0','1','1','0',-1,0,1,'0','0','0','0','0',0,0,'1',0,'0','0','0'),(10,'Ajuste Cuenta Corriente +','0','0','0','0','1','0','1','0','0','A','0','1','1','0',1,0,0,'0','0','0','0','0',0,0,'1',0,'0','0','0'),(11,'Ajuste Cuenta Corriente -','0','0','0','0','1','0','1','0','0','A','0','1','1','0',-1,0,0,'0','0','0','0','0',0,0,'1',0,'0','0','0'),(12,'Orden de Compra','1','0','1','1','1','1','1','1','0','A','0','1','1','0',0,1,-1,'0','0','0','0','0',0,0,'1',0,'0','0','0'),(13,'Fondo de caja','0','0','0','0','1','0','1','0','0','A','0','0','0','0',0,0,1,'0','0','0','0','0',0,0,'1',0,'0','0','0'),(14,'Retiro de caja','0','0','0','0','1','0','1','0','0','A','0','0','0','0',0,0,-1,'0','0','0','0','0',0,0,'1',0,'0','0','0'),(15,'Cambio mercaderia','1','1','0','0','0','0','1','0','0','A','0','1','1','0',0,-1,0,'0','0','0','0','0',0,0,'1',0,'0','0','0'),(16,'Ingreso cheque a caja','0','0','0','0','1','0','1','0','0','A','0','0','0','0',0,0,1,'0','0','0','0','0',0,0,'1',0,'0','0','1');
/*!40000 ALTER TABLE `TipoDocumento` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TipoDocumentoPerfilesUsuarios`
--

DROP TABLE IF EXISTS `TipoDocumentoPerfilesUsuarios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TipoDocumentoPerfilesUsuarios` (
  `codigoTipoDocumento` int(10) unsigned NOT NULL,
  `codigoPerfil` int(10) unsigned NOT NULL,
  PRIMARY KEY (`codigoTipoDocumento`,`codigoPerfil`),
  KEY `fk_TipoDocumentoCodigo` (`codigoTipoDocumento`),
  KEY `fk_PerfilesUsuariosCodigo` (`codigoPerfil`),
  CONSTRAINT `fk_PerfilesUsuariosCodigo` FOREIGN KEY (`codigoPerfil`) REFERENCES `PerfilesUsuarios` (`codigoPerfil`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_TipoDocumentoCodigo` FOREIGN KEY (`codigoTipoDocumento`) REFERENCES `TipoDocumento` (`codigoTipoDocumento`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TipoDocumentoPerfilesUsuarios`
--

LOCK TABLES `TipoDocumentoPerfilesUsuarios` WRITE;
/*!40000 ALTER TABLE `TipoDocumentoPerfilesUsuarios` DISABLE KEYS */;
INSERT INTO `TipoDocumentoPerfilesUsuarios` VALUES (1,1),(1,2),(1,3),(2,1),(2,2),(2,3),(3,1),(3,2),(3,3),(4,1),(4,2),(4,3),(5,1),(5,2),(5,3),(6,1),(6,2),(6,3),(7,1),(7,2),(7,3),(8,1),(9,1),(9,2),(9,3),(10,1),(10,2),(10,3),(11,1),(11,2),(11,3),(12,1),(12,2),(12,3),(13,1),(14,1),(15,1),(15,2),(15,3),(16,1);
/*!40000 ALTER TABLE `TipoDocumentoPerfilesUsuarios` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TipoEstadoDocumento`
--

DROP TABLE IF EXISTS `TipoEstadoDocumento`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TipoEstadoDocumento` (
  `codigoEstadoDocumento` char(1) NOT NULL,
  `descripcionEstadoDocumento` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoEstadoDocumento`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TipoEstadoDocumento`
--

LOCK TABLES `TipoEstadoDocumento` WRITE;
/*!40000 ALTER TABLE `TipoEstadoDocumento` DISABLE KEYS */;
INSERT INTO `TipoEstadoDocumento` VALUES ('A','En edición'),('C','Cancelado'),('E','Emitido'),('G','Guardado'),('P','Pendiente');
/*!40000 ALTER TABLE `TipoEstadoDocumento` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TipoEstadoLiquidacion`
--

DROP TABLE IF EXISTS `TipoEstadoLiquidacion`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TipoEstadoLiquidacion` (
  `codigoTipoEstadoLiquidacion` char(1) NOT NULL,
  `descripcionTipoEstadoLiquidacion` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoTipoEstadoLiquidacion`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TipoEstadoLiquidacion`
--

LOCK TABLES `TipoEstadoLiquidacion` WRITE;
/*!40000 ALTER TABLE `TipoEstadoLiquidacion` DISABLE KEYS */;
INSERT INTO `TipoEstadoLiquidacion` VALUES ('A','Liquidación abierta'),('C','Liquidación cerrada');
/*!40000 ALTER TABLE `TipoEstadoLiquidacion` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TipoMedioDePago`
--

DROP TABLE IF EXISTS `TipoMedioDePago`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TipoMedioDePago` (
  `codigoTipoMedioDePago` int(10) unsigned NOT NULL,
  `descripcionTipoMedioDePago` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoTipoMedioDePago`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TipoMedioDePago`
--

LOCK TABLES `TipoMedioDePago` WRITE;
/*!40000 ALTER TABLE `TipoMedioDePago` DISABLE KEYS */;
INSERT INTO `TipoMedioDePago` VALUES (1,'Efectivo'),(2,'Tarjeta de Credito'),(3,'Cheque'),(4,'Cuenta Bancaria');
/*!40000 ALTER TABLE `TipoMedioDePago` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TipoUsuario`
--

DROP TABLE IF EXISTS `TipoUsuario`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TipoUsuario` (
  `codigoTipoUsuario` int(11) NOT NULL,
  `descripcionTipoUsuario` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoTipoUsuario`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TipoUsuario`
--

LOCK TABLES `TipoUsuario` WRITE;
/*!40000 ALTER TABLE `TipoUsuario` DISABLE KEYS */;
INSERT INTO `TipoUsuario` VALUES (1,'Administrador'),(2,'Operador');
/*!40000 ALTER TABLE `TipoUsuario` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Usuarios`
--

DROP TABLE IF EXISTS `Usuarios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Usuarios` (
  `idUsuario` varchar(45) NOT NULL,
  `claveUsuario` varchar(45) DEFAULT NULL,
  `nombreUsuario` varchar(45) NOT NULL,
  `apellidoUsuario` varchar(45) NOT NULL,
  `tipoUsuario` int(11) NOT NULL DEFAULT '2',
  `esVendedor` char(1) NOT NULL DEFAULT '0',
  `codigoPerfil` int(10) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`idUsuario`),
  KEY `fk_CodigoPerfil` (`codigoPerfil`),
  CONSTRAINT `fk_CodigoPerfil` FOREIGN KEY (`codigoPerfil`) REFERENCES `PerfilesUsuarios` (`codigoPerfil`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Usuarios`
--

LOCK TABLES `Usuarios` WRITE;
/*!40000 ALTER TABLE `Usuarios` DISABLE KEYS */;
INSERT INTO `Usuarios` VALUES ('admin','d033e22ae348aeb5660fc2140aec35850c4da997','Administrador','',1,'0',1);
/*!40000 ALTER TABLE `Usuarios` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-03-25  8:26:08
