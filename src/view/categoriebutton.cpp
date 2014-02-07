#include "categoriebutton.h"

CategorieButton::CategorieButton(QWidget *parent) :
    QPushButton(parent)
{
}

void CategorieButton::setId(int id)
{
    ID = id;
    QObject::connect(this, SIGNAL(pressed()), this, SLOT(clickSlot()));
}

void CategorieButton::clickSlot()
{
    emit categorieClicked(ID);
}
