#-------------------------------------------------
#
# Project created by QtCreator 2017-05-03T11:35:28
#
#-------------------------------------------------

QT       += core gui
win32 {
    LIBS += -lOpengl32
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_GLSL_IDE
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        ide.cpp \
    glwidget.cpp \
    textedit.cpp \
    gltoolbar.cpp \
    about.cpp

HEADERS  += ide.h \
    glwidget.h \
    textedit.h \
    gltoolbar.h \
    about.h

FORMS    += ide.ui

RESOURCES +=

DISTFILES +=
