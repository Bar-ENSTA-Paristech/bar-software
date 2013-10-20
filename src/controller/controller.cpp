#include "controller.h"

#include <QString>


Controller::Controller()
{
    /*Call here functions for the default display : allCustomers, history, productTypes ... */
}

void Controller::newText_Search(QString &viewSearch)
{

    std::string dbSearch;
    type_customerdbTuple db_tmpCurstomerInfo;
    view_customerTuple view_tmpCustomerInfo;
    //db_customerQueue dbQueue;                   // Information returned from the database as a queue
    type_customerdbQueue dbQueue;
    view_customerQueue viewQueue;               // Information send to the view as a queue

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
            view_tmpLogin=QString::fromStdString( std::get<5>(db_tmpCurstomerInfo) );

            view_tmpCustomerInfo = std::make_tuple( view_tmpName, view_tmpFirstName, view_tmpGroup, view_tmpBalance, view_tmpId ,view_tmpLogin );


             qDebug() << "Tuple renvoyée par le modèle :";
            qDebug() << view_tmpName << ", ";
            qDebug() << view_tmpFirstName << ", " ;
            qDebug() << view_tmpGroup << ", " ;
            qDebug() << view_tmpBalance << ", " ;
            qDebug() << view_tmpId << ", " ;
            qDebug() << view_tmpLogin<<", ";

            viewQueue.push(view_tmpCustomerInfo);
            dbQueue.pop();
        }

        // Sent result to view
        //viewSearchResults->setSearchResults( viewQueue );
    }



}

//void Controller::newClic_Customer(unsigned int customerId)
//{
//    string firstName;
//    string familyName;
//    string group;
//    float money;

//    db_customerTuple db_tmpCurstomerInfo;   // Output for SQL request

//    db_tmpCurstomerInfo = database->getCustomerFromId( customerId );

//        /* Create the customer */

//    curCustomer = new Customer( get<0>(db_tmpCurstomerInfo),
//                            get<1>(db_tmpCurstomerInfo),
//                            get<2>(db_tmpCurstomerInfo),
//                            get<3>(db_tmpCurstomerInfo),
//                            get<4>(db_tmpCurstomerInfo)
//                          );

//    //CustomerPanel.setLogin( curCustomer.getLogin() );


//}

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
