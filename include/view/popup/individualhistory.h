#ifndef INDIVIDUALHISTORY_H
#define INDIVIDUALHISTORY_H

#include <QWidget>
#include "multilist.h"
#include "controller.h"
#include "structures.h"

extern ViewObjects VIEW;
class IndividualHistoryList;

class IndividualHistory : public QWidget
{
    Q_OBJECT
public:
    explicit IndividualHistory(QWidget *parent = 0);
    void launchIndividualHistory(view_historyQueue& queue);
    void setController(Controller* controller);
    void resizeEvent(QResizeEvent *event);


private:
    IndividualHistoryList* history;
    QGridLayout* layout;
    Controller* controller;

    
signals:
    
public slots:
    
};

// #####################

class IndividualHistoryList : public MultiList
{
    Q_OBJECT
public:
    explicit IndividualHistoryList(QWidget *parent = 0);


private:


signals:

public slots:

};

#endif // INDIVIDUALHISTORY_H
