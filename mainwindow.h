#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dialog.h>
#include <QString>


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


    void on_modifierR_clicked();

    void on_ajouterR_clicked();

    void on_suppR_clicked();

    void on_trierR_clicked();

    bool on_rechermodifR_clicked();

    void on_ajouterZ_clicked();

    void on_suppZ_clicked();

    void on_trierZ_clicked();

    bool on_rechermodifZ_clicked();

    void on_mail_clicked();

    void on_mail_2_clicked();

    void on_stat_clicked();

    void on_imp_clicked();

    void on_imp_2_clicked();

    void on_modifierZ_2_clicked();

    void on_pdfR_clicked();

    void on_pdfZ_clicked();



    void on_radioButton_clicked();

    void on_DESC_clicked();

    void on_ASCR_clicked();

    void on_DESCR_clicked();

    void on_lineEditCR_textChanged(const QString &arg1);

    void on_line_textEdited(const QString &arg1);

    void on_lineEditCR_textEdited(const QString &arg1);

    void on_IDD_textChanged(const QString &arg1);

    void on_line_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
    Dialog *D;
    Recolte R ;
    Zone Z;
};

#endif // MAINWINDOW_H
