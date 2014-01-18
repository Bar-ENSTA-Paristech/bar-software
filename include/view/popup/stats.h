#ifndef STATS_H
#define STATS_H

#include <QScrollArea>
#include <QLabel>
#include <Qframe>
#include <QGridLayout>
#include <QStyleFactory>
#include "multilist.h"
#include "popup.h"
#include "structures.h"

extern ViewObjects VIEW;
class ViewStocks;

class Stats : public Popup
{
    Q_OBJECT
public:
    explicit Stats(QWidget *parent = 0);
    // launch a window with all the stats, including stocks of each category (that's why there is 6 view_productTuple in arguments)
    void launchStats(view_statsTuple& stats, view_productQueue& category0, view_productQueue& category1, view_productQueue& category2,
                     view_productQueue& category3, view_productQueue& category4, view_productQueue& category5);
    
signals:
    
private:
	QLabel* accountsTotal;
    QLabel* moneyInCashRegister;
    QLabel* moneyGivenThisYear;
    QLabel* moneyGivenLastYear;
    QLabel* totalSoldThisYear;
    QLabel* totalSoldLastYear;
    QLabel* numberOfCustomers;
    QLabel* numberOfProducts;

	QLabel* accountsTotalLabel;
    QLabel* moneyInCashRegisterLabel;
    QLabel* moneyGivenThisYearLabel;
    QLabel* moneyGivenLastYearLabel;
    QLabel* totalSoldThisYearLabel;
    QLabel* totalSoldLastYearLabel;
    QLabel* numberOfCustomersLabel;
    QLabel* numberOfProductsLabel;

    QLabel* stocks0Label;
    QLabel* stocks1Label;
    QLabel* stocks2Label;
    QLabel* stocks3Label;
    QLabel* stocks4Label;
    QLabel* stocks5Label;

	ViewStocks* category0Stocks;
	ViewStocks* category1Stocks;
	ViewStocks* category2Stocks;
	ViewStocks* category3Stocks;
	ViewStocks* category4Stocks;
	ViewStocks* category5Stocks;

	QGridLayout* layout;
    QGridLayout* virtualLayout;
	QFont titleFont;
	QScrollArea* scrollArea;
	QFrame* frame;

public slots:

    
};


// ############ VIEW_STOCKS ###########

class ViewStocks : public MultiList
{
    Q_OBJECT
public:
    explicit ViewStocks(QWidget *parent = 0);
    void setStocks(view_productQueue& queue);

private:



signals:

public slots:
};


#endif // STATS_H