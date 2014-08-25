#include "moneytransfer.h"

MoneyTransfer::MoneyTransfer(QWidget *parent) :
    Popup(parent)
{
    VIEW.moneyTransfer = this;
    this->setFixedSize(350, 300);
    fromCustomerLabel = new QLabel("Transfert du compte de ", this);
    toCustomerLabel = new QLabel("Vers le compte de ", this);
    moneyLabel = new QLabel("€", this);
    labelLabel = new QLabel("Label ", this);
    fromCustomer = new QComboBox(this);
    toCustomer = new QComboBox(this);
    moneyToTransfer = new QLineEdit(this);
    label = new QLineEdit(this);
    validateButton = new QPushButton("Valider", this);
    cancelButton = new QPushButton("Annuler", this);
    layout = new QGridLayout(this);
    layout->addWidget(fromCustomerLabel, 0, 0);
    layout->addWidget(fromCustomer, 0, 1);
    layout->addWidget(toCustomerLabel, 1, 0);
    layout->addWidget(toCustomer, 1, 1);
    layout->addWidget(moneyToTransfer, 2, 0);
    layout->addWidget(moneyLabel, 2, 1);
    layout->addWidget(labelLabel, 3, 0);
    layout->addWidget(label, 3, 1);
    layout->addWidget(validateButton, 10,0);
    layout->addWidget(cancelButton, 10,1);
    this->setLayout(layout);

    QObject::connect(validateButton, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}

void MoneyTransfer::launch(view_customerQueue& queue)
{
    view_customerTuple tuple;
    QString completeName = "";
    customerQueueIds.clear();
    label->clear();
    moneyToTransfer->clear();
    fromCustomer->clear();
    toCustomer->clear();
    int n = queue.size();
    for(int i = 0 ; i < n ; i++)
    {
        tuple = queue.front();
        queue.pop();
        completeName = tuple.getCustomerName() + " " + tuple.getCustomerFirstName();
        fromCustomer->addItem(completeName);
        toCustomer->addItem(completeName);
        customerQueueIds.push_back(tuple.getCustomerId());
    }
    this->show();
}

void MoneyTransfer::validate()
{
    if(!isBalanceCorrect(moneyToTransfer->text()) || !isPositive(moneyToTransfer->text()))
        return;
    if(label->text().size() > 40)
    {
        error->showMessage("Label trop long. 40 caractère max ("+QString::number(label->text().size())+" ici).");
        return;
    }
    int fromCustomerId = (int) customerQueueIds[fromCustomer->currentIndex()];
    int toCustomerId = (int) customerQueueIds[toCustomer->currentIndex()];
    QString text(label->text());
    controller->receiveMoneyTransfer(fromCustomerId, toCustomerId, moneyToTransfer->text().toFloat(), text);
    this->hide();
}

void MoneyTransfer::cancel()
{
    customerQueueIds.clear();
    label->clear();
    moneyToTransfer->clear();
    this->hide();
}
