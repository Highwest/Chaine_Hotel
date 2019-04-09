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
ui->label_staffHotel->setPixmap(pix.scaled(135,135,Qt::KeepAspectRatio));

}

ChaineHotel::~ChaineHotel()
{
delete ui;
}



void ChaineHotel::on_pushButton_connexion_clicked()
{
    QString username = ui ->lineEdit_user->text();
    QString password = ui ->lineEdit_pass->text();
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    qDebug() << "OK1";
    if(personnel::Login(username,password)){
        qDebug() << "OK1";
    D = new TableauDeBord(this);
    D->setUserLabel(username);
    D->setPrivilegeLabel(username,password);
    D->setHotelLabel(username,password);
    D->show();
    hide();
    }
db->DBDisconnect(conn);
}
