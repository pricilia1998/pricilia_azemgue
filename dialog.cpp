#include "dialog.h"
#include "ui_dialog.h"
#include "connection.h"
#include "recolte.h"
#include "zone.h"
#include "smtp.h"
#include "qcustomplot.h"
#include<QtPrintSupport/QPrinter>
#include <QVector2D>
#include <QVector>
#include <QTextEdit>
#include <QMessageBox>
#include<QPdfWriter>
#include <QPainter>
#include <QSqlQuery>
#include<QPainter>
#include <QAbstractSocket>
#include<QDesktopServices>
#include<QPdfWriter>
#include <QMessageBox>
#include<QUrl>
#include<QFileDialog>
#include <QPixmap>
#include <QTabWidget>

#include <QtSql/QSqlQueryModel>
#include<QtSql/QSqlQuery>
#include<QVariant>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //QMainWindow(parent)
    ui->tableViewzone->setModel(Z.afficher_zone());//refresh
    ui->tableViewrecolte->setModel(R.afficher_recolte());//refresh



  }

Dialog::~Dialog()
{
    delete ui;
}


/*void Dialog::on_modifierZ_clicked()
{
    int ID;
    float DIMENSION;
     QString ETAT;

int cod = ui->lineEdit_id_2->text().toInt();

   ID = ui->lineEdit_id_4->text().toInt();
    DIMENSION = ui->doubleSpinBox_6->value();
    ETAT = ui->lineEdit_3->text();//refres

QMessageBox::information(this, tr("Modifier Parcelle"), tr("OK!"));

    Zone z(ID, DIMENSION , ETAT);
    if(z.modifier_zone(cod))
    {
         ui->tableViewzone->setModel(Z.afficher_zone());//refresh

        QMessageBox::information(this, tr("Modifier Parcelle"), tr("La parcelle a été modifiée avec success."));
    }

}*/

bool Dialog::on_rechermodifZ_clicked()
{
    QSqlQuery query;
   int cod = ui->lineEdit_id_2->text().toInt();
    QString res = QString::number(cod);
    query.prepare("SELECT * FROM ZONE WHERE ID = :cod");
    query.bindValue(":cod", res);
    query.exec();
    if(query.first())
    {
        QMessageBox::information(this, tr("Modifier Parcelle"), tr("La parcelle est trouvé avec success, Veuillez entrer les nouvelles informations."));
         ui->lineEdit_id_4->setText(query.value(0).toString());
          ui->doubleSpinBox_6->setSpecialValueText(query.value(1).toString());
         ui->lineEdit_3->setText(query.value(2).toString());

        //ui->comboBox_2->currentText(query.value(3).toString());

        return true;
} }


void Dialog::on_ajouterZ_clicked()
{
    int ID;//= ui->lineEdit_id->text().toInt();
    float DIMENSION= ui->doubleSpinBox->value();
    QString ETAT= ui->lineEdit_6->text();
  Zone z(ID,DIMENSION,ETAT);
  bool test=z.ajouter_zone();
  if(test)
{
    ui->tableViewzone->setModel(z.afficher_zone());//refresh
    QMessageBox::information(nullptr, QObject::tr("Ajouter une zone"),
                  QObject::tr("zone ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un une zone"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void Dialog::on_suppZ_clicked()
{
    int ID= ui->lineEdit_5->text().toInt();
     bool test=Z.supprimer_zone(ID);
     if(test)
     {  ui->tableViewzone->setModel(Z.afficher_zone());//refresh
         QMessageBox::information(nullptr, QObject::tr("Supprimer une parcelle"),
                     QObject::tr("Parcelle supprimée.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
   }
     else
         QMessageBox::critical(nullptr, QObject::tr("Supprimer une parcelle"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}



void Dialog::on_trierZ_clicked()
{
    Zone   *sa = nullptr ;
    ui->tableViewzone->setModel(sa->tri_zone());//refresh
    ui->tableViewrecolte->setModel(R.afficher_recolte());//refresh

}

void Dialog::on_trierR_clicked()
{
    Recolte   *sa = nullptr ;

     ui->tableViewrecolte->setModel(sa->tri_recolte());//refresh
     ui->tableViewzone->setModel(Z.afficher_zone());//refresh
}

/*void Dialog::on_modifierR_clicked()
{
    QString CULTURE;
    float PRIX;
    float MASSE;
int ID;

int cod = ui->idEdit->text().toInt();

   ID = ui->idEdit->text().toInt();
    CULTURE = ui->lineEditCR_2->text();
   PRIX = ui->doubleSpinBox_4->value();//refres
  MASSE =ui->doubleSpinBox_5->value();
QMessageBox::information(this, tr("Modifier recolte"), tr("OK!"));

    Recolte r(ID, CULTURE , MASSE, PRIX);
    if(r.modifier_recolte(cod))
    {
        ui->tableViewrecolte->setModel(R.afficher_recolte());//refresh

        QMessageBox::information(this, tr("Modifier recolte"), tr("La recolte a été modifié avec success."));
    }

}*/

bool Dialog::on_rechermodifR_clicked()
{

    QSqlQuery query;
    int cod = ui->lineEdit_2->text().toInt();

    QString res = QString::number(cod);
    query.prepare("SELECT * FROM RECOLTE WHERE ID = :cod");
    query.bindValue(":cod", res);
    query.exec();
    if(query.first())
    {
        QMessageBox::information(this, tr("Modifier recolte"), tr("La recolte est trouvé avec success, Veuillez entrer les nouvelles informations."));
         ui->idEdit->setText(query.value(0).toString());
         ui->lineEditCR_2->setText(query.value(1).toString());
        ui->doubleSpinBox_5->setSpecialValueText(query.value(2).toString());
        ui->doubleSpinBox_4->setSpecialValueText(query.value(3).toString());

        return true;
}
}



/*void Dialog::on_ajouterR_clicked()
{
    int ID = ui->lineEdit_id_3->text().toInt();
    QString CULTURE= ui->lineEditCR->text();
    float MASSE= ui->doubleSpinBox_3->value();
    float PRIX= ui->doubleSpinBox_2->value();
   Recolte r(ID,CULTURE,MASSE,PRIX);
  bool test=r.ajouter_recolte();
  if(test)
{
    ui->tableViewrecolte->setModel(r.afficher_recolte());//refresh
    QMessageBox::information(nullptr, QObject::tr("Ajouter une recolte"),
                  QObject::tr("recolte ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un une recolte"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}
*/



void Dialog::on_suppR_clicked()
{
    int ID= ui->lineEdit_4->text().toInt();
     bool test=R.supprimer_recolte(ID);
     if(test)
     { ui->tableViewrecolte->setModel(R.afficher_recolte());//refresh
         QMessageBox::information(nullptr, QObject::tr("Supprimer une recolte"),
                     QObject::tr("recolte supprimé.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
   }
     else
         QMessageBox::critical(nullptr, QObject::tr("Supprimer une recolte"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}




void Dialog::on_pdfR_clicked()
{

    QPdfWriter pdf("C:/Users/HP/Documents/sabrinedachraoui_2A16/sabrinedachraoui/pdf/zzz.pdf");/*il faut toujour changer le nom (*/
    QPainter painter;
    if (! painter.begin(&pdf))
    {

                        qWarning("failed to open file, is it writable?");

    }

    QString titre =ui->rechercherR->text();
    const time_t ctt = time(nullptr);
    QSqlQuery query;
     qWarning("testpdf1");
   query.exec("SELECT ID, MASSE, PRIX FROM RECOLTE WHERE CULTURE ='"+titre+"'");
   //query.bindValue(":cod", res);
      qWarning("testpdf2");

            while (query.next())
                  {

                QString ID = query.value(0).toString();
                QString CULTURE = query.value(1).toString();
                QString PRIX = query.value(2).toString();
                QString MASSE = query.value(3).toString();

        painter.drawText(2200,3500,ID);
        painter.drawText(2200,4000,CULTURE);
        painter.drawText(2200,4500,PRIX);
        painter.drawText(2200,5000,MASSE);


        painter.setPen(Qt::red);
        painter.drawText(4500,2000,"RECOLTE");
        painter.setPen(Qt::black);
        painter.drawText(500,2000,asctime(localtime(&ctt)));
        painter.drawText(500,3500,"ID:");
        painter.drawText(500,4000,"CULTURE:");
        painter.drawText(500,4500,"PRIX:");
        painter.drawText(500,5000,"MASSE:");



            }
}


void Dialog::on_PDFZ_clicked()
{
    QPdfWriter pdf("C:/Users/HP/Documents/sabrinedachraoui_2A16/sabrinedachraoui/pdf/zzz.pdf");/*just fucking work and lemme sleep (*/
    QPainter painter;
    if (! painter.begin(&pdf))
    {
        qWarning("failed to open file, is it writable?");
    }

    const time_t ctt = time(nullptr);
    QSqlQuery query;
     qWarning("testpdf1");

     while (query.next())
                  {

                QString ID = query.value(0).toString();
                QString DIMENSION = query.value(1).toString();
                QString ETAT = query.value(2).toString();


        painter.drawText(2200,3500,ID);
        painter.drawText(2200,4000,DIMENSION);
        painter.drawText(2200,4500,ETAT);

        painter.setPen(Qt::red);
        painter.drawText(4500,2000,"ZONE");
        painter.setPen(Qt::black);
        painter.drawText(500,2000,asctime(localtime(&ctt)));
        painter.drawText(500,3500,"ID :");
        painter.drawText(500,4000,"DIMENSION:");
        painter.drawText(500,4500,"ETAT:");
   }
}



void Dialog::on_mail_clicked()
{
    Smtp *s=new Smtp("fournisseurX@gmail.com","fournisseur123","smtp.gmail.com",465);
    s->sendMail("fournisseurX@gmail.com",ui->lineEdit_7->text(),ui->lineEdit_8->text(),ui->lineEdit_9->text());


}

void Dialog::on_mailing_clicked()
{
    Smtp *s=new Smtp("fournisseurX@gmail.com","fournisseur123","smtp.gmail.com",465);
    s->sendMail("fournisseurX@gmail.com",ui->dest->text(),ui->objet->text(),ui->sujet->text());

}

/*void Dialog::on_afiichstat_clicked()
{
    statestique p;

       ui->labeluno->setText("fonction:playground") ;
         ui->labeldos->setText("fonction: salle de jeux") ;
}*/

