#ifndef MODULO_CONFIGURACIONPROXY_H
#define MODULO_CONFIGURACIONPROXY_H

#include <QObject>

class Modulo_ConfiguracionProxy : public QObject
{
    Q_OBJECT
public:
    explicit Modulo_ConfiguracionProxy(QObject *parent = 0);


    static QString retornoValorPatrametro(QString _codigoConfiguracion);


signals:

public slots:
};

#endif // MODULO_CONFIGURACIONPROXY_H
