#ifndef PRODUCTSCHOICES_H
#define PRODUCTSCHOICES_H

#include <QFrame>
#include "multilist.h"
#include <tuple>
#include <queue>

class ProductsChoices : public MultiList
{
    Q_OBJECT
public:
    explicit ProductsChoices(QWidget *parent = 0);

    // receive product choices from controller
    void setProductsChoices(std::queue<std::tuple<QString, QString, float, unsigned> > &queue);

signals:
    
public slots:
    
};

#endif // PRODUCTSCHOICES_H
