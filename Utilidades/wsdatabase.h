#ifndef WSDATABASE_H
#define WSDATABASE_H

#include <QVariant>

class WSDatabase : public QVariant
{
public:


    static QVariant wsSelect(QString);


private:
    WSDatabase();


};

#endif // WSDATABASE_H
