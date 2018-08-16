#-------------------------------------------------
#
# Project created by QtCreator 2018-08-15T15:16:37
#
#-------------------------------------------------

QT       += core gui serialport

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_serialport
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialport.cpp

HEADERS  += mainwindow.h \
    serialport.h
