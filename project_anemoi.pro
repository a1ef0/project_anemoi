TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bigint/constructors.cpp \
        bigint/functions.cpp \
        main.cpp \
        bigint/operators.cpp

HEADERS += \
    bigint/big_integer.h \
    bigint/functions.h
