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

#include "moduloivas.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>



ModuloIvas::ModuloIvas(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[CodigoIvaRole] = "codigoIva";
    roles[DescripcionIvaRole] = "descripcionIva";
    roles[PorcentajeIvaRole] = "porcentajeIva";
    roles[FactorMultiplicadorRole] = "factorMultiplicador";

    setRoleNames(roles);
}


Ivas::Ivas(const int &codigoIva, const QString &descripcionIva,const double &porcentajeIva,const double &factorMultiplicador)
    : m_codigoIva(codigoIva), m_descripcionIva(descripcionIva), m_porcentajeIva(porcentajeIva), m_factorMultiplicador(factorMultiplicador)
{
}

int Ivas::codigoIva() const
{
    return m_codigoIva;
}
QString Ivas::descripcionIva() const
{
    return m_descripcionIva;
}
double Ivas::porcentajeIva() const
{
    return m_porcentajeIva;
}
double Ivas::factorMultiplicador() const
{
    return m_factorMultiplicador;
}


void ModuloIvas::agregarIva(const Ivas &ivas)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Ivas << ivas;
    endInsertRows();
}

void ModuloIvas::limpiarListaIvas(){
    m_Ivas.clear();
}

void ModuloIvas::buscarIvas(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from Ivas where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloIvas::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloIvas::agregarIva(Ivas(q.value(rec.indexOf("codigoIva")).toInt(), q.value(rec.indexOf("descripcionIva")).toString(), q.value(rec.indexOf("porcentajeIva")).toDouble(), q.value(rec.indexOf("factorMultiplicador")).toDouble()));
            }
        }
    }
}

int ModuloIvas::rowCount(const QModelIndex & parent) const {
    return m_Ivas.count();
}

QVariant ModuloIvas::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Ivas.count()){
        return QVariant();

    }

    const Ivas &ivas = m_Ivas[index.row()];

    if (role == CodigoIvaRole){
        return ivas.codigoIva();

    }
    else if (role == DescripcionIvaRole){
        return ivas.descripcionIva();

    }
    else if (role == PorcentajeIvaRole){
        return ivas.porcentajeIva();

    }

    return QVariant();
}
QString ModuloIvas::retornaDescripcionIva(QString _codigoIva) const{

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


        if(query.exec("select descripcionIva from Ivas where codigoIva='"+_codigoIva+"'")) {
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


double ModuloIvas::retornaFactorMultiplicador(QString _codigoArticulo) const{
    bool conexion=true;
    QString _codigoIva;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery query(Database::connect());

        if(query.exec("select codigoIva from Articulos where codigoArticulo='"+_codigoArticulo+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    _codigoIva = query.value(0).toString();

                    if(query.exec("select factorMultiplicador from Ivas where codigoIva='"+_codigoIva+"'")) {
                        if(query.first()){
                            if(query.value(0).toString()!=""){
                                return query.value(0).toDouble();
                            }else{
                                return 1;
                            }
                        }else{return 1;}
                    }else{
                        return 1;
                    }
                }else{
                    return 1;
                }
            }
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}


double ModuloIvas::retornaFactorMultiplicadorIVAPorDefecto() const{
    bool conexion=true;
    QString _codigoIva;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }
    if(conexion){

        QSqlQuery query(Database::connect());

        if(query.exec("select valorConfiguracion from Configuracion where codigoConfiguracion='IVA_DEFAULT_SISTEMA'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    _codigoIva = query.value(0).toString();

                    if(query.exec("select factorMultiplicador from Ivas where codigoIva='"+_codigoIva+"'")) {
                        if(query.first()){
                            if(query.value(0).toString()!=""){
                                return query.value(0).toDouble();
                            }else{
                                return 1;
                            }
                        }else{return 1;}
                    }else{
                        return 1;
                    }
                }else{
                    return 1;
                }
            }
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}



QString ModuloIvas::retornaCodigoIva(QString _codigoArticulo) const{
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


        if(query.exec("select codigoIva from Articulos where codigoArticulo='"+_codigoArticulo+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){

                    return query.value(0).toString();

                }else{
                    return "0";
                }
            }else{return "0";}
        }else{
            return "0";
        }
    }else{
        return "0";
    }
}
