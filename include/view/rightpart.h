#ifndef RIGHTPART_H
#define RIGHTPART_H

#include <QFrame>
#include <QGridLayout>
#include "cartdisplay.h"
#include "productschoices.h"
#include "consologos.h"
#include "controller.h"

class Controller;
class RightPart : public QFrame
{
public:
    Controller* controller;
    RightPart(QWidget* parent = NULL);
    ~RightPart();
    void updateSize();
    void getPointers(ProductsChoices** par1, ConsoLogos** par2, CartDisplay** par3);
    void setController(Controller* par);

private:
    ProductsChoices *productsChoices;
    ConsoLogos *logosFrame;
    CartDisplay *cartDisplay;
    QGridLayout *layout;

};

#endif // RIGHTPART_H
