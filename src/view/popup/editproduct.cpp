#include "editproduct.h"

EditProduct::EditProduct(QWidget *parent) :
    Popup(parent)
{
    VIEW.editProduct = this;
    this->setFixedSize(300,300);

    categorieLabel = new QLabel("Produit :", this);
    newNameLabel = new QLabel("Nouveau nom :", this);
    volumeLabel = new QLabel("Volume (cL) :", this);
    priceLabel = new QLabel("Prix en € :", this);
    stockLabel = new QLabel("Stock :", this);
    newName = new QLineEdit(this);
    volume = new QLineEdit(this);
    price = new QLineEdit(this);
    stock = new QLineEdit("0", this);
    categorie = new QComboBox(this);
    name = new QComboBox(this);
    deleteProduct = new QCheckBox("Supprimer cette consommation", this);
    validateButton = new QPushButton("Valider", this);
    cancelButton = new QPushButton("Annuler", this);
    layout = new QGridLayout(this);

    categorie->addItem("Bières");
    categorie->addItem("Pression");
    categorie->addItem("Vin");
    categorie->addItem("Bouffe salée");
    categorie->addItem("Bouffe sucrée");
    categorie->addItem("Divers");

    layout->addWidget(categorieLabel, 0, 0);
    layout->addWidget(newNameLabel, 2, 0);
    layout->addWidget(volumeLabel, 3, 0);
    layout->addWidget(priceLabel, 4, 0);
    layout->addWidget(stockLabel, 5, 0);
    layout->addWidget(deleteProduct, 6,0,1,2);
    layout->addWidget(validateButton, 7, 0);
    layout->addWidget(categorie, 0, 1);
    layout->addWidget(name, 1,1);
    layout->addWidget(newName, 2, 1);
    layout->addWidget(volume, 3, 1);
    layout->addWidget(price, 4, 1);
    layout->addWidget(stock, 5, 1);
    layout->addWidget(cancelButton, 7, 1);

    QObject::connect(validateButton, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(categorie, SIGNAL(currentIndexChanged(int)), this, SLOT(categorieSelected(int)));
    QObject::connect(name, SIGNAL(currentIndexChanged(int)), this, SLOT(productSelected(int)));

    this->setLayout(layout);
}

void EditProduct::launchEditProduct()
{
    this->show();
}

void EditProduct::validate()
{
    if(!isBalanceCorrect(price->text()))
        return;
    else if(!isInteger(stock->text()))
        return;
    else if(!isUInteger(volume->text()))
        return;

    tmpProduct.setProductCategory(categorie->currentIndex());
    tmpProduct.setProductName(newName->text());
    tmpProduct.setProductPrice(price->text().toFloat());
    tmpProduct.setProductStock(stock->text().toInt());
    //tuple.setProductID()
    tmpProduct.setProductVolume(volume->text().toUInt());
    controller->receiveNewProduct(tmpProduct);

    this->reset();
    this->hide();
}

void EditProduct::cancel()
{
    this->reset();
    this->hide();
}

void EditProduct::reset()
{
    name->clear();
    volume->clear();
    price->clear();
}

void EditProduct::setController(Controller* _controller)
{
    controller = _controller;
    categorieSelected(0);
}

void EditProduct::categorieSelected(int index)
{
    view_productQueue queue;
    view_productTuple tuple;
    tmpProductVector.clear();
    name->clear();
    queue = controller->getProductsOfCategorie(index);
    for (int i=0, n=queue.size() ; i < n ; i++)
    {
        tuple = queue.front();
        tmpProductVector.push_back(tuple);
        name->addItem(tuple.getProductName());
        queue.pop();
    }
    deleteProduct->setChecked(false);
}

void EditProduct::productSelected(int index)
{
    if(index == -1) // new categorie loads so we set by default the index at 0 if it exists
        if(tmpProductVector.size() > 0)
            index = 0;
        else
            return;
    tmpProduct = tmpProductVector[index];
    newName->setText(tmpProduct.getProductName());
    price->setText(QString::number(tmpProduct.getProductPrice()));
    volume->setText(QString::number(tmpProduct.getProductVolume()));
    stock->setText(QString::number(tmpProduct.getProductStock()));
    deleteProduct->setChecked(false);
}





