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
#ifndef MODULOBANCOS_H
#define MODULOBANCOS_H

#include <QAbstractListModel>


class Bancos
{
public:
   Q_INVOKABLE Bancos(const int &codigoBanco, const QString &descripcionBanco);

    int codigoBanco() const;
    QString descripcionBanco() const;


private:
    int m_codigoBanco;
    QString m_descripcionBanco;

};

class ModuloBancos : public QAbstractListModel
{
    Q_OBJECT
public:
    enum BancosRoles {
        codigoBancoRole = Qt::UserRole + 1,
        descripcionBancoRole
    };

    ModuloBancos(QObject *parent = 0);

    Q_INVOKABLE void agregarBanco(const Bancos &Bancos);

    Q_INVOKABLE void limpiarListaBancos();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarBancos(QString , QString);

    Q_INVOKABLE QString retornaDescripcionBanco(QString) const;

   Q_INVOKABLE  int insertarBanco(QString ,QString );

   Q_INVOKABLE bool eliminarBanco(QString) const;

   Q_INVOKABLE QString retornaUltimoCodigoBanco() const;




private:
    QList<Bancos> m_Bancos;
};


#endif // MODULOBANCOS_H
