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

#ifndef MODULOLIMITESALDOCUENTACORRIENTE_H
#define MODULOLIMITESALDOCUENTACORRIENTE_H

#include <QAbstractListModel>

class LimiteSaldoCuentaCorriente
{
public:
   Q_INVOKABLE LimiteSaldoCuentaCorriente(const QString &codigoCliente, const QString &tipoCliente,const QString &codigoMoneda,const double &limiteSaldo);


    QString codigoCliente() const;
    QString tipoCliente() const;
    QString codigoMoneda() const;
    double limiteSaldo() const;

private:
    QString m_codigoCliente;
    QString m_tipoCliente;
    QString m_codigoMoneda;
    double m_limiteSaldo;
};

class ModuloLimiteSaldoCuentaCorriente : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ItemRoles {
        codigoClienteRole = Qt::UserRole + 1,
        tipoClienteRole,
        codigoMonedaRole,
        limiteSaldoRole
    };

    ModuloLimiteSaldoCuentaCorriente(QObject *parent = 0);

    Q_INVOKABLE void agregar(const LimiteSaldoCuentaCorriente &limiteSaldoCuentaCorriente);

    Q_INVOKABLE void limpiar();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscar(QString _codigoCliente, QString _tipoCliente);

    Q_INVOKABLE QVariantMap get(int row) const;
    Q_INVOKABLE int insertar(QString _codigoCliente, QString _tipoCliente, QString _codigoMoneda, QString _limiteSaldo) const;



private:
    QList<LimiteSaldoCuentaCorriente> m_LimiteSaldoCuentaCorriente;
};

#endif // MODULOLIMITESALDOCUENTACORRIENTE_H

