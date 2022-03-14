TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bigint/constructors.cpp \
        main.cpp \
        bigint/operators.cpp

HEADERS += \
    bigint/big_integer.h
