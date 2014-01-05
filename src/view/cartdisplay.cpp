#include "cartdisplay.h"

CartDisplay::CartDisplay(QWidget *parent) :
    QFrame(parent)
{
    VIEW.cartDisplay = this;
    setObjectName("cartDisplay");
    //QWidget* actionMenu = new QWidget(this);
    cartList = new CartDisplayFrame(this);
    totalPrice = new QLabel(this);
    cash = new QCheckBox("Cash", this);
    validateButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    layout = new QGridLayout(this);
    layout->addWidget(cartList, 0, 0, 1, 3);
    layout->addWidget(cash, 1,0, 1,1, Qt::AlignCenter);
    layout->addWidget(totalPrice, 2, 0);
    layout->addWidget(validateButton, 2,1);
    layout->addWidget(cancelButton, 2,2);
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    bold.setBold(true);
    bold.setPixelSize(17);
    validateButton->setText("Valider");
    cancelButton->setText("Annuler");
    totalPrice->setText("- €");
    totalPrice->setFont(bold);
    totalPrice->setAlignment(Qt::AlignCenter);

    QObject::connect(validateButton, SIGNAL(clicked()),this,SLOT(validateCart()));
    QObject::connect(cancelButton, SIGNAL(clicked()),this,SLOT(cancelCart()));

}

CartDisplay::~CartDisplay()
{
    /*delete cartList;
    delete totalPrice;
    delete validateButton;
    delete cancelButton;
    delete layout;*/
}

void CartDisplay::setCart(view_cartQueue &queue)
{
    // TUPLE : QString consumption, float price, unsigned int number of these products

    cartList->setCart(queue);
}

void CartDisplay::setTotalPrice(float price)
{
    if(price !=0)
        totalPrice->setText(QString::number(price) + " €");
    else
        totalPrice->setText("- €");
}



// ################### CART_DISPLAY_FRAME #######################

CartDisplayFrame::CartDisplayFrame(QWidget *parent) :
    MultiList(parent, 3, 0, false)
{
    VIEW.cartDisplayFrame = this;
    this->setObjectName("cartDiplayFrame");
    headers[0]->setText("Consommation");
    headers[1]->setText("Qté");
    headers[2]->setText("Prix");


    stretchColumns = new int[2];
    stretchColumns[0]=0;
    stretchColumns[1]=-1;
    defaultHeaderWidth = 40;
    hiddenColumn = -1;
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);

}


void CartDisplayFrame::setCart(view_cartQueue & queue)
{
    // TUPLE : QString consumption, float price, unsigned int number of these products
    view_cartTuple tuple;

    //On vide l'index précédemment établi
    model->removeRows(0,rows);


    // Inserting new results
    unsigned numberOfElements = queue.size();
    setRows(numberOfElements);

    for(unsigned i=0 ; i<numberOfElements ; i++)
    {
        tuple = queue.front();
        queue.pop();
        model->item(i,0)->setText(tuple.getCartProdName());
        model->item(i,1)->setText(QString::number(tuple.getCartQuantity()));
        model->item(i,2)->setText(QString::number(tuple.getCartPrice()));
    }
    table->sortByColumn(0, Qt::AscendingOrder);
    table->setModel(model);
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);
    return;
}

void CartDisplay::validateCart()
{
    controller->newClic_ValidateCart();
}

void CartDisplay::cancelCart()
{
    controller->newClic_CancelCart();
}
