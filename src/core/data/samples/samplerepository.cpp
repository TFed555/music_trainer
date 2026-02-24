#include "samplerepository.h"

SampleRepository::SampleRepository(SampleLoader* loader) : loader(loader) {

}

Sample SampleRepository::getSample(int midi) {
    return loader->loadSample("", midi);
}
