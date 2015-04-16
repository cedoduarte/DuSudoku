TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    DuSudoku.cpp

HEADERS += \
    DuSudoku.h

QMAKE_CXXFLAGS += -std=gnu++14
