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
    void updateHeadersSize(int defaultWidth, int *stretchColumns, int hiddenColumn = -1); // stretcColumns ends with value -1
    //QTableWidgetItem **headers;
    //QTableWidget *table;
    void setRows(int numberOfRows);
    void setController(Controller* _controller){controller = _controller;}


signals:
    void rowFocusChanged(QModelIndex);

private slots:
    void sortItems(int index);
    void lineEntered(QModelIndex index);

protected:
    int rows;
    int columns;
    int rowFocused;
    int sortColumn;
    int rowsAllocated;
    int defaultHeaderWidth;
    int hiddenColumn;
    int *stretchColumns;
    bool ascendingSort;
    bool isInitialised;
    bool isSortable;
    QTableView* table;
    QStandardItemModel* model;
    QHeaderView* horizontalHeader;
    QStandardItem** headers;

    QFont font;

};

#endif // MULTILIST_H
