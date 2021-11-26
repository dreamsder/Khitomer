#include "wsdatabase.h"
#include <Utilidades/utilidadesxml.h>
#include <funciones.h>




#include <QtNetwork>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QBitArray>
#include <json/json.h>
#include <QDebug>

#include <QMap>
#include <QMapIterator>
#include <QString>
#include <QList>
#include <QMessageBox>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLayout>

#include "waitingdlg.h"


QString mensajeError="";
Funciones funcionesWsDatabase;


WSDatabase::WSDatabase()
{
}

QVariant WSDatabase::wsSelect(QString sql){

    if(UtilidadesXml::getTipoConexion()!=1)
        return "-1";

    if(UtilidadesXml::getHash().trimmed()=="")
        return "-1";


    QNetworkAccessManager nam;
    QNetworkReply *reply;
    QtJson::JsonObject json;

    bool errores=true;

    WaitingDlg dialogo("Consultando la base de datos...");
    dialogo.show();
    mensajeError="";

    QNetworkRequest request(QUrl(UtilidadesXml::getUrl()));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json;charset=UTF-8");

    json.insert("SELECT",sql);
    json.insert("HASH",sql);

    reply = nam.post(request, QtJson::serialize(json));

    uint i = 1;
    while(!reply->isFinished()){
        qApp->processEvents();
        dialogo.setValorPbar(i++);
        if(i==350500)
            i=1;

        if(i==40000){
            dialogo.setMinimumHeight(200);
            dialogo.setMaximumHeight(200);
        }
    }
    qDebug()<< reply->error();

    qDebug()<< reply->readAll();

    if(reply->error()==0){
        errores=false;
    }else if(reply->error()==1){
        mensajeError= "El servidor remoto rechazó la conexión (el servidor no acepta solicitudes o esta apagado)";
    }else if(reply->error()==2){
        mensajeError= "El servidor remoto cerró la conexión prematuramente, antes de que se recibiera y procesara toda la respuesta";
    }else if(reply->error()==3){
        mensajeError= "No se encontró el nombre de host remoto (nombre de host no válido)";
    }else if(reply->error()==4){
        mensajeError= "Se agotó el tiempo de espera de la conexión al servidor remoto";
    }else if(reply->error()==5){
        mensajeError= "La operación se canceló mediante llamadas a abort () o close () antes de que finalizara.";
    }else if(reply->error()==6){
        mensajeError= "El protocolo de enlace SSL/TLS falló y no se pudo establecer el canal cifrado. Se debería haber emitido la señal sslErrors ().";
    }else if(reply->error()==7){
        mensajeError= "La conexión se interrumpió debido a la desconexión de la red; sin embargo, el sistema ha iniciado la itinerancia a otro punto de acceso. La solicitud debe volver a enviarse y se procesará tan pronto como se restablezca la conexión.";
    }else if(reply->error()==201){
        mensajeError= "Se denegó el acceso al contenido remoto (similar al error HTTP 401)";
    }else if(reply->error()==202){
        mensajeError= "La operación solicitada en el contenido remoto no está permitida";
    }else if(reply->error()==203){
        mensajeError= "El contenido remoto no se encontró en el servidor (similar al error HTTP 404)";
    }else if(reply->error()==204){
        mensajeError= "El servidor remoto requiere autenticación para entregar el contenido, pero las credenciales proporcionadas no fueron aceptadas (si las hay)";
    }else if(reply->error()==205){
        mensajeError= "Era necesario enviar la solicitud de nuevo, pero esto falló, por ejemplo, porque los datos de carga no se pudieron leer por segunda vez.";
    }else if(reply->error()==301){
        mensajeError= "No hay una configuración de acceso al Web Service establecida o \nla API de acceso a la red no puede cumplir con la solicitud porque no se conoce el protocolo";
    }else if(reply->error()==302){
        mensajeError= "La operación solicitada no es válida para este protocolo";
    }else if(reply->error()==99){
        mensajeError= "Se detectó un error desconocido relacionado con la red";
    }else if(reply->error()==299){
        mensajeError= "Se detectó un error desconocido relacionado con el contenido remoto";
    }else if(reply->error()==399){
        mensajeError= "Se detectó una falla en el protocolo (error de análisis, respuestas no válidas o inesperadas, etc.)";
    }else{
        mensajeError= "Existe un error no contemplado que no permite continuar con la operación.";
    }


    if(errores){
        dialogo.close();
        funcionesWsDatabase.mensajeAdvertenciaOk(mensajeError);
        return "-1";
    }else{
        QByteArray resultado= reply->readAll();
        qDebug()<< resultado;

        dialogo.close();
        return "";
    }

}
