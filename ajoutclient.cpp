#include "ajoutclient.h"
#include "ui_ajoutclient.h"
#include "gestionclient.h"
#include "ui_gestionclient.h"
#include "client.h"

ajoutclient::ajoutclient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ajoutclient)
{

    ui->setupUi(this);
    ui->labelsts1->setStyleSheet("QLabel { color : red; }");
    ui->labelsts2->setStyleSheet("QLabel { color : red; }");
    ui->labelsts3->setStyleSheet("QLabel { color : red; }");
    ui->labelsts4->setStyleSheet("QLabel { color : red; }");
    ui->labelstsglb->setStyleSheet("QLabel { color : red; }");
}
void ajoutclient::setusername(QString name){
    ui->labelusr->setText(name);
}
void ajoutclient::setpriv(QString priv){
    ui->labeladm->setText(priv);
}
ajoutclient::~ajoutclient()
{
    delete ui;
}

void ajoutclient::on_pushButtonajt_clicked()
{
    ui->labelsts1->clear();
    ui->labelsts2->clear();
    ui->labelsts3->clear();
    ui->labelsts4->clear();
    ui->labelstsglb->clear();
    ui->labelstsglb->setStyleSheet("QLabel { color : red; }");
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    if(ui->lineEditcin->text().isEmpty()){
        ui->labelsts1->setText("Ce champ est obligatoire");
    }
    if(ui->lineEditnom->text().isEmpty()){
        ui->labelsts2->setText("Ce champ est obligatoire");
    }
    if(ui->lineEditprenom->text().isEmpty()){
        ui->labelsts3->setText("Ce champ est obligatoire");
    }
    if(ui->lineEditnum->text().isEmpty()){
        ui->labelsts4->setText("Ce champ est obligatoire");
    }
    if(!ui->lineEditcin->text().isEmpty() && !ui->lineEditnom->text().isEmpty() && !ui->lineEditprenom->text().isEmpty() && !ui->lineEditnum->text().isEmpty()){
     if(!client::exists(ui->lineEditcin->text())){
        if(hoteldb::StrCheck(ui->lineEditnum->text())){
            if(ui->lineEdit->text().isEmpty()){
                client c(ui->lineEditcin->text(),ui->lineEditnom->text(),ui->lineEditprenom->text(),ui->lineEditnum->text().toInt(),"Pas d'adresse fournie");
                client::AjoutClient(c);
                client::WriteToLogFile("["+QDateTime::currentDateTime().toString("dd-MM-yyyy  HH:mm:ss")+"] Insertion du client "+ui->lineEditnom->text()+" "+ui->lineEditprenom->text()+" par "+ui->labelusr->text());
                ui->labelstsglb->setStyleSheet("QLabel { color : green; }");
                ui->labelstsglb->setText("Le Client a été ajouter avec succée");
                ui->lineEditcin->clear();
                ui->lineEditnom->clear();
                ui->lineEditprenom->clear();
                ui->lineEditnum->clear();
                ui->lineEdit->clear();
            }
            else {
                client c(ui->lineEditcin->text(),ui->lineEditnom->text(),ui->lineEditprenom->text(),ui->lineEditnum->text().toInt(),ui->lineEdit->text());
                client::AjoutClient(c);
                client::WriteToLogFile("["+QDateTime::currentDateTime().toString("dd-MM-yyyy  HH:mm:ss")+"] Insertion du client "+ui->lineEditnom->text()+" "+
                                          ui->lineEditprenom->text()+" par "+ui->labelusr->text());
                ui->labelstsglb->setStyleSheet("QLabel { color : green; }");
                ui->labelstsglb->setText("Le Client a été ajouter avec succée");
                ui->lineEditcin->clear();
                ui->lineEditnom->clear();
                ui->lineEditprenom->clear();
                ui->lineEditnum->clear();
                ui->lineEdit->clear();
            }
        }

        else {
            ui->labelsts4->setText("Le numero doit comprende que des digits [0-9]");
        }
    }
     else {
         ui->labelstsglb->setText("Le client existe deja");
     }
    }
    db->DBDisconnect(conn);
}

void ajoutclient::on_pushButtonefface_clicked()
{
    ui->lineEditcin->clear();
    ui->lineEditnom->clear();
    ui->lineEditprenom->clear();
    ui->lineEditnum->clear();
    ui->lineEdit->clear();
    ui->labelsts1->clear();
    ui->labelsts2->clear();
    ui->labelsts3->clear();
    ui->labelsts4->clear();
    ui->labelstsglb->clear();
}

void ajoutclient::on_pushButtonrtr_clicked()
{
    GestionClient *GC = new GestionClient(this);
    GC->setLabeladm(ui->labeladm->text());
    GC->setLabelusr(ui->labelusr->text());
    GC->show();
    hide();
}
