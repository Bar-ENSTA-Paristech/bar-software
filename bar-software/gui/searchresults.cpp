#include "searchresults.h"

SearchResults::SearchResults(QWidget *parent) :
    MultiList(parent)
{
    this->setObjectName("searchResults");
    QTableWidgetItem *headers = new QTableWidgetItem[columns];
    headers[0].setText("Nom");
    headers[1].setText("Prénom");
    headers[2].setText("Catégorie");
    headers[3].setText("Solde");
    for(int i=0 ; i < columns ; i++)
        list->setHorizontalHeaderItem(i, &headers[i]);

    QTableWidgetItem *test = new QTableWidgetItem;
    test->setText("prout");
    QTableWidgetItem *test2 = new QTableWidgetItem;
    test2->setText("maxi");
    QTableWidgetItem *test3 = new QTableWidgetItem;
    test3->setText("Chat");
    QTableWidgetItem *test4 = new QTableWidgetItem;
    test4->setText("Mehdi");
    list->setItem(1, 1, test);
    list->setItem(1, 0, test2);
    list->setItem(0, 1, test4);
    list->setItem(0, 0, test3);
    QBrush negativeSold(Qt::red);
    test->setForeground(negativeSold);
    test->setFont(font);

    list->resize(470, 300);
}

void SearchResults::setSearchResults(Customer* customers, int numberOfResults)
{
    list->resize(this->width(), this->height());
    // Deleting old results
    for(int i = 0 ; i<rows ; i++)
    {
        for(int j=0 ; j<columns ; j++)
            break;
            //delete itemList[i][j];
        // supprimer les vieux resultats
    }


    // Inserting new results
    itemList = new QTableWidgetItem*[numberOfResults];
    for(int i = 0 ; i<numberOfResults ; i++)
    {
        itemList[i] = new QTableWidgetItem[columns];
    }
    for(int i=0 ; i<numberOfResults ; i++)
    {
        // Setting texts
        break;
    }

}
