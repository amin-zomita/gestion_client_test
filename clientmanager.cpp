#include "clientmanager.h"
#include <QDebug>
#include <QString>


ClientManager::ClientManager(int id_client,QString nom,QString prenom,QString email,QString num_tlf,int nb_projet)
{
    this->id_client=id_client;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->num_tlf=num_tlf;
    this->nb_projet=nb_projet;

}

bool ClientManager::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id_client);

    query.prepare("insert into Client (id_client, nom, prenom, email, num_tlf, nb_projet)" "values (:id_client, :nom, :prenom, :email, :num_tlf, :nb_projet)");

    //creation des variables liees
    query.bindValue(":id_client",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":num_tlf",num_tlf);
    query.bindValue(":nb_projet",nb_projet);

    return query.exec(); // exec() envoie la requéte pour l'exécuter
}

//suppression

bool ClientManager::supprimer(int id_client)
{
    QSqlQuery query;
    QString res=QString::number(id_client);

    query.prepare("Delete from Client where Id_client= :id_client");
    query.bindValue(":id_client",res);
    return query.exec();

}

QSqlQueryModel * ClientManager::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Client");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_client"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("num_tlf"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("nb_projet"));

    return model;

}


bool ClientManager::modifier()
{
    QSqlQuery query;
    QString res = QString::number(id_client);

    query.prepare("UPDATE Client SET nom=:nom, prenom=:prenom, email=:email, num_tlf=:num_tlf, nb_projet=:nb_projet WHERE id_client=:id_client");

    query.bindValue(":id_client", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":num_tlf", num_tlf);
    query.bindValue(":nb_projet", nb_projet);

    return query.exec();
}






