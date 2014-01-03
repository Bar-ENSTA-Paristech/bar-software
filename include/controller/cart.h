#ifndef CART_H
#define CART_H

#include "product.h"
#include <map>
#include <memory>
#include <iostream>
#include <QList>

typedef std::pair<unsigned, unsigned> cartProduct;

class Cart
{
public:
    Cart();
    //Cart(Product& product);
    void addProductToCart(unsigned product, unsigned quantity = 1);
    void removeProductFromCart(unsigned product, unsigned quantity = 1);
    void clearCart();
    void editPrice(float modification);
    float getPrice() const;
    void setCustomerID(unsigned _id);
    unsigned int getSizeOfCart() const;
    unsigned getCustomerID();
    QList<cartProduct> getList();


private:
    QList<cartProduct> cartContent;
    unsigned int numberOfProducts;
    unsigned customerId;
    float totalPrice;
    unsigned int sizeOfCart; //usefull to set a bigger table for products

};

#endif // CART_H
