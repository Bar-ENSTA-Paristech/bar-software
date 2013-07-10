#include "mainwindow.h"
#include <initializer_list>
#include "customer.h"
#include <iostream>
#include <QApplication>
#include <QDebug>

unsigned Customer::numberOfConsumers = 0;

int main(int argc, char *argv[])
{
    std::pair<std::string,std::string> name = {"Woody","Rousseau"};
    Customer cus("wrousseau",name,"2014");
    qDebug() << cus.getFirstName().c_str() << " " << cus.getFamilyName().c_str() << " has " << cus.getBalance() << "€ available.";
    cus.addToBalance(70);
    qDebug() << cus.getFirstName().c_str() << " " << cus.getFamilyName().c_str() << " has " << cus.getBalance() << "€ available.";

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
