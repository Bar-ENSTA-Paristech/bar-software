#include "controller.h"


Controller::Controller()
{
    /*Call here functions for the default display : allCustomers, history, productTypes ... */
}

void Controller::newText_Search(QString viewSearch)
{
    typedef std::tuple< std::string, std::string, std::string, float, unsigned > type_dbTuple;
    typedef std::tuple< QString, QString, QString, float, unsigned > type_viewTuple;

    std::string dbSearch;       // The search as send to the database
    std::queue< std::tuple< std::string, std::string, std::string, float, unsigned > > dbQueue;     // Information returned from the database as a queue
    std::queue< std::tuple< QString, QString, QString, float, unsigned > > viewQueue;
    type_dbTuple tmp_dbTuple;
    type_viewTuple tmp_viewTuple;

    dbSearch = viewSearch.toStdString();

    // SQL Query function HERE
    /* Call query fonction from model to get the fields for view.
     * To begin The QString can be either name or firstName of the client : From the DB, query all fields :
     * Name, firstName, Categorie, Solde and Id
     * Mehdi, tu décide si tu fais des returns ou des pointeurs (à mon avis cette 2e solution est mieux)
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

}
