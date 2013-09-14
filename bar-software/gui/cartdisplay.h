#ifndef CARTDISPLAY_H
#define CARTDISPLAY_H

#include <QFrame>
#include "../cart.h"

class CartDisplay : public QFrame
{
    Q_OBJECT
public:
    explicit CartDisplay(QWidget *parent = 0);
    void setCart(/*voir ce que l'on envoie. Un vector me semble pas mal*/);

private:
    Cart* cart;
    
signals:
    
public slots:
    
};

#endif // CARTDISPLAY_H
