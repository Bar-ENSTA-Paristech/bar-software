#include "globalhistory.h"

GlobalHistory::GlobalHistory(QWidget *parent) :
    Popup(parent)
{
    VIEW.globalHistory = this;
    //this->setWindowFlags(Qt::Tool);
    //this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setStyle(QStyleFactory::create("fusion"));
    history = new GlobalHistoryList(this);
    layout = new QGridLayout(this);
    layout->setColumnStretch(0, 1);
    layout->setRowStretch(0, 1);
    layout->addWidget(history, 0, 0);
    this->setLayout(layout);
    this->setGeometry(200, 60, 800, 800);
}

void GlobalHistory::launchGlobalHistory(view_histQueue &queue)
{
    history->launchGlobalHistory(queue);
    history->updateSize();
    this->show();
    return;
    }

void GlobalHistory::setController(Controller* _controller)
{
    controller = _controller;
}

void GlobalHistory::resizeEvent(QResizeEvent *event)
{
    history->updateSize();
}


// ############## LIST ############

GlobalHistoryList::GlobalHistoryList(QWidget *parent) :
    MultiList(parent, 6, 0, false)
{
    headers[0]->setText("Nom");
    headers[1]->setText("Prénom");
    headers[2]->setText("Opération");
    headers[3]->setText("Date");
    headers[4]->setText("Montant");
    headers[5]->setText("Void");

    stretchColumns = new int[3];
    stretchColumns[0]=2;
    stretchColumns[1]=3;
    stretchColumns[2]=-1;
    defaultHeaderWidth = 120;
    hiddenColumn = 5;
    // ####### BUG ######
updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);
    this->updateSize();

}

void GlobalHistoryList::launchGlobalHistory(view_histQueue &queue)
{
    view_histTuple tuple;
    table->setModel(NULL);

    // Inserting new results
    QBrush negativeSold(Qt::red);
    QBrush positiveSold(Qt::black);
    unsigned numberOfElements = queue.size();
    setRows(numberOfElements);
    for(unsigned i=0 ; i<numberOfElements ; i++)
    {
        tuple = queue.front();
        queue.pop();
        float price = tuple.getHistPrice();

        model->item(i,0)->setText(tuple.getHistName());
        model->item(i,1)->setText(tuple.getHistFirstName());
        model->item(i,2)->setText(tuple.getHistOperation());
        model->item(i,3)->setText(tuple.getHistDate());
        if(price > 0 || tuple.getHistOperation() == "DEBIT/CREDIT")
            model->item(i,4)->setText(QString::number(price));
        else
            model->item(i,4)->setText("Cash (" + QString::number(-price)+")");

        QBrush negativeColor(QColor(242,222,222)), positiveColor(QColor(159, 255, 140)), normalColor(QColor(255,255,255));
        QBrush *color;
        if(tuple.getHistOperation() == "DEBIT/CREDIT")
        {
            if(price > 0)
                color = &positiveColor;
            else
                color = &negativeColor;
        }
        else
            color = &normalColor;
        for(int j=0 ; j < columns ; j++)
            model->item(i,j)->setBackground(*color);
    }
    //table->sortItems(0, Qt::AscendingOrder);
    //table->sortByColumn(0, Qt::AscendingOrder);
    table->setModel(model);
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);
    return;
}
