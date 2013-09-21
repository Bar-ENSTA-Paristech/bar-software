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
        gui/mainwindow.cpp \
    customer.cpp \
    product.cpp \
    cart.cpp \
    database.cpp \
    query.cpp \
    sqlite3.c \
    gui/leftpart.cpp \
    gui/rightpart.cpp \
    gui/history.cpp \
    gui/cartdisplay.cpp \
    gui/productschoices.cpp \
    gui/customerpanel.cpp \
    gui/multilist.cpp \
    gui/searchresults.cpp

HEADERS  += gui/mainwindow.h \
    customer.h \
    product.h \
    cart.h \
    database.h \
    query.h \
    sqlite3.h \
    gui/leftpart.h \
    gui/rightpart.h \
    gui/history.h \
    gui/cartdisplay.h \
    gui/productschoices.h \
    gui/customerpanel.h \
    gui/multilist.h \
    gui/searchresults.h

FORMS    +=

QMAKE_CXXFLAGS += -std=c++0x

OTHER_FILES += \
    gui/mainDesign.css
