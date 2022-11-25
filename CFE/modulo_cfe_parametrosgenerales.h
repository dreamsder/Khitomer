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

#ifndef MODULO_CFE_PARAMETROSGENERALES_H
#define MODULO_CFE_PARAMETROSGENERALES_H

#include <QAbstractListModel>



class CFE_ParametrosGenerales
{
public:
    Q_INVOKABLE CFE_ParametrosGenerales(const QString &nombreParametro, const QString &valorParametro);

    QString nombreParametro() const;
    QString valorParametro() const;


private:
    QString m_nombreParametro;
    QString m_valorParametro;

};

class Modulo_CFE_ParametrosGenerales : public QAbstractListModel
{
    Q_OBJECT
public:
    enum listaRoles {
        nombreParametroRole = Qt::UserRole + 1,
        valorParametroRole
    };

    Modulo_CFE_ParametrosGenerales(QObject *parent = 0);

    Q_INVOKABLE void agregar(const CFE_ParametrosGenerales &CFE_ParametrosGenerales);

    Q_INVOKABLE void limpiar();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscar(QString , QString);

    Q_INVOKABLE void cargar();

    Q_INVOKABLE QString retornaValor(QString ) const;


    Q_INVOKABLE bool cargarClavePublica() ;
    Q_INVOKABLE bool cargarLogoImpresora();

    Q_INVOKABLE bool actualizarDatoParametroCFE(QString ,QString );

    Q_INVOKABLE bool actualizarDatoParametroCFEImagen(QString ,QString );






    static QString getmodoTrabajoCFE(){return m_modoTrabajoCFE;}
    static QString getpassword(){return m_password;}
    static QString gettoken(){return m_token;}
    static QString geturlEfacturaContado(){return m_urlEfacturaContado;}
    static QString geturlEfacturaCredito(){return m_urlEfacturaCredito;}
    static QString geturlEfacturaNotaCredito(){return m_urlEfacturaNotaCredito;}
    static QString geturlEfacturaNotaDebito(){return m_urlEfacturaNotaDebito;}
    static QString geturlEticketContado(){return m_urlEticketContado;}
    static QString geturlEticketCredito(){return m_urlEticketCredito;}
    static QString geturlEticketNotaCredito(){return m_urlEticketNotaCredito;}
    static QString geturlEticketNotaDebito(){return m_urlEticketNotaDebito;}
    static QString geturlImixProduccion(){return m_urlImixProduccion;}
    static QString geturlImixTesting(){return m_urlImixTesting;}
    static QString geturlWS(){return m_urlWS;}
    static QString getusername(){return m_username;}
    static QString getmodoFuncionCFE(){return m_modoFuncionCFE;}
    static QString getenvioArticuloClienteGenerico(){return m_envioArticuloClienteGenerico;}   
    static QString getenvioClienteGenerico(){return m_envioClienteGenerico;}
    static QString getclaveCifrada(){return m_claveCifrada;}

    static QString geturlDGI(){return m_urlDGI;}

    static QString getlogoImpresoraTicket(){return m_logoImpresoraTicket;}

    static QString getresolucionDGINro(){return m_resolucionDGINro;}

    static QString getarticuloUsaConcatenacionImix(){return m_articuloUsaConcatenacionImix;}


    static QString retornoValorPatrametro(QString _codigoConfiguracion);





private:
    QList<CFE_ParametrosGenerales> m_generico;


    static QString m_modoTrabajoCFE;
    static QString m_password;
    static QString m_token;
    static QString m_urlEfacturaContado;
    static QString m_urlEfacturaCredito;
    static QString m_urlEfacturaNotaCredito;
    static QString m_urlEfacturaNotaDebito;
    static QString m_urlEticketContado;
    static QString m_urlEticketCredito;
    static QString m_urlEticketNotaCredito;
    static QString m_urlEticketNotaDebito;
    static QString m_urlImixProduccion;
    static QString m_urlImixTesting;
    static QString m_urlWS;
    static QString m_username;
    static QString m_modoFuncionCFE;
    static QString m_envioArticuloClienteGenerico;
    static QString m_envioClienteGenerico;


    static QString m_claveCifrada;
    static QString m_urlDGI;
    static QString m_logoImpresoraTicket;
    static QString m_resolucionDGINro;
    static QString m_articuloUsaConcatenacionImix;







    static void setmodoTrabajoCFE(QString value){m_modoTrabajoCFE=value;}
    static void setpassword(QString value){m_password=value;}
    static void settoken(QString value){m_token=value;}
    static void seturlEfacturaContado(QString value){m_urlEfacturaContado=value;}
    static void seturlEfacturaCredito(QString value){m_urlEfacturaCredito=value;}
    static void seturlEfacturaNotaCredito(QString value){m_urlEfacturaNotaCredito=value;}
    static void seturlEfacturaNotaDebito(QString value){m_urlEfacturaNotaDebito=value;}
    static void seturlEticketContado(QString value){m_urlEticketContado=value;}
    static void seturlEticketCredito(QString value){m_urlEticketCredito=value;}
    static void seturlEticketNotaCredito(QString value){m_urlEticketNotaCredito=value;}
    static void seturlEticketNotaDebito(QString value){m_urlEticketNotaDebito=value;}
    static void seturlImixProduccion(QString value){m_urlImixProduccion=value;}
    static void seturlImixTesting(QString value){m_urlImixTesting=value;}
    static void seturlWS(QString value){m_urlWS=value;}
    static void setusername(QString value){m_username=value;}
    static void setmodoFuncionCFE(QString value){m_modoFuncionCFE=value;}
    static void setenvioArticuloClienteGenerico(QString value){m_envioArticuloClienteGenerico=value;}
    static void setenvioClienteGenerico(QString value){m_envioClienteGenerico=value;}


    static void setclaveCifrada(QString value){m_claveCifrada=value;}

    static void seturlDGI(QString value){m_urlDGI=value;}

    static void setlogoImpresoraTicket(QString value){m_logoImpresoraTicket=value;}

    static void setresolucionDGINro(QString value){m_resolucionDGINro=value;}

    static void setarticuloUsaConcatenacionImix(QString value){m_articuloUsaConcatenacionImix=value;}


};

#endif // MODULO_CFE_PARAMETROSGENERALES_H
