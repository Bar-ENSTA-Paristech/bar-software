#include<stdio.h>
#include<stdlib.h>
#include<QString>

#include"structures.h"


// ##################################
// DB_CUSTOMERTUPLE
// ##################################

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
    result.setCustomerFirstName(QString::fromStdString(firstname));
    result.setCustomerId(id);
    result.setCustomerLogin(QString::fromStdString(login));
    result.setCustomerName(QString::fromStdString(name));

    return result;
}


// ##################################
// VIEW_CUSTOMERTUPLE
// ##################################
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

void view_customerTuple::setCustomerFirstName(QString _firstname)
{
    firstName=_firstname;
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

QString view_customerTuple::getCustomerFirstName()
{
    return firstName;
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
    result.setCustomerFirstname(firstName.QString::toStdString());
    result.setCustomerId(id);
    result.setCustomerLogin(login.QString::toStdString());
    result.setCustomerName(name.QString::toStdString());

    return result;
}


// ##################################
// DB_PRODUCTTUPLE
// ##################################

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

// ##################################
// DB_PRODUCTTUPLE
// ##################################

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

void view_productTuple::setProductStock(int _stock)
{
    stock=_stock;
}

void view_productTuple::setProductCategory(unsigned _category)
{
    category=_category;
}

void view_productTuple::setProductVolume(unsigned _volume)
{
    volume = _volume;
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

int view_productTuple::getProductStock()
{
    return stock;
}

unsigned view_productTuple::getProductCategory()
{
    return category;
}

unsigned view_productTuple::getProductVolume()
{
    return volume;
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


// ##################################
// DB_CATEGORYTUPLE
// ##################################

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

// ##################################
// VIEW_HISTTUPLE
// ##################################

void view_histTuple::setHistId(unsigned _id)
{
    id=_id;
}

void view_histTuple::setHistDate(QString _date)
{
    date=_date;
}

void view_histTuple::setHistName(QString _name)
{
    name=_name;
}

void view_histTuple::setHistPrice(float _price)
{
    price=_price;
}

void view_histTuple::setHistFirstName(QString _firstName)
{
    firstName = _firstName;
}

void view_histTuple::setHistOperation(QString _operation)
{
    operation = _operation;
}

unsigned view_histTuple::getHistId()
{
    return id;
}

QString view_histTuple::getHistDate()
{
    return date;
}

QString view_histTuple::getHistName()
{
    return name;
}

float view_histTuple::getHistPrice()
{
    return price;
}

QString view_histTuple::getHistFirstName()
{
    return firstName;
}

QString view_histTuple::getHistOperation()
{
    return operation;
}

db_histTuple view_histTuple::transformIntoHistDb()
{
    db_histTuple result;
    result.setHistId(id);
    result.setHistName(name.QString::toStdString());
    result.setHistFirstName(firstName.QString::toStdString());
    result.setHistDate(date.QString::toStdString());
    result.setHistOperation(operation.QString::toStdString());
    result.setHistPrice(price);

    return result;
}

// ##################################
// DB_HISTTUPLE
// ##################################

void db_histTuple::setHistId(unsigned _id)
{
    id=_id;
}

void db_histTuple::setHistDate(std::string _date)
{
    date=_date;
}

void db_histTuple::setHistName(std::string _name)
{
    name=_name;
}

void db_histTuple::setHistPrice(float _price)
{
    price=_price;
}

void db_histTuple::setHistFirstName(std::string _firstName)
{
    firstName = _firstName;
}

void db_histTuple::setHistOperation(std::string _operation)
{
    operation = _operation;
}

void db_histTuple::setHistCustomerId(unsigned _id)
{
    customer_id = _id;
}

void db_histTuple::setHistProductId(unsigned _id)
{
    product_id = _id;
}

int db_histTuple::getHistId()
{
    return id;
}

std::string db_histTuple::getHistDate()
{
    return date;
}

std::string db_histTuple::getHistName()
{
    return name;
}

float db_histTuple::getHistPrice()
{
    return price;
}

std::string db_histTuple::getHistFirstName()
{
    return firstName;
}

std::string db_histTuple::getHistOperation()
{
    return operation;
}

unsigned db_histTuple::getHistCustomerId()
{
    return customer_id;
}

unsigned db_histTuple::getHistProduct_Id()
{
    return product_id;
}

view_histTuple db_histTuple::transformIntoHistView()
{
    view_histTuple result;
    result.setHistId(id);
    result.setHistName(QString::fromStdString(name));
    result.setHistFirstName(QString::fromStdString(firstName));
    result.setHistDate(QString::fromStdString(date));
    result.setHistOperation(QString::fromStdString(operation));
    result.setHistPrice(price);

    return result;
}

// ##################################
// VIEW_CARTTUPLE
// ##################################

void view_cartTuple::setCartCustomerId(unsigned _id)
{
    customer_id=_id;
}

void view_cartTuple::setCartPrice(float _price)
{
    price=_price;
}

void view_cartTuple::setCartProdId(unsigned _id)
{
    product_id=_id;
}

void view_cartTuple::setCartProdName(QString _string)
{
    conso_name=_string;
}

void view_cartTuple::setCartQuantity(unsigned _qty)
{
    quantity=_qty;
}

unsigned view_cartTuple::getCarProdId()
{
    return product_id;
}

unsigned view_cartTuple::getCartCustomerId()
{
    return customer_id;
}

unsigned view_cartTuple::getCartQuantity()
{
    return quantity;
}

float view_cartTuple::getCartPrice()
{
    return price;
}

QString view_cartTuple::getCartProdName()
{
    return conso_name;
}
