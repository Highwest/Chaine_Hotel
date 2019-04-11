#ifndef TABLEAUDEBORD_H
#define TABLEAUDEBORD_H

#include <QMainWindow>
#include "parametrecourant.h"
#include "gestionclient.h"

namespace Ui {
class TableauDeBord;
}

class TableauDeBord : public QMainWindow
{
Q_OBJECT

public:
explicit TableauDeBord(QWidget *parent = nullptr);
~TableauDeBord();
void Form1();
void setUserLabel(QString);
void setPrivilegeLabel(QString,QString);
void setHotelLabel(QString,QString);
void setDateLabel();

private slots:
    void UpdateTime();
    void UpdateDate();




    void on_pushButton_Deconnexion_clicked();

    void on_pushButton_PramUser_clicked();

    void on_pushButton_GCli_clicked();

private:
Ui::TableauDeBord *ui;
QTimer *timer_1s;
QTimer *timer2;
ParametreCourant *P;
GestionClient *GC;
};

#endif // TABLEAUDEBORD_H

