#include "personnel.h"

personnel::personnel(QString cinp,QString login,QString password,int is_admin,int idhotel)
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
    {return true;
    }
    else {
        return false;
    }
}
QString personnel::getPassword(QString n){
    QSqlQuery qrry;
    QString q ="SELECT password FROM personnel WHERE login = :l";
    qrry.prepare(q);
    qrry.bindValue(":l",n);
    bool rslt = qrry.exec();
    if (rslt && qrry.next()) {
        qDebug()<< DecryptPassword(qrry.value(0).toString());
        return DecryptPassword(qrry.value(0).toString());
    }
    return "No PASSWORD";
}
QString personnel::getCinP(QString n){
    QSqlQuery qrry;
    QString q ="SELECT cinP FROM personnel WHERE login = :l";
    qrry.prepare(q);
    qrry.bindValue(":l",n);
    bool rslt = qrry.exec();
    if(rslt && qrry.next()){
        return qrry.value(0).toString();
    }
    return "no cin";
}
bool personnel::exists(QString n){
    QSqlQuery qrry;
    int nb=0;
    QString q ="SELECT * FROM personnel WHERE login = :l";
    qrry.prepare(q);
    qrry.bindValue(":l",n);
    bool rslt = qrry.exec();
    while(rslt && qrry.next()){
          nb++;
    }
    if(nb==0){
        return false;
    }
    else {
        return true;
    }

}
bool personnel::ModifPersonnelLogin(QString id,QString l){
    QSqlQuery check;
    QString q1 = "SELECT * FROM personnel WHERE cinP = :id";
    check.prepare(q1);
    check.bindValue(":id",id);
    check.exec();
    int nbrecords = 0;
    while(check.next()){
        nbrecords++;
    }
    if((nbrecords!=0) && (nbrecords==1)){
    QSqlQuery qrry;
    QString q2 = "UPDATE personnel SET login = :l WHERE cinP = :id";
    qrry.prepare(q2);
    qrry.bindValue(":l",l);
    qrry.bindValue(":id",id);
    bool rslt = qrry.exec();
    return rslt;
    }
    else {
    return false;
    }
}
bool personnel::ModifPersonnelPassword(QString id,QString l){
    QSqlQuery check;
    QString q1 = "SELECT * FROM personnel WHERE cinP = :id";
    check.prepare(q1);
    check.bindValue(":id",id);
    check.exec();
    int nbrecords = 0;
    while(check.next()){
        nbrecords++;
    }
    if((nbrecords!=0) && (nbrecords==1)){
    QSqlQuery qrry;
    QString q2 = "UPDATE personnel SET password = :l WHERE cinP = :id";
    qrry.prepare(q2);
    qrry.bindValue(":l",EncryptPassword(l));
    qrry.bindValue(":id",id);
    bool rslt = qrry.exec();
    return rslt;
    }
    else {
    return false;
    }
}
bool personnel::ModifPersonnelHotel(QString id,int idh){
    QSqlQuery check;
    QString q1 = "SELECT * FROM personnel WHERE cinP = :id";
    check.prepare(q1);
    check.bindValue(":id",id);
    check.exec();
    int nbrecords = 0;
    while(check.next()){
        nbrecords++;
    }
    if((nbrecords!=0) && (nbrecords==1)){
    QSqlQuery qrry;
    QString q2 = "UPDATE personnel SET idhotel = :l WHERE cinP = :id";
    qrry.prepare(q2);
    qrry.bindValue(":l",idh);
    qrry.bindValue(":id",id);
    bool rslt = qrry.exec();
    return rslt;
    }
    else {
    return false;
    }
}
int personnel::getPrivilege(QString id){
    int val;
    if(personnel::Login(id,personnel::getPassword(id))){
        QSqlQuery qrry;
        QString q ="SELECT is_admin FROM personnel WHERE login = :l AND password = :p";
        qrry.prepare(q);
        qrry.bindValue(":l",id);
        qrry.bindValue(":p",personnel::EncryptPassword(personnel::getPassword(id)));
        bool rslt = qrry.exec();
        if(rslt && qrry.next()){
            val = qrry.value(0).toInt();
            qDebug()<< val;
        }
        return val;


    }
}
bool personnel::SuppPersonnel(QString id){
    QSqlQuery check;
    QString q1 = "SELECT * FROM personnel WHERE cinP = :id";
    check.prepare(q1);
    check.bindValue(":id",id);
    check.exec();
    int nbrecords = 0;
    while(check.next()){
        nbrecords++;
    }
    if((nbrecords!=0) && (nbrecords==1)){
    QSqlQuery qrry;
    QString q2 = "DELETE FROM personnel WHERE cinP = :id";
    qrry.prepare(q2);
    qrry.bindValue(":id",id);
    bool rslt = qrry.exec();
    return rslt;
    }
    else {
    return false;
    }
}
bool personnel::existsbycin(QString n){
    QSqlQuery qrry;
    int nb=0;
    QString q ="SELECT * FROM personnel WHERE cinP = :l";
    qrry.prepare(q);
    qrry.bindValue(":l",n);
    bool rslt = qrry.exec();
    while(rslt && qrry.next()){
          nb++;
    }
    if(nb==0){
        return false;
    }
    else {
        return true;
    }


}
bool personnel::ModifPersonnelCin(QString id,QString l){
    QSqlQuery check;
    QString q1 = "SELECT * FROM personnel WHERE cinP = :id";
    check.prepare(q1);
    check.bindValue(":id",id);
    check.exec();
    int nbrecords = 0;
    while(check.next()){
        nbrecords++;
    }
    if((nbrecords!=0) && (nbrecords==1)){
    QSqlQuery qrry;
    QString q2 = "UPDATE personnel SET cinP = :l WHERE cinP = :id";
    qrry.prepare(q2);
    qrry.bindValue(":l",l);
    qrry.bindValue(":id",id);
    bool rslt = qrry.exec();
    return rslt;
    }
    else {
    return false;
    }
}
bool personnel::ModifPersonnelAdmin(QString id,int l){
    QSqlQuery check;
    QString q1 = "SELECT * FROM personnel WHERE cinP = :id";
    check.prepare(q1);
    check.bindValue(":id",id);
    check.exec();
    int nbrecords = 0;
    while(check.next()){
        nbrecords++;
    }
    if((nbrecords!=0) && (nbrecords==1)){
    QSqlQuery qrry;
    QString q2 = "UPDATE personnel SET is_admin = :l WHERE cinP = :id";
    qrry.prepare(q2);
    qrry.bindValue(":l",l);
    qrry.bindValue(":id",id);
    bool rslt = qrry.exec();
    return rslt;
    }
    else {
    return false;
    }
}
