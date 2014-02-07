#include "cart.h"

Cart::Cart()
{
    sizeOfCart = 0;
    totalPrice = 0.0;
    customerId =0;
}

void Cart::addProductToCart(unsigned product, unsigned quantity)
{
    // We check if there is enough stock available in a controller method, this is just an update of the cart
    bool added_flag=false;
    std::pair<int,int> new_prod;
    new_prod.first=product;
    new_prod.second=quantity;

    for(int i=0;i<cartContent.size();i++)
    {
        if (cartContent[i].first==product)
        {
            cartContent[i].second+=quantity;
            added_flag=true;
        }
    }

    if (added_flag==false)
    {
        cartContent.push_back(new_prod);
        sizeOfCart++;
    }

    return;
}

void Cart::removeProductFromCart(unsigned product, unsigned quantity)
{
    bool removed_flag=false;
    std::pair<int,int> new_prod;
    new_prod.first=product;
    new_prod.second=quantity;

    for(int i=0;i<cartContent.size();i++)
    {
        if (cartContent[i].first==product)
        {
            cartContent[i].second-=quantity;
            removed_flag=true;
            if (cartContent[i].second==0)
            {
                cartContent.move(i,0);
                cartContent.pop_front();
                sizeOfCart--;
            }
        }
    }

    if (removed_flag==false)
    {
        std::cout<<"Problème : le produit d'id "<<product<<"n'est pas dans le panier : impossible de le supprimer";
    }
    return;
}

void Cart::clearCart()
{
    customerId = 0;
    totalPrice = 0.0;
    sizeOfCart = 0;
    cartContent.clear();
}

void Cart::editPrice(float modification)
{
    totalPrice+=modification;
}

void Cart::setCustomerID(unsigned _id)
{
    customerId=_id;
}

float Cart::getPrice() const
{
    return totalPrice;
}

unsigned int Cart::getSizeOfCart() const
{
    return sizeOfCart;
}

unsigned Cart::getCustomerID()
{
    return customerId;
}

QList<cartProduct> Cart::getList()
{
    return cartContent;
}
