#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include <QTextDocument>
#include <QPrinter>
#include <string>
#include <cstdio>
#include <QCryptographicHash>
#include <QFile>
#include <QDir>
#include <QTimer>
#include <QThread>
#include <cmath>

#include <memory>


#include "../view/searchresults.h"
#include "../view/customerpanel.h"
#include "../view/cartdisplay.h"
#include "../view/productschoices.h"
#include "../view/history.h"
#include "mainwindow.h"
#include "login.h"
#include "individualhistory.h"
#include "editcustomer.h"
#include "deletecustomer.h"
#include "globalhistory.h"
#include "newcustomer.h"
#include "addstock.h"
#include "addproduct.h"
#include "editproduct.h"
#include "stats.h"
#include "admin.h"


#include "customer.h"
#include "cart.h"
#include "product.h"
#include "structures.h"

#include "../model/database.h"
#include "plotting.h"

#define MSEC_BETWEEN_BACKUP 14400000


class SearchResults;
class CustomerPanel;
class CartDisplay;
class ProductsChoices;
class History;
class Login;
class Database;

class Stock;


class Controller : public QObject
{
    Q_OBJECT
public:
    Controller();
    ~Controller();

    void mainController();


    void newText_Search(QString &search);
    void newClic_Customer(unsigned int customerId);

    void newClic_CustomerPanel(unsigned int buttonId);
    void newClic_ValidateCart(bool isCash);
    void newClic_CancelCart ();
    void newClic_ProductTypes(unsigned view_productTypeId);
    void newClic_Product(unsigned &view_productId);
    void newClic_Calculator();
    void newClic_IndividualHistory();
    void newClic_EditCustomer();
    void newClic_DeleteCustomer();
    void newClic_GlobalHistory();
    void newClic_NewCustomer();
    void newClic_AddStock();
    void newClic_AddProduct();
    void newClic_EditProduct();
    void newClic_Stats();
    void newClic_Admin();
    void newClic_Category(int id); // 0 for no filter (category TOUS), else id is the category id
    void newGlobal_Hist();
    void newClic_GlobalHistory_old();
    void newClic_IndividualHistory_old(int customerId);
    void newClic_IndividualGraph(int customerId);
    std::queue<QString> newCustCategoryList();
    void receiveCalculatorEntry(float amount, bool isPaidByCard);
    void receiveEditCustomerEntry(view_customerTuple& customer);
    void receiveNewCustomerEntry(view_customerTuple& customer, bool isCash);
    void receiveNewStocks(view_productQueue& products, float totalTVA, float totalTTC, QString infos);
    void receiveNewProduct(view_productTuple& product);
    void receiveEditProduct(view_productTuple& product, bool deleteProduct = false);
    void receiveAdminInfos(AdminTuple tuple);
    //void setViewPointers(SearchResults* par1, CustomerPanel* par2, CartDisplay* par3, ProductsChoices* par4, History* par5);
    void setViewPointers(ViewObjects *viewObjects);
    void setCurCustomer(view_customerTuple &tuple);
    bool view_isLoginCorrect(QString login, QString passwd, LoginType loginType);
    bool isCustomerInNegative();

    view_productQueue getProductsOfCategorie(unsigned view_productTypeId);
    // for these newPassword functions, they return false if an error occurs (eg new passwords different, bad rootPassword or globalPassord)
    bool newIndividualPassword(QString login, QString rootPasswd, QString passwd1, QString passwd2);
    bool newGlobalPassword(QString globalPasswd, QString passwd1, QString passwd2);
    bool newRootPassword(QString rootPasswd, QString passwd1, QString passwd2);

    void displayProductGraph(int id, bool consumption);
    void setCurrentLoginRequest(LoginObjects _currentLoginRequest){currentLoginRequest = _currentLoginRequest;}
    db_categoryQueue getConsoTypes(){return consoTypes;}
    db_TVAcategoryQueue getTvaRates(){db_TVAcategoryQueue queue; database->openDatabase(); queue=database->getTvaRates(); database->closeDatabase(); return queue;}
    db_categoryQueue getCustomerCategories(){
        db_categoryQueue queue; database->openDatabase(); queue=database->getCustCategories(); database->closeDatabase(); return queue;}
    db_categoryQueue getProductsCategories(){
        db_categoryQueue queue; database->openDatabase(); queue=database->getProdCategories(); database->closeDatabase(); return queue;}

    void setDb(sqlite3*);
    sqlite3* getDb();

    std::string xorCrypt(std::string input); // Crypte la sortie avec la méthode xor
    std::string hashPasswd(std::string password);
    void appendLog(std::string log); // Ajoute un évenement au log
    QString getLog(int month, int year);
    void PrintTvaPdf(int year);
    void deleteOldBackups();
    static float absolute(float val);

public slots:
    bool saveBackup();


private:
        /* View objects */
    /*SearchResults * viewSearchResults;
    CustomerPanel * viewCustomerPanel;
    CartDisplay * viewCartDisplay;
    History * viewHistory;*/
    ViewObjects*  view;
    LoginObjects currentLoginRequest;
    view_customerTuple *view_curCustomer;
    int currentConsoTypeIndex;

        /* Controller objects */
    Stock * mp_stock;
    Customer * curCustomer;
    Cart * curCart;
    QString curSearch;
    std::string currentLoggedCustomer;
    QTimer* backupTimer;

        /* Model objects */
    Database* database;
    Plotting* plotting;
    db_categoryQueue consoTypes;



};

#endif // CONTROLLER_H
