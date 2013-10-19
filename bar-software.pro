#-------------------------------------------------
#
# Project created by QtCreator 2013-06-25T21:35:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bar-software
TEMPLATE = app

SOURCES += src/controller/cart.cpp \
src/controller/controller.cpp \
src/controller/customer.cpp \
src/controller/main.cpp \
src/controller/product.cpp \
src/model/database.cpp \
src/model/query.cpp \
src/model/sqlite3.c \
src/view/cartdisplay.cpp \
src/view/customerpanel.cpp \
src/view/history.cpp \
src/view/leftpart.cpp \
src/view/mainwindow.cpp \
src/view/multilist.cpp \
src/view/productschoices.cpp \
src/view/rightpart.cpp \
src/view/searchresults.cpp \
src/view/consologos.cpp


INCLUDEPATH += include/controller \
include/model \
include/view

HEADERS += include/controller/cart.h \
include/controller/controller.h \
include/controller/customer.h \
include/controller/main.h \
include/controller/product.h \
include/model/database.h \
include/model/query.h \
include/model/sqlite3.h \
include/view/cartdisplay.h \
include/view/customerpanel.h \
include/view/history.h \
include/view/leftpart.h \
include/view/mainwindow.h \
include/view/multilist.h \
include/view/productschoices.h \
include/view/rightpart.h \
include/view/searchresults.h \
include/view/consologos.h

FORMS    += \
    ui/mainwindow_old.ui \

OTHER_FILES += \
    ui/view/mainDesign.css \
    include/view/mainDesign.css

macx {
#QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7
#LIBS += -stdlib=libc++ -mmacosx-version-min=10.7
QMAKE_CXXFLAGS += -std=c++11 -mmacosx-version-min=10.7
LIBS +=  -mmacosx-version-min=10.7
} else {
  QMAKE_CXXFLAGS += -std=c++11
}

#LIBS += -lsqlite3

#LIBS += /lib/x86_64-linux-gnu/libdl.so.2
