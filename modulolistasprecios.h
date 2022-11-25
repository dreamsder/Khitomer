/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2023>  <Cristian Montano>

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

#ifndef MODULOLISTASPRECIOS_H
#define MODULOLISTASPRECIOS_H

#include <QAbstractListModel>

class ListasPrecio
{
public:
    Q_INVOKABLE ListasPrecio(const QString &codigoListaPrecio,const QString &descripcionListaPrecio,const QString &vigenciaDesdeFecha,
                             const QString &vigenciaHastaFecha,const QString &usuarioAlta,const QString &activo,const QString &participaEnBusquedaInteligente

                             );

    QString codigoListaPrecio() const;
    QString descripcionListaPrecio() const;
    QString vigenciaDesdeFecha()const;
    QString vigenciaHastaFecha() const;
    QString usuarioAlta() const;
    QString activo() const;
    QString participaEnBusquedaInteligente() const;

private:
    QString m_codigoListaPrecio;
    QString m_descripcionListaPrecio;
    QString m_vigenciaDesdeFecha;
    QString m_vigenciaHastaFecha;
    QString m_usuarioAlta;
    QString m_activo;
    QString m_participaEnBusquedaInteligente;
};

class ModuloListasPrecios : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ListaPrecioRoles {
        CodigoListaPrecioRole = Qt::UserRole + 1,
        DescripcionListaPrecioRole,
        VigenciaDesdeFechaRole,
        VigenciaHastaFechaRole,
        UsuarioAltaRole,
        activoRole,
        participaEnBusquedaInteligenteRole
    };

    ModuloListasPrecios(QObject *parent = 0);

    Q_INVOKABLE void addListasPrecio(const ListasPrecio &ListasPrecio);

    Q_INVOKABLE void clearListasPrecio();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarListasPrecio(QString , QString);

    Q_INVOKABLE int insertarListasPrecio( QString , QString ,QString,QString ,QString,QString,QString) const;

    Q_INVOKABLE int ultimoRegistroDeListasPrecioEnBase() const;

    Q_INVOKABLE bool eliminarListasPrecio(QString) const;

    Q_INVOKABLE QString retornaDescripcionListaPrecio(QString) const;

    Q_INVOKABLE QString retornaListaPrecioDeCliente(QString, QString, QString) const;

    Q_INVOKABLE bool eliminaListaPrecioDeCliente(QString ,QString) const;

    Q_INVOKABLE bool insertarListaPrecioCliente(QString ,QString ,QString) const;

    Q_INVOKABLE void buscarListasPrecioCliente(QString ,QString );

    Q_INVOKABLE QString retornarListaPrecio(int ,QString, QString) const;

    Q_INVOKABLE QString retornaCodigoListaPrecioPorIndice(int ) const;

    Q_INVOKABLE QString retornaDescripcionListaPrecioPorIndice(int ) const;


    Q_INVOKABLE bool retornaSiClienteTieneListaPrecio(QString ,QString ,QString ) const;


    Q_INVOKABLE bool emitirListaPrecioDuplex(QString , QString , QString, int) const;




private:
    QList<ListasPrecio> m_ListasPrecio;

};

#endif // MODULOLISTASPRECIOS_H
