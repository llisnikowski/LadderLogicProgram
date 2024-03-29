TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt

QT += quick

INCLUDEPATH += \
    googletest/include \
    googlemock/include \
    googletest \
    googlemock


SOURCES += \
    ComponentLd-Test.cpp \
    LdPainter-Test.cpp \
    SymbolsBar-Test.cpp \
    googletest/src/gtest-all.cc \
    googlemock/src/gmock-all.cc \
    main.cpp \
    firstTest.cpp

HEADERS =


DEPENDPATH += \
    ../LibComponentLd

INCLUDEPATH += \
    ../LibComponentLd


win32:CONFIG(release, debug|release):{
    LIBS += \
    -L$$OUT_PWD/../LibComponentLd/release/ -lLibComponentLd
}
else:win32:CONFIG(debug, debug|release):{
    LIBS += \
    -L$$OUT_PWD/../LibComponentLd/debug/ -lLibComponentLd
}
else:unix: {
    LIBS += \
    -L$$OUT_PWD/../LibComponentLd/ -lLibComponentLd
}
