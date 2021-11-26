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

#ifndef MODULOIVAS_H
#define MODULOIVAS_H

#include <QAbstractListModel>

class Ivas
{
public:
   Q_INVOKABLE Ivas(const int &codigoIva, const QString &descripcionIva,const double &porcentajeIva,const double &factorMultiplicador);

    int codigoIva() const;
    QString descripcionIva() const;
    double porcentajeIva() const;
    double factorMultiplicador() const;

private:
    int m_codigoIva;
    QString m_descripcionIva;
    double m_porcentajeIva;
    double m_factorMultiplicador;
};

class ModuloIvas : public QAbstractListModel
{
    Q_OBJECT
public:
    enum IvasRoles {
        CodigoIvaRole = Qt::UserRole + 1,
        DescripcionIvaRole,
        PorcentajeIvaRole,
        FactorMultiplicadorRole
    };

    ModuloIvas(QObject *parent = 0);

    Q_INVOKABLE void agregarIva(const Ivas &Ivas);

    Q_INVOKABLE void limpiarListaIvas();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarIvas(QString , QString);

    Q_INVOKABLE QString retornaDescripcionIva(QString) const;

    Q_INVOKABLE double retornaFactorMultiplicador(QString) const;

    Q_INVOKABLE double retornaFactorMultiplicadorIVAPorDefecto() const;

    Q_INVOKABLE QString retornaCodigoIva(QString) const;




private:
    QList<Ivas> m_Ivas;
};

#endif // MODULOIVAS_H
