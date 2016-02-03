TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG  += c++11

SOURCES += main.cpp \
    muunnin.cpp \
    saannot.cpp \
    onko_laillinen.cpp \
    lue.cpp \
    merkkijonoapu.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    merkkijonoapu.hh \
    muunnin.hh \
    lue.hh \
    saannot.hh \
    onko_laillinen.hh

OTHER_FILES +=

DISTFILES +=

