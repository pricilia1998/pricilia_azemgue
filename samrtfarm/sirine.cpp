#include "sirine.h"
#include "ui_Sirine.h"
#include "animal.h"
#include "carte.h"

#include <iostream>
#include <QMessageBox>
#include  <QDebug>
#include <QRadioButton>
#include<QtPrintSupport/QPrinter>
#include<QPdfWriter>
#include <QPainter>
#include<QFileDialog>
#include<QTextDocument>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include<QtPrintSupport/QPrinter>
#include <QVector2D>
#include <QVector>
#include <QSqlQuery>
#include<QDesktopServices>
#include <QMessageBox>
#include<QUrl>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>
#include <QPrintDialog>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include "mainwindow.h"

using namespace std;

Sirine::Sirine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sirine)
{
    ui->setupUi(this);

    ui->tableAnimal->setModel(tmpanimal.afficher());
    ui->tableCarte->setModel(tmpcarte.afficherC());
    additemnom();

    QStringList list_sexe={"M","F"};
    ui->sexeAnimal->addItems(list_sexe);
    QStringList list_type={"chien","chat","cheval","volaille","bovin"};
    ui->typeAnimal->addItems(list_type);
     ui->testnom->setText("");



}

Sirine::~Sirine()
{
    delete ui;
}

void Sirine::additemnom()
{
    ui->comboBoxanimal->clear();
    QSqlQuery query,query1;
    QStringList list;
    query.prepare("select nom from animal");
    query.exec();
    int i=0;
    while(query.next()){
        query1.prepare("select * from animal inner join carte on carte.id_animal=animal.id_animal where animal.nom='"+query.value(0).toString()+"'");
        query1.exec();
        int j=0;
        while(query1.next()){
            j++;
        }
        if(j==0){
            list.insert(i,query.value(0).toString());
            i++;
        }
    }
    ui->comboBoxanimal->addItems(list);
}
void Sirine::on_ajouterAnimal_clicked()
{
    int idAnimal = ui->idAnimal->text().toInt();

        QString nom= ui->nomAnimal->text();
        //ui->typeNour->setText("Gateau");
        QString type= ui->typeAnimal->currentText();;
        QString sexe= ui->sexeAnimal->currentText();;
        QString description= ui->descAnimal->text();

        QDate date_de_naissance= ui->dateAnimal->date();
      animal a(idAnimal,nom,type,sexe,description,date_de_naissance);
      bool test=a.ajouter();



      if(test)
    {

    ui->tableAnimal->setModel(tmpanimal.afficher());
    QMessageBox::information(nullptr, QObject::tr("Ajouter un animal"),
                      QObject::tr("animal ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    ui->idAnimal->setText("");

        ui->nomAnimal->setText("");

        ui->sexeAnimal->clear();
        QStringList list_sexe={"M","F"};
        ui->sexeAnimal->addItems(list_sexe);
        ui->typeAnimal->clear();
        QStringList list_type={"chien","chat","cheval"};
        ui->typeAnimal->addItems(list_type);

       ui->descAnimal->setText("");
       ui->idAnimal2->setText("");
       additemnom();
    notification n;
    n.Alerte_Ajout(nom,2);

    }
      else{
          notification n;
          n.Alerte_Ajout(nom,1);

          QMessageBox::critical(nullptr, QObject::tr("Ajouter un animal"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
      }
}

void Sirine::on_supAnimal_clicked()
{
     QString nom= ui->nomAnimal->text();
    int idAnimal = ui->idAnimal2->text().toInt();
    bool test=tmpanimal.supprimer(idAnimal);
    if(test)
    {
        ui->tableAnimal->setModel(tmpanimal.afficher());//refresh
        ui->tableCarte->setModel(tmpcarte.afficherC());
        ui->idAnimal2->setText("");
        additemnom();
        QMessageBox::information(nullptr, QObject::tr("Supprimer un animal"),
                    QObject::tr("Animal supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        notification n;
        n.Alerte_Supprimer(nom,2);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un animal"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    notification n;
    n.Alerte_Supprimer(nom,1);
}
}

void Sirine::on_supCarte_clicked()
{
    int idCarte= ui->idCarte2->text().toInt();
    bool test=tmpcarte.supprimer(idCarte);
    if(test)
    {
        ui->tableCarte->setModel(tmpcarte.afficherC());//refresh
        additemnom();
        QMessageBox::information(nullptr, QObject::tr("Supprimerune carte"),
                    QObject::tr("carte supprimée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une carte"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}




void Sirine::on_ajouterCarte_clicked()
{
       int idCarte = ui->idCarte->text().toInt();
        QDate derniere_visite= ui->derniere_visite->date();
       QString info_complementaires= ui->info_complementaires->text();
      float poids= ui->poids->text().toFloat();
     float taille= ui->taille->text().toFloat();
    float temperature= ui->temperature->text().toFloat();
    QString nomanimal=ui->comboBoxanimal->currentText();

      carte c (idCarte,derniere_visite,info_complementaires,poids,taille,temperature,nomanimal);
      bool test=c.ajouterC();
      if(test)
    {
    additemnom();
    ui->tableCarte->setModel(tmpcarte.afficherC());
    ui->idCarte->setText("");
    ui->info_complementaires->setText("");
    ui->poids->setText("");
    ui->taille->setText("");
    ui->temperature->setText("");
    QMessageBox::information(nullptr, QObject::tr("Ajouter une carte"),
                      QObject::tr("carte ajoutée.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    notification n;
    n.Alerte_AjoutCarte(idCarte,2);
    }
      else {
          QMessageBox::critical(nullptr, QObject::tr("Pas d'ajout"),
                      QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
      notification n;
      n.Alerte_AjoutCarte(idCarte,1);
            }
}
void Sirine::on_modCarte_clicked()
{

if (ui->idCarte->text().length()==0)
{
     int id5 = ui->idCarte2->text().toInt();
     carte c =tmpcarte.recupererCarte(id5);
     ui->idCarte->setText(QString::number(c.get_idCarte()));

         ui->derniere_visite->setDate(c.get_derniere_visite());
        ui->info_complementaires->setText(c.get_info_complementaires());
        ui->poids->setText(QString::number(c.get_poids()));
        ui->taille->setText(QString::number(c.get_taille()));
        ui->temperature->setText(QString::number(c.get_temperature()));


}

   else
{
    int id= ui->idCarte2->text().toInt();
    QString info_complementaires = ui->info_complementaires->text();
  int poids= ui->poids->text().toInt();
  int taille= ui->taille->text().toInt();
  int temperature= ui->temperature->text().toInt();
    QString nomanimal=ui->comboBoxanimal->currentText();
    QDate derniere_visite= ui->derniere_visite->date();
      int idCarte = ui->idCarte->text().toInt();

 carte c(id,derniere_visite,info_complementaires, poids,taille,temperature,nomanimal);

    bool test=c.Modifier();

    if(test)
    {
        QMessageBox::critical(nullptr, QObject::tr("Modification"),
                    QObject::tr("done².\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        notification n;
        n.Alerte_ModifierCarte(idCarte,2);
        ui->tableCarte->setModel(tmpcarte.afficherC());
        ui->idCarte->setText("");
        ui->info_complementaires->setText("");
        ui->poids->setText("");
        ui->taille->setText("");
        ui->temperature->setText("");
        ui->idCarte2->setText("");
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modification"),
                    QObject::tr("Erreur.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        notification n;
        n.Alerte_ModifierCarte(idCarte,1);

    }


}
}



void Sirine::on_modAnimal_clicked()
{

if ( ui->idAnimal->text().length()==0)
{
     int id5 = ui->idAnimal2->text().toInt();
     animal a =tmpanimal.recupererAnimal(id5);
     ui->idAnimal->setText(QString::number(a.get_idAnimal()));

         ui->nomAnimal->setText(a.get_nom());
        //ui->typeAnimal->setText(a.get_type());
        ui->typeAnimal->setCurrentText(a.get_type());
        //ui->sexeAnimal->setText(a.get_sexe());
        ui->sexeAnimal->setCurrentText(a.get_sexe());
        ui->descAnimal->setText(a.get_description());
        ui->dateAnimal->setDate(a.get_date_de_naissance());

      //  ui->dateAnimal->setDate(QDate::fromString(a.get_date_de_naissance(),"dd/MM/yyyy"));

}

   else
{
    int id= ui->idAnimal2->text().toInt();
    QString nom= ui->nomAnimal->text();
    QString typeAnimal= ui->typeAnimal->currentText();
    QString sexeAnimal= ui->sexeAnimal->currentText();
    QString descAnimal = ui->descAnimal->text();
  //  QDate date;
   // QDate dateAnimal= date.currentDate();
    QDate dateAnimal= ui->dateAnimal->date();


    animal e(id,nom,typeAnimal,sexeAnimal,descAnimal,dateAnimal);

    bool test=e.Modifier();

    if(test)
    {
       QMessageBox::critical(nullptr, QObject::tr("Modification"),
                    QObject::tr("done².\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        notification n;
        n.Alerte_Modifier(nom,2);
        ui->idAnimal->setText("");

            ui->nomAnimal->setText("");

            ui->sexeAnimal->clear();
            QStringList list_sexe={"M","F"};
            ui->sexeAnimal->addItems(list_sexe);
            ui->typeAnimal->clear();
            QStringList list_type={"chien","chat","cheval"};
            ui->typeAnimal->addItems(list_type);

           ui->descAnimal->setText("");
           ui->idAnimal2->setText("");
            ui->tableAnimal->setModel(tmpanimal.afficher());
            additemnom();


    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modification"),
                    QObject::tr("Erreur.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        notification n;
        n.Alerte_Modifier(nom,1);
    }


}
}


void Sirine::on_ASC_clicked()
{
    animal  *a = nullptr ;

    ui->tableAnimal->setModel(a->trie());//

}

void Sirine::on_DES_clicked()
{
    animal  *a = nullptr ;

    ui->tableAnimal->setModel(a->triee());//

}

void Sirine::on_ASCC_clicked()
{
    carte  *c = nullptr ;

    ui->tableCarte->setModel(c->trieC());//

}

void Sirine::on_DESS_clicked()
{
    carte *c = nullptr ;

    ui->tableCarte->setModel(c->trieeC());//

}

void Sirine::on_rechercher_clicked()
{
    animal  *a = nullptr ;

    //ui->tableAnimal->setModel(a->rechercher());//

}


/*void Sirine::on_ASC_clicked()
{

}*/

void Sirine::on_radioButton_2_clicked()
{
    animal  *a = nullptr ;

    ui->tableAnimal->setModel(a->triee());//
}

void Sirine::on_rechAnimal_textChanged(const QString &arg1)
{
    QString str=ui->rechAnimal->text();
    ui->tableAnimal->setModel(tmpanimal.rechercherAnimal(str));
}

void Sirine::on_nomAnimal_textChanged(const QString &arg1)
{
    if(tmpanimal.testNom(ui->nomAnimal->text())){
        ui->testnom->setText("le nom de l'animal doit etre unique");
    }
    else {
        ui->testnom->setText("");
    }
}




void Sirine::on_statistics_clicked()
{
    openStatistcs();

}







void Sirine::on_pdf_clicked()
{

    QString strStream;
             QTextStream out(&strStream);

             const int rowCount = ui->tableCarte->model()->rowCount();
             const int columnCount = ui->tableCarte->model()->columnCount();

             out <<  "<html>\n"
                 "<head>\n"
                 "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                 <<  QString("<title>%1</title>\n").arg("strTitle")
                 <<  "</head>\n"
                 "<body bgcolor=#ffffff link=#5000A0>\n"

                //     "<align='right'> " << datefich << "</align>"
                 "<center> <H1>Liste des cartes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

             // headers
             out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
             for (int column = 0; column < columnCount; column++)
                 if (!ui->tableCarte->isColumnHidden(column))
                     out << QString("<th>%1</th>").arg(ui->tableCarte->model()->headerData(column, Qt::Horizontal).toString());
             out << "</tr></thead>\n";

             // data table
             for (int row = 0; row < rowCount; row++) {
                 out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                 for (int column = 0; column < columnCount; column++) {
                     if (!ui->tableCarte->isColumnHidden(column)) {
                         QString data = ui->tableCarte->model()->data(ui->tableCarte->model()->index(row, column)).toString().simplified();
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

void Sirine::on_pdfA_clicked()
{
    QString strStream;
                 QTextStream out(&strStream);

                 const int rowCount = ui->tableAnimal->model()->rowCount();
                 const int columnCount = ui->tableAnimal->model()->columnCount();

                 out <<  "<html>\n"
                     "<head>\n"
                     "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                     <<  QString("<title>%1</title>\n").arg("strTitle")
                     <<  "</head>\n"
                     "<body bgcolor=#ffffff link=#5000A0>\n"

                    //     "<align='right'> " << datefich << "</align>"
                     "<center> <H1>Liste des animaux </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                 // headers
                 out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                 for (int column = 0; column < columnCount; column++)
                     if (!ui->tableAnimal->isColumnHidden(column))
                         out << QString("<th>%1</th>").arg(ui->tableAnimal->model()->headerData(column, Qt::Horizontal).toString());
                 out << "</tr></thead>\n";

                 // data table
                 for (int row = 0; row < rowCount; row++) {
                     out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                     for (int column = 0; column < columnCount; column++) {
                         if (!ui->tableAnimal->isColumnHidden(column)) {
                             QString data = ui->tableAnimal->model()->data(ui->tableAnimal->model()->index(row, column)).toString().simplified();
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



void Sirine::openStatistcs()
{
    w = new MainWindow(); // Be sure to destroy your window somewhere
    w->show();
}




void Sirine::on_poids_textChanged(const QString &arg1)


    {
     ui->poids->setValidator( new QDoubleValidator(0.0, 50.00, 2, this));
}

void Sirine::on_temperature_textChanged(const QString &arg1)
{
      ui->temperature->setValidator( new QDoubleValidator(0.0, 50.00, 2, this));
}

void Sirine::on_taille_textChanged(const QString &arg1)
{
  ui->taille->setValidator( new QDoubleValidator(0.0, 5.00, 2, this));
}


void Sirine::on_imprimerA_clicked()
{


                //imprimer
                QPrinter printer;
                printer.setPrinterName("desiered printer name");
              QPrintDialog dialog(&printer,this);
                if(dialog.exec()== QDialog::Rejected)
                    return;

}



void Sirine::on_imprimerC_clicked()
{
    //imprimer
    QPrinter printer;
    printer.setPrinterName("desiered printer name");
  QPrintDialog dialog(&printer,this);
    if(dialog.exec()== QDialog::Rejected)
        return;


}


