set(CORE_MODULE_NAME "core")

find_package(PkgConfig REQUIRED)

pkg_check_modules(SNDFILE REQUIRED sndfile)

add_library(core STATIC
    factory/registryfactory.h
    data/samples/samplerepository.h
    data/samples/samplerepository.cpp
    data/samples/sampleloader.h data/samples/sampleloader.cpp
    data/samples/sample.h
)


target_link_libraries(core PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    ${SNDFILE_LIBRARIES}
)


target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/data
    ${CMAKE_CURRENT_SOURCE_DIR}/factory
    ${SNDFILE_INCLUDE_DIRS}
)

