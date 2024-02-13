cmake_minimum_required(VERSION 3.16)

project(Chess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appChess
    main.cpp
    qml_bridge.cpp
    qml_bridge.h
)

qt6_add_resources(RESOURCES main.qrc)

qt_add_qml_module(appChess
    URI Chess
    VERSION 1.0
    SOURCES game_logic.h game_logic.cpp
    SOURCES qml_bridge_observer.h
    SOURCES hall_of_fame.h hall_of_fame.cpp
    SOURCES record.h record.cpp
    QML_FILES Main.qml
    RESOURCES main.qrc images/blue.png images/red.png images/artboard_0.png
    RESOURCES images/artboard_1.png images/artboard_2.png images/artboard_3.png
    RESOURCES images/artboard_4.png images/artboard_5.png images/artboard_6.png
    RESOURCES images/artboard_7.png images/artboard_8.png
    SOURCES movetimer.h movetimer.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appChess PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appChess
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appChess
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appChess
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
