#include "mainwindow.h"

MainWindow::MainWindow()
{
    QWidget *centralWidget = new QWidget;
    this->setCentralWidget(centralWidget);
    this->setGeometry(20, 40, 1000, 800);

    QGridLayout *mainWindowLayout = new QGridLayout(centralWidget);
    QFrame *menu = new QFrame(centralWidget);
    QFrame *mainPart = new QFrame(centralWidget);
    mainWindowLayout->addWidget(menu, 0, 0);
    mainWindowLayout->addWidget(mainPart, 1, 0);
    centralWidget->setLayout(mainWindowLayout);

    // Adding content of the top menu (searcbar and configuration buttons)
    QLineEdit *searchBar = new QLineEdit("search", menu);
    searchBar->setMaximumSize(150, 20);

    // Adding the left and right frames
    RightPart *rightPart = new RightPart(mainPart);
    LeftPart *leftPart = new LeftPart(mainPart);
    QGridLayout *mainPartLayout = new QGridLayout(mainPart);
    mainPartLayout->addWidget(leftPart, 0, 0);
    mainPartLayout->addWidget(rightPart, 0, 1);
    mainPart->setLayout(mainPartLayout);


}
