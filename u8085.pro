#-------------------------------------------------
#
# Project created by QtCreator 2016-01-09T23:29:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = u8085
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    memeditordock.cpp \
    regeditor.cpp \
    internal8085.cpp \
    genopcodes.cpp \
    register.cpp \
    run.cpp \
    instructionimplementation.cpp \
    flagmaip.cpp \
    assemble.cpp \
    utils.cpp \
    logdock.cpp \
    instructiondatautil.cpp \
    freezing.cpp

HEADERS  += mainwindow.h \
    memeditordock.h \
    regeditor.h \
    internal8085.h \
    register.h \
    utils.h \
    debugmode.h \
    logdock.h

FORMS    += mainwindow.ui

DEFINES += QT_NO_CAST_FROM_ASCII

RESOURCES += \
    icons.qrc

CONFIG += qt debug warn_on console
