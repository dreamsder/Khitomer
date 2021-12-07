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
#include "controlesmantenimientos.h"
#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>
#include <Utilidades/database.h>

ControlesMantenimientos::ControlesMantenimientos(QObject *parent)
    : QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[codigoTipoMantenimientoRole] = "codigoTipoMantenimiento";

    setRoleNames(roles);
}
Mantenimientos::Mantenimientos(const QString &codigoTipoMantenimiento)
    :m_codigoTipoMantenimiento(codigoTipoMantenimiento)
{
}
QString Mantenimientos::codigoTipoMantenimiento() const
{
    return m_codigoTipoMantenimiento;
}
int ControlesMantenimientos::rowCount(const QModelIndex & parent) const {
    return m_Mantenimientos.count();
}

QVariant ControlesMantenimientos::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Mantenimientos.count()){
        return QVariant();
    }
    const Mantenimientos &mantenimientos = m_Mantenimientos[index.row()];

    if (role == codigoTipoMantenimientoRole){
        return mantenimientos.codigoTipoMantenimiento();
    }
    return QVariant();
}
bool ControlesMantenimientos::retornaValorMantenimiento(QString _codigoMantenimiento) const{

    Database::chequeaStatusAccesoMysql();

    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            return false;
        }
    }
    QSqlQuery query(Database::connect());
    if(query.exec("select "+_codigoMantenimiento+" from Mantenimientos")) {
        if(query.first()){
            if(query.value(0).toString()!=""){
                if(query.value(0).toString()=="1"){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
    }else{
        return false;
    }
}
