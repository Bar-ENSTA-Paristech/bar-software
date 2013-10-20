#include "searchresults.h"

// Si Erreur bizarre ici, lancer un qmake sur le projet
MultiList::MultiList(QWidget *parent, int column, int row, bool _isSortable)
{
    setParent(parent);
    columns = column;
    rows = row;
    isInitialised = false;
    isSortable = _isSortable;
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
    list->horizontalHeader()->setSortIndicatorShown(isSortable);
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
    if(!isSortable)
        return;
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

    for(int i = 0 ; i< rows ; i++)
        list->setRowHeight(i, 20);

    for(int i=0 ; i<rows ; i++)
    {
        emptyHeader[i].setText("");
        list->setVerticalHeaderItem(i, emptyHeader);
    }
}

MultiList::~MultiList()
{
    for(int i = 0 ; i<rows ; i++)
    {
        delete itemList[i];
    }
    if(isInitialised && rows !=0)
        delete itemList;

    delete list;
    delete emptyHeader;
}
