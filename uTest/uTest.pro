TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt


INCLUDEPATH += \
    googletest/include \
    googlemock/include \
    googletest \
    googlemock


SOURCES += \
    googletest/src/gtest-all.cc \
    googlemock/src/gmock-all.cc \
    main.cpp \
    firstTest.cpp

HEADERS =
