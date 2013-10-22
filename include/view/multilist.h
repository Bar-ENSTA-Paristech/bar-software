#ifndef MULTILIST_H
#define MULTILIST_H

#include <QDebug>
#include <QFrame>
#include <QHeaderView>
#include <QTableWidget>
#include <QStandardItemModel>
#include <queue>

class Controller;

class MultiList : public QFrame
{
    Q_OBJECT
public:
    MultiList();
    MultiList(QWidget* parent = NULL, int column=0, int row=0, bool _isSortable=true);
    ~MultiList();
    void updateSize();

private slots:
    void sortItems(int index);

protected:
    int rows;
    int columns;
    int sortColumn;
    bool ascendingSort;
    bool isInitialised;
    bool isSortable;
    QTableWidget *list;
    QTableWidgetItem **itemList;
    QFont font;
    QTableWidgetItem *emptyHeader;
    void setRows(int numberOfRows);

};

#endif // MULTILIST_H
