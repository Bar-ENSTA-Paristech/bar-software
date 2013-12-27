#ifndef MULTILIST_H
#define MULTILIST_H

#include <QDebug>
#include <QFrame>
#include <QHeaderView>
#include <QTableWidget>
#include <QStandardItemModel>
#include <queue>
#include <QTimer>
#include <QStandardItemModel>


class Controller;

class MultiList : public QFrame
{
    Q_OBJECT
public:
    Controller* controller;
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
    int rowsAllocated;
    int defaultHeaderWidth;
    int hiddenColumn;
    int *stretchColumns;
    bool ascendingSort;
    bool isInitialised;
    bool isSortable;
    void updateHeadersSize(int defaultWidth, int *stretchColumns, int hiddenColumn = -1); // stretcColumns ends with value -1
    //QTableWidgetItem **headers;
    //QTableWidget *table;
    QTableView* table;
    QStandardItemModel* model;
    QHeaderView* horizontalHeader;
    QStandardItem** headers;

    QFont font;
    void setRows(int numberOfRows);

};

#endif // MULTILIST_H
