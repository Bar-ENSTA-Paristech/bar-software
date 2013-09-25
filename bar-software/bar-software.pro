#-------------------------------------------------
#
# Project created by QtCreator 2013-06-25T21:35:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bar-software
TEMPLATE = app


SOURCES +=  controller/main.cpp \
    controller/product.cpp \
    controller/customer.cpp \
    controller/cart.cpp \
    model/sqlite3.c \
    model/query.cpp \
    model/database.cpp \
    view/searchresults.cpp \
    view/rightpart.cpp \
    view/productschoices.cpp \
    view/multilist.cpp \
    view/mainwindow.cpp \
    #view/mainwindow_old.cpp \
    view/leftpart.cpp \
    view/history.cpp \
    view/customerpanel.cpp \
    view/cartdisplay.cpp \
    controller/controller.cpp

HEADERS  += controller/product.h \
    controller/customer.h \
    controller/cart.h \
    model/sqlite3.h \
    model/query.h \
    model/database.h \
    view/searchresults.h \
    view/rightpart.h \
    view/productschoices.h \
    view/multilist.h \
    view/mainwindow.h \
    #view/mainwindow_old.h \
    view/leftpart.h \
    view/history.h \
    view/customerpanel.h \
    view/cartdisplay.h \
    controller/controller.h

FORMS    += \
    view/mainwindow_old.ui

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    view/mainDesign.css

#LIBS += /lib/x86_64-linux-gnu/libdl.so.2
