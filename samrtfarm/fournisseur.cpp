#include "fournisseur.h"
#include <QDebug>
#include "connexion.h"


fournisseur::fournisseur()
{
    idFour = 0;
    numero = 0;
    nom = "";
    type = "";
    description = "";
    email = "";

}

fournisseur::fournisseur(int idFour,int numero,QString nom,QString type,QString email,QString description)
{
    this->idFour=idFour;
    this->numero=numero;
    this->nom=nom;
    this->type=type;
    this->description=description;
    this->email=email;

}

int fournisseur::get_idFour()
{
    return idFour;
}
int fournisseur::get_numero()
{
    return numero;
}
QString fournisseur::get_nom()
{
    return nom;
}
QString fournisseur::get_type()
{
    return type;
}
QString fournisseur::get_description()
{
    return description;
}
QString fournisseur::get_email()
{
    return email;
}


bool fournisseur::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO FOURNISSEUR (ID_FOUR,NOM,EMAIL_FOUR,TYPE_FOUR,DESCRIPTION,NUMERO) "
                  "VALUES (:idFour,:nom, :email, :type, :description, :numero)");
    query.bindValue(":idFour", idFour);
    query.bindValue(":nom", nom);
    query.bindValue(":email", email);
    query.bindValue(":type", type);
    query.bindValue(":description", description);
    query.bindValue(":numero", numero);


    return    query.exec();
}


QSqlQueryModel * fournisseur::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from FOURNISSEUR");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("E-Mail "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Description "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("numero "));

    return model;
}

fournisseur fournisseur::recupererFour(int idd1)
{
    QSqlQuery * query = new QSqlQuery;
    QString res= QString::number(idd1);
    query->prepare("select * from FOURNISSEUR where ID_FOUR= :idFour ");
    query->bindValue(":idFour", res);
    query->exec();
    while(query->next())
    {
        int idd2=query->value(0).toInt();
        int numero2=query->value(5).toInt();
        QString nom2=query->value(1).toString();
        QString type2=query->value(3).toString();
        QString description2=query->value(4).toString();
        QString email2=query->value(2).toString();
        fournisseur f(idd2,numero2,nom2,type2 ,email2,description2);

        return f;
    }
}


QVector<int> fournisseur::IDFour()
{
    QSqlQuery * query = new QSqlQuery;
    query->prepare("select ID_FOUR from FOURNISSEUR");
    query->exec();
    QVector<int> tab;
    while(query->next())
    {
        tab.push_back(query->value(0).toInt());
    }
    return tab;
}

QVector<int> fournisseur::genererID()
{
    QVector<int> idBase;
    QVector<int> tabId;
    int id = 1;int limit = 5;
    QSqlQuery * query = new QSqlQuery;
    query->prepare("select ID_FOUR from FOURNISSEUR");
    query->exec();
    while(query->next())
    {
        idBase.push_back(query->value(0).toInt());
    }
    while (limit != 0) {


       if(!idBase.contains(id) && !tabId.contains(id))
        {
            tabId.push_back(id);
            limit--;
        }
       id++;

    }
    return tabId;
}

bool fournisseur::Modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE FOURNISSEUR SET "
                  "NOM = :nom2,EMAIL_FOUR = :email2,TYPE_FOUR = :type2,"
                  "DESCRIPTION = :description2,NUMERO = :numero2 WHERE(ID_FOUR = :idFour2)");
    query.bindValue(":idFour2", idFour);
    query.bindValue(":nom2", nom);
    query.bindValue(":email2", email);
    query.bindValue(":type2", type);
    query.bindValue(":description2", description);
    query.bindValue(":numero2", numero);


    return    query.exec();
}


bool fournisseur::supprimer(int idf)
{
    QSqlQuery query;
    QString res= QString::number(idf);
    query.prepare("Delete from FOURNISSEUR where ID_FOUR = :idFour ");
    query.bindValue(":idFour", res);

    return  query.exec();
}


QSqlQueryModel * fournisseur::chercher_Fournisseur(QString nom)

{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from FOURNISSEUR where nom like :nom OR ID_FOUR like :nom OR DESCRIPTION like :nom OR TYPE_FOUR like :nom ");
    query.bindValue(":nom", "%"+nom+"%");

    query.exec();

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("E-Mail "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Description "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("numero "));

    return model;
}


QSqlQueryModel * fournisseur::trier(QString attribut)
{
    // trier fournisseur
    QSqlQueryModel * model=new QSqlQueryModel() ;
    model->setQuery("select * from FOURNISSEUR order by "+attribut+" ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("E-Mail "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Description "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("numero "));

    return model;
}


