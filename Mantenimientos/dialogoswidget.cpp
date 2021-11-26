#include "dialogoswidget.h"
#include <QFileDialog>
#include <QDebug>

DialogosWidget::DialogosWidget(QWidget *parent) :
    QWidget(parent)
{


}
QString DialogosWidget::cargarArchivoMantenimiento(const QString _tipoMantenimiento){

    return QFileDialog::getOpenFileName(this,"Cargar archivo de "+_tipoMantenimiento, QDir::homePath(), tr("Archivos (*.cvs *.txt);;Todos los archivos (*.*)"), 0, QFileDialog::DontUseNativeDialog );

}
