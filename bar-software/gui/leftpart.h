#ifndef LEFTPART_H
#define LEFTPART_H

#include <QFrame>
#include <QGridLayout>
#include "searchresults.h"
#include "history.h"
#include "customerpanel.h"

class LeftPart : public QFrame
{
public:
    LeftPart(QWidget* parent = NULL);
    void setCategories();
    
};

#endif // LEFTPART_H
