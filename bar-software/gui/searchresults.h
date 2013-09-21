#ifndef SEARCHRESULTS_H
#define SEARCHRESULTS_H

#include <QFrame>
#include "multilist.h"

class SearchResults : public MultiList
{
    Q_OBJECT
public:
    explicit SearchResults(QWidget *parent = 0);
    void setSearchResults(Customer* customers, int numberOfResults);

signals:
    
public slots:
    
};

#endif // SEARCHRESULTS_H
