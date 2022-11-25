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

#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include "QSqlQuery"
#include <QVariant>

class Database : public QSqlDatabase
{
public:

    static QSqlDatabase connect() ;
    static void closeDb();
    static QSqlQuery consultaSql(QString);
    static bool chequeaStatusAccesoMysql();
    static bool chequeaStatusAccesoMysqlInicio();




private:
    Database();

};

#endif // DATABASE_H
