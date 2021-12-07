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

#ifndef MODULOMONEDAS_H
#define MODULOMONEDAS_H

#include <QAbstractListModel>

class Monedas
{
public:
   Q_INVOKABLE Monedas(const int &codigoMoneda,
                       const QString &descripcionMoneda,
                       const QString &simboloMoneda,
                       const double &cotizacionMoneda,
                       const double &cotizacionMonedaOficial,
                       const QString &esMonedaReferenciaSistema,
                       const QString &codigoISO3166,
                       const QString &codigoISO4217

                       );

    int codigoMoneda() const;
    QString descripcionMoneda() const;
    QString simboloMoneda() const;
    double cotizacionMoneda() const;

    double cotizacionMonedaOficial() const;
    QString esMonedaReferenciaSistema() const;
    QString codigoISO3166() const;
    QString codigoISO4217() const;

private:
    int m_codigoMoneda;
    QString m_descripcionMoneda;
    QString m_simboloMoneda;
    double m_cotizacionMoneda;

    double m_cotizacionMonedaOficial;
    QString m_esMonedaReferenciaSistema;
    QString m_codigoISO3166;
    QString m_codigoISO4217;
};

class ModuloMonedas : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MonedasRoles {
        CodigoMonedaRole = Qt::UserRole + 1,
        DescripcionMonedaRole,
        SimboloMonedaRole,
        CotizacionMonedaRole,

        cotizacionMonedaOficialRole,
        esMonedaReferenciaSistemaRole,
        codigoISO3166Role,
        codigoISO4217Role
    };

    ModuloMonedas(QObject *parent = 0);

    Q_INVOKABLE void agregarMonedas(const Monedas &Monedas);

    Q_INVOKABLE void limpiarListaMonedas();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarMonedas(QString , QString);

    Q_INVOKABLE int insertarMonedas( QString , QString, QString , QString, QString , QString, QString , QString) const;

    Q_INVOKABLE bool eliminarMonedas(QString) const;

    Q_INVOKABLE QString retornaDescripcionMoneda(QString) const;

    Q_INVOKABLE QString retornaSimboloMoneda(QString) const;

    Q_INVOKABLE QString retornaCodigoMoneda(QString) const;

    Q_INVOKABLE double retornaCotizacionMoneda(QString) const;

    Q_INVOKABLE QString retornaMonedaReferenciaSistema() const;

    Q_INVOKABLE int actualizarCotizacion(QString , QString) const;

    Q_INVOKABLE int ultimoRegistroDeMoneda()const;



private:
    QList<Monedas> m_Monedas;
};

#endif // MODULOMONEDAS_H
