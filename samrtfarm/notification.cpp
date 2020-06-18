#include "notification.h"

notification::notification()
{

}
void notification::Alerte_Ajout(QString nom,int i)
{


    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon("C:/Users/Admin/Desktop/projet_sirine/icon.jpg"));

       notifyIcon->show();

       if (i==1)
       {

       notifyIcon->showMessage("Erreur!","On peut pas ajouter cet animal",QSystemTrayIcon::Warning,1500);
       }
       else if (i==2)
       {
         notifyIcon->showMessage("Animal","Un nouveau animal nommé "+nom+" a été ajouté",QSystemTrayIcon::Information,1500);
       }

}

void notification::Alerte_Modifier(QString nom, int i)
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon("C:/Users/Admin/Desktop/projet_sirine/icon.jpg"));

       notifyIcon->show();

       if (i==1)
       {

       notifyIcon->showMessage("Erreur","On peut pas modifier cet animal",QSystemTrayIcon::Warning,1500);
       }
       else if (i==2)
       {
         notifyIcon->showMessage("Animal","Un animal nommé "+nom+" a été modifié",QSystemTrayIcon::Information,1500);
       }



}
void notification::Alerte_Supprimer(QString nom,int i)
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   notifyIcon->setIcon(QIcon("C:/Users/Admin/Desktop/projet_sirine/icon.jpg"));

       notifyIcon->show();

       if (i==1)
       {

       notifyIcon->showMessage("Erreur!","On ne peut pas supprimer cet animal",QSystemTrayIcon::Warning,1500);
       }
       else if (i==2)
       {
         notifyIcon->showMessage("Animal","Un animal nommé "+nom+" a été supprimé",QSystemTrayIcon::Information,1500);
       }



}
void notification::Alerte_AjoutCarte(int id,int i)
{

    QString res= QString::number(id);
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon("C:/Users/Admin/Desktop/projet_sirine/icon.jpg"));

       notifyIcon->show();

       if (i==1)
       {

       notifyIcon->showMessage("Carte","On ne peut pas ajouter cette Carte",QSystemTrayIcon::Warning,1500);
       }
       else if (i==2)
       {
         notifyIcon->showMessage("Cartes","Une nouvelle carte avec un Numero N°"+res+" a été ajoutée",QSystemTrayIcon::Information,1500);
       }

}

void notification::Alerte_ModifierCarte(int id,int i)
{
    QString res= QString::number(id);
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon("C:/Users/Admin/Desktop/projet_sirine/icon.jpg"));

       notifyIcon->show();

       if (i==1)
       {

       notifyIcon->showMessage("Cartes","On ne peut pas modifier cette carte",QSystemTrayIcon::Warning,1500);
       }
       else if (i==2)
       {
         notifyIcon->showMessage("Cartes","Une Carte avec un Numero N°"+res+" a été modifié",QSystemTrayIcon::Information,1500);
       }



}
void notification::Alerte_SupprimerCarte(int id,int i)
{
    QString res= QString::number(id);
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon("C:/Users/Admin/Desktop/projet_sirine/icon.jpg"));

       notifyIcon->show();

       if (i==1)
       {

       notifyIcon->showMessage("Cartes","On ne peut pas supprimer cette carte",QSystemTrayIcon::Warning,1500);
       }
       else if (i==2)
       {
         notifyIcon->showMessage("Cartes","Une Carte avec un Numero N°"+res+" a été supprimée",QSystemTrayIcon::Information,1500);
       }
}
