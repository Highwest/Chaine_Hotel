#ifndef MODIFPERSONNEL_H
#define MODIFPERSONNEL_H

#include <QMainWindow>

namespace Ui {
class modifpersonnel;
}

class modifpersonnel : public QMainWindow
{
    Q_OBJECT

public:
    explicit modifpersonnel(QWidget *parent = nullptr);
    void setinfo1(QString);
    void setinfo2(QString);
    void setinfo3(QString);
    void setinfo4(QString);
    void setinfo5(QString);
    void setusername(QString);
    void setpriv(QString);
    void extracthotels();
    ~modifpersonnel();

private slots:
    void on_pushButtonrtr_clicked();

    void on_pushButtondelete_clicked();

    void on_pushButton_clicked();

    void on_pushButtonsave_clicked();

private:
    Ui::modifpersonnel *ui;
};

#endif // MODIFPERSONNEL_H
