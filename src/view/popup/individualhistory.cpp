#include "individualhistory.h"

IndividualHistory::IndividualHistory(QWidget *parent) :
    QWidget(parent)
{
    VIEW.individualHistory = this;
    //this->setWindowFlags(Qt::Tool);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    history = new IndividualHistoryList(this);
    layout = new QGridLayout(this);
    layout->addWidget(history, 0, 0);
    this->setLayout(layout);
    this->setGeometry(200, 60, 500, 800);






}

void IndividualHistory::launchIndividualHistory(view_historyQueue &queue)
{
    history->updateSize();
    this->show();
}

void IndividualHistory::setController(Controller* _controller)
{
    controller = _controller;
}

void IndividualHistory::resizeEvent(QResizeEvent *event)
{
    history->updateSize();
}

// ############## LIST ############

IndividualHistoryList::IndividualHistoryList(QWidget *parent) :
    MultiList(parent, 3, 0)
{
    headers[0]->setText("Opération");
    headers[1]->setText("Montant");
    headers[2]->setText("Date");

    stretchColumns = new int[1];
    stretchColumns[0]=0;
    defaultHeaderWidth = 130;
    hiddenColumn = -1;
    // ####### BUG ######
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);
    this->updateSize();
}
