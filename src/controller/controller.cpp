#include "controller.h"
#include "stock.h"
#include "searchresults.h"
#include "login.h"
#include "../model/database.h"
#include <QString>


Controller::Controller()
{
    /*Call here functions for the default display : allCustomers, history, productTypes ... */
    curCart = new Cart;
    curCustomer = new Customer;
    view_curCustomer = new view_customerTuple;
    database = new Database;
    plotting = new Plotting;
    database->openDatabase();
    consoTypes = database->getProdCategories();
    database->closeDatabase();
}

void Controller::setDb(sqlite3* handle)
{
    database->setHandle(handle);
}

sqlite3* Controller::getDb()
{
    return database->getHandle();
}

void Controller::setViewPointers(ViewObjects* viewObjects)
{
    /*viewSearchResults = par1;
    viewCustomerPanel = par2;
    viewCartDisplay = par3;
    viewHistory = par5;*/

    view = viewObjects;

    //mp_stock = new Stock( this, &database, par4 );
    mp_stock = new Stock( this, database, view->productChoices );
}

void Controller::mainController()
{
    QString emptyString;
    // Initialize view fields

    //TEST : Autodump de la BDD
    database->openDatabase();
    database->autoDumpHist();
    database->closeDatabase();

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


    database->openDatabase();
    dbQueue = database->searchCustomer(dbSearch);        // Get customer information corresponding to the search from model


    if ( !dbQueue.empty() ){

        // Copy the dbQueue into the viewQueue
        while( !dbQueue.empty() ){
            db_tmpCustomerInfo = dbQueue.front();
            //TEST sur l'id : NE PAS ENVOYER "VISITEUR/VISITEUR" A LA VUE
            int id=db_tmpCustomerInfo.getCustomerId();
            switch(id) {
            case 0:
                dbQueue.pop();
                break;
            default:
                view_tmpCustomerInfo=db_tmpCustomerInfo.transformIntoCustomerView();
                viewQueue.push(view_tmpCustomerInfo);
                dbQueue.pop();
                break;
            }
        }

    }
    // Sent result to view
    view->searchResults->setSearchResults(viewQueue );

    database->closeDatabase();

}

void Controller::newGlobal_Hist()
{
    view_histQueue HistoryQueue;
    view_histTuple HistoryTuple;

    db_histQueue dbHistoryQueue;
    db_histTuple dbHistoryTuple;

    database->openDatabase();
    dbHistoryQueue = database->getLastOperations(30);

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

    database->closeDatabase();

}

void Controller::newClic_Customer(unsigned int customerId)
{
    database->openDatabase();
    db_customerTuple tmp_dbCustomerInfo;
    view_customerTuple tmpViewCustomerInfo;

    tmp_dbCustomerInfo = database->getCustomerFromId( customerId );

    /* Create the customer */
    tmpViewCustomerInfo=tmp_dbCustomerInfo.transformIntoCustomerView();
    setCurCustomer(tmpViewCustomerInfo);
    view->customerPanel->setCustomer( tmpViewCustomerInfo );
    //view->customerPanel->setFuturBalance(tmpViewCustomerInfo.getCustomerBalance()); Ca sert à rien d'afficher deux fois la meme somme ...
    view->customerPanel->setFuturBalance(0,false); // on l'efface pour le nouveau client (reset)

    database->closeDatabase();

}

//void Controller::newClic_CustomerPanel(unsigned int buttonId)
//{
//    /*switch(buttonId){
//     case 0:

//    }*/
//}

void Controller::newClic_ValidateCart(bool isCash)
{
    // ###################### TO COMPLETE : cashModification #######################
    //
    //
    qDebug()<<"Received click to validate cart. Cash : " << isCash;

    //Inputs and outputs

    db_productTuple db_productInfo;
    QList<cartProduct> currentCartController;
    view_cartQueue displayCart;

    db_histTuple histToBeInserted;
    db_customerTuple customerToBeEdited;
    view_customerTuple editedCustomer;
    db_productTuple productToBeEdited;
    bool cashTrans=isCash;
    //Validation demandée :

    //-Getting informations


    currentCartController = curCart->getList();
    database->openDatabase();
    if (curCustomer->getCustomerId()==0)
    {
        cashTrans=true;
    }
    else
    {}

    for (int i=0; i<currentCartController.size();i++)
    {
        db_productInfo=database->getProductFromId(currentCartController[i].first);

        for (unsigned j=0;j<currentCartController.first().second;j++)
        {
            qDebug()<<"Creating a histTuple to insert into the database";

            histToBeInserted.setHistCustomerId(curCustomer->getCustomerId());
            histToBeInserted.setHistProductId(db_productInfo.getProductId());
            if(cashTrans)
                histToBeInserted.setHistPrice(0);
            else
                histToBeInserted.setHistPrice(db_productInfo.getProductPrice());
            qDebug()<<"Modif de l'hist";
            database->addHist(histToBeInserted);
        }

        if (!cashTrans)
        {
            qDebug()<<"Modification du compte débité";
            customerToBeEdited = database->getCustomerFromId(curCustomer->getCustomerId());
            customerToBeEdited.setCustomerBalance(curCustomer->getBalance()-curCart->getPrice());
            database->editCustomerAccount(customerToBeEdited);
        }

        qDebug()<<"Modification des stocks";
        productToBeEdited = db_productInfo;
        productToBeEdited.setProductStock(productToBeEdited.getProductStock()-currentCartController[i].second);
        database->editProduct(productToBeEdited);

    }

    editedCustomer = database->getCustomerFromId(curCustomer->getCustomerId()).transformIntoCustomerView();

    //update caisse if it is cash
    if(cashTrans)
    {
        db_finop_tuple finopTuple;
        finopTuple.setOpType(CASH);
        finopTuple.setOpValue(curCart->getPrice());
        database->addHistCashier(finopTuple);
        database->updateAccountValue(curCart->getPrice(), CAISSE);
    }

    database->closeDatabase();
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
    currentConsoTypeIndex = view_productTypeId;

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

    database->openDatabase();
    dbQueue = database->getProductsFromCategory(view_productTypeId);        // Get product information corresponding to the search from model

    if ( !dbQueue.empty() ){

        // Copy the dbQueue into the viewQueue
        while( !dbQueue.empty() ){
            db_tmpproductInfo = dbQueue.front();

            view_tmpproductInfo=db_tmpproductInfo.transformIntoProductView();

            viewQueue.push(view_tmpproductInfo);
            dbQueue.pop();
        }

    }
    database->closeDatabase();
    return viewQueue;
}

void Controller::newClic_Product(unsigned &view_productId)
{
    qDebug() << "Supposed to send only product n°" << view_productId;

    QList<cartProduct> currentCartController;

    view_cartQueue displayCart;
    view_cartTuple displayProd;

    db_productTuple db_productInfo;

    int id=curCustomer->getCustomerId();

    if (id==-1)
    {
        return ;
    }
    else
    {
        database->openDatabase();
        db_productInfo=database->getProductFromId(view_productId);

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
            db_productInfo=database->getProductFromId(currentCartController[i].first);
            displayProd.setCartCustomerId(curCustomer->getCustomerId());
            displayProd.setCartPrice(db_productInfo.getProductPrice());
            displayProd.setCartProdId(currentCartController[i].first);
            displayProd.setCartProdName(QString::fromStdString(db_productInfo.getProductName()));
            displayProd.setCartQuantity(currentCartController[i].second);

            displayCart.push(displayProd);
        }
        database->closeDatabase();
        // Send to view
        view->cartDisplay->setTotalPrice(curCart->getPrice());
        view->cartDisplay->setCart(displayCart);
        if(!VIEW.cartDisplay->getCash())
        {
            VIEW.customerPanel->setFuturBalance(curCustomer->getBalance()-curCart->getPrice());
        }
        else
            VIEW.customerPanel->setFuturBalance(0,false);
    }
}

bool Controller::view_isLoginCorrect(QString login, QString passwd, LoginType loginType)
{
    db_categoryQueue dbQueue;
    db_categoryTuple dbTuple;
    db_customerQueue dbCustQueue;
    AdminTuple adminTuple;
    std::vector<QString> categories;

    std::string _login;
    std::string _truepass;
    // ######### TO COMPLETE #######
    int isLoginIncorrect, sizeOfQueue;

    database->openDatabase();

    switch (loginType){
    case GLOBAL:
        _login="global";
        currentLoggedCustomer = "";
        break;
    case ROOT:
        _login="root";
        currentLoggedCustomer = "";
        break;
    case INDIVIDUAL:
        _login=login.toStdString();
        currentLoggedCustomer = _login;
        break;
    }
    _truepass= database->getPassword(_login);
    database->closeDatabase();

    isLoginIncorrect= _truepass.compare(passwd.toStdString());

    if(isLoginIncorrect)
    {
        return false;
    }

    else
    {
        switch(currentLoginRequest) {
        case CALCULATOR :
            view->currentPopup = view->calculator;
            view->calculator->launchCalculator();
            break;
        case EDIT_CUSTOMER :
            view->currentPopup = view->editCustomer;
            database->openDatabase();
            dbQueue = database->getCustCategories();
            database->closeDatabase();
            while(!dbQueue.empty()){
                dbTuple = dbQueue.front();
                categories.push_back( QString::fromStdString( dbTuple.getCategoryName() ) );
                dbQueue.pop();
            }
            //categories.push_back("BAR");categories.push_back("2014");categories.push_back("2015");
            view->editCustomer->launchEditCustomer(*view_curCustomer, categories);


            break;
        case DELETE_CUSTOMER :
            view->currentPopup = view->deleteCustomer;
            view->deleteCustomer->printDelete(*view_curCustomer);
            database->openDatabase();
            database->deleteCustomerAccount(curCustomer->getCustomerId());
            database->closeDatabase();
            newText_Search(curSearch);
            break;
        case NEW_CUSTOMER :
            view->currentPopup = view->newCustomer;
            database->openDatabase();
            dbQueue = database->getCustCategories();
            database->closeDatabase();
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
            database->openDatabase();
            dbCustQueue = database->getOldCustomers();
            sizeOfQueue = dbCustQueue.size();
            for(int i = 0 ; i < sizeOfQueue ; i++)
            {
                adminTuple.oldCustomers.push(dbCustQueue.front().transformIntoCustomerView());
                dbCustQueue.pop();
            }
            database->closeDatabase();
            view->admin->launchAdmin(adminTuple);
            break;
        case NEGATIVE_BALANCE :
            view->cartDisplay->validateNegativeCart();
            break;
        default :
            break;
        }
        currentLoginRequest = NONE;
        return true;
    }
}

void Controller::newClic_Calculator()
{
    int id=curCustomer->getCustomerId();

    if (id==-1) //A l'init, pas de curcustomer
    {
        return ;
    }
    else
    {
        view->currentPopup = view->login;
        view->login->checkGlobal();
        currentLoginRequest = CALCULATOR;
    }
}

void Controller::newClic_IndividualHistory()
{
    //
    int id=curCustomer->getCustomerId();

    if (id==-1)
    {
        return ;
    }
    else
    {
        //
        view->currentPopup = view->individualHistory;
        view_histQueue CustomerHist;
        view_histTuple CustomerHistTuple;

        db_histQueue dbCustomerHist;
        db_histTuple dbCustomerHistTuple;

        database->openDatabase();
        dbCustomerHist = database->getCustomerHist(id,false);

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
        database->closeDatabase();
    }
}

std::queue<QString> Controller::newCustCategoryList()
{
    db_categoryQueue DbCatList;
    db_categoryTuple DbCat;
    QString cat;
    database->openDatabase();
    DbCatList=database->getCustCategories();
    database->closeDatabase();
    std::queue<QString> result;
    result.push(QString("Tous")); // always present : Id -1

    if( !DbCatList.empty())
    {
        while( !DbCatList.empty() )
        {
            DbCat = DbCatList.front();
            cat=QString::fromStdString(DbCat.getCategoryName());
            result.push(cat);
            DbCatList.pop();
        }
    }
    return result;
}

bool Controller::isCustomerInNegative()
{
    return (curCustomer->getBalance() < 0);
}

void Controller::setCurCustomer(view_customerTuple &tuple)
{
    curCustomer->setCustomerId((tuple.getCustomerId()));
    curCustomer->setBalance(tuple.getCustomerBalance());
    curCustomer->setFirstName(tuple.getCustomerFirstName().QString::toStdString());
    curCustomer->setCategory(tuple.getCustomerCategory());
    curCustomer->setName(tuple.getCustomerName().QString::toStdString());
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
    int id=curCustomer->getCustomerId();

    if (id==-1)
    {
        return ;
    }
    else
    {
        view->currentPopup = view->login;
        view->login->checkGlobal();
        currentLoginRequest = EDIT_CUSTOMER;
    }
}

void Controller::receiveCalculatorEntry(float amount, bool isPaidByCard)
{
    db_customerTuple dbTuple;
    database->openDatabase();

    curCustomer->setBalance( curCustomer->getBalance() + amount);

    dbTuple.setCustomerId(curCustomer->getCustomerId());
    dbTuple.setCustomerLogin(curCustomer->getLogin());
    dbTuple.setCustomerFirstname(curCustomer->getFirstName());
    dbTuple.setCustomerName(curCustomer->getName());
    dbTuple.setCustomerCategory(curCustomer->getCategory());
    dbTuple.setCustomerBalance(curCustomer->getBalance());

    database->editCustomerAccount(dbTuple);

    // Ajout dans l'historique
    db_histTuple histToBeInserted;
    histToBeInserted.setHistCustomerId(curCustomer->getCustomerId());
    histToBeInserted.setHistProductId(0);
    histToBeInserted.setHistPrice(amount);
    qDebug()<<"Modif de l'hist";
    database->addHist(histToBeInserted);

    //Send updated information to view so it can display the new customer info
    newText_Search(curSearch);
    curCustomer->setBalance(curCustomer->getBalance() + amount);
    view_curCustomer->setCustomerBalance(view_curCustomer->getCustomerBalance() + amount);
    view->customerPanel->setCustomer(*view_curCustomer);
    database->closeDatabase();

    // refresh historique
    newGlobal_Hist();

    // update caisse / BDE
    database->openDatabase(); // if merge with the database opening above, crash appears ...
    db_finop_tuple finopTuple;
    finopTuple.setOpValue(amount);
    if(isPaidByCard)
    {
        finopTuple.setOpType(CB);
        database->transferToBDE(finopTuple);
        database->updateAccountValue(amount, BDE);
    }
    else
    {
        finopTuple.setOpType(CASH);
        database->addHistCashier(finopTuple);
        database->updateAccountValue(amount, CAISSE);
    }

    database->closeDatabase();
    if(currentLoggedCustomer != "")
    {
        std::string log;
        log = currentLoggedCustomer + " -> " + std::to_string(amount) + "€ to " + curCustomer->getFirstName() + " " + curCustomer->getName()+
                " (id:"+std::to_string(curCustomer->getCustomerId())+")";
        appendLog(log);
    }
}

void Controller::receiveEditCustomerEntry(view_customerTuple& customer)
{
    if(currentLoggedCustomer != "")
    {
        std::string log;
        log = currentLoggedCustomer + " -> changed " + curCustomer->getFirstName() + " " + curCustomer->getName()+ " " + std::to_string(curCustomer->getCategory()) +" (id " +
                std::to_string(curCustomer->getCustomerId()) + ", login :"+ curCustomer->getLogin() + ") to " + customer.getCustomerFirstName().toStdString()+
                " " + customer.getCustomerName().toStdString() + " " + std::to_string(customer.getCustomerCategory())+ " (login : " +
                customer.getCustomerLogin().toStdString()+ ")";
        appendLog(log);
    }

    curCustomer->setCategory(customer.getCustomerCategory());
    curCustomer->setFirstName(customer.getCustomerFirstName().toStdString());
    curCustomer->setLogin(customer.getCustomerLogin().toStdString());
    curCustomer->setName(customer.getCustomerName().toStdString());
    *view_curCustomer = curCustomer->getViewCustomer();

    db_customerTuple editedCustomer = curCustomer->getDbCustomer();
    database->openDatabase();
    database->editCustomerAccount(editedCustomer);
    database->closeDatabase();
    // GUI Update
    newText_Search(curSearch);
    view->customerPanel->setCustomer(*view_curCustomer);
}

void Controller::newClic_DeleteCustomer()
{
    int id=curCustomer->getCustomerId();

    if (id==-1)
    {
        return ;
    }
    else
    {
        view->currentPopup = view->login;
        view->login->checkRoot();
        currentLoginRequest = DELETE_CUSTOMER;
    }
}

void Controller::newClic_GlobalHistory()
{
    view->currentPopup = view->globalHistory;
    // CALL TO DB TO DEFINE
    view_histQueue viewQueue;
    db_histQueue dbQueue;
    view_histTuple viewTuple;
    db_histTuple dbTuple;
    // GO FETCH THE CONTENT OF THE HIST TABLE (ONLY CONTENTS AROUND 1000 ROWS WITH THE AUTODUMP)
    database->openDatabase();
    dbQueue=database->getFullHist();
    database->closeDatabase();

    while (!dbQueue.empty())
    {
        dbTuple=dbQueue.front();
        viewTuple=dbTuple.transformIntoHistView();
        viewQueue.push(viewTuple);

        dbQueue.pop();
    }
    view->globalHistory->launchGlobalHistory(viewQueue);
}

void Controller::newClic_NewCustomer()
{
    view->currentPopup = view->login;
    view->login->checkIndividual();
    currentLoginRequest = NEW_CUSTOMER;
}

void Controller::receiveNewCustomerEntry(view_customerTuple& customer, bool isCash)
{
    db_customerTuple dbTuple;
    db_finop_tuple finopTuple;
    finopTuple.setOpValue(customer.getCustomerBalance());

    database->openDatabase();
    dbTuple = customer.transformIntoCustomerDb();
    qDebug() << database->createCustomerAccount( dbTuple );
    // Updating caisse / BDE
    if(finopTuple.getOpValue() != 0)
    {
        if(isCash)
        {
            finopTuple.setOpType(CASH);
            database->addHistCashier(finopTuple);
            database->updateAccountValue(finopTuple.getOpValue(), CAISSE);
        }
        else
        {
            finopTuple.setOpType(CB);
            database->transferToBDE(finopTuple);
            database->updateAccountValue(finopTuple.getOpValue(), BDE);
        }
    }
    database->closeDatabase();
    if(currentLoggedCustomer != "")
    {
        std::string cash;
        if(isCash)
            cash="Paid with Cash";
        else
            cash = "Paid by Card";
        std::string log;
        log = currentLoggedCustomer + " -> created " + customer.getCustomerFirstName().toStdString()+
                " " + customer.getCustomerName().toStdString() + " " + std::to_string(customer.getCustomerCategory())+ " (login : " +
                customer.getCustomerLogin().toStdString()+ ") with account of " + std::to_string(customer.getCustomerBalance()) + "€ "+ cash;
        appendLog(log);
    }
}

void Controller::newClic_AddStock()
{
    view->currentPopup = view->addStock;
    view->login->checkIndividual();
    currentLoginRequest = ADD_STOCK;
}

void Controller::receiveNewStocks(view_productQueue& products)
{
    view_productTuple view_tuple;
    db_productTuple db_tuple;
    std::string stocks = "";
    unsigned n = products.size();

    database->openDatabase();
    for(unsigned i = 0 ; i < n ; i++)
    {
        view_tuple = products.front();
        products.pop();
        db_tuple = database->getProductFromId(view_tuple.getProductId());
        db_tuple.setProductStock(db_tuple.getProductStock() + view_tuple.getProductStock());
        database->editProduct(db_tuple);
        stocks += " - " + db_tuple.getProductName() + " " + std::to_string(db_tuple.getProductVolume())+ "cL"+ " : "+std::to_string(view_tuple.getProductStock());
    }
    database->closeDatabase();

    if(currentLoggedCustomer != "")
    {
        std::string log;
        log = currentLoggedCustomer + " -> added stocks " + stocks;
        appendLog(log);
    }
}

void Controller::newClic_AddProduct()
{
    view->currentPopup = view->login;
    view->login->checkIndividual();
    currentLoginRequest = ADD_PRODUCT;
}

void Controller::receiveNewProduct(view_productTuple& product)
{
    db_productTuple dbTuple;
    database->openDatabase();
    dbTuple = product.transformIntoProductDb();
    database->createProduct( dbTuple );
    // Should a confirmation popup be set by the view here, to inform the user of the success of the insertion ? => la flemme et le gars va surement vérifier de suite
    database->closeDatabase();
    // Par contre un refresh des produits serait pas mal du coup
    this->newClic_ProductTypes(currentConsoTypeIndex);

    if(currentLoggedCustomer != "")
    {
        std::string log;
        log = currentLoggedCustomer + " -> created " + std::to_string(product.getProductCategory()) + " "+product.getProductName().toStdString()+ " "+
                std::to_string(product.getProductVolume())+ "cL "+ std::to_string(product.getProductPrice())+ "€. Stock : " + std::to_string(product.getProductStock());
        appendLog(log);
    }
}

void Controller::newClic_EditProduct()
{
    view->currentPopup = view->login;
    view->login->checkIndividual();
    currentLoginRequest = EDIT_PRODUCT;
}

void Controller::receiveEditProduct(view_productTuple& product, bool deleteProduct)
{
    db_productTuple db_tuple;

    database->openDatabase();
    if(deleteProduct)
    {
        database->deleteProduct(product.getProductId());
        database->closeDatabase();

        if(currentLoggedCustomer != "")
        {
            std::string log;
            log = currentLoggedCustomer + " -> deleted product of category" + std::to_string(product.getProductCategory()) + " with id "+std::to_string(product.getProductId() );
            appendLog(log);
        }

        return;
    }
    db_tuple = product.transformIntoProductDb();
    database->editProduct(db_tuple);
    database->closeDatabase();
    // refresh de la gui
    this->newClic_ProductTypes(currentConsoTypeIndex);

    std::string log;
    log = currentLoggedCustomer + " -> edited product of " + std::to_string(product.getProductCategory()) + " with id " + std::to_string(product.getProductId()) + " into " +
            product.getProductName().toStdString()+ " "+std::to_string(product.getProductVolume())+ "cL "+std::to_string(product.getProductPrice())+ "€.";
    appendLog(log);
}


bool Controller::newIndividualPassword(QString login, QString rootPasswd, QString passwd1, QString passwd2)
{
    if(passwd1 != passwd2 || passwd1.isEmpty() || rootPasswd.isEmpty() || login.isEmpty())
        return false;

    database->openDatabase();
    std::string _login = "root";
    std::string currentRootPasswd = database->getPassword(_login);
    if(currentRootPasswd != rootPasswd.toStdString()) // Source de bug : A Hacher ?
        return false;

    database->setPassword(login.toStdString(), passwd1.toStdString());
    database->closeDatabase();
    return true;
}

bool Controller::newGlobalPassword(QString globalPasswd, QString passwd1, QString passwd2)
{
    if(passwd1 != passwd2 || passwd1.isEmpty() || globalPasswd.isEmpty())
        return false;

    database->openDatabase();
    std::string _login = "global";
    std::string currentGlobalPasswd = database->getPassword(_login);
    if(currentGlobalPasswd != globalPasswd.toStdString()) // Source de bug : A Hacher ?
        return false;

    database->setPassword(_login, passwd1.toStdString());
    database->closeDatabase();
    return true;
}

bool Controller::newRootPassword(QString rootPasswd, QString passwd1, QString passwd2)
{
    if(passwd1 != passwd2 || passwd1.isEmpty() || rootPasswd.isEmpty())
        return false;

    database->openDatabase();
    std::string _login = "root";
    std::string currentRootPasswd = database->getPassword(_login);
    if(currentRootPasswd != rootPasswd.toStdString()) // Source de bug : A Hacher ?
        return false;

    database->setPassword(_login, passwd1.toStdString());
    database->closeDatabase();
    return true;
}

void Controller::newClic_Stats()
{
    // Besoin de mettre un login ? => Non, Pourquoi ? C'est juste un accès en lecture et le bar n'est pas une secte.
    view_statsTuple statsTuple;
    db_customerTuple custTuple;
    std::string emptyString;
    database->openDatabase();
    db_categoryQueue prodCatQueue = database->getProdCategories();
    database->closeDatabase();
    int NUMBER_OF_CATEGORIES = prodCatQueue.size();
    view_productQueue queues[NUMBER_OF_CATEGORIES];
    for(int i=0 ; i<NUMBER_OF_CATEGORIES ; i++)
        queues[i] = this->getProductsOfCategorie((unsigned)i + 1); // 0 is reserved for +/-
    database->openDatabase();
    db_customerQueue custQueue = database->searchCustomer(emptyString);
    db_productQueue prodQueue = database->getAllProducts();
    statsTuple.moneyInCashRegister = database->getAccountValue(CAISSE);
    database->closeDatabase();
    statsTuple.numberOfCustomers = custQueue.size();
    statsTuple.numberOfProducts = prodQueue.size();
    statsTuple.accountsTotal = 0;
    for(unsigned i = 0 ; i < statsTuple.numberOfCustomers ; i++)
    {
        custTuple = custQueue.front();
        custQueue.pop();
        statsTuple.accountsTotal += custTuple.getCustomerBalance();
    }

    database->openDatabase();
    db_finop_queue finopQueue = database->getBDEHist(0);
    db_finop_tuple finopTuple;
    unsigned queueSize = finopQueue.size();
    statsTuple.moneyGivenThisYear = 0;
    // Calcul de l'argent amené au bde cette année civile
    for(unsigned i =0 ; i < queueSize ; i++)
    {
        finopTuple = finopQueue.front();
        finopQueue.pop();
        statsTuple.moneyGivenThisYear += finopTuple.getOpValue();
    }
    // close and open maybe useless
    database->closeDatabase();
    database->openDatabase();
    // calcul pour l'année dernière
    time_t currentTime = time(NULL);
    tm* timePtr = localtime(&currentTime);
    finopQueue = database->getBDEHist(timePtr->tm_year +1900 - 1); // year starts at 1900
    queueSize = finopQueue.size();
    statsTuple.moneyGivenLastYear = 0;
    for(unsigned i =0 ; i < queueSize ; i++)
    {
        finopTuple = finopQueue.front();
        finopQueue.pop();
        statsTuple.moneyGivenLastYear += finopTuple.getOpValue();
    }
    database->closeDatabase();

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
    if(tuple.cashTransfered != 0)
    {
        db_finop_tuple finopTuple;
        finopTuple.setOpValue(tuple.cashTransfered);
        finopTuple.setOpType(CASH);
        database->openDatabase();
        database->transferToBDE(finopTuple);
        database->updateAccountValue(tuple.cashTransfered, BDE);
        database->updateAccountValue(-tuple.cashTransfered, CAISSE);
        database->closeDatabase();

        std::string log;
        log = currentLoggedCustomer + " -> transfered " + std::to_string(tuple.cashTransfered) + "€ to the BDE";
        appendLog(log);
    }
    if(tuple.newCustCategoryName != "")
    {
        db_categoryTuple catTuple;
        catTuple.setCategoryId(tuple.custCategoryID);
        catTuple.setCategoryName(tuple.newCustCategoryName);
        database->openDatabase();
        database->editCustCategory(catTuple);
        database->openDatabase();

        std::string log;
        log = currentLoggedCustomer + " -> changed name of customer category (" + std::to_string(catTuple.getCategoryId()) + ") to "+catTuple.getCategoryName();
        appendLog(log);
    }
    if(tuple.newProdCategoryName != "")
    {
        db_categoryTuple catTuple;
        catTuple.setCategoryId(tuple.prodCategoryID);
        catTuple.setCategoryName(tuple.newProdCategoryName);
        database->openDatabase();
        database->editProdCategory(catTuple);
        database->openDatabase();

        std::string log;
        log = currentLoggedCustomer + " -> changed name of product category (" + std::to_string(catTuple.getCategoryId()) + ") to "+catTuple.getCategoryName();
        appendLog(log);
    }
}

void Controller::newClic_Category(int id)
{
    QString emptyString;qDebug() << id;
    switch (id) {
    case -1: // for all
        newText_Search(emptyString);
        break;
    default:
        // Inputs and outputs
        std::string dbSearch;
        view_customerTuple view_tmpCustomerInfo;
        db_customerTuple db_tmpCustomerInfo;
        db_customerQueue dbQueue;
        view_customerQueue viewQueue;

        database->openDatabase();
        dbQueue = database->getCustomerFromCategory(id);        // Get customer information corresponding to the search from model

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

        database->closeDatabase();
        break;
    }
}

void Controller::displayProductGraph(int id, bool consumption)
{
    db_dataarray datas;
    database->openDatabase();
    plotting->setDb(database->getHandle());
    db_productTuple db_product = database->getProductFromId(id);
    database->closeDatabase();
    QString title;
    if(consumption)
    {
        database->openDatabase();
        plotting->setDb(database->getHandle());

        datas = plotting->productConsumption(id, 10, 100);
        title = "Evolution de la consommation de "+ QString::fromStdString(db_product.getProductName())+
                " "+QString::number(db_product.getProductVolume())+"cL"+" au cours du temps.";
        view->mainWindow->setGraph(datas, "Temps", "Consommation en unité (L pour la pression)", title);
    }
    else
    {
        //database->openDatabase();
        plotting->setDb(database->getHandle());

        datas = plotting->productStock(id, 10, 100);
        title = "Evolution des stocks de "+ QString::fromStdString(db_product.getProductName())+
                " "+QString::number(db_product.getProductVolume())+"cL"+" au cours du temps.";
        view->mainWindow->setGraph(datas, "Temps", "Stocks en unité (L pour la pression)", title);
    }
}

void Controller::newClic_GlobalHistory_old()
{
    // To define
}

void Controller::newClic_IndividualHistory_old(int customerId)
{
    // To define
}

void Controller::newClic_IndividualGraph(int customerId)
{
    // To define
}

std::string Controller::xorCrypt(std::string input)
{
    // Here is defined the key
    char key[] = "R@b&";
    int nKey=0;
    while(key[nKey] != '\0')
        nKey++;

    int n = input.size();
    const char *buffer;
    char tmpBuffer;
    char *cryptedBuffer;
    cryptedBuffer = new char[input.size() + 1]; // +1 for \0
    buffer = input.c_str();
    for(int i = 0 ; i < n ; i++)
    {
        if(buffer[i] != -1) // If there is a -1 (very rare character), it might be the one inserted because there was a 0 in crypted string. So it is replaced by a 0
            tmpBuffer = buffer[i];
        else
            tmpBuffer = 0;
        cryptedBuffer[i] = key[i % nKey] ^ tmpBuffer;
        if(cryptedBuffer[i] == '\0') // To avoid any cut of the string : '\0' means end of the string in char*
            cryptedBuffer[i] = -1;
    }
    cryptedBuffer[n] = '\0';
    std::string output(cryptedBuffer);

    delete[] cryptedBuffer;
    return output;
}

void Controller::appendLog(std::string log)
{
    time_t currentTime = time(NULL);
    tm* timePtr = localtime(&currentTime);
    char month_year[10];
    if(timePtr->tm_mon < 9) // tm_mon starts at 0 for january
        sprintf(month_year, "%d-0%d", timePtr->tm_year + 1900, timePtr->tm_mon+1); // year count start at year 1900 & there is a 0 before month to keep always 2 number. Eg 2014-03 and not 2014-3
    else
        sprintf(month_year, "%d-%d", timePtr->tm_year + 1900, timePtr->tm_mon+1); // year count start at year 1900
    std::string path = GLOBAL_PATH.toStdString();
    path += "resources/system_files/";
    path += month_year;
    path += ".txt";
    std::string date(asctime(timePtr));
    date.pop_back(); // suppression du retour à la ligne
    log = date + " " + log;

    // lecture de l'ensemble pour décryptage afin d'insérer la nouvelle ligne
    FILE* logFile = fopen(path.c_str(), "r");
    fseek(logFile,0,SEEK_END);
    long sizeOfLog = ftell(logFile);
    char *buffer = (char*) malloc((sizeOfLog+1)*sizeof(char));
    fseek(logFile,0,SEEK_SET); std::cout << "avant:" << ftell(logFile) << " : " << buffer << std::endl;
    fread(buffer, sizeof(char), sizeOfLog, logFile);
    fclose(logFile);
    buffer[sizeOfLog] = '\0';
    std::string logCrypted(buffer);std::cout << "apres:" << logCrypted << std::endl;
    std::string logUncrpyted = xorCrypt(logCrypted);
    logUncrpyted += log + '\n';
    logCrypted = xorCrypt(logUncrpyted);

    // Ecriture de l'ensemble crypté dans le fichier
    logFile = fopen(path.c_str(), "w");
    fwrite(logCrypted.c_str(), sizeof(char), logCrypted.size(), logFile);
    fclose(logFile);
}

QString Controller::getLog(int month, int year)
{
    QString log;
    std::string cryptedLog, path, monthStr;
    char *buffer;
    if(month < 10)
        monthStr = "0" + std::to_string(month);
    else
        monthStr = std::to_string(month);
    path = GLOBAL_PATH.toStdString() + "resources/system_files/" + std::to_string(year) + "-" + monthStr + ".txt";
    FILE* file = fopen(path.c_str(), "r");
    fseek(file,0,SEEK_END);
    long sizeOfLog = ftell(file);
    buffer = (char*) malloc((sizeOfLog+1)*sizeof(char));
    fseek(file,0,SEEK_SET);
    fread(buffer, sizeof(char), sizeOfLog, file);
    fclose(file);
    buffer[sizeOfLog] = '\0';
    cryptedLog.assign(buffer);
    log = QString::fromStdString(xorCrypt(cryptedLog));
    return log;
}
