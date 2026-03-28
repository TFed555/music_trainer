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

Sample SampleRepository::getBeatSample(int type) {
    Sample loadedSample;
    switch (type) {
    case 0:
        loadedSample = loader->loadSample("../../../assets/samples/click_accent.wav",0);
        break;
    case 1:
        loadedSample = loader->loadSample("../../../assets/samples/click.wav",0);
        break;
    case 2:
        loadedSample = loader->loadSample("../../../assets/samples/user_click.wav",0);
        break;
    }

    return loadedSample;
}
