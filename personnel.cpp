#include "personnel.h"

personnel::personnel(int cinp,QString login,QString password,int is_admin,int idhotel)
{
    this->cinp = cinp;
    this->login = login;
    this->password = password;
    this->is_admin = is_admin;
    this->idhotel = idhotel;
}
bool personnel::AjoutPersonnel(personnel p){
    QSqlQuery qrry;
    QString q ="INSERT INTO personnel (cinP, login, password, is_admin, idhotel)  VALUES (:cinp, :login, :password, :admin, :idhotel)";
    qrry.prepare(q);
    qrry.bindValue(":cinp",p.cinp);
    qrry.bindValue(":login",p.login);
    qrry.bindValue(":password",EncryptPassword(p.password));
    qrry.bindValue(":admin",p.is_admin);
    qrry.bindValue("idhotel",p.idhotel);
    bool rslt = qrry.exec();
    return rslt;
}
QString personnel::EncryptPassword(QString pass){

    QString rslt="";
    int code;
    for (int i=0;i<pass.length();i++) {
        code = pass.at(i).unicode()+2;
        qDebug()<<code;
        rslt+=(QChar)code;
    }
    return rslt;

}

QString personnel::DecryptPassword(QString pass){

    QString rslt="";
    int code;
    for (int i=0;i<pass.length();i++) {
        code = pass.at(i).unicode()-2;
        qDebug()<<code;
        rslt+=(QChar)code;
    }
    return rslt;

}
bool personnel::Login(QString l,QString p){
    QSqlQuery qrry;
    QString q ="SELECT * FROM personnel WHERE login = :login AND password = :pass";
    qrry.prepare(q);
    qrry.bindValue(":login",l);
    qrry.bindValue(":pass",EncryptPassword(p));
    bool rslt = qrry.exec();
    if(rslt && qrry.next())
        return true;
    else {
        return false;
    }
}
