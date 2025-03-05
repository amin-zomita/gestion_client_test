#include "gclinet.h"
#include "clientmanager.h"
#include "./ui_gclinet.h"

Gclinet::Gclinet(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gclinet)


{

    if (!ui) {
        qDebug() << "Erreur : ui n'a pas été alloué correctement.";
    }
    if (!parent) {
        qDebug() << "Attention : parent est nul.";
    }

    ui->setupUi(this);
    qDebug() << "UI setup completed!";
    // Active les couleurs alternées pour les lignes
    ui->tableView->setAlternatingRowColors(true);

    ui->tableView->setModel(Client.afficher());


    // Connecter le bouton "Ajouter" à la fonction qui gère l'insertion du client
    connect(ui->validerClient, &QPushButton::clicked, this, &Gclinet::on_validerClient_clicked);

    ui->stackedWidget->setCurrentWidget(ui->page);

    // Create and start the timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000); // Update every 1000ms (1 second)

    updateTime(); // Call once immediately to display the current time


    // Set placeholder text for search
    ui->lineEdit->setPlaceholderText("Recherher...");
    // set placeholder for client delete
    ui->lineEdit_2->setPlaceholderText("ID...");

}

Gclinet::~Gclinet()
{


    delete ui;
}

void Gclinet::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);

}


void Gclinet::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void Gclinet::on_validerClient_clicked()
{
    //recuperation des informations
    int id_client = ui->IDC->text().toInt();
    QString nom = ui->nomClient_2->text();
    QString prenom = ui->prenomClient_2->text();
    QString email = ui->emailClient_2->text();
    QString num_tlf = ui->numClient_2->text();
    int nb_projet = ui->nbcProjet_2->value();  // Récupérer la valeur du QSlider

    ClientManager CL(id_client,nom,prenom,email,num_tlf,nb_projet);

    bool test=CL.ajouter();

    if(test)
    {
        //refrech(actualiser)
        ui->tableView->setModel(Client.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                    QObject::tr("ajout effectue\n"
                                             "click exit"), QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                 QObject::tr("ajout non  effectue\n"
                                             "click exit"), QMessageBox::Cancel);

    }

}


void Gclinet::on_anuulerClient_clicked()
{
    QMessageBox::warning(this,"information","cette action va annuler l'ajout de ce clinet" );

}

void Gclinet::updateTime() {
    // Get the current system time
    QTime currentTime = QTime::currentTime();

    // Format it as HH:MM:SS
    QString timeText = currentTime.toString("hh:mm:ss");

    // Update the label in the UI
    ui->label_time->setText(timeText);
}


void Gclinet::on_suppclient_clicked()
{
    int id_client = ui->lineEdit_2->text().toInt();
    bool test=Client.supprimer(id_client);

    if(test){
        //refrech(actualiser)
        ui->tableView->setModel(Client.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("suppresion effectue\n"
                                             "click exit"), QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("ajout non  effectue\n"
                                          "click exit"), QMessageBox::Cancel);
    }
}


void Gclinet::on_modifierClient_clicked()
{
    // Récupération des informations saisies
    int id_client = ui->IDC->text().toInt();
    QString nom = ui->nomClient_2->text();
    QString prenom = ui->prenomClient_2->text();
    QString email = ui->emailClient_2->text();
    QString num_tlf = ui->numClient_2->text();
    int nb_projet = ui->nbcProjet_2->value();  // Récupérer la valeur du QSpinBox/QSlider

    // Vérifier si les champs obligatoires sont remplis
    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || num_tlf.isEmpty()) {
        QMessageBox::warning(this, "Champs vides", "Veuillez remplir tous les champs.");
        return;
    }

    // Création de l'objet client avec les nouvelles valeurs
    ClientManager CL(id_client, nom, prenom, email, num_tlf, nb_projet);

    // Appel de la fonction modifier()
    bool test = CL.modifier();

    if (test) {
        // Rafraîchir le tableau après la modification
        ui->tableView->setModel(CL.afficher());
        QMessageBox::information(this, "Succès", "Modification effectuée avec succès !");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du client.");
    }
}

