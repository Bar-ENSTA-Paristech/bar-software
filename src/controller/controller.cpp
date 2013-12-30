#include "controller.h"
#include "stock.h"
#include "searchresults.h"
#include "login.h"
#include "../model/database.h"
#include <QString>


Controller::Controller()
{
    /*Call here functions for the default display : allCustomers, history, productTypes ... */
    negativeAllowed = true;
}

void Controller::setDb(sqlite3* handle)
{
    database.setHandle(handle);
}

sqlite3* Controller::getDb()
{
    return database.getHandle();
}

void Controller::setViewPointers(ViewObjects* viewObjects)
{
    /*viewSearchResults = par1;
    viewCustomerPanel = par2;
    viewCartDisplay = par3;
    viewHistory = par5;*/
    view = viewObjects;

    //mp_stock = new Stock( this, &database, par4 );
    mp_stock = new Stock( this, &database, view->productChoices );
}

void Controller::mainController()
{
    QString emptyString;
    // Initialize view fields
    newText_Search( emptyString );
}




void Controller::newText_Search(QString &viewSearch)
{
    // Inputs and outputs
    std::string dbSearch;
    view_customerTuple view_tmpCustomerInfo;
    db_customerTuple db_tmpCustomerInfo;
    db_customerQueue dbQueue;
    view_customerQueue viewQueue;

    dbSearch = viewSearch.toStdString();


    database.openDatabase();
    dbQueue = database.searchCustomer(dbSearch);        // Get customer information corresponding to the search from model


    if ( !dbQueue.empty() ){

        // Copy the dbQueue into the viewQueue
        while( !dbQueue.empty() ){
            db_tmpCustomerInfo = dbQueue.front();

            view_tmpCustomerInfo=db_tmpCustomerInfo.transformIntoCustomerView();

            viewQueue.push(view_tmpCustomerInfo);
            dbQueue.pop();
        }

    }
    // Sent result to view
    view->searchResults->setSearchResults(viewQueue );

    database.closeDatabase();
}

void Controller::newClic_Customer(unsigned int customerId)
{
    //    string firstName;
    //    string familyName;
    //    string group;
    //    float money;
    database.openDatabase();
    db_customerTuple tmp_dbCustomerInfo;
    view_customerTuple tmpViewCustomerInfo;

    tmp_dbCustomerInfo = database.getCustomerFromId( customerId );

    /* Create the customer */
    tmpViewCustomerInfo=tmp_dbCustomerInfo.transformIntoCustomerView();
    view->customerPanel->setCustomer( tmpViewCustomerInfo );

    database.closeDatabase();

}

//void Controller::newClic_CustomerPanel(unsigned int buttonId)
//{
//    /*switch(buttonId){
//     case 0:

//    }*/
//}

void Controller::newClic_ProductTypes(unsigned view_productTypeId)
{
    qDebug() << "Supposed to send only product of categorie" << view_productTypeId;

    // Inputs and outputs

    view_productTuple view_tmpproductInfo;
    db_productTuple db_tmpproductInfo;
    db_productQueue dbQueue;
    view_productQueue viewQueue;

    database.openDatabase();
    dbQueue = database.getProductsFromCategory(view_productTypeId);        // Get product information corresponding to the search from model


    if ( !dbQueue.empty() ){

        // Copy the dbQueue into the viewQueue
        while( !dbQueue.empty() ){
            db_tmpproductInfo = dbQueue.front();

            view_tmpproductInfo=db_tmpproductInfo.transformIntoProductView();

            viewQueue.push(view_tmpproductInfo);
            dbQueue.pop();
        }

    }
    // Sent result to view
    view->productChoices->setProductsChoices(viewQueue);

    database.closeDatabase();
}

//void Controller::newClic_Product(QString &view_productName)
//{


//    string db_productName;
//    pair < float, unsigned > db_Product_Info;
//    Product newProduct;
//    view_productTuple view_tmpProductInfo;
//    queue< view_productTuple > view_Queue;


//        // Get product information from DB
//    db_productName = view_productName.toStdString();
//    /* SQL request : Get product information for product with name : db_productName as a std::pair
//     * float price
//     * unsigned stock
//    */

//        // Create Product
//    newProduct = Product( db_productName, db_Product_Info.first, db_Product_Info.second );
//    auto productPtr = make_shared<Product>(newProduct);

//        // Add it to the cart
//    curCart->addProductToCart( productPtr );


//        // Set cart information
//    curCart->getList(view_Queue);

//        // Send to view
//    viewCartDisplay->setCart(view_Queue);
//    viewCartDisplay->setTotalPrice(curCart->getPrice());
//}

bool Controller::view_isLoginCorrect(QString login, QString passwd, LoginType loginType)
{
    // ######### TO COMPLETE #######
    if(currentLoginRequest == CALCULATOR)
    {
        view->calculator->launchCalculator();
    }
    return true;
}

void Controller::newClic_Calculator()
{
    view->login->checkGlobal();
    currentLoginRequest = CALCULATOR;
}

void Controller::newClic_IndividualHistory()
{
    view_historyQueue toto;
    view->individualHistory->launchIndividualHistory(toto);
}

bool Controller::isNegativeAllowed()
{
    return negativeAllowed;
}
