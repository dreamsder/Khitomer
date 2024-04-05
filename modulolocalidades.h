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
#ifndef MODULOLOCALIDADES_H
#define MODULOLOCALIDADES_H

#include <QAbstractListModel>

class Localidad
{
public:
   Q_INVOKABLE Localidad(const int &codigoLocalidad, const QString &descripcionLocalidad,const int &codigoDepartamento,const int &codigoPais);

    int codigoLocalidad() const;
    QString descripcionLocalidad() const;

    int codigoDepartamento() const;
    int codigoPais() const;

private:
    int m_codigoLocalidad;
    QString m_descripcionLocalidad;
    int m_codigoDepartamento;
    int m_codigoPais;

};

class ModuloLocalidades : public QAbstractListModel
{
    Q_OBJECT
public:
    enum LocalidadesRoles {
        CodigoLocalidadRole = Qt::UserRole + 1,
        DescripcionLocalidadRole,
        CodigoDepartamentoRole,
        CodigoPaisRole

    };

    ModuloLocalidades(QObject *parent = 0);

    Q_INVOKABLE void agregarLocalidad(const Localidad &Localidad);

    Q_INVOKABLE void limpiarListaLocalidades();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarLocalidades(QString , QString);

    Q_INVOKABLE QString retornaDescripcionLocalidad(QString ,QString ,QString ) const;

    Q_INVOKABLE QString retornaUltimoCodigoLocalidad(QString ,QString) const;

    Q_INVOKABLE int insertarLocalidad(QString ,QString ,QString ,QString );

    Q_INVOKABLE bool eliminarLocalidad(QString ,QString ,QString ) const;





private:
    QList<Localidad> m_Localidades;
};

#endif // MODULOLOCALIDADES_H
