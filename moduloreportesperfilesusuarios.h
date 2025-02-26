/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2025>  <Cristian Montano>

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
#ifndef MODULOREPORTESPERFILESUSUARIOS_H
#define MODULOREPORTESPERFILESUSUARIOS_H

#include <QAbstractListModel>

class ReportesPerfilesUsuarios
{
public:
Q_INVOKABLE ReportesPerfilesUsuarios(
    const QString &codigoReporte,
    const QString &codigoPerfil
);

    QString codigoReporte() const;
    QString codigoPerfil() const;

private:
    QString m_codigoReporte;
    QString m_codigoPerfil;
};

class ModuloReportesPerfilesUsuarios : public QAbstractListModel
{
    Q_OBJECT
public:
    enum
    ReportesPerfilesUsuariosRoles {
    codigoReporteRole = Qt::UserRole + 1,
    codigoPerfilRole
};

    ModuloReportesPerfilesUsuarios(QObject *parent = 0);
    Q_INVOKABLE void agregar(const ReportesPerfilesUsuarios &ReportesPerfilesUsuarios);
    Q_INVOKABLE void limpiar();
    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE void buscarReportesPerfilesUsuarios();

    Q_INVOKABLE bool retornaReporteActivoPorPerfil(QString ,QString );

private:
    QList<ReportesPerfilesUsuarios> m_ReportesPerfilesUsuarios;
};
#endif //MODULOREPORTESPERFILESUSUARIOS_H
