cmake_minimum_required(VERSION 3.16)

set(AUDIO_MODULE_NAME "audio_module")

find_package(PkgConfig QUIET)

pkg_check_modules(RTAUDIO REQUIRED rtaudio)
pkg_check_modules(SAMPLERATE REQUIRED samplerate)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/IGenerator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/GeneratedAudio.h
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/generatorfactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/generatorfactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/notegenerator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/notegenerator.cpp
)

set(ALL_SOURCES
    ${AUDIO_SOURCES}
    ${GENERATOR_SOURCES}
    ${PLAYBACK_SOURCES}
)

add_library(${AUDIO_MODULE_NAME} STATIC ${ALL_SOURCES}
)

set_target_properties(${AUDIO_MODULE_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
)

target_include_directories(${AUDIO_MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/generators
    ${CMAKE_CURRENT_SOURCE_DIR}/playback
    ${RTAUDIO_INCLUDE_DIRS}
    ${SAMPLERATE_INCLUDE_DIRS}
)

target_link_libraries(${AUDIO_MODULE_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    ${RTAUDIO_LIBRARIES}
    ${SAMPLERATE_LIBRARIES}
)

set(AUDIO_MODULE_TARGET ${AUDIO_MODULE_NAME} PARENT_SCOPE)
