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
#ifndef MODULODEPARTAMENTOS_H
#define MODULODEPARTAMENTOS_H

#include <QAbstractListModel>

class Departamento
{
public:
   Q_INVOKABLE Departamento(const int &codigoDepartamento, const QString &descripcionDepartamento,const int &codigoPais);

    int codigoDepartamento() const;
    QString descripcionDepartamento() const;
    int codigoPais() const;

private:
    int m_codigoDepartamento;
    QString m_descripcionDepartamento;
    int m_codigoPais;

};

class ModuloDepartamentos : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DepartamentosRoles {
        CodigoDepartamentoRole = Qt::UserRole + 1,
        DescripcionDepartamentoRole,
        CodigoPaisRole

    };

    ModuloDepartamentos(QObject *parent = 0);

    Q_INVOKABLE void agregarDepartamento(const Departamento &Departamento);

    Q_INVOKABLE void limpiarListaDepartamentos();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void buscarDepartamentos(QString , QString);

    Q_INVOKABLE QString retornaUltimoCodigoDepartamento(QString) const;

    Q_INVOKABLE int insertarDepartamento(QString ,QString ,QString );

    Q_INVOKABLE bool eliminarDepartamento(QString ,QString ) const;

    Q_INVOKABLE QString retornaDescripcionDepartamento(QString ,QString ) const;







private:
    QList<Departamento> m_Departamentos;
};

#endif // MODULODEPARTAMENTOS_H
