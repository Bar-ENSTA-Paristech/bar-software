#ifndef HISTORY_H
#define HISTORY_H

#include "multilist.h"

class History : public MultiList
{
    Q_OBJECT
public:
    explicit History(QWidget *parent = 0);
    void setHistory();
    
signals:
    
public slots:
    
};

#endif // HISTORY_H
