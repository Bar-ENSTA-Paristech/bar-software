#include "stock.h"
#include "controller.h"
#include "structures.h"

Stock::Stock(Controller * parent, Database * database, ProductsChoices * viewProductChoices) :
    mep_controller( parent ), mep_database( database), mep_viewProductChoices(viewProductChoices)
{
    initializeInventory();
    displayStock();
}

Stock::~Stock()
{
}

void Stock::displayStock()
{
    std::tuple<QString, QString, float, unsigned> viewProductInfo;
    std::queue<std::tuple<QString, QString, float, unsigned> > viewProductList;
    QString name;
    QString type;
    float price;
    unsigned quantity;

    for( unsigned int k=0; k<m_inventory.size(); ++k)
    {
        name = QString::fromStdString(m_inventory[k].getName());
        type = QString::fromStdString(m_inventory[k].getType());
        price = m_inventory[k].getPrice();
        quantity = m_inventory[k].getStock();

        viewProductInfo = std::make_tuple(name, type, price, quantity);
        viewProductList.push(viewProductInfo);
    }

    //mep_viewProductChoices->setProductsChoices( viewProductList );
}

void Stock::initializeInventory()
{
    unsigned int id;
    std::string name;
    std::string type;
    float price;
    unsigned quantity;
    db_productTuple dbProductInfo;
    db_productQueue dbProductList;

    mep_database->openDatabase();
    dbProductList = mep_database->getAllProducts();

    while( !dbProductList.empty() )
    {
        dbProductInfo = dbProductList.front();

        name = dbProductInfo.getProductName();
        type = dbProductInfo.getProductCategory();
        price = dbProductInfo.getProductPrice();
        quantity = dbProductInfo.getProductStock();
        id = dbProductInfo.getProductId();

        Product newProduct(id,name,type,price,quantity);
        m_inventory.push_back(newProduct);
        dbProductList.pop();
    }
    mep_database->closeDatabase();
}
