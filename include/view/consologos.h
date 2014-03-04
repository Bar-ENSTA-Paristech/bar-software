#ifndef CONSOLOGOS_H
#define CONSOLOGOS_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QStyle>
#include <QFile>
#include "controller.h"
#include "structures.h"
extern ViewObjects VIEW;
extern QString GLOBAL_PATH;

#define NUMBER_OF_CONSUMPTION_TYPES 6

extern QString GLOBAL_PATH;

class Controller;
class ConsoLogos : public QFrame
{
    Q_OBJECT
public:
    explicit ConsoLogos(QWidget *parent = 0);
    void newCategorieToController(int id);
    void setController(Controller* controller);
    ~ConsoLogos();

private:
    Controller* controller;
    QGridLayout* layout;
    QLabel* logos;
    QPushButton* logosLabels;
    QStyle* defaultStyle;

    
signals:
    
public slots:
    void logoClicked(int shortcutId = -1);
    
};

#endif // CONSOLOGOS_H
