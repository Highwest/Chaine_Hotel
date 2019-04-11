#ifndef HOTELDB_H
#define HOTELDB_H
#include <QtSql>
#include <QtDebug>



class hoteldb
{
public:
    hoteldb();
    QSqlDatabase DBConnect();
    void DBDisconnect(QSqlDatabase db);
    static QString Majus(QString);
};

#endif // HOTELDB_H
