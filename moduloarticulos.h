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

#ifndef MODULOARTICULOS_H
#define MODULOARTICULOS_H

#include <QAbstractListModel>
#include <QStringList>

class Articulo
{
public:
   Q_INVOKABLE Articulo(const QString &codigoArticulo,const QString &descripcionArticulo,const QString &descripcionExtendida,const QString &codigoProveedor,const int &codigoIva,const int &codigoMoneda,const QString &activo,const QString &usuarioAlta ,const QString &cantidadMinimaStock,const QString &codigoSubRubro,
                        const int &codigoTipoGarantia
                        );

    QString codigoArticulo() const;
    QString descripcionArticulo() const;
    QString descripcionExtendida() const;
    QString codigoProveedor() const;
    int codigoIva() const;
    int codigoMoneda() const;
    QString activo() const;
    QString usuarioAlta() const;
    QString cantidadMinimaStock() const;
    QString codigoSubRubro() const;
    int codigoTipoGarantia() const;


private:
    QString m_codigoArticulo;
    QString m_descripcionArticulo;
    QString m_descripcionExtendida;
    QString m_codigoProveedor;
    int m_codigoIva;
    int m_codigoMoneda;
    QString m_activo;
    QString m_usuarioAlta;
    QString m_cantidadMinimaStock;
    QString m_codigoSubRubro;
    int m_codigoTipoGarantia;

};

class ModuloArticulos : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ArticuloRoles {
        CodigoArticuloRole = Qt::UserRole + 1,
        DescripcionArticuloRole,
        DescripcionExtendidaRole,
        CodigoProveedorRole,
        CodigoIvaRole,
        CodigoMonedaRole,
        ActivoRole,
        UsuarioAltaRole,
        CantidadMinimaStockRole,
        CodigoSubRubroRole,
        codigoTipoGarantiaRole
    };

    ModuloArticulos(QObject *parent = 0);

    Q_INVOKABLE void addArticulo(const Articulo &Articulo);

    Q_INVOKABLE void clearArticulos();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarArticulo(QString , QString,int);

    Q_INVOKABLE ulong ultimoRegistroDeArticuloEnBase()const;

    Q_INVOKABLE int insertarArticulo( QString , QString, QString, QString, QString ,QString,QString ,QString, QString, QString,QString) const;

    Q_INVOKABLE bool eliminarArticulo(QString) const;

    Q_INVOKABLE QString existeArticulo(QString) const;


    Q_INVOKABLE bool retornaArticuloActivo(QString) const;

    Q_INVOKABLE QString retornaDescripcionArticulo(QString) const;

    Q_INVOKABLE QString retornaDescripcionArticuloExtendida(QString) const;

    Q_INVOKABLE qlonglong retornaStockTotalArticulo(QString _codigoArticulo) const;

    Q_INVOKABLE qlonglong retornaStockTotalArticuloReal(QString _codigoArticulo) const;

    Q_INVOKABLE bool existeArticuloEnDocumentos(QString) const;

    Q_INVOKABLE QString retornaCantidadArticulosSinStock() const;

    Q_INVOKABLE bool reemplazaCantidadArticulosSinStock(QString, QString) const;

    Q_INVOKABLE qlonglong retornaCantidadMinimaAvisoArticulo(QString) const;

    Q_INVOKABLE bool retornaSiPuedeVenderSinStock(qlonglong _cantidad, QString _codigoTipoDocumento, QString _codigoArticulo, qlonglong _cantidadYaVendida) const;

    Q_INVOKABLE QString retornaCodigoTipoGarantia(QString _codigoArticulo) const;



private:
    QList<Articulo> m_Articulos;

};
#endif // MODULOARTICULOS_H
