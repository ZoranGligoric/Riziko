#-------------------------------------------------
#
# Project created by QtCreator 2015-05-04T17:47:44
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT += widgets

QT += multimedia

TARGET = ProjekatRiziko
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -w

TEMPLATE = app


SOURCES += main.cpp \
    player.cpp \
    territory.cpp \
    turn.cpp \
    functions.cpp \
    mainwindow.cpp \
    startingwindow.cpp \
    gamesetup.cpp \
    playerwidget.cpp \
    continent.cpp \
    world.cpp \
    options.cpp \
    game.cpp

HEADERS += \
    player.h \
    territory.h \
    turn.h \
    functions.h \
    mainwindow.h \
    startingwindow.h \
    gamesetup.h \
    playerwidget.h \
    continent.h \
    world.h \
    options.h \
    game.h


FORMS += \
    mainwindow.ui \
    startingwindow.ui \
    gamesetup.ui \
    playerwidget.ui \
    options.ui \
    game.ui

RESOURCES += \
    resource.qrc
