#ifndef PERSONNEL_H
#define PERSONNEL_H
#include "hoteldb.h"


class personnel : public hoteldb
{
    int cinp;
    QString login;
    QString password;
    int is_admin;
    int idhotel;
public:
    personnel(int,QString,QString,int,int);
    static QString EncryptPassword(QString);
    static QString DecryptPassword(QString);
    static QString getPassword(QString);
    static int getCinP(QString);
    static bool exists(QString);
    static bool Login(QString,QString);
    static int getPrivilege(QString);
    static bool AjoutPersonnel(personnel);
    static bool SuppPersonnel(int id);
    static bool ModifPersonnelLogin(int,QString);
    static bool ModifPersonnelPassword(int,QString);
    static bool ModifPersonnelAdmin(int,bool);
    static bool ModifPersonnelHotel(int,int);


};

#endif // PERSONNEL_H
