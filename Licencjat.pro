#-------------------------------------------------
#
# Project created by QtCreator 2014-10-19T10:33:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 \
    static \
    staticlib
QMAKE_CXXFLAGS += -std=c++11 -static
TARGET = Licencjat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    basepanellayout.cpp \
    basescrollarea.cpp \
    Panels/basepanel.cpp \
    Panels/functionpanel.cpp \
    Toolbar/customtoolbar.cpp \
    Toolbar/customtoolbarbutton.cpp \
    Panels/ifelseblockpanel.cpp \
    Panels/ifelseblockpart.cpp \
    Panels/functionblock.cpp \
    Panels/textpanel.cpp \
    Panels/textblock.cpp \
    Panels/ifblock.cpp \
    Panels/whileblock.cpp \
    Forms/variablesframe.cpp \
    Forms/whileconditionframe.cpp \
    Forms/ifconditionframe.cpp \
    Variables/variablestablemodel.cpp \
    Variables/variablemodel.cpp \
    Forms/newfunctionform.cpp \
    Forms/includesframe.cpp \
    Serialization/xmlparser.cpp \
    Serialization/pugixml.cpp \
    Panels/shortpanel.cpp \
    Panels/dynamicblock.cpp \
    Forms/renameframe.cpp \
    Forms/usageform.cpp \
    Forms/usagedefinitionform.cpp \
    Variables/attributestablemodel.cpp \
    Variables/attributemodel.cpp \
    Toolbar/dynamictoolbar.cpp \
    Panels/shortcomponent.cpp \
    Panels/containerpanel.cpp \
    Serialization/sourcecodebuilder.cpp

HEADERS  += mainwindow.h \
    basepanellayout.h \
    basescrollarea.h \
    Panels/basepanel.h \
    Panels/functionpanel.h \
    Toolbar/customtoolbar.h \
    Toolbar/customtoolbarbutton.h \
    Panels/ifelseblockpanel.h \
    Panels/ifelseblockpart.h \
    Panels/functionblock.h \
    Panels/textpanel.h \
    Panels/textblock.h \
    Panels/ifblock.h \
    Panels/whileblock.h \
    Forms/variablesframe.h \
    Forms/whileconditionframe.h \
    Forms/ifconditionframe.h \
    Variables/variablestablemodel.h \
    Variables/variablemodel.h \
    Forms/newfunctionform.h \
    Forms/includesframe.h \
    Serialization/xmlparser.h \
    Panels/shortpanel.h \
    Panels/dynamicblock.h \
    Forms/renameframe.h \
    Forms/usageform.h \
    Forms/usagedefinitionform.h \
    Variables/attributestablemodel.h \
    Variables/attributemodel.h \
    Toolbar/dynamictoolbar.h \
    Panels/shortcomponent.h \
    Panels/containerpanel.h \
    Serialization/sourcecodebuilder.h \
    Constants.h

FORMS    += mainwindow.ui \
    Forms/variablesframe.ui \
    Forms/whileconditionframe.ui \
    Forms/ifconditionframe.ui \
    Forms/newfunctionform.ui \
    Forms/includesframe.ui \
    Forms/renameframe.ui \
    Forms/usageform.ui \
    Forms/usagedefinitionform.ui
