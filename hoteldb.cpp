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

bool hoteldb::StrCheck(QString s){
    bool rslt = true;
    for (int i=0;i<s.length();i++) {
        if(s.at(i).isLetter()){
            rslt = false;
        }
    }
    return rslt;
}

void hoteldb::WriteToLogFile(QString str){
    QFile file("/home/mehdi/Documents/ChaineHotel-master/Chaine_Hotel.log");
    if(!file.open(QFile::WriteOnly | QFile::Append | QFile::Text)){
        qDebug()<<"Erreur d'ouverture de fichier log";
    }
    else {
        QTextStream out(&file);
        str+="\n";
        out << str;
        file.flush();
        file.close();
    }
}
