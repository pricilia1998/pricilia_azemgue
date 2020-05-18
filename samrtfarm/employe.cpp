#include "employe.h"
#include <QDebug>
#include "connexion.h"
#include <QMessageBox>
#include <QSqlQuery>
employe::employe()
{
cin="" ;
nom="";
prenom="";
email="";
type="";

}
employe::employe( QString cin, QString nom,QString prenom ,QString email ,QString type, QDate date )
{
  this->cin=cin;
  this->nom=nom;
  this->prenom=prenom;
  this->email=email;
  this->type=type;
  this->date=date;
}
QString employe::get_cin(){return  cin;}
QString employe::get_nom(){return  nom;}
QString employe::get_prenom(){return prenom;}
QString employe::get_email(){return  email ;}
QString employe::get_type(){return  type ;}

bool employe::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO employe (CIN, NOM, PRENOM, TYPE , EMAIL , DATE_naiss  ) "
                    "VALUES (:cin, :nom, :prenom , :type , :email, :date)");
query.bindValue(":cin", cin);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":email", email);
query.bindValue(":type", type);
query.bindValue(":date", date);


return    query.exec();
}

QSqlQueryModel * employe::afficher(QString tri)
{ QSqlQueryModel * model= new QSqlQueryModel();
    if (tri=="")  model->setQuery("select * from employe");
    else model->setQuery("select * from employe order by nom "+tri+" ");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type "));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_NAISS"));

    return model;
}

bool employe::supprimer(QString c)
{QSqlQuery query;


//QString res= QString::number(c);
query.prepare("Delete from employe where nom = :c ");
query.bindValue(":c", c);

 query.exec();
 return query.numRowsAffected() ;



}

QSqlQueryModel *  employe::rechercher(QString n, QString filtre, QString tri)
{ QSqlQuery query;

    QSqlQueryModel * model=new QSqlQueryModel();
    //QString res=QString::number(jour);

    if (tri !="")

           model->setQuery("select * from employe where ("+filtre+" LIKE '"+n+"%' ) order by "+filtre+" "+tri+" ");
         else




model->setQuery("select * from employe where ("+filtre+" LIKE '"+n+"%' ) ");



            return  model;


}



bool employe::modifier( QString cin, QString nom,QString prenom ,QString email ,QString type,QDate d   )
{ QSqlQuery query;

    query.prepare("UPDATE employe SET nom =:nom ,prenom=:prenom , email=:email, type=:type , DATE_NAISS =:d where cin=:cin");
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
     query.bindValue(":type",type);
     query.bindValue(":d",d);
      query.bindValue(":cin",cin);
     query.exec();
return query.numRowsAffected() ;
}

