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
#include "login.h"
#include "individualhistory.h"
#include "editcustomer.h"
#include "deletecustomer.h"
#include "globalhistory.h"
#include "newcustomer.h"
#include "addstock.h"
#include "addproduct.h"
#include "editproduct.h"


#include "customer.h"
#include "cart.h"
#include "product.h"
#include "structures.h"

#include "../model/database.h"


class SearchResults;
class CustomerPanel;
class CartDisplay;
class ProductsChoices;
class History;
class Login;
class Database;

class Stock;


class Controller
{
public:
    Controller();

    void mainController();


    void newText_Search(QString &search);
    void newClic_Customer(unsigned int customerId);

    void newClic_CustomerPanel(unsigned int buttonId);
    void newClic_ValidateCart(bool isCash);
    void newClic_CancelCart ();
    void newClic_ProductTypes(unsigned view_productTypeId);
    void newClic_Product(unsigned &view_productId);
    void newClic_Calculator();
    void newClic_IndividualHistory(unsigned customerId);
    void newClic_EditCustomer();
    void newClic_DeleteCustomer();
    void newClic_GlobalHistory();
    void newClic_NewCustomer();
    void newClic_AddStock();
    void newClic_AddProduct();
    void newClic_EditProduct();
    void newGlobal_Hist();
    void receiveCalculatorEntry(float amount);
    void receiveEditCustomerEntry(view_customerTuple& customer);
    void receiveNewCustomerEntry(view_customerTuple& customer);
    void receiveNewStocks(view_productQueue& products);
    void receiveNewProduct(view_productTuple& product);
    void receiveEditProduct(view_productTuple& product);
    //void setViewPointers(SearchResults* par1, CustomerPanel* par2, CartDisplay* par3, ProductsChoices* par4, History* par5);
    void setViewPointers(ViewObjects *viewObjects);
    void setCurCustomer(view_customerTuple &tuple);
    bool view_isLoginCorrect(QString login, QString passwd, LoginType loginType);
    bool isNegativeAllowed();

    view_productQueue getProductsOfCategorie(unsigned view_productTypeId);

    void setDb(sqlite3*);
    sqlite3* getDb();

private:
        /* View objects */
    /*SearchResults * viewSearchResults;
    CustomerPanel * viewCustomerPanel;
    CartDisplay * viewCartDisplay;
    History * viewHistory;*/
    ViewObjects*  view;
    LoginObjects currentLoginRequest;
    view_customerTuple *view_curCustomer;

        /* Controller objects */
    Stock * mp_stock;
    Customer * curCustomer;
    Cart * curCart;
    QString curSearch;
    bool negativeAllowed;

        /* Model objects */
    Database database;




};

#endif // CONTROLLER_H
