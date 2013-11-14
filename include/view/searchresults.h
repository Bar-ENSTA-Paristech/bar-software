#ifndef SEARCHRESULTS_H
#define SEARCHRESULTS_H

#include <QFrame>
#include <tuple>
#include <queue>
#include "multilist.h"
#include "controller.h"

class Controller;

class SearchResults : public MultiList
{
    Q_OBJECT
public:
    explicit SearchResults(QWidget *parent = 0);

    // receive search results from controller
    void setSearchResults(std::queue< std::tuple< QString, QString, QString, float, unsigned > >& queue);
    QTimer timer;

signals:
    
private slots:
    void lineClicked(int row, int column);
    
};

#endif // SEARCHRESULTS_H
