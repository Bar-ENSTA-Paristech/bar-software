#include "admin.h"

Admin::Admin(QWidget *parent) :
    Popup(parent)
{
    VIEW.admin = this;
    this->setGeometry(50,50, 600,600);

    layout = new QGridLayout(this);
    negativeAllowed = new QCheckBox("Négatif autorisé", this);
    cashTransferLabel = new QLabel("Argent transféré au BDE (€): ", this);
    cashTransfer = new QLineEdit("0", this);

    validateButton = new QPushButton("Valider", this);
    cancelButton = new QPushButton("Annuler", this);

    layout->addWidget(negativeAllowed, 0,0);
    layout->addWidget(cashTransferLabel, 1,0);
    layout->addWidget(cashTransfer, 1,1);
    layout->addWidget(validateButton, 20,0);
    layout->addWidget(cancelButton, 20,1);

    QObject::connect(validateButton, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}

void Admin::launchAdmin(AdminTuple tuple)
{
    negativeAllowed->setChecked(tuple.isNegativeAllowed);

    this->show();
}

void Admin::validate()
{
    if(!isBalanceCorrect(cashTransfer->text()))
        return;
    AdminTuple tuple;
    tuple.isNegativeAllowed = negativeAllowed->isChecked();
    tuple.cashTransfered = cashTransfer->text().toFloat();
    controller->receiveAdminInfos(tuple);
    this->hide();
}
