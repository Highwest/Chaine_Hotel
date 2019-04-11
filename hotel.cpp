#include "hotel.h"

hotel::hotel(QString nom,QString lieu,int nbchambre,int nbsalleconf,int nbsallemariage)
{
    this->nom = nom;
    this->lieu = lieu;
    this->nbchambre = nbchambre;
    this->nbsalleconf = nbsalleconf;
    this->nbsallemariage = nbsallemariage;
}
int hotel::getHotelId(QString n){
    QSqlQuery qrry;
    QString q ="SELECT idhotel FROM hotel WHERE nom = :l";
    qrry.prepare(q);
    qrry.bindValue(":l",n);
    bool rslt = qrry.exec();
    if(rslt && qrry.next()){
        return qrry.value(0).toInt();
    }
    return -1;
}
