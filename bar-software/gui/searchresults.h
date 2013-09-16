#ifndef SEARCHRESULTS_H
#define SEARCHRESULTS_H

#include <QDebug>
#include <QFrame>
#include <QListView>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QTreeWidget>

class SearchResults : public QFrame
{
public:
    SearchResults(QWidget* parent = NULL);
    void setSearchResults();
};

#endif // SEARCHRESULTS_H
