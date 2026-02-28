cmake_minimum_required(VERSION 3.16)

set(GUI_MODULE_NAME "gui_module")

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(gui STATIC
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    blocks/intervalblockwidget.h 
    blocks/intervalblockwidget.cpp 
    blocks/intervalblockwidget.ui
    blocks/mainmenuwidget.h 
    blocks/mainmenuwidget.cpp 
    blocks/mainmenuwidget.ui
    exercises/intervalexercisewidget.h exercises/intervalexercisewidget.cpp exercises/intervalexercisewidget.ui
    common/notetileswidget.h common/notetileswidget.cpp common/notetileswidget.ui
    blocks/IBlockWidget.h
)

target_link_libraries(gui PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    audio_module
    music_module
    log_module
)
target_link_libraries(gui PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_include_directories(gui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

