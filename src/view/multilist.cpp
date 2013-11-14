#include "searchresults.h"
#include "controller.h"
#include <unistd.h>

// Si Erreur bizarre ici, lancer un qmake sur le projet
MultiList::MultiList(QWidget *parent, int column, int row, bool _isSortable)
{
    setParent(parent);
    columns = column;
    rows = row;
    isInitialised = false;
    isSortable = _isSortable;
    // because headers mustn't be in a tab and be made with operator new()
    headers = new QTableWidgetItem*[columns];
    for(int i=0 ; i< columns ; i++)
        headers[i] = new QTableWidgetItem();
    table = new QTableWidget(this);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setObjectName("multiListTable");
    table->setShowGrid(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    font.setStyleHint(QFont::SansSerif);
    font.setPixelSize(13);
    table->setColumnCount(columns);
    table->horizontalHeader()->setSortIndicatorShown(isSortable);
    for(int i=0 ; i<columns ; i++)
        headers[i]->setFont(font);
    setRows(rows);

    ascendingSort = true;
    sortColumn = 0;
    table->sortItems(0, Qt::AscendingOrder);

    QObject::connect(table->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortItems(int)));
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
        table->sortItems(index, Qt::AscendingOrder);
    else
        table->sortItems(index, Qt::DescendingOrder);

}

void MultiList::updateSize()
{
    table->resize(this->width(), this->height());
}

void MultiList::setRows(int numberOfRows)
{
    if(numberOfRows == rows)
        return;
    int old_rows = rows;
    rows = numberOfRows;
    table->setRowCount(rows);

    for(int i = 0 ; i< rows ; i++)
    {
        table->setRowHeight(i, 20);

        QTableWidgetItem* emptyHeader = new QTableWidgetItem();
        emptyHeader->setText("");
        table->setVerticalHeaderItem(i, emptyHeader);
    }
}


MultiList::~MultiList()
{

    delete table;
    delete[] headers;
}

