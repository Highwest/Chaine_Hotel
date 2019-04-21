#ifndef PERSONNEL_H
#define PERSONNEL_H
#include "hoteldb.h"


class personnel : public hoteldb
{
    QString cinp;
    QString login;
    QString password;
    int is_admin;
    int idhotel;
public:
    personnel(QString,QString,QString,int,int);
    static QString EncryptPassword(QString);
    static QString DecryptPassword(QString);
    static QString getPassword(QString);
    static QString getCinP(QString);
    static bool exists(QString);
    static bool existsbycin(QString);
    static bool Login(QString,QString);
    static int getPrivilege(QString);
    static bool AjoutPersonnel(personnel);
    static bool SuppPersonnel(QString id);
    static bool ModifPersonnelCin(QString,QString);
    static bool ModifPersonnelLogin(QString,QString);
    static bool ModifPersonnelPassword(QString,QString);
    static bool ModifPersonnelAdmin(QString,int);
    static bool ModifPersonnelHotel(QString,int);


};

#endif // PERSONNEL_H
