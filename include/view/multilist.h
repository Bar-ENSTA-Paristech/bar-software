#ifndef MULTILIST_H
#define MULTILIST_H

#include <QDebug>
#include <QFrame>
#include <QHeaderView>
#include <QTableWidget>
#include <QStandardItemModel>
#include <queue>
#include <QTimer>

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
    bool ascendingSort;
    bool isInitialised;
    bool isSortable;
    QTableWidgetItem **headers;
    QTableWidget *table;
    QFont font;
    void setRows(int numberOfRows);

};

#endif // MULTILIST_H
