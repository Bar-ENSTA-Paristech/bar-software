#ifndef GlobalHISTORY_H
#define GlobalHISTORY_H

#include <QWidget>
#include <QLabel>
#include <QStyleFactory>
#include "multilist.h"
#include "controller.h"
#include "structures.h"

extern ViewObjects VIEW;
class GlobalHistoryList;

class GlobalHistory : public QWidget
{
    Q_OBJECT
public:
    explicit GlobalHistory(QWidget *parent = 0);
    void launchGlobalHistory(view_histQueue& queue);
    void setController(Controller* controller);
    void resizeEvent(QResizeEvent *event);


private:
    GlobalHistoryList* history;
    QGridLayout* layout;
    Controller* controller;

    
signals:
    
public slots:
    
};

// #####################

class GlobalHistoryList : public MultiList
{
    Q_OBJECT
public:
    explicit GlobalHistoryList(QWidget *parent = 0);
    void launchGlobalHistory(view_histQueue& queue);


private:


signals:

public slots:

};

#endif // GlobalHISTORY_H
