#ifndef MODIFCLIENT_H
#define MODIFCLIENT_H

#include <QMainWindow>

namespace Ui {
class modifclient;
}

class modifclient : public QMainWindow
{
    Q_OBJECT

public:
    explicit modifclient(QWidget *parent = nullptr);
    void setinfo1(QString);
    void setinfo2(QString);
    void setinfo3(QString);
    void setinfo4(QString);
    void setinfo5(QString);
    void setusername(QString);
    void setpriv(QString);
    ~modifclient();

private slots:
    void on_pushButtonrtr_clicked();

    void on_pushButtondelete_clicked();

    void on_pushButtonsave_clicked();

private:
    Ui::modifclient *ui;
};

#endif // MODIFCLIENT_H
