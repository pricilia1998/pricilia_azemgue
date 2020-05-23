#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QDialog>
#include "fournisseur.h"
#include "nourriture.h"
#include <QVector>

namespace Ui {
class Template;
}

class Template : public QDialog
{
    Q_OBJECT

public:
    explicit Template(QWidget *parent = nullptr);
    ~Template();

private slots:
    void on_ajouterNour_clicked();

    void on_supNour_clicked();

    void on_ajouterFour_clicked();

    void on_supFour_clicked();

    void on_modNour_clicked();

    void on_modFour_clicked();

    void on_miseajourNour_clicked();

    void on_miseajourFour_clicked();

    void on_triFournisseur_clicked();

    void on_triNourriture_clicked();

    void on_rechNour_textChanged(const QString &arg1);


    void on_rechFour_textChanged(const QString &arg1);

    void on_montantNour_textEdited(const QString &arg1);

    void on_numFour_textEdited(const QString &arg1);

    void on_nomFour_textEdited(const QString &arg1);

    void on_nomNour_textEdited(const QString &arg1);

   // void on_pushButton_clicked();

    void on_imprimerNour_clicked();

    void on_imprimerFour_clicked();

private:
    Ui::Template *ui;
    fournisseur tmpfournisseur;
    nourriture tmpnourriture;
    fournisseur f;
    nourriture n;
};

#endif // TEMPLATE_H
