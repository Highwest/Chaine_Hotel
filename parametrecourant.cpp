#include "parametrecourant.h"
#include "ui_parametrecourant.h"
#include "tableaudebord.h"
#include "ui_tableaudebord.h"
#include "personnel.h"
#include "hotel.h"

ParametreCourant::ParametreCourant(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ParametreCourant)
{
    ui->setupUi(this);
    ui->label_11->hide();
    ui->label_11->setStyleSheet("QLabel { color : red; }");
    ui->label_10->setStyleSheet("QLabel { color : red; }");
    ui->label_6->setStyleSheet("QLabel { color : red; }");
    ui->userEdit->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    /* block 1 */
    ui->pass1lbl->hide();
    ui->check1->hide();
    ui->ok1btn->hide();
    ui->newusrlbl->hide();
    ui->savebtn1->hide();
    ui->lineEdit_3->hide();
    ui->label->setStyleSheet("QLabel { color : red; }");
    ui->label->hide();
    /* block 2 */
    ui->pass1lbl_2->hide();
    ui->check1_2->hide();
    ui->ok1btn_2->hide();
    ui->lineEdit_4->hide();
    ui->label_7->hide();
    ui->pushButton_5->hide();
    ui->label_2->setStyleSheet("QLabel { color : red; }");
    ui->label_2->hide();
    /* block 3 */
    ui->pass1lbl_3->hide();
    ui->check1_3->hide();
    ui->ok1btn_3->hide();
    ui->label_5->hide();
    ui->pushButton->hide();
    ui->comboBox->hide();
    ui->label_3->setStyleSheet("QLabel { color : red; }");
    ui->label_3->hide();
}

void ParametreCourant::setusername(QString name){
    ui->userEdit->setText(name);
}
void ParametreCourant::setuserhotel(QString hotel){
    ui->lineEdit_2->setText(hotel);
}
void ParametreCourant::setuserpass(QString name){
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    QString p = personnel::getPassword(name);
    db->DBDisconnect(conn);
    delete db;
    ui->lineEdit->setText(p);
}

ParametreCourant::~ParametreCourant()
{
    delete ui;
}

void ParametreCourant::on_mdfbtn1_clicked()
{
    ui->pass1lbl->show();
    ui->check1->show();
    ui->ok1btn->show();

}

void ParametreCourant::on_ok1btn_clicked()
{
    if(ui->check1->text() == ui->lineEdit->text()){
        ui->label->hide();
        ui->newusrlbl->show();
        ui->savebtn1->show();
        ui->lineEdit_3->show();
        ui->pass1lbl->hide();
        ui->check1->hide();
        ui->ok1btn->hide();
        ui->check1->clear();
    }
    else {
        ui->label->show();
    }
}

void ParametreCourant::on_savebtn1_clicked()
{
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    if(ui->lineEdit_3->text().isEmpty()){
        ui->label_6->show();
        ui->label_6->setText("Le champ est vide, veuillez saisir un nom d'utilisateur");
    }
    else {
        if(!personnel::exists(ui->lineEdit_3->text())){
        QString id = personnel::getCinP(ui->userEdit->text());
        bool rslt = personnel::ModifPersonnelLogin(id,ui->lineEdit_3->text());
        if(rslt){
            ui->label_6->hide();
            ui->userEdit->setText(ui->lineEdit_3->text());
            ui->newusrlbl->hide();
            ui->savebtn1->hide();
            ui->lineEdit_3->clear();
            ui->lineEdit_3->hide();

        }
        else {
            ui->label_6->setText("ERREUR : veuillez réssayer plus tard ");
        }
        }
        else {
        ui->label_6->show();
        ui->label_6->setText("Le nom d'utilisateur saisie est non disponible");

        }
    }
        db->DBDisconnect(conn);
        delete db;
}

void ParametreCourant::on_pushButton_3_clicked()
{
    ui->pass1lbl_2->show();
    ui->check1_2->show();
    ui->ok1btn_2->show();
}

void ParametreCourant::on_ok1btn_2_clicked()
{
    if(ui->check1_2->text() == ui->lineEdit->text()){
        ui->label_2->hide();
        ui->lineEdit_4->show();
        ui->label_7->show();
        ui->pushButton_5->show();
        ui->pass1lbl_2->hide();
        ui->check1_2->hide();
        ui->ok1btn_2->hide();
        ui->check1_2->clear();
    }
    else {
        ui->label_2->show();
    }
}

void ParametreCourant::on_pushButton_5_clicked()
{
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    if(ui->lineEdit_4->text().isEmpty()){
        ui->label_10->setText("Le champ est vide, veuillez saisir une mot de passe");
        ui->label_10->show();
    }
    else {
        QString id = personnel::getCinP(ui->userEdit->text());
        bool rslt = personnel::ModifPersonnelPassword(id,ui->lineEdit_4->text());
        if(rslt){
        ui->label_10->hide();
        ui->lineEdit->setText(ui->lineEdit_4->text());
        ui->lineEdit_4->hide();
        ui->label_7->hide();
        ui->lineEdit_4->clear();
        ui->pushButton_5->hide();
        }
        else {
            ui->label_10->setText("ERREUR : veuillez réssayer plus tard ");
        }
    }
}

void ParametreCourant::on_pushButton_4_clicked()
{
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    ui->label_11->hide();
    if(personnel::getPrivilege(ui->userEdit->text())==1){
    ui->label_11->hide();
    ui->pass1lbl_3->show();
    ui->check1_3->show();
    ui->ok1btn_3->show();
    }
    else {
    ui->label_11->show();
    }
    db->DBDisconnect(conn);
}
void ParametreCourant::extracthotels(){
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

void ParametreCourant::on_ok1btn_3_clicked()
{
    if(ui->check1_3->text() == ui->lineEdit->text()){
        ui->label_3->hide();
        ui->label_5->show();
        ui->pushButton->show();
        ui->comboBox->setEnabled(true);
        ui->comboBox->clear();
        extracthotels();
        ui->comboBox->show();
        ui->pass1lbl_3->hide();
        ui->check1_3->hide();
        ui->ok1btn_3->hide();
        ui->check1_3->clear();
    }
    else {
        ui->label_3->show();
    }

}

void ParametreCourant::on_pushButton_clicked()
{
hoteldb *db = new hoteldb();
QSqlDatabase conn = db->DBConnect();
int idhotel = hotel::getHotelId(ui->comboBox->currentText());
QString id = personnel::getCinP(ui->userEdit->text());
bool rslt = personnel::ModifPersonnelHotel(id,idhotel);
if(rslt){
    ui->lineEdit_2->setText(ui->comboBox->currentText());
    ui->label_5->hide();
    ui->pushButton->hide();
    ui->comboBox->hide();
}
db->DBDisconnect(conn);
delete db;
}

void ParametreCourant::on_rturnbtn_clicked()
{
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    TableauDeBord *D = new TableauDeBord(this);
    D->setUserLabel(ui->userEdit->text());
    D->setPrivilegeLabel(ui->userEdit->text(),personnel::getPassword(ui->userEdit->text()));
    D->setHotelLabel(ui->userEdit->text(),personnel::getPassword(ui->userEdit->text()));
    D->show();
    hide();
    db->DBDisconnect(conn);
    delete db;

}
