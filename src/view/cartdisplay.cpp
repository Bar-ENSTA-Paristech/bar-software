#include "cartdisplay.h"

CartDisplay::CartDisplay(QWidget *parent) :
    QFrame(parent)
{
    VIEW.cartDisplay = this;
    setObjectName("cartDisplay");
    font.setPixelSize(14);
    cartList = new CartDisplayFrame(this);
    totalPrice = new QLabel(this);
    lastCart = new QLabel(this);
    lastCart->setAlignment(Qt::AlignCenter);
    lastCart->setFont(font);
    cash = new QCheckBox("Cash", this);
    validateButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    layout = new QGridLayout(this);
    layout->addWidget(cartList, 0, 0, 1, 3);
    layout->addWidget(cash, 1,0,1,1, Qt::AlignHCenter);
    layout->addWidget(lastCart,1,1,1,2);
    layout->addWidget(totalPrice, 2, 0);
    layout->addWidget(validateButton, 2,1);
    layout->addWidget(cancelButton, 2,2);
    layout->setContentsMargins(0,0,0,0);
    //layout->setRowStretch(0, 1);
    this->setLayout(layout);

    bold.setBold(true);
    bold.setPixelSize(17);
    validateButton->setText("Valider");
    cancelButton->setText("Annuler");
    totalPrice->setText("- €");
    totalPrice->setFont(bold);
    totalPrice->setAlignment(Qt::AlignCenter);


    timer = new QTimer(this);
    timer->setTimerType(Qt::VeryCoarseTimer); // we don't need accuracy at all here

    QObject::connect(validateButton, SIGNAL(clicked()),this,SLOT(tryValidateCart()));
    QObject::connect(cancelButton, SIGNAL(clicked()),this,SLOT(cancelCart()));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));

}

CartDisplay::~CartDisplay()
{
}

bool CartDisplay::getCash()
{
    return cash->isChecked();
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

void CartDisplay::tryValidateCart()
{
    if(cash->isChecked() || !controller->isCustomerInNegative()) // no login requested
    {
        controller->newClic_ValidateCart(cash->isChecked());
        if(cash->isEnabled())
            cash->setChecked(false);
    }
    else // No cash and negative balance => individual request
    {
        controller->setCurrentLoginRequest(NEGATIVE_BALANCE);
        VIEW.login->checkIndividual();
    }
}

void CartDisplay::validateNegativeCart()
{
    controller->newClic_ValidateCart(false);
}

void CartDisplay::cancelCart()
{
    controller->newClic_CancelCart();
    if(cash->isEnabled())
        cash->setChecked(false);
}

void CartDisplay::setLastCart(QString name, float price)
{
    timer->start(4000);
    lastCart->setText(name + " : " + QString::number(price) + "€ Validé");
    lastCart->setStyleSheet("background: #55ff55;");
}

void CartDisplay::timerTimeout()
{
    lastCart->clear();
    lastCart->setStyleSheet("background: none;");
}

void CartDisplay::setCashChoice(bool isCashForced)
{
    if(isCashForced)
    {
        cash->setChecked(true);
        cash->setEnabled(false);
    }
    else
    {
        cash->setChecked(false);
        cash->setEnabled(true);
    }
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


