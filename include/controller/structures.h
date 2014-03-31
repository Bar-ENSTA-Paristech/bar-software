#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>
#include <QString>
#include <stdlib.h>
#include <queue>



//TUPLE model du consommateur : Nom, Prénom ,Login, Catégorie , balance , id
//typedef std::tuple<  std::string, std::string, std::string , std::string, float, unsigned > db_customerTuple;
//TUPLE view du consommateur : Nom, Prénom , Catégorie , balance , id
//typedef std::tuple< QString, QString, QString, float, unsigned/*,QString*/ > view_customerTuple;
//TUPLE model du produit : Produit, Catégorie , prix ,stock , id
//typedef std::tuple< std::string, unsigned, float , unsigned, unsigned > db_consoTuple;
//TUPLE view du produit : Produit, prix, quantity
//typedef std::tuple<QString, float, unsigned int> view_productTuple;
//TUPLE model d'un historique (une transaction) : Nom, Prénom, Produit, Date, valeur
//typedef std::tuple< std::string,std::string,std::string,std::string , float> db_histTuple;

//On définit les structures de queue<> correspondant à chaque type de tuple
//typedef std::queue<db_customerTuple> db_customerQueue;
//typedef std::queue<db_consoTuple> db_consoQueue;
//typedef std::queue<db_histTuple> db_histQueue;
//typedef std::queue<view_customerTuple> view_customerQueue;
//typedef std::queue<view_productTuple> view_productQueue;

typedef enum {INDIVIDUAL, GLOBAL, ROOT} LoginType;
typedef enum {NONE, CALCULATOR, EDIT_CUSTOMER, DELETE_CUSTOMER, NEW_CUSTOMER, ADD_STOCK, ADD_PRODUCT, EDIT_PRODUCT,
              ADMIN, NEGATIVE_BALANCE} LoginObjects;
typedef enum {CASH,CHEQUE,CB,BILL}PaymentType;
typedef enum {BDE=1,CAISSE=2}Account;

class view_customerTuple;
class view_productTuple;
class view_histTuple;

class db_customerTuple
{
public :
    db_customerTuple();

    void setCustomerId (unsigned _id);
    void setCustomerName (std::string _name);
    void setCustomerFirstname (std::string _firstname);
    void setCustomerLogin (std::string _login);
    void setCustomerCategory (unsigned category);
    void setCustomerBalance (float _balance);

    unsigned getCustomerId ();
    std::string getCustomerName();
    std::string getCustomerFirstname();
    std::string getCustomerLogin();
    unsigned getCustomerCategory();
    float getCustomerBalance();

    view_customerTuple transformIntoCustomerView();


private:
    unsigned id;
    std::string name;
    std::string firstname;
    std::string login;
    unsigned category;
    float balance;
};

class view_customerTuple
{
public :
    view_customerTuple();

    void setCustomerId (unsigned _id);
    void setCustomerName (QString _name);
    void setCustomerFirstName (QString _firstName);
    void setCustomerLogin (QString _login);
    void setCustomerCategory (unsigned _category);
    void setCustomerBalance (float _balance);

    unsigned getCustomerId ();
    QString getCustomerName();
    QString getCustomerFirstName();
    QString getCustomerLogin();
    unsigned getCustomerCategory();
    float getCustomerBalance();

    db_customerTuple transformIntoCustomerDb();

private:
    unsigned id;
    QString name;
    QString firstName;
    QString login;
    unsigned category;
    float balance;
};

class db_productTuple
{
public:
    db_productTuple();

    void setProductId (unsigned _id);
    void setProductName (std::string _name);
    void setProductPrice (float _price);
    void setProductStock (int stock);
    void setProductVolume(unsigned _volume){volume=_volume;}
    void setProductCategory (unsigned category);
    void setProductTVAcat (int _TVA);

    unsigned getProductId ();
    std::string getProductName();
    float getProductPrice();
    int getProductStock();
    unsigned getProductVolume(){return volume;}
    unsigned getProductCategory();
    int getProductTVAcat();

    view_productTuple transformIntoProductView();

private:
    unsigned id;
    std::string name;
    float price;
    int TVAcat;
    int stock;
    unsigned volume;
    unsigned category;
};

class view_productTuple
{
public:
    void setProductId (unsigned _id);
    void setProductName (QString _name);
    void setProductPrice (float _price);
    void setProductStock (int stock);
    void setProductCategory (unsigned category);
    void setProductVolume(unsigned _volume);
    void setProductTVAcat (int _TVA);

    unsigned getProductId ();
    QString getProductName();
    float getProductPrice();
    int getProductStock();
    unsigned getProductCategory();
    unsigned getProductVolume();
    int getProductTVAcat();

    db_productTuple transformIntoProductDb();

private:
    unsigned id;
    QString name;
    float price;
    int stock;
    unsigned volume;
    unsigned category;
    int TVAcat;
};

class db_categoryTuple
{
public:
    db_categoryTuple();

    void setCategoryId(int _id);
    void setCategoryName(std::string _name);

    int getCategoryId();
    std::string getCategoryName();

private:
    int id;
    std::string name;

};

class db_histTuple
{
public:
    void setHistId (unsigned _id);
    void setHistDate (std::string _date);
    void setHistName (std::string _name);
    void setHistPrice (float _price);
    void setHistFirstName (std::string firstName);
    void setHistOperation (std::string operation);
    void setHistCustomerId (unsigned _id);
    void setHistProductId (unsigned _id);

    int getHistId();
    std::string getHistDate ();
    std::string getHistName();
    float getHistPrice();
    std::string getHistFirstName();
    std::string getHistOperation();
    unsigned getHistCustomerId();
    unsigned getHistProduct_Id();

    view_histTuple transformIntoHistView();

private:
    unsigned id;
    std::string date;
    std::string name;
    float price;
    std::string firstName;
    std::string operation;
    unsigned customer_id;
    unsigned product_id;
};

class view_histTuple
{
public:
    void setHistId (unsigned _id);
    void setHistDate (QString _date);
    void setHistName (QString _name);
    void setHistPrice (float _price);
    void setHistFirstName (QString firstName);
    void setHistOperation (QString operation);

    unsigned getHistId();
    QString getHistDate ();
    QString getHistName();
    float getHistPrice();
    QString getHistFirstName();
    QString getHistOperation();

    db_histTuple transformIntoHistDb();

private:
    unsigned id;
    QString date;
    QString name;
    float price;
    QString firstName;
    QString operation;
};

class view_cartTuple
{
public:
    void setCartProdId (unsigned _id);
    void setCartCustomerId (unsigned _id);
    void setCartProdName (QString _string);
    void setCartQuantity (unsigned _qty);
    void setCartPrice (float _price);

    unsigned getCarProdId();
    unsigned getCartCustomerId();
    unsigned getCartQuantity();
    float getCartPrice();
    QString getCartProdName();

private:
    unsigned product_id;
    unsigned customer_id;
    QString conso_name;
    unsigned quantity;
    float price;
};

class view_statsTuple
{
public:
    float accountsTotal;
    float moneyInCashRegister;
    float moneyGivenThisYear;
    float moneyGivenLastYear;
    float totalSoldThisYear;
    float totalSoldThisYearTVA1;
    float totalSoldThisYearTVA2;
    float totalSoldThisYearTVA3;
    float totalSoldLastYear;
    float totalSoldLastYearTVA1;
    float totalSoldLastYearTVA2;
    float totalSoldLastYearTVA3;
    unsigned numberOfCustomers;
    unsigned numberOfProducts;
};

class db_finop_tuple
{
public:
    void setOpId (int _id);
    void setOpType (PaymentType _type);
    void setOpValue (float _value);
    void setOpDate (std::string date);

    int getOpId ();
    PaymentType getOpType ();
    float getOpValue ();
    std::string getOpDate();

private:
    int id;
    PaymentType P_type;
    float value;
    std::string date;
};

class db_commandTuple
{
public:
    void setId (int _id);
    void setProd_id (int _prod_id);
    void setProd_qty (int _prod_qty);
    void setDate (std::string _date);

    int getId();
    int getProd_id();
    int getProd_qty ();
    std::string getDate();

private:
    int id;
    int prod_id;
    int prod_qty;
    std::string date;

};

class db_TVAcategoryTuple
{
public:
    void setId (int _id){id= _id;}
    void setRate(float _value){value = _value;}
    void setInfo(std::string _info){info = _info;}

    int getId (){return id;}
    float getRate(){return value;}
    std::string getInfo(){return info;}

private:
    int id;
    float value;
    std::string info;
};

class db_comTuple
{
public:
    void setId (int _id){id= _id;}
    void setTVA(float _TVA){TVA = _TVA;}
    void setTTC(float _TTC){TTC = _TTC;}
    void setInfo(std::string _info){info = _info;}
    void setDate(std::string _date){date = _date;}


    int getId (){return id;}
    float getTVA(){return TVA;}
    float getTTC(){return TTC;}
    std::string getInfo(){return info;}
    std::string getDate(){return date;}


private:
    int id;
    float TVA;
    float TTC;
    std::string date;
    std::string info;
};

class db_saleTuple
{
public:
    void setId (int _id){id= _id;}
    void setTVAIndex (int _TVAIndex){TVAIndex= _TVAIndex;}
    void setTVA(float _TVA){TVA = _TVA;}
    void setTTC(float _TTC){TTC = _TTC;}
    void setDate(std::string _date){date = _date;}
    void setProductName(std::string _productName){ProductName = _productName;}

    int getId (){return id;}
    int getTVAIndex (){return TVAIndex;}
    float getTVA(){return TVA;}
    float getTTC(){return TTC;}
    std::string getProductName(){return ProductName;}
    std::string getDate(){return date;}

private:
    int id;
    float TTC;
    float TVA;
    int TVAIndex;
    std::string date;
    std::string ProductName;
};

typedef std::queue<db_histTuple> db_histQueue;
typedef std::queue<db_customerTuple> db_customerQueue;
typedef std::queue<view_customerTuple> view_customerQueue;
typedef std::queue<db_productTuple> db_productQueue;
typedef std::queue<view_productTuple> view_productQueue;
typedef std::queue<db_categoryTuple> db_categoryQueue;
typedef std::queue<view_histTuple> view_histQueue;
typedef std::queue<db_histTuple> db_histQueue;
typedef std::queue<view_cartTuple> view_cartQueue;
typedef std::queue<db_finop_tuple> db_finop_queue;
typedef std::queue<db_commandTuple> db_commandQueue;
typedef std::queue<db_TVAcategoryTuple> db_TVAcategoryQueue;
typedef std::queue<db_comTuple> db_comQueue;
typedef std::queue<db_saleTuple> db_saleQueue;

typedef std::pair< std::vector< double > , std::vector< double > > db_dataarray;

class SearchResults;
class Admin;
class AddProduct;
class AddStock;
class Calculator;
class CartDisplay;
class CartDisplayFrame;
class ConsoLogos;
class CustomerPanel;
class DeleteCustomer;
class EditCustomer;
class EditLogin;
class EditProduct;
class GlobalHistory;
class History;
class LeftPart;
class RightPart;
class Login;
class MainWindow;
class NewCustomer;
class Popup;
class ProductsChoices;
class Stats;
class ViewStocks;
class IndividualHistory;
class IndividualHistoryList;

typedef struct{
    Admin* admin;
    AddProduct* addProduct;
    AddStock* addStock;
    Calculator* calculator;
    CartDisplay* cartDisplay;
    CartDisplayFrame* cartDisplayFrame;
    ConsoLogos* consoLogos;
    CustomerPanel* customerPanel;
    DeleteCustomer* deleteCustomer;
    EditCustomer* editCustomer;
    EditLogin* editLogin;
    EditProduct* editProduct;
    GlobalHistory* globalHistory;
    GlobalHistory* globalHistory_old;
    History* history;
    IndividualHistoryList* individualHistoryList;
    IndividualHistory* individualHistory;
    IndividualHistory* individualHistory_old;
    LeftPart* leftPart;
    RightPart* rightPart;
    Login* login;
    MainWindow* mainWindow;
    NewCustomer* newCustomer;
    Popup* currentPopup;
    ProductsChoices* productChoices;
    SearchResults* searchResults;
    Stats* stats;
    ViewStocks* viewStocks;
} ViewObjects;

typedef struct{
    float cashTransfered;
    view_customerQueue oldCustomers;
    int custCategoryID;
    int prodCategoryID;
    std::string newCustCategoryName;
    std::string newProdCategoryName;
    db_TVAcategoryTuple tvaTuple;
}AdminTuple;

#endif // STRUCTURES_H
