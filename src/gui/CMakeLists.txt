cmake_minimum_required(VERSION 3.16)

set(GUI_MODULE_NAME "gui_module")

add_library(gui STATIC
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    exercises/ExerciseWidget.h
    blocks/intervalblockwidget.h 
    blocks/intervalblockwidget.cpp 
    blocks/intervalblockwidget.ui
    blocks/mainmenuwidget.h 
    blocks/mainmenuwidget.cpp 
    blocks/mainmenuwidget.ui
    exercises/intervalexercisewidget.h exercises/intervalexercisewidget.cpp exercises/intervalexercisewidget.ui
)

target_link_libraries(gui PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    audio_module
    music_module
    log_module
)

target_include_directories(gui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

