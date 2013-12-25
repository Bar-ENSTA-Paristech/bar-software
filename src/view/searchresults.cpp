#include "searchresults.h"

void printItem(QStandardItemModel* model)
{
    for(int i =0 ; i<10 ; i++)
    {
        qDebug() << model->item(i,0)->text()<< model->item(i,1)->text()<< model->item(i,2)->text()<< model->item(i,3)->text();
    }

}

SearchResults::SearchResults(QWidget *parent) :
    MultiList(parent, 5, 0)
{
    this->setObjectName("searchResults");

    headers[0]->setText("Nom");
    headers[1]->setText("Prénom");
    headers[2]->setText("Catégorie");
    headers[3]->setText("Solde");
    headers[4]->setText("Id");

    stretchColumns = new int[3];
    stretchColumns[0]=0;
    stretchColumns[1]=1;
    stretchColumns[2]=-1;
    defaultHeaderWidth = 70;
    hiddenColumn = 4;
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);

    QObject::connect(table, SIGNAL(clicked(QModelIndex)), this, SLOT(lineClicked(QModelIndex)));

    // ####### TEST #######
    /*std::queue< std::tuple< QString, QString, QString, float, unsigned > > toto;
    std::tuple< QString, QString, QString, float, unsigned > titi("Chat", "Mehdi", "2015", -2, 1);
    std::tuple< QString, QString, QString, float, unsigned > titi2("Diallo", "Guytoof", "2015", 3.5, 2);
    toto.push(titi);
    toto.push(titi2);
    this->setSearchResults(toto);*/
    // ####### FIN TEST #######

}

void SearchResults::setSearchResults(view_customerQueue & queue)
{
    // TUPLE : QString name, QString firstName, QString categorie, float balance, unsigned id
    view_customerTuple tuple;
    table->setModel(NULL);

    // Inserting new results
    QBrush negativeSold(Qt::red);
    QBrush positiveSold(Qt::black);
    float balance = 0;
    unsigned numberOfElements = queue.size();
    timer.start(10000);
    setRows(numberOfElements);
    qDebug() << "Fin setRows" << 10000-timer.remainingTime() << "ms";
    for(unsigned i=0 ; i<numberOfElements ; i++)
    {
        tuple = queue.front();
        queue.pop();
        balance = tuple.getCustomerBalance();
        if(balance < 0)
            model->item(i,3)->setForeground(negativeSold);
        else
            model->item(i,3)->setForeground(positiveSold);

        model->item(i,0)->setText(tuple.getCustomerName());
        model->item(i,1)->setText(tuple.getCustomerFirstname());
        model->item(i,2)->setText(QString::number(tuple.getCustomerCategory()));
        model->item(i,3)->setText(QString::number(balance));
        model->item(i,4)->setText(QString::number(tuple.getCustomerId()));
    }
    qDebug() << "Fin setText" << 10000-timer.remainingTime() << "ms";
    //table->sortItems(0, Qt::AscendingOrder);
    table->sortByColumn(0, Qt::AscendingOrder);
    table->setModel(model);
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);
    return;
}

void SearchResults::lineClicked(QModelIndex index)
{
    controller->newClic_Customer((unsigned) model->item(index.row(),4)->text().toInt());
}
