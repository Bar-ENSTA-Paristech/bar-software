#include "individualhistory.h"

IndividualHistory::IndividualHistory(QWidget *parent) :
    MultiList(parent, 3, 0)
{
    VIEW.individualHistory = this;
    //this->setWindowFlags(Qt::Tool);
    //this->setGeometry(200, 60, 500, 800);

    headers[0]->setText("Opération");
    headers[1]->setText("Montant");
    headers[2]->setText("Date");

    stretchColumns = new int[1];
    stretchColumns[0]=0;
    defaultHeaderWidth = 100;
    hiddenColumn = -1;
    // ####### BUG ######
    //updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);


}

void IndividualHistory::launchIndividualHistory(view_historyQueue &queue)
{



    this->show();
}

void IndividualHistory::setController(Controller* _controller)
{
    controller = _controller;
}
