#include "searchresults.h"

// Si Erreur bizarre ici, lancer un qmake sur le projet
MultiList::MultiList(QWidget *parent)
{
    setParent(parent);

    list = new QTableWidget(this);
    list->setSelectionBehavior(QAbstractItemView::SelectRows);
    list->setObjectName("multiListTable");
    list->setShowGrid(false);
    list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    font.setStyleHint(QFont::SansSerif);
    font.setPixelSize(15);
    // ####### TEST #####
    columns = 4;
    rows = 4;
    // ####### FIN TEST ####
    list->setColumnCount(columns);
    list->setRowCount(rows);

    list->horizontalHeader()->setSortIndicatorShown(true);
    for(int i = 0 ; i< rows ; i++)
        list->setRowHeight(i, 20);

    QTableWidgetItem *emptyHeader = new QTableWidgetItem[1000];
    for(int i=0 ; i<rows ; i++)
    {
        emptyHeader[i].setText("");
        list->setVerticalHeaderItem(i, emptyHeader);
    }

    // TEST
    ascendingSort = true;
    sortColumn = 0;
    list->sortItems(0, Qt::AscendingOrder);

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
    qDebug() << this->width() << this->height();
}