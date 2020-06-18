#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QSystemTrayIcon>

class notification
{
private:
    int id;
public:
    notification();
    void Alerte_Ajout(QString nom, int i);
    void Alerte_Modifier(QString nom,int i);
    void Alerte_Supprimer(QString nom,int i);
    void Alerte_AjoutCarte(int id, int i);
    void Alerte_ModifierCarte(int id,int i);
    void Alerte_SupprimerCarte(int id,int i);
};

#endif // NOTIFICATION_H
