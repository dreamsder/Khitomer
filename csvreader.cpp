#include "csvreader.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

CsvReader::CsvReader(QObject *parent) : QObject(parent) {}

QVariantList CsvReader::readCsvFile(const QString &filePath) {
    QVariantList rows;
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
       // bool firstLine = true;

        while (!stream.atEnd()) {
            QString line = stream.readLine();
            /*if (firstLine) {
                // Ignora la primera línea (encabezado)
                firstLine = false;
                continue;
            }*/

            if(line!=""){
                QStringList fields = line.split(",");
                rows << QVariant::fromValue(fields);
            }
        }

        file.close();
    }

    return rows;
}
