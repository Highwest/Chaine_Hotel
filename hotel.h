#ifndef HOTEL_H
#define HOTEL_H
#include "hoteldb.h"

class hotel : public hoteldb
{
    QString nom;
    QString lieu;
    int nbchambre;
    int nbsalleconf;
    int nbsallemariage;
public:
    hotel(QString,QString,int,int,int);
    static int getHotelId(QString);
};

#endif // HOTEL_H
