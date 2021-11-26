#!/bin/bash


nombreClase=$1

nombreclase_h=`echo $nombreClase | tr '[:upper:]' '[:lower:]'`".h"
nombreclase_cpp=`echo $nombreClase | tr '[:upper:]' '[:lower:]'`".cpp"

nombreItemClase=`echo $nombreClase | tail -c +7|head -c 100`

nombreclaseMiniscula=`echo $nombreClase | tr '[:upper:]' '[:lower:]'`


echo $nombreclase_h
echo $nombreclase_cpp
echo $nombreItemClase

echo "/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2019>  <Cristian Montano>

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
*********************************************************************/" > $nombreclase_h
NOMBRECLASE_H=`echo $nombreClase | tr '[:lower:]' '[:upper:]'`

echo "#ifndef $NOMBRECLASE_H"_H  >> $nombreclase_h
echo "#define $NOMBRECLASE_H"_H  >> $nombreclase_h

echo "">>$nombreclase_h

echo "#include <QAbstractListModel>" >> $nombreclase_h 
echo "">>$nombreclase_h
echo "class $nombreItemClase">>$nombreclase_h
echo "{" >>$nombreclase_h
echo "public:" >>$nombreclase_h
echo "Q_INVOKABLE $nombreItemClase(" >>$nombreclase_h



while read line
do
 
   echo -e "	const QString &$line," >>$nombreclase_h

done < datosLineas.txt
cat $nombreclase_h | sed '$s/.$//' > temporal.txt
cat temporal.txt | tee $nombreclase_h > /dev/null


echo ");" >>$nombreclase_h
echo "">>$nombreclase_h

while read line
do

   echo -e "	QString $line() const;" >>$nombreclase_h

done < datosLineas.txt

echo "">>$nombreclase_h
echo "private:">>$nombreclase_h

while read line
do

   echo -e "	QString m_$line;" >>$nombreclase_h

done < datosLineas.txt


echo "};" >>$nombreclase_h
echo "">>$nombreclase_h

echo "class $nombreClase : public QAbstractListModel" >>$nombreclase_h
echo "{" >>$nombreclase_h
echo "    Q_OBJECT" >>$nombreclase_h
echo "public:">>$nombreclase_h
echo "	enum">>$nombreclase_h
echo "	$nombreItemClase"Roles" {" >>$nombreclase_h



while read line
do

   echo -e "	$line"Role" = Qt::UserRole + 1," >>$nombreclase_h
	break

done < datosLineas.txt

contador=0
while read line
do
	if [ $contador -ne 0 ] ; then
	   echo -e "	$line"Role"," >>$nombreclase_h
        else
		contador=1
	fi
done < datosLineas.txt
cat $nombreclase_h | sed '$s/.$//' > temporal.txt
cat temporal.txt | tee $nombreclase_h > /dev/null




echo "};" >>$nombreclase_h
echo "">>$nombreclase_h

echo "	$nombreClase(QObject *parent = 0);" >>$nombreclase_h
echo "	Q_INVOKABLE void agregar$nombreItemClase(const $nombreItemClase &$nombreItemClase);" >>$nombreclase_h
echo "	Q_INVOKABLE void limpiar$nombreItemClase();">>$nombreclase_h
echo "	Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;">>$nombreclase_h 
echo "	Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;">>$nombreclase_h
echo "	Q_INVOKABLE void buscar$nombreItemClase(QString );">>$nombreclase_h
echo "  Q_INVOKABLE QString retornaValor(int, QString) const;">>$nombreclase_h
echo "  Q_INVOKABLE QString retornaUltimo$nombreItemClase() const;" >>$nombreclase_h
echo "  Q_INVOKABLE bool eliminar$nombreItemClase(QString) const;" >>$nombreclase_h


echo "">>$nombreclase_h
echo "private:">>$nombreclase_h
echo "	QList<$nombreItemClase> m_$nombreItemClase;">>$nombreclase_h
echo "};" >>$nombreclase_h

echo "#endif //$NOMBRECLASE_H"_H  >> $nombreclase_h












#############################################################
#############################################################
######### GENERACION ARCHIVO .CPP ###########################
#############################################################
#############################################################
echo "/*********************************************************************
Khitomer - Sistema de facturación
Copyright (C) <2012-2019>  <Cristian Montano>

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
*********************************************************************/" > $nombreclase_cpp


echo "#include <QtSql>

#include <QtSql>
#include <QSqlQuery>
#include <Utilidades/database.h>
#include <QDebug>
#include <funciones.h>
#include \"$nombreclaseMiniscula.h\"


#include <Utilidades/moduloconfiguracion.h>

ModuloConfiguracion func_configuracion$nombreClase;

$nombreClase::$nombreClase(QObject *parent)
    : QAbstractListModel(parent)
{


    	QHash<int, QByteArray> roles;" >> $nombreclase_cpp


while read line
do

   echo -e "    roles[$line"Role"]=\"$line\";" >>$nombreclase_cpp

done < datosLineas.txt

echo "	setRoleNames(roles);
}">> $nombreclase_cpp

echo "$nombreItemClase::$nombreItemClase(">>$nombreclase_cpp

while read line
do

   echo -e "    const QString &$line," >>$nombreclase_cpp

done < datosLineas.txt
cat $nombreclase_cpp | sed '$s/.$//' > temporal.txt
cat temporal.txt | tee $nombreclase_cpp > /dev/null

echo "):">>$nombreclase_cpp

while read line
do

   echo -e "    m_$line($line)," >>$nombreclase_cpp

done < datosLineas.txt
cat $nombreclase_cpp | sed '$s/.$//' > temporal.txt
cat temporal.txt | tee $nombreclase_cpp > /dev/null
echo "{}">>$nombreclase_cpp
echo "" >>$nombreclase_cpp

while read line
do
	echo -e "QString $nombreItemClase::$line()const{" >>$nombreclase_cpp
	echo -e "    return m_$line;}" >>$nombreclase_cpp

done < datosLineas.txt

echo "" >> $nombreclase_cpp

echo "void $nombreClase::agregar$nombreItemClase(const $nombreItemClase &variable)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_$nombreItemClase << variable;
    endInsertRows();
}" >> $nombreclase_cpp

echo "" >> $nombreclase_cpp


echo "void $nombreClase::limpiar$nombreItemClase(){
    m_$nombreItemClase.clear();
}">> $nombreclase_cpp

echo "" >> $nombreclase_cpp


echo "int $nombreClase::rowCount(const QModelIndex & parent) const {
    return m_$nombreItemClase.count();
}" >> $nombreclase_cpp

echo "" >> $nombreclase_cpp



echo "QVariant $nombreClase::data(const QModelIndex & index, int role) const {

    if (index.row() < 0 || index.row() > m_$nombreItemClase.count()){
        return QVariant();

    }

    const $nombreItemClase &variable = m_$nombreItemClase[index.row()];">> $nombreclase_cpp

while read line
do
           echo -e "	if (role == $line"Role"){" >>$nombreclase_cpp
           echo -e "            return variable.$line();\n	}" >>$nombreclase_cpp
		break

done < datosLineas.txt

contador2=0
while read line
do
        if [ $contador2 -ne 0 ] ; then
           echo -e "	    else if (role == $line"Role")\n	{" >>$nombreclase_cpp
           echo -e "    	return variable.$line();\n	}" >>$nombreclase_cpp
        else
                contador2=1
        fi
done < datosLineas.txt

echo	"    return QVariant();
	}" >> $nombreclase_cpp


echo "">> $nombreclase_cpp


echo "QString $nombreClase::retornaValor(int index, QString role) const{

    const $nombreItemClase &variable = m_$nombreItemClase[index];" >> $nombreclase_cpp


while read line
do
           echo -e "    if (role == \"$line\"){" >>$nombreclase_cpp
           echo -e "            return variable.$line();\n      }" >>$nombreclase_cpp
                break

done < datosLineas.txt

contador3=0
while read line
do
        if [ $contador3 -ne 0 ] ; then
           echo -e "        else if (role == \"$line\")\n     {" >>$nombreclase_cpp
           echo -e "            return variable.$line();\n      }" >>$nombreclase_cpp
        else
                contador3=1
        fi
done < datosLineas.txt


echo "}">> $nombreclase_cpp

echo "">> $nombreclase_cpp


codigoItemPrimero=""
while read line
do

codigoItemPrimero=$line;
break;

done < datosLineas.txt



# Creo la funcion para buscar el ultimo codigo disponible
echo "
QString $nombreClase::retornaUltimo$nombreItemClase() const{
	bool conexion=true;
	Database::chequeaStatusAccesoMysql();
	if(!Database::connect().isOpen()){
        	if(!Database::connect().open()){
            	qDebug() << \"No conecto\";
            	conexion=false;
        	}
    	}
	if(conexion){
        	QSqlQuery query(Database::connect());

        if(query.exec(\"select $codigoItemPrimero from $nombreItemClase order by $codigoItemPrimero desc limit 1\")) {
            if(query.first()){
                if(query.value(0).toString()!=\"\"){
                    return QString::number(query.value(0).toInt()+1);
                }else{
                    return \"1\";
                }
            }else{return \"1\";}
        }else{
            return \"1\";
        }
    }else{
        return \"1\";
    }
}


" >>$nombreclase_cpp

# Clase para eliminar 
echo "
bool $nombreClase::eliminar$nombreItemClase(QString _$codigoItemPrimero) const {
Database::chequeaStatusAccesoMysql();
    bool conexion=true;
    if(!Database::connect().isOpen()){
        if(!Database::connect().open()){
            qDebug() << \"No conecto\";
            conexion=false;
        }
    }
    if(conexion){
        QSqlQuery query(Database::connect());
        if(query.exec(\"select $codigoItemPrimero from $nombreItemClase where $codigoItemPrimero='\"+_$codigoItemPrimero+\"'\")) {
            if(query.first()){
                if(query.value(0).toString()!=\"\"){
                    if(query.exec(\"delete from $nombreItemClase where $codigoItemPrimero='\"+_$codigoItemPrimero+\"'\")){
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    return false;
                }
            }else{return false;}
        }else{
            return false;
        }
    }else{
        return false;
    }
}
" >>$nombreclase_cpp

echo "void $nombreClase::buscar$nombreItemClase(QString campo){
	bool conexion=true;
	Database::chequeaStatusAccesoMysql();
    	if(!Database::connect().isOpen()){
        	if(!Database::connect().open()){
            	qDebug() << \"No conecto\";
            	conexion=false;
        	}
    	}



    	if(conexion){

        QSqlQuery q = Database::consultaSql(\"SELECT * FROM $nombreItemClase \"+campo+\";\");
        QSqlRecord rec = q.record();


        $nombreClase::reset();

        if(q.record().count()>0){

            while (q.next()){
                $nombreClase::agregar$nombreItemClase($nombreItemClase( " >> $nombreclase_cpp

while read line
do

   echo -e "						    q.value(rec.indexOf(\"$line\")).toString()," >>$nombreclase_cpp

done < datosLineas.txt
cat $nombreclase_cpp | sed '$s/.$//' > temporal.txt
cat temporal.txt | tee $nombreclase_cpp > /dev/null




echo "                                                                 ));
            }
        }
    }
}" >> $nombreclase_cpp




