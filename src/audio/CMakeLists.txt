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

set(PLAYBACK_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/playback/noteplayer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/playback/noteplayer.cpp
)

set(GENERATOR_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/IntervalGenerator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/IntervalGenerator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/GeneratedAudio.h
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/generatorfactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/generatorfactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/notegenerator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/notegenerator.cpp
)

set (DSP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/dsp/oscillator.h
)

set(ALL_SOURCES
    ${AUDIO_SOURCES}
    ${GENERATOR_SOURCES}
    ${PLAYBACK_SOURCES}
    ${DSP_SOURCES}
)

add_library(${AUDIO_MODULE_NAME} STATIC ${ALL_SOURCES}
    dsp/oscillator.cpp
)

set_target_properties(${AUDIO_MODULE_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
)

target_include_directories(${AUDIO_MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/generators
    ${CMAKE_CURRENT_SOURCE_DIR}/playback
    ${CMAKE_CURRENT_SOURCE_DIR}/dsp
    ${RTAUDIO_INCLUDE_DIRS}
)

target_link_libraries(${AUDIO_MODULE_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    ${RTAUDIO_LIBRARIES}
)

set(AUDIO_MODULE_TARGET ${AUDIO_MODULE_NAME} PARENT_SCOPE)
