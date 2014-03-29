#ifndef EDITLOGIN_H
#define EDITLOGIN_H

#include <QFrame>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QFont>
#include "popup.h"
#include "controller.h"
#include "structures.h"

class EditLogin : public Popup
{
    Q_OBJECT
public:
    explicit EditLogin(QWidget *parent = 0);
    void setController(Controller* _controller);
    
signals:
    
private:
    Controller* controller;

    QFrame* global;
    QFrame* individual;
    QFrame* root;
    QGridLayout* layout;
    QGridLayout* global_layout;
    QGridLayout* individual_layout;
    QGridLayout* root_layout;

    QLabel* global_title;
    QLabel* global_oldLabel;
    QLabel* global_new1Label;
    QLabel* global_new2Label;
    QLabel* individual_title;
    QLabel* individual_loginLabel;
    QLabel* individual_rootLabel;
    QLabel* individual_new1Label;
    QLabel* individual_new2Label;
    QLabel* root_title;
    QLabel* root_oldLabel;
    QLabel* root_new1Label;
    QLabel* root_new2Label;

    QLineEdit* global_old;
    QLineEdit* global_new1;
    QLineEdit* global_new2;
    QLineEdit* individual_login;
    QLineEdit* individual_root;
    QLineEdit* individual_new1;
    QLineEdit* individual_new2;
    QLineEdit* root_old;
    QLineEdit* root_new1;
    QLineEdit* root_new2;

    QPushButton* individual_validateButton;
    QPushButton* individual_cancelButton;
    QPushButton* global_validateButton;
    QPushButton* global_cancelButton;
    QPushButton* root_validateButton;
    QPushButton* root_cancelButton;

    QFont titleFont;



public slots:
    void launchEditLogin();
    void global_validate();
    void individual_validate();
    void root_validate();
    void cancel();
    void reset();
    void individual_loginChanged(QString); // To avoid any change of login after the boss entered the root password
    
};

#endif // EDITLOGIN_H
