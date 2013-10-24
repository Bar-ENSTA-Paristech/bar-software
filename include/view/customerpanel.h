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

class Controller;
class CustomerPanel : public QFrame
{
    Q_OBJECT
public:
    Controller* controller;
    explicit CustomerPanel(QWidget *parent = 0);
    ~CustomerPanel();
    void setCustomer(std::tuple<QString, QString, QString, QString, float> &tuple);
    
private:
    QLabel *photo;
    QLabel* name;
    QLabel* firstName;
    QLabel* categorie;
    QLabel* balance;
    QFrame* photoFrame;
    QFrame* infosFrame;
    QFrame* optionsFrame;
    QGridLayout* layout;
    QGridLayout* photoLayout;
    QGridLayout* infosLayout;
    QLabel* nameLabel;
    QLabel* firstNameLabel;
    QLabel* categorieLabel;
    QLabel* balanceLabel;

signals:
    
public slots:
    
};

#endif // CUSTOMERPANEL_H
