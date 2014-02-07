#ifndef LEFTPART_H
#define LEFTPART_H

#include <QFrame>
#include <QPushButton>
#include <QGridLayout>
#include <QFont>
#include <queue>
#include <QTimer>
#include "searchresults.h"
#include "history.h"
#include "customerpanel.h"
#include "controller.h"
#include "categoriebutton.h"
#include "structures.h"
extern ViewObjects VIEW;


class Controller;

class LeftPart : public QFrame
{
    Q_OBJECT
public:
    Controller* controller;
    LeftPart(QWidget* parent = NULL);
    ~LeftPart();


    //receive informations from controller
    void setCategories(std::queue<QString> &categories);

    // update size of element to fit to frame (after resize of windows e.g)
    void updateSize();
    void setController(Controller* par);
    void getPointers(SearchResults** searchResults, History** history, CustomerPanel** customerPanel);

private:
    CategorieButton* categoriesLabels;
    QGridLayout *layout;
    QFrame *categoriesList;
    QFont font;
    SearchResults* searchResults;
    History* history;
    CustomerPanel* customerPanel;
    QTimer updateCategorieTimer;
    int numberOfCategories;

private slots:
    void clickOnCategorie(int id);
    void unsetCategorieUpdate();
    
};




#endif // LEFTPART_H
