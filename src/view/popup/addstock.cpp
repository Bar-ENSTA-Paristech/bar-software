#include "addstock.h"

AddStock::AddStock(QWidget *parent) :
    Popup(parent)
{
    VIEW.addStock=this;

    this->setFixedSize(600,600);
    listFrame = new QFrame(this);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(listFrame);
    addLineButton = new QPushButton("Ajouter un produit", this);
    validateButton = new QPushButton("Valider", this);
    cancelButton = new QPushButton("Annuler", this);
    layout = new QGridLayout(this);
    frameLayout = new QGridLayout(listFrame);
    layout->addWidget(scrollArea, 0,0,1,4);
    layout->addWidget(addLineButton, 1,0);
    layout->addWidget(validateButton, 1, 2);
    layout->addWidget(cancelButton, 1,3);
    this->setLayout(layout);

    numberOfLines = 0;
    //lines = new ConsoLine[50]; //on crée 50 lignes dans un premier temps, si il en faut plus on agrandira
    listFrame->setLayout(frameLayout);
    //listFrame->set

    QObject::connect(addLineButton, SIGNAL(clicked()), this, SLOT(addLine()));
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
    lines.push_back(line);
    frameLayout->addWidget(&line->consoTypeLabel, numberOfLines, 0, 1,1, Qt::AlignRight);
    frameLayout->addWidget(&line->consoType, numberOfLines, 1, 1,1, Qt::AlignLeft);
    frameLayout->addWidget(&line->productLabel, numberOfLines, 3, 1,1, Qt::AlignRight);
    frameLayout->addWidget(&line->product, numberOfLines, 4, 1,1, Qt::AlignLeft);
    frameLayout->addWidget(&line->quantityLabel, numberOfLines, 6, 1,1, Qt::AlignRight);
    frameLayout->addWidget(&line->quantity, numberOfLines, 7, 1,1, Qt::AlignLeft);


    numberOfLines++;
}
