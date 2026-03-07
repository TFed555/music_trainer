#ifndef CHORDGENERATOR_H
#define CHORDGENERATOR_H

#include "../IGenerator.h"

class ChordGenerator : public IGenerator<GeneratedChord>
{
public:
    GeneratedChord generate() override;
};

#endif // CHORDGENERATOR_H
