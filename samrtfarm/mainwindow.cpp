#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDate>
#include <QModelIndex>
#include <QtPrintSupport>
#include <QPrinter>
#include <QPrintDialog>

#include "drilldownchart.h"
#include "drilldownslice.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QChar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableemp->setModel(tmpemploye.afficher(""));
    ui->tableView2->setModel(tableView2.afficher("",""));

//liste emloyee fetchh
   QSqlQuery query;

   query.prepare("select cin from employe ") ;

   query.exec();


   while (query.next()) {
          QVariant na = query.value(0);
          QString name = QVariant(na).toString();

        ui->comboBox_2->addItem(name);
      }

//fin liste emloyee fetch combo boxxxxx



//setStyleSheet("background-image: url(oi.jpg);");



//combobox nom emlpoyee
   connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)),
               this, SLOT(indexChanged(int)));

//Non selectable employe

   QStandardItemModel* model =
           qobject_cast<QStandardItemModel*>(ui->comboBox_2->model());
   QModelIndex firstIndex = model->index(0, ui->comboBox_2->modelColumn(),
           ui->comboBox_2->rootModelIndex());
   QStandardItem* firstItem = model->itemFromIndex(firstIndex);
   firstItem->setSelectable(false);

//Non selectable type


    model =
           qobject_cast<QStandardItemModel*>(ui->comboBox_3->model());
  firstIndex = model->index(0, ui->comboBox_3->modelColumn(),
           ui->comboBox_3->rootModelIndex());
  firstItem = model->itemFromIndex(firstIndex);
   firstItem->setSelectable(false);



   //Non selectable statut
    model =
           qobject_cast<QStandardItemModel*>(ui->statuttache->model());
   firstIndex = model->index(0, ui->statuttache->modelColumn(),
           ui->statuttache->rootModelIndex());
   firstItem = model->itemFromIndex(firstIndex);
   firstItem->setSelectable(false);


   //controle de saisie
        QIntValidator *roll=new QIntValidator(1,99999999);
            QIntValidator *roll2=new QIntValidator(1,999);
           ui->lineEdit_id->setValidator(roll);
           ui->idtache->setValidator(roll2);



//StatsTaches() ;






}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pb_ajouter_clicked()
{
    QString cin = ui->lineEdit_id->text();
    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    QString type= ui->comboBox->currentText();
     QString email= ui->lineEdit_email->text();
       QDate date = ui->dateEdit_3->date() ;

  employe e(cin,nom,prenom,email,type,date);
  bool test=e.ajouter();
  if(test)
{
      QMessageBox msgBox;
      msgBox.setIcon(QMessageBox::Information);
      msgBox.setWindowTitle( "Ajouter un employé");
      msgBox.setText(tr("Employé ajouté avec succée."));
      QAbstractButton* pButtonYes = msgBox.addButton(tr("Fermer"), QMessageBox::YesRole);

      msgBox.exec();


ui->tableemp->setModel(tmpemploye.afficher(""));
//update combobox employee on ajout or delete
  ui->comboBox_2->clear();
//liste emloyee fetchh
   QSqlQuery query;

   query.prepare("select cin from employe ") ;

   query.exec();


   while (query.next()) {
          QVariant na = query.value(0);
          QString name = QVariant(na).toString();

        ui->comboBox_2->addItem(name);
      }

//fin liste emloyee fetch combo boxxxxx

}
  else {
      QMessageBox msgBox;
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.setWindowTitle( "Ajouter un employé");
      msgBox.setText(tr("Erreur dans les champs !"));
      QAbstractButton* pButtonYes = msgBox.addButton(tr("Fermer"), QMessageBox::YesRole);

      msgBox.exec();

}

}
void MainWindow::on_pb_rechercher_clicked()
{ QString filtre=""; QString rech = ui->lineEdit_rech->text();
     QString tri="" ;

    if (ui->rb_asc->isChecked()   || ui->rb_desc->isChecked() )
          if (ui->rb_asc->isChecked() ) tri="asc " ;
                                            else  { tri="desc" ; } ;

     if (ui->rb_nom->isChecked()  ) {
      ui->tableemp->setModel(tmpemploye.rechercher(rech, filtre= ui->rb_nom->text(),tri ));}
     else if (ui->rb_type->isChecked()) {
      ui->tableemp->setModel(tmpemploye.rechercher(rech, filtre= ui->rb_type->text() , tri) );}
     else if  (ui->rb_cin->isChecked()) {
      ui->tableemp->setModel(tmpemploye.rechercher(rech, filtre= ui->rb_cin->text(), tri) );}
     else if  (ui->rb_email->isChecked()) {
      ui->tableemp->setModel(tmpemploye.rechercher(rech, filtre= ui->rb_email->text(), tri) );}

     else {


         QMessageBox msgBox;
         msgBox.setWindowTitle("Erreur");
         msgBox.setIcon(QMessageBox::Information);
         msgBox.setText(tr("Choississez un filtre !"));
         msgBox.setInformativeText("Email, Nom, CIN, Type") ;
         msgBox.addButton(tr("D'accord"), QMessageBox::NoRole);
         msgBox.exec();

     }  }
void MainWindow::on_afficher_clicked() {
    QString tri="" ;
    if (ui->rb_asc->isChecked()   || ui->rb_desc->isChecked() )
          if (ui->rb_asc->isChecked() ) tri="asc " ;
                                            else tri="desc";
      ui->tableemp->setModel(tmpemploye.afficher(tri));

}


void MainWindow::on_pb_suppr_clicked() {

    QItemSelectionModel *select = ui->tableemp->selectionModel();

   if( select->hasSelection() ) //check if has selection
   {


       QMessageBox msgBox;
       msgBox.setIcon(QMessageBox::Question);
       msgBox.setWindowTitle( "Supprimer un employé");
       msgBox.setText(tr("Etes-vous sur de supprimer cet employé ?"));
       QAbstractButton* pButtonYes = msgBox.addButton(tr("Supprimer"), QMessageBox::YesRole);
       msgBox.addButton(tr("Annuler"), QMessageBox::NoRole);
       msgBox.exec();


  /*    QMessageBox::StandardButton reply;
       reply = QMessageBox::question(this, "Supprimer un employé", "Etes-vous sur de supprimer cet employé ?",
                                     QMessageBox::Yes|QMessageBox::No);
  if (reply == QMessageBox::Yes) { */
      if (msgBox.clickedButton()==pButtonYes) {
QModelIndex index=ui->tableemp->selectionModel()->currentIndex();

QVariant value=index.sibling(index.row(),1).data();

QString s = QVariant(value).toString();


bool test=tmpemploye.supprimer(s);
if (test) {
 // ui->tabetudiant->setModel(tmpetudiant.afficher());//refresh

 QMessageBox msgBox2;
    msgBox2.setIcon(QMessageBox::Information);
    msgBox2.setWindowTitle( "Supprimer un employé");
    msgBox2.setText(tr("Employé supprimé."));
    msgBox2.addButton(tr("D'accord"), QMessageBox::NoRole);
    msgBox2.exec();


  //   QMessageBox::information(nullptr, QObject::tr("Supprimer un employé"),
          //       QObject::tr("employé supprimé.\n"), QMessageBox::NoIcon);
  ui->tableemp->setModel(tmpemploye.afficher(""));
  //update combobox employee on ajout or delete
    ui->comboBox_2->clear();
  //liste emloyee fetchh
     QSqlQuery query;

     query.prepare("select cin from employe ") ;

     query.exec();


     while (query.next()) {
            QVariant na = query.value(0);
            QString name = QVariant(na).toString();

          ui->comboBox_2->addItem(name);
        }

  //fin liste emloyee fetch combo boxxxxx


}


 else {
    QMessageBox msgBox3;
       msgBox3.setIcon(QMessageBox::Critical);
       msgBox3.setWindowTitle( "Supprimer un employé");
       msgBox3.setText(tr("Erreur lors de la suppression !"));
       msgBox3.addButton(tr("Fermer"), QMessageBox::NoRole);
       msgBox3.exec();


    // QMessageBox::critical(nullptr, QObject::tr("Supprimer un employé"),
            //     QObject::tr("Erreur !.\n"
                //             "Click Cancel to exit."), QMessageBox::Cancel);
}



   }} else {

       QMessageBox msgbox4;
          msgbox4.setIcon(QMessageBox::Information);
          msgbox4.setWindowTitle( "Supprimer un employé");
          msgbox4.setText(tr("Sélectionner un employé à supprimer d'abord !"));
          msgbox4.addButton(tr("D'accord"), QMessageBox::NoRole);
          msgbox4.exec();

     //  QMessageBox::information(nullptr, QObject::tr("Supprimer un employé"),
                //   QObject::tr("Sélectionner un employé à supprimer d'abord.\n"
                  //             ), QMessageBox::Ok);
   }

}
void MainWindow::on_impr2_clicked() {

    QString strStream;
    QTextStream out(&strStream);

     const int rowCount = ui->tableView2->model()->rowCount();
     const int columnCount = ui->tableView2->model()->columnCount();

     out <<  "<html>\n"
         "<head>\n"
         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
         <<  QString("<title>%1</title>\n").arg("strTitle")
         <<  "</head>\n"
         "<body bgcolor=#ffffff link=#5000A0>\n"
         "<table border=1 cellspacing=0 cellpadding=2>\n";

     // headers
     out << "<thead><tr bgcolor=#f0f0f0>";
     for (int column = 0; column < columnCount; column++)
         if (!ui->tableView2->isColumnHidden(column))
             out << QString("<th>%1</th>").arg(ui->tableView2->model()->headerData(column, Qt::Horizontal).toString());
     out << "</tr></thead>\n";

     // data table
     for (int row = 0; row < rowCount; row++) {
         out << "<tr>";
         for (int column = 0; column < columnCount; column++) {
             if (!ui->tableView2->isColumnHidden(column)) {
                 QString data = ui->tableView2->model()->data(ui->tableView2->model()->index(row, column)).toString().simplified();
                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
             }
         }
         out << "</tr>\n";
     }
     out <<  "</table>\n"
         "</body>\n"
         "</html>\n";

   QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

   QPrinter printer;


     QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
     if (dialog->exec() == QDialog::Accepted) {
         document->print(&printer);
     }

  delete document;
}




void MainWindow::on_imprimer1_clicked() {


    QString strStream;
    QTextStream out(&strStream);

     const int rowCount = ui->tableemp->model()->rowCount();
     const int columnCount = ui->tableemp->model()->columnCount();

     out <<  "<html>\n"
         "<head>\n"
         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
         <<  QString("<title>%1</title>\n").arg("strTitle")
         <<  "</head>\n"
         "<body bgcolor=#ffffff link=#5000A0>\n"
         "<table border=1 cellspacing=0 cellpadding=2>\n";

     // headers
     out << "<thead><tr bgcolor=#f0f0f0>";
     for (int column = 0; column < columnCount; column++)
         if (!ui->tableemp->isColumnHidden(column))
             out << QString("<th>%1</th>").arg(ui->tableemp->model()->headerData(column, Qt::Horizontal).toString());
     out << "</tr></thead>\n";

     // data table
     for (int row = 0; row < rowCount; row++) {
         out << "<tr>";
         for (int column = 0; column < columnCount; column++) {
             if (!ui->tableemp->isColumnHidden(column)) {
                 QString data = ui->tableemp->model()->data(ui->tableemp->model()->index(row, column)).toString().simplified();
                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
             }
         }
         out << "</tr>\n";
     }
     out <<  "</table>\n"
         "</body>\n"
         "</html>\n";

   QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

   QPrinter printer;


     QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
     if (dialog->exec() == QDialog::Accepted) {
         document->print(&printer);
     }

  delete document;
}




void MainWindow::on_pdf_clicked() {

   /* QMessageBox msgBox;
    msgBox.setText(tr("Confirm?"));
    QAbstractButton* pButtonhtml = msgBox.addButton(tr("HTML"), QMessageBox::YesRole);
    QAbstractButton* pButtonpdf = msgBox.addButton(tr("PDF"), QMessageBox::NoRole);


    msgBox.exec();

    if (msgBox.clickedButton()==pButtonhtml) { */
    QString datefich = QDateTime::currentDateTime().toString();
    if ( ui->sauv1->currentText()=="En HTML") {

   QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en HTML ", QString(), "*.html");
  if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".html"); }


   QFile strStream(fileName);
   // QString strStream;
    QTextStream out(&strStream);
   strStream.open(QFile::WriteOnly | QFile::Truncate) ;

    const int rowCount = ui->tableemp->model()->rowCount();
    const int columnCount = ui->tableemp->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>Liste des Employees</title>\n")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
          "<align='right'> " << datefich << "</align>"
        "<center> <H1>Liste des Employees</H1>"
                                            "</br></br><table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableemp->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableemp->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableemp->isColumnHidden(column)) {
                QString data = ui->tableemp->model()->data(ui->tableemp->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"
        "</body>\n"
        "</html>\n";

    }
    else {

       QString strStream;
         QTextStream out(&strStream);

         const int rowCount = ui->tableemp->model()->rowCount();
         const int columnCount = ui->tableemp->model()->columnCount();

         out <<  "<html>\n"
             "<head>\n"
             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
             <<  QString("<title>Liste des Employees</title>\n").arg("strTitle")
             <<  "</head>\n"
             "<body bgcolor=#ffffff link=#5000A0>\n"
                 "<align='right'> " << datefich << "</align>"
             "<center> <H1>Liste des Employees</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

         // headers
         out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
         for (int column = 0; column < columnCount; column++)
             if (!ui->tableemp->isColumnHidden(column))
                 out << QString("<th>%1</th>").arg(ui->tableemp->model()->headerData(column, Qt::Horizontal).toString());
         out << "</tr></thead>\n";

         // data table
         for (int row = 0; row < rowCount; row++) {
             out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
             for (int column = 0; column < columnCount; column++) {
                 if (!ui->tableemp->isColumnHidden(column)) {
                     QString data = ui->tableemp->model()->data(ui->tableemp->model()->index(row, column)).toString().simplified();
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




}

void MainWindow::on_pdf22_clicked() {

QString datefich = QDateTime::currentDateTime().toString();
     if ( ui->sauv2->currentText()=="En HTML") {

    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en HTML ", QString(), "*.html");
   if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".html"); }





    QFile strStream(fileName);
    // QString strStream;
     QTextStream out(&strStream);
    strStream.open(QFile::WriteOnly | QFile::Truncate) ;

     const int rowCount = ui->tableView2->model()->rowCount();
     const int columnCount = ui->tableView2->model()->columnCount();

     out <<  "<html>\n"
         "<head>\n"
         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
         <<  QString("<title>Liste Des Taches</title>\n")
         <<  "</head>\n"
         "<body bgcolor=#ffffff link=#5000A0>\n"
 "<align='right'> " << datefich << "</align>"
     "<center> <H1>Liste des Taches</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

     // headers
     out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
     for (int column = 0; column < columnCount; column++)
         if (!ui->tableView2->isColumnHidden(column))
             out << QString("<th>%1</th>").arg(ui->tableView2->model()->headerData(column, Qt::Horizontal).toString());
     out << "</tr></thead>\n";

     // data table
     for (int row = 0; row < rowCount; row++) {
         out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
         for (int column = 0; column < columnCount; column++) {
             if (!ui->tableView2->isColumnHidden(column)) {
                 QString data = ui->tableView2->model()->data(ui->tableView2->model()->index(row, column)).toString().simplified();
                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
             }
         }
         out << "</tr>\n";
     }
     out <<  "</table> </center>\n"
         "</body>\n"
         "</html>\n";

     }
     else {

        QString strStream;
          QTextStream out(&strStream);

          const int rowCount = ui->tableView2->model()->rowCount();
          const int columnCount = ui->tableView2->model()->columnCount();

          out <<  "<html>\n"
              "<head>\n"
              "<meta Content=\"Text/html; charset=Windows-1251\">\n"
              <<  QString("<title>%1</title>\n").arg("strTitle")
              <<  "</head>\n"
              "<body bgcolor=#ffffff link=#5000A0>\n"

                  "<align='right'> " << datefich << "</align>"
              "<center> <H1>Liste des Taches</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

          // headers
          out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
          for (int column = 0; column < columnCount; column++)
              if (!ui->tableView2->isColumnHidden(column))
                  out << QString("<th>%1</th>").arg(ui->tableView2->model()->headerData(column, Qt::Horizontal).toString());
          out << "</tr></thead>\n";

          // data table
          for (int row = 0; row < rowCount; row++) {
              out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
              for (int column = 0; column < columnCount; column++) {
                  if (!ui->tableView2->isColumnHidden(column)) {
                      QString data = ui->tableView2->model()->data(ui->tableView2->model()->index(row, column)).toString().simplified();
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




 }









void MainWindow::on_pb_ajouter2_clicked(){

    int id = ui->idtache->text().toInt();
    QString nom= ui->nomtache->text();
    QString description= ui->descriptiontache->text();
    QString type= ui->comboBox_3->currentText();
     QDate date_limit= ui->datelm->date();
     QDate datedb=  ui->datedeb->date();
       QString statut = ui->statuttache->currentText() ;
 QString cin= ui->comboBox_2->currentText();
  tache t (id,nom,description ,type ,date_limit ,datedb,statut, cin) ;

  bool test=t.ajouter();
  if(test)
{


QMessageBox::information(nullptr, QObject::tr("Ajouter une tâche"),
                  QObject::tr("Tâche ajoutée avec succée.\n"
                              "Click Ok to exit."), QMessageBox::Ok);
ui->tableView2->setModel(tableView2.afficher("",""));
StatsTaches() ;

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une tâche"),
                  QObject::tr("Erreur dans les champs !\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_affichertache_clicked(){
 QString tri2="" ;  QString stat="Tous";
    if (ui->radioButton_4->isChecked()   || ui->radioButton_5->isChecked() )
          if (ui->radioButton_4->isChecked() ) tri2="asc" ;
                                            else tri2="desc";

    if (ui->radioButton->isChecked()   || ui->radioButton_2->isChecked() )
          if (ui->radioButton->isChecked() ) stat=ui->radioButton->text() ;
                                            else stat=ui->radioButton_2->text() ;

      ui->tableView2->setModel(tableView2.afficher(tri2,stat));
}




void MainWindow::on_recherche22_clicked()
{  QString rech = ui->lineEdit_rech2->text();
     QString tri="" ;

     if (ui->radioButton_4->isChecked()   || ui->radioButton_5->isChecked() )
           if (ui->radioButton_4->isChecked() ) tri="asc" ;
                                             else  tri="desc";
QDate drech = ui->dateEdit_rech->date();
    ui->tableView2->setModel(tableView2.rechercher(rech,tri, drech ));

     }

void MainWindow::on_supprim2tache_clicked() {



    QItemSelectionModel *select = ui->tableView2->selectionModel();

   if( select->hasSelection() ) //check if has selection
   {

       QMessageBox msgBox;
       msgBox.setIcon(QMessageBox::Question);
       msgBox.setWindowTitle( "Supprimer une tâche");
       msgBox.setText(tr("Etes-vous sur de supprimer cette tâche ?"));
       QAbstractButton* pButtonYes = msgBox.addButton(tr("Supprimer"), QMessageBox::YesRole);
       msgBox.addButton(tr("Annuler"), QMessageBox::NoRole);
       msgBox.exec();

    if (msgBox.clickedButton()==pButtonYes) {

QModelIndex index=ui->tableView2->selectionModel()->currentIndex();

QVariant value=index.sibling(index.row(),0).data();

int s = QVariant(value).toInt();


bool test=tableView2.supprimer(s);
if (test) {
 // ui->tableView2->setModel(tableView2.afficher());//refresh
     QMessageBox::information(nullptr, QObject::tr("Supprimer une tâche"),
                 QObject::tr("tâche supprimée.\n"), QMessageBox::NoIcon);
   ui->tableView2->setModel(tableView2.afficher("",""));
StatsTaches() ;
}


 else {

    QMessageBox msgBox3;
       msgBox3.setIcon(QMessageBox::Critical);
       msgBox3.setWindowTitle( "Supprimer une tâche");
       msgBox3.setText(tr("Erreur lors de la suppression !"));
       msgBox3.addButton(tr("Fermer"), QMessageBox::NoRole);
       msgBox3.exec();



}



   }} else {
       QMessageBox msgBox3;
          msgBox3.setIcon(QMessageBox::Information);
          msgBox3.setWindowTitle( "Supprimer une tâche");
          msgBox3.setText(tr("Sélectionner une tâche à supprimer d'abord  !"));
          msgBox3.addButton(tr("D'accord"), QMessageBox::NoRole);
          msgBox3.exec();


   }

}

void MainWindow::on_ModifierEmp_clicked() {

    QItemSelectionModel *select = ui->tableemp->selectionModel();

   if( select->hasSelection() ) //check if has selection
   {
  QModelIndex index=ui->tableemp->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),0).data();
    QString s = QVariant(value).toString();
    //fech employe
       QSqlQuery query;

       query.prepare("select NOM, PRENOM , EMAIL , TYPE , DATE_NAISS , cin from employe where cin=:cin ") ;
         query.bindValue(":cin", s);
       query.exec();


       query.next();
              QVariant na = query.value(0);
              QString name = QVariant(na).toString();
              ui->lineEdit_nom->setText(name);
              QVariant pa = query.value(1);
              QString prname = QVariant(pa).toString();
               ui->lineEdit_prenom->setText(prname);
              QVariant em = query.value(2);
              QString eemaill = QVariant(em).toString();
                ui->lineEdit_email->setText(eemaill);

                QVariant dd = query.value(4);
                QDate dated = QVariant(dd).toDate();
                ui->dateEdit_3->setDate(dated);


                QVariant c = query.value(5);
                QString cinnnn = QVariant(c).toString();
                  ui->lineEdit_id->setText(cinnnn);

                  QVariant ty = query.value(3);
                  QString typp = QVariant(ty).toString();

                  int indextyp = ui->comboBox->findText(typp) ;

                  ui->comboBox->setCurrentIndex(indextyp);
               /*   if(typp=="Veterinaire")   ui->comboBox->setCurrentIndex(0);
                  if(typp=="Agent") ui->comboBox->setCurrentIndex(1);
                  if(typp=="Fermier") ui->comboBox->setCurrentIndex(2);
                  if(typp=="Ouvrier") ui->comboBox->setCurrentIndex(3);*/

    //fin


} else {
       QMessageBox msgBox;
          msgBox.setIcon(QMessageBox::Information);
          msgBox.setWindowTitle( "Modifier un employé");
          msgBox.setText(tr("Sélectionner un employé à modifier d'abord !"));
          msgBox.addButton(tr("D'accord"), QMessageBox::NoRole);
          msgBox.exec();


   //    QMessageBox::information(nullptr, QObject::tr("Modifier un employé"),
                 //  QObject::tr("Sélectionner un employé à modifier d'abord.\n"
                          //     ), QMessageBox::Ok);
   }

}
void MainWindow::on_modif222_clicked() {
    int id = ui->idtache->text().toInt();
    QString cin = ui->comboBox_2->currentText();
    QString nom=ui->nomtache->text();
    QString description= ui->descriptiontache->text();
    QString type= ui->comboBox_3->currentText();
       QDate date_deb = ui->datedeb->date() ;
       QDate date_limit = ui->datelm->date() ;
QString statut = ui->statuttache->currentText();
  tache e;
  bool test=e.modifier(  id,  nom, description , type , date_limit ,  date_deb , statut,  cin);
  if(test)
{

      QMessageBox msgBox;
         msgBox.setIcon(QMessageBox::Information);
         msgBox.setWindowTitle( "Modifier une tâche");
         msgBox.setText(tr("tache modifié avec succée. !"));
         msgBox.addButton(tr("D'accord"), QMessageBox::NoRole);
         msgBox.exec();

//QMessageBox::information(nullptr, QObject::tr("Modifier une tache"),
           //      QObject::tr("tache modifié avec succée.\n"
                        //      "Click Ok to exit."), QMessageBox::Ok);
ui->tableView2->setModel(tableView2.afficher("",""));
StatsTaches() ;
}
  else {
      QMessageBox msgBox;
         msgBox.setIcon(QMessageBox::Critical);
         msgBox.setWindowTitle( "Modifier une tâche");
         msgBox.setText(tr("Erreur dans les champs !"));
         msgBox.addButton(tr("D'accord"), QMessageBox::NoRole);
         msgBox.exec();
     // QMessageBox::critical(nullptr, QObject::tr("Modifier une tache"),
             //     QObject::tr("Erreur dans les champs !\n"
                          //    "Click Cancel to exit."), QMessageBox::Cancel);

}

}
void MainWindow::on_modifier1_clicked() {


                  QString cin = ui->lineEdit_id->text();
                  QString nom= ui->lineEdit_nom->text();
                  QString prenom= ui->lineEdit_prenom->text();
                  QString type= ui->comboBox->currentText();
                   QString email= ui->lineEdit_email->text();
                     QDate dat = ui->dateEdit_3->date() ;

                employe e;
                bool test=e.modifier( cin,  nom, prenom , email , type,dat ) ;
                if(test)
              {


                    QMessageBox msgBox;
                       msgBox.setIcon(QMessageBox::Information);
                       msgBox.setWindowTitle( "Modifier un employé");
                       msgBox.setText(tr("Employé modifié avec succée !"));
                       msgBox.addButton(tr("D'accord"), QMessageBox::NoRole);
                       msgBox.exec();


 ui->tableemp->setModel(tmpemploye.afficher(""));
              }
                else {   QMessageBox msgBox2;
                    msgBox2.setIcon(QMessageBox::Critical);
                    msgBox2.setWindowTitle( "Modifier un employé");
                    msgBox2.setText(tr("Erreur dans les champs !"));
                    msgBox2.addButton(tr("Fermer"), QMessageBox::NoRole);
                    msgBox2.exec();





}

}

void MainWindow::on_modifier22_clicked() {


    QItemSelectionModel *select = ui->tableView2->selectionModel();

   if( select->hasSelection() ) //check if has selection
   {
  QModelIndex index=ui->tableView2->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),0).data();
    int s = QVariant(value).toInt();
    QVariant valuecin=index.sibling(index.row(),7).data();
    QString vcin = QVariant(valuecin).toString();
    //fech employe
       QSqlQuery query;

       query.prepare("select  NOM, Description , DATE_LIMIT , STATUT , TYPE ,  ID_TACHE ,DATE_DEBUT from tache where ID_TACHE=:ID_TACHE ") ;
         query.bindValue(":ID_TACHE", s);
       query.exec();


       query.next();
              QVariant na = query.value(0);
              QString name = QVariant(na).toString();
             ui->nomtache->setText(name);
              QVariant pa = query.value(1);
              QString prname = QVariant(pa).toString();
               ui->descriptiontache->setText(prname);

               QVariant dd = query.value(6);
               QDate dated = QVariant(dd).toDate();
               ui->datedeb->setDate(dated);

                 dd = query.value(2);
                 dated = QVariant(dd).toDate();
                ui->datelm->setDate(dated);

                QVariant ty = query.value(3);
                QString typp = QVariant(ty).toString();

                if(typp=="En Cours")   ui->statuttache->setCurrentIndex(1);
                if(typp=="Achevees") ui->statuttache->setCurrentIndex(2);

                QVariant tp = query.value(4);
                QString typ = QVariant(tp).toString();
              if(typ=="Urgente")   ui->comboBox_3->setCurrentIndex(1);
               if(typ=="Ordinaire") ui->comboBox_3->setCurrentIndex(2);


                QVariant c = query.value(5);
                QString cinnnn = QVariant(c).toString();
                 ui->idtache->setText(cinnnn);


                  int indexcin = ui->comboBox_2->findText(vcin) ;

                  ui->comboBox_2->setCurrentIndex(indexcin);

    //fin


} else {
       QMessageBox msgBox;
                          msgBox.setIcon(QMessageBox::Information);
                          msgBox.setWindowTitle( "Modifier une tâche");
                          msgBox.setText(tr("Sélectionner une tâche à modifier d'abord. !"));
                          msgBox.addButton(tr("D'accord"), QMessageBox::NoRole);
                          msgBox.exec();



   }

}

void MainWindow::on_resetpb_clicked() {

    ui->lineEdit_id->setText("") ;
   ui->lineEdit_nom->setText("");
    ui->lineEdit_prenom->setText("");
    ui->comboBox->setCurrentIndex(0);
      ui->lineEdit_email->setText("");

      QDate d = QDate::currentDate() ;
      ui->dateEdit_3->setDate(d) ;
}
void MainWindow::on_resetpb2_clicked() {
  ui->idtache->setText("") ;
ui->nomtache->setText("") ;
ui->descriptiontache->setText("") ;
  ui->comboBox_3->setCurrentIndex(0);
 QDate d = QDate::currentDate() ;
 ui->datedeb->setDate(d) ;
 ui->datelm->setDate(d) ;
      ui->statuttache->setCurrentIndex(0);
   ui->comboBox_2->setCurrentIndex(0);

}
void MainWindow::indexChanged(int index  ){
    QSqlQuery query;
     QString cin= ui->comboBox_2->currentText();
    query.prepare("select nom , prenom from employe where cin = :cin ") ;
    query.bindValue(":cin",cin);
    query.exec();


    query.next();
           QVariant na = query.value(0);
           QString name = QVariant(na).toString();
           QVariant pa = query.value(1);
           QString prenom = QVariant(pa).toString();
           ui->label->setText(name+" "+prenom) ;

}




void MainWindow::on_stats_clicked()
{

/*
    QMainWindow *nw = new QMainWindow();

    DrilldownChart *chart = new DrilldownChart();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QPieSeries *yearSeries = new QPieSeries(nw);
    yearSeries->setName("Tâches par leurs statuts");

    const QStringList months = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    const QStringList names = {
        "En cours", "Achevées", "En attente",
    };

    for (const QString &name : names) {
        QPieSeries *series = new QPieSeries(nw);
        series->setName("Sales by month - " + name);

        for (const QString &month : months)
            *series << new DrilldownSlice(QRandomGenerator::global()->bounded(10), month, yearSeries);



        *yearSeries << new DrilldownSlice(series->sum(), name, series);
    }



    chart->changeSeries(yearSeries);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);







   nw->setCentralWidget(chartView);
    nw->resize(800, 500);
    nw->show();



/*
    MainWindow *nw = new MainWindow();
    QChartView *chartView = new QChartView(donutBreakdown);
    chartView->setRenderHint(QPainter::Antialiasing);
     nw->setCentralWidget(chartView);
     nw->resize(800, 500);
    nw->show();
    */

   //boucle pour connaitre l indice du tab statistique
   /* int i ,s=0, k=0;
    for(i=0; i < ui->ez->count(); i++ )
        if (ui->ez->tabText(i) =="Tâches Stats") {
            k++;
            break ;}



    if (k!=0)
//go to tab page stats
ui->ez->setCurrentIndex(i);
    else  { StatsTaches() ;
        for(i=0; i < ui->ez->count(); i++ )
            if (ui->ez->tabText(i) =="Tâches Stats")  {
s++;
                break;}

    ui->ez->setCurrentIndex(s-1);

}*/
StatsTaches() ;
//boucle pour connaitre l indice du tab statistique
 int i ;
 for(i=0; i < ui->ez->count(); i++ )
     if (ui->ez->tabText(i) =="Tâches Stats") {

         break ;}
ui->ez->setCurrentIndex(i);




}

void MainWindow::on_lineEdit_id_editingFinished()
{
    if (ui->lineEdit_id->text().length()!=8 )  {

        QMessageBox msgBox;
                           msgBox.setIcon(QMessageBox::Warning);
                           msgBox.setWindowTitle( "Numero CIN");
                           msgBox.setText(tr("CIN foit être de 8 chiffres  !"));
                           msgBox.addButton(tr("Fermer"), QMessageBox::NoRole);
                           msgBox.exec();



} }

void MainWindow::on_lineEdit_nom_textEdited(const QString &arg1)
{
int L =ui->lineEdit_nom->text().length() ;
for (int i=0;i<L;i++ )
    if (ui->lineEdit_nom->text().at(i).isDigit())
        {
            QMessageBox msgBox;
                               msgBox.setIcon(QMessageBox::Warning);
                               msgBox.setWindowTitle( "Nom Employee");
                               msgBox.setText(tr("Le nom ne doit pas contenir des chiffres  !"));
                               msgBox.addButton(tr("Fermer"), QMessageBox::NoRole);
                               msgBox.exec();


        }


}

void MainWindow::on_lineEdit_prenom_textEdited(const QString &arg1)
{
    int L =ui->lineEdit_prenom->text().length() ;
    for (int i=0;i<L;i++ )
        if (ui->lineEdit_prenom->text().at(i).isDigit()) {
            QMessageBox msgBox;
                               msgBox.setIcon(QMessageBox::Warning);
                               msgBox.setWindowTitle( "Prenom Employee");
                               msgBox.setText(tr("Le prenom ne doit pas contenir des chiffres  !"));
                               msgBox.addButton(tr("Fermer"), QMessageBox::NoRole);
                               msgBox.exec();


}}


void MainWindow::on_lineEdit_email_editingFinished()
{
    if ( ui->lineEdit_email->text().indexOf("@")<0 ){

        QMessageBox msgBox;
                           msgBox.setIcon(QMessageBox::Warning);
                           msgBox.setWindowTitle( "Email Employee");
                           msgBox.setText(tr("Entrer une email valide ! ( @ )"));
                           msgBox.addButton(tr("D'accord"), QMessageBox::NoRole);
                           msgBox.exec();


    }


      if ( ui->lineEdit_email->text().indexOf("@")> 0 )
    if ( ui->lineEdit_email->text().indexOf(".")<0 ) {
        QMessageBox msgBox2;
                           msgBox2.setIcon(QMessageBox::Warning);
                           msgBox2.setWindowTitle( "Email Employee");
                           msgBox2.setText(tr("Entrer une email valide ! ( . )"));
                           msgBox2.addButton(tr("D'accord"), QMessageBox::NoRole);
                           msgBox2.exec();

}}



void MainWindow::StatsTaches() {
     QSqlQuery query;


    // --------------------------STATS Tâches------------------------------------


       QMainWindow *nw = new QMainWindow();

       DrilldownChart *chart = new DrilldownChart();
       chart->setTheme(QChart::ChartThemeLight);
       chart->setAnimationOptions(QChart::AllAnimations);
       chart->legend()->setVisible(true);
       chart->legend()->setAlignment(Qt::AlignRight);

       QPieSeries *yearSeries = new QPieSeries(nw);
       yearSeries->setName("Tâches par leurs statuts");



           QPieSeries *series = new QPieSeries(nw);

 //          series->setName("Sales by month - " );
 //         *series << new DrilldownSlice(QRandomGenerator::global()->bounded(10), "month", yearSeries);


           //fetch data for taches stats
          //        QSqlQuery query;

              query.prepare(" SELECT COUNT(*)  FROM TACHE where STATUT = 'Achevees'   ") ;
              query.exec();
              query.next();
              QVariant na = query.value(0);
       int    NumAcheves = na.toInt() ;

              query.prepare(" SELECT COUNT(*)  FROM TACHE where STATUT = 'En Cours'   ") ;
              query.exec();
              query.next();
              na = query.value(0);
       int    NumEnCours = na.toInt() ;




              query.prepare(" SELECT COUNT(*)  FROM TACHE where STATUT = 'En Attente'   ") ;
              query.exec();
              query.next();
              na = query.value(0);
       int    NumEnAttente = na.toInt() ;







           *yearSeries << new DrilldownSlice(NumAcheves, "Achevees ", series);
          *yearSeries << new DrilldownSlice(NumEnCours, "En Cours ", series);
           *yearSeries << new DrilldownSlice(NumEnAttente, "En Attente ", series);


       chart->changeSeries(yearSeries);

       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);




       QFrame *frame= new QFrame(this);
   //    frame->setMinimumWidth(800);
  //     frame->setMinimumHeight(500);

auto *hLayout = new QVBoxLayout;

     //  QHBoxLayout *hLayout = new QHBoxLayout();

  //    hLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
       hLayout->addWidget(chartView);
   //   hLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

frame->setLayout(hLayout);

//boucle for pour chercher si le tab de statistique existe ou pas
bool exist = false ;
int i ;
for(i=0; i < ui->ez->count(); i++ ) {
    if (ui->ez->tabText(i) =="Tâches Stats") {
        exist=true;
        break ;
    }

}



if (exist) {
    ui->ez->removeTab(i);
   ui->ez->addTab(frame, "Tâches Stats");
} else
 ui->ez->addTab(frame, "Tâches Stats");






  // --------------------------Stats Tâches-----------------------------
}
void MainWindow::StatsEmply() {
    QSqlQuery query;


   // --------------------------STATS Employes------------------------------------


      QMainWindow *nw = new QMainWindow();

      DrilldownChart *chart = new DrilldownChart();
      chart->setTheme(QChart::ChartThemeLight);
      chart->setAnimationOptions(QChart::AllAnimations);
      chart->legend()->setVisible(true);
      chart->legend()->setAlignment(Qt::AlignRight);

      QPieSeries *yearSeries = new QPieSeries(nw);
      yearSeries->setName("Emplyoées par types");



          QPieSeries *series = new QPieSeries(nw);

//          series->setName("Sales by month - " );
//         *series << new DrilldownSlice(QRandomGenerator::global()->bounded(10), "month", yearSeries);


          //fetch data for Employes stats
         //        QSqlQuery query;

             query.prepare(" SELECT COUNT(*)  FROM EMPLOYE where TYPE = 'Veterinaire'   ") ;
             query.exec();
             query.next();
             QVariant na = query.value(0);
      int    NumVeterinaire = na.toInt() ;

             query.prepare(" SELECT COUNT(*)  FROM EMPLOYE where TYPE = 'Agent'   ") ;
             query.exec();
             query.next();
             na = query.value(0);
      int    NumAgent = na.toInt() ;




             query.prepare(" SELECT COUNT(*)  FROM EMPLOYE where TYPE = 'Fermier'   ") ;
             query.exec();
             query.next();
             na = query.value(0);
      int    NumFermier= na.toInt() ;



      query.prepare(" SELECT COUNT(*)  FROM EMPLOYE where TYPE = 'Ouvrier'   ") ;
      query.exec();
      query.next();
      na = query.value(0);
int    NumOuvrier = na.toInt() ;




           *yearSeries << new DrilldownSlice(NumVeterinaire, "Vétérinaires ", series);
           *yearSeries << new DrilldownSlice(NumAgent, "Agents", series);
           *yearSeries << new DrilldownSlice(NumFermier, "Fermiers ", series);
           *yearSeries << new DrilldownSlice(NumOuvrier, "Ouvriers ", series);


      chart->changeSeries(yearSeries);

      QChartView *chartView = new QChartView(chart);
      chartView->setRenderHint(QPainter::Antialiasing);




      QFrame *frame= new QFrame(this);
  //    frame->setMinimumWidth(800);
 //     frame->setMinimumHeight(500);

auto *hLayout = new QVBoxLayout;

    //  QHBoxLayout *hLayout = new QHBoxLayout();

 //    hLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
      hLayout->addWidget(chartView);
  //   hLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

frame->setLayout(hLayout);

//boucle for pour chercher si le tab de statistique existe ou pas
bool exist = false ;
int i ;
for(i=0; i < ui->ez->count(); i++ ) {
   if (ui->ez->tabText(i) =="Employes Stats") {
       exist=true;
       break ;
   }

}



if (exist) {
   ui->ez->removeTab(i);
  ui->ez->addTab(frame, "Employes Stats");
} else
ui->ez->addTab(frame, "Employes Stats");






 // --------------------------Stats Employes-----------------------------

}




void MainWindow::on_emplystats_clicked()
{

  StatsEmply() ;
    //boucle pour connaitre l indice du tab statistique
     int i ;
     for(i=0; i < ui->ez->count(); i++ )
         if (ui->ez->tabText(i) =="Employes Stats") {

             break ;}
    ui->ez->setCurrentIndex(i);
}
