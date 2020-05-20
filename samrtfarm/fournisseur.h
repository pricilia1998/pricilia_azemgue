#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMetaType>
#include <qmetatype.h>
#include <vector>
#include <iterator>


class fournisseur
{
public:
    fournisseur();
    fournisseur(int,int,QString,QString,QString,QString);
        QString get_nom();
        QString get_type();
        QString get_description();
        QString get_email();
        int get_numero();
        int get_idFour();

        bool ajouter();
        bool supprimer(int);
        bool Modifier();
        QVector<int> IDFour();
        QVector<int> genererID();
        bool supprimer_tout();
        QSqlQueryModel * afficher_par_id(QString);
        QSqlQueryModel * afficher();
        QSqlQueryModel * trier(QString);
        QSqlQueryModel *chercher_Fournisseur(QString nom);
        fournisseur recupererFour(int);

private:
        int idFour;
        int numero;
        QString nom,type,description,email;
};

#endif // FOURNISSEUR_H
