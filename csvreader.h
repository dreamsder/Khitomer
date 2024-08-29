#ifndef CSVREADER_H
#define CSVREADER_H

#include <QObject>
#include <QVariantMap>
#include <QString>

class CsvReader : public QObject {
    Q_OBJECT
public:
    explicit CsvReader(QObject *parent = 0);

    // Declaración de la función que siempre ignora el encabezado
    Q_INVOKABLE QVariantList readCsvFile(const QString &filePath);
};

#endif // CSVREADER_H
