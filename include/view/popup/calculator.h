#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QRegExp>
#include <QErrorMessage>
#include "controller.h"
#include "structures.h"

#define CALCULATOR_BUTTONS 13

extern ViewObjects VIEW;

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = 0);
    void setController(Controller* controller);
    void launchCalculator();

private:
    Controller* controller;
    QLineEdit* sum;
    QFrame* buttonsFrame;
    QPushButton** buttons;
    QGridLayout*  buttonsLayout;


signals:
    
public slots:
    void validate();
    void cancel();
    void buttonPushed();
    
};

#endif // CALCULATOR_H
