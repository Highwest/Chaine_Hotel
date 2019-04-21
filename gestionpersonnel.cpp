#include "gestionpersonnel.h"
#include "ui_gestionpersonnel.h"
#include "tableaudebord.h"
#include "ui_tableaudebord.h"
#include "ajoutpersonnel.h"
#include "ui_ajoutpersonnel.h"
#include "personnel.h"
#include <QMessageBox>

gestionpersonnel::gestionpersonnel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestionpersonnel)
{
    ui->setupUi(this);
    ui->checkBoxnom_2->setChecked(true);
    ui->checkBoxprenom_2->setChecked(true);
    ui->checkBoxun->setChecked(true);
    ui->checkBoxad->setChecked(true);
    ui->label_status->hide();
    ui->label_status->setStyleSheet("QLabel { color : red; }");
    QList<QString> cin_list;
    QList<QString> login_list;
    QList<QString> pass_list;
    QList<QString> priv_list;
    QList<QString> hotel_list;
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    LoadTableData(cin_list,login_list,pass_list,priv_list,hotel_list);
    db->DBDisconnect(conn);
    PModel *PersonnelModel = new PModel(this);
    PersonnelModel->populateData(cin_list,login_list,pass_list,priv_list,hotel_list);
    ui->tableView_2->setModel(PersonnelModel);
    ui->tableView_2->horizontalHeader()->setVisible(true);
    for (int col=0; col<5; col++)
    {
       ui->tableView_2->setColumnWidth(col,150);
    }
    ui->tableView_2->show();
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);
}

gestionpersonnel::~gestionpersonnel()
{
    delete ui;
}
void gestionpersonnel::setLabelusr(QString n){
    ui->labelusr_2->setText(n);
}
void gestionpersonnel::setLabeladm(QString n){
    ui->labeladm_2->setText(n);
}

void gestionpersonnel::on_pushButton_clicked()
{
    TableauDeBord *T = new TableauDeBord(this);
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    T->setUserLabel(ui->labelusr_2->text());
    T->setPrivilegeLabel(ui->labelusr_2->text(),personnel::getPassword(ui->labelusr_2->text()));
    T->setHotelLabel(ui->labelusr_2->text(),personnel::getPassword(ui->labelusr_2->text()));
    db->DBDisconnect(conn);
    T->show();
    hide();
}
/*void gestionpersonnel::loadTable(){

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery qrry;
    QString q ="SELECT p.cinP AS CIN,p.login AS 'Nom d`utilisateur',p.password AS 'Mot de passe',p.is_admin AS 'Privilege',h.nom AS 'Lieu de travail' FROM personnel p,hotel h where p.idhotel = h.idhotel";
    qrry.prepare(q);
    qrry.exec();
    model->setQuery(qrry);
    ui->tableView_2->setModel(model);
    for (int col=0; col<5; col++)
    {
       ui->tableView_2->setColumnWidth(col,150);
    }
    for(int i=0;i<2;i++)
    qDebug()<<ui->tableView_2->model()->data(ui->tableView_2->model()->index(i,3)).toString();

}*/
PModel::PModel(QObject *parent) : QAbstractTableModel(parent)
{
}
void PModel::populateData(const QList<QString> &cinp,const QList<QString> &login,const QList<QString> &pass,const QList<QString> &priv,const QList<QString> &hotel)
{
    lcin.clear();
    lcin = cinp;
    llogin.clear();
    llogin = login;
    lpass.clear();
    lpass = pass;
    lpriv.clear();
    lpriv = priv;
    lhotel.clear();
    lhotel = hotel;
    return;
}
int PModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return lcin.length();
}
int PModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}
QVariant PModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return lcin[index.row()];
    }
    if (index.column() == 1) {
        return llogin[index.row()];
    }
    if (index.column() == 2) {
        return lpass[index.row()];
    }
    if (index.column() == 3) {
        return lpriv[index.row()];
    }
    if (index.column() == 4) {
        return lhotel[index.row()];
    }
    return QVariant();
}
QVariant PModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString("CIN");
        }
        if (section == 1) {
            return QString("Nom d'utilisateur");
        }
        if (section == 2) {
            return QString("Mot de passe");
        }
        if (section == 3) {
            return QString("Privilege");
        }
        if (section == 4) {
            return QString("Lieu de travail");
        }
    }
    return QVariant();
}
void gestionpersonnel::LoadTableData(QList<QString> &cinp,QList<QString> &login,QList<QString> &pass,QList<QString> &priv, QList<QString> &hotel){
    QSqlQuery qrry;
    QString q ="SELECT p.cinP ,p.login ,p.password ,p.is_admin ,h.nom FROM personnel p,hotel h where p.idhotel = h.idhotel";
    qrry.prepare(q);
    qrry.exec();
    while(qrry.next()){
        QString ch="";
        cinp.append(qrry.value(0).toString());
        login.append(qrry.value(1).toString());
        for(int i=0;i<qrry.value(2).toString().length();i++){
            ch+="*";
        }
        pass.append(ch);
        if(qrry.value(3).toInt() == 0){
            priv.append("Utilisateur Normal");
        }
        else {
            priv.append("Administrateur");
        }
        hotel.append(qrry.value(4).toString());
    }
}

void gestionpersonnel::on_pushButtonsearch_2_clicked()
{
    QList<QString> cin_list;
    QList<QString> login_list;
    QList<QString> pass_list;
    QList<QString> priv_list;
    QList<QString> hotel_list;
    hoteldb *db = new hoteldb();
    QSqlDatabase conn = db->DBConnect();
    if(!ui->lineEditsearch_2->text().isEmpty()){
            ui->tableView_2->model()->~QAbstractItemModel();
            LoadTableDataFromSearch(cin_list,login_list,pass_list,priv_list,hotel_list);
            PModel *PersonnelModel = new PModel(this);
            PersonnelModel->populateData(cin_list,login_list,pass_list,priv_list,hotel_list);
            ui->tableView_2->setModel(PersonnelModel);
    }
    else {
        ui->tableView_2->model()->~QAbstractItemModel();
        LoadTableData(cin_list,login_list,pass_list,priv_list,hotel_list);
        PModel *PersonnelModel = new PModel(this);
        PersonnelModel->populateData(cin_list,login_list,pass_list,priv_list,hotel_list);
        ui->tableView_2->setModel(PersonnelModel);
    }
    db->DBDisconnect(conn);
}
void gestionpersonnel::LoadTableDataFromSearch(QList<QString> &cinp,QList<QString> &login,QList<QString> &pass,QList<QString> &priv, QList<QString> &hotel){
    QSqlQuery qrry;
    QString q ="SELECT p.cinP ,p.login ,p.password ,p.is_admin ,h.nom FROM personnel p,hotel h WHERE ( p.idhotel = h.idhotel ) AND ( p.cinP = :cinp";

    if(ui->checkBoxnom_2->isChecked()){
        q+=" OR p.login = :login";
    }
    if(ui->checkBoxprenom_2->isChecked()){
        q+=" OR h.nom = :nhotel";
    }
    if(ui->checkBoxad->isChecked()){
        q+=" OR p.is_admin =:ad";
    }
    if(ui->checkBoxun->isChecked()){
        q+=" OR p.is_admin = :un";
    }
    q+=" )";
    qrry.prepare(q);
    qrry.bindValue(":cinp",ui->lineEditsearch_2->text());
    qrry.bindValue(":login",ui->lineEditsearch_2->text());
    qrry.bindValue(":nhotel",ui->lineEditsearch_2->text());
    qrry.bindValue(":ad",1);
    qrry.bindValue(":un",0);
    qDebug()<<q;
    bool rslt = qrry.exec();
    qDebug()<<rslt;
    while(qrry.next()){
        QString ch="";
        cinp.append(qrry.value(0).toString());
        login.append(qrry.value(1).toString());
        for(int i=0;i<qrry.value(2).toString().length();i++){
            ch+="*";
        }
        pass.append(ch);
        if(qrry.value(3).toInt() == 0){
            priv.append("Utilisateur Normal");
        }
        else {
            priv.append("Administrateur");
        }
        hotel.append(qrry.value(4).toString());
    }
}

void gestionpersonnel::on_pushButton_Delete_2_clicked()
{
    if(ui->tableView_2->selectionModel()->currentIndex().isValid()){
        ui->label_status->clear();
        ui->label_status->hide();
        QItemSelectionModel *select = ui->tableView_2->selectionModel();
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Hotel PACEL");
        msgBox.setPalette(this->palette());
        msgBox.setText("Veuillez confirmer la suppression de "+select->selectedRows(1).value(0).data().toString());
        QAbstractButton* pButtonYes = msgBox.addButton(tr("Confirmer"), QMessageBox::YesRole);
        msgBox.addButton(tr("Annuler"), QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton()==pButtonYes) {
            hoteldb *db = new hoteldb();
            QSqlDatabase conn = db->DBConnect();
            personnel::SuppPersonnel(select->selectedRows(0).value(0).data().toString());
            personnel::WriteToLogFile("["+QDateTime::currentDateTime().toString("dd-MM-yyyy  HH:mm:ss")+"] Suppression du personnel "+select->selectedRows(1).value(0).data().toString()+" par "+ui->labelusr_2->text());
            //client::SuppClient(select->selectedRows(0).value(0).data().toString());
            select->clearSelection();
            select->clearCurrentIndex();
            QList<QString> cin_list;
            QList<QString> login_list;
            QList<QString> pass_list;
            QList<QString> priv_list;
            QList<QString> hotel_list;
            LoadTableData(cin_list,login_list,pass_list,priv_list,hotel_list);
            db->DBDisconnect(conn);
            PModel *PersonnelModel = new PModel(this);
            PersonnelModel->populateData(cin_list,login_list,pass_list,priv_list,hotel_list);
            ui->tableView_2->setModel(PersonnelModel);
            //loadTable();
            db->DBDisconnect(conn);
        }


    }
    else {
        ui->label_status->setText("Veuillez selectionner un personnel");
        ui->label_status->show();
    }
}

void gestionpersonnel::on_pushButton_Add_2_clicked()
{
    AP = new ajoutpersonnel(this);
    AP->setusername(ui->labelusr_2->text());
    AP->setpriv(ui->labeladm_2->text());
    AP->show();
    hide();
}

void gestionpersonnel::on_pushButton_Edit_2_clicked()
{
    QItemSelectionModel *select = ui->tableView_2->selectionModel();
    qDebug()<< select->currentIndex().isValid();
    qDebug()<<select->selectedRows(0).value(0).data().toString();
    qDebug()<<select->selectedRows(1).value(0).data().toString();
    qDebug()<<select->selectedRows(2).value(0).data().toString();
    qDebug()<<select->selectedRows(3).value(0).data().toString();
    qDebug()<<select->selectedRows(4).value(0).data().toString();
    if(select->currentIndex().isValid()){
        ui->label_status->clear();
        ui->label_status->hide();
        MP = new modifpersonnel(this);
        MP->setusername(ui->labelusr_2->text());
        MP->setpriv(ui->labeladm_2->text());
        MP->setinfo1(select->selectedRows(0).value(0).data().toString());
        MP->setinfo2(select->selectedRows(1).value(0).data().toString());
        MP->setinfo3(select->selectedRows(2).value(0).data().toString());
        MP->setinfo4(select->selectedRows(3).value(0).data().toString());
        MP->setinfo5(select->selectedRows(4).value(0).data().toString());
        MP->show();
        hide();
    }
    else {
        ui->label_status->setText("Veuillez selectionner un personnel");
        ui->label_status->show();

    }
    select->clearSelection();
    select->clearCurrentIndex();


}
