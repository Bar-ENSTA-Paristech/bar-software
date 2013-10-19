#ifndef CARTDISPLAY_H
#define CARTDISPLAY_H

#include <QFrame>
#include <queue>
#include <tuple>
#include <QListWidget>
#include <QGridLayout>
#include "cart.h"
#include <QDebug>

class CartDisplay : public QFrame
{
    Q_OBJECT
public:
    explicit CartDisplay(QWidget *parent = 0);
    void setCart(std::queue< std::tuple<QString, float, unsigned int> > & queue);
    void setTotalPrice(float price);

private:
    QListWidget* list;
    
signals:
    
public slots:
    
};

#endif // CARTDISPLAY_H
