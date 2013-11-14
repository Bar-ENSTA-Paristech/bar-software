#include "searchresults.h"
#include "controller.h"

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

    rowsAllocated=0;
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
    bool test = true;

    int old_rows = rows;
    /*if(isInitialised)
        old_rows = rows;
    else
        old_rows = 1000000;*
    isInitialised = true;*/
    rows = numberOfRows;

    // If we need more rows than we have already created, we launch an other salve of 500 rows to create
    if(numberOfRows > rowsAllocated)
    {qDebug() << "1";
        table->setRowCount(rowsAllocated+500);
        QTableWidgetItem** rowItems = new QTableWidgetItem*[columns];
        // allocating items for table
        for(int i = rowsAllocated ; i < rowsAllocated+500 ; i++)
        {
            for(int j=0 ; j<columns ; j++)
            {
                rowItems[j] = new QTableWidgetItem();
                table->setItem(i,j, rowItems[j]);
            }
            table->setRowHeight(i, 20);
            QTableWidgetItem* emptyHeader = new QTableWidgetItem();
            emptyHeader->setText("");
            table->setVerticalHeaderItem(i, emptyHeader);
            // setting extra rows invisible
            //if(i >= numberOfRows)
                //table->setRowHidden(i, true);
        }
        rowsAllocated += 500;
        // We reset visible the rows that were hidden and need to be use now
        for(int i= numberOfRows ; i < rowsAllocated ; i++)
            table->setRowHidden(i, true);

        delete[] rowItems;
    }
    else
    {
        for(int i=0 ; i < numberOfRows ; i++)
            table->setRowHidden(i, false);
        for(int i=numberOfRows ; i < rowsAllocated ; i++)
            table->setRowHidden(i, true);
    }
    /*// if there is fewer rows, we just hide the extra rows that were visible before
    else if(numberOfRows < old_rows)
    {qDebug() << "2";
        for(int i=numberOfRows ; i < rowsAllocated ; i++)
            table->setRowHidden(i, true);
    }
    else // if there is more rows than before but less than rows created, we just set the visible what we need
    {qDebug() << "3";
        for(int i=0 ; i < numberOfRows ; i++)
        {
            table->setRowHidden(i, false);
        }
    }*/
return;
}


MultiList::~MultiList()
{

    delete table;
    delete[] headers;
}

