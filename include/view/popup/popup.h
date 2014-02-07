#ifndef POPUP_H
#define POPUP_H

#include <QWidget>
#include <QShortcut>
#include <QRegExp>
#include <QErrorMessage>
//#include "controller.h"

class Controller;

class Popup : public QWidget
{
    Q_OBJECT
public:
    explicit Popup(QWidget *parent = 0);
    bool isBalanceCorrect(QString value);
    bool isUInteger(QString value);
    bool isInteger(QString value);
    void setController(Controller* controller);
    
signals:
    
protected:
    QShortcut *Enter;
    QShortcut *Return;
    QShortcut *Escape;

    QErrorMessage* error;

    Controller* controller;

public slots:
    virtual void validate(){};
    virtual void cancel(){this->hide();};
    
};

#endif // POPUP_H
