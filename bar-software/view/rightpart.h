#ifndef RIGHTPART_H
#define RIGHTPART_H

#include <QFrame>
#include <QGridLayout>
#include "cartdisplay.h"
#include "productschoices.h"

class RightPart : public QFrame
{
public:
    RightPart(QWidget* parent = NULL);
    void updateSize();
};

#endif // RIGHTPART_H
