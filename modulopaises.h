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

#ifndef MODULOPAISES_H
#define MODULOPAISES_H



#include <QAbstractListModel>

class Pais
{
public:
   Q_INVOKABLE Pais(const int &codigoPais, const QString &descripcionPais);

    int codigoPais() const;
    QString descripcionPais() const;


private:
    int m_codigoPais;
    QString m_descripcionPais;

};

class ModuloPaises : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PaisesRoles {
        CodigoPaisRole = Qt::UserRole + 1,
        DescripcionPaisRole

    };

    ModuloPaises(QObject *parent = 0);

    Q_INVOKABLE void agregarPais(const Pais &Pais);

    Q_INVOKABLE void limpiarListaPaises();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarPaises(QString , QString,QString);

    Q_INVOKABLE QString retornaUltimoCodigoPais() const;

    Q_INVOKABLE bool eliminarPais(QString ) const;

    Q_INVOKABLE int insertarPais(QString ,QString );

    Q_INVOKABLE QString retornaDescripcionPais(QString ) const;







private:
    QList<Pais> m_Paises;
};

#endif // MODULOPAISES_H
