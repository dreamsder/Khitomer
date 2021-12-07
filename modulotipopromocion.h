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
#ifndef MODULOTIPOPROMOCION_H
#define MODULOTIPOPROMOCION_H

#include <QAbstractListModel>

class TipoPromocion
{
public:
Q_INVOKABLE TipoPromocion(
	const QString &idTipoPromocion,
	const QString &nombreTipoPromocion
);

	QString idTipoPromocion() const;
	QString nombreTipoPromocion() const;

private:
	QString m_idTipoPromocion;
	QString m_nombreTipoPromocion;
};

class ModuloTipoPromocion : public QAbstractListModel
{
    Q_OBJECT
public:
	enum
	TipoPromocionRoles {
	idTipoPromocionRole = Qt::UserRole + 1,
	nombreTipoPromocionRole
};

	ModuloTipoPromocion(QObject *parent = 0);
	Q_INVOKABLE void agregarTipoPromocion(const TipoPromocion &TipoPromocion);
	Q_INVOKABLE void limpiarTipoPromocion();
	Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;
	Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
	Q_INVOKABLE void buscarTipoPromocion(QString );
  Q_INVOKABLE QString retornaValor(int, QString) const;
  Q_INVOKABLE QString retornaUltimoTipoPromocion() const;
  Q_INVOKABLE bool eliminarTipoPromocion(QString) const;

private:
	QList<TipoPromocion> m_TipoPromocion;
};
#endif //MODULOTIPOPROMOCION_H
