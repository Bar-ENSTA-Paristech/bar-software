#include "history.h"

History::History(QWidget *parent) : MultiList(parent, 6, 0, false)
{
    this->setObjectName("history"); // for CSS
    // ##### Definition des légendes en haut de colonne ######
    headers[0]->setText("Nom");
    headers[1]->setText("Prénom");
    headers[2]->setText("Opération");
    headers[3]->setText("Montant");
    headers[4]->setText("Date");
    headers[5]->setText("id");
    for(int i=0 ; i < columns ; i++)// On assigne ces légendes au tableau
        table->setHorizontalHeaderItem(i, headers[i]);
    // ##### Fin Définition #####

    // une colonne fait 60 pixels par défaut. Les colonnes 0,1,2,4 s'adapteront également à l'espace restant
    table->horizontalHeader()->setDefaultSectionSize(60);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionHidden(5, true);
    table->horizontalHeader()->setSortIndicatorShown(false);

    // ####### TEST #######
    std::queue< std::tuple< QString, QString, QString, float, QString > > toto;
    std::tuple< QString, QString, QString, float, QString > titi("Chat", "Mehdi", "DEBIT", -1000, "17h45 24-09-2013");
    std::tuple< QString, QString, QString, float, QString > titi2("Diallo", "Guytoof", "CREDIT", 20, "17h44 24-09-2013");
    std::tuple< QString, QString, QString, float, QString > titi3("Manchoul", "Simon", "Duvel 33cL", 1.9, "17h41 24-09-2013");
    toto.push(titi);
    toto.push(titi2);
    toto.push(titi3);
    this->setHistory(toto);
    // ####### FIN TEST #######

}

void History::setHistory(std::queue < std::tuple < QString, QString, QString, float, QString > > & queue)
{
    //TUPLE : QString name, QString firstName, QString operation, float value, QString date(hh-mm JJ-MM-YYYY)
    // Deleting old results
    std::tuple < QString, QString, QString, float, QString > tuple;
    QFont historyFont;
    historyFont.setPixelSize(11);

    // Inserting new results
    QBrush color;
    unsigned numberOfElements = queue.size();
    unsigned rows_old = rows;
    setRows(numberOfElements);

    // If there are more rows than before, we allocate space for the items and set them to the table
    if(numberOfElements > rows_old)
    {
        for(unsigned i=rows_old ; i<numberOfElements ; i++)
        {
            tuple = queue.front();
            queue.pop();
            QTableWidgetItem* item0 = new QTableWidgetItem();
            QTableWidgetItem* item1 = new QTableWidgetItem();
            QTableWidgetItem* item2 = new QTableWidgetItem();
            QTableWidgetItem* item3 = new QTableWidgetItem();
            QTableWidgetItem* item4 = new QTableWidgetItem();
            QTableWidgetItem* item5 = new QTableWidgetItem();

            table->setItem(i, 0, item0);
            table->setItem(i, 1, item1);
            table->setItem(i, 2, item2);
            table->setItem(i, 3, item3);
            table->setItem(i, 4, item4);
            table->setItem(i, 5, item5);

            item0->setText(std::get<0>(tuple));
            item1->setText(std::get<1>(tuple));
            item2->setText(std::get<2>(tuple));
            item3->setText(QString::number(std::get<3>(tuple)));
            item4->setText(std::get<4>(tuple));
            item5->setText(QString::number(i));
            if(std::get<2>(tuple) == "DEBIT")
                color.setColor(Qt::red);
            else if(std::get<2>(tuple) == "CREDIT")
                color.setColor("#008800");
            else
                color.setColor(Qt::black);

            for(int j=0 ; j < columns ; j++)
            {
                table->item(i,j)->setFont(historyFont);
                table->item(i,j)->setForeground(color);
            }
        }
    }

    // Ascending or Descending depends on order of queue
    table->sortItems(5, Qt::AscendingOrder);
    return;
}
