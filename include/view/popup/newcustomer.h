#ifndef NEWCUSTOMER_H
#define NEWCUSTOMER_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include "structures.h"
#include "controller.h"
#include "popup.h"
extern ViewObjects VIEW;

class NewCustomer : public Popup
{
    Q_OBJECT
public:
    explicit NewCustomer(QWidget *parent = 0);
    void launchNewCustomer(std::vector<QString> categories);
    //void setController(Controller* controller);
    
signals:
    
private:
    QLabel* nameLabel;
    QLabel* firstNameLabel;
    QLabel* loginLabel;
    QLabel* categorieLabel;
    QLabel* balanceLabel;
    QLineEdit* name;
    QLineEdit* firstName;
    QLineEdit* login;
    QLineEdit* balance;
    QComboBox* categorie;
    QGridLayout* layout;
    QPushButton* validateButton;
    QPushButton* cancelButton;

    //Controller* controller;
    view_customerTuple tmpCustomer;


public slots:
    void validate();
    void cancel();
    
};

#endif // NEWCUSTOMER_H
