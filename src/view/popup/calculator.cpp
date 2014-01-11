#include "calculator.h"

Calculator::Calculator(QWidget *parent) :
    Popup(parent)
{
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
        QObject::connect(buttons[i], SIGNAL(clicked()), this, SLOT(buttonPushed()));
        if(i < 10)
            buttons[i]->setText(QString::number((i+1)%10));
        else if(i == 10)
            buttons[i]->setText(".");
        else if(i == 11)
            buttons[i]->setText("-");
    }    
    buttonsLayout->addWidget(buttons[12], 3, 3, 1, 1, Qt::AlignCenter);// AC
    QObject::connect(buttons[12], SIGNAL(clicked()), this, SLOT(buttonPushed()));
    buttons[12]->setText("AC");
    buttonsFrame->setLayout(buttonsLayout);
}

void Calculator::launchCalculator()
{
    // If negative balance not allowed, we disable "-" button
    if(!controller->isNegativeAllowed())
        buttons[11]->setEnabled(false);
    else
        buttons[11]->setEnabled(true);
    this->show();
}

void Calculator::validate()
{
    QString value = sum->text();
    sum->clear();
    if(isBalanceCorrect(value))
    {
        float floatValue = value.toFloat();
        // ###### APPEL AU CONTROLLEUR POUR TRANSACTION #####
        controller->receiveCalculatorEntry(floatValue);
        this->hide();
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

void Calculator::buttonPushed()
{
    QPushButton* sender = (QPushButton*) QObject::sender();
    bool isNumber;
    QString valueToInsert = sender->text();
    valueToInsert.toInt(&isNumber);
    if(isNumber)
    {
        sum->setText(sum->text() +  valueToInsert);
    }
    else if( valueToInsert == "AC")
        sum->clear();
    else if( valueToInsert == ".")
        sum->setText(sum->text() + ".");
    else if( valueToInsert == "-")
    {
        // if the number in line edit is negative, we just remove the sign -
        if(sum->text()[0] == '-')
            sum->setText(sum->text().remove(0,1));
        else // Else we add it
            sum->setText( "-" + sum->text());
    }
}
