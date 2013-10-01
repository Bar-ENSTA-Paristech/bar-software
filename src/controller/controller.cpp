#include "controller.h"

using namespace std;


Controller::Controller()
{
    /*Call here functions for the default display : allCustomers, history, productTypes ... */
}

void Controller::newText_Search(QString &viewSearch)
{
    typedef tuple< string, string, string, float, unsigned > db_customerTuple;
    typedef tuple< QString, QString, QString, float, unsigned > view_customerTuple;

    string dbSearch;                   // The search as send to the database
    queue< db_customerTuple > dbQueue;      // Information returned from the database as a queue
    queue< view_customerTuple > viewQueue;  // Information send to the view as a queue
    db_customerTuple db_tmpCurstomerInfo;
    view_customerTuple view_tmpCustomerInfo;

    dbSearch = viewSearch.toStdString();

    // SQL Query function HERE
    /* Call query fonction from model to get the fields for view.
     * To begin The QString can be either name or firstName of the client : From the DB, query all fields :
     * Name, firstName, Categorie, Solde and Id
    */

        // Copy the dbQueue into the viewQueue
    while( dbQueue.empty() ){
        db_tmpCurstomerInfo = dbQueue.front();
        get<0>(view_tmpCustomerInfo).fromStdString( get<0>(db_tmpCurstomerInfo) ) ;
        get<1>(view_tmpCustomerInfo).fromStdString( get<1>(db_tmpCurstomerInfo) );
        get<2>(view_tmpCustomerInfo).fromStdString( get<2>(db_tmpCurstomerInfo) );
        get<3>(view_tmpCustomerInfo) = get<3>(db_tmpCurstomerInfo);
        get<4>(view_tmpCustomerInfo) = get<4>(db_tmpCurstomerInfo);
        viewQueue.push(view_tmpCustomerInfo);
        dbQueue.pop();
    }

    viewSearchResults->setSearchResults( viewQueue );
}

void Controller::newClic_Customer(unsigned int customerId)
{
    typedef tuple< string, string, string, string, float, unsigned > db_customerTuple;

    db_customerTuple db_tmpCurstomerInfo;   // Output for SQL request

    /* SQL Request : type_dbTuple Query_dbFunction0( int customerId ); */
    /* SQL request : std::string photoFilename = Query_dbFunction1(int customerId ) */

        /* Create the customer */
    curCustomer = Customer( get<0>(db_tmpCurstomerInfo),
                            get<1>(db_tmpCurstomerInfo),
                            get<2>(db_tmpCurstomerInfo),
                            get<3>(db_tmpCurstomerInfo),
                            get<4>(db_tmpCurstomerInfo)
                          );

    //CustomerPanel.setLogin( curCustomer.getLogin() );


}

void Controller::newClic_CustomerPanel(unsigned int buttonId)
{
    /*switch(buttonId){
     case 0:

    }*/
}

void Controller::newClic_Product(QString &view_productName)
{
    typedef tuple<QString, float, unsigned int> view_productTuple;

    string db_productName;
    pair < float, unsigned > db_Product_Info;
    Product newProduct;
    view_productTuple view_tmpProductInfo;
    queue< view_productTuple > view_Queue;


        // Get product information from DB
    db_productName = view_productName.toStdString();
    /* SQL request : Get product information for product with name : db_productName as a std::pair
     * float price
     * unsigned stock
    */

        // Create Product
    newProduct = Product( db_productName, db_Product_Info.first, db_Product_Info.second );
    auto productPtr = make_shared<Product>(newProduct);

        // Add it to the cart
    curCart.addProductToCart( productPtr );


        // Set cart information
    curCart.getList(view_Queue);

        // Send to view
    viewCartDisplay->setCart(view_Queue);
    viewCartDisplay->setTotalPrice(curCart.getPrice());
}
