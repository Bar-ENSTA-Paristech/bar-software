#include "cart.h"

using namespace std;

Cart::Cart()
{
    numberOfProducts = 0;
    products = new Product[10];
    sizeOfCart = 10;
    price = 0;
}
Cart::Cart(Product& product)
{
    Cart();
    addProductToCart(product);
}

void Cart::addProductToCart(Product& product)
{
    // if cart is full, we get a bigger
    if (numberOfProducts == sizeOfCart)
    {
        Product* tmp = new Product[numberOfProducts + 10];
        sizeOfCart += 10;
        //then we copy it to the new cart
        for(int i=0 ; i < numberOfProducts ; i++)
        {
            tmp[i] = products[i];
        }
        delete products;
        products = tmp;
    }
    products[0] = product; //Check if it is correct : Does it really clone the product, or just point it ?
    numberOfProducts++;
    price += product.getPrice();
}

void Cart::removeProductFromCart(int productNumber)
{
    price -= products[productNumber].getPrice();
    for(int i=productNumber ; i<sizeOfCart-1 ; i++)
    {
        products[i] = products[i+1];
    }
    numberOfProducts--;
}

void Cart::clearCart()
{
    price = 0;
    numberOfProducts = 0;
}

bool Cart::saveCart()
{
    return true;
}

void Cart::refreshPrice()
{
    price = 0;
    for (int i=0 ; i < numberOfProducts ; i++ )
    {
        price += products[i].getPrice();
    }
}

float Cart::getPrice() const
{
    return price;
}

unsigned int Cart::getNumberOfProducts() const
{
    return numberOfProducts;
}
void Cart::sortProducts()
{
    //TODO
}
