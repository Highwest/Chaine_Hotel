#ifndef AJOUTPERSONNEL_H
#define AJOUTPERSONNEL_H

#include <QMainWindow>

namespace Ui {
class ajoutpersonnel;
}

class ajoutpersonnel : public QMainWindow
{
    Q_OBJECT

public:
    explicit ajoutpersonnel(QWidget *parent = nullptr);
    void setusername(QString);
    void setpriv(QString);
    void extracthotels();
    ~ajoutpersonnel();

private slots:
    void on_pushButtonrtr_clicked();

    void on_pushButtonefface_clicked();

    void on_pushButtonajt_clicked();

private:
    Ui::ajoutpersonnel *ui;
};

#endif // AJOUTPERSONNEL_H
