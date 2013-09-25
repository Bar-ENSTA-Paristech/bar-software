#include "searchresults.h"

// Si Erreur bizarre ici, lancer un qmake sur le projet
MultiList::MultiList(QWidget *parent, int column, int row)
{
    setParent(parent);
    columns = column;
    rows = row;
    isInitialised = false;
    list = new QTableWidget(this);
    list->setSelectionBehavior(QAbstractItemView::SelectRows);
    list->setObjectName("multiListTable");
    list->setShowGrid(false);
    list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    font.setStyleHint(QFont::SansSerif);
    font.setPixelSize(15);
    list->setColumnCount(columns);
    emptyHeader = new QTableWidgetItem[1000];
    setRows(rows);

    ascendingSort = true;
    sortColumn = 0;
    list->sortItems(0, Qt::AscendingOrder);

    if(rows)
        itemList = new QTableWidgetItem*[rows];
    for(int i=0 ; i<rows ; i++)
    {
        itemList[i] = new QTableWidgetItem[columns];
    }

    QObject::connect(list->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortItems(int)));
}



void MultiList::sortItems(int index)
{
    if(index == sortColumn)
        ascendingSort = !ascendingSort;
    else
    {
        ascendingSort = true;
        sortColumn = index;
    }
    if(ascendingSort)
        list->sortItems(index, Qt::AscendingOrder);
    else
        list->sortItems(index, Qt::DescendingOrder);

}

void MultiList::updateSize()
{
    list->resize(this->width(), this->height());
}

void MultiList::setRows(int numberOfRows)
{
    rows = numberOfRows;
    list->setRowCount(rows);

    list->horizontalHeader()->setSortIndicatorShown(true);
    for(int i = 0 ; i< rows ; i++)
        list->setRowHeight(i, 20);

    for(int i=0 ; i<rows ; i++)
    {
        emptyHeader[i].setText("");
        list->setVerticalHeaderItem(i, emptyHeader);
    }
}
