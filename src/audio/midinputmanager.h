#ifndef MIDIINPUTMANAGER_H
#define MIDIINPUTMANAGER_H

#include <rtmidi/RtMidi.h>
#include <QObject>

class MidiInputManager : public QObject
{
    Q_OBJECT
public:
    explicit MidiInputManager(QObject *parent = nullptr);
    ~MidiInputManager();

    QStringList availableDevices();
    void openDevice(int index);
    void closeDevice();
    int getChosenDevice() {return selectedIdx == -1 ? 0 : selectedIdx + 1;};
signals:
    void notePressed(int midi);
    void noteReleased(int midi);
private:
    static void callBack(double deltatime, std::vector< unsigned char > *message, void *userData);
    void processMessage(const std::vector<unsigned char>& message);
    int selectedIdx = -1;
    std::unique_ptr<RtMidiIn> midiIn;
};

#endif // MIDIINPUTMANAGER_H
