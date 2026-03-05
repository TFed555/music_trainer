set(CORE_MODULE_NAME "core")

find_package(PkgConfig REQUIRED)

pkg_check_modules(SNDFILE REQUIRED sndfile)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(core STATIC
    factory/registryfactory.h
    data/samples/samplerepository.h
    data/samples/samplerepository.cpp
    data/samples/sampleloader.h data/samples/sampleloader.cpp
    data/samples/sample.h

    controllers/iexercisecontroller.h
    controllers/intervalrecognisecontroller.h controllers/intervalrecognisecontroller.cpp
    controllers/tilescontroller.h controllers/tilescontroller.cpp
    sessions/intervalrecognisesession.cpp sessions/intervalrecognisesession.h
    sessions/isession.h  common/models/Note.h common/interfaces/IExerciseWidget
    common/models/Mode.h
    sessions/intervalidentifysession.h sessions/intervalidentifysession.cpp
    controllers/intervalidentifycontroller.h controllers/intervalidentifycontroller.cpp
    controllers/intervalbuildcontroller.h controllers/intervalbuildcontroller.cpp
    sessions/intervalbuildsession.h sessions/intervalbuildsession.cpp
    controllers/intervaldirectioncontroller.h controllers/intervaldirectioncontroller.cpp
    sessions/intervaldirectionsession.h sessions/intervaldirectionsession.cpp
)


target_link_libraries(core PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    ${SNDFILE_LIBRARIES}
)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/data
    ${CMAKE_CURRENT_SOURCE_DIR}/factory
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers
    ${SNDFILE_INCLUDE_DIRS}
)

