#include "connection.h"
#include <QStringList>


connection::connection()
{}

bool connection::ouvrirconnection()
{

    db=QSqlDatabase::addDatabase("QODBC3");
    db.setHostName("localhost");
    db.setDatabaseName("xe");
    db.setUserName("system");//inserer nom de l'utilisateur
    db.setPassword("181JFT1968");//inserer mot de passe de cet utilisateur

    // if (db.open()) test = true;
    // db.open();


    if(!db.open()){
        auto rVal = db.lastError().text();
        return false;
    }
    /* auto tables = db.tables();
    QSqlQuery query;
    query.prepare("INSERT INTO ZONE (ID, ETAT, TYPE, DIMENSION) VALUES (68, 'Apple', 'test', 20);");
    query.exec(); */
    return true;

}
void connection::fermerconnection()
{db.close();}
