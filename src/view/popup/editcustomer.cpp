#include "editcustomer.h"

EditCustomer::EditCustomer(QWidget *parent) :
    Popup(parent)
{
    VIEW.editCustomer = this;
    //this->setWindowFlags(Qt::Tool);
    this->setFixedSize(250, 300);
    nameLabel = new QLabel("Nom : ", this);
    firstNameLabel = new QLabel("Prénom : ",this);
    categorieLabel = new QLabel("Categorie : ", this);
    loginLabel = new QLabel("Login : ", this);
    name = new QLineEdit(this);
    firstName = new QLineEdit(this);
    login = new QLineEdit(this);
    categorie = new QComboBox(this);
    validateButton = new QPushButton("Valider", this);
    cancelButton = new QPushButton("Annuler", this);

    layout = new QGridLayout(this);
    layout->addWidget(nameLabel,0,0);
    layout->addWidget(firstNameLabel,1,0);
    layout->addWidget(loginLabel,2,0);
    layout->addWidget(categorieLabel, 3, 0);
    layout->addWidget(name,0,1);
    layout->addWidget(firstName, 1,1);
    layout->addWidget(login, 2,1);
    layout->addWidget(categorie,3,1);
    layout->addWidget(validateButton, 4,0);
    layout->addWidget(cancelButton, 4,1);
    this->setLayout(layout);

    QObject::connect(validateButton, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}

void EditCustomer::setController(Controller* controller_par)
{
    controller = controller_par;
}

void EditCustomer::launchEditCustomer(view_customerTuple& customer, std::vector<QString> categories)
{
    name->setText(customer.getCustomerName());
    firstName->setText(customer.getCustomerFirstName());
    login->setText(customer.getCustomerLogin());
    categorie->clear();
    for(int i = 1 ; i < categories.size() ; i++) // Début à 1 car à 0 on a "Visiteur"
        categorie->addItem(categories[i]);


    tmpCustomer = customer;

    this->show();
}

void EditCustomer::validate()
{
    tmpCustomer.setCustomerCategory((unsigned)categorie->currentIndex()+1); // +1 because category 0 is for guest
    tmpCustomer.setCustomerFirstName(firstName->text());
    tmpCustomer.setCustomerLogin(login->text());
    tmpCustomer.setCustomerName(name->text());
    controller->receiveEditCustomerEntry(tmpCustomer);
    this->hide();
}

void EditCustomer::cancel()
{
    this->hide();
}
