#include "newcustomer.h"

NewCustomer::NewCustomer(QWidget *parent) :
    Popup(parent)
{
    VIEW.newCustomer = this;
    //this->setWindowFlags(Qt::Tool);
    this->setFixedSize(250, 300);
    nameLabel = new QLabel("Nom : ", this);
    firstNameLabel = new QLabel("Prénom : ",this);
    categorieLabel = new QLabel("Categorie : ", this);
    loginLabel = new QLabel("Login : ", this);
    balanceLabel = new QLabel("Solde : ", this);
    name = new QLineEdit(this);
    firstName = new QLineEdit(this);
    login = new QLineEdit(this);
    categorie = new QComboBox(this);
    cardPaid = new QCheckBox("Premier paiement par carte", this);
    balance = new QLineEdit(this);
    validateButton = new QPushButton("Valider", this);
    cancelButton = new QPushButton("Annuler", this);

    layout = new QGridLayout(this);
    layout->addWidget(nameLabel,0,0);
    layout->addWidget(firstNameLabel,1,0);
    layout->addWidget(loginLabel,2,0);
    layout->addWidget(categorieLabel, 3, 0);
    layout->addWidget(balanceLabel, 4, 0);
    layout->addWidget(name,0,1);
    layout->addWidget(firstName, 1,1);
    layout->addWidget(login, 2,1);
    layout->addWidget(categorie,3,1);
    layout->addWidget(balance, 4,1);
    layout->addWidget(cardPaid, 5,0,1,2);
    layout->addWidget(validateButton, 6,0);
    layout->addWidget(cancelButton, 6,1);
    this->setLayout(layout);

    QObject::connect(validateButton, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}

/*void NewCustomer::setController(Controller* controller_par)
{
    controller = controller_par;
}*/

void NewCustomer::launchNewCustomer(std::vector<QString> categories)
{
    //categorie->clear();
    for(unsigned i = 1 ; i < categories.size() ; i++) // Avoid guest at i=0
        categorie->addItem(categories[i]);

    this->show();
    //this->setFocus();
}

void NewCustomer::validate()
{
    if(!isBalanceCorrect(balance->text()))
        return;

    tmpCustomer.setCustomerName(name->text());
    tmpCustomer.setCustomerFirstName(firstName->text());
    tmpCustomer.setCustomerLogin(login->text());
    // #### CATEGORIES EN UNSIGNED ? A REGLER ###################
    tmpCustomer.setCustomerCategory(categorie->currentIndex()+1);// +1 because 0 is for guest
    tmpCustomer.setCustomerBalance(balance->text().toFloat());

    controller->receiveNewCustomerEntry(tmpCustomer, !cardPaid->isChecked());
    cardPaid->setChecked(false);
    this->hide();
}

void NewCustomer::cancel()
{
    this->hide();
}
