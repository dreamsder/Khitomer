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

#include "moduloformasdepago.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>




ModuloFormasDePago::ModuloFormasDePago(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoFormaDePagoRole] = "codigoFormasDePago";
    roles[DescripcionFormaDePagoRole] = "descripcionFormasDePago";

    setRoleNames(roles);
}


FormaDePago::FormaDePago(const int &codigoFormaDePago, const QString &descripcionFormaDePago)
    : m_codigoFormaDePago(codigoFormaDePago), m_descripcionFormaDePago(descripcionFormaDePago)
{
}

int FormaDePago::codigoFormaDePago() const
{
    return m_codigoFormaDePago;
}
QString FormaDePago::descripcionFormaDePago() const
{
    return m_descripcionFormaDePago;
}


void ModuloFormasDePago::agregarFormaDePago(const FormaDePago &formaDePago)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_FormaDePago << formaDePago;
    endInsertRows();
}

void ModuloFormasDePago::limpiarListaFormaDePago(){
    m_FormaDePago.clear();
}

void ModuloFormasDePago::buscarFormaDePago(QString campo, QString datoABuscar){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from FormasDePago where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloFormasDePago::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloFormasDePago::agregarFormaDePago(FormaDePago(q.value(rec.indexOf("codigoFormasDePago")).toInt(), q.value(rec.indexOf("descripcionFormasDePago")).toString()));
            }
        }
    }
}

int ModuloFormasDePago::rowCount(const QModelIndex & parent) const {
    return m_FormaDePago.count();
}

QVariant ModuloFormasDePago::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_FormaDePago.count()){
        return QVariant();

    }

    const FormaDePago &formaDePago = m_FormaDePago[index.row()];

    if (role == CodigoFormaDePagoRole){
        return formaDePago.codigoFormaDePago();

    }
    else if (role == DescripcionFormaDePagoRole){
        return formaDePago.descripcionFormaDePago();

    }

    return QVariant();
}
QString ModuloFormasDePago::retornaDescripcionFormaDePago(QString _codigoFormaDePago) const{

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery query(Database::connect());


        if(query.exec("select descripcionFormasDePago from FormasDePago where codigoFormasDePago='"+_codigoFormaDePago+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{return "";}
        }else{
            return "";
        }
    }else{
        return "";
    }
}

