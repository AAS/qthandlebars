QT -= gui
TARGET = qthandlebars
TEMPLATE = lib
CONFIG += shared
#CONFIG -= debug_and_release debug_and_release_target
DEFINES += QTHANDLEBARS_LIBRARY QTHANDLEBARS_WITH_SQL

CONFIG(staticlib): DEFINES += QTHANDLEBARS_STATIC

if(contains(DEFINES, QTHANDLEBARS_WITH_SQL)){
	QT += sql
}

!win32:VERSION = 1.0.0

include(qthandlebars.pri)

DESTDIR = $$OUT_PWD/..
