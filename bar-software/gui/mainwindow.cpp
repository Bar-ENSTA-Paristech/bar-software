#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow()
{
    QWidget *centralWidget = new QWidget;
    this->setCentralWidget(centralWidget);
    this->setGeometry(20, 40, 1000, 800);
    this->setWindowTitle("RAB WareSoft");
    this->setMinimumSize(800, 600);
    centralWidget->setStyleSheet("padding-top: 0px;");

    QGridLayout *mainWindowLayout = new QGridLayout(centralWidget);
    QFrame *menu = new QFrame(centralWidget);
    menu->setObjectName("menu");
    QFrame *mainPart = new QFrame(centralWidget);
    mainWindowLayout->addWidget(menu, 0, 0);
    mainWindowLayout->addWidget(mainPart, 1, 0);
    mainWindowLayout->setRowStretch(0, 1);
    mainWindowLayout->setRowStretch(1, 20);
    mainWindowLayout->setContentsMargins(0,0,0,0);
    qDebug() << mainWindowLayout->rowStretch(0);
    centralWidget->setLayout(mainWindowLayout);

    // Adding content of the top menu (searchbar and configuration buttons)
    QFrame *searchBar = new QFrame(menu);
    QLabel *searchIcon = new QLabel(searchBar);
    searchIcon->setPixmap(QPixmap(GLOBAL_PATH + "gui/pictures/search.png"));
    QLineEdit *searchText = new QLineEdit("", searchBar);
    searchBar->setObjectName("searchBar");
    //searchBar->setMaximumSize(150, 20);
    QHBoxLayout *searchBarLayout = new QHBoxLayout(searchBar);
    searchBarLayout->addWidget(searchIcon);
    searchBarLayout->addWidget(searchText);
    searchBar->setLayout(searchBarLayout);

    // Adding the left and right frames
    RightPart *rightPart = new RightPart(mainPart);
    LeftPart *leftPart = new LeftPart(mainPart);
    QGridLayout *mainPartLayout = new QGridLayout(mainPart);
    mainPartLayout->addWidget(leftPart, 0, 0);
    mainPartLayout->addWidget(rightPart, 0, 1);
    mainPartLayout->setContentsMargins(0,0,0,0);
    mainPart->setLayout(mainPartLayout);

    timer = new QTimer();
    timer->setSingleShot(true);
    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+D"), this);
    QObject::connect(searchText, SIGNAL(textEdited(const QString &)), this, SLOT(searchChanged(const QString &)));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(sendSearch()));
    QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(shortcut()));


}


void MainWindow::searchChanged(const QString & text)
{
    timer->start(250); // on évite de faire des requêtes à moins de 250 ms d'écart
    search =  text;
}

void MainWindow::sendSearch()
{
    qDebug() << search;
}

void MainWindow::shortcut()
{
    qDebug() << "CTRL + D";
}
