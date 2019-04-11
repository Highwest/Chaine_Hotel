#ifndef PARAMETRECOURANT_H
#define PARAMETRECOURANT_H

#include <QMainWindow>

namespace Ui {
class ParametreCourant;
}

class ParametreCourant : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParametreCourant(QWidget *parent = nullptr);
    ~ParametreCourant();
    void setusername(QString);
    void setuserpass(QString);
    void setuserhotel(QString);
    void extracthotels();

private slots:
    void on_mdfbtn1_clicked();

    void on_ok1btn_clicked();

    void on_savebtn1_clicked();

    void on_pushButton_3_clicked();

    void on_ok1btn_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_ok1btn_3_clicked();

    void on_pushButton_clicked();

    void on_rturnbtn_clicked();

private:
    Ui::ParametreCourant *ui;
};

#endif // PARAMETRECOURANT_H
