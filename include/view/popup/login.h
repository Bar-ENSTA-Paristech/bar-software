#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QRegExp>
#include <QErrorMessage>
#include "controller.h"
#include "popup.h"
#include "structures.h"

extern ViewObjects VIEW;

class Controller;

class Login : public Popup
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = 0);
    void setController(Controller* controller);
    void checkIndividual();
    void checkGlobal();
    void checkRoot();

private:
    Controller* controller;
    QLineEdit* login;
    QLineEdit* passwd;
    QLabel* loginLabel;
    QLabel* passwdLabel;
    QLabel* label;
    LoginType loginType;


signals:
    
public slots:
    void validate();
    void cancel();
    
};

#endif // CALCULATOR_H
