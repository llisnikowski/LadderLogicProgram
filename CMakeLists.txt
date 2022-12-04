cmake_minimum_required(VERSION 3.23.2)

project(PLC VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Gui)

qt_standard_project_setup()

file(GLOB MAIN_FILE
    App/*.hpp
    App/*.cpp
)

file(GLOB PROJECT_HEADERS  
     Ld/*.hpp
     Network/*.hpp
     UserInterface/*.hpp
     LdProperty/*.hpp
)

file(GLOB PROJECT_SOURCES
    Ld/*.cpp
    Network/*.cpp
    UserInterface/*.cpp
    LdProperty/*.cpp
)

set(PROJECT_RESOURSES
    App/qml.qrc
    LdProperty/qml.qrc
)

file(GLOB OTHER_FILES
    .gitignore
)

add_custom_target(OtherFiles
    SOURCES ${OTHER_FILES}
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        App/main.cpp
        MANUAL_FINALIZATION
        ${MAIN_FILE}
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_RESOURSES}
    )
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(${PROJECT_NAME}
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/Ld
  ${CMAKE_SOURCE_DIR}/Network
  ${CMAKE_SOURCE_DIR}/UserInterface
  ${CMAKE_SOURCE_DIR}/LdProperty
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::Gui
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(${PROJECT_NAME})
    qt_finalize_executable(${PROJECT_NAME})
endif()

# -- | Unit Tests | --

enable_testing()

file(GLOB GTEST_FILE
    uTest/googletest/src/gtest-all.cc
    uTest/googlemock/src/gmock-all.cc
)

file(GLOB UTEST_SOURCES
    uTest/*.cpp
    uTest/Ld/*.cpp
    uTest/Network/*.cpp
    uTest/UserInterface/*.cpp
    uTest/LdProperty/*.cpp
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    add_executable(${PROJECT_NAME}-ut
        ${GTEST_FILE}
        ${PROJECT_HEADERS}
        ${PROJECT_SOURCES}
        ${UTEST_SOURCES}
    )
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(${PROJECT_NAME}
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(
    ${PROJECT_NAME}-ut
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Gui
)


target_include_directories(${PROJECT_NAME}-ut PRIVATE
  ${CMAKE_SOURCE_DIR}/uTest/googletest
  ${CMAKE_SOURCE_DIR}/uTest/googletest/include
  ${CMAKE_SOURCE_DIR}/uTest/googlemock
  ${CMAKE_SOURCE_DIR}/uTest/googlemock/include
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/uTest
  ${CMAKE_SOURCE_DIR}/Ld
  ${CMAKE_SOURCE_DIR}/Network
  ${CMAKE_SOURCE_DIR}/UserInterface
  ${CMAKE_SOURCE_DIR}/LdProperty
)



