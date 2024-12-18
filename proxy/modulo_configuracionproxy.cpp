#include "modulo_configuracionproxy.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include <QDebug>
#include <funciones.h>



Modulo_ConfiguracionProxy::Modulo_ConfiguracionProxy(QObject *parent) : QObject(parent)
{

}



QString Modulo_ConfiguracionProxy::retornoValorPatrametro(QString _codigoConfiguracion){

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

        if(query.exec("select valorConfiguracion from ConfiguracionProxy where codigoConfiguracion='"+_codigoConfiguracion+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{
                return "";
            }
        }else{
            return "";
        }
    }else{
        return "";
    }

}
