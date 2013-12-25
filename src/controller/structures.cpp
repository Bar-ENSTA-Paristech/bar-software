#include<stdio.h>
#include<stdlib.h>
#include<QString>

#include"structures.h"


db_histTuple::db_histTuple()
{
}

void db_histTuple::setHistId(unsigned _id)
{
    id=_id;
}

void db_histTuple::setHistName(std::string _name)
{
    name=_name;
}

void db_histTuple::setHistFirstname(std::string _firstname)
{
    firstname=_firstname;
}

void db_histTuple::setHistDatetime(std::string _datetime)
{
    datetime=_datetime;
}

void db_histTuple::setHistPrice(float _price)
{
    price=_price;
}

void db_histTuple::setHistProduct(std::string _product)
{
    product=_product;
}

unsigned db_histTuple::getHistId()
{
    return id;
}

std::string db_histTuple::getHistName()
{
    return name;
}

std::string db_histTuple::getHistFirstname()
{
    return firstname;
}

std::string db_histTuple::getHistDatetime()
{
    return datetime;
}

float db_histTuple::getHistPrice()
{
    return price;
}

std::string db_histTuple::getHistProduct()
{
    return product;
}

// Fin de la classe db_histTuple

db_customerTuple::db_customerTuple()
{
}

void db_customerTuple::setCustomerId(unsigned _id)
{
    id=_id;
}

void db_customerTuple::setCustomerName(std::string _name)
{
    name=_name;
}

void db_customerTuple::setCustomerFirstname(std::string _firstname)
{
    firstname=_firstname;
}

void db_customerTuple::setCustomerLogin(std::string _login)
{
    login=_login;
}

void db_customerTuple::setCustomerBalance(float _balance)
{
    balance=_balance;
}

void db_customerTuple::setCustomerCategory(unsigned _category)
{
    category=_category;
}

unsigned db_customerTuple::getCustomerId()
{
    return id;
}

std::string db_customerTuple::getCustomerName()
{
    return name;
}

std::string db_customerTuple::getCustomerFirstname()
{
    return firstname;
}

std::string db_customerTuple::getCustomerLogin()
{
    return login;
}

float db_customerTuple::getCustomerBalance()
{
    return balance;
}

unsigned db_customerTuple::getCustomerCategory()
{
    return category;
}

view_customerTuple db_customerTuple::transformIntoCustomerView()
{
    view_customerTuple result;

    result.setCustomerBalance(balance);
    result.setCustomerCategory(category);
    result.setCustomerFirstname(QString::fromStdString(firstname));
    result.setCustomerId(id);
    result.setCustomerLogin(QString::fromStdString(login));
    result.setCustomerName(QString::fromStdString(name));

    return result;
}

//fin de la classe db_customerTuple

view_customerTuple::view_customerTuple()
{
}

void view_customerTuple::setCustomerId(unsigned _id)
{
    id=_id;
}

void view_customerTuple::setCustomerName(QString _name)
{
    name=_name;
}

void view_customerTuple::setCustomerFirstname(QString _firstname)
{
    firstname=_firstname;
}

void view_customerTuple::setCustomerLogin(QString _login)
{
    login=_login;
}

void view_customerTuple::setCustomerBalance(float _balance)
{
    balance=_balance;
}

void view_customerTuple::setCustomerCategory(unsigned _category)
{
    category=_category;
}

unsigned view_customerTuple::getCustomerId()
{
    return id;
}

QString view_customerTuple::getCustomerName()
{
    return name;
}

QString view_customerTuple::getCustomerFirstname()
{
    return firstname;
}

QString view_customerTuple::getCustomerLogin()
{
    return login;
}

float view_customerTuple::getCustomerBalance()
{
    return balance;
}

unsigned view_customerTuple::getCustomerCategory()
{
    return category;
}

db_customerTuple view_customerTuple::transformIntoCustomerDb()
{
    db_customerTuple result;

    result.setCustomerBalance(balance);
    result.setCustomerCategory(category);
    result.setCustomerFirstname(firstname.QString::toStdString());
    result.setCustomerId(id);
    result.setCustomerLogin(login.QString::toStdString());
    result.setCustomerName(name.QString::toStdString());

    return result;
}

//fin de la class view_customerTuple

db_productTuple::db_productTuple()
{
}

void db_productTuple::setProductId(unsigned _id)
{
    id=_id;
}

void db_productTuple::setProductName(std::string _name)
{
    name=_name;
}

void db_productTuple::setProductPrice(float _price)
{
    price=_price;
}

void db_productTuple::setProductStock(unsigned _stock)
{
    stock=_stock;
}

void db_productTuple::setProductCategory(unsigned _category)
{
    category=_category;
}

unsigned db_productTuple::getProductId()
{
    return id;
}

std::string db_productTuple::getProductName()
{
    return name;
}


float db_productTuple::getProductPrice()
{
    return price;
}

unsigned db_productTuple::getProductStock()
{
    return stock;
}

unsigned db_productTuple::getProductCategory()
{
    return category;
}

view_productTuple db_productTuple::transformIntoProductView()
{
    view_productTuple result;

    result.setProductId(id);
    result.setProductName(QString::fromStdString(name));
    result.setProductPrice(price);
    result.setProductStock(stock);
    result.setProductCategory(category);

    return result;
}

//fin de la class db_productTuple

void view_productTuple::setProductId(unsigned _id)
{
    id=_id;
}

void view_productTuple::setProductName(QString _name)
{
    name=_name;
}

void view_productTuple::setProductPrice(float _price)
{
    price=_price;
}

void view_productTuple::setProductStock(unsigned _stock)
{
    stock=_stock;
}

void view_productTuple::setProductCategory(unsigned _category)
{
    category=_category;
}

unsigned view_productTuple::getProductId()
{
    return id;
}

QString view_productTuple::getProductName()
{
    return name;
}

float view_productTuple::getProductPrice()
{
    return price;
}

unsigned view_productTuple::getProductStock()
{
    return stock;
}

unsigned view_productTuple::getProductCategory()
{
    return category;
}

db_productTuple view_productTuple::transformIntoProductDb()
{
    db_productTuple result;

    result.setProductId(id);
    result.setProductName(name.QString::toStdString());
    result.setProductPrice(price);
    result.setProductStock(stock);
    result.setProductCategory(category);

    return result;
}
//fin de la class view_producttuple


db_categoryTuple::db_categoryTuple()
{
}


void db_categoryTuple::setCategoryId(unsigned _id)
{
    id=_id;
}

void db_categoryTuple::setCategoryName(std::string _name)
{
    name=_name;
}

unsigned db_categoryTuple::getCategoryId()
{
    return id;
}

std::string db_categoryTuple::getCategoryName()
{
    return name;
}
