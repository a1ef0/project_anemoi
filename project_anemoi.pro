TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bigint/constructors.cpp \
        bigint/functions.cpp \
        bigint/operators.cpp \
        main.cpp

HEADERS += \
    bigint/bigint.h \
    bigint/functions.h
