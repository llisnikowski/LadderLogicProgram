TEMPLATE = lib
CONFIG += staticlib

QT -= gui
QT += quick


CONFIG += c++17


SOURCES += \
    componentLd.cpp

HEADERS += \
    componentLd.hpp

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target


