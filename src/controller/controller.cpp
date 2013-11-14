#include "controller.h"
#include "searchresults.h"
#include "../model/database.h"
#include <QString>


Controller::Controller()
{
    /*Call here functions for the default display : allCustomers, history, productTypes ... */
}

void Controller::setDb(sqlite3* handle)
{
    database.setHandle(handle);
}

sqlite3* Controller::getDb()
{
    return database.getHandle();
}

void Controller::setViewPointers(SearchResults* par1, CustomerPanel* par2, CartDisplay* par3, ProductsChoices* par4, History* par5)
{
    viewSearchResults = par1;
    viewCustomerPanel = par2;
    viewCartDisplay = par3;
    viewProductsChoices = par4;
    viewHistory = par5;
}

void Controller::newText_Search(QString &viewSearch)
{

    std::string dbSearch;
    type_customerdbTuple db_tmpCurstomerInfo;
    view_customerTuple view_tmpCustomerInfo;
    //db_customerQueue dbQueue;                   // Information returned from the database as a queue
    type_customerdbQueue dbQueue;
    //view_customerQueue viewQueue;               // Information send to the view as a queue
    std::queue< std::tuple< QString, QString, QString, float, unsigned > > viewQueue;


    QString view_tmpName;
    QString view_tmpFirstName;
    QString view_tmpLogin;
    float view_tmpBalance;
    unsigned view_tmpId;
    QString view_tmpGroup;

    database.openDatabase();

    dbSearch = viewSearch.toStdString();

    // Get customer information corresponding to the search from model
    dbQueue = database.searchCustomer(dbSearch);


    if ( dbQueue.empty() ){
        qDebug() << " Model returned empty queue ";
        // ####### TEST #######
        /*std::queue< std::tuple< QString, QString, QString, float, unsigned > > toto;
        std::tuple< QString, QString, QString, float, unsigned > titi("Rousseau", "Woody", "2015", -2, 1);
        std::tuple< QString, QString, QString, float, unsigned > titi2("Manchoul", "Lamoule", "2014", 3.5, 2);
        toto.push(titi);
        toto.push(titi2);
        viewSearchResults->setSearchResults(toto);*/
        // ####### FIN TEST #######
    }
    else{

        // Copy the dbQueue into the viewQueue
        while( !dbQueue.empty() ){
            db_tmpCurstomerInfo = dbQueue.front();

            view_tmpName=QString::fromStdString( std::get<0>(db_tmpCurstomerInfo) );
            view_tmpFirstName=QString::fromStdString( std::get<1>(db_tmpCurstomerInfo) );
            view_tmpGroup=QString::fromStdString( std::get<2>(db_tmpCurstomerInfo) );
            view_tmpBalance = std::get<3>(db_tmpCurstomerInfo);
            view_tmpId = std::get<4>(db_tmpCurstomerInfo);
            //view_tmpLogin=QString::fromStdString( std::get<5>(db_tmpCurstomerInfo) );

            view_tmpCustomerInfo = std::make_tuple( view_tmpName, view_tmpFirstName, view_tmpGroup, view_tmpBalance, view_tmpId /*,view_tmpLogin*/ );

            viewQueue.push(view_tmpCustomerInfo);
            dbQueue.pop();
        }

        // Sent result to view
        qDebug() << "Taille de la queue :" << viewQueue.size();
        viewSearchResults->setSearchResults( viewQueue );

    }



}

void Controller::newClic_Customer(unsigned int customerId)
{
//    string firstName;
//    string familyName;
//    string group;
//    float money;

    type_customerdbTuple tmpDBCurstomerInfo;   // Output for SQL request
    std::tuple<QString, QString, QString, QString, float> tmpViewCurstomerInfo;

    qDebug() << "TEST0";
    tmpDBCurstomerInfo = database.getCustomerFromId( customerId );
    qDebug() << "TEST1";

        /* Create the customer */

    curCustomer = new Customer( std::get<5>( tmpDBCurstomerInfo ).c_str(),
                                std::get<0>( tmpDBCurstomerInfo ).c_str(),
                                std::get<1>( tmpDBCurstomerInfo ).c_str(),
                                std::get<2>( tmpDBCurstomerInfo ).c_str(),
                                std::get<3>( tmpDBCurstomerInfo ) );

    tmpViewCurstomerInfo = std::make_tuple( QString::fromStdString( curCustomer->getLogin() ),
                                            QString::fromStdString( curCustomer->getFirstName() ),
                                            QString::fromStdString( curCustomer->getFamilyName() ),
                                            QString::fromStdString( std::get<2>( tmpDBCurstomerInfo ) ),
                                            curCustomer->getBalance() );

    viewCustomerPanel->setCustomer( tmpViewCurstomerInfo );


}

//void Controller::newClic_CustomerPanel(unsigned int buttonId)
//{
//    /*switch(buttonId){
//     case 0:

//    }*/
//}

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
