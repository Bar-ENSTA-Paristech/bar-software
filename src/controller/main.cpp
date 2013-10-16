#include "mainwindow.h"
#include "controller.h"
#include <initializer_list>
#include "customer.h"
#include <iostream>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "../model/database.h"
#include "cart.h"
#include "product.h"

unsigned Customer::numberOfCustomers = 0;
QString GLOBAL_PATH;


int main(int argc, char *argv[])
{
    QDir currentDir(QDir::currentPath());
    #ifdef Q_OS_LINUX //pour linux
    currentDir.cdUp();
    currentDir.cd("bar-software/bar-software");
    #endif
    #ifdef Q_OS_MAC // Pour MAC
    currentDir.cd("../../../../bar-software");
    #endif
    #ifdef Q_OS_WIN32 // Pour Windows
    currentDir.cd("../bar-software/bar-software");
    #endif
    GLOBAL_PATH = currentDir.absolutePath()+"/";
    qDebug() << GLOBAL_PATH;

    std::pair<std::string,std::string> name = {"Woody","Rousseau"};
    Customer cus("wrousseau",name,"2014");
    qDebug() << cus.getFirstName().c_str() << " " << cus.getFamilyName().c_str() << " has " << cus.getBalance() << "€ available.";
    cus.addToBalance(70);
    qDebug() << cus.getFirstName().c_str() << " " << cus.getFamilyName().c_str() << " has " << cus.getBalance() << "€ available.";

    // Test cart
    Product Duvel;
    Cart monPanier(Duvel);
    monPanier.removeProductFromCart( std::make_shared<Product>(Duvel) );
    monPanier.clearCart();

    Controller *controller = new Controller;

    Database DB;
    DB.openDatabase();
    DB.initializeDatabaseForm();
    //DB.getCustomerFromId(152);
    DB.getProductsFromCategory(5);
    DB.getProductFromId(1);
    std::string kikoo="s";
    DB.searchCustomer(kikoo);
    DB.getLastOperations();
    DB.closeDatabase();


    QApplication application(argc, argv);
    QFile css(GLOBAL_PATH + "include/view/mainDesign.css");
    if(css.open(QIODevice::ReadOnly)) {
       application.setStyleSheet(css.readAll());
    }
    qDebug() << "test " << GLOBAL_PATH;
    MainWindow mainWindow;
    mainWindow.setController(controller);
    mainWindow.show();

    return application.exec();
}
