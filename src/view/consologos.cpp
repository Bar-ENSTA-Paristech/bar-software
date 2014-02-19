#include "consologos.h"

ConsoLogos::ConsoLogos(QWidget *parent) :
    QFrame(parent)
{
    VIEW.consoLogos = this;
    setObjectName("consoLogos");
    layout = new QGridLayout(this);
    QFont font;
    font.setBold(true);
    font.setPixelSize(14);
    logos = new QLabel[NUMBER_OF_CONSUMPTION_TYPES];
    logosLabels = new QPushButton[NUMBER_OF_CONSUMPTION_TYPES];
    for(int i=0 ; i < NUMBER_OF_CONSUMPTION_TYPES ; i++)
    {
        logos[i].setParent(this);
        logosLabels[i].setParent(this);
        logos[i].setPixmap(GLOBAL_PATH + "resources/pictures/logo" + QString::number(i+1) + ".png");
        layout->addWidget(&logos[i], i, 0);
        layout->addWidget(&logosLabels[i], i, 1, 1, 2);
        logosLabels[i].setFont(font);
        //logosLabels[i].setFlat(true);
        QObject::connect(&logosLabels[i], SIGNAL(clicked()), this, SLOT(logoClicked()));
    }
    //logosLabels[0].se

    //mdefaultStyle = logosLabels[0].st;
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    logosLabels[0].setText("Bières - Ctrl+B");
    logosLabels[1].setText("Pression - Ctrl+P");
    logosLabels[2].setText("Vin - Ctrl+W");
    logosLabels[3].setText("Salé - Ctrl+Q");
    logosLabels[4].setText("Sucré - Ctrl+U");
    logosLabels[5].setText("Divers - Ctrl+D");
    newCategorieToController(-1);
    this->setLayout(layout);


}

void ConsoLogos::logoClicked(int shortcutId)
{
    // If shortcutId is -1, it is a click on the button, otherwise it a shortcut hit and the id is defined in this value

    // So we check if it is a shortcut hit, if yes we call controller and return.
    if (shortcutId != -1)
    {
        newCategorieToController(shortcutId);
        return;
    }


    unsigned long long sender = (unsigned long long) QObject::sender();
    unsigned long long tabAdress = (unsigned long long) logosLabels;

    // We search what index of logosLabel called the routine, (the adress &logoLabels[1] = logoLabels + 1*sizeof(QPushButton) )
    for(int i =0 ; i < NUMBER_OF_CONSUMPTION_TYPES ; i++)
    {
        if(sender ==  tabAdress + i*sizeof(QPushButton))
        {
            newCategorieToController(i);
            return;
        }
    }


}

void ConsoLogos::newCategorieToController(int id)
{
    if(id < 0 || id >= NUMBER_OF_CONSUMPTION_TYPES)
        return;

    for(int i = 0 ; i < NUMBER_OF_CONSUMPTION_TYPES ; i++)
    {
        if(i != id)
        {
            //logosLabels[i].setStyleSheet("ConsoLogos QPushButton{padding-top: 4px; padding-bottom: 4px; padding-left: 2px; padding-right: 2px; border: 1px solid black; border-radius: 7px;}");
            logosLabels[i].setObjectName("");
        }
    }

    //logosLabels[id].setStyleSheet("ConsoLogos QPushButton{outline: none; color: #f9f9f9; background-color: grey;}");
    logosLabels[id].setObjectName("activeTypeOfProduct");
    QFile css(GLOBAL_PATH + "resources/design/mainDesign.css");
    if(css.open(QIODevice::ReadOnly)) {
        this->setStyleSheet(css.readAll());
    }
    controller->newClic_ProductTypes( (unsigned) id);
    VIEW.productChoices->setFocus();

}

ConsoLogos::~ConsoLogos()
{
    /*delete layout;
    delete[] logos;
    delete[] logosLabels;*/
}
