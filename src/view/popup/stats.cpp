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
	totalSoldLastYear = new QLabel(frame);
	numberOfCustomers = new QLabel(frame);
	numberOfProducts = new QLabel(frame);

	accountsTotalLabel = new QLabel("Total des soldes : ", frame);
	moneyInCashRegisterLabel = new QLabel("Argent dans la caisse : ", frame);
	moneyGivenThisYearLabel = new QLabel("Argent amené au bde cette année civile : ", frame);
	moneyGivenLastYearLabel = new QLabel("Argent amené au bde l'année civile précédente : ", frame);
	totalSoldThisYearLabel = new QLabel("Total chiffre d'affaire cette année civile : ", frame);
	totalSoldLastYearLabel = new QLabel("Total chiffre d'affaire l'année civile précédente : ", frame);
	numberOfCustomersLabel = new QLabel("Nombre de comptes : ", frame);
	numberOfProductsLabel = new QLabel("Nombre total de produits : ", frame);

    stocks0Label = new QLabel("Stocks de la catégorie Bières : ", frame);
	stocks1Label = new QLabel("Stocks de la catégorie Pression : ", frame);
	stocks2Label = new QLabel("Stocks de la catégorie Vin : ", frame);
	stocks3Label = new QLabel("Stocks de la catégorie Bouffe salée : ", frame);
	stocks4Label = new QLabel("Stocks de la catégorie Bouffe sucrée : ", frame);
	stocks5Label = new QLabel("Stocks de la catégorie Divers : ", frame);

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
    layout->addWidget(totalSoldThisYearLabel, 4, 0);
	layout->addWidget(totalSoldLastYearLabel, 5, 0);
	layout->addWidget(numberOfCustomersLabel, 6, 0);
	layout->addWidget(numberOfProductsLabel, 7, 0);

	layout->addWidget(accountsTotal, 0, 1);
	layout->addWidget(moneyInCashRegister, 1, 1);
	layout->addWidget(moneyGivenThisYear, 2, 1);
	layout->addWidget(moneyGivenLastYear, 3, 1);
	layout->addWidget(totalSoldThisYear, 4, 1);
	layout->addWidget(totalSoldLastYear, 5, 1);
	layout->addWidget(numberOfCustomers, 6, 1);
	layout->addWidget(numberOfProducts, 7, 1);

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



}

void Stats::launchStats(view_statsTuple& stats, view_productQueue& category0, view_productQueue& category1, view_productQueue& category2,
                 view_productQueue& category3, view_productQueue& category4, view_productQueue& category5)
{
    accountsTotal->setText(QString::number(stats.accountsTotal));
    moneyInCashRegister->setText(QString::number(stats.moneyInCashRegister) + " €");
    moneyGivenThisYear->setText(QString::number(stats.moneyGivenThisYear) + " €");
    moneyGivenLastYear->setText(QString::number(stats.moneyGivenLastYear) + " €");
    totalSoldThisYear->setText(QString::number(stats.totalSoldThisYear) + " €");
    totalSoldLastYear->setText(QString::number(stats.totalSoldLastYear) + " €");
    numberOfCustomers->setText(QString::number(stats.numberOfCustomers));
    numberOfProducts->setText(QString::number(stats.numberOfProducts));

    category0Stocks->setStocks(category0);
    category1Stocks->setStocks(category1);
    category2Stocks->setStocks(category2);
    category3Stocks->setStocks(category3);
    category4Stocks->setStocks(category4);
    category5Stocks->setStocks(category5);

    this->show();
}




// #################### VIEW_STOCKS #######


ViewStocks::ViewStocks(QWidget *parent) :
    MultiList(parent, 3, 0)
{
    headers[0]->setText("Consommation");
    headers[1]->setText("Vol.(cL)");
    headers[2]->setText("Stock");

    stretchColumns = new int[3];
    stretchColumns[0]=0;
    stretchColumns[1]=2;
    stretchColumns[2]=-1;
    defaultHeaderWidth = 100;
    hiddenColumn = -1;
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);
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
    }
    table->sortByColumn(0, Qt::AscendingOrder);
    table->setModel(model);
    updateHeadersSize(defaultHeaderWidth, stretchColumns, hiddenColumn);
    return;
}

