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

#include "utilidadesdemenu.h"
#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>
#include <Utilidades/database.h>

UtilidadesDeMenu::UtilidadesDeMenu(QObject *parent)
    : QAbstractListModel(parent)
{


    QHash<int, QByteArray> roles;
    roles[CodigoMenuRole] = "codigoMenu";
    roles[NombreMenuRole] = "nombreMenu";

    setRoleNames(roles);

}


Menus::Menus(const int &codigoMenu, const QString &nombreMenu)
    : m_codigoMenu(codigoMenu), m_nombreMenu(nombreMenu)
{
}

int Menus::codigoMenu() const
{
    return m_codigoMenu;
}
QString Menus::nombreMenu() const
{
    return m_nombreMenu;
}


void UtilidadesDeMenu::agregarMenu(const Menus &menu)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Menus << menu;
    endInsertRows();
}

void UtilidadesDeMenu::limpiarListaMenus(){
    m_Menus.clear();
}

void UtilidadesDeMenu::buscarMenus(QString campo, QString datoABuscar){

    Database::chequeaStatusAccesoMysql();
    bool conexion=true;
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery q = Database::consultaSql("select * from MenuSistema where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();


        UtilidadesDeMenu::reset();
        if(q.record().count()>0){

            while (q.next()){
                UtilidadesDeMenu::agregarMenu(Menus(q.value(rec.indexOf("codigoMenu")).toInt(), q.value(rec.indexOf("nombreMenu")).toString()));
            }
        }
    }
}

int UtilidadesDeMenu::rowCount(const QModelIndex & parent) const {
    return m_Menus.count();
}

QVariant UtilidadesDeMenu::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Menus.count()){
        return QVariant();
    }
    const Menus &menu = m_Menus[index.row()];

    if (role == CodigoMenuRole){
        return menu.codigoMenu();
    }
    else if (role == NombreMenuRole){
        return menu.nombreMenu();
    }

    return QVariant();
}
int UtilidadesDeMenu::retornaCodigoMenu(int indice) const{
    return m_Menus[indice].codigoMenu();
}
QString UtilidadesDeMenu::retornaNombreMenu(int indice) const{
    return m_Menus[indice].nombreMenu();
}

