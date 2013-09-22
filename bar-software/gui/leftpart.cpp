#include "leftpart.h"

LeftPart::LeftPart(QWidget* parent)
{
    setParent(parent);
    this->setObjectName("leftPart");

    SearchResults* searchResults = new SearchResults(this);
    History* history = new History(this);
    CustomerPanel* customerPanel = new CustomerPanel(this);
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

    this->setLayout(layout);
}


void LeftPart::setCategories(std::queue<QString> &categories)
{
    QVBoxLayout *layout = new QVBoxLayout(categoriesList);
    font.setStyleHint(QFont::SansSerif);
    font.setPixelSize(18);
    font.setBold(true);
    unsigned n = categories.size();qDebug() << "test" << categories.front();
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
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    categoriesList->setLayout(layout);
}
