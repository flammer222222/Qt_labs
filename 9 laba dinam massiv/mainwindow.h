#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent=0);
    ~MainWindow();

private slots:

    void on_pushButtonInput_clicked();

    void on_pushButtonRandom_clicked();

    void on_pushButtonMin_clicked();

    void on_pushButtonMax_clicked();

    void on_pushButtonAvg_clicked();

    void on_pushButtonBubbleSort_clicked();

    void on_pushButtonQuickSort_clicked();

    void on_pushButtonCombSort_clicked();

    void on_pushButtonGnomeSort_clicked();

    void on_pushButtonBogoSort_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonSearch_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    //void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;

    bool GetColumnToArray(int arr[], int size);

    bool CheckBogoSorted(int *arr, int size);

    bool BogoSort(int *arr, int size,int& k);

    void DeleteDuplicates (int *arr, int &size);

    void SetColFromArray(int arr[], int size);

    void linearSearch(int *arr, int size, int search, int &n, QString &arrStr);

    int binarySearch(int *arr, int size, int k);

    void HadeLabels();

    void ValueError(int idCol, int size);

    void NullExistError(int idCol, int size);

    void QuickSort(int *arr, int size);

    bool ArraySorted;
};
#endif // MAINWINDOW_H
