#ifndef ZONE_H
#define ZONE_H
#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDateEdit>


class Zone
{

public:
    Zone();
    Zone(int, int,QString, QString);
    int get_ID_ZONE();
   int get_DIMENSION();
    QString get_ETAT();
     QString get_DESCRIPTION();

    bool ajouter_zone();
    bool supprimer_zone(int  ID_ZONE);
    bool modifier_zone(int cod);
    QSqlQueryModel * afficher_zone();
    QSqlQueryModel * tri_zone();
    QSqlQueryModel * tri_zoneDESC();


private:

    int ID_ZONE;
    int DIMENSION;
    QString ETAT;
    QString DESCRIPTION;

};
#endif // ZONE_H
