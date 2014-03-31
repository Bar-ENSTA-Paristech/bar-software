#include "popup.h"

Popup::Popup(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    Enter = new QShortcut(QKeySequence("Enter"), this);
    Return = new QShortcut(QKeySequence("Return"), this);
    Escape = new QShortcut(QKeySequence("Escape"), this);
    QObject::connect(Enter, SIGNAL(activated()), this, SLOT(validate()));
    QObject::connect(Return, SIGNAL(activated()), this, SLOT(validate()));
    QObject::connect(Escape, SIGNAL(activated()), this, SLOT(cancel()));

    error = new QErrorMessage(this);

    this->hide();

}

bool Popup::isBalanceCorrect(QString value)
{
    const QRegExp regex ("^-?[0-9]+(\.[0-9]?)?$");
    if(value.contains(regex))
    {
        return true;
    }
    else
    {
        error->showMessage("Cette quantité d'argent n'est pas valide ! La virgule doit être représentée par un point et la partie décimale ne dépasse pas le dixième. Si la somme est négative, coller la virgule à la partie entière. Ne pas mettre le symbole €. Exemple : -15.5");
        return false;
    }
}

bool Popup::isUInteger(QString value)
{
    QRegExp regex("^[0-9]+$");
    if(!value.contains(regex))
    {
        error->showMessage("Ce nombre ("+ value + ") n'est pas valide. Ce doit être un entier positif.");
        return false;
    }
    return true;
}

bool Popup::isInteger(QString value)
{
    QRegExp regex("^-?[0-9]+$");
    if(!value.contains(regex))
    {
        error->showMessage("Ce nombre ("+ value + ") n'est pas valide. Ce doit être un entier relatif.");
        return false;
    }
    return true;
}

bool Popup::isFloat(QString value)
{
    const QRegExp regex ("^-?[0-9]*(\.[0-9]*)?$");
    if(value.contains(regex))
    {
        return true;
    }
    else
    {
        error->showMessage("Ce nombre à virgule n'est pas valide ! La virgule doit être représentée par un point. Si la somme est négative, coller la virgule à la partie entière. Ne pas mettre le symbole €. Exemple : -15.53");
        return false;
    }
}

void Popup::setController(Controller* _controller)
{
    controller = _controller;
}
