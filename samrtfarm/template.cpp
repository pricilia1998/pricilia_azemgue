#include "template.h"
#include "ui_template.h"
#include "nourriture.h"
#include "fournisseur.h"
#include <iostream>
#include <QMessageBox>
#include  <QDebug>

#include <QDate>
#include <QModelIndex>
#include <QtPrintSupport>
#include <QPrinter>
#include <QPrintDialog>
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

    QMessageBox msgBox;
                       msgBox.setIcon(QMessageBox::Information);
                       msgBox.setWindowTitle( "Ajouter une nourriture");
                       msgBox.setText(tr("Nourriture ajoutée avec succès"));
                       msgBox.addButton(tr("Fermer"), QMessageBox::NoRole);

                       msgBox.exec();

ui->tableNour->setModel(tmpnourriture.afficher());

/*QMessageBox::information(nullptr, QObject::tr("Ajouter une nourriture"),
                QObject::tr("nourriture ajouté.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);*/
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
      {
          QMessageBox msgBox;
                  msgBox.setIcon(QMessageBox::Critical);
                             msgBox.setWindowTitle( "Ajouter une nourriture");
                             msgBox.setText(tr("Erreur dans les champs"));
                             msgBox.addButton(tr("Fermer"), QMessageBox::NoRole);

                             msgBox.exec();

      }
          /*QMessageBox::critical(nullptr, QObject::tr("Ajouter une nourriture"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
*/
}

void Template::on_supNour_clicked()
{
    int idNour = ui->idNour2->text().toInt();
    bool test=tmpnourriture.supprimer(idNour);

    if(test)
    {
        QMessageBox msgBox1;
                           msgBox1.setIcon(QMessageBox::Information);
                           msgBox1.setWindowTitle( "Supprimer une nourriture");
                           msgBox1.setText(tr("Nourriture supprimée avec succès"));
                           msgBox1.addButton(tr("Fermer"), QMessageBox::NoRole);

                           msgBox1.exec();

        ui->tableNour->setModel(tmpnourriture.afficher());//refresh

        /*QMessageBox::information(nullptr, QObject::tr("Supprimer une nourriture"),
                    QObject::tr("Nourriture supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); */
        ui->idNour2->setText("");

    }
    else
    {
        QMessageBox msgBox1;
                msgBox1.setIcon(QMessageBox::Critical);
                           msgBox1.setWindowTitle( "Supprimer une nourriture");
                           msgBox1.setText(tr("Erreur dans les champs"));
                           msgBox1.addButton(tr("Fermer"), QMessageBox::NoRole);

                           msgBox1.exec();

    }
        /*QMessageBox::critical(nullptr, QObject::tr("Supprimer une nourriture"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); */
}



void Template::on_supFour_clicked()
{
    int idFour = ui->idFour2->text().toInt();
   // qDebug()<<"id à supprimer :" <<idFour;
    bool test=tmpfournisseur.supprimer(idFour);

    if(test)
    {
        ui->tableFour->setModel(tmpfournisseur.afficher());//refresh
        QMessageBox msgBox6;
                           msgBox6.setIcon(QMessageBox::Information);
                           msgBox6.setWindowTitle( "Supprimer un fournisseur");
                           msgBox6.setText(tr("Fournisseur supprimé avec succès"));
                           msgBox6.addButton(tr("Fermer"), QMessageBox::NoRole);

                           msgBox6.exec();

        ui->idFour2->setText("");

    }
    else
    {
        QMessageBox msgBox6;
                msgBox6.setIcon(QMessageBox::Critical);
                           msgBox6.setWindowTitle( "Supprimer une nourriture");
                           msgBox6.setText(tr("Erreur dans les champs"));
                           msgBox6.addButton(tr("Fermer"), QMessageBox::NoRole);

                           msgBox6.exec();

    }
        /*QMessageBox::critical(nullptr, QObject::tr("Supprimer un fournisseur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); */
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

        QMessageBox msgBox2;
                           msgBox2.setIcon(QMessageBox::Information);
                           msgBox2.setWindowTitle( "Ajouter un fournisseur");
                           msgBox2.setText(tr("Fournisseur ajouté avec succès"));
                           msgBox2.addButton(tr("Fermer"), QMessageBox::NoRole);

                           msgBox2.exec();

        ui->tableFour->setModel(tmpfournisseur.afficher());//refresh

       /* QMessageBox::information(nullptr, QObject::tr("Supprimer un fournisseur"),
                    QObject::tr("Fournisseur supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); */

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
    {
        QMessageBox msgBox2;
                msgBox2.setIcon(QMessageBox::Critical);
                           msgBox2.setWindowTitle( "Ajouter un fournisseur");
                           msgBox2.setText(tr("Erreur dans les champs"));
                           msgBox2.addButton(tr("Fermer"), QMessageBox::NoRole);

                           msgBox2.exec();

    }
       /* QMessageBox::critical(nullptr, QObject::tr("Supprimer un fournisseur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); */
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

    QMessageBox msgBox4;
                       msgBox4.setIcon(QMessageBox::Information);
                       msgBox4.setWindowTitle( "Modifier une nourriture");
                       msgBox4.setText(tr("Nourriture modifiée avec succès"));
                       msgBox4.addButton(tr("Fermer"), QMessageBox::NoRole);

                       msgBox4.exec();
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
      {
          QMessageBox msgBox4;
                  msgBox4.setIcon(QMessageBox::Critical);
                             msgBox4.setWindowTitle( "Modifier une nourriture");
                             msgBox4.setText(tr("Erreur dans les champs"));
                             msgBox4.addButton(tr("Fermer"), QMessageBox::NoRole);

                            msgBox4.exec();
       }


          /*QMessageBox::critical(nullptr, QObject::tr("Modifier une nourriture"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel); */

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

  QMessageBox msgBox5;
                     msgBox5.setIcon(QMessageBox::Information);
                     msgBox5.setWindowTitle( "Modifier un fournisseur");
                     msgBox5.setText(tr("Fournisseur modifiée avec succès"));
                     msgBox5.addButton(tr("Fermer"), QMessageBox::NoRole);

                     msgBox5.exec();

  /*QMessageBox::information(nullptr, QObject::tr("Modifier un fournisseur"),
                    QObject::tr("fournisseur Modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); */

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
    {
        QMessageBox msgBox5;
                msgBox5.setIcon(QMessageBox::Critical);
                           msgBox5.setWindowTitle( "Modifier un fournisseur");
                           msgBox5.setText(tr("Erreur dans les champs"));
                           msgBox5.addButton(tr("Fermer"), QMessageBox::NoRole);

                           msgBox5.exec();

    }
        /*QMessageBox::critical(nullptr, QObject::tr("Modifier un fournisseur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); */
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

/*
 void Template::on_pushButton_clicked()
{

    QMessageBox msgBox;
                       msgBox.setIcon(QMessageBox::Warning);
                       msgBox.setWindowTitle( "Email Employee");
                       msgBox.setText(tr("Entrer une email valide ! ( @ )"));
                       msgBox.addButton(tr("D'accord"), QMessageBox::NoRole);

                       msgBox.exec();
}
*/
void Template::on_imprimerNour_clicked()
{
    QString strStream;
              QTextStream out(&strStream);

              const int rowCount = ui->tableNour->model()->rowCount();
              const int columnCount = ui->tableNour->model()->columnCount();

              out <<  "<html>\n"
                  "<head>\n"
                  "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                  <<  QString("<title>%1</title>\n").arg("strTitle")
                  <<  "</head>\n"
                  "<body bgcolor=#ffffff link=#5000A0>\n"

                     // "<align='right'> " << datefich << "</align>"
                  "<center> <H1>Liste des Nourritures</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

              // headers
              out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
              for (int column = 0; column < columnCount; column++)
                  if (!ui->tableNour->isColumnHidden(column))
                      out << QString("<th>%1</th>").arg(ui->tableNour->model()->headerData(column, Qt::Horizontal).toString());
              out << "</tr></thead>\n";

              // data table
              for (int row = 0; row < rowCount; row++) {
                  out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                  for (int column = 0; column < columnCount; column++) {
                      if (!ui->tableNour->isColumnHidden(column)) {
                          QString data = ui->tableNour->model()->data(ui->tableNour->model()->index(row, column)).toString().simplified();
                          out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                      }
                  }
                  out << "</tr>\n";
              }
              out <<  "</table> </center>\n"
                  "</body>\n"
                  "</html>\n";

        QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
          if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

          QPrinter printer(QPrinter::PrinterResolution);
          printer.setOutputFormat(QPrinter::PdfFormat);
         printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

          QTextDocument doc;
          doc.setHtml(strStream);
          doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
          doc.print(&printer);
}

void Template::on_imprimerFour_clicked()
{
    QString strStream;
              QTextStream out(&strStream);

              const int rowCount = ui->tableFour->model()->rowCount();
              const int columnCount = ui->tableFour->model()->columnCount();

              out <<  "<html>\n"
                  "<head>\n"
                  "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                  <<  QString("<title>%1</title>\n").arg("strTitle")
                  <<  "</head>\n"
                  "<body bgcolor=#ffffff link=#5000A0>\n"

                     // "<align='right'> " << datefich << "</align>"
                  "<center> <H1>Liste des Nourritures</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

              // headers
              out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
              for (int column = 0; column < columnCount; column++)
                  if (!ui->tableFour->isColumnHidden(column))
                      out << QString("<th>%1</th>").arg(ui->tableFour->model()->headerData(column, Qt::Horizontal).toString());
              out << "</tr></thead>\n";

              // data table
              for (int row = 0; row < rowCount; row++) {
                  out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                  for (int column = 0; column < columnCount; column++) {
                      if (!ui->tableFour->isColumnHidden(column)) {
                          QString data = ui->tableFour->model()->data(ui->tableFour->model()->index(row, column)).toString().simplified();
                          out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                      }
                  }
                  out << "</tr>\n";
              }
              out <<  "</table> </center>\n"
                  "</body>\n"
                  "</html>\n";

        QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
          if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

          QPrinter printer(QPrinter::PrinterResolution);
          printer.setOutputFormat(QPrinter::PdfFormat);
         printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

          QTextDocument doc;
          doc.setHtml(strStream);
          doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
          doc.print(&printer);
}
