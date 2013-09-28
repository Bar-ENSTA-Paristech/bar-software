#ifndef CARTDISPLAY_H
#define CARTDISPLAY_H

#include <QFrame>
#include <queue>
#include <tuple>
#include "cart.h"

class CartDisplay : public QFrame
{
    Q_OBJECT
public:
    explicit CartDisplay(QWidget *parent = 0);
    void setCart(std::queue< std::tuple<  > > & queue);
    void setTotalPrice(float price);

private:
    Cart* cart;
    
signals:
    
public slots:
    
};

#endif // CARTDISPLAY_H
