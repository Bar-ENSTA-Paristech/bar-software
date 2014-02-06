#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product
{
public:
    Product();
    Product(unsigned _id, std::string _name, std::string _type, float _price, unsigned _stock);
    std::string getName() const;
    std::string getType() const;
    float getPrice() const;
    int getStock() const;
    float getTotalPrice() const;
    void setName(const std::string &_name);
    void setPrice(float _price);
    void setStock(int _stock);
    void setId(int _id);
    void setTypeId(int _typeid);
    Product& operator++(); // Prefix
    Product& operator++(int); // Postfix
    Product& operator--(); // Prefix
    Product& operator--(int); // Postfix
    Product& operator+=(int addedStock);
    Product& operator-=(int removedStock);
private:
    std::string name;
    std::string type; //based on data table, for example "Boisson", "Divers", ...
    float price;
    int stock; // Can be negative but must be unisgned at construction of object
    unsigned id;
    int typeId;


};

#endif // PRODUCT_H
