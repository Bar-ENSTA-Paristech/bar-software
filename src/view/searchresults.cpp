#include "searchresults.h"


SearchResults::SearchResults(QWidget *parent) :
    MultiList(parent, 5, 0)
{
    this->setObjectName("searchResults");

    headers[0]->setText("Nom");
    headers[1]->setText("Prénom");
    headers[2]->setText("Catégorie");
    headers[3]->setText("Solde");
    headers[4]->setText("Id");
    for(int i=0 ; i < columns ; i++)
        table->setHorizontalHeaderItem(i, headers[i]);

    table->horizontalHeader()->setDefaultSectionSize(70);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionHidden(4, true);

    QObject::connect(table, SIGNAL(cellClicked(int, int)), this, SLOT(lineClicked(int, int)));

    // ####### TEST #######
    /*std::queue< std::tuple< QString, QString, QString, float, unsigned > > toto;
    std::tuple< QString, QString, QString, float, unsigned > titi("Chat", "Mehdi", "2015", -2, 1);
    std::tuple< QString, QString, QString, float, unsigned > titi2("Diallo", "Guytoof", "2015", 3.5, 2);
    toto.push(titi);
    toto.push(titi2);
    this->setSearchResults(toto);*/
    // ####### FIN TEST #######

}

void SearchResults::setSearchResults(std::queue< std::tuple< QString, QString, QString, float, unsigned > > & queue)
{
    // TUPLE : QString name, QString firstName, QString categorie, float balance, unsigned id
    std::tuple< QString, QString, QString, float, unsigned > tuple;

    // Inserting new results
    QBrush negativeSold(Qt::red);
    QBrush positiveSold(Qt::black);
    float balance = 0;
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
            QTableWidgetItem* item4 = new QTableWidgetItem();

            table->setItem(i, 0, item0);
            table->setItem(i, 1, item1);
            table->setItem(i, 2, item2);
            table->setItem(i, 3, item3);
            table->setItem(i, 4, item4);
        }
    }
    for(unsigned i=0 ; i<numberOfElements ; i++)
    {
        tuple = queue.front();
        queue.pop();
        table->item(i,0)->setText(std::get<0>(tuple));
        table->item(i,1)->setText(std::get<1>(tuple));
        table->item(i,2)->setText(std::get<2>(tuple));
        balance = std::get<3>(tuple);
        table->item(i,3)->setText(QString::number(balance));
        if(balance < 0)
            table->item(i,3)->setForeground(negativeSold);
        else
            table->item(i,3)->setForeground(positiveSold);
        table->item(i,4)->setText(QString::number(std::get<4>(tuple)));
    }
    table->sortItems(0, Qt::AscendingOrder);
    return;
}

void SearchResults::lineClicked(int row, int column)
{
    controller->newClic_Customer((unsigned) table->item(row,4)->text().toInt());
}
