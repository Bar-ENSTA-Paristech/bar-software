#ifndef CUSTOMERPANEL_H
#define CUSTOMERPANEL_H

#include <QFrame>

class CustomerPanel : public QFrame
{
    Q_OBJECT
public:
    explicit CustomerPanel(QWidget *parent = 0);
    void setCustomer();
    
signals:
    
public slots:
    
};

#endif // CUSTOMERPANEL_H
