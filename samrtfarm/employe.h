#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QSqlDatabase>

class employe
{
public:
    employe();
    employe(QString,QString,QString,QString,QString, QDate);
    QString get_cin();
    QString get_nom();
    QString get_prenom();
    QString get_email();
    QString get_type();

    bool ajouter();
    QSqlQueryModel * afficher(QString);
    bool supprimer(QString);
    QSqlQueryModel * rechercher(QString,QString, QString) ;
    bool modifier( QString cin, QString nom,QString prenom ,QString email ,QString type, QDate date ) ;
private:
    QString nom,prenom,email,type;
    QString cin;
    QDate date;
};

#endif // EMPLOYE_H
