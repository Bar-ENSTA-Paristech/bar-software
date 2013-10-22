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
    void setCustomer(std::tuple<QString, QString, QString, QString, float> &tuple);
    
private:
    QLabel *photo;
    QLabel* name;
    QLabel* firstName;
    QLabel* categorie;
    QLabel* balance;

signals:
    
public slots:
    
};

#endif // CUSTOMERPANEL_H
