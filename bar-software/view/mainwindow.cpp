#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow()
{
    // Setting up central widget of Mainwindow (actually the only part of MainWindow)
    QWidget *centralWidget = new QWidget;
    this->setCentralWidget(centralWidget);
    this->setGeometry(20, 40, 1000, 800);
    this->setWindowTitle("RAB WareSoft");
    this->setMinimumSize(800, 600);

    // Creating main widgets (menu at top and the remaining
    QGridLayout *mainWindowLayout = new QGridLayout(centralWidget);
    QFrame *menu = new QFrame(centralWidget);
    menu->setObjectName("menu");
    QFrame *mainPart = new QFrame(centralWidget);
    mainWindowLayout->addWidget(menu, 0, 0);
    mainWindowLayout->addWidget(mainPart, 1, 0);
    // row 0 (the menu) have a weight of 1 and the row remaining (at bottom) have a weight of 20
    // So menu is 20 times thinner as the rest
    mainWindowLayout->setRowStretch(0, 1);
    mainWindowLayout->setRowStretch(1, 20);
    mainWindowLayout->setContentsMargins(0,0,0,0);
    centralWidget->setLayout(mainWindowLayout);

    // Adding content of the top menu (searchbar and configuration buttons)
    QFrame *searchBar = new QFrame(menu);
    QLabel *searchIcon = new QLabel(searchBar);
    searchIcon->setPixmap(QPixmap(GLOBAL_PATH + "view/pictures/search.png"));
    QLineEdit *searchText = new QLineEdit("", searchBar);
    searchBar->setObjectName("searchBar");
    QHBoxLayout *searchBarLayout = new QHBoxLayout(searchBar);
    searchBarLayout->addWidget(searchIcon);
    searchBarLayout->addWidget(searchText);
    searchBar->setLayout(searchBarLayout);

    // Adding the left and right frames
    rightPart = new RightPart(mainPart);
    leftPart = new LeftPart(mainPart);
    QGridLayout *mainPartLayout = new QGridLayout(mainPart);
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
    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+D"), this);
    QObject::connect(searchText, SIGNAL(textEdited(const QString &)), this, SLOT(searchChanged(const QString &)));
    QObject::connect(timerSearch, SIGNAL(timeout()), this, SLOT(sendSearch()));
    QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(shortcut()));
    QObject::connect(timerAtStart, SIGNAL(timeout()), this, SLOT(updateSize()));
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

void MainWindow::shortcut()
{
    qDebug() << "CTRL + D";
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
}


