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
#ifndef MODULORUBROS_H
#define MODULORUBROS_H

#include <QAbstractListModel>

class Rubros
{
public:
    Q_INVOKABLE Rubros(const int &codigoRubro, const QString &descripcionRubro);

    int codigoRubro() const;
    QString descripcionRubro() const;


private:
    int m_codigoRubro;
    QString m_descripcionRubro;

};

class ModuloRubros : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RubrosRoles {
        CodigoRubroRole = Qt::UserRole + 1,
        DescripcionRubroRole

    };

    ModuloRubros(QObject *parent = 0);

    Q_INVOKABLE void agregarRubro(const Rubros &Rubros);

    Q_INVOKABLE void limpiarListaRubros();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarRubros(QString , QString);

    Q_INVOKABLE int retornaCantidadSubRubros(QString);

    Q_INVOKABLE QString retornaNombreRubro(QString);

    Q_INVOKABLE int insertarRubro(QString,QString);

    Q_INVOKABLE bool eliminarRubro(QString ) const;

    Q_INVOKABLE int ultimoRegistroDeRubro()const;






private:
    QList<Rubros> m_Rubros;
};


#endif // MODULORUBROS_H
