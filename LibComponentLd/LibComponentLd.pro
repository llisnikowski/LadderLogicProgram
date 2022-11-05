TEMPLATE = lib
CONFIG += staticlib

QT -= gui
QT += quick


CONFIG += c++17


SOURCES += \
    componentLd.cpp \
    drag.cpp \
    input.cpp \
    output.cpp \
    coil.cpp \
    contact.cpp \
    line.cpp \
    node.cpp

HEADERS += \
    componentLd.hpp \
    drag.hpp \
    input.hpp \
    output.hpp \
    coil.hpp \
    contact.hpp \
    line.hpp \
    node.hpp

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target


