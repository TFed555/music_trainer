#include "generatorfactory.h"

GeneratorFactory& GeneratorFactory::instance()
{
    static GeneratorFactory inst;
    return inst;
}


void GeneratorFactory::registerGenerator(
    GeneratorType type,
    RegistryFactory<GeneratorType, IGenerator, GeneratorParams>::Creator creator)
{
    factory.registerFactory(type, std::move(creator));
}

std::unique_ptr<IGenerator>
GeneratorFactory::create(GeneratorType type, GeneratorParams params)
{
    return factory.create(type, params);
}


extern void forceLinkIntervalGenerator();

static int _interval_anchor = (forceLinkIntervalGenerator(), 0);
