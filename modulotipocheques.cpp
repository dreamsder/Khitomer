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
#include "modulotipocheques.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>



ModuloTipoCheques::ModuloTipoCheques(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[codigoTipoChequeRole] = "codigoTipoCheque";
    roles[descripcionTipoChequeRole] = "descripcionTipoCheque";


    setRoleNames(roles);
}


Cheques::Cheques(const int &codigoTipoCheque, const QString &descripcionTipoCheque)
    : m_codigoTipoCheque(codigoTipoCheque), m_descripcionTipoCheque(descripcionTipoCheque)
{
}

int Cheques::codigoTipoCheque() const
{
    return m_codigoTipoCheque;
}
QString Cheques::descripcionTipoCheque() const
{
    return m_descripcionTipoCheque;
}


void ModuloTipoCheques::agregarCheque(const Cheques &cheques)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Cheques << cheques;
    endInsertRows();
}

void ModuloTipoCheques::limpiarListaCheques(){
    m_Cheques.clear();
}

void ModuloTipoCheques::buscarCheques(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from TipoCheque where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloTipoCheques::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloTipoCheques::agregarCheque(Cheques(q.value(rec.indexOf("codigoTipoCheque")).toInt(), q.value(rec.indexOf("descripcionTipoCheque")).toString()));
            }
        }
    }
}

int ModuloTipoCheques::rowCount(const QModelIndex & parent) const {
    return m_Cheques.count();
}

QVariant ModuloTipoCheques::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Cheques.count()){
        return QVariant();

    }

    const Cheques &cheques = m_Cheques[index.row()];

    if (role == codigoTipoChequeRole){
        return cheques.codigoTipoCheque();

    }
    else if (role == descripcionTipoChequeRole){
        return cheques.descripcionTipoCheque();

    }

    return QVariant();
}
QString ModuloTipoCheques::retornaDescripcionCheque(QString _codigoTipoCheque) const{

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

        if(query.exec("select descripcionTipoCheque from TipoCheque where codigoTipoCheque='"+_codigoTipoCheque+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    return query.value(0).toString();
                }else{
                    return "";
                }
            }else{
                return "";
            }
        }else{
            return "";
        }
    }else{
        return "";
    }
}
