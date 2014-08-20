#ifndef ADMIN_H
#define ADMIN_H

#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>
#include <QFile>
#include <QTextEdit>
#include "popup.h"
#include "controller.h"
#include "structures.h"
extern ViewObjects VIEW;

class Admin : public Popup
{
    Q_OBJECT
public:
    explicit Admin(QWidget *parent = 0);
    void launchAdmin(AdminTuple &tuple);
    
signals:

private:
    QGridLayout* layout;
    QPushButton* oldHistory;
    QLabel* oldHistoryBeginLabel;
    QLineEdit* oldHistoryBegin;
    QPushButton* oldIndividualHistory;
    QComboBox* oldIndividualCustomer;
    QPushButton* individualGraphButton;
    QPushButton* validateButton;
    QPushButton* cancelButton;
    QLabel* cashTransferLabel;
    QLineEdit* cashTransfer;
    QLabel* oldCustCategoryNameLabel;
    QComboBox* oldCustCategoryName;
    QLineEdit* newCustCategoryName;
    QLabel* oldProdCategoryNameLabel;
    QComboBox* oldProdCategoryName;
    QLineEdit* newProdCategoryName;
    QLabel *logLabel;
    QLineEdit* logYear;
    QPushButton* viewLog;
    QLabel* tvaEditLabel;
    QComboBox* tvaEdit;
    QLineEdit* tvaEditNewValue;
    QLabel* tvaPdfLabel;
    QLineEdit* tvaPdf;
    QPushButton* tvaPdfButton;

    
public slots:
    void validate();
    void clickOnGlobalHistory();
    void clickOnIndividualHistory();
    void clickOnIndividualGraph();
    void clickOnViewLog();
    void createTvaPdf();
    
};

#endif // ADMIN_H
