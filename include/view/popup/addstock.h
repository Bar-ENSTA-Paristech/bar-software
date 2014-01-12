#ifndef ADDSTOCK_H
#define ADDSTOCK_H

#include <QScrollArea>
#include "popup.h"
#include "controller.h"

typedef struct{
    QLabel consoTypeLabel;
    QComboBox consoType;
    QLabel productLabel;
    QComboBox product;
    QLabel quantityLabel;
    QLineEdit quantity;
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
    QGridLayout* layout;
    QGridLayout* frameLayout;
    QScrollArea* scrollArea;

    std::vector<ConsoLine*> lines;
    unsigned numberOfLines;
    
public slots:
    void addLine();
};

#endif // ADDSTOCK_H
