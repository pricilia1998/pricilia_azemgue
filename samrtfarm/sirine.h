#ifndef SIRINE_H
#define SIRINE_H

#include <QDialog>
#include "carte.h"
#include "animal.h"
#include"notification.h"

#include"mainwindow.h"

namespace Ui {
class Sirine;
}

class Sirine : public QDialog
{
    Q_OBJECT

public:
    explicit Sirine(QWidget *parent = nullptr);
    ~Sirine();
    void additemnom();

private slots:
    void on_ajouterAnimal_clicked();

    void on_supAnimal_clicked();

    void on_ajouterCarte_clicked();

    void on_supCarte_clicked();

    void on_modAnimal_clicked();

    void on_modCarte_clicked();

    void on_tabWidget_objectNameChanged(const QString &objectName);

    void on_ASC_clicked();
    void on_ASCC_clicked();

    void on_DESS_clicked();

    void on_DES_clicked();
     void on_rechercher_clicked();

     void on_radioButton_2_clicked();

     void on_rechAnimal_textChanged(const QString &arg1);

     void on_nomAnimal_textChanged(const QString &arg1);

     void on_statistics_clicked();

     void on_pdf_clicked();
      void on_imprimerA_clicked();

     void on_pdfA_clicked();
     void openStatistcs();

     void on_testnom_linkActivated(const QString &link);

     void on_poids_textChanged(const QString &arg1);

     void on_temperature_textChanged(const QString &arg1);

     void on_taille_textChanged(const QString &arg1);

     void on_imprimerC_clicked();



private:
    Ui::Sirine *ui;
   carte tmpcarte;
    animal tmpanimal;
    MainWindow *w;
};

#endif // Sirine_H
