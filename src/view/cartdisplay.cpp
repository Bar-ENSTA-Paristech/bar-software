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
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(cartList, 0, 0, 1, 3);
    layout->addWidget(totalPrice, 1, 0);
    layout->addWidget(validateButton, 1,1);
    layout->addWidget(cancelButton, 1,2);
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    validateButton->setText("Valider");
    cancelButton->setText("Annuler");

    // ####### TEST #######
    std::queue< std::tuple< QString, float, unsigned > > toto;
    std::tuple< QString, float, unsigned > titi("Bières-Guiness 0.5L", 5.4, 2);
    std::tuple< QString, float, unsigned > titi2("Vin-Quessard 0.75L", 5.0, 1);
    std::tuple< QString, float, unsigned > titi3("Pression-Kronembourg 0.5L", 2.4*3, 3);
    toto.push(titi);
    toto.push(titi2);
    toto.push(titi3);
    this->setCart(toto);
    // ####### FIN TEST #######
}

void CartDisplay::setCart(std::queue< std::tuple<QString, float, unsigned int> > & queue)
{
    // TUPLE : QString consumption, float price, unsigned int number of these products

    cartList->setCart(queue);
    // Removing old entrys
    /*QListWidgetItem* item;
    while((item = cartList->takeItem(0)) != NULL)
        delete item;

    std::tuple<QString, float, unsigned int> tuple;
    for(unsigned i =0, n = queue.size() ; i < n ; i++)
    {
        tuple = queue.front();
        queue.pop();
        cartList->addItem(QString::number(std::get<1>(tuple)) + "€ : " + QString::number(std::get<2>(tuple))+" "+std::get<0>(tuple));
    }*/
}

void CartDisplay::setTotalPrice(float price)
{

}


CartDisplayFrame::CartDisplayFrame(QWidget *parent) :
    MultiList(parent, 3, 0, false)
{
    this->setObjectName("cartDiplayFrame");
    QTableWidgetItem *headers = new QTableWidgetItem[columns];
    headers[0].setText("Consommation");
    headers[1].setText("Qté");
    headers[2].setText("Prix");
    for(int i=0 ; i < columns ; i++)
        list->setHorizontalHeaderItem(i, &headers[i]);

    list->horizontalHeader()->setDefaultSectionSize(40);
    list->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}


void CartDisplayFrame::setCart(std::queue< std::tuple<QString, float, unsigned int> > & queue)
{
    // TUPLE : QString consumption, float price, unsigned int number of these products
    std::tuple<QString, float, unsigned int> tuple;
    for(int i = 0 ; i<rows ; i++)
    {
        delete itemList[i];
    }
    if(isInitialised && rows !=0)
        delete itemList;
    else
        isInitialised = true;

    // Inserting new results
    unsigned numberOfElements = queue.size();
    setRows(numberOfElements);
    // Creating our matrix representing table
    itemList = new QTableWidgetItem*[numberOfElements];
    for(unsigned i = 0 ; i<numberOfElements ; i++)
    {
        itemList[i] = new QTableWidgetItem[columns];
    }
    // Setting it up to table
    for(unsigned i=0 ; i<numberOfElements ; i++)
    {
        tuple = queue.front();
        queue.pop();
        itemList[i][0].setText(std::get<0>(tuple));
        itemList[i][1].setText(QString::number(std::get<2>(tuple)));
        itemList[i][2].setText(QString::number(std::get<1>(tuple)));
        for(int j=0 ; j < columns ; j++)
            list->setItem(i, j, &itemList[i][j]);
    }
    list->sortItems(2, Qt::AscendingOrder);
}



