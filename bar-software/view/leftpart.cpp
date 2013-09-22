#include "leftpart.h"

LeftPart::LeftPart(QWidget* parent)
{
    setParent(parent);
    // for CSS
    this->setObjectName("leftPart");

    searchResults = new SearchResults(this);
    history = new History(this);
    CustomerPanel* customerPanel = new CustomerPanel(this);
    // categoriesList will be the widget which will show categories on the left (TOUS, BAR, 2014, 2015, etc)
    categoriesList = new QFrame(this);
    categoriesList->setObjectName("categoriesList");

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(searchResults, 0, 0, 1, 10);
    layout->addWidget(categoriesList, 1, 0);
    layout->addWidget(customerPanel, 1, 1);
    layout->addWidget(history, 2, 0, 1, 10);
    layout->setContentsMargins(0, 0, 0, 0);

    //##### TEST ####
    std::queue<QString> categories;
    categories.push(QString("Tous"));
    categories.push(QString("RAB"));
    setCategories(categories);
    // ##### FIN TEST #####

    this->setLayout(layout);
}

// Normally launch once at start of software to set categories on the left (no delete planned if not ...)
void LeftPart::setCategories(std::queue<QString> &categories)
{
    QVBoxLayout *layout = new QVBoxLayout(categoriesList);
    font.setStyleHint(QFont::SansSerif);
    font.setPixelSize(18);
    font.setBold(true);
    unsigned n = categories.size();
    categoriesLabels = new QPushButton[n];
    for(unsigned i=0 ; i<n ; i++)
    {

        categoriesLabels[i].setParent(categoriesList);
        categoriesLabels[i].setText(categories.front());
        categoriesLabels[i].setFlat(true);
        categoriesLabels[i].setFont(font);
        categoriesLabels[i].setFixedHeight(30);
        categoriesLabels[i].setFixedWidth(100);
        layout->addWidget(&categoriesLabels[i]);
        categories.pop();
    }
    // to get them at top and without space between them
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    categoriesList->setLayout(layout);
}

void LeftPart::updateSize()
{
    searchResults->updateSize();
    history->updateSize();
}
