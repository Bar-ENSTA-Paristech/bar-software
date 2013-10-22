#ifndef CONSOLOGOS_H
#define CONSOLOGOS_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QFont>

#define NUMBER_OF_CONSUMPTION_TYPES 4

extern QString GLOBAL_PATH;

class ConsoLogos : public QFrame
{
    Q_OBJECT
public:
    explicit ConsoLogos(QWidget *parent = 0);

private:

    
signals:
    
public slots:
    
};

#endif // CONSOLOGOS_H
