#ifndef MONEYTRANSFER_H
#define MONEYTRANSFER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QList>
#include <popup.h>
#include <structures.h>
#include "controller.h"

extern ViewObjects VIEW;

class MoneyTransfer : public Popup
{
    Q_OBJECT
public:
    explicit MoneyTransfer(QWidget *parent = 0);
    void launch(view_customerQueue& queue);
    
signals:
    
public slots:
    void validate();
    void cancel();

private:
    QLabel* fromCustomerLabel;
    QLabel* toCustomerLabel;
    QLabel* moneyLabel;
    QLabel* labelLabel;
    QComboBox* fromCustomer;
    QComboBox* toCustomer;
    QLineEdit* moneyToTransfer;
    QLineEdit* label;
    QPushButton* validateButton;
    QPushButton* cancelButton;
    QGridLayout* layout;
    QList<unsigned int> customerQueueIds;
    
};

#endif // MONEYTRANSFER_H
