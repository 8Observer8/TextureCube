#-------------------------------------------------
#
# Project created by QtCreator 2014-09-06T12:15:42
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextureCube
TEMPLATE = app


SOURCES += main.cpp\
        Dialog.cpp \
    Scene.cpp

HEADERS  += Dialog.h \
    Scene.h

FORMS    += Dialog.ui

RESOURCES += \
    Textures.qrc
