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

    controllers/common/iexercisecontroller.h
    controllers/intervals/intervalrecognisecontroller.h controllers/intervals/intervalrecognisecontroller.cpp
    controllers/common/tilescontroller.h controllers/common/tilescontroller.cpp
    sessions/intervals/intervalrecognisesession.cpp sessions/intervals/intervalrecognisesession.h
    sessions/common/isession.h  common/models/Note.h common/interfaces/IExerciseWidget
    common/models/Mode.h
    sessions/intervals/intervalidentifysession.h sessions/intervals/intervalidentifysession.cpp
    controllers/intervals/intervalidentifycontroller.h controllers/intervals/intervalidentifycontroller.cpp
    controllers/intervals/intervalbuildcontroller.h controllers/intervals/intervalbuildcontroller.cpp
    sessions/intervals/intervalbuildsession.h sessions/intervals/intervalbuildsession.cpp
    controllers/intervals/intervaldirectioncontroller.h controllers/intervals/intervaldirectioncontroller.cpp
    sessions/intervals/intervaldirectionsession.h sessions/intervals/intervaldirectionsession.cpp
    controllers/chords/chordidentifycontroller.h controllers/chords/chordidentifycontroller.cpp
    sessions/chords/chordidentifysession.h sessions/chords/chordidentifysession.cpp
    controllers/chords/chordinversioncontroller.h controllers/chords/chordinversioncontroller.cpp
    sessions/chords/chordinversionsession.h sessions/chords/chordinversionsession.cpp
    controllers/chords/chordrootcontroller.h controllers/chords/chordrootcontroller.cpp
    sessions/chords/chordrootsession.h sessions/chords/chordrootsession.cpp
    factory/sessionfactory.h
    factory/sessionregistry.h
    controllers/chords/chordbuildcontroller.h controllers/chords/chordbuildcontroller.cpp
    sessions/chords/chordbuildsession.h sessions/chords/chordbuildsession.cpp
    common/models/Difficulty.h controllers/notes/noterecognisecontroller.h controllers/notes/noterecognisecontroller.cpp
    sessions/notes/noterecognisesession.h sessions/notes/noterecognisesession.cpp
    controllers/notes/notebuildcontroller.h controllers/notes/notebuildcontroller.cpp
    sessions/notes/notebuildsession.h sessions/notes/notebuildsession.cpp

)


target_link_libraries(core PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    ${SNDFILE_LIBRARIES}
)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/data
    ${CMAKE_CURRENT_SOURCE_DIR}/factory
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers
    ${SNDFILE_INCLUDE_DIRS}
)
target_link_libraries(core PUBLIC generators_module)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core)

