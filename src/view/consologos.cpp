#include "consologos.h"

ConsoLogos::ConsoLogos(QWidget *parent) :
    QFrame(parent)
{
    setObjectName("consoLogos");
    layout = new QGridLayout(this);
    QFont font;
    font.setBold(true);
    font.setPixelSize(14);
    logos = new QLabel[NUMBER_OF_CONSUMPTION_TYPES];
    logosLabels = new QLabel[NUMBER_OF_CONSUMPTION_TYPES];
    for(int i=0 ; i < NUMBER_OF_CONSUMPTION_TYPES ; i++)
    {
        logos[i].setParent(this);
        logosLabels[i].setParent(this);
        logos[i].setPixmap(GLOBAL_PATH + "resources/pictures/logo" + QString::number(i+1) + ".png");
        layout->addWidget(&logos[i], i, 0);
        layout->addWidget(&logosLabels[i], i, 1, 1, 2);
        logosLabels[i].setFont(font);
    }
    layout->setContentsMargins(0, 0, 0, 0);

    logosLabels[0].setText("Bières - Ctrl+B");
    logosLabels[1].setText("Pression - Ctrl+P");
    logosLabels[2].setText("Vin - Ctrl+V");
    logosLabels[3].setText("Divers - Ctrl+D");
    this->setLayout(layout);

}

ConsoLogos::~ConsoLogos()
{
    /*delete layout;
    delete[] logos;
    delete[] logosLabels;*/
}
