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
#ifndef MODULOCUENTASBANCARIAS_H
#define MODULOCUENTASBANCARIAS_H

#include <QAbstractListModel>



class CuentasBancarias
{
public:
   Q_INVOKABLE CuentasBancarias(const QString &numeroCuentaBancaria, const int &codigoBanco,const QString &descripcionCuentaBancaria,const QString &observaciones);

    QString numeroCuentaBancaria() const;
    int codigoBanco() const;
    QString descripcionCuentaBancaria() const;
    QString observaciones() const;

private:
    QString m_numeroCuentaBancaria;
    int m_codigoBanco;
    QString m_descripcionCuentaBancaria;
    QString m_observaciones;
};

class ModuloCuentasBancarias : public QAbstractListModel
{
    Q_OBJECT
public:
    enum CuentasBancariasRoles {
        numeroCuentaBancariaRole = Qt::UserRole + 1,
        codigoBancoRole,
        descripcionCuentaBancariaRole,
        observacionesRole
    };

    ModuloCuentasBancarias(QObject *parent = 0);

    Q_INVOKABLE void agregarCuentaBancaria(const CuentasBancarias &CuentasBancarias);

    Q_INVOKABLE void limpiarListaCuentasBancarias();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarCuentasBancarias(QString , QString);

    Q_INVOKABLE bool eliminarCuentaBancaria(QString ,QString) const;

    Q_INVOKABLE int insertarCuentaBancaria(QString ,QString ,QString ,QString );

    Q_INVOKABLE QString retornaPrimeraCuentaBancariaDisponible()const;

    Q_INVOKABLE QString retornaBancoCuentaBancaria(QString )const;

    Q_INVOKABLE QString retornaTotalXMonedaCuentaBancaria(QString , QString ,QString )const;




private:
    QList<CuentasBancarias> m_CuentasBancarias;
};

#endif // MODULOCUENTASBANCARIAS_H
