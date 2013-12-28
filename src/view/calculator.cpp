#include "calculator.h"

Calculator::Calculator(QWidget *parent) :
    QWidget(parent)
{qDebug() << this;
    VIEW.calculator = this;
    this->setFixedSize(250, 300);
    QGridLayout* layout = new QGridLayout(this);
    QLabel* label = new QLabel(this);
    sum = new QLineEdit(this);
    QPushButton* validate = new QPushButton(this);
    QPushButton* cancel = new QPushButton(this);
    buttonsFrame = new QFrame(this);
    buttonsLayout = new QGridLayout(buttonsFrame);
    buttons = new QPushButton*[CALCULATOR_BUTTONS];
    for(int i=0 ; i < CALCULATOR_BUTTONS ; i++)
        buttons[i] = new QPushButton(buttonsFrame);

    layout->addWidget(label, 0,0, 1, 2, Qt::AlignCenter);
    layout->addWidget(buttonsFrame, 1,0,1,2, Qt::AlignCenter);
    layout->addWidget(sum, 2,0, 1, 2, Qt::AlignCenter);
    layout->addWidget(validate, 3,0);
    layout->addWidget(cancel, 3,1);
    this->setLayout(layout);

    label->setText("Tapez une valeur. Ex : 9.5 ajoutera 9.5€ au compte, -14 retirera 14€");
    label->setWordWrap(true);

    validate->setText("Valider");
    cancel->setText("Annuler");
    QObject::connect(validate, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancel()));

    // ####### BUTTONS OF CALCULTOR #######
    for( int i=0 ; i < 12 ; i++)
    {
        buttonsLayout->addWidget(buttons[i], i/3, i%3, 1, 1, Qt::AlignCenter);
        if(i < 10)
            buttons[i]->setText(QString::number((i+1)%10));
        else if(i == 10)
            buttons[i]->setText(".");
        else if(i == 11)
            buttons[i]->setText("-");
    }
    buttonsLayout->addWidget(buttons[12], 3, 3, 1, 1, Qt::AlignCenter);// AC
    /*buttonsLayout->addWidget(buttons[10], 1, 3, 1, 1, Qt::AlignCenter); // .
    buttonsLayout->addWidget(buttons[11], 2, 3, 1, 1, Qt::AlignCenter); // 0
    buttons[9]->setText("AC");
    buttons[10]->setText(".");*/
    buttons[12]->setText("AC");
    buttonsFrame->setLayout(buttonsLayout);




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
