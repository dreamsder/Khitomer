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
#include "modulobancos.h"
#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>



ModuloBancos::ModuloBancos(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[codigoBancoRole] = "codigoBanco";
    roles[descripcionBancoRole] = "descripcionBanco";


    setRoleNames(roles);
}


Bancos::Bancos(const int &codigoBanco, const QString &descripcionBanco)
    : m_codigoBanco(codigoBanco), m_descripcionBanco(descripcionBanco)
{
}

int Bancos::codigoBanco() const
{
    return m_codigoBanco;
}
QString Bancos::descripcionBanco() const
{
    return m_descripcionBanco;
}


void ModuloBancos::agregarBanco(const Bancos &bancos)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Bancos << bancos;
    endInsertRows();
}

void ModuloBancos::limpiarListaBancos(){
    m_Bancos.clear();
}

void ModuloBancos::buscarBancos(QString campo, QString datoABuscar){

    bool conexion=true;
Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from Bancos where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloBancos::reset();
        if(q.record().count()>0){

            while (q.next()){
                ModuloBancos::agregarBanco(Bancos(q.value(rec.indexOf("codigoBanco")).toInt(), q.value(rec.indexOf("descripcionBanco")).toString()));
            }
        }
    }
}

int ModuloBancos::rowCount(const QModelIndex & parent) const {
    return m_Bancos.count();
}

QVariant ModuloBancos::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Bancos.count()){
        return QVariant();

    }

    const Bancos &bancos = m_Bancos[index.row()];

    if (role == codigoBancoRole){
        return bancos.codigoBanco();

    }
    else if (role == descripcionBancoRole){
        return bancos.descripcionBanco();

    }

    return QVariant();
}
QString ModuloBancos::retornaDescripcionBanco(QString _codigoBanco) const{

    QString _valor="";
    for (int var = 0; var < m_Bancos.size(); ++var) {
        if(QString::number(m_Bancos[var].codigoBanco())==_codigoBanco ){

            _valor= m_Bancos[var].descripcionBanco();

        }
    }
    return _valor;

    /*
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

        if(query.exec("select descripcionBanco from Bancos where codigoBanco='"+_codigoBanco+"'")) {
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
    }*/
}

QString ModuloBancos::retornaUltimoCodigoBanco() const{
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


        if(query.exec("select codigoBanco from Bancos order by codigoBanco desc limit 1")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    return QString::number(query.value(0).toInt()+1);
                }else{
                    return "1";
                }
            }else{return "1";}
        }else{
            return "1";
        }
    }else{
        return "1";
    }
}
bool ModuloBancos::eliminarBanco(QString _codigoBanco) const {

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
        if(query.exec("select codigoBanco from Bancos where codigoBanco='"+_codigoBanco+"'")) {
            if(query.first()){
                if(query.value(0).toString()!=""){
                    if(query.exec("delete from Bancos where codigoBanco='"+_codigoBanco+"'")){
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    return false;
                }
            }else{return false;}
        }else{
            return false;
        }
    }else{
        return false;
    }
}
int ModuloBancos::insertarBanco(QString _codigoBanco,QString _nombreBanco){
    // -1  No se pudo conectar a la base de datos.
    // -2  No se pudo actualizar el banco.
    // 1  banco dado de alta ok.
    // 2  Actualizacion correcta.
    // -3  no se pudo insertar el banco.
    // -4 no se pudo realizar la consulta a la base de datos.
    // -5 El banco no tiene los datos sufucientes para darse de alta.

    if(_codigoBanco.trimmed()=="" || _nombreBanco.trimmed()=="" ){
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



            if(query.exec("select codigoBanco from Bancos where codigoBanco='"+_codigoBanco+"'")) {

                if(query.first()){
                    if(query.value(0).toString()!=""){

                        if(query.exec("update Bancos set descripcionBanco='"+_nombreBanco+"'  where codigoBanco='"+_codigoBanco+"'")){
                            return 2;
                        }else{
                            return -2;
                        }
                    }else{
                        return -4;
                    }
                }else{
                    if(query.exec("insert INTO Bancos (codigoBanco,descripcionBanco) values('"+_codigoBanco+"','"+_nombreBanco+"')")){
                        return 1;
                    }else{
                        return -3;
                    }
                }
            }else{
                return -4;
            }
    }else{
        return -1;
    }
}
