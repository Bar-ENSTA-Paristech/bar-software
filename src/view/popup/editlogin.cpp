#include "editlogin.h"

EditLogin::EditLogin(QWidget *parent) :
    Popup(parent)
{
    VIEW.editLogin = this;
    this->setFixedSize(400, 700);
    titleFont.setPixelSize(16);
    titleFont.setBold(true);

    global = new QFrame(this);
    individual = new QFrame(this);
    root = new QFrame(this);
    layout = new QGridLayout(this);
    global_layout = new QGridLayout(global);
    individual_layout = new QGridLayout(individual);
    root_layout = new QGridLayout(root);

    global_title = new QLabel("Edition mot de passe global", global);
    global_oldLabel = new QLabel("Ancien mot de passe :", global);
    global_new1Label = new QLabel("Nouveau mot de passe :", global);
    global_new2Label = new QLabel("Retapez le nouveau mot de passe :", global);
    individual_title = new QLabel("Edition mot de passe individuel", individual);
    individual_loginLabel = new QLabel("Login concerné par ce changement :", individual);
    individual_rootLabel = new QLabel("Tapez le mot de passe root", individual);
    individual_new1Label = new QLabel("Nouveau mot de passe :", individual);
    individual_new2Label = new QLabel("Retapez le nouveau mot de passe :", individual);
    root_title = new QLabel("Edition mot de passe root", root);
    root_oldLabel = new QLabel("Ancien mot de passe :", root);
    root_new1Label = new QLabel("Nouveau mot de passe :", root);
    root_new2Label = new QLabel("Retapez le nouveau mot de passe :", root);
    global_title->setFont(titleFont);
    individual_title->setFont(titleFont);
    root_title->setFont(titleFont);    

    global_old = new QLineEdit(global);
    global_new1 = new QLineEdit(global);
    global_new2 = new QLineEdit(global);
    individual_login = new QLineEdit(individual);
    individual_root = new QLineEdit(individual);
    individual_new1 = new QLineEdit(individual);
    individual_new2 = new QLineEdit(individual);
    root_old = new QLineEdit(root);
    root_new1 = new QLineEdit(root);
    root_new2 = new QLineEdit(root);

    global_old->setEchoMode(QLineEdit::Password);
    global_new1->setEchoMode(QLineEdit::Password);
    global_new2->setEchoMode(QLineEdit::Password);
    individual_root->setEchoMode(QLineEdit::Password);
    individual_new1->setEchoMode(QLineEdit::Password);
    individual_new2->setEchoMode(QLineEdit::Password);
    root_old->setEchoMode(QLineEdit::Password);
    root_new1->setEchoMode(QLineEdit::Password);
    root_new2->setEchoMode(QLineEdit::Password);

    individual_validateButton = new QPushButton("Valider", global);
    individual_cancelButton = new QPushButton("Annuler", global);
    global_validateButton = new QPushButton("Valider", individual);
    global_cancelButton = new QPushButton("Annuler", individual);
    root_validateButton = new QPushButton("Valider", root);
    root_cancelButton = new QPushButton("Annuler", root);

    layout->addWidget(global,0,0);
    layout->addWidget(individual,1,0);
    layout->addWidget(root, 2,0);
    this->setLayout(layout);

    global_layout->addWidget(global_title, 0,0,1,2, Qt::AlignCenter);
    global_layout->addWidget(global_oldLabel, 1, 0);
    global_layout->addWidget(global_old, 1, 1);
    global_layout->addWidget(global_new1Label, 2, 0);
    global_layout->addWidget(global_new1, 2, 1);
    global_layout->addWidget(global_new2Label, 3, 0);
    global_layout->addWidget(global_new2, 3, 1);
    global_layout->addWidget(global_validateButton, 4, 0);
    global_layout->addWidget(global_cancelButton, 4, 1);
    global->setLayout(global_layout);

    individual_layout->addWidget(individual_title, 0,0,1,2, Qt::AlignCenter);
    individual_layout->addWidget(individual_loginLabel, 1, 0);
    individual_layout->addWidget(individual_login, 1, 1);
    individual_layout->addWidget(individual_rootLabel, 2, 0);
    individual_layout->addWidget(individual_root, 2, 1);
    individual_layout->addWidget(individual_new1Label, 3, 0);
    individual_layout->addWidget(individual_new1, 3, 1);
    individual_layout->addWidget(individual_new2Label, 4, 0);
    individual_layout->addWidget(individual_new2, 4, 1);
    individual_layout->addWidget(individual_validateButton, 5, 0);
    individual_layout->addWidget(individual_cancelButton, 5, 1);
    individual->setLayout(individual_layout);

    root_layout->addWidget(root_title, 0,0,1,2, Qt::AlignCenter);
    root_layout->addWidget(root_oldLabel, 1, 0);
    root_layout->addWidget(root_old, 1, 1);
    root_layout->addWidget(root_new1Label, 2, 0);
    root_layout->addWidget(root_new1, 2, 1);
    root_layout->addWidget(root_new2Label, 3, 0);
    root_layout->addWidget(root_new2, 3, 1);
    root_layout->addWidget(root_validateButton, 4, 0);
    root_layout->addWidget(root_cancelButton, 4, 1);
    root->setLayout(root_layout);

    QObject::connect(global_cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(individual_cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(root_cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(global_validateButton, SIGNAL(clicked()), this, SLOT(global_validate()));
    QObject::connect(individual_validateButton, SIGNAL(clicked()), this, SLOT(individual_validate()));
    QObject::connect(root_validateButton, SIGNAL(clicked()), this, SLOT(root_validate()));

}

void EditLogin::launchEditLogin()
{
    this->show();
}

void EditLogin::setController(Controller* _controller)
{
    controller = _controller;
}

void EditLogin::global_validate()
{
    if(controller->newGlobalPassword(global_old->text(), global_new1->text(), global_new2->text()))
    {
        cancel();
    }
    else
    {
        error->showMessage("Erreur ! Vérifiez que tout soit valide");
    }
}

void EditLogin::individual_validate()
{
    if(controller->newIndividualPassword(individual_login->text(), individual_root->text(), individual_new1->text(), individual_new2->text()))
    {
        cancel();
    }
    else
    {
        error->showMessage("Erreur ! Vérifiez que tout soit valide");
    }
}

void EditLogin::root_validate()
{
    if(controller->newRootPassword(root_old->text(), root_new1->text(), root_new2->text()))
    {
        cancel();
    }
    else
    {
        error->showMessage("Erreur ! Vérifiez que tout soit valide");
    }
}

void EditLogin::cancel()
{
    reset();
    hide();
}

void EditLogin::reset()
{
    global_old->clear();
    global_new1->clear();
    global_new2->clear();
    individual_login->clear();
    individual_root->clear();
    individual_new1->clear();
    individual_new2->clear();
    root_old->clear();
    root_new1->clear();
    root_new2->clear();
}
