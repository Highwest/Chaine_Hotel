#include "modifclient.h"
#include "ui_modifclient.h"
#include "gestionclient.h"
#include "ui_gestionclient.h"
#include "client.h"

modifclient::modifclient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::modifclient)
{
    ui->setupUi(this);
    ui->labelstatus->setStyleSheet("QLabel { color : red; }");
}

void modifclient::setusername(QString name){
    ui->labelusr->setText(name);
}
void modifclient::setpriv(QString priv){
    ui->labeladm->setText(priv);
}
modifclient::~modifclient()
{
    delete ui;
}

void modifclient::on_pushButtonrtr_clicked()
{
    GestionClient *GC = new GestionClient(this);
    GC->setLabeladm(ui->labeladm->text());
    GC->setLabelusr(ui->labelusr->text());
    GC->show();
    hide();
}
void modifclient::setinfo1(QString info){
    ui->labelinfo1->setText(info);
}
void modifclient::setinfo2(QString info){
    ui->labelinfo2->setText(info);
}
void modifclient::setinfo3(QString info){
    ui->labelinfo3->setText(info);
}
void modifclient::setinfo4(QString info){
    ui->labelinfo4->setText(info);
}
void modifclient::setinfo5(QString info){
    ui->labelinfo5->setText(info);
}

void modifclient::on_pushButtondelete_clicked()
{
    ui->lineEditcin->clear();
    ui->lineEditnom->clear();
    ui->lineEditprenom->clear();
    ui->lineEditnum->clear();
    ui->lineEditadr->clear();
}

void modifclient::on_pushButtonsave_clicked()
{
    bool r1=false,r2=false,r3=false,r4=false,r5=false;
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    ui->labelstatus->clear();
    ui->labelstatus->setStyleSheet("QLabel { color : red; }");
    if(ui->lineEditnom->text().isEmpty() && ui->lineEditcin->text().isEmpty() && ui->lineEditprenom->text().isEmpty() && ui->lineEditnum->text().isEmpty() && ui->lineEditadr->text().isEmpty()){
        ui->labelstatus->clear();
        ui->labelstatus->setText("Le formulaire est vide , remplissez les champs que vous souhaitez modifier");
    }

    if(!ui->lineEditcin->text().isEmpty()){
        r1=client::ModifClientCin(ui->labelinfo1->text(),ui->lineEditcin->text());
        ui->labelinfo1->setText(ui->lineEditcin->text());
    }
    if(!ui->lineEditnom->text().isEmpty()){
        r2=client::ModifClientNom(ui->labelinfo1->text(),ui->lineEditnom->text());
        ui->labelinfo2->setText(ui->lineEditnom->text());
    }
    if(!ui->lineEditprenom->text().isEmpty()){
        r3=client::ModifClientPrenom(ui->labelinfo1->text(),ui->lineEditprenom->text());
        ui->labelinfo3->setText(ui->lineEditprenom->text());
    }
    if(!ui->lineEditnum->text().isEmpty()){
        if(hoteldb::StrCheck(ui->lineEditnum->text())){
        r4=client::ModifClientNum(ui->labelinfo1->text(),ui->lineEditnum->text().toInt());
        ui->labelinfo4->setText(ui->lineEditnum->text());
        }
        else {
        ui->labelstatus->clear();
        ui->labelstatus->setText("Le numero doit conentir que des digits [0-9]. Réssayer");
        }
    }
    if(!ui->lineEditadr->text().isEmpty()){
        r5=client::ModifClientAdresse(ui->labelinfo1->text(),ui->lineEditadr->text());
        ui->labelinfo5->setText(ui->lineEditadr->text());
    }
    if( r1 || r2 || r3 || r4 || r5){
        ui->labelstatus->clear();
        client::WriteToLogFile("["+QDateTime::currentDateTime().toString("dd-MM-yyyy  HH:mm:ss")+"] Modification du client "+ui->labelinfo2->text()+" "+ui->labelinfo3->text()+" par "+ui->labelusr->text());
        ui->labelstatus->setStyleSheet("QLabel { color : green; }");
        ui->labelstatus->setText("Vos modification ont été faites avec succées");
    }
    db->DBDisconnect(conn);
 }

