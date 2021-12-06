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

#include "funciones.h"
#include <QtSql>
#include "QMessageBox"
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QCryptographicHash>
#include <QDateTime>
#include <QPrinterInfo>
#include <Utilidades/database.h>
#include "QProcess"
#include "Utilidades/utilidadesxml.h"
#include "QThread"
#include <QDesktopServices>
#include <QFile>
#include <QDir>
#include <QDate>
#include <QTime>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>



#if linux
#if __x86_64
#define ENV64BIT
#include "chilkat/include64/CkEmail.h"
#include "chilkat/include64/CkMailMan.h"
#include "chilkat/include64/CkString.h"
#include "chilkat/include64/CkHttpRequest.h"
#include "chilkat/include64/CkHttp.h"
#include "chilkat/include64/CkHttpResponse.h"


#else
#define ENV32BIT
#include "chilkat/include32/CkEmail.h"
#include "chilkat/include32/CkMailMan.h"
#include "chilkat/include32/CkString.h"

#include "chilkat/include32/CkHttpRequest.h"
#include "chilkat/include32/CkHttp.h"
#include "chilkat/include32/CkHttpResponse.h"

#endif
#else
#include "chilkat/include32/CkEmail.h"
#include "chilkat/include32/CkMailMan.h"
#include "chilkat/include32/CkString.h"
#include "chilkat/include32/CkHttpRequest.h"
#include "chilkat/include32/CkHttp.h"
#include "chilkat/include32/CkHttpResponse.h"
#endif

void ChilkatSample();

QThread* thread = new QThread;

CkMailMan ok();




Funciones::Funciones(QObject *parent) :
    QObject(parent)
{

}

bool Funciones::verificoConexionBaseDeDatos(){


    //    QString blah3 = QString(QCryptographicHash::hash(("admin"),QCryptographicHash::Sha1).toHex());
    //     qDebug() << blah3;

    Database::chequeaStatusAccesoMysql();

    if(Database::connect().isOpen()){
        return true;
    }else{
        if(Database::connect().open()){
            return true;
        }else{
            return false;
        }
    }



}

bool Funciones::guardarConfiguracionXML(QString _host,QString _usuario, QString _password, QString _puerto, QString _baseDeDatos){


    QFile file;
    bool resultado=false;


    QDir directorioKhitomer;
    if(!directorioKhitomer.exists(directorioKhitomer.homePath()+"/.config/Khitomer")){
        if(directorioKhitomer.mkdir(directorioKhitomer.homePath()+"/.config/Khitomer")){

        }else{
            return resultado;
        }
    }


    if(QDir::rootPath()=="/"){
        file.setFileName(QDir::homePath()+"/.config/Khitomer/conf.xml");
    }else{
        file.setFileName(QDir::rootPath()+"/Khitomer/conf.xml");
    }


    if (!file.open(QFile::WriteOnly | QFile::Text)) {



        return resultado;

    }else{
        QXmlStreamWriter stream(&file);
        stream.setAutoFormatting(true);

        stream.setAutoFormatting(true);
        stream.writeStartDocument();


        stream.writeStartElement("CONFIGURACION");

        stream.writeStartElement("ACCESO");
        stream.writeAttribute("term", "Acceso al sistema");

        stream.writeTextElement("usuario", _usuario);
        stream.writeTextElement("clave", _password);
        stream.writeTextElement("base", _baseDeDatos);
        stream.writeTextElement("host", _host);
        stream.writeTextElement("puerto", _puerto);

        stream.writeEndElement();
        stream.writeEndElement();

        stream.writeEndDocument();


        resultado=true;

    }

    file.close();

    return resultado;

}

QString Funciones::impresoraPorDefecto(){

    ChilkatSample();


    QString resultado = QPrinterInfo::defaultPrinter().printerName();

    if(resultado=="")
        return "Sin impresora predeterminada";

    return resultado;
}


QString Funciones::retornaFechaImportante(){
    QDateTime dat;

    if(dat.currentDateTime().toString("MM").toInt()==12 && dat.currentDateTime().toString("dd").toInt()>=8){
        return "navidad";
    }else if(dat.currentDateTime().toString("MM").toInt()==1 && (dat.currentDateTime().toString("dd").toInt()==6 || dat.currentDateTime().toString("dd").toInt()==5)){
        return "reyes_magos";
    }else{
        return "dia_normal";
    }
}


QString Funciones::fechaDeHoy(){
    QDateTime dat;
    return dat.currentDateTime().toString("yyyy/MM/dd");
}

QString Funciones::fechaDeHoyCFE(){
    QDateTime dat;
    return dat.currentDateTime().toString("yyyyMMdd");
}


QString Funciones::fechaHoraDeHoy(){

    QDateTime dat;
    return dat.currentDateTime().toString("yyyy/MM/dd HH/mm/ss");
}

QString Funciones::fechaHoraDeHoyTrimeado(){

    QDateTime dat;
    return dat.currentDateTime().toString("MM-dd_HH.mm");
}

void Funciones::abrirPaginaWeb(QString _paginaWeb)const{

    QDesktopServices::openUrl(QUrl(_paginaWeb));

}



bool Funciones::mensajeAdvertencia(QString mensaje) const{


    QMessageBox msgBox;
    msgBox.setText(mensaje);
    msgBox.setModal(true);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("ATENCIÓN!!!: ");
    msgBox.setWindowIcon(QIcon("qrc:/qml/ProyectoQML/Imagenes/icono.png"));
    msgBox.setMinimumHeight(100);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setButtonText(1024,"Sí");

    if(msgBox.exec()!=1024)
        return false;

    return true;

}
bool Funciones::mensajeAdvertenciaOk(QString mensaje) const{

    QMessageBox msgBox;
    msgBox.setText(mensaje);
    msgBox.setModal(true);

    if(mensaje.contains("error",Qt::CaseInsensitive)){
        msgBox.setIcon(QMessageBox::Critical);
    }else{
        msgBox.setIcon(QMessageBox::Information);
    }



    msgBox.setWindowTitle("ATENCIÓN!!!: ");
    msgBox.setWindowIcon(QIcon("qrc:/qml/ProyectoQML/Imagenes/icono.png"));
    msgBox.setMinimumHeight(100);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setButtonText(1024,"Continuar");

    if(msgBox.exec()!=1024)
        return false;


    return true;

}

bool Funciones::consutlaMysqlEstaViva(){

    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            return false;
        }else{
            QSqlQuery query(Database::connect());

            if(query.exec("select 1")) {
                return true;

            }else{
                Database::connect().close();
                return false;
            }
        }
    }else{
        QSqlQuery query(Database::connect());

        if(query.exec("select 1")) {
            return true;
        }else{
            Database::connect().close();
            return false;
        }
    }
}

void Funciones::reseteaConexionMysql(){

    Database::connect().close();

}



bool Funciones::consultaPingServidor(){

    QProcess *connected = new QProcess(0);
    QString exec="ping";
    QStringList params;

    connected->moveToThread(thread());



    if(QDir::rootPath()=="/"){
        params << "-c" << "1" << "-W" << "1" << UtilidadesXml::getHostLocal();
    }else{
        params << "-n" << "1" << "-w" << "1" << UtilidadesXml::getHostLocal();
    }


    connected->start(exec,params);

    thread()->start();


    if(!connected->waitForFinished()){
        delete connected;
        return false;
    }

    if(connected->exitCode()==0){
        delete connected;
        return true;
    }else{
        delete connected;
        return false;
    }
}


/////////////////////////////////////////////////////////////////////////////////////////
///////////          UTILIDAD DE LOGUEO             /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void Funciones::loguear(QString _infoLog){

    QFile logDeInformacion(retornaDirectorioLog()+retornaNombreLog());
    QTextStream out(&logDeInformacion);

    if(!QDir(retornaDirectorioLog()).exists()){
        QDir directorio;
        if(!directorio.mkdir(retornaDirectorioLog())){

        }
    }

    if(QFile(retornaDirectorioLog()+retornaNombreLog()).exists()){
        logDeInformacion.open(QIODevice::Append);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")+" ||>> "+_infoLog+"\n";
    }else{
        logDeInformacion.open(QIODevice::WriteOnly);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")+" ||>> "+_infoLog+"\n";
    }
    logDeInformacion.close();

}

QString Funciones::retornaDirectorioLog(){
    if(QDir::rootPath()=="/"){
        return QDir::homePath()+"/.config/Khitomer/logs/";
    }else{
        return QDir::rootPath()+"/Khitomer/logs/";
    }
}

QString Funciones::retornaNombreLog(){
    return "LogKhitomer-"+QString::number(QDate::currentDate().day())+".log";
}

void Funciones::depurarLog(){

    if(QFileInfo(retornaDirectorioLog()+retornaNombreLog()).lastModified().toString("yyyy-MM-dd")!=QDateTime::currentDateTime().toString("yyyy-MM-dd")){
        QFile(retornaDirectorioLog()+retornaNombreLog()).remove();
    }
}
QString Funciones::leerLog(){
   // return "LogKhitomer-"+QString::number(QDate::currentDate().day())+".log";

    QFile inputFile(retornaDirectorioLog()+retornaNombreLog());
    QString lineas="";
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       lineas = in.readAll();

       /*while (!in.atEnd())
       {
          lineas = in.readAll();

       }*/
       inputFile.close();
    }

    return lineas;

}



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////




qlonglong Funciones::versionDeBaseDeDatos()const{


    bool conexion=true;
    Database::chequeaStatusAccesoMysql();

    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect());
        if(query.exec("SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion='VERSION_BD';")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    return query.value(0).toLongLong();
                }else{return -1;}
            }else{
                if(query.exec("INSERT INTO `Configuracion` (`codigoConfiguracion`, `valorConfiguracion`, `descripcionConfiguracion`) VALUES ('VERSION_BD', '7', 'Muestra la verisión de la base de datos. Este dato se utiliza para indicarle a la aplicación la versión de la base de datos, y que la misma realice las actualizaciones necesarias.')")){
                    return versionDeBaseDeDatos();
                }else{
                    return -1;
                }
            }
        }else{
            return -1;
        }
    }else{return -1;}

}

bool Funciones::impactoCambioEnBD(QString _cambioSql,QString _versionBD) const {

    if(_cambioSql.trimmed()=="")
        return false;


    Database::chequeaStatusAccesoMysql();

    bool conexion=true;
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery query(Database::connect());
        if(_cambioSql=="-1"){

            if(query.exec("update Configuracion set valorConfiguracion='"+_versionBD+"' where codigoConfiguracion='VERSION_BD'")){
                return true;
            }else{
                mensajeAdvertencia(query.lastError().text()+ "\n\nError al actualizar Configuracion");
                qDebug()<< query.lastError();
                return false;
            }
        }else{
            qDebug()<< _cambioSql;
            if(query.exec(_cambioSql)){
                query.clear();
                if(query.exec("update Configuracion set valorConfiguracion='"+_versionBD+"' where codigoConfiguracion='VERSION_BD'")){
                    return true;
                }else{
                    mensajeAdvertencia(query.lastError().text() + "\n\nError al actualizar Configuracion");
                    qDebug()<< query.lastError();
                    return false;
                }
            }else{
                mensajeAdvertencia("Version del cambio en base de datos: "+_versionBD);
                mensajeAdvertencia(query.lastError().text() + "\n\nError al actualizar la base de datos:\n\n"+_cambioSql);
                qDebug()<< query.lastError();
                return false;
            }
        }
    }else{
        return false;
    }
}



bool Funciones::actualizacionBaseDeDatos(qlonglong _valor)const{

    bool _iterador=true;
    /// do while que itera mientras haya actualizaciones pendientes
    do{
        /// El switch va chequeado que versión de la base de datos es la ultima, y va aplicando las actualizaciones.
        switch (_valor) {      
        case 150:
            if(!impactoCambioEnBD("ALTER TABLE `Documentos` ADD COLUMN `FormaDePago` VARCHAR(256) NOT NULL DEFAULT '' AFTER `SaldoClienteCuentaCorriente`;","151")){
                _iterador=false; return false;
            }
            break;
        case 151:
            if(!impactoCambioEnBD("ALTER TABLE `Documentos`  CHANGE COLUMN `SaldoClienteCuentaCorriente` `saldoClienteCuentaCorriente` DECIMAL(45,2) NOT NULL DEFAULT '0.00' , CHANGE COLUMN `FormaDePago` `formaDePago` VARCHAR(256) NOT NULL DEFAULT '' ;","152")){
                _iterador=false; return false;
            }
            break;
        case 152:
            if(!impactoCambioEnBD("ALTER TABLE `Reportes` ADD COLUMN `utilizaPais` CHAR(1) NOT NULL DEFAULT '0' AFTER `utilizaMonedas`,ADD COLUMN `utilizaDepartamento` CHAR(1) NOT NULL DEFAULT '0' AFTER  `utilizaPais`, ADD COLUMN `utilizaLocalidad` CHAR(1) NOT NULL DEFAULT '0' AFTER `utilizaDepartamento`;","153")){
                _iterador=false; return false;
            }
            break;
        case 153:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `utilizaMonedas`, `utilizaLocalidad`) VALUES ('47', '5', 'Saldo de clientes por Departamentos y moneda(nuevo)', 'SELECT DOC.codigoCliente\\'CODIGO CLIENTE\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\')\\')\\'DOCUMENTO\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente where DOC.tipoCliente=\\'1\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1 and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'  and DOC.saldoClienteCuentaCorriente!=0 and CLI.codigoPais=\\'@_codigoLocalidadPais\\' and codigoDepartamento=\\'@_codigoLocalidadDepartamento\\' order by DOC.codigoCliente asc , DOC.fechaEmisionDocumento asc;', '1', '1');","153")){
                if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `utilizaMonedas`, `utilizaLocalidad`) VALUES ('48', '5', 'Saldo de proveedores por Departamentos y moneda(nuevo)', 'SELECT DOC.codigoCliente\\'CODIGO PROVEEDOR\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\')\\')\\'DOCUMENTO\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente where DOC.tipoCliente=\\'2\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1 and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'  and DOC.saldoClienteCuentaCorriente!=0 and CLI.codigoPais=\\'@_codigoLocalidadPais\\' and codigoDepartamento=\\'@_codigoLocalidadDepartamento\\' order by DOC.codigoCliente asc , DOC.fechaEmisionDocumento asc;', '1', '1');","153")){
                    if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `utilizaCodigoCliente`, `utilizaMonedas`) VALUES ('49', '5', 'Saldo de cliente por moneda(nuevo)', 'SELECT DOC.codigoCliente\\'CODIGO CLIENTE\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\')\\')\\'DOCUMENTO\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente where DOC.codigoCliente=\\'@_codigoCliente\\' and DOC.tipoCliente=\\'1\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1 and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'  and DOC.saldoClienteCuentaCorriente!=0  order by  DOC.fechaEmisionDocumento asc;', '1', '1');","153")){
                        if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `utilizaCodigoProveedor`, `utilizaMonedas`) VALUES ('50', '5', 'Saldo de proveedor por moneda(nuevo)', 'SELECT DOC.codigoCliente\\'CODIGO PROVEEDOR\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\')\\')\\'DOCUMENTO\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente where DOC.codigoCliente=\\'@_codigoProveedor\\' and DOC.tipoCliente=\\'2\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1 and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'  and DOC.saldoClienteCuentaCorriente!=0  order by  DOC.fechaEmisionDocumento asc;', '1', '1');","153")){
                            if(impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('49', '5', '2', '1', '', 'MONTO');","153")){
                                if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('50', '5', '2', '1', '', 'MONTO');","154")){
                                    _iterador=false; return false;
                                }
                            }else{_iterador=false; return false;}
                        }else{_iterador=false; return false;}
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 154:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT DOC.codigoCliente\\'CODIGO CLIENTE\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\')\\')\\'DOCUMENTO\\', MON.simboloMoneda\\'\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.codigoCliente=\\'@_codigoCliente\\' and DOC.tipoCliente=\\'1\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1 and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'  and DOC.saldoClienteCuentaCorriente!=0  order by  DOC.fechaEmisionDocumento asc; ' WHERE `codigoReporte`='49';","154")){
                if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT DOC.codigoCliente\\'CODIGO PROVEEDOR\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\')\\')\\'DOCUMENTO\\', MON.simboloMoneda\\'\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.codigoCliente=\\'@_codigoProveedor\\' and DOC.tipoCliente=\\'2\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1 and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'  and DOC.saldoClienteCuentaCorriente!=0  order by  DOC.fechaEmisionDocumento asc; ' WHERE `codigoReporte`='50';","155")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 155:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT DOC.codigoCliente\\'CODIGO CLIENTE\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\')\\')\\'DOCUMENTO\\',MON.simboloMoneda\\'\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente where DOC.tipoCliente=\\'1\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1 and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'  and DOC.saldoClienteCuentaCorriente!=0 and CLI.codigoPais=\\'@_codigoLocalidadPais\\' and codigoDepartamento=\\'@_codigoLocalidadDepartamento\\' order by DOC.codigoCliente asc , DOC.fechaEmisionDocumento asc;' WHERE `codigoReporte`='47';","155")){
                if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT DOC.codigoCliente\\'CODIGO PROVEEDOR\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\')\\')\\'DOCUMENTO\\',MON.simboloMoneda\\'\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente where DOC.tipoCliente=\\'2\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1 and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'  and DOC.saldoClienteCuentaCorriente!=0 and CLI.codigoPais=\\'@_codigoLocalidadPais\\' and codigoDepartamento=\\'@_codigoLocalidadDepartamento\\' order by DOC.codigoCliente asc , DOC.fechaEmisionDocumento asc;' WHERE `codigoReporte`='48';","155")){
                    if(impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('47', '5', '2', '0', '', 'MONTO');","155")){
                        if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('48', '5', '2', '0', '', 'MONTO');","156")){
                            _iterador=false; return false;
                        }
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 156:
            if(!impactoCambioEnBD("ALTER TABLE `Reportes` ADD COLUMN `utilizaCoincidenciaCodigoCliente` CHAR(1) NOT NULL DEFAULT '0' AFTER `utilizaLocalidad`;","157")){
                _iterador=false; return false;
            }
            break;
        case 157:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `utilizaMonedas`, `utilizaCoincidenciaCodigoCliente`) VALUES ('51', '5', 'Saldo de cliente por primer caracter de su código', 'SELECT DOC.codigoCliente\\'CODIGO CLIENTE\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\')\\')\\'DOCUMENTO\\',MON.simboloMoneda\\'\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'   FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  where DOC.tipoCliente=\\'1\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1  and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'   and DOC.codigoCliente like \\'@_principioCodigoDelCliente%\\' and DOC.saldoClienteCuentaCorriente!=0  order by DOC.codigoCliente asc , DOC.fechaEmisionDocumento asc; ', '1', '1');","157")){
                if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('51', '5', '2', '0', '', 'MONTO');","158")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 158:
            if(!impactoCambioEnBD("ALTER TABLE `TipoDocumento` ADD COLUMN `utilizaFormasDePago` CHAR(1) NOT NULL DEFAULT '0' AFTER `cantidadMaximaLineasEnDocumento`;","159")){
                _iterador=false; return false;
            }
            break;
        case 159:
            if(!impactoCambioEnBD("INSERT INTO `ImpresionCampos` (`codigoCampoImpresion`, `descripcionCampoImpresion`, `tipoCampo`, `codigoEtiqueta`, `campoEnTabla`) VALUES ('39', 'Forma de pago', '3', 'txtFormaDePago', 'Doc.formaDePago');","160")){
                _iterador=false; return false;
            }
            break;
        case 160:
            if(!impactoCambioEnBD("INSERT INTO `Configuracion` (`codigoConfiguracion`, `valorConfiguracion`, `descripcionConfiguracion`) VALUES ('IVA_DEFAULT_SISTEMA', '1', 'Parametro que indica el codigo de IVA por defecto en el sistema para los medios de pago');","161")){
                _iterador=false; return false;
            }
            break;
        case 161:
            if(!impactoCambioEnBD("UPDATE  `PerfilesUsuarios` SET `permiteUsarCuentaCorriente`='1' WHERE `codigoPerfil`='1';","162")){
                _iterador=false; return false;
            }
            break;
        case 162:
            if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT AR.codigoArticulo\\'Código\\', AR.descripcionArticulo\\'Nombre\\', case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)\\'cantidad\\' FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOC.fechaEmisionDocumento  <=  \\'@_hasta\\'  and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0  else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOC.fechaEmisionDocumento  <=  \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end  \\'Unidades stock(Real)\\' ,    case when  (SELECT DOCLL.costoArticuloMonedaReferencia FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloMonedaReferencia!=0  and DOCLL.fechaHoraGuardadoLineaSQL  <=  \\'@_hasta\\' + INTERVAL 1 DAY  order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) is null  then \\'Costo no definido\\' else  concat((select MON.simboloMoneda from Monedas MON where MON.esMonedaReferenciaSistema=1  order by MON.codigoMoneda asc limit 1),\\'  \\', (SELECT DOCLL.costoArticuloMonedaReferencia FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloMonedaReferencia!=0 and DOCLL.fechaHoraGuardadoLineaSQL  <=  \\'@_hasta\\' + INTERVAL 1 DAY order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) )end\\'Costo Unitario\\', case when  (SELECT DOCLL.costoArticuloMonedaReferencia FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloMonedaReferencia!=0 and DOCLL.fechaHoraGuardadoLineaSQL  <=  \\'@_hasta\\' + INTERVAL 1 DAY order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) is null then 0 else  (case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)  FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento    join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where  TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOC.fechaEmisionDocumento  <=  \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOC.fechaEmisionDocumento  <=  \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end) *  (SELECT DOCLL.costoArticuloMonedaReferencia FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloMonedaReferencia!=0 and DOCLL.fechaHoraGuardadoLineaSQL  <=  \\'@_hasta\\' + INTERVAL 1 DAY  order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) end \\'Total costo según stock\\'  FROM Articulos AR  where AR.codigoArticulo between CONVERT(\\'@_ArticulodesdeCodigoArticulo\\', SIGNED INTEGER) and CONVERT(\\'@_ArticulohastaCodigoArticulo\\', SIGNED INTEGER) and (case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)\\'cantidad\\'  FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 	and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOC.fechaEmisionDocumento  <=  \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0   else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOC.fechaEmisionDocumento  <=  \\'@_hasta\\'  and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8  and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end)>0 order by CONVERT(AR.codigoArticulo, SIGNED INTEGER); ' WHERE `codigoReporte`='46';","163")){
                _iterador=false; return false;
            }
            break;
        case 163:
            if(!impactoCambioEnBD("ALTER TABLE `DocumentosLineas` ADD COLUMN `costoArticuloPonderado` DECIMAL(45,2) NOT NULL DEFAULT '0.00' AFTER `costoArticuloMonedaReferencia`;","164")){
                _iterador=false; return false;
            }
            break;
        case 164:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT AR.codigoArticulo\\'Código\\', AR.descripcionArticulo\\'Nombre\\', case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)\\'cantidad\\' FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and DOC.fechaEmisionDocumento  <=  \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0  else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and  DOC.fechaEmisionDocumento  <=  \\'@_hasta\\'  and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end  \\'Unidades stock(Real)\\' , case when  (SELECT DOCLL.costoArticuloMonedaReferencia FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloMonedaReferencia!=0  and DOCLL.fechaHoraGuardadoLineaSQL  <=  \\'@_hasta\\' + INTERVAL 1 DAY  order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) is null  then \\'Costo no definido\\' else  concat((select MON.simboloMoneda from Monedas MON where MON.esMonedaReferenciaSistema=1  order by MON.codigoMoneda asc limit 1),\\'  \\', (SELECT DOCLL.costoArticuloMonedaReferencia FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloMonedaReferencia!=0 and DOCLL.fechaHoraGuardadoLineaSQL  <=   \\'@_hasta\\' + INTERVAL 1 DAY order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) )end\\'Costo Unitario(Ultima compra)\\', case when  (SELECT DOCLL.costoArticuloPonderado FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloPonderado!=0  and DOCLL.fechaHoraGuardadoLineaSQL  <=   \\'@_hasta\\' + INTERVAL 1 DAY  order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) is null  then \\'Costo no definido\\' else  concat((select MON.simboloMoneda from Monedas MON where MON.esMonedaReferenciaSistema=1  order by MON.codigoMoneda asc limit 1),\\'  \\', (SELECT DOCLL.costoArticuloPonderado FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloPonderado!=0 and DOCLL.fechaHoraGuardadoLineaSQL  <=  \\'@_hasta\\' + INTERVAL 1 DAY order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) )end\\'Costo Unitario Ponderado\\', case when  (SELECT DOCLL.costoArticuloPonderado FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloPonderado!=0 and DOCLL.fechaHoraGuardadoLineaSQL  <=   \\'@_hasta\\' + INTERVAL 1 DAY order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) is null then 0 else  (case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)  FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento    join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where  TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOC.fechaEmisionDocumento  <=    \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOC.fechaEmisionDocumento  <=   \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end) *  (SELECT DOCLL.costoArticuloPonderado FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloPonderado!=0 and DOCLL.fechaHoraGuardadoLineaSQL  <=   \\'@_hasta\\' + INTERVAL 1 DAY  order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) end \\'Total costo ponderado según stock\\' FROM Articulos AR  where AR.codigoArticulo between CONVERT(\\'@_ArticulodesdeCodigoArticulo\\', SIGNED INTEGER)  and CONVERT(\\'@_ArticulohastaCodigoArticulo\\', SIGNED INTEGER)  and (case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)\\'cantidad\\'  FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 	and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOC.fechaEmisionDocumento  <=   \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0   else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOC.fechaEmisionDocumento  <=   \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8  and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end)>0 order by CONVERT(AR.codigoArticulo, SIGNED INTEGER);' WHERE `codigoReporte`='46';","164")){
                if(!impactoCambioEnBD("UPDATE `ReportesConfiguracion` SET `columnaReporte`='5' WHERE `codigoReporte`='46' and`columnaReporte`='4';","165")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 165:
            if(!impactoCambioEnBD("INSERT INTO  `Configuracion` (`codigoConfiguracion`, `valorConfiguracion`, `descripcionConfiguracion`) VALUES ('MODO_AUTORIZACION', '1', 'Parametro para indicar si se utilizan los cuadros de autorizaciones. 0 - autorizaciones descativadas. 1 - autorizaciones activadas. Esto esta por encima de lo que se configure en los perfiles del sistema');","166")){
                _iterador=false; return false;
            }
            break;
        case 166:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select AR.codigoArticulo\\'CODIGO\\',  AR.descripcionArticulo\\'DETALLE\\',  case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\' then concat(MON.simboloMoneda,\\' \\',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2)) else  ROUND(LPA.precioArticulo,2)  end   \\'Precio sin I.V.A\\', case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\' then  concat(MON.simboloMoneda,\\' \\',LPA.precioArticulo)  else  ROUND(LPA.precioArticulo*IV.factorMultiplicador,2) end \\'Precio I.V.A Inc.\\' FROM Articulos AR JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda JOIN Ivas IV on IV.codigoIva=AR.codigoIva where AR.activo=1 and LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' order by 2;' WHERE `codigoReporte`='30';","166")){
                if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select AR.codigoArticulo\\'CODIGO\\', AR.descripcionArticulo\\'DETALLE\\', case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'  then concat(MON.simboloMoneda,\\' \\',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2)) else  ROUND(LPA.precioArticulo,2)  end   \\'Precio sin I.V.A\\',  case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'  then  concat(MON.simboloMoneda,\\' \\',LPA.precioArticulo)  else  ROUND(LPA.precioArticulo*IV.factorMultiplicador,2)  end \\'Precio I.V.A Inc.\\'   FROM Articulos AR JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda JOIN Ivas IV on IV.codigoIva=AR.codigoIva    where AR.activo=1 and (case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and DOCL.codigoArticulo=AR.codigoArticulo     and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos  where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by codigoDocumento desc limit 1)   group by DOCL.codigoArticulo) end) > \\'@_cantidad\\' and  LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' order by 2 ;' WHERE `codigoReporte`='31';","167")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 167:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select AR.codigoArticulo\\'CODIGO\\', AR.descripcionArticulo\\'DETALLE\\', case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'   then concat(MON.simboloMoneda,\\' \\',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2)) else  ROUND(LPA.precioArticulo,2)   end   \\'Precio sin I.V.A\\',  case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion= \\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'  then  concat(MON.simboloMoneda,\\' \\',LPA.precioArticulo)  else   ROUND(LPA.precioArticulo*IV.factorMultiplicador,2)  end \\'Precio I.V.A Inc.\\'      FROM Articulos AR  JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda  JOIN Ivas IV on IV.codigoIva=AR.codigoIva   JOIN SubRubros SUB on SUB.codigoSubRubro=AR.codigoSubRubro JOIN Rubros RUB on RUB.codigoRubro=SUB.codigoRubro   where AR.activo=1 and LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\'  and RUB.codigoRubro=\\'@_codigoRubro\\' order by 2; ' WHERE `codigoReporte`='33';","167")){
                if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select AR.codigoArticulo\\'CODIGO\\', AR.descripcionArticulo\\'DETALLE\\', case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'   then concat(MON.simboloMoneda,\\' \\',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2)) else  ROUND(LPA.precioArticulo,2)   end   \\'Precio sin I.V.A\\',  case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion= \\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'  then  concat(MON.simboloMoneda,\\' \\',LPA.precioArticulo)  else   ROUND(LPA.precioArticulo*IV.factorMultiplicador,2)  end \\'Precio I.V.A Inc.\\'     FROM Articulos AR  JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda  JOIN Ivas IV on IV.codigoIva=AR.codigoIva   JOIN SubRubros SUB on SUB.codigoSubRubro=AR.codigoSubRubro JOIN Rubros RUB on RUB.codigoRubro=SUB.codigoRubro  where AR.activo=1 and LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\'  and SUB.codigoSubRubro=\\'@_codigoSubRubro\\' order by 2;  ' WHERE `codigoReporte`='34';","168")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 168:
            if(impactoCambioEnBD("CREATE TABLE `TipoDocumentoMonedasRedondeo` (`codigoTipoDocumento` INT(10) UNSIGNED NOT NULL,`codigoMoneda` INT(10) UNSIGNED NOT NULL,PRIMARY KEY (`codigoTipoDocumento`, `codigoMoneda`));","168")){
                if(!impactoCambioEnBD("INSERT INTO `TipoDocumentoMonedasRedondeo` (`codigoTipoDocumento`, `codigoMoneda`) VALUES ('1', '1'),('2', '1'),('3', '1'),('4', '1');","169")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 169:
            if(impactoCambioEnBD("ALTER TABLE `Reportes` ADD COLUMN `consultaSqlCabezal` VARCHAR(10000) NOT NULL DEFAULT '' AFTER `consultaSqlGraficas`;","169")){
                if(!impactoCambioEnBD("ALTER TABLE `DocumentosCanceladosCuentaCorriente` ADD COLUMN `montoDescontadoCuentaCorriente` DECIMAL(45,2) NOT NULL DEFAULT 0.00 AFTER `codigoTipoDocumentoQueCancela`;","170")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 170:
            if(!impactoCambioEnBD("ALTER TABLE `TipoDocumento` ADD COLUMN `tipoOrdenLineasFacturasAlEmitirse` CHAR(1) NOT NULL DEFAULT '0' AFTER `utilizaFormasDePago`;","171")){
                _iterador=false; return false;
            }
            break;
        case 171:
            if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSqlCabezal`='select concat(CLI.nombreCliente,\\'(\\',CLI.codigoCliente,\\')\\'),concat(\\'Dirección: \\',CLI.direccion),concat(\\'Telefono: \\',CLI.telefono) from Clientes CLI  where CLI.codigoCliente=\\'@_codigoCliente\\' and CLI.tipoCliente=1;' WHERE `codigoReporte`='49';","172")){
                _iterador=false; return false;
            }
            break;
        case 172:
            if(impactoCambioEnBD("ALTER TABLE `Documentos` ADD COLUMN `saldoClientePagoContado` DECIMAL(45,2) NOT NULL DEFAULT '0.00' AFTER `formaDePago`;","172")){
                if(!impactoCambioEnBD("ALTER TABLE `TipoDocumento` ADD COLUMN `documentoAceptaIngresoDeMediosDePagoLuegoDeEmitido` CHAR(1) NOT NULL DEFAULT '0' AFTER `tipoOrdenLineasFacturasAlEmitirse`;","173")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 173:
            if(impactoCambioEnBD("ALTER TABLE `Configuracion` CHANGE COLUMN `codigoConfiguracion` `codigoConfiguracion` VARCHAR(300) NOT NULL ;","173")){
                if(impactoCambioEnBD("INSERT INTO `Configuracion` (`codigoConfiguracion`, `valorConfiguracion`, `descripcionConfiguracion`) VALUES ('MULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADOS', '1.03', 'Este multiplicador de porcentaje minimo de deuda para los contados, se usa para la funcionalidad de control de medios de pago pendientes, para las facturas contados.');","173")){
                    if(!impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `utilizaMonedas`) VALUES ('52', '4', 'Facturas con deuda de Medios de Pago', 'SELECT concat(TD.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\')\\')\\'Documento\\', DOC.fechaEmisionDocumento\\'Fecha Documento\\', concat(MON.simboloMoneda,\\' \\',DOC.precioTotalVenta)\\'Total Documento\\', concat(MON.simboloMoneda,\\' \\',ROUND(DOC.precioTotalVenta-(DOC.precioTotalVenta/(SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADO\\' limit 1)),2))\\'Deuda minima permitida\\',  MON.simboloMoneda\\'\\', DOC.precioTotalVenta-DOC.saldoClientePagoContado\\'Saldo por pagar\\'  FROM Documentos DOC  join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where TD.documentoAceptaIngresoDeMediosDePagoLuegoDeEmitido=\\'1\\' and  DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and ROUND(DOC.precioTotalVenta-(DOC.precioTotalVenta/(SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADO\\' limit 1)),2)<=DOC.precioTotalVenta-DOC.saldoClientePagoContado and MON.codigoMoneda=\\'@_codigoMonedaReporte\\' order by DOC.fechaEmisionDocumento;', '1');","174")){
                        _iterador=false; return false;
                    }
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 174:
            if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('52', '5', '2', '1', '', 'MONTO');","175")){
                _iterador=false; return false;
            }
            break;
        case 175:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaCodigoProveedor`) VALUES ('53', '8', 'Stock por proveedor', 'select  AR.codigoArticulo\\'Codigo\\',AR.descripcionArticulo\\'Descripción\\',  case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end \\'Stock Real\\',  case when (select concat(MON.simboloMoneda,\\'   \\',round(DOCL.precioArticuloUnitario,2)) from Documentos DOC  join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1 and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) is null then \\'No hay costo definido\\' else (select concat(MON.simboloMoneda,\\'   \\',round(DOCL.precioArticuloUnitario,2)) from Documentos DOC  join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1 and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) end  \\'Costo en moneda extranjera\\', AR.descripcionExtendida\\'Codigo origen\\', case when (select DOC.fechaEmisionDocumento from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1 and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) is null then \\'No existen compras\\' else  (select DOC.fechaEmisionDocumento from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1 and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) end \\'Fecha última compra\\',  case when (select sum(DOCL.cantidad) from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1  and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  group by DOC.fechaEmisionDocumento  order by  DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) is null then \\'No existen compras\\'  else   convert((select sum(DOCL.cantidad) from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1  and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  group by DOC.fechaEmisionDocumento  order by  DOC.fechaHoraGuardadoDocumentoSQL desc limit 1),unsigned INTEGER) end \\'Cantidad última compra\\', case when(select DOC.fechaEmisionDocumento from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=-1 and TDOC.utilizaCliente=1 and TDOC.esDocumentoDeVenta=1 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) is null then \\'No existen ventas\\' else  (select DOC.fechaEmisionDocumento from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=-1 and TDOC.utilizaCliente=1 and TDOC.esDocumentoDeVenta=1 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) end \\'Fecha última venta\\' from Articulos AR join Clientes CLI on CLI.codigoCliente=AR.codigoProveedor and CLI.tipoCliente=AR.tipoCliente  where CLI.codigoCliente=\\'@_codigoProveedor\\' and CLI.tipoCliente=2   order by CONVERT(AR.codigoArticulo, SIGNED INTEGER);', '', 'SELECT concat(\\'Código proveedor: \\',CLIE.codigoCliente), concat(\\'Razon social: \\',CLIE.razonSocial), concat(\\'Nombre: \\',CLIE.nombreCliente) from Clientes CLIE where  CLIE.codigoCliente=\\'@_codigoProveedor\\' and CLIE.tipoCliente=2;', '1');","175")){
                if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('53', '0', '0', '0', '', 'TEXTO'),('53', '1', '0', '0', '', 'TEXTO'),('53', '2', '2', '0', '', 'TEXTO'),('53', '3', '2', '0', '', 'TEXTO'),('53', '4', '0', '0', '', 'TEXTO'),('53', '5', '0', '0', '', 'TEXTO'),('53', '6', '2', '0', '', 'TEXTO'),('53', '7', '0', '0', '', 'TEXTO');","176")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 176:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT  concat(CLI.razonSocial,\\'(\\',CLI.codigoCliente,\\')\\')\\'Cliente\\',  concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\')\\')\\'Documento\\',  case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND((DOC.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda ))*TDOC.afectaTotales,2) end \\'Total $\\',  case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND((DOC.precioTotalVenta/(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=2 ))*TDOC.afectaTotales,2) end \\'Total U$S\\' FROM Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'  and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'  and DOC.codigoVendedorComisiona=\\'@_codigoVendedor\\' order by DOC.fechaEmisionDocumento asc ; ', `consultaSqlCabezal`='select concat(\\'Vendedor: \\',USU.nombreUsuario,\\' \\',USU.apellidoUsuario) from Usuarios USU where USU.idUsuario=\\'@_codigoVendedor\\';' WHERE `codigoReporte`='14';","176")){
                if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT  concat(CLI.razonSocial,\\'(\\',CLI.codigoCliente,\\')\\')\\'Cliente\\',  concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\')\\')\\'Documento\\',    case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta,2)  else ROUND(DOC.precioSubTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda ),2) end \\'Total $\\',    case when MON.codigoMoneda=2 then  ROUND(DOC.precioSubTotalVenta,2)  else ROUND(DOC.precioSubTotalVenta/(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=2 ),2) end \\'Total U$S\\'   FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\' and DOC.fechaEmisionDocumento    between \\'@_desde\\' and \\'@_hasta\\'   and DOC.codigoVendedorComisiona=\\'@_codigoVendedor\\' order by DOC.fechaEmisionDocumento asc ;', `consultaSqlCabezal`='select concat(\\'Vendedor: \\',USU.nombreUsuario,\\' \\',USU.apellidoUsuario) from Usuarios USU where USU.idUsuario=\\'@_codigoVendedor\\';' WHERE `codigoReporte`='26';","177")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;

        case 177:
            if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT  concat(CLI.razonSocial,\\'(\\',CLI.codigoCliente,\\')\\')\\'Cliente\\', concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\')\\')\\'Documento\\', case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta,2)*TDOC.afectaTotales  else ROUND(DOC.precioSubTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda ),2)*TDOC.afectaTotales end \\'Total $\\', case when MON.codigoMoneda=2 then  ROUND(DOC.precioSubTotalVenta,2)*TDOC.afectaTotales  else ROUND(DOC.precioSubTotalVenta/(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=2 ),2)*TDOC.afectaTotales end \\'Total U$S\\'    FROM Documentos DOC   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')   and TDOC.esDocumentoDeVenta=\\'1\\'  and DOC.fechaEmisionDocumento    between \\'@_desde\\' and \\'@_hasta\\'    and DOC.codigoVendedorComisiona=\\'@_codigoVendedor\\'  order by DOC.fechaEmisionDocumento asc ;' WHERE `codigoReporte`='26';","178")){
                _iterador=false; return false;
            }
            break;
        case 178:
            if(!impactoCambioEnBD("ALTER TABLE `Reportes`  ADD COLUMN `utilizaOrdenEnReporte` CHAR(1) NOT NULL DEFAULT '0' AFTER `utilizaCoincidenciaCodigoCliente`;","179")){
                _iterador=false; return false;
            }
            break;
        case 179:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select AR.codigoArticulo\\'CODIGO\\',  AR.descripcionArticulo\\'DETALLE\\',  case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\' then concat(MON.simboloMoneda,\\' \\',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2)) else  ROUND(LPA.precioArticulo,2)  end   \\'Precio sin I.V.A\\', case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\' then  concat(MON.simboloMoneda,\\' \\',LPA.precioArticulo)  else  ROUND(LPA.precioArticulo*IV.factorMultiplicador,2) end \\'Precio I.V.A Inc.\\' FROM Articulos AR JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda JOIN Ivas IV on IV.codigoIva=AR.codigoIva where AR.activo=1 and  LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\'  order by  (case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_ARTICULO\\' limit 1)=\\'1\\' then CONVERT(AR.codigoArticulo, UNSIGNED INTEGER) else 2 end);' WHERE `codigoReporte`='30';","179")){
                if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select AR.codigoArticulo\\'CODIGO\\', AR.descripcionArticulo\\'DETALLE\\', case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'   then concat(MON.simboloMoneda,\\' \\',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2)) else  ROUND(LPA.precioArticulo,2)   end   \\'Precio sin I.V.A\\',  case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion= \\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'  then  concat(MON.simboloMoneda,\\' \\',LPA.precioArticulo)  else   ROUND(LPA.precioArticulo*IV.factorMultiplicador,2)  end \\'Precio I.V.A Inc.\\'      FROM Articulos AR  JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda  JOIN Ivas IV on IV.codigoIva=AR.codigoIva   JOIN SubRubros SUB on SUB.codigoSubRubro=AR.codigoSubRubro JOIN Rubros RUB on RUB.codigoRubro=SUB.codigoRubro   where AR.activo=1 and LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\'  and RUB.codigoRubro=\\'@_codigoRubro\\' order by  (case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_ARTICULO\\' limit 1)=\\'1\\' then CONVERT(AR.codigoArticulo, UNSIGNED INTEGER) else 2 end);' WHERE `codigoReporte`='33';","179")){
                    if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select AR.codigoArticulo\\'CODIGO\\', AR.descripcionArticulo\\'DETALLE\\', case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'  then concat(MON.simboloMoneda,\\' \\',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2)) else  ROUND(LPA.precioArticulo,2)  end   \\'Precio sin I.V.A\\',  case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'  then  concat(MON.simboloMoneda,\\' \\',LPA.precioArticulo)  else  ROUND(LPA.precioArticulo*IV.factorMultiplicador,2)  end \\'Precio I.V.A Inc.\\'   FROM Articulos AR JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda JOIN Ivas IV on IV.codigoIva=AR.codigoIva    where AR.activo=1 and (case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and DOCL.codigoArticulo=AR.codigoArticulo     and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos  where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by codigoDocumento desc limit 1)  group by DOCL.codigoArticulo) end) > \\'@_cantidad\\' and  LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' order by  (case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_ARTICULO\\' limit 1)=\\'1\\' then CONVERT(AR.codigoArticulo, UNSIGNED INTEGER) else 2 end);' WHERE `codigoReporte`='31';","179")){
                        if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select AR.codigoArticulo\\'CODIGO\\', AR.descripcionArticulo\\'DETALLE\\', case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'   then concat(MON.simboloMoneda,\\' \\',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2)) else  ROUND(LPA.precioArticulo,2)   end   \\'Precio sin I.V.A\\',  case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion= \\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'  then  concat(MON.simboloMoneda,\\' \\',LPA.precioArticulo)  else   ROUND(LPA.precioArticulo*IV.factorMultiplicador,2)  end \\'Precio I.V.A Inc.\\'     FROM Articulos AR  JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda  JOIN Ivas IV on IV.codigoIva=AR.codigoIva   JOIN SubRubros SUB on SUB.codigoSubRubro=AR.codigoSubRubro JOIN Rubros RUB on RUB.codigoRubro=SUB.codigoRubro  where AR.activo=1 and LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\'  and SUB.codigoSubRubro=\\'@_codigoSubRubro\\' order by  (case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_ARTICULO\\' limit 1)=\\'1\\' then CONVERT(AR.codigoArticulo, UNSIGNED INTEGER) else 2 end);' WHERE `codigoReporte`='34';","179")){
                            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Cliente\\',  concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\')\\')\\'Documento\\',  DOC.fechaHoraGuardadoDocumentoSQL\\'Fecha Creacion Doc.\\',  case when DOC.codigoVendedorComisiona is null or DOC.codigoVendedorComisiona=\\'0\\' then \\'Sin Vendedor\\' else concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)end \\'Vendedor\\',  MON.simboloMoneda\\'\\', case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2)   when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2)  else ROUND(0.00,2) end \\'Movimientos\\'  from Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  left join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona where DOC.tipoCliente=1   and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   and TDOC.afectaCuentaCorriente!=0  and DOC.codigoCliente=\\'@_codigoCliente\\'   and MON.codigoMoneda=\\'@_codigoMonedaReporte\\' order by DOC.fechaHoraGuardadoDocumentoSQL asc ;' WHERE `codigoReporte`='42';","179")){
                                if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Proveedor\\', concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\')\\')\\'Documento\\', DOC.fechaHoraGuardadoDocumentoSQL\\'Fecha Creacion Doc.\\', case when DOC.codigoVendedorComisiona is null or DOC.codigoVendedorComisiona=\\'0\\' then \\'Sin Vendedor\\' else concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)end \\'Vendedor\\',   MON.simboloMoneda\\'\\',  case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \\'Movimientos\\'  from Documentos DOC   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente   left join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona  where DOC.tipoCliente=2  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and TDOC.afectaCuentaCorriente!=0   and DOC.codigoCliente=\\'@_codigoProveedor\\'   and MON.codigoMoneda=\\'@_codigoMonedaReporte\\'  order by DOC.fechaHoraGuardadoDocumentoSQL asc ;' WHERE `codigoReporte`='43';","179")){
                                    if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Cliente\\', concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\')\\')\\'Documento\\',  DOC.fechaHoraGuardadoDocumentoSQL\\'Fecha Creacion Doc.\\', case when DOC.codigoVendedorComisiona is null or DOC.codigoVendedorComisiona=\\'0\\' then \\'Sin Vendedor\\' else concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)end \\'Vendedor\\',  MON.simboloMoneda\\'\\',  case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \\'Movimientos\\' from Documentos DOC    join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente    left join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona where DOC.tipoCliente=1   and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and TDOC.afectaCuentaCorriente!=0   and DOC.codigoCliente=\\'@_codigoCliente\\'   and MON.codigoMoneda=\\'@_codigoMonedaReporte\\'  and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' order by DOC.fechaHoraGuardadoDocumentoSQL asc ; ' WHERE `codigoReporte`='44';","179")){
                                        if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Proveedor\\', concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\')\\')\\'Documento\\',  DOC.fechaHoraGuardadoDocumentoSQL\\'Fecha Creacion Doc.\\',  case when DOC.codigoVendedorComisiona is null or DOC.codigoVendedorComisiona=\\'0\\' then \\'Sin Vendedor\\' else concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)end \\'Vendedor\\',  MON.simboloMoneda\\'\\',  case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \\'Movimientos\\' from Documentos DOC    join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente     left join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona   where DOC.tipoCliente=2   and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and TDOC.afectaCuentaCorriente!=0   and DOC.codigoCliente=\\'@_codigoCliente\\'   and MON.codigoMoneda=\\'@_codigoMonedaReporte\\'  and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' order by DOC.fechaHoraGuardadoDocumentoSQL asc ;' WHERE `codigoReporte`='45';","179")){
                                            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select DOC.fechaEmisionDocumento\\'Fecha\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\'    from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo    where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'  and DOCL.codigoArticulo=\\'@_codigoArticulo\\' group by DOC.fechaEmisionDocumento,DOCL.codigoArticulo order by 1 asc;', `consultaSqlCabezal`='Select concat(\\'ARTICULO: \\',descripcionArticulo,\\'(\\',codigoArticulo,\\')\\') from Articulos where codigoArticulo=\\'@_codigoArticulo\\';' WHERE `codigoReporte`='21';","179")){
                                                if(impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('21', '1', '2', '1', '', 'TEXTO');","179")){
                                                    if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaGraficas`) VALUES ('54', '4', 'Ventas entre fechas detallado sin imp.', 'select   concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\')\\')\\'Documento (Fecha)\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND(DOC.precioSubTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda )*TDOC.afectaTotales,2) end) \\'Total $\\',   sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND(DOC.precioSubTotalVenta/(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=2 )*TDOC.afectaTotales,2) end) \\'Total U$S\\'      from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'    group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;', 'select   concat(\\'Fecha: \\',( case when  MONTH(DOC.fechaEmisionDocumento)=1 then \\'Enero\\'  when  MONTH(DOC.fechaEmisionDocumento)=2 then \\'Febrero\\'  when  MONTH(DOC.fechaEmisionDocumento)=3 then \\'Marzo\\' when  MONTH(DOC.fechaEmisionDocumento)=4 then \\'Abril\\' when  MONTH(DOC.fechaEmisionDocumento)=5 then \\'Mayo\\' when  MONTH(DOC.fechaEmisionDocumento)=6 then \\'Junio\\' when  MONTH(DOC.fechaEmisionDocumento)=7 then \\'Julio\\'   when  MONTH(DOC.fechaEmisionDocumento)=8 then \\'Agosto\\' when  MONTH(DOC.fechaEmisionDocumento)=9 then \\'Setiembre\\'  when  MONTH(DOC.fechaEmisionDocumento)=10 then \\'Octubre\\' when  MONTH(DOC.fechaEmisionDocumento)=11 then \\'Noviembre\\' when  MONTH(DOC.fechaEmisionDocumento)=12 then \\'Diciembre\\'  else \\'Mes Incorrecto\\' end)  ,\\' de \\',YEAR(DOC.fechaEmisionDocumento))\\'fecha\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND(DOC.precioSubTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda )*TDOC.afectaTotales,2) end) \\'Total $\\', \\'$\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND(DOC.precioSubTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda )*TDOC.afectaTotales,2) end)   from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'     and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'      group by YEAR(DOC.fechaEmisionDocumento), MONTH(DOC.fechaEmisionDocumento) order by DOC.fechaEmisionDocumento desc; ', '', '1', '1', '1');","179")){
                                                        if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('54', '0', '0', '0', '', 'TEXTO'),('54', '1', '2', '1', '', 'MONTO'),('54', '2', '2', '1', '', 'MONTO');","180")){
                                                            _iterador=false; return false;
                                                        }
                                                    }else{_iterador=false; return false;}
                                                }else{_iterador=false; return false;}
                                            }else{_iterador=false; return false;}
                                        }else{_iterador=false; return false;}
                                    }else{_iterador=false; return false;}
                                }else{_iterador=false; return false;}
                            }else{_iterador=false; return false;}
                        }else{_iterador=false; return false;}
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 180:
            if(impactoCambioEnBD("UPDATE `ReportesConfiguracion` SET `totalizacionColumna`='1' WHERE `codigoReporte`='47' and`columnaReporte`='5';","180")){
                if(impactoCambioEnBD("UPDATE `ReportesConfiguracion` SET `totalizacionColumna`='1' WHERE `codigoReporte`='51' and`columnaReporte`='5';","180")){
                    if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT  concat(CLI.codigoCliente,\\' - \\',CLI.nombreCliente)\\'Cliente\\', CLI.razonSocial\\'Razón social\\', LOC.descripcionLocalidad\\'Localidad\\', concat(CLI.direccion, case when trim(CLI.codigoPostal)=\\'\\' or CLI.codigoPostal is null then \\'\\' else \\' - C.P.: \\' end ,CLI.codigoPostal)\\'Dirección + C. Postal\\', CLI.telefono\\'Telefono\\' /*DATE_FORMAT(CLI.fechaAlta, \\'%Y-%m-%d\\')\\'Fecha de alta\\'*/ FROM Clientes CLI join Localidades LOC on LOC.codigoPais=CLI.codigoPais and LOC.codigoDepartamento=CLI.codigoDepartamento and LOC.codigoLocalidad=CLI.codigoLocalidad  where CLI.tipoCliente=1;' WHERE `codigoReporte`='3';","180")){
                        if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('3', '0', '0', '0', '', 'TEXTO'),('3', '1', '0', '0', '', 'TEXTO'),('3', '2', '0', '0', '', 'TEXTO'),('3', '3', '0', '0', '', 'TEXTO'),('3', '4', '0', '0', '', 'TEXTO');","181")){
                            _iterador=false; return false;
                        }
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 181:
            if(!impactoCambioEnBD("ALTER TABLE `Documentos` ADD COLUMN `cae_codigoSeguridad` VARCHAR(45) NOT NULL DEFAULT '' AFTER `saldoClientePagoContado`, ADD COLUMN `cae_fechaVencimiento` DATE NOT NULL DEFAULT '0000-00-00' AFTER `cae_codigoSeguridad`, ADD COLUMN `cae_numeroCae` VARCHAR(45) NOT NULL DEFAULT '' AFTER `cae_fechaVencimiento`,                                  ADD COLUMN `cae_rangoDesde` VARCHAR(45) NOT NULL DEFAULT '' AFTER `cae_numeroCae`,ADD COLUMN `cae_rangoHasta` VARCHAR(45) NOT NULL DEFAULT '' AFTER `cae_rangoDesde`,ADD COLUMN `cae_serie` VARCHAR(10) NOT NULL DEFAULT '' AFTER `cae_rangoHasta`, ADD COLUMN `cae_Cae` VARCHAR(45) NOT NULL DEFAULT '' AFTER `cae_serie`, ADD COLUMN `cae_urlCode` VARCHAR(500) NOT NULL DEFAULT '' AFTER `cae_Cae`, ADD COLUMN `cae_QrCode` VARCHAR(2000) NOT NULL DEFAULT '' AFTER `cae_urlCode`;","182")){
                _iterador=false; return false;
            }
            break;
        case 182:
            if(!impactoCambioEnBD("ALTER TABLE `Documentos` CHANGE COLUMN `cae_numeroCae` `cae_numeroCae` VARCHAR(45) NOT NULL DEFAULT '' AFTER `saldoClientePagoContado`, CHANGE COLUMN `cae_serie` `cae_serie` VARCHAR(10) NOT NULL DEFAULT '' AFTER `cae_numeroCae`, CHANGE COLUMN `cae_fechaVencimiento` `cae_fechaVencimiento` DATE NOT NULL DEFAULT '0000-00-00' AFTER `cae_serie`, CHANGE COLUMN `cae_Cae` `cae_Cae` VARCHAR(45) NOT NULL DEFAULT '' AFTER `cae_codigoSeguridad`, CHANGE COLUMN `cae_codigoSeguridad` `cae_codigoSeguridad` VARCHAR(45) NOT NULL DEFAULT '' ,CHANGE COLUMN `cae_urlCode` `cae_urlCode` VARCHAR(500) NOT NULL DEFAULT '' , CHANGE COLUMN `cae_QrCode` `cae_QrCode` VARCHAR(2000) NOT NULL DEFAULT '' ;","183")){
                _iterador=false; return false;
            }
            break;
        case 183:
            if(!impactoCambioEnBD("ALTER TABLE `Documentos` CHANGE COLUMN `cae_rangoDesde` `cae_rangoDesde` VARCHAR(45) NOT NULL DEFAULT '' , CHANGE COLUMN `cae_rangoHasta` `cae_rangoHasta` VARCHAR(45) NOT NULL DEFAULT '' ;","184")){
                _iterador=false; return false;
            }
            break;
        case 184:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `utilizaMonedas`) VALUES ('55', '5', 'Saldo Total de clientes por moneda', 'SELECT DOC.codigoCliente\\'CODIGO CLIENTE\\', CLI.razonSocial\\'RAZON SOCIAL\\', MON.simboloMoneda\\'\\', sum(round(DOC.saldoClienteCuentaCorriente,2))\\'SALDO\\' FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente where  	DOC.tipoCliente=\\'1\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and TDOC.afectaCuentaCorriente=1  and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'   and DOC.saldoClienteCuentaCorriente!=0 group by DOC.codigoCliente order by DOC.codigoCliente asc ;', '1');","184")){
                if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('55', '3', '2', '1', '', 'MONTO');","185")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 185:
            if(!impactoCambioEnBD("ALTER TABLE `TipoDocumento` ADD COLUMN `noAfectaIva` CHAR(1) NOT NULL DEFAULT '0' AFTER `documentoAceptaIngresoDeMediosDePagoLuegoDeEmitido`;","186")){
                _iterador=false; return false;
            }
            break;
        case 186:
            if(!impactoCambioEnBD("ALTER TABLE `TipoDocumento` ADD COLUMN `ordenDelMenu` INT NOT NULL DEFAULT 99 AFTER `descripcionTipoDocumento`;","187")){
                _iterador=false; return false;
            }
            break;
        case 187:
            if(!impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaRubros`, `utilizaListaPrecio`) VALUES ('56', '4', 'Ventas entre fechas por rubro y lista de precio', 'select  AR.codigoArticulo\\'Codigo art.\\', AR.descripcionArticulo\\'Descripción\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'# ventas\\' ,case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end \\'Stock Real\\',MON.simboloMoneda\\'Moneda\\', LPA.precioArticulo\\'Precio Artículo\\', AR.descripcionExtendida\\'Descripción extendida\\' from  DocumentosLineas DOCL   left join Documentos DOC  on DOC.codigoDocumento=DOCL.codigoDocumento and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo   join SubRubros SR on SR.codigoSubRubro=AR.codigoSubRubro join Rubros RU on RU.codigoRubro=SR.codigoRubro join Monedas MON on MON.codigoMoneda=AR.codigoMoneda join ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo where   DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\' and LPA.codigoListaPrecio=1 and LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'    and RU.codigoRubro=\\'@_codigoRubro\\'   group by AR.codigoArticulo  order by  RU.codigoRubro, SR.codigoSubRubro,AR.codigoArticulo;', '', '', '1', '1', '1', '1');","188")){
                _iterador=false; return false;
            }
            break;
        case 188:
            if(!impactoCambioEnBD("ALTER TABLE `TipoDocumento` ADD COLUMN `utilizaSeteoDePreciosEnListasDePrecioPorArticulo` CHAR(1) NOT NULL DEFAULT '0' AFTER `noAfectaIva`;","189")){
                _iterador=false; return false;
            }
            break;
        case 189:
            if(!impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaRubros`) VALUES ('57', '4', 'Artículos sin venta por rubro entre fechas', 'select AR.codigoArticulo\\'Codigo Artículo\\',AR.descripcionArticulo\\'Nombre Arículo\\' from Articulos AR join SubRubros SUR on SUR.codigoSubRubro=AR.codigoSubRubro join Rubros RUB on RUB.codigoRubro=SUR.codigoRubro where  RUB.codigoRubro=\\'@_codigoRubro\\'  and ((select sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\'   from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.afectaTotales!=0  and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' ) is null or (select sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\'   from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.afectaTotales!=0  and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' )=0)  order by CONVERT(AR.codigoArticulo, SIGNED INTEGER);', '', '', '1', '1', '1');","190")){
                _iterador=false; return false;
            }
            break;
        case 190:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(DOCL.codigoArticulo,\\' - \\',AR.descripcionArticulo)\\'Artículo\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.afectaTotales!=0 and TDOC.esDocumentoDeVenta=\\'1\\' and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'  group by DOCL.codigoArticulo order by 2 desc limit @_cantidad ;' WHERE `codigoReporte`='12';","190")){
                if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(DOCL.codigoArticulo,\\' - \\',AR.descripcionArticulo)\\'Artículo\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.afectaTotales!=0 and TDOC.esDocumentoDeVenta=\\'1\\' group by DOCL.codigoArticulo order by 2 desc limit @_cantidad ;' WHERE `codigoReporte`='11';","190")){
                    if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(DOCL.codigoArticulo,\\' - \\',AR.descripcionArticulo)\\'Artículo\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.afectaTotales!=0 and TDOC.esDocumentoDeVenta=\\'1\\' group by DOCL.codigoArticulo order by 2 asc limit @_cantidad ;' WHERE `codigoReporte`='20';","191")){
                        _iterador=false; return false;
                    }
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 191:
            if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SET @v1 = (select CONF.valorConfiguracion from Configuracion CONF where CONF.codigoConfiguracion=\\'MODO_CLIENTE\\'); SELECT  concat(CLI.codigoCliente,\\' - \\',CLI.nombreCliente)\\'Cliente\\', CLI.razonSocial\\'Razón social\\', LOC.descripcionLocalidad\\'Localidad\\', concat(CLI.direccion, case when trim(CLI.codigoPostal)=\\'\\' or CLI.codigoPostal is null then \\'\\' else \\' - C.P.: \\' end ,CLI.codigoPostal)\\'Dirección + C. Postal\\', CLI.telefono\\'Telefono\\' /*DATE_FORMAT(CLI.fechaAlta, \\'%Y-%m-%d\\')\\'Fecha de alta\\'*/ FROM Clientes CLI join Localidades LOC on LOC.codigoPais=CLI.codigoPais and LOC.codigoDepartamento=CLI.codigoDepartamento and LOC.codigoLocalidad=CLI.codigoLocalidad  where CLI.tipoCliente=1 order by  IF(@v1=1,CONVERT(CLI.codigoCliente, SIGNED INTEGER),0) asc,IF(@v1=0,CLI.codigoCliente,0) asc;' WHERE `codigoReporte`='3';","192")){
                _iterador=false; return false;
            }
            break;
        case 192:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SET @v1 = (select CONF.valorConfiguracion from Configuracion CONF where CONF.codigoConfiguracion=\\'MODO_CLIENTE\\'); SELECT concat(CLI.codigoCliente,\\' - \\',CLI.razonSocial)\\'Razón social\\', LOC.descripcionLocalidad\\'Localidad\\', concat(CLI.direccion, case when trim(CLI.codigoPostal)=\\'\\' or CLI.codigoPostal is null then \\'\\' else \\' - C.P.: \\' end ,CLI.codigoPostal)\\'Dirección + C. Postal\\', CLI.telefono\\'Telefono\\' /*DATE_FORMAT(CLI.fechaAlta, \\'%Y-%m-%d\\')\\'Fecha de alta\\'*/ FROM Clientes CLI join Localidades LOC on LOC.codigoPais=CLI.codigoPais and LOC.codigoDepartamento=CLI.codigoDepartamento and LOC.codigoLocalidad=CLI.codigoLocalidad  where CLI.tipoCliente=1 order by  IF(@v1=1,CONVERT(CLI.codigoCliente, SIGNED INTEGER),0) asc,IF(@v1=0,CLI.codigoCliente,0) asc;' WHERE `codigoReporte`='3';","192")){
                if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select  AR.codigoArticulo\\'Cod.\\',AR.descripcionArticulo\\'Descripción\\',  case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end \\'Stock R.\\', RIGHT(case when (select concat(MON.simboloMoneda,\\'   \\',round(DOCL.precioArticuloUnitario,2)) from Documentos DOC  join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1 and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) is null then \\'N/A\\' else (select concat(MON.simboloMoneda,\\'   \\',round(DOCL.precioArticuloUnitario,2)) from Documentos DOC  join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1 and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) end,9)  \\'Cos.mon.ext.\\',  AR.descripcionExtendida\\'Cod. origen\\',  case when (select DOC.fechaEmisionDocumento from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1 and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) is null then \\'0000-00-00\\' else  (select DOC.fechaEmisionDocumento from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1 and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) end \\'Fecha.últ.com.\\',   RIGHT(case when (select sum(DOCL.cantidad) from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1  and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  group by DOC.fechaEmisionDocumento  order by  DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) is null then \\'N/A\\'  else   convert((select sum(DOCL.cantidad) from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1  and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  group by DOC.fechaEmisionDocumento  order by  DOC.fechaHoraGuardadoDocumentoSQL desc limit 1),unsigned INTEGER) end,5) \\'Cant.últ.com.\\',  case when(select DOC.fechaEmisionDocumento from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=-1 and TDOC.utilizaCliente=1 and TDOC.esDocumentoDeVenta=1 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) is null then \\'0000-00-00\\' else  (select DOC.fechaEmisionDocumento from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=-1 and TDOC.utilizaCliente=1 and TDOC.esDocumentoDeVenta=1 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) end \\'Fecha.últ.ven\\' from Articulos AR join Clientes CLI on CLI.codigoCliente=AR.codigoProveedor and CLI.tipoCliente=AR.tipoCliente  where CLI.codigoCliente=\\'@_codigoProveedor\\' and CLI.tipoCliente=2   order by CONVERT(AR.codigoArticulo, SIGNED INTEGER);' WHERE `codigoReporte`='53';","193")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 193:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SET @v1 = (select CONF.valorConfiguracion from Configuracion CONF where CONF.codigoConfiguracion=\\'MODO_ARTICULO\\'); SELECT AR.codigoArticulo\\'Código\\', AR.descripcionArticulo\\'Nombre\\', AR.descripcionExtendida\\'Descripción extendida\\', FORMAT(case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end,0) \\'Cantidad Real\\'  , case when AR.activo=1 then \\'activo\\' else \\'¡ARTÍCULO INACTIVO!\\' end\\'Estado\\'  FROM Articulos AR  order by  IF(@v1=1,CONVERT(AR.codigoArticulo, SIGNED INTEGER),0) asc,IF(@v1=0,AR.codigoArticulo,0) asc;' WHERE `codigoReporte`='18';","193")){
                if(impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('18', '0', '0', '0', '', 'TEXTO');","193")){
                    if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('18', '1', '0', '0', '', 'TEXTO');","194")){
                        _iterador=false; return false;
                    }
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 194:
            if(!impactoCambioEnBD("UPDATE `ReportesConfiguracion` SET `alineacionColumna`='2' WHERE `codigoReporte`='18' and`columnaReporte`='3';","195")){
                _iterador=false; return false;
            }
            break;
        case 195:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaFechaDesde`, `utilizaFechaHasta`) VALUES ('58', '1', 'Artículos sin venta y sin stock', 'SELECT * FROM  (select AR.codigoArticulo AS Codigo,AR.descripcionArticulo \\'Nombre Artículo\\', case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end AS Stock , (select    sum(DOCL.cantidad) from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'    and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo    group by DOCL.codigoArticulo) AS CantidadVenta  		from Articulos AR  join Clientes CLI on CLI.codigoCliente=AR.codigoProveedor and CLI.tipoCliente=AR.tipoCliente       ) sub  WHERE (sub.Stock<=0 or sub.cantidadVenta is null or sub.CantidadVenta=0)     order by CONVERT(sub.Codigo, SIGNED INTEGER);', '', '', '1', '1');","195")){
                if(impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('58', '0', '0', '0', '', 'TEXTO');","195")){
                    if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('58', '1', '0', '0', '', 'TEXTO');","196")){
                        _iterador=false; return false;
                    }
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 196:
            if(!impactoCambioEnBD("ALTER TABLE `Reportes` ADD COLUMN `utilizaTipoClasificacionCliente` CHAR(1) NOT NULL DEFAULT '0' AFTER `utilizaOrdenEnReporte`;","197")){
                _iterador=false; return false;
            }
            break;
        case 197:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(( case when  MONTH(DOC.fechaEmisionDocumento)=1 then \\'Enero\\'  when  MONTH(DOC.fechaEmisionDocumento)=2 then \\'Febrero\\'  when  MONTH(DOC.fechaEmisionDocumento)=3 then \\'Marzo\\' when  MONTH(DOC.fechaEmisionDocumento)=4 then \\'Abril\\' when  MONTH(DOC.fechaEmisionDocumento)=5 then \\'Mayo\\' when  MONTH(DOC.fechaEmisionDocumento)=6 then \\'Junio\\' when  MONTH(DOC.fechaEmisionDocumento)=7 then \\'Julio\\'   when  MONTH(DOC.fechaEmisionDocumento)=8 then \\'Agosto\\' when  MONTH(DOC.fechaEmisionDocumento)=9 then \\'Setiembre\\'  when  MONTH(DOC.fechaEmisionDocumento)=10 then \\'Octubre\\' when  MONTH(DOC.fechaEmisionDocumento)=11 then \\'Noviembre\\' when  MONTH(DOC.fechaEmisionDocumento)=12 then \\'Diciembre\\'  else \\'Mes Incorrecto\\' end)  ,\\' de \\',YEAR(DOC.fechaEmisionDocumento))\\'fecha\\',   sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND((DOC.precioTotalVenta*DOC.cotizacionMoneda)*TDOC.afectaTotales,2) end) \\'Total $\\',   sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND((DOC.precioTotalVenta/DOC.cotizacionMoneda)*TDOC.afectaTotales,2) end) \\'Total U$S\\'       from  Documentos DOC   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'      and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'      group by YEAR(DOC.fechaEmisionDocumento), MONTH(DOC.fechaEmisionDocumento) order by DOC.fechaEmisionDocumento; ' WHERE `codigoReporte`='39';","197")){
                if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select   concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\')\\')\\'Documento (Fecha)\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND((DOC.precioSubTotalVenta*DOC.cotizacionMoneda )*TDOC.afectaTotales,2) end) \\'Total $\\',   sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND((DOC.precioSubTotalVenta/DOC.cotizacionMoneda)*TDOC.afectaTotales,2) end) \\'Total U$S\\'      from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'    group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;' WHERE `codigoReporte`='54';","197")){
                    if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select   concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\')\\')\\'Documento (Fecha)\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND((DOC.precioTotalVenta*DOC.cotizacionMoneda)*TDOC.afectaTotales,2) end) \\'Total $\\',  sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND((DOC.precioTotalVenta/DOC.cotizacionMoneda)*TDOC.afectaTotales,2) end) \\'Total U$S\\'     from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'    group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;' WHERE `codigoReporte`='38';","197")){
                        if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT   concat((case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end),\\' (\\',DOC.codigoCliente,\\')\\')\\'CLIENTE\\',  concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\')\\')\\'Documento\\',  DOC.fechaEmisionDocumento\\'FECHA DOCUMENTO\\',  case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(((DOC.precioTotalVenta*DOC.cotizacionMoneda))*TDOC.afectaTotales,2) end \\'Total $\\',   case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(((DOC.precioTotalVenta/DOC.cotizacionMoneda))*TDOC.afectaTotales,2) end \\'Total U$S\\'   FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.codigoCliente=\\'@_codigoCliente\\' and  DOC.tipoCliente=1  and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'  order by DOC.fechaEmisionDocumento desc ;' WHERE `codigoReporte`='19';","197")){
                            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select  concat(SR.codigoSubRubro,\\' - \\',SR.descripcionSubRubro)\\'SubRubro\\',  sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\' , sum(case when MON.codigoMoneda=1 then  ROUND(DOCL.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND((DOCL.precioTotalVenta*DOC.cotizacionMoneda)*TDOC.afectaTotales,2) end) \\'Total $\\',  sum(case when MON.codigoMoneda=2 then  ROUND(DOCL.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND((DOCL.precioTotalVenta/DOC.cotizacionMoneda)*TDOC.afectaTotales,2) end) \\'Total U$S\\'    from  DocumentosLineas DOCL  left join Documentos DOC  on DOC.codigoDocumento=DOCL.codigoDocumento and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo  join SubRubros SR on SR.codigoSubRubro=AR.codigoSubRubro join Rubros RU on RU.codigoRubro=SR.codigoRubro  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'   and RU.codigoRubro=\\'@_codigoRubro\\'  group by RU.codigoRubro,SR.codigoSubRubro  order by RU.descripcionRubro,SR.descripcionSubRubro; ' WHERE `codigoReporte`='32';","197")){
                                if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT  concat(CLI.razonSocial,\\'(\\',CLI.codigoCliente,\\')\\')\\'Cliente\\',  concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\')\\')\\'Documento\\',  case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(((DOC.precioTotalVenta*DOC.cotizacionMoneda))*TDOC.afectaTotales,2) end \\'Total $\\',  case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(((DOC.precioTotalVenta/DOC.cotizacionMoneda))*TDOC.afectaTotales,2) end \\'Total U$S\\' FROM Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'  and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'  and DOC.codigoVendedorComisiona=\\'@_codigoVendedor\\' order by DOC.fechaEmisionDocumento asc ; ' WHERE `codigoReporte`='14';","198")){
                                    _iterador=false; return false;
                                }
                            }else{_iterador=false; return false;}
                        }else{_iterador=false; return false;}
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 198:
            if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT  concat(CLI.razonSocial,\\'(\\',CLI.codigoCliente,\\')\\')\\'Cliente\\', concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\')\\')\\'Documento\\', case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta,2)*TDOC.afectaTotales  else ROUND((DOC.precioSubTotalVenta*DOC.cotizacionMoneda),2)*TDOC.afectaTotales end \\'Total $\\', case when MON.codigoMoneda=2 then  ROUND(DOC.precioSubTotalVenta,2)*TDOC.afectaTotales  else ROUND((DOC.precioSubTotalVenta/DOC.cotizacionMoneda),2)*TDOC.afectaTotales end \\'Total U$S\\'    FROM Documentos DOC   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')   and TDOC.esDocumentoDeVenta=\\'1\\'  and DOC.fechaEmisionDocumento    between \\'@_desde\\' and \\'@_hasta\\'    and DOC.codigoVendedorComisiona=\\'@_codigoVendedor\\'  order by DOC.fechaEmisionDocumento asc ;' WHERE `codigoReporte`='26';","199")){
                _iterador=false; return false;
            }
            break;
        case 199:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT   concat((case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end),\\' (\\',DOC.codigoCliente,\\')\\')\\'CLIENTE\\',   concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\')\\')\\'Documento\\',   DOC.fechaEmisionDocumento\\'FECHA DOCUMENTO\\',   case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total $\\', case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total U$S\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.codigoCliente=\\'@_codigoCliente\\' and  DOC.tipoCliente=1   and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'   order by DOC.fechaEmisionDocumento desc ;' WHERE `codigoReporte`='19';","199")){
                if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT    concat(CLI.razonSocial,\\'(\\',CLI.codigoCliente,\\')\\')\\'Cliente\\',   concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\')\\')\\'Documento\\',   case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total $\\', case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total U$S\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'  and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'   and DOC.codigoVendedorComisiona=\\'@_codigoVendedor\\'  order by DOC.fechaEmisionDocumento asc ;' WHERE `codigoReporte`='14';","199")){
                    if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT  concat(CLI.razonSocial,\\'(\\',CLI.codigoCliente,\\')\\')\\'Cliente\\',  concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\')\\')\\'Documento\\',  case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta,2)*TDOC.afectaTotales  else ROUND(0,2)*TDOC.afectaTotales end \\'Total $\\',  case when MON.codigoMoneda=2 then  ROUND(DOC.precioSubTotalVenta,2)*TDOC.afectaTotales  else ROUND(0,2)*TDOC.afectaTotales end \\'Total U$S\\'    FROM Documentos DOC   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')      and TDOC.esDocumentoDeVenta=\\'1\\'  and DOC.fechaEmisionDocumento    between \\'@_desde\\' and \\'@_hasta\\'    and DOC.codigoVendedorComisiona=\\'@_codigoVendedor\\'  order by DOC.fechaEmisionDocumento asc ;' WHERE `codigoReporte`='26';","199")){
                        if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select  concat(SR.codigoSubRubro,\\' - \\',SR.descripcionSubRubro)\\'SubRubro\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\' , sum(case when MON.codigoMoneda=1 then  ROUND(DOCL.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',  sum(case when MON.codigoMoneda=2 then  ROUND(DOCL.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\'    from  DocumentosLineas DOCL  left join Documentos DOC  on DOC.codigoDocumento=DOCL.codigoDocumento and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo  join SubRubros SR on SR.codigoSubRubro=AR.codigoSubRubro join Rubros RU on RU.codigoRubro=SR.codigoRubro  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'  and RU.codigoRubro=\\'@_codigoRubro\\'  group by RU.codigoRubro,SR.codigoSubRubro  order by RU.descripcionRubro,SR.descripcionSubRubro; ' WHERE `codigoReporte`='32';","199")){
                            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select   concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\')\\')\\'Documento (Fecha)\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',  sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\'     from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'    group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;' WHERE `codigoReporte`='38';","199")){
                                if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(( case when  MONTH(DOC.fechaEmisionDocumento)=1 then \\'Enero\\'  when  MONTH(DOC.fechaEmisionDocumento)=2 then \\'Febrero\\'  when  MONTH(DOC.fechaEmisionDocumento)=3 then \\'Marzo\\' when  MONTH(DOC.fechaEmisionDocumento)=4 then \\'Abril\\' when  MONTH(DOC.fechaEmisionDocumento)=5 then \\'Mayo\\' when  MONTH(DOC.fechaEmisionDocumento)=6 then \\'Junio\\' when  MONTH(DOC.fechaEmisionDocumento)=7 then \\'Julio\\'   when  MONTH(DOC.fechaEmisionDocumento)=8 then \\'Agosto\\' when  MONTH(DOC.fechaEmisionDocumento)=9 then \\'Setiembre\\'  when  MONTH(DOC.fechaEmisionDocumento)=10 then \\'Octubre\\' when  MONTH(DOC.fechaEmisionDocumento)=11 then \\'Noviembre\\' when  MONTH(DOC.fechaEmisionDocumento)=12 then \\'Diciembre\\'  else \\'Mes Incorrecto\\' end)  ,\\' de \\',YEAR(DOC.fechaEmisionDocumento))\\'fecha\\',   sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',  sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\' from  Documentos DOC   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'     group by YEAR(DOC.fechaEmisionDocumento), MONTH(DOC.fechaEmisionDocumento) order by DOC.fechaEmisionDocumento; ' WHERE `codigoReporte`='39';","200")){
                                    _iterador=false; return false;
                                }
                            }else{_iterador=false; return false;}
                        }else{_iterador=false; return false;}
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 200:
            if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select   concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\')\\')\\'Documento (Fecha)\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',   sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\'      from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'   group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;' WHERE `codigoReporte`='54';","201")){
                _iterador=false; return false;
            }
            break;
        case 201:
            if(impactoCambioEnBD("ALTER TABLE `Documentos`  CHANGE COLUMN `precioTotalVenta` `precioTotalVenta` DECIMAL(45,4) NOT NULL DEFAULT '0.00' ,  CHANGE COLUMN `precioSubTotalVenta` `precioSubTotalVenta` DECIMAL(45,4) NOT NULL DEFAULT '0.00' , CHANGE COLUMN `precioSubTotalVentaSinDescuento` `precioSubTotalVentaSinDescuento` DECIMAL(45,4) NOT NULL DEFAULT '0.00' ,  CHANGE COLUMN `precioIvaVenta` `precioIvaVenta` DECIMAL(45,4) NOT NULL DEFAULT '0.00' ,  CHANGE COLUMN `totalIva1` `totalIva1` DECIMAL(45,4) NOT NULL DEFAULT '0.00' , CHANGE COLUMN `totalIva2` `totalIva2` DECIMAL(45,4) NOT NULL DEFAULT '0.00' , CHANGE COLUMN `totalIva3` `totalIva3` DECIMAL(45,4) NOT NULL DEFAULT '0.00' , CHANGE COLUMN `montoDescuentoTotal` `montoDescuentoTotal` DECIMAL(45,4) NOT NULL DEFAULT '0.00' , CHANGE COLUMN `porcentajeDescuentoAlTotal` `porcentajeDescuentoAlTotal` DECIMAL(45,4) NOT NULL DEFAULT '0.00' , CHANGE COLUMN `saldoClienteCuentaCorriente` `saldoClienteCuentaCorriente` DECIMAL(45,4) NOT NULL DEFAULT '0.00' , CHANGE COLUMN `saldoClientePagoContado` `saldoClientePagoContado` DECIMAL(45,4) NOT NULL DEFAULT '0.00' ;","201")){
                if(impactoCambioEnBD("ALTER TABLE `DocumentosCanceladosCuentaCorriente` CHANGE COLUMN `montoDescontadoCuentaCorriente` `montoDescontadoCuentaCorriente` DECIMAL(45,4) NOT NULL DEFAULT '0.00' ;","201")){
                    if(impactoCambioEnBD("ALTER TABLE `DocumentosLineas` CHANGE COLUMN `precioTotalVenta` `precioTotalVenta` DECIMAL(45,4) NOT NULL DEFAULT '0.00' ,             CHANGE COLUMN `precioArticuloUnitario` `precioArticuloUnitario` DECIMAL(45,4) NOT NULL DEFAULT '0.00' , CHANGE COLUMN `precioIvaArticulo` `precioIvaArticulo` DECIMAL(45,4) NOT NULL DEFAULT '0.00' , CHANGE COLUMN `montoDescuento` `montoDescuento` DECIMAL(45,4) NOT NULL DEFAULT '0.00' , CHANGE COLUMN `costoArticuloMonedaReferencia` `costoArticuloMonedaReferencia` DECIMAL(45,4) NOT NULL DEFAULT '0.00' , CHANGE COLUMN `costoArticuloPonderado` `costoArticuloPonderado` DECIMAL(45,4) NOT NULL DEFAULT '0.00' ;","201")){
                        if(impactoCambioEnBD("ALTER TABLE `DocumentosLineasPago` CHANGE COLUMN `importePago` `importePago` DECIMAL(45,4) NULL DEFAULT NULL , CHANGE COLUMN `montoCobrado` `montoCobrado` DECIMAL(45,4) NOT NULL DEFAULT '0.00' ;","201")){
                            if(impactoCambioEnBD("ALTER TABLE `Ivas`  CHANGE COLUMN `porcentajeIva` `porcentajeIva` DECIMAL(45,4) UNSIGNED NULL DEFAULT NULL , CHANGE COLUMN `factorMultiplicador` `factorMultiplicador` DECIMAL(45,4) UNSIGNED NULL DEFAULT NULL ;","201")){
                                if(!impactoCambioEnBD("ALTER TABLE `ListaPrecioArticulos` CHANGE COLUMN `precioArticulo` `precioArticulo` DECIMAL(45,4) NULL DEFAULT NULL ;","202")){
                                    _iterador=false; return false;
                                }
                            }else{_iterador=false; return false;}
                        }else{_iterador=false; return false;}
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 202:
            if(impactoCambioEnBD("INSERT INTO `Configuracion` (`codigoConfiguracion`, `valorConfiguracion`, `descripcionConfiguracion`) VALUES ('CANTIDAD_DIGITOS_DECIMALES_MONTO', '2', 'Especifica la cantidad de digitos despues de la coma para los montos.');","202")){
                if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaTipoClasificacionCliente`) VALUES ('59', '4', 'Ventas de clientes entre fechas por clasificación', 'SET @CANTIDAD_DIGITOS_DECIMALES_MONTO = (select CONF.valorConfiguracion from Configuracion CONF where CONF.codigoConfiguracion=\\'CANTIDAD_DIGITOS_DECIMALES_MONTO\\');  SELECT   concat((case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end),\\' (\\',DOC.codigoCliente,\\')\\')\\'CLIENTE\\',  sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,@CANTIDAD_DIGITOS_DECIMALES_MONTO)  else ROUND(0,@CANTIDAD_DIGITOS_DECIMALES_MONTO) end) \\'Total $\\', sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,@CANTIDAD_DIGITOS_DECIMALES_MONTO)  else ROUND(0,@CANTIDAD_DIGITOS_DECIMALES_MONTO) end) \\'Total U$S\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\'    and  DOC.tipoCliente=1      and  DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\' and  CLI.tipoClasificacion = \\'@_codigoClasificacionClienteReporte\\' group by DOC.codigoCliente  order by CLI.razonSocial;', '', '', '1', '1', '1');","202")){
                    if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('59', '0', '0', '0', '', 'TEXTO'),('59', '1', '2', '1', '', 'MONTO'),('59', '2', '2', '1', '', 'MONTO');","203")){
                        _iterador=false; return false;
                    }
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 203:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaListaPrecio`) VALUES ('60', '4', 'Ventas de clientes entre fechas por lista de precio', 'SET @CANTIDAD_DIGITOS_DECIMALES_MONTO = (select CONF.valorConfiguracion from Configuracion CONF where CONF.codigoConfiguracion=\\'CANTIDAD_DIGITOS_DECIMALES_MONTO\\');    select * from  (SELECT   concat((case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end),\\' (\\',DOC.codigoCliente,\\')\\')\\'CLIENTE\\',   sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,@CANTIDAD_DIGITOS_DECIMALES_MONTO)  else ROUND(0,@CANTIDAD_DIGITOS_DECIMALES_MONTO) end) \\'Total $\\',  sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,@CANTIDAD_DIGITOS_DECIMALES_MONTO)  else ROUND(0,@CANTIDAD_DIGITOS_DECIMALES_MONTO) end) \\'Total U$S\\' , case when LPC.codigoListaPrecio is null then \\'Sin lista precio, asume la 1\\' else LPC.codigoListaPrecio end AS CodigoListaPrecio  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente    join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    left join ListaPrecioClientes LPC on LPC.tipoCliente=CLI.tipoCliente and LPC.codigoCliente=CLI.codigoCliente    where  	DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  	and TDOC.esDocumentoDeVenta=\\'1\\'    	and  DOC.tipoCliente=1      	and  DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'    group by DOC.codigoCliente  order by CLI.razonSocial) Sub where (((Sub.CodigoListaPrecio=\\'Sin lista precio, asume la 1\\' or Sub.CodigoListaPrecio=1) and \\'1\\'=\\'@_codigoListaPrecio\\') or  Sub.CodigoListaPrecio=\\'@_codigoListaPrecio\\');', '', '', '1', '1', '1');","203")){
                if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('60', '0', '0', '0', '', 'TEXTO'),('60', '1', '2', '1', '', 'MONTO'),('60', '2', '2', '1', '', 'MONTO');","204")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 204:
            if(!impactoCambioEnBD("INSERT INTO `Configuracion` (`codigoConfiguracion`, `valorConfiguracion`, `descripcionConfiguracion`) VALUES ('MODO_AVISO_NUEVO_DOCUMENTO', '0', 'Muestra un cuadro de dialogo que permite seleccionar un nuevo documento en la facturación, al finalizar cada factura');","205")){
                _iterador=false; return false;
            }
            break;

        case 205:
            if(!impactoCambioEnBD("CREATE TABLE `ReportesPerfilesUsuarios` (`codigoReporte` BIGINT(10) UNSIGNED NOT NULL,`codigoPerfil` INT(10) UNSIGNED NOT NULL,PRIMARY KEY (`codigoReporte`,`codigoPerfil`));","206")){
                _iterador=false; return false;
            }
            break;
        case 206:
            if(impactoCambioEnBD("ALTER TABLE `ReportesPerfilesUsuarios`  ADD INDEX `fk_codigoPerfilPerfilesUsuarios_idx` (`codigoPerfil` ASC);","206")){
                if(!impactoCambioEnBD("ALTER TABLE `ReportesPerfilesUsuarios` ADD CONSTRAINT `fk_codigoReportePerfilesUsuarios` FOREIGN KEY (`codigoReporte`)   REFERENCES `Reportes` (`codigoReporte`)   ON DELETE NO ACTION   ON UPDATE NO ACTION, ADD CONSTRAINT `fk_codigoPerfilPerfilesUsuarios`   FOREIGN KEY (`codigoPerfil`)   REFERENCES `khitomer`.`PerfilesUsuarios`  (`codigoPerfil`)   ON DELETE NO ACTION   ON UPDATE NO ACTION;","207")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 207:
            if(!impactoCambioEnBD("INSERT INTO `Configuracion` (`codigoConfiguracion`, `valorConfiguracion`, `descripcionConfiguracion`) VALUES ('CANTIDAD_DIGITOS_DECIMALES_MONTO_IMPRESION', '2', 'Especifica la cantidad de digitos despues de la coma para los montos en los documentos impresos.');","208")){
                _iterador=false; return false;
            }
            break;
        case 208:
            if(!impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaListaPrecio`, `utilizaMonedas`) VALUES ('61', '4', 'Balance por moneda y lista de precio', 'select  sum(Sub.Stock_Real*Sub.Precio_Articulo)\\'Monto balance total\\', Sub.Moneda \\'Moneda\\' from  (SELECT  AR.codigoArticulo as Codigo_Articulo, MON.simboloMoneda as Moneda, case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and DOCL.codigoArticulo=AR.codigoArticulo     and DOC.fechaHoraGuardadoDocumentoSQL>=    (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos  where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by codigoDocumento desc limit 1)  group by DOCL.codigoArticulo) end  as Stock_Real, LPA.precioArticulo as Precio_Articulo FROM Articulos AR  join ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  join Monedas MON on MON.codigoMoneda=AR.codigoMoneda join SubRubros SUBRUB on SUBRUB.codigoSubRubro=AR.codigoSubRubro  where LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' and AR.codigoMoneda=\\'@_codigoMonedaReporte\\' order by CAST(AR.codigoArticulo AS SIGNED) ) Sub where Sub.Stock_Real>0;', '', 'SELECT  concat(\\'Lista: \\',LP.descripcionListaPrecio),concat(\\'Moneda: \\',(select MON.descripcionMoneda from Monedas MON where MON.codigoMoneda=\\'@_codigoMonedaReporte\\')) from ListaPrecio LP  where LP.codigoListaPrecio=\\'@_codigoListaPrecio\\';', '1', '1');","209")){
                _iterador=false; return false;
            }
            break;
        case 209:
            if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('61', '0', '2', '0', '', 'MONTO'),('61', '1', '0', '0', '', 'TEXTO');","210")){
                _iterador=false; return false;
            }
            break;
        case 210:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaListaPrecio`, `utilizaMonedas`) VALUES ('62', '4', 'Balance por moneda y lista de precio detallado', 'select  Sub.Codigo_Articulo\\'Artículo\\', Sub.Stock_Real\\'Stock\\', Sub.Precio_Articulo\\'Costo unitario\\', Sub.Stock_Real*Sub.Precio_Articulo\\'Stock valorizado\\', Sub.Moneda  \\'Moneda\\' from  (SELECT  AR.codigoArticulo as Codigo_Articulo, MON.simboloMoneda as Moneda, case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and DOCL.codigoArticulo=AR.codigoArticulo     and DOC.fechaHoraGuardadoDocumentoSQL>=    (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos  where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by codigoDocumento desc limit 1)  group by DOCL.codigoArticulo) end  as Stock_Real, LPA.precioArticulo as Precio_Articulo FROM Articulos AR  join ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  join Monedas MON on MON.codigoMoneda=AR.codigoMoneda join SubRubros SUBRUB on SUBRUB.codigoSubRubro=AR.codigoSubRubro  where  LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' and AR.codigoMoneda=\\'@_codigoMonedaReporte\\'  order by CAST(AR.codigoArticulo AS SIGNED) ) Sub where Sub.Stock_Real>0;', '', 'SELECT  concat(\\'Lista: \\',LP.descripcionListaPrecio),concat(\\'Moneda: \\',(select MON.descripcionMoneda from Monedas MON where MON.codigoMoneda=\\'@_codigoMonedaReporte\\')) from ListaPrecio LP  where LP.codigoListaPrecio=\\'@_codigoListaPrecio\\';', '1', '1');","210")){
                if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('62', '0', '0', '0', '', 'TEXTO'),('62', '1', '2', '0', '', 'TEXTO'),('62', '2', '2', '0', '', 'MONTO'),('62', '3', '2', '1', '', 'MONTO'),('62', '4', '0', '0', '', 'TEXTO');","211")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 211:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaTipoDocumento`) VALUES ('63', '4', 'Ventas entre fechas detallado por tipo documento', 'select  concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\')\\')\\'Documento (Fecha)\\',  sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',   sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\'    from  Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\'    and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'     and DOC.codigoTipoDocumento=\\'@_codigoDocumento\\' group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;', '', '', '1', '1', '1');","211")){
                if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('63', '0', '0', '0', '', 'TEXTO'),('63', '1', '2', '1', '', 'MONTO'),('63', '2', '2', '1', '', 'MONTO');","212")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 212:
            if(!impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaTipoDocumento`) VALUES ('64', '4', 'Ventas por documento con detalle medios de pago', 'select  concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\')\\')\\'Documento (Fecha)\\',  case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total doc. en $\\',    case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total doc. en U$S\\', case when DLP.codigoMedioPago=1  then DLP.importePago else 0 end \\'Efec. $\\',  case when DLP.codigoMedioPago=2  then DLP.importePago else 0 end \\'Efec. U$S\\',  case when DLP.codigoMedioPago=3  then DLP.importePago else 0 end \\'Tarj. Cre. $\\', case when DLP.codigoMedioPago=4  then DLP.importePago else 0 end \\'Tarj. Cre. U$S\\', case when DLP.codigoMedioPago=5  then DLP.importePago else 0 end \\'Cheque $\\',  case when DLP.codigoMedioPago=6  then DLP.importePago else 0 end \\'Cheque U$S\\', case when DLP.codigoMedioPago=7  then DLP.importePago else 0 end \\'Dep. banco $\\', case when DLP.codigoMedioPago=8  then DLP.importePago else 0 end \\'Dep. banco U$S\\' from  Documentos DOC   left join DocumentosLineasPago DLP on DLP.codigoDocumento=DOC.codigoDocumento  and DLP.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\'    and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'    and DOC.codigoTipoDocumento=\\'@_codigoDocumento\\'  order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento,DLP.codigoMedioPago,DLP.monedaMedioPago;', '', '', '1', '1', '1');","213")){
                _iterador=false; return false;
            }
            break;
        case 213:
            if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('64', '0', '0', '0', '', 'TEXTO'),('64', '1', '2', '0', '', 'MONTO'),('64', '2', '2', '0', '', 'MONTO'),('64', '3', '2', '1', '', 'MONTO'),('64', '4', '2', '1', '', 'MONTO'),('64', '5', '2', '1', '', 'MONTO'),('64', '6', '2', '1', '', 'MONTO'),('64', '7', '2', '1', '', 'MONTO'),('64', '8', '2', '1', '', 'MONTO'),('64', '9', '2', '1', '', 'MONTO'),('64', '10', '2', '1', '', 'MONTO');","214")){
                _iterador=false; return false;
            }
            break;
        case 214:
            if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select  concat(Sub.Codigo_Articulo,\\' - \\', Sub.Descripcion_Articulo)\\'Artículo\\', Sub.Stock_Real\\'Stock\\', Sub.Precio_Articulo\\'Costo unitario\\',  Sub.Stock_Real*Sub.Precio_Articulo\\'Stock valorizado\\', Sub.Moneda  \\'Moneda\\' from    (SELECT  AR.codigoArticulo as Codigo_Articulo, AR.descripcionArticulo as Descripcion_Articulo , MON.simboloMoneda as Moneda, case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and DOCL.codigoArticulo=AR.codigoArticulo     and DOC.fechaHoraGuardadoDocumentoSQL>=    (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos  where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by codigoDocumento desc limit 1)  group by DOCL.codigoArticulo) end  as Stock_Real, LPA.precioArticulo as Precio_Articulo FROM Articulos AR  join ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  join Monedas MON on MON.codigoMoneda=AR.codigoMoneda join SubRubros SUBRUB on SUBRUB.codigoSubRubro=AR.codigoSubRubro  where  LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' and AR.codigoMoneda=\\'@_codigoMonedaReporte\\'  order by CAST(AR.codigoArticulo AS SIGNED) ) Sub where Sub.Stock_Real>0;' WHERE `codigoReporte`='62';","215")){
                _iterador=false; return false;
            }
            break;
        case 215:
            if(impactoCambioEnBD("ALTER TABLE `Documentos` CHANGE COLUMN `fechaUltimaModificacionDocumento` `fechaUltimaModificacionDocumento` TIMESTAMP NULL , CHANGE COLUMN `fechaEmisionDocumento` `fechaEmisionDocumento` DATE NULL , CHANGE COLUMN `cae_fechaVencimiento` `cae_fechaVencimiento` DATE NULL ;","215")){
                if(impactoCambioEnBD("ALTER TABLE `Documentos` CHANGE COLUMN `fechaUltimaModificacionDocumento` `fechaUltimaModificacionDocumento` TIMESTAMP NOT NULL DEFAULT '1970-01-01 00:00:01' ;","215")){
                    if(impactoCambioEnBD("ALTER TABLE `Documentos` CHANGE COLUMN `fechaEmisionDocumento` `fechaEmisionDocumento` DATE NOT NULL ;","215")){
                        if(impactoCambioEnBD("ALTER TABLE `Documentos` CHANGE COLUMN `cae_fechaVencimiento` `cae_fechaVencimiento` DATE NOT NULL ;","215")){
                            if(impactoCambioEnBD("ALTER TABLE `Documentos` CHANGE COLUMN `fechaEmisionDocumento` `fechaEmisionDocumento` DATE NOT NULL DEFAULT '1000-01-01' ;","215")){
                                if(!impactoCambioEnBD("ALTER TABLE `Documentos` CHANGE COLUMN `cae_fechaVencimiento` `cae_fechaVencimiento` DATE NOT NULL DEFAULT '1000-01-01' ;","216")){
                                    _iterador=false; return false;
                                }
                            }else{_iterador=false; return false;}
                        }else{_iterador=false; return false;}
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;

        case 216:
            if(!impactoCambioEnBD("ALTER TABLE `Reportes` ADD COLUMN `utilizaListaPrecio2` CHAR(1) NOT NULL DEFAULT '0' AFTER `utilizaTipoClasificacionCliente`;","217")){
                _iterador=false; return false;
            }
            break;

        case 217:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaCodigoCliente`, `utilizaListaPrecio`, `utilizaListaPrecio2`) VALUES ('65', '8', 'Stock con listas de precios', 'SET @v1 = (select CONF.valorConfiguracion from Configuracion CONF where CONF.codigoConfiguracion=\\'MODO_ARTICULO\\');   select  AR.descripcionArticulo\\'Nombre\\', AR.descripcionExtendida\\'Descripcion corta\\', AR.codigoArticulo, case when (select ARB.codigoArticuloBarras from ArticulosBarras ARB where ARB.codigoArticuloInterno=AR.codigoArticulo limit 1) is null then \\'\\'  else   (select ARB.codigoArticuloBarras from ArticulosBarras ARB where ARB.codigoArticuloInterno=AR.codigoArticulo limit 1)  end \\'N° de parte origen\\',   FORMAT(case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end,0) \\'Stock\\' , case when (select LPA.precioArticulo from ListaPrecioArticulos LPA where LPA.codigoArticulo=AR.codigoArticulo and LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' limit 1) is null   then 0.00  else (select LPA.precioArticulo from ListaPrecioArticulos LPA where LPA.codigoArticulo=AR.codigoArticulo and LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' limit 1) end \\'Precio neto\\', case when (select LPA.precioArticulo from ListaPrecioArticulos LPA where LPA.codigoArticulo=AR.codigoArticulo and LPA.codigoListaPrecio=\\'@_codigoLista2Precio\\' limit 1) is null  then 0.00  else  (select LPA.precioArticulo from ListaPrecioArticulos LPA where LPA.codigoArticulo=AR.codigoArticulo and LPA.codigoListaPrecio=\\'@_codigoLista2Precio\\' limit 1)  end \\'PVP\\'  , MON.simboloMoneda\\'Moneda\\'  from Articulos AR  join Monedas MON on MON.codigoMoneda=AR.codigoMoneda  where AR.activo=1 order by  IF(@v1=1,CONVERT(AR.codigoArticulo, SIGNED INTEGER),0) asc,IF(@v1=0,AR.codigoArticulo,0) asc;   ', '', '', '0', '1', '1');","217")){
                if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('65', '0', '0', '0', '', 'TEXTO'),('65', '6', '2', '0', '', 'MONTO'),('65', '1', '0', '0', '', 'TEXTO'),('65', '2', '2', '0', '', 'TEXTO'),('65', '3', '2', '0', '', 'TEXTO'),('65', '4', '2', '0', '', 'TEXTO'),('65', '5', '2', '0', '', 'MONTO');","218")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;


        case 218:
            if(impactoCambioEnBD("ALTER TABLE `PerfilesUsuarios` ADD COLUMN `permiteUsarMenuAvanzadoUsuarios` CHAR(1) NOT NULL DEFAULT '0' AFTER `permiteAutorizarAnulaciones`;","218")){
                if(impactoCambioEnBD("ALTER TABLE `PerfilesUsuarios` ADD COLUMN `permiteUsarMenuAvanzadoPermisos` CHAR(1) NOT NULL DEFAULT '0' AFTER `permiteAutorizarAnulaciones`;","218")){
                    if(impactoCambioEnBD("ALTER TABLE `PerfilesUsuarios` ADD COLUMN `permiteUsarMenuAvanzadoMonedas` CHAR(1) NOT NULL DEFAULT '0' AFTER `permiteAutorizarAnulaciones`;","218")){
                        if(impactoCambioEnBD("ALTER TABLE `PerfilesUsuarios` ADD COLUMN `permiteUsarMenuAvanzadoRubros` CHAR(1) NOT NULL DEFAULT '0' AFTER `permiteAutorizarAnulaciones`;","218")){
                            if(impactoCambioEnBD("ALTER TABLE `PerfilesUsuarios` ADD COLUMN `permiteUsarMenuAvanzadoCuentasBancarias` CHAR(1) NOT NULL DEFAULT '0' AFTER `permiteAutorizarAnulaciones`;","218")){
                                if(impactoCambioEnBD("ALTER TABLE `PerfilesUsuarios` ADD COLUMN `permiteUsarMenuAvanzadoPagoDeFinacieras` CHAR(1) NOT NULL DEFAULT '0' AFTER `permiteAutorizarAnulaciones`;","218")){
                                    if(impactoCambioEnBD("ALTER TABLE `PerfilesUsuarios` ADD COLUMN `permiteUsarMenuAvanzadoBancos` CHAR(1) NOT NULL DEFAULT '0' AFTER `permiteAutorizarAnulaciones`;","218")){
                                        if(impactoCambioEnBD("ALTER TABLE `PerfilesUsuarios` ADD COLUMN `permiteUsarMenuAvanzadoLocalidades` CHAR(1) NOT NULL DEFAULT '0' AFTER `permiteAutorizarAnulaciones`;","218")){
                                            if(impactoCambioEnBD("ALTER TABLE `PerfilesUsuarios` ADD COLUMN `permiteUsarMenuAvanzadoTiposDeDocumentos` CHAR(1) NOT NULL DEFAULT '0' AFTER `permiteAutorizarAnulaciones`;","218")){
                                                if(impactoCambioEnBD("ALTER TABLE `PerfilesUsuarios` ADD COLUMN `permiteUsarMenuAvanzadoIvas` CHAR(1) NOT NULL DEFAULT '0' AFTER `permiteAutorizarAnulaciones`;","218")){
                                                    if(impactoCambioEnBD("ALTER TABLE `PerfilesUsuarios` ADD COLUMN `permiteUsarMenuAvanzadoConfiguraciones` CHAR(1) NOT NULL DEFAULT '0' AFTER `permiteAutorizarAnulaciones`;","218")){
                                                        if(!impactoCambioEnBD("UPDATE `PerfilesUsuarios` SET `permiteUsarMenuAvanzadoConfiguraciones`='1', `permiteUsarMenuAvanzadoIvas`='1', `permiteUsarMenuAvanzadoTiposDeDocumentos`='1', `permiteUsarMenuAvanzadoLocalidades`='1', `permiteUsarMenuAvanzadoBancos`='1', `permiteUsarMenuAvanzadoPagoDeFinacieras`='1', `permiteUsarMenuAvanzadoCuentasBancarias`='1', `permiteUsarMenuAvanzadoRubros`='1', `permiteUsarMenuAvanzadoMonedas`='1', `permiteUsarMenuAvanzadoPermisos`='1', `permiteUsarMenuAvanzadoUsuarios`='1' WHERE `codigoPerfil`='1';","219")){
                                                            _iterador=false; return false;
                                                        }
                                                    }else{_iterador=false; return false;}
                                                }else{_iterador=false; return false;}
                                            }else{_iterador=false; return false;}
                                        }else{_iterador=false; return false;}
                                    }else{_iterador=false; return false;}
                                }else{_iterador=false; return false;}
                            }else{_iterador=false; return false;}
                        }else{_iterador=false; return false;}
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;


        case 219:
            if(!impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaDesdeCodigoArticulo`, `utilizaHastaCodigoArticulo`) VALUES ('66', '1', 'Artículos desde > hasta', 'SELECT AR.codigoArticulo\\'Código\\', AR.descripcionArticulo\\'Nombre\\',   AR.fechaAlta\\'Fecha alta\\', AR.usuarioAlta \\'Usuario alta\\', AR.fechaUltimaModificacion\\'Fecha última modificación\\'  , AR.usuarioUltimaModificacion \\'Usuario última modificación \\'   FROM Articulos AR    where AR.codigoArticulo between CONVERT(\\'@_ArticulodesdeCodigoArticulo\\', SIGNED INTEGER)  and CONVERT(\\'@_ArticulohastaCodigoArticulo\\', SIGNED INTEGER)   order by CONVERT(AR.codigoArticulo, SIGNED INTEGER);', '', '', '1', '1');","220")){
                _iterador=false; return false;
            }
            break;
        case 220:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaTipoDocumento`, `utilizaMonedas`) VALUES ('67', '4', 'Ventas entre fechas deta. x tipo documento y moneda', 'select  concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\')\\')\\'Documento (Fecha)\\',  sum(ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)) \\'Total\\',    MON.simboloMoneda\\'Moneda\\'   from  Documentos DOC     join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento     join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')   and TDOC.esDocumentoDeVenta=\\'1\\'     and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'      and DOC.codigoTipoDocumento=\\'@_codigoDocumento\\'  group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;', '', '', '1', '1', '1', '1');","220")){
                if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('67', '0', '0', '0', '', 'TEXTO'),('67', '1', '2', '1', '', 'MONTO'),('67', '2', '0', '0', '', 'TEXTO');","221")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 221:
            if(!impactoCambioEnBD("INSERT INTO `Configuracion` (`codigoConfiguracion`, `valorConfiguracion`, `descripcionConfiguracion`) VALUES ('MODO_CFE', '0', 'Parametro que indica si la factura electronica esta habilitada(1) o desactivada(0)');","222")){
                _iterador=false; return false;
            }
            break;
        case 222:
            if(!impactoCambioEnBD("ALTER TABLE `Documentos` ADD INDEX `index_TipoDocumentoTipoCliente` (`codigoTipoDocumento` ASC, `tipoCliente` ASC, `codigoCliente` ASC);","223")){
                _iterador=false; return false;
            }
            break;
        case 223:
            if(impactoCambioEnBD("ALTER TABLE `Documentos` ADD COLUMN `esDocumentoCFE` CHAR(1) NOT NULL DEFAULT '0' AFTER `cae_QrCode`;","223")){
                if(!impactoCambioEnBD("CREATE TABLE `CFE_ParametrosGenerales` (`nombreParametro` VARCHAR(30) NOT NULL,`valorParametro` VARCHAR(5000) NULL,`descripcionParametro` VARCHAR(100) NULL,PRIMARY KEY (`nombreParametro`),UNIQUE INDEX `nombreParametro_UNIQUE` (`nombreParametro` ASC));","224")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;

        case 224:
            if(!impactoCambioEnBD("INSERT INTO   `Configuracion` (`codigoConfiguracion`, `valorConfiguracion`, `descripcionConfiguracion`) VALUES ('MUESTRA_DESCRIPCION_ARTICULO_EXTENDIDA_FACTURACION', '1', 'Parametro que indica si se muestra el campo de descripción extendida del artículo en la descripción del campo en el mantenimiento facturacion');","225")){
                _iterador=false; return false;
            }
            break;
        case 225:
            if(!impactoCambioEnBD("INSERT INTO `CFE_ParametrosGenerales` (`nombreParametro`, `valorParametro`, `descripcionParametro`) VALUES ('username', '', 'Información del usuario de acceso al ws'),('password', '', 'Información de password del usuario de acceso al ws'),('token', '', 'Información de token de acceso al ws') ,('urlE-ticketContado', '/etickets/contado/','') ,('urlWS', 'http://demo.dynamia.uy/gaia/api','') ,('urlE-ticketCredito', '/etickets/credito/',''),('urlE-ticketNotaCredito', '/etickets/notacredito/',''),('urlE-ticketNotaDebito', '/etickets/notadebito/','') ,('urlE-facturaContado', '/efacturas/contado/',''),('urlE-facturaCredito', '/efacturas/credito/',''),('urlE-facturaNotaCredito', '/efacturas/notacredito/',''),('urlE-facturaNotaDebito', '/efacturas/notadebito/','');","226")){
                _iterador=false; return false;
            }
            break;

        case 226:
            if(impactoCambioEnBD("ALTER TABLE `Ivas` ADD COLUMN `indicadorFacturacionCFE` TINYINT UNSIGNED NULL AFTER `factorMultiplicador`;","226")){
                if(impactoCambioEnBD("UPDATE `Ivas` SET `indicadorFacturacionCFE`='3' WHERE `codigoIva`='1';","226")){
                    if(impactoCambioEnBD("UPDATE `Ivas` SET `indicadorFacturacionCFE`='2' WHERE `codigoIva`='2';","226")){
                        if(!impactoCambioEnBD("UPDATE `Ivas` SET `indicadorFacturacionCFE`='1' WHERE `codigoIva`='3';","227")){
                            _iterador=false; return false;
                        }
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;

        case 227:
            if(impactoCambioEnBD("CREATE TABLE `CFE_TipoDocumentoCliente` (`codigoTipoDocumentoCliente` INT UNSIGNED NOT NULL, `descripcionTipoDocumentoCliente` VARCHAR(45) NOT NULL DEFAULT '', `comentario` VARCHAR(45) NOT NULL DEFAULT '', PRIMARY KEY (`codigoTipoDocumentoCliente`));","227")){
                if(!impactoCambioEnBD("INSERT INTO `CFE_TipoDocumentoCliente` (`codigoTipoDocumentoCliente`, `descripcionTipoDocumentoCliente`, `comentario`) VALUES ('2', 'RUT', ''),('3', 'CI', ''),('4', 'OTRO', ''),('5', 'PASAPORTE', ''),('6', 'DNI', 'Sólo para paises AR, BR, CL, PY');","228")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 228:
            if(!impactoCambioEnBD("ALTER TABLE `Clientes` ADD COLUMN `codigoTipoDocumentoCliente` INT(10) UNSIGNED NOT NULL DEFAULT 2 AFTER `cantidadMinimaMercaderia`;","229")){
                _iterador=false; return false;
            }
            break;

        case 229:
            if(impactoCambioEnBD("CREATE TABLE `TipoProcedenciaCliente` (`codigoTipoProcedenciaCliente` INT UNSIGNED NOT NULL,`descripcionTipoProcedenciaCliente` VARCHAR(45) NULL, PRIMARY KEY (`codigoTipoProcedenciaCliente`));","229")){
                if(impactoCambioEnBD("INSERT INTO `TipoProcedenciaCliente` (`codigoTipoProcedenciaCliente`, `descripcionTipoProcedenciaCliente`) VALUES ('1', 'No se sabe');","229")){
                    if(impactoCambioEnBD("ALTER TABLE `Clientes` ADD COLUMN `codigoTipoProcedenciaCliente` INT(10) UNSIGNED NOT NULL DEFAULT 1 AFTER `codigoTipoDocumentoCliente`, ADD INDEX `fk_codigoTipoProcedenciaCliente_idx` (`codigoTipoProcedenciaCliente` ASC); ","229")){
                        if(!impactoCambioEnBD("ALTER TABLE `Clientes` ADD CONSTRAINT `fk_codigoTipoProcedenciaCliente`  FOREIGN KEY (`codigoTipoProcedenciaCliente`) REFERENCES `TipoProcedenciaCliente` (`codigoTipoProcedenciaCliente`) ON DELETE NO ACTION ON UPDATE NO ACTION;","230")){
                            _iterador=false; return false;
                        }
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;

        case 230:
            if(!impactoCambioEnBD("ALTER TABLE `Mantenimientos` ADD COLUMN `clientesUsaProcedencia` CHAR(1) NOT NULL DEFAULT '0' AFTER `articulosUsaCargaBatch`;","231")){
                _iterador=false; return false;
            }
            break;
        case 231:
            if(!impactoCambioEnBD("INSERT INTO `TipoProcedenciaCliente` (`codigoTipoProcedenciaCliente`, `descripcionTipoProcedenciaCliente`) VALUES ('2', 'Google'),('3', 'Pagina Web'),('4', 'Recomendación'),('5', 'Mercado Libre'),('6', 'Facebook'),('7', 'GGC'),('8', 'Radio'),('9', 'Televisión'),('10', 'Otros');","232")){
                _iterador=false; return false;
            }
            break;

        case 232:
            if(!impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaGraficas`) VALUES ('68', '2', 'Clientes según procedencia entre fechas', 'SELECT TPC.descripcionTipoProcedenciaCliente\\'Procedencia\\', count(CLI.codigoTipoProcedenciaCliente)\\'Cantidad\\'  FROM Clientes CLI  join TipoProcedenciaCliente TPC on TPC.codigoTipoProcedenciaCliente=CLI.codigoTipoProcedenciaCliente   where  CLI.tipoCliente=1 and CLI.fechaAlta between \\'@_desde\\' and \\'@_hasta\\'  group by CLI.codigoTipoProcedenciaCliente;', 'SELECT TPC.descripcionTipoProcedenciaCliente\\'Procedencia\\', count(CLI.codigoTipoProcedenciaCliente)\\'Cantidad\\'  FROM Clientes CLI  join TipoProcedenciaCliente TPC on TPC.codigoTipoProcedenciaCliente=CLI.codigoTipoProcedenciaCliente   where  CLI.tipoCliente=1 and CLI.fechaAlta between \\'@_desde\\' and \\'@_hasta\\'  group by CLI.codigoTipoProcedenciaCliente;', '', '1', '1', '1');","233")){
                _iterador=false; return false;
            }
            break;

        case 233:
            if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSqlGraficas`='SELECT TPC.descripcionTipoProcedenciaCliente\\'Procedencia\\', count(CLI.codigoTipoProcedenciaCliente)\\'Cantidad\\',\\'#\\',count(CLI.codigoTipoProcedenciaCliente)  FROM Clientes CLI  join TipoProcedenciaCliente TPC on TPC.codigoTipoProcedenciaCliente=CLI.codigoTipoProcedenciaCliente   where  CLI.tipoCliente=1 and CLI.fechaAlta between \\'@_desde\\' and \\'@_hasta\\'  group by CLI.codigoTipoProcedenciaCliente;' WHERE `codigoReporte`='68';","234")){
                _iterador=false; return false;
            }
            break;

        case 234:
            if(!impactoCambioEnBD("INSERT INTO `CFE_ParametrosGenerales` (`nombreParametro`, `valorParametro`, `descripcionParametro`) VALUES ('urlImixProduccion', 'http://200.58.157.47/ImixIntegracionRest/CrearOperacion', 'Url de acceso a produccion de Imix'),('urlImixTesting', 'http://200.58.157.47/ImixIntegracionRest/CrearOperacion', 'Url de acceso a testing de Imix'),('modoTrabajoCFE', '0', 'Produccion=1 o Testing=0');","235")){
                _iterador=false; return false;
            }
            break;
        case 235:
            if(!impactoCambioEnBD("INSERT INTO `MenuSistema` (`codigoMenu`, `nombreMenu`) VALUES ('14', 'Factura Electronica');","236")){
                _iterador=false; return false;
            }
            break;


        case 236:
            if(!impactoCambioEnBD("ALTER TABLE `PerfilesUsuarios` ADD COLUMN `permiteUsarMenuAvanzadoFacturaElectronica` CHAR(1) NOT NULL DEFAULT '0' AFTER `permiteUsarMenuAvanzadoUsuarios`;","237")){
                _iterador=false; return false;
            }
            break;
        case 237:
            if(!impactoCambioEnBD("UPDATE `PerfilesUsuarios` SET `permiteUsarMenuAvanzadoFacturaElectronica`='1' WHERE `codigoPerfil`='1';","238")){
                _iterador=false; return false;
            }
            break;

        case 238:
            if(impactoCambioEnBD("ALTER TABLE `TipoDocumento` ADD COLUMN `descripcionTipoDocumentoCFE` VARCHAR(45) NOT NULL DEFAULT 'Venta contado' AFTER `utilizaSeteoDePreciosEnListasDePrecioPorArticulo`;","238")){
                if(impactoCambioEnBD("UPDATE `TipoDocumento` SET `descripcionTipoDocumentoCFE`='Venta crédito' WHERE `codigoTipoDocumento`='2';","238")){
                    if(impactoCambioEnBD("UPDATE `TipoDocumento` SET `descripcionTipoDocumentoCFE`='Devolución venta' WHERE `codigoTipoDocumento`='3';","238")){
                        if(!impactoCambioEnBD("UPDATE `TipoDocumento` SET `descripcionTipoDocumentoCFE`='Nota crédito venta' WHERE `codigoTipoDocumento`='4';","239")){
                            _iterador=false; return false;
                        }
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 239:
            if(!impactoCambioEnBD("ALTER TABLE `Pais` ADD COLUMN `codigoIsoPais` VARCHAR(5) NOT NULL DEFAULT 'UY' AFTER `descripcionPais`;","240")){
                _iterador=false; return false;
            }
            break;
        case 240:
            if(!impactoCambioEnBD("INSERT INTO `CFE_ParametrosGenerales` (`nombreParametro`, `valorParametro`, `descripcionParametro`) VALUES ('modoFuncionCFE', '0', '0 = imix, 1 = dynamia');","241")){
                _iterador=false; return false;
            }
            break;
        case 241:
            if(!impactoCambioEnBD("ALTER TABLE `TipoDocumento` ADD COLUMN `emiteCFEImprime` CHAR(1) NOT NULL DEFAULT '0' AFTER `descripcionTipoDocumentoCFE`;","242")){
                _iterador=false; return false;
            }
            break;
        case 242:
            if(!impactoCambioEnBD("INSERT INTO `CFE_ParametrosGenerales` (`nombreParametro`, `valorParametro`, `descripcionParametro`) VALUES ('envioArticuloClienteGenerico', '1', '1- Se envia dato generico. 0- Se envia  dato especifico. Especifica si se envia el articulo y el cliente 1 siempre, o se envia el dato acorde a la facturación');","243")){
                _iterador=false; return false;
            }
            break;

        case 243:
            if(!impactoCambioEnBD("INSERT INTO `CFE_ParametrosGenerales` (`nombreParametro`, `valorParametro`, `descripcionParametro`) VALUES ('montoUI', '3.7275', 'Monto anual de las UI');","244")){
                _iterador=false; return false;
            }
            break;
        case 244:
            if(!impactoCambioEnBD("INSERT INTO `CFE_ParametrosGenerales` (`nombreParametro`, `descripcionParametro`) VALUES ('claveCifrada', 'Clavecifrada para Dynamia');","245")){
                _iterador=false; return false;
            }
            break;

        case 245:
            if(!impactoCambioEnBD("ALTER TABLE `Documentos` ADD COLUMN `cae_idDocGaia` VARCHAR(45) NOT NULL DEFAULT '' AFTER `esDocumentoCFE`;","246")){
                _iterador=false; return false;
            }
            break;

        case 246:
            if(!impactoCambioEnBD("INSERT INTO `ImpresionCampos` (`codigoCampoImpresion`, `descripcionCampoImpresion`, `tipoCampo`, `codigoEtiqueta`, `campoEnTabla`) VALUES ('40', 'NumeroCae', '3', 'txtCae_numeroCae', 'Doc.cae_numeroCae'),('41', 'SerieCae', '3', 'txtCae_serie', 'Doc.cae_serie'),('42', 'Cae_fechaVenc', '3', 'txtCae_fechaVencimiento', 'Doc.cae_fechaVencimiento'),('43', 'Cae_codigoSegu', '3', 'txtCae_codigoSeguridad', 'Doc.cae_codigoSeguridad'), ('44', 'Cae_Cae', '3', 'txtCae_Cae', 'Doc.cae_Cae'),('45', 'Cae_rangoDesde', '3', 'txtCae_rangoDesde', 'Doc.cae_rangoDesde'),('46', 'Cae_rangoHasta', '3', 'txtCae_rangoHasta', 'Doc.cae_rangoHasta'),('47', 'Cae_QrCode', '3', 'txtCae_QrCode', 'Doc.cae_QrCode'),('48', 'Cae_urlCode', '3', 'txtCae_urlCode', 'Doc.cae_urlCode');","247")){
                _iterador=false; return false;
            }
            break;

        case 247:
            if(!impactoCambioEnBD("INSERT INTO `CFE_ParametrosGenerales` (`nombreParametro`, `valorParametro`, `descripcionParametro`) VALUES ('urlDGI', 'http://www.dgi.com.uy', 'Link para mostrar en la impresión como url donde consultar el cliente');","248")){
                _iterador=false; return false;
            }
            break;

        case 248:
            if(!impactoCambioEnBD("ALTER TABLE `Documentos` ADD COLUMN `caeTipoDocumentoCFEDescripcion` VARCHAR(45) NOT NULL DEFAULT '' AFTER `cae_idDocGaia`;","249")){
                _iterador=false; return false;
            }
            break;

        case 249:
            if(!impactoCambioEnBD("INSERT INTO `ImpresionCampos` (`codigoCampoImpresion`, `descripcionCampoImpresion`, `tipoCampo`, `codigoEtiqueta`, `campoEnTabla`) VALUES ('49', 'CaeTipoDocCFEDescrip', '3', 'txtCaeTipoDocumentoCFEDescripcion', 'Doc.caeTipoDocumentoCFEDescripcion');","250")){
                _iterador=false; return false;
            }
            break;
        case 250:
            if(impactoCambioEnBD("INSERT INTO `MenuSistema` (`codigoMenu`, `nombreMenu`) VALUES ('15', 'Log del sistema');","250")){
                if(impactoCambioEnBD("ALTER TABLE `PerfilesUsuarios` ADD COLUMN `permiteUsarMenuAvanzadoLogDelSistema` CHAR(1) NOT NULL DEFAULT '0' AFTER `permiteUsarMenuAvanzadoFacturaElectronica`;","250")){
                    if(!impactoCambioEnBD("UPDATE `PerfilesUsuarios` SET `permiteUsarMenuAvanzadoLogDelSistema`='1' WHERE `codigoPerfil`='1';","251")){
                        _iterador=false; return false;
                    }
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 251:
            if(!impactoCambioEnBD("ALTER TABLE `TipoDocumento` ADD COLUMN `noPermiteFacturarConStockPrevistoCero` CHAR(1) NOT NULL DEFAULT '0' AFTER `emiteCFEImprime`;","252")){
                _iterador=false; return false;
            }
            break;
        case 252:
            if(!impactoCambioEnBD("ALTER TABLE `ModeloImpresionLineas` CHANGE COLUMN `textoImprimibleIzquierda` `textoImprimibleIzquierda` VARCHAR(250) NOT NULL , CHANGE COLUMN `textoImprimibleDerecha` `textoImprimibleDerecha` VARCHAR(250) NOT NULL ;","253")){
                _iterador=false; return false;
            }
            break;
        case 253:
            if(!impactoCambioEnBD("INSERT INTO `ImpresionCampos` (`codigoCampoImpresion`, `descripcionCampoImpresion`, `tipoCampo`, `codigoEtiqueta`, `campoEnTabla`) VALUES ('50', 'Text_cabezal_4', '1', 'txtTextoGenericoCabezal4', '\\'txtTextoGenericoCabezal4\\''),('51', 'Text_cuerpo_4', '2', 'txtTextoGenericoCuerpo4', '\\'txtTextoGenericoCuerpo4\\''),('52', 'Text_pie_4', '3', 'txtTextoGenericoPie4', '\\'txtTextoGenericoPie4\\'');","254")){
                _iterador=false; return false;
            }
            break;
        case 254:
            if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Cliente\\',  concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\')\\')\\'Documento\\',  DOC.fechaEmisionDocumento\\'Fecha Emision Doc.\\',  case when DOC.codigoVendedorComisiona is null or DOC.codigoVendedorComisiona=\\'0\\' then \\'Sin Vendedor\\' else concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)end \\'Vendedor\\',  MON.simboloMoneda\\'\\', case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2)   when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2)  else ROUND(0.00,2) end \\'Movimientos\\'  from Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  left join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona where DOC.tipoCliente=1   and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   and TDOC.afectaCuentaCorriente!=0  and DOC.codigoCliente=\\'@_codigoCliente\\'   and MON.codigoMoneda=\\'@_codigoMonedaReporte\\' order by DOC.fechaEmisionDocumento asc ;' WHERE `codigoReporte`='42';","255")){
                _iterador=false; return false;
            }
            break;

        case 255:
            if(impactoCambioEnBD("ALTER TABLE `Documentos` ADD INDEX `index_CodigoEstadoDocumento` (`codigoEstadoDocumento` ASC);","255")){
                if(!impactoCambioEnBD("ALTER TABLE `Documentos` ADD INDEX `index_CodigoClienteTipoCliente` (`codigoCliente` ASC, `tipoCliente` ASC);","256")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;

        case 256:
            if(!impactoCambioEnBD("replace INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaTipoDocumento`) VALUES ('69', '7', 'Documentos por tipo y entre fechas', 'SELECT concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\')\\')\\'Documento\\', case when CLI.nombreCliente is null then \\'\\' else CLI.nombreCliente end  \\'Cliente\\', concat(MON.simboloMoneda,\\'      \\',DOC.precioTotalVenta)\\'Total\\',   DOC.fechaEmisionDocumento\\'Fecha Doc.\\',  DOC.usuarioUltimaModificacion\\'Usuario ultima modificación\\'  , DOC.usuarioAlta\\'Usuario creador\\'    FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   left join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Usuarios USU on USU.idUsuario=DOC.usuarioUltimaModificacion where    DOC.codigoTipoDocumento=\\'@_codigoDocumento\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' ;', '', '', '1', '1', '1');","257")){
                _iterador=false; return false;
            }
            break;
        case 257:
            if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select  concat(SR.codigoSubRubro,\\' - \\',SR.descripcionSubRubro)\\'SubRubro\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\' , sum(case when MON.codigoMoneda=1 then  ROUND((DOCL.precioTotalVenta-DOCL.montoDescuento)*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',   sum(case when MON.codigoMoneda=2 then  ROUND((DOCL.precioTotalVenta-DOCL.montoDescuento)*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\'  from  DocumentosLineas DOCL  left join Documentos DOC  on DOC.codigoDocumento=DOCL.codigoDocumento and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo  join SubRubros SR on SR.codigoSubRubro=AR.codigoSubRubro join Rubros RU on RU.codigoRubro=SR.codigoRubro  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'  and RU.codigoRubro=\\'@_codigoRubro\\'  group by RU.codigoRubro,SR.codigoSubRubro  order by RU.descripcionRubro,SR.descripcionSubRubro; ' WHERE `codigoReporte`='32';","258")){
                _iterador=false; return false;
            }
            break;
        case 258:
            if(!impactoCambioEnBD("INSERT INTO `ImpresionCampos` (`codigoCampoImpresion`, `descripcionCampoImpresion`, `tipoCampo`, `codigoEtiqueta`, `campoEnTabla`) VALUES ('53', 'DescuentoLineaArticulo', '2', 'txtMontoDescuentoLineaArticulo', 'montoDescuento');","259")){
                _iterador=false; return false;
            }
            break;                        
        case 259:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT concat(TD.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\' )\\'Documento\\', DOC.fechaEmisionDocumento\\'Fecha Documento\\', concat(MON.simboloMoneda,\\' \\',DOC.precioTotalVenta)\\'Total Documento\\', concat(MON.simboloMoneda,\\' \\',ROUND(DOC.precioTotalVenta-(DOC.precioTotalVenta/(SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADO\\' limit 1)),2))\\'Deuda minima permitida\\',  MON.simboloMoneda\\'\\', DOC.precioTotalVenta-DOC.saldoClientePagoContado\\'Saldo por pagar\\'  FROM Documentos DOC  join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where TD.documentoAceptaIngresoDeMediosDePagoLuegoDeEmitido=\\'1\\' and  DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and ROUND(DOC.precioTotalVenta-(DOC.precioTotalVenta/(SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADO\\' limit 1)),2)<=DOC.precioTotalVenta-DOC.saldoClientePagoContado and MON.codigoMoneda=\\'@_codigoMonedaReporte\\' order by DOC.fechaEmisionDocumento;' WHERE `codigoReporte`='52';","259")){
                if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select  concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento (Fecha)\\',  sum(ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)) \\'Total\\',    MON.simboloMoneda\\'Moneda\\'   from  Documentos DOC     join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento     join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')   and TDOC.esDocumentoDeVenta=\\'1\\'     and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'      and DOC.codigoTipoDocumento=\\'@_codigoDocumento\\'  group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;' WHERE `codigoReporte`='67';","259")){
                    if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\' )\\'Documento (Fecha)\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',  sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\'     from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'    group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;' WHERE `codigoReporte`='38';","259")){
                        if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento (Fecha)\\',  sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',   sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\'    from  Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\'    and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'     and DOC.codigoTipoDocumento=\\'@_codigoDocumento\\' group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;' WHERE `codigoReporte`='63';","259")){
                            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento (Fecha)\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',   sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\'      from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'   group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;' WHERE `codigoReporte`='54';","259")){
                                if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT concat((case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end),\\' (\\',DOC.codigoCliente,\\')\\')\\'CLIENTE\\',   concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\',   DOC.fechaEmisionDocumento\\'FECHA DOCUMENTO\\',   case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total $\\', case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total U$S\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.codigoCliente=\\'@_codigoCliente\\' and  DOC.tipoCliente=1   and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'   order by DOC.fechaEmisionDocumento desc ;' WHERE `codigoReporte`='19';","260")){
                                    _iterador=false; return false;
                                }
                            }else{_iterador=false; return false;}
                        }else{_iterador=false; return false;}
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 260:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento (Fecha)\\',  case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total doc. en $\\',    case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total doc. en U$S\\', case when DLP.codigoMedioPago=1  then DLP.importePago else 0 end \\'Efec. $\\',  case when DLP.codigoMedioPago=2  then DLP.importePago else 0 end \\'Efec. U$S\\',  case when DLP.codigoMedioPago=3  then DLP.importePago else 0 end \\'Tarj. Cre. $\\', case when DLP.codigoMedioPago=4  then DLP.importePago else 0 end \\'Tarj. Cre. U$S\\', case when DLP.codigoMedioPago=5  then DLP.importePago else 0 end \\'Cheque $\\',  case when DLP.codigoMedioPago=6  then DLP.importePago else 0 end \\'Cheque U$S\\', case when DLP.codigoMedioPago=7  then DLP.importePago else 0 end \\'Dep. banco $\\', case when DLP.codigoMedioPago=8  then DLP.importePago else 0 end \\'Dep. banco U$S\\' from  Documentos DOC   left join DocumentosLineasPago DLP on DLP.codigoDocumento=DOC.codigoDocumento  and DLP.codigoTipoDocumento=DOC.codigoTipoDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\'    and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'    and DOC.codigoTipoDocumento=\\'@_codigoDocumento\\'  order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento,DLP.codigoMedioPago,DLP.monedaMedioPago;' WHERE `codigoReporte`='64';","260")){
                if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT concat(CLI.razonSocial,\\'(\\',CLI.codigoCliente,\\')\\')\\'Cliente\\',   concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\',   case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total $\\', case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total U$S\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'  and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'   and DOC.codigoVendedorComisiona=\\'@_codigoVendedor\\'  order by DOC.fechaEmisionDocumento asc ;' WHERE `codigoReporte`='14';","260")){
                    if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT concat(CLI.razonSocial,\\'(\\',CLI.codigoCliente,\\')\\')\\'Cliente\\',  concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\',  case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta,2)*TDOC.afectaTotales  else ROUND(0,2)*TDOC.afectaTotales end \\'Total $\\',  case when MON.codigoMoneda=2 then  ROUND(DOC.precioSubTotalVenta,2)*TDOC.afectaTotales  else ROUND(0,2)*TDOC.afectaTotales end \\'Total U$S\\'    FROM Documentos DOC   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')      and TDOC.esDocumentoDeVenta=\\'1\\'  and DOC.fechaEmisionDocumento    between \\'@_desde\\' and \\'@_hasta\\'    and DOC.codigoVendedorComisiona=\\'@_codigoVendedor\\'  order by DOC.fechaEmisionDocumento asc ;' WHERE `codigoReporte`='26';","260")){
                        if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Cliente\\', concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\', DOC.fechaEmisionDocumento\\'Fecha Doc.\\', MON.simboloMoneda\\'\\', case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(0.00,2) end \\'Debe\\', case when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \\'Haber\\' from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente where DOC.tipoCliente=1 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\\'@_codigoCliente\\' order by DOC.fechaEmisionDocumento asc ;' WHERE `codigoReporte`='5';","260")){
                            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT DOC.codigoCliente\\'CODIGO CLIENTE\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'DOCUMENTO\\', MON.simboloMoneda\\'\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.codigoCliente=\\'@_codigoCliente\\' and DOC.tipoCliente=\\'1\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1 and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'  and DOC.saldoClienteCuentaCorriente!=0  order by  DOC.fechaEmisionDocumento asc; ' WHERE `codigoReporte`='49';","260")){
                                if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT DOC.codigoCliente\\'CODIGO CLIENTE\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'DOCUMENTO\\',MON.simboloMoneda\\'\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'   FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  where DOC.tipoCliente=\\'1\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1  and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'   and DOC.codigoCliente like \\'@_principioCodigoDelCliente%\\' and DOC.saldoClienteCuentaCorriente!=0  order by DOC.codigoCliente asc , DOC.fechaEmisionDocumento asc; ' WHERE `codigoReporte`='51';","261")){
                                    _iterador=false; return false;
                                }
                            }else{_iterador=false; return false;}
                        }else{_iterador=false; return false;}
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 261:
            if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT DOC.codigoCliente\\'CODIGO CLIENTE\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'DOCUMENTO\\',MON.simboloMoneda\\'\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente where DOC.tipoCliente=\\'1\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1 and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'  and DOC.saldoClienteCuentaCorriente!=0 and CLI.codigoPais=\\'@_codigoLocalidadPais\\' and codigoDepartamento=\\'@_codigoLocalidadDepartamento\\' order by DOC.codigoCliente asc , DOC.fechaEmisionDocumento asc;' WHERE `codigoReporte`='47';","261")){
                if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Cliente\\',  concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\',  DOC.fechaEmisionDocumento\\'Fecha Emision Doc.\\',  case when DOC.codigoVendedorComisiona is null or DOC.codigoVendedorComisiona=\\'0\\' then \\'Sin Vendedor\\' else concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)end \\'Vendedor\\',  MON.simboloMoneda\\'\\', case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2)   when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2)  else ROUND(0.00,2) end \\'Movimientos\\'  from Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  left join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona where DOC.tipoCliente=1   and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   and TDOC.afectaCuentaCorriente!=0  and DOC.codigoCliente=\\'@_codigoCliente\\'   and MON.codigoMoneda=\\'@_codigoMonedaReporte\\' order by DOC.fechaEmisionDocumento asc ;' WHERE `codigoReporte`='42';","261")){
                    if(impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Cliente\\', concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\',  DOC.fechaHoraGuardadoDocumentoSQL\\'Fecha Creacion Doc.\\', case when DOC.codigoVendedorComisiona is null or DOC.codigoVendedorComisiona=\\'0\\' then \\'Sin Vendedor\\' else concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)end \\'Vendedor\\',  MON.simboloMoneda\\'\\',  case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \\'Movimientos\\' from Documentos DOC    join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente    left join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona where DOC.tipoCliente=1   and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and TDOC.afectaCuentaCorriente!=0   and DOC.codigoCliente=\\'@_codigoCliente\\'   and MON.codigoMoneda=\\'@_codigoMonedaReporte\\'  and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' order by DOC.fechaHoraGuardadoDocumentoSQL asc ; ' WHERE `codigoReporte`='44';","261")){
                        if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\', case when CLI.nombreCliente is null then \\'\\' else CLI.nombreCliente end  \\'Cliente\\', concat(MON.simboloMoneda,\\'      \\',DOC.precioTotalVenta)\\'Total\\', DOC.fechaEmisionDocumento\\'Fecha Doc.\\', concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)\\'Usuario que anulo\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento left join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento join Usuarios USU on USU.idUsuario=DOC.usuarioUltimaModificacion where DOC.codigoEstadoDocumento=\\'C\\' and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' ;' WHERE `codigoReporte`='16';","262")){
                            _iterador=false; return false;
                        }
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 262:
            if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='SELECT concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\', case when CLI.nombreCliente is null then \\'\\' else CLI.nombreCliente end  \\'Cliente\\', concat(MON.simboloMoneda,\\'      \\',DOC.precioTotalVenta)\\'Total\\',   DOC.fechaEmisionDocumento\\'Fecha Doc.\\',  DOC.usuarioUltimaModificacion\\'Usuario ultima modificación\\'  , DOC.usuarioAlta\\'Usuario creador\\'    FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   left join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Usuarios USU on USU.idUsuario=DOC.usuarioUltimaModificacion where    DOC.codigoTipoDocumento=\\'@_codigoDocumento\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' ;' WHERE `codigoReporte`='69';","263")){
                _iterador=false; return false;
            }
            break;
        case 263:
            if(!impactoCambioEnBD("ALTER TABLE `TipoDocumento` ADD COLUMN `TipoTrasladoRemito` CHAR(1) NOT NULL DEFAULT '0' AFTER `noPermiteFacturarConStockPrevistoCero`;","264")){
                _iterador=false; return false;
            }
            break;
        case 264:
            if(!impactoCambioEnBD("ALTER TABLE `Clientes` ADD COLUMN `fechaNacimiento` DATE NULL AFTER `codigoTipoProcedenciaCliente`, ADD COLUMN `fechaUltimoAvisoCumpleanios` DATE NOT NULL DEFAULT '1000-01-01' AFTER `fechaNacimiento`;","265")){
                _iterador=false; return false;
            }
            break;
        case 265:
            if(!impactoCambioEnBD("ALTER TABLE `Clientes` CHANGE COLUMN `fechaNacimiento` `fechaNacimiento` DATE NOT NULL DEFAULT '0000-00-00' ;","266")){
                _iterador=false; return false;
            }
            break;
        case 266:
            if(!impactoCambioEnBD("ALTER TABLE `PerfilesUsuarios` ADD COLUMN `permiteUsarPromociones` CHAR(1) NOT NULL DEFAULT '0' AFTER `permiteUsarMenuAvanzadoLogDelSistema`;","267")){
                _iterador=false; return false;
            }
            break;
        case 267:
            if(!impactoCambioEnBD("UPDATE `PerfilesUsuarios` SET `permiteUsarPromociones`='1' WHERE `codigoPerfil`='1';","268")){
                _iterador=false; return false;
            }
            break;
        case 268:
            if(impactoCambioEnBD("CREATE TABLE `TipoPromocion` ( `idTipoPromocion` INT UNSIGNED NOT NULL, `nombreTipoPromocion` VARCHAR(45) NULL, PRIMARY KEY (`idTipoPromocion`));","268")){
                if(!impactoCambioEnBD("INSERT INTO `TipoPromocion` (`idTipoPromocion`, `nombreTipoPromocion`) VALUES ('1', 'Mail de cumpleaños');","269")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 269:
            if(!impactoCambioEnBD("CREATE TABLE `Promociones` (`idPromociones` INT UNSIGNED NOT NULL, `idTipoPromocion` INT UNSIGNED NOT NULL, `habilitada` TINYINT UNSIGNED NOT NULL DEFAULT 0, `fecha` DATE NOT NULL DEFAULT '0000-00-00', `fechaDesde` DATE NOT NULL DEFAULT '0000-00-00', `fechaHasta` DATE NOT NULL DEFAULT '0000-00-00', `diasSemana` VARCHAR(14) NOT NULL DEFAULT '',`nombrePromocion` VARCHAR(45) NOT NULL DEFAULT '',`HTMLPromocion` VARCHAR(50000) NOT NULL DEFAULT '', `urlImagen` VARCHAR(1000) NOT NULL DEFAULT '', `urlImagen2` VARCHAR(1000) NOT NULL DEFAULT '',  `ejecutaSiempre` TINYINT UNSIGNED NOT NULL DEFAULT 0, PRIMARY KEY (`idPromociones`, `idTipoPromocion`));","270")){
                _iterador=false; return false;
            }
            break;
        case 270:
            if(impactoCambioEnBD("ALTER TABLE `Promociones` ADD INDEX `fk_idTipoPromociones_1_idx` (`idTipoPromocion` ASC);","270")){
                if(!impactoCambioEnBD("ALTER TABLE `Promociones` ADD CONSTRAINT `fk_idTipoPromociones_1`FOREIGN KEY (`idTipoPromocion`) REFERENCES `TipoPromocion` (`idTipoPromocion`) ON DELETE NO ACTION  ON UPDATE NO ACTION;","271")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;

        case 271:
            if(!impactoCambioEnBD("ALTER TABLE `Promociones` ADD COLUMN `codigoTipoCliente` INT(11) NOT NULL DEFAULT 0 AFTER `ejecutaSiempre`;","272")){
                _iterador=false; return false;
            }
            break;
        case 272:
            if(!impactoCambioEnBD("ALTER TABLE `DocumentosLineas` CHANGE COLUMN `codigoArticuloBarras` `codigoArticuloBarras` VARCHAR(1000) NOT NULL DEFAULT '' ;","273")){
                _iterador=false; return false;
            }
            break;

        case 273:
            if(!impactoCambioEnBD("INSERT INTO `Configuracion` (`codigoConfiguracion`, `valorConfiguracion`, `descripcionConfiguracion`) VALUES ('CODIGO_BARRAS_A_DEMANDA_EXTENDIDO', '0', 'Si esta activo, permite escribir hasta 1000 caracteres en el codigo de barras a demanda en las facturas, alterna el enter por el tabulador al confirmar');","274")){
                _iterador=false; return false;
            }
            break;

        case 274:
            if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Proveedor\\', concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\')\\')\\'Documento\\',  DOC.fechaHoraGuardadoDocumentoSQL\\'Fecha Creacion Doc.\\',  case when DOC.codigoVendedorComisiona is null or DOC.codigoVendedorComisiona=\\'0\\' then \\'Sin Vendedor\\' else concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)end \\'Vendedor\\',  MON.simboloMoneda\\'\\',  case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \\'Movimientos\\' from Documentos DOC    join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente     left join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona   where DOC.tipoCliente=2   and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and TDOC.afectaCuentaCorriente!=0   and DOC.codigoCliente=\\'@_codigoProveedor\\'   and MON.codigoMoneda=\\'@_codigoMonedaReporte\\'  and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' order by DOC.fechaHoraGuardadoDocumentoSQL asc ;' WHERE `codigoReporte`='45';","275")){
                _iterador=false; return false;
            }
            break;

        case 275:
            if(!impactoCambioEnBD("ALTER TABLE `TipoDocumento` ADD COLUMN `imprimeEnFormatoTicket` CHAR(1) NOT NULL DEFAULT '0' AFTER `TipoTrasladoRemito`;","276")){
                _iterador=false; return false;
            }
            break;
        case 276:
            if(!impactoCambioEnBD("REPLACE INTO `CFE_ParametrosGenerales` (`nombreParametro`, `valorParametro`, `descripcionParametro`) VALUES ('logoImpresoraTicket', '', 'Logo opcional para el cabezal de la imrpesora de ticket');","277")){
                _iterador=false; return false;
            }
            break;
        case 277:
            if(!impactoCambioEnBD("ALTER TABLE `CFE_ParametrosGenerales` ADD COLUMN `imagen` longblob NOT NULL AFTER `descripcionParametro`;","278")){
                _iterador=false; return false;
            }
            break;
        case 278:
            if(!impactoCambioEnBD("INSERT INTO `CFE_ParametrosGenerales` (`nombreParametro`, `valorParametro`, `descripcionParametro`) VALUES ('resolucionDGINro', 'Res. Nro 10194/2017', 'Codigo resolución DGI');","279")){
                _iterador=false; return false;
            }
            break;            
        case 279:
            if(!impactoCambioEnBD("INSERT INTO `Configuracion` (`codigoConfiguracion`, `valorConfiguracion`, `descripcionConfiguracion`) VALUES ('DISTANCIAENTREBOTONESMENU', '15', 'Carga la distancia en pixeles para los botones del menu de herramientas');","280")){
                _iterador=false; return false;
            }
            break;
        case 280:
            if(!impactoCambioEnBD("ALTER TABLE `TipoDocumento`  ADD COLUMN `imprimeObservacionesEnTicket` CHAR(1) NOT NULL DEFAULT '0' AFTER `imprimeEnFormatoTicket`;","281")){
                _iterador=false; return false;
            }
            break;                        
        case 281:
            if(impactoCambioEnBD("ALTER TABLE `DocumentosLineas`                    ADD COLUMN `serieDocumento` VARCHAR(45) NOT NULL DEFAULT 'A' AFTER `costoArticuloPonderado`;","281")){
                if(impactoCambioEnBD("ALTER TABLE `DocumentosCanceladosCuentaCorriente` ADD COLUMN `serieDocumento` VARCHAR(45) NOT NULL DEFAULT 'A' AFTER `montoDescontadoCuentaCorriente`;","281")){
                    if(impactoCambioEnBD("ALTER TABLE `DocumentosLineasPago`                ADD COLUMN `serieDocumento` VARCHAR(45) NOT NULL DEFAULT 'A' AFTER `codigoBancoCuentaBancaria`;","281")){
                        if(impactoCambioEnBD("ALTER TABLE `Documentos` DROP PRIMARY KEY, ADD PRIMARY KEY (`codigoDocumento`, `codigoTipoDocumento`, `serieDocumento`);","281")){
                            if(impactoCambioEnBD("ALTER TABLE `DocumentosLineas` DROP PRIMARY KEY, ADD PRIMARY KEY (`codigoDocumento`, `codigoTipoDocumento`, `numeroLinea`, `serieDocumento`);","281")){
                                if(!impactoCambioEnBD("ALTER TABLE `DocumentosLineasPago`DROP PRIMARY KEY,ADD PRIMARY KEY (`codigoDocumento`, `codigoTipoDocumento`, `numeroLinea`, `serieDocumento`);","282")){
                                    _iterador=false; return false;
                                }
                            }else{_iterador=false; return false;}
                        }else{_iterador=false; return false;}
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 282:
            if(impactoCambioEnBD("ALTER TABLE `DocumentosCanceladosCuentaCorriente` ADD COLUMN `serieDocumentoQueCancela` VARCHAR(45) NOT NULL DEFAULT 'A' AFTER `serieDocumento`;","282")){
                if(impactoCambioEnBD("ALTER TABLE `DocumentosCanceladosCuentaCorriente` DROP PRIMARY KEY, ADD PRIMARY KEY (`codigoDocumento`, `codigoTipoDocumento`, `codigoDocumentoQueCancela`, `codigoTipoDocumentoQueCancela`, `serieDocumento`, `serieDocumentoQueCancela`);","282")){
                    if(!impactoCambioEnBD("ALTER TABLE `DocumentosLineas` DROP INDEX `fk_DocumentoExiste` , ADD INDEX `fk_DocumentoExiste` (`codigoDocumento` ASC, `codigoTipoDocumento` ASC, `serieDocumento` ASC);","283")){
                        _iterador=false; return false;
                    }
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;





        case 283:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (1,1,'Lista de artículos inactivos','SELECT codigoArticulo\\'Código\\',descripcionArticulo\\'Nombre\\', fechaAlta\\'Fecha de alta\\',fechaUltimaModificacion\\'Fecha de última modificación\\'   FROM Articulos where activo=0;','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","284")){
                _iterador=false; return false; } break;
        case 284:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (2,1,'Artículos x proveedor','SELECT CLI.nombreCliente\\'Proveedor\\',concat(AR.codigoArticulo,\\' - \\',AR.descripcionArticulo)\\'Artículo\\', AR.fechaAlta\\'Fecha de alta\\',AR.fechaUltimaModificacion\\'Fecha de última modificación\\'   FROM Articulos AR join Clientes CLI on CLI.codigoCliente=AR.codigoProveedor and CLI.tipoCliente=AR.tipoCliente where AR.tipoCliente=2 and AR.codigoProveedor=\\'@_codigoProveedor\\';','','','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","285")){
                _iterador=false; return false; } break;
        case 285:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (3,2,'Listado de clientes','SET @v1 = (select CONF.valorConfiguracion from Configuracion CONF where CONF.codigoConfiguracion=\\'MODO_CLIENTE\\'); SELECT concat(CLI.codigoCliente,\\' - \\',CLI.razonSocial)\\'Razón social\\', LOC.descripcionLocalidad\\'Localidad\\', concat(CLI.direccion, case when trim(CLI.codigoPostal)=\\'\\' or CLI.codigoPostal is null then \\'\\' else \\' - C.P.: \\' end ,CLI.codigoPostal)\\'Dirección + C. Postal\\', CLI.telefono\\'Telefono\\' /*DATE_FORMAT(CLI.fechaAlta, \\'%Y-%m-%d\\')\\'Fecha de alta\\'*/ FROM Clientes CLI join Localidades LOC on LOC.codigoPais=CLI.codigoPais and LOC.codigoDepartamento=CLI.codigoDepartamento and LOC.codigoLocalidad=CLI.codigoLocalidad  where CLI.tipoCliente=1 order by  IF(@v1=1,CONVERT(CLI.codigoCliente, SIGNED INTEGER),0) asc,IF(@v1=0,CLI.codigoCliente,0) asc;','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","286")){
                _iterador=false; return false; } break;
        case 286:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (4,3,'Listado de proveedores','SELECT concat(codigoCliente,\\' - \\',nombreCliente)\\'Cliente\\',razonSocial\\'Razón social\\',direccion\\'Dirección\\',telefono\\'Telefono\\',fechaAlta\\'Fecha de alta\\'  FROM Clientes where tipoCliente=2;','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","287")){
                _iterador=false; return false; } break;
        case 287:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (5,5,'Movimientos x cliente','select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Cliente\\', concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\', DOC.fechaEmisionDocumento\\'Fecha Doc.\\', MON.simboloMoneda\\'\\', case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(0.00,2) end \\'Debe\\', case when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \\'Haber\\' from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente where DOC.tipoCliente=1 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\\'@_codigoCliente\\' order by DOC.fechaEmisionDocumento asc ;','','','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","288")){
                _iterador=false; return false; } break;
        case 288:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (6,5,'Movimientos x proveedor','select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Proveedor\\', concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\')\\')\\'Documento\\', DOC.fechaEmisionDocumento\\'Fecha Doc.\\', MON.simboloMoneda\\'\\', case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(0.00,2) end \\'Debe\\', case when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \\'Haber\\' from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente where DOC.tipoCliente=2 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\\'@_codigoProveedor\\' order by DOC.fechaEmisionDocumento asc ;','','','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","289")){
                _iterador=false; return false; } break;
        case 289:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (7,5,'Saldo de cliente en Pesos','select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Cliente\\', MON.simboloMoneda\\'\\', sum(case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(DOC.precioTotalVenta*-1,2) end)\\'Saldo en Pesos\\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.tipoCliente=1 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\\'@_codigoCliente\\' and DOC.codigoMonedaDocumento=1 ;','','','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","290")){
                _iterador=false; return false; } break;
        case 290:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (8,5,'Saldo de cliente en Dolares','select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Cliente\\', MON.simboloMoneda\\'\\', sum(case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(DOC.precioTotalVenta*-1,2) end)\\'Saldo en Dolares\\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.tipoCliente=1  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\\'@_codigoCliente\\' and DOC.codigoMonedaDocumento=2;','','','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","291")){
                _iterador=false; return false; } break;
        case 291:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (9,5,'Saldo de proveedores en Pesos','select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Proveedor\\', MON.simboloMoneda\\'\\', sum(case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(DOC.precioTotalVenta*-1,2) end)\\'Saldo en Pesos\\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.tipoCliente=2 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\\'@_codigoProveedor\\' and DOC.codigoMonedaDocumento=1;','','','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","292")){
                _iterador=false; return false; } break;
        case 292:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (10,5,'Saldo de proveedores en Dolares','select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Proveedor\\', MON.simboloMoneda\\'\\', sum(case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) else ROUND(DOC.precioTotalVenta*-1,2) end)\\'Saldo en Pesos\\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.tipoCliente=2 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente!=0 and DOC.codigoCliente=\\'@_codigoProveedor\\' and DOC.codigoMonedaDocumento=2;','','','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","293")){
                _iterador=false; return false; } break;
        case 293:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (11,6,'Artículos mas vendidos','select concat(DOCL.codigoArticulo,\\' - \\',AR.descripcionArticulo)\\'Artículo\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento DOCL.serieDocumento=DOC.serieDocumento  join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.afectaTotales!=0 and TDOC.esDocumentoDeVenta=\\'1\\' group by DOCL.codigoArticulo order by 2 desc limit @_cantidad ;','','','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","294")){
                _iterador=false; return false; } break;
        case 294:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (12,6,'Artículos mas vendidos entre fechas','select concat(DOCL.codigoArticulo,\\' - \\',AR.descripcionArticulo)\\'Artículo\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.afectaTotales!=0 and TDOC.esDocumentoDeVenta=\\'1\\' and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'  group by DOCL.codigoArticulo order by 2 desc limit @_cantidad ;','','','0','0','0','1','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","295")){
                _iterador=false; return false; } break;
        case 295:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (13,3,'Alta de proveedores entre fechas','SELECT  concat(CLI.codigoCliente,\\' - \\',CLI.nombreCliente)\\'Proveedor\\', CLI.razonSocial\\'Razón Social\\', CLI.fechaAlta\\'Alta en sistema\\', concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)\\'Usuario del alta\\' FROM Clientes CLI  join Usuarios USU on USU.idUsuario=CLI.usuarioAlta where CLI.tipoCliente=2 and CLI.fechaAlta between \\'@_desde\\' and \\'@_hasta\\' + INTERVAL 1 DAY order by CLI.fechaAlta asc;','','','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","296")){
                _iterador=false; return false; } break;
        case 296:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (14,4,'Ventas x vendedor entre fechas','SELECT    concat(CLI.razonSocial,\\'(\\',CLI.codigoCliente,\\')\\')\\'Cliente\\',   concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\',   case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total $\\', case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total U$S\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'  and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'   and DOC.codigoVendedorComisiona=\\'@_codigoVendedor\\'  order by DOC.fechaEmisionDocumento asc ;','SELECT  DOC.fechaEmisionDocumento,  sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND((DOC.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda ))*TDOC.afectaTotales,2) end) \\'Total $\\', \\'$\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND((DOC.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda ))*TDOC.afectaTotales,2) end) \\'Total $\\' FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\'  and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'  and DOC.codigoVendedorComisiona=\\'@_codigoVendedor\\'  group by DOC.fechaEmisionDocumento order by DOC.fechaEmisionDocumento asc ;','select concat(\\'Vendedor: \\',USU.nombreUsuario,\\' \\',USU.apellidoUsuario) from Usuarios USU where USU.idUsuario=\\'@_codigoVendedor\\';','0','0','0','0','0','1','1','1','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","297")){
                _iterador=false; return false; } break;
        case 297:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (15,2,'Alta de clientes entre fechas','SELECT  concat(CLI.codigoCliente,\\' - \\',CLI.nombreCliente)\\'Cliente\\', CLI.razonSocial\\'Razón Social\\', CLI.fechaAlta\\'Alta en sistema\\', concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)\\'Usuario del alta\\' FROM Clientes CLI  join Usuarios USU on USU.idUsuario=CLI.usuarioAlta where CLI.tipoCliente=1 and CLI.fechaAlta between \\'@_desde\\' and \\'@_hasta\\' + INTERVAL 1 DAY order by CLI.fechaAlta asc;','','','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","298")){
                _iterador=false; return false; } break;
        case 298:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (16,7,'Documentos anulados entre fechas','SELECT concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\', case when CLI.nombreCliente is null then \\'\\' else CLI.nombreCliente end  \\'Cliente\\', concat(MON.simboloMoneda,\\'      \\',DOC.precioTotalVenta)\\'Total\\', DOC.fechaEmisionDocumento\\'Fecha Doc.\\', concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)\\'Usuario que anulo\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento left join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento join Usuarios USU on USU.idUsuario=DOC.usuarioUltimaModificacion where DOC.codigoEstadoDocumento=\\'C\\' and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' ;','','','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","299")){
                _iterador=false; return false; } break;
        case 299:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (17,7,'Total de documentos entre fechas','SELECT TDOC.descripcionTipoDocumento\\'Documentos\\', count(DOC.codigoDocumento+DOC.codigoTipoDocumento)\\'Cantidad\\' FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' group by TDOC.descripcionTipoDocumento order by count(DOC.codigoDocumento+DOC.codigoTipoDocumento) desc;','SELECT  TDOC.descripcionTipoDocumento\\'Documentos\\',  count(DOC.codigoDocumento+DOC.codigoTipoDocumento)\\'Cantidad\\' , \\'\\' as \\'simbolo\\', sum(1)  FROM Documentos DOC   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'  group by TDOC.descripcionTipoDocumento order by count(DOC.codigoDocumento+DOC.codigoTipoDocumento) desc;','','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","300")){
                _iterador=false; return false; } break;
        case 300:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (18,8,'Stock total real','SET @v1 = (select CONF.valorConfiguracion from Configuracion CONF where CONF.codigoConfiguracion=\\'MODO_ARTICULO\\'); SELECT AR.codigoArticulo\\'Código\\', AR.descripcionArticulo\\'Nombre\\', AR.descripcionExtendida\\'Descripción extendida\\', FORMAT(case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end,0) \\'Cantidad Real\\'  , case when AR.activo=1 then \\'activo\\' else \\'¡ARTÍCULO INACTIVO!\\' end\\'Estado\\'  FROM Articulos AR  order by  IF(@v1=1,CONVERT(AR.codigoArticulo, SIGNED INTEGER),0) asc,IF(@v1=0,AR.codigoArticulo,0) asc;','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","301")){
                _iterador=false; return false; } break;
        case 301:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (19,4,'Ventas por cliente entre fechas','SELECT   concat((case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end),\\' (\\',DOC.codigoCliente,\\')\\')\\'CLIENTE\\',   concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\',   DOC.fechaEmisionDocumento\\'FECHA DOCUMENTO\\',   case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total $\\', case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total U$S\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.codigoCliente=\\'@_codigoCliente\\' and  DOC.tipoCliente=1   and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'   order by DOC.fechaEmisionDocumento desc ;','SELECT  concat(\\'Fecha: \\',DOC.fechaEmisionDocumento),  sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND((DOC.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda ))*TDOC.afectaTotales,2) end) \\'Total $\\', \\'$\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND((DOC.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda ))*TDOC.afectaTotales,2) end) \\'Total $\\' FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.codigoCliente=\\'@_codigoCliente\\' and  DOC.tipoCliente=1   and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'  group by DOC.fechaEmisionDocumento order by DOC.fechaEmisionDocumento desc ; ','','1','0','0','0','0','1','1','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","302")){
                _iterador=false; return false; } break;
        case 302:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (20,6,'Artículos menos vendidos','select concat(DOCL.codigoArticulo,\\' - \\',AR.descripcionArticulo)\\'Artículo\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\'  from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.afectaTotales!=0 and TDOC.esDocumentoDeVenta=\\'1\\' group by DOCL.codigoArticulo order by 2 asc limit @_cantidad ;','','','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","303")){
                _iterador=false; return false; } break;
        case 303:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (21,4,'Venta de artículo entre fechas','select DOC.fechaEmisionDocumento\\'Fecha\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\'    from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento  join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo    where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'  and DOCL.codigoArticulo=\\'@_codigoArticulo\\' group by DOC.fechaEmisionDocumento,DOCL.codigoArticulo order by 1 asc;','select  concat(\\'Fecha: \\',DOC.fechaEmisionDocumento),  sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\',   \\'Cantidad vendida:\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'suma\\'    from Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento  join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo     where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'   and DOCL.codigoArticulo=\\'@_codigoArticulo\\'  group by DOC.fechaEmisionDocumento,DOCL.codigoArticulo order by 1 desc ; ','Select concat(\\'ARTICULO: \\',descripcionArticulo,\\'(\\',codigoArticulo,\\')\\') from Articulos where codigoArticulo=\\'@_codigoArticulo\\';','0','0','1','0','0','1','1','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","304")){
                _iterador=false; return false; } break;
        case 304:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (22,8,'Control stock bajo mínimo','select concat(AR.codigoArticulo,\\' - \\',AR.descripcionArticulo)\\'ARTÍCULO\\', AR.cantidadMinimaStock \\'MÍNIMO STOCK\\', case when (SELECT  sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)  from    Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento and DOC.serieDocumento=DOCL.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS   where DOCS.codigoTipoDocumento=8   and DOCS.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOCS.codigoDocumento desc limit 1)) is null then 0 else  (SELECT   sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)   from    Documentos DOC     join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento      and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento and DOC.serieDocumento=DOCL.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo   and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS   where DOCS.codigoTipoDocumento=8   and DOCS.codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by DOCS.codigoDocumento desc limit 1))  end \\'STOCK REAL\\', case when  (SELECT  sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) from    Documentos DOC    join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento     and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento and DOC.serieDocumento=DOCL.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\',\\'P\\') and DOCL.codigoArticulo=AR.codigoArticulo   and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS   where DOCS.codigoTipoDocumento=8   and DOCS.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOCS.codigoDocumento desc limit 1)) is null then 0 else (SELECT   sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) from    Documentos DOC    join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento     and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento and DOC.serieDocumento=DOCL.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\',\\'P\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS   where DOCS.codigoTipoDocumento=8   and DOCS.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOCS.codigoDocumento desc limit 1)) end  \\'STOCK PREVISTO\\'  from  FaltaStock FS join Articulos AR on AR.codigoArticulo=FS.codigoArticulo where cantidadArticulosSinStock!=0 ;','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","305")){
                _iterador=false; return false; } break;
        case 305:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (23,8,'Stock por sub rubro','SELECT AR.codigoArticulo\\'Código\\',AR.descripcionArticulo\\'Nombre\\',AR.descripcionExtendida\\'Descripción extendida\\' ,case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and DOCL.codigoArticulo=AR.codigoArticulo     and DOC.fechaHoraGuardadoDocumentoSQL>=    (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos  where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by codigoDocumento desc limit 1)  group by DOCL.codigoArticulo) end \\'Stock Real\\'  FROM Articulos AR  where AR.codigoSubRubro=\\'@_codigoSubRubro\\' order by CAST(AR.codigoArticulo AS SIGNED)  ;','','','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","306")){
                _iterador=false; return false; } break;
        case 306:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (24,9,'Total por Medios de Pago','select  concat(MP.descripcionMedioPago,\\' \\',MON.simboloMoneda) \\'Total Medios de pago Efectivo: \\', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\\'Valor Total:\\' from MediosDePago MP join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and D.codigoTipoDocumento=DLP.codigoTipoDocumento and D.serieDocumento=DLP.serieDocumento join TipoDocumento T on   T.codigoTipoDocumento=D.codigoTipoDocumento join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago where  MP.codigoTipoMedioDePago=1 and  T.afectaTotales!=0  \\r\\nand D.codigoEstadoDocumento not in (\\'C\\',\\'A\\',\\'P\\') and D.codigoLiquidacion=\\'@_codigoLiquidacionCaja\\' and D.codigoVendedorLiquidacion=\\'@_codigoVendedor\\' group by MP.monedaMedioPago; select   concat(MP.descripcionMedioPago,\\' \\',MON.simboloMoneda) \\'Total Medios de pago Tarjetas: \\', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\\'Valor Total:\\' from MediosDePago MP\\r\\njoin DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and   D.codigoTipoDocumento=DLP.codigoTipoDocumento and D.serieDocumento=DLP.serieDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago\\r\\nwhere  MP.codigoTipoMedioDePago=2 and  T.afectaTotales!=0  and D.codigoEstadoDocumento not in (\\'C\\',\\'A\\',\\'P\\') and D.codigoLiquidacion=\\'@_codigoLiquidacionCaja\\' and  D.codigoVendedorLiquidacion=\\'@_codigoVendedor\\' group by MP.monedaMedioPago; select  concat(MP.descripcionMedioPago,\\' \\',MON.simboloMoneda) \\'Total Medios de pago Cheques : \\', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\\'Valor Total:\\' from MediosDePago MP  join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento and D.serieDocumento=DLP.serieDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago where  MP.codigoTipoMedioDePago=3 and T.afectaTotales!=0  and D.codigoEstadoDocumento not in (\\'C\\',\\'A\\',\\'P\\') and D.codigoLiquidacion=\\'@_codigoLiquidacionCaja\\' and  D.codigoVendedorLiquidacion=\\'@_codigoVendedor\\' group by MP.monedaMedioPago; select  concat(MP.descripcionMedioPago,\\' \\',MON.simboloMoneda) \\'Total Medios de pago Deposito Bancario : \\',  case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\\'Valor Total:\\'  from MediosDePago MP   join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago  join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento and D.serieDocumento=DLP.serieDocumento  join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago  where  MP.codigoTipoMedioDePago=4 and T.afectaTotales!=0  and D.codigoEstadoDocumento not in (\\'C\\',\\'A\\',\\'P\\')  and D.codigoLiquidacion=\\'@_codigoLiquidacionCaja\\'  and  D.codigoVendedorLiquidacion=\\'@_codigoVendedor\\' group by MP.monedaMedioPago;','','','0','0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","307")){
                _iterador=false; return false; } break;
        case 307:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (25,9,'Total por Documentos y Medios de Pago','select concat(\\'Total en \\',M.descripcionMoneda,\\' \\',M.simboloMoneda) as \\'Total en documentos:\\', sum(D.precioTotalVenta*T.afectaTotales ) as \\'Valor Total:\\' FROM Documentos D  join Monedas M on M.codigoMoneda=D.codigoMonedaDocumento  join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  where D.codigoLiquidacion=\\'@_codigoLiquidacionCaja\\' and D.codigoVendedorLiquidacion=\\'@_codigoVendedor\\' and T.afectaTotales!=0 and D.codigoEstadoDocumento not in (\\'C\\',\\'A\\',\\'P\\')  group by M.codigoMoneda;select  concat(MP.descripcionMedioPago,\\' \\',MON.simboloMoneda) \\'Total Medios de pago Efectivo: \\', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\\'Valor Total:\\' from MediosDePago MP join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and D.codigoTipoDocumento=DLP.codigoTipoDocumento and D.serieDocumento=DLP.serieDocumento  join TipoDocumento T on   T.codigoTipoDocumento=D.codigoTipoDocumento join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago where  MP.codigoTipoMedioDePago=1 and  T.afectaTotales!=0  \\r\\nand D.codigoEstadoDocumento not in (\\'C\\',\\'A\\',\\'P\\') and D.codigoLiquidacion=\\'@_codigoLiquidacionCaja\\' and D.codigoVendedorLiquidacion=\\'@_codigoVendedor\\' group by MP.monedaMedioPago; select   concat(MP.descripcionMedioPago,\\' \\',MON.simboloMoneda) \\'Total Medios de pago Tarjetas: \\', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\\'Valor Total:\\' from MediosDePago MP\\r\\njoin DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and   D.codigoTipoDocumento=DLP.codigoTipoDocumento and D.serieDocumento=DLP.serieDocumento  join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago\\r\\nwhere  MP.codigoTipoMedioDePago=2 and  T.afectaTotales!=0  and D.codigoEstadoDocumento not in (\\'C\\',\\'A\\',\\'P\\') and D.codigoLiquidacion=\\'@_codigoLiquidacionCaja\\' and  D.codigoVendedorLiquidacion=\\'@_codigoVendedor\\' group by MP.monedaMedioPago; select  concat(MP.descripcionMedioPago,\\' \\',MON.simboloMoneda) \\'Total Medios de pago Cheques : \\', case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\\'Valor Total:\\' from MediosDePago MP  join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento  and D.serieDocumento=DLP.serieDocumento join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago where  MP.codigoTipoMedioDePago=3 and T.afectaTotales!=0  and D.codigoEstadoDocumento not in (\\'C\\',\\'A\\',\\'P\\') and D.codigoLiquidacion=\\'@_codigoLiquidacionCaja\\' and  D.codigoVendedorLiquidacion=\\'@_codigoVendedor\\' group by MP.monedaMedioPago; select  concat(MP.descripcionMedioPago,\\' \\',MON.simboloMoneda) \\'Total Medios de pago Deposito Bancario: \\',  case when ROUND(sum(DLP.importePago*T.afectaTotales),2) is null then 0.00 else  ROUND(sum(DLP.importePago*T.afectaTotales),2) end\\'Valor Total:\\'  from MediosDePago MP   join DocumentosLineasPago DLP on DLP.codigoMedioPago=MP.codigoMedioPago  join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento  and D.serieDocumento=DLP.serieDocumento  join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=MP.monedaMedioPago  where   MP.codigoTipoMedioDePago=4 and T.afectaTotales!=0            and D.codigoEstadoDocumento not in (\\'C\\',\\'A\\',\\'P\\') and D.codigoLiquidacion=\\'@_codigoLiquidacionCaja\\' and  D.codigoVendedorLiquidacion=\\'@_codigoVendedor\\'  group by MP.monedaMedioPago;','','','0','0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","308")){
                _iterador=false; return false; } break;
        case 308:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (26,4,'Ventas x vendedor entre fechas sin imp.','SELECT  concat(CLI.razonSocial,\\'(\\',CLI.codigoCliente,\\')\\')\\'Cliente\\',  concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.codigoDocumento,\\'-\\',DOC.serieDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\',  case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta,2)*TDOC.afectaTotales  else ROUND(0,2)*TDOC.afectaTotales end \\'Total $\\',  case when MON.codigoMoneda=2 then  ROUND(DOC.precioSubTotalVenta,2)*TDOC.afectaTotales  else ROUND(0,2)*TDOC.afectaTotales end \\'Total U$S\\'    FROM Documentos DOC   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')      and TDOC.esDocumentoDeVenta=\\'1\\'  and DOC.fechaEmisionDocumento    between \\'@_desde\\' and \\'@_hasta\\'    and DOC.codigoVendedorComisiona=\\'@_codigoVendedor\\'  order by DOC.fechaEmisionDocumento asc ;','','select concat(\\'Vendedor: \\',USU.nombreUsuario,\\' \\',USU.apellidoUsuario) from Usuarios USU where USU.idUsuario=\\'@_codigoVendedor\\';','0','0','0','0','0','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","309")){
                _iterador=false; return false; } break;
        case 309:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (27,1,'Lista total de artículos activos','SELECT codigoArticulo\\'Código\\',descripcionArticulo\\'Nombre\\', fechaAlta\\'Fecha de alta\\',fechaUltimaModificacion\\'Fecha de última modificación\\'  FROM Articulos where activo=1; ','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","310")){
                _iterador=false; return false; } break;
        case 310:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (28,1,'Lista total de artículos','SELECT codigoArticulo\\'Código\\',descripcionArticulo\\'Nombre\\', fechaAlta\\'Fecha de alta\\',fechaUltimaModificacion\\'Fecha de última modificación\\'  FROM Articulos;','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","311")){
                _iterador=false; return false; } break;
        case 311:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (29,8,'Stock por rubro','SELECT AR.codigoArticulo\\'Código\\',AR.descripcionArticulo\\'Nombre\\',AR.descripcionExtendida\\'Descripción extendida\\' , case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and DOCL.codigoArticulo=AR.codigoArticulo     and DOC.fechaHoraGuardadoDocumentoSQL>=    (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos  where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by codigoDocumento desc limit 1)  group by DOCL.codigoArticulo) end \\'Stock Real\\'   FROM Articulos AR join SubRubros SUBRUB on SUBRUB.codigoSubRubro=AR.codigoSubRubro where SUBRUB.codigoRubro=\\'@_codigoRubro\\' order by CAST(AR.codigoArticulo AS SIGNED);','','','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","312")){
                _iterador=false; return false; } break;
        case 312:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (30,10,'Precio de artículos por lista de precio','select AR.codigoArticulo\\'CODIGO\\',  AR.descripcionArticulo\\'DETALLE\\',  case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\' then concat(MON.simboloMoneda,\\' \\',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2)) else  ROUND(LPA.precioArticulo,2)  end   \\'Precio sin I.V.A\\', case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\' then  concat(MON.simboloMoneda,\\' \\',LPA.precioArticulo)  else  ROUND(LPA.precioArticulo*IV.factorMultiplicador,2) end \\'Precio I.V.A Inc.\\' FROM Articulos AR JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda JOIN Ivas IV on IV.codigoIva=AR.codigoIva where AR.activo=1 and  LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\'  order by  (case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_ARTICULO\\' limit 1)=\\'1\\' then CONVERT(AR.codigoArticulo, UNSIGNED INTEGER) else 2 end);','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","313")){
                _iterador=false; return false; } break;
        case 313:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (31,10,'Precio de artículos por lista de precio y stock mayor a','select AR.codigoArticulo\\'CODIGO\\', AR.descripcionArticulo\\'DETALLE\\', case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'  then concat(MON.simboloMoneda,\\' \\',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2)) else  ROUND(LPA.precioArticulo,2)  end   \\'Precio sin I.V.A\\',  case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'  then  concat(MON.simboloMoneda,\\' \\',LPA.precioArticulo)  else  ROUND(LPA.precioArticulo*IV.factorMultiplicador,2)  end \\'Precio I.V.A Inc.\\'   FROM Articulos AR JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda JOIN Ivas IV on IV.codigoIva=AR.codigoIva    where AR.activo=1 and (case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and DOCL.codigoArticulo=AR.codigoArticulo     and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos  where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by codigoDocumento desc limit 1)  group by DOCL.codigoArticulo) end) > \\'@_cantidad\\' and  LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' order by  (case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_ARTICULO\\' limit 1)=\\'1\\' then CONVERT(AR.codigoArticulo, UNSIGNED INTEGER) else 2 end);','','','0','0','0','1','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","314")){
                _iterador=false; return false; } break;
        case 314:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (32,4,'Ventas por rubro entre fechas','select  concat(SR.codigoSubRubro,\\' - \\',SR.descripcionSubRubro)\\'SubRubro\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\' , sum(case when MON.codigoMoneda=1 then  ROUND((DOCL.precioTotalVenta-DOCL.montoDescuento)*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',   sum(case when MON.codigoMoneda=2 then  ROUND((DOCL.precioTotalVenta-DOCL.montoDescuento)*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\'  from  DocumentosLineas DOCL  left join Documentos DOC  on DOC.codigoDocumento=DOCL.codigoDocumento and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo  join SubRubros SR on SR.codigoSubRubro=AR.codigoSubRubro join Rubros RU on RU.codigoRubro=SR.codigoRubro  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'  and RU.codigoRubro=\\'@_codigoRubro\\'  group by RU.codigoRubro,SR.codigoSubRubro  order by RU.descripcionRubro,SR.descripcionSubRubro; ','','','0','0','0','0','0','1','1','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","315")){
                _iterador=false; return false; } break;
        case 315:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (33,10,'Precio de artículos por lista de precio y rubros','select AR.codigoArticulo\\'CODIGO\\', AR.descripcionArticulo\\'DETALLE\\', case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'   then concat(MON.simboloMoneda,\\' \\',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2)) else  ROUND(LPA.precioArticulo,2)   end   \\'Precio sin I.V.A\\',  case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion= \\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'  then  concat(MON.simboloMoneda,\\' \\',LPA.precioArticulo)  else   ROUND(LPA.precioArticulo*IV.factorMultiplicador,2)  end \\'Precio I.V.A Inc.\\'      FROM Articulos AR  JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda  JOIN Ivas IV on IV.codigoIva=AR.codigoIva   JOIN SubRubros SUB on SUB.codigoSubRubro=AR.codigoSubRubro JOIN Rubros RUB on RUB.codigoRubro=SUB.codigoRubro   where AR.activo=1 and LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\'  and RUB.codigoRubro=\\'@_codigoRubro\\' order by  (case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_ARTICULO\\' limit 1)=\\'1\\' then CONVERT(AR.codigoArticulo, UNSIGNED INTEGER) else 2 end);','','','0','0','0','0','0','0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","316")){
                _iterador=false; return false; } break;
        case 316:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (34,10,'Precio de artículos por lista de precio y sub rubros','select AR.codigoArticulo\\'CODIGO\\', AR.descripcionArticulo\\'DETALLE\\', case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'   then concat(MON.simboloMoneda,\\' \\',ROUND(LPA.precioArticulo/IV.factorMultiplicador,2)) else  ROUND(LPA.precioArticulo,2)   end   \\'Precio sin I.V.A\\',  case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion= \\'MODO_CALCULOTOTAL\\' limit 1)=\\'1\\'  then  concat(MON.simboloMoneda,\\' \\',LPA.precioArticulo)  else   ROUND(LPA.precioArticulo*IV.factorMultiplicador,2)  end \\'Precio I.V.A Inc.\\'     FROM Articulos AR  JOIN ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  JOIN Monedas MON on MON.codigoMoneda=AR.codigoMoneda  JOIN Ivas IV on IV.codigoIva=AR.codigoIva   JOIN SubRubros SUB on SUB.codigoSubRubro=AR.codigoSubRubro JOIN Rubros RUB on RUB.codigoRubro=SUB.codigoRubro  where AR.activo=1 and LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\'  and SUB.codigoSubRubro=\\'@_codigoSubRubro\\' order by  (case when (SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MODO_ARTICULO\\' limit 1)=\\'1\\' then CONVERT(AR.codigoArticulo, UNSIGNED INTEGER) else 2 end);','','','0','0','0','0','0','0','0','0','0','1','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","317")){
                _iterador=false; return false; } break;
        case 317:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (35,12,'Totales por Cuenta Bancaria','select   CB.numeroCuentaBancaria\\'Cuenta\\',BAN.descripcionBanco\\'Banco\\', concat(MON.descripcionMoneda,\\' \\',MON.simboloMoneda)\\'Moneda\\',ROUND(sum(case when T.utilizaCuentaBancaria=1 then case when (DLP.importePago*T.afectaCuentaBancaria) is null then 0.00 else  (DLP.importePago*T.afectaCuentaBancaria) end else case when (DLP.importePago*T.afectaTotales) is null then 0.00 else (DLP.importePago*T.afectaTotales) end  end),2)\\'Valor Total:\\' from DocumentosLineasPago DLP  join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento  and D.serieDocumento=DLP.serieDocumento     join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento                        join Monedas MON on MON.codigoMoneda=DLP.monedaMedioPago                       join CuentaBancaria CB on CB.numeroCuentaBancaria=DLP.numeroCuentaBancaria and CB.codigoBanco=DLP.codigoBancoCuentaBancaria 					  join Bancos BAN on BAN.codigoBanco=CB.codigoBanco   where  D.codigoEstadoDocumento not in (\\'C\\',\\'A\\',\\'P\\') and CB.numeroCuentaBancaria=\\'@_numeroCuentaBancaria\\' and CB.codigoBanco=\\'@_numeroBancoCuentaBancaria\\'   group by CB.numeroCuentaBancaria , CB.codigoBanco, MON.codigoMoneda order by CB.numeroCuentaBancaria, MON.codigoMoneda;','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","318")){
                _iterador=false; return false; } break;
        case 318:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (36,12,'Totales por Cuenta Bancaria entre fechas','select      CB.numeroCuentaBancaria\\'Cuenta\\',BAN.descripcionBanco\\'Banco\\', concat(MON.descripcionMoneda,\\' \\',MON.simboloMoneda)\\'Moneda\\',ROUND(sum(case when T.utilizaCuentaBancaria=1    then     case when (DLP.importePago*T.afectaCuentaBancaria) is null then 0.00 else  (DLP.importePago*T.afectaCuentaBancaria) end    else   case when (DLP.importePago*T.afectaTotales) is null then 0.00 else (DLP.importePago*T.afectaTotales) end    end),2)\\'Valor Total:\\'  from DocumentosLineasPago DLP     join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento  and D.serieDocumento=DLP.serieDocumento    join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DLP.monedaMedioPago  join CuentaBancaria CB on CB.numeroCuentaBancaria=DLP.numeroCuentaBancaria and CB.codigoBanco=DLP.codigoBancoCuentaBancaria  	  join Bancos BAN on BAN.codigoBanco=CB.codigoBanco where  D.codigoEstadoDocumento not in (\\'C\\',\\'A\\',\\'P\\')  and CB.numeroCuentaBancaria=\\'@_numeroCuentaBancaria\\'   and CB.codigoBanco=\\'@_numeroBancoCuentaBancaria\\'  and D.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'  group by CB.numeroCuentaBancaria , CB.codigoBanco, MON.codigoMoneda  order by CB.numeroCuentaBancaria, MON.codigoMoneda;','','','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","319")){
                _iterador=false; return false; } break;
        case 319:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (37,12,'Total Cuenta Bancaria entre fechas por moneda','select   concat(DLP.codigoDocumento,\\' - \\',T.descripcionTipoDocumento,\\' (\\',D.fechaEmisionDocumento,\\')\\')\\'Documento (Fecha)\\',  concat(CB.numeroCuentaBancaria,\\' - \\',BAN.descripcionBanco)\\'Cuenta\\',   concat(MON.descripcionMoneda,\\' \\',MON.simboloMoneda)\\'Moneda\\',  ROUND(sum(case when T.utilizaCuentaBancaria=1    then     case when (DLP.importePago*T.afectaCuentaBancaria) is null then 0.00 else  (DLP.importePago*T.afectaCuentaBancaria) end    else   case when (DLP.importePago*T.afectaTotales) is null then 0.00 else (DLP.importePago*T.afectaTotales) end    end),2)\\'Valor Total:\\'  from DocumentosLineasPago DLP     join Documentos D on D.codigoDocumento=DLP.codigoDocumento and  D.codigoTipoDocumento=DLP.codigoTipoDocumento  and D.serieDocumento=DLP.serieDocumento     join TipoDocumento T on T.codigoTipoDocumento=D.codigoTipoDocumento    join Monedas MON on MON.codigoMoneda=DLP.monedaMedioPago   join CuentaBancaria CB on CB.numeroCuentaBancaria=DLP.numeroCuentaBancaria and CB.codigoBanco=DLP.codigoBancoCuentaBancaria  	   join Bancos BAN on BAN.codigoBanco=CB.codigoBanco   where  D.codigoEstadoDocumento not in (\\'C\\',\\'A\\',\\'P\\')  and CB.numeroCuentaBancaria=\\'@_numeroCuentaBancaria\\'   and CB.codigoBanco=\\'@_numeroBancoCuentaBancaria\\'   and D.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'    and MON.codigoMoneda=\\'@_codigoMonedaReporte\\'  group by DLP.codigoDocumento,CB.numeroCuentaBancaria , CB.codigoBanco, MON.codigoMoneda  order by D.fechaEmisionDocumento,DLP.codigoDocumento, T.codigoTipoDocumento, CB.numeroCuentaBancaria, MON.codigoMoneda;','','','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","320")){
                _iterador=false; return false; } break;
        case 320:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (38,4,'Ventas entre fechas detallado','select   concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\' )\\'Documento (Fecha)\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',  sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\'     from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'    group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;','select   concat(\\'Fecha: \\',( case when  MONTH(DOC.fechaEmisionDocumento)=1 then \\'Enero\\'  when  MONTH(DOC.fechaEmisionDocumento)=2 then \\'Febrero\\'  when  MONTH(DOC.fechaEmisionDocumento)=3 then \\'Marzo\\' when  MONTH(DOC.fechaEmisionDocumento)=4 then \\'Abril\\' when  MONTH(DOC.fechaEmisionDocumento)=5 then \\'Mayo\\' when  MONTH(DOC.fechaEmisionDocumento)=6 then \\'Junio\\' when  MONTH(DOC.fechaEmisionDocumento)=7 then \\'Julio\\'   when  MONTH(DOC.fechaEmisionDocumento)=8 then \\'Agosto\\' when  MONTH(DOC.fechaEmisionDocumento)=9 then \\'Setiembre\\'  when  MONTH(DOC.fechaEmisionDocumento)=10 then \\'Octubre\\' when  MONTH(DOC.fechaEmisionDocumento)=11 then \\'Noviembre\\' when  MONTH(DOC.fechaEmisionDocumento)=12 then \\'Diciembre\\'  else \\'Mes Incorrecto\\' end)  ,\\' de \\',YEAR(DOC.fechaEmisionDocumento))\\'fecha\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(DOC.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda )*TDOC.afectaTotales,2) end) \\'Total $\\', \\'$\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(DOC.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda )*TDOC.afectaTotales,2) end)   from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'     and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'      group by YEAR(DOC.fechaEmisionDocumento), MONTH(DOC.fechaEmisionDocumento) order by DOC.fechaEmisionDocumento desc; ','','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","321")){
                _iterador=false; return false; } break;
        case 321:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (39,4,'Ventas entre fechas resumidas','select concat(( case when  MONTH(DOC.fechaEmisionDocumento)=1 then \\'Enero\\'  when  MONTH(DOC.fechaEmisionDocumento)=2 then \\'Febrero\\'  when  MONTH(DOC.fechaEmisionDocumento)=3 then \\'Marzo\\' when  MONTH(DOC.fechaEmisionDocumento)=4 then \\'Abril\\' when  MONTH(DOC.fechaEmisionDocumento)=5 then \\'Mayo\\' when  MONTH(DOC.fechaEmisionDocumento)=6 then \\'Junio\\' when  MONTH(DOC.fechaEmisionDocumento)=7 then \\'Julio\\'   when  MONTH(DOC.fechaEmisionDocumento)=8 then \\'Agosto\\' when  MONTH(DOC.fechaEmisionDocumento)=9 then \\'Setiembre\\'  when  MONTH(DOC.fechaEmisionDocumento)=10 then \\'Octubre\\' when  MONTH(DOC.fechaEmisionDocumento)=11 then \\'Noviembre\\' when  MONTH(DOC.fechaEmisionDocumento)=12 then \\'Diciembre\\'  else \\'Mes Incorrecto\\' end)  ,\\' de \\',YEAR(DOC.fechaEmisionDocumento))\\'fecha\\',   sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',  sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\' from  Documentos DOC   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'     group by YEAR(DOC.fechaEmisionDocumento), MONTH(DOC.fechaEmisionDocumento) order by DOC.fechaEmisionDocumento; ','select   concat(\\'Fecha: \\',( case when  MONTH(DOC.fechaEmisionDocumento)=1 then \\'Enero\\'  when  MONTH(DOC.fechaEmisionDocumento)=2 then \\'Febrero\\'  when  MONTH(DOC.fechaEmisionDocumento)=3 then \\'Marzo\\' when  MONTH(DOC.fechaEmisionDocumento)=4 then \\'Abril\\' when  MONTH(DOC.fechaEmisionDocumento)=5 then \\'Mayo\\' when  MONTH(DOC.fechaEmisionDocumento)=6 then \\'Junio\\' when  MONTH(DOC.fechaEmisionDocumento)=7 then \\'Julio\\'   when  MONTH(DOC.fechaEmisionDocumento)=8 then \\'Agosto\\' when  MONTH(DOC.fechaEmisionDocumento)=9 then \\'Setiembre\\'  when  MONTH(DOC.fechaEmisionDocumento)=10 then \\'Octubre\\' when  MONTH(DOC.fechaEmisionDocumento)=11 then \\'Noviembre\\' when  MONTH(DOC.fechaEmisionDocumento)=12 then \\'Diciembre\\'  else \\'Mes Incorrecto\\' end)  ,\\' de \\',YEAR(DOC.fechaEmisionDocumento))\\'fecha\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(DOC.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda )*TDOC.afectaTotales,2) end) \\'Total $\\', \\'$\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(DOC.precioTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda )*TDOC.afectaTotales,2) end)   from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'     and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'      group by YEAR(DOC.fechaEmisionDocumento), MONTH(DOC.fechaEmisionDocumento) order by DOC.fechaEmisionDocumento desc; ','','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","322")){
                _iterador=false; return false; } break;
        case 322:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (40,2,'Lista de email\\'s de clientes','SELECT concat(trim(CLI.email),\\',\\')\\'Email de clientes\\' FROM Clientes CLI join ListaPrecioClientes LPC on LPC.codigoCliente=CLI.codigoCliente  where CLI.tipoCliente=\\'1\\' and trim(CLI.email) rlike \\'@\\' and LPC.codigoListaPrecio=\\'@_codigoListaPrecio\\'; ','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","323")){
                _iterador=false; return false; } break;
        case 323:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (41,3,'Lista de email\\'s de proveedores','SELECT concat(trim(CLI.email),\\',\\')\\'Email de proveedores\\' FROM Clientes CLI join ListaPrecioClientes LPC on LPC.codigoCliente=CLI.codigoCliente  where CLI.tipoCliente=\\'2\\' and trim(CLI.email) rlike \\'@\\' and LPC.codigoListaPrecio=\\'@_codigoListaPrecio\\'; ','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","324")){
                _iterador=false; return false; } break;
        case 324:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (42,5,'Saldo por cliente y moneda','select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Cliente\\',  concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\',  DOC.fechaEmisionDocumento\\'Fecha Emision Doc.\\',  case when DOC.codigoVendedorComisiona is null or DOC.codigoVendedorComisiona=\\'0\\' then \\'Sin Vendedor\\' else concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)end \\'Vendedor\\',  MON.simboloMoneda\\'\\', case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2)   when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2)  else ROUND(0.00,2) end \\'Movimientos\\'  from Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente  left join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona where DOC.tipoCliente=1   and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   and TDOC.afectaCuentaCorriente!=0  and DOC.codigoCliente=\\'@_codigoCliente\\'   and MON.codigoMoneda=\\'@_codigoMonedaReporte\\' order by DOC.fechaEmisionDocumento asc ;','','','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","325")){
                _iterador=false; return false; } break;
        case 325:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (43,5,'Saldo por proveedor y moneda','select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Proveedor\\', concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\')\\')\\'Documento\\', DOC.fechaHoraGuardadoDocumentoSQL\\'Fecha Creacion Doc.\\', case when DOC.codigoVendedorComisiona is null or DOC.codigoVendedorComisiona=\\'0\\' then \\'Sin Vendedor\\' else concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)end \\'Vendedor\\',   MON.simboloMoneda\\'\\',  case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \\'Movimientos\\'  from Documentos DOC   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente   left join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona  where DOC.tipoCliente=2  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and TDOC.afectaCuentaCorriente!=0   and DOC.codigoCliente=\\'@_codigoProveedor\\'   and MON.codigoMoneda=\\'@_codigoMonedaReporte\\'  order by DOC.fechaHoraGuardadoDocumentoSQL asc ;','','','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","326")){
                _iterador=false; return false; } break;
        case 326:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (44,5,'Saldo por cliente y moneda entre fechas','select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Cliente\\', concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\',  DOC.fechaHoraGuardadoDocumentoSQL\\'Fecha Creacion Doc.\\', case when DOC.codigoVendedorComisiona is null or DOC.codigoVendedorComisiona=\\'0\\' then \\'Sin Vendedor\\' else concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)end \\'Vendedor\\',  MON.simboloMoneda\\'\\',  case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \\'Movimientos\\' from Documentos DOC    join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente    left join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona where DOC.tipoCliente=1   and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and TDOC.afectaCuentaCorriente!=0   and DOC.codigoCliente=\\'@_codigoCliente\\'   and MON.codigoMoneda=\\'@_codigoMonedaReporte\\'  and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' order by DOC.fechaHoraGuardadoDocumentoSQL asc ; ','','','1','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","327")){
                _iterador=false; return false; } break;
        case 327:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (45,5,'Saldo por proveedor y moneda entre fechas','select concat(CLI.codigoCliente,\\' - \\',(case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end))\\'Proveedor\\', concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\')\\')\\'Documento\\',  DOC.fechaHoraGuardadoDocumentoSQL\\'Fecha Creacion Doc.\\',  case when DOC.codigoVendedorComisiona is null or DOC.codigoVendedorComisiona=\\'0\\' then \\'Sin Vendedor\\' else concat(USU.nombreUsuario,\\' \\',USU.apellidoUsuario)end \\'Vendedor\\',  MON.simboloMoneda\\'\\',  case when TDOC.afectaCuentaCorriente=1 then ROUND(DOC.precioTotalVenta,2) when TDOC.afectaCuentaCorriente=-1 then ROUND(DOC.precioTotalVenta*-1,2) else ROUND(0.00,2) end \\'Movimientos\\' from Documentos DOC    join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente   and CLI.tipoCliente=DOC.tipoCliente     left join Usuarios USU on USU.idUsuario=DOC.codigoVendedorComisiona   where DOC.tipoCliente=2   and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and TDOC.afectaCuentaCorriente!=0   and DOC.codigoCliente=\\'@_codigoProveedor\\'   and MON.codigoMoneda=\\'@_codigoMonedaReporte\\'  and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' order by DOC.fechaHoraGuardadoDocumentoSQL asc ;','','','0','1','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","328")){
                _iterador=false; return false; } break;
        case 328:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (46,8,'Costo según stock','SELECT AR.codigoArticulo\\'Código\\', AR.descripcionArticulo\\'Nombre\\', case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)\\'cantidad\\' FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and DOC.fechaEmisionDocumento  <=  \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0  else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and  DOC.fechaEmisionDocumento  <=  \\'@_hasta\\'  and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end  \\'Unidades stock(Real)\\' , case when  (SELECT DOCLL.costoArticuloMonedaReferencia FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloMonedaReferencia!=0  and DOCLL.fechaHoraGuardadoLineaSQL  <=  \\'@_hasta\\' + INTERVAL 1 DAY  order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) is null  then \\'Costo no definido\\' else  concat((select MON.simboloMoneda from Monedas MON where MON.esMonedaReferenciaSistema=1  order by MON.codigoMoneda asc limit 1),\\'  \\', (SELECT DOCLL.costoArticuloMonedaReferencia FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloMonedaReferencia!=0 and DOCLL.fechaHoraGuardadoLineaSQL  <=   \\'@_hasta\\' + INTERVAL 1 DAY order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) )end\\'Costo Unitario(Ultima compra)\\', case when  (SELECT DOCLL.costoArticuloPonderado FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloPonderado!=0  and DOCLL.fechaHoraGuardadoLineaSQL  <=   \\'@_hasta\\' + INTERVAL 1 DAY  order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) is null  then \\'Costo no definido\\' else  concat((select MON.simboloMoneda from Monedas MON where MON.esMonedaReferenciaSistema=1  order by MON.codigoMoneda asc limit 1),\\'  \\', (SELECT DOCLL.costoArticuloPonderado FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloPonderado!=0 and DOCLL.fechaHoraGuardadoLineaSQL  <=  \\'@_hasta\\' + INTERVAL 1 DAY order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) )end\\'Costo Unitario Ponderado\\', case when  (SELECT DOCLL.costoArticuloPonderado FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloPonderado!=0 and DOCLL.fechaHoraGuardadoLineaSQL  <=   \\'@_hasta\\' + INTERVAL 1 DAY order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) is null then 0 else  (case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)  FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento    join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where  TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOC.fechaEmisionDocumento  <=    \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOC.fechaEmisionDocumento  <=   \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end) *  (SELECT DOCLL.costoArticuloPonderado FROM DocumentosLineas DOCLL where DOCLL.codigoArticulo=AR.codigoArticulo and DOCLL.costoArticuloPonderado!=0 and DOCLL.fechaHoraGuardadoLineaSQL  <=   \\'@_hasta\\' + INTERVAL 1 DAY  order by DOCLL.fechaHoraGuardadoLineaSQL desc limit 1) end \\'Total costo ponderado según stock\\' FROM Articulos AR  where AR.codigoArticulo between CONVERT(\\'@_ArticulodesdeCodigoArticulo\\', SIGNED INTEGER)  and CONVERT(\\'@_ArticulohastaCodigoArticulo\\', SIGNED INTEGER)  and (case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)\\'cantidad\\'  FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 	and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOC.fechaEmisionDocumento  <=   \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0   else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOC.fechaEmisionDocumento  <=   \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8  and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end)>0 order by CONVERT(AR.codigoArticulo, SIGNED INTEGER);','','','0','0','0','0','0','0','1','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","329")){
                _iterador=false; return false; } break;
        case 329:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (47,5,'Saldo de clientes por Departamentos y moneda(nuevo)','SELECT DOC.codigoCliente\\'CODIGO CLIENTE\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'DOCUMENTO\\',MON.simboloMoneda\\'\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente where DOC.tipoCliente=\\'1\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1 and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'  and DOC.saldoClienteCuentaCorriente!=0 and CLI.codigoPais=\\'@_codigoLocalidadPais\\' and codigoDepartamento=\\'@_codigoLocalidadDepartamento\\' order by DOC.codigoCliente asc , DOC.fechaEmisionDocumento asc;','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','1','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","330")){
                _iterador=false; return false; } break;
        case 330:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (48,5,'Saldo de proveedores por Departamentos y moneda(nuevo)','SELECT DOC.codigoCliente\\'CODIGO PROVEEDOR\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\')\\')\\'DOCUMENTO\\',MON.simboloMoneda\\'\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente where DOC.tipoCliente=\\'2\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1 and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'  and DOC.saldoClienteCuentaCorriente!=0 and CLI.codigoPais=\\'@_codigoLocalidadPais\\' and codigoDepartamento=\\'@_codigoLocalidadDepartamento\\' order by DOC.codigoCliente asc , DOC.fechaEmisionDocumento asc;','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','1','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","331")){
                _iterador=false; return false; } break;
        case 331:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (49,5,'Saldo de cliente por moneda(nuevo)','SELECT DOC.codigoCliente\\'CODIGO CLIENTE\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'DOCUMENTO\\', MON.simboloMoneda\\'\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.codigoCliente=\\'@_codigoCliente\\' and DOC.tipoCliente=\\'1\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1 and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'  and DOC.saldoClienteCuentaCorriente!=0  order by  DOC.fechaEmisionDocumento asc; ','','select concat(CLI.nombreCliente,\\'(\\',CLI.codigoCliente,\\')\\'),concat(\\'Dirección: \\',CLI.direccion),concat(\\'Telefono: \\',CLI.telefono) from Clientes CLI  where CLI.codigoCliente=\\'@_codigoCliente\\' and CLI.tipoCliente=1;','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","332")){
                _iterador=false; return false; } break;
        case 332:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (50,5,'Saldo de proveedor por moneda(nuevo)','SELECT DOC.codigoCliente\\'CODIGO PROVEEDOR\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\')\\')\\'DOCUMENTO\\', MON.simboloMoneda\\'\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.codigoCliente=\\'@_codigoProveedor\\' and DOC.tipoCliente=\\'2\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1 and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'  and DOC.saldoClienteCuentaCorriente!=0  order by  DOC.fechaEmisionDocumento asc; ','','','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","333")){
                _iterador=false; return false; } break;
        case 333:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (51,5,'Saldo de cliente por primer caracter de su código','SELECT DOC.codigoCliente\\'CODIGO CLIENTE\\', CLI.razonSocial\\'RAZON SOCIAL\\', DOC.fechaEmisionDocumento\\'FECHA DOC.\\', concat(TDOC.descripcionTipoDocumento,\\'(\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'DOCUMENTO\\',MON.simboloMoneda\\'\\', round(DOC.saldoClienteCuentaCorriente,2)\\'SALDO\\', formaDePago\\'FORMA DE PAGO\\'   FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  where DOC.tipoCliente=\\'1\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOC.afectaCuentaCorriente=1  and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'   and DOC.codigoCliente like \\'@_principioCodigoDelCliente%\\' and DOC.saldoClienteCuentaCorriente!=0  order by DOC.codigoCliente asc , DOC.fechaEmisionDocumento asc; ','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','1','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","334")){
                _iterador=false; return false; } break;
        case 334:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (52,4,'Facturas con deuda de Medios de Pago','SELECT concat(TD.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\' )\\'Documento\\', DOC.fechaEmisionDocumento\\'Fecha Documento\\', concat(MON.simboloMoneda,\\' \\',DOC.precioTotalVenta)\\'Total Documento\\', concat(MON.simboloMoneda,\\' \\',ROUND(DOC.precioTotalVenta-(DOC.precioTotalVenta/(SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADO\\' limit 1)),2))\\'Deuda minima permitida\\',  MON.simboloMoneda\\'\\', DOC.precioTotalVenta-DOC.saldoClientePagoContado\\'Saldo por pagar\\'  FROM Documentos DOC  join TipoDocumento TD on TD.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where TD.documentoAceptaIngresoDeMediosDePagoLuegoDeEmitido=\\'1\\' and  DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and ROUND(DOC.precioTotalVenta-(DOC.precioTotalVenta/(SELECT valorConfiguracion FROM Configuracion where codigoConfiguracion=\\'MULTIPLICADOR_PORCENTAJE_MINIMO_DEUDA_CONTADO\\' limit 1)),2)<=DOC.precioTotalVenta-DOC.saldoClientePagoContado and MON.codigoMoneda=\\'@_codigoMonedaReporte\\' order by DOC.fechaEmisionDocumento;','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","335")){
                _iterador=false; return false; } break;
        case 335:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (53,8,'Stock por proveedor','select  AR.codigoArticulo\\'Cod.\\',AR.descripcionArticulo\\'Descripción\\',  case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end \\'Stock R.\\', RIGHT(case when (select concat(MON.simboloMoneda,\\'   \\',round(DOCL.precioArticuloUnitario,2)) from Documentos DOC  join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1 and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) is null then \\'N/A\\' else (select concat(MON.simboloMoneda,\\'   \\',round(DOCL.precioArticuloUnitario,2)) from Documentos DOC  join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1 and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) end,9)  \\'Cos.mon.ext.\\',  AR.descripcionExtendida\\'Cod. origen\\',  case when (select DOC.fechaEmisionDocumento from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento   and DOCL.serieDocumento=DOC.serieDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1 and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) is null then \\'0000-00-00\\' else  (select DOC.fechaEmisionDocumento from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento   and DOCL.serieDocumento=DOC.serieDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1 and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) end \\'Fecha.últ.com.\\',   RIGHT(case when (select sum(DOCL.cantidad) from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento   and DOCL.serieDocumento=DOC.serieDocumento    join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1  and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  group by DOC.fechaEmisionDocumento  order by  DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) is null then \\'N/A\\'  else   convert((select sum(DOCL.cantidad) from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=1  and TDOC.utilizaSoloProveedores=1 and TDOC.esDocumentoDeVenta=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  group by DOC.fechaEmisionDocumento  order by  DOC.fechaHoraGuardadoDocumentoSQL desc limit 1),unsigned INTEGER) end,5) \\'Cant.últ.com.\\',  case when(select DOC.fechaEmisionDocumento from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=-1 and TDOC.utilizaCliente=1 and TDOC.esDocumentoDeVenta=1 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) is null then \\'0000-00-00\\' else  (select DOC.fechaEmisionDocumento from Documentos DOC join DocumentosLineas DOCL ON DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where DOCL.codigoArticulo=AR.codigoArticulo and TDOC.afectaStock=-1 and TDOC.utilizaCliente=1 and TDOC.esDocumentoDeVenta=1 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')   order by DOC.fechaHoraGuardadoDocumentoSQL desc limit 1) end \\'Fecha.últ.ven\\' from Articulos AR join Clientes CLI on CLI.codigoCliente=AR.codigoProveedor and CLI.tipoCliente=AR.tipoCliente  where CLI.codigoCliente=\\'@_codigoProveedor\\' and CLI.tipoCliente=2   order by CONVERT(AR.codigoArticulo, SIGNED INTEGER);','','SELECT concat(\\'Código proveedor: \\',CLIE.codigoCliente), concat(\\'Razon social: \\',CLIE.razonSocial), concat(\\'Nombre: \\',CLIE.nombreCliente) from Clientes CLIE where  CLIE.codigoCliente=\\'@_codigoProveedor\\' and CLIE.tipoCliente=2;','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","336")){
                _iterador=false; return false; } break;
        case 336:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (54,4,'Ventas entre fechas detallado sin imp.','select   concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento (Fecha)\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',   sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\'      from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'   group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;','select   concat(\\'Fecha: \\',( case when  MONTH(DOC.fechaEmisionDocumento)=1 then \\'Enero\\'  when  MONTH(DOC.fechaEmisionDocumento)=2 then \\'Febrero\\'  when  MONTH(DOC.fechaEmisionDocumento)=3 then \\'Marzo\\' when  MONTH(DOC.fechaEmisionDocumento)=4 then \\'Abril\\' when  MONTH(DOC.fechaEmisionDocumento)=5 then \\'Mayo\\' when  MONTH(DOC.fechaEmisionDocumento)=6 then \\'Junio\\' when  MONTH(DOC.fechaEmisionDocumento)=7 then \\'Julio\\'   when  MONTH(DOC.fechaEmisionDocumento)=8 then \\'Agosto\\' when  MONTH(DOC.fechaEmisionDocumento)=9 then \\'Setiembre\\'  when  MONTH(DOC.fechaEmisionDocumento)=10 then \\'Octubre\\' when  MONTH(DOC.fechaEmisionDocumento)=11 then \\'Noviembre\\' when  MONTH(DOC.fechaEmisionDocumento)=12 then \\'Diciembre\\'  else \\'Mes Incorrecto\\' end)  ,\\' de \\',YEAR(DOC.fechaEmisionDocumento))\\'fecha\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND(DOC.precioSubTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda )*TDOC.afectaTotales,2) end) \\'Total $\\', \\'$\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND(DOC.precioSubTotalVenta*(select MONE.cotizacionMoneda from Monedas MONE where MONE.codigoMoneda=MON.codigoMoneda )*TDOC.afectaTotales,2) end)   from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'     and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'      group by YEAR(DOC.fechaEmisionDocumento), MONTH(DOC.fechaEmisionDocumento) order by DOC.fechaEmisionDocumento desc; ','','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","337")){
                _iterador=false; return false; } break;
        case 337:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (55,5,'Saldo Total de clientes por moneda','SELECT DOC.codigoCliente\\'CODIGO CLIENTE\\', CLI.razonSocial\\'RAZON SOCIAL\\', MON.simboloMoneda\\'\\', sum(round(DOC.saldoClienteCuentaCorriente,2))\\'SALDO\\' FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente where  	DOC.tipoCliente=\\'1\\' and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and TDOC.afectaCuentaCorriente=1  and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'   and DOC.saldoClienteCuentaCorriente!=0 group by DOC.codigoCliente order by DOC.codigoCliente asc ;','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","338")){
                _iterador=false; return false; } break;
        case 338:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (56,4,'Ventas entre fechas por rubro y lista de precio','select  AR.codigoArticulo\\'Codigo art.\\', AR.descripcionArticulo\\'Descripción\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'# ventas\\' ,case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end \\'Stock Real\\',MON.simboloMoneda\\'Moneda\\', LPA.precioArticulo\\'Precio Artículo\\', AR.descripcionExtendida\\'Descripción extendida\\' from  DocumentosLineas DOCL   left join Documentos DOC  on DOC.codigoDocumento=DOCL.codigoDocumento and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento  and DOC.serieDocumento=DOCL.serieDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo   join SubRubros SR on SR.codigoSubRubro=AR.codigoSubRubro join Rubros RU on RU.codigoRubro=SR.codigoRubro join Monedas MON on MON.codigoMoneda=AR.codigoMoneda join ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo where   DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\' and LPA.codigoListaPrecio=1 and LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'    and RU.codigoRubro=\\'@_codigoRubro\\'   group by AR.codigoArticulo  order by  RU.codigoRubro, SR.codigoSubRubro,AR.codigoArticulo;','','','0','0','0','0','0','1','1','0','0','0','0','1','0','0','1','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","339")){
                _iterador=false; return false; } break;
        case 339:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (57,4,'Artículos sin venta por rubro entre fechas','select AR.codigoArticulo\\'Codigo Artículo\\',AR.descripcionArticulo\\'Nombre Arículo\\' from Articulos AR join SubRubros SUR on SUR.codigoSubRubro=AR.codigoSubRubro join Rubros RUB on RUB.codigoRubro=SUR.codigoRubro where  RUB.codigoRubro=\\'@_codigoRubro\\'  and ((select sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\'   from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento   where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.afectaTotales!=0  and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' ) is null or (select sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\'   from Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento   where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.afectaTotales!=0  and DOCL.codigoArticulo=AR.codigoArticulo and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' )=0)  order by CONVERT(AR.codigoArticulo, SIGNED INTEGER);','','','0','0','0','0','0','1','1','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","340")){
                _iterador=false; return false; } break;
        case 340:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (58,1,'Artículos sin venta y sin stock','SELECT * FROM  (select AR.codigoArticulo AS Codigo,AR.descripcionArticulo \\'Nombre Artículo\\', case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end AS Stock , (select    sum(DOCL.cantidad) from  Documentos DOC join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'    and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' and DOCL.codigoArticulo=AR.codigoArticulo    group by DOCL.codigoArticulo) AS CantidadVenta  		from Articulos AR  join Clientes CLI on CLI.codigoCliente=AR.codigoProveedor and CLI.tipoCliente=AR.tipoCliente       ) sub  WHERE (sub.Stock<=0 or sub.cantidadVenta is null or sub.CantidadVenta=0)     order by CONVERT(sub.Codigo, SIGNED INTEGER);','','','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","341")){
                _iterador=false; return false; } break;
        case 341:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (59,4,'Ventas de clientes entre fechas por clasificación','SET @CANTIDAD_DIGITOS_DECIMALES_MONTO = (select CONF.valorConfiguracion from Configuracion CONF where CONF.codigoConfiguracion=\\'CANTIDAD_DIGITOS_DECIMALES_MONTO\\');  SELECT   concat((case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end),\\' (\\',DOC.codigoCliente,\\')\\')\\'CLIENTE\\',  sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,@CANTIDAD_DIGITOS_DECIMALES_MONTO)  else ROUND(0,@CANTIDAD_DIGITOS_DECIMALES_MONTO) end) \\'Total $\\', sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,@CANTIDAD_DIGITOS_DECIMALES_MONTO)  else ROUND(0,@CANTIDAD_DIGITOS_DECIMALES_MONTO) end) \\'Total U$S\\'  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\'    and  DOC.tipoCliente=1      and  DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\' and  CLI.tipoClasificacion = \\'@_codigoClasificacionClienteReporte\\' group by DOC.codigoCliente  order by CLI.razonSocial;','','','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0'); SET FOREIGN_KEY_CHECKS=1;","342")){
                _iterador=false; return false; } break;
        case 342:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (60,4,'Ventas de clientes entre fechas por lista de precio','SET @CANTIDAD_DIGITOS_DECIMALES_MONTO = (select CONF.valorConfiguracion from Configuracion CONF where CONF.codigoConfiguracion=\\'CANTIDAD_DIGITOS_DECIMALES_MONTO\\');    select * from  (SELECT   concat((case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end),\\' (\\',DOC.codigoCliente,\\')\\')\\'CLIENTE\\',   sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,@CANTIDAD_DIGITOS_DECIMALES_MONTO)  else ROUND(0,@CANTIDAD_DIGITOS_DECIMALES_MONTO) end) \\'Total $\\',  sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,@CANTIDAD_DIGITOS_DECIMALES_MONTO)  else ROUND(0,@CANTIDAD_DIGITOS_DECIMALES_MONTO) end) \\'Total U$S\\' , case when LPC.codigoListaPrecio is null then \\'Sin lista precio, asume la 1\\' else LPC.codigoListaPrecio end AS CodigoListaPrecio  FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente    join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    left join ListaPrecioClientes LPC on LPC.tipoCliente=CLI.tipoCliente and LPC.codigoCliente=CLI.codigoCliente    where  	DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  	and TDOC.esDocumentoDeVenta=\\'1\\'    	and  DOC.tipoCliente=1      	and  DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'    group by DOC.codigoCliente  order by CLI.razonSocial) Sub where (((Sub.CodigoListaPrecio=\\'Sin lista precio, asume la 1\\' or Sub.CodigoListaPrecio=1) and \\'1\\'=\\'@_codigoListaPrecio\\') or  Sub.CodigoListaPrecio=\\'@_codigoListaPrecio\\');','','','0','0','0','0','0','1','1','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","343")){
                _iterador=false; return false; } break;
        case 343:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (61,4,'Balance por moneda y lista de precio','select  sum(Sub.Stock_Real*Sub.Precio_Articulo)\\'Monto balance total\\', Sub.Moneda \\'Moneda\\' from  (SELECT  AR.codigoArticulo as Codigo_Articulo, MON.simboloMoneda as Moneda, case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and DOCL.codigoArticulo=AR.codigoArticulo     and DOC.fechaHoraGuardadoDocumentoSQL>=    (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos  where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by codigoDocumento desc limit 1)  group by DOCL.codigoArticulo) end  as Stock_Real, LPA.precioArticulo as Precio_Articulo FROM Articulos AR  join ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  join Monedas MON on MON.codigoMoneda=AR.codigoMoneda join SubRubros SUBRUB on SUBRUB.codigoSubRubro=AR.codigoSubRubro  where LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' and AR.codigoMoneda=\\'@_codigoMonedaReporte\\' order by CAST(AR.codigoArticulo AS SIGNED) ) Sub where Sub.Stock_Real>0;','','SELECT  concat(\\'Lista: \\',LP.descripcionListaPrecio),concat(\\'Moneda: \\',(select MON.descripcionMoneda from Monedas MON where MON.codigoMoneda=\\'@_codigoMonedaReporte\\')) from ListaPrecio LP  where LP.codigoListaPrecio=\\'@_codigoListaPrecio\\';','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","344")){
                _iterador=false; return false; } break;
        case 344:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (62,4,'Balance por moneda y lista de precio detallado','select  concat(Sub.Codigo_Articulo,\\' - \\', Sub.Descripcion_Articulo)\\'Artículo\\', Sub.Stock_Real\\'Stock\\', Sub.Precio_Articulo\\'Costo unitario\\',  Sub.Stock_Real*Sub.Precio_Articulo\\'Stock valorizado\\', Sub.Moneda  \\'Moneda\\' from    (SELECT  AR.codigoArticulo as Codigo_Articulo, AR.descripcionArticulo as Descripcion_Articulo , MON.simboloMoneda as Moneda, case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0  and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\')  and DOCL.codigoArticulo=AR.codigoArticulo     and DOC.fechaHoraGuardadoDocumentoSQL>=    (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\'  FROM Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos  where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\')  order by codigoDocumento desc limit 1)  group by DOCL.codigoArticulo) end  as Stock_Real, LPA.precioArticulo as Precio_Articulo FROM Articulos AR  join ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  join Monedas MON on MON.codigoMoneda=AR.codigoMoneda join SubRubros SUBRUB on SUBRUB.codigoSubRubro=AR.codigoSubRubro  where  LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' and AR.codigoMoneda=\\'@_codigoMonedaReporte\\'  order by CAST(AR.codigoArticulo AS SIGNED) ) Sub where Sub.Stock_Real>0;','','SELECT  concat(\\'Lista: \\',LP.descripcionListaPrecio),concat(\\'Moneda: \\',(select MON.descripcionMoneda from Monedas MON where MON.codigoMoneda=\\'@_codigoMonedaReporte\\')) from ListaPrecio LP  where LP.codigoListaPrecio=\\'@_codigoListaPrecio\\';','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","345")){
                _iterador=false; return false; } break;
        case 345:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (63,4,'Ventas entre fechas detallado por tipo documento','select  concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento (Fecha)\\',  sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',   sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\'    from  Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\'    and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'     and DOC.codigoTipoDocumento=\\'@_codigoDocumento\\' group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;','','','0','0','0','0','0','1','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","346")){
                _iterador=false; return false; } break;
        case 346:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (64,4,'Ventas por documento con detalle medios de pago','select  concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento (Fecha)\\',  case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total doc. en $\\',    case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total doc. en U$S\\', case when DLP.codigoMedioPago=1  then DLP.importePago else 0 end \\'Efec. $\\',  case when DLP.codigoMedioPago=2  then DLP.importePago else 0 end \\'Efec. U$S\\',  case when DLP.codigoMedioPago=3  then DLP.importePago else 0 end \\'Tarj. Cre. $\\', case when DLP.codigoMedioPago=4  then DLP.importePago else 0 end \\'Tarj. Cre. U$S\\', case when DLP.codigoMedioPago=5  then DLP.importePago else 0 end \\'Cheque $\\',  case when DLP.codigoMedioPago=6  then DLP.importePago else 0 end \\'Cheque U$S\\', case when DLP.codigoMedioPago=7  then DLP.importePago else 0 end \\'Dep. banco $\\', case when DLP.codigoMedioPago=8  then DLP.importePago else 0 end \\'Dep. banco U$S\\' from  Documentos DOC   left join DocumentosLineasPago DLP on DLP.codigoDocumento=DOC.codigoDocumento  and DLP.codigoTipoDocumento=DOC.codigoTipoDocumento  and DLP.serieDocumento=DOC.serieDocumento   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\'    and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'    and DOC.codigoTipoDocumento=\\'@_codigoDocumento\\'  order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento,DLP.codigoMedioPago,DLP.monedaMedioPago;','','','0','0','0','0','0','1','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","347")){
                _iterador=false; return false; } break;
        case 347:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (65,8,'Stock con listas de precios','SET @v1 = (select CONF.valorConfiguracion from Configuracion CONF where CONF.codigoConfiguracion=\\'MODO_ARTICULO\\');   select  AR.descripcionArticulo\\'Nombre\\', AR.descripcionExtendida\\'Descripcion corta\\', AR.codigoArticulo, case when (select ARB.codigoArticuloBarras from ArticulosBarras ARB where ARB.codigoArticuloInterno=AR.codigoArticulo limit 1) is null then \\'\\'  else   (select ARB.codigoArticuloBarras from ArticulosBarras ARB where ARB.codigoArticuloInterno=AR.codigoArticulo limit 1)  end \\'N° de parte origen\\',   FORMAT(case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) end,0) \\'Stock\\' , case when (select LPA.precioArticulo from ListaPrecioArticulos LPA where LPA.codigoArticulo=AR.codigoArticulo and LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' limit 1) is null   then 0.00  else (select LPA.precioArticulo from ListaPrecioArticulos LPA where LPA.codigoArticulo=AR.codigoArticulo and LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\' limit 1) end \\'Precio neto\\', case when (select LPA.precioArticulo from ListaPrecioArticulos LPA where LPA.codigoArticulo=AR.codigoArticulo and LPA.codigoListaPrecio=\\'@_codigoLista2Precio\\' limit 1) is null  then 0.00  else  (select LPA.precioArticulo from ListaPrecioArticulos LPA where LPA.codigoArticulo=AR.codigoArticulo and LPA.codigoListaPrecio=\\'@_codigoLista2Precio\\' limit 1)  end \\'PVP\\'  , MON.simboloMoneda\\'Moneda\\'  from Articulos AR  join Monedas MON on MON.codigoMoneda=AR.codigoMoneda  where AR.activo=1 order by  IF(@v1=1,CONVERT(AR.codigoArticulo, SIGNED INTEGER),0) asc,IF(@v1=0,AR.codigoArticulo,0) asc;   ','','','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','1'); SET FOREIGN_KEY_CHECKS=1;","348")){
                _iterador=false; return false; } break;
        case 348:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (66,1,'Artículos desde > hasta','SELECT AR.codigoArticulo\\'Código\\', AR.descripcionArticulo\\'Nombre\\',   AR.fechaAlta\\'Fecha alta\\', AR.usuarioAlta \\'Usuario alta\\', AR.fechaUltimaModificacion\\'Fecha última modificación\\'  , AR.usuarioUltimaModificacion \\'Usuario última modificación \\'   FROM Articulos AR    where AR.codigoArticulo between CONVERT(\\'@_ArticulodesdeCodigoArticulo\\', SIGNED INTEGER)  and CONVERT(\\'@_ArticulohastaCodigoArticulo\\', SIGNED INTEGER)   order by CONVERT(AR.codigoArticulo, SIGNED INTEGER);','','','0','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","349")){
                _iterador=false; return false; } break;
        case 349:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (67,4,'Ventas entre fechas deta. x tipo documento y moneda','select  concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento (Fecha)\\',  sum(ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)) \\'Total\\',    MON.simboloMoneda\\'Moneda\\'   from  Documentos DOC     join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento     join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')   and TDOC.esDocumentoDeVenta=\\'1\\'     and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'      and DOC.codigoTipoDocumento=\\'@_codigoDocumento\\'  group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento;','','','0','0','0','0','0','1','1','0','1','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","350")){
                _iterador=false; return false; } break;
        case 350:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (68,2,'Clientes según procedencia entre fechas','SELECT TPC.descripcionTipoProcedenciaCliente\\'Procedencia\\', count(CLI.codigoTipoProcedenciaCliente)\\'Cantidad\\'  FROM Clientes CLI  join TipoProcedenciaCliente TPC on TPC.codigoTipoProcedenciaCliente=CLI.codigoTipoProcedenciaCliente   where  CLI.tipoCliente=1 and CLI.fechaAlta between \\'@_desde\\' and \\'@_hasta\\'  group by CLI.codigoTipoProcedenciaCliente;','SELECT TPC.descripcionTipoProcedenciaCliente\\'Procedencia\\', count(CLI.codigoTipoProcedenciaCliente)\\'Cantidad\\',\\'#\\',count(CLI.codigoTipoProcedenciaCliente)  FROM Clientes CLI  join TipoProcedenciaCliente TPC on TPC.codigoTipoProcedenciaCliente=CLI.codigoTipoProcedenciaCliente   where  CLI.tipoCliente=1 and CLI.fechaAlta between \\'@_desde\\' and \\'@_hasta\\'  group by CLI.codigoTipoProcedenciaCliente;','','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","351")){
                _iterador=false; return false; } break;
        case 351:
                if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;REPLACE INTO `Reportes` VALUES (69,7,'Documentos por tipo y entre fechas','SELECT concat(TDOC.descripcionTipoDocumento,\\' (\\',DOC.serieDocumento,\\'-\\',DOC.codigoDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento\\', case when CLI.nombreCliente is null then \\'\\' else CLI.nombreCliente end  \\'Cliente\\', concat(MON.simboloMoneda,\\'      \\',DOC.precioTotalVenta)\\'Total\\',   DOC.fechaEmisionDocumento\\'Fecha Doc.\\',  DOC.usuarioUltimaModificacion\\'Usuario ultima modificación\\'  , DOC.usuarioAlta\\'Usuario creador\\'    FROM Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   left join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Usuarios USU on USU.idUsuario=DOC.usuarioUltimaModificacion where    DOC.codigoTipoDocumento=\\'@_codigoDocumento\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\' ;','','','0','0','0','0','0','1','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'); SET FOREIGN_KEY_CHECKS=1;","352")){
                _iterador=false; return false; } break;
        case 352:
                if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select  sub.codigoArticulo\\'Codigo art.\\', sub.descripcionArticulo\\'Descripción\\',sub.ventas\\'# ventas\\',sub.stockReal\\'Stock Real\\',sub.moneda\\'Moneda\\',sub.precioArticulo\\'Precio Artículo\\', sub.descripcionExtendida\\'Descripción extendida\\' from (select  AR.codigoArticulo\\'codigoArticulo\\', AR.descripcionArticulo\\'descripcionArticulo\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'ventas\\' , case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo)  end \\'stockReal\\',  MON.simboloMoneda\\'moneda\\',  LPA.precioArticulo\\'precioArticulo\\',  AR.descripcionExtendida\\'descripcionExtendida\\' from  DocumentosLineas DOCL    left join Documentos DOC  on DOC.codigoDocumento=DOCL.codigoDocumento and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento  and DOC.serieDocumento=DOCL.serieDocumento    join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo   join SubRubros SR on SR.codigoSubRubro=AR.codigoSubRubro  join Rubros RU on RU.codigoRubro=SR.codigoRubro   join Monedas MON on MON.codigoMoneda=AR.codigoMoneda  join ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  where   DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\' and LPA.codigoListaPrecio=1  and LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\'  and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'    and RU.codigoRubro=\\'@_codigoRubro\\'  group by AR.codigoArticulo  order by  RU.codigoRubro, SR.codigoSubRubro,AR.codigoArticulo) sub where sub.ventas!=0 ;' WHERE `codigoReporte`='56';","353")){
                _iterador=false; return false; } break;
        case 353:
                if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select concat(DOCL.codigoArticulo,\\' - \\',AR.descripcionArticulo)\\'Artículo\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\'        from Documentos DOC  	join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento      join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento      join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo  where 	DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  		and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\' 	and TDOC.afectaTotales!=0  and TDOC.esDocumentoDeVenta=\\'1\\'  group by DOCL.codigoArticulo order by 2 asc limit @_cantidad ;', `utilizaFechaDesde`='1', `utilizaFechaHasta`='1' WHERE `codigoReporte`='20';","354")){
                _iterador=false; return false; } break;
        case 354:
                if(!impactoCambioEnBD("ALTER TABLE `Clientes` CHANGE COLUMN `email` `email` VARCHAR(100) NULL DEFAULT NULL ;","355")){
                _iterador=false; return false; } break;
        case 355:
                if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select  concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\')\\'Documento (Fecha)\\', CLI.razonSocial\\'Razón Social\\', sum(ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)) \\'Total\\',    MON.simboloMoneda\\'Moneda\\'   from  Documentos DOC      join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento      join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento     join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente  where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')   and TDOC.esDocumentoDeVenta=\\'1\\'     and DOC.codigoMonedaDocumento=\\'@_codigoMonedaReporte\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'      and DOC.codigoTipoDocumento=\\'@_codigoDocumento\\'  group by DOC.codigoDocumento order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento; ' WHERE `codigoReporte`='67';","356")){
                _iterador=false; return false; } break;
        case 356:
            if(impactoCambioEnBD("UPDATE `ReportesConfiguracion` SET `columnaReporte`='3' WHERE `codigoReporte`='67' and`columnaReporte`='2';","356")){
                if(!impactoCambioEnBD("UPDATE `ReportesConfiguracion` SET `columnaReporte`='2' WHERE `codigoReporte`='67' and`columnaReporte`='1';","357")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 357:
            if(impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;ALTER TABLE `Documentos` CHANGE COLUMN `codigoDocumento` `codigoDocumento` BIGINT(20) UNSIGNED NOT NULL ;SET FOREIGN_KEY_CHECKS=1;","357")){
                if(impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;ALTER TABLE `DocumentosCanceladosCuentaCorriente` CHANGE COLUMN `codigoDocumento` `codigoDocumento` BIGINT(20) UNSIGNED NOT NULL ;SET FOREIGN_KEY_CHECKS=1;","357")){
                    if(impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;ALTER TABLE `DocumentosLineas` DROP FOREIGN KEY `fk_DocumentoExiste`; ALTER TABLE `khitomer`.`DocumentosLineas` CHANGE COLUMN `codigoDocumento` `codigoDocumento` BIGINT(20) UNSIGNED NOT NULL ; ALTER TABLE `khitomer`.`DocumentosLineas` ADD CONSTRAINT `fk_DocumentoExiste`  FOREIGN KEY (`codigoDocumento` , `codigoTipoDocumento`)   REFERENCES `khitomer`.`Documentos` (`codigoDocumento` , `codigoTipoDocumento`)  ON DELETE NO ACTION  ON UPDATE NO ACTION;SET FOREIGN_KEY_CHECKS=1;","357")){
                        if(!impactoCambioEnBD("SET FOREIGN_KEY_CHECKS=0;ALTER TABLE `DocumentosLineasPago` DROP FOREIGN KEY `fk_DocumentosMediosDePago`; ALTER TABLE `khitomer`.`DocumentosLineasPago` CHANGE COLUMN `codigoDocumento` `codigoDocumento` BIGINT(20) UNSIGNED NOT NULL ; ALTER TABLE `khitomer`.`DocumentosLineasPago` ADD CONSTRAINT `fk_DocumentosMediosDePago`   FOREIGN KEY (`codigoDocumento` , `codigoTipoDocumento`)  REFERENCES `khitomer`.`Documentos` (`codigoDocumento` , `codigoTipoDocumento`)  ON DELETE NO ACTION ON UPDATE NO ACTION; SET FOREIGN_KEY_CHECKS=1;","358")){
                            _iterador=false; return false;
                        }
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 358:
            if(!impactoCambioEnBD("INSERT INTO `CFE_ParametrosGenerales` (`nombreParametro`, `valorParametro`, `descripcionParametro`) VALUES ('articuloUsaConcatenacionImix', '0', 'Se concatena codigo y nombre articulo para Imix');","359")){
                _iterador=false; return false; } break;

        case 359:
            if(!impactoCambioEnBD("INSERT INTO `CFE_ParametrosGenerales` (`nombreParametro`, `valorParametro`, `descripcionParametro`) VALUES ('envioClienteGenerico', '1', '1- Se envia dato generico. 0- Se envia  dato especifico. Especifica si se envia el cliente 1 siempre, o se envia el dato acorde a la facturación');","360")){
                _iterador=false; return false;
            }
            break;


        case 360:
            if(impactoCambioEnBD("ALTER TABLE `Ivas` ADD COLUMN `Ivascol` VARCHAR(45) NULL AFTER `indicadorFacturacionCFE`,  ADD COLUMN `codigoIvaCFE` INT(10) UNSIGNED NOT NULL DEFAULT 1 AFTER `Ivascol`;","360")){
                if(impactoCambioEnBD("update Ivas set codigoIvaCFE = 1  where codigoIva = 1;","360")){
                    if(impactoCambioEnBD("update Ivas set codigoIvaCFE = 2  where codigoIva = 3;","360")){
                        if(!impactoCambioEnBD("update Ivas set codigoIvaCFE = 3  where codigoIva = 2;","361")){
                            _iterador=false; return false;
                        }
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 361:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaCodigoCliente`, `utilizaCodigoProveedor`, `utilizaCodigoArticulo`, `utilizaCantidadItemRanking`, `utilizaFecha`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaVendedor`, `utilizaTipoDocumento`, `utilizaSubRubros`, `utilizaCodigoLiquidacionCaja`, `utilizaRubros`, `utilizaDesdeCodigoArticulo`, `utilizaHastaCodigoArticulo`, `utilizaListaPrecio`, `utilizaGraficas`, `utilizaCuentaBancaria`, `utilizaMonedas`, `utilizaPais`, `utilizaDepartamento`, `utilizaLocalidad`, `utilizaCoincidenciaCodigoCliente`, `utilizaOrdenEnReporte`, `utilizaTipoClasificacionCliente`, `utilizaListaPrecio2`) VALUES ('70', '4', 'Ventas entre fechas detallado con iva', 'select   concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\') - CFE: \\', DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\' )\\'Documento (Fecha)\\',  \\'PESOS:\\' as \\' - \\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.totalIva1*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Iva BASICO $\\',  sum(case when MON.codigoMoneda=1 then  ROUND(DOC.totalIva2*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Iva MINIMO $\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.totalIva3*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Iva EXENTO $\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'SubTotal $\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\', \\'DOLARES:\\' as \\' - \\', sum(case when MON.codigoMoneda=2 then  ROUND(DOC.totalIva1*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Iva BASICO U$S\\', sum(case when MON.codigoMoneda=2 then  ROUND(DOC.totalIva2*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Iva MINIMO U$S\\',  sum(case when MON.codigoMoneda=2 then  ROUND(DOC.totalIva3*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Iva EXENTO U$S\\', sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioSubTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'SubTotal U$S\\', sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\'     from  Documentos DOC  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'    and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'     group by DOC.codigoDocumento  order by DOC.fechaHoraGuardadoDocumentoSQL,DOC.codigoDocumento; ', '', '', '', '', '', '', '', '1', '1', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '');","361")){
                if(!impactoCambioEnBD("INSERT INTO ReportesConfiguracion VALUES(70,0,0,0,'','TEXTO'),(70,1,2,0,'','TEXTO'),(70,2,2,1,'','MONTO'),(70,3,2,1,'','MONTO'),(70,4,2,1,'','MONTO'),(70,5,2,1,'','MONTO'),(70,6,2,1,'','MONTO'),(70,7,2,0,'','TEXTO'),(70,8,2,1,'','MONTO'),(70,9,2,1,'','MONTO'),(70,10,2,1,'','MONTO'),(70,11,2,1,'','MONTO'),(70,12,2,1,'','MONTO');","362")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;

        case 362:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaCodigoCliente`, `utilizaCodigoProveedor`, `utilizaCodigoArticulo`, `utilizaCantidadItemRanking`, `utilizaFecha`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaVendedor`, `utilizaTipoDocumento`, `utilizaSubRubros`, `utilizaCodigoLiquidacionCaja`, `utilizaRubros`, `utilizaDesdeCodigoArticulo`, `utilizaHastaCodigoArticulo`, `utilizaListaPrecio`, `utilizaGraficas`, `utilizaCuentaBancaria`, `utilizaMonedas`, `utilizaPais`, `utilizaDepartamento`, `utilizaLocalidad`, `utilizaCoincidenciaCodigoCliente`, `utilizaOrdenEnReporte`, `utilizaTipoClasificacionCliente`, `utilizaListaPrecio2`) VALUES ('71', '4', 'Ventas de IVA  BASICO entre fechas', 'select   concat(AR.descripcionArticulo,\\'(\\',AR.codigoArticulo,\\')\\')\\'ARTICULO\\', sum(ROUND(DOCL.cantidad*TDOC.afectaTotales,2)) \\'Cantidad\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOCL.precioIvaArticulo*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Iva BASICO $\\', sum(case when MON.codigoMoneda=2 then  ROUND(DOCL.precioIvaArticulo*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Iva BASICO U$S\\' from   Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'    and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'     and AR.codigoIva=1  group by AR.codigoArticulo order by AR.descripcionArticulo;  ', '', '', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0');","362")){
                if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaCodigoCliente`, `utilizaCodigoProveedor`, `utilizaCodigoArticulo`, `utilizaCantidadItemRanking`, `utilizaFecha`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaVendedor`, `utilizaTipoDocumento`, `utilizaSubRubros`, `utilizaCodigoLiquidacionCaja`, `utilizaRubros`, `utilizaDesdeCodigoArticulo`, `utilizaHastaCodigoArticulo`, `utilizaListaPrecio`, `utilizaGraficas`, `utilizaCuentaBancaria`, `utilizaMonedas`, `utilizaPais`, `utilizaDepartamento`, `utilizaLocalidad`, `utilizaCoincidenciaCodigoCliente`, `utilizaOrdenEnReporte`, `utilizaTipoClasificacionCliente`, `utilizaListaPrecio2`) VALUES ('72', '4', 'Ventas de IVA  MINIMO entre fechas', 'select   concat(AR.descripcionArticulo,\\'(\\',AR.codigoArticulo,\\')\\')\\'ARTICULO\\', sum(ROUND(DOCL.cantidad*TDOC.afectaTotales,2)) \\'Cantidad\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOCL.precioIvaArticulo*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Iva MINIMO $\\', sum(case when MON.codigoMoneda=2 then  ROUND(DOCL.precioIvaArticulo*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Iva MINIMO U$S\\' from   Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'    and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'     and AR.codigoIva=2  group by AR.codigoArticulo order by AR.descripcionArticulo;  ', '', '', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0');","362")){
                    if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaCodigoCliente`, `utilizaCodigoProveedor`, `utilizaCodigoArticulo`, `utilizaCantidadItemRanking`, `utilizaFecha`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaVendedor`, `utilizaTipoDocumento`, `utilizaSubRubros`, `utilizaCodigoLiquidacionCaja`, `utilizaRubros`, `utilizaDesdeCodigoArticulo`, `utilizaHastaCodigoArticulo`, `utilizaListaPrecio`, `utilizaGraficas`, `utilizaCuentaBancaria`, `utilizaMonedas`, `utilizaPais`, `utilizaDepartamento`, `utilizaLocalidad`, `utilizaCoincidenciaCodigoCliente`, `utilizaOrdenEnReporte`, `utilizaTipoClasificacionCliente`, `utilizaListaPrecio2`) VALUES ('73', '4', 'Ventas de IVA  EXENTO entre fechas', 'select   concat(AR.descripcionArticulo,\\'(\\',AR.codigoArticulo,\\')\\')\\'ARTICULO\\', sum(ROUND(DOCL.cantidad*TDOC.afectaTotales,2)) \\'Cantidad\\', sum(case when MON.codigoMoneda=1 then  ROUND(DOCL.precioIvaArticulo*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Iva EXENTO $\\', sum(case when MON.codigoMoneda=2 then  ROUND(DOCL.precioIvaArticulo*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Iva EXENTO U$S\\' from   Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'    and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'     and AR.codigoIva=3  group by AR.codigoArticulo order by AR.descripcionArticulo;  ', '', '', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0');","362")){
                        if(impactoCambioEnBD("UPDATE `Reportes` SET `utilizaCodigoCliente`='0', `utilizaCodigoProveedor`='0', `utilizaCodigoArticulo`='0', `utilizaCantidadItemRanking`='0', `utilizaFecha`='0', `utilizaVendedor`='0', `utilizaTipoDocumento`='0', `utilizaSubRubros`='0', `utilizaCodigoLiquidacionCaja`='0', `utilizaRubros`='0', `utilizaDesdeCodigoArticulo`='0', `utilizaHastaCodigoArticulo`='0', `utilizaListaPrecio`='0', `utilizaGraficas`='0', `utilizaCuentaBancaria`='0', `utilizaMonedas`='0', `utilizaPais`='0', `utilizaDepartamento`='0', `utilizaLocalidad`='0', `utilizaCoincidenciaCodigoCliente`='0', `utilizaOrdenEnReporte`='0', `utilizaTipoClasificacionCliente`='0', `utilizaListaPrecio2`='0' WHERE `codigoReporte`='70';","362")){
                                if(!impactoCambioEnBD("INSERT INTO ReportesConfiguracion VALUES(71,0,0,0,'','TEXTO'),(71,1,2,2,'','TEXTO'),(71,2,2,1,'','MONTO'),(71,3,2,1,'','MONTO'),(72,0,0,0,'','TEXTO'),(72,1,2,2,'','TEXTO'),(72,2,2,1,'','MONTO'),(72,3,2,1,'','MONTO'),(73,0,0,0,'','TEXTO'),(73,1,2,2,'','TEXTO'),(73,2,2,1,'','MONTO'),(73,3,2,1,'','MONTO');","363")){
                                    _iterador=false; return false;
                                }
                        }else{_iterador=false; return false;}
                    }else{_iterador=false; return false;}
                }else{_iterador=false; return false;}
            }else{_iterador=false; return false;}
            break;
        case 363:
            if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select   concat(AR.descripcionArticulo,\\'(\\',AR.codigoArticulo,\\')\\')\\'ARTICULO\\',  sum(ROUND(DOCL.cantidad*TDOC.afectaTotales,2)) \\'Cantidad\\',  sum(case when MON.codigoMoneda=1 then  ROUND(DOCL.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Mto. NO Grabado EXENTO $\\',  sum(case when MON.codigoMoneda=2 then  ROUND(DOCL.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Mto. NO Grabado EXENTO U$S\\'   from   Documentos DOC  join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento   join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'    and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'   and AR.codigoIva=3  group by AR.codigoArticulo order by AR.descripcionArticulo;  ' WHERE `codigoReporte`='73';","364")){
                _iterador=false; return false;
            }
            break;
        case 364:
            if(!impactoCambioEnBD("INSERT INTO `CFE_ParametrosGenerales` (`nombreParametro`, `valorParametro`, `descripcionParametro`) VALUES ('envioCiudadEnDireccion', '0', 'Envio información de la ciudad en la dirección del cliente');","365")){
                _iterador=false; return false;
            }
            break;
        case 365:
            if(!impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaCodigoCliente`, `utilizaCodigoProveedor`, `utilizaCodigoArticulo`, `utilizaCantidadItemRanking`, `utilizaFecha`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaVendedor`, `utilizaTipoDocumento`, `utilizaSubRubros`, `utilizaCodigoLiquidacionCaja`, `utilizaRubros`, `utilizaDesdeCodigoArticulo`, `utilizaHastaCodigoArticulo`, `utilizaListaPrecio`, `utilizaGraficas`, `utilizaCuentaBancaria`, `utilizaMonedas`, `utilizaPais`, `utilizaDepartamento`, `utilizaLocalidad`, `utilizaCoincidenciaCodigoCliente`, `utilizaOrdenEnReporte`, `utilizaTipoClasificacionCliente`, `utilizaListaPrecio2`) VALUES ('74', '4', 'Ventas entre fechas por rubro y lista de precio y compras', 'select  sub.codigoArticulo\\'Codigo art.\\', sub.descripcionArticulo\\'Descripción\\', sub.ventas\\'# ventas\\', sub.stockReal\\'Stock Real\\', sub.moneda\\'Moneda\\', sub.precioArticulo\\'Precio Artículo\\',  (select concat(lpad(sum(DOCUL.cantidad),5,\\'0\\'),\\' - \\',DOCU.fechaEmisionDocumento)\\'d\\'  from Documentos DOCU   join DocumentosLineas DOCUL on DOCUL.codigoDocumento=DOCU.codigoDocumento and DOCUL.codigoTipoDocumento=DOCU.codigoTipoDocumento and DOCUL.serieDocumento=DOCU.serieDocumento  join TipoDocumento TDOCU on TDOCU.codigoTipoDocumento=DOCU.codigoTipoDocumento  where DOCU.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOCU.utilizaArticulos=1 and TDOCU.utilizaSoloProveedores=1 and TDOCU.afectaStock=1  and DOCUL.codigoArticulo=sub.codigoArticulo  group by DOCUL.codigoArticulo,DOCU.fechaEmisionDocumento  order by DOCU.fechaEmisionDocumento desc  limit 1)\\'Ultima compra(#-Fecha)\\',  (select concat(lpad(sum(DOCUL.cantidad*TDOCU.afectaTotales),5,\\'0\\'),\\' - \\',DOCU.fechaEmisionDocumento)\\'d\\'  from Documentos DOCU   join DocumentosLineas DOCUL on DOCUL.codigoDocumento=DOCU.codigoDocumento and DOCUL.codigoTipoDocumento=DOCU.codigoTipoDocumento and DOCUL.serieDocumento=DOCU.serieDocumento   join TipoDocumento TDOCU on TDOCU.codigoTipoDocumento=DOCU.codigoTipoDocumento  where DOCU.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOCU.esDocumentoDeVenta=\\'1\\'   and DOCUL.codigoArticulo=sub.codigoArticulo  group by DOCUL.codigoArticulo,DOCU.fechaEmisionDocumento  order by DOCU.fechaEmisionDocumento desc  limit 1)\\'Ultima venta(#-Fecha)\\',  sub.descripcionExtendida\\'Descripción extendida\\' from (select  AR.codigoArticulo\\'codigoArticulo\\', AR.descripcionArticulo\\'descripcionArticulo\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'ventas\\' , case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo)  end \\'stockReal\\',  MON.simboloMoneda\\'moneda\\',  LPA.precioArticulo\\'precioArticulo\\',  AR.descripcionExtendida\\'descripcionExtendida\\' from  DocumentosLineas DOCL    left join Documentos DOC  on DOC.codigoDocumento=DOCL.codigoDocumento and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento  and DOC.serieDocumento=DOCL.serieDocumento    join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo   join SubRubros SR on SR.codigoSubRubro=AR.codigoSubRubro  join Rubros RU on RU.codigoRubro=SR.codigoRubro   join Monedas MON on MON.codigoMoneda=AR.codigoMoneda  join ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  where   DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\' and   LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\'  and  DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'    and  RU.codigoRubro=\\'@_codigoRubro\\'   group by AR.codigoArticulo  order by  RU.codigoRubro, SR.codigoSubRubro,AR.codigoArticulo) sub where sub.ventas!=0 ; ', '', '', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0');","366")){
                _iterador=false; return false;
            }
            break;
        case 366:
            if(!impactoCambioEnBD("UPDATE `Reportes` SET `consultaSql`='select  sub.codigoArticulo\\'Codigo art.\\', sub.descripcionArticulo\\'Desc.\\', sub.ventas\\'# ventas\\', sub.stockReal\\'Stock Real\\', sub.moneda\\'Moneda\\', sub.precioArticulo\\'Precio Artículo\\',   (select concat(lpad(sum(DOCUL.cantidad),5,\\'0\\'),\\' - \\',DOCU.fechaEmisionDocumento)\\'d\\'  from Documentos DOCU   join DocumentosLineas DOCUL on DOCUL.codigoDocumento=DOCU.codigoDocumento and DOCUL.codigoTipoDocumento=DOCU.codigoTipoDocumento and DOCUL.serieDocumento=DOCU.serieDocumento   join TipoDocumento TDOCU on TDOCU.codigoTipoDocumento=DOCU.codigoTipoDocumento    where DOCU.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOCU.utilizaArticulos=1 and TDOCU.utilizaSoloProveedores=1 and TDOCU.afectaStock=1  and DOCUL.codigoArticulo=sub.codigoArticulo   group by DOCUL.codigoArticulo,DOCU.fechaEmisionDocumento,DOCU.codigoDocumento,DOCU.codigoTipoDocumento,DOCU.serieDocumento  order by DOCU.fechaEmisionDocumento desc  limit 1)\\'Ultima compra(#-Fecha)\\',  (select concat(lpad(sum(DOCUL.cantidad*TDOCU.afectaTotales),5,\\'0\\'),\\' - \\',DOCU.fechaEmisionDocumento)\\'d\\'  from Documentos DOCU   join DocumentosLineas DOCUL on DOCUL.codigoDocumento=DOCU.codigoDocumento and DOCUL.codigoTipoDocumento=DOCU.codigoTipoDocumento and DOCUL.serieDocumento=DOCU.serieDocumento   join TipoDocumento TDOCU on TDOCU.codigoTipoDocumento=DOCU.codigoTipoDocumento  where DOCU.codigoEstadoDocumento in (\\'E\\',\\'G\\') and TDOCU.esDocumentoDeVenta=\\'1\\'   and DOCUL.codigoArticulo=sub.codigoArticulo  group by DOCUL.codigoArticulo,DOCU.fechaEmisionDocumento,DOCU.codigoDocumento,DOCU.codigoTipoDocumento,DOCU.serieDocumento  order by DOCU.fechaEmisionDocumento desc  limit 1)\\'Ultima venta(#-Fecha)\\',  sub.descripcionExtendida\\'Descripción extendida\\'  from (select  AR.codigoArticulo\\'codigoArticulo\\', AR.descripcionArticulo\\'descripcionArticulo\\', sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'ventas\\' , case when (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>=   (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo) is null  then 0 else  (SELECT sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end) \\'cantidad\\' FROM Documentos DOC join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento  and DOCL.serieDocumento=DOC.serieDocumento  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in (\\'E\\',\\'G\\') and DOCL.codigoArticulo=AR.codigoArticulo    and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT fechaHoraGuardadoDocumentoSQL FROM Documentos where codigoTipoDocumento=8 and codigoEstadoDocumento in (\\'E\\',\\'G\\') order by codigoDocumento desc limit 1) group by DOCL.codigoArticulo)  end \\'stockReal\\',  MON.simboloMoneda\\'moneda\\',  LPA.precioArticulo\\'precioArticulo\\',  AR.descripcionExtendida\\'descripcionExtendida\\' from  DocumentosLineas DOCL    left join Documentos DOC  on DOC.codigoDocumento=DOCL.codigoDocumento and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento  and DOC.serieDocumento=DOCL.serieDocumento    join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento    join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo   join SubRubros SR on SR.codigoSubRubro=AR.codigoSubRubro  join Rubros RU on RU.codigoRubro=SR.codigoRubro   join Monedas MON on MON.codigoMoneda=AR.codigoMoneda  join ListaPrecioArticulos LPA on LPA.codigoArticulo=AR.codigoArticulo  where   DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\' and  LPA.codigoListaPrecio=\\'@_codigoListaPrecio\\'  and  DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'    and  RU.codigoRubro=\\'@_codigoRubro\\'  group by AR.codigoArticulo  order by  RU.codigoRubro, SR.codigoSubRubro,AR.codigoArticulo) sub where sub.ventas!=0 ;' WHERE `codigoReporte`='74';","367")){
                _iterador=false; return false;
            }
            break;
        case 367:
            if(!impactoCambioEnBD("ALTER TABLE `Documentos` ADD COLUMN `documentoEnviadoPorMail` TINYINT(1) UNSIGNED NOT NULL DEFAULT 1 AFTER `caeTipoDocumentoCFEDescripcion`;","368")){
                _iterador=false; return false;
            }
            break;
        case 368:
            if(impactoCambioEnBD("INSERT INTO `CFE_ParametrosGenerales` (`nombreParametro`, `valorParametro`, `descripcionParametro`) VALUES ('empresaImix', '', 'Información sobre la empresa para enviar a Imix remoto');","368")){
                if(!impactoCambioEnBD("INSERT INTO `CFE_ParametrosGenerales` (`nombreParametro`, `valorParametro`, `descripcionParametro`) VALUES ('claveEmpresaImix', '', 'Información de la clave empresa para enviar a Imix');","369")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 369:
            if(!impactoCambioEnBD("INSERT INTO `CFE_ParametrosGenerales` (`nombreParametro`, `valorParametro`, `descripcionParametro`) VALUES ('rutEmpresa', 'XXXXXXXXXXX', 'Información de Rut del comercio.');","370")){
                _iterador=false; return false;
            }
            break;
        case 370:
            if(!impactoCambioEnBD("ALTER TABLE `Documentos`  CHANGE COLUMN `cae_QrCode` `cae_QrCode` VARCHAR(10000) NOT NULL DEFAULT '' ;","371")){
                _iterador=false; return false;
            }
            break;
        case 371:
            if(impactoCambioEnBD("ALTER TABLE `Rubros`  ADD COLUMN `id_web` INT(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `sincronizadoWeb`;","371")){
                if(!impactoCambioEnBD("ALTER TABLE `SubRubros` ADD COLUMN `id_web` INT(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `sincronizadoWeb`;","372")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 372:
            if(!impactoCambioEnBD("ALTER TABLE `Articulos` ADD COLUMN `id_web` INT(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `sincronizadoWeb`;","373")){
                _iterador=false; return false;
            }
            break;
        case 373:
            if(!impactoCambioEnBD("ALTER TABLE `Articulos` ADD INDEX `index_sincWeb2` (`tipoCliente` ASC, `activo` ASC, `sincronizadoWeb` ASC, `id_web` ASC);","374")){
                _iterador=false; return false;
            }
            break;
        case 374:
            if(!impactoCambioEnBD("ALTER TABLE `Clientes` ADD COLUMN `id_web` BIGINT(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `fechaUltimoAvisoCumpleanios`;","375")){
                _iterador=false; return false;
            }
            break;
        case 375:
            if(impactoCambioEnBD("CREATE TABLE `DocumentosBilling` ( `codigoDocumento` BIGINT(20) UNSIGNED NOT NULL,  `codigoTipoDocumento` INT(10) UNSIGNED NOT NULL,  `serieDocumento` VARCHAR(45) NOT NULL,  `first_name` VARCHAR(45) NULL, `last_name` VARCHAR(45) NULL, `company` VARCHAR(45) NULL, `address_1` VARCHAR(45) NULL, `address_2` VARCHAR(45) NULL, `city` VARCHAR(45) NULL, `state` VARCHAR(45) NULL, `postcode` VARCHAR(45) NULL,  `country` VARCHAR(45) NULL, `email` VARCHAR(45) NULL, `phone` VARCHAR(45) NULL, PRIMARY KEY (`codigoDocumento`, `codigoTipoDocumento`, `serieDocumento`));","375")){
                if(!impactoCambioEnBD("CREATE TABLE `DocumentosShipping` (`codigoDocumento` BIGINT(20) UNSIGNED NOT NULL,`codigoTipoDocumento` INT(10) UNSIGNED NOT NULL,`serieDocumento` VARCHAR(45) NOT NULL, `first_name` VARCHAR(45) NULL, `last_name` VARCHAR(45) NULL,`company` VARCHAR(45) NULL,`address_1` VARCHAR(45) NULL,`address_2` VARCHAR(45) NULL,`city` VARCHAR(45) NULL,`state` VARCHAR(45) NULL, `postcode` VARCHAR(45) NULL,`country` VARCHAR(45) NULL,PRIMARY KEY (`codigoDocumento`, `codigoTipoDocumento`, `serieDocumento`));","376")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 376:
            if(!impactoCambioEnBD("ALTER TABLE `Articulos` ADD COLUMN `sincronizadoWebStock` CHAR(1) NOT NULL DEFAULT '0' AFTER `id_web`;","377")){
                _iterador=false; return false;
            }
            break;
        case 377:
            if(!impactoCambioEnBD("ALTER TABLE `Documentos` ADD COLUMN `id_web` BIGINT(20) UNSIGNED NOT NULL DEFAULT 0 AFTER `documentoEnviadoPorMail`;","378")){
                _iterador=false; return false;
            }
            break;
        case 378:
            if(!impactoCambioEnBD("ALTER TABLE `Documentos`  ADD COLUMN `estadoInformarWeb` CHAR(1) NOT NULL DEFAULT 'C' AFTER `id_web`;","379")){
                _iterador=false; return false;
            }
            break;
        case 379:
            if(!impactoCambioEnBD("ALTER TABLE `Reportes` ADD COLUMN `utilizaProcedenciaEnReporte` CHAR(1) NOT NULL DEFAULT '0' AFTER `utilizaListaPrecio2`;","380")){
                _iterador=false; return false;
            }
            break;
        case 380:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaCodigoCliente`, `utilizaCodigoProveedor`, `utilizaCodigoArticulo`, `utilizaCantidadItemRanking`, `utilizaFecha`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaVendedor`, `utilizaTipoDocumento`, `utilizaSubRubros`, `utilizaCodigoLiquidacionCaja`, `utilizaRubros`, `utilizaDesdeCodigoArticulo`, `utilizaHastaCodigoArticulo`, `utilizaListaPrecio`, `utilizaGraficas`, `utilizaCuentaBancaria`, `utilizaMonedas`, `utilizaPais`, `utilizaDepartamento`, `utilizaLocalidad`, `utilizaCoincidenciaCodigoCliente`, `utilizaOrdenEnReporte`, `utilizaTipoClasificacionCliente`, `utilizaListaPrecio2`,`utilizaProcedenciaEnReporte`) VALUES ('75', '4', 'Ventas entre fecha por procedencia', 'SELECT   concat((case when CLI.razonSocial=\\'\\' then CLI.nombreCliente else CLI.razonSocial end),\\' (\\',DOC.codigoCliente,\\')\\')\\'CLIENTE\\',      sum(case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total $\\',   sum(case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end) \\'Total U$S\\'  ,  TPC.descripcionTipoProcedenciaCliente\\'Procedencia\\'  FROM Documentos DOC    join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento     join Clientes CLI on CLI.codigoCliente=DOC.codigoCliente and CLI.tipoCliente=DOC.tipoCliente    join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento    join TipoProcedenciaCliente TPC on TPC.codigoTipoProcedenciaCliente=CLI.codigoTipoProcedenciaCliente  where  DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\')  and TDOC.esDocumentoDeVenta=\\'1\\'    and  DOC.tipoCliente=1    and DOC.fechaEmisionDocumento  between \\'@_desde\\' and \\'@_hasta\\'    and TPC.codigoTipoProcedenciaCliente=\\'@_codigoProcedenciaClienteReporte\\'  group by DOC.codigoCliente   order by DOC.fechaEmisionDocumento desc;', '', '', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1');","380")){
                if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('75', '1', '2', '1', '', 'MONTO'),('75', '2', '2', '1', '', 'MONTO');","381")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 381:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaCodigoCliente`, `utilizaCodigoProveedor`, `utilizaCodigoArticulo`, `utilizaCantidadItemRanking`, `utilizaFecha`, `utilizaFechaDesde`, `utilizaFechaHasta`, `utilizaVendedor`, `utilizaTipoDocumento`, `utilizaSubRubros`, `utilizaCodigoLiquidacionCaja`, `utilizaRubros`, `utilizaDesdeCodigoArticulo`, `utilizaHastaCodigoArticulo`, `utilizaListaPrecio`, `utilizaGraficas`, `utilizaCuentaBancaria`, `utilizaMonedas`, `utilizaPais`, `utilizaDepartamento`, `utilizaLocalidad`, `utilizaCoincidenciaCodigoCliente`, `utilizaOrdenEnReporte`, `utilizaTipoClasificacionCliente`, `utilizaListaPrecio2`, `utilizaProcedenciaEnReporte`) VALUES ('76', '4', 'Ventas entre fechas por vendedor y artículo', 'select concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\' )\\'Documento (Fecha)\\',  DOC.fechaEmisionDocumento\\'Fecha\\',   sum(case when TDOC.afectaStock=1 then DOCL.cantidad*-1 else  case when TDOC.afectaStock=-1 then DOCL.cantidad else 0 end  end)\\'Cantidad ventas\\'    ,  case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total $\\',     case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total U$S\\'  ,  DOC.codigoVendedorComisiona\\'Vendedor\\'    from Documentos DOC   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento and DOCL.codigoTipoDocumento=DOC.codigoTipoDocumento and DOCL.serieDocumento=DOC.serieDocumento   join Articulos AR on AR.codigoArticulo=DOCL.codigoArticulo     join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'    and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'   and DOCL.codigoArticulo=\\'@_codigoArticulo\\'  and DOC.codigoVendedorComisiona=\\'@_codigoVendedor\\'  group by DOC.codigoDocumento,DOC.codigoTipoDocumento ,DOCL.serieDocumento,DOCL.codigoArticulo order by DOC.fechaEmisionDocumento,DOC.codigoDocumento,DOC.codigoTipoDocumento ,DOCL.serieDocumento;   ', '', '', '0', '0', '1', '0', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0');","381")){
                if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('76', '0', '0', '0', '', 'TEXTO'),('76', '2', '1', '1', '', 'TEXTO'),('76', '3', '2', '1', '', 'MONTO'),('76', '4', '2', '1', '', 'MONTO');","382")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 382:
            if(impactoCambioEnBD("INSERT INTO `Reportes` (`codigoReporte`, `codigoMenuReporte`, `descripcionReporte`, `consultaSql`, `consultaSqlGraficas`, `consultaSqlCabezal`, `utilizaFechaDesde`, `utilizaFechaHasta`) VALUES ('77', '4', 'Ventas Web entre fechas', 'select  concat(DOC.codigoDocumento,\\' - \\',TDOC.descripcionTipoDocumento,\\' (\\',DOC.fechaEmisionDocumento,\\') - CFE: \\',DOC.cae_numeroCae,\\'(\\',DOC.cae_serie,\\')\\' )\\'Documento (Fecha)\\',   DOC.fechaEmisionDocumento\\'Fecha\\',  case when MON.codigoMoneda=1 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total $\\',     case when MON.codigoMoneda=2 then  ROUND(DOC.precioTotalVenta*TDOC.afectaTotales,2)  else ROUND(0,2) end \\'Total U$S\\' from Documentos DOC   join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento   join Monedas MON on MON.codigoMoneda=DOC.codigoMonedaDocumento  where DOC.codigoEstadoDocumento in (\\'G\\',\\'E\\') and TDOC.esDocumentoDeVenta=\\'1\\'   and DOC.esDocumentoWeb =\\'1\\'   and DOC.fechaEmisionDocumento between \\'@_desde\\' and \\'@_hasta\\'   group by DOC.codigoDocumento,DOC.codigoTipoDocumento ,DOC.serieDocumento order by DOC.fechaEmisionDocumento,DOC.codigoDocumento,DOC.codigoTipoDocumento ,DOC.serieDocumento;', '', '', '1', '1');","382")){
                if(!impactoCambioEnBD("INSERT INTO `ReportesConfiguracion` (`codigoReporte`, `columnaReporte`, `alineacionColumna`, `totalizacionColumna`, `textoPieOpcional`, `tipoDatoColumna`) VALUES ('77', '0', '0', '0', '', 'TEXTO'),('77', '2', '2', '1', '', 'MONTO'),('77', '3', '2', '1', '', 'MONTO');","383")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 383:
            if(impactoCambioEnBD("INSERT INTO `Configuracion` (`codigoConfiguracion`, `valorConfiguracion`, `descripcionConfiguracion`) VALUES ('UTILIZA_CONTROL_CLIENTE_CREDITO', '0', 'Habilita el control de clientes credito. Si el esta en 1, el cliente tienen un checkbox que lo habilita a ser credito, y se controla en la facturación.');","383")){
                if(!impactoCambioEnBD("ALTER TABLE `Clientes`  ADD COLUMN `permiteFacturaCredito` CHAR(1) NOT NULL DEFAULT '0' AFTER `fechaUltimoAvisoCumpleanios`;","384")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 384:
            if(impactoCambioEnBD("CREATE TABLE TipoDocumentoImix (nombreTipoDocumentoImix varchar(100) NULL);","384")){
                if(!impactoCambioEnBD("INSERT INTO TipoDocumentoImix VALUES ('Venta contado'),('Venta crédito exenta'),('Venta contado exenta'),('Dev venta exenta'),('NC venta exenta'),('Venta crédito'),('Devolución venta'),('Nota crédito venta');","385")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        case 385:
            if(!impactoCambioEnBD("ALTER TABLE TipoDocumento ADD utilizaComentarios char(1) DEFAULT '0' NOT NULL;","386")){
                _iterador=false; return false;
            }
            break;
        case 386:
            if(!impactoCambioEnBD("ALTER TABLE `Documentos` ADD COLUMN `comentarios` varchar(100) NULL  AFTER `observaciones`;","387")){
                _iterador=false; return false;
            }
            break;
        case 387:
            if(!impactoCambioEnBD("ALTER TABLE Clientes ADD codigoMonedaDefault int(10) unsigned DEFAULT 0 NOT NULL;","388")){
                _iterador=false; return false;
            }
            break;
        case 388:
            if(!impactoCambioEnBD("ALTER TABLE Clientes ADD codigoFormasDePagoDefault int(10) unsigned DEFAULT 0 NOT NULL;","389")){
                _iterador=false; return false;
            }
            break;
        case 389:
            if(impactoCambioEnBD("ALTER TABLE Mantenimientos ADD clientesUsaFormaDePago char(1) DEFAULT '0' NOT NULL;","389")){
                if(!impactoCambioEnBD("ALTER TABLE Mantenimientos ADD clientesUsaMoneda char(1) DEFAULT '0' NOT NULL;","390")){
                    _iterador=false; return false;
                }
            }else{_iterador=false; return false;}
            break;
        //
        //
        //




        default:
            qDebug()<< "Se Finalizan las actualizaciones de base de datos.";
            _iterador=false;
            return true;
            break;
        }
        _valor++;
    }while(_iterador);
}



void ChilkatSample(void)
{
    //  The mailman object is used for sending and receiving email.


}







QString Funciones::verificarCedula(QString pNumero){

    pNumero = pNumero.replace(".","").replace("-","").replace("=","").replace(",","").replace("_","").replace("´","").replace("+","").replace(";","")
            .replace("̣̣⨪","").replace("{","").replace("}","").replace("[","").replace("]","").replace("^","").replace("`","").replace("¨","").replace("¨","")
            .replace("¿","").replace("¡","").replace("¸","").replace("'","").replace("?","").replace("\\","").replace("|","").replace("°","");

    if (pNumero.length() == 8 || pNumero.length() == 7 || pNumero.length() == 9)
    {
        int *_formula = new int[pNumero.length()]{2,9,8,7,6,3,4};

        int _suma = 0;
        int *_numero = new int[9]{0, 0, 0, 0, 0, 0, 0, 0};

        if (pNumero.length() == 8)
        {
            _numero[0] = pNumero.at(0).digitValue();
            _numero[1] = pNumero.at(1).digitValue();
            _numero[2] = pNumero.at(2).digitValue();
            _numero[3] = pNumero.at(3).digitValue();
            _numero[4] = pNumero.at(4).digitValue();
            _numero[5] = pNumero.at(5).digitValue();
            _numero[6] = pNumero.at(6).digitValue();
            _numero[7] = pNumero.at(7).digitValue();
        }


        if (pNumero.length() == 7)
        {
            _numero[0] = 0;
            _numero[1] = pNumero.at(0).digitValue();
            _numero[2] = pNumero.at(1).digitValue();
            _numero[3] = pNumero.at(2).digitValue();
            _numero[4] = pNumero.at(3).digitValue();
            _numero[5] = pNumero.at(4).digitValue();
            _numero[6] = pNumero.at(5).digitValue();
            _numero[7] = pNumero.at(6).digitValue();
        }

        _suma = QString::number(_numero[0] * _formula[0]).right(1).toInt() +
                QString::number(_numero[1] * _formula[1]).right(1).toInt() +
                QString::number(_numero[2] * _formula[2]).right(1).toInt() +
                QString::number(_numero[3] * _formula[3]).right(1).toInt() +
                QString::number(_numero[4] * _formula[4]).right(1).toInt() +
                QString::number(_numero[5] * _formula[5]).right(1).toInt() +
                QString::number(_numero[6] * _formula[6]).right(1).toInt();


        if (pNumero.length() == 9)
        {
            _suma=0;
            _numero[0] = pNumero.at(0).digitValue();
            _numero[1] = pNumero.at(1).digitValue();
            _numero[2] = pNumero.at(2).digitValue();
            _numero[3] = pNumero.at(3).digitValue();
            _numero[4] = pNumero.at(4).digitValue();
            _numero[5] = pNumero.at(5).digitValue();
            _numero[6] = pNumero.at(6).digitValue();
            _numero[7] = pNumero.at(7).digitValue();
            _numero[8] = pNumero.at(8).digitValue();


            _suma = QString::number(_numero[0] * _formula[0]).right(1).toInt() +
                    QString::number(_numero[1] * _formula[0]).right(1).toInt() +
                    QString::number(_numero[2] * _formula[1]).right(1).toInt() +
                    QString::number(_numero[3] * _formula[2]).right(1).toInt() +
                    QString::number(_numero[4] * _formula[3]).right(1).toInt() +
                    QString::number(_numero[5] * _formula[4]).right(1).toInt() +
                    QString::number(_numero[6] * _formula[5]).right(1).toInt() +
                    QString::number(_numero[7] * _formula[6]).right(1).toInt();

        }
        int _resto=0;

        if(pNumero.length() == 8 && _numero[7]==0){

             _resto = ((QString::number(_suma).left(1)+"0").toInt())-_suma;

        }else{
             _resto = ((QString::number(_suma).left(1)+"0").toInt()+10)-_suma;
        }


        if (pNumero.length() == 8 || pNumero.length() == 7 ){
            if (_numero[7] == _resto) {
                return pNumero;
            }
            else{
                mensajeAdvertenciaOk("ATENCION:...Cedula invalida");
                return "-1ERROR";
            }
        }else if(pNumero.length() == 9){
            if (_numero[8] == _resto) {
                return pNumero;
            }
            else{
                mensajeAdvertenciaOk("ATENCION:...Cedula invalida");
                return "-1ERROR";
            }
        }else{
            mensajeAdvertenciaOk("ATENCION:...Cedula con cantidad de digitos incorrectos.");
            return "-1ERROR";
        }
    }else{
        mensajeAdvertenciaOk("ATENCION:...Cedula con cantidad de digitos incorrectos.");
        return "-1ERROR";
    }
}
