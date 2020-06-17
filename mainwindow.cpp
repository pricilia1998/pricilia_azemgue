#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
//#include "dialog.h"
//#include "ui_dialog.h"
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
#include <QRadioButton>
#include <QRegExp>
#include <QRegExpValidator>
#include <QValidator>


#include <QtSql/QSqlQueryModel>
#include<QtSql/QSqlQuery>
#include<QVariant>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QMainWindow(parent)
    ui->tableViewzone->setModel(Z.afficher_zone());//refresh
    ui->tableViewrecolte->setModel(R.afficher_recolte());//refresh
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouterR_clicked()
{
    int ID_RECOLTE = ui->line->text().toInt();
    QString CULTURE= ui->lineEditCR->text();
    float MASSE= ui->doubleSpinBox_3->value();
    float PRIX= ui->doubleSpinBox_2->value();


   Recolte r(ID_RECOLTE,CULTURE,MASSE,PRIX);
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

void MainWindow::on_suppR_clicked()
{

    int ID_RECOLTE= ui->line->text().toInt();
     bool test=R.supprimer_recolte(ID_RECOLTE);
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

/*void MainWindow::on_trierR_clicked()
{

    Recolte   *sa = nullptr ;

     ui->tableViewrecolte->setModel(sa->tri_recolte());//refresh
     ui->tableViewzone->setModel(Z.afficher_zone());//refresh
}*/


bool MainWindow::on_rechermodifR_clicked()
{

    QSqlQuery query;
    int cod = ui->line->text().toInt();

    QString res = QString::number(cod);
    query.prepare("SELECT * FROM RECOLTE WHERE ID_RECOLTE = :cod");
    query.bindValue(":cod", res);
    query.exec();
    if(query.first())
    {
        QMessageBox::information(this, tr("Modifier recolte"), tr("La recolte est trouvé avec success, Veuillez entrer les nouvelles informations."));
         //ui->line_2->setText(query.value(0).toString());
         ui->lineEditCR->setText(query.value(1).toString());
         ui->doubleSpinBox_3->setValue(query.value(2).toInt());
         ui->doubleSpinBox_2->setValue(query.value(3).toInt());

         ui->tableViewrecolte->setModel(R.afficher_recolte());//refresh

        return true;
}

}

void MainWindow::on_ajouterZ_clicked()
{
    int ID_ZONE; //= ui->idFour_2->text().toInt();
   int DIMENSION= ui->doubleSpinBox->value();
    QString ETAT= ui->lineEdit_6->text();
    QString DISCRIPTION= ui->desc->text();


  Zone z(ID_ZONE,DIMENSION,ETAT,DISCRIPTION);
  bool test=z.ajouter_zone();
  if(test)
{

    QMessageBox::information(nullptr, QObject::tr("Ajouter une parcelle"),
                  QObject::tr("Parcelle ajoutée.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une parcelle"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tableViewzone->setModel(z.afficher_zone());//refresh
}


void MainWindow::on_suppZ_clicked()
{
    int ID= ui->IDD->text().toInt();
     bool test=Z.supprimer_zone(ID);
     if(test)
     {
         QMessageBox::information(nullptr, QObject::tr("Supprimer une parcelle"),
                     QObject::tr("Parcelle supprimée.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
   }
     else
         QMessageBox::critical(nullptr, QObject::tr("Supprimer une parcelle"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
       ui->tableViewzone->setModel(Z.afficher_zone());//refresh
}


bool MainWindow::on_rechermodifZ_clicked()
{


    QSqlQuery query;
    int cod = ui->IDD->text().toInt();

    QString res = QString::number(cod);
    query.prepare("SELECT * FROM ZONE WHERE ID_ZONE = :cod");
    query.bindValue(":cod", res);
    query.exec();
    if(query.first())
    {
        QMessageBox::information(this, tr("Modifier parcelle"), tr("La parcelle est trouvé avec success, Veuillez entrer les nouvelles informations."));
          //ui->id->setText(query.value(0).toString());
          ui->doubleSpinBox->setValue(query.value(1).toInt());
          ui->lineEdit_6->setText(query.value(2).toString());
          ui->desc->setText(query.value(3).toString());


        ui->tableViewzone->setModel(Z.afficher_zone());//refresh

   }
 return true;
}


void MainWindow::on_mail_clicked()
{
    Smtp *s=new Smtp("fournisseurX@gmail.com","fournisseur123","smtp.gmail.com",465);
    s->sendMail("fournisseurX@gmail.com",ui->lineEdit_7->text(),ui->lineEdit_8->text(),ui->lineEdit_9->text());

}

void MainWindow::on_mail_2_clicked()
{
    Smtp *s=new Smtp("fournisseurX@gmail.com","fournisseur123","smtp.gmail.com",465);
    s->sendMail("fournisseurX@gmail.com",ui->lineEdit_10->text(),ui->lineEdit_11->text(),ui->lineEdit_12->text());
}

void MainWindow::on_stat_clicked()
{
    double dag=0;
    double dir=0;


    QSqlQuery q;
        q.prepare("SELECT * FROM RECOLTE WHERE MASSE like 'MASSE' ");
        q.exec();
          while (q.next())
        {
        dag++;
        }

          q.prepare("SELECT * FROM RECOLTE WHERE PRIX like 'PRIX' ");
          q.exec();
            while (q.next())
          {
          dir++;
          }

    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->gplot->setBackground(QBrush(gradient));

    // create empty bar chart objects:

    QCPBars *fossil = new QCPBars(ui->gplot->xAxis, ui->gplot->yAxis);
    fossil->setAntialiased(false);


    fossil->setStackingGap(1);
    // set names and colors:
    /*fossil->setName("nembre des offres");
    fossil->setPen(QPen(QColor(111, 9, 176).lighter(170)));
    fossil->setBrush(QColor(111, 9, 176));*/


    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 ;
    labels << "MASSE" << "PRIX" ;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->gplot->xAxis->setTicker(textTicker);
    ui->gplot->xAxis->setTickLabelRotation(60);
    ui->gplot->xAxis->setSubTicks(false);
    ui->gplot->xAxis->setTickLength(0, 4);
    ui->gplot->xAxis->setRange(0, 13);
    ui->gplot->xAxis->setBasePen(QPen(Qt::white));
    ui->gplot->xAxis->setTickPen(QPen(Qt::white));
    ui->gplot->xAxis->grid()->setVisible(true);
    ui->gplot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->gplot->xAxis->setTickLabelColor(Qt::white);
    ui->gplot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->gplot->yAxis->setRange(0, 10);
    ui->gplot->yAxis->setPadding(5); // a bit more space to the left border
    ui->gplot->yAxis->setLabel("CULTURE");
    ui->gplot->yAxis->setBasePen(QPen(Qt::white));
    ui->gplot->yAxis->setTickPen(QPen(Qt::white));
    ui->gplot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->gplot->yAxis->grid()->setSubGridVisible(true);
    ui->gplot->yAxis->setTickLabelColor(Qt::white);
    ui->gplot->yAxis->setLabelColor(Qt::white);
    ui->gplot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->gplot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> fossilData;

    fossilData  << dag << dir ;
    fossil->setData(ticks, fossilData);

    ui->gplot->legend->setVisible(true);
    ui->gplot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->gplot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->gplot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->gplot->legend->setFont(legendFont);
    ui->gplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}

void MainWindow::on_imp_clicked()
{
    QString titre =ui->line->text();
    QSqlQuery q;

            q.exec("SELECT ID_RECOLTE,CULTURE,MASSE,PRIX FROM RECOLTE WHERE CULTURE='"+titre+"'");

            while (q.next())
                      {

                        QString ID_RECOLTE = q.value(0).toString() ;
                        QString  CULTURE= q.value(1).toString();
                        QString MASSE = q.value(2).toString();
                        QString PRIX= q.value(3).toString();
                       }

                //imprimer
                QPrinter printer;
                printer.setPrinterName("desiered printer name");
              QPrintDialog dialog(&printer,this);
                if(dialog.exec()== QDialog::Rejected)
                    return;
}

void MainWindow::on_imp_2_clicked()
{
    QString titre =ui->IDD->text();
    QSqlQuery q;

            q.exec("SELECT ID_ZONE,DIMENSION,ETAT,DESCRIPTION FROM ZONE WHERE ETAT='"+titre+"'");

            while (q.next())
                      {

                        QString ID = q.value(0).toString() ;
                        QString  DIMENSION= q.value(1).toString();
                        QString ETAT = q.value(2).toString();
                        QString DESCRIPTION= q.value(3).toString();
                       }

                //imprimer
                QPrinter printer;
                printer.setPrinterName("desiered printer name");
              QPrintDialog dialog(&printer,this);
                if(dialog.exec()== QDialog::Rejected)
                    return;
}

void MainWindow::on_modifierR_clicked()
{
        int ID_RECOLTE;
        QString CULTURE;
        float PRIX;
        float MASSE;


        int cod = ui->line->text().toInt();

        ID_RECOLTE = ui->line->text().toInt();
        CULTURE = ui->lineEditCR->text();
        MASSE =float(ui->doubleSpinBox_3->value());
        PRIX = float(ui->doubleSpinBox_2->value());


    QMessageBox::information(this, tr("Modifier recolte"), tr("OK!"));

        Recolte r(ID_RECOLTE, CULTURE , MASSE, PRIX);

        if(r.modifier_recolte(cod))
        {
             QMessageBox::information(this, tr("Modifier recolte"), tr("La recolte a été modifié avec success."));
        }
        ui->tableViewrecolte->setModel(R.afficher_recolte());//refresh

}

void MainWindow::on_modifierZ_2_clicked()
{
    int ID_ZONE = ui->IDD->text().toInt();
    int DIMENSION= ui->doubleSpinBox->value();
    QString ETAT = ui->lineEdit_6->text();
    QString DESCRIPTION= ui->desc->text();

   // QMessageBox::information(this, tr("Modifier recolte"), tr("OK!"));

        Zone z(ID_ZONE, DIMENSION,ETAT, DESCRIPTION);

        if(z.modifier_zone(ID_ZONE))
        {


            QMessageBox::information(this, tr("Modifier recolte"), tr("La recolte a été modifié avec success."));
        }
        ui->tableViewzone->setModel(Z.afficher_zone());//refresh
}




void MainWindow::on_pdfR_clicked()
{
    QString strStream;
             QTextStream out(&strStream);

             const int rowCount = ui->tableViewrecolte->model()->rowCount();
             const int columnCount = ui->tableViewrecolte->model()->columnCount();

             out <<  "<html>\n"
                 "<head>\n"
                 "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                 <<  QString("<title>%1</title>\n").arg("strTitle")
                 <<  "</head>\n"
                 "<body bgcolor=#ffffff link=#5000A0>\n"

                     //"<align='right'> " << datefich << "</align>"
                 "<center> <H1>Liste des recoltes</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

             // headers
             out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
             for (int column = 0; column < columnCount; column++)
                 if (!ui->tableViewrecolte->isColumnHidden(column))
                     out << QString("<th>%1</th>").arg(ui->tableViewrecolte->model()->headerData(column, Qt::Horizontal).toString());
             out << "</tr></thead>\n";

             // data table
             for (int row = 0; row < rowCount; row++) {
                 out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                 for (int column = 0; column < columnCount; column++) {
                     if (!ui->tableViewrecolte->isColumnHidden(column)) {
                         QString data = ui->tableViewrecolte->model()->data(ui->tableViewrecolte->model()->index(row, column)).toString().simplified();
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


void MainWindow::on_pdfZ_clicked()
{
    QString strStream;
             QTextStream out(&strStream);

             const int rowCount = ui->tableViewzone->model()->rowCount();
             const int columnCount = ui->tableViewzone->model()->columnCount();

             out <<  "<html>\n"
                 "<head>\n"
                 "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                 <<  QString("<title>%1</title>\n").arg("strTitle")
                 <<  "</head>\n"
                 "<body bgcolor=#ffffff link=#5000A0>\n"

                     //"<align='right'> " << datefich << "</align>"
                 "<center> <H1>Liste des parcelles</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

             // headers
             out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
             for (int column = 0; column < columnCount; column++)
                 if (!ui->tableViewzone->isColumnHidden(column))
                     out << QString("<th>%1</th>").arg(ui->tableViewzone->model()->headerData(column, Qt::Horizontal).toString());
             out << "</tr></thead>\n";

             // data table
             for (int row = 0; row < rowCount; row++) {
                 out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                 for (int column = 0; column < columnCount; column++) {
                     if (!ui->tableViewzone->isColumnHidden(column)) {
                         QString data = ui->tableViewzone->model()->data(ui->tableViewzone->model()->index(row, column)).toString().simplified();
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






void MainWindow::on_radioButton_clicked()
{
    Zone   *sa = nullptr ;
    ui->tableViewzone->setModel(sa->tri_zone());//refresh

}



void MainWindow::on_ASCR_clicked()
{
    Recolte  *sa = nullptr ;
    ui->tableViewrecolte->setModel(sa->tri_recolte());//refresh
}

void MainWindow::on_DESC_clicked()
{
    Zone   *sa = nullptr  ;
   ui->tableViewzone->setModel(sa-> tri_zoneDESC());//refresh
}

void MainWindow::on_DESCR_clicked()
{
    Recolte  *sa = nullptr ;
    ui->tableViewrecolte->setModel(sa->tri_recolteDESC());//refresh
}

void MainWindow::on_lineEditCR_textChanged(const QString &arg1)
{
    QRegExp nom("[a-z-A-Z]{20}");
        QValidator *validatorNom = new QRegExpValidator(nom, this);
        ui->lineEditCR->setValidator(validatorNom);
}

void MainWindow::on_IDD_textChanged(const QString &arg1)
{
     ui->IDD->setValidator( new QDoubleValidator(0, 50, 0, this));
}

void MainWindow::on_line_textEdited(const QString &arg1)
{

       ui->line->setValidator( new QDoubleValidator(0, 50, 0, this));
}



