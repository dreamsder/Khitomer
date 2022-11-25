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

#ifndef MODULOUSUARIOS_H
#define MODULOUSUARIOS_H

#include <QAbstractListModel>


class Usuarios
{
public:
   Q_INVOKABLE Usuarios(const QString &idUsuario,const QString &nombreUsuario,const QString &apellidoUsuario,const int &tipoUsuario, const QString &esVendedor,const int &codigoPerfil);

    QString idUsuario() const;
    QString nombreUsuario() const;
    QString apellidoUsuario() const;
    int tipoUsuario() const;
    QString esVendedor() const;
    int codigoPerfil() const;

private:
    QString m_idUsuario;
    QString m_nombreUsuario;
    QString m_apellidoUsuario;
    int m_tipoUsuario;
    QString m_esVendedor;
    int m_codigoPerfil;

};



class ModuloUsuarios : public QAbstractListModel
{
    Q_OBJECT
public:

    enum UsuariosRoles {
        IdUsuarioRole = Qt::UserRole + 1,
        NombreUsuarioRole,
        ApellidoUsuarioRole,
        TipoUsuarioRole,
        EsVendedorRole,
        CodigoPerfilRole

    };

    ModuloUsuarios(QObject *parent = 0);

    Q_INVOKABLE void addUsuarios(const Usuarios &Usuarios);

    Q_INVOKABLE void clearUsuarios();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarUsuarios(QString , QString);

    Q_INVOKABLE bool conexionUsuario(QString , QString) const;

    Q_INVOKABLE bool eliminarUsuario(QString) const;

    Q_INVOKABLE int insertarUsuario(QString , QString,QString , QString,QString , QString) const;

    Q_INVOKABLE QString retornaVendedorSiEstaLogueado(QString) const;

    Q_INVOKABLE QString retornaNombreUsuarioLogueado(QString) const;

    Q_INVOKABLE int actualizarClave(QString , QString  ) const;

    Q_INVOKABLE bool existenUsuariosConPerfilAsociado(QString) const;

    Q_INVOKABLE QString retornaCodigoPerfil(QString _idUsuario) const;





private:
    QList<Usuarios> m_Usuarios;


    
};

#endif // MODULOUSUARIOS_H
