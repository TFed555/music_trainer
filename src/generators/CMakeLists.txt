find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(generators_module STATIC
    IGenerator.h
    GeneratedAudio.h
    intervals/IntervalGenerator.h
    intervals/IntervalGenerator.cpp
    chords/chordgenerator.h chords/chordgenerator.cpp notes/notegenerator.h notes/notegenerator.cpp
    rhythm/rhythmgenerator.h rhythm/rhythmgenerator.cpp
    generatedrhythm.h
)
target_link_libraries(generators_module PUBLIC music_module Qt::Core)
target_link_libraries(generators_module PRIVATE Qt${QT_VERSION_MAJOR}::Core)
