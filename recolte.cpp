#include "recolte.h"
#include <QString>
#include <QDebug>
#include <QTabWidget>
#include <QDateEdit>
#include <QDate>
#include "connection.h"




Recolte::Recolte()
{
    ID_RECOLTE = 0;
    CULTURE="";
    MASSE=0.0;
    PRIX= 0.0;





}

Recolte::Recolte(int ID_RECOLTE, QString CULTURE, float MASSE,  float PRIX)

{    this->ID_RECOLTE=ID_RECOLTE;
     this->CULTURE=CULTURE;
    this->PRIX=PRIX;
    this->MASSE=MASSE;


}
    int Recolte ::get_ID_RECOLTE(){return ID_RECOLTE;}
    QString Recolte::get_CULTURE(){return  CULTURE;}
     float Recolte::get_MASSE(){return  MASSE;}

     float Recolte::get_PRIX(){return  PRIX;}

bool Recolte::ajouter_recolte()
{
        QSqlQuery query;
        QString M ;
        M.setNum(MASSE);
        QString P ;
        P.setNum(PRIX);
        QString res= QString::number(ID_RECOLTE);

      query.prepare("INSERT INTO RECOLTE (CULTURE,MASSE,PRIX) "
                    "VALUES (:CULTURE,:MASSE,:PRIX )");

          query.bindValue(":ID_RECOLTE", res);

            query.bindValue(":CULTURE", CULTURE);
            query.bindValue(":MASSE", M);

           query.bindValue(":PRIX", P);

           return    query.exec();
}


QSqlQueryModel * Recolte::afficher_recolte()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from RECOLTE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RECOLTE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("CULTURE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MASSE "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));


        return model;
}

bool Recolte::supprimer_recolte(int ID_RECOLTE)
{
    QSqlQuery query;
    QString res= QString::number(ID_RECOLTE);
    query.prepare("Delete from RECOLTE where ID_RECOLTE = :ID_RECOLTE");
    query.bindValue(":ID_RECOLTE", res);
    return    query.exec();
}


bool Recolte :: modifier_recolte (int cod)
{

    QSqlQuery query;
    //QString::number(MASSE);
    QString P=QString::number(PRIX) ;
    QString M=QString::number(MASSE) ;
    P.setNum(PRIX);
    M.setNum(MASSE);
    //QString::number(PRIX);
    QString res= QString::number(cod);

    query.prepare("UPDATE RECOLTE SET CULTURE=:CULTURE, MASSE=:MASSE ,PRIX=:PRIX where ID_RECOLTE=:cod ");
    query.bindValue(":CULTURE", CULTURE);
    query.bindValue(":PRIX", P);
    query.bindValue(":MASSE", M);

    query.bindValue(":cod", res);

     return    query.exec();
}

QSqlQueryModel * Recolte::tri_recolte()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from RECOLTE order by PRIX ASC");
    return model;
}

QSqlQueryModel * Recolte::tri_recolteDESC()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from RECOLTE order by PRIX DESC");
    return model;
}
