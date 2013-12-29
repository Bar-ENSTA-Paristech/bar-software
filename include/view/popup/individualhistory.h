#ifndef INDIVIDUALHISTORY_H
#define INDIVIDUALHISTORY_H

#include <QWidget>
#include "multilist.h"
#include "controller.h"
#include "structures.h"

extern ViewObjects VIEW;

class IndividualHistory : public MultiList
{
    Q_OBJECT
public:
    explicit IndividualHistory(QWidget *parent = 0);
    void launchIndividualHistory(view_historyQueue& queue);
    void setController(Controller* controller);
    
signals:
    
public slots:
    
};

#endif // INDIVIDUALHISTORY_H
