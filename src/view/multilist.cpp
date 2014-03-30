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

    //table = new QTableWidget(this);
    table = new QTableView(this);
    model = new QStandardItemModel(this);
    model->setColumnCount(columns);
    table->setModel(model);

    // because headers mustn't be in a tab and be made with operator new()
    headers = new QStandardItem*[columns];
        for(int i=0 ; i< columns ; i++)
        {
            headers[i] = new QStandardItem();
            model->setHorizontalHeaderItem(i,headers[i]);
        }

    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setObjectName("multiListTable");
    table->setShowGrid(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    table->setSortingEnabled(isSortable);

    font.setStyleHint(QFont::SansSerif);
    font.setPixelSize(13);

    for(int i=0 ; i<columns ; i++)
        headers[i]->setFont(font);

    rowsAllocated=0;
    setRows(rows);

    ascendingSort = true;
    sortColumn = 0;
    //table->sortItems(0, Qt::AscendingOrder);
    model->sort(0, Qt::AscendingOrder);
    //table->setAlternatingRowColors(true);

    QObject::connect(table, SIGNAL(clicked(QModelIndex)), this, SLOT(lineEntered(QModelIndex)));
    QObject::connect(table, SIGNAL(entered(QModelIndex)), this, SLOT(lineEntered(QModelIndex)));

    //QObject::connect(table->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortItems(int)));
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
        //table->sortItems(index, Qt::AscendingOrder);
        model->sort(index, Qt::AscendingOrder);
    else
        //table->sortItems(index, Qt::DescendingOrder);
        model->sort(index, Qt::AscendingOrder);

}

void MultiList::updateSize()
{
    table->resize(this->width(), this->height());
}

void MultiList::setRows(int numberOfRows)
{
    if(numberOfRows == rows)
        return;
    bool newRows = false;

    //int old_rows = rows;
    rows = numberOfRows;

    // If we need more rows than we have already created, we launch an other salve of 500 rows to create
    while(numberOfRows > rowsAllocated)
    {
        newRows = true;
        //table->setRowCount(rowsAllocated+500);
        model->setRowCount(rowsAllocated+500);
        //QTableWidgetItem** rowItems = new QTableWidgetItem*[columns];
        QStandardItem** rowItems = new QStandardItem*[columns];
        // allocating items for table
        for(int i = rowsAllocated ; i < rowsAllocated+500 ; i++)
        {
            for(int j=0 ; j<columns ; j++)
            {
                rowItems[j] = new QStandardItem();
                model->setItem(i,j, rowItems[j]);
            }
            table->setRowHeight(i, 20);
            QStandardItem *verticalHeader = new QStandardItem();
            verticalHeader->setText("");
            model->setVerticalHeaderItem(i,verticalHeader);
        }
        rowsAllocated += 500;
        // We reset visible the rows that were hidden and need to be use now
        for(int i= numberOfRows ; i < rowsAllocated ; i++)
            table->setRowHidden(i, true);

        delete[] rowItems;
    }
    if(!newRows)
    {// ############## FACTORING
        for(int i=0 ; i < numberOfRows ; i++)
            table->setRowHidden(i, false);
        for(int i=numberOfRows ; i < rowsAllocated ; i++)
            table->setRowHidden(i, true);
        //updateHeadersSize(defaultHeaderWidth, stretchColumns);
    }
return;
}

//in stretchColumns we put the columns that will stretch the remaining place. We know we reach end of array because there is a -1 at end (as \0 with strings)
// if hiddenColumn >= 0 this column will be hidden, nothing will happen otherwise
void MultiList::updateHeadersSize(int defaultWidth, int* stretchColumns, int hiddenColumn)
{
    table->horizontalHeader()->setDefaultSectionSize(defaultWidth);
    table->horizontalHeader()->setHighlightSections(false);

    table->verticalHeader()->setVisible(false);


    if(hiddenColumn >= 0)
        table->setColumnHidden(hiddenColumn, true);
    for(int i = 0 ; stretchColumns!=NULL && stretchColumns[i] >= 0 ; i++)
        table->horizontalHeader()->setSectionResizeMode(stretchColumns[i], QHeaderView::Stretch);

    for(int i=0 ; i < rowsAllocated ; i++)
        table->setRowHeight(i, 20);

    for(int i=0 ; i < rows ; i++)
        table->setRowHidden(i, false);

    for(int i=rows ; i < rowsAllocated ; i++)
        table->setRowHidden(i, true);
}

void MultiList::lineEntered(QModelIndex index)
{
    rowFocused = index.row();
    emit rowFocusChanged(index);
}


MultiList::~MultiList()
{
    delete[] stretchColumns;
    delete[] headers;
}

