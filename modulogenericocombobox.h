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
#ifndef MODELOGENERICOCOMBOBOX_H
#define MODELOGENERICOCOMBOBOX_H

#include <QAbstractListModel>

class ModuloGenerico
{
public:
   Q_INVOKABLE ModuloGenerico(const QString &codigoItem, const QString &descripcionItem, const bool &checkBoxActivo
                              , const QString &codigoTipoItem ,const QString &valorItem, const QString &descripcionItemSegundafila

                              , const QString &serieDoc
                              );

    QString codigoItem() const;
    QString descripcionItem() const;
    bool checkBoxActivo() const;
    QString codigoTipoItem() const;

    QString valorItem() const;
    QString descripcionItemSegundafila() const;

    QString serieDoc() const;


private:
    QString m_codigoItem;
    QString m_descripcionItem;
    bool m_checkBoxActivo;
    QString m_codigoTipoItem;
    QString m_valorItem;
    QString m_descripcionItemSegundafila;
    QString m_serieDoc;
};

class ModuloGenericoCombobox : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ModuloGenericoRoles {
        codigoItemRole = Qt::UserRole + 1,
        descripcionItemRole,
        checkBoxActivoRole,
        codigoTipoItemRole,
        valorItemRole,
        descripcionItemSegundafilaRole,
        serieDocRole
    };

    ModuloGenericoCombobox(QObject *parent = 0);

    Q_INVOKABLE void agregarModuloGenerico(const ModuloGenerico &ModuloGenerico);

    Q_INVOKABLE void limpiarListaModuloGenerico();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarModuloGenerico();

    Q_INVOKABLE void buscarTodosLosTipoDocumentos();
    Q_INVOKABLE void buscarTodosLosReportes();

    Q_INVOKABLE void buscarTodosLosTiposPromocion();


    Q_INVOKABLE QString retornarCodigoItem(int) const;
    Q_INVOKABLE QString retornarSerieDoc(int) const;
    Q_INVOKABLE QString retornarDescripcionItem(int) const;
    Q_INVOKABLE bool retornarCheckBoxActivo(int) const;

    Q_INVOKABLE QString retornarCodigoTipoItem(int) const;
    Q_INVOKABLE QString retornarValorItem(int) const;
    Q_INVOKABLE QString retornarDescripcionItemSegundafila(int) const;



private:
    QList<ModuloGenerico> m_ModuloGenerico;
};

#endif // MODELOGENERICOCOMBOBOX_H
