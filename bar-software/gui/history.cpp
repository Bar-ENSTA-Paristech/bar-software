#include "history.h"

History::History(QWidget *parent) : MultiList(parent)
{
    this->setObjectName("history");
    QTableWidgetItem *headers = new QTableWidgetItem[columns];
    headers[0].setText("Nom");
    headers[1].setText("Prénom");
    headers[2].setText("Opération");
    headers[3].setText("Date");
    for(int i=0 ; i < columns ; i++)
        list->setHorizontalHeaderItem(i, &headers[i]);

    list->horizontalHeader()->setDefaultSectionSize(120);
    list->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    list->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    list->resize(470, 300);
}

void History::setHistory()
{

}
