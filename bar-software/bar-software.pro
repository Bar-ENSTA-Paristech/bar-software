#-------------------------------------------------
#
# Project created by QtCreator 2013-06-25T21:35:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bar-software
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customer.cpp \
    product.cpp \
    cart.cpp \
    database.cpp \
    query.cpp \
    sqlite3.c

HEADERS  += mainwindow.h \
    customer.h \
    product.h \
    cart.h \
    database.h \
    query.h \
    sqlite3.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
