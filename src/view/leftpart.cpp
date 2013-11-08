#include "leftpart.h"

LeftPart::LeftPart(QWidget* parent)
{
    setParent(parent);
    // for CSS
    this->setObjectName("leftPart");

    searchResults = new SearchResults(this);
    history = new History(this);
    customerPanel = new CustomerPanel(this);
    // categoriesList will be the widget which will show categories on the left (TOUS, BAR, 2014, 2015, etc)
    categoriesList = new QFrame(this);
    categoriesList->setObjectName("categoriesList");

    layout = new QGridLayout(this);
    layout->addWidget(searchResults, 0, 0, 1, 10);
    layout->addWidget(categoriesList, 1, 0);
    layout->addWidget(customerPanel, 1, 1, 1, 9);
    layout->addWidget(history, 2, 0, 1, 10);
    layout->setContentsMargins(0, 0, 0, 0);

    //##### TEST ####
    std::queue<QString> categories;
    categories.push(QString("Tous"));
    categories.push(QString("RAB"));
    setCategories(categories);
    // ##### FIN TEST #####
    //QObject::connect(&categoriesLabels[1], SIGNAL(pressed()), this, SLOT(clickOnCategorie()));
    QObject::connect(&updateCategorieTimer, SIGNAL(timeout()), this, SLOT(unsetCategorieUpdate()));

    this->setLayout(layout);
}

LeftPart::~LeftPart()
{
    /*delete[] categoriesLabels;
    delete layout;
    delete categoriesList;
    delete searchResults;
    delete history;
    delete customerPanel;*/
}

// Normally launch once at start of software to set categories on the left (no delete planned if not ...)
void LeftPart::setCategories(std::queue<QString> &categories)
{
    QVBoxLayout *layout = new QVBoxLayout(categoriesList);
    font.setStyleHint(QFont::SansSerif);
    font.setPixelSize(18);
    font.setBold(true);
    numberOfCategories = categories.size();
    categoriesLabels = new QPushButton[numberOfCategories];
    for(int i=0 ; i<numberOfCategories ; i++)
    {

        categoriesLabels[i].setParent(categoriesList);
        categoriesLabels[i].setText(categories.front());
        categoriesLabels[i].setFlat(true);
        categoriesLabels[i].setFont(font);
        categoriesLabels[i].setFixedHeight(30);
        categoriesLabels[i].setFixedWidth(100);
        //categoriesLabels[i].setId(i);
        layout->addWidget(&categoriesLabels[i]);
        categories.pop();
        QObject::connect(&categoriesLabels[i], SIGNAL(categorieClicked(int)), this, SLOT(clickOnCategorie(int)));
    }
    categoriesLabels[0].setObjectName("activeCategorie");
    // to get them at top and without space between them
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    categoriesList->setLayout(layout);
}

void LeftPart::clickOnCategorie(int id)
{
    categoriesLabels[0].setUpdatesEnabled(true);
    //categoriesLabels[0].setObjectName("inactiveCategorie");
    //categoriesLabels[1].setObjectName("activeCategorie");
    categoriesLabels[0].setStyleSheet("background : url("+GLOBAL_PATH+"resources/pictures/test.png)");
    //categoriesList[1].setStyleSheet("background-image: url(../bar-software/resources/pictures/test.png)");
    qDebug() << "pute" << id;
    updateCategorieTimer.start(500);
    //this->update();
    //categoriesLabels[0].setUpdatesEnabled(false);

}

void LeftPart::unsetCategorieUpdate()
{
    for(int i=0 ; i < numberOfCategories ; i++)
    {
        categoriesLabels[i].setUpdatesEnabled(false);
    }
}

void LeftPart::updateSize()
{
    searchResults->updateSize();
    history->updateSize();
}

void LeftPart::getPointers(SearchResults** par1, History** par2, CustomerPanel** par3)
{
    *par1 = searchResults;
    *par2 = history;
    *par3 = customerPanel;
}

void LeftPart::setController(Controller* par)
{
    controller = par;
    searchResults->controller = par;
    history->controller = par;
    customerPanel->controller = par;
}
