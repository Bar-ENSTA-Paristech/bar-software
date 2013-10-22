#ifndef RIGHTPART_H
#define RIGHTPART_H

#include <QFrame>
#include <QGridLayout>
#include "cartdisplay.h"
#include "productschoices.h"
#include "consologos.h"

class RightPart : public QFrame
{
public:
    RightPart(QWidget* parent = NULL);
    void updateSize();
    void getPointers(ProductsChoices** par1, ConsoLogos** par2, CartDisplay** par3);

private:
    ProductsChoices *productsChoices;
    ConsoLogos *logosFrame;
    CartDisplay *cartDisplay;
};

#endif // RIGHTPART_H
