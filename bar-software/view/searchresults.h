#ifndef SEARCHRESULTS_H
#define SEARCHRESULTS_H

#include <QFrame>
#include <tuple>
#include <queue>
#include "multilist.h"

class SearchResults : public MultiList
{
    Q_OBJECT
public:
    explicit SearchResults(QWidget *parent = 0);

    // receive search results from controller
    virtual void setSearchResults(std::queue<std::tuple<QString, QString, QString, float, unsigned>>& queue);

private:


signals:
    
public slots:
    
};

#endif // SEARCHRESULTS_H
