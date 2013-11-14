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
    std::queue< std::tuple< QString, QString, QString, float, unsigned > > toto;
    std::tuple< QString, QString, QString, float, unsigned > titi("Chat", "Mehdi", "2015", -2, 1);
    std::tuple< QString, QString, QString, float, unsigned > titi2("Diallo", "Guytoof", "2015", 3.5, 2);
    toto.push(titi);
    toto.push(titi2);
    this->setSearchResults(toto);
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
    timer.start(10000);
    setRows(numberOfElements);
    qDebug() << "Fin setRows" << 10000-timer.remainingTime() << "ms";

    for(unsigned i=0 ; i<numberOfElements ; i++)
    {
        tuple = queue.front();
        queue.pop();
        balance = std::get<3>(tuple);
        if(balance < 0)
            table->item(i,3)->setForeground(negativeSold);
        else
            table->item(i,3)->setForeground(positiveSold);
        /*table->item(i,0)->setData(Qt::DisplayRole, std::get<0>(tuple));
        table->item(i,1)->setData(Qt::DisplayRole, std::get<1>(tuple));
        table->item(i,2)->setData(Qt::DisplayRole, std::get<2>(tuple));
        table->item(i,3)->setData(Qt::DisplayRole, QString::number(balance));
        table->item(i,4)->setData(Qt::DisplayRole, QString::number(std::get<4>(tuple)));*/
        table->item(i,0)->setText(std::get<0>(tuple));
        table->item(i,1)->setText(std::get<1>(tuple));
        table->item(i,2)->setText(std::get<2>(tuple));
        table->item(i,3)->setText(QString::number(balance));
        table->item(i,4)->setText(QString::number(std::get<4>(tuple)));
    }qDebug() << "Fin setText" << 10000-timer.remainingTime() << "ms";
    table->sortItems(0, Qt::AscendingOrder);
    return;
}

void SearchResults::lineClicked(int row, int column)
{
    controller->newClic_Customer((unsigned) table->item(row,4)->text().toInt());
}
