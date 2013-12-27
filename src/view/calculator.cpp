#include "calculator.h"

Calculator::Calculator(QWidget *parent) :
    QWidget(parent)
{
    VIEW.calculator = this;
    this->setFixedSize(250, 150);
    QGridLayout* layout = new QGridLayout(this);
    QLabel* label = new QLabel(this);
    sum = new QLineEdit(this);
    QPushButton* validate = new QPushButton(this);
    QPushButton* cancel = new QPushButton(this);

    layout->addWidget(label, 0,0, 1, 2, Qt::AlignCenter);
    layout->addWidget(sum, 1,0, 1, 2, Qt::AlignCenter);
    layout->addWidget(validate, 2,0);
    layout->addWidget(cancel, 2,1);
    this->setLayout(layout);

    label->setText("Tapez une valeur. Ex : 9.5 ajoutera 9.5€ au compte, -14 retirera 14€");
    label->setWordWrap(true);

    validate->setText("Valider");
    cancel->setText("Annuler");
    QObject::connect(validate, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancel()));


}

void Calculator::validate()
{
    QString value = sum->text();
    sum->clear();
    // use of regex to check if it is a correct number
    const QRegExp regex ("^-?[0-9]+(.[0-9]?)?$");
    if(value.contains(regex))
    {
        float floatValue = value.toFloat();
        // ###### APPEL AU CONTROLLEUR POUR TRANSACTION #####

        this->hide();
    }
    else
    {
        QErrorMessage* error = new QErrorMessage(this);
        error->showMessage("Cette quantité d'argent n'est pas valide ! La virgule doit être représentée par un point et la partie décimale ne dépasse pas le dixième. Si la somme est négative, coller la virgule à la partie entière. Ne pas mettre le symbole €. Exemple : -15.5");
    }

}

void Calculator::cancel()
{
    sum->clear();
    this->hide();
}

void Calculator::setController(Controller* controller_par)
{
    controller = controller_par;
}
