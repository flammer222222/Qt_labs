#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QTextStream>
#include <QValidator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      ValidateName(QRegExp("^\\s|[a-zA-Zа-яА-Я0-9]{3,20}$"),
                   parent), //^[a-z]{2,15}$
      ValidateDigitsf1to10(QRegExp("[1]{1}$|^[1-9]{1}$|^10"), parent),
      ValidateSpace(QRegExp("^\\S|\\w{0,}$"), parent)
    //^\\S{20}$                  //^\\s|[a-zA-Zа-я0-9_-]{3,20}$
{
    ui->setupUi(this);

//     ValidateName(QRegExp("^\\s|[a-z0-9_-]{3,20}$"));
//     ValidateDigitsf1to10(QRegExp("[1]{1}$|^[1-9]{1}$|^10"));

//     ValidateName(QRegExp("^\\s|[а-я0-9_-]{3,20}$"), parent);

    ui->radioButton->setVisible(false);
    ui->labelType->setVisible(false);
    ui->labelType2->setVisible(false);

    ui->lineEditForce->setText("0");
    ui->lineEditForce->setText("");
    ui->lineEditDexterity->setText("0");
    ui->lineEditDexterity->setText("");
    ui->lineEditIntelligence->setText("0");
    ui->lineEditIntelligence->setText("");
    ui->lineEditLuck->setText("0");
    ui->lineEditLuck->setText("");

    ui->lineEditForce->setValidator(&ValidateDigitsf1to10);
    ui->lineEditDexterity->setValidator(&ValidateDigitsf1to10);
    ui->lineEditIntelligence->setValidator(&ValidateDigitsf1to10);
    ui->lineEditLuck->setValidator(&ValidateDigitsf1to10);
    ui->lineEditName->setAutoFillBackground(true);
     ui->lineEditForce->clear();
     ui->lineEditName->setValidator (&ValidateName);

    ui->lineEditName->setPlaceholderText ("Имя от 2 до 20 символов");



    paletteRedText.setColor(QPalette::Text, Qt::red);
    paletteGreenText.setColor(QPalette::Text, Qt::green);
    paletteNeutralText.setColor(QPalette::Text, Qt::black);

    paletteGreenWindowText.setColor(QPalette::WindowText, Qt::green);
    paletteRedWindowText.setColor(QPalette::WindowText, Qt::red);
    paletteNeutralWindowText.setColor(QPalette::WindowText, Qt::black);


    points = 20;
    Force = 0;
    Dexterity = 0;
    Intelligence = 0;
    Luck = 0;

    ui->lineEditPerfomancePoints->setText(QString::number(points));

}

void MainWindow::Clear()
{
    ui->lineEditHP->clear();
    ui->lineEditMana->clear();
    ui->lineEditAttack->clear();
    ui->lineEditDefense->clear();
    ui->labelHP->setStyleSheet("background-color: rgb(240,240,240)");
    ui->labelMana->setStyleSheet("background-color: rgb(240,240,240)");
    ui->labelAttack->setStyleSheet("background-color: rgb(240,240,240)");
    ui->labelDefense->setStyleSheet("background-color: rgb(240,240,240)");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButtonInput_clicked()
{
    ui->labelType->setVisible(false);
    ui->labelType2->setVisible(false);
    bool ok;
    int force, dexterity, intelligence,
            luck;
    if (ui->lineEditName->text() == "" /* || ui->lineEditName->text() == " "*/) {
        QMessageBox::information(this, "Внимание", "Ведите имя");
        Clear();
        return;
    }

    int pos1 = 0, pos2 = 0;
    QString tmp;
    tmp = ui->lineEditName->text();
    QValidator::State stat = ValidateName.validate(tmp, pos1);
    QValidator::State statspace = ValidateSpace.validate(tmp, pos2);

    if (statspace == QValidator::Invalid)
    {
        QMessageBox::information(this, "Внимание", "Имя не должно содержать пробелов");
        Clear();
        return;
    }

    if (stat == QValidator::Invalid || stat == QValidator::Intermediate)
    {
        QMessageBox::information(this, "Внимание","Длина имени должна быть от 3 до 20");
        Clear();
        return;
    }

    if (!(ui->radioButtonMale->isChecked() || ui->radioButtonFeMale->isChecked()))
    {
        QMessageBox::information(this, "Внимание", "Вы не выбрали пол");
        Clear();
        return;
    }

    force = ui->lineEditForce->text().toInt(&ok);

    if (!ok || force < 1 || force > 10)
    {
        QMessageBox::information(this, "Внимание","Сила должна быть числом от 1 до 10");
        Clear();
        return;
    }
    ui->lineEditPerfomancePoints->setText(QString::number(points));
    dexterity = ui->lineEditDexterity->text().toInt(&ok);

    if (!ok || dexterity < 1 || dexterity > 10)
    {
        QMessageBox::information(this, "Внимание","Ловкость должны быть числом от 1 до 10");
        Clear();
        return;
    }
    ui->lineEditPerfomancePoints->setText(QString::number(points));
    intelligence = ui->lineEditIntelligence->text().toInt(&ok);
    if (!ok || intelligence < 1 || intelligence > 10)
    {
        QMessageBox::information(this, "Внимание","Интеллект должен быть числом от 1 до 10");
        Clear();
        return;
    }
    ui->lineEditPerfomancePoints->setText(QString::number(points));
    luck = ui->lineEditLuck->text().toInt(&ok);

    if (!ok || luck < 1 || luck > 10)
    {
        QMessageBox::information(this, "Внимание","Удача должна быть числом от 1 до 10");
        Clear();
        return;
    }
    ui->lineEditPerfomancePoints->setText(QString::number(points));

    if (points < 0)
    {
        QMessageBox::information(this, "Внимание","Использовано больше 20 очков характеристик");
        Clear();
        return;
    }

    if (points > 0)
    {
        QMessageBox::information(this, "Внимание","Остались нераспределенные очки характеристик");
        Clear();
        return;
    }

    float hp = 1.0f * force + 0.1f * dexterity;
    float mp = 1.0f * intelligence + 0.15f * luck ;
    float at = 0.5f * force + 0.2f * luck + 0.3f * dexterity;
    float df = 0.7f * force + 0.25f * luck + 0.05f * dexterity;

    ui->lineEditHP->setText(QString::number(hp));
    ui->lineEditMana->setText(QString::number(mp));
    ui->lineEditAttack->setText(QString::number(at));
    ui->lineEditDefense->setText(QString::number(df));


    if (hp > 7)
    {
        ui->labelHP->setStyleSheet("background-color: rgb(0,255,0)");
    } else if (hp < 4)
    {
        ui->labelHP->setStyleSheet("background-color: rgb(255,0,0)");
        ui->labelHP->setStyleSheet("background-color: rgb(150, 150, 150)");
    }

    if (mp > 7)
    {
        ui->labelMana->setStyleSheet("background-color: rgb(0,255,0)");
    } else if (mp < 4)
    {
        ui->labelMana->setStyleSheet("background-color: rgb(255,0,0)");
    } else
    {
        ui->labelMana->setStyleSheet("background-color: rgb(150, 150, 150)");
    }

    if (at > 7)
    {
        ui->labelAttack->setStyleSheet("background-color: rgb(0,255,0)");
    } else if (at < 4)
    {
        ui->labelAttack->setStyleSheet("background-color: rgb(255,0,0)");
    } else
    {
        ui->labelAttack->setStyleSheet("background-color: rgb(150, 150, 150)");
    }

    if (df > 7)
    {
        ui->labelDefense->setStyleSheet("background-color: rgb(0,255,0)");
    } else if (df < 4)
    {
        ui->labelDefense->setStyleSheet("background-color: rgb(255,0,0)");
    } else
    {
        ui->labelDefense->setStyleSheet("background-color: rgb(150, 150, 150)");
    }

    enum Gender { Male, Female };

    Gender gn;

    if (ui->radioButtonMale->isChecked())
    {
        gn = Male;
    }
    if (ui->radioButtonFeMale->isChecked())
    {
        gn = Female;
    }

    if (gn == Male)
    {

        if (force >= 7 && dexterity >= 7 && intelligence >= 1 && luck >= 1)
        {
            ui->labelType2->setText("воин-варвар");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if(force==intelligence&&force>4&&intelligence>4)
        {
            ui->labelType2->setText("паладин-чаровник");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
        }
        if (force == 8 && dexterity == 2 && intelligence == 8 && luck == 2) {
            ui->labelType2->setText("воин-маг");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if (force == 9 && dexterity == 1 && intelligence == 9 && luck == 1) {
            ui->labelType2->setText("воин-маг");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }

        if (force >= 3 && dexterity >= 1 && intelligence >= 7 && luck >= 1) {
            ui->labelType2->setText("Жрец");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }

        if (force >= 7 && dexterity >= 5 && intelligence >= 5 && luck >= 1) {
            ui->labelType2->setText("арбалетчик");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if (force > 5 && dexterity > 5 && intelligence > 4 && luck > 1) {
            ui->labelType2->setText("убийца");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if (force <= 4 && dexterity <= 4 && intelligence >= 5 && luck >= 5) {
            ui->labelType2->setText("магик");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if ((force <= 5) && (dexterity >= 7) && (intelligence <= 3) && (luck >= 1)) {
            ui->labelType2->setText("вор");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if (force >= 4 && dexterity >= 4 && intelligence >= 4 && luck >= 4) {
            ui->labelType2->setText("середнячок");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if(force==1&&dexterity==9&&intelligence==9&&luck==1)
        {
            ui->labelType2->setText("шаман");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if (dexterity > 4 && intelligence >= 5) {
            ui->labelType2->setText("плут");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        else {
            ui->labelType2->setText("разбойник");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
    }

    if (gn == Female)
    {
        if (force >= 7 && dexterity >= 7 && intelligence >= 1 && luck >= 1)
        {
            ui->labelType2->setText("воительница");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if(force==intelligence&&force>4&&intelligence>4)
        {
            ui->labelType2->setText("воительница маг");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
        }
        if (force == 8 && dexterity == 2 && intelligence == 8 && luck == 2)
        {
            ui->labelType2->setText("воительница маг");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if (force == 9 && dexterity == 1 && intelligence == 9 && luck == 1)
        {
            ui->labelType2->setText("воительница маг");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if (force >= 3 && dexterity >= 1 && intelligence >= 7 && luck >= 1)
        {
            ui->labelType2->setText("жрец");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }

        if (force >= 7 && dexterity >= 5 && intelligence >= 5 && luck >= 1)
        {
            ui->labelType2->setText("лучница");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if (force > 5 && dexterity > 5 && intelligence > 4 && luck >= 1) {
            ui->labelType2->setText("убийца");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if (force <= 3 && dexterity <= 3 && intelligence >= 3 && luck <= 3)
        {
            ui->labelType2->setText("разбойница");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if (force <= 5 && dexterity >= 7 && intelligence <= 3 && luck >= 1)
        {
            ui->labelType2->setText("воровка");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if (force >= 4 && dexterity >= 4 && intelligence >= 4 && luck >= 4)
        {
            ui->labelType2->setText("середнячок");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if (force <= 4 && dexterity <= 4 && intelligence >= 5 && luck >= 5)
        {
            ui->labelType2->setText("мистик");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if(force==1&&dexterity==9&&intelligence==9&&luck==1)
        {
            ui->labelType2->setText("Шаманка");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        if (Force >= 5 && at > 4 && dexterity > 4) {
            ui->labelType2->setText("паладинша");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
        else {
            ui->labelType2->setText("разбойница");
            ui->labelType->setVisible(true);
            ui->labelType2->setVisible(true);
            return;
        }
    }
}

void MainWindow::on_pushButtonCancelelation_clicked()
{

    ui->lineEditForce->clear();
    ui->lineEditDexterity->clear();
    ui->lineEditIntelligence->clear();
    ui->lineEditLuck->clear();
    ui->lineEditName->clear();
    ui->radioButtonMale->setDown(false);
    ui->radioButtonFeMale->setChecked(false);
    ui->radioButton->setChecked(true);
    ui->lineEditHP->clear();
    ui->lineEditMana->clear();
    ui->lineEditAttack->clear();
    ui->lineEditDefense->clear();
    ui->lineEditPerfomancePoints->setText("20");
    ui->labelType->setVisible(false);
    ui->labelType2->setVisible(false);

    ui->labelForce->setStyleSheet("background-color: rgb(240,240,240)");
    ui->labelIntelligence->setStyleSheet("background-color: rgb(240,240,240)");
    ui->labelLuck->setStyleSheet("background-color: rgb(240,240,240)");
    ui->labelDexterity->setStyleSheet("background-color: rgb(240,240,240)");
    ui->labelHP->setStyleSheet("background-color: rgb(240,240,240)");
    ui->labelMana->setStyleSheet("background-color: rgb(240,240,240)");
    ui->labelAttack->setStyleSheet("background-color: rgb(240,240,240)");
    ui->labelDefense->setStyleSheet("background-color: rgb(240,240,240)");
    ui->radioButtonFeMale->setPalette(paletteNeutralWindowText);
    ui->radioButtonMale->setPalette(paletteNeutralWindowText);
    ui->lineEditName->setPalette(paletteNeutralText);
}

void MainWindow::on_lineEditName_textChanged(const QString &arg1)
{
    int pos = 0;
    QString tmp;
    tmp = ui->lineEditName->text();

    QValidator::State stat = ValidateName.validate(tmp, pos);
    QValidator::State stat2 = ValidateName.validate(tmp, pos);

    if (stat == QValidator::Invalid || stat == QValidator::Intermediate ||
            stat2 == QValidator::Invalid || stat2 == QValidator::Intermediate)
    {
        ui->lineEditName->setPalette(paletteRedText);
    } else if (stat == QValidator::Acceptable) {
        ui->lineEditName->setPalette(paletteGreenText);
    }
}

void MainWindow::on_lineEditForce_textChanged(const QString &arg1)
{

    bool ok;
    Force = ui->lineEditForce->text().toInt(&ok);

    points = 20 - (Force + Dexterity + Intelligence + Luck);
    ui->lineEditPerfomancePoints->setText(QString::number(points));

    if (ui->lineEditForce->text() == "") {
        ui->labelForce->setStyleSheet("background-color: rgb(240, 240, 240)");
        ui->lineEditForce->setStyleSheet("background-color: rgb(255,255,255)");
        return;
    }

    if (Force > 0 && Force < 11)
    {
        ui->lineEditForce->setPalette(paletteGreenText);
        if (Force > 7)
        {
            ui->labelForce->setStyleSheet("background-color: rgb(0,255,0)");
        } else if (Force < 4)
        {
            ui->labelForce->setStyleSheet("background-color: rgb(255,0,0)");
        } else
        {
            ui->labelForce->setStyleSheet("background-color: rgb(150, 150, 150)");
        }
    }
    else
    {
        ui->lineEditForce->setPalette(paletteRedText);
    }
}

void MainWindow::on_radioButtonMale_clicked()
{
    ui->radioButtonMale->setPalette(paletteGreenWindowText);
    ui->radioButtonFeMale->setPalette(paletteNeutralWindowText);
}

void MainWindow::on_radioButtonFeMale_clicked()
{
    ui->radioButtonMale->setPalette(paletteNeutralWindowText);
    ui->radioButtonFeMale->setPalette(paletteGreenWindowText);
}

void MainWindow::on_lineEditDexterity_textChanged(const QString &arg1)
{

    bool ok;
    Dexterity = ui->lineEditDexterity->text().toInt(&ok);

    points = 20 - (Force + Dexterity + Intelligence + Luck);
    ui->lineEditPerfomancePoints->setText(QString::number(points));

    if (ui->lineEditDexterity->text() == "") {
        ui->labelDexterity->setStyleSheet("background-color: rgb(240, 240, 240)");
        ui->lineEditDexterity->setStyleSheet("background-color: rgb(255,255,255)");
        return;
    }

    if (Dexterity > 0 && Dexterity < 11)
    {
        ui->lineEditDexterity->setPalette(paletteGreenText);
        if (Dexterity > 7)
        {
            ui->labelDexterity->setStyleSheet("background-color: rgb(0,255,0)");
        } else if (Dexterity < 4)
        {
            ui->labelDexterity->setStyleSheet("background-color: rgb(255,0,0)");
        }
        else
        {
            ui->labelDexterity->setStyleSheet("background-color: rgb(150, 150, 150)");
        }
    }
    else
    {
        ui->lineEditDexterity->setPalette(paletteRedText);
    }
}

void MainWindow::on_lineEditIntelligence_textChanged(const QString &arg1)
{
    bool ok;
    Intelligence = ui->lineEditIntelligence->text().toInt(&ok);
    points = 20 - (Force + Dexterity + Intelligence + Luck);
    ui->lineEditPerfomancePoints->setText(QString::number(points));

    if (ui->lineEditIntelligence->text() == "") {
        ui->labelIntelligence->setStyleSheet("background-color: rgb(240, 240, 240)");
        ui->lineEditIntelligence->setStyleSheet("background-color: rgb(255,255,255)");
        return;
    }

    if (Intelligence > 0 && Intelligence < 11)
    {
        ui->lineEditIntelligence->setPalette(paletteGreenText);
        if (Intelligence > 7)
        {
            ui->labelIntelligence->setStyleSheet("background-color: rgb(0,255,0)");
        } else if (Intelligence < 4)
        {
            ui->labelIntelligence->setStyleSheet("background-color: rgb(255,0,0)");
        } else
        {
            ui->labelIntelligence->setStyleSheet("background-color: rgb(150, 150, 150)");
        }
    }
    else
    {
        ui->lineEditIntelligence->setPalette(paletteRedText);
    }
}

void MainWindow::on_lineEditLuck_textChanged(const QString &arg1)
{
    bool ok;
    Luck = ui->lineEditLuck->text().toInt(&ok);

    points = 20 - (Force + Dexterity + Intelligence + Luck);
    ui->lineEditPerfomancePoints->setText(QString::number(points));

    if (ui->lineEditLuck->text() == "")
    {
        ui->labelLuck->setStyleSheet("background-color: rgb(240, 240, 240)");
        ui->lineEditLuck->setStyleSheet("background-color: rgb(255,255,255)");
        return;
    }

    if (Luck > 0 && Luck < 11)
    {
        ui->lineEditLuck->setPalette(paletteGreenText);
        if (Luck > 7)
        {
            ui->labelLuck->setStyleSheet("background-color: rgb(0,255,0)");
        } else if (Luck < 4)
        {
            ui->labelLuck->setStyleSheet("background-color: rgb(255,0,0)");
        } else
        {
            ui->labelLuck->setStyleSheet("background-color: rgb(150, 150, 150)");
        }
    }
    else
    {
        ui->lineEditLuck->setPalette(paletteRedText);
    }
}
