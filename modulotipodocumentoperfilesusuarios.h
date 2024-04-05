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
#ifndef MODULOTIPODOCUMENTOPERFILESUSUARIOS_H
#define MODULOTIPODOCUMENTOPERFILESUSUARIOS_H

#include <QAbstractListModel>

class TipoDocumentoPerfilesUsuarios
{
public:
Q_INVOKABLE TipoDocumentoPerfilesUsuarios(
    const QString &codigoTipoDocumento,
    const QString &codigoPerfil
);

    QString codigoTipoDocumento() const;
    QString codigoPerfil() const;

private:
    QString m_codigoTipoDocumento;
    QString m_codigoPerfil;
};

class ModuloTipoDocumentoPerfilesUsuarios : public QAbstractListModel
{
    Q_OBJECT
public:
    enum
    TipoDocumentoPerfilesUsuariosRoles {
    codigoTipoDocumentoRole = Qt::UserRole + 1,
    codigoPerfilRole
};

    ModuloTipoDocumentoPerfilesUsuarios(QObject *parent = 0);
    Q_INVOKABLE void agregar(const TipoDocumentoPerfilesUsuarios &TipoDocumentoPerfilesUsuarios);
    Q_INVOKABLE void limpiar();
    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE void buscarTipoDocumentoPerfilesUsuarios();
    Q_INVOKABLE bool retornaTipoDocumentoActivoPorPerfil(QString _codigoTipoDocumento,QString _codigoPerfil);


private:
    QList<TipoDocumentoPerfilesUsuarios> m_TipoDocumentoPerfilesUsuarios;
};
#endif //MODULOTIPODOCUMENTOPERFILESUSUARIOS_H
