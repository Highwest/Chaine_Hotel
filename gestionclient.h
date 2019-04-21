#ifndef GESTIONCLIENT_H
#define GESTIONCLIENT_H

#include <QMainWindow>
#include "ajoutclient.h"
#include "modifclient.h"

namespace Ui {
class GestionClient;
}

class GestionClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit GestionClient(QWidget *parent = nullptr);
    ~GestionClient();
    void setLabelusr(QString);
    void setLabeladm(QString);
    void loadTable();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_Edit_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButtonsearch_clicked();

    void on_pushButton_Add_clicked();

private:
    Ui::GestionClient *ui;
    ajoutclient *AC;
    modifclient *MC;

};

#endif // GESTIONCLIENT_H
