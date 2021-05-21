#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QtWidgets>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

class QLCDNumber;

class Widget : public QMenuBar
{
    Q_OBJECT

public:
    Widget(QMenuBar *parent = 0);
    double fnum, lnum;

    QLineEdit *line;




    QPushButton *b0;
    QPushButton *b1;
    QPushButton *b2;
    QPushButton *b3;
    QPushButton *b4;
    QPushButton *b5;
    QPushButton *b6;
    QPushButton *b7;
    QPushButton *b8;
    QPushButton *b9;
    QPushButton *bclear;
    QPushButton *bbackspace;
    QPushButton *bplusminus;
    QPushButton *bsub;
    QPushButton *bmult;
    QPushButton *bminus;
    QPushButton *bplus;
    QPushButton *bcomma;
    QPushButton *bequal;

    QPushButton *coss;
    QPushButton *sins;
    QPushButton *drob;
    QPushButton *sqrt;
    //QPushButton *proc;

    QPushButton *bmemsave;
    QPushButton *bmemread;

    QAction* calc1Act;
    QAction* calc2Act;
    QAction* calc3Act;
    QAction* calc4Act;
    QAction* dop1Act;
    QAction* dop2Act;
    QAction* dop3Act;
    QAction* dop4Act;
    QAction* dop5Act;
    QAction* copy;
    QAction* past;
    QAction* helpAct;
    QAction* op;
    QAction* list;
    QAction* ipot;
    QAction* avto;
    QAction* econ1;
    QAction* econ2;


private:
    QWidget* p;
    QMenu* editMenu;
    QMenu* viewMenu;
    QMenu* helpMenu;
    QMenu* editlist;



    void createMenuBar();
    void createActions();

protected:
    //void bt1(QKeyEvent *event);

public slots:
    void bt1();
    void bt2();
    void bt3();
    void bt4();
    void bt5();
    void bt6();
    void bt7();
    void bt8();
    void bt9();
    void bt0();
    void bs();
    void ps();
    void plus();
    void minus();
    void multiply();
    void divide();
    void com();
    void equal();

    void cossb();
    void sinsb();
    void drobb();
    void sqrtb();
    //void procb();

    void memsave();
    void memread();

    void poppub();
    void oprb();
    void copyb();
    void pastb();
};

#endif // MYWINDOW_H
