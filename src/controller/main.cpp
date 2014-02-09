#include "controller.h"
#include "mainwindow.h"
#include <initializer_list>
#include "customer.h"
#include <iostream>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "../model/plotting.h"
#include "qcustomplot.h"

#include "../model/database.h"
#include "cart.h"
#include "product.h"

QString GLOBAL_PATH;

int main(int argc, char *argv[])
{
    //
    QDir currentDir(QDir::currentPath());
    //QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath()); for deployement ?
#ifdef Q_OS_LINUX //pour linux
    currentDir.cdUp();
    currentDir.cd("bar-software");
#endif
#ifdef Q_OS_MAC // Pour MAC
    currentDir.cd("../../../../bar-software");
#endif
#ifdef Q_OS_WIN32 // Pour Windows
    currentDir.cd("../bar-software");
#endif
    GLOBAL_PATH = currentDir.absolutePath()+"/";
    qDebug() << "GLOBAL_PATH :" << GLOBAL_PATH;
/*
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
    //DB.getCustomerFromId(152);
    DB.getProductsFromCategory(5);
    DB.getProductFromId(1);
    DB.getLastOperations(30);
    Plotting plot;
    plot.setDb(DB.getHandle());
    db_dataarray Values_2 = plot.productStock(41,1);
    db_dataarray Values = plot.productConsumption(41,1);
    DB.getAllProducts ();
    DB.closeDatabase();
*/
    //Test graph
    Controller * controller = new Controller; qDebug() << "Controlleur : " << controller;
    QApplication application(argc, argv);
    QFile css(GLOBAL_PATH + "resources/design/mainDesign.css");
    if(css.open(QIODevice::ReadOnly)) {
        application.setStyleSheet(css.readAll());
    }
    MainWindow mainWindow;
    mainWindow.setController(controller);
    mainWindow.show();
    application.setWindowIcon(QIcon(GLOBAL_PATH + "resources/pictures/icon.png"));

    // ########## TEST GRAPHS ############
    //mainWindow.setGraph(Values, "xTitle", "yTitle", "Title de famille");
    //mainWindow.setGraph(Values_2, "xTitle", "yTitle", "Title de famille");


    return application.exec();
}
