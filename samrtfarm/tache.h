#ifndef TACHE_H
#define TACHE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class tache
{
public:
    tache();
    tache(int,QString,QString,QString,QDate,QDate,QString,QString);
    QString get_nom();
    QString get_description();
    QDate get_date_debut();
    QDate get_date_limit();
    QString get_statut();
    int get_id();
    bool ajouter();
    QSqlQueryModel * afficher(QString,QString);
    bool supprimer(int);
    QSqlQueryModel * rechercher(QString,QString,QDate) ;
   bool modifier( int , QString ,QString  ,QString  ,QDate  , QDate  ,QString , QString ) ;

private:
    QString nom,description,statut, cin, type ;
    QDate date_limit, date_deb;
    int id;
};

#endif // TACHE_H









