#include "hoteldb.h"

hoteldb::hoteldb()
{

}
QSqlDatabase hoteldb::DBConnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/mehdi/chaine_hotels");
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
QString hoteldb::Majus(QString s){
    QString rs="";
    for (int i=0;i<s.length();i++) {
        if(i==0){
            rs+=s.at(i).toUpper();
        }
        else {
            rs+=s.at(i);
        }
    }
    return rs;
}
