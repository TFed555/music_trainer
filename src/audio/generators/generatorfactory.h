#ifndef GENERATORFACTORY_H
#define GENERATORFACTORY_H
#pragma once
#include "IGenerator.h"
#include "../../core/registryfactory.h"

enum GeneratorType {
    Interval,
    Chord
};

struct GeneratorParams {

};

class GeneratorFactory
{
public:
    static GeneratorFactory& instance();

    void registerGenerator(
        GeneratorType type,
        RegistryFactory<GeneratorType, IGenerator,
                        GeneratorParams>::Creator creator
        );

    std::unique_ptr<IGenerator>
    create(GeneratorType type, GeneratorParams params);


private:
    RegistryFactory<GeneratorType, IGenerator, GeneratorParams> factory;
};

#endif // GENERATORFACTORY_H
