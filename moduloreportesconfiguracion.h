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
#ifndef MODULOREPORTESCONFIGURACION_H
#define MODULOREPORTESCONFIGURACION_H

#include <QAbstractListModel>

class ReportesConfiguracion
{
public:
    Q_INVOKABLE ReportesConfiguracion(
            const QString &codigoReporte,
            const QString &columnaReporte,
            const QString &alineacionColumna,
            const QString &totalizacionColumna,
            const QString &textoPieOpcional,
            const QString &tipoDatoColumna
            );

    QString codigoReporte() const;
    QString columnaReporte() const;
    QString alineacionColumna() const;
    QString totalizacionColumna() const;
    QString textoPieOpcional() const;
    QString tipoDatoColumna() const;

private:
     QString m_codigoReporte;
    QString m_columnaReporte;
    QString m_alineacionColumna;
    QString m_totalizacionColumna;
    QString m_textoPieOpcional;
    QString m_tipoDatoColumna;
};

class  ModuloReportesConfiguracion : public QAbstractListModel
{
    Q_OBJECT
public:
    enum
        ReportesConfiguracionRoles {
        codigoReporteRole = Qt::UserRole + 1,
        columnaReporteRole,
        alineacionColumnaRole,
        totalizacionColumnaRole,
        textoPieOpcionalRole,
        tipoDatoColumnaRole
    };
    ModuloReportesConfiguracion(QObject *parent = 0);
    Q_INVOKABLE void agregar(const ReportesConfiguracion &ReportesConfiguracion);
    Q_INVOKABLE void limpiar();
    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE void buscarReportesConfiguracion();
    QList<ReportesConfiguracion> m_ReportesConfiguracion;

private:

};
#endif //MODULOREPORTESCONFIGURACION_H
