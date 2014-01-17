#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QFrame>
#include <QLineEdit>
#include <QLabel>
#include <QTimer>
#include <QShortcut>
#include <QVector>
#include <queue>
#include "leftpart.h"
#include "rightpart.h"
#include "controller.h"
#include "structures.h"
#include "qcustomplot.h"
#include "login.h"
#include "individualhistory.h"
#include "globalhistory.h"
#include "newcustomer.h"
#include "addstock.h"
#include "addproduct.h"
#include "editproduct.h"
#include "editlogin.h"
#include "stats.h"
#include "admin.h"
#include "structures.h"
extern ViewObjects VIEW;

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
    void setGraph(db_dataarray& data, QString xTitle, QString yTitle, QString title);


private:
    void setShortcut();


private slots:
    void searchChanged(const QString &text); //something written in searchbar
    void sendSearch(); // to controller
    void shortcutRoutine();
    void updateSize(); // after resize of window e.g
    void launchGlobalHistory();
    void launchNewCustomer();
    void launchAddStock();
    void launchAddProduct();
    void launchEditProduct();
    void launchStats();
    void launchAdmin();


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
    QFrame *menuButtons;
    QFrame *mainPart;
    QFrame *searchBar;
    QLabel *searchIcon;
    QLineEdit *searchText;
    QHBoxLayout *searchBarLayout;
    QGridLayout *mainPartLayout;
    QShortcut **shortcuts;
    QGridLayout *menuLayout;
    QLabel *logo;
    Calculator* calculatorWindow;

    QGridLayout *buttonsLayout;
    QPushButton* globalHistory;
    QPushButton* newCustomer;
    QPushButton* addStock;
    QPushButton* addProduct;
    QPushButton* editProduct;
    QPushButton* editLogin;
    QPushButton* stats;
    QPushButton* admin;
};

#endif // MAINWINDOW_H
