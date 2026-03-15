add_library(generators_module STATIC
    IGenerator.h
    GeneratedAudio.h
    intervals/IntervalGenerator.h
    intervals/IntervalGenerator.cpp
    chords/chordgenerator.h chords/chordgenerator.cpp notes/notegenerator.h notes/notegenerator.cpp
)
target_link_libraries(generators_module PUBLIC music_module Qt::Core)
