cmake_minimum_required(VERSION 3.16)

project(AlbumPlayer_CMake VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui Multimedia)

include_directories(${CMAKE_SOURCE_DIR})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        wizard.h
        slideshowdialog.h
        removeprojdialog.h
        projtreewidget.h
        projtreethread.h
        projtreeitem.h
        projtree.h
        picstatebutton.h
        projsetpage.h
        picshow.h
        picbutton.h
        picanimationwidget.h
        opentreethread.h
        mymediaplayer.h
        mainwindow.h
        const.h
        confirmpage.h
        abbrlistwidgetitem.h
        abbrlistwidget.h
        wizard.cpp
        slideshowdialog.cpp
        removeprojdialog.cpp
        projtreewidget.cpp
        projtreethread.cpp
        projtreeitem.cpp
        projtree.cpp
        projsetpage.cpp
        picstatebutton.cpp
        picshow.cpp
        picbutton.cpp
        picanimationwidget.cpp
        opentreethread.cpp
        mymediaplayer.cpp
        mainwindow.cpp
        confirmpage.cpp
        abbrlistwidgetitem.cpp
        abbrlistwidget.cpp
        rc.qrc
        logo.rc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AlbumPlayer_CMake
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        logo.rc
    )
endif()

target_link_libraries(AlbumPlayer_CMake PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Multimedia)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AlbumPlayer_CMake)
endif()
set_target_properties(AlbumPlayer_CMake PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AlbumPlayer_CMake)
endif()
