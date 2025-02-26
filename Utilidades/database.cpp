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

#include "database.h"
#include "QDebug"
#include "QSqlQuery"
#include "QSqlRecord"
#include <Utilidades/utilidadesxml.h>


static QSqlDatabase dbcon= QSqlDatabase::addDatabase("QMYSQL");
static QSqlQuery resultadoConsulta;
static QSqlRecord rec;



Database::Database()
{    
}

QSqlDatabase Database::connect() {

    dbcon.setPort(UtilidadesXml::getPuertoLocal());
    dbcon.setHostName(UtilidadesXml::getHostLocal());
    dbcon.setDatabaseName(UtilidadesXml::getBaseLocal());
    dbcon.setUserName(UtilidadesXml::getUsuarioLocal());
    dbcon.setPassword(UtilidadesXml::getClaveLocal());

    // dbcon.setConnectOptions("CLIENT_SSL=1;CLIENT_IGNORE_SPACE=1;MYSQL_OPT_RECONNECT=true;CLIENT_COMPRESS=1");



    return dbcon;
}
void Database::closeDb() {
    QSqlDatabase::removeDatabase("QMYSQL");
}

QSqlQuery Database::consultaSql(QString _consulta){

    resultadoConsulta = dbcon.exec(_consulta);
    rec = resultadoConsulta.record();

    return resultadoConsulta;
}

bool Database::chequeaStatusAccesoMysql() {

    int randNum = rand()%(1-15 + 1) + 1;

    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            Database::connect().close();
            return false;
        }else{
            if(randNum==7){
                QSqlQuery query = Database::consultaSql("select 1");
                if(query.first()) {
                    return true;
                }else{
                    Database::connect().close();
                    return false;
                }
            }else{
                return true;
            }

        }
    }else{
        if(randNum==7){
            QSqlQuery query = Database::consultaSql("select 1;");
            if(query.first()) {
                return true;
            }else{
                Database::connect().close();
                return false;
            }
        }else{
            return true;
        }

    }
}

bool Database::chequeaStatusAccesoMysqlInicio() {


    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            Database::connect().close();
            return false;
        }else{
            QSqlQuery query = Database::consultaSql("select 1");
            if(query.first()) {
                return true;
            }else{
                Database::connect().close();
                return false;
            }
        }
    }else{
        QSqlQuery query = Database::consultaSql("select 1;");
        if(query.first()) {
            return true;
        }else{
            Database::connect().close();
            return false;
        }
    }
}

