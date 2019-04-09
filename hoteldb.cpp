#include "hoteldb.h"

hoteldb::hoteldb()
{

}
QSqlDatabase hoteldb::DBConnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":/new/img/chaine_hotels.db");
    if(db.isOpen()){
        qDebug() << "DB OPENED";
        return db;
    }
    else {
        db.open();
        qDebug() << "DB OPENED";
        return db;

    }
}
void hoteldb::DBDisconnect(QSqlDatabase db) {
    if(db.isOpen()){
        db.close();
        qDebug() << "DB CLOSED";
    }

}
