#include <mywindow.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.showMaximized();
    w.setFixedSize(250,300);
    w.show();

    return a.exec();
}
