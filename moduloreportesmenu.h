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
#ifndef MODULOREPORTESMENU_H
#define MODULOREPORTESMENU_H

#include <QAbstractListModel>

class ReportesMenu
{
public:
   Q_INVOKABLE ReportesMenu(const int &codigoMenuReporte, const QString &descripcionMenuReporte);

    int codigoMenuReporte() const;
    QString descripcionMenuReporte() const;


private:
    int m_codigoMenuReporte;
    QString m_descripcionMenuReporte;

};

class ModuloReportesMenu : public QAbstractListModel
{
    Q_OBJECT
public:
    enum IvasRoles {
        CodigoMenuReporteRole = Qt::UserRole + 1,
        DescripcionMenuReporteRole
    };

    ModuloReportesMenu(QObject *parent = 0);

    Q_INVOKABLE void agregarReporteMenu(const ReportesMenu &ReportesMenu);

    Q_INVOKABLE void limpiarListaReportesMenu();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarReportesMenu(QString , QString, QString );
    Q_INVOKABLE QString listaCodigoMenusPorPerfil(QString );


private:
    QList<ReportesMenu> m_ReportesMenu;
};

#endif // MODULOREPORTESMENU_H
