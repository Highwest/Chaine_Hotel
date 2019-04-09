#ifndef CHAINEHOTEL_H
#define CHAINEHOTEL_H

#include <QMainWindow>
#include "tableaudebord.h"

namespace Ui {
class ChaineHotel;
}

class ChaineHotel : public QMainWindow
{
Q_OBJECT

public:
explicit ChaineHotel(QWidget *parent = nullptr);
~ChaineHotel();

private slots:

    void on_pushButton_connexion_clicked();

private:
Ui::ChaineHotel *ui;
TableauDeBord *D;


};

#endif // CHAINEHOTEL_H
