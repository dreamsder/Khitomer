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

#ifndef MODULOPERFILES_H
#define MODULOPERFILES_H

#include <QAbstractListModel>

class Perfiles
{
public:
    Q_INVOKABLE Perfiles(const int &codigoPerfil
                         ,const QString &descripcionPerfil
                         ,const QString &permiteUsarLiquidaciones
                         ,const QString &permiteUsarFacturacion
                         ,const QString &permiteUsarArticulos
                         ,const QString &permiteUsarListaPrecios
                         ,const QString &permiteUsarClientes
                         ,const QString &permiteUsarMenuAvanzado
                         ,const QString &permiteUsarDocumentos
                         ,const QString &permiteUsarReportes
                         ,const QString &permiteUsarCuentaCorriente
                         ,const QString &permiteCrearLiquidaciones
                         ,const QString &permiteBorrarLiquidaciones
                         ,const QString &permiteCerrarLiquidaciones
                         ,const QString &permiteAutorizarCierreLiquidaciones
                         ,const QString &permiteCrearFacturas
                         ,const QString &permiteBorrarFacturas
                         ,const QString &permiteAnularFacturas
                         ,const QString &permiteCrearClientes
                         ,const QString &permiteBorrarClientes
                         ,const QString &permiteCrearArticulos
                         ,const QString &permiteBorrarArticulos
                         ,const QString &permiteCrearListaDePrecios
                         ,const QString &permiteBorrarListaDePrecios
                         ,const QString &permiteAutorizarDescuentosArticulo
                         ,const QString &permiteAutorizarDescuentosTotal
                         ,const QString &permiteAutorizarAnulaciones
                         ,const QString &permiteExportarAPDF
                         ,const QString &permiteReimprimirFacturas
                         ,const QString &permiteCambioRapidoDePrecios


                         ,
                         const QString &permiteUsarMenuAvanzadoConfiguraciones,
                         const QString &permiteUsarMenuAvanzadoIvas,
                         const QString &permiteUsarMenuAvanzadoTiposDeDocumentos,
                         const QString &permiteUsarMenuAvanzadoLocalidades,
                         const QString &permiteUsarMenuAvanzadoBancos,
                         const QString &permiteUsarMenuAvanzadoPagoDeFinacieras,
                         const QString &permiteUsarMenuAvanzadoCuentasBancarias,
                         const QString &permiteUsarMenuAvanzadoRubros,
                         const QString &permiteUsarMenuAvanzadoMonedas,
                         const QString &permiteUsarMenuAvanzadoPermisos,
                         const QString &permiteUsarMenuAvanzadoUsuarios





                         );

    int codigoPerfil() const;
    QString descripcionPerfil() const;

    QString permiteUsarLiquidaciones() const;
    QString permiteUsarFacturacion() const;
    QString permiteUsarArticulos() const;
    QString permiteUsarListaPrecios() const;
    QString permiteUsarClientes() const;
    QString permiteUsarMenuAvanzado() const;

    QString permiteUsarDocumentos() const;
    QString permiteUsarReportes() const;
    QString permiteUsarCuentaCorriente() const;
    QString permiteCrearLiquidaciones() const;
    QString permiteBorrarLiquidaciones() const;
    QString permiteCerrarLiquidaciones() const;
    QString permiteAutorizarCierreLiquidaciones() const;
    QString permiteCrearFacturas() const;
    QString permiteBorrarFacturas() const;
    QString permiteAnularFacturas() const;
    QString permiteCrearClientes() const;
    QString permiteBorrarClientes() const;
    QString permiteCrearArticulos() const;
    QString permiteBorrarArticulos() const;
    QString permiteCrearListaDePrecios() const;
    QString permiteBorrarListaDePrecios() const;
    QString permiteAutorizarDescuentosArticulo() const;
    QString permiteAutorizarDescuentosTotal() const;
    QString permiteAutorizarAnulaciones() const;
    QString permiteExportarAPDF() const;
    QString permiteReimprimirFacturas() const;
    QString permiteCambioRapidoDePrecios() const;
    QString permiteUsarMenuAvanzadoConfiguraciones() const;
    QString permiteUsarMenuAvanzadoIvas() const;
    QString permiteUsarMenuAvanzadoTiposDeDocumentos() const;
    QString permiteUsarMenuAvanzadoLocalidades() const;
    QString permiteUsarMenuAvanzadoBancos() const;
    QString permiteUsarMenuAvanzadoPagoDeFinacieras() const;
    QString permiteUsarMenuAvanzadoCuentasBancarias() const;
    QString permiteUsarMenuAvanzadoRubros() const;
    QString permiteUsarMenuAvanzadoMonedas() const;
    QString permiteUsarMenuAvanzadoPermisos() const;
    QString permiteUsarMenuAvanzadoUsuarios() const;



private:
    int m_codigoPerfil;
    QString m_descripcionPerfil;

    QString m_permiteUsarLiquidaciones;
    QString m_permiteUsarFacturacion;
    QString m_permiteUsarArticulos;
    QString m_permiteUsarListaPrecios;
    QString m_permiteUsarClientes;
    QString m_permiteUsarMenuAvanzado;

    QString m_permiteUsarDocumentos;
    QString m_permiteUsarReportes;
    QString m_permiteUsarCuentaCorriente;
    QString m_permiteCrearLiquidaciones;
    QString m_permiteBorrarLiquidaciones;
    QString m_permiteCerrarLiquidaciones;
    QString m_permiteAutorizarCierreLiquidaciones;
    QString m_permiteCrearFacturas;
    QString m_permiteBorrarFacturas;
    QString m_permiteAnularFacturas;
    QString m_permiteCrearClientes;
    QString m_permiteBorrarClientes;
    QString m_permiteCrearArticulos;
    QString m_permiteBorrarArticulos;
    QString m_permiteCrearListaDePrecios;
    QString m_permiteBorrarListaDePrecios;
    QString m_permiteAutorizarDescuentosArticulo;
    QString m_permiteAutorizarDescuentosTotal;
    QString m_permiteAutorizarAnulaciones;
    QString m_permiteExportarAPDF;
    QString m_permiteReimprimirFacturas;
    QString m_permiteCambioRapidoDePrecios;

    QString m_permiteUsarMenuAvanzadoConfiguraciones;
    QString m_permiteUsarMenuAvanzadoIvas;
    QString m_permiteUsarMenuAvanzadoTiposDeDocumentos;
    QString m_permiteUsarMenuAvanzadoLocalidades;
    QString m_permiteUsarMenuAvanzadoBancos;
    QString m_permiteUsarMenuAvanzadoPagoDeFinacieras;
    QString m_permiteUsarMenuAvanzadoCuentasBancarias;
    QString m_permiteUsarMenuAvanzadoRubros;
    QString m_permiteUsarMenuAvanzadoMonedas;
    QString m_permiteUsarMenuAvanzadoPermisos;
    QString m_permiteUsarMenuAvanzadoUsuarios;

};


class ModuloPerfiles : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PerfilesRoles {
        CodigoPerfilRole = Qt::UserRole + 1,
        DescripcionPerfilRole,

        permiteUsarLiquidacionesRole,
        permiteUsarFacturacionRole,
        permiteUsarArticulosRole,
        permiteUsarListaPreciosRole,
        permiteUsarClientesRole,
        permiteUsarMenuAvanzadoRole,

        permiteUsarDocumentosRole,
        permiteUsarReportesRole,
        permiteUsarCuentaCorrienteRole,
        permiteCrearLiquidacionesRole,
        permiteBorrarLiquidacionesRole,
        permiteCerrarLiquidacionesRole,
        permiteAutorizarCierreLiquidacionesRole,
        permiteCrearFacturasRole,
        permiteBorrarFacturasRole,
        permiteAnularFacturasRole,
        permiteCrearClientesRole,
        permiteBorrarClientesRole,
        permiteCrearArticulosRole,
        permiteBorrarArticulosRole,
        permiteCrearListaDePreciosRole,
        permiteBorrarListaDePreciosRole,
        permiteAutorizarDescuentosArticuloRole,
        permiteAutorizarDescuentosTotalRole,
        permiteAutorizarAnulacionesRole,
        permiteExportarAPDFRole,
        permiteReimprimirFacturasRole,
        permiteCambioRapidoDePreciosRole,

        permiteUsarMenuAvanzadoConfiguracionesRole,
        permiteUsarMenuAvanzadoIvasRole,
        permiteUsarMenuAvanzadoTiposDeDocumentosRole,
        permiteUsarMenuAvanzadoLocalidadesRole,
        permiteUsarMenuAvanzadoBancosRole,
        permiteUsarMenuAvanzadoPagoDeFinacierasRole,
        permiteUsarMenuAvanzadoCuentasBancariasRole,
        permiteUsarMenuAvanzadoRubrosRole,
        permiteUsarMenuAvanzadoMonedasRole,
        permiteUsarMenuAvanzadoPermisosRole,
        permiteUsarMenuAvanzadoUsuariosRole


    };

    ModuloPerfiles(QObject *parent = 0);

    Q_INVOKABLE void agregarPerfil(const Perfiles &Perfiles);

    Q_INVOKABLE void limpiarListaPerfiles();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarPerfiles(QString , QString);

    Q_INVOKABLE bool retornaValorDePermiso(QString , QString) const;

    Q_INVOKABLE QString retornaDescripcionPerfil(QString) const;

    Q_INVOKABLE QString retornaCodigoPerfil(QString) const;

    Q_INVOKABLE int ultimoRegistroDePerfil() const;

    Q_INVOKABLE bool eliminarPerfil(QString ) const;

    Q_INVOKABLE int insertarPerfil(QString  , QString , QString , QString , QString , QString , QString  , QString  , QString
                                   , QString  , QString  , QString  , QString  , QString  , QString  , QString  , QString  , QString
                                   , QString  , QString  , QString
                                   , QString  , QString  , QString  , QString  , QString  , QString  , QString , QString, QString

                                   , QString AccedeAlMenuUsuarios
                                   , QString AccedeAlMenuPermisos
                                   , QString AccedeAlMenuMonedas
                                   , QString AccedeAlMenuRubros
                                   , QString AccedeAlMenuCuentasBancarias
                                   , QString AccedeAlMenuPagoDeFinacieras
                                   , QString AccedeAlMenuBancos
                                   , QString AccedeAlMenuLocalidades
                                   , QString AccedeAlMenuTiposDeDocumentos
                                   , QString AccedeAlMenuIvas
                                   , QString AccedeAlMenuConfiguraciones

                                   );



private:
    QList<Perfiles> m_Perfiles;
};


#endif // MODULOPERFILES_H
