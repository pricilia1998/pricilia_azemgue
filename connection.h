#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>



class connection
{
private:
    QSqlDatabase db;

public:
    connection();
    bool ouvrirconnection();
    void fermerconnection();

};


#endif // CONNECTION_H
