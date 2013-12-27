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
typedef enum {CALCULATOR} LoginObjects;

class view_customerTuple;
class view_productTuple;

class db_histTuple
{
public:
    db_histTuple();

    void setHistId (unsigned _id);
    void setHistName (std::string _name);
    void setHistFirstname (std::string _firstname);
    void setHistProduct (std::string _product);
    void setHistDatetime (std::string _datetime);
    void setHistPrice (float _price);

    unsigned getHistId ();
    std::string getHistName();
    std::string getHistFirstname();
    std::string getHistProduct();
    std::string getHistDatetime();
    float getHistPrice();

private:
    unsigned id;
    std::string name;
    std::string firstname;
    std::string product;
    std::string datetime;
    float price;

};

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
    void setCustomerFirstname (QString _firstname);
    void setCustomerLogin (QString _login);
    void setCustomerCategory (unsigned _category);
    void setCustomerBalance (float _balance);

    unsigned getCustomerId ();
    QString getCustomerName();
    QString getCustomerFirstname();
    QString getCustomerLogin();
    unsigned getCustomerCategory();
    float getCustomerBalance();

    db_customerTuple transformIntoCustomerDb();

private:
    unsigned id;
    QString name;
    QString firstname;
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
    void setProductStock (unsigned stock);
    void setProductCategory (unsigned category);

    unsigned getProductId ();
    std::string getProductName();
    float getProductPrice();
    unsigned getProductStock();
    unsigned getProductCategory();

    view_productTuple transformIntoProductView();

private:
    unsigned id;
    std::string name;
    float price;
    unsigned stock;
    unsigned category;
};

class view_productTuple
{
public:
    void setProductId (unsigned _id);
    void setProductName (QString _name);
    void setProductPrice (float _price);
    void setProductStock (unsigned stock);
    void setProductCategory (unsigned category);

    unsigned getProductId ();
    QString getProductName();
    float getProductPrice();
    unsigned getProductStock();
    unsigned getProductCategory();

    db_productTuple transformIntoProductDb();

private:
    unsigned id;
    QString name;
    float price;
    unsigned stock;
    unsigned category;
};

class db_categoryTuple
{
public:
    db_categoryTuple();

    void setCategoryId(unsigned _id);
    void setCategoryName(std::string _name);

    unsigned getCategoryId();
    std::string getCategoryName();

private:
    unsigned id;
    std::string name;

};

typedef std::queue<db_histTuple> db_histQueue;
typedef std::queue<db_customerTuple> db_customerQueue;
typedef std::queue<view_customerTuple> view_customerQueue;
typedef std::queue<db_productTuple> db_productQueue;
typedef std::queue<view_productTuple> view_productQueue;
typedef std::queue<db_categoryTuple> db_categoryQueue;

typedef std::pair< std::vector< double > , std::vector< double > > db_dataarray;

class SearchResults;
class Calculator;
class CartDisplay;
class CartDisplayFrame;
class ConsoLogos;
class CustomerPanel;
class History;
class LeftPart;
class RightPart;
class Login;
class MainWindow;
class ProductsChoices;

typedef struct{
    Calculator* calculator;
    CartDisplay* cartDisplay;
    CartDisplayFrame* cartDisplayFrame;
    ConsoLogos* consoLogos;
    CustomerPanel* customerPanel;
    History* history;
    LeftPart* leftPart;
    RightPart* rightPart;
    Login* login;
    MainWindow* mainWindow;
    ProductsChoices* productChoices;
    SearchResults* searchResults;
} ViewObjects;

#endif // STRUCTURES_H
