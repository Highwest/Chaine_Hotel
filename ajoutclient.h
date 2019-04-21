#ifndef AJOUTCLIENT_H
#define AJOUTCLIENT_H

#include <QMainWindow>

namespace Ui {
class ajoutclient;
}

class ajoutclient : public QMainWindow
{
    Q_OBJECT

public:
    explicit ajoutclient(QWidget *parent = nullptr);
    void setusername(QString);
    void setpriv(QString);
    ~ajoutclient();

private slots:
    void on_pushButtonajt_clicked();

    void on_pushButtonefface_clicked();

    void on_pushButtonrtr_clicked();

private:
    Ui::ajoutclient *ui;
};

#endif // AJOUTCLIENT_H
