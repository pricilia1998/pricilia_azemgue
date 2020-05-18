#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include "tache.h"
#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pb_ajouter_clicked();
    void on_pb_rechercher_clicked();
    void on_afficher_clicked();
    void on_pb_suppr_clicked() ;
    void on_imprimer1_clicked();
    void on_impr2_clicked()  ;
    void on_pdf_clicked();
    void on_pdf22_clicked()  ;
    void on_pb_ajouter2_clicked();
    void on_affichertache_clicked();
    void on_recherche22_clicked() ;
    void on_supprim2tache_clicked() ;
    void on_ModifierEmp_clicked();
    void on_modifier1_clicked();
    void on_modif222_clicked();
     void on_stats_clicked();
        void indexChanged(int );
void on_modifier22_clicked() ;
void on_resetpb_clicked();
void on_resetpb2_clicked() ;

void StatsTaches() ;


void StatsEmply() ;




void on_lineEdit_id_editingFinished();

void on_lineEdit_nom_textEdited(const QString &arg1);

void on_lineEdit_prenom_textEdited(const QString &arg1);







void on_lineEdit_email_editingFinished();



void on_emplystats_clicked();

private:
    Ui::MainWindow *ui;
    employe tmpemploye;
     tache tableView2;
};

#endif // MAINWINDOW_H
