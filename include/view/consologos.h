#ifndef CONSOLOGOS_H
#define CONSOLOGOS_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include "controller.h"

#define NUMBER_OF_CONSUMPTION_TYPES 6

extern QString GLOBAL_PATH;

class Controller;
class ConsoLogos : public QFrame
{
    Q_OBJECT
public:
    Controller* controller;
    explicit ConsoLogos(QWidget *parent = 0);
    ~ConsoLogos();

private:
    QGridLayout* layout;
    QLabel* logos;
    QLabel* logosLabels;

    
signals:
    
public slots:
    
};

#endif // CONSOLOGOS_H
