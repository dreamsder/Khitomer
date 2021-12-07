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

#ifndef MODULOLIQUIDACIONES_H
#define MODULOLIQUIDACIONES_H

#include <QAbstractListModel>


class Liquidacion
{
public:
   Q_INVOKABLE Liquidacion(const QString &codigoLiquidacion,const QString &codigoVendedor,const QString &nombreCompletoVendedor,const QString &fechaLiquidacion,const QString &fechaCierreLiquidacion,const QString &estadoLiquidacion,const QString &usuarioAlta);

    QString codigoLiquidacion() const;
    QString codigoVendedor() const;
    QString nombreCompletoVendedor()const;
    QString fechaLiquidacion() const;
    QString fechaCierreLiquidacion() const;
    QString estadoLiquidacion() const;
    QString usuarioAlta() const;

private:
    QString m_codigoLiquidacion;
    QString m_codigoVendedor;
    QString m_nombreCompletoVendedor;
    QString m_fechaLiquidacion;
    QString m_fechaCierreLiquidacion;
    QString m_estadoLiquidacion;
    QString m_usuarioAlta;


};

class ModuloLiquidaciones : public QAbstractListModel
{
    Q_OBJECT
public:
    enum LiquidacionesRoles {
        CodigoLiquidacionRole = Qt::UserRole + 1,
        CodigoVendedorRole,
        NombreCompletoVendedorRole,
        FechaLiquidacionRole,
        FechaCierreLiquidacionRole,
        EstadoLiquidacionRole,
        UsuarioAltaRole

    };

    ModuloLiquidaciones(QObject *parent = 0);

    Q_INVOKABLE void addLiquidacion(const Liquidacion &Liquidacion);

    Q_INVOKABLE void clearLiquidaciones();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarLiquidacion(QString , QString);

    Q_INVOKABLE int insertarLiquidacion( QString , QString ,QString ) const;

    Q_INVOKABLE int ultimoRegistroDeLiquidacionEnBase(QString) const;

    Q_INVOKABLE bool eliminarLiquidacion(QString,QString) const;

    Q_INVOKABLE QString retornaDescripcionLiquidacionDeVendedorPorDefault(QString) const;

    Q_INVOKABLE QString retornaDescripcionLiquidacionDeVendedor(QString, QString) const;

    Q_INVOKABLE QString retornaNumeroPrimeraLiquidacionActiva() const;

    Q_INVOKABLE QString retornaCodigoVendedorPrimeraLiquidacionActiva() const;


    Q_INVOKABLE QString retornaNumeroLiquidacionDeVendedor(QString) const;

    Q_INVOKABLE QString retornaValorTotalDocumentosEnLiquidaciones(QString,QString,QString) const;

    Q_INVOKABLE QString retornaCantidadDocumentosEnLiquidacionSegunEstado(QString,QString,QString) const;

    Q_INVOKABLE bool cerrarLiquidacion(QString ,QString ) const;

    Q_INVOKABLE bool liquidacionActiva(QString ,QString ) const;




private:
    QList<Liquidacion> m_Liquidaciones;

};
#endif // MODULOLIQUIDACIONES_H
