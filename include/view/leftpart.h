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
#include "controller.h"

class Controller;
class LeftPart : public QFrame
{
public:
    Controller* controller;
    LeftPart(QWidget* parent = NULL);


    //receive informations from controller
    void setCategories(std::queue<QString> &categories);

    // update size of element to fit to frame (after resize of windows e.g)
    void updateSize();
    void setController(Controller* par);
    void getPointers(SearchResults** searchResults, History** history, CustomerPanel** customerPanel);

private:
    QPushButton* categoriesLabels;
    QFrame *categoriesList;
    QFont font;
    SearchResults* searchResults;
    History* history;
    CustomerPanel* customerPanel;


    
};

#endif // LEFTPART_H
