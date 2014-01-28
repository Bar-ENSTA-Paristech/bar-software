#ifndef CARTDISPLAY_H
#define CARTDISPLAY_H

#include <QFrame>
#include <queue>
#include <tuple>
#include <QListView>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QCheckBox>
#include <QTimer>
#include "multilist.h"
#include <QDebug>
#include "controller.h"
#include "structures.h"
#include "productschoices.h"

extern ViewObjects VIEW;

class Controller;
class CartDisplayFrame : public MultiList
{
    Q_OBJECT
public:
    explicit CartDisplayFrame(QWidget *parent = 0);
    void setCart(view_cartQueue & queue);
};


class CartDisplay : public QFrame
{
    Q_OBJECT
public:
    Controller* controller;
    explicit CartDisplay(QWidget *parent = 0);
    ~CartDisplay();
    void setCart(view_cartQueue & queue);
    void setTotalPrice(float price);
    void updateSize(){cartList->updateSize();}
    void setLastCart(QString name, float price);
    bool getCash();
    void setCashChoice(bool isCashForced);


private:
    CartDisplayFrame* cartList;
    QLabel* totalPrice;
    QLabel* lastCart;
    QPushButton* validateButton;
    QPushButton* cancelButton;
    QFont bold;
    QGridLayout* layout;
    QCheckBox *cash;
    QTimer* timer;
    QFont font;

    
signals:
    
public slots:
    void validateCart();
    void cancelCart();
    void timerTimeout();
    
};



#endif // CARTDISPLAY_H
