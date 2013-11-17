#include "productschoices.h"

ProductsChoices::ProductsChoices(QWidget *parent) :
    MultiList(parent, 4, 0)
{
    setObjectName("productChoices");
    headers[0]->setText("Consommation");
    headers[1]->setText("Volume");
    headers[2]->setText("Prix");
    headers[3]->setText("Id");

    stretchColumns = new int[2];
    stretchColumns[0]=0;
    stretchColumns[1]=-1;
    defaultHeaderWidth = 70;
    hiddenColumn = 3;
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);

    // ####### TEST #######
    std::queue< std::tuple< QString, QString, float, unsigned > > toto;
    std::tuple< QString, QString, float, unsigned > titi("Duvel", "0.33L", 1.9, 1);
    std::tuple< QString, QString, float, unsigned > titi2("Super Bock", "0.25L", 0.9, 2);
    toto.push(titi);
    toto.push(titi2);
    this->setProductsChoices(toto);
    // ####### FIN TEST #######
}

void ProductsChoices::setProductsChoices(std::queue< std::tuple< QString, QString, float, unsigned > > & queue)
{
    // TUPLE : QString conso, QString Volume, float price, unsigned id
    std::tuple< QString, QString, float, unsigned > tuple;

    // Inserting new results
    unsigned numberOfElements = queue.size();
    setRows(numberOfElements);

    for(unsigned i=0 ; i<numberOfElements ; i++)
    {
        tuple = queue.front();
        queue.pop();
        model->item(i,0)->setText(std::get<0>(tuple));
        model->item(i,1)->setText(std::get<1>(tuple));
        model->item(i,2)->setText(QString::number(std::get<2>(tuple)));
        model->item(i,3)->setText(QString::number(std::get<3>(tuple)));
    }
    //table->sortItems(0, Qt::AscendingOrder);
    return;
}

void ProductsChoices::lineClicked(int row, int column)
{
    //controller->newClic_Customer((unsigned) itemList[row][3].text().toInt());
}
