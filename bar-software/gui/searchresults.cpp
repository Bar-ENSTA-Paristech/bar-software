#include "searchresults.h"

SearchResults::SearchResults(QWidget *parent)
{
    setParent(parent);
    this->setObjectName("searchResults");
    qDebug() <<"prout " << this->width();

    /*QTableWidget *list = new QTableWidget(this);
    QStringList entetes;
    entetes << "titre" << "message";
    list->setHorizontalHeaderLabels(entetes);*/
    //list->setColumnCount(4);
    //list->setRowCount(4);
    //list->setRowHeight(0, 20);
    //QTableWidgetItem a;
    //a.setText("test");
    //list->setItem(0, 0, &a);
    //list->setHorizontalHeaderItem(0, QTableWidgetItem("test"));
    //list->addItem("tachatte tachatte tachatte tachatte tachatte tachatte tachatte tachatte tachatte tachatte ");

    /*QTreeWidget *treeView = new QTreeWidget(this);
    treeView->setColumnCount (2 ) ;
    treeView->setRootIsDecorated(false);
    treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    treeView->setSelectionMode ( QAbstractItemView::SingleSelection);
    //treeView->header() ->hide();
    QStringList testitem;
    testitem.append("test");
    testitem.append("test col 2");
    treeView-> addTopLevelItem(new QTreeWidgetItem(testitem,QTreeWidgetItem::UserType));
    treeView-> addTopLevelItem(new QTreeWidgetItem(testitem,QTreeWidgetItem::UserType));*/

    QTableWidget *list = new QTableWidget(this);
    list->setSelectionBehavior(QAbstractItemView::SelectRows);
    list->setObjectName("searchResultsTable");
    list->setShowGrid(false);
    list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    QFont font;
    font.setStyleHint(QFont::SansSerif);
    font.setPixelSize(15);
    QStringList labels;
    labels << "test" << "tachatte" << "version" << "pute";
    qDebug() << labels;
    list->setVerticalHeaderLabels(labels);
    //list->verticalHeader->setHidden(true);
    int lignes = 4;
    list->setColumnCount(4);
    list->setRowCount(lignes);
    for(int i = 0 ; i< lignes ; i++)
        list->setRowHeight(i, 20);
    QTableWidgetItem *test = new QTableWidgetItem;
    test->setText("prout");
    QTableWidgetItem *test2 = new QTableWidgetItem;
    test2->setText("maxi");
    list->setItem(1, 1, test);
    list->setItem(1, 0, test2);
    QBrush paintBottle(Qt::red);
    test->setForeground(paintBottle);
    test->setFont(font);


    list->resize(this->width(), this->height());


}

void SearchResults::setSearchResults()
{

}
