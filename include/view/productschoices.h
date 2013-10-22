#ifndef PRODUCTSCHOICES_H
#define PRODUCTSCHOICES_H

#include <QFrame>
#include "multilist.h"
#include <tuple>
#include <queue>
#include "controller.h"

class Controller;
class ProductsChoices : public MultiList
{
    Q_OBJECT
public:
    explicit ProductsChoices(QWidget *parent = 0);

    // receive product choices from controller
    void setProductsChoices(std::queue<std::tuple<QString, QString, float, unsigned> > &queue);

signals:
    
private slots:
    void lineClicked(int row, int column);
    
};

#endif // PRODUCTSCHOICES_H
