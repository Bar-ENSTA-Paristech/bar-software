#include "cartdisplay.h"

CartDisplay::CartDisplay(QWidget *parent) :
    QFrame(parent)
{
    setObjectName("cartDisplay");
    //QWidget* actionMenu = new QWidget(this);
    cartList = new CartDisplayFrame(this);
    totalPrice = new QLabel(this);
    validateButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    layout = new QGridLayout(this);
    layout->addWidget(cartList, 0, 0, 1, 3);
    layout->addWidget(totalPrice, 1, 0);
    layout->addWidget(validateButton, 1,1);
    layout->addWidget(cancelButton, 1,2);
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    bold.setBold(true);
    bold.setPixelSize(17);
    validateButton->setText("Valider");
    cancelButton->setText("Annuler");
    totalPrice->setText("- €");
    totalPrice->setFont(bold);
    totalPrice->setAlignment(Qt::AlignCenter);

    // ####### TEST #######
    std::queue< std::tuple< QString, float, unsigned > > toto;
    std::tuple< QString, float, unsigned > titi("Bières-Guiness 0.5L", 5.4, 2);
    std::tuple< QString, float, unsigned > titi2("Vin-Quessard 0.75L", 5.0, 1);
    std::tuple< QString, float, unsigned > titi3("Pression-Kronembourg 0.5L", 2.4*3, 3);
    toto.push(titi);
    toto.push(titi2);
    toto.push(titi3);
    this->setCart(toto);
    this->setTotalPrice(5.4+5+2.4*3);
    // ####### FIN TEST #######
}

CartDisplay::~CartDisplay()
{
    /*delete cartList;
    delete totalPrice;
    delete validateButton;
    delete cancelButton;
    delete layout;*/
}

void CartDisplay::setCart(std::queue< std::tuple<QString, float, unsigned int> > & queue)
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
    this->setObjectName("cartDiplayFrame");
    headers[0]->setText("Consommation");
    headers[1]->setText("Qté");
    headers[2]->setText("Prix");

    /*for(int i=0 ; i < columns ; i++)
        table->setHorizontalHeaderItem(i, headers[i]);*/

    stretchColumns = new int[2];
    stretchColumns[0]=0;
    stretchColumns[1]=-1;
    defaultHeaderWidth = 40;
    hiddenColumn = -1;
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);
}


void CartDisplayFrame::setCart(std::queue< std::tuple<QString, float, unsigned int> > & queue)
{
    // TUPLE : QString consumption, float price, unsigned int number of these products
    std::tuple<QString, float, unsigned int> tuple;

    // Inserting new results
    unsigned numberOfElements = queue.size();
    setRows(numberOfElements);

    for(unsigned i=0 ; i<numberOfElements ; i++)
    {
        tuple = queue.front();
        queue.pop();
        model->item(i,0)->setText(std::get<0>(tuple));
        model->item(i,1)->setText(QString::number(std::get<1>(tuple)));
        model->item(i,2)->setText(QString::number(std::get<2>(tuple)));
    }
    //table->sortItems(2, Qt::AscendingOrder);
}



