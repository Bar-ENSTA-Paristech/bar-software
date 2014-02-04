#ifndef ADDSTOCK_H
#define ADDSTOCK_H

#include <QScrollArea>
#include <QRegExp>
#include "popup.h"
#include "controller.h"
#include "structures.h"

typedef struct{
    QLabel consoTypeLabel;
    QComboBox consoType;
    QLabel productLabel;
    QComboBox product;
    QLabel quantityLabel;
    QLineEdit quantity;
    unsigned* productID;
}ConsoLine;

class AddStock : public Popup
{
    Q_OBJECT
public:
    explicit AddStock(QWidget *parent = 0);
    void setController(Controller* _controller);
    void launchAddStock();
    
signals:

private:
    Controller* controller;
    QFrame* listFrame;
    QPushButton* addLineButton;
    QPushButton* validateButton;
    QPushButton* cancelButton;
    QPushButton* resetButton;
    QGridLayout* layout;
    QGridLayout* frameLayout;
    QScrollArea* scrollArea;

    std::vector<ConsoLine*> lines;
    unsigned numberOfLines;
    
public slots:
    void addLine();
    void consoTypeChanged(int index);
    void validate();
    void cancel();
    void reset();
};

#endif // ADDSTOCK_H
