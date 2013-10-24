#include "customerpanel.h"

CustomerPanel::CustomerPanel(QWidget *parent) :
    QFrame(parent)
{
    setObjectName("customerPanel");
    photoFrame = new QFrame(this);
    infosFrame = new QFrame(this);
    optionsFrame = new QFrame(this);
    layout = new QGridLayout(this);
    layout->addWidget(photoFrame, 0, 0, 2, 1);
    layout->addWidget(infosFrame, 0, 1);
    layout->addWidget(optionsFrame, 1, 1);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    //###### PHOTO ######
    photo = new QLabel(photoFrame);
    photoLayout = new QGridLayout(photoFrame);
    photoLayout->addWidget(photo, 0, 0);
    photoLayout->setContentsMargins(0, 0, 0, 0);
    photoFrame->setLayout(photoLayout);

    //###### INFOS ########
    infosLayout = new QGridLayout(infosFrame);
    nameLabel = new QLabel("Nom :", infosFrame);
    firstNameLabel = new QLabel("Prénom :", infosFrame);
    categorieLabel = new QLabel("Catégorie :", infosFrame);
    balanceLabel = new QLabel("Solde :", infosFrame);
    name = new QLabel(infosFrame);
    firstName = new QLabel(infosFrame);
    categorie = new QLabel(infosFrame);
    balance = new QLabel(infosFrame);
    QFont bold, normal;
    bold.setBold(true);
    normal.setPixelSize(13);
    bold.setPixelSize(13);
    name->setFont(bold);
    firstName->setFont(bold);
    categorie->setFont(bold);
    balance->setFont(bold);
    nameLabel->setFont(normal);
    firstNameLabel->setFont(normal);
    categorieLabel->setFont(normal);
    balanceLabel->setFont(normal);

    infosLayout->addWidget(nameLabel, 0, 0);
    infosLayout->addWidget(name, 0, 1);
    infosLayout->addWidget(firstNameLabel, 1, 0);
    infosLayout->addWidget(firstName, 1, 1);
    infosLayout->addWidget(categorieLabel, 2, 0);
    infosLayout->addWidget(categorie, 2, 1);
    infosLayout->addWidget(balanceLabel, 3, 0);
    infosLayout->addWidget(balance, 3, 1);
    infosLayout->setContentsMargins(0, 30, 0, 0);
    infosFrame->setLayout(infosLayout);

    // ###### TEST #########
    std::tuple<QString, QString, QString, QString, float> toto("Rousseau", "Woody", "wrousseau", "2015", -3.5);
    setCustomer(toto);
}

CustomerPanel::~CustomerPanel()
{
    /*delete photo;
    delete name;
    delete firstName;
    delete categorie;
    delete balance;
    delete photoFrame;
    delete infosFrame;
    delete optionsFrame;
    delete layout;
    delete photoLayout;
    delete infosLayout;
    delete nameLabel;
    delete firstNameLabel;
    delete categorieLabel;
    delete balanceLabel;*/
}

void CustomerPanel::setCustomer(std::tuple< QString, QString, QString, QString, float> & tuple)
{
    // std::tuple<QString name, QString firstName, QString login, QString categorie, float balance>
    name->setText(std::get<0>(tuple));
    firstName->setText(std::get<1>(tuple));
    categorie->setText(std::get<3>(tuple));
    balance->setText(QString::number(std::get<4>(tuple)) + " €");
    if(std::get<4>(tuple) < 0)
        balance->setStyleSheet("color: #FF0000;");
    else
        balance->setStyleSheet("color: black;");
    if(QFile::exists(GLOBAL_PATH + "resources/photos/"+ std::get<2>(tuple).toLower() + ".jpg"))
        photo->setPixmap(GLOBAL_PATH + "resources/photos/"+ std::get<2>(tuple).toLower() + ".jpg");
    else
        photo->setPixmap(GLOBAL_PATH + "resources/photos/no_photo.jpg");

}

