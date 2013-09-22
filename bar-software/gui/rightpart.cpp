#include "rightpart.h"

RightPart::RightPart(QWidget* parent)
{
    setParent(parent);
    setObjectName("rightPart");

    QFrame *logoFrame = new QFrame(this);
    CartDisplay *cartDisplay = new CartDisplay(this);
    ProductsChoices *productsChoices = new ProductsChoices(this);
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(logoFrame, 0, 0);
    layout->addWidget(cartDisplay, 0, 1);
    layout->addWidget(productsChoices, 1, 0, 1, 10);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
}
