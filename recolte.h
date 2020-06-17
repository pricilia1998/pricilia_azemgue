#ifndef RECOLTE_H
#define RECOLTE_H

#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateEdit>
#include <QDialog>

class Recolte
{public:
    Recolte();
    Recolte(int , QString , float, float );
    QString get_CULTURE();
    float get_MASSE();
    int get_ID_RECOLTE();
    float get_PRIX();


    bool ajouter_recolte();
    bool supprimer_recolte(int ID_RECOLTE);
    bool modifier_recolte( int cod );
    QSqlQueryModel * afficher_recolte();
    QSqlQueryModel * tri_recolte();
    QSqlQueryModel * tri_recolteDESC();
    QSqlQueryModel * rechercher_recolte(QString );



private:
    int ID_RECOLTE;
    QString CULTURE;
     float MASSE;
     float  PRIX;
};

#endif // RECOLTE_H
