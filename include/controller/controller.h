#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include <string>

#include <memory>


#include "../view/searchresults.h"
#include "../view/customerpanel.h"
#include "../view/cartdisplay.h"
#include "../view/productschoices.h"
#include "../view/history.h"

#include "customer.h"
#include "cart.h"
#include "product.h"

#include "../model/database.h"

    //TUPLE model du consommateur : Nom, Prénom ,Login, Catégorie , balance , id , login
//typedef std::tuple<  std::string, std::string, std::string , std::string, float, unsigned > db_customerTuple;
    //TUPLE view du consommateur : Nom, Prénom , Catégorie , balance , id
typedef std::tuple< QString, QString, QString, float, unsigned,QString > view_customerTuple;
    //TUPLE model du produit : Produit, Catégorie , prix ,stock , id
typedef std::tuple< std::string, unsigned, float , unsigned, unsigned > db_consoTuple;
    //TUPLE view du produit : Produit, prix, quantity
typedef std::tuple<QString, float, unsigned int> view_productTuple;
    //TUPLE model d'un historique (une transaction) : Nom, Prénom, Produit, Date, valeur
typedef std::tuple< std::string,std::string,std::string,std::string , float> db_histTuple;

    //On définit les structures de queue<> correspondant à chaque type de tuple
//typedef std::queue<db_customerTuple> db_customerQueue;
typedef std::queue<db_consoTuple> db_consoQueue;
typedef std::queue<db_histTuple> db_histQueue;
typedef std::queue<view_customerTuple> view_customerQueue;
typedef std::queue<view_productTuple> view_productQueue;



class Controller
{
public:
    Controller();
    void newText_Search(QString &search);
    void newClic_Customer(unsigned int customerId);
    void newClic_CustomerPanel(unsigned int buttonId);
    void newClic_Cart(unsigned int buttonId);
    void newClic_ProductTypes(QString &view_productTypeName);
    void newClic_Product(QString &view_productName);

private:
        /* View objects */
    SearchResults * viewSearchResults;
    CustomerPanel * viewCustomerPanel;
    CartDisplay * viewCartDisplay;
    ProductsChoices * viewProductsChoices;
    History * viewHistory;

        /* Controller objects */
    Customer * curCustomer;
    Cart * curCart; // Should the Cart be a member of Customer ?

        /* Model objects */
    Database database;




};

#endif // CONTROLLER_H
