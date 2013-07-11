#ifndef CART_H
#define CART_H

#include "product.h"
#include <map>
#include <memory>

struct CartMapCompare {
  bool operator() (const std::shared_ptr<Product>& lhs, const std::shared_ptr<Product>& rhs) const
  {return lhs->getName()<rhs->getName();}
};

class Cart
{
public:
    Cart();
    Cart(Product& product);
    void addProductToCart(std::shared_ptr<Product> product, unsigned quantity = 1);
    void removeProductFromCart(std::shared_ptr<Product> product, unsigned quantity = 1);
    void clearCart();
    bool saveCart(); //Return True if sucessful otherwise False
    void refreshPrice();
    float getPrice() const;
    unsigned int getNumberOfProducts() const;
    void sortProducts();

private:
    std::map<std::shared_ptr<Product>, unsigned, CartMapCompare> products;
    unsigned int numberOfProducts;
    float price;
    unsigned int sizeOfCart; //usefull to set a bigger table for products
};

#endif // CART_H
