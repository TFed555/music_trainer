cmake_minimum_required(VERSION 3.16)

set(AUDIO_MODULE_NAME "audio_module")

find_package(PkgConfig QUIET)

pkg_check_modules(RTAUDIO REQUIRED rtaudio)

# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(AUDIO_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/audio.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/audio.h
)

file(GLOB_RECURSE GENERATOR_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/*.ui
)

set(ALL_SOURCES
    ${AUDIO_SOURCES}
    ${GENERATOR_SOURCES}
)

add_library(${AUDIO_MODULE_NAME} STATIC ${ALL_SOURCES}
    generators/IntervalGenerator.h
    generators/IntervalGenerator.cpp
    generators/GeneratedAudio.h)

set_target_properties(${AUDIO_MODULE_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
)

target_include_directories(${AUDIO_MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/generators
    ${RTAUDIO_INCLUDE_DIRS}
)

target_link_libraries(${AUDIO_MODULE_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    ${RTAUDIO_LIBRARIES}
)

set(AUDIO_MODULE_TARGET ${AUDIO_MODULE_NAME} PARENT_SCOPE)
