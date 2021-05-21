/********************************************************************************
** Form generated from reading UI file 'mywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWINDOW_H
#define UI_MYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyWindow)
    {
        if (MyWindow->objectName().isEmpty())
            MyWindow->setObjectName(QString::fromUtf8("MyWindow"));
        MyWindow->resize(400, 300);
        menuBar = new QMenuBar(MyWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        MyWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MyWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(MyWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MyWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MyWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MyWindow->setStatusBar(statusBar);

        retranslateUi(MyWindow);

        QMetaObject::connectSlotsByName(MyWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MyWindow)
    {
        MyWindow->setWindowTitle(QCoreApplication::translate("MyWindow", "MyWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyWindow: public Ui_MyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWINDOW_H
