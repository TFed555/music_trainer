#include "samplerepository.h"

SampleRepository::SampleRepository(SampleLoader* loader) : loader(loader) {

}

Sample SampleRepository::getSample(int midi) {
    char path[50];
    int nearestMidi = std::floor(midi / 3.0) * 3;
    sprintf(path, "../../../assets/samples/%d.wav", nearestMidi);
    Sample loadedSample = loader->loadSample(path, nearestMidi);
    return loadedSample;
}
