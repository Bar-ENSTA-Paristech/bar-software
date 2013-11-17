#include "mainwindow.h"
#include "controller.h"
#include <QDebug>

MainWindow::MainWindow()
{
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
    qDebug() << sender->key().toString();
    this->updateSize();
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
    controller->setViewPointers(searchResults, customerPanel, cartDisplay, productsChoices, history);
    //viewManager->controller = controllerParam;
    rightPart->setController(controller);
    leftPart->setController(controller);
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


