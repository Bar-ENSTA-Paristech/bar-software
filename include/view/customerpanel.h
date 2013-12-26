#ifndef CUSTOMERPANEL_H
#define CUSTOMERPANEL_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <tuple>
#include <QDebug>
#include <QFile>
#include "controller.h"

extern QString GLOBAL_PATH;

class db_categoryTuple;
class db_customerTuple;
class db_histTuple;
class db_productTuple;

class view_customerTuple;
class view_productTuple;

class Controller;
class CustomerPanel : public QFrame
{
    Q_OBJECT
public:
    Controller* controller;
    explicit CustomerPanel(QWidget *parent = 0);
    ~CustomerPanel();
    void setCustomer(view_customerTuple &tuple);
    void setFuturBalance(float nextBalance);
    
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
    QLabel* nameLabel;
    QLabel* firstNameLabel;
    QLabel* loginLabel;
    QLabel* categorieLabel;
    QLabel* balanceLabel;

signals:
    
public slots:
    
};

#endif // CUSTOMERPANEL_H
