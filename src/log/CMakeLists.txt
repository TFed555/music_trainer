add_library(log_module STATIC
    logger.h
)


target_link_libraries(log_module PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
)


target_include_directories(log_module PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

