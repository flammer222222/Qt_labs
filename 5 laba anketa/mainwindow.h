#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegExpValidator>
#include <QPalette>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButtonInput_clicked();
    void on_pushButtonCancelelation_clicked();
    void on_lineEditName_textChanged(const QString &arg1);
    void on_lineEditForce_textChanged(const QString &arg1);
    void on_radioButtonMale_clicked();
    void on_radioButtonFeMale_clicked();
    void on_lineEditDexterity_textChanged(const QString &arg1);
    void on_lineEditIntelligence_textChanged(const QString &arg1);
    void on_lineEditLuck_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QRegExpValidator ValidateName;
    QRegExpValidator ValidateDigitsf1to10;
    QRegExpValidator ValidateSpace;
    QPalette paletteGreenText,paletteRedText,paletteNeutralText;
    QPalette paletteGreenWindowText,paletteRedWindowText,paletteNeutralWindowText;
    int points;
    int Force,Dexterity,Intelligence,Luck;
    void Clear();

};

#endif // MAINWINDOW_H
