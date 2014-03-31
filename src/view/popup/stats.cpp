#include "stats.h"

Stats::Stats(QWidget *parent) :
    Popup(parent)
{
	VIEW.stats = this;
    //this->setFixedSize(400, 700);
    this->setGeometry(50,50,600, 800);
    this->setStyle(QStyleFactory::create("fusion"));

    titleFont.setPixelSize(16);
    titleFont.setBold(true);

	scrollArea = new QScrollArea(this);
	frame = new QFrame(scrollArea);
    scrollArea->setWidget(frame);
    scrollArea->setWidgetResizable(true);
	accountsTotal = new QLabel(frame);
	moneyInCashRegister = new QLabel(frame);
	moneyGivenThisYear = new QLabel(frame);
	moneyGivenLastYear = new QLabel(frame);
	totalSoldThisYear = new QLabel(frame);
    /*totalTVA_1SoldThisYear = new QLabel(frame);
    totalTVA_2SoldThisYear = new QLabel(frame);
    totalTVA_3SoldThisYear = new QLabel(frame);
	totalSoldLastYear = new QLabel(frame);
    totalTVA_1SoldLastYear = new QLabel(frame);
    totalTVA_2SoldLastYear = new QLabel(frame);
    totalTVA_3SoldLastYear = new QLabel(frame);*/
	numberOfCustomers = new QLabel(frame);
	numberOfProducts = new QLabel(frame);

	accountsTotalLabel = new QLabel("Total des soldes : ", frame);
	moneyInCashRegisterLabel = new QLabel("Argent dans la caisse : ", frame);
	moneyGivenThisYearLabel = new QLabel("Argent amené au bde cette année civile : ", frame);
	moneyGivenLastYearLabel = new QLabel("Argent amené au bde l'année civile précédente : ", frame);
    /*totalSoldThisYearLabel = new QLabel("Total chiffre d'affaire cette année civile : ", frame);
    totalTVA_1SoldThisYearLabel = new QLabel("Dont TVA à taux réduit", frame);
    totalTVA_2SoldThisYearLabel = new QLabel("Dont TVA intermédiaire", frame);
    totalTVA_3SoldThisYearLabel = new QLabel("Dont TVA à taux plein", frame);
	totalSoldLastYearLabel = new QLabel("Total chiffre d'affaire l'année civile précédente : ", frame);
    totalTVA_1SoldLastYearLabel = new QLabel("Dont TVA à taux réduit", frame);
    totalTVA_2SoldLastYearLabel = new QLabel("Dont TVA intermédiaire", frame);
    totalTVA_3SoldLastYearLabel = new QLabel("Dont TVA à taux plein", frame);*/
	numberOfCustomersLabel = new QLabel("Nombre de comptes : ", frame);
	numberOfProductsLabel = new QLabel("Nombre total de produits : ", frame);

    stocks0Label = new QLabel("Stocks de la catégorie ", frame);
    stocks1Label = new QLabel("Stocks de la catégorie ", frame);
    stocks2Label = new QLabel("Stocks de la catégorie ", frame);
    stocks3Label = new QLabel("Stocks de la catégorie ", frame);
    stocks4Label = new QLabel("Stocks de la catégorie ", frame);
    stocks5Label = new QLabel("Stocks de la catégorie ", frame);

	stocks0Label->setFont(titleFont);
	stocks1Label->setFont(titleFont);
	stocks2Label->setFont(titleFont);
	stocks3Label->setFont(titleFont);
	stocks4Label->setFont(titleFont);
	stocks5Label->setFont(titleFont);

    category0Stocks = new ViewStocks(frame);
    category1Stocks = new ViewStocks(frame);
    category2Stocks = new ViewStocks(frame);
    category3Stocks = new ViewStocks(frame);
    category4Stocks = new ViewStocks(frame);
    category5Stocks = new ViewStocks(frame);

	layout = new QGridLayout(frame);
    virtualLayout = new QGridLayout(this);
    virtualLayout->addWidget(scrollArea);
    virtualLayout->setRowStretch(0,1);
    virtualLayout->setColumnStretch(0,1);

    layout->addWidget(accountsTotalLabel, 0, 0);
	layout->addWidget(moneyInCashRegisterLabel, 1, 0);
    layout->addWidget(moneyGivenThisYearLabel, 2, 0);
    layout->addWidget(moneyGivenLastYearLabel, 3, 0);
    /*layout->addWidget(totalSoldThisYearLabel, 4, 0);
    layout->addWidget(totalTVA_1SoldThisYearLabel, 5, 0);
    layout->addWidget(totalTVA_2SoldThisYearLabel, 6, 0);
    layout->addWidget(totalTVA_3SoldThisYearLabel, 7, 0);
    layout->addWidget(totalSoldLastYearLabel, 8, 0);
    layout->addWidget(totalTVA_1SoldLastYearLabel, 9, 0);
    layout->addWidget(totalTVA_2SoldLastYearLabel, 10, 0);
    layout->addWidget(totalTVA_3SoldLastYearLabel, 11, 0);*/
    layout->addWidget(numberOfCustomersLabel, 12, 0);
    layout->addWidget(numberOfProductsLabel, 13, 0);

	layout->addWidget(accountsTotal, 0, 1);
	layout->addWidget(moneyInCashRegister, 1, 1);
	layout->addWidget(moneyGivenThisYear, 2, 1);
	layout->addWidget(moneyGivenLastYear, 3, 1);
	layout->addWidget(totalSoldThisYear, 4, 1);
    /*layout->addWidget(totalTVA_1SoldThisYear, 5, 1);
    layout->addWidget(totalTVA_2SoldThisYear, 6, 1);
    layout->addWidget(totalTVA_3SoldThisYear, 7, 1);
    layout->addWidget(totalSoldLastYear, 8, 1);
    layout->addWidget(totalTVA_1SoldLastYear, 9, 1);
    layout->addWidget(totalTVA_2SoldLastYear, 10, 1);
    layout->addWidget(totalTVA_3SoldLastYear, 11, 1);*/
    layout->addWidget(numberOfCustomers, 12, 1);
    layout->addWidget(numberOfProducts, 13, 1);

    layout->addWidget(stocks0Label, 20, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(stocks1Label, 22, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(stocks2Label, 24, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(stocks3Label, 26, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(stocks4Label, 28, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(stocks5Label, 30, 0, 1, 2, Qt::AlignCenter);

	layout->addWidget(category0Stocks, 21, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(category1Stocks, 23, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(category2Stocks, 25, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(category3Stocks, 27, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(category4Stocks, 29, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(category5Stocks, 31, 0, 1, 2, Qt::AlignCenter);


    category0Stocks->setFixedSize(500, 400);
    category1Stocks->setFixedSize(500, 400);
    category2Stocks->setFixedSize(500, 400);
    category3Stocks->setFixedSize(500, 400);
    category4Stocks->setFixedSize(500, 400);
    category5Stocks->setFixedSize(500, 400);

    category0Stocks->updateSize();
    category1Stocks->updateSize();
	category2Stocks->updateSize();
	category3Stocks->updateSize();
	category4Stocks->updateSize();
    category5Stocks->updateSize();qDebug() << "toto";


    //category0Stocks->setStyleSheet("background: #f00;");
    frame->setLayout(layout);
    CtrlActive = false;

}

void Stats::launchStats(view_statsTuple& stats, view_productQueue& category0, view_productQueue& category1, view_productQueue& category2,
                 view_productQueue& category3, view_productQueue& category4, view_productQueue& category5)
{
    accountsTotal->setText(QString::number(stats.accountsTotal) + " €");
    moneyInCashRegister->setText(QString::number(stats.moneyInCashRegister) + " €");
    moneyGivenThisYear->setText(QString::number(stats.moneyGivenThisYear) + " €");
    moneyGivenLastYear->setText(QString::number(stats.moneyGivenLastYear) + " €");
    /*totalSoldThisYear->setText(QString::number(stats.totalSoldThisYear) + " €");
    totalTVA_1SoldThisYear->setText(QString::number(stats.totalSoldThisYearTVA1) + " €");
    totalTVA_2SoldThisYear->setText(QString::number(stats.totalSoldThisYearTVA2) + " €");
    totalTVA_3SoldThisYear->setText(QString::number(stats.totalSoldThisYearTVA3) + " €");
    totalSoldLastYear->setText(QString::number(stats.totalSoldLastYear) + " €");
    totalTVA_1SoldLastYear->setText(QString::number(stats.totalSoldLastYearTVA1) + " €");
    totalTVA_2SoldLastYear->setText(QString::number(stats.totalSoldLastYearTVA2) + " €");
    totalTVA_3SoldLastYear->setText(QString::number(stats.totalSoldLastYearTVA3) + " €");*/
    numberOfCustomers->setText(QString::number(stats.numberOfCustomers));
    numberOfProducts->setText(QString::number(stats.numberOfProducts));

    db_categoryQueue catQueue = controller->getProductsCategories();
    db_categoryTuple catTuple;
    int n = catQueue.size();
    if(n < 6)
    {
        error->showMessage("Nombre de catégorie de produit insuffisant, rétablissez le bon nombre de catégorie, ou remaniez la classe Stats ...");
        return;
    }
    catTuple = catQueue.front();catQueue.pop();
    stocks0Label->setText(stocks0Label->text() + QString::fromStdString(catTuple.getCategoryName()) + " : ");
    catTuple = catQueue.front();catQueue.pop();
    stocks1Label->setText(stocks1Label->text() + QString::fromStdString(catTuple.getCategoryName()) + " : ");
    catTuple = catQueue.front();catQueue.pop();
    stocks2Label->setText(stocks2Label->text() + QString::fromStdString(catTuple.getCategoryName()) + " : ");
    catTuple = catQueue.front();catQueue.pop();
    stocks3Label->setText(stocks3Label->text() + QString::fromStdString(catTuple.getCategoryName()) + " : ");
    catTuple = catQueue.front();catQueue.pop();
    stocks4Label->setText(stocks4Label->text() + QString::fromStdString(catTuple.getCategoryName()) + " : ");
    catTuple = catQueue.front();catQueue.pop();
    stocks5Label->setText(stocks5Label->text() + QString::fromStdString(catTuple.getCategoryName()) + " : ");

    category0Stocks->setStocks(category0);
    category1Stocks->setStocks(category1);
    category2Stocks->setStocks(category2);
    category3Stocks->setStocks(category3);
    category4Stocks->setStocks(category4);
    category5Stocks->setStocks(category5);

    this->show();
}

void Stats::keyPressEvent(QKeyEvent * key)
{
    if(key->key() == Qt::Key_Control)
        CtrlActive = true;
}

void Stats::keyReleaseEvent(QKeyEvent * key)
{
    if(key->key() == Qt::Key_Control)
        CtrlActive = false;
}

void Stats::lineClicked(int id)
{
    // Call to consumption datas if Ctrl key pressed, else Stock datas
    controller->displayProductGraph(id, CtrlActive);
    CtrlActive = false;
}

// #################### VIEW_STOCKS #######


ViewStocks::ViewStocks(QWidget *parent) :
    MultiList(parent, 4, 0)
{
    VIEW.viewStocks = this;
    headers[0]->setText("Consommation");
    headers[1]->setText("Vol.(cL)");
    headers[2]->setText("Stock");
    headers[3]->setText("Id");

    stretchColumns = new int[3];
    stretchColumns[0]=0;
    stretchColumns[1]=2;
    stretchColumns[2]=-1;
    defaultHeaderWidth = 100;
    hiddenColumn = 3;
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);

    QObject::connect(table, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(lineClicked(QModelIndex)));
}

void ViewStocks::setStocks(view_productQueue& queue)
{
    view_productTuple tuple;
    table->setModel(NULL);

    // Inserting new results
    unsigned numberOfElements = queue.size();
    setRows(numberOfElements);
    for(unsigned i=0 ; i<numberOfElements ; i++)
    {
        tuple = queue.front();
        queue.pop();

        model->item(i,0)->setText(tuple.getProductName());
        model->item(i,1)->setText(QString::number(tuple.getProductVolume()));
        model->item(i,2)->setText(QString::number(tuple.getProductStock()));
        model->item(i,3)->setText(QString::number(tuple.getProductId()));
    }
    table->sortByColumn(0, Qt::AscendingOrder);
    table->setModel(model);
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);
    return;
}

void ViewStocks::lineClicked(QModelIndex index)
{
    VIEW.stats->lineClicked(model->item(index.row(), 3)->text().toInt());
}

