#include "client.h"

client::client(QString cinc,QString nom,QString prenom,int num,QString adresse)
{
    this->cinc = cinc;
    this->nom = nom;
    this->prenom = prenom;
    this->num = num;
    this->adresse = adresse;
}
bool client::exists(QString cinc){
    QSqlQuery qrry;
    int nb=0;
    QString q ="SELECT * FROM client WHERE cinC = :l";
    qrry.prepare(q);
    qrry.bindValue(":l",cinc);
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
bool client::AjoutClient(client c){
    QSqlQuery qrry;
    if(!client::exists(c.cinc)){
    QString q ="INSERT INTO client (cinC, nom, prenom, numero, adresse)  VALUES (:cinc, :nom, :prenom, :num, :adr)";
    qrry.prepare(q);
    qrry.bindValue(":cinc",c.cinc);
    qrry.bindValue(":nom",c.nom);
    qrry.bindValue(":prenom",c.prenom);
    qrry.bindValue(":num",c.num);
    qrry.bindValue(":adr",c.adresse);
    bool rslt = qrry.exec();
    return rslt;
    }
    else {
        return false;
    }
}
 bool client::SuppClient(QString id){
    QSqlQuery check;
    QString q1 = "SELECT * FROM client WHERE cinC = :id";
    check.prepare(q1);
    check.bindValue(":id",id);
    check.exec();
    int nbrecords = 0;
    while(check.next()){
        nbrecords++;
    }
    if((nbrecords!=0) && (nbrecords==1)){
    QSqlQuery qrry;
    QString q2 = "DELETE FROM client WHERE cinC = :id";
    qrry.prepare(q2);
    qrry.bindValue(":id",id);
    bool rslt = qrry.exec();
    return rslt;
    }
    else {
    return false;
    }
}

 bool client::ModifClientNom(QString id,QString nom){
     QSqlQuery check;
     QString q1 = "SELECT * FROM client WHERE cinC = :id";
     check.prepare(q1);
     check.bindValue(":id",id);
     check.exec();
     int nbrecords = 0;
     while(check.next()){
         nbrecords++;
     }
     if((nbrecords!=0) && (nbrecords==1)){
     QSqlQuery qrry;
     QString q2 = "UPDATE client SET nom = :nom WHERE cinC = :id";
     qrry.prepare(q2);
     qrry.bindValue(":nom",nom);
     qrry.bindValue(":id",id);
     bool rslt = qrry.exec();
     return rslt;
     }
     else {
     return false;
     }
 }
 bool client::ModifClientCin(QString id, QString cinc){
     QSqlQuery check;
     QString q1 = "SELECT * FROM client WHERE cinC = :id";
     check.prepare(q1);
     check.bindValue(":id",id);
     check.exec();
     int nbrecords = 0;
     while(check.next()){
         nbrecords++;
     }
     if((nbrecords!=0) && (nbrecords==1)){
     QSqlQuery qrry;
     QString q2 = "UPDATE client SET cinC = :nom WHERE cinC = :id";
     qrry.prepare(q2);
     qrry.bindValue(":nom",cinc);
     qrry.bindValue(":id",id);
     bool rslt = qrry.exec();
     return rslt;
     }
     else {
     return false;
     }
 }
 bool client::ModifClientPrenom(QString id, QString prenom){
     QSqlQuery check;
     QString q1 = "SELECT * FROM client WHERE cinC = :id";
     check.prepare(q1);
     check.bindValue(":id",id);
     check.exec();
     int nbrecords = 0;
     while(check.next()){
         nbrecords++;
     }
     if((nbrecords!=0) && (nbrecords==1)){
     QSqlQuery qrry;
     QString q2 = "UPDATE client SET prenom = :nom WHERE cinC = :id";
     qrry.prepare(q2);
     qrry.bindValue(":nom",prenom);
     qrry.bindValue(":id",id);
     bool rslt = qrry.exec();
     return rslt;
     }
     else {
     return false;
     }
 }
 bool client::ModifClientAdresse(QString id,QString adr){
     QSqlQuery check;
     QString q1 = "SELECT * FROM client WHERE cinC = :id";
     check.prepare(q1);
     check.bindValue(":id",id);
     check.exec();
     int nbrecords = 0;
     while(check.next()){
         nbrecords++;
     }
     if((nbrecords!=0) && (nbrecords==1)){
     QSqlQuery qrry;
     QString q2 = "UPDATE client SET adresse = :nom WHERE cinC = :id";
     qrry.prepare(q2);
     qrry.bindValue(":nom",adr);
     qrry.bindValue(":id",id);
     bool rslt = qrry.exec();
     return rslt;
     }
     else {
     return false;
     }
 }
 bool client::ModifClientNum(QString id, int num){
     QSqlQuery check;
     QString q1 = "SELECT * FROM client WHERE cinC = :id";
     check.prepare(q1);
     check.bindValue(":id",id);
     check.exec();
     int nbrecords = 0;
     while(check.next()){
         nbrecords++;
     }
     if((nbrecords!=0) && (nbrecords==1)){
     QSqlQuery qrry;
     QString q2 = "UPDATE client SET numero = :nom WHERE cinC = :id";
     qrry.prepare(q2);
     qrry.bindValue(":nom",num);
     qrry.bindValue(":id",id);
     bool rslt = qrry.exec();
     return rslt;
     }
     else {
     return false;
     }
 }
