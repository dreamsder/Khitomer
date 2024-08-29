#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QObject>
#include <QString>
#include <QFileDialog>

class FileSelector : public QObject {
    Q_OBJECT
public:
    explicit FileSelector(QObject *parent = 0) : QObject(parent) {}  // Reemplazado nullptr por 0

    Q_INVOKABLE QString openFileDialog() {
        QString fileName = QFileDialog::getOpenFileName(
            0,  // Reemplazado nullptr por 0
            "Seleccione el archivo .CSV a cargar",
            "",
            "CSV Files (*.csv)"
        );
        return fileName;
    }
};

#endif // FILESELECTOR_H
