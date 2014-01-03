#include "productschoices.h"

ProductsChoices::ProductsChoices(QWidget *parent) :
    MultiList(parent, 4, 0)
{
    VIEW.productChoices = this;
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

    QObject::connect(table, SIGNAL(clicked(QModelIndex)), this, SLOT(lineClicked(QModelIndex)));

}

void ProductsChoices::setProductsChoices(view_productQueue queue)
{
    //On vide l'index précédemment établi
    model->removeRows(0,rows);

    // TUPLE : QString conso, QString Volume, float price, unsigned id
    view_productTuple tuple;
    // Inserting new results
    unsigned numberOfElements = queue.size();
    setRows(numberOfElements);

    for(unsigned i=0;i<numberOfElements ; i++)
    {
        tuple = queue.front();

        model->item(i,0)->setText(tuple.getProductName());
        model->item(i,1)->setText(QString::number(tuple.getProductStock()));
        model->item(i,2)->setText(QString::number(tuple.getProductPrice()));
        model->item(i,3)->setText(QString::number(tuple.getProductId()));
        queue.pop();
    }
    table->sortByColumn(0, Qt::AscendingOrder);
    table->setModel(model);
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);
    return;
}

void ProductsChoices::lineClicked(QModelIndex index)
{
    unsigned int clickedProductId =(unsigned) model->item(index.row(),3)->text().toInt();
    controller->newClic_Product(clickedProductId );
    //controller->newClic_Customer((unsigned) model->item(index.row(),3)->text().toInt());
}
