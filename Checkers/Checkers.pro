#-------------------------------------------------
#
# Project created by QtCreator 2011-12-02T17:38:24
#
#-------------------------------------------------

QT       += core gui network

TARGET = Checkers
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    checkerview.cpp \
    piece.cpp \
    board.cpp \
    field.cpp \
    move.cpp \
    creategamedialog.cpp \
    tests.cpp \
    networkclient.cpp \
    networkmanager.cpp \
    networkserver.cpp \
    gamestate.cpp \
    uncheckablefield.cpp \
    checkablefield.cpp

HEADERS  += mainwindow.h \
    checkerview.h \
    piece.h \
    board.h \
    field.h \
    move.h \
    creategamedialog.h \
    tests.h \
    consts.h \
    networkclient.h \
    networkmanager.h \
    networkserver.h \
    gamestate.h \
    uncheckablefield.h \
    checkablefield.h

FORMS    += mainwindow.ui \
    creategamedialog.ui


















