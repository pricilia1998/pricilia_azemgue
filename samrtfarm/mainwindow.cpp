#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tahaa.h"
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
{  if((ui->username->text()=="taha") && (ui->password->text()=="taha")) {

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

}

void MainWindow::on_pushButton_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_3_clicked()
{
   tahaa t;
    t.show();
   // MainWindow::hide();
       t.setWindowTitle("Smart Farm");
    t.exec();
}

void MainWindow::on_pushButton_4_clicked()
{  Template p ;
    p.show();
    //MainWindow::hide();
       p.setWindowTitle("Smart Farm");
    p.exec();

}
