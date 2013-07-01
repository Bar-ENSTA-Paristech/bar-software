#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product
{
public:
    Product(std::string _name, float _price, unsigned _stock);
    std::string getName() const;
    float getPrice() const;
    int getStock() const;
    float getTotalPrice() const;
    void setName(const std::string &_name);
    void setPrice(float _price);
    void setStock(int _stock);
    Product& operator++(); // Prefix
    Product& operator++(int); // Postfix
    Product& operator--(); // Prefix
    Product& operator--(int); // Postfix
    Product& operator+=(int addedStock);
    Product& operator-=(int removedStock);
private:
    std::string name;
    float price;
    int stock; // Can be negative but must be unisgned at construction of object


};

#endif // PRODUCT_H
