#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow()
{
    QWidget *centralWidget = new QWidget;
    this->setCentralWidget(centralWidget);
    this->setGeometry(20, 40, 1000, 800);
    this->setWindowTitle("RAB WareSoft");
    this->setMinimumSize(800, 600);

    QGridLayout *mainWindowLayout = new QGridLayout(centralWidget);
    QFrame *menu = new QFrame(centralWidget);
    menu->setObjectName("menu");
    QFrame *mainPart = new QFrame(centralWidget);
    mainWindowLayout->addWidget(menu, 0, 0);
    mainWindowLayout->addWidget(mainPart, 1, 0);
    mainWindowLayout->setRowStretch(0, 1);
    mainWindowLayout->setRowStretch(1, 20);
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
    mainPart->setLayout(mainPartLayout);


}
