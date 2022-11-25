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

#include "utilidadesxml.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QDir>

QString UtilidadesXml::m_usuarioLocal;
QString UtilidadesXml::m_baseLocal;
QString UtilidadesXml::m_claveLocal;
QString UtilidadesXml::m_hostLocal;
int UtilidadesXml::m_puertoLocal;
int UtilidadesXml::m_tipoConexion;
QString UtilidadesXml::m_url;
QString UtilidadesXml::m_hash;
QString filename;


UtilidadesXml::UtilidadesXml()
{

}




bool UtilidadesXml::leerConfiguracionXml(){

    if(QDir::rootPath()=="/"){
        filename = QDir::homePath()+"/.config/Khitomer/conf.xml";
    }else{
        filename = QDir::rootPath()+"/Khitomer/conf.xml";
    }

    if(QFile::exists(filename)){

        QFile file(filename);
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug() << " ERROR   ->>  No se pudo leer el archivo de configuración: " +filename;
            return false;
        }

        QXmlStreamReader read;

        read.setDevice(&file);
        read.readNext();

        while(!read.atEnd()){

            if(read.isStartElement())
            {
                if(read.name() == "CONFIGURACION")
                {
                    read.readNext();

                }else if(read.name() == "ACCESO"){

                    read.readNext();

                }else if(read.name() == "usuario"){


                    UtilidadesXml::setUsuarioLocal(read.readElementText());

                }else if(read.name() == "clave"){

                    UtilidadesXml::setClaveLocal(read.readElementText());

                }else if(read.name() == "base"){

                    UtilidadesXml::setBaseLocal(read.readElementText());

                }else if(read.name() == "host"){

                    UtilidadesXml::setHostLocal(read.readElementText());

                }else if(read.name() == "puerto"){

                    UtilidadesXml::setPuertoLocal(read.readElementText().toInt());

                }else if(read.name() == "tipoConexion"){

                    if(read.readElementText().toInt()==1){
                        UtilidadesXml::setTipoConexion(1);
                    }else{
                        UtilidadesXml::setTipoConexion(0);
                    }

                }else if(read.name() == "url"){

                    UtilidadesXml::setUrl(read.readElementText());

                }else{
                    read.readNext();
                }
            }else{
                read.readNext();
            }
        }
        file.close();

        if(UtilidadesXml::getBaseLocal()!="")
            return true;

    }else{
        /*QMessageBox men;
        men.setText("No exite configuración de acceso para esta terminal.\nContactese con el administrador para solucionar\nel problema.\nLa aplicación se cerrara.");
        men.exec();*/
        return false;
    }
}
