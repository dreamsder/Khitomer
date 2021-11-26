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

#ifndef UTILIDADESXML_H
#define UTILIDADESXML_H

#include <QString>


class UtilidadesXml
{    

public:

    static bool leerConfiguracionXml();

    static QString getUsuarioLocal(){
        return m_usuarioLocal;
    }
    static QString getClaveLocal(){
        return m_claveLocal;
    }
    static QString getBaseLocal(){
        return m_baseLocal;
    }
    static int getPuertoLocal(){
        return m_puertoLocal;
    }
    static QString getHostLocal(){
        return m_hostLocal;
    }
    static int getTipoConexion(){
        return m_tipoConexion;
    }
    static QString getUrl(){
        return m_url;
    }
    static QString getHash(){
        return m_hash;
    }

    static void setHash(QString value){
        m_hash=value;
    }

private:
   UtilidadesXml();

    static QString m_usuarioLocal;
    static QString m_claveLocal;
    static QString m_baseLocal;
    static int m_puertoLocal;
    static QString m_hostLocal;
    static int m_tipoConexion;
    static QString m_url;
    static QString m_hash;

    static void setUsuarioLocal(QString value){
        m_usuarioLocal=value;
    }
    static void setClaveLocal(QString value){
        m_claveLocal=value;
    }
    static void setBaseLocal(QString value){
        m_baseLocal=value;
    }
    static void setPuertoLocal(int value){
        m_puertoLocal=value;
    }
    static void setHostLocal(QString value){
        m_hostLocal=value;
    }
    static void setTipoConexion(int value){
        m_tipoConexion=value;
    }
    static void setUrl(QString value){
        m_url=value;
    }


};
#endif // UTILIDADESXML_H
