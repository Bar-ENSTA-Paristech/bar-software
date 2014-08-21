#ifndef PRODUCTSCHOICES_H
#define PRODUCTSCHOICES_H

#include <QFrame>
#include "multilist.h"
#include <tuple>
#include <queue>
#include "controller.h"
#include "structures.h"
extern ViewObjects VIEW;

class Controller;
class ProductsChoices : public MultiList
{
    Q_OBJECT
public:
    explicit ProductsChoices(QWidget *parent = 0);

    // receive product choices from controller
    void setProductsChoices(view_productQueue queue, bool printVolume=true);
    void setFocus();
    void addFocusedProduct();

signals:
    
private slots:
    void lineClicked(QModelIndex index);
    
};

#endif // PRODUCTSCHOICES_H
