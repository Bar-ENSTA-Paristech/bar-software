#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include "structures.h"
#include "popup.h"
#include "controller.h"

class AddProduct : public Popup
{
    Q_OBJECT
public:
    explicit AddProduct(QWidget *parent = 0);
    void launchAddProduct();
    void setController(Controller* controller);
    
signals:
    
private:
    Controller* controller;

    QLabel* nameLabel;
    QLabel* volumeLabel;
    QLabel* priceLabel;
    QLabel* stockLabel;
    QLabel* categorieLabel;
    QLabel* tvaLabel;
    QLineEdit* name;
    QLineEdit* volume;
    QLineEdit* price;
    QLineEdit* stock;
    QComboBox* categorie;
    QComboBox* tva;
    QGridLayout* layout;
    QPushButton* validateButton;
    QPushButton* cancelButton;

public slots:
    void validate();
    void cancel();
    void reset();
    
};

#endif // ADDPRODUCT_H
