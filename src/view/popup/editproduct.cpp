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
    tvaLabel = new QLabel("TVA : ", this);
    linkstockLabel = new QLabel("Stock lié à :",this);
    newName = new QLineEdit(this);
    volume = new QLineEdit(this);
    price = new QLineEdit(this);
    stock = new QLineEdit("0", this);
    categorie = new QComboBox(this);
    name = new QComboBox(this);
    tva = new QComboBox(this);
    linkstock = new QComboBox (this);
    deleteProduct = new QCheckBox("Supprimer cette consommation", this);
    validateButton = new QPushButton("Valider", this);
    cancelButton = new QPushButton("Annuler", this);
    layout = new QGridLayout(this);

    // Class asks the DB for current categories at each launch

    layout->addWidget(categorieLabel, 0, 0);
    layout->addWidget(newNameLabel, 2, 0);
    layout->addWidget(volumeLabel, 3, 0);
    layout->addWidget(priceLabel, 4, 0);
    layout->addWidget(stockLabel, 5, 0);
    layout->addWidget(tvaLabel, 6,0);
    layout->addWidget(linkstockLabel, 7,0);
    layout->addWidget(deleteProduct, 8,0,1,2);
    layout->addWidget(validateButton, 9, 0);
    layout->addWidget(categorie, 0, 1);
    layout->addWidget(name, 1,1);
    layout->addWidget(newName, 2, 1);
    layout->addWidget(volume, 3, 1);
    layout->addWidget(price, 4, 1);
    layout->addWidget(stock, 5, 1);
    layout->addWidget(tva, 6,1);
    layout->addWidget(linkstock,7,1);
    layout->addWidget(cancelButton, 9, 1);

    QObject::connect(validateButton, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(categorie, SIGNAL(currentIndexChanged(int)), this, SLOT(categorieSelected(int)));
    QObject::connect(name, SIGNAL(currentIndexChanged(int)), this, SLOT(productSelected(int)));
    QObject::connect(linkstock,SIGNAL(currentIndexChanged(int)),this,SLOT(LinkStockSelected(int)));

    this->setLayout(layout);
}

void EditProduct::launchEditProduct()
{
    db_categoryQueue catQueue = controller->getProductsCategories();
    db_categoryTuple catTuple;
    //Appel au controlleur pour avoir les taux de tva
    db_TVAcategoryQueue tvaQueue = controller->getTvaRates();
    db_TVAcategoryTuple tvaTuple;
    categorie->clear();
    tva->clear();
    int n = catQueue.size();
    for(int i = 0 ; i < n ; i++)
    {
        catTuple = catQueue.front();
        catQueue.pop();
        categorie->addItem(QString::fromStdString(catTuple.getCategoryName()));
    }
    n = tvaQueue.size();
    for(int i = 0 ; i < n ; i++)
    {
        tvaTuple = tvaQueue.front();
        tvaQueue.pop();
        tva->addItem(QString::number(tvaTuple.getRate())+"% : "+QString::fromStdString(tvaTuple.getInfo()));
    }

    // to update consos to fit this category

    categorieSelected(categorie->currentIndex());

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

    tmpProduct.setProductCategory(categorie->currentIndex() + 1); // 0 is reserved for +/-
    tmpProduct.setProductName(newName->text());
    tmpProduct.setProductPrice(price->text().toFloat());
    tmpProduct.setProductStock(stock->text().toInt());
    tmpProduct.setProductId(ID);
    tmpProduct.setProductVolume(volume->text().toUInt());
    tmpProduct.setProductTVAcat(tva->currentIndex() + 1);
    tmpProduct.setProductLinkStock(linkstockID);
    controller->receiveEditProduct(tmpProduct, deleteProduct->isChecked());

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
    linkstock->clear();
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
    linkstock->clear();
    queue = controller->getProductsOfCategorie(index + 1); // 0 is reserved for +/-
    for (int i=0, n=queue.size() ; i < n ; i++)
    {
        tuple = queue.front();
        tmpProductVector.push_back(tuple);
        if (index==1)
        {
            name->addItem(tuple.getProductName()+" : "+QString::number(tuple.getProductVolume())+"cL");
            linkstock->addItem(tuple.getProductName()+" : "+QString::number(tuple.getProductVolume())+"cL");
        }
        else
        {
        name->addItem(tuple.getProductName());
        linkstock->addItem(tuple.getProductName()+" : "+QString::number(tuple.getProductVolume())+"cL");
        }
        queue.pop();
    }

    deleteProduct->setChecked(false);
}

void EditProduct::productSelected(int index)
{
    if(index == -1) // -1 means categorie just loaded. so we set by default the index at 0 if it exists
    {
        if(tmpProductVector.size() > 0)
            index = 0;
        else
            return;
    }
    tmpProduct = tmpProductVector[index];
    newName->setText(tmpProduct.getProductName());
    price->setText(QString::number(tmpProduct.getProductPrice()));
    volume->setText(QString::number(tmpProduct.getProductVolume()));
    stock->setText(QString::number(tmpProduct.getProductStock()));
    tva->setCurrentIndex(tmpProduct.getProductTVAcat()-1);
    ID = tmpProduct.getProductId();
    deleteProduct->setChecked(false);
}

void EditProduct::LinkStockSelected(int index)
{
    if(index == -1) // -1 means categorie just loaded. so we set by default the index at 0 if it exists
    {
        if(tmpProductVector.size() > 0)
            index = 0;
        else
            return;
    }
    tmpLinkProduct = tmpProductVector[index];
    linkstockID = tmpLinkProduct.getProductId();
}
