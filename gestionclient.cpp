#include "gestionclient.h"
#include "ui_gestionclient.h"
#include "tableaudebord.h"
#include "ui_tableaudebord.h"
#include "ajoutclient.h"
#include "ui_ajoutclient.h"
#include "modifclient.h"
#include "ui_modifclient.h"
#include "personnel.h"
#include "client.h"
#include <qpixmap.h>
#include <QMessageBox>

GestionClient::GestionClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GestionClient)
{
    ui->setupUi(this);
      ui->checkBoxnom->setChecked(true);
      ui->checkBoxprenom->setChecked(true);
      ui->checkBoxnum->setChecked(true);
      ui->checkBoxadr->setChecked(true);
      ui->label_status->hide();
      ui->label_status->setStyleSheet("QLabel { color : red; }");
      hoteldb *db = new hoteldb();
      QSqlDatabase conn = db->DBConnect();
      loadTable();
      db->DBDisconnect(conn);
      ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
      ui->tableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
      ui->tableView->horizontalHeader()->setStretchLastSection(true);
      /*QItemSelectionModel *select = ui->tableView->selectionModel();
      qDebug()<<select->selectedRows(0).value(0).data().toString();
      qDebug()<<select->selectedRows(1).value(0).data().toString();
      qDebug()<<select->selectedRows(2).value(0).data().toString();
      qDebug()<<select->selectedRows(3).value(0).data().toString();*/
//    QPixmap logo(":/new/img/img/PACEM.png");
//    ui->label_logo->setPixmap(logo.scaled(170,170,Qt::KeepAspectRatio));
}

GestionClient::~GestionClient()
{

    delete ui;
}
void GestionClient::setLabelusr(QString n){
    ui->labelusr->setText(n);
}
void GestionClient::setLabeladm(QString n){
    ui->labeladm->setText(n);
}
void GestionClient::loadTable(){

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery qrry;
    QString q ="SELECT cinC AS CIN, nom AS Nom, prenom AS Prenom, numero AS Numero, adresse AS Adresse FROM client";
    qrry.prepare(q);
    qrry.exec();
    model->setQuery(qrry);
    ui->tableView->setModel(model);
}
void GestionClient::on_pushButton_clicked()
{
    TableauDeBord *T = new TableauDeBord(this);
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    T->setUserLabel(ui->labelusr->text());
    T->setPrivilegeLabel(ui->labelusr->text(),personnel::getPassword(ui->labelusr->text()));
    T->setHotelLabel(ui->labelusr->text(),personnel::getPassword(ui->labelusr->text()));
    db->DBDisconnect(conn);
    T->show();
    hide();
}

void GestionClient::on_pushButton_Edit_clicked()
{

    QItemSelectionModel *select = ui->tableView->selectionModel();
    qDebug()<< select->currentIndex().isValid();
    qDebug()<<select->selectedRows(0).value(0).data().toString();
    qDebug()<<select->selectedRows(1).value(0).data().toString();
    qDebug()<<select->selectedRows(2).value(0).data().toString();
    qDebug()<<select->selectedRows(3).value(0).data().toString();
    qDebug()<<select->selectedRows(4).value(0).data().toString();
    if(select->currentIndex().isValid()){
        ui->label_status->clear();
        ui->label_status->hide();
        MC = new modifclient(this);
        MC->setusername(ui->labelusr->text());
        MC->setpriv(ui->labeladm->text());
        MC->setinfo1(select->selectedRows(0).value(0).data().toString());
        MC->setinfo2(select->selectedRows(1).value(0).data().toString());
        MC->setinfo3(select->selectedRows(2).value(0).data().toString());
        MC->setinfo4(select->selectedRows(3).value(0).data().toString());
        MC->setinfo5(select->selectedRows(4).value(0).data().toString());
        MC->show();
        hide();
    }
    else {
        ui->label_status->setText("Veuillez selectionner un client");
        ui->label_status->show();

    }
    select->clearSelection();
    select->clearCurrentIndex();


}

void GestionClient::on_pushButton_Delete_clicked()
{
    if(ui->tableView->selectionModel()->currentIndex().isValid()){
        ui->label_status->clear();
        ui->label_status->hide();
        QItemSelectionModel *select = ui->tableView->selectionModel();
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Hotel PACEL");
        msgBox.setPalette(this->palette());
        msgBox.setText("Veuillez confirmer la suppression de "+select->selectedRows(1).value(0).data().toString()+" "+
                       select->selectedRows(2).value(0).data().toString());
        QAbstractButton* pButtonYes = msgBox.addButton(tr("Confirmer"), QMessageBox::YesRole);
        msgBox.addButton(tr("Annuler"), QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton()==pButtonYes) {
            hoteldb *db = new hoteldb();
            QSqlDatabase conn = db->DBConnect();
            client::SuppClient(select->selectedRows(0).value(0).data().toString());
            QString prenom = select->selectedRows(2).value(0).data().toString();
            QString nom = select->selectedRows(1).value(0).data().toString();
            personnel::WriteToLogFile("["+QDateTime::currentDateTime().toString("dd-MM-yyyy  HH:mm:ss")+"] Suppression du client "+nom+" "+prenom+" par "+ui->labelusr->text());
            select->clearSelection();
            select->clearCurrentIndex();
            loadTable();
            db->DBDisconnect(conn);
        }


    }
    else {
        ui->label_status->setText("Veuillez selectionner un client");
        ui->label_status->show();
    }
}

void GestionClient::on_pushButtonsearch_clicked()
{
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    if(ui->lineEditsearch->text().isEmpty()){
            ui->tableView->model()->~QAbstractItemModel();
            loadTable();
    }
    else {
        ui->tableView->model()->~QAbstractItemModel();
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery qrry;
        QString q ="SELECT cinC AS CIN, nom AS Nom, prenom AS Prenom, numero AS Numero, adresse AS Adresse FROM client WHERE cinC = :cinc";
        if(ui->checkBoxnom->isChecked()){
            q+=" OR nom = :nom";
        }
        if(ui->checkBoxprenom->isChecked()){
            q+=" OR prenom = :prenom";
        }
        if(ui->checkBoxnum->isChecked()){
            q+=" OR numero = :num";
        }
        if(ui->checkBoxadr->isChecked()){
            q+=" OR adresse = :adr";
        }
        qrry.prepare(q);
        qrry.bindValue(":cinc",ui->lineEditsearch->text());
        qrry.bindValue(":nom",ui->lineEditsearch->text());
        qrry.bindValue(":prenom",ui->lineEditsearch->text());
        qrry.bindValue(":num",ui->lineEditsearch->text().toInt());
        qrry.bindValue(":adr",ui->lineEditsearch->text());
        qrry.exec();
        model->setQuery(qrry);
        ui->tableView->setModel(model);
    }
        db->DBDisconnect(conn);
}

void GestionClient::on_pushButton_Add_clicked()
{
    AC = new ajoutclient(this);
    AC->setusername(ui->labelusr->text());
    AC->setpriv(ui->labeladm->text());
    AC->show();
    hide();
}
