#include "ajoutpersonnel.h"
#include "ui_ajoutpersonnel.h"
#include "gestionpersonnel.h"
#include "ui_gestionpersonnel.h"
#include "personnel.h"
#include "hotel.h"

ajoutpersonnel::ajoutpersonnel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ajoutpersonnel)
{
    ui->setupUi(this);
    ui->radioButtonun->setChecked(true);
    extracthotels();
    ui->labelsts1->setStyleSheet("QLabel { color : red; }");
    ui->labelsts2->setStyleSheet("QLabel { color : red; }");
    ui->labelsts3->setStyleSheet("QLabel { color : red; }");
    ui->labelsts4->setStyleSheet("QLabel { color : red; }");
    ui->labelstsglb->setStyleSheet("QLabel { color : red; }");
}
void ajoutpersonnel::setusername(QString name){
    ui->labelusr->setText(name);
}
void ajoutpersonnel::setpriv(QString priv){
    ui->labeladm->setText(priv);
}
ajoutpersonnel::~ajoutpersonnel()
{
    delete ui;
}

void ajoutpersonnel::on_pushButtonrtr_clicked()
{
    gestionpersonnel *GP = new gestionpersonnel(this);
    GP->setLabeladm(ui->labeladm->text());
    GP->setLabelusr(ui->labelusr->text());
    GP->show();
    hide();
}
void ajoutpersonnel::extracthotels(){
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    QSqlQuery qrry;
    QString q ="SELECT * FROM hotel";
    qrry.prepare(q);
    qrry.exec();
    while (qrry.next()) {
        ui->comboBox->addItem(qrry.value(1).toString());
    }
    db->DBDisconnect(conn);
    delete db;
}

void ajoutpersonnel::on_pushButtonefface_clicked()
{
    ui->lineEditcin->clear();
    ui->lineEditnom->clear();
    ui->lineEditprenom->clear();
    ui->lineEditnum->clear();
    ui->labelsts1->clear();
    ui->labelsts2->clear();
    ui->labelsts3->clear();
    ui->labelsts4->clear();
    ui->labelstsglb->clear();
}

void ajoutpersonnel::on_pushButtonajt_clicked()
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
     if(!personnel::exists(ui->lineEditnom->text()) && !personnel::existsbycin(ui->lineEditcin->text())){
        if(ui->lineEditprenom->text() == ui->lineEditnum->text()){
            if(ui->radioButtonad->isChecked()){
                    qDebug()<<ui->comboBox->currentText();
                    qDebug()<<hotel::getHotelId(ui->comboBox->currentText());
                  int id = hotel::getHotelId(ui->comboBox->currentText());
                  personnel p(ui->lineEditcin->text(),ui->lineEditnom->text(),ui->lineEditprenom->text(),1,id);
                  bool rslt = personnel::AjoutPersonnel(p);
                  personnel::ModifPersonnelHotel(ui->lineEditcin->text(),id);
                  personnel::WriteToLogFile("["+QDateTime::currentDateTime().toString("dd-MM-yyyy  HH:mm:ss")+"] Insertion du personnel "+ui->lineEditnom->text()+" par "+ui->labelusr->text());
                  qDebug()<<rslt;
                ui->labelstsglb->setStyleSheet("QLabel { color : green; }");
                ui->labelstsglb->setText("Le Personnel a été ajouter avec succée");
                ui->lineEditcin->clear();
                ui->lineEditnom->clear();
                ui->lineEditprenom->clear();
                ui->lineEditnum->clear();
            }
            else {
                int id = hotel::getHotelId(ui->comboBox->currentText());
                personnel p(ui->lineEditcin->text(),ui->lineEditnom->text(),ui->lineEditprenom->text(),0,id);
                 bool rslt = personnel::AjoutPersonnel(p);
                 personnel::ModifPersonnelHotel(ui->lineEditcin->text(),id);
                 personnel::WriteToLogFile("["+QDateTime::currentDateTime().toString("dd-MM-yyyy  HH:mm:ss")+"] Insertion du personnel "+ui->lineEditnom->text()+" par "+ui->labelusr->text());
                qDebug()<<rslt;
                qDebug()<<ui->comboBox->currentText();
                qDebug()<<hotel::getHotelId(ui->comboBox->currentText());
                ui->labelstsglb->setStyleSheet("QLabel { color : green; }");
                ui->labelstsglb->setText("Le Personnel a été ajouter avec succée");
                ui->lineEditcin->clear();
                ui->lineEditnom->clear();
                ui->lineEditprenom->clear();
                ui->lineEditnum->clear();
            }
        }

        else {
            ui->labelsts4->setText("Les mots de passe saisies ne sont pas identique. Rééssayer");
        }
    }
     else {
         ui->labelstsglb->setText("Le Personnel existe deja");
     }
    }
    db->DBDisconnect(conn);
}
