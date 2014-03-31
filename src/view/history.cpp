#include "history.h"

History::History(QWidget *parent) : MultiList(parent, 6, 0, false)
{
    VIEW.history = this;
    this->setObjectName("history"); // for CSS
    // ##### Definition des légendes en haut de colonne ######
    headers[0]->setText("Nom");
    headers[1]->setText("Prénom");
    headers[2]->setText("Opération");
    headers[3]->setText("Montant");
    headers[4]->setText("Date");
    headers[5]->setText("id");

    // ##### Fin Définition #####

    // une colonne fait 60 pixels par défaut. Les colonnes 0,1,2,4 s'adapteront également à l'espace restant
    stretchColumns = new int[5];
    stretchColumns[0]=0;
    stretchColumns[1]=1;
    stretchColumns[2]=2;
    stretchColumns[3]=4;
    stretchColumns[4]=-1;
    defaultHeaderWidth = 60;
    hiddenColumn = 5;
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);
}

void History::setHistory(view_histQueue queue)
{
    view_histTuple tuple;
    QFont historyFont;
    historyFont.setPixelSize(11);
    table->setModel(NULL);

    // Inserting new results
    unsigned numberOfElements = queue.size();
    setRows(numberOfElements);

    for(unsigned i=0; i < numberOfElements ; i++)
    {
        tuple = queue.front();
        queue.pop();
        float price = tuple.getHistPrice();
        model->item(i,0)->setText(tuple.getHistName());
        model->item(i,1)->setText(tuple.getHistFirstName());
        model->item(i,2)->setText(tuple.getHistOperation());
        if(price >= 0 || tuple.getHistOperation() == "DEBIT/CREDIT")
            model->item(i,3)->setText(QString::number(price));
        else
            model->item(i,3)->setText("Cash (" + QString::number(-price)+")");
        model->item(i,4)->setText(tuple.getHistDate());
        model->item(i,5)->setText(QString::number(i));

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
        {
            model->item(i,j)->setFont(historyFont);
            model->item(i,j)->setBackground(*color);
        }
    }
    table->setModel(model);
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);

    // Ascending or Descending depends on order of queue
    //table->sortItems(5, Qt::AscendingOrder);
    return;
}
