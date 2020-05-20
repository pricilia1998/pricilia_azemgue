#ifndef NOURRITURE_H
#define NOURRITURE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMetaType>
#include <qmetatype.h>

class nourriture
{
public:
    nourriture();
    nourriture(int,int,QString,QString,QString,QString,QString,QString,QString);
        QString get_nom();
        QString get_type();
        QString get_description();
        QString get_montant();
        QString get_fournisseur();
        QString get_dateExp();
        QString get_dateAch();
        int get_idNour();
        int get_quantite();

        bool ajouter();
        bool supprimer(int);
        bool Modifier();
        bool supprimer_tout();
        QVector<int> genererID();
        //bool affecter_Nourriture(int,QString);
        QSqlQueryModel * afficher_par_id(QString);
        QSqlQueryModel * trier(QString);
        QSqlQueryModel * afficher();
        QSqlQueryModel *chercher_Nourriture(QString nom);
        nourriture recupererNour(int);

private:
        int idNour,quantite;
        QString montant;
        QString nom,type,description,fournisseur,dateExp,dateAch;
};

#endif // NOURRITURE_H
