/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2022>  <Cristian Montano>

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

#ifndef UTILIDADESDEMENU_H
#define UTILIDADESDEMENU_H

#include <QAbstractListModel>



class Menus
{
public:
   Q_INVOKABLE Menus(const int &codigoMenu, const QString &nombreMenu);

    int codigoMenu() const;
    QString nombreMenu() const;


private:
    int m_codigoMenu;
    QString m_nombreMenu;

};

class UtilidadesDeMenu : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MenusRoles {
        CodigoMenuRole = Qt::UserRole + 1,
        NombreMenuRole
    };

    UtilidadesDeMenu(QObject *parent = 0);

    Q_INVOKABLE void agregarMenu(const Menus &Menus);

    Q_INVOKABLE void limpiarListaMenus();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarMenus(QString , QString);

    Q_INVOKABLE int retornaCodigoMenu(int ) const;


    Q_INVOKABLE QString retornaNombreMenu(int ) const;





private:
    QList<Menus> m_Menus;
};

#endif // UTILIDADESDEMENU_H
