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
    layout->addWidget(scrollArea, 0,0,1,4);
    layout->addWidget(addLineButton, 1,0);
    layout->addWidget(resetButton, 1,1);
    layout->addWidget(validateButton, 1, 2);
    layout->addWidget(cancelButton, 1,3);
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
    line->consoType.addItem("Bières");
    line->consoType.addItem("Pression");
    line->consoType.addItem("Vin");
    line->consoType.addItem("Bouffe Salée");
    line->consoType.addItem("Bouffe Sucrée");
    line->consoType.addItem("Divers");
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
    view_productQueue queue = controller->getProductsOfCategorie(index);
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
    for(i = 0 ; i < queueSize ; i++)
    {
        tuple = queue.front();
        lines[line]->product.addItem(tuple.getProductName());
        lines[line]->productID = tuple.getProductId();
        queue.pop();
    }
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
        tuple.setProductCategory(lines[i]->consoType.currentIndex());
        tuple.setProductId(lines[i]->productID);
        tuple.setProductName(lines[i]->product.currentText());
        tuple.setProductStock(lines[i]->quantity.text().toUInt());
        queue.push(tuple);
    }
    controller->receiveNewStocks(queue);
    this->reset();
    //this->hide();

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




