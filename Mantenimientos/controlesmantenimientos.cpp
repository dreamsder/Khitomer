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

    roles[idConfiguracionMantenimientoRole] = "idConfiguracionMantenimiento";
    roles[clientesUsaTelefonoRole] = "clientesUsaTelefono";
    roles[clientesUsaTelefono2Role] = "clientesUsaTelefono2";
    roles[clientesUsaCodigoPostalRole] = "clientesUsaCodigoPostal";
    roles[clientesUsaEmailRole] = "clientesUsaEmail";
    roles[clientesUsaContactoRole] = "clientesUsaContacto";
    roles[clientesUsaObservacionesRole] = "clientesUsaObservaciones";
    roles[clientesUsaHorarioRole] = "clientesUsaHorario";
    roles[clientesUsaLocalidadRole] = "clientesUsaLocalidad";
    roles[clientesUsaEsquinaRole] = "clientesUsaEsquina";
    roles[clientesUsaNumeroPuertaRole] = "clientesUsaNumeroPuerta";
    roles[clientesUsaSitioWebRole] = "clientesUsaSitioWeb";
    roles[clientesUsaValoracionRole] = "clientesUsaValoracion";
    roles[clientesUsaAgregarListaPrecioRole] = "clientesUsaAgregarListaPrecio";
    roles[clientesUsaCuentaBancariaRole] = "clientesUsaCuentaBancaria";
    roles[clientesUsaCargaBatchRole] = "clientesUsaCargaBatch";
    roles[articulosUsaTipoIVARole] = "articulosUsaTipoIVA";
    roles[articulosUsaMonedaRole] = "articulosUsaMoneda";
    roles[articulosUsaSubRubroRole] = "articulosUsaSubRubro";
    roles[articulosUsaListaDePrecioRole] = "articulosUsaListaDePrecio";
    roles[articulosUsaCodigoBarrasRole] = "articulosUsaCodigoBarras";
    roles[articulosUsaCantidadMinimaRole] = "articulosUsaCantidadMinima";
    roles[articulosUsaDescripcionExtendidaRole] = "articulosUsaDescripcionExtendida";
    roles[articulosUsaCheckActivoRole] = "articulosUsaCheckActivo";
    roles[articulosUsaCargaBatchRole] = "articulosUsaCargaBatch";
    roles[clientesUsaProcedenciaRole] = "clientesUsaProcedencia";
    roles[clientesUsaFormaDePagoRole] = "clientesUsaFormaDePago";
    roles[clientesUsaMonedaRole] = "clientesUsaMoneda";
    roles[articulosUsaTipoGarantiaRole] = "articulosUsaTipoGarantia";

    setRoleNames(roles);
}
Mantenimientos::Mantenimientos(
        const QString &idConfiguracionMantenimiento ,
        const QString &clientesUsaTelefono ,
        const QString &clientesUsaTelefono2 ,
        const QString &clientesUsaCodigoPostal ,
        const QString &clientesUsaEmail ,
        const QString &clientesUsaContacto ,
        const QString &clientesUsaObservaciones ,
        const QString &clientesUsaHorario ,
        const QString &clientesUsaLocalidad ,
        const QString &clientesUsaEsquina ,
        const QString &clientesUsaNumeroPuerta ,
        const QString &clientesUsaSitioWeb ,
        const QString &clientesUsaValoracion ,
        const QString &clientesUsaAgregarListaPrecio ,
        const QString &clientesUsaCuentaBancaria ,
        const QString &clientesUsaCargaBatch ,
        const QString &articulosUsaTipoIVA ,
        const QString &articulosUsaMoneda ,
        const QString &articulosUsaSubRubro ,
        const QString &articulosUsaListaDePrecio ,
        const QString &articulosUsaCodigoBarras ,
        const QString &articulosUsaCantidadMinima ,
        const QString &articulosUsaDescripcionExtendida ,
        const QString &articulosUsaCheckActivo ,
        const QString &articulosUsaCargaBatch ,
        const QString &clientesUsaProcedencia ,
        const QString &clientesUsaFormaDePago ,
        const QString &clientesUsaMoneda ,
        const QString &articulosUsaTipoGarantia


        )
      :m_idConfiguracionMantenimiento(idConfiguracionMantenimiento),
      m_clientesUsaTelefono(clientesUsaTelefono),
      m_clientesUsaTelefono2(clientesUsaTelefono2),
      m_clientesUsaCodigoPostal(clientesUsaCodigoPostal),
      m_clientesUsaEmail(clientesUsaEmail),
      m_clientesUsaContacto(clientesUsaContacto),
      m_clientesUsaObservaciones(clientesUsaObservaciones),
      m_clientesUsaHorario(clientesUsaHorario),
      m_clientesUsaLocalidad(clientesUsaLocalidad),
      m_clientesUsaEsquina(clientesUsaEsquina),
      m_clientesUsaNumeroPuerta(clientesUsaNumeroPuerta),
      m_clientesUsaSitioWeb(clientesUsaSitioWeb),
      m_clientesUsaValoracion(clientesUsaValoracion),
      m_clientesUsaAgregarListaPrecio(clientesUsaAgregarListaPrecio),
      m_clientesUsaCuentaBancaria(clientesUsaCuentaBancaria),
      m_clientesUsaCargaBatch(clientesUsaCargaBatch),
      m_articulosUsaTipoIVA(articulosUsaTipoIVA),
      m_articulosUsaMoneda(articulosUsaMoneda),
      m_articulosUsaSubRubro(articulosUsaSubRubro),
      m_articulosUsaListaDePrecio(articulosUsaListaDePrecio),
      m_articulosUsaCodigoBarras(articulosUsaCodigoBarras),
      m_articulosUsaCantidadMinima(articulosUsaCantidadMinima),
      m_articulosUsaDescripcionExtendida(articulosUsaDescripcionExtendida),
      m_articulosUsaCheckActivo(articulosUsaCheckActivo),
      m_articulosUsaCargaBatch(articulosUsaCargaBatch),
      m_clientesUsaProcedencia(clientesUsaProcedencia),
      m_clientesUsaFormaDePago(clientesUsaFormaDePago),
      m_clientesUsaMoneda(clientesUsaMoneda),
      m_articulosUsaTipoGarantia(articulosUsaTipoGarantia)
{
}
QString Mantenimientos::idConfiguracionMantenimiento() const
{
    return m_idConfiguracionMantenimiento;
}
int ControlesMantenimientos::rowCount(const QModelIndex & parent) const {
    return m_Mantenimientos.count();
}

QVariant ControlesMantenimientos::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_Mantenimientos.count()){
        return QVariant();
    }
    const Mantenimientos &mantenimientos = m_Mantenimientos[index.row()];

    if (role == idConfiguracionMantenimientoRole){
        return mantenimientos.idConfiguracionMantenimiento();
    }
    return QVariant();
}
bool ControlesMantenimientos::retornaValorMantenimiento(QString _permisoDocumento) const{

    bool _valorARetornar=false;
    for (int var = 0; var < m_Mantenimientos.size(); ++var) {

            if (_permisoDocumento == "clientesUsaTelefono"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaTelefono());}
            else if(_permisoDocumento == "clientesUsaTelefono2"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaTelefono2());
            }
            else if(_permisoDocumento == "clientesUsaCodigoPostal"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaCodigoPostal());
            }
            else if(_permisoDocumento == "clientesUsaEmail"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaEmail());
            }
            else if(_permisoDocumento == "clientesUsaContacto"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaContacto());
            }
            else if(_permisoDocumento == "clientesUsaObservaciones"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaObservaciones());
            }
            else if(_permisoDocumento == "clientesUsaHorario"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaHorario());
            }
            else if(_permisoDocumento == "clientesUsaLocalidad"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaLocalidad());
            }
            else if(_permisoDocumento == "clientesUsaEsquina"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaEsquina());
            }
            else if(_permisoDocumento == "clientesUsaNumeroPuerta"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaNumeroPuerta());
            }
            else if(_permisoDocumento == "clientesUsaSitioWeb"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaSitioWeb());
            }
            else if(_permisoDocumento == "clientesUsaValoracion"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaValoracion());
            }
            else if(_permisoDocumento == "clientesUsaAgregarListaPrecio"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaAgregarListaPrecio());
            }
            else if(_permisoDocumento == "clientesUsaCuentaBancaria"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaCuentaBancaria());
            }
            else if(_permisoDocumento == "clientesUsaCargaBatch"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaCargaBatch());
            }
            else if(_permisoDocumento == "articulosUsaTipoIVA"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].articulosUsaTipoIVA());
            }
            else if(_permisoDocumento == "articulosUsaMoneda"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].articulosUsaMoneda());
            }
            else if(_permisoDocumento == "articulosUsaSubRubro"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].articulosUsaSubRubro());
            }
            else if(_permisoDocumento == "articulosUsaListaDePrecio"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].articulosUsaListaDePrecio());
            }
            else if(_permisoDocumento == "articulosUsaCodigoBarras"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].articulosUsaCodigoBarras());
            }
            else if(_permisoDocumento == "articulosUsaCantidadMinima"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].articulosUsaCantidadMinima());
            }
            else if(_permisoDocumento == "articulosUsaDescripcionExtendida"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].articulosUsaDescripcionExtendida());
            }
            else if(_permisoDocumento == "articulosUsaCheckActivo"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].articulosUsaCheckActivo());
            }
            else if(_permisoDocumento == "articulosUsaCargaBatch"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].articulosUsaCargaBatch());
            }
            else if(_permisoDocumento == "clientesUsaProcedencia"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaProcedencia());
            }
            else if(_permisoDocumento == "clientesUsaFormaDePago"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaFormaDePago());
            }
            else if(_permisoDocumento == "clientesUsaMoneda"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].clientesUsaMoneda());
            }
            else if(_permisoDocumento == "articulosUsaTipoGarantia"){
                _valorARetornar = convertirStringABool(m_Mantenimientos[var].articulosUsaTipoGarantia());
            }

    }
    return _valorARetornar;
    /*
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
    }*/
}


bool ControlesMantenimientos::convertirStringABool(QString valor) const{
    if(valor=="1"){
        return true;
    }else{
        return false;
    }
}

void ControlesMantenimientos::agregar(const Mantenimientos &valor)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Mantenimientos << valor;
    endInsertRows();
}

void ControlesMantenimientos::limpiar(){
    m_Mantenimientos.clear();
}

void ControlesMantenimientos::buscarMantenimiento(){

    bool conexion=true;
    Database::chequeaStatusAccesoMysql();
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << "No conecto";
            conexion=false;
        }
    }

    if(conexion){

        QSqlQuery q = Database::consultaSql("select * from Mantenimientos;");
        QSqlRecord rec = q.record();

        ControlesMantenimientos::reset();

        if(q.record().count()>0){

            while (q.next()){
                ControlesMantenimientos::agregar(Mantenimientos(
                                                     q.value(rec.indexOf("idConfiguracionMantenimiento")).toString(),
                                                     q.value(rec.indexOf("clientesUsaTelefono")).toString(),
                                                     q.value(rec.indexOf("clientesUsaTelefono2")).toString(),
                                                     q.value(rec.indexOf("clientesUsaCodigoPostal")).toString(),
                                                     q.value(rec.indexOf("clientesUsaEmail")).toString(),
                                                     q.value(rec.indexOf("clientesUsaContacto")).toString(),
                                                     q.value(rec.indexOf("clientesUsaObservaciones")).toString(),
                                                     q.value(rec.indexOf("clientesUsaHorario")).toString(),
                                                     q.value(rec.indexOf("clientesUsaLocalidad")).toString(),
                                                     q.value(rec.indexOf("clientesUsaEsquina")).toString(),
                                                     q.value(rec.indexOf("clientesUsaNumeroPuerta")).toString(),
                                                     q.value(rec.indexOf("clientesUsaSitioWeb")).toString(),
                                                     q.value(rec.indexOf("clientesUsaValoracion")).toString(),
                                                     q.value(rec.indexOf("clientesUsaAgregarListaPrecio")).toString(),
                                                     q.value(rec.indexOf("clientesUsaCuentaBancaria")).toString(),
                                                     q.value(rec.indexOf("clientesUsaCargaBatch")).toString(),
                                                     q.value(rec.indexOf("articulosUsaTipoIVA")).toString(),
                                                     q.value(rec.indexOf("articulosUsaMoneda")).toString(),
                                                     q.value(rec.indexOf("articulosUsaSubRubro")).toString(),
                                                     q.value(rec.indexOf("articulosUsaListaDePrecio")).toString(),
                                                     q.value(rec.indexOf("articulosUsaCodigoBarras")).toString(),
                                                     q.value(rec.indexOf("articulosUsaCantidadMinima")).toString(),
                                                     q.value(rec.indexOf("articulosUsaDescripcionExtendida")).toString(),
                                                     q.value(rec.indexOf("articulosUsaCheckActivo")).toString(),
                                                     q.value(rec.indexOf("articulosUsaCargaBatch")).toString(),
                                                     q.value(rec.indexOf("clientesUsaProcedencia")).toString(),
                                                     q.value(rec.indexOf("clientesUsaFormaDePago")).toString(),
                                                     q.value(rec.indexOf("clientesUsaMoneda")).toString(),
                                                     q.value(rec.indexOf("articulosUsaTipoGarantia")).toString()
                                                     ));
            }
        }
    }
}
