#ifndef MULTILIST_H
#define MULTILIST_H

#include <QDebug>
#include <QFrame>
#include <QHeaderView>
#include <QTableWidget>
#include <QStandardItemModel>
#include <queue>
#include "../customer.h"

class MultiList : public QFrame
{
    Q_OBJECT
public:
    MultiList();
    MultiList(QWidget* parent = NULL);
    void updateSize();

private slots:
    void sortItems(int index);

protected:
    int rows;
    int columns;
    int sortColumn;
    bool ascendingSort;
    QTableWidget *list;
    QTableWidgetItem **itemList;
    QFont font;

};

#endif // MULTILIST_H
