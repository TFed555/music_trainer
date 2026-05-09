cmake_minimum_required(VERSION 3.16)

set(LOG_MODULE_NAME "log_module")

set(LOG_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp
)

add_library(${LOG_MODULE_NAME} STATIC ${LOG_SOURCES})

set(ALL_SOURCES
    ${LOG_SOURCES}
)

target_link_libraries(log_module PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
)


target_include_directories(log_module PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

