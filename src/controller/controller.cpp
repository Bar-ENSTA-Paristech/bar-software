#include "controller.h"


Controller::Controller()
{
    /*Call here functions for the default display : allCustomers, history, productTypes ... */
}

void Controller::newText_Search(QString &viewSearch)
{

    std::string dbSearch;                   // The search as send to the database
    std::queue< type_dbTuple > dbQueue;      // Information returned from the database as a queue
    std::queue< type_viewTuple > viewQueue;  // Information send to the view as a queue
    type_dbTuple tmp_dbTuple;
    type_viewTuple tmp_viewTuple;

    dbSearch = viewSearch.toStdString();

    // SQL Query function HERE
    /* Call query fonction from model to get the fields for view.
     * To begin The QString can be either name or firstName of the client : From the DB, query all fields :
     * Name, firstName, Categorie, Solde and Id
    */

        // Copy the dbQueue into the viewQueue
    while( dbQueue.empty() ){
        tmp_dbTuple = dbQueue.front();
        std::get<0>(tmp_viewTuple).fromStdString( std::get<0>(tmp_dbTuple) ) ;
        std::get<1>(tmp_viewTuple).fromStdString( std::get<1>(tmp_dbTuple) );
        std::get<2>(tmp_viewTuple).fromStdString( std::get<2>(tmp_dbTuple) );
        std::get<3>(tmp_viewTuple) = std::get<3>(tmp_dbTuple);
        std::get<4>(tmp_viewTuple) = std::get<4>(tmp_dbTuple);
        viewQueue.push(tmp_viewTuple);
        dbQueue.pop();
    }

    viewSearchResults->setSearchResults( viewQueue );
}

void Controller::newClic_Customer(unsigned int customerId)
{
    type_dbTuple tmp_dbTuple;   // Output for SQL request

    /* SQL Request : type_dbTuple Query_dbFunction0( int customerId ); */
    /* SQL request : std::string photoFilename = Query_dbFunction1(int customerId ) */

        /* Create the customer */
    curCustomer = Customer( "Vinzo", std::get<0>(tmp_dbTuple), std::get<1>(tmp_dbTuple), std::get<2>(tmp_dbTuple), std::get<3>(tmp_dbTuple));



}
