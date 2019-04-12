#include "gestionclient.h"
#include "ui_gestionclient.h"
#include "tableaudebord.h"
#include "ui_tableaudebord.h"
#include <qpixmap.h>

GestionClient::GestionClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GestionClient)
{
    ui->setupUi(this);
//    QPixmap logo(":/new/img/img/PACEM.png");
//    ui->label_logo->setPixmap(logo.scaled(170,170,Qt::KeepAspectRatio));
}

GestionClient::~GestionClient()
{

    delete ui;
}

void GestionClient::on_pushButton_clicked()
{
    TableauDeBord *T = new TableauDeBord(this);
    T->show();
    hide();
}
