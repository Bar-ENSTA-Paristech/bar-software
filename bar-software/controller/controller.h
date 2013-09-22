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

private:
        /* View objects */
    SearchResults* viewSearchResults;
    CustomerPanel* viewCustomerPanel;
    CartDisplay* viewCartDisplay;
    ProductsChoices* viewProductsChoices;
    History* viewHistory;




};

#endif // CONTROLLER_H
