#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include <string>

#include <memory>


#include "../view/searchresults.h"
#include "../view/customerpanel.h"
#include "../view/cartdisplay.h"
#include "../view/productschoices.h"
#include "../view/history.h"

#include "customer.h"
#include "cart.h"
#include "product.h"


class Controller
{
public:
    Controller();
    void newText_Search(QString &search);
    void newClic_Customer(unsigned int customerId);
    void newClic_CustomerPanel(unsigned int buttonId);
    void newClic_Cart(unsigned int buttonId);
    void newClic_ProductTypes(QString &view_productTypeName);
    void newClic_Product(QString &view_productName);

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
