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

#include "moduloarticulosbarra.h"
#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>
#include <Utilidades/database.h>

ModuloArticulosBarra::ModuloArticulosBarra(QObject *parent)
    : QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[CodigoArticuloInternoRole] = "codigoArticuloInterno";
    roles[CodigoArticuloBarrasRole] = "codigoArticuloBarra";
    setRoleNames(roles);

}


ArticuloBarra::ArticuloBarra(const QString &codigoArticuloBarras, const QString &codigoArticuloInterno)
    : m_codigoArticuloBarras(codigoArticuloBarras), m_codigoArticuloInterno(codigoArticuloInterno)
{
}

QString ArticuloBarra::codigoArticuloBarras() const
{
    return m_codigoArticuloBarras;
}
QString ArticuloBarra::codigoArticuloInterno() const
{
    return m_codigoArticuloInterno;
}


void ModuloArticulosBarra::addArticuloBarra(const ArticuloBarra &articuloBarra)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ArticulosBarra << articuloBarra;
    endInsertRows();
}

void ModuloArticulosBarra::clearArticulosBarra(){
    m_ArticulosBarra.clear();
}

void ModuloArticulosBarra::buscarArticuloBarra(QString _codigoArticuloInterno){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from ArticulosBarras where codigoArticuloInterno = "+_codigoArticuloInterno);
        QSqlRecord rec = q.record();

        ModuloArticulosBarra::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloArticulosBarra::addArticuloBarra(ArticuloBarra(q.value(rec.indexOf("codigoArticuloBarras")).toString(), q.value(rec.indexOf("codigoArticuloInterno")).toString()));
            }
        }
    }
}

int ModuloArticulosBarra::rowCount(const QModelIndex & parent) const {
    return m_ArticulosBarra.count();
}

QVariant ModuloArticulosBarra::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_ArticulosBarra.count()){
        return QVariant();
    }
    const ArticuloBarra &articuloBarra = m_ArticulosBarra[index.row()];

    if (role == CodigoArticuloInternoRole){
        return articuloBarra.codigoArticuloInterno();
    }else if (role == CodigoArticuloBarrasRole){
        return articuloBarra.codigoArticuloBarras();
    }
    return QVariant();
}

QString ModuloArticulosBarra::retornarCodigoBarras(int indice, QString  _codigoArticuloInterno) const{

int contador=0;
int totalm_ArticulosBarra=m_ArticulosBarra.count();

    for(int i=0;i<totalm_ArticulosBarra;i++){
        if(m_ArticulosBarra[i].codigoArticuloInterno()==_codigoArticuloInterno){
            if(contador==indice){
                return m_ArticulosBarra[i].codigoArticuloBarras();
            }
            contador++;
        }
    }
    return "";
}

int ModuloArticulosBarra::insertarArticuloBarra(QString _codigoArticuloBarras,QString _codigoArticuloInterno) const {

    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el articulo
    // 1  articulo dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar el articulo
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El articulo no tiene los datos sufucientes para darse de alta.

    if(_codigoArticuloBarras.trimmed()=="" || _codigoArticuloInterno.trimmed()==""){
        return -5;
    }

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

        if(query.exec("insert INTO ArticulosBarras (codigoArticuloBarras,codigoArticuloInterno) values('"+_codigoArticuloBarras+"','"+_codigoArticuloInterno+"')")){
            return 1;
        }else{
            return -3;
        }
    }else{
        return -1;
    }
}

bool ModuloArticulosBarra::eliminarArticuloBarra(QString _codigoArticuloInterno) const {

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

        if(query.exec("delete from ArticulosBarras where codigoArticuloInterno='"+_codigoArticuloInterno+"'")){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}
