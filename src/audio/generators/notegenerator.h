#ifndef NOTEGENERATOR_H
#define NOTEGENERATOR_H
#pragma once

#include "IGenerator.h"

class NoteGenerator : public IGenerator
{
public:
    GeneratedAudio generate(int sampleRate, float durationSec) override;
};

#endif // NOTEGENERATOR_H
