#include "addstock.h"

AddStock::AddStock(QWidget *parent) :
    Popup(parent)
{
    VIEW.addStock=this;

    this->setFixedSize(800,600);
    scrollArea = new QScrollArea(this);
    listFrame = new QFrame(scrollArea);
    addLineButton = new QPushButton("Ajouter un produit", this);
    resetButton = new QPushButton("Reset", this);
    validateButton = new QPushButton("Valider", this);
    cancelButton = new QPushButton("Annuler", this);
    layout = new QGridLayout(this);
    frameLayout = new QGridLayout(listFrame);
    tvaTotalLabel = new QLabel("Total tva de la commande (€) : ", this);
    ttcTotalLabel = new QLabel("Total ttc de la commande (€] : ", this);
    tvaTotal = new QLineEdit(this);
    ttcTotal = new QLineEdit(this);
    infosLabel = new QLabel("Remarques : ", this);
    infos = new QLineEdit(this);
    layout->addWidget(tvaTotalLabel, 0,0);
    layout->addWidget(tvaTotal, 0,1);
    layout->addWidget(infosLabel, 0,3);
    layout->addWidget(infos, 1, 3);
    layout->addWidget(ttcTotalLabel, 1,0);
    layout->addWidget(ttcTotal, 1,1);
    layout->addWidget(scrollArea, 2,0,1,4);
    layout->addWidget(addLineButton, 3,0);
    layout->addWidget(resetButton, 3,1);
    layout->addWidget(validateButton, 3, 2);
    layout->addWidget(cancelButton, 3,3);
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,1);
    layout->setColumnStretch(3,1);
    this->setLayout(layout);

    numberOfLines = 0;
    //lines = new ConsoLine[50]; //on crée 50 lignes dans un premier temps, si il en faut plus on agrandira
    listFrame->setLayout(frameLayout);
    frameLayout->setColumnStretch(1, 1);
    frameLayout->setColumnStretch(3,1);
    scrollArea->setWidget(listFrame);
    scrollArea->setWidgetResizable(true);


    QObject::connect(addLineButton, SIGNAL(clicked()), this, SLOT(addLine()));
    QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
    QObject::connect(validateButton, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}


void AddStock::launchAddStock()
{
    productCatQueue.clear();
    db_categoryQueue _productCatQueue = controller->getProductsCategories();
    db_categoryTuple catTuple;
    int n = _productCatQueue.size();
    for(int i = 0 ; i < n ; i++)
    {
        catTuple = _productCatQueue.front();
        _productCatQueue.pop();
        productCatQueue.push_back(catTuple);
    }
    this->show();
}

void AddStock::setController(Controller* _controller)
{
    controller = _controller;
}

void AddStock::addLine()
{
    ConsoLine *line = new ConsoLine;
    line->consoTypeLabel.setText("Type de Consommation");
    line->productLabel.setText("Produit");
    line->quantityLabel.setText("Quantité");
    // Now we ask to DB for categories, refresh at each launch
    /*line->consoType.addItem("Bières");
    line->consoType.addItem("Pression");
    line->consoType.addItem("Vin");
    line->consoType.addItem("Salé");
    line->consoType.addItem("Sucré");
    line->consoType.addItem("Divers");*/
    int n = productCatQueue.size();
    for(int i = 0 ; i < n ; i++)
    {
        line->consoType.addItem(QString::fromStdString(productCatQueue[i].getCategoryName()));
    }
    QObject::connect(&line->consoType, SIGNAL(currentIndexChanged(int)), this, SLOT(consoTypeChanged(int)));
    lines.push_back(line);
    frameLayout->addWidget(&line->consoTypeLabel, numberOfLines, 0, 1,1, Qt::AlignTop);
    frameLayout->addWidget(&line->consoType, numberOfLines, 1, 1,1, Qt::AlignTop);
    frameLayout->addWidget(&line->productLabel, numberOfLines, 2, 1,1, Qt::AlignTop);
    frameLayout->addWidget(&line->product, numberOfLines, 3, 1,1, Qt::AlignTop);
    frameLayout->addWidget(&line->quantityLabel, numberOfLines, 4, 1,1, Qt::AlignTop);
    frameLayout->addWidget(&line->quantity, numberOfLines, 5, 1,1, Qt::AlignTop);
    frameLayout->setRowStretch(numberOfLines, 0);
    frameLayout->setRowStretch(numberOfLines+1, 1);

    numberOfLines++;
    this->consoTypeChanged(0);

}

void AddStock::consoTypeChanged(int index)
{
    // CALL TO DB TO GET PRODUCTS OF THIS CONSO_TYPE INDEX (Bières, pression, etc)
    view_productQueue queue = controller->getProductsOfCategorie(index + 1); // 0 is reserved for +/-
    view_productTuple tuple;

    void* consoTypeSender = (void*) QObject::sender();
    unsigned i, line, queueSize = queue.size();
    bool isSenderInVector = false;
    if(consoTypeSender != NULL)
    {
        // Here we search for which line call the routine, comparing the adresses of the consoType Combobox of all lines and the one the sender
        for(i =0 ; i < lines.size() ; i++)
        {
            if(consoTypeSender == &lines[i]->consoType)
            {
                isSenderInVector = true;
                line= i;
                break;
            }
        }
        if(!isSenderInVector)
            line = numberOfLines - 1;
    }
    else
        line = numberOfLines - 1;
    // Now we remove all previous item in combobox product, then we put new ones
    lines[line]->product.clear();
    lines[line]->productID = new unsigned[queueSize];
    for(i = 0 ; i < queueSize ; i++)
    {
        tuple = queue.front();
        lines[line]->product.addItem(tuple.getProductName());
        lines[line]->productID[i] = tuple.getProductId();
        queue.pop();
    }qDebug() << lines[0]->productID;
}

void AddStock::validate()
{
    // Check of syntax of quantities
    QRegExp regex("^-?[0-9]+$");
    QString tmpString;
    for(unsigned i =0 ; i < numberOfLines ; i++)
    {
        tmpString = lines[i]->quantity.text();
        if(!tmpString.contains(regex))
        {
            error->showMessage("La quantité rentrée à la ligne " + QString::number(i+1) + " ("+lines[i]->product.currentText() +") n'est pas valide. Ce doit être un entier relatif.");
            return;
        }
    }

    // Generating the queue to send to controller
    view_productQueue queue;
    view_productTuple tuple;
    for (unsigned i =0 ; i <numberOfLines ; i++)
    {
        tuple.setProductCategory(lines[i]->consoType.currentIndex() + 1); // 0 is reserved for +/-
        tuple.setProductId(lines[i]->productID[lines[i]->product.currentIndex()]);
        tuple.setProductName(lines[i]->product.currentText());
        tuple.setProductStock(lines[i]->quantity.text().toInt());
        queue.push(tuple);
        delete[] lines[i]->productID;
    }
    if(!isFloat(tvaTotal->text()) || !isFloat(ttcTotal->text()))
        return;
    float tva = tvaTotal->text().toFloat();
    float ttc = ttcTotal->text().toFloat();
    controller->receiveNewStocks(queue,tva, ttc, infos->text());
    this->reset();
    this->hide();

}

void AddStock::cancel()
{
    this->reset();
    this->hide();
}

void AddStock::reset()
{
    // deleting all lines created
    for (unsigned i =0 ; i< numberOfLines ; i++)
    {
        delete lines[i];
    }
    lines.clear();
    delete frameLayout;
    delete listFrame;
    numberOfLines = 0;

    listFrame = new QFrame(scrollArea);
    scrollArea->setWidget(listFrame);
    frameLayout = new QGridLayout(listFrame);
    listFrame->setLayout(frameLayout);
    frameLayout->setColumnStretch(1, 1);
    frameLayout->setColumnStretch(3,1);
}




