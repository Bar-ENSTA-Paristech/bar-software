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
    void setCategories(std::queue<QString> &categories);

private:
    QPushButton* categoriesLabels;
    QFrame *categoriesList;
    QFont font;
    
};

#endif // LEFTPART_H
