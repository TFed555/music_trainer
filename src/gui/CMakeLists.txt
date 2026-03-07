cmake_minimum_required(VERSION 3.16)

set(GUI_MODULE_NAME "gui_module")

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(gui_module STATIC
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    blocks/intervalblockwidget.h 
    blocks/intervalblockwidget.cpp 
    blocks/intervalblockwidget.ui
    blocks/mainmenuwidget.h 
    blocks/mainmenuwidget.cpp 
    blocks/mainmenuwidget.ui
    exercises/exercisewithtileswidget.h exercises/exercisewithtileswidget.cpp exercises/exercisewithtileswidget.ui
    common/notetileswidget.h common/notetileswidget.cpp common/notetileswidget.ui
    blocks/IBlockWidget.h
    exercises/exercisenotileswidget.h exercises/exercisenotileswidget.cpp exercises/exercisenotileswidget.ui
    blocks/chordblockwidget.h blocks/chordblockwidget.cpp blocks/chordblockwidget.ui
    common/octavetileswidget.h common/octavetileswidget.cpp common/octavetileswidget.ui

)

target_link_libraries(gui_module PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    audio_module
    music_module
    log_module
)
target_link_libraries(gui_module PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_include_directories(gui_module PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

