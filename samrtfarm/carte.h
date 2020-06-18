#ifndef CARTE_H
#define CARTE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMetaType>
#include <qmetatype.h>
#include <QDate>

class carte
{
public:
    carte();
    carte(int,QDate,QString,float,float,float,QString);


        QDate get_derniere_visite();

        QString get_info_complementaires();
      int get_idCarte();
        float get_poids();
         float get_taille();
        float get_temperature();
        int get_idAnimal();
         bool testpoids(int idCarte);
        void set_idAnimal(int idAnimal);


        void set_nomAnimal(QString nomAnimal);

        int recupererIdanimal(QString nom);
        bool ajouterC();
        QSqlQueryModel * afficherC();
        bool supprimer(int);
        bool Modifier();
        bool supprimer_tout();
        QSqlQueryModel * afficher_par_id(QString);
        carte recupererCarte(int);
          QSqlQueryModel * trieC();
           QSqlQueryModel * trieeC();
            QSqlQueryModel * rechercher( QString );

private:
        int idCarte,idAnimal;
       float  poids,taille, temperature;


        QString info_complementaires,nomAnimal;
        QDate derniere_visite ;
};

#endif // CARTE_H
