#include "cart.h"

using namespace std;

Cart::Cart()
{
    numberOfProducts = 0;
    price = 0.0;
}
Cart::Cart(Product& product) : Cart()
{
    auto productPtr = make_shared<Product>(product);
    addProductToCart(productPtr);
}

void Cart::addProductToCart(shared_ptr<Product> product, unsigned quantity)
{
    // We might need to check if there is enough stock available ?
    auto ret = products.insert(make_pair(product,quantity)); // We try to insert the product in the map
    if (ret.second == false) // insert returns a std::pair, whose .second is false if key already existed
        products[product] += quantity; // In which case, we just add to the quantity
    numberOfProducts += quantity;
    price += product->getPrice()*quantity;
    refreshPrice();
    cout << "Ajout du produit " << product->getName() << "au panier : succès" << endl;
}

void Cart::removeProductFromCart(shared_ptr<Product> product, unsigned quantity)
{
    unsigned remoQuantity;
    // We might want to check if the product is already in the cart ?
    if(quantity < products[product]){ // If we remove less than the quantity in the cart
        products[product] -= quantity;  // Just decrease the number of that product in the cart
        remoQuantity = quantity;
    }
    else{
        remoQuantity = products[product];
        products.erase(products.find(product)); // If we remove more than there is in the cart, just erase the product
        cout << "Suppresion du produit " << product->getName() << "depuis le panier : succès" << endl;
    }
    numberOfProducts -= remoQuantity;
    price -= product->getPrice()*remoQuantity;
    refreshPrice();

    // TODO
    /*price -= products[productNumber].getPrice();
    for(int i=productNumber ; i<sizeOfCart-1 ; i++)
    {
        products[i] = products[i+1];
    }
    numberOfProducts--;
    refreshPrice();*/
}

void Cart::clearCart()
{
    price = 0.0;
    numberOfProducts = 0;
    products.clear();
}

bool Cart::saveCart()
{
    // Do all needed queries
    clearCart();
    return true;
}

void Cart::refreshPrice()
{
    price = 0;
    for (auto product : products )
    {
        price += product.first->getPrice()*product.second;
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
