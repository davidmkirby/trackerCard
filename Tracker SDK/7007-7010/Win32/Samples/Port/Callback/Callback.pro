# Qt Project File for Callback
QT += core gui

CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Define the target
TARGET = Callback
TEMPLATE = app

# Source and header files
SOURCES += \
    Callback.cpp \
    CallbackDlg.cpp \
    StdAfx.cpp

HEADERS += \
    Callback.h \
    CallbackDlg.h \
    StdAfx.h

# Resource file
RESOURCES += Callback.qrc

# Include paths
INCLUDEPATH += .

# Linker settings (adjust as necessary)
LIBS +=

# Remove Windows-specific flags
win32:CONFIG -= windows
