#include <QCoreApplication>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int x;
    QCoreApplication a(argc, argv);
    cout << "Input first number:" << endl;
    cin >> x;
    cout << x << endl;
    return a.exec();
}
