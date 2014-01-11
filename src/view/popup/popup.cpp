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

    this->hide();

}

bool Popup::isBalanceCorrect(QString value)
{
    const QRegExp regex ("^-?[0-9]+(.[0-9]?)?$");
    if(value.contains(regex))
    {
        return true;
    }
    else
    {
        error = new QErrorMessage(this);
        error->showMessage("Cette quantité d'argent n'est pas valide ! La virgule doit être représentée par un point et la partie décimale ne dépasse pas le dixième. Si la somme est négative, coller la virgule à la partie entière. Ne pas mettre le symbole €. Exemple : -15.5");
        return false;
    }
}
