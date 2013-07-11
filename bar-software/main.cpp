#include "mainwindow.h"
#include <initializer_list>
#include "customer.h"
#include <iostream>
#include <QApplication>

unsigned Customer::numberOfCustomers = 0;

int main(int argc, char *argv[])
{
    std::pair<std::string,std::string> name = {"Woody","Rousseau"};
    Customer cus("wrousseau",name,"2014");
    std::cout << cus.getFirstName() << " " << cus.getFamilyName() << " has " << cus.getBalance() << "€ available." << std::endl;
    cus.addToBalance(70);
    std::cout << cus.getFirstName() << " " << cus.getFamilyName() << " has " << cus.getBalance() << "€ available." << std::endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
