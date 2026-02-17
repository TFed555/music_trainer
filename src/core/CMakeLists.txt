add_library(core STATIC
    registryfactory.h
)


target_link_libraries(core PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
)


target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

