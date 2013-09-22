#ifndef PRODUCTSCHOICES_H
#define PRODUCTSCHOICES_H

#include <QFrame>

class ProductsChoices : public QFrame
{
    Q_OBJECT
public:
    explicit ProductsChoices(QWidget *parent = 0);

    // receive product choices from controller
    void setProductsChoices();

signals:
    
public slots:
    
};

#endif // PRODUCTSCHOICES_H
