#include "history.h"

History::History(QWidget *parent) : MultiList(parent, 4, 4)
{
    this->setObjectName("history"); // for CSS
    // ##### Definition des légendes en haut de colonne ######
    QTableWidgetItem *headers = new QTableWidgetItem[columns];
    headers[0].setText("Nom");
    headers[1].setText("Prénom");
    headers[2].setText("Opération");
    headers[3].setText("Date");
    for(int i=0 ; i < columns ; i++)// On assigne ces légendes au tableau
        list->setHorizontalHeaderItem(i, &headers[i]);
    // ##### Fin Définition #####

    // une colonne fait 120 pixels par défaut. Les colonnes 1 et 2 s'adapteront également à l'espace restant
    list->horizontalHeader()->setDefaultSectionSize(120);
    list->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    list->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    // on redimensionne à un valeur arbitraire au démarrage
    list->resize(470, 300);
}

void History::setHistory()
{

}
