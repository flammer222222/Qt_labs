#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->on_comboBox_2_activated(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::getIndexForcomboBox()
{
    return static_cast<QVariant>(ui->comboBox->currentText()).toBool();
}

int MainWindow::getIndexForComboBox2()
{
    return ui->comboBox_2->currentIndex();
}

bool MainWindow::getIndexForComboBox3()
{
    return static_cast<QVariant>(ui->comboBox_3->currentText()).toBool();
}

bool MainWindow::compare(int op1, int op2, int CompareIndex)
{
    switch (CompareIndex)
    {
    case 0:
        return op1 && op2;
    case 1:
        return op1 || op2;
    case 2:
        return !op1;
    case 3:
        return op1 ^ op2;
    case 4:
        return op1 == op2;
    case 5:
        return op1 != op2;
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    ui->comboBox_3->setVisible(true);
    if (getIndexForComboBox2() == 2)
    {
        ui->comboBox_3->setVisible(false);
    }

    int CurrentIndexComboBox, CurrentIndexComboBox2, CurrentIndexComboBox3;
    CurrentIndexComboBox = getIndexForcomboBox();
    CurrentIndexComboBox2 = getIndexForComboBox2();
    CurrentIndexComboBox3 = getIndexForComboBox3();

    if (compare(CurrentIndexComboBox, CurrentIndexComboBox3, CurrentIndexComboBox2))
    {
        this->setStyleSheet("background-color: rgb(0,255,0);");
    }
    else
    {
        this->setStyleSheet("background-color: rgb(255,0,0);");
    }
}

void MainWindow::on_comboBox_2_activated(int index)
{
    ui->comboBox_3->setVisible(true);
    if (index == 2)
    {
        ui->comboBox_3->setVisible(false);
    }

    int CurrentIndexComboBox, CurrentIndexComboBox3;
    CurrentIndexComboBox = getIndexForcomboBox();
    CurrentIndexComboBox3 = getIndexForComboBox3();

    if (compare(CurrentIndexComboBox, CurrentIndexComboBox3, index))
    {
        this->setStyleSheet("background-color: rgb(0,255,0);");
    }
    else
    {
        this->setStyleSheet("background-color: rgb(255,0,0);");
    }
}

void MainWindow::on_comboBox_3_activated(int index)
{
    int CurrentIndexComboBox, CurrentIndexComboBox2, CurrentIndexComboBox3;
    CurrentIndexComboBox = getIndexForcomboBox();
    CurrentIndexComboBox2 = getIndexForComboBox2();
    CurrentIndexComboBox3 = getIndexForComboBox3();

    if (compare(CurrentIndexComboBox, CurrentIndexComboBox3, CurrentIndexComboBox2))
    {
        this->setStyleSheet("background-color: rgb(0,255,0);");
    }
    else
    {
        this->setStyleSheet("background-color: rgb(255,0,0);");
    }
}
