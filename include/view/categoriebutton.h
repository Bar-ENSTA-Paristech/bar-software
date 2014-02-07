#ifndef CATEGORIEBUTTON_H
#define CATEGORIEBUTTON_H

#include <QPushButton>

extern QString GLOBAL_PATH;

class CategorieButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CategorieButton(QWidget *parent = 0);
    void setId(int id);
    
signals:
    void categorieClicked(int);

public slots:
    void clickSlot();

private:
    int ID;
    
};

#endif // CATEGORIEBUTTON_H
