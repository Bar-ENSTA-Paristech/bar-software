#ifndef INDIVIDUALHISTORY_H
#define INDIVIDUALHISTORY_H

#include <QWidget>
#include <QLabel>
#include <QStyleFactory>
#include "multilist.h"
#include "controller.h"
#include "structures.h"
#include "popup.h"

extern ViewObjects VIEW;
class IndividualHistoryList;

class IndividualHistory : public Popup
{
    Q_OBJECT
public:
    explicit IndividualHistory(QWidget *parent = 0);
    void launchIndividualHistory(view_histQueue& queue);
    void setController(Controller* controller);
    void resizeEvent(QResizeEvent *event);
    void setTitle(QString text);
    void setTotalConsummed(QString total);


private:
    IndividualHistoryList* history;
    QGridLayout* layout;
    Controller* controller;
    QLabel* title;
    QLabel* totalConsummedLabel;
    QLabel* totalConsummed;

    
signals:
    
public slots:
    
};

// #####################

class IndividualHistoryList : public MultiList
{
    Q_OBJECT
public:
    explicit IndividualHistoryList(QWidget *parent = 0);
    void launchIndividualHistory(view_histQueue& queue);


private:


signals:

public slots:

};

#endif // INDIVIDUALHISTORY_H
