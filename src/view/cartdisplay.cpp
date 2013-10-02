#include "cartdisplay.h"

CartDisplay::CartDisplay(QWidget *parent) :
    QFrame(parent)
{
}

void CartDisplay::setCart(std::queue< std::tuple<QString, float, unsigned int> > & queue)
{

}

void CartDisplay::setTotalPrice(float price)
{

}
