cmake_minimum_required(VERSION 3.2.2)
project(hswitch)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package( Qt5LinguistTools )
find_package( Qt5Core 5.3 REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Svg REQUIRED )

qt5_wrap_ui(mainwindow.h mainwindow.ui)
qt5_wrap_ui(libraries/qmarkdowntextedit/ui_qplaintexteditsearchwidget.h
        libraries/qmarkdowntextedit/qplaintexteditsearchwidget.ui)
qt5_wrap_ui(libraries/qttoolbareditor/src/toolbar_editor.hpp
        libraries/qttoolbareditor/src/toolbar_editor.ui)

set(RESOURCE_FILES
        libraries/qmarkdowntextedit/media.qrc
        )

qt5_add_resources(RESOURCE_ADDED ${RESOURCE_FILES})

set(SOURCE_FILES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    version.h
    libraries/qmarkdowntextedit/markdownhighlighter.cpp
    libraries/qmarkdowntextedit/markdownhighlighter.h
    libraries/qmarkdowntextedit/qmarkdowntextedit.cpp
    libraries/qmarkdowntextedit/qmarkdowntextedit.h
    libraries/qmarkdowntextedit/qplaintexteditsearchwidget.cpp
    libraries/qmarkdowntextedit/qplaintexteditsearchwidget.h
    libraries/qmarkdowntextedit/qplaintexteditsearchwidget.ui
)

add_executable(hswitch ${SOURCE_FILES} ${RESOURCE_ADDED} ${QON_QM_FILES})


# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES} ${Qt5Svg_INCLUDES})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS} ${Qt5Svg_DEFINITIONS})

# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${Qt5Svg_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "-std=c++0x")

# The Qt5Widgets_LIBRARIES variable also includes QtGui and QtCore
target_link_libraries(hswitch ${Qt5Widgets_LIBRARIES} ${Qt5Svg_LIBRARIES})

#qt5_use_modules(hswitch Widgets Core Gui Sql Svg Network Script Xml PrintSupport)
