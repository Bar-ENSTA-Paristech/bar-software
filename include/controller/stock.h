#ifndef STOCK_H
#define STOCK_H

#include "database.h"
#include "productschoices.h"
#include "product.h"

class Controller;

class Stock
{
public:
    Stock(Controller * parent, Database * database, ProductsChoices * viewProductChoices);
    ~Stock();
     void displayStock();

private:
    Controller * mep_controller;
    Database * mep_database;
    ProductsChoices * mep_viewProductChoices;
    std::map<Product, unsigned> m_inventory;        // Inventaire : liste des produits associés à leur quantité en stock

};

#endif // STOCK_H
