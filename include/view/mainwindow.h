#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QFrame>
#include <QLineEdit>
#include <QLabel>
#include <QTimer>
#include <QShortcut>
#include <queue>
#include "leftpart.h"
#include "rightpart.h"
#include "controller.h"

extern QString GLOBAL_PATH;

class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
    void resizeEvent(QResizeEvent *event);
    void setController(Controller *controllerParam);


private:
    void setShortcut();


private slots:
    void searchChanged(const QString &text); //something written in searchbar
    void sendSearch(); // to controller
    void shortcutRoutine();
    void updateSize(); // after resize of window e.g

private:
    Controller* controller;
    QTimer* timerSearch;
    QTimer* timerAtStart;
    QString search;
    RightPart *rightPart;
    LeftPart *leftPart;
    SearchResults * searchResults;
    CustomerPanel * customerPanel;
    CartDisplay * cartDisplay;
    ProductsChoices * productsChoices;
    History * history;
    ConsoLogos* consoLogos;
    QWidget *centralWidget;
    QGridLayout *mainWindowLayout;
    QFrame *menu;
    QFrame *mainPart;
    QFrame *searchBar;
    QLabel *searchIcon;
    QLineEdit *searchText;
    QHBoxLayout *searchBarLayout;
    QGridLayout *mainPartLayout;
    QShortcut **shortcuts;
    QGridLayout *menuLayout;
    QLabel *logo;


};

#endif // MAINWINDOW_H
