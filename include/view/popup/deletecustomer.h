#ifndef DELETECUSTOMER_H
#define DELETECUSTOMER_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "structures.h"
#include "popup.h"
extern ViewObjects VIEW;

class DeleteCustomer : public Popup
{
    Q_OBJECT
public:
    explicit DeleteCustomer(QWidget *parent = 0);
    void printDelete(view_customerTuple& customer);
    
signals:

private:
    QLabel* text;
    
public slots:
    
};

#endif // DELETECUSTOMER_H
