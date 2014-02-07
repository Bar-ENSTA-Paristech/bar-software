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

    // ####### TEST #######
    /*std::queue< std::tuple< QString, QString, QString, float, QString > > toto;
    std::tuple< QString, QString, QString, float, QString > titi("Chat", "Mehdi", "DEBIT", -1000, "17h45 24-09-2013");
    std::tuple< QString, QString, QString, float, QString > titi2("Diallo", "Guytoof", "CREDIT", 20, "17h44 24-09-2013");
    std::tuple< QString, QString, QString, float, QString > titi3("Manchoul", "Simon", "Duvel 33cL", 1.9, "17h41 24-09-2013");
    toto.push(titi);
    toto.push(titi2);
    toto.push(titi3);
    this->setHistory(toto);
    view_historyTuple titi;
    view_historyQueue toto;
    titi.setHistoryName("Chat");titi.setHistoryFirstName("Mehdi");titi.setHistoryOperation("DEBIT");titi.setHistoryPrice(-1000);titi.setHistoryDate("17h45 24-09-2013");
    toto.push(titi);
    titi.setHistoryName("Diallo");titi.setHistoryFirstName("Guitoof");titi.setHistoryOperation("CREDIT");titi.setHistoryPrice(20);titi.setHistoryDate("17h44 24-09-2013");
    toto.push(titi);
    titi.setHistoryName("Manchoul");titi.setHistoryFirstName("Simon");titi.setHistoryOperation("Duvel 33cL");titi.setHistoryPrice(1.9);titi.setHistoryDate("17h41 24-09-2013");
    toto.push(titi);


    this->setHistory(toto);*/
    // ####### FIN TEST #######*/

}

void History::setHistory(view_histQueue queue)
{
    // OBSOLETE!  TUPLE : QString name, QString firstName, QString operation, float value, QString date(hh-mm JJ-MM-YYYY)
    view_histTuple tuple;
    QFont historyFont;
    historyFont.setPixelSize(11);
    table->setModel(NULL);

    // Inserting new results
    QBrush color;
    unsigned numberOfElements = queue.size();
    setRows(numberOfElements);

    for(unsigned i=0; i < numberOfElements ; i++)
    {
        tuple = queue.front();
        queue.pop();
        model->item(i,0)->setText(tuple.getHistName());
        model->item(i,1)->setText(tuple.getHistFirstName());
        model->item(i,2)->setText(tuple.getHistOperation());
        model->item(i,3)->setText(QString::number(tuple.getHistPrice()));
        model->item(i,4)->setText(tuple.getHistDate());
        model->item(i,5)->setText(QString::number(i));
        if(tuple.getHistOperation() == "DEBIT")
            color.setColor("#f2dede"); // light red
        else if(tuple.getHistOperation() == "CREDIT")
            color.setColor("#dfd008"); // light green
        else
            color.setColor(Qt::black);

        for(int j=0 ; j < columns ; j++)
        {
            model->item(i,j)->setFont(historyFont);
            model->item(i,j)->setForeground(color);
        }
    }
    table->setModel(model);
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);

    // Ascending or Descending depends on order of queue
    //table->sortItems(5, Qt::AscendingOrder);
    return;
}
