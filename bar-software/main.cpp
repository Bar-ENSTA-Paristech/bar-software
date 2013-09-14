#include "gui/mainwindow.h"
#include <initializer_list>
#include "customer.h"
#include <iostream>
#include <QApplication>
#include <QFile>

#include <QDebug>

#include "database.h"
#include "cart.h"
#include "product.h"

unsigned Customer::numberOfCustomers = 0;

int main(int argc, char *argv[])
{
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


    database DB;
    DB.openDatabase();

    Query test_q;
    test_q.setQuery("CREATE TABLE IF NOT EXISTS Bar(test VARCHAR(40));");
    DB.executeQuery(test_q);

    DB.closeDatabase();

    QApplication a(argc, argv);
    /* Pas de BUG avec le .qss (css pour Qt) mais aucun effet ...*/
    QFile css(":/qss/mainDesign.qss");
    if(css.open(QIODevice::ReadOnly)) {
       a.setStyleSheet(css.readAll());
    }
    MainWindow w;
    w.show();
    
    return a.exec();
}
