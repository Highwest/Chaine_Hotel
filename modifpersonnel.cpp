#include "modifpersonnel.h"
#include "ui_modifpersonnel.h"
#include "gestionpersonnel.h"
#include "ui_gestionpersonnel.h"
#include "personnel.h"
#include "hotel.h"
modifpersonnel::modifpersonnel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::modifpersonnel)
{
    ui->setupUi(this);
    extracthotels();
    ui->labelstatus->setStyleSheet("QLabel { color : red; }");
}
void modifpersonnel::setusername(QString name){
    ui->labelusr->setText(name);
}
void modifpersonnel::setpriv(QString priv){
    ui->labeladm->setText(priv);
}
void modifpersonnel::setinfo1(QString info){
    ui->labelinfo1->setText(info);
}
void modifpersonnel::setinfo2(QString info){
    ui->labelinfo2->setText(info);
}
void modifpersonnel::setinfo3(QString info){
    ui->labelinfo3->setText(info);
}
void modifpersonnel::setinfo4(QString info){
    ui->labelinfo4->setText(info);
}
void modifpersonnel::setinfo5(QString info){
    ui->labelinfo5->setText(info);
}
modifpersonnel::~modifpersonnel()
{
    delete ui;
}

void modifpersonnel::on_pushButtonrtr_clicked()
{
    gestionpersonnel *GC = new gestionpersonnel(this);
    GC->setLabeladm(ui->labeladm->text());
    GC->setLabelusr(ui->labelusr->text());
    GC->show();
    hide();
}

void modifpersonnel::on_pushButtondelete_clicked()
{
    ui->lineEditcin->clear();
    ui->lineEditnom->clear();
    ui->lineEditprenom->clear();
    ui->radioButtonun->setAutoExclusive(false);
    ui->radioButtonad->setAutoExclusive(false);
    ui->radioButtonun->setChecked(false);
    ui->radioButtonad->setChecked(false);
    ui->radioButtonun->setAutoExclusive(true);
    ui->radioButtonad->setAutoExclusive(true);
    ui->comboBox->setCurrentIndex(0);
}

void modifpersonnel::on_pushButton_clicked()
{
    if(ui->pushButton->text()=="Afficher"){
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    ui->labelinfo3->setText(personnel::getPassword(ui->labelinfo2->text()));
    db->DBDisconnect(conn);
    ui->pushButton->setText("Masquer");
    }
    else {
        QString ch="";
        for (int i=0;i<ui->labelinfo3->text().length();i++) {
            ch+="*";
        }
        ui->labelinfo3->setText(ch);
        ui->pushButton->setText("Afficher");
    }
}
void modifpersonnel::extracthotels(){
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    QSqlQuery qrry;
    QString q ="SELECT * FROM hotel";
    qrry.prepare(q);
    qrry.exec();
        ui->comboBox->addItem("----selectionner un hotel----");
    while (qrry.next()) {
        ui->comboBox->addItem(qrry.value(1).toString());
    }
    db->DBDisconnect(conn);
    delete db;
}

void modifpersonnel::on_pushButtonsave_clicked()
{
    bool r1=false,r2=false,r3=false,r4=false,r5=false;
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    ui->labelstatus->clear();
    ui->labelstatus->setStyleSheet("QLabel { color : red; }");
    if(ui->lineEditnom->text().isEmpty() && ui->lineEditcin->text().isEmpty() && ui->lineEditprenom->text().isEmpty() && !ui->radioButtonad->isChecked() && !ui->radioButtonun->isChecked() && (ui->comboBox->currentText()=="----selectionner un hotel----")){
        ui->labelstatus->clear();
        ui->labelstatus->setText("Le formulaire est vide , remplissez les champs que vous souhaitez modifier");
    }

    if(!ui->lineEditcin->text().isEmpty()){
        //r1=client::ModifClientCin(ui->labelinfo1->text(),ui->lineEditcin->text());
        r1=personnel::ModifPersonnelCin(ui->labelinfo1->text(),ui->lineEditcin->text());
        ui->labelinfo1->setText(ui->lineEditcin->text());
    }
    if(!ui->lineEditnom->text().isEmpty()){
        //r2=client::ModifClientNom(ui->labelinfo1->text(),ui->lineEditnom->text());
        r2=personnel::ModifPersonnelLogin(ui->labelinfo1->text(),ui->lineEditnom->text());
        ui->labelinfo2->setText(ui->lineEditnom->text());
    }
    if(!ui->lineEditprenom->text().isEmpty()){
        //r3=client::ModifClientPrenom(ui->labelinfo1->text(),ui->lineEditprenom->text());
        r3=personnel::ModifPersonnelPassword(ui->labelinfo1->text(),ui->lineEditprenom->text());
        QString ch="";
        for (int i=0;i<ui->lineEditprenom->text().length();i++) {
            ch+="*";
        }
        ui->labelinfo3->setText(ch);
    }
    if(ui->radioButtonad->isChecked()){
        r4=personnel::ModifPersonnelAdmin(ui->labelinfo1->text(),1);
        ui->labelinfo4->setText("Administrateur");
    }
    if(ui->radioButtonun->isChecked()){
        r4=personnel::ModifPersonnelAdmin(ui->labelinfo1->text(),0);
        ui->labelinfo4->setText("Utilisateur Normal");
    }
    if(ui->comboBox->currentText()!="----selectionner un hotel----"){
        r5=personnel::ModifPersonnelHotel(ui->labelinfo1->text(),hotel::getHotelId(ui->comboBox->currentText()));
        ui->labelinfo5->setText(ui->comboBox->currentText());
    }

    if( r1 || r2 || r3 || r4 || r5){
        ui->labelstatus->clear();
        personnel::WriteToLogFile("["+QDateTime::currentDateTime().toString("dd-MM-yyyy  HH:mm:ss")+"] Modification du personnel "+ui->labelinfo2->text()+" par "+ui->labelusr->text());
        ui->labelstatus->setStyleSheet("QLabel { color : green; }");
        ui->labelstatus->setText("Vos modification ont été faites avec succées");
    }
    db->DBDisconnect(conn);
}
