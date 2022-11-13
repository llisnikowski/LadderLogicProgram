TEMPLATE = lib
CONFIG += staticlib

QT -= gui
QT += core quick qml


CONFIG += c++17


SOURCES += \
    componentLd.cpp \
    drag.cpp \
    input.cpp \
    ldPainter.cpp \
    output.cpp \
    coil.cpp \
    contact.cpp \
    line.cpp \
    node.cpp \
    symbolsBar.cpp

HEADERS += \
    componentLd.hpp \
    drag.hpp \
    input.hpp \
    ldPainter.hpp \
    output.hpp \
    coil.hpp \
    contact.hpp \
    line.hpp \
    node.hpp \
    symbolsBar.hpp

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target


