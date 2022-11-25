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

#ifndef FUNCIONESMYSQL_H
#define FUNCIONESMYSQL_H

#include <QObject>

//#include <QStandardItemModel>

class Funciones : public QObject
{
    Q_OBJECT
public:
    explicit Funciones(QObject *parent = 0);
    int cantidaddeRegistros;


signals:


public slots:


    Q_INVOKABLE bool verificoConexionBaseDeDatos();

    Q_INVOKABLE QString fechaDeHoy();

    Q_INVOKABLE QString fechaHoraDeHoy();

    Q_INVOKABLE QString fechaDeHoyCFE();


    Q_INVOKABLE QString fechaHoraDeHoyTrimeado();


    Q_INVOKABLE QString impresoraPorDefecto();

    Q_INVOKABLE bool mensajeAdvertencia(QString)const;

    Q_INVOKABLE bool mensajeAdvertenciaOk(QString mensaje) const;

    Q_INVOKABLE bool consutlaMysqlEstaViva();

    Q_INVOKABLE void reseteaConexionMysql();

    Q_INVOKABLE bool consultaPingServidor();

    Q_INVOKABLE qlonglong versionDeBaseDeDatos() const;

    bool actualizacionBaseDeDatos(qlonglong) const;

    bool impactoCambioEnBD(QString ,QString ) const;

    Q_INVOKABLE void abrirPaginaWeb(QString)const;

    Q_INVOKABLE QString retornaFechaImportante();

    Q_INVOKABLE bool guardarConfiguracionXML(QString, QString, QString, QString , QString );

    Q_INVOKABLE QString verificarCedula(QString);



    Q_INVOKABLE void loguear(QString);

    Q_INVOKABLE QString retornaNombreLog();
    Q_INVOKABLE QString retornaDirectorioLog();

    Q_INVOKABLE QString leerLog();

    void depurarLog();


    
};

#endif // FUNCIONESMYSQL_H
