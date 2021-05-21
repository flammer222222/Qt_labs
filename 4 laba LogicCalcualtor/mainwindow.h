#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_comboBox_activated(int index);
    void on_comboBox_2_activated(int index);
    void on_comboBox_3_activated(int index);

private:
    Ui::MainWindow *ui;
    bool getIndexForcomboBox();
    bool compare(int op1,int op2,int res);
    bool getIndexForComboBox3();
    int getIndexForComboBox2();
};

#endif // MAINWINDOW_H
