#ifndef MANTENIMIENTOBATCH_H
#define MANTENIMIENTOBATCH_H

#include <QAbstractListModel>


class CargaMantenimientoBatch
{
public:
   Q_INVOKABLE CargaMantenimientoBatch(const QString &codigoTipoCargaMantenimientoBatch,
                                       const QString &codigoTipoCampoCargaMantenimientoBatch,
                                       const QString &utilizaCarga);

    QString codigoTipoCargaMantenimientoBatch() const;
    QString codigoTipoCampoCargaMantenimientoBatch() const;
    QString utilizaCarga() const;


private:
    QString m_codigoTipoCargaMantenimientoBatch;
    QString m_codigoTipoCampoCargaMantenimientoBatch;
    QString m_utilizaCarga;
};


class MantenimientoBatch : public QAbstractListModel
{
    Q_OBJECT
public:
    enum CargaMantenimientoBatchRoles {
        codigoTipoCargaMantenimientoBatchRole = Qt::UserRole + 1,
        codigoTipoCampoCargaMantenimientoBatchRole,
        utilizaCargaRole
    };

    MantenimientoBatch(QObject *parent = 0);


    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE bool cargarMantenimientoArticulos();


private:
    QList<CargaMantenimientoBatch> m_CargaMantenimientoBatch;
};

#endif // MANTENIMIENTOBATCH_H
