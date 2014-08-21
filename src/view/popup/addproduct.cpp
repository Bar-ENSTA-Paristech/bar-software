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
    tvaLabel = new QLabel("TVA : ", this);
    name = new QLineEdit(this);
    volume = new QLineEdit(this);
    price = new QLineEdit(this);
    stock = new QLineEdit("0", this);
    categorie = new QComboBox(this);
    tva = new QComboBox(this);
    validateButton = new QPushButton("Valider", this);
    cancelButton = new QPushButton("Annuler", this);
    layout = new QGridLayout(this);

    // On récupère ces infos via la BDD maintenant, à chaque lancement dans launchAddProduct.
    /*categorie->addItem("Bières");
    categorie->addItem("Pression");
    categorie->addItem("Vin");
    categorie->addItem("Salé");
    categorie->addItem("Sucré");
    categorie->addItem("Divers");*/

    layout->addWidget(categorieLabel, 0, 0);
    layout->addWidget(nameLabel, 1, 0);
    layout->addWidget(volumeLabel, 2, 0);
    layout->addWidget(priceLabel, 3, 0);
    layout->addWidget(stockLabel, 4, 0);
    layout->addWidget(tvaLabel, 5,0);
    layout->addWidget(validateButton, 6, 0);
    layout->addWidget(categorie, 0, 1);
    layout->addWidget(name, 1, 1);
    layout->addWidget(volume, 2, 1);
    layout->addWidget(price, 3, 1);
    layout->addWidget(stock, 4, 1);
    layout->addWidget(tva, 5,1);
    layout->addWidget(cancelButton, 6, 1);

    QObject::connect(validateButton, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(categorie, SIGNAL(currentIndexChanged(int)), this, SLOT(categorySelected(int)));

    this->setLayout(layout);
}

void AddProduct::launchAddProduct()
{
    catVector = controller->getProductsCategories();
    db_categoryTuple catTuple;
    //Appel au controlleur pour avoir les taux de tva
    db_TVAcategoryQueue tvaQueue = controller->getTvaRates();
    db_TVAcategoryTuple tvaTuple;
    categorie->clear();
    tva->clear();
    int n = catVector.size();
    for(int i = 0 ; i < n ; i++)
    {
        catTuple = catVector[i];
        categorie->addItem(QString::fromStdString(catTuple.getCategoryName()));
    }
    n = tvaQueue.size();
    for(int i = 0 ; i < n ; i++)
    {
        tvaTuple = tvaQueue.front();
        tvaQueue.pop();
        tva->addItem(QString::number(tvaTuple.getRate())+"% : "+QString::fromStdString(tvaTuple.getInfo()));
    }

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
    tuple.setProductCategory(categorie->currentIndex()+1); // 0 is reserved for +/-
    tuple.setProductName(name->text());
    tuple.setProductPrice(price->text().toFloat());
    tuple.setProductStock(stock->text().toInt());
    tuple.setProductVolume(volume->text().toUInt());
    tuple.setProductTVAcat(tva->currentIndex()+1);
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
    catVector = controller->getProductsCategories();
}

void AddProduct::categorySelected(int index)
{
    bool isPression = QString::fromStdString(catVector[index].getCategoryName()).toLower()== "pression";
    if(isPression)
        volume->setReadOnly(false);
    else
    {
        volume->setText("1");
        volume->setReadOnly(true);
    }
}
