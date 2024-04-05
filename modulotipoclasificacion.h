/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2024>  <Cristian Montano>

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

#ifndef MODULOTIPOCLASIFICACION_H
#define MODULOTIPOCLASIFICACION_H

#include <QAbstractListModel>


class TipoDeClasificacion
{
public:
   Q_INVOKABLE TipoDeClasificacion(const int &codigoTipoClasificacion,const QString &descripcionTipoClasificacion);


    int codigoTipoClasificacion() const;
    QString descripcionTipoClasificacion() const;

private:
    int m_codigoTipoClasificacion;
    QString m_descripcionTipoClasificacion;

};





class ModuloTipoClasificacion : public QAbstractListModel
{
    Q_OBJECT
public:

    enum TipoClasificacionRoles {
        CodigoTipoClasificacionRole = Qt::UserRole + 1,
        DescripcionTipoClasificacionRole


    };

    ModuloTipoClasificacion(QObject *parent = 0);

    Q_INVOKABLE void addTipoClasificacion(const TipoDeClasificacion &TipoDeClasificacion);

    Q_INVOKABLE void clearTipoClasificacion();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarTipoClasificacion(QString , QString);

    Q_INVOKABLE QString primerRegistroDeTipoClasificacionEnBase() const;



private:
    QList<TipoDeClasificacion> m_TipoDeClasificacion;


    
};

#endif // MODULOTIPOCLASIFICACION_H
