#include "admin.h"

Admin::Admin(QWidget *parent) :
    Popup(parent)
{
    VIEW.admin = this;
    this->setGeometry(50,50, 600,600);

    layout = new QGridLayout(this);
    //negativeAllowed = new QCheckBox("Négatif autorisé", this);
    cashTransferLabel = new QLabel("Argent transféré au BDE (€): ", this);
    cashTransfer = new QLineEdit("0", this);
    oldHistory = new QPushButton(QIcon(GLOBAL_PATH + "resources/pictures/history_old.png"), "", this);
    oldHistory->setFlat(true);
    oldHistory->setCursor(Qt::PointingHandCursor);
    oldHistory->setIconSize(QSize(32,32));
    oldHistory->setStyleSheet("background: none;");
    oldHistory->setToolTip("Voir le vieux historique");
    oldIndividualHistory = new QPushButton(QIcon(GLOBAL_PATH + "resources/pictures/history_individual_old.png"), "", this);
    oldIndividualHistory->setFlat(true);
    oldIndividualHistory->setCursor(Qt::PointingHandCursor);
    oldIndividualHistory->setIconSize(QSize(32,32));
    oldIndividualHistory->setStyleSheet("background: none;");
    oldIndividualHistory->setToolTip("Voir le vieux historique de cette personne");
    oldIndividualCustomer = new QComboBox(this);

    validateButton = new QPushButton("Valider", this);
    cancelButton = new QPushButton("Annuler", this);

    layout->addWidget(oldHistory, 0,0);
    layout->addWidget(oldIndividualCustomer, 1,0);
    layout->addWidget(oldIndividualHistory, 1,1);
    layout->addWidget(cashTransferLabel, 2,0);
    layout->addWidget(cashTransfer, 2,1);
    layout->addWidget(validateButton, 20,0);
    layout->addWidget(cancelButton, 20,1);

    QObject::connect(validateButton, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}

void Admin::launchAdmin(AdminTuple& tuple)
{
    //negativeAllowed->setChecked(tuple.isNegativeAllowed);

    this->show();
}

void Admin::validate()
{
    if(!isBalanceCorrect(cashTransfer->text()))
        return;
    AdminTuple tuple;
    //tuple.isNegativeAllowed = negativeAllowed->isChecked();
    tuple.cashTransfered = cashTransfer->text().toFloat();
    controller->receiveAdminInfos(tuple);
    this->hide();
}
