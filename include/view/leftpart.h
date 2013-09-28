#ifndef LEFTPART_H
#define LEFTPART_H

#include <QFrame>
#include <QPushButton>
#include <QGridLayout>
#include <QFont>
#include <queue>
#include "searchresults.h"
#include "history.h"
#include "customerpanel.h"

class LeftPart : public QFrame
{
public:
    LeftPart(QWidget* parent = NULL);

    //receive informations from controller
    void setCategories(std::queue<QString> &categories);

    // update size of element to fit to frame (after resize of windows e.g)
    void updateSize();

private:
    QPushButton* categoriesLabels;
    QFrame *categoriesList;
    QFont font;
    SearchResults* searchResults;
    History* history;
    CustomerPanel* customerPanel;

    
};

#endif // LEFTPART_H
