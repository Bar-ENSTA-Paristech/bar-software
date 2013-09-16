#include "leftpart.h"

LeftPart::LeftPart(QWidget* parent)
{
    setParent(parent);
    this->setObjectName("leftPart");

    SearchResults* searchResults = new SearchResults(this);
    History* history = new History(this);
    CustomerPanel* customerPanel = new CustomerPanel(this);
    QFrame *categories = new QFrame(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(searchResults, 0, 0, 1, 10);
    layout->addWidget(categories, 1, 0);
    layout->addWidget(customerPanel, 1, 1);
    layout->addWidget(history, 2, 0, 1, 10);

    this->setLayout(layout);
}
