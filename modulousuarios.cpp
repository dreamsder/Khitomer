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

#include "modulousuarios.h"
#include <QtSql>
#include <QCryptographicHash>
#include <Utilidades/database.h>
#include <Utilidades/wsdatabase.h>



ModuloUsuarios::ModuloUsuarios(QObject *parent)
    : QAbstractListModel(parent)
{

    QHash<int, QByteArray> roles;
    roles[IdUsuarioRole] = "idUsuario";
    roles[NombreUsuarioRole] = "nombreUsuario";
    roles[ApellidoUsuarioRole] = "apellidoUsuario";
    roles[TipoUsuarioRole] = "tipoUsuario";
    roles[EsVendedorRole] = "esVendedor";
    roles[CodigoPerfilRole] = "codigoPerfil";
    setRoleNames(roles);
}


Usuarios::Usuarios(const QString &idUsuario,const QString &nombreUsuario,const QString &apellidoUsuario,const int &tipoUsuario,const QString &esVendedor,const int &codigoPerfil)

    : m_idUsuario(idUsuario),m_nombreUsuario(nombreUsuario),m_apellidoUsuario(apellidoUsuario),m_tipoUsuario(tipoUsuario),m_esVendedor(esVendedor),m_codigoPerfil(codigoPerfil)
{


}


QString Usuarios::idUsuario() const
{
    return m_idUsuario;
}
QString Usuarios::nombreUsuario() const
{
    return m_nombreUsuario;
}

QString Usuarios::apellidoUsuario() const
{
    return m_apellidoUsuario;
}
int Usuarios::tipoUsuario() const
{
    return m_tipoUsuario;
}

QString Usuarios::esVendedor() const
{
    return m_esVendedor;
}
int Usuarios::codigoPerfil() const
{
    return m_codigoPerfil;
}

/*void ModuloUsuarios::addUsuarios(const Usuarios &usuarios)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Usuarios << usuarios;
    endInsertRows();

}*/

void ModuloUsuarios::addUsuarios(const Usuarios &usuarios) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Usuarios << usuarios;
    cacheCodigosPerfil[usuarios.idUsuario()] = usuarios.codigoPerfil(); // Añadir a la caché
    endInsertRows();
}

void ModuloUsuarios::clearUsuarios(){
    m_Usuarios.clear();
}

void ModuloUsuarios::buscarUsuarios(QString campo, QString datoABuscar){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select idUsuario,nombreUsuario,apellidoUsuario,tipoUsuario,esVendedor,codigoPerfil from Usuarios where "+campo+"'"+datoABuscar+"'");
        QSqlRecord rec = q.record();

        ModuloUsuarios::reset();
        if(q.record().count()>0){
            while (q.next()){
                ModuloUsuarios::addUsuarios(Usuarios(q.value(rec.indexOf("idUsuario")).toString(),
                                                     q.value(rec.indexOf("nombreUsuario")).toString(),
                                                     q.value(rec.indexOf("apellidoUsuario")).toString(),
                                                     q.value(rec.indexOf("tipoUsuario")).toInt(),
                                                     q.value(rec.indexOf("esVendedor")).toString(),
                                                     q.value(rec.indexOf("codigoPerfil")).toInt()
                                                     ));

            }
        }
    }
}


int ModuloUsuarios::rowCount(const QModelIndex & parent) const {
    return m_Usuarios.count();
}




QVariant ModuloUsuarios::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Usuarios.count()){
        return QVariant();

    }

    const Usuarios &usuarios = m_Usuarios[index.row()];

    if (role == IdUsuarioRole){
        return usuarios.idUsuario();

    }else if (role == NombreUsuarioRole){
        return usuarios.nombreUsuario();

    }else if (role == ApellidoUsuarioRole){
        return usuarios.apellidoUsuario();

    }else if (role == TipoUsuarioRole){
        return usuarios.tipoUsuario();

    }else if (role == EsVendedorRole){
        return usuarios.esVendedor();

    }else if (role == CodigoPerfilRole){
        return usuarios.codigoPerfil();

    }

    return QVariant();

}

bool ModuloUsuarios::conexionUsuario(QString usuario, QString password) const {

    QString claveDeUsuario="";
    QString claveValida = QString(QCryptographicHash::hash((password.toAscii()),QCryptographicHash::Sha1).toHex());


    //  qDebug()<< WSDatabase::wsSelect("select * from Usuarios").typeName();


    // qDebug()<< WSDatabase::wsSelect("select * from Usuarios");


    //qDebug()<< UtilidadesXml::getUrl();


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

        if(query.exec("select claveUsuario from Usuarios where idUsuario='"+usuario+"'limit 1")) {
            if(query.first()){
                claveDeUsuario = query.value(0).toString();

                if(claveDeUsuario!=""){

                    if(claveDeUsuario.compare(claveDeUsuario,claveValida,Qt::CaseSensitive)==0){

                        return true;

                    }else{
                        return false;
                    }
                }else{
                    return false;
                }
            }else{return false;}
        }else{return false;}
    }else{
        return false;
    }
}

int ModuloUsuarios::insertarUsuario(QString _idUsuario,QString _nombreUsuario, QString _apellidoUsuario, QString _esVendedor, QString _codigoPerfil, QString _claveUsuario ) const {


    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el usuario
    // 1  usuario dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar el usuario
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El usuario no tiene los datos sufucientes para darse de alta.



    if(_idUsuario.trimmed()=="" || _nombreUsuario.trimmed()=="" || _codigoPerfil.trimmed()==""){
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

        QString claveValida = QString(QCryptographicHash::hash((_claveUsuario.toAscii()),QCryptographicHash::Sha1).toHex());

        if(query.exec("select idUsuario from Usuarios where idUsuario='"+_idUsuario+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(_claveUsuario.trimmed()==""){
                        if(query.exec("update Usuarios set nombreUsuario='"+_nombreUsuario+"', apellidoUsuario='"+_apellidoUsuario+"',esVendedor='"+_esVendedor+"',codigoPerfil='"+_codigoPerfil+"'  where idUsuario='"+_idUsuario+"'")){


                            return 2;

                        }else{


                            return -2;
                        }
                    }else{

                        if(query.exec("update Usuarios set nombreUsuario='"+_nombreUsuario+"', apellidoUsuario='"+_apellidoUsuario+"',esVendedor='"+_esVendedor+"',codigoPerfil='"+_codigoPerfil+"', claveUsuario='"+claveValida+"'  where idUsuario='"+_idUsuario+"'")){

                            return 2;

                        }else{

                            return -2;
                        }
                    }

                }else{

                    return -4;

                }
            }else{

                if(_claveUsuario.trimmed()==""){

                    return -5;

                }else{
                    if(query.exec("insert INTO Usuarios (idUsuario,nombreUsuario,apellidoUsuario,esVendedor,codigoPerfil,claveUsuario) values('"+_idUsuario+"','"+_nombreUsuario+"','"+_apellidoUsuario+"','"+_esVendedor+"','"+_codigoPerfil+"','"+claveValida+"')")){

                        return 1;
                    }else{

                        return -3;
                    }
                }

            }


        }else{

            return -4;
        }
    }else{
        return -1;
    }
}

bool ModuloUsuarios::eliminarUsuario(QString _idUsuario) const {
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

        if(query.exec("select idUsuario from Usuarios where idUsuario='"+_idUsuario+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){

                    if(query.exec("delete from Usuarios where idUsuario='"+_idUsuario+"'")){

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
QString ModuloUsuarios::retornaVendedorSiEstaLogueado(QString _idUsuario) const{

   /* QString _valor="";
    for (int var = 0; var < m_Usuarios.size(); ++var) {
        if(m_Usuarios[var].idUsuario()==_idUsuario && m_Usuarios[var].esVendedor()=="1"){

            _valor= m_Usuarios[var].nombreUsuario()+" "+m_Usuarios[var].apellidoUsuario();

        }
    }


    if(m_Usuarios.size()==0 && _valor==""){*/
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


            if(query.exec("select concat(nombreUsuario,' ',apellidoUsuario) from Usuarios where idUsuario='"+_idUsuario+"' and esVendedor=1")) {


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
   /* }else{
        return _valor;
    }*/

    /*
    */
}
QString ModuloUsuarios::retornaNombreUsuarioLogueado(QString _idUsuario) const{


    QString _valor="";
    for (int var = 0; var < m_Usuarios.size(); ++var) {
        if(m_Usuarios[var].idUsuario()==_idUsuario){

            _valor= m_Usuarios[var].nombreUsuario()+" "+m_Usuarios[var].apellidoUsuario();

        }
    }

    if(m_Usuarios.size()==0 && _valor==""){
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


            if(query.exec("select concat(nombreUsuario,' ',(case when apellidoUsuario is null then '' else apellidoUsuario end)) from Usuarios where idUsuario='"+_idUsuario+"'")) {

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
    }else{
        qDebug()<< _valor;
        return _valor;
    }


}
int ModuloUsuarios::actualizarClave(QString _idUsuario, QString _claveUsuario ) const {


    // -1  No se pudo conectar a la base de datos
    // -2  No se pudo actualizar el usuario
    // 1  usuario dado de alta ok
    // 2  Actualizacion correcta
    // -3  no se pudo insertar el usuario
    // -4 no se pudo realizar la consulta a la base de datos
    // -5 El usuario no tiene los datos sufucientes para darse de alta.



    if(_idUsuario.trimmed()==""){
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
        QString claveValida = QString(QCryptographicHash::hash((_claveUsuario.toAscii()),QCryptographicHash::Sha1).toHex());

        if(query.exec("select idUsuario from Usuarios where idUsuario='"+_idUsuario+"'")) {

            if(query.first()){
                if(query.value(0).toString()!=""){
                    if(query.exec("update Usuarios set claveUsuario='"+claveValida+"'  where idUsuario='"+_idUsuario+"'")){
                        return 2;
                    }else{
                        return -2;
                    }
                }else{
                    return -4;
                }
            }else{
                return -4;
            }
        }else{
            return -4;
        }
    }else{
        return -1;
    }
}
bool ModuloUsuarios::existenUsuariosConPerfilAsociado(QString _codigoPerfil) const{

 /*   bool _valor=false;
    for (int var = 0; var < m_Usuarios.size(); ++var) {
        if(QString::number(m_Usuarios[var].codigoPerfil())==_codigoPerfil){

            _valor= true;

        }
    }


    if(m_Usuarios.size()==0 && _valor==false){*/
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
            if(query.exec("select idUsuario from Usuarios where codigoPerfil='"+_codigoPerfil+"'")) {
                if(query.first()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return true;
            }
        }else{
            return true;
        }
   /* }else{
        return _valor;
    }*/
}




QString ModuloUsuarios::retornaCodigoPerfil(QString _idUsuario) const{

    // Comprobar si _idUsuario es vacío o tiene menos de 3 dígitos
        if (_idUsuario.isEmpty() || _idUsuario.length() < 3) {
            return "0";
        }


    // Primero revisa en la caché
        if (cacheCodigosPerfil.contains(_idUsuario)) {
            return QString::number(cacheCodigosPerfil.value(_idUsuario));
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

            if(query.exec("select codigoPerfil from Usuarios where idUsuario='"+_idUsuario+"'")) {

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
        }else{return "0";}

}
