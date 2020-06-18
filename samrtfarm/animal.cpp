#include "animal.h"
#include <QDebug>
#include "connexion.h"
#include <qmetatype.h>

animal::animal()
{
    idAnimal = 0;

    nom = "";
    type = "";
    sexe = "";
    description = "";

   // date_de_naissance= ;
}

animal::animal(int idAnimal,QString nom,QString type,QString sexe,QString description,QDate date_de_naissance)
{
     this->idAnimal=idAnimal;

     this->nom=nom;
     this->type=type;
    this->sexe=sexe;
     this->description=description;

     this->date_de_naissance=date_de_naissance;
}

int animal::get_idAnimal()
{
    return idAnimal;
}

QString animal::get_nom()
{
    return nom;
}
QString animal::get_type()
{
    return type;
}

QString animal::get_sexe()
{
    return sexe ;
}



QString animal::get_description()
{
    return description;
}

QDate animal::get_date_de_naissance()
{
    return date_de_naissance;
}


bool animal::ajouter( )
{
QSqlQuery querytest,query;
querytest.prepare("select * from animal where nom=:nom");
querytest.bindValue(":nom", nom);
querytest.exec();
int count=0;
while(querytest.next())
{
    count++;
}
if(count==0){


query.prepare("INSERT INTO ANIMAL (ID_ANIMAL,NOM,TYPE, SEXE,DESCRIPTION,DATE_DE_NAISSANCE) "
                    "VALUES (:idAnimal, :nom, :type, :sexe, :description,  :date_de_naissance)");
query.bindValue(":idAnimal", idAnimal);
query.bindValue(":nom", nom);
query.bindValue(":type", type);
query.bindValue(":sexe", sexe);
query.bindValue(":description", description);
query.bindValue(":date_de_naissance", date_de_naissance);
return    query.exec();
}
else{
    return false;
}
}

bool animal::testNom(QString nom)
{
    QSqlQuery querytest;
    querytest.prepare("select * from animal where nom=:nom");
    querytest.bindValue(":nom", nom);
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




QSqlQueryModel * animal::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from ANIMAL");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Sexe "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Description "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_de_naissance"));

        return model;
}

animal animal::recupererAnimal(int id1)
{
    QSqlQuery * query = new QSqlQuery;
    QString res= QString::number(id1);
    query->prepare("select * from ANIMAL where ID_ANIMAL= :idAnimal ");
    query->bindValue(":idAnimal", res);
    query->exec();

    while(query->next())
       {
        int id2=query->value(0).toInt();

        QString nom1=query->value(1).toString();
        QString type1=query->value(2).toString();
        QString sexe1=query->value(3).toString();
         QString description1=query->value(4).toString();
        QDate date_de_naissance1=query->value(5).toDate();
        animal a (id2,nom1,type1,sexe1,description1,date_de_naissance1);

        return a ;
       }
}




bool animal::supprimer(int idd)
{
    QSqlQuery querytest,query1,query;
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
        query1.prepare("select id_carte from carte inner join animal on carte.id_animal=animal.id_animal where animal.id_animal=:idAnimal");
        query1.bindValue(":idAnimal", res);
        query1.exec();
        int j=0;
        int id_carte=0;
        while(query1.next()){
            j++;
            id_carte=query1.value(0).toInt();
        }
        if(j>0){
            carte c;
            c.supprimer(id_carte);
            query.prepare("Delete from ANIMAL where ID_ANIMAL =:idAnimal ");
            query.bindValue(":idAnimal", res);
        }
        else {
            query.prepare("Delete from ANIMAL where ID_ANIMAL =:idAnimal ");
            query.bindValue(":idAnimal", res);
        }

        return  query.exec();
    }
        else{
            return false;
        }


}

bool animal::Modifier()
{
    QSqlQuery query;
    QString id_e= QString::number(idAnimal);
    query.prepare("update ANIMAL SET  NOM=:nom , TYPE=:type ,SEXE=:sexe , DESCRIPTION=:description ,DATE_DE_NAISSANCE=:date_de_naissance WHERE ID_ANIMAL=:ID");

    query.bindValue(":ID", id_e);
    query.bindValue(":nom", nom);

    query.bindValue(":type", type);
    query.bindValue(":sexe", sexe);

    query.bindValue(":description",description);
    query.bindValue(":date_de_naissance", date_de_naissance);

    return    query.exec();
}

QSqlQueryModel *animal::trie()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from animal order by  date_de_naissance ASC");
    return model;
}

QSqlQueryModel *animal::triee()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from animal order by  date_de_naissance DESC");
    return model;
}


QSqlQueryModel *animal::rechercherAnimal(QString rechAnimal)

{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from ANIMAL where nom LIKE '"+rechAnimal+"%' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Sexe "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Description "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_de_naissance"));

    return model;
}

int animal::CalculAnimalType(QString type)
{
    QSqlQuery query;
    query.prepare("select * from animal where type=:type");
    query.bindValue(":type", type);
    query.exec();
    int count=0;
    while(query.next())
    {
        count++;
    }
    return count;
}
