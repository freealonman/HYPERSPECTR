#-------------------------------------------------
#
# Project created by QtCreator 2014-11-21T17:10:17
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HYPERSPECTR
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cspectr.cpp

HEADERS  += mainwindow.h \
    cspectr.h \
    SData.h

FORMS    += mainwindow.ui
