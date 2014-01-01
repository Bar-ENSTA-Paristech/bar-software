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

void IndividualHistory::launchIndividualHistory(view_histQueue &queue)
{
    view_histTuple tuple;
    // Inserting new results
    unsigned numberOfElements = queue.size();
    history->setRows(numberOfElements);

    for(unsigned i=0;i<numberOfElements ; i++)
    {
        tuple = queue.front();
        queue.pop();
        history->model->item(i,0)->setText(tuple.getHistOperation());
        history->model->item(i,1)->setText(tuple.getHistDate());
        history->model->item(i,2)->setText(QString::number(tuple.getHistPrice()));
    }
    history->table->sortByColumn(1, Qt::DescendingOrder);
    history->table->setModel(history->model);
    history->updateHeadersSize(history->defaultHeaderWidth, history->stretchColumns, history->hiddenColumn);

    history->updateSize();
    this->show();
    return;
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
    MultiList(parent, 4, 0)
{
    headers[0]->setText("Opération");
    headers[1]->setText("Date");
    headers[2]->setText("Montant");
    headers[3]->setText("Void");

    stretchColumns = new int[2];
    stretchColumns[0]=0;
    stretchColumns[1]=-1;
    defaultHeaderWidth = 120;
    hiddenColumn = 3;
    // ####### BUG ######
updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);
    this->updateSize();

}
