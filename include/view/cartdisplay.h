#ifndef CARTDISPLAY_H
#define CARTDISPLAY_H

#include <QFrame>
#include <queue>
#include <tuple>
#include <QListView>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include "multilist.h"
#include <QDebug>
#include "controller.h"

class Controller;
class CartDisplayFrame : public MultiList
{
    Q_OBJECT
public:
    explicit CartDisplayFrame(QWidget *parent = 0);
    void setCart(std::queue< std::tuple<QString, float, unsigned int> > & queue);
};


class CartDisplay : public QFrame
{
    Q_OBJECT
public:
    Controller* controller;
    explicit CartDisplay(QWidget *parent = 0);
    void setCart(std::queue< std::tuple<QString, float, unsigned int> > & queue);
    void setTotalPrice(float price);
    void updateSize(){cartList->updateSize();}

private:
    CartDisplayFrame* cartList;
    QLabel* totalPrice;
    QPushButton* validateButton;
    QPushButton* cancelButton;
    QFont bold;

    
signals:
    
public slots:
    
};



#endif // CARTDISPLAY_H
