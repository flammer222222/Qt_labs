#include <mywindow.h>
#include <cmath>
#include <QtWidgets>

bool plusbool=false, minusbool=false, multiplybool=false, dividebool=false;
 double valuee=0;
Widget::Widget(QMenuBar *parent):QMenuBar(parent)

 {
    p = parent;

    line=new QLineEdit;
    line->setAlignment(Qt::AlignRight);
    line->setReadOnly(true);


    QVBoxLayout *vbox = new QVBoxLayout;
    QGridLayout *gbox = new QGridLayout;
    b1=new QPushButton("1");
    b2=new QPushButton("2");
    b3=new QPushButton("3");
    b4=new QPushButton("4");
    b5=new QPushButton("5");
    b6=new QPushButton("6");
    b7=new QPushButton("7");
    b8=new QPushButton("8");
    b9=new QPushButton("9");
    b0=new QPushButton("0");
    bplus=new QPushButton("+");
    bequal=new QPushButton("=");

    setStyleSheet("QPushButton:pressed{"
                              "background-color: rgb(0, 0, 0);"
                              "border-style: inset;"
                              "color: white;"
                              "border-style: outset;"
                              "border-width: 1px;"
                              "border-radius: 3px;"
                              "border-color: beige;"
                              "font: bold 14p;"
                              "min-width: 10em;"
                              "padding: 50px;}" );




    vbox->addWidget(line);
    gbox->addWidget(b7,1,0);
    gbox->addWidget(b8,1,1);
    gbox->addWidget(b9,1,2);
    gbox->addWidget(b4,2,0);
    gbox->addWidget(b5,2,1);
    gbox->addWidget(b6,2,2);
    gbox->addWidget(b1,3,0);
    gbox->addWidget(b2,3,1);
    gbox->addWidget(b3,3,2);
    gbox->addWidget(bplus,4,1);
    gbox->addWidget(b0,4,0);
    gbox->addWidget(bequal,4,2);
    vbox->addLayout(gbox);
    connect(b1, SIGNAL(clicked()), this, SLOT(bt1()));
    connect(b2, SIGNAL(clicked()), this, SLOT(bt2()));
    connect(b3, SIGNAL(clicked()), this, SLOT(bt3()));
    connect(b4, SIGNAL(clicked()), this, SLOT(bt4()));
    connect(b5, SIGNAL(clicked()), this, SLOT(bt5()));
    connect(b6, SIGNAL(clicked()), this, SLOT(bt6()));
    connect(b7, SIGNAL(clicked()), this, SLOT(bt7()));
    connect(b8, SIGNAL(clicked()), this, SLOT(bt8()));
    connect(b9, SIGNAL(clicked()), this, SLOT(bt9()));
    connect(b0, SIGNAL(clicked()), this, SLOT(bt0()));
    connect(bplus, SIGNAL(clicked()), this, SLOT(plus()));
    connect(bequal, SIGNAL(clicked()), this, SLOT(equal()));
    this->setLayout(vbox);

}
void Widget::bt1(){
    QString s = line->text();
    s=s+"1";
    line->setText(s);
}
void Widget::bt2(){
    QString s = line->text();
    s=s+"2";
    line->setText(s);
}
void Widget::bt3(){
    QString s = line->text();
    s=s+"3";
    line->setText(s);
}
void Widget::bt4(){
    QString s = line->text();
    s=s+"4";
    line->setText(s);
}
void Widget::bt5(){
    QString s = line->text();
    s=s+"5";
    line->setText(s);
}
void Widget::bt6(){
    QString s = line->text();
    s=s+"6";
    line->setText(s);
}
void Widget::bt7(){
    QString s = line->text();
    s=s+"7";
    line->setText(s);
}
void Widget::bt8(){
    QString s = line->text();
    s=s+"8";
    line->setText(s);
}
void Widget::bt9(){
    QString s = line->text();
    s=s+"9";
    line->setText(s);
}
void Widget::bt0(){
    QString s = line->text();
    s=s+"0";
    line->setText(s);
}
void Widget::bs(){ // удаление
    QString s = line->text();
    int a=s.toDouble();
    a=a/10;
    line->setText(QString::number(a));
}
void Widget::ps(){ //плюс-минус
    QString s = line->text();
    int a=s.toInt();
    line->setText(QString::number(-a));
}
void Widget::plus(){ //плюс
    QString s=line->text();
    fnum=s.toDouble();
    s=s+"+";
    line->clear();
    plusbool=true;
}
void Widget::minus(){ //минус
    QString s= line->text();
    fnum=s.toDouble();
    line->clear();
    minusbool=true;
}
void Widget::multiply(){ //умножить
    QString s= line->text();
    fnum=s.toDouble();
    line->clear();
    multiplybool=true;

}
void Widget::divide(){ //деление
    QString s=line->text();
    fnum=s.toDouble();
    line->clear();
    dividebool=true;
}


void Widget::equal(){ // равно
    QString s=line->text();
    lnum=s.toDouble();
    if (plusbool){
        double c=fnum+lnum;
        line->setText(QString::number(c));
        plusbool=false;
    }
    if (minusbool){
        double c=fnum-lnum;
        line->setText(QString::number(c));
        minusbool=false;
    }
    if (multiplybool){
        double c=fnum*lnum;
        line->setText(QString::number(c));
        multiplybool=false;
    }
    if (dividebool){
         double c=fnum/lnum;
         line->setText(QString::number(c));
        dividebool=false;
    }
}

void Widget::memsave(){ // COPY
    valuee=line->text().toDouble();
}
void Widget::memread(){ // PAST
    line->setText(QString::number(valuee));
}


void Widget::copyb(){
    valuee=line->text().toDouble();
}
void Widget::pastb(){
    line->setText(QString::number(valuee));
}


