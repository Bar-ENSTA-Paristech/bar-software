#include "searchresults.h"

SearchResults::SearchResults(QWidget *parent)
{
    setParent(parent);
    this->setObjectName("searchResults");

    QTableWidget *list = new QTableWidget(this);
    list->setSelectionBehavior(QAbstractItemView::SelectRows);
    list->setObjectName("searchResultsTable");
    list->setShowGrid(false);
    list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    QFont font;
    font.setStyleHint(QFont::SansSerif);
    font.setPixelSize(15);
    int columns = 4;
    int rows = 4;
    list->setColumnCount(columns);
    list->setRowCount(rows);

    QTableWidgetItem *headers = new QTableWidgetItem[columns];
    headers[0].setText("Nom");
    headers[1].setText("Prénom");
    headers[2].setText("Catégorie");
    headers[3].setText("Solde");
    for(int i=0 ; i < columns ; i++)
        list->setHorizontalHeaderItem(i, &headers[i]);

    list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i = 0 ; i< rows ; i++)
        list->setRowHeight(i, 20);

    QTableWidgetItem *emptyHeader = new QTableWidgetItem();
    emptyHeader->setText("");
    for(int i=0 ; i<rows ; i++)
        list->setVerticalHeaderItem(i, emptyHeader);
    QTableWidgetItem *test = new QTableWidgetItem;
    test->setText("prout");
    QTableWidgetItem *test2 = new QTableWidgetItem;
    test2->setText("maxi");
    list->setItem(1, 1, test);
    list->setItem(1, 0, test2);
    QBrush paintBottle(Qt::red);
    test->setForeground(paintBottle);
    test->setFont(font);


    list->resize(470, 300);
    qDebug() << this->width() << this->height();


}

void SearchResults::setSearchResults()
{
    list->resize(this->width(), this->height());

}
