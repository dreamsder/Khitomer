/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2024>  <Cristian Montano>

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

#ifndef MODULOLISTAPRECIOARTICULOS_H
#define MODULOLISTAPRECIOARTICULOS_H

#include <QAbstractListModel>


class ArticulosListaPrecio
{
public:
   Q_INVOKABLE ArticulosListaPrecio(const QString &codigoListaPrecio,const QString &codigoArticulo,const QString &descripcionArticulo,const QString &precioArticulo);

    QString codigoListaPrecio() const;
    QString codigoArticulo() const;
    QString descripcionArticulo() const;
    QString precioArticulo() const;

private:
    QString m_codigoListaPrecio;
    QString m_codigoArticulo;
    QString m_descripcionArticulo;
    QString m_precioArticulo;
};

class ModuloListaPrecioArticulos : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ArticulosListaPrecioRoles {
        CodigoListaPrecioRole = Qt::UserRole + 1,
        CodigoArticuloRole,
        DescripcionArticuloRole,
        PrecioArticuloRole

    };

    ModuloListaPrecioArticulos(QObject *parent = 0);

    Q_INVOKABLE void addArticulosListaPrecio(const ArticulosListaPrecio &ArticulosListaPrecio);

    Q_INVOKABLE void clearArticulosListaPrecio();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarArticulosListaPrecio(QString , QString);

    Q_INVOKABLE void buscarArticulosListaPrecioParaModificar(QString);


    Q_INVOKABLE int insertarArticulosListaPrecio(QString , QString , QString, QString usuarioUltimaModificacion) const;

    Q_INVOKABLE bool eliminarArticulosListaPrecio(QString) const;

    Q_INVOKABLE bool eliminarArticuloDeListaPrecio(QString) const;

    Q_INVOKABLE bool eliminarArticuloPorListaPrecio(QString , QString ) const;


    Q_INVOKABLE QString retornarArticulosEnLista(int,QString) const;
    Q_INVOKABLE QString retornarPrecioEnLista(int,QString) const;
    Q_INVOKABLE QString retornarDescripcionArticulosEnLista(int indice, QString  _codigoListaPrecio) const;


    Q_INVOKABLE double retornarPrecioDeArticuloEnBaseDeDatos(QString,QString) const;

    ///Retorna Costos
    Q_INVOKABLE double retornarCostoMonedaReferenciaDelSistema(QString) const;
    Q_INVOKABLE double retornarCostoEnMonedaExtrangera(QString) const;
    Q_INVOKABLE QString retornarSimboloMonedaDocumentoArticuloCosto(QString) const;



    Q_INVOKABLE bool actualizarArticuloDeListaPrecio(QString, QString, QString, QString usuarioUltimaModificacion) const;

    Q_INVOKABLE qlonglong retornaCantidadArticulosEnListaPrecio(QString) const;

    Q_INVOKABLE QString retornaCodigoListaPrecio(int );
    Q_INVOKABLE QString retornaCodigoArticulo(int );
    Q_INVOKABLE QString retornaPrecioArticulo(int );
    Q_INVOKABLE QString retornaDescripcionArticulo(int index);

    void marcarArticuloParaSincronizar(QString _codigoArticulo) const;



private:
    QList<ArticulosListaPrecio> m_ArticulosListaPrecio;

};


#endif // MODULOLISTAPRECIOARTICULOS_H
