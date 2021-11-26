#ifndef DIALOGOSWIDGET_H
#define DIALOGOSWIDGET_H

#include <QWidget>
#include <QString>

class DialogosWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DialogosWidget(QWidget *parent = 0);

   Q_INVOKABLE QString cargarArchivoMantenimiento(const QString);
    
signals:
    
public slots:
    
};

#endif // DIALOGOSWIDGET_H
