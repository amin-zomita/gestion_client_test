#ifndef GCLINET_H
#define GCLINET_H

#include <QMainWindow>
#include "clientmanager.h"
#include"QMessageBox"
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class Gclinet;
}
QT_END_NAMESPACE

class Gclinet : public QMainWindow
{
    Q_OBJECT

public:
    Gclinet(QWidget *parent = nullptr);
    ~Gclinet();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_validerClient_clicked();

    void on_anuulerClient_clicked();

    void updateTime(); // Function to update time

    void on_suppclient_clicked();

    void on_modifierClient_clicked();

private:
    Ui::Gclinet *ui;
    ClientManager Client;  // Déclaration de l'objet
    QTimer *timer; // Timer for updating time
};
#endif // GCLINET_H
