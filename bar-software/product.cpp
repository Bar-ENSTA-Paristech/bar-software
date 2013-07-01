#include "product.h"
#include <iostream>

using namespace std;

Product::Product(std::string _name, float _price, unsigned _stock) : name(_name), price(_price), stock(_stock)
{
}

std::string Product::getName() const
{
    return name;
}

float Product::getPrice() const
{
    return price;
}

int Product::getStock() const
{
    return stock;
}

float Product::getTotalPrice() const
{
    return static_cast<float>(stock)*price;
}

void Product::setName(const std::string &_name)
{
    name = _name;
}

void Product::setPrice(float _price)
{
    if (_price >= 0)
        price = _price;
    else
        cerr << "The price must be a positive floating number" << endl;
}

void Product::setStock(int _stock)
{
    if (stock < 0)
        cout << "The stock of this product is lower than 0" << endl;
    stock = _stock;
}

Product &Product::operator ++()
{
    ++stock;
    return *this;
}

Product &Product::operator ++(int)
{
    Product temp = *this;
    ++stock;
    return temp;
}

Product &Product::operator --()
{
    return ++(*this);
}

Product &Product::operator --(int)
{
    return (*this)++;
}

Product &Product::operator +=(int addedStock)
{
    stock += addedStock;
    return *this;
}

Product &Product::operator -=(int removedStock)
{
    return (*this)+=(-removedStock);
}
