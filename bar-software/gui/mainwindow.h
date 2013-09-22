#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QFrame>
#include <QLineEdit>
#include <QLabel>
#include <QTimer>
#include <QShortcut>
#include "leftpart.h"
#include "rightpart.h"

extern QString GLOBAL_PATH;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow();

    private slots:
        void searchChanged(const QString &text);
        void sendSearch();
        void shortcut();
        void updateSize();

    private:
        QTimer* timerSearch;
        QTimer* timerAtStart;
        QString search;
        RightPart *rightPart;
        LeftPart *leftPart;


};

#endif // MAINWINDOW_H
