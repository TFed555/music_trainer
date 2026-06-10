#include "samplerepository.h"
#include <QCoreApplication>

SampleRepository::SampleRepository(SampleLoader* loader) : loader(loader) {

}

Sample SampleRepository::getSample(int midi) {
    int nearestMidi = std::floor(midi / 3.0) * 3;
    QString path = QCoreApplication::applicationDirPath()
                   + "/assets/samples/" + QString::number(nearestMidi) + ".wav";
    Sample loadedSample = loader->loadSample(path.toStdString().c_str(), nearestMidi);
    return loadedSample;
}

Sample SampleRepository::getBeatSample(int type) {
    QString base = QCoreApplication::applicationDirPath() + "/assets/samples/";
    Sample loadedSample;
    switch (type) {
    case 0:
        loadedSample = loader->loadSample((base + "click_accent.wav").toStdString().c_str(), 0);
        break;
    case 1:
        loadedSample = loader->loadSample((base + "click.wav").toStdString().c_str(), 0);
        break;
    case 2:
        loadedSample = loader->loadSample((base + "user_click.wav").toStdString().c_str(), 0);
        break;
    }
    return loadedSample;
}
