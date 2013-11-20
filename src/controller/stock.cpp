#include "stock.h"
#include "controller.h"

Stock::Stock(Controller * parent, Database * database, ProductsChoices * viewProductChoices) :
    mep_controller( parent ), mep_database( database), mep_viewProductChoices(viewProductChoices)
{
    displayStock();
}

Stock::~Stock()
{
}

void Stock::displayStock()
{
    type_consodbTuple dbProductInfo;
    type_consodbQueue dbProductList;
    std::tuple<QString, QString, float, unsigned> viewProductInfo;
    std::queue<std::tuple<QString, QString, float, unsigned> > viewProductList;

    QString name;
    QString type;
    float price;
    unsigned quantity;
    //unsigned id;

    mep_database->openDatabase();

    dbProductList = mep_database->getAllProducts();

    while( !dbProductList.empty() )
    {
        dbProductInfo = dbProductList.front();

        name = QString::fromStdString( std::get<0>( dbProductInfo ) );
        type = QString::number( std::get<1>( dbProductInfo ) );
        price = std::get<2>( dbProductInfo );
        quantity = std::get<3>( dbProductInfo );
        //id = std::get<4>( dbProductInfo );

        viewProductInfo = std::make_tuple( name, type, price, quantity );
        viewProductList.push( viewProductInfo );

        dbProductList.pop();
    }

    mep_viewProductChoices->setProductsChoices( viewProductList );

    mep_database->closeDatabase();
}
