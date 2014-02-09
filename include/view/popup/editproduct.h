#ifndef EDITPRODUCT_H
#define EDITPRODUCT_H

#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include "structures.h"
#include "popup.h"
#include "controller.h"

class EditProduct : public Popup
{
    Q_OBJECT
public:
    explicit EditProduct(QWidget *parent = 0);
    void launchEditProduct();
    void setController(Controller* controller);
    
signals:
    
private:
    Controller* controller;

    QLabel* newNameLabel;
    QLabel* volumeLabel;
    QLabel* priceLabel;
    QLabel* categorieLabel;
    QLabel* stockLabel;
    QLineEdit* newName;
    QLineEdit* volume;
    QLineEdit* price;
    QComboBox* name;
    QLineEdit* stock;
    QComboBox* categorie;
    QGridLayout* layout;
    QPushButton* validateButton;
    QPushButton* cancelButton;
    QCheckBox* deleteProduct;

    unsigned ID;
    view_productTuple tmpProduct;
    std::vector<view_productTuple> tmpProductVector;

public slots:
    void validate();
    void cancel();
    void reset();
    void categorieSelected(int index);
    void productSelected(int index);

    
};

#endif // EDITPRODUCT_H
