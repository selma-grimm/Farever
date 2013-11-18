#-------------------------------------------------
#
# Project created by QtCreator 2012-12-15T13:39:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Farever
TEMPLATE = app
CONFIG += precompile_header

PRECOMPILED_HEADER = Precompile.h

SOURCES += main.cpp\
        MainWindow.cpp \
    Panels/Delegates/BrowseTable.cpp \
    Panels/RootPanel.cpp \
    Panels/BrowsePanel.cpp \
    Panels/AbstractPanel.cpp \
    FileManager.cpp \
    Utils.cpp \
    Dialogs/CreateFolderDialog.cpp \
    Panels/Delegates/RootTable.cpp \
    Panels/Delegates/NameDelegate.cpp \
    Panels/Delegates/BrowseModel.cpp \
    Panels/Delegates/CustomHeader.cpp \
    Panels/Delegates/ViewDelegate.cpp \
    Dialogs/ConfirmDialog.cpp

HEADERS  += MainWindow.h \
    Panels/Delegates/BrowseTable.h \
    Panels/RootPanel.h \
    Panels/BrowsePanel.h \
    Panels/AbstractPanel.h \
    Precompile.h \
    FileManager.h \
    Utils.h \
    Dialogs/CreateFolderDialog.h \
    Panels/Delegates/RootTable.h \
    Panels/Delegates/NameDelegate.h \
    Panels/Delegates/BrowseModel.h \
    Panels/Delegates/CustomHeader.h \
    Colors.h \
    Panels/Delegates/ViewDelegate.h \
    Dialogs/ConfirmDialog.h

FORMS    += MainWindow.ui
