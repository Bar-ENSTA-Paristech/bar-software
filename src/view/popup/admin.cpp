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
    oldHistory->setToolTip("Voir le vieux historique");
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

    validateButton = new QPushButton("Valider", this);
    cancelButton = new QPushButton("Annuler", this);

    layout->addWidget(oldHistory, 0,0);
    layout->addWidget(oldIndividualCustomer, 1,0);
    layout->addWidget(oldIndividualHistory, 1,1);
    layout->addWidget(individualGraphButton, 1,2);
    layout->addWidget(oldCustCategoryNameLabel, 2, 0);
    layout->addWidget(oldCustCategoryName, 2 , 1);
    layout->addWidget(newCustCategoryName, 2,2);
    layout->addWidget(oldProdCategoryNameLabel, 3, 0);
    layout->addWidget(oldProdCategoryName, 3 , 1);
    layout->addWidget(newProdCategoryName, 3,2);
    layout->addWidget(cashTransferLabel, 10,0);
    layout->addWidget(cashTransfer, 10,1);
    layout->addWidget(validateButton, 20,0);
    layout->addWidget(cancelButton, 20,1);

    QObject::connect(validateButton, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(oldHistory, SIGNAL(clicked()), this, SLOT(clickOnGlobalHistory()));
    QObject::connect(oldIndividualHistory, SIGNAL(clicked()), this, SLOT(clickOnIndividualHistory()));
    QObject::connect(individualGraphButton, SIGNAL(clicked()), this, SLOT(clickOnIndividualGraph()));
}

void Admin::launchAdmin(AdminTuple& tuple)
{
    //negativeAllowed->setChecked(tuple.isNegativeAllowed);
    db_categoryQueue catQueue;
    db_categoryTuple catTuple;

    catQueue = controller->getCustomerCategories();
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

    this->show();
}

void Admin::validate()
{
    if(!isBalanceCorrect(cashTransfer->text()))
        return;
    AdminTuple tuple;
    //tuple.isNegativeAllowed = negativeAllowed->isChecked();
    tuple.cashTransfered = cashTransfer->text().toFloat();
    tuple.newCustCategoryName = newCustCategoryName->text().toStdString();
    tuple.custCategoryID = oldCustCategoryName->currentIndex() + 1; // because visitor not displayed
    tuple.newProdCategoryName = newProdCategoryName->text().toStdString();
    tuple.prodCategoryID = oldProdCategoryName->currentIndex();
    controller->receiveAdminInfos(tuple);
    this->hide();
}

void Admin::clickOnGlobalHistory()
{
    controller->newClic_GlobalHistory_old();
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
