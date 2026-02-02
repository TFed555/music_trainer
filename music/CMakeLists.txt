cmake_minimum_required(VERSION 3.16)

set(MUSIC_MODULE_NAME "music_module")


set(MUSIC_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/pitchutils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pitchutils.h
)

add_library(${MUSIC_MODULE_NAME} STATIC ${MUSIC_SOURCES})

set(ALL_SOURCES
    ${MUSIC_SOURCES}
)

set_target_properties(${MUSIC_MODULE_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
)

target_include_directories(${MUSIC_MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${MUSIC_MODULE_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)

set(MUSIC_MODULE_TARGET ${MUSIC_MODULE_NAME} PARENT_SCOPE)

