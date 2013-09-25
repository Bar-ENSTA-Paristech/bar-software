#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>

#include "../view/searchresults.h"
#include "../view/customerpanel.h"
#include "../view/cartdisplay.h"
#include "../view/productschoices.h"
#include "../view/history.h"



class Controller
{
public:
    Controller();
    void newText_Search(QString search);
    void newClic_Customer(unsigned int customerId);
    void newClic_CustomerPanel(unsigned int buttonId);
    void newClic_Cart(unsigned int buttonId);
    void newClic_ProductTypes(QString productTypeName);
    void newClic_Product(QString productName);

private:
        /* View objects */
    SearchResults* viewSearchResults;
    CustomerPanel* viewCustomerPanel;
    CartDisplay* viewCartDisplay;
    ProductsChoices* viewProductsChoices;
    History* viewHistory;




};

#endif // CONTROLLER_H
