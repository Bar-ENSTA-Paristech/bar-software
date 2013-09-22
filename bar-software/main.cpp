#include "gui/mainwindow.h"
#include <initializer_list>
#include "customer.h"
#include <iostream>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "database.h"
#include "cart.h"
#include "product.h"

unsigned Customer::numberOfCustomers = 0;
QString GLOBAL_PATH;


int main(int argc, char *argv[])
{
    QDir currentDir(QDir::currentPath());
    #ifndef Q_OS_MAC //pour windows et linux
    currentDir.cd("../bar-software/bar-software");
    #else // Pour MAC
    // A définir
    #endif
    GLOBAL_PATH = currentDir.absolutePath()+"/";

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


    Database DB;
    DB.openDatabase();
    DB.initializeDatabaseForm();
    DB.closeDatabase();

    QApplication application(argc, argv);
    QFile css(GLOBAL_PATH + "gui/mainDesign.css");
    if(css.open(QIODevice::ReadOnly)) {
       application.setStyleSheet(css.readAll());
    }
    qDebug() << "test " << QDir::currentPath() ;
    MainWindow mainWindow;
    mainWindow.show();
    
    return application.exec();
}
