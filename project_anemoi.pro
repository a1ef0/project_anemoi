TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bigint/auxillary.cpp \
        bigint/constructors.cpp \
        bigint/functions.cpp \
        bigint/operators.cpp \
        main.cpp

HEADERS += \
    bigint/auxillary.h \
    bigint/bigint.h \
    bigint/functions.h
