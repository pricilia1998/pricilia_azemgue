#include "carte.h"
#include <QDebug>
#include "connexion.h"


    carte::carte()
    {
        idCarte= 0;

        idAnimal=0;
        info_complementaires = "";
        poids = 0;
        taille = 0.0;
        temperature= 0.0;

       // derniere_visite = ;
    }

    carte::carte(int idCarte, QDate derniere_visite, QString info_complementaires, float poids ,float taille ,float temperature,QString nomAnimal)
    {
         this->idCarte =idCarte;

        this->nomAnimal=nomAnimal;

         this->derniere_visite=derniere_visite;
        this->info_complementaires=info_complementaires;
         this->poids =poids;
         this->taille =taille;
         this->temperature =temperature;

    }

    int carte::get_idAnimal()
    {
        return idAnimal;
    }
    void carte::set_idAnimal(int idAnimal)
    {
        this->idAnimal=idAnimal;
    }

    int carte::get_idCarte()
    {
        return idCarte;
    }



    QDate carte::get_derniere_visite()
    {
        return derniere_visite;
    }

    QString carte::get_info_complementaires()
    {
        return info_complementaires;
    }


   float carte::get_poids()
    {
        return poids ;
    }

  float carte::get_taille()
    {
        return taille;
    }


float  carte::get_temperature()
    {
        return temperature ;
    }
void carte::set_nomAnimal(QString nomAnimal)
{
    this->nomAnimal=nomAnimal;
}



bool carte::testpoids(int idCarte)
{
      QString res= QString::number(idCarte);
    QSqlQuery querytest;
    querytest.prepare("select * from carte where ID_CARTE = :idCarte");
    querytest.bindValue(":ID_CARTE",res);
    querytest.exec();
    int count=0;
    while(querytest.next())
    {
        count++;
    }
    if(count>0){
        return true;
    }
    else{
        return false;
    }
}



    bool carte::ajouterC( )
    {
    QSqlQuery query;
    QString res= QString::number(idCarte);
    QString idAnimall= QString::number(recupererIdanimal(nomAnimal));
    QString poidss= QString::number(poids);
    QString taillee= QString::number(taille);
    QString temperaturee= QString::number(temperature);


    query.prepare("INSERT INTO CARTE (ID_CARTE,DERNIERE_VISITE,INFO_COMPLEMENTAIRES,POIDS,TAILLE,TEMPERATURE,ID_ANIMAL) "
                        "VALUES (:ID_CARTE,:DERNIERE_VISITE,:INFO_COMPLEMENTAIRES,:POIDS,:TAILLE, :TEMPERATURE,:ID_ANIMAL)");


    query.bindValue(":ID_CARTE",res);
    query.bindValue(":DERNIERE_VISITE", derniere_visite);
    query.bindValue(":INFO_COMPLEMENTAIRES", info_complementaires);
    query.bindValue(":POIDS", poidss);
    query.bindValue(":TAILLE", taillee);
    query.bindValue(":TEMPERATURE", temperaturee);
    query.bindValue(":ID_ANIMAL",idAnimall);

    return    query.exec();
    }

    QSqlQueryModel * carte::afficherC()
    {
        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select carte.*,animal.nom from CARTE inner join animal on carte.id_animal=animal.id_animal");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Dernière visite "));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Info complémentaires "));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poids "));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Taille "));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Température"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Id de l'Animal"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Nom Animal"));

            return model;
    }

    int carte::recupererIdanimal(QString nom)
    {
        QSqlQuery * query = new QSqlQuery;
        query->prepare("select * from animal where nom=:nom");
        query->bindValue(":nom", nom);
        query->exec();

        while(query->next())
           {
            int id=query->value(0).toInt();
            return id ;
           }
    }

    carte carte::recupererCarte(int id1)
    {
        QSqlQuery * query = new QSqlQuery;
        QString ress= QString::number(id1);
        query->prepare("select carte.*,animal.nom from CARTE inner join animal on carte.id_animal=animal.id_animal where ID_CARTE= :idCarte ");
        query->bindValue(":idCarte", ress);
        query->exec();

        while(query->next())
           {
            int id2=query->value(0).toInt();
            QDate derniere_visite1=query->value(1).toDate();
            QString info_complementaires1=query->value(2).toString();
          int poids1=query->value(3).toInt();
          int taille1=query->value(4).toInt();
           int temperature1=query->value(5).toInt();
           QString nomanimal=query->value(6).toString();


      carte c (id2,derniere_visite1,info_complementaires1,poids1,taille1,temperature1,nomanimal);

            return c ;
           }
    }



    bool carte::supprimer(int idd)
    {
    QSqlQuery querytest,query;
    QString res= QString::number(idd);
    querytest.prepare("select * from animal where id_animal=:idAnimal");
    querytest.bindValue(":idAnimal", res);
    querytest.exec();
    int count=0;
    while(querytest.next())
    {
        count++;
    }
    if(count>0){
        query.prepare("Delete from CARTE where ID_CARTE = :idCarte");
        query.bindValue(":idCarte", res);

        return  query.exec();
    }
    else{
        return false;
    }

    }

    bool carte::Modifier()
    {
        QSqlQuery query;
        QString idAnimall= QString::number(recupererIdanimal(nomAnimal));
        QString poidss= QString::number(poids);
        QString taillee= QString::number(taille);
        QString temperaturee= QString::number(temperature);

        QString id_c= QString::number(idCarte);
        query.prepare("update CARTE SET  DERNIERE_VISITE=:derniere_visite , INFO_COMPLEMENTAIRES=:info_complementaires ,POIDS=:poids , TAILLE=:taille ,TEMPERATURE=:temperature WHERE ID_CARTE=:ID");

        query.bindValue(":ID", id_c);
        query.bindValue(":derniere_visite", derniere_visite);
        query.bindValue(":info_complementaires", info_complementaires);
        query.bindValue(":poids", poidss);
        query.bindValue(":taille",taillee);
        query.bindValue(":temperature",temperaturee);

        return    query.exec();
    }

    QSqlQueryModel *carte::trieC()
    {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("select * from carte order by  derniere_visite ASC");
        return model;
    }

    QSqlQueryModel *carte::trieeC()
    {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("select * from carte order by derniere_visite  DESC");
        return model;
    }

