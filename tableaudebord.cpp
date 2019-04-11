#include "tableaudebord.h"
#include "ui_tableaudebord.h"
#include "chainehotel.h"
#include "ui_chainehotel.h"
#include "personnel.h"
#include <qpixmap.h>
#include <QTimer>
#include <QTime>

TableauDeBord::TableauDeBord(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::TableauDeBord)
{
    ui->setupUi(this);
    timer_1s = new QTimer(this);
    QObject::connect(timer_1s, SIGNAL(timeout()), this, SLOT(UpdateTime()));
    timer_1s->start(1000);
    timer2 = new QTimer(this);
    QObject::connect(timer2, SIGNAL(timeout()), this, SLOT(UpdateDate()));
    timer2->start(1000);
    QPixmap logo(":/new/img/img/PACEM.png");
    ui->label_logo->setPixmap(logo.scaled(170,170,Qt::KeepAspectRatio));
}

TableauDeBord::~TableauDeBord()
{
delete ui;
}


void TableauDeBord::setUserLabel(QString username){

    ui->label_User->setText(username);
}

void TableauDeBord::setPrivilegeLabel(QString l,QString p){

    if(personnel::Login(l,p)){
        QSqlQuery qrry;
        QString q ="SELECT is_admin FROM personnel WHERE login = :l AND password = :p";
        qrry.prepare(q);
        qrry.bindValue(":l",l);
        qrry.bindValue(":p",personnel::EncryptPassword(p));
        bool rslt = qrry.exec();
        if(rslt && qrry.next()){
            int val = qrry.value(0).toInt();
            if(val==1){
                ui->label_Prev->setText("Administrateur");
            }
            else {
                ui->label_Prev->setText("Utilisateur Normal");
            }
        }


    }
}



void TableauDeBord::setHotelLabel(QString l,QString p){
    if(personnel::Login(l,p)){
        QSqlQuery qrry;
        QString q ="SELECT idhotel FROM personnel WHERE login = :l AND password = :p";
        qrry.prepare(q);
        qrry.bindValue(":l",l);
        qrry.bindValue(":p",personnel::EncryptPassword(p));
        bool rslt = qrry.exec();
        if(rslt && qrry.next()){
            int val = qrry.value(0).toInt();
            QSqlQuery fetch;
            QString r = "SELECT nom FROM hotel WHERE idhotel = :id";
            fetch.prepare(r);
            fetch.bindValue(":id",val);
            rslt = fetch.exec();
            if(rslt && fetch.next()){
                ui->label_Local->setText(fetch.value(0).toString());
            }
        }


    }

}
void TableauDeBord::UpdateTime()
{
    ui->label_Time->setText(QTime::currentTime().toString("hh:mm:ss"));
}
void TableauDeBord::UpdateDate()
{
    QString day = hoteldb::Majus(QDate::longDayName(QDate::currentDate().dayOfWeek()));
    QString month = hoteldb::Majus(QDate::longMonthName(QDate::currentDate().month()));
    ui->label_Date->setText(day+" "+QDate::currentDate().toString("dd")+" "+month+" "+QDate::currentDate().toString("yyyy")+",");
}



void TableauDeBord::on_pushButton_Deconnexion_clicked()
{
    ChaineHotel *C = new ChaineHotel(this);
    C->show();
    hide();
}

void TableauDeBord::on_pushButton_PramUser_clicked()
{
    ParametreCourant *P = new ParametreCourant(this);
    P->setusername(ui->label_User->text());
    P->setuserhotel(ui->label_Local->text());
    P->setuserpass(ui->label_User->text());
    P->show();
    hide();
}

void TableauDeBord::on_pushButton_GCli_clicked()
{
    GC = new GestionClient(this);
    GC->show();
    hide();
}
