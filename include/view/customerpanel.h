#ifndef CUSTOMERPANEL_H
#define CUSTOMERPANEL_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <tuple>
#include <QDebug>
#include <QFile>
#include "controller.h"
#include "calculator.h"
#include "structures.h"
extern ViewObjects VIEW;

extern QString GLOBAL_PATH;

class db_categoryTuple;
class db_customerTuple;
class db_histTuple;
class db_productTuple;

class view_customerTuple;
class view_productTuple;

class Controller;
class Calculator;
class CustomerPanel : public QFrame
{
    Q_OBJECT
public:
    Controller* controller;
    explicit CustomerPanel(QWidget *parent = 0);
    ~CustomerPanel();
    void setCustomer(view_customerTuple &tuple);
    void setFuturBalance(float nextBalance);
    void setController(Controller* controllerPar);
    
private:
    QLabel *photo;
    QLabel* name;
    QLabel* firstName;
    QLabel* login;
    QLabel* categorie;
    QLabel* balance;
    QLabel* futurBalance;
    QFrame* photoFrame;
    QFrame* infosFrame;
    QFrame* optionsFrame;
    QGridLayout* layout;
    QGridLayout* photoLayout;
    QGridLayout* infosLayout;
    QGridLayout* optionsLayout;
    QLabel* nameLabel;
    QLabel* firstNameLabel;
    QLabel* loginLabel;
    QLabel* categorieLabel;
    QLabel* balanceLabel;
    QPushButton* calculator;
    QPushButton* history;;


signals:
    
public slots:
    void launchCalculator();
    void launchIndividualHistory();
    
};

#endif // CUSTOMERPANEL_H
