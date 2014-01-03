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
    void newClic_Cart(unsigned int buttonId);
    void newClic_ProductTypes(unsigned view_productTypeId);
    void newClic_Product(unsigned &view_productId);
    void newClic_Calculator();
    void newClic_IndividualHistory(unsigned customerId);
    void newGlobal_Hist();
    //void setViewPointers(SearchResults* par1, CustomerPanel* par2, CartDisplay* par3, ProductsChoices* par4, History* par5);
    void setViewPointers(ViewObjects *viewObjects);
    bool view_isLoginCorrect(QString login, QString passwd, LoginType loginType);
    bool isNegativeAllowed();

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

        /* Controller objects */
    Stock * mp_stock;
    Customer * curCustomer;
    Cart * curCart; // Should the Cart be a member of Customer ?
    bool negativeAllowed;

        /* Model objects */
    Database database;




};

#endif // CONTROLLER_H
