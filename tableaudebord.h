#ifndef TABLEAUDEBORD_H
#define TABLEAUDEBORD_H

#include <QMainWindow>

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



    void on_pushButton_clicked();

private:
Ui::TableauDeBord *ui;
QTimer *timer_1s;
QTimer *timer2;
};

#endif // TABLEAUDEBORD_H

