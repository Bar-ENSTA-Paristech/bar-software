#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>

#include "../view/searchresults.h"
#include "../view/customerpanel.h"
#include "../view/cartdisplay.h"
#include "../view/productschoices.h"
#include "../view/history.h"

#include "customer.h"
#include "cart.h"

typedef std::tuple< std::string, std::string, std::string, float, unsigned > type_dbTuple;
typedef std::tuple< QString, QString, QString, float, unsigned > type_viewTuple;

class Controller
{
public:
    Controller();
    void newText_Search(QString &search);
    void newClic_Customer(unsigned int customerId);
    void newClic_CustomerPanel(unsigned int buttonId);
    void newClic_Cart(unsigned int buttonId);
    void newClic_ProductTypes(QString &productTypeName);
    void newClic_Product(QString &productName);

private:
        /* View objects */
    SearchResults* viewSearchResults;
    CustomerPanel* viewCustomerPanel;
    CartDisplay* viewCartDisplay;
    ProductsChoices* viewProductsChoices;
    History* viewHistory;

        /* Controller objects */
    Customer curCustomer;
    Cart curCart; // Should the Cart be a member of Customer ?




};

#endif // CONTROLLER_H
