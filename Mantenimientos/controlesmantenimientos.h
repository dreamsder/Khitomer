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
#ifndef CONTROLESMANTENIMIENTOS_H
#define CONTROLESMANTENIMIENTOS_H

#include <QAbstractListModel>


class Mantenimientos
{
public:
   Q_INVOKABLE Mantenimientos(
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
            );

    QString  idConfiguracionMantenimiento () const;
    QString  clientesUsaTelefono () const;
    QString  clientesUsaTelefono2 () const;
    QString  clientesUsaCodigoPostal () const;
    QString  clientesUsaEmail () const;
    QString  clientesUsaContacto () const;
    QString  clientesUsaObservaciones () const;
    QString  clientesUsaHorario () const;
    QString  clientesUsaLocalidad () const;
    QString  clientesUsaEsquina () const;
    QString  clientesUsaNumeroPuerta () const;
    QString  clientesUsaSitioWeb () const;
    QString  clientesUsaValoracion () const;
    QString  clientesUsaAgregarListaPrecio () const;
    QString  clientesUsaCuentaBancaria () const;
    QString  clientesUsaCargaBatch () const;
    QString  articulosUsaTipoIVA () const;
    QString  articulosUsaMoneda () const;
    QString  articulosUsaSubRubro () const;
    QString  articulosUsaListaDePrecio () const;
    QString  articulosUsaCodigoBarras () const;
    QString  articulosUsaCantidadMinima () const;
    QString  articulosUsaDescripcionExtendida () const;
    QString  articulosUsaCheckActivo () const;
    QString  articulosUsaCargaBatch () const;
    QString  clientesUsaProcedencia () const;
    QString  clientesUsaFormaDePago () const;
    QString  clientesUsaMoneda () const;
    QString  articulosUsaTipoGarantia () const;

private:
    QString m_idConfiguracionMantenimiento ;
    QString m_clientesUsaTelefono ;
    QString m_clientesUsaTelefono2 ;
    QString m_clientesUsaCodigoPostal ;
    QString m_clientesUsaEmail ;
    QString m_clientesUsaContacto ;
    QString m_clientesUsaObservaciones ;
    QString m_clientesUsaHorario ;
    QString m_clientesUsaLocalidad ;
    QString m_clientesUsaEsquina ;
    QString m_clientesUsaNumeroPuerta ;
    QString m_clientesUsaSitioWeb ;
    QString m_clientesUsaValoracion ;
    QString m_clientesUsaAgregarListaPrecio ;
    QString m_clientesUsaCuentaBancaria ;
    QString m_clientesUsaCargaBatch ;
    QString m_articulosUsaTipoIVA ;
    QString m_articulosUsaMoneda ;
    QString m_articulosUsaSubRubro ;
    QString m_articulosUsaListaDePrecio ;
    QString m_articulosUsaCodigoBarras ;
    QString m_articulosUsaCantidadMinima ;
    QString m_articulosUsaDescripcionExtendida ;
    QString m_articulosUsaCheckActivo ;
    QString m_articulosUsaCargaBatch ;
    QString m_clientesUsaProcedencia ;
    QString m_clientesUsaFormaDePago ;
    QString m_clientesUsaMoneda ;
    QString m_articulosUsaTipoGarantia ;
};



class ControlesMantenimientos : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MantenimientosRoles {
        idConfiguracionMantenimientoRole = Qt::UserRole + 1,
        clientesUsaTelefonoRole,
        clientesUsaTelefono2Role,
        clientesUsaCodigoPostalRole,
        clientesUsaEmailRole,
        clientesUsaContactoRole,
        clientesUsaObservacionesRole,
        clientesUsaHorarioRole,
        clientesUsaLocalidadRole,
        clientesUsaEsquinaRole,
        clientesUsaNumeroPuertaRole,
        clientesUsaSitioWebRole,
        clientesUsaValoracionRole,
        clientesUsaAgregarListaPrecioRole,
        clientesUsaCuentaBancariaRole,
        clientesUsaCargaBatchRole,
        articulosUsaTipoIVARole,
        articulosUsaMonedaRole,
        articulosUsaSubRubroRole,
        articulosUsaListaDePrecioRole,
        articulosUsaCodigoBarrasRole,
        articulosUsaCantidadMinimaRole,
        articulosUsaDescripcionExtendidaRole,
        articulosUsaCheckActivoRole,
        articulosUsaCargaBatchRole,
        clientesUsaProcedenciaRole,
        clientesUsaFormaDePagoRole,
        clientesUsaMonedaRole,
        articulosUsaTipoGarantiaRole


    };

    ControlesMantenimientos(QObject *parent = 0);

    Q_INVOKABLE void agregar(const Mantenimientos &valor);

    Q_INVOKABLE void limpiar();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE bool retornaValorMantenimiento(QString _permisoDocumento) const;

    Q_INVOKABLE void buscarMantenimiento();

    Q_INVOKABLE bool convertirStringABool(QString valor) const;



private:
    QList<Mantenimientos> m_Mantenimientos;
};


#endif // CONTROLESMANTENIMIENTOS_H
