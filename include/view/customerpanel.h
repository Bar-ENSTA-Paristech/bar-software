#ifndef CUSTOMERPANEL_H
#define CUSTOMERPANEL_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <tuple>
#include <QDebug>
#include <QFile>

extern QString GLOBAL_PATH;

class CustomerPanel : public QFrame
{
    Q_OBJECT
public:
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
