#include "template.h"
#include "ui_template.h"
#include "nourriture.h"
#include "fournisseur.h"
#include <iostream>
#include <QMessageBox>
#include  <QDebug>

using namespace std;

Template::Template(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Template)
{
    ui->setupUi(this);
    ui->tableFour->setModel(tmpfournisseur.afficher());
    ui->tableNour->setModel(tmpnourriture.afficher());
    QComboBox *type1 = ui->typeNour;
    QComboBox *type2 = ui->typeFour;
    QComboBox *type3 = ui->fourNour;
    QComboBox *type4 = ui->rechTypeNour;
    QComboBox *type5 = ui->triTypeFour;
    QComboBox *type6 = ui->idFour;
    QComboBox *type7 = ui->idNour;


    type1 -> addItem("lait");
    type1 -> addItem("croquet");
    type1 -> addItem("viande");
    type1 -> addItem("mais");
    type1 -> addItem("pain");

    type2 -> addItem("laitier");
    type2 -> addItem("boulanger");
    type2 -> addItem("boucher");
    type2 -> addItem("agriculteur");

    ui->idFour->clear();
    QVector<int> tab=tmpfournisseur.IDFour();
    for (int i=0;i<tab.size();i++) {
        type3 -> addItem( QString::number(tab[i]));
    }

    QVector<int> tabId= tmpfournisseur.genererID();
    for(int i=0; i<tabId.size();i++)
    {
         type6 -> addItem( QString::number(tabId[i]));
    }

    ui->idNour->clear();
    QVector<int> tabId1= tmpnourriture.genererID();
    for(int i=0; i<tabId1.size();i++)
    {
         type7 -> addItem( QString::number(tabId1[i]));
    }

    type4 -> addItem("ID_NOUR");
    type4 -> addItem("NOM");

    type5 -> addItem("ID_FOUR");
    type5 -> addItem("NOM");

}

Template::~Template()
{
    delete ui;
}

void Template::on_ajouterNour_clicked()
{
    QComboBox *type1 = ui->typeNour;
    QVariant val = type1 ->currentText() ;
    QComboBox *type2 = ui->fourNour;
    QVariant val1 = type2 ->currentText() ;
    QString a=val1.toString();
    int idNour = ui->idNour->currentText().toInt();
    int quantite = ui->quantNour->text().toInt();
        QString nom= ui->nomNour->text();
        //ui->typeNour->setText("Gateau");
        QString type= val.toString();
        QString description= ui->descNour->text();
        QString montant= ui->montantNour->text();
        //ui->fournisNour->setText("Boulangerie");
        QString fournisseur =a;
        QString dateExp= ui->expNour->text();
        QString dateAch= ui->achNour->text();
      nourriture n(idNour,quantite,nom,type,description,montant,fournisseur,dateExp,dateAch);
      bool test=n.ajouter();

//      std::cout << idNour << endl;
//      std::cout << quantite << endl;
//      std::cout << nom.toStdString() << endl;
//      std::cout << type.toStdString() << endl;
//      std::cout << description.toStdString() << endl;
//      std::cout << montant << endl;
//      std::cout << fournisseur.toStdString() << endl;
//      std::cout << dateExp.toStdString() << endl;
//      std::cout << dateAch.toStdString() << endl;

      if(test)
    {

    ui->tableNour->setModel(tmpnourriture.afficher());
    QMessageBox::information(nullptr, QObject::tr("Ajouter une nourriture"),
                      QObject::tr("nourriture ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    ui->idNour->clear();

   QVector<int> tabId1= tmpnourriture.genererID();
   for(int i=0; i<tabId1.size();i++)
   {
        ui->idNour -> addItem( QString::number(tabId1[i]));
   }

    ui->quantNour->setValue(0);
    ui->nomNour->setText("");
    //ui->typeNour->setText("Gateau");
    ui->descNour->setText("");
    ui->montantNour->setText("");
    //ui->fournisNour->setText("Boulangerie");
    ui->expNour->setDate(QDate::fromString(""));
    ui->achNour->setDate(QDate::fromString(""));

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter une nourriture"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}

void Template::on_supNour_clicked()
{
    int idNour = ui->idNour2->text().toInt();
    bool test=tmpnourriture.supprimer(idNour);

    if(test)
    {
        ui->tableNour->setModel(tmpnourriture.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une nourriture"),
                    QObject::tr("Nourriture supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->idNour2->setText("");

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une nourriture"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}



void Template::on_supFour_clicked()
{
    int idFour = ui->idFour2->text().toInt();
   // qDebug()<<"id à supprimer :" <<idFour;
    bool test=tmpfournisseur.supprimer(idFour);

    if(test)
    {
        ui->tableFour->setModel(tmpfournisseur.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un fournisseur"),
                    QObject::tr("Fournisseur supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->idFour2->setText("");

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un fournisseur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

/**
 * -fonction qui recupere la tchop de la DB par son id: getTchop(int id)
 * tchop pricillia = getTchop(id)
 * -injection des valeur avec
 * ui->idFour->setText(pricillia->getId());
 */

void Template::on_ajouterFour_clicked()
{
    QComboBox *type2 = ui->typeFour;
    QVariant val = type2 ->currentText() ;

    int idFour = ui->idFour->currentText().toInt();
    int numero= ui->numFour->text().toInt();
    QString nom= ui->nomFour->text();
    QString type= val.toString();
    QString description= ui->descFour->text();
    QString email= ui->mailFour->text();


    fournisseur f (idFour,numero,nom,type,email,description);
    bool test= f.ajouter();

    if(test)
  {

  ui->tableFour->setModel(tmpfournisseur.afficher());
  QMessageBox::information(nullptr, QObject::tr("Ajouter un fournisseur"),
                    QObject::tr("fournisseur ajouté.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

   ui->idFour->clear();

  QVector<int> tabId= tmpfournisseur.genererID();
  for(int i=0; i<tabId.size();i++)
  {
       ui->idFour -> addItem( QString::number(tabId[i]));
  }

  ui->nomFour->setText("");
  //ui->typeFour->setText("");
  ui->descFour->setText("");
  ui->mailFour->setText("");
  ui->numFour->setText("");

  }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un fournisseur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Template::on_modNour_clicked()
{
    QComboBox *type1 = ui->typeNour;
    QVariant val = type1 ->currentText();

    int id5 = ui->idNour2->text().toInt();
    nourriture n=tmpnourriture.recupererNour(id5);

     ui->idNour->clear();

    ui->idNour->addItem(QString::number(n.get_idNour()));
    ui->quantNour->setValue(n.get_quantite());
        ui->nomNour->setText(n.get_nom());
       ui->descNour->setText(n.get_description());
       ui->montantNour->setText(n.get_montant());
       //ui->fournisNour->setText(n.);
       ui->expNour->setDate(QDate::fromString(n.get_dateExp(),"dd/MM/yyyy"));
       ui->achNour->setDate(QDate::fromString(n.get_dateAch(),"dd/MM/yyyy"));
}

void Template::on_modFour_clicked()
{
    QComboBox *type2 = ui->typeFour;
    QVariant val = type2 ->currentText() ;

    int idd5 = ui->idFour2->text().toInt();
    fournisseur f = tmpfournisseur.recupererFour(idd5);

    ui->idFour->clear();

    ui->idFour->addItem(QString::number(f.get_idFour()));
    ui->numFour->setText(QString::number(f.get_numero()));
    ui->nomFour->setText(f.get_nom());
   ui->descFour->setText(f.get_description());
   ui->mailFour->setText(f.get_email());

}


void Template::on_miseajourNour_clicked()
{
        QComboBox *type1 = ui->typeNour;
        QVariant val = type1 ->currentText() ;
        QComboBox *type2 = ui->fourNour;
        QVariant val1 = type2 ->currentText();

    int idNour = ui->idNour->currentText().toInt();
    int quantite = ui->quantNour->text().toInt();
        QString nom= ui->nomNour->text();
        //ui->typeNour->setText("Gateau");
        QString type= val.toString();
        QString description= ui->descNour->text();
        QString montant= ui->montantNour->text();
        //ui->fournisNour->setText("Boulangerie");
        QString fournisseur = val1.toString();
        QString dateExp= ui->expNour->text();
        QString dateAch= ui->achNour->text();

      nourriture n(idNour,quantite,nom,type,description,montant,fournisseur,dateExp,dateAch);
      bool test=n.Modifier();

      if(test)
    {

    ui->tableNour->setModel(tmpnourriture.afficher());
    QMessageBox::information(nullptr, QObject::tr("Modifier une nourriture"),
                      QObject::tr("nourriture Modifié.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    ui->idNour->clear();

   QVector<int> tabId1= tmpnourriture.genererID();
   for(int i=0; i<tabId1.size();i++)
   {
        ui->idNour -> addItem( QString::number(tabId1[i]));
   }

    ui->quantNour->setValue(0);
    ui->nomNour->setText("");
    //ui->typeNour->setText("Gateau");
    //ui->typeNour->setText("");
    ui->descNour->setText("");
    ui->montantNour->setText("");
    //ui->fournisNour->setText("Boulangerie");
    //ui->fournisNour->setText("");
    ui->expNour->setDate(QDate::fromString(""));
    ui->achNour->setDate(QDate::fromString(""));

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Modifier une nourriture"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

}

void Template::on_miseajourFour_clicked()
{
    QComboBox *type2 = ui->typeFour;
    QVariant val = type2 ->currentText() ;
    int idFour = ui->idFour->currentText().toInt();
    int numero= ui->numFour->text().toInt();
    QString nom= ui->nomFour->text();
    QString type= val.toString();
    QString description= ui->descFour->text();
    QString email= ui->mailFour->text();


    fournisseur f (idFour,numero,nom,type,email,description);
    bool test= f.Modifier();

    if(test)
  {

  ui->tableFour->setModel(tmpfournisseur.afficher());
  QMessageBox::information(nullptr, QObject::tr("Modifier un fournisseur"),
                    QObject::tr("fournisseur Modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

   ui->idFour->clear();

  QVector<int> tabId= tmpfournisseur.genererID();
  for(int i=0; i<tabId.size();i++)
  {
       ui->idFour -> addItem( QString::number(tabId[i]));
  }

  ui->nomFour->setText("");
  //ui->typeFour->setText("");
  ui->descFour->setText("");
  ui->mailFour->setText("");
  ui->numFour->setText("");

  }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un fournisseur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


void Template::on_triFournisseur_clicked()
{
    QComboBox *type2 = ui->triTypeFour;
        QVariant val = type2 ->currentText() ;
        ui->tableFour->setModel(tmpfournisseur.trier(val.toString()));
}



void Template::on_triNourriture_clicked()
{
    QComboBox *type2 = ui->rechTypeNour;
        QVariant val = type2 ->currentText() ;
        ui->tableNour->setModel(tmpnourriture.trier(val.toString()));
}



void Template::on_rechNour_textChanged(const QString &arg1)
{
    ui->tableNour->setModel(tmpnourriture.chercher_Nourriture(arg1));
}



void Template::on_rechFour_textChanged(const QString &arg1)
{
    ui->tableFour->setModel(tmpfournisseur.chercher_Fournisseur(arg1));
}

void Template::on_montantNour_textEdited(const QString &arg1)
{
    QString ipRange = "(?:[0-9]?[0-9]?[0-9])";
    QRegExp ipRegex ("^" + ipRange + ipRange+ ipRange
                      + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ui->montantNour->setValidator(ipValidator);
    ui->montantNour->setText(arg1);
}

void Template::on_numFour_textEdited(const QString &arg1)
{
    QString ipRange = "(?:[0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9])";
    QRegExp ipRegex ("^" + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ui->numFour->setValidator(ipValidator);
    ui->numFour->setText(arg1); 
}

void Template::on_nomFour_textEdited(const QString &arg1)
{
    QString ipRange = "(?:[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]"
                      "?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]"
                      "?[aA-zZ]?[aA-zZ])";
    QRegExp ipRegex ("^" + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ui->nomFour->setValidator(ipValidator);
    ui->nomFour->setText(arg1);
}

void Template::on_nomNour_textEdited(const QString &arg1)
{
    QString ipRange = "(?:[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]"
                      "?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]?[aA-zZ]"
                      "?[aA-zZ]?[aA-zZ])";
    QRegExp ipRegex ("^" + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ui->nomNour->setValidator(ipValidator);
    ui->nomNour->setText(arg1);
}
