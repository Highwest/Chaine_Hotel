#ifndef GESTIONPERSONNEL_H
#define GESTIONPERSONNEL_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include "ajoutpersonnel.h"
#include "modifpersonnel.h"

namespace Ui {
class gestionpersonnel;
}
class PModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    PModel(QObject *parent = 0);

    void populateData(const QList<QString> &cinp,const QList<QString> &login,const QList<QString> &pass,const QList<QString> &priv,const QList<QString> &hotel);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private:
    QList<QString> lcin;
    QList<QString> llogin;
    QList<QString> lpass;
    QList<QString> lpriv;
    QList<QString> lhotel;

};
class gestionpersonnel : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestionpersonnel(QWidget *parent = nullptr);
    void setLabelusr(QString);
    void setLabeladm(QString);
    void LoadTableData(QList<QString> &cinp,QList<QString> &login,QList<QString> &pass,QList<QString> &priv, QList<QString> &hotel);
    void LoadTableDataFromSearch(QList<QString> &cinp,QList<QString> &login,QList<QString> &pass,QList<QString> &priv, QList<QString> &hotel);
    //void loadTable();
    ~gestionpersonnel();

private slots:
    void on_pushButton_clicked();

    void on_pushButtonsearch_2_clicked();

    void on_pushButton_Delete_2_clicked();

    void on_pushButton_Add_2_clicked();

    void on_pushButton_Edit_2_clicked();

private:
    Ui::gestionpersonnel *ui;
    ajoutpersonnel *AP;
    modifpersonnel *MP;
};

#endif // GESTIONPERSONNEL_H
