#include "controller.h"
#include "login.h"

Login::Login(QWidget *parent) :
    Popup(parent)
{
    VIEW.login = this;
    //this->setWindowFlags(Qt::Dialog);
    this->setFixedSize(250, 150);
    QGridLayout* layout = new QGridLayout(this);
    label = new QLabel(this);
    login = new QLineEdit(this);
    passwd = new QLineEdit(this);
    passwd->setEchoMode(QLineEdit::Password);
    loginLabel = new QLabel(this);
    passwdLabel = new QLabel(this);
    QPushButton* validate = new QPushButton(this);
    QPushButton* cancel = new QPushButton(this);

    layout->addWidget(label, 0,0, 1, 2, Qt::AlignCenter);
    layout->addWidget(loginLabel, 1,0);
    layout->addWidget(login, 1,1);
    layout->addWidget(passwdLabel, 2,0);
    layout->addWidget(passwd, 2,1);
    layout->addWidget(validate, 3,0);
    layout->addWidget(cancel, 3,1);
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,1);
    this->setLayout(layout);

    label->setText("Tapez une valeur. Ex : 9.5 ajoutera 9.5€ au compte, -14 retirera 14€");
    loginLabel->setText("Login");
    passwdLabel->setText("Password");

    validate->setText("Valider");
    cancel->setText("Annuler");
    QObject::connect(validate, SIGNAL(clicked()), this, SLOT(validate()));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancel()));


}

void Login::validate()
{
    //if(controller->view_isLoginCorrect())
    if (controller->view_isLoginCorrect(login->text(), passwd->text(), loginType))
    {
        login->clear();
        passwd->clear();
        this->hide();
    }
    else
    {
        login->clear();
        passwd->clear();
    }

}

void Login::cancel()
{
    login->clear();
    passwd->clear();
    this->hide();
}

void Login::setController(Controller* controller_par)
{
    controller = controller_par;
}

void Login::checkIndividual()
{
    label->setText("Identification Personnelle");
    loginType = INDIVIDUAL;
    loginLabel->show();
    login->show();
    this->show();
}

void Login::checkGlobal()
{
    label->setText("Identification Générale");
    loginType = GLOBAL;
    loginLabel->hide();
    login->hide();
    this->show();
}

void Login::checkRoot()
{
    label->setText("Identification Administrateur");
    loginType = ROOT;
    loginLabel->hide();
    login->hide();
    this->show();
}
