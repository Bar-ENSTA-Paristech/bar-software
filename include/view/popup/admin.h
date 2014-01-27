#ifndef ADMIN_H
#define ADMIN_H

#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>
#include "popup.h"
#include "controller.h"
#include "structures.h"
extern ViewObjects VIEW;

class Admin : public Popup
{
    Q_OBJECT
public:
    explicit Admin(QWidget *parent = 0);
    void launchAdmin(AdminTuple tuple);
    
signals:

private:
    QGridLayout* layout;
    QPushButton* validateButton;
    QPushButton* cancelButton;
    QCheckBox* negativeAllowed;
    QLabel* cashTransferLabel;
    QLineEdit* cashTransfer;

    
public slots:
    void validate();
    
};

#endif // ADMIN_H
