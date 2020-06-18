#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include "recolte.h"
#include "zone.h"

namespace Ui {

    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();



private slots:


    void on_modifierZ_clicked();

    void on_ajouterZ_clicked();

    void on_PDFZ_clicked();

    void on_suppR_clicked();

    void on_suppZ_clicked();

    void on_modifierR_clicked();

    void on_ajouterR_clicked();

    void on_pdfR_clicked();



    void on_trierZ_clicked();

    void on_trierR_clicked();



    



    bool on_rechermodifR_clicked();
    bool on_rechermodifZ_clicked();

    void on_mail_clicked();

    void on_mailing_clicked();

    void on_afiichstat_clicked();

private:
    Ui::Dialog *ui;
   Recolte R ;
   Zone Z;



};

#endif // DIALOG_H
