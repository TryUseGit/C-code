#-------------------------------------------------
#
# Project created by QtCreator 2016-02-02T22:04:10
#
#-------------------------------------------------

QT       += core gui
QT += core
QT += multimedia
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    gamewidget.cpp

HEADERS  += mainwidget.h \
    gamewidget.h

FORMS    +=

RC_FILE  += myico.rc

DISTFILES +=

RESOURCES += \
    snakeresource.qrc \
    sounds.qrc



