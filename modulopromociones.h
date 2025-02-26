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
#ifndef MODULOPROMOCIONES_H
#define MODULOPROMOCIONES_H

#include <QAbstractListModel>

class Promociones
{
public:
Q_INVOKABLE Promociones(
	const QString &idPromociones,
	const QString &idTipoPromocion,
	const QString &habilitada,
	const QString &fecha,
	const QString &fechaDesde,
	const QString &fechaHasta,
	const QString &diasSemana,
	const QString &nombrePromocion,
	const QString &HTMLPromocion,
	const QString &urlImagen,
	const QString &urlImagen2,
	const QString &ejecutaSiempre,
	const QString &codigoTipoCliente
);

	QString idPromociones() const;
	QString idTipoPromocion() const;
	QString habilitada() const;
	QString fecha() const;
	QString fechaDesde() const;
	QString fechaHasta() const;
	QString diasSemana() const;
	QString nombrePromocion() const;
	QString HTMLPromocion() const;
	QString urlImagen() const;
	QString urlImagen2() const;
	QString ejecutaSiempre() const;
	QString codigoTipoCliente() const;

private:
	QString m_idPromociones;
	QString m_idTipoPromocion;
	QString m_habilitada;
	QString m_fecha;
	QString m_fechaDesde;
	QString m_fechaHasta;
	QString m_diasSemana;
	QString m_nombrePromocion;
	QString m_HTMLPromocion;
	QString m_urlImagen;
	QString m_urlImagen2;
	QString m_ejecutaSiempre;
	QString m_codigoTipoCliente;
};

class ModuloPromociones : public QAbstractListModel
{
    Q_OBJECT
public:
	enum
	PromocionesRoles {
	idPromocionesRole = Qt::UserRole + 1,
	idTipoPromocionRole,
	habilitadaRole,
	fechaRole,
	fechaDesdeRole,
	fechaHastaRole,
	diasSemanaRole,
	nombrePromocionRole,
	HTMLPromocionRole,
	urlImagenRole,
	urlImagen2Role,
	ejecutaSiempreRole,
	codigoTipoClienteRole
};

	ModuloPromociones(QObject *parent = 0);
	Q_INVOKABLE void agregarPromociones(const Promociones &Promociones);
	Q_INVOKABLE void limpiarPromociones();
	Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;
	Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
	Q_INVOKABLE void buscarPromociones(QString );
  Q_INVOKABLE QString retornaValor(int, QString) const;
  Q_INVOKABLE QString retornaUltimoPromociones() const;
  Q_INVOKABLE bool eliminarPromociones(QString) const;

private:
	QList<Promociones> m_Promociones;
};
#endif //MODULOPROMOCIONES_H
