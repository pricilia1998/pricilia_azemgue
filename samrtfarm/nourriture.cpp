#include "nourriture.h"
#include <QDebug>
#include "connexion.h"
#include <qmetatype.h>

nourriture::nourriture()
{
    idNour = 0;
    quantite = 0;
    nom = "";
    type = "";
    description = "";
    montant = "";
    fournisseur = "";
    dateExp = "";
    dateAch = "";
}

nourriture::nourriture(int idNour,int quantite,QString nom,QString type,QString description,QString montant,QString fournisseur,QString dateExp,QString dateAch )
{
     this->idNour=idNour;
     this->quantite=quantite;
     this->nom=nom;
     this->type=type;
     this->description=description;
     this->montant=montant;
     this->fournisseur=fournisseur;
     this->dateExp=dateExp;
     this->dateAch=dateAch;
}

int nourriture::get_idNour()
{
    return idNour;
}
int nourriture::get_quantite()
{
    return quantite;
}
QString nourriture::get_nom()
{
    return nom;
}
QString nourriture::get_type()
{
    return type;
}
QString nourriture::get_description()
{
    return description;
}
QString nourriture::get_montant()
{
    return montant;
}
QString nourriture::get_fournisseur()
{
    return fournisseur;
}
QString nourriture::get_dateExp()
{
    return dateExp;
}
QString nourriture::get_dateAch()
{
    return dateAch;
}


bool nourriture::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO NOURRITURE (ID_NOUR,NOM,QUANTITE,DATE_EXPIR,TYPE_NOUR, DATE_ACHAT,FOURNISSEUR,MONTANT,DESCRIPTION) "
                    "VALUES (:idNour,:nom, :quantite, :dateExp, :type, :dateAch, :fournisseur, :montant, :description)");
query.bindValue(":idNour", idNour);
query.bindValue(":nom", nom);
query.bindValue(":quantite", quantite);
query.bindValue(":dateExp", dateExp);
query.bindValue(":type", type);
query.bindValue(":dateAch", dateAch);
query.bindValue(":fournisseur", QString(fournisseur).toInt());
query.bindValue(":montant",montant );
query.bindValue(":description", description);


return    query.exec();
}

QVector<int> nourriture::genererID()
{
    QVector<int> idBase1;
    QVector<int> tabId1;
    int idd = 1;int limit = 5;
    QSqlQuery * query = new QSqlQuery;
    query->prepare("select ID_NOUR from NOURRITURE");
    query->exec();
    while(query->next())
    {
        idBase1.push_back(query->value(0).toInt());
    }
    while (limit != 0) {


       if(!idBase1.contains(idd) && !tabId1.contains(idd))
        {
            tabId1.push_back(idd);
            limit--;
        }
       idd++;

    }
    return tabId1;
}

QSqlQueryModel * nourriture::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from NOURRITURE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantité "));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Montant "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Fournisseur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_Expiration "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_Achat "));

        return model;
}



nourriture nourriture::recupererNour(int id1)
{
    QSqlQuery * query = new QSqlQuery;
    QString res= QString::number(id1);
    query->prepare("select * from NOURRITURE where ID_NOUR= :idNour ");
    query->bindValue(":idNour", res);
    query->exec();
    while(query->next())
       {
        int id2=query->value(0).toInt();
        int quantite1=query->value(2).toInt();
        QString nom1=query->value(1).toString();
        QString type1=query->value(4).toString();
        QString description1=query->value(8).toString();
        QString montant1=query->value(7).toString();
        QString fournisseur1=query->value(6).toString();
        QString dateExp1=query->value(3).toString();
        QString dateAch1=query->value(5).toString();
        nourriture n(id2,quantite1,nom1,type1,description1,montant1,fournisseur1,dateExp1,dateAch1);

        return n;
       }
}


bool nourriture::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from NOURRITURE where ID_NOUR = :idNour ");
query.bindValue(":idNour", res);

return  query.exec();
}


bool nourriture::Modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE NOURRITURE SET "
                  "NOM = :nom1,QUANTITE = :quantite1,DATE_EXPIR = :dateExp1,"
                  "TYPE_NOUR= :type1 ,DATE_ACHAT = :dateAch1,FOURNISSEUR= :fournisseur1 ,"
                  "MONTANT = :montant1,DESCRIPTION = :description1 WHERE(ID_NOUR = :idNour1)");
    query.bindValue(":idNour1", idNour);
    query.bindValue(":nom1", nom);
    query.bindValue(":quantite1", quantite);
    query.bindValue(":dateExp1", dateExp);
    query.bindValue(":type1", type);
    query.bindValue(":dateAch1", dateAch);
    query.bindValue(":fournisseur1", QString(fournisseur).toInt());
    query.bindValue(":montant1",montant );
    query.bindValue(":description1", description);

    return    query.exec();
}

QSqlQueryModel * nourriture::chercher_Nourriture(QString nom)

{
    QSqlQueryModel * model= new QSqlQueryModel();
QSqlQuery query;
query.prepare("select * from NOURRITURE where nom like :nom OR ID_NOUR like :nom OR QUANTITE like :nom OR DESCRIPTION like :nom ");
query.bindValue(":nom", "%"+nom+"%");

query.exec();

model->setQuery(query);
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantité "));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("Montant "));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Fournisseur"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_Expiration "));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_Achat "));

    return model;
}


QSqlQueryModel * nourriture::trier(QString attribut)
{
    // trier nourriture
    QSqlQueryModel * model=new QSqlQueryModel() ;
    model->setQuery("select * from NOURRITURE order by "+attribut+" ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantité "));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Montant "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Fournisseur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_Expiration "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_Achat "));

        return model;
}



