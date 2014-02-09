#include "mainwindow.h"
#include "controller.h"
#include <QDebug>
#include <QStyleFactory>

ViewObjects VIEW;

MainWindow::MainWindow()
{
    VIEW.mainWindow = this;
    // Setting up central widget of Mainwindow (actually the only part of MainWindow)
    centralWidget = new QWidget;
    this->setCentralWidget(centralWidget);
    this->setGeometry(20, 40, 1000, 800);
    this->setWindowTitle("RAB WareSoft");
    this->setMinimumSize(900, 600);
    this->setStyle(QStyleFactory::create("fusion"));

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
    menuButtons = new QFrame(menu);
    menuButtons->setObjectName("menuButtons");
    logo = new QLabel(menu);
    logo->setPixmap(QPixmap(GLOBAL_PATH + "resources/pictures/logo.png"));
    menuLayout = new QGridLayout(menu);
    menuLayout->addWidget(searchBar, 0, 0);
    menuLayout->addWidget(menuButtons, 0, 2);
    menuLayout->addWidget(logo, 0, 4);
    menu->setLayout(menuLayout);
    menuLayout->setContentsMargins(0,0,0,0);
    menuLayout->setColumnStretch(1,1);
    menuLayout->setColumnStretch(3,1);

    // SEARCH PART
    searchIcon = new QLabel(searchBar);
    searchIcon->setPixmap(QPixmap(GLOBAL_PATH + "resources/pictures/search.png"));
    searchIcon->setStyleSheet("background: none");
    searchText = new QLineEdit("", searchBar);
    searchText->setStyleSheet("background: white;");
    searchBar->setObjectName("searchBar");
    searchBarLayout = new QHBoxLayout(searchBar);
    searchBarLayout->addWidget(searchIcon);
    searchBarLayout->addWidget(searchText);
    searchBar->setLayout(searchBarLayout);

    // MENU BUTTONS
    buttonsLayout = new QGridLayout(menuButtons);
    globalHistory = new QPushButton(QIcon(GLOBAL_PATH + "resources/pictures/history.png"), "", menuButtons);
    globalHistory->setFlat(true);
    globalHistory->setCursor(Qt::PointingHandCursor);
    globalHistory->setIconSize(QSize(32,32));
    globalHistory->setStyleSheet("background: none;");
    globalHistory->setToolTip("Historique Global");
    newCustomer = new QPushButton(QIcon(GLOBAL_PATH + "resources/pictures/newCust.png"), "", menuButtons);
    newCustomer->setFlat(true);
    newCustomer->setCursor(Qt::PointingHandCursor);
    newCustomer->setIconSize(QSize(32,32));
    newCustomer->setStyleSheet("background: none;");
    newCustomer->setToolTip("Ajouter un nouveau client");
    addStock = new QPushButton(QIcon(GLOBAL_PATH + "resources/pictures/addStock.png"), "", menuButtons);
    addStock->setFlat(true);
    addStock->setCursor(Qt::PointingHandCursor);
    addStock->setIconSize(QSize(32,32));
    addStock->setStyleSheet("background: none;");
    addStock->setToolTip("Ajouter/retirer du stock");
    addProduct = new QPushButton(QIcon(GLOBAL_PATH + "resources/pictures/addProduct.png"), "", menuButtons);
    addProduct->setFlat(true);
    addProduct->setCursor(Qt::PointingHandCursor);
    addProduct->setIconSize(QSize(32,32));
    addProduct->setStyleSheet("background: none;");
    addProduct->setToolTip("Ajouter une nouvelle consommation");
    editProduct = new QPushButton(QIcon(GLOBAL_PATH + "resources/pictures/editProduct.png"), "", menuButtons);
    editProduct->setFlat(true);
    editProduct->setCursor(Qt::PointingHandCursor);
    editProduct->setIconSize(QSize(32,32));
    editProduct->setStyleSheet("background: none;");
    editProduct->setToolTip("Editer une consommation particulière");
    editLogin = new QPushButton(QIcon(GLOBAL_PATH + "resources/pictures/editLogin.png"), "", menuButtons);
    editLogin->setFlat(true);
    editLogin->setCursor(Qt::PointingHandCursor);
    editLogin->setIconSize(QSize(32,32));
    editLogin->setStyleSheet("background: none;");
    editLogin->setToolTip("Organiser les mots de passe du logiciel");
    stats = new QPushButton(QIcon(GLOBAL_PATH + "resources/pictures/stats.png"), "", menuButtons);
    stats->setFlat(true);
    stats->setCursor(Qt::PointingHandCursor);
    stats->setIconSize(QSize(32,32));
    stats->setStyleSheet("background: none;");
    stats->setToolTip("Visualisez toutes les stats du bar ici !");
    admin = new QPushButton(QIcon(GLOBAL_PATH + "resources/pictures/admin.png"), "", menuButtons);
    admin->setFlat(true);
    admin->setCursor(Qt::PointingHandCursor);
    admin->setIconSize(QSize(32,32));
    admin->setStyleSheet("background: none;");
    admin->setToolTip("Panneau d'administration");
    buttonsLayout->addWidget(globalHistory,0,0);
    buttonsLayout->addWidget(newCustomer, 0,1);
    buttonsLayout->addWidget(addStock, 0,2);
    buttonsLayout->addWidget(addProduct, 0,3);
    buttonsLayout->addWidget(editProduct, 0,4);
    buttonsLayout->addWidget(editLogin, 0,5);
    buttonsLayout->addWidget(stats, 0,6);
    buttonsLayout->addWidget(admin, 0,7);
    buttonsLayout->setContentsMargins(0,0,0,0);
    menuButtons->setLayout(buttonsLayout);

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

    // Popup Windows
    VIEW.login = new Login();
    calculatorWindow = new Calculator();
    VIEW.individualHistory = new IndividualHistory();
    VIEW.editCustomer = new EditCustomer();
    VIEW.deleteCustomer = new DeleteCustomer();
    VIEW.globalHistory = new GlobalHistory();
    VIEW.newCustomer = new NewCustomer();
    VIEW.addStock = new AddStock();
    VIEW.addProduct = new AddProduct();
    VIEW.editProduct = new EditProduct();
    VIEW.editLogin = new EditLogin();
    VIEW.stats = new Stats();
    VIEW.admin = new Admin();

    QObject::connect(searchText, SIGNAL(textEdited(const QString &)), this, SLOT(searchChanged(const QString &)));
    QObject::connect(timerSearch, SIGNAL(timeout()), this, SLOT(sendSearch()));
    QObject::connect(timerAtStart, SIGNAL(timeout()), this, SLOT(updateSize()));
    QObject::connect(globalHistory, SIGNAL(clicked()), this, SLOT(launchGlobalHistory()));
    QObject::connect(newCustomer, SIGNAL(clicked()), this, SLOT(launchNewCustomer()));
    QObject::connect(addStock, SIGNAL(clicked()), this, SLOT(launchAddStock()));
    QObject::connect(addProduct, SIGNAL(clicked()), this, SLOT(launchAddProduct()));
    QObject::connect(editProduct, SIGNAL(clicked()), this, SLOT(launchEditProduct()));
    QObject::connect(editLogin, SIGNAL(clicked()), VIEW.editLogin, SLOT(launchEditLogin()));
    QObject::connect(stats, SIGNAL(clicked()), this, SLOT(launchStats()));
    QObject::connect(admin, SIGNAL(clicked()), this, SLOT(launchAdmin()));


    // DESIGN
    menu->setStyleSheet("background : url("+GLOBAL_PATH+"resources/pictures/menu_background.png);");
    //this->setStyleSheet("background-color: black;");


    //tmpLayout->addWidget(VIEW.individualHistory, 0,0);
    //widget->setLayout(tmpLayout);
    //VIEW.individualHistory->show();
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
    else if(sender->key().toString() == QString("Enter") || sender->key().toString() == QString("Return"))
        VIEW.cartDisplay->tryValidateCart();


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
    VIEW.login->setController(controller);
    calculatorWindow->setController(controller);
    VIEW.individualHistory->setController(controller);
    VIEW.editCustomer->setController(controller);
    VIEW.newCustomer->setController(controller);
    VIEW.addStock->setController(controller);
    VIEW.addProduct->setController(controller);
    VIEW.editProduct->setController(controller);
    VIEW.editLogin->setController(controller);
    VIEW.admin->setController(controller);
    VIEW.stats->setController(controller);
    VIEW.viewStocks->setController(controller);

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
    customPlot->setWindowFlags(Qt::WindowStaysOnTopHint);
    customPlot->setAttribute(Qt::WA_DeleteOnClose); // Pour supprimer l'espace mémoire à la fermeture de la fenêtre.

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

void MainWindow::launchGlobalHistory()
{
    controller->newClic_GlobalHistory();
}

void MainWindow::launchNewCustomer()
{
    controller->newClic_NewCustomer();
}

void MainWindow::launchAddStock()
{
    controller->newClic_AddStock();
}

void MainWindow::launchAddProduct()
{
    controller->newClic_AddProduct();
}

void MainWindow::launchEditProduct()
{
    controller->newClic_EditProduct();
}

void MainWindow::launchStats()
{
    controller->newClic_Stats();
}

void MainWindow::launchAdmin()
{
    controller->newClic_Admin();
}
