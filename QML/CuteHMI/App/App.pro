include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_app_1_qml)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick
#<workaround ref="cutehmi_app_1-1" target="Qt" cause="bug">
QT += widgets
#</workaround>

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_app_1_qml_pl.ts

include(../../../cutehmi_1/import.pri)
include(../../../cutehmi_app_1/import.pri)

DISTFILES += \
    qmldir \
    designer/App.metainfo

RESOURCES +=

HEADERS += \
    src/CuteHMIAppQMLPlugin.hpp

SOURCES += \
    src/CuteHMIAppQMLPlugin.cpp

