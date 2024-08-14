#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QObject>
#include <QString>
#include <QFileDialog>

class FileSelector : public QObject {
    Q_OBJECT
public:
    explicit FileSelector(QObject *parent = nullptr) : QObject(parent) {}  // Constructor definido en línea

    Q_INVOKABLE QString openFileDialog() {
        QString fileName = QFileDialog::getOpenFileName(
            nullptr,
            "Seleccione el archivo .CSV a cargar",
            "",
            "CSV Files (*.csv)"
        );
        return fileName;
    }
};

#endif // FILESELECTOR_H
