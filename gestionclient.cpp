#include "gestionclient.h"
#include "ui_gestionclient.h"

GestionClient::GestionClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GestionClient)
{
    ui->setupUi(this);
}

GestionClient::~GestionClient()
{
    delete ui;
}
