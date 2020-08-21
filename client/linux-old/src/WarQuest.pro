#-------------------------------------------------
#
# Project created by QtCreator 2011-03-08T06:19:55
#
#-------------------------------------------------

QT       += network core gui webkit

TARGET = WarQuest
TEMPLATE = app
VERSION = 1.4

SOURCES += main.cpp\
        mainwindow.cpp \
    proxy.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    proxy.h \
    about.h \
    general.h

FORMS    += mainwindow.ui \
    proxy.ui \
    about.ui

RC_FILE = WarQuest.rc

RESOURCES += \
    resources.qrc
