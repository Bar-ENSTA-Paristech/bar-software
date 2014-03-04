#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QCheckBox>
#include <QRegExp>
#include <QErrorMessage>
#include "controller.h"
#include "popup.h"
#include "structures.h"

#define CALCULATOR_BUTTONS 13

extern ViewObjects VIEW;

class Calculator : public Popup
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator(){delete[] buttons;}
    void setController(Controller* controller);
    void launchCalculator();

private:
    Controller* controller;
    QLineEdit* sum;
    QFrame* buttonsFrame;
    QPushButton** buttons;
    QCheckBox* paidByCard;
    QGridLayout*  buttonsLayout;


signals:
    
public slots:
    void validate();
    void cancel();
    void buttonPushed();
    void sumEdited(QString str);
    
};

#endif // CALCULATOR_H
