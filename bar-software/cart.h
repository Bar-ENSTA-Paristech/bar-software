#ifndef CART_H
#define CART_H

#include "product.h"

class Cart
{
public:
    Cart();
    Cart(Product& product);
    void addProductToCart(Product& product);
    void removeProductFromCart(int productNumber); //begin at 0
    void clearCart();
    bool saveCart(); //Return True if sucessful otherwise False
    void refreshPrice();
    float getPrice() const;
    unsigned int getNumberOfProducts() const;
    void sortProducts();

private:
    Product* products; //table of products in the cart
    unsigned int numberOfProducts;
    float price;
    unsigned int sizeOfCart; //usefull to set a bigger table for products
};

#endif // CART_H
