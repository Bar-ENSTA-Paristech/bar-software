#include "rightpart.h"

RightPart::RightPart(QWidget* parent)
{
    VIEW.rightPart = this;
    setParent(parent);
    setObjectName("rightPart");

    logosFrame = new ConsoLogos(this);
    cartDisplay = new CartDisplay(this);
    productsChoices = new ProductsChoices(this);
    layout = new QGridLayout(this);
    layout->addWidget(logosFrame, 0, 0, 1, 2);
    layout->addWidget(cartDisplay, 0, 2, 1, 3);
    layout->addWidget(productsChoices, 1, 0, 3, 5);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
}

RightPart::~RightPart()
{
    /*delete productsChoices;
    delete logosFrame;
    delete cartDisplay;
    delete layout;*/
}

void RightPart::updateSize()
{
    productsChoices->updateSize();
    cartDisplay->updateSize();
}

void RightPart::getPointers(ProductsChoices** par1, ConsoLogos** par2, CartDisplay** par3)
{
    *par1 = productsChoices;
    *par2 = logosFrame;
    *par3 = cartDisplay;
}

void RightPart::setController(Controller* par)
{
    controller = par;
    productsChoices->controller = par;
    logosFrame->controller = par;
    cartDisplay->controller = par;
}

