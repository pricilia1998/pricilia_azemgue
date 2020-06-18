#ifndef ANIMAL_H
#define ANIMAL_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMetaType>
#include <qmetatype.h>
#include <QDate>
#include "carte.h"

class animal
{
public:
    animal();
    animal(int,QString,QString,QString,QString,QDate);
        QString get_nom();
        QString get_type();
        QString get_sexe();
        QString get_description();
        QDate get_date_de_naissance();


        int get_idAnimal();


        bool ajouter();
        bool testNom(QString nom);
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool Modifier();
        bool supprimer_tout();
        QSqlQueryModel * afficher_par_id(QString);
        animal recupererAnimal(int);
          QSqlQueryModel * trie();
           QSqlQueryModel * triee();
            QSqlQueryModel * rechercherAnimal( QString );
        int CalculAnimalType(QString type);

private:
        int idAnimal;

        QString nom,type,sexe,description;
        QDate date_de_naissance ;
};

#endif // ANIMAL_H
