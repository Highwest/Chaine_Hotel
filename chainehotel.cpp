#include "chainehotel.h"
#include "ui_chainehotel.h"
#include "tableaudebord.h"
#include "ui_tableaudebord.h"
#include "personnel.h"
#include <qpixmap.h>
#include <QDebug>

ChaineHotel::ChaineHotel(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::ChaineHotel)
{

ui->setupUi(this);
QPixmap pix(":/new/img/img/service.png");
ui ->lineEdit_user->clear();
ui ->lineEdit_pass->clear();
ui->label_status->hide();
ui->label_staffHotel->setPixmap(pix.scaled(135,135,Qt::KeepAspectRatio));
ui->label_status->setStyleSheet("QLabel { color : white; background : red; }");
}

ChaineHotel::~ChaineHotel()
{
delete ui;
}



void ChaineHotel::on_pushButton_connexion_clicked()
{
    ui->label_status->hide();
    QString username = ui ->lineEdit_user->text();
    QString password = ui ->lineEdit_pass->text();
    hoteldb *db = new hoteldb();

    QSqlDatabase conn = db->DBConnect();

    if(personnel::Login(username,password)){
        personnel::WriteToLogFile("["+QDateTime::currentDateTime().toString("dd-MM-yyyy  HH:mm:ss")+"] Ouverture de Connexion par "+username);
    D = new TableauDeBord(this);
    D->setUserLabel(username);
    D->setPrivilegeLabel(username,password);
    D->setHotelLabel(username,password);
    D->show();
    hide();
    }
    else {
        ui->label_status->setText("Nom d'utilisateur ou mot de passe incorrecte");
        ui->label_status->show();
    }
db->DBDisconnect(conn);
delete db;
}
