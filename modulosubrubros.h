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
#ifndef MODULOSUBRUBROS_H
#define MODULOSUBRUBROS_H

#include <QAbstractListModel>


class SubRubros
{
public:
    Q_INVOKABLE SubRubros(const int &codigoSubRubro, const int &codigoRubro, const QString &descripcionSubRubro);

    int codigoSubRubro() const;
    int codigoRubro() const;
    QString descripcionSubRubro() const;


private:
    int m_codigoSubRubro;
    int m_codigoRubro;
    QString m_descripcionSubRubro;

};

class ModuloSubRubros : public QAbstractListModel
{
    Q_OBJECT
public:
    enum SubRubrosRoles {
        CodigoSubRubroRole = Qt::UserRole + 1,
        CodigoRubroRole,
        DescripcionSubRubroRole

    };

    ModuloSubRubros(QObject *parent = 0);

    Q_INVOKABLE void agregarSubRubros(const SubRubros &SubRubros);

    Q_INVOKABLE void limpiarListaSubRubros();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarSubRubros(QString , QString);

    Q_INVOKABLE QString retornaDescripcionSubRubro(QString);

    Q_INVOKABLE int ultimoRegistroDeSubRubro()const;

    Q_INVOKABLE bool eliminarSubRubro(QString ) const;

    Q_INVOKABLE int insertarSubRubro(QString ,QString ,QString );




private:
    QList<SubRubros> m_SubRubros;
};

#endif // MODULOSUBRUBROS_H
