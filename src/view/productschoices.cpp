#include "productschoices.h"

ProductsChoices::ProductsChoices(QWidget *parent) :
    MultiList(parent, 4, 0)
{
    setObjectName("productChoices");
    headers[0]->setText("Consommation");
    headers[1]->setText("Volume");
    headers[2]->setText("Prix");
    headers[3]->setText("Id");
    for(int i=0 ; i < columns ; i++)
        table->setHorizontalHeaderItem(i, headers[i]);

    table->horizontalHeader()->setDefaultSectionSize(70);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionHidden(3, true);

    QObject::connect(table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(lineClicked(int,int)));

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
    unsigned rows_old = rows;
    setRows(numberOfElements);

    // If there are more rows than before, we allocate space for the items and set them to the table
    if(numberOfElements > rows_old)
    {
        for(unsigned i=rows_old ; i<numberOfElements ; i++)
        {
            QTableWidgetItem* item0 = new QTableWidgetItem();
            QTableWidgetItem* item1 = new QTableWidgetItem();
            QTableWidgetItem* item2 = new QTableWidgetItem();
            QTableWidgetItem* item3 = new QTableWidgetItem();

            table->setItem(i, 0, item0);
            table->setItem(i, 1, item1);
            table->setItem(i, 2, item2);
            table->setItem(i, 3, item3);
        }
    }
    for(unsigned i=0 ; i<numberOfElements ; i++)
    {
        tuple = queue.front();
        queue.pop();
        table->item(i,0)->setText(std::get<0>(tuple));
        table->item(i,1)->setText(std::get<1>(tuple));
        table->item(i,2)->setText(QString::number(std::get<2>(tuple)));
        table->item(i,3)->setText(QString::number(std::get<3>(tuple)));
    }
    table->sortItems(0, Qt::AscendingOrder);
    return;
}

void ProductsChoices::lineClicked(int row, int column)
{
    //controller->newClic_Customer((unsigned) itemList[row][3].text().toInt());
}
