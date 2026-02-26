#ifndef NOTEGENERATOR_H
#define NOTEGENERATOR_H
#pragma once

#include "IGenerator.h"

class NoteGenerator : public IGenerator
{
public:
    GeneratedAudio generate() override;
};

#endif // NOTEGENERATOR_H
