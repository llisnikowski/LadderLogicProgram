TEMPLATE = app

QT += quick qml

CONFIG += create_libtool compile_included_sources
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

RESOURCES += qml.qrc




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


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target


