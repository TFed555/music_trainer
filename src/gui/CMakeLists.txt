cmake_minimum_required(VERSION 3.16)

set(GUI_MODULE_NAME "gui_module")

add_library(gui STATIC
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ExerciseWidget.h
    intervalblockwidget.h intervalblockwidget.cpp intervalblockwidget.ui
    mainmenuwidget.h mainmenuwidget.cpp mainmenuwidget.ui




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

