#include "history.h"

History::History(QWidget *parent) : MultiList(parent, 6, 0, false)
{
    this->setObjectName("history"); // for CSS
    // ##### Definition des légendes en haut de colonne ######
    QTableWidgetItem *headers = new QTableWidgetItem[columns];
    headers[0].setText("Nom");
    headers[1].setText("Prénom");
    headers[2].setText("Opération");
    headers[3].setText("Montant");
    headers[4].setText("Date");
    headers[5].setText("id");
    for(int i=0 ; i < columns ; i++)// On assigne ces légendes au tableau
        list->setHorizontalHeaderItem(i, &headers[i]);
    // ##### Fin Définition #####

    // une colonne fait 60 pixels par défaut. Les colonnes 0,1,2,4 s'adapteront également à l'espace restant
    list->horizontalHeader()->setDefaultSectionSize(60);
    list->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    list->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    list->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    list->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    list->horizontalHeader()->setSectionHidden(5, true);
    list->horizontalHeader()->setSortIndicatorShown(false);

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
    qDebug() << itemList;
    QFont historyFont;
    historyFont.setPixelSize(11);
    for(int i=0 ; i<rows ; i++)
    {
        delete itemList[i];
    }
    if(isInitialised && rows !=0)
        delete itemList;
    else
        isInitialised = true;

    // Inserting new results
    QBrush color;
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
        itemList[i][1].setText(std::get<1>(tuple));
        itemList[i][2].setText(std::get<2>(tuple));
        itemList[i][3].setText(QString::number(std::get<3>(tuple)));
        itemList[i][4].setText(std::get<4>(tuple));
        itemList[i][5].setText(QString::number(i));
        if(std::get<2>(tuple) == "DEBIT")
            color.setColor(Qt::red);
        else if(std::get<2>(tuple) == "CREDIT")
            color.setColor("#008800");
        else
            color.setColor(Qt::black);

        for(int j=0 ; j < columns ; j++)
        {
            itemList[i][j].setFont(historyFont);
            itemList[i][j].setForeground(color);
            list->setItem(i, j, &itemList[i][j]);
        }
    }
    // Ascending or Descending depends on order of queue
    list->sortItems(5, Qt::AscendingOrder);
    return;
}
