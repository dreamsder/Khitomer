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

#ifndef MODULOREPORTES_H
#define MODULOREPORTES_H

#include <QAbstractListModel>
#include <QSqlQuery>


class Reportes
{
public:
    Q_INVOKABLE Reportes(const qlonglong &codigoReporte, const int &codigoMenuReporte,const QString &descripcionReporte,const QString &consultaSql,const QString &consultaSqlGraficas,const QString &consultaSqlCabezal);

    qlonglong codigoReporte() const;
    int codigoMenuReporte() const;
    QString descripcionReporte() const;
    QString consultaSql() const;
    QString consultaSqlGraficas() const;
    QString consultaSqlCabezal() const;


private:
    qlonglong m_codigoReporte;
    int m_codigoMenuReporte;
    QString m_descripcionReporte;
    QString m_consultaSql;
    QString m_consultaSqlGraficas;
    QString m_consultaSqlCabezal;
};

class ModuloReportes : public QAbstractListModel
{
    Q_OBJECT
public:
    enum IvasRoles {
        CodigoReporteRole = Qt::UserRole + 1,
        CodigoMenuReporteRole,
        DescripcionReporteRole,
        ConsultaSqlRole,
        ConsultaSqlGraficasRole,
        ConsultaSqlCabezalRole
    };

    ModuloReportes(QObject *parent = 0);

    Q_INVOKABLE void agregarReportes(const Reportes &Reportes);

    Q_INVOKABLE void limpiarListaReportes();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarReportes(QString , QString , QString );

    Q_INVOKABLE bool retornaPermisosDelReporte(QString ,QString ) const;

    Q_INVOKABLE QString generarReporte(QString, QString , QString, bool,QString) const;

    Q_INVOKABLE QString generarReporteXLS(QString ,QString ) const;

    Q_INVOKABLE QString retornaDirectorioReporteXLS(QString )const;



    Q_INVOKABLE QString retornaDescripcionDelReporte(QString) const;

    Q_INVOKABLE QString retornaConfiguracionAlineacionDeColumnaDelReporte(QString ,QString ) const;

    Q_INVOKABLE QString retornaConfiguracionTotalizadorDeColumnaDelReporte(QString ,QString ) const;

    Q_INVOKABLE QString retornaConfiguracionTipoDeDatoDeColumnaDelReporte(QString ,QString ) const;

    Q_INVOKABLE bool retornaSiReportaEstaHabilitadoEnPerfil(QString ,QString ) const;


    Q_INVOKABLE void eliminarReportesPerfil(QString ,QString ) const;

    Q_INVOKABLE void insertarReportesPerfil(QString ,QString ) const ;


    Q_INVOKABLE bool imprimirReporteEnImpresora(QString )const;




    Q_INVOKABLE QString retornaDirectorioReporteWeb() const;
    Q_INVOKABLE QString retornaDirectorioEstiloCssPDF() const;
    Q_INVOKABLE QString retornaDirectorioEstiloCssHTML() const;
    Q_INVOKABLE QString retornaDirectorioJquery_min_js() const;
    Q_INVOKABLE QString retornaDirectorioJs_highcharts_js() const;
    Q_INVOKABLE QString retornaDirectorioJs_modules_exporting_js() const;






    QString totalizoSumando(QSqlQuery ,int ) const;
    QVariant totalizoSumandoXLS(QSqlQuery ,int ) const;


    QString totalizoContando(QSqlQuery ,int ) const;

    Q_INVOKABLE bool imprimirReporteEnPDF(QString) const;

    Q_INVOKABLE QString retornaSqlReporte(QString) const;
    Q_INVOKABLE QString retornaSqlReporteGraficas(QString) const;
    Q_INVOKABLE QString retornaSqlReporteCabezal(QString) const;


    Q_INVOKABLE void abrirNavegadorArchivos()const;








private:
    QList<Reportes> m_Reportes;
};

#endif // MODULOREPORTES_H
