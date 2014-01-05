#ifndef EDITCUSTOMER_H
#define EDITCUSTOMER_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include "structures.h"
#include "controller.h"
extern ViewObjects VIEW;

class EditCustomer : public QWidget
{
    Q_OBJECT
public:
    explicit EditCustomer(QWidget *parent = 0);
    void launchEditCustomer(view_customerTuple& customer, std::vector<QString> categories);
    void setController(Controller* controller);
    
signals:
    
private:
    QLabel* nameLabel;
    QLabel* firstNameLabel;
    QLabel* loginLabel;
    QLabel* categorieLabel;
    QLineEdit* name;
    QLineEdit* firstName;
    QLineEdit* login;
    QComboBox* categorie;
    QGridLayout* layout;
    QPushButton* validateButton;
    QPushButton* cancelButton;

    Controller* controller;
    view_customerTuple tmpCustomer;


public slots:
    void validate();
    void cancel();
    
};

#endif // EDITCUSTOMER_H
