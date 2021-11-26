-- MySQL dump 10.13  Distrib 5.5.32, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: khitomer
-- ------------------------------------------------------
-- Server version	5.5.32-0ubuntu0.12.04.1

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
  `codigoProveedor` varchar(10) NOT NULL,
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
  `sincronizadoWeb` char(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoArticulo`),
  KEY `fk_CodigoIva2` (`codigoArticulo`,`codigoProveedor`,`codigoIva`,`tipoCliente`),
  KEY `fk_CodigoMoneda2` (`codigoArticulo`,`codigoProveedor`,`tipoCliente`,`codigoMoneda`),
  KEY `fk_CodigoSubRubro2` (`codigoArticulo`,`codigoProveedor`,`codigoSubRubro`,`tipoCliente`),
  KEY `fk_CodigoProveedor2` (`codigoArticulo`,`codigoProveedor`,`tipoCliente`),
  KEY `index_sincronizadoWeb` (`codigoArticulo`,`sincronizadoWeb`),
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
/*!40000 ALTER TABLE `Bancos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `CargaMantenimientoBatch`
--

DROP TABLE IF EXISTS `CargaMantenimientoBatch`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CargaMantenimientoBatch` (
  `codigoTipoCargaMantenimientoBatch` varchar(100) NOT NULL,
  `codigoTipoCampoCargaMantenimientoBatch` varchar(100) NOT NULL,
  `utilizaCarga` char(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoTipoCargaMantenimientoBatch`,`codigoTipoCampoCargaMantenimientoBatch`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CargaMantenimientoBatch`
--

LOCK TABLES `CargaMantenimientoBatch` WRITE;
/*!40000 ALTER TABLE `CargaMantenimientoBatch` DISABLE KEYS */;
INSERT INTO `CargaMantenimientoBatch` VALUES ('ARTICULOS','activo','0'),('ARTICULOS','cantidadMinimaStock','0'),('ARTICULOS','codigoArticulo','0'),('ARTICULOS','codigoIva','0'),('ARTICULOS','codigoMoneda','0'),('ARTICULOS','codigoSubRubro','0'),('ARTICULOS','descripcionArticulo','0'),('ARTICULOS','descripcionExtendida','0'),('CLIENTES','codigoCliente','0'),('CLIENTES','codigoDepartamento','0'),('CLIENTES','codigoLocalidad','0'),('CLIENTES','codigoPais','0'),('CLIENTES','codigoPostal','0'),('CLIENTES','contacto','0'),('CLIENTES','direccion','0'),('CLIENTES','documento','0'),('CLIENTES','email','0'),('CLIENTES','esquina','0'),('CLIENTES','horario','0'),('CLIENTES','nombreCliente','0'),('CLIENTES','numeroPuerta','0'),('CLIENTES','observaciones','0'),('CLIENTES','razonSocial','0'),('CLIENTES','rut','0'),('CLIENTES','sitioWeb','0'),('CLIENTES','telefono','0'),('CLIENTES','telefono2','0'),('CLIENTES','tipoClasificacion','0'),('PROVEEDORES','codigoCliente','0'),('PROVEEDORES','codigoDepartamento','0'),('PROVEEDORES','codigoLocalidad','0'),('PROVEEDORES','codigoPais','0'),('PROVEEDORES','codigoPostal','0'),('PROVEEDORES','contacto','0'),('PROVEEDORES','direccion','0'),('PROVEEDORES','documento','0'),('PROVEEDORES','email','0'),('PROVEEDORES','esquina','0'),('PROVEEDORES','horario','0'),('PROVEEDORES','nombreCliente','0'),('PROVEEDORES','numeroPuerta','0'),('PROVEEDORES','observaciones','0'),('PROVEEDORES','razonSocial','0'),('PROVEEDORES','rut','0'),('PROVEEDORES','sitioWeb','0'),('PROVEEDORES','telefono','0'),('PROVEEDORES','telefono2','0'),('PROVEEDORES','tipoClasificacion','0');
/*!40000 ALTER TABLE `CargaMantenimientoBatch` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Clientes`
--

DROP TABLE IF EXISTS `Clientes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Clientes` (
  `codigoCliente` varchar(10) NOT NULL,
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
  `codigoPais` int(10) unsigned NOT NULL,
  `codigoDepartamento` int(10) unsigned NOT NULL,
  `codigoLocalidad` int(10) unsigned NOT NULL,
  `esClienteWeb` char(1) NOT NULL DEFAULT '0',
  `sincronizadoWeb` char(1) NOT NULL DEFAULT '0',
  `cantidadMinimaMercaderia` bigint(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoCliente`,`tipoCliente`),
  KEY `fk_Localidades2` (`codigoCliente`,`tipoCliente`,`codigoPais`,`codigoDepartamento`,`codigoLocalidad`),
  CONSTRAINT `fk_Localidades` FOREIGN KEY (`codigoLocalidad`, `codigoDepartamento`, `codigoPais`) REFERENCES `Localidades` (`codigoLocalidad`, `codigoDepartamento`, `codigoPais`) ON DELETE NO ACTION ON UPDATE NO ACTION
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
INSERT INTO `Configuracion` VALUES ('MODO_AFECTACION_CAJA','2','Parametro que indica como afectar los valores de caja, 0 no afecta, 1 afectan los totales de documentos, 2 afectan los medios de pago.'),('MODO_ARTICULO','1','Parametro que indica la modalidad de uso del codigo de articulo, 0 es alfanumerico, 1 es numerico.'),('MODO_CALCULOTOTAL','1','Parametro que indica la forma de calculo de los totales y como se guardan los precios de los articulos. 1 - El precio del articulo incluye IVA. 2 - El precio del articulo no incluye IVA, y se calcula en el total de la factura.'),('MODO_CLIENTE','1','Parametro que indica la modalidad de uso del codigo de cliente, 0 es alfanumerico, 1 es numerico.'),('MODO_IMPRESION_A4','1','Parametro que indica si la hoja se toma como A4 a pesar de las configuraciones pre establecidas.'),('MONEDA_DEFAULT','2','Codigo de moneda por defecto para la facturación y los artículos.'),('MULTI_BD','0','Permite la utilizacion de otra base de datos. 0 - desactivado, 1 activado'),('MULTI_EMPRESA','0','Parametro que indica si se usa multiempresa, 1 - sí, 0 - no.'),('SEPARADOR_MANTENIMIENTO_BATCH',';','Definicion del separador del mantenimiento batch para clientes, proveedores y artículos.'),('TIPO_CIERRE_LIQUIDACION','1','Parametro que indica como se cierran las liquidaciones. 0 - Se cierran al precionar boton de cierre. 1 - Se cierran al precionar boton de cierre y pide autorizacion. 2 - Se abre la ventana de declaracion de valores para poder cerrarse, requiere autorización.'),('VERSION_BD','120','Muestra la verisión de la base de datos. Este dato se utiliza para indicarle a la aplicación la versión de la base de datos, y que la misma realice las actualizaciones necesarias.');
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
-- Table structure for table `Departamentos`
--

DROP TABLE IF EXISTS `Departamentos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Departamentos` (
  `codigoDepartamento` int(10) unsigned NOT NULL,
  `codigoPais` int(10) unsigned NOT NULL,
  `descripcionDepartamento` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoDepartamento`,`codigoPais`),
  KEY `fk_codigoPais` (`codigoPais`),
  CONSTRAINT `fk_codigoPais` FOREIGN KEY (`codigoPais`) REFERENCES `Pais` (`codigoPais`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Departamentos`
--

LOCK TABLES `Departamentos` WRITE;
/*!40000 ALTER TABLE `Departamentos` DISABLE KEYS */;
INSERT INTO `Departamentos` VALUES (1,1,'MONTEVIDEO'),(2,1,'CANELONES'),(3,1,'COLONIA'),(4,1,'MALDONADO'),(5,1,'TACUAREMBO'),(6,1,'SALTO'),(7,1,'FLORIDA'),(8,1,'RIVERA'),(9,1,'SAN JOSE'),(10,1,'DURAZNO'),(11,1,'ARTIGAS'),(12,1,'ROCHA'),(13,1,'LAVALLEJA'),(14,1,'CERRO LARGO'),(15,1,'TREINTA Y TRES'),(16,1,'SORIANO'),(17,1,'PAYSANDU');
/*!40000 ALTER TABLE `Departamentos` ENABLE KEYS */;
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
  `codigoFacturaWeb` bigint(10) unsigned NOT NULL DEFAULT '0',
  `serieDocumento` varchar(45) NOT NULL DEFAULT '',
  `codigoEstadoDocumento` char(1) NOT NULL DEFAULT '',
  `codigoCliente` varchar(10) NOT NULL DEFAULT '0',
  `tipoCliente` int(10) unsigned NOT NULL DEFAULT '0',
  `codigoMonedaDocumento` int(10) unsigned DEFAULT NULL,
  `cotizacionMoneda` decimal(45,8) unsigned NOT NULL DEFAULT '1.00000000',
  `fechaHoraGuardadoDocumentoSQL` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `fechaUltimaModificacionDocumento` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `fechaEmisionDocumento` date NOT NULL DEFAULT '0000-00-00',
  `usuarioUltimaModificacion` varchar(45) DEFAULT NULL,
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
  `codigoEntorno` char(1) NOT NULL DEFAULT '0',
  `observacionesWeb` varchar(256) NOT NULL DEFAULT '',
  `esDocumentoWeb` char(1) NOT NULL DEFAULT '0',
  `direccionWeb` varchar(256) NOT NULL,
  PRIMARY KEY (`codigoDocumento`,`codigoTipoDocumento`),
  KEY `index_codigoDocumento` (`codigoDocumento`,`codigoTipoDocumento`,`serieDocumento`,`codigoEstadoDocumento`),
  KEY `fk_CodigoMonedas2` (`codigoDocumento`,`codigoTipoDocumento`,`codigoEstadoDocumento`,`codigoMonedaDocumento`),
  KEY `index_cliente` (`codigoDocumento`,`codigoTipoDocumento`,`codigoCliente`,`tipoCliente`),
  KEY `index_cliente2` (`codigoDocumento`,`codigoTipoDocumento`,`codigoEstadoDocumento`,`codigoCliente`,`tipoCliente`,`codigoMonedaDocumento`),
  KEY `index_liquidacion` (`codigoDocumento`,`codigoTipoDocumento`,`codigoLiquidacion`,`codigoVendedorLiquidacion`),
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
  KEY `fk_DocumentoExiste2` (`codigoDocumento`,`codigoTipoDocumento`,`numeroLinea`,`codigoArticulo`),
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
  `numeroCuentaBancaria` varchar(45) DEFAULT NULL,
  `codigoBancoCuentaBancaria` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoDocumento`,`codigoTipoDocumento`,`numeroLinea`),
  KEY `fk_MediosDePago2` (`codigoDocumento`,`codigoTipoDocumento`,`codigoMedioPago`),
  KEY `fk_DocumentosMediosDePago2` (`codigoDocumento`,`codigoTipoDocumento`,`numeroLinea`,`codigoMedioPago`,`monedaMedioPago`),
  KEY `fk_CodigoMonedaDocLineasPago2` (`codigoDocumento`,`codigoTipoDocumento`,`numeroLinea`,`monedaMedioPago`),
  KEY `fk_CuentaBancaria` (`codigoDocumento`,`codigoTipoDocumento`,`numeroLinea`,`numeroCuentaBancaria`,`codigoBancoCuentaBancaria`),
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
  `codigoArticulo` varchar(10) DEFAULT NULL,
  KEY `index_codigoArticulo` (`codigoArticulo`)
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
INSERT INTO `ImpresionCampos` VALUES (1,'Razón Social',1,'txtRazonSocialCampo','C.razonSocial'),(2,'Nombre',1,'txtNombreCampo','C.nombreCliente'),(3,'R.U.T.',1,'txtRutCampo','C.rut'),(4,'Direc.',1,'txtDireccionCampo','C.direccion'),(5,'Tel.',1,'txtTelefonoCampo','C.telefono'),(6,'Cód Art.',2,'txtCodigoArticuloCampo','codigoArticulo'),(7,'Des. Art.',2,'txtDescripcionArticuloCampo','descripcionArticulo'),(8,'Pre. U Art.',2,'txtPrecioListaArticuloCampo','precioArticuloUnitario'),(9,'Total linea art.',2,'txtTotalLineaArticuloCampo','precioTotalVenta'),(10,'Fecha doc.',1,'txtFechaDocumentoCampo','Doc.fechaEmisionDocumento'),(11,'Sub total',3,'txtSubTotalCampo','precioSubTotalVenta'),(12,'Total',3,'txtTotalCampo','precioTotalVenta'),(13,'Iva total',3,'txtIvaTotalCampo','precioIvaVenta'),(14,'Iva bas.',3,'txtIvaBasicoCampo','totalIva1'),(15,'Iva min.',3,'txtIvaMinimoCampo','totalIva2'),(16,'Iva exe.',3,'txtIvaExentoCampo','totalIva3'),(17,'Cant. art.',2,'txtCantidadArticuloCampo','CANTIDAD'),(18,'Sim. Mon.',3,'txtSimboloMonedaCampo','simboloMoneda'),(19,'Nro. Doc',1,'txtNumeroDocumentoCampo','Doc.codigoDocumento'),(20,'Serie',1,'txtSerieDocumentoCampo','Doc.serieDocumento'),(21,'X Cli. Final',1,'txtMarcaXDeClienteFinalCampo','\'X\''),(22,'Desc. Doc',1,'txtDescripcionTipoDocumento','TD.descripcionTipoDocumentoImpresora'),(23,'Total Desc.',3,'txtTotalDescuentoAlTotal','Doc.montoDescuentoTotal'),(24,'Obs. Web',3,'txtObservacionesWeb','Doc.observacionesWeb'),(25,'Observaciones.',3,'txtObservacionesDoc','Doc.observaciones');
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
  KEY `fk_VendedorLiquidacion` (`codigoVendedor`),
  KEY `fk_TipoEstadoLiquidacion2` (`codigoLiquidacion`,`codigoVendedor`,`estadoLiquidacion`),
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
  PRIMARY KEY (`codigoListaPrecio`),
  KEY `index_listaActiva` (`codigoListaPrecio`,`activo`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ListaPrecio`
--

LOCK TABLES `ListaPrecio` WRITE;
/*!40000 ALTER TABLE `ListaPrecio` DISABLE KEYS */;
INSERT INTO `ListaPrecio` VALUES (1,'Lista de precio generica','2013-01-01','2049-12-31','admin','1','1');
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
  `sincronizadoWeb` char(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoListaPrecio`,`codigoArticulo`),
  KEY `fk_CodigoListaPrecio2` (`codigoListaPrecio`,`codigoArticulo`,`sincronizadoWeb`),
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
  `codigoCliente` varchar(10) NOT NULL,
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
-- Table structure for table `Localidades`
--

DROP TABLE IF EXISTS `Localidades`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Localidades` (
  `codigoLocalidad` int(10) unsigned NOT NULL,
  `codigoDepartamento` int(10) unsigned NOT NULL,
  `codigoPais` int(10) unsigned NOT NULL,
  `descripcionLocalidad` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoLocalidad`,`codigoDepartamento`,`codigoPais`),
  KEY `fk_codigoDepartamento` (`codigoDepartamento`,`codigoPais`),
  CONSTRAINT `fk_codigoDepartamento` FOREIGN KEY (`codigoDepartamento`, `codigoPais`) REFERENCES `Departamentos` (`codigoDepartamento`, `codigoPais`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Localidades`
--

LOCK TABLES `Localidades` WRITE;
/*!40000 ALTER TABLE `Localidades` DISABLE KEYS */;
INSERT INTO `Localidades` VALUES (1,1,1,'CENTRO'),(1,2,1,'CANELONES'),(1,3,1,'COLONIA DEL SACRAMENTO'),(1,4,1,'MALDONADO'),(1,5,1,'PASO DE LOS TOROS'),(1,6,1,'SALTO'),(1,7,1,'FLORIDA'),(1,8,1,'RIVERA'),(1,10,1,'DURAZNO'),(1,12,1,'ROCHA'),(1,14,1,'MELO'),(1,16,1,'MERCEDES'),(1,17,1,'PAYSANDU'),(2,1,1,'CURVA DE MAROÑAS'),(2,2,1,'SANTA LUCIA'),(2,3,1,'ROSARIO'),(2,4,1,'SAN CARLOS'),(2,7,1,'SARANDI GRANDE'),(3,1,1,'COLON'),(3,2,1,'LOS CERRILLOS'),(3,3,1,'CARMELO'),(3,4,1,'PIRIAPOLIS'),(4,1,1,'SAYAGO'),(4,2,1,'LAS PIEDRAS'),(4,4,1,'PAN DE AZUCAR'),(5,1,1,'CIUDAD VIEJA'),(5,2,1,'LA PAZ'),(5,4,1,'PUNTA DEL ESTE'),(6,1,1,'LA TEJA'),(6,2,1,'TALA'),(7,1,1,'POCITOS'),(7,2,1,'PANDO'),(8,1,1,'PUNTA CARRETAS'),(9,1,1,'CERRO'),(10,1,1,'CORDON'),(11,1,1,'COLON'),(12,1,1,'CERRITO'),(13,1,1,'UNION'),(14,1,1,'BELVEDERE'),(15,1,1,'LA COMERCIAL'),(16,1,1,'ARROYO SECO');
/*!40000 ALTER TABLE `Localidades` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Mantenimientos`
--

DROP TABLE IF EXISTS `Mantenimientos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Mantenimientos` (
  `idConfiguracionMantenimiento` int(10) NOT NULL,
  `clientesUsaTelefono` char(1) NOT NULL DEFAULT '1',
  `clientesUsaTelefono2` char(1) NOT NULL DEFAULT '1',
  `clientesUsaCodigoPostal` char(1) NOT NULL DEFAULT '1',
  `clientesUsaEmail` char(1) NOT NULL DEFAULT '1',
  `clientesUsaContacto` char(1) NOT NULL DEFAULT '1',
  `clientesUsaObservaciones` char(1) NOT NULL DEFAULT '1',
  `clientesUsaHorario` char(1) NOT NULL DEFAULT '1',
  `clientesUsaLocalidad` char(1) NOT NULL DEFAULT '1',
  `clientesUsaEsquina` char(1) NOT NULL DEFAULT '0',
  `clientesUsaNumeroPuerta` char(1) NOT NULL DEFAULT '0',
  `clientesUsaSitioWeb` char(1) NOT NULL DEFAULT '0',
  `clientesUsaValoracion` char(1) NOT NULL DEFAULT '1',
  `clientesUsaAgregarListaPrecio` char(1) NOT NULL DEFAULT '1',
  `clientesUsaCuentaBancaria` char(1) NOT NULL DEFAULT '1',
  `clientesUsaCargaBatch` char(1) NOT NULL DEFAULT '0',
  `articulosUsaTipoIVA` char(1) NOT NULL DEFAULT '1',
  `articulosUsaMoneda` char(1) NOT NULL DEFAULT '1',
  `articulosUsaSubRubro` char(1) NOT NULL DEFAULT '1',
  `articulosUsaListaDePrecio` char(1) NOT NULL DEFAULT '1',
  `articulosUsaCodigoBarras` char(1) NOT NULL DEFAULT '1',
  `articulosUsaCantidadMinima` char(1) NOT NULL DEFAULT '1',
  `articulosUsaDescripcionExtendida` char(1) NOT NULL DEFAULT '1',
  `articulosUsaCheckActivo` char(1) NOT NULL DEFAULT '1',
  `articulosUsaCargaBatch` char(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`idConfiguracionMantenimiento`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Mantenimientos`
--

LOCK TABLES `Mantenimientos` WRITE;
/*!40000 ALTER TABLE `Mantenimientos` DISABLE KEYS */;
INSERT INTO `Mantenimientos` VALUES (1,'1','1','1','1','1','1','1','1','0','0','0','1','1','1','0','1','1','1','1','1','1','1','1','0');
/*!40000 ALTER TABLE `Mantenimientos` ENABLE KEYS */;
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
INSERT INTO `MediosDePago` VALUES (1,'Efectivo Pesos',1,1),(2,'Efectivo Dolares',2,1),(3,'Tarjeta de Credito Pesos',1,2),(4,'Tarjeta de Credito Dolares',2,2),(5,'Cheque Pesos',1,3),(6,'Cheque Dolares',2,3),(7,'Deposito bancario Pesos',1,4),(8,'Deposito bancario Dolares',2,4);
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
INSERT INTO `MenuSistema` VALUES (1,'Sistema'),(2,'Mantenimientos'),(3,'Usuarios'),(4,'Permisos'),(5,'Configuraciones'),(6,'Monedas'),(7,'Rubros'),(8,'Cuentas bancarias'),(9,'Pago de financieras'),(10,'Bancos'),(11,'Localidades'),(12,'Tipos de documentos');
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
INSERT INTO `ModeloImpresion` VALUES (1,'Modelo Contado',14.50,21.50,6.50,11.00,9);
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
INSERT INTO `ModeloImpresionLineas` VALUES (1,1,4.00,4.00,10.00,0),(1,3,10.00,2.70,4.00,0),(1,4,4.00,4.70,10.00,0),(1,7,3.50,7.30,10.00,0),(1,8,17.80,7.30,2.00,2),(1,9,19.70,7.30,2.00,2),(1,10,18.50,4.00,2.00,2),(1,11,19.70,13.40,2.00,2),(1,12,19.70,14.40,2.00,2),(1,13,19.70,13.90,2.00,2),(1,17,2.40,7.30,2.00,2);
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
INSERT INTO `Monedas` VALUES (1,'Pesos','858','UYU','$',1.00000000,0.00000000,'1'),(2,'Dolares','840','USD','U$S',22.00000000,0.00000000,'1');
/*!40000 ALTER TABLE `Monedas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Pais`
--

DROP TABLE IF EXISTS `Pais`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Pais` (
  `codigoPais` int(10) unsigned NOT NULL,
  `descripcionPais` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`codigoPais`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Pais`
--

LOCK TABLES `Pais` WRITE;
/*!40000 ALTER TABLE `Pais` DISABLE KEYS */;
INSERT INTO `Pais` VALUES (1,'Uruguay');
/*!40000 ALTER TABLE `Pais` ENABLE KEYS */;
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
  `permiteCambioRapidoDePrecios` char(1) NOT NULL DEFAULT '0',
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
INSERT INTO `PerfilesUsuarios` VALUES (1,'Administrador','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'),(2,'Administracion-vendedor','1','1','1','1','1','1','1','0','1','1','1','1','0','0','1','1','1','1','1','1','1','1','1','1','0','1','1','1'),(3,'Vendedores','1','1','1','1','1','1','0','0','0','0','1','0','0','0','1','1','0','1','1','1','1','1','1','1','1','1','1','0');
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
  `descripcionReporte` varchar(200) DEFAULT NULL,
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
  `utilizaRubros` char(1) NOT NULL DEFAULT '0',
  `utilizaDesdeCodigoArticulo` char(1) NOT NULL DEFAULT '0',
  `utilizaHastaCodigoArticulo` char(1) NOT NULL DEFAULT '0',
  `utilizaListaPrecio` char(1) NOT NULL DEFAULT '0',
  `utilizaGraficas` char(1) NOT NULL DEFAULT '0',
  `utilizaCuentaBancaria` char(1) NOT NULL DEFAULT '0',
  `utilizaMonedas` char(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoReporte`),
  KEY `fk_CodigoMenu2` (`codigoReporte`,`codigoMenuReporte`),
  CONSTRAINT `fk_CodigoMenu` FOREIGN KEY (`codigoMenuReporte`) REFERENCES `ReportesMenu` (`codigoMenuReporte`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Reportes`
--

LOCK TABLES `Reportes` WRITE;
/*!40000 ALTER TABLE `Reportes` DISABLE KEYS */;
INSERT INTO `Reportes` VALUES (1,1,'Lista de artículos inactivos','SELECT codigoArticulo\'Código\',descripcionArticulo\'Nombre\', fechaAlta\'Fecha de alta\',fechaUltimaModificacion\'Fecha de última modificación\'   FROM Articulos where activo=0;','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(2,1,'Artículos x proveedor','SELECT CLI.nombreCliente\'Proveedor\',concat(AR.codigoArticulo,\' - \',AR.descripcionArticulo)\'Artículo\', AR.fechaAlta\'Fecha de alta\',AR.fechaUltimaModificacion\'Fecha de última modificación\'   FROM Articulos AR join Clientes CLI on CLI.codigoCliente=AR.codigoProveedor and CLI.tipoCliente=AR.tipoCliente where AR.tipoCliente=2 and AR.codigoProveedor=\'@_codigoProveedor\';','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(3,2,'Listado de clientes','SELECT concat(codigoCliente,\' - \',nombreCliente)\'Cliente\',razonSocial\'Razón social\',direccion\'Dirección\',telefono\'Telefono\',fechaAlta\'Fecha de alta\'  FROM Clientes where tipoCliente=1;','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(4,3,'Listado de proveedores','SELECT concat(codigoCliente,\' - \',nombreCliente)\'Cliente\',razonSocial\'Razón social\',direccion\'Dirección\',telefono\'Telefono\',fechaAlta\'Fecha de alta\'  FROM Clientes where tipoCliente=2;','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(5,5,'Movimientos x cliente','select concat(CLI.codigoCliente,\' - \',(case when CLI.razonSocial=\'\' then CLI.nombreCliente else CLI.razonSocial end))\'Cliente\', concat(TDOC.descripcionTipoDocumento,\' (\',DOC.serieDocumento,\'-\',DOC.codigoDocumento,\')\')\'Documento\', DOC.fechaEmisionDocumento\'Fecha Doc.\', MON.simboloMoneda\'\', case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(0.00,2) end \'Debe\', case when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \'Haber\' from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente where DOC.tipoCliente=1 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\'@_codigoCliente\' order by DOC.fechaEmisionDocumento asc ;','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(6,5,'Movimientos x proveedor','select concat(CLI.codigoCliente,\' - \',(case when CLI.razonSocial=\'\' then CLI.nombreCliente else CLI.razonSocial end))\'Proveedor\', concat(TDOC.descripcionTipoDocumento,\' (\',DOC.serieDocumento,\'-\',DOC.codigoDocumento,\')\')\'Documento\', DOC.fechaEmisionDocumento\'Fecha Doc.\', MON.simboloMoneda\'\', case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(0.00,2) end \'Debe\', case when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \'Haber\' from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente where DOC.tipoCliente=2 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\'@_codigoProveedor\' order by DOC.fechaEmisionDocumento asc ;','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(7,5,'Saldo de cliente en Pesos','select concat(CLI.codigoCliente,\' - \',(case when CLI.razonSocial=\'\' then CLI.nombreCliente else CLI.razonSocial end))\'Cliente\', MON.simboloMoneda\'\', sum(case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(DOC.precioTotalVenta*-1,2) end)\'Saldo en Pesos\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.tipoCliente=1 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\'@_codigoCliente\' and DOC.codigoMonedaDocumento=1 ;','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(8,5,'Saldo de cliente en Dolares','select concat(CLI.codigoCliente,\' - \',(case when CLI.razonSocial=\'\' then CLI.nombreCliente else CLI.razonSocial end))\'Cliente\', MON.simboloMoneda\'\', sum(case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(DOC.precioTotalVenta*-1,2) end)\'Saldo en Dolares\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.tipoCliente=1  and DOC.codigoEstadoDocumento in (\'E\',\'G\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\'@_codigoCliente\' and DOC.codigoMonedaDocumento=2;','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(9,5,'Saldo de proveedores en Pesos','select concat(CLI.codigoCliente,\' - \',(case when CLI.razonSocial=\'\' then CLI.nombreCliente else CLI.razonSocial end))\'Proveedor\', MON.simboloMoneda\'\', sum(case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(DOC.precioTotalVenta*-1,2) end)\'Saldo en Pesos\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.tipoCliente=2 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\'@_codigoProveedor\' and DOC.codigoMonedaDocumento=1;','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(10,5,'Saldo de proveedores en Dolares','select concat(CLI.codigoCliente,\' - \',(case when CLI.razonSocial=\'\' then CLI.nombreCliente else CLI.razonSocial end))\'Proveedor\', MON.simboloMoneda\'\', sum(case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(DOC.precioTotalVenta*-1,2) end)\'Saldo en Pesos\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.tipoCliente=2 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\'@_codigoProveedor\' and DOC.codigoMonedaDocumento=2;','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(11,6,'Artículos mas vendidos','select concat(DOCL.codigoArticulo,\' - \',AR.descripcionArticulo)\'Artículo\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\'Cantidad ventas\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo where DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.afectaTotales!=0 group by DOCL.codigoArticulo order by 2 desc limit @_cantidad ;','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(12,6,'Artículos mas vendidos entre fechas','select concat(DOCL.codigoArticulo,\' - \',AR.descripcionArticulo)\'Artículo\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\'Cantidad ventas\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo  where DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.afectaTotales!=0 and DOC.fechaEmisionDocumento between \'@_desde\' and \'@_hasta\'  group by DOCL.codigoArticulo order by 2 desc limit @_cantidad ;','0','0','0','1','0','1','1','0','0','0','0','0','0','0','0','0','0','0'),(13,3,'Alta de proveedores entre fechas','SELECT  concat(CLI.codigoCliente,\' - \',CLI.nombreCliente)\'Proveedor\', CLI.razonSocial\'Razón Social\', CLI.fechaAlta\'Alta en sistema\', concat(USU.nombreUsuario,\' \',USU.apellidoUsuario)\'Usuario del alta\' FROM Clientes CLI  join Usuarios USU on USU.idUsuario=CLI.usuarioAlta where CLI.tipoCliente=2 and CLI.fechaAlta between \'@_desde\' and \'@_hasta\' + INTERVAL 1 DAY order by CLI.fechaAlta asc;','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0'),(14,4,'Ventas x vendedor entre fechas','SELECT concat(USU.nombreUsuario,\' \',USU.apellidoUsuario)\'Vendedor\', concat(TDOC.descripcionTipoDocumento,\' (\',DOC.codigoDocumento,\'-\',DOC.serieDocumento,\')\')\'Documento\', case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta,2)  else ROUND(DOC.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda ),2) end \'Total $\', case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta,2)  else ROUND(DOC.precioTotalVenta/(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=2 ),2) end \'Total U$S\' FROM Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where  DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.esDocumentoDeVenta=\'1\' and DOC.fechaEmisionDocumento  between \'@_desde\' and \'@_hasta\' and DOC.codigoVendedorComisiona=\'@_codigoVendedor\' order by DOC.fechaEmisionDocumento asc ;','0','0','0','0','0','1','1','1','0','0','0','0','0','0','0','0','0','0'),(15,2,'Alta de clientes entre fechas','SELECT  concat(CLI.codigoCliente,\' - \',CLI.nombreCliente)\'Cliente\', CLI.razonSocial\'Razón Social\', CLI.fechaAlta\'Alta en sistema\', concat(USU.nombreUsuario,\' \',USU.apellidoUsuario)\'Usuario del alta\' FROM Clientes CLI  join Usuarios USU on USU.idUsuario=CLI.usuarioAlta where CLI.tipoCliente=1 and CLI.fechaAlta between \'@_desde\' and \'@_hasta\' + INTERVAL 1 DAY order by CLI.fechaAlta asc;','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0'),(16,7,'Documentos anulados entre fechas','SELECT concat(TDOC.descripcionTipoDocumento,\' (\',DOC.serieDocumento,\'-\',DOC.codigoDocumento,\')\')\'Documento\', case when CLI.nombreCliente is null then \'\' else CLI.nombreCliente end  \'Cliente\', concat(MON.simboloMoneda,\'      \',DOC.precioTotalVenta)\'Total\', DOC.fechaEmisionDocumento\'Fecha Doc.\', concat(USU.nombreUsuario,\' \',USU.apellidoUsuario)\'Usuario que anulo\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento left join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento join Usuarios USU on USU.idUsuario=DOC.usuarioUltimaModificacion where DOC.codigoEstadoDocumento=\'C\' and DOC.fechaEmisionDocumento between \'@_desde\' and \'@_hasta\' ;','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0'),(17,7,'Total de documentos entre fechas','SELECT TDOC.descripcionTipoDocumento\'Documentos\', count(DOC.codigoDocumento+DOC.codigoTipoDocumento)\'Cantidad\' FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento where DOC.codigoEstadoDocumento in (\'G\',\'E\') and DOC.fechaEmisionDocumento between \'@_desde\' and \'@_hasta\' group by TDOC.descripcionTipoDocumento ;','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0'),(18,8,'Stock total real','SELECT AR.codigoArticulo\'Código\',AR.descripcionArticulo\'Nombre\',AR.descripcionExtendida\'Descripción extendida\',case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \'cantidad\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\'E\',\'G\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \'cantidad\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\'E\',\'G\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end \'Cantidad Real\'  ,case when AR.activo=1 then \'activo\' else \'¡ARTÍCULO INACTIVO!\' end\'Estado\' FROM Articulos AR ;','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(19,4,'Ventas por cliente entre fechas','SELECT  concat((case when CLI.razonSocial=\'\' then CLI.nombreCliente else CLI.razonSocial end),\' (\',DOC.codigoCliente,\')\')\'CLIENTE\', concat(TDOC.descripcionTipoDocumento,\' (\',DOC.codigoDocumento,\'-\',DOC.serieDocumento,\')\')\'Documento\', DOC.fechaEmisionDocumento\'FECHA DOCUMENTO\', case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta,2)  else ROUND(DOC.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda ),2) end \'Total $\', case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta,2)  else ROUND(DOC.precioTotalVenta/(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=2 ),2) end \'Total U$S\' FROM Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where  DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.esDocumentoDeVenta=\'1\' and DOC.codigoCliente=\'@_codigoCliente\' and  DOC.tipoCliente=1 and DOC.fechaEmisionDocumento  between \'@_desde\' and \'@_hasta\' order by DOC.fechaEmisionDocumento desc ;','1','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0'),(20,6,'Artículos menos vendidos','select concat(DOCL.codigoArticulo,\' - \',AR.descripcionArticulo)\'Artículo\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\'Cantidad ventas\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo where DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.afectaTotales!=0 group by DOCL.codigoArticulo order by 2 asc limit @_cantidad ;','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(21,4,'Venta de artículo entre fechas','select DOC.fechaEmisionDocumento\'Fecha\', concat(DOCL.codigoArticulo,\' - \',AR.descripcionArticulo)\'Artículo\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\'Cantidad ventas\'   from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo    where DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.esDocumentoDeVenta=\'1\'  and DOC.fechaEmisionDocumento between \'@_desde\' and \'@_hasta\'  and DOCL.codigoArticulo=\'@_codigoArticulo\' group by DOC.fechaEmisionDocumento,DOCL.codigoArticulo order by 1,2 asc;','0','0','1','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0'),(22,8,'Control stock bajo mínimo','select concat(AR.codigoArticulo,\' - \',AR.descripcionArticulo)\'ARTÍCULO\', AR.cantidadMinimaStock \'MÍNIMO STOCK\', case when (SELECT  sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)  from    Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\'E\',\'G\') and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS   where DOCS.codigoTipoDocumento=8   and DOCS.codigoEstadoDocumento in (\'E\',\'G\')   order by DOCS.codigoDocumento desc limit 1)) is null then 0 else  (SELECT   sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)   from    Documentos DOC     join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento      and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\'E\',\'G\') and DOCL.codigoArticulo=AR.codigoArticulo   and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS   where DOCS.codigoTipoDocumento=8   and DOCS.codigoEstadoDocumento in (\'E\',\'G\')  order by DOCS.codigoDocumento desc limit 1))  end \'STOCK REAL\', case when  (SELECT  sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) from    Documentos DOC    join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento     and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\'E\',\'G\',\'P\') and DOCL.codigoArticulo=AR.codigoArticulo   and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS   where DOCS.codigoTipoDocumento=8   and DOCS.codigoEstadoDocumento in (\'E\',\'G\')   order by DOCS.codigoDocumento desc limit 1)) is null then 0 else (SELECT   sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) from    Documentos DOC    join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento     and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\'E\',\'G\',\'P\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS   where DOCS.codigoTipoDocumento=8   and DOCS.codigoEstadoDocumento in (\'E\',\'G\')   order by DOCS.codigoDocumento desc limit 1)) end  \'STOCK PREVISTO\'  from  FaltaStock FS join Articulos AR on AR.codigoArticulo=FS.codigoArticulo where cantidadArticulosSinStock!=0 ;','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(23,8,'Stock por sub rubro','SELECT AR.codigoArticulo\'Código\',AR.descripcionArticulo\'Nombre\',AR.descripcionExtendida\'Descripción extendida\' ,case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \'cantidad\'  FROM Documentos DOC   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\'E\',\'G\')  and DOCL.codigoArticulo=AR.codigoArticulo     and DOC.fechaHoraGuardadoDocumentoSQL>=    (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\'E\',\'G\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \'cantidad\'  FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos  where codigoTipoDocumento=8 and codigoEstadoDocumento in (\'E\',\'G\')  order by codigoDocumento desc limit 1)  group by DOCL.codigoArticulo) end \'Stock Real\'  FROM Articulos AR  where AR.codigoSubRubro=\'@_codigoSubRubro\' order by CAST(AR.codigoArticulo AS SIGNED)  ;','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0'),(24,9,'Total por Medios de Pago','select  concat(MP.descripcionMedioPago,\' \',MON.simboloMoneda) \'Total Medios de pago Efectivo: \', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\'Valor Total:\' from MediosDePago MP join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and D.codigoTipoDocumento=DLP.codigoTipoDocumento join TipoDocumento T on   T.codigoTipoDocumento=D.codigoTipoDocumento join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago where  MP.codigoTipoMedioDePago=1 and  T.afectaTotales!=0  \r\nand D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\') and D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and D.codigoVendedorLiquidacion=\'@_codigoVendedor\' group by MP.monedaMedioPago; select   concat(MP.descripcionMedioPago,\' \',MON.simboloMoneda) \'Total Medios de pago Tarjetas: \', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\'Valor Total:\' from MediosDePago MP\r\njoin DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and   D.codigoTipoDocumento=DLP.codigoTipoDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago\r\nwhere  MP.codigoTipoMedioDePago=2 and  T.afectaTotales!=0  and D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\') and D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and  D.codigoVendedorLiquidacion=\'@_codigoVendedor\' group by MP.monedaMedioPago; select  concat(MP.descripcionMedioPago,\' \',MON.simboloMoneda) \'Total Medios de pago Cheques : \', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\'Valor Total:\' from MediosDePago MP  join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago where  MP.codigoTipoMedioDePago=3 and T.afectaTotales!=0  and D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\') and D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and  D.codigoVendedorLiquidacion=\'@_codigoVendedor\' group by MP.monedaMedioPago; select  concat(MP.descripcionMedioPago,\' \',MON.simboloMoneda) \'Total Medios de pago Deposito Bancario : \',  case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\'Valor Total:\'  from MediosDePago MP   join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago  join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento  join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago  where  MP.codigoTipoMedioDePago=4 and T.afectaTotales!=0  and D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\')  and D.codigoLiquidacion=\'@_codigoLiquidacionCaja\'  and  D.codigoVendedorLiquidacion=\'@_codigoVendedor\' group by MP.monedaMedioPago;','0','0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0','0'),(25,9,'Total por Documentos y Medios de Pago','select concat(\'Total en \',M.descripcionMoneda,\' \',M.simboloMoneda) as \'Total en documentos:\', sum(D.precioTotalVenta*T.afectaTotales ) as \'Valor Total:\' FROM Documentos D  join Monedas M on M.codigoMoneda=D.codigoMonedaDocumento  join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  where D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and D.codigoVendedorLiquidacion=\'@_codigoVendedor\' and T.afectaTotales!=0 and D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\')  group by M.codigoMoneda;select  concat(MP.descripcionMedioPago,\' \',MON.simboloMoneda) \'Total Medios de pago Efectivo: \', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\'Valor Total:\' from MediosDePago MP join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and D.codigoTipoDocumento=DLP.codigoTipoDocumento join TipoDocumento T on   T.codigoTipoDocumento=D.codigoTipoDocumento join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago where  MP.codigoTipoMedioDePago=1 and  T.afectaTotales!=0  \r\nand D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\') and D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and D.codigoVendedorLiquidacion=\'@_codigoVendedor\' group by MP.monedaMedioPago; select   concat(MP.descripcionMedioPago,\' \',MON.simboloMoneda) \'Total Medios de pago Tarjetas: \', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\'Valor Total:\' from MediosDePago MP\r\njoin DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and   D.codigoTipoDocumento=DLP.codigoTipoDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago\r\nwhere  MP.codigoTipoMedioDePago=2 and  T.afectaTotales!=0  and D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\') and D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and  D.codigoVendedorLiquidacion=\'@_codigoVendedor\' group by MP.monedaMedioPago; select  concat(MP.descripcionMedioPago,\' \',MON.simboloMoneda) \'Total Medios de pago Cheques : \', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\'Valor Total:\' from MediosDePago MP  join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago where  MP.codigoTipoMedioDePago=3 and T.afectaTotales!=0  and D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\') and D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and  D.codigoVendedorLiquidacion=\'@_codigoVendedor\' group by MP.monedaMedioPago; select  concat(MP.descripcionMedioPago,\' \',MON.simboloMoneda) \'Total Medios de pago Deposito Bancario: \',  case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\'Valor Total:\'  from MediosDePago MP   join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago  join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento  join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago  where   MP.codigoTipoMedioDePago=4 and T.afectaTotales!=0            and D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\') and D.codigoLiquidacion=\'@_codigoLiquidacionCaja\' and  D.codigoVendedorLiquidacion=\'@_codigoVendedor\'  group by MP.monedaMedioPago;','0','0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0','0'),(26,4,'Ventas x vendedor entre fechas sin imp.','SELECT concat(USU.nombreUsuario,\' \',USU.apellidoUsuario)\'Vendedor\',  concat(TDOC.descripcionTipoDocumento,\' (\',DOC.codigoDocumento,\'-\',DOC.serieDocumento,\')\')\'Documento\',   case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta,2)  else ROUND(DOC.precioSubTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda ),2) end \'Total $\',   case when MON.codigoMoneda=2 then  ROUND(DOC.precioSubTotalVenta,2)  else ROUND(DOC.precioSubTotalVenta/(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=2 ),2) end \'Total U$S\'  FROM Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where  DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.esDocumentoDeVenta=\'1\' and DOC.fechaEmisionDocumento   between \'@_desde\' and \'@_hasta\' and DOC.codigoVendedorComisiona=\'@_codigoVendedor\' order by DOC.fechaEmisionDocumento asc ; ','0','0','0','0','0','1','1','1','0','0','0','0','0','0','0','0','0','0'),(27,1,'Lista total de artículos activos','SELECT codigoArticulo\'Código\',descripcionArticulo\'Nombre\', fechaAlta\'Fecha de alta\',fechaUltimaModificacion\'Fecha de última modificación\'  FROM Articulos where activo=1; ','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(28,1,'Lista total de artículos','SELECT codigoArticulo\'Código\',descripcionArticulo\'Nombre\', fechaAlta\'Fecha de alta\',fechaUltimaModificacion\'Fecha de última modificación\'  FROM Articulos;','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),(29,8,'Stock por rubro','SELECT AR.codigoArticulo\'Código\',AR.descripcionArticulo\'Nombre\',AR.descripcionExtendida\'Descripción extendida\' , case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \'cantidad\'  FROM Documentos DOC   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\'E\',\'G\')  and DOCL.codigoArticulo=AR.codigoArticulo     and DOC.fechaHoraGuardadoDocumentoSQL>=    (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\'E\',\'G\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \'cantidad\'  FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos  where codigoTipoDocumento=8 and codigoEstadoDocumento in (\'E\',\'G\')  order by codigoDocumento desc limit 1)  group by DOCL.codigoArticulo) end \'Stock Real\'   FROM Articulos AR join SubRubros SUBRUB on SUBRUB.codigoSubRubro=AR.codigoSubRubro where SUBRUB.codigoRubro=\'@_codigoRubro\' order by CAST(AR.codigoArticulo AS SIGNED);','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0'),(30,10,'Precio de artículos por lista de precio','select AR.codigoArticulo\'CODIGO\', AR.descripcionArticulo\'DETALLE\', concat(MON.simboloMoneda,\' \',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2))\'Precio sin I.V.A\', concat(MON.simboloMoneda,\' \',LPA.precioArticulo)\'Precio I.V.A Inc.\' FROM Articulos AR JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda JOIN Ivas IV on IV.codigoIva=AR.codigoIva  where AR.activo=1 and LPA.codigoListaPrecio=\'@_codigoListaPrecio\' order by 2;','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0'),(31,10,'Precio de artículos por lista de precio y stock mayor a','select AR.codigoArticulo\'CODIGO\', AR.descripcionArticulo\'DETALLE\', concat(MON.simboloMoneda,\' \',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2))\'Precio sin I.V.A\', concat(MON.simboloMoneda,\' \',LPA.precioArticulo)\'Precio I.V.A Inc.\' FROM Articulos AR JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda JOIN Ivas IV on IV.codigoIva=AR.codigoIva   where AR.activo=1 and (case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \'cantidad\'  FROM Documentos DOC   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\'E\',\'G\')  and DOCL.codigoArticulo=AR.codigoArticulo     and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\'E\',\'G\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \'cantidad\'  FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\'E\',\'G\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos  where codigoTipoDocumento=8 and codigoEstadoDocumento in (\'E\',\'G\')  order by codigoDocumento desc limit 1)  group by DOCL.codigoArticulo) end) > \'@_cantidad\' and LPA.codigoListaPrecio=\'@_codigoListaPrecio\' order by 2 ;','0','0','0','1','0','0','0','0','0','0','0','0','0','0','1','0','0','0'),(32,4,'Ventas por rubro entre fechas','select  concat(SR.codigoSubRubro,\' - \',SR.descripcionSubRubro)\'SubRubro\',  sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\'Cantidad ventas\' , sum(case when MON.codigoMoneda=1 then  ROUND(DOCL.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(DOCL.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda )*TDOC.afectaTotales,2) end) \'Total $\',  sum(case when MON.codigoMoneda=2 then  ROUND(DOCL.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(DOCL.precioTotalVenta/(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=2 )*TDOC.afectaTotales,2) end) \'Total U$S\'    from  DocumentosLineas DOCL  left join Documentos DOC  on DOC.codigoDocumento=DOCL.codigoDocumento and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo  join SubRubros SR on SR.codigoSubRubro=AR.codigoSubRubro join Rubros RU on RU.codigoRubro=SR.codigoRubro  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.esDocumentoDeVenta=\'1\'   and DOC.fechaEmisionDocumento  between \'@_desde\' and \'@_hasta\'   and RU.codigoRubro=\'@_codigoRubro\'  group by RU.codigoRubro,SR.codigoSubRubro  order by RU.descripcionRubro,SR.descripcionSubRubro; ','0','0','0','0','0','1','1','0','0','0','0','1','0','0','0','0','0','0'),(33,10,'Precio de artículos por lista de precio y rubros','select AR.codigoArticulo\'CODIGO\', AR.descripcionArticulo\'DETALLE\', concat(MON.simboloMoneda,\' \',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2))\'Precio sin I.V.A\', concat(MON.simboloMoneda,\' \',LPA.precioArticulo)\'Precio I.V.A Inc.\'  FROM Articulos AR  JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda  JOIN Ivas IV on IV.codigoIva=AR.codigoIva   JOIN SubRubros SUB on SUB.codigoSubRubro=AR.codigoSubRubro JOIN Rubros RUB on RUB.codigoRubro=SUB.codigoRubro   where AR.activo=1 and LPA.codigoListaPrecio=\'@_codigoListaPrecio\'  and RUB.codigoRubro=\'@_codigoRubro\' order by 2;','0','0','0','0','0','0','0','0','0','0','0','1','0','0','1','0','0','0'),(34,10,'Precio de artículos por lista de precio y sub rubros','select AR.codigoArticulo\'CODIGO\', AR.descripcionArticulo\'DETALLE\', concat(MON.simboloMoneda,\' \',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2))\'Precio sin I.V.A\', concat(MON.simboloMoneda,\' \',LPA.precioArticulo)\'Precio I.V.A Inc.\'  FROM Articulos AR  JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda  JOIN Ivas IV on IV.codigoIva=AR.codigoIva   JOIN SubRubros SUB on SUB.codigoSubRubro=AR.codigoSubRubro JOIN Rubros RUB on RUB.codigoRubro=SUB.codigoRubro  where AR.activo=1 and LPA.codigoListaPrecio=\'@_codigoListaPrecio\'  and SUB.codigoSubRubro=\'@_codigoSubRubro\' order by 2; ','0','0','0','0','0','0','0','0','0','1','0','0','0','0','1','0','0','0'),(35,12,'Totales por Cuenta Bancaria','select   CB.numeroCuentaBancaria\'Cuenta\',BAN.descripcionBanco\'Banco\', concat(MON.descripcionMoneda,\' \',MON.simboloMoneda)\'Moneda\',ROUND(sum(case when T.utilizaCuentaBancaria=1 then case when (DLP.importePago*T.afectaCuentaBancaria) is null then 0.00 else  (DLP.importePago*T.afectaCuentaBancaria) end else case when (DLP.importePago*T.afectaTotales) is null then 0.00 else (DLP.importePago*T.afectaTotales) end  end),2)\'Valor Total:\' from DocumentosLineasPago DLP  join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento     join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento                        join Monedas MON on MON.codigoMoneda=DLP.monedaMedioPago                       join CuentaBancaria CB on CB.numeroCuentaBancaria=DLP.numeroCuentaBancaria and CB.codigoBanco=DLP.codigoBancoCuentaBancaria 					  join Bancos BAN on BAN.codigoBanco=CB.codigoBanco   where  D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\') and CB.numeroCuentaBancaria=\'@_numeroCuentaBancaria\' and CB.codigoBanco=\'@_numeroBancoCuentaBancaria\'   group by CB.numeroCuentaBancaria , CB.codigoBanco, MON.codigoMoneda order by CB.numeroCuentaBancaria, MON.codigoMoneda;','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0'),(36,12,'Totales por Cuenta Bancaria entre fechas','select      CB.numeroCuentaBancaria\'Cuenta\',BAN.descripcionBanco\'Banco\', concat(MON.descripcionMoneda,\' \',MON.simboloMoneda)\'Moneda\',ROUND(sum(case when T.utilizaCuentaBancaria=1    then     case when (DLP.importePago*T.afectaCuentaBancaria) is null then 0.00 else  (DLP.importePago*T.afectaCuentaBancaria) end    else   case when (DLP.importePago*T.afectaTotales) is null then 0.00 else (DLP.importePago*T.afectaTotales) end    end),2)\'Valor Total:\'  from DocumentosLineasPago DLP     join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento    join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DLP.monedaMedioPago  join CuentaBancaria CB on CB.numeroCuentaBancaria=DLP.numeroCuentaBancaria and CB.codigoBanco=DLP.codigoBancoCuentaBancaria  	  join Bancos BAN on BAN.codigoBanco=CB.codigoBanco where  D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\')  and CB.numeroCuentaBancaria=\'@_numeroCuentaBancaria\'   and CB.codigoBanco=\'@_numeroBancoCuentaBancaria\'  and D.fechaEmisionDocumento between \'@_desde\' and \'@_hasta\'  group by CB.numeroCuentaBancaria , CB.codigoBanco, MON.codigoMoneda  order by CB.numeroCuentaBancaria, MON.codigoMoneda;','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','1','0'),(37,12,'Total Cuenta Bancaria entre fechas por moneda','select   concat(DLP.codigoDocumento,\' - \',T.descripcionTipoDocumento,\' (\',D.fechaEmisionDocumento,\')\')\'Documento (Fecha)\',  concat(CB.numeroCuentaBancaria,\' - \',BAN.descripcionBanco)\'Cuenta\',   concat(MON.descripcionMoneda,\' \',MON.simboloMoneda)\'Moneda\',  ROUND(sum(case when T.utilizaCuentaBancaria=1    then     case when (DLP.importePago*T.afectaCuentaBancaria) is null then 0.00 else  (DLP.importePago*T.afectaCuentaBancaria) end    else   case when (DLP.importePago*T.afectaTotales) is null then 0.00 else (DLP.importePago*T.afectaTotales) end    end),2)\'Valor Total:\'  from DocumentosLineasPago DLP     join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento     join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento    join Monedas MON on MON.codigoMoneda=DLP.monedaMedioPago   join CuentaBancaria CB on CB.numeroCuentaBancaria=DLP.numeroCuentaBancaria and CB.codigoBanco=DLP.codigoBancoCuentaBancaria  	   join Bancos BAN on BAN.codigoBanco=CB.codigoBanco   where  D.codigoEstadoDocumento not in (\'C\',\'A\',\'P\')  and CB.numeroCuentaBancaria=\'@_numeroCuentaBancaria\'   and CB.codigoBanco=\'@_numeroBancoCuentaBancaria\'   and D.fechaEmisionDocumento between \'@_desde\' and \'@_hasta\'    and MON.codigoMoneda=\'@_codigoMonedaReporte\'  group by DLP.codigoDocumento,CB.numeroCuentaBancaria , CB.codigoBanco, MON.codigoMoneda  order by D.fechaEmisionDocumento,DLP.codigoDocumento, T.codigoTipoDocumento, CB.numeroCuentaBancaria, MON.codigoMoneda;','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','1','1'),(38,4,'Ventas entre fechas','select   concat(DOC.codigoDocumento,\' - \',TDOC.descripcionTipoDocumento,\' (\',DOC.fechaEmisionDocumento,\')\')\'Documento (Fecha)\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(DOC.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda )*TDOC.afectaTotales,2) end) \'Total $\',  sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(DOC.precioTotalVenta/(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=2 )*TDOC.afectaTotales,2) end) \'Total U$S\'     from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\'G\',\'E\') and TDOC.esDocumentoDeVenta=\'1\'   and DOC.fechaEmisionDocumento between \'@_desde\' and \'@_hasta\'    group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0');
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
  CONSTRAINT `fk_codigoReporte` FOREIGN KEY (`codigoReporte`) REFERENCES `Reportes` (`codigoReporte`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Configuracion de las columnas del reporte';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ReportesConfiguracion`
--

LOCK TABLES `ReportesConfiguracion` WRITE;
/*!40000 ALTER TABLE `ReportesConfiguracion` DISABLE KEYS */;
INSERT INTO `ReportesConfiguracion` VALUES (5,4,'2','0','','MONTO'),(5,5,'2','0','','MONTO'),(6,4,'2','0','','MONTO'),(6,5,'2','0','','MONTO'),(7,2,'2','0','','MONTO'),(8,2,'2','0','','MONTO'),(9,2,'2','0','','MONTO'),(10,2,'2','0','','MONTO'),(14,2,'2','1','','MONTO'),(14,3,'2','1','','MONTO'),(17,1,'1','1','','TEXTO'),(18,3,'1','0','','TEXTO'),(18,4,'1','0','','TEXTO'),(19,3,'2','0','','MONTO'),(19,4,'2','0','','MONTO'),(22,0,'0','0','','TEXTO'),(24,1,'2','0','','MONTO'),(25,1,'2','0','','MONTO'),(26,2,'2','1','','MONTO'),(26,3,'2','1','','MONTO'),(32,0,'0','0','','TEXTO'),(32,1,'2','1','','TEXTO'),(32,2,'2','1','','MONTO'),(32,3,'2','1','','MONTO'),(35,3,'2','0','','MONTO'),(36,3,'2','0','','MONTO'),(37,3,'2','1','','MONTO'),(38,0,'0','0','','TEXTO'),(38,1,'2','1','','MONTO'),(38,2,'2','1','','MONTO');
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
INSERT INTO `ReportesMenu` VALUES (1,'Artículos'),(2,'Clientes'),(3,'Proveedores'),(4,'Ventas'),(5,'Cuenta corriente credito'),(6,'Ranking\'s'),(7,'Documentos'),(8,'Stock'),(9,'Caja'),(10,'Listas de precio'),(11,'Cuenta corriente mercaderia'),(12,'Cuentas bancarias');
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
  `sincronizadoWeb` char(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoRubro`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Rubros`
--

LOCK TABLES `Rubros` WRITE;
/*!40000 ALTER TABLE `Rubros` DISABLE KEYS */;
INSERT INTO `Rubros` VALUES (1,'Sin clasificar','0');
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
  `sincronizadoWeb` char(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoSubRubro`),
  KEY `fk_codigoRubro` (`codigoRubro`),
  KEY `fk_CodigoRubros` (`codigoRubro`),
  CONSTRAINT `fk_codigoRubro` FOREIGN KEY (`codigoRubro`) REFERENCES `Rubros` (`codigoRubro`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_CodigoRubros` FOREIGN KEY (`codigoRubro`) REFERENCES `Rubros` (`codigoRubro`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `SubRubros`
--

LOCK TABLES `SubRubros` WRITE;
/*!40000 ALTER TABLE `SubRubros` DISABLE KEYS */;
INSERT INTO `SubRubros` VALUES (1,1,'Sin clasificar','0');
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
INSERT INTO `TipoCheque` VALUES (1,'Sin clasificación'),(2,'Diferido'),(3,'Al portador'),(4,'Cruzado');
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
  `afectaCuentaCorrienteMercaderia` int(11) NOT NULL DEFAULT '0',
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
  `esDocumentoDeVenta` char(1) NOT NULL DEFAULT '0',
  `descripcionTipoDocumentoImpresora` varchar(45) NOT NULL DEFAULT 'CONTADO',
  `utilizaArticulosInactivos` char(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`codigoTipoDocumento`),
  KEY `index_utilizaArticulos` (`codigoTipoDocumento`,`utilizaArticulos`),
  KEY `index_utilizaClientes` (`codigoTipoDocumento`,`utilizaCliente`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TipoDocumento`
--

LOCK TABLES `TipoDocumento` WRITE;
/*!40000 ALTER TABLE `TipoDocumento` DISABLE KEYS */;
INSERT INTO `TipoDocumento` VALUES (1,'Factura CONTADO','1','1','1','1','1','1','1','1','0','A','1','1','1','0',0,0,-1,1,'0','0','0','0','1',1,1,'0',0,'0','0','0','1','CONTADO','0'),(2,'Factura CREDITO','1','1','1','1','1','1','1','1','0','A','1','1','1','0',1,0,-1,1,'0','0','0','0','1',1,1,'0',0,'0','0','0','1','CREDITO','0'),(3,'Factura DEVOLUCION CONTADO','1','1','1','1','1','1','1','1','0','A','1','1','1','0',0,0,1,-1,'0','0','0','0','1',1,1,'0',0,'0','0','0','1','DEVOLUCION','0'),(4,'Factura NOTA CREDITO','1','1','1','1','1','1','1','1','0','A','1','1','1','0',-1,0,1,-1,'0','0','0','0','1',1,1,'0',0,'0','0','0','1','DEVOLUCION','0'),(5,'Factura COMPRA PROVEEDOR','1','0','1','1','1','1','1','1','0','A','0','1','1','1',0,0,1,-1,'1','1','0','0','0',0,0,'0',0,'0','1','0','0','CONTADO','1'),(6,'Ajuste de Stock +','1','0','0','0','0','0','1','0','0','A','0','0','0','0',0,0,1,0,'1','0','0','0','0',0,0,'1',0,'0','0','0','0','CONTADO','1'),(7,'Ajuste de Stock -','1','0','0','0','0','0','1','0','0','A','0','0','0','0',0,0,-1,0,'1','0','0','0','0',0,0,'1',0,'0','0','0','0','CONTADO','1'),(8,'Ingreso Inventario Maestro','1','0','0','0','0','0','1','0','0','A','0','0','0','0',0,0,1,0,'1','0','0','0','0',0,0,'1',0,'0','0','0','0','CONTADO','1'),(9,'Recibo','0','0','0','0','1','0','1','1','0','A','0','1','1','0',-1,0,0,1,'0','0','0','0','0',0,0,'1',0,'0','0','0','0','CONTADO','0'),(10,'Ajuste Cuenta Corriente +','0','0','0','0','1','0','1','0','0','A','0','1','1','0',1,0,0,0,'0','0','0','0','0',0,0,'1',0,'0','0','0','0','CONTADO','0'),(11,'Ajuste Cuenta Corriente -','0','0','0','0','1','0','1','0','0','A','0','1','1','0',-1,0,0,0,'0','0','0','0','0',0,0,'1',0,'0','0','0','0','CONTADO','0'),(12,'Orden de Compra','1','0','1','1','1','1','1','1','0','A','0','1','1','0',0,0,1,-1,'0','0','0','0','0',0,0,'1',0,'0','0','0','0','CONTADO','0'),(13,'Ingreso de caja','0','0','0','0','1','0','1','0','0','A','0','0','0','0',0,0,0,1,'0','0','0','0','0',0,0,'1',0,'0','0','0','0','CONTADO','0'),(14,'Retiro de caja','0','0','0','0','1','0','1','0','0','A','0','0','0','0',0,0,0,-1,'0','0','0','0','0',0,0,'1',0,'0','0','0','0','CONTADO','0'),(15,'Cambio mercaderia','1','1','0','0','0','0','1','0','0','A','0','1','1','0',0,0,-1,0,'0','0','0','0','0',0,0,'1',0,'0','0','0','0','CONTADO','0'),(16,'Ingreso cheque a caja','0','0','0','0','1','0','1','0','0','A','0','0','0','0',0,0,0,1,'0','0','0','0','0',0,0,'1',0,'0','0','1','0','CONTADO','0'),(17,'Envio de valores de caja a banco','0','0','0','0','1','0','1','0','0','A','0','0','0','0',0,0,0,-1,'0','0','0','0','0',0,0,'1',1,'1','1','0','0','CONTADO','0'),(18,'Envio de valores de banco a caja','0','0','0','0','1','0','1','0','0','A','0','0','0','0',0,0,0,1,'0','0','0','0','0',0,0,'1',-1,'1','0','0','0','CONTADO','0'),(19,'Fondo de banco','0','0','0','0','1','0','1','0','0','A','0','0','0','0',0,0,0,0,'0','0','0','0','0',0,0,'1',1,'1','1','0','0','CONTADO','0'),(20,'Retiro de banco','0','0','0','0','1','0','1','0','0','A','0','0','0','0',0,0,0,0,'0','0','0','0','0',0,0,'1',-1,'1','0','0','0','CONTADO','0');
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
INSERT INTO `TipoDocumentoPerfilesUsuarios` VALUES (1,1),(1,2),(1,3),(2,1),(2,2),(2,3),(3,1),(3,2),(3,3),(4,1),(4,2),(4,3),(5,1),(5,2),(5,3),(6,1),(6,2),(6,3),(7,1),(7,2),(7,3),(8,1),(9,1),(9,2),(9,3),(10,1),(10,2),(10,3),(11,1),(11,2),(11,3),(12,1),(12,2),(12,3),(13,1),(14,1),(15,1),(15,2),(15,3),(16,1),(17,1),(18,1),(19,1),(20,1);
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
INSERT INTO `TipoEstadoDocumento` VALUES ('A','En edición'),('C','Anulado'),('E','Emitido'),('G','Guardado'),('P','Pendiente');
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
  `baseDatosExterna` varchar(45) NOT NULL DEFAULT 'khitomer',
  `hostBaseDatosExterna` varchar(45) DEFAULT 'localhost',
  `codigoEntorno` char(1) NOT NULL DEFAULT '0',
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
INSERT INTO `Usuarios` VALUES ('admin','d033e22ae348aeb5660fc2140aec35850c4da997','Administrador','',1,'0',1,'khitomer','localhost','0');
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

-- Dump completed on 2013-09-23 12:35:03
