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

extern QString GLOBAL_PATH;

//class CategorieButton;
class Controller;

class CategorieButton : public QPushButton
{
    Q_OBJECT
private:
    int ID;

public:
    CategorieButton(QWidget* parent = NULL) : QPushButton(parent)
    {}

    void setId(int _ID)
    {
        ID = _ID;
        QObject::connect(this, SIGNAL(clicked()), this, SLOT(clickSlot()));
    }

public slots:
    void clickSlot(){emit categorieClicked(ID);}

signals:
    void categorieClicked(int);

};

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
    QPushButton* categoriesLabels;
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
