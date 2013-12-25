#ifndef SEARCHRESULTS_H
#define SEARCHRESULTS_H

#include <QFrame>
#include <tuple>
#include <queue>
#include "multilist.h"
#include "controller.h"
#include "structures.h"

class Controller;

class SearchResults : public MultiList
{
    Q_OBJECT
public:
    explicit SearchResults(QWidget *parent = 0);

    // receive search results from controller
    void setSearchResults(view_customerQueue&);
    QTimer timer;

signals:
    
private slots:
    void lineClicked(QModelIndex index);
    
};

#endif // SEARCHRESULTS_H
