#-------------------------------------------------
#
# Project created by QtCreator 2011-03-08T06:19:55
#
#-------------------------------------------------

QT       += core gui network webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WarQuest
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    proxy.cpp \
    about.cpp \
    customstyle.cpp

HEADERS  += mainwindow.h \
    proxy.h \
    about.h \
    general.h \
    customstyle.h

FORMS    += mainwindow.ui \
    proxy.ui \
    about.ui

RC_FILE = WarQuest.rc

RESOURCES += \
    resources.qrc
