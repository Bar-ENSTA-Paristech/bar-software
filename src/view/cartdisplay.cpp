#include "cartdisplay.h"

CartDisplay::CartDisplay(QWidget *parent) :
    QFrame(parent)
{
    setObjectName("cartDisplay");
    list = new QListWidget(this);
    //QGridLayout* layout = new QGridLayout(this);
    //layout->addWidget(list, 0, 0);
    //this->setLayout(layout);

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

    // Removing old entrys
    QListWidgetItem* item;
    while((item = list->takeItem(0)) != NULL)
        delete item;

    std::tuple<QString, float, unsigned int> tuple;
    for(unsigned i =0, n = queue.size() ; i < n ; i++)
    {
        tuple = queue.front();
        queue.pop();
        list->addItem(QString::number(std::get<1>(tuple)) + "€ : " + QString::number(std::get<2>(tuple))+" "+std::get<0>(tuple));
    }
}

void CartDisplay::setTotalPrice(float price)
{

}
