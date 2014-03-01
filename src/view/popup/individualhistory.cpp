#include "individualhistory.h"

IndividualHistory::IndividualHistory(QWidget *parent) :
    Popup(parent)
{
    VIEW.individualHistory = this;
    //this->setWindowFlags(Qt::Tool);
    //this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setStyle(QStyleFactory::create("fusion"));
    history = new IndividualHistoryList(this);
    layout = new QGridLayout(this);
    title = new QLabel(this);
    totalConsummedLabel = new QLabel("Total Consommé : ", this);
    totalConsummed = new QLabel(this);
    layout->addWidget(title, 0, 0, 1, 3, Qt::AlignCenter);
    layout->addWidget(totalConsummedLabel, 1, 0);
    layout->addWidget(totalConsummed, 1, 1);
    layout->setColumnStretch(2, 1);
    layout->setRowStretch(2, 1);
    layout->addWidget(history, 2, 0, 1, 3);
    this->setLayout(layout);
    this->setGeometry(200, 60, 500, 800);
}

void IndividualHistory::launchIndividualHistory(view_histQueue &queue)
{
    history->launchIndividualHistory(queue);
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

void IndividualHistory::setTitle(QString text)
{
    title->setText(text);
}

void IndividualHistory::setTotalConsummed(QString total)
{
    totalConsummed->setText(total);
}

// ############## LIST ############

IndividualHistoryList::IndividualHistoryList(QWidget *parent) :
    MultiList(parent, 4, 0, false)
{
    headers[0]->setText("Opération");
    headers[1]->setText("Date");
    headers[2]->setText("Montant");
    headers[3]->setText("Void");

    stretchColumns = new int[3];
    stretchColumns[0]=0;
    stretchColumns[1]=1;
    stretchColumns[2]=-1;
    defaultHeaderWidth = 100;
    hiddenColumn = 3;
    // ####### BUG ######
updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);
    this->updateSize();

}

void IndividualHistoryList::launchIndividualHistory(view_histQueue &queue)
{
    view_histTuple tuple;
    float totalPrice = 0;
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
        // if is normal consumption, we calculate the new total of consumptions
        if(tuple.getHistOperation() != "CREDIT" && tuple.getHistOperation() != "DEBIT")
            totalPrice += tuple.getHistPrice();

        model->item(i,0)->setText(tuple.getHistOperation());
        model->item(i,1)->setText(tuple.getHistDate());
        if(price > 0 || tuple.getHistOperation() == "DEBIT/CREDIT")
            model->item(i,2)->setText(QString::number(price));
        else
            model->item(i,2)->setText("Cash");

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
    VIEW.individualHistory->setTitle("Historique de " + tuple.getHistFirstName() + " " + tuple.getHistName());
    VIEW.individualHistory->setTotalConsummed(QString::number(totalPrice) + " €");
    //table->sortItems(0, Qt::AscendingOrder);
    //table->sortByColumn(0, Qt::AscendingOrder);
    table->setModel(model);
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);
    return;
}
