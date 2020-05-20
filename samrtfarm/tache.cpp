#include "tache.h"
#include <QDebug>
#include "connexion.h"
#include <QDate>
tache::tache()
{
id=0;
nom="";
description="";


statut ="";
cin="";
type="";
}
tache::tache( int id, QString nom,QString description ,QString type ,QDate date_limit , QDate date_deb ,QString statut, QString cin)
{
  this->id=id;
  this->nom=nom;
  this->description=description;
  this->statut=statut;
this->date_deb=date_deb;
  this->date_limit=date_limit;
    this->cin=cin;
      this->type=type;
}
int tache::get_id(){return  id;}
QString tache::get_nom(){return  nom;}
QString tache::get_description(){return description;}

QDate tache::get_date_limit(){return  date_limit ;}
QString tache::get_statut(){return  statut ;}

bool tache::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO tache (ID_TACHE, NOM, DESCRIPTION, DATE_DEBUT, DATE_LIMIT, STATUT ,CIN_EMPLOYE  ,type) "
                    "VALUES (:id, :nom, :description , :date_deb , :date_limit , :statut , :cin , :type)");
query.bindValue(":id", id);
query.bindValue(":nom", nom);
query.bindValue(":description", description);
// QDate d = QDate::currentDate() ;
query.bindValue(":date_deb", date_deb);
query.bindValue(":date_limit", date_limit);
query.bindValue(":statut", statut);
query.bindValue(":cin", cin);
query.bindValue(":type", type);
return    query.exec();
}

QSqlQueryModel * tache::afficher(QString tri2, QString stat)
{   QSqlQueryModel * model= new QSqlQueryModel();

    if (stat=="Tous"  || stat=="" )
         if (tri2=="")  model->setQuery("select * from tache");
         else model->setQuery("select * from tache order by ID_TACHE "+tri2+" ");
    else
        if (tri2=="")  model->setQuery("select * from tache where   (STATUT LIKE '"+stat+"%' )      ");
        else model->setQuery("select * from tache  where (STATUT LIKE '"+stat+"%' )    order by ID_TACHE "+tri2+" ");



model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_TACHE"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_DEBUT"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_LIMIT"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("STATUT"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("TYPE"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("CIN_EMPLOYE"));
    return model;
}
QSqlQueryModel * tache::rechercher(QString n, QString tri , QDate d) {
    QSqlQuery query;


        QSqlQueryModel * model=new QSqlQueryModel();


      if (tri !="")

               model->setQuery("select * from tache where (nom LIKE '"+n+"%' ) order by nom "+tri+" ");
             else




  model->setQuery("select * from tache where ((nom LIKE '"+n+"%' ) ");


                return  model;







}









bool tache::supprimer(int ref)
{QSqlQuery query;


//QString res= QString::number(c);
query.prepare("Delete from tache where ID_TACHE = :id ");
query.bindValue(":id", ref);

 query.exec();
 return query.numRowsAffected() ;



}




bool tache::modifier( int id, QString nom,QString description ,QString type ,QDate date_limit , QDate date_deb ,QString statut, QString cin)
{ QSqlQuery query;

    query.prepare("UPDATE tache SET CIN_EMPLOYE =:cin ,NOM=:nom , DESCRIPTION=:description, DATE_DEBUT=:date_deb , DATE_LIMIT =:date_limit, STATUT= :statut  , TYPE=:type    where  ID_TACHE=:id");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":description",description);
     query.bindValue(":date_deb",date_deb);
     query.bindValue(":date_limit",date_limit);
      query.bindValue(":statut",statut);
            query.bindValue(":type",type);
                  query.bindValue(":cin",cin);
     query.exec();
return query.numRowsAffected() ;}









