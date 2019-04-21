#ifndef CLIENT_H
#define CLIENT_H
#include "hoteldb.h"

class client : public hoteldb
{
    QString cinc;
    QString nom;
    QString prenom;
    int num;
    QString adresse;
public:
    client(QString,QString,QString,int,QString);
    static bool AjoutClient(client);
    static bool SuppClient(QString id);
    static bool ModifClientCin(QString,QString);
    static bool ModifClientNom(QString,QString);
    static bool ModifClientPrenom(QString,QString);
    static bool ModifClientNum(QString,int);
    static bool ModifClientAdresse(QString,QString);
    static bool exists(QString);
};

#endif // CLIENT_H
