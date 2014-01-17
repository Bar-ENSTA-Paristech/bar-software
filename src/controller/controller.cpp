#include "controller.h"
#include "stock.h"
#include "searchresults.h"
#include "login.h"
#include "../model/database.h"
#include <QString>


Controller::Controller()
{
    /*Call here functions for the default display : allCustomers, history, productTypes ... */
    negativeAllowed = true;
    curCart = new Cart;
    curCustomer = new Customer;
    view_curCustomer = new view_customerTuple;
}

void Controller::setDb(sqlite3* handle)
{
    database.setHandle(handle);
}

sqlite3* Controller::getDb()
{
    return database.getHandle();
}

void Controller::setViewPointers(ViewObjects* viewObjects)
{
    /*viewSearchResults = par1;
    viewCustomerPanel = par2;
    viewCartDisplay = par3;
    viewHistory = par5;*/

    view = viewObjects;

    //mp_stock = new Stock( this, &database, par4 );
    mp_stock = new Stock( this, &database, view->productChoices );
}

void Controller::mainController()
{
    QString emptyString;
    // Initialize view fields
    newText_Search( emptyString );
    newGlobal_Hist();
}




void Controller::newText_Search(QString &viewSearch)
{
    // Inputs and outputs
    std::string dbSearch;
    view_customerTuple view_tmpCustomerInfo;
    db_customerTuple db_tmpCustomerInfo;
    db_customerQueue dbQueue;
    view_customerQueue viewQueue;

    curSearch= viewSearch;
    dbSearch = viewSearch.toStdString();


    database.openDatabase();
    dbQueue = database.searchCustomer(dbSearch);        // Get customer information corresponding to the search from model


    if ( !dbQueue.empty() ){

        // Copy the dbQueue into the viewQueue
        while( !dbQueue.empty() ){
            db_tmpCustomerInfo = dbQueue.front();

            view_tmpCustomerInfo=db_tmpCustomerInfo.transformIntoCustomerView();

            viewQueue.push(view_tmpCustomerInfo);
            dbQueue.pop();
        }

    }
    // Sent result to view
    view->searchResults->setSearchResults(viewQueue );

    database.closeDatabase();
}

void Controller::newGlobal_Hist()
{
    view_histQueue HistoryQueue;
    view_histTuple HistoryTuple;

    db_histQueue dbHistoryQueue;
    db_histTuple dbHistoryTuple;

    database.openDatabase();
    dbHistoryQueue = database.getLastOperations(30);

    if ( !dbHistoryQueue.empty() ){

        // Copy the dbQueue into the viewQueue
        while( !dbHistoryQueue.empty() )
        {
            dbHistoryTuple = dbHistoryQueue.front();

            HistoryTuple=dbHistoryTuple.transformIntoHistView();

            HistoryQueue.push(HistoryTuple);
            dbHistoryQueue.pop();
        }

    }
    // Sent result to view
    view->history->setHistory(HistoryQueue);

    database.closeDatabase();

}

void Controller::newClic_Customer(unsigned int customerId)
{
    database.openDatabase();
    db_customerTuple tmp_dbCustomerInfo;
    view_customerTuple tmpViewCustomerInfo;

    tmp_dbCustomerInfo = database.getCustomerFromId( customerId );

    /* Create the customer */
    tmpViewCustomerInfo=tmp_dbCustomerInfo.transformIntoCustomerView();
    setCurCustomer(tmpViewCustomerInfo);
    view->customerPanel->setCustomer( tmpViewCustomerInfo );
    //view->customerPanel->setFuturBalance(tmpViewCustomerInfo.getCustomerBalance()); Ca sert à rien d'afficher deux fois la meme somme ...
    view->customerPanel->setFuturBalance(0,false); // on l'efface pour le nouveau client (reset)

    database.closeDatabase();

}

//void Controller::newClic_CustomerPanel(unsigned int buttonId)
//{
//    /*switch(buttonId){
//     case 0:

//    }*/
//}

void Controller::newClic_ValidateCart(bool isCash)
{
    // ###################### TO COMPLETE : isCash #######################

    qDebug()<<"Received click to validate cart";

    //Inputs and outputs

    db_productTuple db_productInfo;
    QList<cartProduct> currentCartController;
    view_cartQueue displayCart;

    db_histTuple histToBeInserted;
    db_customerTuple customerToBeEdited;
    view_customerTuple editedCustomer;
    db_productTuple productToBeEdited;
    //Validation demandée :

    //-Getting informations

    currentCartController = curCart->getList();
    database.openDatabase();

    for (int i=0; i<currentCartController.size();i++)
    {
        db_productInfo=database.getProductFromId(currentCartController[i].first);

        qDebug()<<"Creating a histTuple to insert into the database";

        histToBeInserted.setHistCustomerId(curCustomer->getCustomerId());
        histToBeInserted.setHistProductId(db_productInfo.getProductId());
        histToBeInserted.setHistPrice(db_productInfo.getProductPrice());
        qDebug()<<"Modifde l'hist";
        database.addHist(histToBeInserted);

        qDebug()<<"Modification du compte débité";
        customerToBeEdited = database.getCustomerFromId(curCustomer->getCustomerId());
        customerToBeEdited.setCustomerBalance(curCustomer->getBalance()-curCart->getPrice());
        database.editCustomerAccount(customerToBeEdited);

        qDebug()<<"Modification des stocks";
        productToBeEdited = db_productInfo;
        productToBeEdited.setProductStock(productToBeEdited.getProductStock()-currentCartController[i].second);
        database.editProduct(productToBeEdited);

    }
    editedCustomer = database.getCustomerFromId(curCustomer->getCustomerId()).transformIntoCustomerView();
    database.closeDatabase();
    qDebug()<<"Validated cart";

    //Affichage d'un popup ? -> non juste un Qlabel au dessus des boutons : plus léger et plus rapide
    // Et on affiche la validation dans la partie dédiée du cart
    view->cartDisplay->setLastCart(view_curCustomer->getCustomerName(), curCart->getPrice());

    //On efface ensuite les infos du cart
    curCart->clearCart();
    view->cartDisplay->setTotalPrice(curCart->getPrice());
    view->cartDisplay->setCart(displayCart);

    view->customerPanel->setCustomer(editedCustomer);
    // On efface la prévision du solde
    view->customerPanel->setFuturBalance(0, false);


    //Updating l'hist global
    newGlobal_Hist();

    //reloading les comptes
    newText_Search(curSearch);
    return;
}

void Controller::newClic_CancelCart()
{
    qDebug()<<"Received click to cancel cart";
    view_cartQueue displayCart;
    //On efface les infos du cart
    curCart->clearCart();
    view->cartDisplay->setTotalPrice(curCart->getPrice());
    view->cartDisplay->setCart(displayCart);
    // On efface la prévision du solde
    view->customerPanel->setFuturBalance(0, false);
    qDebug()<<"cancelled cart";
    return;
}



void Controller::newClic_ProductTypes(unsigned view_productTypeId)
{
    qDebug() << "Supposed to send only product of categorie" << view_productTypeId;

    view_productQueue viewQueue = getProductsOfCategorie(view_productTypeId);

    // Sent result to view
    view->productChoices->setProductsChoices(viewQueue);


    //Emptying the view queue
    return;
}

view_productQueue Controller::getProductsOfCategorie(unsigned view_productTypeId)
{
    // Inputs and outputs
    view_productTuple view_tmpproductInfo;
    db_productTuple db_tmpproductInfo;

    db_productQueue dbQueue;
    //dbQueue=new db_productQueue;

    view_productQueue viewQueue;
    //viewQueue=new view_productQueue;

    database.openDatabase();
    dbQueue = database.getProductsFromCategory(view_productTypeId);        // Get product information corresponding to the search from model

    if ( !dbQueue.empty() ){

        // Copy the dbQueue into the viewQueue
        while( !dbQueue.empty() ){
            db_tmpproductInfo = dbQueue.front();

            view_tmpproductInfo=db_tmpproductInfo.transformIntoProductView();

            viewQueue.push(view_tmpproductInfo);
            dbQueue.pop();
        }

    }
    database.closeDatabase();
    return viewQueue;
}

void Controller::newClic_Product(unsigned &view_productId)
{
    qDebug() << "Supposed to send only product n°" << view_productId;

    QList<cartProduct> currentCartController;

    view_cartQueue displayCart;
    view_cartTuple displayProd;

    db_productTuple db_productInfo;

    // Get product information from DB
    //unsigned id=10;

    database.openDatabase();
    db_productInfo=database.getProductFromId(view_productId);

    //10 is a standard value while waiting Customer to be OK.
    //curCart->setCustomerID(10);

    //Check if there is enough stock or id selled (the = is for the debug)
    if (true==true)
        //(db_productInfo.getProductStock()>0)
    {
        // Add it to the cart
        curCart->addProductToCart( view_productId );
        //Edit price
        curCart->editPrice(db_productInfo.getProductPrice());
    }
    //else : Display Warning

    // Get cart information
    currentCartController = curCart->getList();

    //Tranform cart into Displaycart
    //Which contains : customerId,product_id,p
    for (int i=0; i<currentCartController.size();i++)
    {
        db_productInfo=database.getProductFromId(currentCartController[i].first);
        displayProd.setCartCustomerId(curCustomer->getCustomerId());
        displayProd.setCartPrice(db_productInfo.getProductPrice());
        displayProd.setCartProdId(currentCartController[i].first);
        displayProd.setCartProdName(QString::fromStdString(db_productInfo.getProductName()));
        displayProd.setCartQuantity(currentCartController[i].second);

        displayCart.push(displayProd);
    }
    database.closeDatabase();
    // Send to view
    view->cartDisplay->setTotalPrice(curCart->getPrice());
    view->cartDisplay->setCart(displayCart);
    VIEW.customerPanel->setFuturBalance(curCustomer->getBalance()-curCart->getPrice());
}

bool Controller::view_isLoginCorrect(QString login, QString passwd, LoginType loginType)
{
    db_categoryQueue dbQueue;
    db_categoryTuple dbTuple;
    std::vector<QString> categories;

    // ######### TO COMPLETE #######
    bool isLoginCorrect;
    /*if(!isLoginCorrect)
        return false;*/

    switch(currentLoginRequest) {
        case CALCULATOR :
            view->currentPopup = view->calculator;
            view->calculator->launchCalculator();
            break;
        case EDIT_CUSTOMER :
            view->currentPopup = view->editCustomer;
            database.openDatabase();
            dbQueue = database.getCategories();
            while(!dbQueue.empty()){
                dbTuple = dbQueue.front();
                categories.push_back( QString::fromStdString( dbTuple.getCategoryName() ) );
                dbQueue.pop();
            }
            //categories.push_back("BAR");categories.push_back("2014");categories.push_back("2015");
            view->editCustomer->launchEditCustomer(*view_curCustomer, categories);

            database.closeDatabase();
            break;
        case DELETE_CUSTOMER :
            view->currentPopup = view->deleteCustomer;
            view->deleteCustomer->printDelete(*view_curCustomer);
            newText_Search(curSearch);
            break;
        case NEW_CUSTOMER :
            view->currentPopup = view->newCustomer;
            database.openDatabase();
            dbQueue = database.getCategories();
            while(!dbQueue.empty()){
                dbTuple = dbQueue.front();
                categories.push_back( QString::fromStdString( dbTuple.getCategoryName() ) );
                dbQueue.pop();
            }
            view->newCustomer->launchNewCustomer(categories);
            break;
        case ADD_STOCK :
            view->addStock->launchAddStock();
            break;
        case ADD_PRODUCT :
            view->addProduct->launchAddProduct();
            break;
        case EDIT_PRODUCT :
            view->editProduct->launchEditProduct();
            break;
        case ADMIN :
            AdminTuple tuple;
            view->admin->launchAdmin(tuple);
            break;
        default :
            return false;
    }
    return true;
}

void Controller::newClic_Calculator()
{
    view->currentPopup = view->login;
    view->login->checkGlobal();
    currentLoginRequest = CALCULATOR;
}

void Controller::newClic_IndividualHistory(unsigned id)
{
    view->currentPopup = view->individualHistory;
    view_histQueue CustomerHist;
    view_histTuple CustomerHistTuple;

    db_histQueue dbCustomerHist;
    db_histTuple dbCustomerHistTuple;

    database.openDatabase();
    dbCustomerHist = database.getCustomerHist(id);

    if ( !dbCustomerHist.empty() ){

        // Copy the dbQueue into the viewQueue
        while( !dbCustomerHist.empty() ){
            dbCustomerHistTuple = dbCustomerHist.front();

            CustomerHistTuple=dbCustomerHistTuple.transformIntoHistView();

            CustomerHist.push(CustomerHistTuple);
            dbCustomerHist.pop();
        }

    }
    // Send result to view

    view->individualHistory->launchIndividualHistory(CustomerHist);
    database.closeDatabase();
}

bool Controller::isNegativeAllowed()
{
    return negativeAllowed;
}

void Controller::setCurCustomer(view_customerTuple &tuple)
{
    curCustomer->setCustomerId((tuple.getCustomerId()));
    curCustomer->setBalance(tuple.getCustomerBalance());
    curCustomer->setFirstName(tuple.getCustomerFirstName().QString::toStdString());
    curCustomer->setCategory(tuple.getCustomerCategory());
    curCustomer->setName(tuple.getCustomerFirstName().QString::toStdString());
    curCustomer->setLogin(tuple.getCustomerLogin().QString::toStdString());
    view_curCustomer->setCustomerId((tuple.getCustomerId()));
    view_curCustomer->setCustomerBalance(tuple.getCustomerBalance());
    view_curCustomer->setCustomerFirstName(tuple.getCustomerFirstName());
    view_curCustomer->setCustomerCategory(tuple.getCustomerCategory());
    view_curCustomer->setCustomerName(tuple.getCustomerName());
    view_curCustomer->setCustomerLogin(tuple.getCustomerLogin());
}

void Controller::newClic_EditCustomer()
{
    view->currentPopup = view->login;
    view->login->checkGlobal();
    currentLoginRequest = EDIT_CUSTOMER;
}

void Controller::receiveCalculatorEntry(float amount)
{
    db_customerTuple dbTuple;
    database.openDatabase();

    curCustomer->setBalance( curCustomer->getBalance() + amount);

    dbTuple.setCustomerId(curCustomer->getCustomerId());
    dbTuple.setCustomerLogin(curCustomer->getLogin());
    dbTuple.setCustomerFirstname(curCustomer->getFirstName());
    dbTuple.setCustomerName(curCustomer->getName());
    dbTuple.setCustomerCategory(curCustomer->getCategory());
    dbTuple.setCustomerBalance(curCustomer->getBalance());

    database.editCustomerAccount(dbTuple);

    database.closeDatabase();

    /*TODO*/
    //Send updated information to view so it can display the new customer info
}

void Controller::receiveEditCustomerEntry(view_customerTuple& customer)
{
    // TO DEFINE
}

void Controller::newClic_DeleteCustomer()
{
    view->currentPopup = view->login;
    view->login->checkRoot();
    currentLoginRequest = DELETE_CUSTOMER;
}

void Controller::newClic_GlobalHistory()
{
    view->currentPopup = view->globalHistory;
    // CALL TO DB TO DEFINE

    view_histQueue queue;
    view->globalHistory->launchGlobalHistory(queue);
}

void Controller::newClic_NewCustomer()
{
    view->currentPopup = view->login;
    view->login->checkIndividual();
    currentLoginRequest = NEW_CUSTOMER;
}

void Controller::receiveNewCustomerEntry(view_customerTuple& customer)
{
    // TO COMPLETE
}

void Controller::newClic_AddStock()
{
    view->currentPopup = view->addStock;
    view->login->checkIndividual();
    currentLoginRequest = ADD_STOCK;
}

void Controller::receiveNewStocks(view_productQueue& products)
{
    // TO COMPLETE (additionnal stock is in stock attribute of the tuple)
}

void Controller::newClic_AddProduct()
{
    view->currentPopup = view->login;
    view->login->checkIndividual();
    currentLoginRequest = ADD_PRODUCT;
}

void Controller::receiveNewProduct(view_productTuple& product)
{
    // TO COMPLETE
}

void Controller::newClic_EditProduct()
{
    view->currentPopup = view->login;
    view->login->checkIndividual();
    currentLoginRequest = EDIT_PRODUCT;
}

void Controller::receiveEditProduct(view_productTuple& product)
{
    // TO COMPLETE (the ID in the tuple is the one used in DB)
}


bool Controller::newIndividualPassword(QString login, QString rootPasswd, QString passwd1, QString passwd2)
{
    if(passwd1 != passwd2 || passwd1.isEmpty() || rootPasswd.isEmpty() || login.isEmpty())
        return false;
    // ############ TO COMPLETE ##############

    return true;
}

bool Controller::newGlobalPassword(QString globalPasswd, QString passwd1, QString passwd2)
{
    if(passwd1 != passwd2 || passwd1.isEmpty() || globalPasswd.isEmpty())
        return false;
    // ############ TO COMPLETE ##############

    return true;
}

bool Controller::newRootPassword(QString rootPasswd, QString passwd1, QString passwd2)
{
    if(passwd1 != passwd2 || passwd1.isEmpty() || rootPasswd.isEmpty())
        return false;
    // ############ TO COMPLETE ##############

    return true;
}

void Controller::newClic_Stats()
{
    // Besoin de mettre un login ?
    view_statsTuple statsTuple;
    view_productQueue queues[NUMBER_OF_CATEGORIES];
    for(int i=0 ; i<NUMBER_OF_CATEGORIES ; i++)
        queues[i] = this->getProductsOfCategorie((unsigned)i);

    view->stats->launchStats(statsTuple, queues[0], queues[1], queues[2], queues[3], queues[4], queues[5]);

}

void Controller::newClic_Admin()
{
    view->currentPopup = view->admin;
    view->login->checkIndividual();
    currentLoginRequest = ADMIN;
}

void Controller::receiveAdminInfos(AdminTuple tuple)
{
    // TO COMPLETE
}
