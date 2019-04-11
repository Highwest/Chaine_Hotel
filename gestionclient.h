#ifndef GESTIONCLIENT_H
#define GESTIONCLIENT_H

#include <QMainWindow>

namespace Ui {
class GestionClient;
}

class GestionClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit GestionClient(QWidget *parent = nullptr);
    ~GestionClient();

private:
    Ui::GestionClient *ui;
};

#endif // GESTIONCLIENT_H
