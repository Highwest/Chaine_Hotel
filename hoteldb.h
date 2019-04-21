#ifndef HOTELDB_H
#define HOTELDB_H
#include <QtSql>
#include <QtDebug>
#include <QFile>
#include <QTextStream>


class hoteldb
{
public:
    hoteldb();
    QSqlDatabase DBConnect();
    void DBDisconnect(QSqlDatabase db);
    static QString Majus(QString);
    static bool StrCheck(QString);
    static void WriteToLogFile(QString);
};

#endif // HOTELDB_H
