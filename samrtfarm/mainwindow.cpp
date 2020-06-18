#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tahaa.h"
#include "sirine.h"
#include "sabrine.h"
#include "template.h"
#include <QLineEdit>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);

   setWindowIcon(QIcon("icon/icon.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{  if(((ui->username->text()=="taha") && (ui->password->text()=="taha")) ||
      ((ui->username->text()=="sirine") && (ui->password->text()=="sirine")) ||
     ( (ui->username->text()=="sabrine") && (ui->password->text()=="sabrine")) ||
     ( (ui->username->text()=="priscilia") && (ui->password->text()=="priscilia")) ||
    (  (ui->username->text()=="admin") && (ui->password->text()=="admin")) )

    {

    ui->stackedWidget->setCurrentIndex(1); }
    else {
        QMessageBox msgBox;
                           msgBox.setIcon(QMessageBox::Critical);
                           msgBox.setWindowTitle( "Erreur de connexion");
                           msgBox.setText(tr("Vérifier vos coordonnées !"));
                           msgBox.addButton(tr("Réssayer"), QMessageBox::NoRole);
                           QPixmap pixmap = QPixmap("icon/icon.png");
                             msgBox.setWindowIcon(QIcon(pixmap));
                           msgBox.exec();
    }
    ui->user->setText("Connecté en tant que "+ui->username->text()) ;

}

void MainWindow::on_pushButton_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_3_clicked()
{ if  ( (ui->username->text()=="taha") ||  (ui->username->text()=="admin") ) {
        tahaa t;
         t.show();
        // MainWindow::hide();
            t.setWindowTitle("Smart Farm");
         t.exec();}

     else { QMessageBox msgBox;
msgBox.setIcon(QMessageBox::Critical);
msgBox.setWindowTitle( "Erreur ");
msgBox.setText(tr("Vous n'avez pas la permission pour accéder !"));
msgBox.addButton(tr("Réssayer"), QMessageBox::NoRole);
QPixmap pixmap = QPixmap("icon/icon.png");
  msgBox.setWindowIcon(QIcon(pixmap));
msgBox.exec();

    } }

void MainWindow::on_pushButton_4_clicked()
{  if  ( (ui->username->text()=="priscilia") ||  (ui->username->text()=="admin") ) {
        Template p ;
    p.show();
    //MainWindow::hide();
       p.setWindowTitle("Smart Farm");
       p.exec(); } else { QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle( "Erreur ");
        msgBox.setText(tr("Vous n'avez pas la permission pour accéder !"));
        msgBox.addButton(tr("Réssayer"), QMessageBox::NoRole);
        QPixmap pixmap = QPixmap("icon/icon.png");
          msgBox.setWindowIcon(QIcon(pixmap));
        msgBox.exec(); }

}

void MainWindow::on_pushButton_5_clicked()
{ if  ( (ui->username->text()=="sirine") ||  (ui->username->text()=="admin") ) {
    Sirine s ;
       s.show();
       //MainWindow::hide();
          s.setWindowTitle("Smart Farm");
          s.exec(); } else { QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle( "Erreur ");
        msgBox.setText(tr("Vous n'avez pas la permission pour accéder !"));
        msgBox.addButton(tr("Réssayer"), QMessageBox::NoRole);
        QPixmap pixmap = QPixmap("icon/icon.png");
          msgBox.setWindowIcon(QIcon(pixmap));
        msgBox.exec(); }
}

void MainWindow::on_pushButton_6_clicked()
{  if  ( (ui->username->text()=="sabrine") ||  (ui->username->text()=="admin") ) {
        sabrine g ;
    g.show();
    //MainWindow::hide();
       g.setWindowTitle("Smart Farm");
       g.exec(); } else { QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle( "Erreur ");
        msgBox.setText(tr("Vous n'avez pas la permission pour accéder !"));
        msgBox.addButton(tr("Réssayer"), QMessageBox::NoRole);
        QPixmap pixmap = QPixmap("icon/icon.png");
          msgBox.setWindowIcon(QIcon(pixmap));
        msgBox.exec();

    }

}
