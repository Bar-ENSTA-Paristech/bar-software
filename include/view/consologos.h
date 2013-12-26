#ifndef CONSOLOGOS_H
#define CONSOLOGOS_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QStyle>
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
    void newCategorieToController(int id);
    ~ConsoLogos();

private:
    QGridLayout* layout;
    QLabel* logos;
    QPushButton* logosLabels;
    QStyle* defaultStyle;

    
signals:
    
public slots:
    void logoClicked(int shortcutId = -1);
    
};

#endif // CONSOLOGOS_H
