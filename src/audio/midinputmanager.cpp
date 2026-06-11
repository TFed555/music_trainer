#include "midinputmanager.h"
#include <QDebug>

MidiInputManager::MidiInputManager(QObject *parent) : QObject(parent),
 midiIn(std::make_unique<RtMidiIn>()){}

MidiInputManager::~MidiInputManager() {
    closeDevice();
}

void MidiInputManager::openDevice(int index) {
    closeDevice();
    midiIn->openPort(index);
    midiIn->setCallback(&MidiInputManager::callBack, this);
    midiIn->ignoreTypes(false, false, false);
}

void MidiInputManager::closeDevice() {
    if (midiIn->isPortOpen())
    {
        midiIn->cancelCallback();
        midiIn->closePort();
    }
}

QStringList MidiInputManager::availableDevices() {
    unsigned int portsCount = midiIn->getPortCount();
    QStringList ports;
    for (unsigned int i = 0; i < portsCount; i++) {
        std::string name = midiIn->getPortName(i);
        ports.append(QString::fromStdString(name));
        qDebug() << i;
    }
    return ports;
}

void MidiInputManager::callBack(double deltatime, std::vector< unsigned char > *message, void *userData) {
    unsigned int nBytes = message->size();
    for (unsigned int i=0; i<nBytes; i++)
        std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
    if (nBytes > 0)
        std::cout << "stamp = " << deltatime << std::endl;
    auto* manager =
        static_cast<MidiInputManager*>(userData);

    manager->processMessage(*message);
}

void MidiInputManager::processMessage(const std::vector<unsigned char>& message) {
    unsigned char status = message[0];
    unsigned char note = message[1];
    unsigned char velocity = message[2];
    unsigned char command = status & 0xF0;

    if (command == 0x90 && velocity > 0)
    {
        emit notePressed(note);
    }
    else if (command == 0x80 || (command == 0x90 && velocity == 0))
    {
        emit noteReleased(note);
    }
    qDebug() << "Status:" << status
             << "Note:" << note
             << "Velocity:" << velocity;
}
