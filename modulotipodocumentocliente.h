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

#ifndef MODULOTIPODOCUMENTOCLIENTE_H
#define MODULOTIPODOCUMENTOCLIENTE_H

#include <QAbstractListModel>


class TipoDocumentoCliente
{
public:
   Q_INVOKABLE TipoDocumentoCliente(const int &codigoTipoDocumentoCliente,const QString &descripcionTipoDocumentoCliente);


    int codigoTipoDocumentoCliente() const;
    QString descripcionTipoDocumentoCliente() const;

private:
    int m_codigoTipoDocumentoCliente;
    QString m_descripcionTipoDocumentoCliente;

};

class ModuloTipoDocumentoCliente : public QAbstractListModel
{
    Q_OBJECT


public:
    enum TipoDocumentoClienteRoles {
        codigoTipoDocumentoClienteRole = Qt::UserRole + 1,
        descripcionTipoDocumentoClienteRole


    };

    ModuloTipoDocumentoCliente(QObject *parent = 0);

    Q_INVOKABLE void add(const TipoDocumentoCliente &TipoDocumentoCliente);

    Q_INVOKABLE void limpiar();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscar(QString , QString);
    Q_INVOKABLE void buscar();

    Q_INVOKABLE QString retornaDescripcionTipoDocumentoCliente(QString) const;




private:
    QList<TipoDocumentoCliente> m_lista;

};



#endif // MODULOTIPODOCUMENTOCLIENTE_H
