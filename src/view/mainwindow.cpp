#include "mainwindow.h"
#include "controller.h"
#include <QDebug>

ViewObjects VIEW;

MainWindow::MainWindow()
{
    VIEW.mainWindow = this;
    // Setting up central widget of Mainwindow (actually the only part of MainWindow)
    centralWidget = new QWidget;
    this->setCentralWidget(centralWidget);
    this->setGeometry(20, 40, 1000, 800);
    this->setWindowTitle("RAB WareSoft");
    this->setMinimumSize(800, 600);

    // Creating main widgets (menu at top and the remaining
    mainWindowLayout = new QGridLayout(centralWidget);
    menu = new QFrame(centralWidget);
    menu->setObjectName("menu");
    mainPart = new QFrame(centralWidget);
    mainWindowLayout->addWidget(menu, 0, 0);
    mainWindowLayout->addWidget(mainPart, 1, 0);
    // row 0 (the menu) have a weight of 1 and the row remaining (at bottom) have a weight of 20
    // So menu is 20 times thinner as the rest
    mainWindowLayout->setRowStretch(0, 1);
    mainWindowLayout->setRowStretch(1, 20);
    mainWindowLayout->setContentsMargins(0,0,0,0);
    centralWidget->setLayout(mainWindowLayout);

    // Adding content of the top menu (searchbar and configuration buttons)
    searchBar = new QFrame(menu);
    logo = new QLabel(menu);
    logo->setPixmap(QPixmap(GLOBAL_PATH + "resources/pictures/logo.png"));
    menuLayout = new QGridLayout(menu);
    menuLayout->addWidget(searchBar, 0, 0);
    menuLayout->addWidget(logo, 0, 2);
    menu->setLayout(menuLayout);
    menuLayout->setContentsMargins(0,0,0,0);
    menuLayout->setColumnStretch(1,1);

    searchIcon = new QLabel(searchBar);
    searchIcon->setPixmap(QPixmap(GLOBAL_PATH + "resources/pictures/search.png"));
    //searchIcon->setStyleSheet("opacity: 0");
    searchText = new QLineEdit("", searchBar);
    searchBar->setObjectName("searchBar");
    searchBarLayout = new QHBoxLayout(searchBar);
    searchBarLayout->addWidget(searchIcon);
    searchBarLayout->addWidget(searchText);
    searchBar->setLayout(searchBarLayout);

    // Adding the left and right frames
    rightPart = new RightPart(mainPart);
    leftPart = new LeftPart(mainPart);
    // Referencing all pointers of objects in mainWindow
    leftPart->getPointers(&searchResults, &history, &customerPanel);
    rightPart->getPointers(&productsChoices, &consoLogos, &cartDisplay);

    mainPartLayout = new QGridLayout(mainPart);
    mainPartLayout->addWidget(leftPart, 0, 0);
    mainPartLayout->addWidget(rightPart, 0, 1);
    mainPartLayout->setContentsMargins(0,0,0,0);
    mainPart->setLayout(mainPartLayout);

    // Will be used not to spam controller with new search : not more than one request each 250ms
    timerSearch = new QTimer();
    timerSearch->setSingleShot(true);
    timerAtStart = new QTimer();
    timerAtStart->setSingleShot(true);
    timerAtStart->start(500);

    // ShortCuts
    setShortcut();

    QObject::connect(searchText, SIGNAL(textEdited(const QString &)), this, SLOT(searchChanged(const QString &)));
    QObject::connect(timerSearch, SIGNAL(timeout()), this, SLOT(sendSearch()));
    QObject::connect(timerAtStart, SIGNAL(timeout()), this, SLOT(updateSize()));

    // DESIGN
    menu->setStyleSheet("background : url("+GLOBAL_PATH+"resources/pictures/menu_background.png);");

}

MainWindow::~MainWindow()
{
    /*delete controller;
    delete timerSearch;
    delete timerAtStart;
    delete rightPart;
    delete leftPart;
    delete searchResults;
    delete customerPanel;
    delete cartDisplay;
    delete productsChoices;
    delete history;
    delete consoLogos;
    delete centralWidget;
    delete mainWindowLayout;
    delete menu;
    delete mainPart;
    delete searchBar;
    delete searchIcon;
    delete searchText;
    delete searchBarLayout;
    delete mainPartLayout;
    delete shortcut;*/
}


void MainWindow::searchChanged(const QString & text)
{
    timerSearch->start(250); // on évite de faire des requêtes à moins de 250 ms d'écart
    search =  text;
}

void MainWindow::sendSearch()
{
    controller->newText_Search(search);
}

void MainWindow::shortcutRoutine()
{
    QShortcut* sender = (QShortcut*) QObject::sender();
    if(sender->key().toString() == QString("Ctrl+B"))
        consoLogos->newCategorieToController(0);
    else if(sender->key().toString() == QString("Ctrl+P"))
        consoLogos->newCategorieToController(1);
    else if(sender->key().toString() == QString("Ctrl+W"))
        consoLogos->newCategorieToController(2);
    else if(sender->key().toString() == QString("Ctrl+Q"))
        consoLogos->newCategorieToController(3);
    else if(sender->key().toString() == QString("Ctrl+U"))
        consoLogos->newCategorieToController(4);
    else if(sender->key().toString() == QString("Ctrl+D"))
        consoLogos->newCategorieToController(5);


}

void MainWindow::updateSize()
{
    leftPart->updateSize();
    rightPart->updateSize();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    this->updateSize();
}

void MainWindow::setController(Controller *controllerParam)
{
    controller = controllerParam;
    //controller->setViewPointers(searchResults, customerPanel, cartDisplay, productsChoices, history);
    controller->setViewPointers(&   VIEW);
    //viewManager->controller = controllerParam;
    rightPart->setController(controller);
    leftPart->setController(controller);

    controller->mainController();
}

void MainWindow::setShortcut()
{
    int numberOfShortcuts = 8;

    shortcuts = new QShortcut*[numberOfShortcuts];
    shortcuts[0] = new QShortcut(QKeySequence("Ctrl+B"), this);
    shortcuts[1] = new QShortcut(QKeySequence("Ctrl+P"), this);
    shortcuts[2] = new QShortcut(QKeySequence("Ctrl+W"), this);
    shortcuts[3] = new QShortcut(QKeySequence("Ctrl+Q"), this);
    shortcuts[4] = new QShortcut(QKeySequence("Ctrl+U"), this);
    shortcuts[5] = new QShortcut(QKeySequence("Ctrl+D"), this);
    shortcuts[6] = new QShortcut(QKeySequence("Enter"), this);
    shortcuts[7] = new QShortcut(QKeySequence("Return"), this);

    for(int i=0 ; i < numberOfShortcuts ; i++)
        QObject::connect(shortcuts[i], SIGNAL(activated()), this, SLOT(shortcutRoutine()));
}


void MainWindow::setGraph(db_dataarray& data, QString xTitle, QString yTitle, QString title)
{
    if(data.first.size() != data.second.size())
    {
        qDebug() << "ERROR : Graph datas haven't the same size !";
        return;
    }

    QCustomPlot* customPlot = new QCustomPlot();

    // create graph and assign data to it:
    customPlot->addGraph();
    QVector<double> x, y;
    x = QVector<double>::fromStdVector(data.first);

    y = QVector<double>::fromStdVector(data.second);
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->setLocale(QLocale(QLocale::French, QLocale::France));
    customPlot->xAxis->setLabel(xTitle);
    customPlot->yAxis->setLabel(yTitle);
    customPlot->xAxis->setDateTimeFormat("MMMM\nyyyy");
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setAutoTickStep(true);
    // set axes ranges, so we see all data:
    register double minX = x.first(), maxX = x.first(), minY = y.first(), maxY=y.first();
    register double xi, yi;
    for(int i =0 ; i < x.size() ; i++)
    {
        xi = x[i];
        yi = y[i];
        if(xi < minX)
            minX = xi;
        else if(xi > maxX)
            maxX = xi;

        if(yi < minY)
            minY = yi;
        else if(yi > maxY)
            maxY = yi;
    }
    customPlot->xAxis->setRange(minX, maxX);

    customPlot->yAxis->setRange(minY, maxY);
    customPlot->replot();
    customPlot->setGeometry(20,40,800,600);
    customPlot->setWindowTitle(title);
    customPlot->show();
}

