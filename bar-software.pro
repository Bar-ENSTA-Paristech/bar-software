#-------------------------------------------------
#
# Project created by QtCreator 2013-06-25T21:35:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = bar-software
TEMPLATE = app

SOURCES += src/controller/cart.cpp \
src/controller/customer.cpp\
src/controller/controller.cpp \
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
src/view/consologos.cpp \
src/view/categoriebutton.cpp \
resources/lib/qcustomplot.cpp \
src/model/plotting.cpp \
src/controller/stock.cpp \
src/controller/structures.cpp \
src/view/popup/calculator.cpp \
src/view/popup/login.cpp \
src/view/popup/individualhistory.cpp \
src/view/popup/editcustomer.cpp \
src/view/popup/deletecustomer.cpp \
src/view/popup/globalhistory.cpp \
src/view/popup/newcustomer.cpp \
    src/view/popup/popup.cpp \
    src/view/popup/addstock.cpp \
    src/view/popup/addproduct.cpp \
    src/view/popup/editproduct.cpp \
    src/view/popup/editlogin.cpp \
    src/view/popup/stats.cpp \
    src/view/popup/admin.cpp \
    src/view/popup/moneytransfer.cpp



INCLUDEPATH += include/controller \
include/model \
include/view \
resources/lib \
include/view/popup

HEADERS += include/controller/cart.h \
include/controller/customer.h \
include/controller/controller.h \
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
include/view/consologos.h \
include/view/categoriebutton.h \
resources/lib/matplotpp.h \
resources/lib/gl2ps.h \
include/model/plotting.h \
resources/lib/qcustomplot.h \
include/controller/stock.h \
include/controller/structures.h \
include/view/popup/calculator.h \
include/view/popup/login.h \
include/view/popup/individualhistory.h \
include/view/popup/editcustomer.h \
include/view/popup/deletecustomer.h \
include/view/popup/globalhistory.h \
include/view/popup/newcustomer.h \
include/view/popup/popup.h \
    include/view/popup/addstock.h \
    include/view/popup/addproduct.h \
    include/view/popup/editproduct.h \
    include/view/popup/editlogin.h \
    include/view/popup/stats.h \
    include/view/popup/admin.h \
    include/view/popup/moneytransfer.h



OTHER_FILES += \
    ui/view/mainDesign.css \
    resources/design/mainDesign.css \

macx {
#QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7
#LIBS += -stdlib=libc++ -mmacosx-version-min=10.7
QMAKE_CXXFLAGS += -std=c++11 -mmacosx-version-min=10.7 #-stdlib=libc++
LIBS +=  -mmacosx-version-min=10.7
} else {
  QMAKE_CXXFLAGS += -std=c++11
}
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_DEBUG += -O0

#LIBS += -lsqlite3

linux{
LIBS += /lib/x86_64-linux-gnu/libdl.so.2
}
