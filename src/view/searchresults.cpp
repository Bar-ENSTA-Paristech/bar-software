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
    VIEW.searchResults = this;
    this->setObjectName("searchResults");

    headers[0]->setText("Nom");
    headers[1]->setText("Prénom");
    headers[2]->setText("Cat.");
    headers[3]->setText("Solde");
    headers[4]->setText("Id");

    stretchColumns = new int[3];
    stretchColumns[0]=0;
    stretchColumns[1]=1;
    stretchColumns[2]=-1;
    defaultHeaderWidth = 70;
    hiddenColumn = 4;
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);

    QObject::connect(this, SIGNAL(rowFocusChanged(QModelIndex)), this, SLOT(lineClicked(QModelIndex)), Qt::QueuedConnection);
}

void SearchResults::setSearchResults(view_customerQueue & queue)
{
    // TUPLE : QString name, QString firstName, QString categorie, float balance, unsigned id
    view_customerTuple tuple;
    table->setModel(NULL);
    db_categoryQueue cat_queue = controller->getCustomerCategories();
    std::vector <db_categoryTuple> categories;
    int n = cat_queue.size();
    for(int i=0 ; i<n ; i++)
    {
        categories.push_back(cat_queue.front());
        cat_queue.pop();
    }

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
        model->item(i,1)->setText(tuple.getCustomerFirstName());
        if (tuple.getCustomerCategory() < categories.size())
            model->item(i,2)->setText(QString::fromStdString(categories[tuple.getCustomerCategory()].getCategoryName()));
        model->item(i,3)->setText(QString::number(balance));
        //model->item(i,3)->setData(QVariant(balance)); essai d'envoi du nombre pour corriger le problème du tri. rien ne s'affiche ...
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

void SearchResults::setFocus()
{
    table->setFocus();
}

void SearchResults::selectFocusedCustomer()
{
    if(table->hasFocus())
        lineClicked(table->currentIndex());
}
