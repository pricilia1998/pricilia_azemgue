#include "zone.h"
#include <QTabWidget>
#include <QDebug>
#include "connection.h"

Zone::Zone()
{
    ID_ZONE=0;
    DIMENSION=0.0;
    ETAT="";
    DESCRIPTION = "";


}

Zone::Zone(int ID_ZONE,int DIMENSION, QString ETAT,  QString DESCRIPTION)
{
    this->ID_ZONE=ID_ZONE;
    this->DIMENSION=DIMENSION;
    this->ETAT=ETAT;
    this->DESCRIPTION=DESCRIPTION;

}


int Zone::get_ID_ZONE(){return  ID_ZONE;}
int Zone::get_DIMENSION(){return  DIMENSION;}
QString Zone::get_ETAT(){return  ETAT;}
QString Zone::get_DESCRIPTION(){return  DESCRIPTION;}

bool Zone::ajouter_zone()
{
    QSqlQuery query;
    QString D;
    D.setNum(DIMENSION);
    //QString res= QString::number(ID_ZONE);
    query.prepare("INSERT INTO ZONE ( DIMENSION,ETAT,DESCRIPTION) "
                  "VALUES (  :DIMENSION ,:ETAT ,:DESCRIPTION )");
    //query.bindValue(":ID_ZONE", res);
    query.bindValue(":DIMENSION", D);
    query.bindValue(":ETAT", ETAT);
    query.bindValue(":DESCRIPTION", DESCRIPTION);


    //return    query.exec();
    auto retVal = query.exec();
    return retVal;

}

QSqlQueryModel * Zone::afficher_zone()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from ZONE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ZONE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DIMENSION"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCRIPTION"));


    return model;
}

bool Zone::supprimer_zone(int ID_ZONE)
{
    QSqlQuery query;
    QString res= QString::number(ID_ZONE);
    query.prepare("Delete from Zone where ID_ZONE = :ID_ZONE ");
    query.bindValue(":ID_ZONE", res);

    return    query.exec();
}


bool Zone :: modifier_zone (int cod )
{
    QSqlQuery query;

  //  int D=DIMENSION ;

    QString res= QString::number(cod);

    query.prepare("UPDATE ZONE SET DIMENSION=:DIMENSION, ETAT=:ETAT ,DESCRIPTION=:DESCRIPTION where ID_ZONE=:cod ");

    query.bindValue(":DIMENSION", DIMENSION);
    query.bindValue(":ETAT", ETAT);
    query.bindValue(":DESCRIPTION", DESCRIPTION);

    query.bindValue(":cod", cod);

     return    query.exec();
     }



QSqlQueryModel * Zone::tri_zone()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from ZONE order by DIMENSION ASC");
    return model;
}

QSqlQueryModel * Zone::tri_zoneDESC()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from ZONE order by DIMENSION DESC");
    return model;
}





