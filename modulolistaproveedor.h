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


//#ifndef MODULOCLIENTES_H
//#define MODULOCLIENTES_H

#include <QAbstractListModel>
#include <QStringList>

class ListaProveedor
{
public:
   Q_INVOKABLE ListaProveedor(const QString &codigoClienteProveedor, const int &tipoClienteProveedor, const QString &nombreClienteProveedor,const QString &razonSocialProveedor);


    QString codigoClienteProveedor() const;
    int tipoClienteProveedor() const;
    QString nombreClienteProveedor() const;
    QString razonSocialProveedor() const;

private:
    QString m_codigoClienteProveedor;
    int m_tipoClienteProveedor;
    QString m_nombreClienteProveedor;
    QString m_razonSocialProveedor;

};

class ModuloListaProveedor : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ListaProveedorRoles {
        CodigoClienteProveedorRole = Qt::UserRole + 1,
        TipoClienteProveedorRole,
        NombreClienteProveedorRole,
        RazonSocialProveedorRole


    };

    ModuloListaProveedor(QObject *parent = 0);

    Q_INVOKABLE void addCliente(const ListaProveedor &ListaProveedor);

    Q_INVOKABLE void clearClientes();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarCliente(QString , QString);

    Q_INVOKABLE QString primerRegistroDeProveedorCodigoEnBase() const;

     Q_INVOKABLE QString primerRegistroDeProveedorNombreEnBase(QString) const;

private:
    QList<ListaProveedor> m_ListaProveedor;


};

//#endif // MODULOCLIENTES_H
