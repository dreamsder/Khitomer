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
#ifndef MODULOMODELOSDEIMPRESION_H
#define MODULOMODELOSDEIMPRESION_H


#include <QAbstractListModel>


class ModeloImpresion
{
public:
   Q_INVOKABLE ModeloImpresion(const int &codigoModeloImpresion, const QString &descripcionModeloImpresion);

    int codigoModeloImpresion() const;
    QString descripcionModeloImpresion() const;


private:
    int m_codigoModeloImpresion;
    QString m_descripcionModeloImpresion;

};

class ModuloModelosDeImpresion : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ModeloImpresionRoles {
        codigoModeloImpresionRole = Qt::UserRole + 1,
        descripcionModeloImpresionRole
    };

    ModuloModelosDeImpresion(QObject *parent = 0);

    Q_INVOKABLE void agregarModeloImpresion(const ModeloImpresion &ModeloImpresion);

    Q_INVOKABLE void limpiarListaModeloImpresion();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarModeloImpresion(QString , QString);

    Q_INVOKABLE QString retornaDescripcionModeloImpresion(QString ) const;



private:
    QList<ModeloImpresion> m_ModeloImpresion;
};



#endif // MODULOMODELOSDEIMPRESION_H
