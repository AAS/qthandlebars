QT += testlib core
QT -= gui
TARGET = test_qthandlebars
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

SOURCES += \
	tst_qthandlebars.cpp

HEADERS += \
	tst_qthandlebars.h

INCLUDEPATH += $$PWD/../src
LIBS += -L.. -lqthandlebars

DESTDIR = $$OUT_PWD/..
