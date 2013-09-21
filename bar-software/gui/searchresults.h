#ifndef SEARCHRESULTS_H
#define SEARCHRESULTS_H

#include <QDebug>
#include <QFrame>
#include <QHeaderView>
#include <QListView>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QTreeWidget>

class SearchResults : public QFrame
{
public:
    SearchResults(QWidget* parent = NULL);
    void setSearchResults();

private:
    int rows;
    int columns;
};

#endif // SEARCHRESULTS_H
