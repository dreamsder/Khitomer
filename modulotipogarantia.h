#ifndef MODULOTIPOGARANTIA_H
#define MODULOTIPOGARANTIA_H

#include <QObject>
#include <QAbstractListModel>

class TipoGarantia
{
public:
   Q_INVOKABLE TipoGarantia(const int &codigoTipoGarantia, const QString &descripcionTipoGarantia);

    int codigoTipoGarantia() const;
    QString descripcionTipoGarantia() const;


private:
    int m_codigoTipoGarantia;
    QString m_descripcionTipoGarantia;

};

class ModuloTipoGarantia : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TipoGarantiaRoles {
        codigoTipoGarantiaRole = Qt::UserRole + 1,
        descripcionTipoGarantiaRole

    };

    ModuloTipoGarantia(QObject *parent = 0);

    Q_INVOKABLE void agregarTipoGarantia(const TipoGarantia &TipoGarantia);

    Q_INVOKABLE void limpiarListaTipoGarantia();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarTipoGarantia(QString , QString);

    Q_INVOKABLE QString retornaDescripcionTipoGarantia(QString) const;

private:
    QList<TipoGarantia> m_TipoGarantia;
};

#endif // MODULOTIPOGARANTIA_H
