#include "admin.h"

Admin::Admin(QWidget *parent) :
    Popup(parent)
{
    VIEW.admin = this;
    this->setGeometry(50,50, 400, 300);

    layout = new QGridLayout(this);
    //negativeAllowed = new QCheckBox("Négatif autorisé", this);
    cashTransferLabel = new QLabel("Argent transféré au BDE (€): ", this);
    cashTransfer = new QLineEdit("0", this);
    oldHistory = new QPushButton(QIcon(GLOBAL_PATH + "resources/pictures/history_old.png"), "", this);
    oldHistory->setFlat(true);
    oldHistory->setCursor(Qt::PointingHandCursor);
    oldHistory->setIconSize(QSize(32,32));
    oldHistory->setStyleSheet("background: none;");
    oldHistory->setToolTip("Voir le vieil historique");
    oldHistoryBeginLabel = new QLabel("Afficher depuis année ", this);
    oldHistoryBegin = new QLineEdit(this);
    oldIndividualHistory = new QPushButton(QIcon(GLOBAL_PATH + "resources/pictures/history_individual_old.png"), "", this);
    oldIndividualHistory->setFlat(true);
    oldIndividualHistory->setCursor(Qt::PointingHandCursor);
    oldIndividualHistory->setIconSize(QSize(32,32));
    oldIndividualHistory->setStyleSheet("background: none;");
    oldIndividualHistory->setToolTip("Voir le vieux historique de cette personne");
    oldIndividualCustomer = new QComboBox(this);
    individualGraphButton = new QPushButton(QIcon(GLOBAL_PATH + "resources/pictures/graph.png"), "", this);
    individualGraphButton->setFlat(true);
    individualGraphButton->setCursor(Qt::PointingHandCursor);
    individualGraphButton->setIconSize(QSize(32,32));
    individualGraphButton->setStyleSheet("background: none;");
    individualGraphButton->setToolTip("Voir le graphe de solde de cette personne");
    oldCustCategoryNameLabel = new QLabel("Changer le nom de cette catégorie", this);
    oldCustCategoryName = new QComboBox(this);
    newCustCategoryName = new QLineEdit(this);
    oldProdCategoryNameLabel = new QLabel("Changer le nom de cette catégorie", this);
    oldProdCategoryName = new QComboBox(this);
    newProdCategoryName = new QLineEdit(this);
    tvaEditLabel = new QLabel("Changement taux TVA : ", this);
    tvaEdit = new QComboBox(this);
    tvaEditNewValue = new QLineEdit(this);
    tvaPdfLabel = new QLabel("Année Tva", this);
    tvaPdf = new QLineEdit(this);
    tvaPdfButton = new QPushButton("Générer Pdf", this);

    logLabel = new QLabel("Mois (AAAA-MM) : ", this);
    logYear = new QLineEdit(this);
    viewLog = new QPushButton("Voir le log", this);

    validateButton = new QPushButton("Valider", this);
    cancelButton = new QPushButton("Annuler", this);

    layout->addWidget(oldHistoryBeginLabel, 0,0);
    layout->addWidget(oldHistoryBegin, 0,1);
    layout->addWidget(oldHistory, 0,2);
    layout->addWidget(oldIndividualCustomer, 1,0);
    layout->addWidget(oldIndividualHistory, 1,1);
    layout->addWidget(individualGraphButton, 1,2);
    layout->addWidget(oldCustCategoryNameLabel, 2, 0);
    layout->addWidget(oldCustCategoryName, 2 , 1);
    layout->addWidget(newCustCategoryName, 2,2);
    layout->addWidget(oldProdCategoryNameLabel, 3, 0);
    layout->addWidget(oldProdCategoryName, 3 , 1);
    layout->addWidget(newProdCategoryName, 3,2);
    layout->addWidget(logLabel, 4,0);
    layout->addWidget(logYear, 4,1);
    layout->addWidget(viewLog, 4,2);
    layout->addWidget(tvaEditLabel,5,0);
    layout->addWidget(tvaEdit, 5,1 );
    layout->addWidget(tvaEditNewValue, 5,2);
    layout->addWidget(tvaPdfLabel, 6,0);
    layout->addWidget(tvaPdf, 6,1);
    layout->addWidget(tvaPdfButton, 6,2);
    layout->addWidget(cashTransferLabel, 10,0);
    layout->addWidget(cashTransfer, 10,1);
    layout->addWidget(validateButton, 20,0);
    layout->addWidget(cancelButton, 20,1);

    QObject::connect(validateButton, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(oldHistory, SIGNAL(clicked()), this, SLOT(clickOnGlobalHistory()));
    QObject::connect(oldIndividualHistory, SIGNAL(clicked()), this, SLOT(clickOnIndividualHistory()));
    QObject::connect(individualGraphButton, SIGNAL(clicked()), this, SLOT(clickOnIndividualGraph()));
    QObject::connect(viewLog, SIGNAL(clicked()), this, SLOT(clickOnViewLog()));
    QObject::connect(tvaPdfButton, SIGNAL(clicked()), this, SLOT(createTvaPdf()));
}

void Admin::launchAdmin(AdminTuple& tuple)
{
    //negativeAllowed->setChecked(tuple.isNegativeAllowed);
    db_categoryQueue catQueue;
    db_categoryTuple catTuple;
    db_TVAcategoryQueue tvaQueue;
    db_TVAcategoryTuple tvaTuple;
    oldCustCategoryName->clear();
    oldProdCategoryName->clear();
    tvaEdit->clear();
    cashTransfer->setText("0");

    catQueue = controller->getCustomerCategories();
    tvaQueue = controller->getTvaRates();
    int n = catQueue.size() - 1;
    catQueue.pop(); // on enlève la catégorie visiteur.
    for(int i =0 ; i < n ; i++)
    {
        catTuple = catQueue.front();
        catQueue.pop();
        oldCustCategoryName->addItem(QString::fromStdString(catTuple.getCategoryName()));
    }

    catQueue = controller->getProductsCategories();
    n = catQueue.size();
    for(int i =0 ; i < n ; i++)
    {
        catTuple = catQueue.front();
        catQueue.pop();
        oldProdCategoryName->addItem(QString::fromStdString(catTuple.getCategoryName()));
    }
    n = tvaQueue.size();
    for(int i =0 ; i < n ; i++)
    {
        tvaTuple = tvaQueue.front();
        tvaQueue.pop();
        tvaEdit->addItem(QString::fromStdString(tvaTuple.getInfo()));
    }

    this->show();
}

void Admin::validate()
{
    if(!isBalanceCorrect(cashTransfer->text()))
        return;
    if(!isFloat(tvaEditNewValue->text()))
        return;
    AdminTuple tuple;
    tuple.cashTransfered = cashTransfer->text().toFloat();
    tuple.newCustCategoryName = newCustCategoryName->text().toStdString();
    tuple.custCategoryID = oldCustCategoryName->currentIndex() + 1; // because visitor not displayed
    tuple.newProdCategoryName = newProdCategoryName->text().toStdString();
    tuple.prodCategoryID = oldProdCategoryName->currentIndex() + 1; // because id 0 is reserved for cash transactions
    tuple.tvaTuple.setRate(tvaEditNewValue->text().toFloat());
    tuple.tvaTuple.setId(tvaEdit->currentIndex()+1);
    controller->receiveAdminInfos(tuple);

    newCustCategoryName->clear();
    cashTransfer->clear();
    newProdCategoryName->clear();
    this->hide();
}

void Admin::clickOnGlobalHistory()
{
    int year;
    QString yearText = oldHistoryBegin->text();
    if (yearText == "")
        year = 0;
    else
    {
        if (!isUInteger(yearText))
            return;
        year = yearText.toInt();
    }
    controller->newClic_GlobalHistory_old(year);
}

void Admin::clickOnIndividualHistory()
{
    // id to define
    int id=0;
    controller->newClic_IndividualHistory_old(id);
}

void Admin::clickOnIndividualGraph()
{
    // id to define
    int id=0;
    controller->newClic_IndividualGraph(id);
}

void Admin::clickOnViewLog()
{
    QRegExp regex("^[0-9]{4}-[0-9]{2}$");
    if(!logYear->text().contains(regex))
    {
        error->showMessage("Syntaxe du mois incorrecte (AAAA-MM), par exemple 2014-03");
        return;
    }
    if(!QFile::exists(GLOBAL_PATH + "resources/system_files/" + logYear->text() + ".txt"))
    {
        error->showMessage("Aucun fichier de log pour ce mois.");
        return;
    }
    QString tmp;
    int month, year;
    tmp[0] = logYear->text()[5];
    tmp[1] = logYear->text()[6];
    month = tmp.toInt();
    for(int i =0 ; i < 4 ; i++)
        tmp[i] = logYear->text()[i];
    year = tmp.toInt();
    QString logText = controller->getLog(month, year);
    QWidget *log = new QWidget();
    log->setAttribute(Qt::WA_DeleteOnClose);
    log->setWindowFlags(Qt::WindowStaysOnTopHint);
    log->setGeometry(100,100, 700, 600);
    QTextEdit *text = new QTextEdit(log);
    text->setFixedSize(650, 550);
    text->setWordWrapMode(QTextOption::WordWrap);
    text->setText(logText);
    text->setReadOnly(true);
    log->show();
}

void Admin::createTvaPdf()
{
    if(isUInteger(tvaPdf->text()))
        controller->PrintTvaPdf(tvaPdf->text().toInt());
}
