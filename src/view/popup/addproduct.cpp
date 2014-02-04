#include "addproduct.h"

AddProduct::AddProduct(QWidget *parent) :
    Popup(parent)
{
    VIEW.addProduct = this;
    this->setFixedSize(300,300);

    categorieLabel = new QLabel("Categorie :", this);
    nameLabel = new QLabel("Nom :", this);
    volumeLabel = new QLabel("Volume (cL) :", this);
    priceLabel = new QLabel("Prix en € :", this);
    stockLabel = new QLabel("Stock :", this);
    name = new QLineEdit(this);
    volume = new QLineEdit(this);
    price = new QLineEdit(this);
    stock = new QLineEdit("0", this);
    categorie = new QComboBox(this);
    validateButton = new QPushButton("Valider", this);
    cancelButton = new QPushButton("Annuler", this);
    layout = new QGridLayout(this);

    categorie->addItem("Bières");
    categorie->addItem("Pression");
    categorie->addItem("Vin");
    categorie->addItem("Salé");
    categorie->addItem("Sucré");
    categorie->addItem("Divers");

    layout->addWidget(categorieLabel, 0, 0);
    layout->addWidget(nameLabel, 1, 0);
    layout->addWidget(volumeLabel, 2, 0);
    layout->addWidget(priceLabel, 3, 0);
    layout->addWidget(stockLabel, 4, 0);
    layout->addWidget(validateButton, 5, 0);
    layout->addWidget(categorie, 0, 1);
    layout->addWidget(name, 1, 1);
    layout->addWidget(volume, 2, 1);
    layout->addWidget(price, 3, 1);
    layout->addWidget(stock, 4, 1);
    layout->addWidget(cancelButton, 5, 1);

    QObject::connect(validateButton, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

    this->setLayout(layout);
}

void AddProduct::launchAddProduct()
{
    this->show();
}

void AddProduct::validate()
{
    if(!isBalanceCorrect(price->text()))
        return;
    else if(!isUInteger(stock->text()))
        return;
    else if(!isUInteger(volume->text()))
        return;

    view_productTuple tuple;
    tuple.setProductCategory(categorie->currentIndex());
    tuple.setProductName(name->text());
    tuple.setProductPrice(price->text().toFloat());
    tuple.setProductStock(stock->text().toInt());
    tuple.setProductVolume(volume->text().toUInt());
    controller->receiveNewProduct(tuple);

    this->reset();
    this->hide();
}

void AddProduct::cancel()
{
    this->reset();
    this->hide();
}

void AddProduct::reset()
{
    name->clear();
    volume->clear();
    price->clear();
    stock->clear();
}

void AddProduct::setController(Controller* _controller)
{
    controller = _controller;
}
