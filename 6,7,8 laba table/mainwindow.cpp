#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <time.h>
#include <algorithm>
#include <QDebug>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(1);
    ArraySorted = false;

    ui->labelElementCount->setVisible (false);
    ui->labelElementNumber->setVisible (false);
    ui->labelMaxMinAvg->setVisible (false);
    ui->labelResMaxMinAvg->setVisible (false);
    ui->labelError->setVisible(false);
    ui->labelDub->setVisible (false);
    ui->label11->setVisible(false);
    ui->label22->setVisible(false);
    ui->label33->setVisible(false);
    ui->labelFoundedNumber->setVisible(false);
    ui->labelSovpadeni9->setVisible(false);
    ui->labelNumberInTable->setVisible(false);
    ui->labelCorrectly->setVisible(false);

    ui->labelError->setStyleSheet("color: rgb(255,0,0)");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HadeLabels()
{
    ui->labelElementCount->setVisible (false);
    ui->labelElementNumber->setVisible (false);
    ui->labelError->setVisible (false);
    ui->labelMaxMinAvg->setVisible (false);
    ui->labelResMaxMinAvg->setVisible (false);
    ui->labelDub->setVisible (false);
    ui->label11->setVisible(false);
    ui->label22->setVisible(false);
    ui->label33->setVisible(false);
    ui->labelFoundedNumber->setVisible(false);
    ui->labelSovpadeni9->setVisible(false);
    ui->labelNumberInTable->setVisible(false);
    ui->labelCorrectly->setVisible(false);
}

void MainWindow::ValueError(int Col, int size)
{
    ui->tableWidget->clearSelection ();
    ui->labelError->setText("put numbers in a table");
    ui->labelError->setVisible(true);

    for (int i = Col; i < size; ++i)
    {
        if (ui->tableWidget->item(0, i) != NULL)
        {
            bool flag;
            ui->tableWidget->item(0, i)->text().toInt(&flag);

            if (!flag)
            {
                ui->tableWidget->item(0,i)->setBackgroundColor(Qt::red);
            }
        }
        else if (ui->tableWidget->item(0,i) == NULL)
        {
            QTableWidgetItem* newItem;
            newItem = new QTableWidgetItem;
            ui->tableWidget->setItem(0,i,newItem);
            ui->tableWidget->item(0,i)->setBackgroundColor(Qt::red);
        }
    }
    ui->tableWidget->scrollToItem(ui->tableWidget->item(0, Col));
}

void MainWindow::on_pushButtonInput_clicked()
{
    HadeLabels();

    bool ok;
    QString tmp;
    tmp=ui->lineEditInput->text();
    int col = tmp.toInt(&ok);

    if(!ok)
    {
        ui->labelError->setText ("you entered not a number");
        ui->labelError->setVisible (true);
        return;
    }
    if (col>=1 && col <=200/*100000*/)
    {
        ui->tableWidget->setColumnCount(col);
        ArraySorted = false;
        int ColSize = ui->tableWidget->columnCount();
        for (int i = 0; i < ColSize; ++i)
        {
            if (ui->tableWidget->item(0,i) == NULL)
            {
                QTableWidgetItem * newItem;
                newItem = new QTableWidgetItem;
                ui->tableWidget->setItem(0,i,newItem);
            }
        }
    }
    else
    {
        ui->labelError->setText ("the number of \n columns must be \n between 1 and 200");
        ui->labelError->setVisible (true);
    }
}

void MainWindow::NullExistError(int Col, int size)
{

    ui->labelError->setText("put numbers in a table");
    ui->labelError->setVisible(true);

    for (int i = Col; i < size; ++i)
    {
        if (ui->tableWidget->item(0, i) == NULL)
        {
            QTableWidgetItem * newItem;
            newItem = new QTableWidgetItem;
            ui->tableWidget->setItem(0,i,newItem);
            ui->tableWidget->item(0,i)->setBackgroundColor(Qt::red);
        }
    }
    ui->tableWidget->scrollToItem(ui->tableWidget->item(0, Col));
}


bool MainWindow::GetColumnToArray(int* arr, int size)
{
    int ColSize = size;
    bool flag = false;

    for (int i=0; i < ColSize; i++)
    {
        if (ui->tableWidget->item(0,i) != NULL)
        {
            int num = ui->tableWidget->item(0,i)->text().toInt(&flag);
            if (flag)
            {
                arr[i] = num;
            }
            else
            {
                ValueError(i,ColSize);
                break;
            }
        }
        else if ((ui->tableWidget->item(0,i)== NULL) && i < ColSize)
        {
            NullExistError(i,ColSize);
            flag = false;
            break;
        }
    }
    return flag;
}

void MainWindow::DeleteDuplicates (int *arr, int &size)
{
    int i = 0;

    for (int j = i + 1; j < size; ++j)
    {
        if (arr[i] != arr[j])
        {
            i++;
            arr[i]=arr[j];
        }
    }

    size = ++i;
}

void MainWindow::SetColFromArray(int arr[], int size)
{
    int ColSize = ui->tableWidget->columnCount();
    QString str;

    for (int i = 0; i < size; ++i)
    {
        int num = arr[i];
        str.setNum(num);
        ui->tableWidget->item(0,i)->setText(str);
    }

    int newCol = ColSize - size;
    ui->tableWidget->setColumnCount(ColSize - newCol);
}

void MainWindow::QuickSort(int *arr, int size)
{
    int begin = 0;
    int end = size;
    int mid = arr[size/2];

    do
    {
        while (arr[begin] < mid)
        {
            begin++;
        }
        while (arr[end] > mid)
        {
            end--;
        }
        if (begin <= end)
        {
            swap(arr[begin], arr[end]);
            begin++;
            end--;
        }
    }
    while (begin <= end);

    if (end > 0)
    {
        QuickSort(arr, end);
    }
    if (size > 0)
    {
        QuickSort(arr + begin, size - begin);
    }
}

bool MainWindow::CheckBogoSorted(int *arr, int size)
{
    for(int i = 0;i<size-1;i++)
    {
        if(arr[i]>arr[i+1])
            return false;
    }
    return true;
}

bool MainWindow::BogoSort(int* arr, int size,int& k)
{
    bool sorted = false;
    int iteration = 0;
    qDebug()<<size<<"\n";
    while (!sorted && iteration < 10000000)
    {
        swap(arr[rand() % size], arr[rand() % size]);
        sorted=CheckBogoSorted(arr,size);
        if (sorted) {break;}
        ++iteration;
    }
    return sorted;
}

void MainWindow::on_pushButtonMin_clicked()
{
    HadeLabels();
    int ColSize = ui->tableWidget->columnCount();
    int min = INT_MAX;
    bool flag = false;
    int pos=0;
    if (ui->tableWidget->columnCount()<=0)
    {
        ui->labelError->setText("you haven't created a table");
        ui->labelError->setVisible(true);
    }

    for (int i = 0; i < ColSize; ++i)
    {
        if (ui->tableWidget->item(0, i) != NULL)
        {
            int num = ui->tableWidget->item(0, i)->text().toInt(&flag);

            if (flag && (num < min))
            {
                min = num;
                pos=i+1;
            }
            if (!flag)
            {
                ValueError(i, ColSize);
                break;
            }
        }
        else if ((ui->tableWidget->item(0,i) == NULL) && (i < ColSize))
        {
            NullExistError(i,ColSize);
            flag = false;
            break;
        }
    }
    if (flag)
    {
        ui->labelMaxMinAvg->setVisible (true);
        ui->labelElementCount->setVisible(true);
        ui->labelElementNumber->setText (QString::number (pos));
        ui->labelElementNumber->setVisible (true);
        ui->labelResMaxMinAvg->setText(QString::number(min));
        ui->labelResMaxMinAvg->setVisible (true);
    }
}

void MainWindow::on_pushButtonMax_clicked()
{
    HadeLabels();
    int ColSize = ui->tableWidget->columnCount();
    int max = INT_MIN;
    bool flag = false;
    int pos = 0;

    if (ui->tableWidget->columnCount()<=0)
    {
        ui->labelError->setText("you haven't created a table");
        ui->labelError->setVisible(true);
    }

    for (int i = 0; i < ColSize; ++i)
    {
        if (ui->tableWidget->item(0,i) != NULL)
        {
            int num = ui->tableWidget->item(0,i)->text().toInt(&flag);

            if (flag && (num > max))
            {
                max = num;
                pos = i+1;
            }
            if (!flag)
            {
                ValueError(i,ColSize);
                break;
            }
        }
        else if ((ui->tableWidget->item(0,i) == NULL) && (i < ColSize))
        {
            NullExistError(i,ColSize);
            flag = false;
            break;
        }
    }
    if (flag)
    {
        ui->labelMaxMinAvg->setVisible (true);
        ui->labelElementCount->setVisible(true);
        ui->labelElementNumber->setText (QString::number (pos));
        ui->labelElementNumber->setVisible (true);
        ui->labelResMaxMinAvg->setText(QString::number(max));
        ui->labelResMaxMinAvg->setVisible (true);
    }
}

void MainWindow::on_pushButtonAvg_clicked()
{
    HadeLabels();
    int ColSize = ui->tableWidget->columnCount();
    int sum = 0;
    bool flag = false;

    if (ui->tableWidget->columnCount()<=0)
    {
        ui->labelError->setText("you haven't created a table");
        ui->labelError->setVisible(true);
    }

    for (int i = 0; i < ColSize; ++i)
    {
        if (ui->tableWidget->item(0,i) != NULL)
        {
            int num = ui->tableWidget->item(0,i)->text().toInt(&flag);
            if (flag)
            {
                sum += num;
            }
            if (!flag)
            {
                ValueError(i,ColSize);
                break;
            }
        }
        else if ((ui->tableWidget->item(0,i) == NULL) && (i < ColSize))
        {
            NullExistError(i,ColSize);
            flag = 0;
            break;
        }
    }
    if (flag)
    {
		double avg = (double)sum/(double)ColSize;
        ui->labelMaxMinAvg->setVisible (true);
        ui->labelElementNumber->setVisible (false);
        ui->labelElementCount->setVisible(false);
        ui->labelResMaxMinAvg->setText(QString::number(avg,'g',2));
        ui->labelResMaxMinAvg->setVisible (true);
    }
}

void MainWindow::linearSearch(int *arr, int size, int search, int &n, QString &arrStr)
{
    int arrItems[200];
    for (int i = 0; i < size; ++i)
    {
        if (search == arr[i])
        {
            arrStr += QString::number(i+1) + " ";
            arrItems[n++] = i;
        }
    }
}
int MainWindow::binarySearch(int *arr, int size, int k)
{
    int l = 0;
    int r = size;

    while (l <= r)
    {
        int m = (l+r)/2;

        if (k < arr[m])
        {
            r = m - 1;
        }
        else if (k > arr[m])
        {
            l = m + 1;
        }
        else
        {
            return m;
        }
    }
    return -1;
}
void MainWindow::on_pushButtonRandom_clicked()
{
    HadeLabels();
    int ColSize = ui->tableWidget->columnCount();

    srand(clock());

    if (ui->tableWidget->columnCount()==0)
    {
        ui->labelError->setText ("you haven't created a table");
        ui->labelError->setVisible (true);
        return;
    }
    else
    {
        for (int i = 0; i < ColSize; ++i)
        {
            int num = rand()%201-100;
            ui->tableWidget->item(0,i)->setText(QString::number(num));
        }
        ArraySorted = false;
    }
}

void MainWindow::on_pushButtonBubbleSort_clicked()
{
    HadeLabels();

    if (ui->tableWidget->columnCount()<=0)
    {
        ui->labelError->setText("you haven't created a table");
        ui->labelError->setVisible(true);
    }

    int ColSize=ui->tableWidget->columnCount();
    int arr[200];
    bool flag = GetColumnToArray(arr, ColSize);

    if (flag)
    {
        for (int i = 0; i < ColSize; i++)
        {
            for (int j = 0; j < ColSize - 1; j++)
            {
                if (arr[i] < arr[j])
                {
                    swap(arr[i], arr[j]);
                }
            }
        }
        SetColFromArray(arr, ColSize);
        ArraySorted = true;
    }
}

void MainWindow::on_pushButtonQuickSort_clicked()
{
    HadeLabels();
    if (ui->tableWidget->columnCount()<=0)
    {
        ui->labelError->setText("you haven't created a table");
        ui->labelError->setVisible(true);
    }

    int ColSize = ui->tableWidget->columnCount();
    int arr[200];
    int flag = GetColumnToArray(arr, ColSize);
    if (flag)
    {
        QuickSort(arr, ColSize-1);
        SetColFromArray(arr, ColSize);
        ArraySorted = true;
    }
}

void MainWindow::on_pushButtonCombSort_clicked()
{
    HadeLabels();
    if (ui->tableWidget->columnCount()<=0)
    {
        ui->labelError->setText("you haven't created a table");
        ui->labelError->setVisible(true);
    }

    int Colsize = ui->tableWidget->columnCount();
    int arr[200];
    int flag = GetColumnToArray(arr, Colsize);
    int step = Colsize;
    bool transposition = true;
    if (flag)
    {
        while (step > 1 || transposition)
        {
            if (step>1)
            {
                step /= 1.247;
            }
            transposition = false;
            int i = 0;
            while ((i + step) < Colsize)
            {
                if (arr[i] > arr[i+step])
                {
                    swap(arr[i], arr[i+step]);
                    transposition = true;
                }
                i++;
            }
        }
        SetColFromArray(arr, Colsize);
        ArraySorted = true;
    }
}

void MainWindow::on_pushButtonGnomeSort_clicked()
{
    HadeLabels();
    int ColSize = ui->tableWidget->columnCount();
    int arr[200];
    int flag = GetColumnToArray(arr, ColSize);
    if (ui->tableWidget->columnCount()<=0)
    {
        ui->labelError->setText("you haven't created a table");
        ui->labelError->setVisible(true);
    }

    if (flag)
    {
        int i = 0;
        while (i < ColSize)
        {
            if (i == 0 || (arr[i-1] <= arr[i]))
                i++;
            else
            {
                swap(arr[i], arr[i-1]);
                i--;
            }
        }
        SetColFromArray(arr, ColSize);
        ArraySorted = true;
    }
}

void MainWindow::on_pushButtonBogoSort_clicked()
{
    HadeLabels();
    int ColSize = ui->tableWidget->columnCount();
    int arr[200];
    bool flag = GetColumnToArray(arr, ColSize);
    int k = 0;

    if (ui->tableWidget->columnCount()<=0)
    {
        ui->labelError->setText("you haven't created a table");
        ui->labelError->setVisible(true);
    }

    if (flag)
    {
        bool correct = BogoSort(arr,ColSize,k);
        if (correct)
        {
            SetColFromArray(arr, ColSize);
            ArraySorted = true;
        }
        else
        {
            ui->labelError->setText("sorting failed,\n execution time exceeded");

            ui->labelError->setVisible(true);
        }
    }
}

void MainWindow::on_pushButtonDelete_clicked()
{
    HadeLabels();
    int ColSize = ui->tableWidget->columnCount();
    const int count = ColSize;
    int arr[200];
    bool flag = GetColumnToArray(arr, ColSize);
    bool correct = false;
    if (ui->tableWidget->columnCount()<=0)
    {
        ui->labelError->setText("you haven't created a table");
        ui->labelError->setVisible(true);
    }

    if (flag)
    {
        for (int i = 0; i < ColSize; ++i)
        {
            for  (int j = 0; j < ColSize-1; ++j)
            {
                if (arr[j] > arr[j+1])
                {
                    correct = false;
                    break;
                }
                else
                {
                    correct = true;
                }
            }
        }

        if (correct&&ArraySorted)
        {
            DeleteDuplicates(arr, ColSize);
            SetColFromArray(arr, ColSize);
            if (ColSize != count)
            {
                ui->labelDub->setText("duplicate removal\n completed");
                ui->labelDub->setVisible (true);
            }
            else
            {
                ui->labelDub->setText("duplicate removal \n completed, \n no duplicates");

                ui->labelDub->setVisible (true);
            }


        }
        else
        {
            ui->labelDub->setText("array is not sorted");
            ui->labelDub->setVisible (true);
        }
    }
}

void MainWindow::on_pushButtonSearch_clicked()
{
    HadeLabels();
    if(ui->tableWidget->columnCount ()<=0)
    {
        ui->labelError->setText ("you haven't created a table");
        ui->labelError->setVisible (true);
        return;
    }

    int ColSize = ui->tableWidget->columnCount();
    int arr[200];
    bool flag = GetColumnToArray(arr, ColSize);
    bool correct = false;
    bool flagnumberinlineedit = true;
    int overlap = 0;
    int numberinlineedit = ui->lineEditSearch->text().toInt(&flagnumberinlineedit);
    bool count = false;
    QString arrStr;


    if(flagnumberinlineedit)
    {
        if(flag)
        {
            for (int i = 0; i < ColSize; i++)
            {
                for  (int j = 0; j < ColSize-1; j++)
                {
                    if (arr[j] > arr[j+1])
                    {
                        correct = false;
                        count = false;
                        break;
                    }
                    else if (arr[j] == arr[j+1])
                    {
                        count = true;
                        correct = true;
                    }
                    else
                    {
                        correct = true;
                    }
                }
            }
            if (correct)
            {
                if(!count)
                {
                    int binary=binarySearch(arr, ColSize, numberinlineedit);
                    if(binary!=-1)
                    {
                        ui->labelFoundedNumber->setText(QString::number(numberinlineedit));
                        ui->labelNumberInTable->setText(QString::number(binary+1));
                        ui->labelSovpadeni9->setText("1");
                        ui->label11->setVisible(true);
                        ui->label22->setVisible(true);
                        ui->label33->setVisible(true);
                        ui->labelFoundedNumber->setVisible(true);
                        ui->labelSovpadeni9->setVisible(true);
                        ui->labelNumberInTable->setVisible(true);
                    }
                    else
                    {
                        ui->label11->setVisible(false);
                        ui->label22->setVisible(false);
                        ui->label33->setVisible(false);
                        ui->labelFoundedNumber->setVisible(false);
                        ui->labelSovpadeni9->setVisible(false);
                        ui->labelNumberInTable->setVisible(false);
                        ui->labelError->setText("number not found");
                        ui->labelError->setVisible(true);
                    }
                }
                else
                {
                    linearSearch(arr, ColSize, numberinlineedit, overlap, arrStr);
                    if (overlap > 0)
                    {
                        ui->label11->setVisible(true);
                        ui->label22->setVisible(true);
                        ui->label33->setVisible(true);
                        ui->labelFoundedNumber->setVisible(true);
                        ui->labelSovpadeni9->setVisible(true);
                        ui->labelNumberInTable->setVisible(true);
                        ui->labelFoundedNumber->setText(QString::number(numberinlineedit));
                        ui->labelNumberInTable->setText(arrStr);
                        ui->labelSovpadeni9->setText(QString::number(overlap));
                    }
                    else
                    {
                        ui->label11->setVisible(false);
                        ui->label22->setVisible(false);
                        ui->label33->setVisible(false);
                        ui->labelFoundedNumber->setVisible(false);
                        ui->labelSovpadeni9->setVisible(false);
                        ui->labelNumberInTable->setVisible(false);
                        ui->labelError->setText(QString::number(numberinlineedit) + "error, \n number not find");

                    }
                }
            }
            else
            {
                linearSearch(arr, ColSize, numberinlineedit, overlap, arrStr);
                if (overlap > 0)
                {
                    ui->label11->setVisible(true);
                    ui->label22->setVisible(true);
                    ui->label33->setVisible(true);
                    ui->labelFoundedNumber->setVisible(true);
                    ui->labelSovpadeni9->setVisible(true);
                    ui->labelNumberInTable->setVisible(true);
                    ui->labelFoundedNumber->setText(QString::number(numberinlineedit));
                    ui->labelNumberInTable->setText(arrStr);
                    ui->labelSovpadeni9->setText(QString::number(overlap));
                }
                else
                {
                    ui->label11->setVisible(false);
                    ui->label22->setVisible(false);
                    ui->label33->setVisible(false);
                    ui->labelFoundedNumber->setVisible(false);
                    ui->labelSovpadeni9->setVisible(false);
                    ui->labelNumberInTable->setVisible(false);
                    ui->labelError->setText(QString::number(numberinlineedit) + " not found");
                    ui->labelError->setVisible(true);
                }
            }
        }
    }
    else
    {
        ui->label11->setVisible(false);
        ui->label22->setVisible(false);
        ui->label33->setVisible(false);
        ui->labelFoundedNumber->setVisible(false);
        ui->labelSovpadeni9->setVisible(false);
        ui->labelNumberInTable->setVisible(false);
        ui->labelError->setText ("must be a number");
        ui->labelError->setVisible (true);
    }
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    HadeLabels();
    bool flagError=false;
    bool flag;
    ui->tableWidget->item(0,column)->text().toInt (&flag);
    if (flag)
    {
        ui->tableWidget->item(0,column)->setBackgroundColor(Qt::white);
    }
    else
    {
        flagError=true;
        ui->tableWidget->item(0,column)->setBackgroundColor(Qt::red);
    }
    if(flagError)
    {
        ui->labelError->setText("put numbers in a table");
        ui->labelError->setVisible (true);
    }
    ui->tableWidget->clearSelection ();
    ArraySorted = false;
}
